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
 * 2007-10-01: Hartmut creation
 * 2008-09-30: Hartmut, Marcos
 *
 ****************************************************************************/
//the own include file firstly
#include <emC/OSAL/thread_OSemC.h>

//needed from os_adaption itself
#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include <emC/OSAL/sync_OSemC.h>
#include <emC_srcOSALspec/os_LinuxGcc/os_internal.h>

//Needed includes from os:
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //memset

#define OS_DEFAULT_STACK 10000

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

  pthread_t handleThread;             /* handle des Threads */

  pthread_t uTID;                  /* ID des threads */

  OS_HandleEvent EvHandle;                     /* Event des threads */

  uint uFlagRegister;                  /* Actual flag status (32 bits) */
  
  //QueueStruct *pMessageQueue;     /* Pointer to The MessageQueue Structure */
  //OS_HandleThread TDupHandle;          /* to be filled by the child */

  /**The thread run routine used for start the thread. */
  OS_ThreadRoutine* ThreadRoutine;
  /** to be passed to the child wrapper routine */
  void*  pUserData;

  /**Name of the thread.*/
  const char* name; 

  /**The user ThreadContext is part of the thread specific data.
   * It is defined application-specific via the included applstdef_emC.h */
  ThreadContext_emC_s userThreadContext;

}OS_ThreadContext;

/* CONSTANTS *************************************************************************************/
/**this value defines the max num of threads with an attached EventFlag, if more threads are
   created in the same process, they will have no attached EventFlag and flag related functions 
   will not work on these threads 
*/
#define OS_maxNrofThreads  256

/* GLOBAL VARIABLES ******************************************************************************/

/**The pool of all thread contexts. It is a staticly amount of data. */
//OS_ThreadContext* ThreadPool[OS_maxNrofThreads] = {0};

/* actual number of threads */
uint uThreadCounter = 0;               

/* Thread protection to access the handle pool.  */
Mutex_OSemC_s const* uThreadPoolSema = null;

bool bLibIsInitialized = false;

/**A pointer to test whether a void*-given data is really a OS_ThreadContext.
 * The content of variable isn't meanfull. The comarision of pointer is significant.
 */
const char* sSignificanceText_OS_ThreadContext = "OS_ThreadContext";



/**Key for TSD (thread specific data) to store this data inclusively the user thread context.
 * Note: http://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap10-008.htm#RxxKap10008040003221F025100
 */
static pthread_key_t keyThreadContext;


/* IMPLEMENTATION ********************************************************************************/


/**This method should be called on startup of the system.
 * It is called elsewhere from the routines, which needs them.
 */
//void init_OSAL();


/**Searches a free slot in ThreadPool and returns it.
 * @return null if no slot free, it is a system exception.
 */
static OS_ThreadContext* new_OS_ThreadContext(const char* sThreadName)
{ //int idxThreadPool;
  //int ok = 0;
  OS_ThreadContext* threadContext = null;  //default if not found.
  threadContext = (OS_ThreadContext*)os_allocMem(sizeof(*threadContext));  //
  memset(threadContext, 0, sizeof(*threadContext));
  threadContext->sSignificanceText = sSignificanceText_OS_ThreadContext;
  threadContext->name = sThreadName;
  return threadContext;
  #if 0
  /* search for free struct in the pool */
  ok = os_lockMutex( uThreadPoolSema, 0 );
  /*
  DWORD winRet = WaitForSingleObject( uThreadPoolSema, -1 );
  if (WinRet == WAIT_FAILED)
  {  error = GetLastError();
    os_Error( "os_waitMutex: ERROR: WaitForSingleObject failed with Win err=%d\n", error );
  }
  */
  if(ok >= 0)
  { for (idxThreadPool=1; idxThreadPool<OS_maxNrofThreads; idxThreadPool++)
    {
      if ( ThreadPool[idxThreadPool] == null )
      { int sizeThreadContext = sizeof(OS_ThreadContext); // + nrofBytesUserThreadContext_os_thread;
        threadContext = (OS_ThreadContext*)os_allocMem(sizeThreadContext);
        memset(threadContext, 0, sizeThreadContext); 
        ThreadPool[idxThreadPool] = threadContext; // = ctorc_OS_ThreadContext(threadContext, sThreadName, 250);
        break;
      }
    }
  }
  os_unlockMutex( uThreadPoolSema );
  //if(ok < 0) os_NotifyError( -1, "os_unlockMutex: Problem after getting a new OS_ThreadContext err=%d", ok,0 );
  return threadContext; 
#endif
}



