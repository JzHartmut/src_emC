#include "emC/InspcTargetSimple/Target2ProxySharedMem_Inspc.h"
#include <string.h>
#include <emC/OSAL/os_sharedmem.h>

#ifndef DEF_REFLECTION_NO
  //#include "Inspc/Target2ProxySharedMem_Inspc.crefl"
  //Do not include the crefl here, they are not necessary here. 
  //If the crefl are need for associated data it should be included in the main context of the application.
#else

#endif


void ctor_Target2ProxySharedMem_Inspc(Target2ProxySharedMem_Inspc* thiz, char const* nameAppl) {
  //STACKTRC_TENTRY("ctor_Target2ProxySharedMem_Inspc");
  memset(thiz, 0, sizeof(*thiz));
  ctor_SharedMem2Target_Inspc(&thiz->shMemAccess, nameAppl, null);
  thiz->super.target2proxy = thiz->shMemAccess.target2proxy;
  thiz->super.proxy2target = thiz->shMemAccess.proxy2target;
  //thiz->super.target2proxy = PTR_MemC(thiz->shMemAccess.sharedMemMng_target2proxy.addrSize, TelgTarget2Proxy_Inspc_s);
  //thiz->super.proxy2target = PTR_MemC(thiz->shMemAccess.sharedMemMng_proxy2target.addrSize, TelgProxy2Target_Inspc_s);
  if(thiz->super.proxy2target !=null) {
    //initialize.
    int seqnr = getSeqnr_TelgProxy2Target_Inspc(thiz->super.proxy2target);
    thiz->super.seqnrLast = seqnr;  //currently communication
    thiz->super.target2proxy->length_seq_cmd = sizeof(TelgTarget2Proxy_Inspc_s) << kBitLength_TelgTarget2Proxy_Inspc;  //initialize
    thiz->super.target2proxy->error__lifeCt = 0;  //initialize
  }
}



void dtor_Target2ProxySharedMem_Inspc(Target2ProxySharedMem_Inspc* thiz) {
  dtor_SharedMem2Target_Inspc(&thiz->shMemAccess);
}

