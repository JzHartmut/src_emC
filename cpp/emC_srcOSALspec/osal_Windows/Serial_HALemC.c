#include <emC/HAL/Serial_HALemC.h>
#include <emC/OSAL/thread_OSemC.h>
#include <applstdef_emC.h>
#include <stdio.h>

#ifdef XXDEF_REFLECTION_FULL
  //#ifndef DEF_REFLECTION_NOXX
  #include <emC/HAL/genRefl/Serial_HALemC.crefl>
#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_Serial_HALemC) //may defined in the *.refloffs.c file
  //Class definition only as type marker: Note the ID_refl... may be used and should be planned application-wide.
  ClassJc const refl_Serial_HALemC = INIZ_ClassJc(refl_Serial_HALemC, "Serial_HALemC");
#endif



#undef INT32
#undef UINT32
#undef int64
#undef uint64

int32 trcRx_Serial[0x20] = {0};

static void writeTrc(int ix, char cc) {
  int ixTrc = trcRx_Serial[0];
  if(++ixTrc >= ARRAYLEN_emC(trcRx_Serial)) {
    ixTrc = 1;
  }
  trcRx_Serial[0] = ixTrc;
  trcRx_Serial[ixTrc] = (ix<<16) | (((uint32)cc) & 0xff);
}

//Windows-specific includes
#include <wtypes.h>
#include <winbase.h>

typedef struct InternalData_Serial_HALemC_T {
  int channel;
  //int volatile zBuffer;
  int volatile ixBufferRd;  //:used for ring buffer read and write 
  int volatile ixBufferWr;  //:for receiving bytes -ReadFile(...)
  int volatile run;
  int ctException;
  Thread_OSemC* hThread;
  HANDLE hPort;
  MemUnit valueBuffer[200];   //:the user buffer to get the data.
} InternalData_Serial_HALemC;

//for up to 10 serial channels, data allocated on open:
static InternalData_Serial_HALemC* thdata_g[10] = { 0 };

//This extra thread routine is necessary for the console because it blocks if not RETURN was pressed.
int rxThreadRoutine(void* data) {
  STACKTRC_ENTRY("rxThreadRoutine");
  InternalData_Serial_HALemC* thiz = C_CAST(InternalData_Serial_HALemC*, data);
  //thiz->ixFIFOrd = 0;
  //thiz->ixFIFOwr = 0;
  thiz->run = 1;
  DWORD dwBytesTransferred;
  while(thiz->run) {
    TRY{
      if(thiz->ixBufferRd == thiz->ixBufferWr) { // processed all
        thiz->ixBufferRd = thiz->ixBufferWr = 0; // only then read a new line
      }
      if(thiz->ixBufferWr ==0) {
        BOOL ok = ReadFile(thiz->hPort, thiz->valueBuffer, sizeof(thiz->valueBuffer), &dwBytesTransferred, 0);
        if (ok && dwBytesTransferred > 0) {  // anytime till ENTER, it is only for the console
          thiz->ixBufferWr = (int)dwBytesTransferred;
        }
      }
      Sleep(10);
    }_TRY
    CATCH(Exception, exc) {
      thiz->ctException += 1;                    //Exception maybe able to visit in Inspector
    }
    END_TRY
  }
  STACKTRC_RETURN 0;
}



