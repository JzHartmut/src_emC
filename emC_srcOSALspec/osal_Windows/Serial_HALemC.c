#include <emC/HAL/Serial_HALemC.h>
#include <emC/OSAL/os_thread.h>
#include <applstdef_emC.h>
#include <stdio.h>

#undef INT32
#undef UINT32
#undef int64
#undef uint64


//Windows-specific includes
#include <wtypes.h>
#include <winbase.h>

typedef struct RxThread_Serial_HALemC_T {
  int channel;
  int zBuffer;
  int ixBuffer;           //:index already transferred characters from FIFO (rxFIFO) to valueBuffer.
  //MemUnit rxFIFO[32];  //:the internal rxFIFO
  //int ixFIFOrd;                  //.....^           ^            |
  //int ixFIFOwr;                 //     store       read
  int run;
  OS_HandleThread hThread;
  HANDLE hPort;
  MemUnit* valueBuffer;   //:the user buffer to get the data.
} RxThread_Serial_HALemC;

//handles for CONIN, CONOUT and 8 UART, null if not opened.
static HANDLE hUART_g[10][2] = {{null, null}};  

static RxThread_Serial_HALemC* thdata_g[10];


int rxThreadRoutine(void* data) {
  RxThread_Serial_HALemC* thiz = C_CAST(RxThread_Serial_HALemC*, data);
  //thiz->ixFIFOrd = 0;
  //thiz->ixFIFOwr = 0;
  thiz->run = 1;
  DWORD dwBytesTransferred;
  while(thiz->run) {
    /*
    int zFree;
    if(thiz->ixFIFOrd == ARRAYLEN_emC(thiz->rxFIFO)) { //all was read till end
      thiz->ixFIFOrd = thiz->ixFIFOwr = 0;          //start from begin, ringbuffer
    } 
    zFree = ARRAYLEN_emC(thiz->rxFIFO) - thiz->ixFIFOwr;  //fill till end
    */
    //
    //if(zFree >0) {
    if(thiz->ixBuffer < thiz->zBuffer) {
      int rxByte = 0;  //write received data in stack is possible.
      //MemUnit* pRxBuffer = &thiz->rxFIFO[thiz->ixFIFOwr];
      //BOOL ok = ReadFile (thiz->hPort, pRxBuffer, zFree, &dwBytesTransferred, 0);
      //it stores only one received byte immediately local:
      BOOL ok = ReadFile (thiz->hPort, &rxByte, 1, &dwBytesTransferred, 0);
      if(ok && dwBytesTransferred >0) {
        MemUnit* buffer;
        int ix, ixExpected;
        int ctAbort = 3;
        do {
          do {
            buffer = thiz->valueBuffer;
            ix = thiz->ixBuffer;
            if(buffer ==null) {                  //if the buffer is not available, possible set a new one
              Sleep(1);                          //then wait. do not store the byte.
            }                                    //other meanwhile received bytes are stored internally. 
          } while(buffer ==null);
          ixExpected = ix = thiz->ixBuffer;
          thiz->valueBuffer[ix] = (char)(rxByte);
          int ixNew = ix+1;
          //thiz->ixFIFOwr += (int)(dwBytesTransferred);
          ix = compareAndSwap_AtomicInteger(&thiz->ixBuffer, ix, ixNew);
        } while(ix != ixExpected && --ctAbort >=0); 
        ASSERT_emC(ctAbort >=0, "internal error rxThreadRoutine Serial_emC", ctAbort, thiz->channel);         
      } else {                                   //timeout on ReadFile
        Sleep(10);
      }
    } else {                                     //rxFIFO is full, should be read, 
      Sleep(10);
    }               
  }
  return 0;
}



void close_Serial_HAL_emC(int channel) {
  if(channel <0 || channel >9) { return; }
  HANDLE hPort = hUART_g[channel][0];
  RxThread_Serial_HALemC* thiz = thdata_g[channel];
  thdata_g[channel] = null;
  BOOL ok = 1;
  if(thiz != null) {
    thiz->run = 0;
  }
  if(hPort !=null) {
    ok = CancelIoEx(hPort, 0);
    ok = CloseHandle(hPort);
    if(!ok) {
      STACKTRC_ENTRY("close_Serial_OSAL_emC");
      THROW_s0(IllegalArgumentException, "close faulty", 0, 0);
      STACKTRC_LEAVE;
    } 
  }
  if(thiz != null) {
    free(thiz);
  }
}