// init adapter, to be called from main thread before calling any other function (only Windows)
static void init_OSAL()
{
  if(!bLibIsInitialized) {
    int ok = pthread_key_create(&keyThreadContext, null);               //The key for all threads to get Thread Related Data
    ASSERT_emC(ok==0, "key for thread context fault", ok, 0);

    OS_ThreadContext* mainThreadContext;


    //uThreadPoolSema = os_createMutex("os_Threadpool");

    // store thread parameters in thread pool (first thread, no thread protection)
    mainThreadContext = new_OS_ThreadContext("main");
    void* topStackAddr = &mainThreadContext;  //maybe a proper value
    ctor_ThreadContext_emC(&mainThreadContext->userThreadContext, topStackAddr);

    if (mainThreadContext != null){
      pthread_setspecific(keyThreadContext, mainThreadContext);
      mainThreadContext->handleThread = pthread_self();
      /* create an event for this thread (for use in eventFlag functions) */
      //automatically resets the event state to nonsignaled after a single waiting thread has been released.
      mainThreadContext->uFlagRegister = 0;
      bLibIsInitialized = true;
    }
    else
    { ERROR_SYSTEM_emC(1, "too many threads", 0, 0);
    }
  }
}








MT_os_Error* users_os_Error = null;

int os_setErrorRoutine(MT_os_Error routine)
{
  users_os_Error = routine;
  return 0;
}



void os_NotifyError(int errorCode, const char* description, int value1, int value2)
{ if(users_os_Error != null)
  { //call the users routine:
    users_os_Error(errorCode, description, value1, value2);
  }
  else
  { //If no user routine is known, the error should be detect by the return code of the os-routines.
  }
}

/*
void os_Error(const char* text, int value)
{ printf("\nFATAL SYSTEM ERROR %s: %i=%8.8X\nTHREAD STOPPED\n", text, value, value);
  *(int*)0 = 0;
}
*/
void os_userError(const char* text, int value)
{ printf("\nUSER SYSTEM ERROR %s: %i=%8.8X\nTHREAD STOPPED\n", text, value, value);
}

#define NOT_TlsGetValue
#ifdef NOT_TlsGetValue
//#error
  #include <emC/OSAL/os_ThreadContextInTable.ci>
  //#define setCurrent_OS_ThreadContext(context) (0 == os_setThreadContextInTable((int)pthread_self(), context))
  //#define getCurrent_OS_ThreadContext() os_getThreadContextInTable((int)pthread_self())
#elif defined(TEST_ThreadContext_IMMEDIATE)
  //this TEST case is only possible if only one thread is used. Only for timing testing.
  OS_ThreadContext* current_OS_ThreadContext = null;
  #define setCurrent_OS_ThreadContext(context) (current_OS_ThreadContext = context)
  #define getCurrent_OS_ThreadContext() current_OS_ThreadContext
#else
//#error
  #define setCurrent_OS_ThreadContext(context) TlsSetValue(dwTlsIndex, context)
  #define getCurrent_OS_ThreadContext() (OS_ThreadContext*)TlsGetValue(dwTlsIndex)
#endif


//invokes init_OSAL() on first call.
OS_ThreadContext* getCurrent_OS_ThreadContext(){                          //getCurrent_OS_ThreadContext(...)
  if(keyThreadContext ==null){
    init_OSAL();
  }
  OS_ThreadContext* threadContext = (OS_ThreadContext*) pthread_getspecific(keyThreadContext);
  if(threadContext == null) { //it should be not null if init_OSAL() is
    ERROR_SYSTEM_emC(-1, "os_getCurrentThreadContext() - no ThreadContext found, error creating ThreadContext. ", 0, 0);
  }
  return threadContext;
}




