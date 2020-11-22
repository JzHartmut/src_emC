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
* @content Definition of Thread Context structures for all variants. 
*
* @author Hartmut Schorrig
* @version 2.0
* 2020-05-16: Hartmut creation 
*
************************************************************************************************/
#ifndef HGUARD_emC_Base_ExcThreadCxt
#define HGUARD_emC_Base_ExcThreadCxt

#ifndef HGUARD_applstdef_emC
  #include <applstdef_emC.h>
#endif


#ifndef DEF_ThreadContext_SIMPLE
  #include <emC/Base/MemC_emC.h>
  #include <emC/Base/SimpleC_emC.h>
#endif

/*========== structures only for not SIMPLE thread context =============================================*/
#ifndef DEF_ThreadContext_SIMPLE   //only defined for full ThreadContext


#define DEF_ThreadContextHeap_emC

typedef struct AddrUsed_ThreadContext_emC_t
{ char const* sign;
  MemC used;
} AddrUsed_ThreadContext_emC;




typedef struct UserBufferInThCxt_T {
/**A memory area referenced in the thread context. This area is either initially created or created on demand
* with a default size. It can be used especially for String values or other instances
* which are used only in the tread, returned by reference and immediately used and freed.
*/
MemC bufferAlloc;
//TODO this define in applstdef_emC.h
#define DEF_UserBuffer_ThreadContext_emC

/**Up to 30 used addresses for allocated buffers in thread context.
* The positions in this array refers to the bits from 0...9 in [[ThreadContext_emC_s.bitAddrUsed]].
* If the bit is set, this is the associated memory location for a allocated buffer.
* If the bit is 0 but higher bits are set, this is the gap in the buffer for a freed block. 
* That block is reused if an [[ThreadContext_emC_s.getUserBuffer_ThreadContext_emC(...)]] is called with exactly the same size.
* That is usual if more as one time a block is allocated and freed in a loop.
* If the element contains {0,0} than it is not a gap, and the whole memory till end of [[ThreadContext_emC_s.bufferAlloc]] is available. 
*/
AddrUsed_ThreadContext_emC addrUsed[30];

/**If the bit from 0..29 is set, the address is in use. 0: freed. */
int32 bitAddrUsed;

/**The free address of [[ThreadContext_emC_s.bufferAlloc]]. It is equal the start address if all is free.*/
MemUnit* addrFree;

int16 ixLastAddrUsed;

int16 mode;

#define mOptimizeToString_Mode_ThCxt 0x0001

#define mBufferUsed_Mode_ThCxt 0x0002

#define mCheckBufferUsed_Mode_ThCxt 0x0004

} UserBufferInThCxt_s;



#ifndef DEF_ThreadContext_STACKTRC
  #define DEF_ThreadContext_STACKTRC
#endif

/*@CLASS_C StacktraceElement_emC_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**An element of the stacktrace, 12 Byte for a 32-bit-System, 
 * 6 byte for a 16-bit-system, if char const* references are short. */
typedef struct StacktraceElement_emC_T
{
  const char* name;
  const char* source;
  int line;
} StacktraceElement_emC_s;



/*@CLASS_C StacktraceThreadContext_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**The max. number of stacktrace entries should be defined as constant. It limits the shown stacktrace depth,
* but it doesn't limit the useable stacktrace depth. It is a problem of available memory. It should be not to small.
*/
#define nrofStacktraceEntries_ThreadContexJc 100

struct StacktraceJc_t;

/**This structure is the last part of the ThreadContext and contains the necessary values for handling with Stacktrace.
 */
typedef struct StacktraceThreadContext_emC_t
{
  /**actual nrofEntries in stacktraceBuffer. */
  uint zEntries; 

  /**The available number of Stacktrace entries. */
  uint maxNrofEntriesStacktraceBuffer;

  /**This mask is used for safety operation 
   * if the indices in IxStacktrace_emC are corrupt.
   * This can occure especially in errorneous situations on software development.
   * It simply helps to prevent faulty array accesses.
   * But this mask information should be safe by itself or cyclically checkec
   */
  uint mBitEntriesStacktrc;

  /**Space for Stacktrace Buffer. Should be the last element because of enhancements*/
  StacktraceElement_emC_s entries[128]; 

} StacktraceThreadContext_emC_s;

