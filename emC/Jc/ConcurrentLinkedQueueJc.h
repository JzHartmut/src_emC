/****************************************************************************
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
 * This source is written looking at the original java source from sun.
 * Original comments and the copyright from Sun Microsystems are preserved, 
 * but some comments are added from me.
 * The translation of the algorithm for C language is done from me.
 * The state of licence should be validate. 
 **copyright***************************************************************************************
 *
 * @content Implementation of ConcurrentLinkedQueue
 *
 * @author JcHartmut www.vishia.org
 * @version 0.83
 * list of changes:
 * 2008-05-00: JcHartmut creation
 *
 ****************************************************************************/
#ifndef __ConcurrentLinkedQueueJc_h__
#define __ConcurrentLinkedQueueJc_h__

#include "emC/Base/MemC_emC.h"
#include "emC/Jc/ObjectJc.h"

/*@CLASS_C Node_ConcurrentLinkedQueueJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#define ITEM_QueueJcREF void*
#define NULLITEM_QueueJcREF ((void*)null)


typedef struct Node_ConcurrentLinkedQueueJc_t 
{
  /**Refer to the item. @refl: void*. */
  ITEM_QueueJcREF item;

  /**Refer the next node. */
  struct Node_ConcurrentLinkedQueueJc_t* volatile next;

  /**next Value if no next node is existing. 
   * If null is used as reference to a not existing next node, 
   * the mechanism of detecting using a freeNodePool is disturbed.
   */ 
  #define NOTEXISTING_Node_ConcurrentLinkedQueueJc ((Node_ConcurrentLinkedQueueJc*)(-1))
}Node_ConcurrentLinkedQueueJc;


/*@CLASS_C ConcurrentLinkedQueueJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**A ConcurrentLinkedQueue is a linked queue with thread safe access using lock-free programming with compareAndSet mechanism.
 * It is javalike, see java.util.concurrent.ConcurrentLinkedQueue.java. Some comments are orignally sun.
 */
typedef struct ConcurrentLinkedQueueJc_t
{
  union { ObjectJc object; } base; 
  /**
   * Pointer to header node, initialized to a dummy node.  The first
   * actual node is at head.getNext().
   */
  /*private*/ /*transient*/ struct Node_ConcurrentLinkedQueueJc_t* volatile head;
  
  /** Pointer to last node on list **/
  /*private*/ /*transient*/ struct Node_ConcurrentLinkedQueueJc_t* volatile tail;
  
  

  /**Access to a pool of free Entries to link, getted from a fix ListMapEntryJc-pool.
   * This attribute is null if no fix pool should be used. 
   * The pointer references the element theFreeNodePool in the instance which holds the pool.
   */
  struct Node_ConcurrentLinkedQueueJc_t* volatile* refFreeNodePool;

  /**The pool of free Entries to link, setted with method initEntryPool_ConcurrentLinkedQueueJcF().
   * This attribute is only used for the LinkedList holding the freeEntryPool.
   */
  struct Node_ConcurrentLinkedQueueJc_t* volatile theFreeNodePool;

  
}ConcurrentLinkedQueueJc_s;

#define sizeof_ConcurrentLinkedQueueJc_s sizeof(ConcurrentLinkedQueueJc_s)

#define ID_refl_ConcurrentLinkedQueueJc 0xee

#ifndef ConcurrentLinkedQueueJcREFDEF
  #define ConcurrentLinkedQueueJcREFDEF
  typedef TYPE_EnhancedRefJc(ConcurrentLinkedQueueJc);
#endif


/**The sizeof of a node.
 * It is a immediate constant here, but the correctness is tested in ctor_ConcurrentLinkedQueueJc().
 */
#define SIZEOF_Node_ConcurrentLinkedQueueJc (2*sizeof(void*))

/**Creates a uninitialized instance. */
METHOD_C ConcurrentLinkedQueueJc_s* ctorO_init_ConcurrentLinkedQueueJc(ObjectJc* othis, bool init, ThCxt* _thCxt);

/**Creates a ,,ConcurrentLinkedQueue,, that is initially empty but with a node pool
 */
METHOD_C ConcurrentLinkedQueueJc_s* ctorO_MemC_ConcurrentLinkedQueueJc(ObjectJc* othis, MemC memNodes, ThCxt* _thCxt);

