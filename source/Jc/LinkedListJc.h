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
 *
 * @content Implementation of a LinkedList like java.util.LinkedList.
 *
 *
 * @author JcHartmut www.vishia.org
 * @version 0.83
 * list of changes:
 * 2007-05-00: JcHartmut creation
 *
 ****************************************************************************/
#ifndef JAVACPP_LINKEDLIST_H_
#define JAVACPP_LINKEDLIST_H_

#include "Jc/ObjectJc.h"
#include "emC/Exception.h"

#ifndef JAVACPP_ABSTRACTLIST_H_
  #include "Jc/AbstractListJc.h"  //includes pkgSystem/Object.h, pkgSystem/String.h
#endif

#ifndef JAVACPP_LISTITERAOR_H_
  #include "Jc/ListIteratorJc.h"  //includes pkgSystem/Object.h, pkgSystem/String.h
#endif



#include "Jc/ListMapEntryJc.h"

//#include "Exception_Jc.h"







typedef struct ListItr_LinkedListJc_t
{ ObjectJc object;
  struct LinkedListJc_t* outer;
  struct ListMapEntryJc_t* lastReturned;
  struct ListMapEntryJc_t* next;
  int nextIndex;
  int expectedModCount;
}ListItr_LinkedListJc;


METHOD_C ListItr_LinkedListJc* ctorO_ListItr_LinkedListJc(struct LinkedListJc_t* outer, ObjectJc* othis, ThCxt* _thCxt);

METHOD_C bool hasNext_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis, ThCxt* _thCxt);
METHOD_C ObjectJc* next_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis, ThCxt* _thCxt);
METHOD_C void remove_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis, ThCxt* _thCxt);


/**reinitialize the given instance to prevent a new mem allocation if a iterator is necessary.
 */
METHOD_C void reinit_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis, struct LinkedListJc_t* list);

/** Inner definition of the data of a linkedlist.*/
typedef struct LinkedListJcD_t
{ /**index of the items in the memPool, not in the list!, -1 if invalid*/
  ListMapEntryJc header;
  
  /**nr of items, 0 if no items*/
  int size;


}LinkedListJcD;



//public class LinkedList extends AbstractSequentialList
//		        implements List, Cloneable, java.io.Serializable
/** LinkedList

*/
typedef struct LinkedListJc_t
{ union{ ListJc List; ObjectJc object; AbstractListJc super; } base;
  LinkedListJcD data;
}LinkedListJc;


/**Finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_LinkedListJc_F(ObjectJc* othis, ThCxt* _thCxt);



/**The reflection information is supplied in a global variable, setted in code. */
//extern const Class_Jc* REFLECTION_LinkedListJc;

METHOD_C LinkedListJc* ctor_LinkedListJc(MemC mem);

/**Constructor based on a initialized Object. */
METHOD_C LinkedListJc* ctorO_LinkedListJc(ObjectJc* othis);

/**Constructor with a given node pool. 
 * This list won't allocate any dynamic memory, but the number of elements able to store is limited.
 * It is able to share the node pool between some other container instances.
 * @param mNodes: The memory is used for all nodes necessary to handle with the entries.
 *        The possible number of entries for all lists which shared this pool is size(siezof(ListMapEntryJc).
 */
METHOD_C LinkedListJc* ctorO_nodePool_LinkedListJc(ObjectJc* othis, MemC mNodes);

/**Constructor with a given other Container to share its node pool. 
 * If the other container referes a nood pool, the list won't allocate any dynamic memory, 
 * but the number of elements able to store in sume in all containers is limited.
 * @param sharedNodeContainer: The container which referes a node pool. 
 *                             It needn't be the first list initialized with ctorO_nodePool_LinkedListJc(...),
 *                             it may be also another container initialized with ctorO_shareNodes_... like this.
 */
METHOD_C LinkedListJc* ctorO_shareNodes_LinkedListJc(ObjectJc* othis, AbstractCollectionJc* sharedNodeContainer);


/**Constructor with a given Blockheap for the nodes.
 * @param heap The nodes will allocated in this heap.
 */
METHOD_C LinkedListJc* ctorO_BlockHeap_LinkedListJc(ObjectJc* othis, struct BlockHeap_emC_t* heap);



/**Initializes a LinkedList with a given pool of empty entries.
 */
//METHOD_C LinkedListJc* ctor_ListMapEntryJc_LinkedListJc(LinkedListJc* ythis, ListMapEntryJc* freeEntries);


#if defined(__CPLUSPLUS_Jcpp) && defined(__cplusplus)
  class IteratorJcpp* iteratorCpp_LinkedListJcF(LinkedListJc* ythis, IteratorJcpp* instanceToUse); //{ return listIterator(0); }
  //#define listIterator_LinkedList()             listIterator_LinkedList(0)
#endif //__CPLUSPLUS_Jcpp

//virtual void add(int ix, OBJECTPTR obj);
METHOD_C void add_i_LinkedListJcF(LinkedListJc* ythis, int ix, ObjectJc* obj, ThCxt* _thCxt);
//#define add_LinkedListJcF(ythis, obj){ add_i_LinkedList_V(ythis, (ythis)->data.nLen, obj);}

