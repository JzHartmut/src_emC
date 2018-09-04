#ifndef __Inspc__Proxy2TargetSharedMem_Inspc_h__
#define __Inspc__Proxy2TargetSharedMem_Inspc_h__
#include "Inspc/Proxy2Target_Inspc.h"
#include "Inspc/SharedMem2Target_Inspc.h"


typedef struct Proxy2TargetSharedMem_Inspc_t
{

  /**Derived from TargetData*/
  Proxy2Target_Inspc super;

  SharedMem2Target_Inspc shMemAccess;
  



} Proxy2TargetSharedMem_Inspc;


/**Initializes the data and opens the shared memory.
* If the shared memory access failes, THROW is invoked. Then the internal references are null.
* If it has worked successfully, the pointer target2proxy and proxy2target are set.
*/
Proxy2TargetSharedMem_Inspc* ctor_Proxy2TargetSharedMem_Inspc(ObjectJc* othiz, char const* nameAppl, ThCxt* _thCxt);

/**frees the shared memory.
*/
void dtor_Proxy2TargetSharedMem_Inspc(Proxy2TargetSharedMem_Inspc*);



#endif //__Inspc__Proxy2TargetSharedMem_Inspc_h__
