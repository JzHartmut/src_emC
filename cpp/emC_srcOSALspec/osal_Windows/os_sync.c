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


#include <emC/OSAL/sync_OSemC.h>
#include <emC/OSAL/thread_OSemC.h>
#include <emC/Base/Time_emC.h>
#include <emC/OSAL/os_AtomicAccess.h>

#undef BOOL
#undef PBOOL
#undef boolean


//#include <OSAL/os_waitnotify.h>

#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include "os_internal.h"

//It allocates a CRITICAL_SECTION data and calla InitializeCriticalSection(cs) 
//tag::createMutex[]
extern_C int createMutex_OSemC ( struct Mutex_OSemC_T* thiz, char const* name) {
  void* handleOld = thiz->osHandleMutex;
  if(handleOld == null) {                      // create only if not given. 
    thiz->name = name;
    CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,malloc(sizeof(CRITICAL_SECTION)));
    InitializeCriticalSection(cs);
    int repeat = 20;
    void volatile* handleRead = compareAndSwap_AtomicRef( &thiz->osHandleMutex, null, cs);
    if(handleRead != null) {                   // another thread has written also meanwhile
      DeleteCriticalSection(cs);               // forget the work, all is done by the other thread.
      free(cs);                                // deallocates
    } else {
      thiz->name = name;
    }
  }
  return 0;
}
//end::createMutex[]


//tag::deleteMutex[]
int deleteMutex_OSemC ( struct Mutex_OSemC_T* thiz) {
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,thiz->osHandleMutex);
  DeleteCriticalSection(cs);
  free(cs);                        // deallocates
  thiz->osHandleMutex = null;
  return 0;
}
//end::deleteMutex[]



//tag::lockMutex[]
bool lockMutex_OSemC  ( struct Mutex_OSemC_T* thiz) {
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,thiz->osHandleMutex);
  EnterCriticalSection(cs);            // EnterCriticalSection reenter in the same thread is supported be OS-Windows
  if(thiz->ctLock ==0 && thiz->lockingThread !=null) {
    THROW_s0n(RuntimeException, "on lock the lockingThread should be 0", thiz->ctLock, 0);
  }
  thiz->lockingThread = getCurrent_Thread_OSemC(); //Hint: do it after lock!
  thiz->ctLock +=1;                    // count only for debug
  thiz->millisecLock = milliTime_emC();// milliseconds relative system time.
  return true;                         // true always
}

//end::lockMutex[]


bool lockMutexFirst_OSemC  ( struct Mutex_OSemC_T* thiz) {
  bool ok = lockMutex_OSemC(thiz);
  ASSERT_emC(thiz->ctLock ==1, "unlockMutexFirst ctLock !=1", thiz->ctLock, 0);
  return ok;
}


//tag::unlockMutex[]
bool unlockMutex_OSemC  (  struct Mutex_OSemC_T* thiz){
  bool ok = true;
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,thiz->osHandleMutex);
  Thread_OSemC* currThread = getCurrent_Thread_OSemC();
  if(thiz->lockingThread != currThread) {
    THROW_s0n(RuntimeException, "faulty thread on unlock ", (int)(intPTR)currThread, 0);  // not an ERROR_SYSTEM, a user error
    return false;                      // do not unlock, the thread is not authorized. bug to debug.
  }
  if(--thiz->ctLock <=0) {             // Hint: do it before unlock
    thiz->lockingThread = null;        // it is only for debugging
    thiz->ctLock = 0;
  } else {
    thiz->ctLock +=0;
  }
  LeaveCriticalSection(cs);
  return true;
}
//end::unlockMutex[]

bool unlockMutexFirst_OSemC  ( struct Mutex_OSemC_T* thiz) {
  ASSERT_emC(thiz->ctLock ==1, "unlockMutexFirst ctLock !=1", thiz->ctLock, 0);
  return unlockMutex_OSemC(thiz);
}



