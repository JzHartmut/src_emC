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

#undef BOOL
#undef PBOOL
#undef boolean


//#include <OSAL/os_waitnotify.h>

#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include "os_internal.h"

/**Creates a mutex object.
 * @param name Name of the Mutex Object. In some operation systems this name should be unique. Please regard it, also in windows.
 * The mutex Object contains the necessary data for example a HANDLE etc.
 */
extern_C int createMutex_OSemC ( struct Mutex_OSemC_T* thiz, char const* name) {
    CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,malloc(sizeof(CRITICAL_SECTION)));
    InitializeCriticalSection(cs);
    thiz->osHandleMutex  = cs;
    return 0;
}


int deleteMutex_OSemC ( struct Mutex_OSemC_T* thiz) {
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,thiz->osHandleMutex);
  DeleteCriticalSection(cs);
  free(cs);
  thiz->osHandleMutex = null;
  return true;
}



bool lockMutex_OSemC  ( struct Mutex_OSemC_T* thiz) {
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,thiz->osHandleMutex);
  EnterCriticalSection(cs);            // reenter in the same thread is supported be OS-Windows
  thiz->lockingThread = getCurrent_Thread_OSemC(); //Hint: do it after lock!
  thiz->ctLock +=1;                    // MS-Windows in EnterCriticalSection allows reenter in the same thread
  return true;                         // true if no timeout was done.
}




bool unlockMutex_OSemC  (  struct Mutex_OSemC_T* thiz){
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*,thiz->osHandleMutex);
  if(--thiz->ctLock <=0) {             // Hint: do it before unlock
    thiz->lockingThread = null;        // it is only for debugging
    thiz->ctLock = 0;
  }
  LeaveCriticalSection(cs);
  return true;
}




int createWaitNotifyObj_OSemC  (  char const* name, HandleWaitNotify_OSemC_s const** waitObjectP)
{ //folg. Mechanismus ist nicht verfügbar unter Win2000
 
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, malloc(sizeof(CONDITION_VARIABLE)));
  InitializeConditionVariable(cv);
  
  HandleWaitNotify_OSemC_s* waitObject = (HandleWaitNotify_OSemC_s*)os_allocMem(sizeof(HandleWaitNotify_OSemC_s));
  waitObject->osHandleWaitNotify = cv;
  waitObject->threadWait = null;
  *waitObjectP = waitObject;
  return 0;
}



/**removes a object for wait-notify.
 */
int deleteWaitNotifyObj_OSemC  (  struct HandleWaitNotify_OSemC_T const* thiz) { 
  struct HandleWaitNotify_OSemC_T* waitObj = (struct HandleWaitNotify_OSemC_T*)thiz;
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, thiz->osHandleWaitNotify);
  free(cv);

  os_freeMem((void*)waitObj);
  return 0;
}


int wait_OSemC  (  struct HandleWaitNotify_OSemC_T const* waitObjP, struct Mutex_OSemC_T* mutex, uint32 milliseconds) {
 //HANDLE semaphor = (HANDLE)handle;
  struct HandleWaitNotify_OSemC_T* waitObj = (struct HandleWaitNotify_OSemC_T*)waitObjP;
  struct Thread_OSemC_T const* pThread = getCurrent_Thread_OSemC();
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, waitObjP->osHandleWaitNotify);
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*, mutex->osHandleMutex);
  /*
    if(pThread != mutex->threadOwner)
    { os_Error("notify: it is necessary to have a lockMutex_OSemC in the current thread", (int)mutex->threadOwner);
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
  if(milliseconds ==0) { milliseconds = INFINITE; } 
  //
  //inside Sleep, the lock is free, wait for timeout or notify
  int error = SleepConditionVariableCS(cv, cs, milliseconds);
  //after sleep, the lock is given:
  waitObj->threadWait = null; 
  if(error ==0) {
    error = GetLastError();
    return false;                    // time elapsed or any other error
  } else { 
    return true;                     // return >0, it is ok
  }
  //
  //the user have to be unlock.
}


/** Notifies all waiting thread to continue.
 */
int notifyAll_OSemC  (  HandleWaitNotify_OSemC waitObject, struct Mutex_OSemC_T const* hMutex)
{
  return -1;

}


/** Notifies only one waiting thread to continue.
 */
int notify_OSemC  (  struct HandleWaitNotify_OSemC_T const* waitObjP, struct Mutex_OSemC_T* mutex) { 
  struct HandleWaitNotify_OSemC_T* waitObj = (struct HandleWaitNotify_OSemC_T*)waitObjP;
  struct Thread_OSemC_T const* pThread = getCurrent_Thread_OSemC();
  CONDITION_VARIABLE* cv = C_CAST(CONDITION_VARIABLE*, waitObjP->osHandleWaitNotify);
  CRITICAL_SECTION* cs = C_CAST(CRITICAL_SECTION*, mutex->osHandleMutex);
  int error = 0xbaadf00d;
  /*
  if(pThread != mutex->threadOwner)
  { os_Error("notify: it is necessary to have a lockMutex_OSemC in the current thread", (int)mutex->threadOwner);
    error = OS_UNEXPECTED_CALL;
  }
  else
  */
  {
    boolean shouldNotify = (waitObj->threadWait != null); //notify only if a thread waits, test under mutex!
    //see http://msdn.microsoft.com/en-us/library/ms685071(VS.85).aspx
    if(shouldNotify)
    { 
      WakeConditionVariable(cv);
    }
  }
  return true;  //the mutex is locked.
}



