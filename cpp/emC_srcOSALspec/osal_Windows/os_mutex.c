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
 * @content Bodies of mutex routines for Windows-XP and Windows-2000.
 * The implementation is os-specific. A mutex should regard a second call from the same thread.
 * It is more complex as a simple semaphore request. 
 * Some operation systems supports this request immediately. 
 * If a opeation system does know only the semaphore mechanism, the thread identification
 *   should be stored in a mutex structure.
 *
 * @author Hartmut Schorrig
 * @version sf-0.94
 * list of changes:
 * 2010-01-15 Hartmut adap: Some corrections 
 * 2008-09-30 Marcos: re-design of some methods
 * 2008-02-01: Hartmut creation 
 *
 ************************************************************************************************/
#include <applstdef_emC.h>
#include <emC/OSAL/sync_OSemC.h>
#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include <emC/Base/String_emC.h>

#undef INT32
#undef UINT32
#undef int64
//#undef uint64
#include "os_internal.h"
#include <windows.h>
#include <stdio.h>

/* CONSTANTS *************************************************************************************/


/* GLOBAL VARIABLES ******************************************************************************/


/* EXTERNALS *************************************************************************************/



/**Creates a mutex object.
 * @param name Name of the Mutex Object. In some operation systems this name should be unique. Please regard it, also in windows.
 * The mutex Object contains the necessary data for example a HANDLE etc.
 */
struct Mutex_OSemC_T const* createMutex_OSemC  (  char const* pName)
{

    HANDLE    hIOMutex;
    DWORD err;
    Mutex_OSemC_s* pMutex;
    const int zMutex = sizeof(Mutex_OSemC_s);
    
    hIOMutex = CreateMutex (NULL, FALSE, NULL);  // initially not owned
    if ( hIOMutex == NULL )
    {
		  err = GetLastError();
      STACKTRC_ENTRY("createMutex_OSemC");
      THROW_s0(IllegalStateException, "createMutex_OSemC: ERROR: create mutex failed with Win err", err, 0 );
      STACKTRC_RETURN null;
    }
	  pMutex = (Mutex_OSemC_s*)(os_allocMem(zMutex));
    //memset(pMutex, 0, zMutex); //already done in os_allocMem(...)
    pMutex->winHandleMutex  = hIOMutex;
    return pMutex;                         // returns a const*, automatically regarded.
}


void deleteMutex_OSemC  (  struct Mutex_OSemC_T const* pMutex)
{
  if (pMutex == null) return; //no THROW, it should be shown in lockMutex already.

  HANDLE winHandleMutex = pMutex->winHandleMutex;
  os_freeMem(pMutex);
  if( !CloseHandle( winHandleMutex ) )  //returns BOOL false on error 
  {
    DWORD err = GetLastError();
    STACKTRC_ENTRY("createMutex_OSemC");
    THROW_s0(IllegalStateException, "deleteMutex_OSemC: ERROR: CloseHandle failed with Win err", err, (int)(intPTR)winHandleMutex);
    STACKTRC_RETURN;
  }
}


bool lockMutex_OSemC  (  Mutex_OSemC_s const* pMutex, int timeout_millisec)
{
	DWORD WinRet;
  if(timeout_millisec ==0){ timeout_millisec = INFINITE; }
  if(pMutex !=null) {
    WinRet = WaitForSingleObject( pMutex->winHandleMutex, timeout_millisec );
    if (WinRet == WAIT_ABANDONED)
    { STACKTRC_ENTRY("lockMutex_OSemC");
      THROW_s0(IllegalStateException, "lockMutex_OSemC: ERROR: Mutex is blocked because a killed thread", (int32)(intptr_t)pMutex->winHandleMutex, 0);
      STACKTRC_RETURN false;
    }
    if (WinRet == WAIT_FAILED) {
      DWORD err = GetLastError();
      STACKTRC_ENTRY("lockMutex_OSemC");
      THROW_s0(IllegalStateException, "lockMutex_OSemC: ERROR: Mutex, debug necessary ", (int32)(intptr_t)pMutex->winHandleMutex, err);
      STACKTRC_RETURN false;
    }
    else {
      return (WinRet == WAIT_OBJECT_0 ? true : false); //true if signaled, false especially on WAIT_TIMEOUT
    }
  } else {
    STACKTRC_ENTRY("lockMutex_OSemC");
    THROW_s0(Exception, "mutex pointer is null", 0,0);
    STACKTRC_RETURN false;
  }
}


void unlockMutex_OSemC  (  struct Mutex_OSemC_T const* pMutex)
{
  if(pMutex == null) return; //no THROW, it should be shown in lockMutex already.
  /*
    struct OS_ThreadContext_t const* pThread = os_getCurrentThreadContext();
    struct OS_ThreadContext_t const* threadOwner = mutex->threadOwner;
    //it is neccesary to test whether the unlocker is the correct thread.
    if(pThread != threadOwner)
    { os_Error("faut thread", (int)pThread);
    }
    //first write null for locking thread, than release,
    //because anther thread may be locked immediately and will found an empty threadOwner!
    mutex->threadOwner = null;
  */
  if ( !ReleaseMutex( pMutex->winHandleMutex ) ) { //returns BOOL false on error 
    int32 err;
    STACKTRC_ENTRY("unlockMutex_OSemC");
    //revert infos because the unlock isn't valid! It is important for debug
    //mutex->threadOwner = threadOwner;
    err = GetLastError();
    if (err == ERROR_NOT_OWNER)
    { /**It is helpfull to produce another error message if another thread release the mutex,
       * because it is a users programming error. */
      THROW_s0(Exception, "unlockMutex_OSemC: ERROR: Faild thread releases the mutex, win-error", err, (int)(intPTR)pMutex);		
    }
    else
    {
      THROW_s0(Exception, "unlockMutex_OSemC: ERROR: ReleaseMutex failed with win-error", err, (int)(intPTR)pMutex);
	  }
    STACKTRC_LEAVE;
  }
}