//tag::createWaitNotify[]
bool createWaitNotifyObj_OSemC  (  char const* name, WaitNotify_OSemC_s* thiz) { 
  memset(thiz, 0, sizeof(*thiz));
  thiz->name = name;

  //the following. mechanisms is not available in Win2000
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, malloc(sizeof(CONDITION_VARIABLE)));
  InitializeConditionVariable(cv);
  thiz->osHandleWaitNotify = cv;
  return true;
}
//end::createWaitNotify[]



/**removes a object for wait-notify.
 */
//tag::deleteWaitNotify[]
bool deleteWaitNotifyObj_OSemC  (  struct WaitNotify_OSemC_T* thiz) { 
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, thiz->osHandleWaitNotify);
  free(cv);

  return true;
}
//end::deleteWaitNotify[]


//tag::wait[]
bool wait_OSemC  (  struct WaitNotify_OSemC_T* thiz, struct Mutex_OSemC_T* mutex, uint32 milliseconds) {
  //HANDLE semaphor = (HANDLE)handle;
  struct Thread_OSemC_T* threadWait = getCurrent_Thread_OSemC();
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, thiz->osHandleWaitNotify);
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*, mutex->osHandleMutex);
  if(threadWait != mutex->lockingThread) {
    THROW_s0n(RuntimeException, "notify: it is necessary to have a lockMutex_OSemC in the current thread", (int)(intPTR)mutex->lockingThread, 0);
    return false;
  }
  /**note the waiting thread, because notify weaks up only if a thread waits.
   */
  if(thiz->threadWait == null)
  { thiz->threadWait = threadWait;
  }
  else
  { //build a queue of waiting threads. TODO
  }
  thiz->mutex = mutex;
  thiz->ctLockMutex = mutex->ctLock;             // save for restoring
  mutex->ctLock = 0;                             // necessary because the mutex will be free inside wait
  mutex->lockingThread = null;
  //
  threadWait->nextWaitingThread = thiz->threadWait;  // maybe null if the waitObj is not used for wait till now
  thiz->threadWait = threadWait;                 // build a queue of waiting threads.
  threadWait->waitObj = thiz;
  //
  if(milliseconds ==0) { milliseconds = INFINITE; } 
  //
  //inside Sleep, the lock is free, wait for timeout or notify
  int error = SleepConditionVariableCS(cv, cs, milliseconds);
  //after sleep, the lock is given:
  if(error ==0) {
    error = GetLastError();
    return false;                    // time elapsed or any other error
  }
  mutex->lockingThread = threadWait;             // restore state before wait for the mutex.
  mutex->ctLock = thiz->ctLockMutex;
  thiz->ctLockMutex = 0;
  thiz->threadWait = threadWait->nextWaitingThread;
  threadWait->nextWaitingThread = null;
  threadWait->waitObj = null;
  if(thiz->threadWait == null) {                 // only if nobody else waits
    thiz->mutex = null;                          // set the mutex to null, other mutex can be used.
  } else {
    thiz->ctLockMutex += 0;
  }
  //
  return true;                                   //the user have to be unlock.
}
//end::wait[]


/** Notifies all waiting thread to continue.
 */
//tag::notifyAll[]
bool notifyAll_OSemC  ( WaitNotify_OSemC_s* thiz, struct Mutex_OSemC_T* hMutex)
{
  return false;

}
//end::notifyAll[]


/** Notifies only one waiting thread to continue.
 */
//tag::notify[]
bool notify_OSemC  (  WaitNotify_OSemC_s* thiz, struct Mutex_OSemC_T* mutex) { 
  struct Thread_OSemC_T const* pThread = getCurrent_Thread_OSemC();
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, thiz->osHandleWaitNotify);
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*, mutex->osHandleMutex);
  int error = 0;
  /*
  if(pThread != mutex->threadOwner)
  { os_Error("notify: it is necessary to have a lockMutex_OSemC in the current thread", (int)mutex->threadOwner);
    error = OS_UNEXPECTED_CALL;
  }
  else
  */
  {
    boolean shouldNotify = (thiz->threadWait != null); //notify only if a thread waits, test under mutex!
    //see http://msdn.microsoft.com/en-us/library/ms685071(VS.85).aspx
    if(shouldNotify)
    { 
      WakeConditionVariable(cv);
    }
  }
  return true;  //the mutex is locked.
}
//end::notify[]



