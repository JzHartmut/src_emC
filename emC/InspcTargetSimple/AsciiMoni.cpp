#include <emC/InspcTargetSimple/AsciiMoni.h>

#include <emC/Base/StringPacked_emC.h>
#include <emC/Base/StringBase_emC.h>

#include <emC/HAL/serial_HALemC.h>
#include <emC/Base/Time_emC.h>
#include <emC/HAL/SystemSettings_HALemC.h>
#include <string.h> //memset
#include <stdio.h>  //snprintf


int dbgStop() {
  return 0;
}


AsciiMoni_emC::AsciiMoni_emC ( void const* mainDataArg, ClassJc const* refl) //int32 const* reflMainDataArg )
: mainData(mainDataArg), reflMainData(refl->reflOffs) //MainDataArg)
{
  this->ixInspcTelg = -1;
  this->stateRxInspcTelg = 0;
  ctor_Target2Proxy_Inspc(&this->inspcAccess.object, &this->rxInspc, &this->txInspc);
}



void AsciiMoni_emC::init ( int channelRx, int channelTx, int channelEcho) {
  this->channelRx = channelRx;
  this->channelTx = channelTx;
  this->channelEcho = channelEcho;
  this->timeoutRx = 2000000000L /  systemSettings_HwCpu_emC.clkCpu_ns;
  this->initRx();
  this->ixCharChecked = this->ixCharEcho = this->zPendingTx = 0;
  this->bFirst = 0;
}



int AsciiMoni_emC::evalRx ( ) {
  int nWaitCharacters = 12;
  this->ctEvalRx +=1;                  //only for debug view, ct calls
  int nChars;
  do {
    nChars = stepRx_Serial_HALemC(this->channelRx);   //chars available, care receive buffer
    switch(this->stateRxInspcTelg) {     //State machine for InspcTelg
      case 1: {
        int cc = getChar_Serial_HALemC(this->channelRx);
        if(cc == 0x01) {
          this->zRx = 0;
          this->stateRxInspcTelg = 2;    //expect Inspc Command
          nWaitCharacters = 12;
        } else {
          this->stateRxInspcTelg = 0;    //other character after escape, ignore. Do not echo.
          this->initRx();
        }
      }  break;
      case 2: {
        if(this->zRx >0) {
          dbgStop();
        }
        int zRx = getData_Serial_HALemC (this->channelRx, &this->rxInspc, this->zRx, sizeof(this->rxInspc));
        nChars -= zRx -1;              //do not repeat.
        if(zRx == 16) {
          this->w1 = this->rxInspc.length_seq_cmd;
          if((this->w1 & 0xffff0000) == 0x00100000) {
            step_Target2Proxy_Inspc(&this->inspcAccess, this->mainData, this->reflMainData, reflectionOffsetArrays);
            this->initRx();
            int txBytes = sizeof(this->txInspc) * BYTE_IN_MemUnit;
            this->test_txPendingAfterInspc = this->zPendingTx = txData_Serial_HALemC(this->channelTx, (MemUnit*)&this->txInspc, 0, txBytes);
            nWaitCharacters = txBytes;                 //wait till all is transmitted.
          } else {
            nWaitCharacters = 5;                      //faulty command, clear!
            this->initRx();
          }                                            //switch back to the previous buffer, continue there.
        }
        else if(zRx == this->zRx) {
          this->initRx();               //timeout, no newer bytes received.
          zRx = 0;
        }
        this->zRx = zRx;
      } break;
      default: {                         //expected an ordinary character
        int cc = getChar_Serial_HALemC(this->channelRx);
        if(cc !=-1) {                    //char received, check it
          switch(cc) {
            case 0x1b: {
              this->stateRxInspcTelg = 1;
              nWaitCharacters = 2;
            } break;
            case '\r': {                 //ENTER or RETURN key as line end
              if(this->zCmd <0 ) {
                this->zCmd = this->ixCharChecked;  //execute command
              } //else: zCmd as single-char command is always in execution.
            } break;
            case '\n':                   //newline: ignore
              this->initRx();
              break;
            case 0x8:                    //Back space
              break;
            default: {
              if(this->ixCharChecked ==0 && cc == 'n') {
                this->rxBuffer[ 0 ] = cc;
                this->zCmd = 1;          //execute "n" as simple command without need of \r
              }
              else if(cc >= ' ') {            //textual character: store it.
                if(this->ixCharChecked < ARRAYLEN_emC(this->rxBuffer)) {
                  this->rxBuffer[ this->ixCharChecked] = cc;
                  this->ixCharChecked +=1;
                }
              }
              else {
                this->initRx();
              }
            } //default
          } //switch cc
        } //!=-1,                 //-1 is: nothing received.
      }//default
    }//switch
  } while (--nChars >0);
  return nWaitCharacters;    //wait for 12 characters
}