//0 is console, 1...8 = COM1..8
int init_Serial_HALemC ( int channel, Direction_Serial_HALemC dir
  , int32 baud, ParityStop_Serial_HALemC bytePattern) {

  int erret = 0;
  char const* errorText = null;
  STACKTRC_ENTRY("open_Serial_OSAL_emC");
  if(channel <0 ||channel >8) {
    erret = -1;
    errorText = "faulty channel, admissible 0..8";
    STACKTRC_RETURN erret;
  }
  char sPort[5]; 
  if(channel ==0) {
    strcpy(sPort, "CON");   //with 0, 5 chars
  } else {
    strcpy(sPort, "COM1");   //with 0, 5 chars
    sPort[3] = '0' + channel;  //character 1...8
  }
  int dirFile = 0;
  if(dir & toRead_Serial_HALemC) { dirFile |= GENERIC_READ; }
  if(dir & toWrite_Serial_HALemC) { dirFile |= GENERIC_WRITE; }
  uint32 mode = 0; //FILE_FLAG_OVERLAPPED;
  HANDLE h1 = CreateFile( sPort, dirFile, 0, NULL, OPEN_EXISTING, mode, NULL );
  DCB dcb;
  if (h1 == null || h1 == INVALID_HANDLE_VALUE) {
    errorText = "open fails, invalid handle";
    erret = -26;
  } else if(channel >=1 && baud >0) {
    if (!GetCommState(h1,&dcb)) {
      erret = -4;
      errorText = "GetCommState fails";
    }
    dcb.BaudRate = baud;
    dcb.ByteSize = 8; //8 data bits
    int parity = (bytePattern & ParityOddStop1_Serial_HALemC) ? ODDPARITY :
                 (bytePattern & ParityEvenStop1_Serial_HALemC) ? EVENPARITY :
                 NOPARITY;
    dcb.Parity = parity;
    dcb.StopBits = (bytePattern & ParityNoStop2_Serial_HALemC) ? TWOSTOPBITS : ONESTOPBIT;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcb.fOutxDsrFlow = 0;
    dcb.fOutxCtsFlow = 0;
    dcb.fDsrSensitivity = 0;
    dcb.fOutX = 0;
    dcb.fInX = 0;

    if (!SetCommState(h1,&dcb)) {
      erret = -3;
      errorText = "SetCommState fails";
    } else {

      COMMTIMEOUTS commTimeout;
      if(!GetCommTimeouts(h1, &commTimeout)) {
        errorText = "GetCommTimeouts fails";
      } else {
        commTimeout.ReadIntervalTimeout = MAXDWORD;  //see https://docs.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-commtimeouts
        commTimeout.ReadTotalTimeoutConstant = 0;
        commTimeout.ReadTotalTimeoutMultiplier = 0;
        commTimeout.WriteTotalTimeoutConstant = 10;
        commTimeout.WriteTotalTimeoutMultiplier = 10;
        if(!SetCommTimeouts(h1, &commTimeout)) {
          errorText = "SetCommTimeouts fails";
          erret = -3;
        }
      }
    }
  }
  if(erret ==0 && errorText == null) {
    hUART_g[channel][0] = h1;  //store static globally
    void* thdataVoid = malloc(sizeof(RxThread_Serial_HALemC));
    RxThread_Serial_HALemC* thdata = C_CAST(RxThread_Serial_HALemC*, thdataVoid);
    thdata->valueBuffer = null;    //
    thdata->zBuffer = 0;
    thdata->channel = channel;
    //thdata->ixFIFOrd = 0;
    //thdata->ixFIFOwr = 0;
    thdata->hPort = h1;
    os_createThread(&thdata->hThread, rxThreadRoutine, thdata, sPort, 128, 0);
    thdata_g[channel] = thdata;                          //yet allow access to received data.
  } else {
    CloseHandle(h1);
    THROW_s0(IllegalArgumentException, errorText, channel, erret);
  }
  STACKTRC_RETURN erret;
}




