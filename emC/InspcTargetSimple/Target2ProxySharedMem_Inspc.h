#ifndef __Inspc__Proxy2TargetSharedMem_Inspc_h__
#define __Inspc__Proxy2TargetSharedMem_Inspc_h__
#include "emC/InspcTargetSimple/Target2Proxy_Inspc.h"
#include "emC/InspcTargetSimple/SharedMem2Target_Inspc.h"


typedef struct Target2ProxySharedMem_Inspc_t
{

  /**Derived from TargetData*/
  Target2Proxy_Inspc_s super;

  SharedMem2Target_Inspc shMemAccess;
  



} Target2ProxySharedMem_Inspc;


/**Initializes the data and opens the shared memory.
* If the shared memory access failes, the system is aborted via os_FatalError(...).
* If it has worked successfully, the pointer target2proxy and proxy2target are set (not null).
*/
void ctor_Target2ProxySharedMem_Inspc(Target2ProxySharedMem_Inspc* thiz, char const* nameAppl);

void dtor_Target2ProxySharedMem_Inspc(Target2ProxySharedMem_Inspc* thiz);



#endif //__Inspc__Proxy2TargetSharedMem_Inspc_h__
