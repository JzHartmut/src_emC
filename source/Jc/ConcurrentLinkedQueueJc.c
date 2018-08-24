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

/*
 * @(#)ConcurrentLinkedQueue.java	1.12 06/04/21
 *
 * Copyright 2006 Sun Microsystems, Inc. All rights reserved.
 * SUN PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 */


#include "Jc/ObjectJc.h"
#include "Jc/ConcurrentLinkedQueueJc.h"
#include "os_AtomicAccess.h"
#include "emC/Exception_emC.h"

//package java.util.concurrent;
//import java.util.*;
//import java.util.concurrent.atomic.*;


/**
 * An unbounded thread-safe {@linkplain Queue queue} based on linked nodes.
 * This queue orders elements FIFO (first-in-first-out).
 * The <em>head</em> of the queue is that element that has been on the
 * queue the longest time.
 * The <em>tail</em> of the queue is that element that has been on the
 * queue the shortest time. New elements
 * are inserted at the tail of the queue, and the queue retrieval
 * operations obtain elements at the head of the queue.
 * A <tt>ConcurrentLinkedQueue</tt> is an appropriate choice when
 * many threads will share access to a common collection.
 * This queue does not permit <tt>null</tt> elements.
 *
 * <p>This implementation employs an efficient &quot;wait-free&quot;
 * algorithm based on one described in <a
 * href="http://www.cs.rochester.edu/u/michael/PODC96.html"> Simple,
 * Fast, and Practical Non-Blocking and Blocking Concurrent Queue
 * Algorithms</a> by Maged M. Michael and Michael L. Scott.
 *
 * <p>Beware that, unlike in most collections, the <tt>size</tt> method
 * is <em>NOT</em> a constant-time operation. Because of the
 * asynchronous nature of these queues, determining the current number
 * of elements requires a traversal of the elements.
 *
 * <p>This class and its iterator implement all of the
 * <em>optional</em> methods of the {@link Collection} and {@link
 * Iterator} interfaces.
 *
 * <p>Memory consistency effects: As with other concurrent
 * collections, actions in a thread prior to placing an object into a
 * {@code ConcurrentLinkedQueue}
 * <a href="package-summary.html#MemoryVisibility"><i>happen-before</i></a>
 * actions subsequent to the access or removal of that element from
 * the {@code ConcurrentLinkedQueue} in another thread.
 *
 * <p>This class is a member of the
 * <a href="{@docRoot}/../technotes/guides/collections/index.html">
 * Java Collections Framework</a>.
 *
 * @since 1.5
 * @author Doug Lea
 * @param <E> the type of elements held in this collection
 *
 */

/*
 * This is a straight adaptation of Michael & Scott algorithm.
 * For explanation, read the paper.  The only (minor) algorithmic
 * difference is that this version supports lazy deletion of
 * internal nodes (method remove(Object)) -- remove CAS'es item
 * fields to null. The normal queue operations unlink but then
 * pass over nodes with null item fields. Similarly, iteration
 * methods ignore those with nulls.
 *
 * Also note that like most non-blocking algorithms in this
 * package, this implementation relies on the fact that in garbage
 * collected systems, there is no possibility of ABA problems due
 * to recycled nodes, so there is no need to use "counted
 * pointers" or related techniques seen in versions used in
 * non-GC'ed settings.
 */


Node_ConcurrentLinkedQueueJc*  new_Node_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s*ythis, ITEM_QueueJcREF item, Node_ConcurrentLinkedQueueJc*  next);
void restitute_Node_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, Node_ConcurrentLinkedQueueJc*  node);

/*    
static Node_ConcurrentLinkedQueueJc*  ctor_Node_ConcurrentLinkedQueueJc(MemC rawMem, ITEM_QueueJcREF x) 
{ Node_ConcurrentLinkedQueueJc*  ythis = PTR_MemC(rawMem, Node_ConcurrentLinkedQueueJc);
  STACKTRC_ENTRY("ctor_Node_ConcurrentLinkedQueueJc");
  if(size_MemC(rawMem) < sizeof(Node_ConcurrentLinkedQueueJc)) 
  { THROW1_s0(IllegalArgumentException,"size to less", size_MemC(rawMem)); }
  ythis->item = x;
  STACKTRC_LEAVE; return ythis; 
}
*/


