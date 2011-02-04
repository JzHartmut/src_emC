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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.81d
 * list of changes:
 * 2007-03-01: JcHartmut www.vishia.org creation from older source
 *
 ****************************************************************************/
#ifndef __ConcurrentRingBufferJc_h__
#define __ConcurrentRingBufferJc_h__

struct MemAreaC_t;

#include "Fwc/fw_MemC.h"
#include "Jc/ObjectJc.h"


/*@CLASS_C ConcurrentRingBufferJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct WriteArea_ConcurrentRingBufferJc_t
{ /**A start address, 0 if not set, -1 if under construction. */
  struct MemAreaC_t* volatile begin;
  
  /**The associated end address, valid if start is valid. */
  struct MemAreaC_t* volatile end;
} WriteArea_ConcurrentRingBufferJc;   


/**A ConcurrentRingBuffer is a ring bufer with thread safe access using lock-free programming with compareAndSet mechanism.
 * It is not javalike, only available in C
 */
typedef struct ConcurrentRingBufferJc_t
{
  /**Begin of the buffer.
   */
  /*private*/ /*transient*/ struct MemAreaC_t* begin;
  
  /**End exclusive of the buffer.
   */
  /*private*/ /*transient*/ struct MemAreaC_t* end;
  
  /**If lock is found setted, the written should not be adjusted. */
  int32 lock;
  /**Address from which the next read will be started. 
   * On write do not overwrite bytes after read, because there aren't read yet.
   */
  /*private*/ /*transient*/ struct MemAreaC_t* volatile read;
  
  /**Address on which the next read will be ended at last. 
   * This data are written completely.
   */
  /*private*/ /*transient*/ struct MemAreaC_t* volatile written;
  
  /**Address from which the next write will be insert data.
   * Layout if no wrapping:
   * ,,......read.......written..next....,
   * The area between written and next exists, if a write is pending.
   * If no write is pending, written == next. 
   */
  /*private*/ /*transient*/ struct MemAreaC_t* volatile next;
  
  WriteArea_ConcurrentRingBufferJc* writeAreas;
  
  int lengthWriteAreas;

  /**Only for debug: This counter will be incremented if the atomic next setting will be repeated. */
  int32 dbgcntRepeatSetNext;
  
  int32 dbgmaxRepeatSetNext;

  /**Only for debug: This counter will be incremented if the atomic written setting will be execute for an higher thread. */
  int32 dbgcntWrittenRepeat;

  int32 dbgmaxWrittenRepeat;
  
  /**Only for debug: This counter will be incremented if the atomic written setting isn't execute because it is an intterupting higher Thread. */
  int32 dbgcntWrittenNotDone;
  
  int32 dbgcntGetMonitorAfterSetNext;


}ConcurrentRingBufferJc;



ConcurrentRingBufferJc* ctor_ConcurrentRingBufferJc(MemC rawMem, MemC ringarea, MemC writeArea);

void ctorc_ConcurrentRingBufferJc(ConcurrentRingBufferJc* ythis, MemC ringarea, MemC writeArea);




/**
 * Inserts the specified element at the tail of this queue.
 *
 * @return <tt>true</tt> (as specified by {@link Collection#add})
 * @throws NullPointerException if the specified element is null
 */
bool add_ConcurrentRingBufferJcF(ConcurrentRingBufferJc* ythis, void const* data, int sizeData);

/**
 * Inserts the specified element at the tail of this queue.
 *
 * @return <tt>true</tt> (as specified by {@link Queue#offer})
 * @throws NullPointerException if the specified element is null
 */
bool offer_ConcurrentRingBufferJcF(ConcurrentRingBufferJc* ythis, void const* data, int sizeData);



/**
 * Returns <tt>true</tt> if this queue contains no elements.
 *
 * @return <tt>true</tt> if this queue contains no elements
 */
bool isEmpty_ConcurrentRingBufferJcF(ConcurrentRingBufferJc* ythis);

/**
 * returns the pointer to data inside the ringBuffer from read pointer.
 * No bytes are copied. The user have to copy itself.
 * This routine don't affect any data.
 * This routine only provides data to the end, if the data after read pointer wraps at end.
 * To get the rest data, process the data (copy), 
 * call [[free_ConcurrentRingBufferJcF]] with the returned nrofBytes and call peek second.
 *
 * This routine in pairs with [[free_ConcurrentRingBufferJcF]] should only called in one thread.
 * @param nrofBytes Output: available nrofBytes.
 */
void* peek_ConcurrentRingBufferJcF(ConcurrentRingBufferJc const* ythis, int* nrofBytes);


/**
 * frees the area after read pointer, 
 * @param nrofBytes to free. It should be no greater as the readable area.
 * @throws IndexOutOfBoundsException if nrofBytes is to large.
 */
void free_ConcurrentRingBufferJcF(ConcurrentRingBufferJc* ythis, int nrofBytes);





/**
 * Returns the number of elements in this queue.  If this queue
 * contains more than <tt>Integer.MAX_VALUE</tt> elements, returns
 * <tt>Integer.MAX_VALUE</tt>.
 *
 * <p>Beware that, unlike in most collections, this method is
 * <em>NOT</em> a constant-time operation. Because of the
 * asynchronous nature of these queues, determining the current
 * number of elements requires an O(n) traversal.
 *
 * @return the number of elements in this queue
 */
int size_ConcurrentRingBufferJcF(ConcurrentRingBufferJc* ythis);


 


#endif /*__ConcurrentRingBufferJc_h__*/
