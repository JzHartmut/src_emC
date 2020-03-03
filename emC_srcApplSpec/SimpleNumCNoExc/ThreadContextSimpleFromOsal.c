//#include <emC_srcApplSpec/SimpleNumCNoExc/ExcNoStringStacktrcNo_emC.h>
#include <applstdef_emC.h>
#include <emC/Base/MemC_emC.h>
#include <emC/OSAL/os_thread.h>
#




/**This mehtod is necessary because the user shouldn't know the struct ThreadContext.
* It should be hidden, but the embedded part of threadcontext for Stacktrace handling
* should be known in all user routines because it is used inline-like.
*/
ThreadContext_emC_s* getCurrent_ThreadContext_emC  ()
{
  ThreadContext_emC_s* thC;
  //The users thread context is managed but not knwon in detail from osal:
  AddrVal_emC memThreadContext = os_getCurrentUserThreadContext();
  thC = PTR_MemC(memThreadContext, ThreadContext_emC_s);
  if (thC == null)
  {
    ALLOC_MemC(memThreadContext, sizeof(ThreadContext_emC_s));
    os_setCurrentUserThreadContext(memThreadContext);
    thC = PTR_MemC(memThreadContext, ThreadContext_emC_s);
  }
  return thC;  //it is a embedded struct inside the whole ThreadContext.
}



bool stop_AssertJc( ){
  return false;
}