static Node_ConcurrentLinkedQueueJc*  ctor_itemNext_Node_ConcurrentLinkedQueueJc(MemC rawMem, ITEM_QueueJcREF x, Node_ConcurrentLinkedQueueJc*  n) 
{ Node_ConcurrentLinkedQueueJc*  ythis = PTR_MemC(rawMem, Node_ConcurrentLinkedQueueJc);
  STACKTRC_ENTRY("ctor_Node_ConcurrentLinkedQueueJc");
  if(size_MemC(rawMem) < sizeof(Node_ConcurrentLinkedQueueJc)) 
  { THROW1_s0(IllegalArgumentException,"size to less", size_MemC(rawMem)); }
  ythis->item = x; ythis->next = n; 
  STACKTRC_LEAVE; return ythis; 
}



void* getItem_Node_ConcurrentLinkedQueueJcF(Node_ConcurrentLinkedQueueJc*  ythis) 
{
        return ythis->item;
}


/**compare and set item. */
static/*private*/ bool casItem_Node_ConcurrentLinkedQueueJcF(Node_ConcurrentLinkedQueueJc*  ythis, ITEM_QueueJcREF cmp, ITEM_QueueJcREF val) 
{
  void* last = compareAndSwap_AtomicReference(CAST_AtomicReference(ythis->item), cmp, val);
  return last == cmp;  //true if the last present value was equal the expected value before update.
}




static/*private*/ void setItem_Node_ConcurrentLinkedQueueJcF(Node_ConcurrentLinkedQueueJc*  ythis, ITEM_QueueJcREF val) 
{
    ythis->item = val;
}

static/*private*/ Node_ConcurrentLinkedQueueJc*  volatile getNext_Node_ConcurrentLinkedQueueJcF(Node_ConcurrentLinkedQueueJc*  ythis) 
{
  return ythis->next;
}

static/*private*/ bool casNext_Node_ConcurrentLinkedQueueJcF
( Node_ConcurrentLinkedQueueJc*  ythis
, Node_ConcurrentLinkedQueueJc*  cmp
, Node_ConcurrentLinkedQueueJc*  val
) 
{
  void* last = compareAndSwap_AtomicReference(CAST_AtomicReference(ythis->next), cmp, val);
  return last == cmp;  //true if the last present value was equal the expected value before update.
}

/*
static void setNext_Node_ConcurrentLinkedQueueJcF(Node_ConcurrentLinkedQueueJc*  ythis, Node_ConcurrentLinkedQueueJc*  val) 
{
    ythis->next = val;
}
*/

static/*private*/ bool casTail_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, Node_ConcurrentLinkedQueueJc*  cmp, Node_ConcurrentLinkedQueueJc*  val) 
{
  void* last = compareAndSwap_AtomicReference(CAST_AtomicReference(ythis->tail), cmp, val);
  return last == cmp;  //true if the last present value was equal the expected value before update.
}

static/*private*/ bool casHead_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, Node_ConcurrentLinkedQueueJc*  cmp, Node_ConcurrentLinkedQueueJc*  val) 
{
  void* last = compareAndSwap_AtomicReference(CAST_AtomicReference(ythis->head), cmp, val);
  return last == cmp;  //true if the last present value was equal the expected value before update.
}



/**
 * Creates a <tt>ConcurrentLinkedQueue</tt> that is initially empty.
 */
