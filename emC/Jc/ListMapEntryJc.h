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
 * @version 0.83
 * @content definition of entries for container like java.util
 *
 * @author Jchartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#ifndef ListMapEntryJc_i__H_
#define ListMapEntryJc_i__H_

//#include "RuntimeHeapJc.h"
#include "emC/Jc/ObjectJc.h"

/** The analogue in Java is TreeMap.Entry! See there.
*/



struct ThreadContext_emC_t;
struct NodePoolJc_t;

/** Definition of 1 Entry in the Mempool*/
typedef struct ListMapEntryJc_t
{
  /** The parent node of a TreeMap*/
  struct ListMapEntryJc_t* parent;

  /** The left node of a TreeMap or the prev node of a LinkedList*/
  struct ListMapEntryJc_t* previous;

  /** The right node of a TreeMap or the next node of a LinkedList*/
  struct ListMapEntryJc_t* volatile next;

  /**Reference to the instance such as a LinkedList or TreeMap which uses this node.*/
  ObjectJc* allocater;

  //int32 mark_Map;   //mark of the using see EColor

  /** Reference to the key object of a TreeMap.
      the reference contains a reference to the parent Object,
      this is the LinkedList, TreeMap and others,
      for backtrace references for the garbage collection
      @refl: ObjectJc*.
  */
  ObjectJcREF key;

  /** Reference to the object of a Linked List, TreeMap or others.
      the reference contains a reference to the parent Object,
      this is the LinkedList, TreeMap and others,
      for backtrace references for the garbage collection
      @refl: ObjectJc*.
  */
  ObjectJcREF element;



} ListMapEntryJc;


#define LAST_ListMapEntryJc ((ListMapEntryJc*)(-1))


typedef enum EColor_t { kBlack = 0, kRed = 0x1 }EColor_ListMapEntryJc; //mark of a item for TreeMap
typedef enum { mBlackRed = 0x1 } EcolorBlackRed_ListMapEntryJc;        //bits in
typedef enum { kNoEntry = -1 }ENoEntry_ListMapEntryJc;          //Index


METHOD_C ListMapEntryJc* searchFreeItem_MapEntry(ObjectJc* parent);  //throws runtimeException if no memory
    void releaseItem_MapEntry(ListMapEntryJc* ythis);



    /** skip to the requested item in a double chain.
        Skipping from top if the item is nearly on top, and from end it is nearly end.
        @param iList pos of item in the chain
        @param zList nr of items in the list.
        @param iFirst index in the memory pool of the first item
        @param iLast index in the memory pool of the last item
        @return the index in memPool of the found item
    */
METHOD_C ListMapEntryJc* skip_MapEntry(int iList, int zList, ListMapEntryJc* iFirst, ListMapEntryJc* iLast);

    //ListMapEntryJc* next_MapEntry(ListMapEntryJc* ythis) { return ythis->next}
    #define next_MapEntry(ythis) (ythis->next)
    #define prev_MapEntry(ythis) (ythis->previous)
    #define right_MapEntry(ythis) (ythis->next)
    #define left_MapEntry(ythis) (ythis->previous)
    #define parent_MapEntry(ythis) (ythis->parent_Map)
    //bool isRed_MapEntry(ListMapEntryJc* ythis) { return(ythis->mark_Map & mBlackRed) == kRed}
    #define isRed_MapEntry(ythis) ((ythis->mark_Map & mBlackRed) == kRed)
    #define isBlack_MapEntry(ythis) ((ythis->mark_Map & mBlackRed) == kBlack)

    //void setLeft_MapEntry(ListMapEntryJc* ythis, ListMapEntryJc* left){ ythis->previous = left; }
    #define setLeft_MapEntry(ythis, left){ ythis->previous = left; }
    #define setRight_MapEntry(ythis, right){ ythis->next = right; }
    #define setPrev_MapEntry(ythis, left){ ythis->previous = left; }
    #define setNext_MapEntry(ythis, right){ ythis->next = right; }

/**gets the nodepool adequat to the implementation of NodePool-Allocation. */
METHOD_C struct NodePoolJc_t* current_NodePool_ListMapEntryJc(struct ThreadContext_emC_t* _thCxt);

/**Allocates a node.
 * @param nodePool The node-pool. It is returned from [[>current_NodePool_ListMapEntryJc(...)]].
 * @return the node. 
 */
METHOD_C ListMapEntryJc* alloc_ListMapEntryJc(struct NodePoolJc_t* nodePool, struct ThreadContext_emC_t* _thCxt);

/**Frees a node.
 * @param nodePool The node-pool. It is returned from [[>current_NodePool_ListMapEntryJc(...)]].
 * @param entry The node.
 * @return the node. 
 */
METHOD_C void free_ListMapEntryJc(struct NodePoolJc_t*, ListMapEntryJc* entry, struct ThreadContext_emC_t* _thCxt);


    /** assign the obj in a new item and concat it with the item at ix.
        @param parentRef reference to the Object administered this Entry, this is the
             instance of a LinkedList, TreeMap and others.
        @param obj the Object to be refered
        @param iBefore  the index in the memory pool after the Position, or -1 if not after exists
        @param iAfter the index in the memory pool after the Position, or -1 if not after exists
        @return the index of the new item
    */
METHOD_C ListMapEntryJc* add_MapEntry(ObjectJc* parentRef, ObjectJcREF obj, ListMapEntryJc* iBefore, ListMapEntryJc* iAfter);

    /** search a new Entry and set the values, exception if no memory
        @param parentRef reference to the Object administered this Entry, this is the
               instance of a LinkedList, TreeMap and others.
        @param obj the Object to be referenced by this entry
    */
METHOD_C ListMapEntryJc* xxnew_MapEntry(ObjectJc* parentRef, ObjectJcREF obj, ObjectJcREF key, ListMapEntryJc* parent);

/** search a new Entry and set the values, exception if no memory
    @xxxparam parentRef reference to the Object administered this Entry, this is the
           instance of a LinkedList, TreeMap and others.
    @param obj the Object to be referenced by this entry
*/
//METHOD_C ListMapEntryJc* new_ListMapEntryJc(ListMapEntryJc** emptyEntries, struct BlockHeap_emC_t* blockHeap); //, ListMapEntryJc* parent, ListMapEntryJc* iBefore, ListMapEntryJc* iAfter);


    /** get the Object in memPool.
      @param ix index in memPool
      @return Object
    */

METHOD_C ObjectJcREF setObj_MapEntry(ListMapEntryJc* ythis, ObjectJcREF obj);

    #define    get_MapEntry(ythis) ( ythis->obj_Map )
    #define getObj_MapEntry(ythis) ( ythis->obj_Map )
    #define getKey_MapEntry(ythis) ( ythis->key_Map )
    #define setKey_MapEntry(ythis, key) { ythis->key_Map = *key; }






#endif
