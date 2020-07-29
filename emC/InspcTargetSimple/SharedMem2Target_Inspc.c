/**This file contains the initialization and invocation of the Inspc-Interface via a simple shared memory access
* made by Hartmut Schorrig, www vishia.org
* date first: 2018
*/
#include "SharedMem2Target_Inspc.h"
#include "emC/InspcTargetSimple/IfcTargetProxy_Inspc.h"
#include <emC/base/String_emC.h>
#include <string.h>


#ifndef DEF_REFLECTION_NO
  #include "emC/InspcTargetSimple/genRefl/SharedMem2Target_Inspc.crefl"
  //Do not include the crefl here, they are not necessary here. 
  //If the crefl are need for associated data it should be included in the main context of the application.
#else

#endif




//NOTE: throw inside
//Checks whether a SharedMem is existing. If it is, it checks whether the length of telg is correct.
//THROW on error.
void ctor_SharedMem2Target_Inspc ( SharedMem2Target_Inspc* thiz, char const* nameAppl, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_SharedMem2Target_Inspc");
  memset(thiz, 0, sizeof(*thiz));
  //prepare size.
  int pos1 = 8;
  int pos2 = (pos1 + sizeof(TelgTarget2Proxy_Inspc_s) + 7) & ~0x7;  //assert 8-aligned
  int size = (pos2 + sizeof(TelgProxy2Target_Inspc_s) +7) & ~0x7;
  //
  //try to access:
  MemC memLocation = os_accessSharedMem(&thiz->sharedMemMng_target2proxy, nameAppl);
  if (!os_isReadySharedMem(&thiz->sharedMemMng_target2proxy)) {
    //create and init if access failes:
    memLocation = os_createSharedMem(&thiz->sharedMemMng_target2proxy, nameAppl, size);
    if (!os_isReadySharedMem(&thiz->sharedMemMng_target2proxy)) {
      THROW_s0(IllegalStateException, "Problem with shared mem - exit\n", 0, 0);
      STACKTRC_RETURN;  //abort on error
    }
    //initialize.
    thiz->target2proxy = (TelgTarget2Proxy_Inspc_s*)(addOffset_MemC(thiz->sharedMemMng_target2proxy.addrSize, pos1));
    thiz->proxy2target = (TelgProxy2Target_Inspc_s*)(addOffset_MemC(thiz->sharedMemMng_target2proxy.addrSize, pos2));
    setInt32BigEndian(&thiz->target2proxy->length_seq_cmd, sizeof(TelgTarget2Proxy_Inspc_s) << kBitLength_TelgTarget2Proxy_Inspc);  //initialize
    setInt32BigEndian(&thiz->proxy2target->length_seq_cmd, sizeof(TelgProxy2Target_Inspc_s) << kBitLength_TelgProxy2Target_Inspc);  //initialize
  }
  else {
    //it is found existent, check the content:
    int size_SharedMem_TelgTarget2Proxy_Inspc = size_MemC(memLocation);
    if (size_SharedMem_TelgTarget2Proxy_Inspc < sizeof(TelgTarget2Proxy_Inspc_s)) {
      THROW_s0(IllegalStateException, "Problem with size of shared mem: %d, expected: %d - exit\n", size_MemC(memLocation), size);
      STACKTRC_RETURN;  //abort on error
    }
    //check
    thiz->target2proxy = (TelgTarget2Proxy_Inspc_s*)(addOffset_MemC(thiz->sharedMemMng_target2proxy.addrSize, pos1));
    thiz->proxy2target = (TelgProxy2Target_Inspc_s*)(addOffset_MemC(thiz->sharedMemMng_target2proxy.addrSize, pos2));
    int lengthTelg2Proxy = getInt32BigEndian(&thiz->target2proxy->length_seq_cmd) >> 16;
    int lengthTelg2Target = getInt32BigEndian(&thiz->proxy2target->length_seq_cmd) >> 16;
    if (lengthTelg2Proxy != sizeof(TelgTarget2Proxy_Inspc_s)) {
      THROW_s0(IllegalStateException, "Problem with data consistence of TelgTarget2Proxy_Inspc_s. len= %d, expected: %d - exit\n", lengthTelg2Proxy, sizeof(TelgTarget2Proxy_Inspc_s));
      STACKTRC_RETURN;
    }
    if (lengthTelg2Target != sizeof(TelgProxy2Target_Inspc_s)) {
      THROW_s0(IllegalStateException, "Problem with data consistence of TelgProxy2Target_Inspc_s. len= %d, expected: %d - exit\n", lengthTelg2Target, sizeof(TelgProxy2Target_Inspc_s));
      STACKTRC_RETURN;
    }
  }
  //
}



void dtor_SharedMem2Target_Inspc(SharedMem2Target_Inspc* thiz) {
  os_closeSharedMem(&thiz->sharedMemMng_target2proxy);
}