ConcurrentLinkedQueueJc_s* ctor_ConcurrentLinkedQueueJc(MemC rawMem) 
{ ConcurrentLinkedQueueJc_s* ythis = PTR_MemC(rawMem, ConcurrentLinkedQueueJc_s);
  STACKTRC_ENTRY("ctor_ConcurrentLinkedQueueJc");
  if(size_MemC(rawMem) < sizeof(ConcurrentLinkedQueueJc_s)) 
  { THROW1_s0(IllegalArgumentException,"size to less", size_MemC(rawMem)); }
  ctorc_ConcurrentLinkedQueueJc(ythis);
  STACKTRC_LEAVE; return ythis;
}

void ctorc_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis) 
{ ythis->head = new_Node_ConcurrentLinkedQueueJcF(ythis, null, null);
  ythis->tail = ythis->head;
}

/**
 * Creates a <tt>ConcurrentLinkedQueue</tt> that is initially empty but with a node pool
 */
ConcurrentLinkedQueueJc_s* ctorO_MemC_ConcurrentLinkedQueueJc(ObjectJc* othis, MemC memNodes, ThCxt* _thCxt)
{ ConcurrentLinkedQueueJc_s* ythis = (ConcurrentLinkedQueueJc_s*)othis;
  STACKTRC_TENTRY("ctorO_MemC_ConcurrentLinkedQueueJc");
  checkConsistence_ObjectJc(othis, sizeof(ConcurrentLinkedQueueJc_s), null/*&reflection_ConcurrentLinkedQueueJc_s*/, _thCxt); 
  ctorcMn_ConcurrentLinkedQueueJc(ythis, memNodes);
  STACKTRC_LEAVE;
  return ythis;
}


ConcurrentLinkedQueueJc_s* ctorMn_ConcurrentLinkedQueueJc(MemC rawMem, MemC memNodes) 
{ ConcurrentLinkedQueueJc_s* ythis = PTR_MemC(rawMem, ConcurrentLinkedQueueJc_s);
  STACKTRC_ENTRY("ctor_ConcurrentLinkedQueueJc");
  if(size_MemC(rawMem) < sizeof(ConcurrentLinkedQueueJc_s)) 
  { THROW1_s0(IllegalArgumentException,"size to less", size_MemC(rawMem)); }
  ctorcMn_ConcurrentLinkedQueueJc(ythis, memNodes);
  STACKTRC_LEAVE; return ythis;
}

void ctorcMn_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, MemC memNodes) 
{ INIT0p_MemC(ythis);
  initNodePool_ConcurrentLinkedQueueJc(ythis, memNodes);
}

/**
 * Creates a <tt>ConcurrentLinkedQueue</tt> that is initially empty but with a node pool
 */
ConcurrentLinkedQueueJc_s* ctorO_Clq_ConcurrentLinkedQueueJc(ObjectJc* othis, ConcurrentLinkedQueueJc_s* srcNodeShare, ThCxt* _thCxt)
{ ConcurrentLinkedQueueJc_s* ythis = (ConcurrentLinkedQueueJc_s*)othis;
  STACKTRC_TENTRY("ctorO_Clq_ConcurrentLinkedQueueJc");
  checkConsistence_ObjectJc(othis, sizeof(ConcurrentLinkedQueueJc_s), null/*&reflection_ConcurrentLinkedQueueJc_s*/, _thCxt); 
  ctorcSn_ConcurrentLinkedQueueJc(ythis, srcNodeShare);
  STACKTRC_LEAVE;
  return ythis;
}


ConcurrentLinkedQueueJc_s* ctorSn_ConcurrentLinkedQueueJc(MemC rawMem, ConcurrentLinkedQueueJc_s* srcNodeShare) 
{ ConcurrentLinkedQueueJc_s* ythis = PTR_MemC(rawMem, ConcurrentLinkedQueueJc_s);
  STACKTRC_ENTRY("ctor_ConcurrentLinkedQueueJc");
  if(size_MemC(rawMem) < sizeof(ConcurrentLinkedQueueJc_s)) 
  { THROW1_s0(IllegalArgumentException,"size to less", size_MemC(rawMem)); }
  ctorcSn_ConcurrentLinkedQueueJc(ythis, srcNodeShare);
  STACKTRC_LEAVE; return ythis;
}

