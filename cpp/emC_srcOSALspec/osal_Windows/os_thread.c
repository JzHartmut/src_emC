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
 * @version 2023-01-11
 * list of changes:
 * 2023-01-11 refactored due to new documentation. 
 * 201x some usage and adaption
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


#undef boolean    // undef this, it is conflicting with windows-system headers.
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




/* CONSTANTS *************************************************************************************/

/**For PC-application: use 32k Stack per thread. */
#define OS_DEFAULT_STACK 0x8000

/* GLOBAL VARIABLES ******************************************************************************/

/**This variable is initialized in os_init(). The main thread runs by itself
 * and it gets there its emC-defined data. 
 */
static Thread_OSemC* mainThread = null;

//yet unnecessary, use mainThread ==null check
static bool bOSALInitialized = false;

/**A pointer to test whether a void*-given data is really a Thread_OSemC.
 * The content of variable isn't meanfull. The comarision of pointer is significant.
 */
static const char* sSignificanceText_Thread_OSemC = "Thread_OSemC";


/** TLS index to store a handle as unique identifiers of values 
 * (index is valid inside any current thread as key for "Thread Specific Values"
 * It is initialized in os_init()
 */
static DWORD dwTlsIndex;


#define setCurrent_Thread_OSemC(context) TlsSetValue(dwTlsIndex, context) 

//definition see thread_OSemC.h:
Thread_OSemC* getCurrent_Thread_OSemC() { return (Thread_OSemC*)TlsGetValue(dwTlsIndex); }


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


//creates the emC specific thread data, only used in os_init().
static Thread_OSemC* new_Thread_OSemC(const char* sThreadName, void* topAddrStack)
{ Thread_OSemC* threadContext = null;  //default if not found.
  int sizeThreadContext = sizeof(Thread_OSemC); // + nrofBytesUserThreadContext_os_thread;
  threadContext = (Thread_OSemC*)os_allocMem(sizeThreadContext);
  memset(threadContext, 0, sizeThreadContext);
  #ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
  ctor_ThreadContext_emC(&threadContext->userThreadContext, topAddrStack);   //This constructor depends of the settings in <applstdef_emC.h>. There it is defined which type of ThreadContext is used.
	#endif
  return threadContext; 
}


