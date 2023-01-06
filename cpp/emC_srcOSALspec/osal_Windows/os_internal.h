#ifndef __os_internWin_h__
#define __os_internWin_h__

#undef BOOL
#undef PBOOL
#undef boolean
#undef INT32
#undef UINT32
#undef int64
//#undef uint64

#include <wtypes.h>
#include <Winbase.h>

#include <applstdef_emC.h>

/**Informations about the current thread, more as an simple id. */
struct OS_ThreadContext_t* getCurrent_OS_ThreadContext();


typedef struct Mutex_OSemC_T{
  /**The owner of the mutex. Not necessary in Windows because Win_API check it.*/
  //struct OS_ThreadContext_t const* threadOwner;
  
  /**The system use an handle mostly. It is 32 or 64 bit (on 64-bit-Windows-Version).*/
  HANDLE winHandleMutex;
} Mutex_OSemC_s;




/**The type of a HandleWaitNotify_OSemC is represented by a pointer to a not far defined struct. */ 
typedef struct HandleWaitNotify_OSemC_T 
{ /**The owner of the mutex. */
  //int threadOwner;
  /**null if nobody waits. elsewhere the queue of waiting threads.*/
  /**The owner of the mutex. */
  struct OS_ThreadContext_t const* threadWait;
  /**The system use an handle. */
  HANDLE winHandleWaitNotify;
} HandleWaitNotify_OSemC_s;



#endif //__os_internWin_h__