void close_Serial_HAL_emC(int channel) {
  if(channel <0 || channel >9) { return; }
  InternalData_Serial_HALemC* thiz = thdata_g[channel];
  HANDLE hPort = thiz->hPort;
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
int open_Serial_HALemC ( int channel, Direction_Serial_HALemC dir
  , int32 baud, ParityStop_Serial_HALemC bytePattern) {
  char const* errorText = null;
  STACKTRC_ENTRY("open_Serial_OSAL_emC");
  HANDLE h1 = null;
  if(channel <0 ||channel >8) {
    errorText = "faulty channel, admissible 0..8";
  }
  else {                      //channel ok
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
    h1 = CreateFile( sPort, dirFile, 0, NULL, OPEN_EXISTING, mode, NULL );
    if (h1 == null || h1 == INVALID_HANDLE_VALUE) {
      errorText = "open fails, invalid handle";
    }
    else if (channel >= 1 && baud > 0) {
      DCB dcb;
      if (!GetCommState(h1, &dcb)) {
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

      if (!SetCommState(h1, &dcb)) {
        errorText = "SetCommState fails";
      }
      else {                //set immediate return from quest for CON 
        COMMTIMEOUTS commTimeout;
        if (!GetCommTimeouts(h1, &commTimeout)) {
          errorText = "GetCommTimeouts fails";
        }
        else {
          commTimeout.ReadIntervalTimeout = MAXDWORD;  //see https://docs.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-commtimeouts
          commTimeout.ReadTotalTimeoutConstant = 0;
          commTimeout.ReadTotalTimeoutMultiplier = 0;
          commTimeout.WriteTotalTimeoutConstant = 10;
          commTimeout.WriteTotalTimeoutMultiplier = 10;
          if (!SetCommTimeouts(h1, &commTimeout)) {
            errorText = "SetCommTimeouts fails";
          }
        }
      }
    }
    if(errorText ==null) {
    }
    if(errorText == null) {
      void* thdataVoid = malloc(sizeof(InternalData_Serial_HALemC));
      if (thdataVoid != null) {
        InternalData_Serial_HALemC* thdata = C_CAST(InternalData_Serial_HALemC*, thdataVoid);
        memset(thdata, 0, sizeof(*thdata));
        thdata->channel = channel;
        thdata->hPort = h1;
        if (channel == 0) {                      // create receiving thread for the console.
          //thdata->zBuffer = 0;
          //thdata->ixFIFOrd = 0;
          //thdata->ixFIFOwr = 0;
          thdata->hThread = alloc_Thread_OSemC(sPort, rxThreadRoutine, thdata, 128, 0);
        }
        thdata_g[channel] = thdata;                          //yet allow access to received data.
      }
      else {
        //TODO close
      }
    } else {
      if(h1 !=null && h1 != INVALID_HANDLE_VALUE) { 
        CloseHandle(h1); 
      }
    }
  }
  if(errorText != null) {
    THROW_s0(IllegalArgumentException, errorText, channel, 0);
  }
  STACKTRC_RETURN errorText == null ? 0 : -1;
}



int open_Com_HALemC(Com_HALemC_s* ithiz) {
  STACKTRC_ENTRY("open_Comm_HALemC");
  int ret = 0;
  if(INSTANCEOF_ObjectJc(&ithiz->base.object, refl_Serial_HALemC)) {  //check which type
    Serial_HALemC_s* thiz = C_CAST(Serial_HALemC_s*, ithiz);
    ret = open_Serial_HALemC(thiz->channel, thiz->dir, thiz->baud, thiz->bytePattern);
    thiz->base.comm_HAL_emC._handle_ = (const void*)thiz->channel;
  } else {
    THROW(IllegalArgumentException, z_StringJc("not expected"), 0,0);
  }
  STACKTRC_RETURN ret;
}



static InternalData_Serial_HALemC* getThiz ( int channel) {
  if(channel <0 || channel >8) { 
    THROW_s0n(IllegalArgumentException, "faulty serial port", channel, 0); 
    return null;
  }
  InternalData_Serial_HALemC* thiz = thdata_g[channel];
  if(thiz == null) {
    THROW_s0n(IllegalArgumentException, "serial port is not opened", channel, 0); 
  }
  return thiz;  //null only if no Exceptionhandling
}




void XXXprepareRx_Serial_HALemC ( int channel, void* valueBuffer, int zBuffer, int fromCurrent) {
  MemUnit* valueBuffer0 = C_CAST(MemUnit*, valueBuffer);  //C_CAST because it is a memory address.
  InternalData_Serial_HALemC* thiz = getThiz(channel);
  MemUnit* bufferCurr = thiz->valueBuffer;
  //thiz->valueBuffer = null;                //from now the rxThreadRoutine cannot write
  int ixBuffer = 0; //NOTE: mem is bytewise for PC
  if(fromCurrent >0) {
    int zCopy = thiz->ixBufferWr - fromCurrent;
    if(bufferCurr ==null) {
      ASSERT_emC(bufferCurr !=null && zCopy >=0, "?", 0,0);
    }
    if(zCopy > zBuffer) {
      zCopy = zBuffer;
    }
    if(zCopy >0) {
      memcpy( valueBuffer, bufferCurr + fromCurrent, zCopy);
      ixBuffer = zCopy;
    }
  }
  memset(valueBuffer0 + ixBuffer, 0, zBuffer - ixBuffer); 
  //thiz->zBuffer = zBuffer;
  thiz->ixBufferWr = ixBuffer;
  //thiz->valueBuffer = valueBuffer0;             //set buffer at last, up to now writing is possible.
}



int stepRx_Serial_HALemC ( int channel ) {
  STACKTRC_ENTRY("");
  InternalData_Serial_HALemC* thiz = getThiz(channel);
  if(channel ==0) {                              // console:
    //ixBufferWr was incremented in RxThread
  }
  else {
    //try to get all received bytes from Windows:
    DWORD dwBytesTransferred = 0;
    int zBytes = -1;
    BOOL ok = true;
    if(thiz->ixBufferWr >= thiz->ixBufferRd) {  //free till end | ___ rd 1111 wr ->--|
      zBytes = sizeof(thiz->valueBuffer) - thiz->ixBufferWr;
      ok = ReadFile(thiz->hPort, &thiz->valueBuffer[thiz->ixBufferWr], zBytes, &dwBytesTransferred, 0);
      //ReadFile returns immediately with the number of transferred bytes because the timeout is 0.
      if (ok && dwBytesTransferred > 0) {
        thiz->ixBufferWr += (int)(dwBytesTransferred);
        ASSERT_emC(thiz->ixBufferWr <= sizeof(thiz->valueBuffer), "internal", 0, 0);
      }
    }
    if (thiz->ixBufferWr >= sizeof(thiz->valueBuffer) && thiz->ixBufferRd >0 ) {
      ASSERT_emC(thiz->ixBufferWr <= sizeof(thiz->valueBuffer), "internal", 0, 0);
      thiz->ixBufferWr = 0;                      // wrap only if at least 1 byte is read, elsewhere the buffer is seen as empty.
    }
    // fill the rest till ixBufferRd -1: | 111 wr ->--_ rd 111|
    zBytes = thiz->ixBufferRd - thiz->ixBufferWr -1; //1 byte space, to distinguish empty from full buffer
    if(zBytes >0) {
      ok = ReadFile(thiz->hPort, &thiz->valueBuffer[thiz->ixBufferWr], zBytes, &dwBytesTransferred, 0);
      if(ok && dwBytesTransferred >0) {
        thiz->ixBufferWr += (int)(dwBytesTransferred);
      }
    }
    if(!ok) {
      THROW_s0(IllegalStateException, "serial read error", 0,0);
    }
  }
  int nrofBytesAvail = thiz->ixBufferWr - thiz->ixBufferRd; //expecting: //wrapping state: |___ ixRd 111 ixWr ___ |
  if(nrofBytesAvail <0) { 
    nrofBytesAvail += sizeof(thiz->valueBuffer); //wrapping state: |111 ixWr ___ ixRd 111 |
  }
  STACKTRC_RETURN nrofBytesAvail;
}


int getChar_Serial_HALemC ( int channel ) {
  STACKTRC_ENTRY("getChar_Serial_HALemC");
  InternalData_Serial_HALemC* thiz = getThiz(channel);
  if(thiz->ixBufferWr != thiz->ixBufferRd) {
    int cc = thiz->valueBuffer[thiz->ixBufferRd];
    if(++thiz->ixBufferRd >= sizeof(thiz->valueBuffer)) {
      thiz->ixBufferRd = 0;  //wrap
    }
    STACKTRC_RETURN cc;
  } else {
    return -1;
  }
}




int getData_Serial_HALemC ( int channel, void* dst, int fromByteInDst, int zDst ) {
  InternalData_Serial_HALemC* thiz = getThiz(channel);
  int nBytes = thiz->ixBufferWr - thiz->ixBufferRd;
  if(nBytes <0) {      // wr is wrapped
    nBytes = sizeof(thiz->valueBuffer) - thiz->ixBufferRd;
  }
  if(nBytes > zDst) {
    nBytes = zDst;
  }
  if(nBytes >0) {
    memcpy(((MemUnit*)dst)+fromByteInDst, thiz->valueBuffer + thiz->ixBufferRd, nBytes);
    thiz->ixBufferRd += nBytes;
  }
  int nBytesSum = nBytes;
  if(thiz->ixBufferRd >= sizeof(thiz->valueBuffer) ){ //wrapped
    thiz->ixBufferRd = 0;
    nBytes = thiz->ixBufferWr;
    if(nBytes > (zDst - nBytesSum)) {
      nBytes = zDst - nBytesSum;  //0 if all was read exact before wrap.
    }
    if(nBytes >0) {
      memcpy(((MemUnit*)dst)+fromByteInDst + nBytesSum, thiz->valueBuffer + thiz->ixBufferRd, nBytes);
      thiz->ixBufferRd += nBytes;
      nBytesSum += nBytes;
    } 
  }
  return nBytesSum;
}


int txData_Serial_HALemC ( int const channel, void const* const data, int const fromCharPos, int const zChars) {
  void* data01 = WR_CAST(void*, data);  //unfortunately C++ or Visual Studio does not allow const* to const* cast
  MemUnit const* const data0 = C_CAST(MemUnit const*, data01);  //It is a memory pointer
  if(channel == 0) {
    for(int ix = fromCharPos; ix < zChars; ++ix) {
      char cc = data0[ix];
      putchar( cc );
    }
    return 0;
  }
  else {
    InternalData_Serial_HALemC* thiz = getThiz(channel);
    DWORD byteswritten = 0;
    MemUnit const* dataCurr = data0 + fromCharPos;
    int zCharsCt = zChars;
    BOOL retVal;
    while( --zCharsCt >=0) {     // writes byte for byte.
      retVal = WriteFile(thiz->hPort, dataCurr, 1, &byteswritten, NULL);
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



int busyTx_Serial_HAL_emC ( int channel) { return 0; }  // never busy. chars are transmitted.

int txChars_Serial_HALemC ( int const channel, char const* const text, int const fromCharPos, int const zChars) {
  return txData_Serial_HALemC(channel, text, fromCharPos, zChars);
}


int stepTx_Serial_HALemC ( int const channel) {
  return 0;
}