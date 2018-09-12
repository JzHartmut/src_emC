#include <sourceApplSpecific/applConv/ExcStacktrcNo_emC.h>
#include <OSAL/os_thread.h>
#




/**This mehtod is necessary because the user shouldn't know the struct ThreadContext.
* It should be hidden, but the embedded part of threadcontext for Stacktrace handling
* should be known in all user routines because it is used inline-like.
*/
ThreadContext_emC_s* getCurrent_ThreadContext_emC  ()
{
  ThreadContext_emC_s* thC;
  //The users thread context is managed but not knwon in detail from osal:
  MemC memThreadContext = os_getCurrentUserThreadContext();
  thC = PTR_MemC(memThreadContext, ThreadContext_emC_s);
  if (thC == null)
  {
    memThreadContext = alloc_MemC(sizeof(ThreadContext_emC_s));
    os_setCurrentUserThreadContext(memThreadContext);
    thC = PTR_MemC(memThreadContext, ThreadContext_emC_s);
  }
  return thC;  //it is a embedded struct inside the whole ThreadContext.
}



bool stop_AssertJc( ){
  return false;
}