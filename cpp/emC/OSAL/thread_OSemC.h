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
 * @content Definition of Routines for thread handling in the Operation System Adaption Layer.
 * This routines are implemented in a operation system specific way. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.93
 * list of changes:
 * 2008-10: re-creation of the ThreadContext, it was present in the older sources.
 * 2008-06: Marcos Rodriguez: some improvements.
 * 2008-02-01: Hartmut creation from older sources: ThreadJc-os-adaption.
 *
 ************************************************************************************************/
#ifndef __os_thread_h__
#define __os_thread_h__

#include <applstdef_emC.h>
                             // OS-specific files must not included here!
#include <specific_OSemc.h>  //This is for OS-specific stuct definition, but commonly given elements

#ifdef __cplusplus
// extern "C" {
#endif
extern_C_BLOCK_



/**Handle to a thread. The internal data structure is not known here. 
 * A ,,HandleThread_OSemC,, may also be a simple integer, which is converted to this pointer type.
 */
#define HandleThread_OSemC struct Thread_OSemC_T*

/**The thread routine should have the followed prototype.
 * @param data Pointer to data. Mostly it is a class structure. 
 *        It is the same value given in createThread, param pUserData.
 * @return The exit value of the thread. The operation system can protocol or show the exit value in a special kind.
 */
typedef int OS_ThreadRoutine(void* data);
//int (*OS_ThreadRoutineP)(void* data);



typedef struct Thread_OSemC_T
{
  /**This is a constant text, to test whether a reference to Thread_OSemC is correct.
   * It will be initialized with pointer to "Thread_OSemC".
   */
  const char* sSignificanceText;


  /**Name of the thread.*/
  const char* name;

  //bool bInUse;                         /* structure in use */

  void* handleThread;             /* handle des Threads */

  int nThreadID;                  /* ID des threads */

  /**State of the thread: 
   * 0 = not created 
   * 1 = created in OS, not started
   * 2 = started, not running
   * 4 = running
   * 8 = finished. 
   */
  int state;
  #define mState_Thread_OSemC 0x000f
  #define mCreated_Thread_OSemC 0x0001
  #define mStarted_Thread_OSemC 0x0002
  #define mRunning_Thread_OSemC 0x0004
  #define mFinished_Thread_OSemC 0x0008


  /**The thread run routine used for start the thread. */
  OS_ThreadRoutine* ThreadRoutine;

  /**to be initial passed to the wrapper routine, thread specific user data */
  void*  pUserData;

  /**The user ThreadContext is part of the thread specific data.
   * It is defined application-specific via the included applstdef_emC.h */
  ThreadContext_emC_s userThreadContext;

}Thread_OSemC;



/**Returns the os-specific value for a thread priority.
 *
 * @param abstractPrio A value between 1 and 255. 1 is the lowest priority, 255 the highest one.
 * @return associated priority of the os.
 */
int os_getRealThreadPriority(int abstractPrio);

/**Returns the info about the main thread. */
Thread_OSemC* main_Thread_OSemC ();


/**Allocates data for a new Thread. */
Thread_OSemC* alloc_Thread_OSemC ( char const* sThreadName 
, OS_ThreadRoutine routine,  void* pUserData 
, int abstactPrio, int stackSize );

/**Creates a thread in the operation system. 
 * The thread is not started here. This is changed in 2023-01. Call start_Thread_OSemC() after creation.
 * @param thiz instance for emC-Thread data. This instance can be statically defined, or allocated.
 *   The user is responsible to management this threat data storage. 
 *   Referencing allows using non-allocation approaches. 
 * @param sThreadName A textual identification for the operation system.
 * @param routine Pointer to the thread routine, which is started.
 * @param pUserData This value will be transported to the first parameter of the user routine.
 *        Typically it are the user instance data of the thread method.
 * @param abstractPrio Priority between 1 (lowest) and 10 (highest).
 *        Note: The opeation system may assign different abstract priorities 
 *        to the same real priority. It is not guaranteed, that such threads have different priorities. 
 * @param stackSize The necessary size of stack. If 0 or -1,than the default stack size is used.
 *        The default stack size is defined in the implementation and depends of the os-possibilities.
 *        Note: Possible stack sizes depends on possibilities of the operation system.
 *        It is a good style that the stack size should be in range of 2..16 kBytes, 
 *        the user shouldn't placed large data in stack.
 *        Note, that interrupt handlers uses the stack also. 
 * @return 0 if ok, negativ value on error.
 */ 
int create_Thread_OSemC
( Thread_OSemC* thiz
, char const* sThreadName
, OS_ThreadRoutine routine
, void* pUserData
, int abstactPrio
, int stackSize
);


/**Start a thread after construction. 
 * A thread can be started only once after construction. 
 * The thread will be end if the thread routine returns.
 * If the thread has ending, restart is not possible. 
 * This is the same behavior as for java.lang.Thread.
 * A thread is either created, or running, or even finished.
 */
extern_C bool start_Thread_OSemC ( Thread_OSemC* thiz);

/**Delete or release a Thread handle. 
 * The thread should either in state not started, or finished. 
 */
extern_C bool delete_Thread_OSemC(Thread_OSemC* thiz);


/**Changes the thread priority.
*/
int os_setThreadPriority(HandleThread_OSemC handle, uint abstractPrio);

/**Returns the priority of the given thread in the operation system's kind.
 * This is to compare priorities and for showing (in debug)
 */
int os_getOsThreadPriority(HandleThread_OSemC handle);


/**NOTE: suspend and resumed must not called from another thread. Therefore this routines
 * are not defined here!!! 
 * If a thread is suspended from outside, and it is the owner of a ressource, the system may hang.
 */
//do not use: int os_suspendThread(HandleThread_OSemC handle);
//do not use: int os_resumeThread(HandleThread_OSemC handle);


/**Gets the current thread handle. This routine should have a short calculation time.
 */
//HandleThread_OSemC os_getCurrentThreadHandle(void);

/**Returns the Thread_OSemC as reference to the emC specific thread data of the current thread.
 * This reference can be used as thread identification (only compare the pointer value).
 * Internally it contains the OS-specific thread handle.
 */ 
struct Thread_OSemC_T* getCurrent_Thread_OSemC();



_END_extern_C_BLOCK

#endif //__os_thread_h__