/**Creates a ,,ConcurrentLinkedQueue,, that is initially empty but with a node pool shared with another queue.
 */
METHOD_C ConcurrentLinkedQueueJc_s* ctorO_Clq_ConcurrentLinkedQueueJc(ObjectJc* othis, ConcurrentLinkedQueueJc_s* srcShare, ThCxt* _thCxt);

ConcurrentLinkedQueueJc_s* ctor_ConcurrentLinkedQueueJc(MemC rawMem);

void ctorc_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis);

/**constructs a LinkedQueue with a fix number of nodes. */
ConcurrentLinkedQueueJc_s* ctorMn_ConcurrentLinkedQueueJc(MemC rawMem, MemC memNodes);

/**constructs a LinkedQueue with a fix number of nodes. */
void ctorcMn_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, MemC memNodes);

/**constructs a LinkedQueue with shard nodes with another List. */
ConcurrentLinkedQueueJc_s* ctorSn_ConcurrentLinkedQueueJc(MemC rawMem, ConcurrentLinkedQueueJc_s* srcShare);

/**constructs a LinkedQueue with a fix number of nodes. */
void ctorcSn_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, ConcurrentLinkedQueueJc_s* srcShare);



/**assigns a pool of nodes in memory to this container.
 * @params mem A mem pool. All bytes are used as nodes. The mem pool is initalized in the routine. 
               No intializing before is neccessary 
 */
METHOD_C void initNodePool_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, MemC mem);


/**shares the pool of nodes with the given other container.
 * The other container should initialized with [[initNodePool_ConcurrentLinkedQueueJc]] before
 * or it is also shared calling [[shareNodePool_ConcurrentLinkedQueueJc]] before.
 */
METHOD_C void shareNodePool_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, ConcurrentLinkedQueueJc_s* srcNodeShare);



/**
 * Inserts the specified element at the tail of this queue.
 *
 * @return <tt>true</tt> (as specified by {@link Collection#add})
 * @throws NullPointerException if the specified element is null
 */
bool add_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, ITEM_QueueJcREF e);
#define add_ConcurrentLinkedQueueJc(YTHIS, ITEM, THC) add_ConcurrentLinkedQueueJcF(YTHIS, ITEM)

/**
 * Inserts the specified element at the tail of this queue.
 *
 * @return <tt>true</tt> (as specified by {@link Queue#offer})
 * @throws NullPointerException if the specified element is null
 */
bool offer_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, ITEM_QueueJcREF e);
#define offer_ConcurrentLinkedQueueJc(YTHIS, ENTRY, THC) offer_ConcurrentLinkedQueueJcF(YTHIS, ENTRY)
/**
 * Returns <tt>true</tt> if this queue contains the specified element.
 * More formally, returns <tt>true</tt> if and only if this queue contains
 * at least one element <tt>e</tt> such that <tt>o.equals(e)</tt>.
 *
 * @param o object to be checked for containment in this queue
 * @return <tt>true</tt> if this queue contains the specified element
 */
bool contains_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, ObjectJc* o);


/**
 * Returns <tt>true</tt> if this queue contains no elements.
 *
 * @return <tt>true</tt> if this queue contains no elements
 */
bool isEmpty_ConcurrentLinkedQueue(ConcurrentLinkedQueueJc_s* ythis);


ITEM_QueueJcREF peek_ConcurrentLinkedQueue(ConcurrentLinkedQueueJc_s* ythis);


ITEM_QueueJcREF poll_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis);
#define poll_ConcurrentLinkedQueueJc(YTHIS, STC) poll_ConcurrentLinkedQueueJcF(YTHIS) 
/**
 * Removes a single instance of the specified element from this queue,
 * if it is present.  More formally, removes an element <tt>e</tt> such
 * that <tt>o.equals(e)</tt>, if this queue contains one or more such
 * elements.
 * Returns <tt>true</tt> if this queue contained the specified element
 * (or equivalently, if this queue changed as a result of the call).
 *
 * @param o element to be removed from this queue, if present
 * @return <tt>true</tt> if this queue changed as a result of the call
 */
bool remove_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, ITEM_QueueJcREF o);



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
int size_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis);


 


#endif /*__ConcurrentLinkedQueueJc_h__*/
