

#include <emC/Base/StringBase_emC.h>
#include <emC/Base/StringNum_emC.h>
#include <emC/HAL/Serial_HALemC.h>
#include <emC/Base/EventTask_emC.h>
#include <emC/InspcTargetSimple/AsciiMoni_emC.h>

// private encapsulated operations:

void execCmd_AsciiMoni_emC ( AsciiMoni_emC_s* thiz, int zChars );






//Note: The hardware, serial interface, should be already intiialized, operations from Serial_HAL can be used.
void ctor_AsciiMoni_emC ( AsciiMoni_emC_s* thiz, int nrSerialChn) {
  thiz->flags.val.channel = nrSerialChn;
  thiz->flags.bit.bEcho = 1;
  thiz->flags.bit.bTxState = 1;
}




void txStatus_AsciiMoni_emC ( AsciiMoni_emC_s* thiz, char const* text) {
  if(  thiz->flags.bit.bTxState ==1
    && thiz->flags.val.ixRxChars ==0      // nothing currently received
    && thiz->flags.bit.bRxTxAnswer ==0
    && busyTx_Serial_HAL_emC(thiz->flags.val.channel) ==0 // thiz->flags.bit.bTxPending ==0
    ) {
    int zChars = strnlen_emC(text, 100);
    txChars_Serial_HALemC(thiz->flags.val.channel, text, 0, zChars);
  }
}






/**Help to detect the format char for d and s command. */
static char const* const formatChars = "xwqrusil";

/**number of shift for a byte address due to format char. */
static uint8 const shAddrFormat[] = { 0, 1, 2, 2, 0, 1, 2, 3 };

/**Radix for parse and write due to format char. 0: float conversion necessary. */
static uint8 const nRadixFormat[] = { 16, 16, 16, 0, 10, 10, 10, 10 };



/**Transmits one information for the registered d command . */
static void showMemContent (  AsciiMoni_emC_s* thiz ) {
  int ix = 0;
  int zBuffer = ARRAYLEN_emC(thiz->txBuffer);
  if(thiz->flags.bit.bTxFirstNewline) {
    thiz->txBuffer[ix++] = '\n';
    thiz->flags.bit.bTxFirstNewline = 0;
  }
  char sep = ' ';
  if(thiz->ixValuesToShow ==0) {
    ix += toString_int32_emC(thiz->txBuffer +ix, 6, (int32)(thiz->lastMemAddr), 16, 6);
    sep = ':';
  }
  thiz->txBuffer[ix++] = sep;
  int32 val;
  int minNrCharsHex, minNrCharsDec;
  int format = thiz->flags.bit.nShowFormat;
  switch(format) {
  case 0: case 4: //byte hex or decimal
    val = (int32)(*((uint8*)(thiz->lastMemAddr + thiz->ixValuesToShow)));
    minNrCharsHex = 2; minNrCharsDec = 3;
    break;
  case 1: case 5: //16 bit hex or decimal
    val = *(uint16*)(thiz->lastMemAddr + 2*thiz->ixValuesToShow);
    minNrCharsHex = 4; minNrCharsDec = 5;
    break;
  case 2: case 6: //qword hex or decimal
    val = *(uint32*)(thiz->lastMemAddr + 4*thiz->ixValuesToShow);
    minNrCharsHex = 8; minNrCharsDec = 11;
    break;
  case 3: //float
    val = *(uint32*)(thiz->lastMemAddr + 4*thiz->ixValuesToShow);    // as float image
    minNrCharsHex = 7; minNrCharsDec = 7;
    break;
  case 7: //long
    val = *(uint32*)(thiz->lastMemAddr + 8*thiz->ixValuesToShow);    // as float image
    minNrCharsHex = 7; minNrCharsDec = 7;
    break;
  default: val = 0;
  } //switch
  thiz->ixValuesToShow +=1;
  int radix = 16;
  int minNrChars = minNrCharsHex;
  if(thiz->flags.bit.nShowFormat >= 4) {
    radix = 10;
    minNrChars = minNrCharsDec;
  }
//  int radix = thiz->flags.bit.nShowFormat < 3 : 16 : 10;
  if(format ==3) { //float
    ix += toString_float_emC(thiz->txBuffer + ix, zBuffer -3 - ix, *(float*)&val, "331m111");
  } else {
    ix += toString_int32_emC(thiz->txBuffer + ix, zBuffer -3 - ix, val, radix, minNrChars);
  }
  if(thiz->ixValuesToShow >= thiz->nrofValuesToShow) {
    thiz->txBuffer[ix++] = '\r';
    thiz->txBuffer[ix++] = '\n';
    thiz->flags.bit.bRxTxAnswer = 0;
  }
  txChars_Serial_HALemC(thiz->flags.val.channel, thiz->txBuffer, 0, ix);
}