METHOD_C void add_LinkedListJcF(LinkedListJc* ythis, ObjectJc* obj, ThCxt* _thCxt);
  
  
  
METHOD_C ObjectJc* set_LinkedListJcF(LinkedListJc* ythis, int index, ObjectJc* element, ThCxt* _thCxt);

METHOD_C void clear_LinkedListJcF(LinkedListJc* ythis, ThCxt* _thCxt);

METHOD_C ObjectJc* remove_i_LinkedListJcF(LinkedListJc* ythis, int index, ThCxt* _thCxt);

/**Removes the object */
METHOD_C bool remove_o_LinkedListJcF(LinkedListJc* ythis, ObjectJcREF obj, ThCxt* _thCxt);

#define remove_LinkedListJcF(ythis, _thCxt) remove_i_LinkedListJcF(ythis, 0, _thCxt)

METHOD_C ObjectJc* removeFirst_LinkedListJcF(LinkedListJc* ythis, ThCxt* _thCxt);

METHOD_C ObjectJc* removeLast_LinkedListJcF(LinkedListJc* ythis, ThCxt* _thCxt);

#define size_LinkedListJcF(ythis)( (ythis)->data.size)

METHOD_C ObjectJc* get_LinkedListJcF(LinkedListJc* ythis, int ix, ThCxt* _thCxt);

METHOD_C int indexOf_LinkedListJcF(LinkedListJc* ythis, ObjectJc*, ThCxt* _thCxt);

METHOD_C bool isEmpty_LinkedListJcF(LinkedListJc* ythis);




typedef void (*Method_add_i_LinkedList)(LinkedListJc* ythis, int ix, ObjectJc* obj);
#define add_i_LinkedList(YTHIS, IX, OBJ) ((Method_add_i_List)(METHOD_V(idxVtbl_add_i_LinkedList, YTHIS)))(IX, OBJ)

#define sizeofEntry_LinkedListJc sizeof(ListMapEntryJc)

/**Initialize the node pool @deprecated, use ctorO_nodePool_LinkedListJc(...). */
METHOD_C void initEntryPool_LinkedListJc(LinkedListJc* ythis, MemC memBlock, ThCxt* _thCxt);


/**Share the node pool @deprecated, use ctorO_shareNodes_LinkedListJc(...). */
METHOD_C void shareEntryPool_LinkedListJc(LinkedListJc* ythis, LinkedListJc* srcShare, ThCxt* _thCxt);




#if 0
typedef enum IdxVtbl_LinkedList_t
{ idxVtbl_add_List_LinkedList    = idxVtbl_NEXT_Object
, idxVtbl_add_i_List_LinkedList    //Methods of interface List
, idxVtbl_addAll_List_LinkedList
, idxVtbl_addAll_i_List_LinkedList
, idxVtbl_Jclear_List_LinkedList
, idxVtbl_Jcontains_List_LinkedList
, idxVtbl_JcontainsAll_List_LinkedList
, idxVtbl_equals_List_LinkedList
, idxVtbl_get_List_LinkedList
, idxVtbl_hashCode_List_LinkedList
, idxVtbl_indexOf_List_LinkedList
, idxVtbl_isEmpty_List_LinkedList
, idxVtbl_iterator_List_LinkedList
, idxVtbl_lastIndexOf_List_LinkedList
, idxVtbl_listIterator_List_LinkedList
, idxVtbl_listIterator_i_List_LinkedList
, idxVtbl_remove_i_List_LinkedList
, idxVtbl_remove_o_List_LinkedList
, idxVtbl_removeAll_List_LinkedList
, idxVtbl_retainAll_List_LinkedList
, idxVtbl_set_List_LinkedList
, idxVtbl_size_List_LinkedList
, idxVtbl_subList_List_LinkedList
, idxVtbl_toArray_List_LinkedList
, idxVtbl_toArray_o_List_LinkedList
, idxVtbl_NEXT_LinkedList
}IdxVtbl_LinkedList;
#endif




#if defined(__CPLUSPLUS_Jcpp) && defined(__cplusplus)
class ListItr_LinkedListJcpp: public ListIteratorJcpp, private ListItr_LinkedListJc
{ 
  public: virtual bool hasNext(){ return hasNext_ListItr_LinkedListJcF(this); }
  public: virtual ObjectJc* next(){ return next_ListItr_LinkedListJcF(this); }
  public: virtual void remove(){ remove_ListItr_LinkedListJcF(this); }
  public: virtual IteratorJc* iter(){ return (IteratorJc*)(&this->object); } 


  public: virtual bool hasPrevious()     { return false; }
  public: virtual ObjectJc* previous()  { return null; }
  public: virtual int nextIndex()        { return 0; }
  public: virtual int previousIndex()    { return 0; }
  public: virtual void set(ObjectJc obj){ return; }
  public: virtual void add(ObjectJc obj){ return; }

  public: ObjectJcpp* toObject_Jcpp(){ return null; }
  public: ObjectJc*   toObject_Jc()  { return &object; }

  public: void reinit(LinkedListJc* list){ reinit_ListItr_LinkedListJcF(this, list); }

  public: ListItr_LinkedListJcpp(LinkedListJc* outer);

};

#endif //__CPLUSPLUS_Jcpp





#endif