void ctorcSn_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, ConcurrentLinkedQueueJc_s* srcNodeShare) 
{ INIT0p_MemC(ythis);
  shareNodePool_ConcurrentLinkedQueueJc(ythis, srcNodeShare);
}




METHOD_C ConcurrentLinkedQueueJc_s* ctorO_init_ConcurrentLinkedQueueJc(ObjectJc* othis, bool init, ThCxt* _thCxt)
{
  ConcurrentLinkedQueueJc_s* ythis = (ConcurrentLinkedQueueJc_s*)othis;
  STACKTRC_TENTRY("ctorO_Clq_ConcurrentLinkedQueueJc");
  checkConsistence_ObjectJc(othis, sizeof(ConcurrentLinkedQueueJc_s), null/*&reflection_ConcurrentLinkedQueueJc_s*/, _thCxt); 
  return ythis; 
}


    /**
     * Creates a <tt>ConcurrentLinkedQueue</tt>
     * initially containing the elements of the given collection,
     * added in traversal order of the collection's iterator.
     * @param c the collection of elements to initially contain
     * @throws NullPointerException if the specified collection or any
     *         of its elements are null
     */
    /*
    public ctor_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, Collection<? extends E> c) {
        for (Iterator<? extends E> it = c.iterator(); it.hasNext();)
            add(it.next());
    }
    */

    /**
     * Inserts the specified element at the tail of this queue.
     *
     * @return true if the node is added, false if not.
     * @throws NullPointerException if the specified element is null
     */
    bool add_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, ITEM_QueueJcREF e) 
    {
        return offer_ConcurrentLinkedQueueJcF(ythis, e);
    }

/**
 * Inserts the specified element at the tail of this queue.
 *
 * @return true if the node is added, false if not.
 * @throws NullPointerException if the specified element is null
 */
bool offer_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, ITEM_QueueJcREF e) 
{ STACKTRC_ENTRY("offer_ConcurrentLinkedQueue");
  if (e == null) THROW1_s0(NullPointerException,"",0);
  { Node_ConcurrentLinkedQueueJc*  n = new_Node_ConcurrentLinkedQueueJcF(ythis, e, null);
    if(n == null)
    { STACKTRC_LEAVE; return false; 
    }
    for (;;) 
    {
      Node_ConcurrentLinkedQueueJc*  t = ythis->tail;
      Node_ConcurrentLinkedQueueJc*  s = getNext_Node_ConcurrentLinkedQueueJcF(t);
      if (t == ythis->tail) //normally, it is true. But if an interrupt occurs, repeat access to tail 
      { 
        if (s == null) //normally, it is true, because the tail node is the last. But repeat on interrupt.
        {
          if (casNext_Node_ConcurrentLinkedQueueJcF(t, s, n)) //try set next of tail-node with the newNode
          { //the tail node refers the new node as next.
            //try to set the tail of this with the new node.
            //If the thread was interrupted, the tail-reference may be updated already. 
            //Than this newNode is not refer by tail, but the updated node. This node is refered properly,
            //because it is enqueued already before the tail. 
              casTail_ConcurrentLinkedQueueJcF(ythis, t, n); //It is okay anyway. 
              STACKTRC_LEAVE; return true;
          }
        } 
        else 
        { //The thread has interrupted another access to the the tail reference,
          //before the tail was set to the really end.
          //Therefore: set the lastMapEntry to the next found strange entry.
          //after them the test will be repeated so long as next == null.
          casTail_ConcurrentLinkedQueueJcF(ythis, t, s);
        }
      }
    }
  }
}