/**Initializer.
 * @arg SIZE have to be a power of 2! 
   The really number of elements maybe with additional elements.
 */
#define INIZ_StacktraceThreadContext_emC(SIZE) { 0, SIZE, SIZE-1, {0}}



METHOD_C StacktraceThreadContext_emC_s* ctorM_StacktraceThreadContext_emC(MemC mthis);

/**Returns the method name of the requested level.
* @param level 0 is actual, 1... are previous levels.
* @return "" if no previous level is found.
*/
METHOD_C char const* getCallingMethodName_StacktraceThreadContext_emC(StacktraceThreadContext_emC_s* ythis, int level);




#endif //not DEF_ThreadContext_SIMPLE









/*========== ThreadContext_emC_s ============================================================*/

typedef struct ThreadContext_emC_t {
  #ifdef DEF_ThreadContextHeap_emC
  UserBufferInThCxt_s threadheap;
  #endif

  #ifdef USE_BlockHeap_emC
  /**It is the heap, where block heap allocations are provided in this thread. */
  struct BlockHeap_emC_T* blockHeap;
  #endif

  /**The known highest address in the stack. It is the address of the _struct ThreadContext_emC_t* pointer
  * of the first routine, which creates the Thread context.
  */
  MemUnit const* topmemAddrOfStack;

  /**This is the maximal found value of the stack size which is evaluated on [[getCurrentStackDepth_ThreadContext_emC(...)]] . */
  int stacksizeMax;

  /**Number of and index to the current exception instance*/
  int zException, ixException;
  //
  /**Up to NROF_ExceptionObjects (default 4) for nested Exception. */
  ExceptionJc exception[4];
  //
  /**Reference to the current TryObject in Stack.
  * It is possible to access in deeper stack frames.
  * This reference is removed for the outer stack frames.
  */
  TryObjectJc* tryObject;
  //


  /**Set to 0 on input of matching CATCH block to set exc.exceptionNr to 0 on END_TRY */
  //int32 excNrTestCatch;
  //int32 line;
  //char const* file;

  #ifdef DEF_ThreadContext_STACKTRC
  /**Data of the Stacktrace if this concept is used. */
  StacktraceThreadContext_emC_s stacktrc;
  /*IMPORTANT NOTE: The element stacktrc have to be the last because some additional StackEntryJc may be added on end.*/
  #endif

} ThreadContext_emC_s;

#define ThCxt ThreadContext_emC_s

/**Gets the ThreadContext of the current Thread.
 * How it is done depends deeply from the Operation system. Hence it is a function call.
 * It is possible that a simple access to a global pointer is done, possible on non-preemptive threads
 * Or simple interrupt systems. 
 */
#ifndef getCurrent_ThreadContext_emC  //NOTE: may be defined as macro via applstdef_emC.h
extern_C ThreadContext_emC_s* getCurrent_ThreadContext_emC ();
#endif


#ifdef DEF_ThreadContext_SIMPLE

/**Because the operation may use a pointer variable named _thCxt it is defined here.
* But it is initialized with null, because a ThreadContext is unknown, and it is a unknown forward type.
*/
#define STACKTRC_ROOT_ENTRY(NAME) struct ThreadContext_emC_t* _thCxt = getCurrent_ThreadContext_emC(); _thCxt->topmemAddrOfStack = (MemUnit*)&_thCxt 

#define STACKTRC_ROOT_TENTRY(NAME) _thCxt->topmemAddrOfStack = (MemUnit*)&_thCxt

/**For that the _thCxt variable is given in arguments of the operation */
#define STACKTRC_TENTRY(NAME)