// Wrapper thread function for thread creation and parameter initialization
void* os_wrapperFunction(void* data)
{

  OS_ThreadContext* threadContext = (OS_ThreadContext*) data;
  pthread_t h2 = pthread_self();                                     // check whether this thread has the same handle as stored in threadContext!
  if(! pthread_equal(threadContext->handleThread, h2)){   // should be same
    ERROR_SYSTEM_emC(0, "pthread_self fails", 0,0);
  } else {
    h2 = 0;
  }

  if(threadContext->sSignificanceText != sSignificanceText_OS_ThreadContext)
  { ERROR_SYSTEM_emC(-1, "FATAL: threadContext incorrect: %p\n", (int)(intPTR)threadContext, 0);
  }
  else {
    pthread_setspecific(keyThreadContext, threadContext);
    //complete threadContext
    void* topStackAddr = &threadContext;  //The first variable in stack, cast to pointer forces a real stack location.
    ctor_ThreadContext_emC(&threadContext->userThreadContext, topStackAddr);
    threadContext->uFlagRegister = 0;

    {
       /* create an event for this thread (for use in eventFlag functions) */
       //automatically resets the event state to nonsignaled after a single waiting thread has been released.
       //threadContext->EvHandle = CreateEvent( NULL, FALSE, FALSE, NULL);
       //if (threadContext->EvHandle == NULL)
      {
         //printf("os_createThread: ERROR: Failed to create Event for thread:0x%x\n", (uint)threadContext->uTID);
      }
    }
    // execute user routine
    OS_ThreadRoutine* threadRoutine = threadContext->ThreadRoutine;
    MAYBE_UNUSED_emC int exit = threadRoutine(threadContext->pUserData); //&threadContext->stacktraceThreadContext);    // execute user routine

    //If the thread routine is finished, the thread will be removed.
    //Hence free the threadContext. Nobody outside should use it!
    //The return value is also unused. The thread should say all internally.
    free(threadContext);
  }
  return null;
}




int os_createThread
( HandleThread_OSemC* pHandle,
  OS_ThreadRoutine routine, 
  void* pUserData, 
  char const* sThreadName, 
  int abstractPrio, 
  int stackSize )
{
  //int iWinRet = 0;
  pthread_t threadId;
  //HANDLE hDupChildHandle;
  int ret_ok;
  //int idxThreadPool = 0;
  OS_ThreadContext* threadContext = null;
  //WraperParamStruct ThreadWraperStr;
  
  //HANDLE threadHandle;
    
  if (!bLibIsInitialized)
  { init_OSAL();
      //printf("/nos_createThread: init_OSAL() has to be called first in order to use Windows-Threads!");
      //return OS_SYSTEM_ERROR;
  }
  if (stackSize == 0 || stackSize == -1)
  {
    stackSize = OS_DEFAULT_STACK;
  }

  if(abstractPrio <= 0 || abstractPrio > 255)
  {
    abstractPrio = 128;
  }

  threadContext = new_OS_ThreadContext(sThreadName);
  if(threadContext != null)
  { threadContext->ThreadRoutine = routine;  // user routine
    threadContext->pUserData = pUserData;    // user data
    threadContext->sSignificanceText = sSignificanceText_OS_ThreadContext;
    // use immediately the handleThread, the thread starts immediately.
    ret_ok = pthread_create(&threadContext->handleThread, null, os_wrapperFunction, threadContext);
    /*
    threadHandle = CreateThread(
                            NULL,
                            stackSize,
                            (LPTHREAD_START_ROUTINE)(os_wrapperFunction),
                            (void*)threadContext,
                            CREATE_SUSPENDED,      //wait because some values should be initialized
                            &uThreadID);       
    */

    threadContext->uTID = null; //TODO
    threadId = threadContext->handleThread;

    // set the thread prio
    { long uWinPrio = os_getRealThreadPriority( abstractPrio );
      //printf("DEBUG: os_createThread: abstrPrio=%d, WinPrio=%d\n", abstactPrio, uWinPrio);
        ret_ok = pthread_setschedprio(threadId, uWinPrio);

      //ResumeThread(threadHandle);        // start thread
    }
    *pHandle = (HandleThread_OSemC)threadContext->handleThread;  // return the pseudo handle
    return OS_OK;
  }
  else 
  { //no space in threadpool, no threadContext
    
    return OS_SYSTEM_ERROR;
  }

}