int AsciiMoni_emC::step ( ) {
  int nWaitCharacters;
  if(this->channelRx ==-1) { 
    return 200;                          //no serial communication.
  }
  if(this->zPendingTx >0) {                                //if some chars are pending to send:
    nWaitCharacters = this->zPendingTx;                    //try to send what is pending still yet.
    this->zPendingTx = stepTx_Serial_HALemC(this->channelTx); 
  } else if(this->ixCharChecked > this->ixCharEcho) {
    int zTx = this->ixCharChecked - this->ixCharEcho;      //tx echo
    this->zPendingTx = txChar_Serial_HALemC(this->channelTx, &this->rxBuffer[this->ixCharEcho], 0, zTx);
    this->ixCharEcho = this->ixCharChecked;
    nWaitCharacters = zTx;                                  //wait for tx echo
  } else if(this->zCmd >=0) {
    evalCmd(this->zCmd);
    //this->zPendingTx = txChar_Serial_HALemC(this->channelTx, "\r\ncmd\r\n", 0, 999);
    this->zCmd = -1;
  } else {
    if(this->bFirst) {
      this->bFirst = 0;
      this->zPendingTx = txChar_Serial_HALemC(this->channelTx, "test Appl_MotorCtrl\r\n", 0, 999);
    }
    else {
      //do only accept new commands if tx is not pending.
      //because a new tx can only start if the old one is finished.
      //but the receiving itself can be done.
      nWaitCharacters = this->evalRx();
        
    }
  }
  if(nWaitCharacters >16) {
    nWaitCharacters = 16;
  } else if(nWaitCharacters <5) {
    nWaitCharacters = 5;                                 //wait 0.45 ... 1.5 ms till next check and transmit.
  }                                                      //90 µs per Byte 115200 Baud.
  return nWaitCharacters;
}


char* writeHex(char* dst, int zDigit, int32 number) {
  while(--zDigit >=0) {
    int ixBit = zDigit*4;
    char const* digits = "0123456789AbCdef";
    char cc = digits[( (number>>ixBit) & 0x0f)];
    *dst++ = cc;
  }
  return dst;
}

char* writeMemLine(char* dst, int32 addr) {
  dst = writeHex(dst, 6, addr);
  *dst++ = ':'; *dst++ = ' ';
  MemUnit* src = C_CAST(MemUnit*, addr);
  for(int ix = 0; ix < 8; ++ix) {
    int val = *src++;
    dst = writeHex(dst, 4, val);
    *dst++ = ' ';
  }
  dst = strcpy(dst, "\r\n")+2;
  return dst;
}


//Standard implementation (virtual)
int AsciiMoni_emC::evalCmd ( int zCmd ) {
  int nWaitCharacters;
  if(zCmd ==0) {
      writeMemLine(this->txCharBuffer, this->memaddr);
      this->zPendingTx = txChar_Serial_HALemC(1, this->txCharBuffer, 0, ARRAYLEN_emC(this->txCharBuffer));
  }
  else if(this->rxBuffer[0] == 'n') {
    this->memaddr += 0x10;
    writeMemLine(this->txCharBuffer, this->memaddr);
    this->zPendingTx = txChar_Serial_HALemC(1, this->txCharBuffer, 0, ARRAYLEN_emC(this->txCharBuffer));
  }
  else if(strncmp_emC(this->rxBuffer, "dm ", 3) ==0) {
    //display memory
    this->memaddr = parseIntRadix_emC(rxBuffer+3, zCmd -3, 16, null);
    if(this->memaddr >=0 && this->memaddr < 0xfffff0) {
      //Note: snprintf uses a lot of memory, and does not work properly ...
      //snprintf(this->txCharBuffer, ARRAYLEN_emC(this->txCharBuffer), "\r\n%6.6X ....\r\n", addr);
      char* dst = strcpy(this->txCharBuffer, "\r\n") +2;
      writeMemLine(dst, this->memaddr);
      this->zPendingTx = txChar_Serial_HALemC(1, this->txCharBuffer, 0, ARRAYLEN_emC(this->txCharBuffer));
    } else {
      this->zPendingTx = txChar_Serial_HALemC(1, "faulty mem address, range 0...0xfffff0", 0, 999);
    }
  } else {
    this->zPendingTx = txChar_Serial_HALemC(1, "...wrong cmd, admissible: dm \n", 0, 29);
    nWaitCharacters = 29;
  }
  this->initRx();
  return nWaitCharacters;
}


void AsciiMoni_emC::initRx() {
  memset(this->rxBuffer, 0, ARRAYLEN_emC(this->rxBuffer));
  this->zRx = 0;
  this->zCmd = -1;
  this->stateRxInspcTelg = 0;                //expect an Inspc telg
  this->ixCharChecked = 0;
  this->ixCharEcho = 0;
}
