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
 * @content some methods to implement ThreadJc.
 *
 * @author Hartmut Schorrig
 * @version 0.91
 * list of changes:
 * 2009-10-08: Hartmut creation from older source
 *
 ****************************************************************************/
#ifndef __ThreadJc_h__
#define __ThreadJc_h__


#include "StringJc.h"
#include "ReflectionJc.h"
#include <os_thread.h>



/*@CLASS_C RunnableJc @@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct represents an interface adequat to ,,java.lang.Runnable,,. 
 * It contains only a struct ObjectJc, it is to use in a ,,union{...},, commonly with the ,,ObjectJc,,-base of any struct.
 */
typedef struct RunnableJc_t
{ 
  union { ObjectJc object; } base; 
} RunnableJc_s;
  
/* Enhanced references *********************************************************/
#ifndef RunnableJcREFDEF
  #define RunnableJcREFDEF
  DEFINE_EnhancedRefJc(RunnableJc);
  //Should be compatible with non-enhanced ref using. typedef struct RunnableJcREF_t { ObjectRefValuesJc refbase; struct RunnableJc_t* ref; } RunnableJcREF;
#endif
#if !defined(mBackRef_ObjectJc) 
  //if enhanced references are used, the REF types have own reflection const.
  //in this case they are dummies.
  #define reflection_RunnableJcREF reflection_RunnableJc_s
#endif



/**Define of the array type. This type should only be used as pointer. */
typedef struct RunnableJc_Y_t { ObjectArrayJc head; RunnableJc_s data[50]; } RunnableJc_Y;

extern struct ClassJc_t const reflection_RunnableJc_s;

/**The method type, which is able to implement the run method. */
typedef void MT_run_RunnableJc(ObjectJc* ithis, ThCxt* _thCxt);
/** Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void run_RunnableJc(ObjectJc* ithis, ThCxt* _thCxt);

/* Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
extern const char sign_Mtbl_RunnableJc[]; //marker for methodTable check
typedef struct Mtbl_RunnableJc_t
{ MtblHeadJc head;
  MT_run_RunnableJc* run;
  Mtbl_ObjectJc ObjectJc;
} Mtbl_RunnableJc;


/*@CLASS_C ThreadJc @@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct represents a class adequate to ,,java.lang.Thread,,. 
 */
typedef struct ThreadJc_t
{

  union { ObjectJc object; RunnableJc_s RunnableJc;} base; 

  /**Ident of the thread, to check the correctnis (debugmodi).*/
  OS_HandleThread hThread;

  /**Name of the thread. */
  StringJc name;

  /**The pointer to the associated Runnable Object, contains the run()-method.
   * This pointer will be set only in the constructor, if an associated Runnable-object is given.
   * The pointer may be null, if the run-method of this class is overridden.
   */
  RunnableJcREF target;

  /**The given stackSize. */
  int32 stackSize;

  /**State of the thread. */
  int32 state;  //use enum EState_Thread;

  /**The priority of thread is able to adjust. */
  int32 nPriority;

  /** pointer to the Stack with name of the actual called method saved on Thread switch
   */
  const char** sCalledName;


  #define MIN_PRIORITY_ThreadJc 1
  #define NORM_PRIORITY_ThreadJc 0x80
  #define MAX_PRIORITY_ThreadJc 0xfe

}ThreadJc_s;


#define sizeof_ThreadJc_s sizeof(ThreadJc_s)

typedef struct ThreadJc_s_Y_t { ObjectArrayJc head; ThreadJc_s data[50]; } ThreadJc_s_Y;

extern struct ClassJc_t const reflection_ThreadJc_s;
  




#define CONST_Runnable_ThreadJc(RUNNABLE) {CONST_ObjectJc(), "", 0, RUNNABLE, 2000, 5}

/** Constant in form {...} defines a Thread with associated Runnable class*/
#define CONST_Runnable_z_ThreadJc(RUNNABLE, NAME) {CONST_Object_Jc(0, null, (Class_Jc const*)(&reflection__ThreadJc)), NAME, 0, RUNNABLE, 2000, 5}

/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_ThreadJc_F(ObjectJc* othis, ThCxt* _thCxt);



#define ctorO_ThreadJc(OTHIS, THCXT) ctorO_Runnable_s_ThreadJc(OTHIS, null, null_StringJc, THCXT);

#define ctorO_z_ThreadJc(OTHIS, NAME, THCXT) ctorO_Runnable_s_ThreadJc(OTHIS, null, s0_StringJc(NAME), THCXT)

#define ctorO_s_ThreadJc(OTHIS, NAME, THCXT) ctorO_Runnable_s_ThreadJc(OTHIS, null, NAME, THCXT)

#define ctorO_Runnable_z_ThreadJc(OTHIS, RUN, NAME, THCXT) ctorO_Runnable_s_ThreadJc(OTHIS, RUN, s0_StringJc(NAME), THCXT)

METHOD_C ThreadJc_s* ctorO_Runnable_s_ThreadJc(ObjectJc* othis, RunnableJc_s* pRunnable,  StringJc pName, ThCxt* _thCxt);



METHOD_C void setPriority_ThreadJc(ThreadJc_s* ythis, int newPriority);

METHOD_C int getPriority_ThreadJc(ThreadJc_s* ythis);


METHOD_C void start_ThreadJc(ThreadJc_s* ythis, int stackSize, ThCxt* _thCxt);

/** The original virtual method run of class Thread, used for an immediate non-dynamic call.
*/
METHOD_C void run_Thread_F(ObjectJc* ithis, ThCxt* _thCxt);

/** The call of run, executes a dynamic call of the override-able method.
*/
METHOD_C void run_ThreadJc(ObjectJc* ithis, ThCxt* _thCxt);


/**
 * Tests if this thread is alive. A thread is alive if it has
 * been started and has not yet died.
 *
 * @return  <code>true</code> if this thread is alive;
 *          <code>false</code> otherwise.
 */
METHOD_C bool isAlive_ThreadJc(ThreadJc_s*);


METHOD_C void finalize_ThreadJc(ThreadJc_s*);


METHOD_C void sleep_ThreadJc(int32 milliseconds, ThCxt* _thCxt);


/** javalike:*/
METHOD_C ThreadJc_s* currentThread_ThreadJc();

/* Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
extern const char sign_Mtbl_ThreadJc[]; //marker for methodTable check
typedef struct Mtbl_ThreadJc_t
{ MtblHeadJc head;
  Mtbl_ObjectJc ObjectJc;
  //Method table of interfaces:
  Mtbl_RunnableJc RunnableJc;  
} Mtbl_ThreadJc;


/** private states of the thread.
    The order must considere the realisation of isAlive
*/
typedef enum EState_ThreadJc_t
{ kUnknownState_ThreadJc = 0
, kCreatedState_ThreadJc = 1
, kStartedState_ThreadJc = 2
, kRunningState_ThreadJc = 3
, kWaitingState_ThreadJc = 5
, kFinishedState_ThreadJc = 9
}EState_ThreadJc;


#endif  //__ThreadJc_h__
