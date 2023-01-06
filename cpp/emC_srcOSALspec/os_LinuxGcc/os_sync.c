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
#include <emC/OSAL/os_sync.h>

//needed from os_adaption itself
#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include <emC_srcOSALspec/os_LinuxGcc/os_internal.h>

//Needed includes from os:
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int os_createWaitNotifyObject(char const* name, OS_HandleWaitNotify_s const** waitObjectP)
{ int error = 0;
  OS_HandleWaitNotify_s* waitObject;

  waitObject = (OS_HandleWaitNotify_s*)malloc(sizeof(OS_HandleWaitNotify_s*));
  //init anything?

  *waitObjectP = waitObject;
  return error;
}


/**removes a object for wait-notify.
 */
int os_removeWaitNotifyObject(struct OS_HandleWaitNotify_t const* waitObj)
{ //TODO
  return 0;
}


int os_wait(
    struct OS_HandleWaitNotify_t const* waitObjP
  , struct OS_Mutex_t const* mutexP
  , uint32 milliseconds
)
{
  int error;
  //cast it from const to non-const. const is only outside!
  OS_HandleWaitNotify_s* waitObj = (struct OS_HandleWaitNotify_t*)waitObjP;
  OS_Mutex_s* mutex = (struct OS_Mutex_t*)mutexP;
  //the current threadcontext is nice to have for debugging - get the name of the thread.
  struct OS_ThreadContext_t const* pThread = getCurrent_OS_ThreadContext();
  struct timespec time;
  /*
    if(pThread != mutex->threadOwner)
    { os_Error("notify: it is necessary to have a os_lockMutex in the current thread", (int)mutex->threadOwner);
      return OS_INVALID_PARAMETER;
    }
  */
  /**note the waiting thread, because notify weaks up only if a thread waits.
   */
  if(waitObj->threadWait == null)
  { waitObj->threadWait = pThread;
  }
  else
  { //build a queue of waiting threads. TODO
  }
  if(milliseconds >0){
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


    error = pthread_cond_timedwait(&waitObj->waitCondition, &mutex->mutex, &time);
  } else { //milliseconds == 0:
    error = pthread_cond_wait(&waitObj->waitCondition, &mutex->mutex);
  }
  //os_lockMutex(mutex) will be executed in cond_relative_timed_wait(...)
  waitObj->threadWait = null; 
  //
  //the user have to be unlock.
  return error;
}


/** Notifies all waiting thread to continue.
 */
int os_notifyAll(OS_HandleWaitNotify waitObject, OS_Mutex_s hMutex)
{
  return -1;

}


/** Notifies only one waiting thread to continue.
 */
int os_notify(struct OS_HandleWaitNotify_t const* waitObjP, OS_Mutex_s* mutexP)
{ bool shouldNotify;
  int error = 0xbaadf00d;
  //cast it from const to non-const. const is only outside!
  OS_HandleWaitNotify_s* waitObj = (struct OS_HandleWaitNotify_t*)waitObjP;
  OS_Mutex_s* mutex = (OS_Mutex_s*)mutexP;
  //the current threadcontext is nice to have for debugging - get the name of the thread.
  struct OS_ThreadContext_t const* pThread = getCurrent_OS_ThreadContext();
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