int os_getRealThreadPriority(int abstractPrio)
{
  long priority = 0;

  static int const delta = 63;
  if (abstractPrio <= 127 - delta){
    //priority = THREAD_PRIORITY_BELOW_NORMAL;
  }
  else if (abstractPrio >= 127 + delta){
    //priority = THREAD_PRIORITY_ABOVE_NORMAL;
  }
  else{
    //priority = THREAD_PRIORITY_NORMAL;
  }
  return priority;
}




int os_setThreadPriority(HandleThread_OSemC handle, uint abstractPrio)
{   
  //int ret_ok = 0;
  return OS_OK;
}

//see also https://stackoverflow.com/questions/43471743/pthread-self-on-linux
//https://man7.org/linux/man-pages/man3/pthread_self.3.html
// returns the thread_id, which is also stored in the OS_ThreadContext
HandleThread_OSemC os_getCurrentThreadHandle ( void ){
  pthread_t h = pthread_self();
  return (HandleThread_OSemC) h;   // present it outside to a specific pointer type, OS-independent.
}


ThreadContext_emC_s* getCurrent_ThreadContext_emC  ()
{
  OS_ThreadContext* os_threadContext = getCurrent_OS_ThreadContext();
  if(os_threadContext->sSignificanceText != sSignificanceText_OS_ThreadContext) {
    ERROR_SYSTEM_emC(-1, "OS_ThreadContext faulty", 0,0);
  }
  ThreadContext_emC_s* thCxt = &os_threadContext->userThreadContext;
  return thCxt;
}



char const* os_getTextOfOsError(int nError)
{
  switch (nError){
  case OS_SYSTEM_ERROR:        return "System Fehler.";
/*
  case OS_INVALID_PARAMETER:   return "in Parameter war ung�ltig.";
  case OS_INVALID_STRING:      return  "Ein String ist nicht innerhalb der vorgegebenen Gr��e.";
  case OS_INVALID_HANDLE:      return "Das Objekt-Handle ist ung�ltig.";
  case OS_INVALID_STATE:       return "Der Objekt-Sustand ist ung�ltig f�r diese Operation.";
  case OS_TEST_NOT_OK:         return "Testbedingungen nicht erf�llt.";
  case OS_GOT_TIMEOUT:         return "Der Aufruf wurde nach dem eingestellten Timeout abgebrochen.";
  case OS_QUEUE_EXIST:         return "Die Message-Queue existiert bereits f�r diesen Thread.";
  case OS_QUEUE_NOT_EXIST:     return "Die Message-Queue dieses Thread existiert nicht.";
  case OS_RESOURCE_BUSY:       return "In diesem Objekt stehen noch Nachrichten, oder ein Thread wartet.";
  case OS_QUEUE_FULL:          return "Die Message�Queue ist voll.";
  case OS_QUEUE_EMPTY:         return "Die Message-Queue enth�lt keine Nachricht.";
  case OS_NAME_EXIST:          return "Der Name existiert bereits.";
  case OS_NAME_NOT_EXIST:      return "Der angegebene Name existiert im System nicht.";
  case OS_MAILBOX_FULL:        return "Die Anforderung �berschreitet die eingetragene Grenze der Mailbox.";
  case OS_MAILBOX_EMPTY:       return "Die Mailbox enth�lt keine Nachricht (wenn timeOut = 0).";
  case OS_INVALID_POINTER:     return "Zeiger zu Resource ung�ltig.";
  case OS_UNKNOWN_ERROR:       return "Undefinierte Fehlermeldung.";
*/
  default:                     return "Unknown error-code.";
  }
}