/**Because the operation may use a pointer variable named _thCxt it is defined here.
* But it is initialized with null, because a ThreadContext is unknown, and it is a unknown forward type.
*/
#define STACKTRC_ENTRY(NAME) \
  MAYBE_UNUSED_emC struct ThreadContext_emC_t* _thCxt = getCurrent_ThreadContext_emC(); /*It is a variable in Stack. */\
  int stacksize = (int)(((MemUnit*)&_thCxt) - _thCxt->topmemAddrOfStack); \
  if(stacksize <0) { stacksize = -stacksize; } \
  if(stacksize > _thCxt->stacksizeMax) { _thCxt->stacksizeMax = stacksize; } \



#else  //not DEF_ThreadContext_SIMPLE

/**It should be the first invocation of STACKTRC_ENTRY in main or in a thread routine. 
* For this environment it does the same as STACKTRC_ENTRY(NAME). 
*/
#define STACKTRC_ROOT_ENTRY(NAME) STACKTRC_ENTRY(NAME); _thCxt->topmemAddrOfStack = (MemUnit*)&_thCxt


/**This macro defines and initializes the stack variables ,,_ixStacktrace_,,.
* Use the macro ,,STACKTRC_LEAVE;,, at end of the block unconditionally!
* After the macro in the users call a semicolon should be written.
* NOTE: The initialization with __FILE__ and __LINE__ must be a part of macro
* because otherwise it is the fault file and line.
*/
#define STACKTRC_TENTRY(NAME) \
  IxStacktrace_emC _ixStacktrace_; \
  if(_thCxt==null){ _thCxt = getCurrent_ThreadContext_emC(); } \
  _ixStacktrace_.ixStacktracePrev = _thCxt->stacktrc.zEntries; \
  if(_thCxt->stacktrc.zEntries < (ARRAYLEN_SimpleC(_thCxt->stacktrc.entries))) { \
    StacktraceElement_emC_s* stdst; \
    _ixStacktrace_.ixStacktrace = _thCxt->stacktrc.zEntries; \
    _thCxt->stacktrc.zEntries+=1; \
    stdst = &_thCxt->stacktrc.entries[_ixStacktrace_.ixStacktrace]; \
    stdst->name = NAME; stdst->source = __FILE__; stdst->line = __LINE__;  \
  } else { /**do nothing special in this error case. */ \
    /**But do not create the index in thread context. */ \
    _ixStacktrace_.ixStacktrace = _ixStacktrace_.ixStacktracePrev; \
  } 

/**Use the macro ,,STACKTRC_LEAVE;,, at end of the block unconditionally!*/
#define STACKTRC_ENTRY(NAME) ThCxt* _thCxt = getCurrent_ThreadContext_emC();  STACKTRC_TENTRY(NAME)

#endif


#ifdef DEF_ThreadContext_SIMPLE

#define STACKTRC_LEAVE

#define THCXT _thCxt

#define CALLINE

#else  //not DEF_ThreadContext_SIMPLE

/**This macro corrects the chained list of stacktrace, it sets the end of the previous stacktrace.
* Use this macro unconditionally at end of a block using ,,STACKTRC_ENTRY(),, or ,,STACKTRC_XENTRY(),,.
* Otherwise the chain of stacktrace elements is corrupted.
*/
#define STACKTRC_LEAVE _thCxt->stacktrc.zEntries = _ixStacktrace_.ixStacktracePrev

/**This macro supplies the ,,_thCxt,,-Variable but stores the __LINE__ before.
* A forgotten ,,STACKTRC_LEAVE,, in a last subroutine will be repaire yet also.
*/
#define THCXT (_thCxt->stacktrc.entries[_ixStacktrace_.ixStacktrace].line=__LINE__, _thCxt->stacktrc.zEntries = _ixStacktrace_.ixStacktrace +1, _thCxt)

//#define CALLINE(stacktrace.entry.line=__LINE__)
#define CALLINE (_thCxt->stacktrc.entries[_ixStacktrace_.ixStacktrace].line=__LINE__)

#endif  //not DEF_ThreadContext_SIMPLE








#define ADDR_IN_STACK_ThreadContext_emC(ptr) ((MemUnit const*)ptr > (MemUnit const*)&ptr && (MemUnit const*)ptr < _thCxt->topmemAddrOfStack)








#ifndef DEF_ThreadContext_SIMPLE