ITEM_QueueJcREF poll_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis) 
{
  for (;;) {
    Node_ConcurrentLinkedQueueJc*  h = ythis->head;  //the head node.
    Node_ConcurrentLinkedQueueJc*  t = ythis->tail;
    //first is the first node with content, not the head node.
    Node_ConcurrentLinkedQueueJc*  second = getNext_Node_ConcurrentLinkedQueueJcF(h);
    if (h == ythis->head) 
    { //if ...
      if (h == t) 
      { //only one node in list, it has to remain there.
        if (second == null)
        { //one node hasn't a next. It is the only one node of list, it is a node without item.
          //therefore return null, no content available.
          return null;  //it is possible, that another thread has add something, but at time off start of this routine it isn't so!
        }
        else
        { //the first node have a next, though tail references first. 
          //It is only possible because another Thread has set the next of first but not set tail yet.
          //do it now, but only if tail isn't modified meanwhile.
          casTail_ConcurrentLinkedQueueJcF(ythis, t, second);
          //repeat the access to head and tail!
        }
      } 
      else if (casHead_ConcurrentLinkedQueueJcF(ythis, h, second)) 
      { //a first node with an item exists, attemp to set it as head node.
        //if it is successfull, the item can getted in peace. 
        //No other thread disturbed it because no other thread read out the item of the head node. 
        void* item = getItem_Node_ConcurrentLinkedQueueJcF(second);
        if (item != null) 
        { //a node can be a dead node, with removed item, see [[remove_ConcurrentLinkedQueueJc]].
          //only if there is an item,it is successfull. 
          setItem_Node_ConcurrentLinkedQueueJcF(second, null);  //now it is the head node, it shouldn't have an item as content.
          restitute_Node_ConcurrentLinkedQueueJcF(ythis, h);   //this is for C, the free node is to restitue. In Java the GC do it.
          return item;
        }
        // else skip over deleted item, continue loop,
      }
    }
  }
}

    ITEM_QueueJcREF peek_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis) 
    { // same as poll except don't remove item
        for (;;) {
            Node_ConcurrentLinkedQueueJc*  h = ythis->head;
            Node_ConcurrentLinkedQueueJc*  t = ythis->tail;
            Node_ConcurrentLinkedQueueJc*  first = getNext_Node_ConcurrentLinkedQueueJcF(h);
            if (h == ythis->head) {
                if (h == t) {
                    if (first == null)
                        return null;
                    else
                        casTail_ConcurrentLinkedQueueJcF(ythis, t, first);
                } else if (casHead_ConcurrentLinkedQueueJcF(ythis, h, first)) {
                    void* item = getItem_Node_ConcurrentLinkedQueueJcF(first);
                    if (item != null)
                        return item;
                    else // remove deleted node and continue
                        casHead_ConcurrentLinkedQueueJcF(ythis, h, first);
                    // else skip over deleted item, continue loop,
                }
            }
        }
    }

    /**
     * Returns the first actual (non-header) node on list.  This is yet
     * another variant of poll/peek; here returning out the first
     * node, not element (so we cannot collapse with peek() without
     * introducing race.)
     */
    static Node_ConcurrentLinkedQueueJc*  first_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis) 
    {
        for (;;) {
            Node_ConcurrentLinkedQueueJc*  h = ythis->head;
            Node_ConcurrentLinkedQueueJc*  t = ythis->tail;
            Node_ConcurrentLinkedQueueJc*  first = getNext_Node_ConcurrentLinkedQueueJcF(h);
            if (h == ythis->head) {
                if (h == t) {
                    if (first == null)
                        return null;
                    else
                        casTail_ConcurrentLinkedQueueJcF(ythis, t, first);
                } else {
                    if (getItem_Node_ConcurrentLinkedQueueJcF(first) != null)
                        return first;
                    else // remove deleted node and continue
                        casHead_ConcurrentLinkedQueueJcF(ythis, h, first);
                }
            }
        }
    }


    /**
     * Returns <tt>true</tt> if this queue contains no elements.
     *
     * @return <tt>true</tt> if this queue contains no elements
     */
    bool isEmpty_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis) {
        return first_ConcurrentLinkedQueueJcF(ythis) == null;
    }

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
int size_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis) 
{  Node_ConcurrentLinkedQueueJc*  p;
    int count = 0;
    for (p = first_ConcurrentLinkedQueueJcF(ythis); p != null; p = getNext_Node_ConcurrentLinkedQueueJcF(p)) 
    {
        if (getItem_Node_ConcurrentLinkedQueueJcF(p) != null) 
        {
            // Collections.size() spec says to max out
            if (++count == MAX_VALUE_IntegerJc)
                break;
        }
    }
    return count;
}

    /**
     * Returns <tt>true</tt> if this queue contains the specified element.
     * More formally, returns <tt>true</tt> if and only if this queue contains
     * at least one element <tt>e</tt> such that <tt>o.equals(e)</tt>.
     *
     * @param o object to be checked for containment in this queue
     * @return <tt>true</tt> if this queue contains the specified element
     */
    bool contains_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, ITEM_QueueJcREF o) 
    { Node_ConcurrentLinkedQueueJc*  p;
        if (o == null) return false;
        for ( p = first_ConcurrentLinkedQueueJcF(ythis); p != null; p = getNext_Node_ConcurrentLinkedQueueJcF(p)) {
            void* item = getItem_Node_ConcurrentLinkedQueueJcF(p);
            if (item != null &&
                o == item )  //o.equals(item))  CLARIFY direct pointer compare or Object.equals like in Java
                return true;
        }
        return false;
    }

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
    bool remove_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, ITEM_QueueJcREF o) 
    { Node_ConcurrentLinkedQueueJc*  p;
        if (o == null) return false;
        for ( p = first_ConcurrentLinkedQueueJcF(ythis); p != null; p = getNext_Node_ConcurrentLinkedQueueJcF(p)) {
            ITEM_QueueJcREF item = getItem_Node_ConcurrentLinkedQueueJcF(p);
            if (item != null &&
                o == item &&  //o.equals(item) &&  CLARIFY direct pointer compare or Object.equals like in Java
                casItem_Node_ConcurrentLinkedQueueJcF(p, item, NULLITEM_QueueJcREF))
                return true;
        }
        return false;
    }













