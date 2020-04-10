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
 * @content some methods to access threadContext from user level.
 *
 * @author Hartmut Schorrig
 * @version 0.91
 * list of changes:
 * 2016-11-12: Hartmut: The CLASS_C [[class_StacktraceElementJc]] and [[class_StacktraceThreadContext_emC]] are now defined in this file.
 *   Therewith the include of fw_exception.h is unneccessary. The dependence is solved. Note that the both definitions are independent
 *   of the core ideas of the exception handling in C. They define only a set of name, filepath and a line number. 
 * 2009-10-20: Hartmut: *new: element mode, used for bit mOptimizeToString_Mode_ThCxt. This property should be able to set in a thread context, used in StringJc.h
 * 2008-10-00: Hartmut creation
 *
 ****************************************************************************/
#ifndef __applstdef_emC_h__
  /**This file fw_ThreadContext.h or fw_Exception.h should be included in the applstdef_emC.h. 
   * If this file is directly included, it needs the applstdef_emC.h. But the __fw_ThreadContext_h__ guard should not be set firstly
   * to include the fw_ThreadContext.h in the given order in applstddef.h
   */
  #include <applstdef_emC.h>
#endif
#ifndef __emC_ThreadContext_emC_h__
#define __emC_ThreadContext_emC_h__

#include <emC/Base/MemC_emC.h>
struct TryObjectJc_t;

#define __ThreadContext_emC_supported__

#define DEF_ThreadContextStracktrc_emC

typedef struct AddrUsed_ThreadContext_emC_t
{ char const* sign;
  MemC used;
} AddrUsed_ThreadContext_emC;


/*@CLASS_C StacktraceElementJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
typedef struct StacktraceElementJc_t
{
  const char* name;
  const char* source;
  int line;
  struct TryObjectJc_t* tryObject;
}StacktraceElementJc;



/*@CLASS_C StacktraceThreadContext_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**The max. number of stacktrace entries should be defined as constant. It limits the shown stacktrace depth,
 * but it doesn't limit the useable stacktrace depth. It is a problem of available memory. It should be not to small.
 */
#define nrofStacktraceEntries_ThreadContexJc 100

struct StacktraceJc_t;

/**This structure is a part of the ThreadContext and contains the necessary values for handling with Stacktrace.
 * A reference to this structure should be known in every routine to handle with Stacktrace.
 * The reference may be the last argument of call of any routine.
 */
typedef struct StacktraceThreadContext_emC_t
{
  /**Pointer to the actual stacktrace entry.
   * This pointer is used and setted in any routine using the macro STACKthread_ENTRY and STACKthread_LEAVE.
   */
  //struct StacktraceJc_t* stacktrace;

  /**Pointer to the whole ThreadContext. */
  //struct ThreadContext_emC_t* threadContext;

  /**actual nrofEntries i stacktraceBuffer. */
  uint zEntries; //nrofEntriesStacktraceBuffer;

  /**The available number of Stacktrace entries. */
  uint maxNrofEntriesStacktraceBuffer;
  
  /**Space for Stacktrace Buffer. */
  StacktraceElementJc entries[100]; //CHeader.zbnf??? nrofStacktraceEntries_ThreadContexJc];
  //struct StacktraceElementJcARRAY_t* stacktraceBuffer;

  
} StacktraceThreadContext_emC_s;


METHOD_C StacktraceThreadContext_emC_s* ctorM_StacktraceThreadContext_emC(MemC mthis);

/**Returns the method name of the requested level.
 * @param level 0 is actual, 1... are previous levels.
 * @return "" if no previous level is found.
 */
METHOD_C char const* getCallingMethodName_StacktraceThreadContext_emC(StacktraceThreadContext_emC_s* ythis, int level);


/*@CLASS_C ThreadContext_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct ThreadContext_emC_t
{ 
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
  
  #ifdef SIZEBLOCK_BlockHeap_emC
    /**It is the heap, where block heap allocations are provided in this thread. */
    struct BlockHeap_emC_t* blockHeap;
  #endif
  
  /**The known highest address in the stack. It is the address of the _struct ThreadContext_emC_t* pointer
   * of the first routine, which creates the Thread context.
   */
  MemUnit* topmemAddrOfStack;
  
  /**This is the maximal found value of the stack size which is evaluated on [[getCurrentStackDepth_ThreadContext_emC(...)]] . */
  int stacksizeMax;



  /**Data of the Stacktrace if this concept is used. */
  StacktraceThreadContext_emC_s stacktrc;
  /*NOTE: The element stacktrc have to be the last because some additional StackEntryJc may be added on end.*/

} ThreadContext_emC_s;



/**Its a short form of ThreadContext_emC-pointer. */
#define ThCxt struct ThreadContext_emC_t


/**initializes the ThreadContext_emC. */
METHOD_C ThreadContext_emC_s* ctorM_ThreadContext_emC(MemC mthis);



/**gets the ThreadContext of the current Thread.
 * @return The pointer and size of the thread context without type information.
 *         The user is responsible for test of size and type conversion.
 *         Normally the given size setted with os_setThreadContextSettings should be returned.
 *         If the os_setThreadContextSettings-routine is not called before, the routine returns {0, null}.
 */
METHOD_C ThreadContext_emC_s* getCurrent_ThreadContext_emC(); 

/**Sets a buffer in ThreadContext.
 * The buffer may be necessary and filled in inner routines.
 * @return the existing buffer. If an existing buffer is to be kept, 
 *         the content of the returned buffer should be stored in stack and restore
 *         before the calling routine returns. 
 */
METHOD_C MemC setUserBuffer_ThreadContext_emC(MemC newBuffer, struct ThreadContext_emC_t* _thCxt);

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
 */ 
METHOD_C MemC getUserBuffer_ThreadContext_emC(int size, char const* sign, struct ThreadContext_emC_t* _thCxt);

/**Reduces the size of the last gotten buffer in thread context.
 * This routine shall be called immediately after filling the current one buffer, before another buffer is gotten.
 * This routine is called in toStringNonPersist_StringBuilderJc(). It is success if it is the last gotten buffer.
 * If ptr does not refer the last gotten buffer this routine does nothing.
 * Especially if a string is prepared, its length is only given after preparation. Then it is time to set to used size.
 * @param ptr To check wheterh it is the last gotten buffer.
 * @param size the used size. The rest till the end of the Thread contect buffer area is now free for further buffer. 
 */
METHOD_C void reduceLastUserBuffer_ThreadContext_emC(void* ptr, int size, struct ThreadContext_emC_t* _thCxt);


/**Sets the mode whether the release of the buffer in ThreadContext is necessary. 
 */ 
METHOD_C bool setCheckingUserBuffer_ThreadContext_emC(struct ThreadContext_emC_t* _thCxt, bool value);


/**Releases the buffer in ThreadContext. 
 */ 
METHOD_C bool releaseUserBuffer_ThreadContext_emC(void const* data, struct ThreadContext_emC_t* _thCxt);

#define ADDR_IN_STACK_ThreadContext_emC(ptr) ((MemUnit const*)ptr > (MemUnit const*)&ptr && (MemUnit const*)ptr < _thCxt->topmemAddrOfStack)


#endif //__emC_ThreadContext_emC_h__
