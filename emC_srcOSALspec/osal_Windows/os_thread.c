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
 * @content This file contains the implementation of thread_OSemC.h for MS-Windows.
 * @author Hartmut Schorrig, Pinzberg, Germany and Marcos Rodriguez
 * @version 0.81ad
 * list of changes:
 * 2010-01-15 Hartmut adap, corr: einige details
 * 2010-01-15 Hartmut corr: Fehlerbehandlung, muss noch weiter geführt werden, Nutzung os_error.c, printf auf file? Vorversion im KM anschauen!
 * 2007-10-01: Hartmut creation
 * 2008-09-30: Hartmut, Marcos
 *
 ****************************************************************************/
#include <applstdef_emC.h>
#include <emC/OSAL/thread_OSemC.h>
#include <emC/OSAL/os_mem.h>
#include <emC/OSAL/os_error.h>
#include <emC/OSAL/sync_OSemC.h>


#undef boolean
#undef INT32
#undef UINT32
#undef int64
//#undef uint64

#include <wtypes.h>
#include <winbase.h>
#include <stdio.h>

/* Compiler switches for some test variants for Stacktrace. */

//#define NOT_TlsGetValue
//#define TEST_ThreadContext_IMMEDIATE


/* Internal structures *******************************************************************/

typedef struct OS_ThreadContext_t
{                    /* Structure for thread-eventFlags */
	
  /**This is a constant text, to test whether a reference to OS_ThreadContext is correct.
   * It will be initialized with pointer to "OS_ThreadContext".
   */
  const char* sSignificanceText;

  //bool bInUse;                         /* structure in use */
	
  HandleThread_OSemC THandle;             /* handle des Threads */
	
  uint32 uTID;                  /* ID des threads */
	
  //QueueStruct *pMessageQueue;		 /* Pointer to The MessageQueue Structure */
	//HandleThread_OSemC TDupHandle;          /* to be filled by the child */
  
  /**The thread run routine used for start the thread. */
  OS_ThreadRoutine* ThreadRoutine;     
	/** to be passed to the child wrapper routine */
  void*	pUserData;                     

  /**Name of the thread.*/
  const char* name; 

  #ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
  /**The user ThreadContext is part of the thread specific data. 
   * It is defined application-specific via the included applstdef_emC.h */
  ThreadContext_emC_s userThreadContext;
  #endif

}OS_ThreadContext;

/* CONSTANTS *************************************************************************************/
/**this value defines the max num of threads with an attached EventFlag, if more threads are
   created in the same process, they will have no attached EventFlag and flag related functions 
   will not work on these threads 
*/
#define XXXOS_maxNrofThreads	256

/**For PC-application: use 32k Stack per thread. */
#define OS_DEFAULT_STACK 0x8000

/* GLOBAL VARIABLES ******************************************************************************/

/* actual number of threads */
uint XXXuThreadCounter = 0;               

/* Thread protection to access the handle pool.  */
struct Mutex_OSemC_T const* XXXuThreadPoolSema = 0;              

static bool bOSALInitialized = false;

/**A pointer to test whether a void*-given data is really a OS_ThreadContext.
 * The content of variable isn't meanfull. The comarision of pointer is significant.
 */
static const char* sSignificanceText_OS_ThreadContext = "OS_ThreadContext";


/** TLS index to store pseudo thread-handles as unique identifiers of threads 
 * (index is valid inside current thread if it was previously initialized)
 */
static DWORD dwTlsIndex;

/* EXTERNALS *************************************************************************************/

/* PROTOTYPES ************************************************************************************/


/* IMPLEMENTATION ********************************************************************************/


  #define setCurrent_OS_ThreadContext(context) TlsSetValue(dwTlsIndex, context) 
OS_ThreadContext* getCurrent_OS_ThreadContext() { return (OS_ThreadContext*)TlsGetValue(dwTlsIndex); }


