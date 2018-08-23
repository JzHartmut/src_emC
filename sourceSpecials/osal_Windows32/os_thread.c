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
 * @content This file contains the implementation of os_thread.h for MS-Windows.
 * @author Hartmut Schorrig, Pinzberg, Germany and Marcos Rodriguez
 * @version 0.81ad
 * list of changes:
 * 2010-01-15 Hartmut adap, corr: einige details
 * 2010-01-15 Hartmut corr: Fehlerbehandlung, muss noch weiter geführt werden, Nutzung os_error.c, printf auf file? Vorversion im KM anschauen!
 * 2007-10-01: Hartmut creation
 * 2008-09-30: Hartmut, Marcos
 *
 ****************************************************************************/
#include <os_thread.h>
#include <os_mem.h>
#include <os_error.h>
#include <os_sync.h>


#undef boolean
#undef INT32
#undef UINT32
#undef int64
#undef uint64

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
	
  OS_HandleThread THandle;             /* handle des Threads */
	
  unsigned long uTID;                  /* ID des threads */
	
  OS_HandleEvent XXXEvHandle;                     /* Event des threads */
	
  uint XXXuFlagRegister;                  /* Actual flag status (32 bits) */
	
  //QueueStruct *pMessageQueue;		 /* Pointer to The MessageQueue Structure */
	//OS_HandleThread TDupHandle;          /* to be filled by the child */
  
  /**The thread run routine used for start the thread. */
  OS_ThreadRoutine* ThreadRoutine;     
	/** to be passed to the child wrapper routine */
  void*	pUserData;                     

  /**Name of the thread.*/
  const char* name; 

  OS_PtrValue userThreadContext;

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
struct OS_Mutex_t* XXXuThreadPoolSema = 0;              

static bool bOSALInitialized = false;

/**A pointer to test whether a void*-given data is really a OS_ThreadContext.
 * The content of variable isn't meanfull. The comarision of pointer is significant.
 */
const char* sSignificanceText_OS_ThreadContext = "OS_ThreadContext";


/** TLS index to store pseudo thread-handles as unique identifiers of threads 
 * (index is valid inside current thread if it was previously initialized)
 */
DWORD dwTlsIndex;

/* EXTERNALS *************************************************************************************/

/* PROTOTYPES ************************************************************************************/


/* IMPLEMENTATION ********************************************************************************/


  #define setCurrent_OS_ThreadContext(context) TlsSetValue(dwTlsIndex, context) 
  #define getCurrent_OS_ThreadContext() (OS_ThreadContext*)TlsGetValue(dwTlsIndex) 


/**@Beschreibung:
* Mit dieser Funktion wird eine abstrakte Thread-Priorität in einer betriebssystemspezifischen
* Thread-Priorität gewandelt.
* @return Betriebssystemspezifische Threadpriorität.
* @abstractPrio Abstrakte Threadpriorität (0-255).
*/
static int convertThreadPriority2Os(int abstractPrio)
{
  long priority;

  static int const delta = 63;
  if (abstractPrio <= 127 - delta) {
    priority = THREAD_PRIORITY_BELOW_NORMAL;
  }
  else if (abstractPrio >= 127 + delta) {
    priority = THREAD_PRIORITY_ABOVE_NORMAL;
  }
  else {
    priority = THREAD_PRIORITY_NORMAL;
  }
  return priority;
}





/**Searches a free slot in ThreadPool and returns it.
 * @return null if no slot free, it is a system exception.
 */
static OS_ThreadContext* new_OS_ThreadContext(const char* sThreadName)
{ OS_ThreadContext* threadContext = null;  //default if not found.
  int sizeThreadContext = sizeof(OS_ThreadContext); // + nrofBytesUserThreadContext_os_thread;
  threadContext = (OS_ThreadContext*)os_allocMem(sizeThreadContext);
  memset(threadContext, 0, sizeThreadContext); 
	return threadContext; 
}


