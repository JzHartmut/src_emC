#include <emC/AsciiMoni/AsciiMoni.h>
#include <emC/Base/StringPacked_emC.h>
#include <emC/HAL/Serial_HALemC.h>

int AsciiMoni_emC::evalCmd ( int zCmd ) {
  int nWaitCharacters;
  if(strncmpPacked_emC(this->rxBuffer, "dm ", 3) ==0) {
    //display memory
    testTxt[0] +=1;
    if(testTxt[0] >'z'){
      testTxt[0] = 'A';
    }
    this->zPending = txChar_Serial_HALemC(1, testTxt, 0, sizeof(testTxt));
    nWaitCharacters = sizeof(testTxt);
  } else {
    this->zPending = txChar_Serial_HALemC(1, "...wrong cmd, admissible: dm \n", 0, 29);
    nWaitCharacters = 29;
  }
  return nWaitCharacters;      

}