METHOD_C void initNodePool_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, MemC mem)
{ int nrofEntries;
  STACKTRC_ENTRY("newPool_ListMapEntryJc");
  if(PTR_MemC(mem, void) == null)
  { THROW1_s0(RuntimeException, "no memory", size_MemC(mem));
  }
  init0_MemC(mem);
  nrofEntries = size_MemC(mem) / sizeof(Node_ConcurrentLinkedQueueJc);
  { int ii;
    Node_ConcurrentLinkedQueueJc*  actNode = PTR_MemC(mem, Node_ConcurrentLinkedQueueJc);
    ythis->theFreeNodePool = actNode;
    ythis->refFreeNodePool = &ythis->theFreeNodePool;
    for(ii=0; ii < (nrofEntries-1); ii++)
    { Node_ConcurrentLinkedQueueJc*  nextNode = actNode +1;  //pointer increment of sizeof(*actNode)
      actNode->next = nextNode;  //pointer to the next
      actNode = nextNode;                     //
    }
    //the last entry has entries->rigth_Map = 0xffffffff!
    actNode->next = NOTEXISTING_Node_ConcurrentLinkedQueueJc;
  }
  ythis->head = new_Node_ConcurrentLinkedQueueJcF(ythis, null, null);
  ythis->tail = ythis->head;
  STACKTRC_LEAVE;
}



METHOD_C void shareNodePool_ConcurrentLinkedQueueJc(ConcurrentLinkedQueueJc_s* ythis, ConcurrentLinkedQueueJc_s* srcShare)
{ /*NOTE: the srcShare have to be that linkedlist holding the entryPool.
   * It may be possible to use a always shared List for reference of entry pool,
   * but the user should use the original List.
   */
  ythis->refFreeNodePool = srcShare->refFreeNodePool; 
  ythis->head = new_Node_ConcurrentLinkedQueueJcF(ythis, null, null);
  ythis->tail = ythis->head;
}








/**supplies a node.
 * Not in Java, extension for C embedded systems.
 * @returns null if a freeNodePool is used, but there aren't any nodes available.
 */
