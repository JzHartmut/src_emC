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


#include <emC/OSAL/thread_OSemC.h>

#undef BOOL
#undef PBOOL
#undef boolean


//#include <OSAL/os_waitnotify.h>
#include <emC/OSAL/sync_OSemC.h>

#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include "os_internal.h"


int createWaitNotifyObj_OSemC  (  char const* name, HandleWaitNotify_OSemC_s const** waitObjectP)
{ //folg. Mechanismus ist nicht verf�gbar unter Win2000, w�re aber richtiger:
  //PCONDITION_VARIABLE var;
  //InitializeConditionVariable(&var);
  //HANDLE semaphor;
  int error = 0;

  HANDLE semaphor = CreateSemaphore
  ( null /*LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,*/
  , 0    /*__in      LONG lInitialCount, */
  , 1    /*__in      LONG lMaximumCount, */
  , null /*__in_opt  LPCTSTR lpName */
  );
  if(semaphor==null)
  { error = GetLastError();
    *waitObjectP = null;
  }
  else
  { HandleWaitNotify_OSemC_s* waitObject = (HandleWaitNotify_OSemC_s*)os_allocMem(sizeof(HandleWaitNotify_OSemC_s));
    waitObject->winHandleWaitNotify = semaphor;
    waitObject->threadWait = null;
    *waitObjectP = waitObject;
  }
  return error;
}


/**removes a object for wait-notify.
 */
int removeWaitNotifyObj_OSemC  (  struct HandleWaitNotify_OSemC_T const* waitObj)
{ STACKTRC_ENTRY("removeWaitNotifyObj_OSemC");
  HANDLE winHandleWaitNotify = waitObj->winHandleWaitNotify;
  os_freeMem((void*)waitObj);
  if ( CloseHandle( winHandleWaitNotify ) == 0 ) 
  {
    DWORD err = GetLastError();
    THROW_s0(RuntimeException, "os_removeWaitNotifyObj: ERROR: CloseHandle failed with Win err=%d\n", err, 0);
	  if (err==ERROR_INVALID_HANDLE)
    {	STACKTRC_RETURN OS_INVALID_HANDLE;
	  }
    else
	  { STACKTRC_RETURN OS_SYSTEM_ERROR;
    }
  }
  else
  { STACKTRC_RETURN OS_OK;
  } 
}


int wait_OSemC  (  struct HandleWaitNotify_OSemC_T const* waitObjP, struct Mutex_OSemC_T const* mutex, uint32 milliseconds)
{ //HANDLE semaphor = (HANDLE)handle;
  int error;
  struct HandleWaitNotify_OSemC_T* waitObj = (struct HandleWaitNotify_OSemC_T*)waitObjP;
  struct OS_ThreadContext_t const* pThread = getCurrent_OS_ThreadContext();
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
  /**but now the mutex should be release, after storing the thread, notify_OSemC should not test it before. */ 
  unlockMutex_OSemC(mutex);
  //ab hier kann die Bedingungen ge�ndert werden und notify wird gerufen, 
  //notify increments the semaphore, so that wait returns immediately. 
  //Here normally a thread change should be done:
  error = WaitForSingleObject(waitObj->winHandleWaitNotify, milliseconds);
  if(error == WAIT_FAILED)
  { error = GetLastError();
  }
  else
  { error = 0;
  }
  //if the thread is revived:
  //The mutex is relocked 
  lockMutex_OSemC(mutex,  0);  //should be locked, the caller unlocks.
  waitObj->threadWait = null; 
  //
  //the user have to be unlock.
  return error;
}


/** Notifies all waiting thread to continue.
 */
int notifyAll_OSemC  (  HandleWaitNotify_OSemC waitObject, struct Mutex_OSemC_T const* hMutex)
{
  return -1;

}


/** Notifies only one waiting thread to continue.
 */
int notify_OSemC  (  struct HandleWaitNotify_OSemC_T const* waitObjP, struct Mutex_OSemC_T const* mutex)
{ struct HandleWaitNotify_OSemC_T* waitObj = (struct HandleWaitNotify_OSemC_T*)waitObjP;
  LONG prevCount;
  bool shouldNotify;
  int error = 0xbaadf00d;
  struct OS_ThreadContext_t const* pThread = getCurrent_OS_ThreadContext();
  /*
  if(pThread != mutex->threadOwner)
  { os_Error("notify: it is necessary to have a lockMutex_OSemC in the current thread", (int)mutex->threadOwner);
    error = OS_UNEXPECTED_CALL;
  }
  else
  */
  {
    shouldNotify = (waitObj->threadWait != null); //notify only if a thread waits, test under mutex!
    //see http://msdn.microsoft.com/en-us/library/ms685071(VS.85).aspx
    if(shouldNotify)
    { int ok;
      //unlock, because ReleaseSemaphore() mustn_t call in a critical section, threadchange possible 
      unlockMutex_OSemC(mutex);
      ok = ReleaseSemaphore(waitObj->winHandleWaitNotify, 1, &prevCount);
      if(ok == 0) 
      { //If the function fails, the return value is zero. To get extended error information, call GetLastError.
        error = -((int)GetLastError()); 
        if(error == -ERROR_TOO_MANY_POSTS)  //windows-error
        { //warning
          error = OS_WARNING_NOTIFY_TooManyPosts;
        }
      }
      else 
      { //If the function succeeds, the return value is nonzero
        error = 0; 
      }
      //lock before return.
      lockMutex_OSemC(mutex, 0);  //should be locked, the caller unlocks.
    }
    else
    { error = OS_WARNING_NOTIFY_NothingIsWaiting;
    }
  }
  return error;  //the mutex is locked.
}


#if 0
int createMutex_OSemC(struct OS_HandleMutex_t const** handle)
{ CRITICAL_SECTION* semaphore = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
  InitializeCriticalSection(semaphore);
  *handle = (struct OS_HandleMutex_t const*)semaphore;
  return 0;
}


int os_entryMutex(struct OS_HandleMutex_t const* handle)
{
  CRITICAL_SECTION* semphore = (CRITICAL_SECTION*)handle;
  EnterCriticalSection(semphore);
  return 0;
}


int os_releaseMutex(struct OS_HandleMutex_t const* handle)
{
  CRITICAL_SECTION* semphore = (CRITICAL_SECTION*)handle;
  LeaveCriticalSection(semphore); 
  return 0;
}

#endif

