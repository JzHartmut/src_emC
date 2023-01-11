#ifndef HGUARD_os_internal
#define HGUARD_os_internal
//tag::start[]
#include <applstdef_emC.h>

#undef BOOL
#undef PBOOL
#undef boolean
#undef INT32
#undef UINT32
#undef int64
//#undef uint64

#include <wtypes.h>
#include <Winbase.h>


/**Informations about the current thread, more as an simple id. */
//struct OS_ThreadContext_t* getCurrent_OS_ThreadContext();
//end::start[]





/**The type of a HandleWaitNotify_OSemC is represented by a pointer to a not far defined struct. */ 
typedef struct HandleWaitNotify_OSemC_T 
{ /**The owner of the mutex. */
  //int threadOwner;
  /**null if nobody waits. elsewhere the queue of waiting threads.*/
  /**The owner of the mutex. */
  struct Thread_OSemC_T const* threadWait;
  /**The system use an handle. */
  void* osHandleWaitNotify;
} HandleWaitNotify_OSemC_s;



#endif //HGUARD_os_internal
