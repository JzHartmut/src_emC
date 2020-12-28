#include <emC/AsciiMoni/AsciiMoni.h>
#include <emC/Base/StringPacked_emC.h>
#include <emC/Base/StringBase_emC.h>

#include <emC/HAL/serial_HALemC.h>
#include <emC/Base/Time_emC.h>
#include <emC/HAL/SystemSettings_HALemC.h>
#include <string.h> //memset



void AsciiMoni_emC::init ( int channelRx, int channelTx, int channelEcho) {
  this->channelRx = channelRx;
  this->channelTx = channelTx;
  this->channelEcho = channelEcho;
  prepareRx_Serial_HALemC(this->channelRx, (MemUnit*)this->rxBuffer, sizeof(this->rxBuffer), 0);
  this->ixCharChecked = this->ixCharEcho = this->zPending = 0;
  this->bFirst = 0;
  strncpy_emC(this->testTxt, "abcdefg\r\n", ARRAYLEN_emC(this->testTxt));
}



int AsciiMoni_emC::evalRx ( ) {
  int nWaitCharacters;
  int zRx = hasRxChars_Serial_HALemC(this->channelRx);
  int zRxEcho = zRx - this->ixCharEcho; //echo only new chars
  if(zRxEcho >0) {                                               //new characters
    nWaitCharacters = zRxEcho;
    if(this->channelEcho >=0) {
      this->zPending = tx_Serial_HALemC(this->channelEcho, this->rxBuffer, this->ixCharEcho, zRx);
    }
    if(zPending >=0) {  //0 is expectable, >0 only in not manual typed commands.
      this->ixCharEcho += zRxEcho - zPending;
    } //else: error or buffer not free, remain ixCharEcho.
    if(this->zPending ==0) {                             //check only rxBuffer if all characters are echoed.
      char cc;
      int zCmd = 0;
      for(int ix = this->ixCharChecked; ix < zRx; ++ix) {//check whether a 0x0d is received (ENTER key)
        cc = getCharPacked(this->rxBuffer, ix);
        if(cc == '\r') { 
          zCmd = ix;
          break; 
        }
      }
      int zCmdEnd;
      for(zCmdEnd = zCmd +1; zCmdEnd < zRx; ++zCmdEnd) {//check whether a 0x0d is received (ENTER key)
        cc = getCharPacked(this->rxBuffer, zCmdEnd);
        if(cc != '\r' && cc != '\n') { 
          break; 
        }
      }
      if(zCmd >0) {                                   //ENTER key is 0x0d or \r
        if(this->channelEcho >=0) {
          txChar_Serial_HALemC(this->channelEcho, "\n", 0, 1);              //complete echo with \n
        }
        nWaitCharacters += evalCmd(zCmd);
        prepareRx_Serial_HALemC(this->channelRx, this->rxBuffer, sizeof(this->rxBuffer), zCmdEnd);
        this->ixCharEcho = 0;
        this->ixCharChecked = 0;
      } else if(zRx == ARRAYLEN_emC(this->rxBuffer)) {
        if(this->channelTx >=0) {
          txChar_Serial_HALemC(this->channelEcho, "\r\nRETURN not found\r\n", 0, 21);              //complete echo with \n
        }
        prepareRx_Serial_HALemC(this->channelRx, this->rxBuffer, sizeof(this->rxBuffer), 0);
        this->ixCharEcho = 0;
        this->ixCharChecked = 0;
      } else {
        this->ixCharChecked = zRx;
      }
    }
  } else {
    nWaitCharacters = 5;   //nothing received, check after 5 character times again
  }
  return nWaitCharacters;
}


int AsciiMoni_emC::step ( ) {
  int nWaitCharacters;
  if(this->zPending >0) {                                //if some chars are pending to send:
    nWaitCharacters = this->zPending;                    //try to send what is pending still yet.
    this->zPending = stepTx_Serial_HALemC(this->channelTx); 
  } else {
    if(this->bFirst) {
      this->bFirst = 0;
      this->zPending = txChar_Serial_HALemC(this->channelTx, "test Appl_MotorCtrl\r\n", 0, 999);
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


//Standard implementation (virtual)
int AsciiMoni_emC::evalCmd ( int zCmd ) {
  return 0;
}