/**This routine should be called cyclically in a back loop or in a middle prior thread
 * to care the inputs of the ASCII monitor.
 */
void step_AsciiMoni_emC ( AsciiMoni_emC_s* thiz) {
  stepRx_Serial_HALemC(0);             // part of organization: call cyclically the rx serial.
  int ixRxCharsLast = thiz->flags.val.ixRxChars;     //from last call
  //---------------------------------- // on a simple target: check received and already stored characters,
  //---------------------------------- // on a target with kernel: get new received characters and store here.
  thiz->flags.val.ixRxChars = getData_Serial_HALemC(0, thiz->rxBuffer, ixRxCharsLast, ARRAYLEN_emC(thiz->rxBuffer));
  if( thiz->flags.val.ixRxChars > ixRxCharsLast) {   // any what received
    if(thiz->flags.bit.bEcho) {
      //-------------------------------- // for simple target: tx one char, the rest are done in stepTx_Serial_HAL_emC
      txChars_Serial_HALemC(thiz->flags.val.channel, thiz->rxBuffer, ixRxCharsLast, thiz->flags.val.ixRxChars); //hence no waiting.
    }
    for(int ix = ixRxCharsLast; ix < thiz->flags.val.ixRxChars; ++ix) {
      char cc = thiz->rxBuffer[ix];
      if(cc == 0x0d) {                   // RETURN als termination of a command
        execCmd_AsciiMoni_emC(thiz, ix);
        thiz->flags.val.ixRxChars = 0;
        break;
      }
    }
  }
  else if(thiz->flags.val.ixRxChars < ixRxCharsLast) {
    txChars_Serial_HALemC(thiz->flags.val.channel, "\b\b\b", 0, 1); //hence no waiting.
  }
  //================================== // show mem content:
  if(  thiz->flags.bit.bRxTxAnswer ==1
    && busyTx_Serial_HAL_emC(thiz->flags.val.channel) ==0 //thiz->flags.bit.bTxPending ==0
    ) {
    showMemContent(thiz);
  }
}

//
//static char const* cmds[] =
//{ "e-", "echo on"
//, "q-", "alive off"
//, "d", "d0c00 [x[w|q|r] 10 display memory hex addr byte (default) word quad hex nr bytes"
//, "s", "d0c00 { [x|w|q|r] 0012} set memory hex addr x:hex f:float space:decimal so much as possible in the line"
//, "? Help"
//, "+ repeat display with incremented address"
//, "only enter: repeat last action"
//};



static int parseFormat (  AsciiMoni_emC_s* thiz, int ix, int zChars ) {
  char ccmd;
  while(ix < zChars && (ccmd = thiz->rxBuffer[ix])==' '){ ix+=1;} //(ix on next pos, also after spaces)
  int format = searchChar_emC(formatChars, 8, ccmd);
  if(format >=0) {                             // use same format as before if not given
    thiz->flags.bit.nShowFormat = format;
    thiz->flags.bit.nShIncrMemAddr = shAddrFormat[format];
  }
  while(ix < zChars && (ccmd = thiz->rxBuffer[++ix])==' '); //(ix on next pos, also after spases)
  return ix;
}




