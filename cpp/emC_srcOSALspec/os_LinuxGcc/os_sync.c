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



int createWaitNotifyObj_OSemC(char const* name, HandleWaitNotify_OSemC_s const** waitObjectP)
{ HandleWaitNotify_OSemC_s* thiz;

  thiz = (HandleWaitNotify_OSemC_s*)malloc(sizeof(HandleWaitNotify_OSemC_s*));
  //init anything?
  int error = pthread_cond_init(&thiz->waitCondition, null);   // use null aus attribute for default behavior
  if(error !=null) {
    ERROR_SYSTEM_emC(error, "pthread_cond_init fails", error,0);
  }
  *waitObjectP = thiz;
  return error;
}


/**removes a object for wait-notify.
 */
int deleteWaitNotifyObj_OSemC(HandleWaitNotify_OSemC waitObj)
{ //TODO
  return 0;
}


int wait_OSemC(
    struct HandleWaitNotify_OSemC_T const* waitObjP
  , struct Mutex_OSemC_T* mutexP
  , uint32 milliseconds
)
{
  int error;
  //cast it from const to non-const. const is only outside!
  HandleWaitNotify_OSemC_s* waitObj = (struct HandleWaitNotify_OSemC_T*)waitObjP;
  Mutex_OSemC_s* mutex = (struct Mutex_OSemC_T*)mutexP;
  //the current threadcontext is nice to have for debugging - get the name of the thread.
  Thread_OSemC const* threadContextWait = getCurrent_Thread_OSemC();
  pthread_t hThread = pthread_self();
  //The mutex should be locked, check it:
  if(! pthread_equal((pthread_t)mutex->lockingThread->handleThread, hThread)){   // should be same
    //This is a user error, try to THROW an excption or ignore it.
    THROW_s0n(RuntimeException, "wait_OSemC should be called under mutex ", (int)(intPTR)hThread, (int)(intPTR)mutex->lockingThread);
  }
  waitObj->ctLockMutex = mutex->ctLock;          // save for restoring
  mutex->ctLock = 0;                             //necessary because the mutex will be free inside wait
  mutex->lockingThread = null;
  /*
    if(pThread != mutex->threadOwner)
    { os_Error("notify: it is necessary to have a os_lockMutex in the current thread", (int)mutex->threadOwner);
      return OS_INVALID_PARAMETER;
    }
  */
  /**note the waiting thread, because notify weaks up only if a thread waits.
   */
  if(waitObj->threadWait == null)
  { waitObj->threadWait = threadContextWait;
  }
  else
  { //build a queue of waiting threads. TODO
  }
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


    error = pthread_cond_timedwait(&waitObj->waitCondition, (__pthread_mutex_t**)&mutex->osHandleMutex, &time);
  } else { //milliseconds == 0:
    error = pthread_cond_wait(&waitObj->waitCondition, (__pthread_mutex_t**)&mutex->osHandleMutex);
  }
  if(error !=0){
    ERROR_SYSTEM_emC(99, "error in pthread_cond_wait", error, (int)(intPTR)waitObj);
  }
  //----------------------------------------------- the mutex is already locked after wait:
  mutex->lockingThread = threadContextWait;
  mutex->ctLock = waitObj->ctLockMutex;          // restore state before wait for the mutex.
  waitObj->ctLockMutex = 0;
  waitObj->threadWait = null; 
  //
  //the user have to be unlock.
  return error;
}


/** Notifies all waiting thread to continue.
 */
int notifyAll_OSemC(HandleWaitNotify_OSemC waitObject, Mutex_OSemC_s hMutex)
{
  return -1;

}


/** Notifies only one waiting thread to continue.
 */
int notify_OSemC(struct HandleWaitNotify_OSemC_T const* waitObjP, Mutex_OSemC_s* mutexP)
{ bool shouldNotify;
  int error = 0xbaadf00d;
  //cast it from const to non-const. const is only outside!
  HandleWaitNotify_OSemC_s* waitObj = (struct HandleWaitNotify_OSemC_T*)waitObjP;
  Mutex_OSemC_s* mutex = (Mutex_OSemC_s*)mutexP;
  //the current threadcontext is nice to have for debugging - get the name of the thread.
  Thread_OSemC const* pThread = getCurrent_Thread_OSemC();
    /*
  if(pThread != mutex->threadOwner)
  { os_Error("notify: it is necessary to have a os_lockMutex in the current thread", (int)mutex->threadOwner);
    error = OS_UNEXPECTED_CALL;
  }
  else
  */
  {
    shouldNotify = (waitObj->threadWait != null); //notify only if a thread waits, test under mutex!
    if(shouldNotify)
    { //the mutex is locked and will be locked still!
      error = pthread_cond_signal(&waitObj->waitCondition);
      if(error != 0)
      { //If the function fails, the return value is not zero.
        //if(error == -ERROR_TOO_MANY_POSTS)  //windows-error
        { //warning
          //error = OS_WARNING_NOTIFY_TooManyPosts;
        }
      }
      //lock before return.
      //it is locekd: os_lockMutex(mutex);
    }
    else
    { error = OS_WARNING_NOTIFY_NothingIsWaiting;
    }
  }
  return error;  //the mutex is locked.
}

