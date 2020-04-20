#include "Proxy2TargetSharedMem_Inspc.h"
#include <string.h>
#include <emC/OSAL/os_sharedmem.h>
#include <emC/OSAL/os_time.h>
#include <stdio.h>

#ifndef DEF_REFLECTION_NO
  #include "genRefl/Proxy2TargetSharedMem_Inspc.crefl"
#else

#endif


Proxy2TargetSharedMem_Inspc* ctor_Proxy2TargetSharedMem_Inspc(ObjectJc* othiz, char const* nameAppl, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_Proxy2TargetSharedMem_Inspc");
  //memset(thiz, 0, sizeof(*thiz));
  checkInit_ObjectJc(othiz, sizeof(Proxy2TargetSharedMem_Inspc), &reflection_Proxy2TargetSharedMem_Inspc, 0, THCXT);
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


