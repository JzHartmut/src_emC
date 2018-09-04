#include "Inspc/Target2ProxySharedMem_Inspc.h"
#include <string.h>
#include <OSAL/os_sharedmem.h>

#ifndef __DONOTUSE_REFLECTION__
#include "Inspc/Target2ProxySharedMem_Inspc.crefl"
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
    setInt32BigEndian(&thiz->super.target2proxy->length_cmd, sizeof(TelgTarget2Proxy_Inspc_s) << 16);  //initialize
    setInt32BigEndian(&thiz->super.target2proxy->seqnr, 0);  //initialize
  }
}



void dtor_Target2ProxySharedMem_Inspc(Target2ProxySharedMem_Inspc* thiz) {
  dtor_SharedMem2Target_Inspc(&thiz->shMemAccess);
}

