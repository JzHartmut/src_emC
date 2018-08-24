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


#include <os_thread.h>

#undef BOOL
#undef PBOOL
#undef boolean


//#include <os_waitnotify.h>
#include <os_sync.h>

#include <os_error.h>
#include <os_mem.h>
#include "os_internal.h"


int os_createWaitNotifyObject(char const* name, OS_HandleWaitNotify_s const** waitObjectP)
{ //folg. Mechanismus ist nicht verfügbar unter Win2000, wäre aber richtiger:
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
  { OS_HandleWaitNotify_s* waitObject = (OS_HandleWaitNotify_s*)os_allocMem(sizeof(OS_HandleWaitNotify_s));
    waitObject->winHandleWaitNotify = semaphor;
    waitObject->threadWait = null;
    *waitObjectP = waitObject;
  }
  return error;
}


/**removes a object for wait-notify.
 */
int os_removeWaitNotifyObject(struct OS_HandleWaitNotify_t const* waitObj)
{ HANDLE winHandleWaitNotify = waitObj->winHandleWaitNotify;
  os_freeMem((void*)waitObj);
  if ( CloseHandle( winHandleWaitNotify ) == 0 ) 
  {
    DWORD err = GetLastError();
    os_notifyError(-1, "os_removeWaitNotifyObj: ERROR: CloseHandle failed with Win err=%d\n", err, 0);
	  if (err==ERROR_INVALID_HANDLE)
    {	return OS_INVALID_HANDLE;
	  }
    else
	  { return OS_SYSTEM_ERROR;
    }
  }
  else
  { return OS_OK;
  } 
}


int os_wait(struct OS_HandleWaitNotify_t const* waitObjP, struct OS_Mutex_t* mutex, uint32 milliseconds)
{ //HANDLE semaphor = (HANDLE)handle;
  int error;
  struct OS_HandleWaitNotify_t* waitObj = (struct OS_HandleWaitNotify_t*)waitObjP;
  struct OS_ThreadContext_t const* pThread = os_getCurrentThreadContext();
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
  /**but now the mutex should be release, after storing the thread, os_notify should not test it before. */ 
  os_unlockMutex(mutex);
  //ab hier kann die Bedingungen geändert werden und notify wird gerufen, 
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
  os_lockMutex(mutex);
  waitObj->threadWait = null; 
  //
  //the user have to be unlock.
  return error;
}


/** Notifies all waiting thread to continue.
 */
int os_notifyAll(OS_HandleWaitNotify waitObject, struct OS_Mutex_t* hMutex)
{
  return -1;

}


/** Notifies only one waiting thread to continue.
 */
int os_notify(struct OS_HandleWaitNotify_t const* waitObjP, struct OS_Mutex_t* mutex)
{ struct OS_HandleWaitNotify_t* waitObj = (struct OS_HandleWaitNotify_t*)waitObjP;
  LONG prevCount;
  bool shouldNotify;
  int error = 0xbaadf00d;
  struct OS_ThreadContext_t const* pThread = os_getCurrentThreadContext();
  /*
  if(pThread != mutex->threadOwner)
  { os_Error("notify: it is necessary to have a os_lockMutex in the current thread", (int)mutex->threadOwner);
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
      os_unlockMutex(mutex);
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
      os_lockMutex(mutex);
    }
    else
    { error = OS_WARNING_NOTIFY_NothingIsWaiting;
    }
  }
  return error;  //the mutex is locked.
}


#if 0
int os_createMutex(struct OS_HandleMutex_t const** handle)
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

