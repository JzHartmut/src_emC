#ifndef __os_internLinux_h__
#define __os_internLinux_h__

#include <applstdef_emC.h>
#include <emC/OSAL/sync_OSemC.h>
#include <emC/OSAL/thread_OSemC.h>

#include <pthread.h>




//#include "fw_MemC.h"


/**The type of a OS_HandleWaitNotify is represented . */
typedef struct HandleWaitNotify_OSemC_T
{
  /**The owner of the mutex. */
  /**null if nobody waits. elsewhere the queue of waiting threads.*/
  struct Thread_OSemC_T const* threadWait;

  /**The number of recursively lock should be stored to restore. */
  int ctLockMutex;
  /**see http://linux.die.net/man/3/pthread_cond_wait. */
  pthread_cond_t waitCondition;             //: the pthread handle of the waitCond
} HandleWaitNotify_OSemC_s;



#endif //__os_internWin_h__