/**Test the consistence of the stacktrace, useable if errors are searched
* The compiler switch should be set in the ,,fw_Platform_conventions.h,,
*/
#ifdef TEST_STACKTRCJc
METHOD_C bool test_StacktraceJc ( IxStacktrace_emC* ythis);
#else
/**Let it empty. */
#define test_StacktraceJc(ST)

#endif

#endif  //not DEF_ThreadContext_SIMPLE











/*===== Operations for User Buffer ThreadContext ==============================================*/
#ifdef DEF_ThreadContextHeap_emC
//only available on not simple ThreadContext, elsewhere linker error. 
//You cannot use things which are not defined. 

/**Sets a buffer in ThreadContext.
* The buffer may be necessary and filled in inner routines.
* @return the existing buffer. If an existing buffer is to be kept, 
*         the content of the returned buffer should be stored in stack and restore
*         before the calling routine returns. 
*/
METHOD_C MemC setUserBuffer_ThreadContext_emC ( MemC newBuffer, struct ThreadContext_emC_t* _thCxt);

/**Gets a buffer in ThreadContext. 
* This is a special simple way to handle with memory, if no everlastingly allocation is admissible,
* but a buffer should filled and returned inside called routines. 
* It is possible to allocate a buffer more as one time but at maximum 10 buffers are possible.
* That is enough to build string etc. for logging messages, paths etc.
* A buffer can be allocate, freed with [[ThreadContext_emC_s.releaseUserBuffer_ThreadContext_emC(...)]] and allocate with the same size again.
* Then the same position is reused. 
*
* The algorithm used the fields [[ThreadContext_emC_s.addrUsed]] etc.
*
* The buffer may be given by [[ThreadContext_emC_s.setUserBuffer_ThreadContext_emC(...)]] or it is allocated on demand on first usage.
* Because the buffer is stored not globally but thread specific this mechanism is threadsafe, .
* @param size in MemUnit
* @param sign a number to support debugging which part of code has allocated, use a unified number if possible.
* @return null_MemC with length=0 if no buffer is free. The application should deal with this situation.
* NOTE: An exception is not thrown because this is an expectable result. Especially if this routine is used inside an exception handling
*   a simple exception exacerbate the situation.
*/ 
METHOD_C MemC getUserBuffer_ThreadContext_emC ( int size, char const* sign, struct ThreadContext_emC_t* _thCxt);

/**Reduces the size of the last gotten buffer in thread context.
* This routine shall be called immediately after filling the current one buffer, before another buffer is gotten.
* This routine is called in toStringNonPersist_StringBuilderJc(). It is success if it is the last gotten buffer.
* If ptr does not refer the last gotten buffer this routine does nothing.
* Especially if a string is prepared, its length is only given after preparation. Then it is time to set to used size.
* @param ptr To check wheterh it is the last gotten buffer.
* @param size the used size. The rest till the end of the Thread contect buffer area is now free for further buffer. 
*/
METHOD_C void reduceLastUserBuffer_ThreadContext_emC ( void* ptr, int size, struct ThreadContext_emC_t* _thCxt);


/**Sets the mode whether the release of the buffer in ThreadContext is necessary. 
*/ 
METHOD_C bool setCheckingUserBuffer_ThreadContext_emC ( struct ThreadContext_emC_t* _thCxt, bool value);


/**Releases the buffer in ThreadContext. 
*/ 
METHOD_C bool releaseUserBuffer_ThreadContext_emC ( void const* data, struct ThreadContext_emC_t* _thCxt);




/**Allocates an ObjectJc in the thread buffer. Such an instance must be used immediately, then it is similar to an embedded instance in the stack. 
* It can be returned and used in the calling enviroment immediately or return. That is the difference to a embedded instance in the stack.
* Only one instance can be located in the thread context. It is over-written if another instance is created in the thread context.
*/
struct ObjectJc_T* allocInThreadCxt_ObjectJc ( int size, char const* sign, struct ThreadContext_emC_t* _thCxt);




#endif

#endif //HGUARD_emC_Base_ExcThreadCxt
