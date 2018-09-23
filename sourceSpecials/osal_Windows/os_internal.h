#ifndef __os_internWin_h__
#define __os_internWin_h__

#undef BOOL
#undef PBOOL
#undef boolean
#undef INT32
#undef UINT32
#undef int64
#undef uint64

#include <wtypes.h>
#include <Winbase.h>

#include <applstdef_emC.h>

/**Informations about the current thread, more as an simple id. */
struct OS_ThreadContext_t* getCurrent_OS_ThreadContext();


typedef struct OS_Mutex_t{
  /**The owner of the mutex. Not necessary in Windows because Win_API check it.*/
  //struct OS_ThreadContext_t const* threadOwner;
  
  /**The system use an handle mostly. It is 32 or 64 bit (on 64-bit-Windows-Version).*/
  HANDLE winHandleMutex;
} OS_Mutex_s;




/**The type of a OS_HandleWaitNotify is represented by a pointer to a not far defined struct. */ 
typedef struct OS_HandleWaitNotify_t 
{ /**The owner of the mutex. */
  //int threadOwner;
  /**null if nobody waits. elsewhere the queue of waiting threads.*/
  /**The owner of the mutex. */
  struct OS_ThreadContext_t const* threadWait;
  /**The system use an handle. */
  HANDLE winHandleWaitNotify;
} OS_HandleWaitNotify_s;



#endif //__os_internWin_h__