void prepareRx_Serial_HALemC ( int channel, MemUnit* valueBuffer, int zBuffer, int fromCurrent) {
  if(channel <0 || channel >8) { 
    THROW_s0n(IllegalArgumentException, "faulty serial port", channel, 0); 
    return;
  }
  HANDLE hPort = hUART_g[channel][0];
  RxThread_Serial_HALemC* thdata = thdata_g[channel];
  if(hPort == null || thdata == null) {
    THROW_s0n(IllegalArgumentException, "serial port is not opened", channel, 0); 
    return;
  }
  int ixBuffer = 0;
  if(fromCurrent >0) {
    MemUnit* bufferCurr = thdata->valueBuffer;
    thdata->valueBuffer = null;                //from now the rxThreadRoutine cannot write
    int zCopy = thdata->ixBuffer - fromCurrent;
    ASSERT_emC(bufferCurr !=null && zCopy >=0, "?", 0,0);
    if(zCopy > zBuffer) {
      zCopy = zBuffer;
    }
    if(zCopy >0) {
      memcpy( valueBuffer, bufferCurr + fromCurrent, zCopy);
      ixBuffer = zCopy;
    }
  }
  thdata->zBuffer = zBuffer;
  thdata->ixBuffer = ixBuffer;
  thdata->valueBuffer = valueBuffer;             //set buffer at last, up to now writing is possible.
}


//int readBinary_Serial_OSAL_emC(int channel, MemUnit* buffer, int zBuffer) {
int hasRxChars_Serial_HALemC ( int channel ) {
  if(channel <0 || channel >8) { 
    THROW_s0n(IllegalArgumentException, "faulty serial port", channel, 0); 
    return 0;
  }
  HANDLE hPort = hUART_g[channel][0];
  RxThread_Serial_HALemC* thiz = thdata_g[channel];
  if(hPort == null) {
    THROW_s0n(IllegalArgumentException, "serial port is not opened", channel, 0); 
    return 0; 
  }
//  DWORD dwBytesTransferred = 0;
//  BOOL ok;
//  ok = PeekNamedPipe(hPort, null, 0, 0, &dwBytesTransferred, null);
//  if(dwBytesTransferred ==0) {
//    return 0; 
//  } else 
#if 0
    int zFree;
    if(thiz->ixFIFOrd == ARRAYLEN_emC(thiz->rxFIFO)) { //all was read till end
      thiz->ixFIFOrd = thiz->ixFIFOwr = 0;          //start from begin, ringbuffer
    } 
    zFree = ARRAYLEN_emC(thiz->rxFIFO) - thiz->ixFIFOwr;  //fill till end
    //if(zFree >0) {
      DWORD dwBytesTransferred;
      static OVERLAPPED overlapped = {0};
      DWORD error = 0;
      MemUnit* pRxBuffer = &thiz->rxFIFO[thiz->ixFIFOwr];
      BOOL ok = ReadFile (thiz->hPort, pRxBuffer, zFree, &dwBytesTransferred, &overlapped);
      if(!ok) {
        error = GetLastError();
        if(error == ERROR_IO_PENDING) {
        } else {
          error = 0;
        }
      }
      if(ok && dwBytesTransferred >0) {
        thiz->ixFIFOwr += (int)(dwBytesTransferred);
      }
    //}  
#endif

#if 0 //receive only 1 byte in READFILE
    int nrCharsAvail = thiz->ixFIFOwr - thiz->ixFIFOrd;
  for(int ix = 0; ix < nrCharsAvail; ++ix) {
    if(thiz->ixBuffer >= thiz->zBuffer) {
      break;                                               //no more space in valueBuffer
    }
    thiz->valueBuffer[thiz->ixBuffer++] = thiz->rxFIFO[thiz->ixFIFOrd++];
  }
#endif
  return thiz->ixBuffer;
}






int tx_Serial_HALemC ( int const channel, MemUnit const* const data, int const fromCharPos, int const zChars) {
  if(channel == 0) {
    for(int ix = fromCharPos; ix < zChars; ++ix) {
      char cc = data[ix];
      putchar( cc );
    }
    return 0;
  }
  else if(channel <0 || channel >8) { 
    return 0; 
  }
  else {
    RxThread_Serial_HALemC* thiz = thdata_g[channel];    
    HANDLE hPort = hUART_g[channel][0];
    DWORD byteswritten = 0;
    MemUnit const* dataCurr = data + fromCharPos;
    int zCharsCt = zChars;
    BOOL retVal;
    while( --zCharsCt >=0) {
      retVal = WriteFile(hPort, dataCurr, 1, &byteswritten, NULL);
      dataCurr +=1;
      if(!retVal) {break; } 
    }
    if(retVal) {
      return zChars - ((int)byteswritten);  //often 0
    } else {
      THROW_s0n(IllegalStateException, "txSerial_HALemC", channel, zChars);
      return 0;
    }
  }
}



int txChar_Serial_HALemC ( int const channel, char const* const text, int const fromCharPos, int const zChars) {
  return tx_Serial_HALemC(channel, text, fromCharPos, zChars);
}


int stepTx_Serial_HALemC ( int const channel) {
  return 0;
}