// this should be called one time if any of thread data are necessary. 
static int init_OSAL()
{
  if(bOSALInitialized){ return OS_UNEXPECTED_CALL; }
  else {
  	  int idxThreadPool = 0;
	  HANDLE hMainHandle, hDupMainHandle;
    #ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
    //Thread_OSemC* mainThreadContext;
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
      mainThread = new_Thread_OSemC("main", &idxThreadPool);
	  
	    if (mainThread != null){
		    mainThread->nThreadID = GetCurrentThreadId();
		    mainThread->handleThread = hDupMainHandle;
		    /* create an event for this thread (for use in eventFlag functions) */
		    //automatically resets the event state to nonsignaled after a single waiting thread has been released. 
        bOSALInitialized = true;
	      { bool ok = setCurrent_Thread_OSemC(mainThread)!=0; 
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
// This function is used anytime for the start thread function. 
void os_wrapperFunction(Thread_OSemC* threadContext)
{
	if(threadContext->sSignificanceText != sSignificanceText_Thread_OSemC)
	{ printf("FATAL: threadContext incorrect: %p\n", threadContext);
	  ERROR_SYSTEM_emC(-1, "FATAL: threadContext incorrect: %p\n", (int)(intptr_t)threadContext, 0);
	}
	{ bool ok = setCurrent_Thread_OSemC(threadContext)!=0; 
    if (!ok  )
    { 
      printf("init_OSAL: ERROR: TlsSetValue for child failed!\n"); 
    }
  } 

  // execute user routine
  STACKTRC_ROOT_ENTRY("os_wrapperThread");
  threadContext->state = mRunning_Thread_OSemC;
  OS_ThreadRoutine* fpStart = threadContext->ThreadRoutine;
  //======>>>>>>
  fpStart(threadContext->pUserData); 		//=============== execute user routine
    
  STACKTRC_LEAVE;	
  threadContext->state = mFinished_Thread_OSemC;
  ExitThread(0);
  	
}



Thread_OSemC* main_Thread_OSemC ( ) {
  if(mainThread ==null) {
    init_OSAL();
  }
  return mainThread;
}


Thread_OSemC* alloc_Thread_OSemC ( char const* sThreadName 
, OS_ThreadRoutine routine,  void* pUserData 
, int abstractPrio, int stackSize ) {

  Thread_OSemC* thiz = C_CAST(Thread_OSemC*, os_allocMem(sizeof(Thread_OSemC)));
  create_Thread_OSemC(thiz, sThreadName, routine, pUserData, abstractPrio, stackSize);
  return thiz;
}



int create_Thread_OSemC
( Thread_OSemC* thiz, 
  char const* sThreadName, 
  OS_ThreadRoutine routine, 
  void* pUserData, 
  int abstractPrio, 
  int stackSize )
{
  int iWinRet = 0;
  unsigned long uThreadID;
  HANDLE hDupChildHandle;
  int ret_ok;
	int idxThreadPool = 0;
  
  HANDLE threadHandle;
    
  if (!bOSALInitialized)
  { init_OSAL();
    	//printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
    	//return OS_SYSTEM_ERROR;
  }
  thiz->name = sThreadName;
  if (stackSize == 0 || stackSize == -1)
  {
    stackSize = OS_DEFAULT_STACK;
  }

  if(abstractPrio <= 0 || abstractPrio > 255)
  {
    abstractPrio = 128;
  }
  ctor_ThreadContext_emC(&thiz->userThreadContext, null);   //This constructor depends of the settings in <applstdef_emC.h>. There it is defined which type of ThreadContext is used.

  thiz->ThreadRoutine = routine;	// user routine
	thiz->pUserData = pUserData;		// user data
	thiz->sSignificanceText = sSignificanceText_Thread_OSemC;
  //thiz->callParams.TDupHandle = 0;				// to be filled by the child thread in the wrapper
  threadHandle = CreateThread(
                          NULL,
                          stackSize,
                          (LPTHREAD_START_ROUTINE)(os_wrapperFunction),
                          (void*)thiz,
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

  thiz->nThreadID = uThreadID;
	thiz->handleThread = hDupChildHandle;

	// set the thread prio
	{ long uWinPrio = os_getRealThreadPriority( abstractPrio );
	  //printf("DEBUG: os_createThread: abstrPrio=%d, WinPrio=%d\n", abstractPrio, uWinPrio);
      ret_ok = SetThreadPriority(threadHandle, uWinPrio);
      if ( ret_ok == 0 ) {
          DWORD err = GetLastError();
          printf( "os_createThread: ERROR: failed to set prio with Win errorCode= %d\n", (int)err );
          if (err==ERROR_INVALID_PARAMETER){
        	  return OS_INVALID_PARAMETER;
        	  }
          return OS_SYSTEM_ERROR;
      }
  }
  thiz->state = mCreated_Thread_OSemC;

  return OS_OK;
	
}



bool start_Thread_OSemC ( Thread_OSemC* thiz) {
	HANDLE h = thiz->handleThread;
  if(h ==null || thiz->state != mCreated_Thread_OSemC ) {
    THROW_s0n(IllegalStateException, "Thread finished or not initialized", 0, 0);
  }
  thiz->state = mStarted_Thread_OSemC;
  int err = ResumeThread(h);				// start thread
  return err >=0;
}




/**remove a thread handle.
 */
bool delete_Thread_OSemC(Thread_OSemC* thiz) {
	HANDLE h = thiz->handleThread;
  if(h ==null || (thiz->state & (mCreated_Thread_OSemC | mFinished_Thread_OSemC))==0 ) {
    THROW_s0n(IllegalStateException, "Thread running or not exisiting", 0, 0);
    return false;
  }
  BOOL ok = CloseHandle(h);
  if(ok ==0) {
    uint err = GetLastError();
    THROW_s0n(IllegalStateException, "Thread CloseHandle error", err, 0);
    return false;
  }
  return true;
}
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


int os_getOsThreadPriority(HandleThread_OSemC handle) {
  return GetThreadPriority((HANDLE)handle);
}











#ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
/**Implementation of definition in emC/Base/Exception_emC.h:
 * The Exception used thread context is part of the thread data of the operation system,
 * hence defined here. 
 */
ThreadContext_emC_s* getCurrent_ThreadContext_emC  ()
{
  Thread_OSemC* os_thCxt = getCurrent_Thread_OSemC();
  if(os_thCxt == null){ //only on startup in main without multithreading 
    init_OSAL();  //only 1 cause if the ThreadContext haven't set.
    os_thCxt = getCurrent_Thread_OSemC();  //repeat it
    if (os_thCxt == null) {
      ERROR_SYSTEM_emC(-1, "init_OSAL failed, no ThreadConect", 0,0);
      return null;
    }
  }
  return &os_thCxt->userThreadContext;  //it is a embedded struct inside the whole ThreadContext.
}
#endif

