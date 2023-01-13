/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content This file contains the implementation of os_waitnotify.h for MS-Windows.
 * @author Jchartmut www.vishia.org
 * @version 0.81d
 * list of changes:
 * 2007-10-01: JcHartmut creation
 *
 ****************************************************************************/
//the own include file firstly
#include <emC/OSAL/sync_OSemC.h>

//needed from os_adaption itself
#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include <emC_srcOSALspec/os_LinuxGcc/os_internal.h>

//Needed includes from os:
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>  //ETIMEDOUT

//tag::createWaitNotify[]
bool createWaitNotifyObj_OSemC(char const* name, WaitNotify_OSemC_s* thiz)
{ memset(thiz, 0, sizeof(*thiz));
  WaitNotify_pthread* h = (WaitNotify_pthread*)malloc(sizeof(WaitNotify_pthread));
  //init anything?
  int error = pthread_cond_init(&h->waitCondition, null);   // use null as attribute for default behavior
  if(error !=0) {
    ERROR_SYSTEM_emC(error, "pthread_cond_init fails", error,0);
  }
  thiz->osHandleWaitNotify = h;
  return error ==0;
}
//end::createWaitNotify[]


/**removes a object for wait-notify.
 */
//tag::deleteWaitNotify[]
bool deleteWaitNotifyObj_OSemC(WaitNotify_OSemC_s* thiz)
{ //TODO
  WaitNotify_pthread* h = C_CAST(WaitNotify_pthread*, thiz->osHandleWaitNotify);
  int err = pthread_cond_destroy(&h->waitCondition);
  if(err !=0) {
    THROW_s0n(RuntimeException, "problem on pthread_cond_destroy ", err, (int)(intPTR)thiz);
  }
  thiz->osHandleWaitNotify = null;
  free(h);
  return err ==0;
}
//end::deleteWaitNotify[]


//tag::wait[]
bool wait_OSemC(
    WaitNotify_OSemC_s* thiz
  , struct Mutex_OSemC_T* mutex
  , uint32 milliseconds
)
{
  int error;
  WaitNotify_pthread* h = C_CAST(WaitNotify_pthread*, thiz->osHandleWaitNotify);
  //cast it from const to non-const. const is only outside!
  //the current threadcontext is nice to have for debugging - get the name of the thread.
  Thread_OSemC* threadWait = getCurrent_Thread_OSemC();
  pthread_t hThread = pthread_self();            //The mutex should be locked, check it:
  if(mutex ==null || ! pthread_equal((pthread_t)mutex->lockingThread->handleThread, hThread)){   // should be same
    //This is a user error, try to THROW an excption or ignore it.
    THROW_s0n(RuntimeException, "wait_OSemC should be called under mutex ", (int)(intPTR)hThread, (int)(intPTR)mutex->lockingThread);
  }
  if(thiz->mutex !=null && thiz->mutex != mutex) {
    THROW_s0n(RuntimeException, "more wait_OSemC with this Obj uses different mutexes ", (int)(intPTR)hThread, (int)(intPTR)mutex->lockingThread);
  }
  thiz->mutex = mutex;
  thiz->ctLockMutex = mutex->ctLock;             // save for restoring
  mutex->ctLock = 0;                             // necessary because the mutex will be free inside wait
  mutex->lockingThread = null;
  /**note the waiting thread, because notify weaks up only if a thread waits.
   */
  if(threadWait->waitObj !=null || threadWait->nextWaitingThread !=null) {
    THROW_s0n(RuntimeException, "wait_OSemC mismatch in waiting Thread ", (int)(intPTR)hThread, (int)(intPTR)threadWait);
  }
  threadWait->nextWaitingThread = thiz->threadWait;  // maybe null if the waitObj is not used for wait till now
  thiz->threadWait = threadWait;                 // build a queue of waiting threads.
  threadWait->waitObj = thiz;
  //
  MutexData_pthread* hmutex = C_CAST(MutexData_pthread*, mutex->osHandleMutex);
  if(milliseconds >0){
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    { uint32 sec = milliseconds / 1000;
      milliseconds -= 1000*sec;  //rest is millisec
      time.tv_sec += sec;
      time.tv_nsec += 1000000*milliseconds;
      if(time.tv_nsec > 1000000000){ //overflow of nanoseconds:
        time.tv_nsec -= 1000000000;
        time.tv_sec +=1;
      }
    }

    error = pthread_cond_timedwait(&h->waitCondition, &hmutex->m, &time);
  } else { //milliseconds == 0:
    error = pthread_cond_wait(&h->waitCondition, &hmutex->m);
  }
  if (error !=0 && error != ETIMEDOUT) {         //ETIMEDOUT comes if the time has expired befor call wait, maybe possisble
    ERROR_SYSTEM_emC(99, "error in pthread_cond_wait", error, (int)(intPTR)thiz);
  }
  //----------------------------------------------- the mutex is already locked after wait:
  mutex->lockingThread = threadWait;             // restore state before wait for the mutex.
  mutex->ctLock = thiz->ctLockMutex;
  thiz->ctLockMutex = 0;
  thiz->threadWait = threadWait->nextWaitingThread;
  threadWait->nextWaitingThread = null;
  threadWait->waitObj = null;
  if(thiz->threadWait == null) {                 // only if nobody else waits
    thiz->mutex = null;                          // set the mutex to null, other mutex can be used.
  }
  return error ==0;                              // false if timeout or any other error
  //the user have to be unlock the mutex.
}
//end::wait[]


/** Notifies all waiting thread to continue.
 */
bool notifyAll_OSemC(HandleWaitNotify_OSemC waitObject, Mutex_OSemC_s hMutex)
{
  return false;

}


/** Notifies only one waiting thread to continue.
 */
//tag::notify[]
bool notify_OSemC(WaitNotify_OSemC_s* thiz, Mutex_OSemC_s* mutex)
{ int error = 0;
  WaitNotify_pthread* h = C_CAST(WaitNotify_pthread*, thiz->osHandleWaitNotify);
  //the current threadcontext is nice to have for debugging - get the name of the thread.
  Thread_OSemC const* thread = getCurrent_Thread_OSemC();
  if(mutex == null || thread != mutex->lockingThread ) {
    THROW_s0n(RuntimeException, "notify_OSemC should be called only under mutex ", (int)(intPTR)thread, (int)(intPTR)mutex);
  }
  bool shouldNotify = (thiz->threadWait != null); //notify only if a thread waits, test under mutex!
  if(shouldNotify)
  { //the mutex is locked and will be locked still!
    if(thiz->mutex != mutex ) {
      THROW_s0n(RuntimeException, "notify_OSemC should be called with the same mutex as wait", (int)(intPTR)thiz->mutex, (int)(intPTR)mutex);
    }
    error = pthread_cond_signal(&h->waitCondition);
    if(error != 0) {
      ERROR_SYSTEM_emC(99, "error in pthread_cond_signal", error, (int)(intPTR)thiz);
    }
  }
  else
  { // do nothing, all is ok
  }
  return error ==0;  //the mutex is locked.
}
//end::notify[]