int os_getRealThreadPriority(int abstractPrio)
{
  long priority;

  static int const delta = 63;
  if (abstractPrio <= 127 - delta) {
    priority = THREAD_PRIORITY_BELOW_NORMAL;
  }
  else if(abstractPrio >= 240) {
    priority = THREAD_BASE_PRIORITY_LOWRT;  //seems to be the realtime priority in windows.
  }
  else if(abstractPrio >= 200) {
    priority = abstractPrio - 200;  //for experience. What does windows?
  }
  else if(abstractPrio >= 192) {
    priority = THREAD_BASE_PRIORITY_MAX;
  }
  else if (abstractPrio >= 127 + delta) {
    priority = THREAD_PRIORITY_ABOVE_NORMAL;
  }
  else {
    priority = THREAD_PRIORITY_NORMAL;
  }
  return priority;
}





static OS_ThreadContext* new_OS_ThreadContext(const char* sThreadName, void* topAddrStack)
{ OS_ThreadContext* threadContext = null;  //default if not found.
  int sizeThreadContext = sizeof(OS_ThreadContext); // + nrofBytesUserThreadContext_os_thread;
  threadContext = (OS_ThreadContext*)os_allocMem(sizeThreadContext);
  memset(threadContext, 0, sizeThreadContext);
  #ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
  ctor_ThreadContext_emC(&threadContext->userThreadContext, topAddrStack);   //This constructor depends of the settings in <applstdef_emC.h>. There it is defined which type of ThreadContext is used.
	#endif
  return threadContext; 
}


