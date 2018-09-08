#include "Inspc/Proxy2TargetSharedMem_Inspc.h"
#include <string.h>
#include <OSAL/os_sharedmem.h>
#include <OSAL/os_time.h>

#ifndef __DONOTUSE_REFLECTION__
#include "Inspc/Proxy2TargetSharedMem_Inspc.crefl"
#else

#endif


Proxy2TargetSharedMem_Inspc* ctor_Proxy2TargetSharedMem_Inspc(ObjectJc* othiz, char const* nameAppl, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_Proxy2TargetSharedMem_Inspc");
  //memset(thiz, 0, sizeof(*thiz));
  checkInit_ObjectJc(othiz, sizeof(Proxy2TargetSharedMem_Inspc), 0, &reflection_Proxy2TargetSharedMem_Inspc, THCXT);
  Proxy2TargetSharedMem_Inspc* thiz = (Proxy2TargetSharedMem_Inspc*)othiz;
  ctor_Proxy2Target_Inspc(&thiz->super.object, THCXT);
  ///init_ObjectJc(&thiz->super.object, sizeof(thiz->super),0);
  ctor_SharedMem2Target_Inspc(&thiz->shMemAccess, nameAppl, THCXT);
  thiz->super.target2proxy = thiz->shMemAccess.target2proxy;
  thiz->super.proxy2target = thiz->shMemAccess.proxy2target;
  //thiz->super.target2proxy = PTR_MemC(thiz->shMemAccess.sharedMemMng_target2proxy.addrSize, TelgTarget2Proxy_Inspc_s);
  //thiz->super.proxy2target = PTR_MemC(thiz->shMemAccess.sharedMemMng_proxy2target.addrSize, TelgProxy2Target_Inspc_s);
  if(thiz->super.proxy2target !=null) {
    //initialize.
    setInt32BigEndian(&thiz->super.proxy2target->length_seq_cmd, sizeof(TelgTarget2Proxy_Inspc_s) << 16);  //initialize
  }
  return thiz;
}


void dtor_Proxy2TargetSharedMem_Inspc(Proxy2TargetSharedMem_Inspc* thiz) {
  dtor_SharedMem2Target_Inspc(&thiz->shMemAccess);

}



int32 get_Proxy2TargetSharedMem_Inspc(Proxy2TargetSharedMem_Inspc* thiz, Cmd_InspcTargetProxy_e cmd, struct RemoteAddressJc* address, int32 input) {

  int32 ret = -1;
  TelgProxy2Target_Inspc_s* txTelg = thiz->super.proxy2target;
  int16 nrofBytesTx = (int16)sizeof(*txTelg);
  setInt32BigEndian(&txTelg->address, (int32)address);
  setInt32BigEndian(&txTelg->value, input);
  //at last set new seqnr and cmd
  setCmdSeqnr_TelgProxy2Target_Inspc(txTelg, cmd, ++thiz->super.seqnrTxTarget);
  //The target will be read this information in about the next few micro to milliseconds.
  //It is a poor polling. 
  int seqnrtarget;
  TelgTarget2Proxy_Inspc_s const* rxTelg = thiz->super.target2proxy;
  int timeout = 1000;  //seconds
  do {
    os_delayThread(1);
    //return thiz->answerWord_Target;
    seqnrtarget = getSeqnr_TelgTarget2Proxy_Inspc(rxTelg);
    if (timeout <= 100) {
      timeout +=0;   //debug break
    }
  } while(seqnrtarget != thiz->super.seqnrTxTarget && --timeout >=0);
  int32 value;
  if(timeout < 0){
    value = -1;
  } else { value = getInt32BigEndian(&rxTelg->retValue); }
  return value; 

}

