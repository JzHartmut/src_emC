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
 * 2008-10-00: Hartmut creation
 * 2009-10-20: Hartmut: *new: element mode, used for bit mOptimizeToString_Mode_ThCxt. This property should be able to set in a thread context, used in StringJc.h
 *
 ****************************************************************************/
#ifndef __fw_ThreadContext_h__
#define __fw_ThreadContext_h__

#include <Fwc/fw_MemC.h>

#ifndef __fw_Exception_h__
  #include "fw_Exception.h"
#endif

/*@CLASS_C ThreadContextFW @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct ThreadContextFW_t
{ 
  MemC bufferInThreadContext;

  
  /**It is the heap, where allocations are provided in this thread. */
  struct BlockHeapJc_t* blockHeap;

  int32 mode;

  #define mOptimizeToString_Mode_ThCxt 0x00000001
  
  #define mBufferUsed_Mode_ThCxt 0x00000002
  
  #define mCheckBufferUsed_Mode_ThCxt 0x00000004
  
  /**The known highest address in the stack. It is the address of the _ThCxt* pointer
   * of the first routine, which creates the Thread context.
   */
  void* topmemAddrOfStack;
  
  StacktraceThreadContext_s stacktraceThreadContext;
  /*NOTE: The element stacktraceThreadContext have to be the last because some additional StackEntryJc may be added on end.*/

} ThreadContextFW_s;

/**initializes the ThreadContextFW. */
METHOD_C ThreadContextFW_s* ctorM_ThreadContextFW(MemC mthis);



/**gets the ThreadContext of the current Thread.
 * @return The pointer and size of the thread context without type information.
 *         The user is responsible for test of size and type conversion.
 *         Normally the given size setted with os_setThreadContextSettings should be returned.
 *         If the os_setThreadContextSettings-routine is not called before, the routine returns {0, null}.
 */
METHOD_C ThreadContextFW_s* getCurrent_ThreadContextFW(); 

/**Sets a buffer in ThreadContext.
 * The buffer may be necessary and filled in inner routines.
 * @return the existing buffer. If an existing buffer is to be kept, 
 *         the content of the returned buffer should be stored in stack and restore
 *         before the calling routine returns. 
 */
METHOD_C MemC setUserBuffer_ThreadContextFw(MemC newBuffer, ThCxt* _thCxt);

/**Gets a buffer in ThreadContext. 
 * This is a special simple way to handle with memory, if no everlastingly allocation is admissible,
 * but a buffer should filled and returned inside called routines. 
 * The buffer may be given outside such routines using setUserBuffer_ThreadContextFw().
 * This mechanism should be threadsafe, therefor the buffer is stored not globally but thread specific.
 * The user is responsible for handling the buffers in its thread. 
 */ 
METHOD_C MemC getUserBuffer_ThreadContextFw(ThCxt* _thCxt);


/**Sets the mode whether the release of the buffer in ThreadContext is necessary. 
 */ 
METHOD_C bool setCheckingUserBuffer_ThreadContextFw(ThCxt* _thCxt, bool value);


/**Releases the buffer in ThreadContext. 
 */ 
METHOD_C bool releaseUserBuffer_ThreadContextFw(ThCxt* _thCxt);






METHOD_C bool xxxoptimizeString_ThCxt(ThCxt* ythis, bool value);

METHOD_C bool xxxisOptimizeString_ThCxt(ThCxt* ythis);


#endif //__fw_ThreadContext_h__