void execCmd_AsciiMoni_emC ( AsciiMoni_emC_s* thiz, int zChars ) {
  int ix = 0;
  int parsedChars = 0;
  char ccmd = thiz->rxBuffer[ix++];
  switch(ccmd) {
  case '?':
    txChars_Serial_HALemC(thiz->flags.val.channel, "emC ASCII monitor V 1.2 \r\nsee https://www.vishia.org/emc/html/Inspc/AsciiMoni_emC.html\r\nq-<ENTER> to switch off status msg\r\n", 0, -1 );
    break;
  case '+':  // NO break!
    thiz->flags.bit.bIncrMemAddr = 1;
    // no break, do the same as only return
  case '\r': case '\n':
    if(thiz->nrofValuesToShow >0) {              // repeat the last d command
      if(thiz->flags.bit.bIncrMemAddr) {
        thiz->lastMemAddr += (thiz->nrofValuesToShow << thiz->flags.bit.nShIncrMemAddr);
      }
      thiz->ixValuesToShow = 0;
      thiz->flags.bit.bRxTxAnswer = 1;
    } else {                                     // write any text, only the first time after rest, version hint for docu.
      txChars_Serial_HALemC(thiz->flags.val.channel, "?<ENTER> for help\r\n", 0, -1 );
    }
    break;
  case 'd': {
    thiz->flags.bit.bTxFirstNewline = 1;
    thiz->flags.bit.bIncrMemAddr = 0;
    intPTR memAddr = parseIntRadix_emC(thiz->rxBuffer+ix, zChars - ix, 16, &parsedChars, " ");
    if(parsedChars >0) {
      thiz->lastMemAddr = memAddr;               // use the same mem address if not newly given.
      ix += parsedChars;
    }
    ix = parseFormat(thiz, ix, zChars);
    int nrofValues = parseIntRadix_emC(thiz->rxBuffer+ix, zChars - ix, 10, &parsedChars, " x");
    if(parsedChars >0) {                         // use the same nrof values if not newly given.
      thiz->nrofValuesToShow = nrofValues;       // no more as 16, limit it simple for handling errors.
    }
    thiz->ixValuesToShow = 0;
    thiz->flags.bit.bRxTxAnswer = 1;
  } break;
  case 's': case 'S':{
    thiz->flags.bit.bTxFirstNewline = 1;
    intPTR memAddr = parseIntRadix_emC(thiz->rxBuffer+ix, zChars - ix, 16, &parsedChars, " ");
    if(parsedChars >0) {
      thiz->lastMemAddr = memAddr;               // use the same mem address if not newly given.
      ix += parsedChars;   //(pre increment follows)
      int ixValue = 0;
      do {
        int ix2 = parseFormat(thiz, ix, zChars);           // skip also over spaces
        if(ix2 > ix) {
          ix = ix2;
          int radix = nRadixFormat[thiz->flags.bit.nShowFormat];  //the yet parsed format
          int32 value;
          if(radix ==0) {

            float fValue = parseFloat_emC(thiz->rxBuffer+ix, zChars - ix, &parsedChars);
            value = *(int32*)(&fValue);   // int image of the float value
          } else {
            value = parseIntRadix_emC(thiz->rxBuffer+ix, zChars - ix, radix, &parsedChars, " - x");
          }
          if(parsedChars >0) {
            ix += parsedChars -1;  //Note: preincrement in next parseFormat.
            switch(thiz->flags.bit.nShIncrMemAddr) {     // store requested number of bytes.
            case 0: *(uint8*)(thiz->lastMemAddr + ixValue) = (uint8)value; break; // store 8 bit;
            case 1: *(uint16*)(thiz->lastMemAddr + ixValue) = (uint16)value; break; // store 16 bit;
            case 2: *(uint32*)(thiz->lastMemAddr + ixValue) = (uint32)value; break; // store 32 bit;
            //case 3: *(uint64*)(thiz->lastMemAddr) = (uint64)value; break; // store 64 bit;
            //default: //do nothing.
            }
            ixValue += (1 << thiz->flags.bit.nShIncrMemAddr);  //next address depending on format
          }
        } else {
          parsedChars = 0;             // no format or space between last number.
        }
      }while(parsedChars >0);
      if(ccmd=='s') {                            // set and show, 'S' is only set.
        if(thiz->nrofValuesToShow ==0) { thiz->nrofValuesToShow = 1; }
        thiz->ixValuesToShow = 0;
        thiz->flags.bit.bRxTxAnswer = 1;
      }
    }
  } break;
  case 'q':
    thiz->flags.bit.bTxState = (thiz->rxBuffer[1] == '-') ? 0 : 1;
    break;
  case 'e':
    thiz->flags.bit.bEcho = (thiz->rxBuffer[1] == '-') ? 0 : 1;
    break;
  } //switch

  //after cmd execution, offer the buffer newly, clear.
  getData_Serial_HALemC(thiz->flags.val.channel, null, 0, 0);  //to clean.
  getData_Serial_HALemC(thiz->flags.val.channel, thiz->rxBuffer, 0, ARRAYLEN_emC(thiz->rxBuffer)); // fill newly

}

