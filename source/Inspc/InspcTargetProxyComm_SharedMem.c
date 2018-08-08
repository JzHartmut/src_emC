/**This file contains the initialization and invocation of the Inspc-Interface via a simple shared memory access
* made by Hartmut Schorrig, www vishia.org
* date first: 2018
*/
#include "Inspc/InspcTargetProxyTelg.h"
#include <OSAL/os_sharedMem.h>
#include <OSAL/os_error.h>
#include <Fwc/fw_String.h>
#include <applstdef_emC.h>
#include <string.h>

//NOTE: return inside, os_FatalError(...) inside
void ctor_SharedMemAccess_Target2Proxy_Inspc(SharedMemAccess_Target2Proxy_Inspc* thiz, char const* nameAppl) {
  memset(thiz, 0, sizeof(*thiz));
  //prepare name.
  //hint: use memcpy because strncpy is denunciated as non save by the C11 standard.  
  int zname = strlen_Fwc(nameAppl, sizeof(thiz->name_proxy2target) - 7); //regard the dst size!
  memcpy(thiz->name_proxy2target, nameAppl, zname);
  memcpy(thiz->name_proxy2target + zname, "_t2pxy", 6);  //zero termination is guaranteed. 
  memcpy(thiz->name_target2proxy, nameAppl, zname);
  memcpy(thiz->name_target2proxy + zname, "_pxy2t", 6);
  //
  //try to access:
  MemC memLocation = os_accessSharedMem(&thiz->sharedMemMng_target2proxy, thiz->name_target2proxy);
  if (!os_isReadySharedMem(&thiz->sharedMemMng_target2proxy)) {
    //create and init if access failes:
    memLocation = os_createSharedMem(&thiz->sharedMemMng_target2proxy, thiz->name_target2proxy, sizeof(TelgTarget2Proxy_Inspc_s));
    if (!os_isReadySharedMem(&thiz->sharedMemMng_target2proxy)) {
      os_FatalError(-1, "Problem with shared mem - exit\n", 0, 0);
      return;  //abort on error
    }
    //initialize.
    thiz->target2proxy = PTR_MemC(memLocation, TelgTarget2Proxy_Inspc_s);
    setInt32BigEndian(&thiz->target2proxy->length_cmd, sizeof(TelgTarget2Proxy_Inspc_s) << 16);  //initialize
  }
  else {
    //it is found existent, check the content:
    int size_SharedMem_TelgTarget2Proxy_Inspc = size_MemC(memLocation);
    if (size_SharedMem_TelgTarget2Proxy_Inspc < sizeof(TelgTarget2Proxy_Inspc_s)) {
      os_FatalError(-1, "Problem with size of shared mem: %d, expected: %d - exit\n", size_MemC(memLocation), sizeof(TelgTarget2Proxy_Inspc_s));
      return;
    }
    thiz->target2proxy = PTR_MemC(memLocation, TelgTarget2Proxy_Inspc_s);
    int lengthTelg = getInt32BigEndian(&thiz->target2proxy->length_cmd) >> 16;
    if (lengthTelg != sizeof(TelgTarget2Proxy_Inspc_s)) {
      os_FatalError(-1, "Problem with data consistence of TelgTarget2Proxy_Inspc_s. len= %d, expected: %d - exit\n", lengthTelg, sizeof(TelgTarget2Proxy_Inspc_s));
      return;
    }
  }
  //
  //try to access:
  memLocation = os_accessSharedMem(&thiz->sharedMemMng_proxy2target, thiz->name_proxy2target);
  if (!os_isReadySharedMem(&thiz->sharedMemMng_proxy2target)) {
    //create and init if access failes:
    memLocation = os_createSharedMem(&thiz->sharedMemMng_proxy2target, thiz->name_proxy2target, sizeof(TelgProxy2Target_Inspc_s));
    if (!os_isReadySharedMem(&thiz->sharedMemMng_proxy2target)) {
      os_FatalError(-1, "Problem with shared mem proxy2target - exit\n", 0, 0);
      return;  //abort on error
    }
    //initialize.
    thiz->proxy2target = PTR_MemC(memLocation, TelgProxy2Target_Inspc_s);
    setInt32BigEndian(&thiz->proxy2target->length_cmd, sizeof(TelgProxy2Target_Inspc_s) << 16);  //initialize
  }
  else {
    //it is found existent, check the content:
    int size_SharedMem = size_MemC(memLocation);
    if (size_SharedMem < sizeof(TelgProxy2Target_Inspc_s)) {
      os_FatalError(-1, "Problem with size of shared mem proxy2target: %d, expected: %d - exit\n", size_MemC(memLocation), sizeof(TelgProxy2Target_Inspc_s));
      return;
    }
    thiz->proxy2target = PTR_MemC(memLocation, TelgProxy2Target_Inspc_s);
    int lengthTelg = getInt32BigEndian(&thiz->proxy2target->length_cmd) >> 16;
    if (lengthTelg != sizeof(TelgProxy2Target_Inspc_s)) {
      os_FatalError(-1, "Problem with data consistence of TelgProxy2Target_Inspc_s. len= %d, expected: %d - exit\n", lengthTelg, sizeof(TelgProxy2Target_Inspc_s));
      return;
    }
  }
}


