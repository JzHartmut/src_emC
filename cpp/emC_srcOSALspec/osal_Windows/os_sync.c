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
    memset(thiz, 0, sizeof(*thiz));
    CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,malloc(sizeof(CRITICAL_SECTION)));
    InitializeCriticalSection(cs);
    thiz->osHandleMutex  = cs;
    thiz->name = name;
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
  thiz->lockingThread = getCurrent_Thread_OSemC(); //Hint: do it after lock!
  thiz->ctLock +=1;                    // count only for debug
  thiz->millisecLock = milliTime_emC();// milliseconds relative system time.
  return true;                         // true always
}
//end::lockMutex[]




//tag::unlockMutex[]
bool unlockMutex_OSemC  (  struct Mutex_OSemC_T* thiz){
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,thiz->osHandleMutex);
  if(--thiz->ctLock <=0) {             // Hint: do it before unlock
    thiz->lockingThread = null;        // it is only for debugging
    thiz->ctLock = 0;
  }
  LeaveCriticalSection(cs);
  return true;
}
//end::unlockMutex[]




//tag::createWaitNotify[]
bool createWaitNotifyObj_OSemC  (  char const* name, WaitNotify_OSemC_s* thiz) { 
  memset(thiz, 0, sizeof(*thiz));
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
  struct Thread_OSemC_T const* pThread = getCurrent_Thread_OSemC();
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, thiz->osHandleWaitNotify);
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*, mutex->osHandleMutex);
  /*
    if(pThread != mutex->threadOwner)
    { os_Error("notify: it is necessary to have a lockMutex_OSemC in the current thread", (int)mutex->threadOwner);
      return OS_INVALID_PARAMETER;
    }
  */
  /**note the waiting thread, because notify weaks up only if a thread waits.
   */
  if(thiz->threadWait == null)
  { thiz->threadWait = pThread;
  }
  else
  { //build a queue of waiting threads. TODO
  }
  if(milliseconds ==0) { milliseconds = INFINITE; } 
  //
  //inside Sleep, the lock is free, wait for timeout or notify
  int error = SleepConditionVariableCS(cv, cs, milliseconds);
  //after sleep, the lock is given:
  thiz->threadWait = null; 
  if(error ==0) {
    error = GetLastError();
    return false;                    // time elapsed or any other error
  } else { 
    return true;                     // return >0, it is ok
  }
  //
  //the user have to be unlock.
}
//end::wait[]


/** Notifies all waiting thread to continue.
 */
//tag::notifyAll[]
bool notifyAll_OSemC  ( struct WaitNotify_OSemC_T* thiz, struct Mutex_OSemC_T const* hMutex)
{
  return false;

}
//end::notifyAll[]


/** Notifies only one waiting thread to continue.
 */
//tag::notify[]
bool notify_OSemC  (  struct WaitNotify_OSemC_T* thiz, struct Mutex_OSemC_T* mutex) { 
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