Node_ConcurrentLinkedQueueJc*  new_Node_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, ITEM_QueueJcREF item, Node_ConcurrentLinkedQueueJc*  next)
{ Node_ConcurrentLinkedQueueJc*  newNode = null;
  MemC mem;
  STACKTRC_ENTRY("new_Node_ConcurrentLinkedQueueJcF");
  if(   ythis->refFreeNodePool != null  //the argument is given, (null if admissible) 
    && *ythis->refFreeNodePool != null  //the given emptyEntries are setted.
    )
  { //pointer to the first free node pointer. It is a fix address in the instance of ConcurrentLinkedQueueJc_s
    bool bRepeatCompareAndSet;
    Node_ConcurrentLinkedQueueJc*  volatile* firstFreeNode = ythis->refFreeNodePool;  
    do
    { Node_ConcurrentLinkedQueueJc*  newFirstFreeNode;
      newNode = *firstFreeNode;
      ASSERTJc_TEST(newNode != null);   //null is not valid!
      if(newNode == NOTEXISTING_Node_ConcurrentLinkedQueueJc)
      { bRepeatCompareAndSet = false;
        set_MemC(mem, null, 0);
        newNode = null;
      }
      else
      { //The new firstFreeNode is the next from current firstFreeNode.
        newFirstFreeNode = newNode->next; //may be null if it is the last one. 
        //Set the newFirstFreeNode only if the newNode is still the current. 
        { void* last = compareAndSwap_AtomicReference(CAST_AtomicReference(*firstFreeNode), newNode, newFirstFreeNode);
          bRepeatCompareAndSet = (last != newNode);  //repeat it if it isn't successfully.
        }
      }
    }while(bRepeatCompareAndSet);
    mem = build_MemC((void* /*not volatile, its my*/)newNode, sizeof(*newNode));
  }
  else if(false) //blockHeap != null)
  { //TODO
  }
  else
  { mem = alloc_MemC(sizeof(Node_ConcurrentLinkedQueueJc));
  }
  if(PTR_MemC(mem, void) != null)
  { newNode = ctor_itemNext_Node_ConcurrentLinkedQueueJc(mem, item, next);
  }
  STACKTRC_LEAVE; return newNode;  //null is possible.
}



void restitute_Node_ConcurrentLinkedQueueJcF(ConcurrentLinkedQueueJc_s* ythis, Node_ConcurrentLinkedQueueJc*  node)
{
  STACKTRC_ENTRY("restitute_Node_ConcurrentLinkedQueueJcF");
  if(   ythis->refFreeNodePool != null  //the argument is given, (null if admissible) 
    && *ythis->refFreeNodePool != null  //the given emptyEntries are setted.
    )
  { //pointer to the first free node pointer. It is a fix address in the instance of ConcurrentLinkedQueueJc_s
    bool bRepeatCompareAndSet;
    Node_ConcurrentLinkedQueueJc*  volatile* firstFreeNode = ythis->refFreeNodePool;  
    do
    { Node_ConcurrentLinkedQueueJc*  currentFirstFreeNode;
      currentFirstFreeNode = *firstFreeNode;  
      node->next = currentFirstFreeNode;   //It is correct if the finite compareAndSet will be successfull.
      //Set the newFirstFreeNode only if the currentFirstFreeNode is still the current. 
      { void* last = compareAndSwap_AtomicReference(CAST_AtomicReference(*firstFreeNode), currentFirstFreeNode, node);
        bRepeatCompareAndSet = (last != currentFirstFreeNode);  //repeat it if it isn't successfully.
      }
    }while(bRepeatCompareAndSet);
  }
  else
  {
    //MemC mem = build_MemC((void* /*not volatile*/)node, sizeof(*node));
    int error = free_MemC(node);
    ASSERTJc_TEST(error==0);
  }
  STACKTRC_LEAVE;
}

#include <genRefl/Jc/ConcurrentLinkedQueueJc.crefl>


/**
 * Not in Java, extension for C embedded systems.
 */
