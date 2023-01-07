#ifndef __os_internWin_h__
#define __os_internWin_h__


#include <applstdef_emC.h>

#include <pthread.h>

/**Informations about the current thread, more as an simple id. */
struct OS_ThreadContext_t* getCurrent_OS_ThreadContext();


typedef struct Mutex_OSemC_T{
  pthread_mutex_t mutex;
  pthread_mutexattr_t attr;
  const char* name;

}Mutex_OSemC_s;


//#include "fw_MemC.h"


/**The type of a OS_HandleWaitNotify is represented . */
typedef struct HandleWaitNotify_OSemC_T
{
  /**The owner of the mutex. */
  /**null if nobody waits. elsewhere the queue of waiting threads.*/
  struct OS_ThreadContext_t const* threadWait;

  /**see http://linux.die.net/man/3/pthread_cond_wait. */
  pthread_cond_t waitCondition;
} HandleWaitNotify_OSemC_s;



#endif //__os_internWin_h__