// init adapter, to be called from main thread before calling any other function (only Windows)
int init_OSAL()
{
  if(bOSALInitialized){ return OS_UNEXPECTED_CALL; }
  else
  {
	  int idxThreadPool = 0;
	  HANDLE hMainHandle, hDupMainHandle;
    OS_ThreadContext* mainThreadContext;
    	  
	  // Allocate the global TLS index (valid for all threads when they are running (current thread)). 
	  if ((dwTlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES){
		  printf("init_OSAL: ERROR: TlsAlloc failed!\n"); 
	  }

    //os_createMutex("os_Threadpool", &uThreadPoolSema);
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
    mainThreadContext = new_OS_ThreadContext("main");
	  
	  if (mainThreadContext != null){
		  mainThreadContext->uTID = GetCurrentThreadId();
		  mainThreadContext->THandle = (OS_HandleThread) hDupMainHandle;
		  /* create an event for this thread (for use in eventFlag functions) */
		  //automatically resets the event state to nonsignaled after a single waiting thread has been released. 
		  mainThreadContext->XXXEvHandle = CreateEvent( NULL, FALSE, FALSE, NULL); 
		  if (mainThreadContext->XXXEvHandle == NULL){
			  printf("ERROR: init_OSAL: Failed to crate Event for thread:0x%x\n", (uint)hDupMainHandle);
		  }
		  mainThreadContext->XXXuFlagRegister = 0;
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
  }
}




// Wrapper thread function for thread creation and parameter initialization
void os_wrapperFunction(OS_ThreadContext* threadContext)
{
  STACKTRC_ROOT_ENTRY("os_wrapperThread");
  //HANDLE hChildHandle;
	
	//hChildHandle = GetCurrentThread();
	// get a pseudo handle for this thread to be referenced by other threads
	// Initialize the TLS index for this thread (store pseudo-handle). 
  OS_ThreadRoutine* fpStart;
	if(threadContext->sSignificanceText != sSignificanceText_OS_ThreadContext)
	{ printf("FATAL: threadContext incorrect: %p\n", threadContext);
	  os_notifyError(-1, "FATAL: threadContext incorrect: %p\n", (int)threadContext, 0);
	}
	{ bool ok = setCurrent_OS_ThreadContext(threadContext)!=0; 
    if (!ok  )
    { 
      printf("init_OSAL: ERROR: TlsSetValue for child failed!\n"); 
    }
  } 
  { //complete threadContext
   	/* create an event for this thread (for use in eventFlag functions) */
   	//automatically resets the event state to nonsignaled after a single waiting thread has been released. 
   	threadContext->XXXEvHandle = CreateEvent( NULL, FALSE, FALSE, NULL); 
   	if (threadContext->XXXEvHandle == NULL)
    {
   		printf("os_createThread: ERROR: Failed to create Event for thread:0x%x\n", (uint)threadContext->uTID);
    }
    threadContext->XXXuFlagRegister = 0;
  }

  // execute user routine
  fpStart = threadContext->ThreadRoutine;
  fpStart(threadContext->pUserData); //&threadContext->stacktraceThreadContext);		// execute user routine
    
  STACKTRC_LEAVE;	
  ExitThread(0);
  	
}

/**@Beschreibung:
 * Mit dieser Funktion wird einen Thread angelegt und gestartet.
 * @Rückgabewert: Ergebnis der Operation, 0 bei erfolgreicher Operation, ansonsten enthält der 
 * Rückgabewert einen detaillierten Fehlercode.
 * @pHandle Zeiger auf das Thread-Handle.
 * @routine Einsprungadresse des Threads.
 * @pUserData Zeiger auf die Parameter für die Übergabe in der Thread-Routine.
 * @pThreadName Name des Threads.
 * @abstactPrio Abstrakt Thread-Priorität (0-255).
 * @stackSize Größe des benötigten Stacks.
 * @Autor Rodriguez
 * @Datum 30.05.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @30.05.2008 / Rodriguez / Erste Implementierung.
 * @since 2008-09-30 redesign Hartmut
 */
int os_createThread
( OS_HandleThread* pHandle, 
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

  threadContext = new_OS_ThreadContext(sThreadName);
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
        printf( "os_createThread: ERROR: CreateThread failed with Win errorCode= %d\n", err );
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
	  threadContext->THandle = (OS_HandleThread)hDupChildHandle;

	  // set the thread prio
	  { long uWinPrio = convertThreadPriority2Os( abstactPrio );
	    //printf("DEBUG: os_createThread: abstrPrio=%d, WinPrio=%d\n", abstactPrio, uWinPrio);
        ret_ok = SetThreadPriority(threadHandle, uWinPrio);
        if ( ret_ok == 0 ) {
            DWORD err = GetLastError();
            printf( "os_createThread: ERROR: failed to set prio with Win errorCode= %d\n", err );
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
//int os_deleteThread(OS_HandleThread handle)
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
int os_setThreadPriority(OS_HandleThread handle, uint abstractPrio)
{   
  int ret_ok;
	long uWinPrio = convertThreadPriority2Os( abstractPrio );
	
	if (!bOSALInitialized){
		printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
    return OS_SYSTEM_ERROR;
  }
  
	//printf("DEBUG: os_setThreadPriority: astrPrio=%d, WinPrio=%d\n", abstractPrio, uWinPrio);
    ret_ok = SetThreadPriority( (HANDLE)handle, (int)uWinPrio );
    if ( ret_ok == 0 ){
        DWORD err = GetLastError();        
        printf("os_setThreadPriority: ERROR: set prio failed with Win errorCode= %d\n", err );
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
int os_suspendThread(OS_HandleThread handle)
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
int os_resumeThread(OS_HandleThread handle)
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
OS_HandleThread os_getCurrentThreadHandle(void)
{ 
	OS_HandleThread currHandle;
	OS_ThreadContext* threadContext = getCurrent_OS_ThreadContext();
  if (!bOSALInitialized){
		printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
    return 0;
  }
  currHandle = threadContext->THandle;
	if (currHandle==0){
		return (OS_HandleThread) GetCurrentThread();	// in worst case return constant handle (0xfffffffe)
	}
	return currHandle;
}



int os_getOsThreadPriority(OS_HandleThread handle) {
  return GetThreadPriority((HANDLE)handle);
}

/**liefert den ThreadContext des laufenden Threads zurück.
 * @return: Context des laufenden Threads.
 * @Autor Hartmut Schorrig 
 * @Datum 22.10.2008
 * @Änderungsübersicht: 
 * @Datum/Autor/Änderungen
 * @since 2008-10-22 / Hartmut Schorrig / Erste Implementierung.
 */
OS_ThreadContext* os_getCurrentThreadContext_intern()
{ 
  OS_ThreadContext* threadContext = getCurrent_OS_ThreadContext();
  if(threadContext == null)
  { //it is only null on the main thread if init_OSAL() was not called before.
    if(!bOSALInitialized)
    { init_OSAL();
      threadContext = getCurrent_OS_ThreadContext(); //at begin it is the main thread.
    }
    if(threadContext == null)  //it should be not null if init_OSAL() is 
    { 
      threadContext = new_OS_ThreadContext("unnamed");
	    if (threadContext != null)
      {
        HANDLE hThreadHandle, hDupThreadHandle;
  		  hThreadHandle = GetCurrentThread();
	      threadContext->uTID = GetCurrentThreadId();
	      DuplicateHandle
        ( GetCurrentProcess(), 
			    hThreadHandle, 
			    GetCurrentProcess(),
			    &hDupThreadHandle, 
			    0,
			    FALSE,
			    DUPLICATE_SAME_ACCESS 
        );

		    threadContext->THandle = (OS_HandleThread) hDupThreadHandle;
		    /* create an event for this thread (for use in eventFlag functions) */
		    //automatically resets the event state to nonsignaled after a single waiting thread has been released. 
		    threadContext->XXXuFlagRegister = 0;
  	    { 
          bool ok = setCurrent_OS_ThreadContext(threadContext)!=0; 
          if (!ok  ){ 
            printf("init_OSAL: ERROR: TlsSetValue for child failed!\n"); 
          }
        }
	    }
      else
      { os_notifyError(-1, "os_getCurrentThreadContext() - no ThreadContext found, error creating ThreadContext. ", 0, 0);
      }
    }
  }
  return threadContext;
}



PtrVal_MemUnit os_getCurrentUserThreadContext()
{ OS_ThreadContext const* threadContext = os_getCurrentThreadContext_intern();
  return threadContext->userThreadContext;
}

int os_setCurrentUserThreadContext(OS_PtrValue mem)
{ int error = 0;
  OS_ThreadContext* threadContext = os_getCurrentThreadContext_intern();
  void* userThreadContext = PTR_OS_PtrValue(threadContext->userThreadContext, void); 
  if( userThreadContext != null)
  { os_notifyError(-1, "os_setCurrentUserThreadContext(), a threadcontext exists. ", (int)userThreadContext, 0);
    error = OS_UNEXPECTED_CALL;
  }
  else
  { threadContext->userThreadContext = mem;
  }
  return error;
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
char* os_getTextOfOsError(int nError)
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






/**This mehtod is necessary because the user shouldn't know the struct ThreadContext.
* It should be hidden, but the embedded part of threadcontext for Stacktrace handling
* should be known in all user routines because it is used inline-like.
*/
ThreadContext_emC_s* getCurrent_ThreadContext_emC()
{
  ThreadContext_emC_s* thC;
  //The users thread context is managed but not knwon in detail from osal:
  MemC memThreadContext = os_getCurrentUserThreadContext();
  thC = PTR_MemC(memThreadContext, ThreadContext_emC_s);
  if (thC == null)
  {
    memThreadContext = alloc_MemC(sizeof(ThreadContext_emC_s));
    os_setCurrentUserThreadContext(memThreadContext);
    thC = PTR_MemC(memThreadContext, ThreadContext_emC_s);
  }
  return thC;  //it is a embedded struct inside the whole ThreadContext.
}