// init adapter, to be called from main thread before calling any other function (only Windows)
int init_OSAL()
{
  if(bOSALInitialized){ return OS_UNEXPECTED_CALL; }
  else {
  	  int idxThreadPool = 0;
	  HANDLE hMainHandle, hDupMainHandle;
    #ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
    OS_ThreadContext* mainThreadContext;
    #endif	  
	  // Allocate the global TLS index (valid for all threads when they are running (current thread)). 
	  if ((dwTlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES){
		  printf("init_OSAL: ERROR: TlsAlloc failed!\n"); 
	  }

    //createMutex_OSemC("os_Threadpool", &uThreadPoolSema);
	  hMainHandle = GetCurrentThread();
	  // get a pseudo handle for the main thread to be referenced by other threads
	  DuplicateHandle(    GetCurrentProcess(), 
						  hMainHandle, 
						  GetCurrentProcess(),
						  &hDupMainHandle, 
						  0,
						  FALSE,
						  DUPLICATE_SAME_ACCESS );

	  // store thread parameters in thread pool (first thread, no thread protection)
    #ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
      mainThreadContext = new_OS_ThreadContext("main", &idxThreadPool);
	  
	    if (mainThreadContext != null){
		    mainThreadContext->uTID = GetCurrentThreadId();
		    mainThreadContext->THandle = (HandleThread_OSemC) hDupMainHandle;
		    /* create an event for this thread (for use in eventFlag functions) */
		    //automatically resets the event state to nonsignaled after a single waiting thread has been released. 
        bOSALInitialized = true;
	      { bool ok = setCurrent_OS_ThreadContext(mainThreadContext)!=0; 
          if (!ok  ){ 
            printf("init_OSAL: ERROR: TlsSetValue for child failed!\n"); 
          }
        }
        return 0; 
	    }
      else
      { printf("too many threads");
        return OS_SYSTEM_ERROR;
      }
    #else
      return 0;
    #endif //DEF_NO_THCXT_STACKTRC_EXC_emC


  }
}




// Wrapper thread function for thread creation and parameter initialization
void os_wrapperFunction(OS_ThreadContext* threadContext)
{
  //HANDLE hChildHandle;
	
	//hChildHandle = GetCurrentThread();
	// get a pseudo handle for this thread to be referenced by other threads
	// Initialize the TLS index for this thread (store pseudo-handle). 
  OS_ThreadRoutine* fpStart;
	if(threadContext->sSignificanceText != sSignificanceText_OS_ThreadContext)
	{ printf("FATAL: threadContext incorrect: %p\n", threadContext);
	  ERROR_SYSTEM_emC(-1, "FATAL: threadContext incorrect: %p\n", (int)(intptr_t)threadContext, 0);
	}
	{ bool ok = setCurrent_OS_ThreadContext(threadContext)!=0; 
    if (!ok  )
    { 
      printf("init_OSAL: ERROR: TlsSetValue for child failed!\n"); 
    }
  } 

  // execute user routine
  STACKTRC_ROOT_ENTRY("os_wrapperThread");
  fpStart = threadContext->ThreadRoutine;
  fpStart(threadContext->pUserData); 		//=============== execute user routine
    
  STACKTRC_LEAVE;	
  ExitThread(0);
  	
}



int os_createThread
( HandleThread_OSemC* pHandle, 
  OS_ThreadRoutine routine, 
  void* pUserData, 
  char const* sThreadName, 
  int abstactPrio, 
  int stackSize )
{
  int iWinRet = 0;
  unsigned long uThreadID;
  HANDLE hDupChildHandle;
  int ret_ok;
	int idxThreadPool = 0;
  OS_ThreadContext* threadContext = null;
	//WraperParamStruct ThreadWraperStr;
  
  HANDLE threadHandle;
    
  if (!bOSALInitialized)
  { init_OSAL();
    	//printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
    	//return OS_SYSTEM_ERROR;
  }
  if (stackSize == 0 || stackSize == -1)
  {
    stackSize = OS_DEFAULT_STACK;
  }

  if(abstactPrio <= 0 || abstactPrio > 255)
  {
    abstactPrio = 128;
  }

  threadContext = new_OS_ThreadContext(sThreadName, null);
	if(threadContext != null)
  { threadContext->ThreadRoutine = routine;	// user routine
	  threadContext->pUserData = pUserData;		// user data
	  threadContext->sSignificanceText = sSignificanceText_OS_ThreadContext;
    //threadContext->callParams.TDupHandle = 0;				// to be filled by the child thread in the wrapper
    threadHandle = CreateThread(
                            NULL,
                            stackSize,
                            (LPTHREAD_START_ROUTINE)(os_wrapperFunction),
                            (void*)threadContext,
                            CREATE_SUSPENDED,			//wait because some values should be initialized
                            &uThreadID);       
    if ( threadHandle == NULL ) {
        DWORD err = GetLastError();
        printf( "os_createThread: ERROR: CreateThread failed with Win errorCode= %d\n", (int)err );
        if (err==ERROR_INVALID_PARAMETER){
        	return OS_INVALID_PARAMETER;
        	}
        return OS_SYSTEM_ERROR;
    }
	  DuplicateHandle
    ( GetCurrentProcess(), 
			threadHandle, 
			GetCurrentProcess(),
			&hDupChildHandle, 
			0,
			FALSE,
			DUPLICATE_SAME_ACCESS 
    );

    threadContext->uTID = uThreadID;
	  threadContext->THandle = (HandleThread_OSemC)hDupChildHandle;

	  // set the thread prio
	  { long uWinPrio = os_getRealThreadPriority( abstactPrio );
	    //printf("DEBUG: os_createThread: abstrPrio=%d, WinPrio=%d\n", abstactPrio, uWinPrio);
        ret_ok = SetThreadPriority(threadHandle, uWinPrio);
        if ( ret_ok == 0 ) {
            DWORD err = GetLastError();
            printf( "os_createThread: ERROR: failed to set prio with Win errorCode= %d\n", (int)err );
            if (err==ERROR_INVALID_PARAMETER){
        	    return OS_INVALID_PARAMETER;
        	    }
            return OS_SYSTEM_ERROR;
        }
	    ResumeThread(threadHandle);				// start thread
    }
    *pHandle = threadContext->THandle;	// return the pseudo handle
    return OS_OK;
  }
  else 
  { //no space in threadpool, no threadContext
    *pHandle = null;
    return OS_SYSTEM_ERROR;
  }
	
}




/**@Beschreibung:
 * Mit dieser Funktion wird einen Thread beendet.
 * @Rückgabewert: Ergebnis der Operation, 0 bei erfolgreicher Operation, ansonsten enthält der 
 * Rückgabewert einen detaillierten Fehlercode.
 * @handle Handle des Ziel-Threads.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 */
//int os_deleteThread(HandleThread_OSemC handle)
//{
//	HANDLE ThreadHandle = GetCurrentThread();
//	if(ThreadHandle == (HANDLE)handle){
//		ExitThread(0);						/* Thread terminates by itself */
//	}
//	else{
//		TerminateThread((HANDLE)handle,0);	/* Terminates other thread */
//	}
//	/* may be memory leakage of the handle */
//	return OS_OK;
//}


/**@Beschreibung:
 * Mit diesem Aufruf wird die Priorität eines beliebigen Threads verändert.
 * @Rückgabewert: 0 beim erfolgreichen Operation,ansonsten enthält der Rückgabewert einen 
 * detaillierten Fehlercode.
 * @handle Handle des Ziel-Threads.
 * @abstractPrio Abstrakt Thread-Priorität (0-255).
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 * @since 2008-09-30 redesign Hartmut
 */
int os_setThreadPriority(HandleThread_OSemC handle, uint abstractPrio)
{   
  int ret_ok;
	long uWinPrio = os_getRealThreadPriority( abstractPrio );
	
	if (!bOSALInitialized){
		printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
    return OS_SYSTEM_ERROR;
  }
  
	//printf("DEBUG: os_setThreadPriority: astrPrio=%d, WinPrio=%d\n", abstractPrio, uWinPrio);
    ret_ok = SetThreadPriority( (HANDLE)handle, (int)uWinPrio );
    if ( ret_ok == 0 ){
        DWORD err = GetLastError();        
        printf("os_setThreadPriority: ERROR: set prio failed with Win errorCode= %d\n", (int)err );
        if (err==ERROR_INVALID_PARAMETER){
        	return OS_INVALID_PARAMETER;
        	}
        else if(err==ERROR_INVALID_HANDLE){
             return OS_INVALID_HANDLE;	
        	}
        return OS_UNKNOWN_ERROR;
    }
	return OS_OK;
}


/**@Beschreibung:
 * Diese Funktion suspendiert einen beliebigen Thread für eine undefinierte Zeit.
 * @Rückgabewert: Ergebnis der Operation, 0 bei erfolgreicher Operation, ansonsten enthält der 
 * Rückgabewert einen detaillierten Fehlercode.
 * @handle Handle des Ziel-Threads.
 * @Autor Rodriguez
 * @Datum 18.06.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @18.06.2008 / Rodriguez / Erste Implementierung.
 * @since 2008-09-30 redesign Hartmut
 */
int os_suspendThread(HandleThread_OSemC handle)
{

	if (!bOSALInitialized){
		printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
    return OS_SYSTEM_ERROR;
  }
  
	{ DWORD WinRet = SuspendThread( (HANDLE)handle );
	  if(WinRet == -1){
      DWORD err = GetLastError();
      printf( "os_suspendThread: ERROR: failed to suspend with Win errorCode= %d\n", err );
      if (err==ERROR_INVALID_HANDLE){
         return OS_INVALID_HANDLE;
      }
  	  return OS_UNKNOWN_ERROR;
	  }
  }
	return OS_OK;
}


/**@Beschreibung:
 * Diese Funktion aktiviert einen suspendierten Thread wieder.
 * @Rückgabewert: Ergebnis der Operation, 0 bei erfolgreicher Operation, ansonsten enthält der 
 * Rückgabewert einen detaillierten Fehlercode.
 * @handle Handle des Ziel-Threads.
 * @Autor Rodriguez
 * @Datum 18.06.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @18.06.2008 / Rodriguez / Erste Implementierung.
 */
int os_resumeThread(HandleThread_OSemC handle)
{

	if (!bOSALInitialized){
		printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
    return OS_SYSTEM_ERROR;
  }
  
	{ DWORD WinRet = ResumeThread( (HANDLE)handle );
	  if(WinRet == -1){
		  DWORD err = GetLastError();
		  printf( "os_resumeThread: ERROR: failed to resume with Win errorCode= %d\n", err );
		  if (err==ERROR_INVALID_HANDLE){
			  return OS_INVALID_HANDLE;
		  }
  		  return OS_UNKNOWN_ERROR;
	  }
  }
	return OS_OK;
}

/**@Beschreibung:
 * Diese Funktion liefert das Handle des laufenden Threads zurück.
 * @Rückgabewert: Handle des laufenden Threads.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 */
HandleThread_OSemC os_getCurrentThreadHandle(void)
{ 
	HandleThread_OSemC currHandle;
	OS_ThreadContext* threadContext = getCurrent_OS_ThreadContext();
  if (!bOSALInitialized){
		printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
    return 0;
  }
  currHandle = threadContext->THandle;
	if (currHandle==0){
		return (HandleThread_OSemC) GetCurrentThread();	// in worst case return constant handle (0xfffffffe)
	}
	return currHandle;
}



int os_getOsThreadPriority(HandleThread_OSemC handle) {
  return GetThreadPriority((HANDLE)handle);
}







/**@Beschreibung:
 * Diese Funktion liefert die Beschreibung in Klartext einer Fehlermeldung der OS-Funktionen.
 * @Rückgabewert: Ergebnis der Operation, 0 bei erfolgreicher Operation, ansonsten enthält der 
 * Rückgabewert einen detaillierten Fehlercode.
 * @nError Fehlermeldungsnummer.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 * @since 2008-09-30 redesign Hartmut
 */
char const* os_getTextOfOsError(int nError)
{
	switch (nError){
	case OS_SYSTEM_ERROR:        return "System Fehler.";
/*
	case OS_INVALID_PARAMETER:   return "in Parameter war ungültig.";
	case OS_INVALID_STRING:      return  "Ein String ist nicht innerhalb der vorgegebenen Größe.";
	case OS_INVALID_HANDLE:      return "Das Objekt-Handle ist ungültig.";
	case OS_INVALID_STATE:       return "Der Objekt-Sustand ist ungültig für diese Operation.";
	case OS_TEST_NOT_OK:         return "Testbedingungen nicht erfüllt.";
	case OS_GOT_TIMEOUT:         return "Der Aufruf wurde nach dem eingestellten Timeout abgebrochen.";
	case OS_QUEUE_EXIST:         return "Die Message-Queue existiert bereits für diesen Thread.";
	case OS_QUEUE_NOT_EXIST:     return "Die Message-Queue dieses Thread existiert nicht.";
	case OS_RESOURCE_BUSY:       return "In diesem Objekt stehen noch Nachrichten, oder ein Thread wartet.";
	case OS_QUEUE_FULL:          return "Die Message–Queue ist voll.";
	case OS_QUEUE_EMPTY:         return "Die Message-Queue enthält keine Nachricht.";
	case OS_NAME_EXIST:          return "Der Name existiert bereits.";
	case OS_NAME_NOT_EXIST:      return "Der angegebene Name existiert im System nicht.";
	case OS_MAILBOX_FULL:        return "Die Anforderung überschreitet die eingetragene Grenze der Mailbox.";
	case OS_MAILBOX_EMPTY:       return "Die Mailbox enthält keine Nachricht (wenn timeOut = 0).";
	case OS_INVALID_POINTER:     return "Zeiger zu Resource ungültig.";
	case OS_UNKNOWN_ERROR:       return "Undefinierte Fehlermeldung.";
*/
	default:                     return "Unknown error-code.";
	}
}





#ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
ThreadContext_emC_s* getCurrent_ThreadContext_emC  ()
{
  OS_ThreadContext* os_thCxt = getCurrent_OS_ThreadContext();
  if(os_thCxt == null){ //only on startup in main without multithreading 
    init_OSAL();  //only 1 cause if the ThreadContext haven't set.
    os_thCxt = getCurrent_OS_ThreadContext();  //repeat it
    if (os_thCxt == null) {
      ERROR_SYSTEM_emC(-1, "init_OSAL failed, no ThreadConect", 0,0);
      return null;
    }
  }
  return &os_thCxt->userThreadContext;  //it is a embedded struct inside the whole ThreadContext.
}
#endif

