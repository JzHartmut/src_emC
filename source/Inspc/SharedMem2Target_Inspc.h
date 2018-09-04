#ifndef __Inspc__SharedMem2Target_Inspc_h__
#define __Inspc__SharedMem2Target_Inspc_h__
#include <applstdef_emC.h>
#include <OSAL/os_sharedmem.h>
#include <Inspc/TelgTargetProxy_Inspc.h>

/**Organization struct for sharedMem from Proxy 2 Target and vice versa.
 */
typedef struct SharedMem2Target_Inspc_t {
  /**The necessary management data for os_sharedMem */
  SharedMem_OSAL sharedMemMng_target2proxy; //, XXXXXsharedMemMng_proxy2target;

  /**Gotten reference to the exchange data range. */
  TelgTarget2Proxy_Inspc_s* target2proxy;

  /**Gotten reference to the exchange data range. */
  TelgProxy2Target_Inspc_s* proxy2target;



  //char name_target2proxy[32], name_proxy2target[32];


} SharedMem2Target_Inspc;




/**Checks whether a SharedMem is existing.If it is, it checks whether the length of telg is correct.
 * THROW on error.
 */
void ctor_SharedMem2Target_Inspc(SharedMem2Target_Inspc* thiz, char const* nameAppl, ThCxt* _thCxt);

void dtor_SharedMem2Target_Inspc(SharedMem2Target_Inspc* thiz);


#endif  //__Inspc__SharedMem2Target_Inspc_h__