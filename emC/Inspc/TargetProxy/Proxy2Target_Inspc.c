#include <applstdef_emC.h>
#ifdef DEF_INSPC_REMOTEACCESS

#include "Proxy2Target_Inspc.h"
#include <emC/HAL/Serial_HALemC.h>

#include <stdio.h> //printf
#include <emC/OSAL/os_time.h>


#ifndef DEF_REFLECTION_NO
#include "genRefl/Proxy2Target_Inspc.crefl"
#else

#endif



Proxy2Target_Inspc* ctor_Proxy2Target_Inspc(ObjectJc* thizo, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_Proxy2Target_Inspc");
  checkInit_ObjectJc(thizo, sizeof(Proxy2Target_Inspc), &refl_Proxy2Target_Inspc, 0);
  Proxy2Target_Inspc* thiz = (Proxy2Target_Inspc*) thizo;
  thiz->channelTarget = 7;  //COM7
  thiz->ms_timeout = 2000;
  thiz->ms_LastTimeTx = 0;  //!=0: receives InspcTargetData
  //open_Serial_HALemC(thiz->channelTarget, toReadWrite_Serial_HALemC, 115200, ParityNoStop1_Serial_HALemC);
  STACKTRC_RETURN thiz;
}


static char const* cmdTxt[] =
{ "0"
, "getRootAddr"  // 1
, "getRootType"  // 2
, "getType    "  // 3
, "getSizeOffs"  // 4
, "getLenArray"  // 5
, "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"
, "getByte    "  // 0x10
, "getInt16   "  // 0x11
, "getInt32   "  // 0x12
, "getInt64   "  // 0x13
, "getFloat   "  // 0x14
, "getDouble  "  // 0x15
, "getRef     "  // 0x16
, "getBitfild "  // 0x17
, "setByte    "  // 0x18
, "setInt16   "  // 0x19
, "setInt32   "  // 0x1a
, "setInt64   "  // 0x1b
, "setFloat   "  // 0x1c
, "setDouble  "  // 0x1d
, "setRef     "  // 0x1e
, "setBitfild "  // 0x1f

};


//This operation will be called from inner of the inspector access.
//If the address is in a target.
int32 get_Proxy2Target_Inspc(Proxy2Target_Inspc* thiz, Cmd_InspcTargetProxy_e cmd, uint32 address, int32 input) {

  int32 ret = -1;
  TelgProxy2Target_Inspc_s* txTelg = thiz->proxy2target;
  int16 nrofBytesTx = (int16)sizeof(*txTelg);
  txTelg->address = address;
  txTelg->value = input;
  //at last set new seqnr and cmd
  thiz->seqnrTxTarget = (thiz->seqnrTxTarget +1) & 0xff;
  setCmdSeqnr_TelgProxy2Target_Inspc(txTelg, cmd, thiz->seqnrTxTarget);
  //The target will be read this information in about the next few micro to milliseconds.
  //No: It is a poor polling. 
  //applies the send data in a specific way
  //prepareRx_Serial_HALemC(thiz->channelTarget, (MemUnit*)thiz->target2proxy, sizeof(*thiz->target2proxy), 0);
  printf("tx: %8.8x=%s addr=%8.8x %8.8x %8.8x ...", txTelg->length_seq_cmd, cmdTxt[((int)cmd) & 0x1f], txTelg->address, txTelg->valueHi, txTelg->value);
  thiz->ms_LastTimeTx = os_getMilliTime();       //marking uses the other com
  if(thiz->ms_LastTimeTx ==0) { thiz->ms_LastTimeTx = 1; } //marks pending, should be !=0
  if(thiz->channelTarget >0) {
    int32 escTx = 0x011b;
    tx_Serial_HALemC(thiz->channelTarget, &escTx, 0, 2);   //with esc 01 the target detects the InspcTargetTeleg
    tx_Serial_HALemC(thiz->channelTarget, txTelg, 0, nrofBytesTx);
    sleepMicroSec_Time_emC(4000);  //wait 4 ms for tx and rx.
  }
  int seqnrtarget = -1;
  bool hasReceived = false;
  TelgTarget2Proxy_Inspc_s const* rxTelg = thiz->target2proxy;
  int timeout = thiz->ms_timeout;  //seconds
  do {
    sleepMicroSec_Time_emC(1000);  //wait a little moment.
    if(thiz->channelTarget >0) {
      int zRx = hasRxChars_Serial_HALemC(thiz->channelTarget);
      if(zRx >=sizeof((*rxTelg))) {
        //The thiz->target2proxy area will be set by the communication thread. 
        //whereby the seqnr need be set as last. 
        seqnrtarget = getSeqnr_TelgTarget2Proxy_Inspc(rxTelg);
        hasReceived = seqnrtarget == thiz->seqnrTxTarget;
      } 
    }
    if (timeout == 3) {
      timeout +=0;   //debug break
    }
  } while(!hasReceived && --timeout !=0);  //note: if starts with 0, loop for ever.
  int32 value;
  if(timeout == 0){
    value = -1;
    printf("Timeout target seqtx=%2.2X seqrx=%2.2X\n", thiz->seqnrTxTarget, seqnrtarget);
    thiz->ms_LastTimeTx = 0;
  } else { 
    value = rxTelg->retValue; 
    int32 milliseconds = thiz->ms_LastTimeCommunication;
    thiz->ms_LastTimeCommunication = os_getMilliTime();
    int32 timediff = thiz->ms_LastTimeCommunication - milliseconds;
    int32 timediffRx = thiz->ms_LastTimeCommunication - thiz->ms_LastTimeTx;
    thiz->ms_LastTimeTx = 0;                     //no more pending.
    if(timediff > 1000){
      //printf("\n");
    }
    //printf("%8.8x %s-@%8.8x x=%8.8x ret=%8.8x\n", (int)cmd, cmdTxt[((int)cmd) & 0x1f], address, input, value);
    printf("%2.3fs: %8.8x addr=%8.8x %8.8x val=%8.8x\n", 0.001f*timediffRx, rxTelg->length_seq_cmd, rxTelg->error__lifeCt, rxTelg->retValueHi, rxTelg->retValue);
  }
  return value; 

}

#endif //DEF_INSPC_REMOTEACCESS

