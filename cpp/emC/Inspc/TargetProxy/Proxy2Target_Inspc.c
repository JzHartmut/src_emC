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
  thiz->ms_timeout = 2000;
  thiz->ms_LastTimeTx = 0;  //!=0: receives InspcTargetData
  //open_Serial_HALemC(thiz->channelTarget, toReadWrite_Serial_HALemC, 115200, ParityNoStop1_Serial_HALemC);
  STACKTRC_RETURN thiz;
}


//This operation will be called from inner of the inspector access.
//If the address is in a target.
int32 get_Proxy2Target_Inspc(Proxy2Target_Inspc* thiz, Cmd_InspcTargetProxy_e cmd, uint32 address, int32 input) {

  int32 ret = -1;
  TelgProxy2Target_Inspc_s* txTelg = thiz->proxy2target;
  txTelg->address = address;
  txTelg->value = input;
  //at last set new seqnr and cmd
  thiz->seqnrTxTarget = (thiz->seqnrTxTarget +1) & 0xff;
  setCmdSeqnr_TelgProxy2Target_Inspc(txTelg, cmd, thiz->seqnrTxTarget);
  //
  if (forceComm_Proxy2Target_Inspc(thiz, cmd)) {    //call this external routine to force communication. 
    int32 value = thiz->target2proxy->retValue; //
    return value;
  }
  else {
    return -1;
  }
}

#endif //DEF_INSPC_REMOTEACCESS

