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

#include "emC/Jc/LinkedListJc.h"

#include "emC/Jc/ListMapEntryJc.h"

#include <string.h>

#ifndef NO_DYNAMICALLY_MEMORY
	#include <emC/BlockHeap/BlockHeap_emC.h>
#endif
/***************************************************************************************
****************************************************************************************
***************************************************************************************/

/** Methods from LinkedList
*/

/**@deprecated: compatibility. */
LinkedListJc* ctor_LinkedListJc(MemC mem)
{
  ObjectJc* othis = PTR_MemC(mem, ObjectJc);
  if(othis == null || size_MemC(mem) < sizeof(LinkedListJc))
  { STACKTRC_ENTRY("ctor_LinkedListJc");
    THROW1_s0(RuntimeException, "", 0);
    STACKTRC_LEAVE;
  }
  init_ObjectJc(othis, size_MemC(mem), 0);
  return ctorO_LinkedListJc(othis);

}

extern_C ClassJc const reflection_LinkedListJc;


LinkedListJc* ctorO_LinkedListJc(ObjectJc* othis)
{ 
  LinkedListJc* ythis = (LinkedListJc*)othis;  //upcasting to the real class.
  int sizeObj = getSizeInfo_ObjectJc(othis);
  STACKTRC_ENTRY("ctorO_LinkedListJc");
  setReflection_ObjectJc(othis, &reflection_LinkedListJc, sizeof(LinkedListJc));  
  checkConsistence_ObjectJc(othis, sizeof(LinkedListJc), &reflection_LinkedListJc, _thCxt);  
  
  ythis->data.header.previous = ythis->data.header.next = &ythis->data.header;  //no valid pointer is pointer to itself.
  ythis->data.size = 0;
  ythis->base.super.modCount = 0;

  ythis->base.super.nodePool = null;
  ythis->base.super.refFreeEntryPool = null;
  ythis->base.super.theFreeEntryPool = null;

  STACKTRC_LEAVE;
  return ythis;
}


LinkedListJc* ctorO_nodePool_LinkedListJc(ObjectJc* othis, MemC mNodes)
{
  int nrofEntries;
  LinkedListJc* ythis;
  STACKTRC_ENTRY("ctorO_nodePool_LinkedListJc");
  if(PTR_MemC(mNodes, void) == null)
  { THROW1_s0(RuntimeException, "no memory", size_MemC(mNodes));
  }
  ythis = ctorO_LinkedListJc(othis);
  //
  init0_MemC(mNodes);
  nrofEntries = size_MemC(mNodes) / sizeof(ListMapEntryJc); 
  { /**Initialize the nodes in a queue. */
    int ii;
    ListMapEntryJc* firstEntry = PTR_MemC(mNodes, ListMapEntryJc);
    ListMapEntryJc* actEntry = firstEntry;
    for(ii=0; ii < (nrofEntries-1); ii++)
    { ListMapEntryJc* nextEntry = actEntry +1;
      actEntry->next = nextEntry;  //pointer to the next
      actEntry = nextEntry;                     //
    }
    actEntry->next = LAST_ListMapEntryJc;  //0xffffffff
    /**activate it at last action. */
    ythis->base.super.theFreeEntryPool = firstEntry;
    ythis->base.super.refFreeEntryPool = &ythis->base.super.theFreeEntryPool;
  }
  STACKTRC_LEAVE; return ythis;
}



LinkedListJc* ctorO_shareNodes_LinkedListJc(ObjectJc* othis, AbstractCollectionJc* sharedNodeContainer)
{
  LinkedListJc* ythis;
  STACKTRC_ENTRY("ctorO_shareNodes_LinkedListJc");
  ythis = ctorO_LinkedListJc(othis);
  //
  //If it is null, it is without effect.
  ythis->base.super.refFreeEntryPool = &sharedNodeContainer->theFreeEntryPool; 
  STACKTRC_LEAVE; return ythis;
}




LinkedListJc* ctorO_NodePool_LinkedListJc(ObjectJc* othis, struct NodePoolJc_t* heap)
{
  LinkedListJc* ythis;
  STACKTRC_ENTRY("ctorO_BlockHeap_LinkedListJc");
  ythis = ctorO_LinkedListJc(othis);
  //
  ythis->base.super.nodePool = heap;
  STACKTRC_LEAVE; return ythis;
}


void finalize_LinkedListJc_F(ObjectJc* othis, ThCxt* _thCxt)
{ LinkedListJc* ythis = (LinkedListJc*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("finalize_LinkedListJc_F");
  finalize_ObjectJc_F(&ythis->base.object, _thCxt);      //finalizing the superclass.
  STACKTRC_LEAVE;
}




static ListMapEntryJc* new_ListMapEntryJc(AbstractListJc* ythis)
{ ListMapEntryJc** emptyEntries = ythis->refFreeEntryPool;
  ListMapEntryJc* newEntry = null;
  STACKTRC_ENTRY("new_ListMapEntryJc");
  if(   emptyEntries != null  //the argument is given, (null if admissible) 
    && *emptyEntries != null  //the given emptyEntries are setted.
    )
  { newEntry = *emptyEntries;
    if(newEntry == LAST_ListMapEntryJc)
    { //the limit of nodes is reached.
      THROW1_s0(IllegalArgumentException, "no more shared nodes for list.", 0);
      //ASSERT(false); //Exception
    }
    else
    {
      *emptyEntries = newEntry->next;  //may be null if it is the last one.
    }
  }
  else 
  { if(ythis->nodePool == null){
      ythis->nodePool = current_NodePool_ListMapEntryJc(_thCxt);  //the first usage of list determines the blockHeap.
    }
    newEntry = alloc_ListMapEntryJc(ythis->nodePool, _thCxt);
  }
  STACKTRC_LEAVE; return newEntry;
}









/**Private method searches a new ListMapEntryJc and inializes it.
 * This isnot a standard algorithm in Java. In Java theire is ,,new LinkedList.Entry(obj, next, previous).
 * It is the same like here, but this method allocates the new Entry in the emptyEntries or in the blockHeap if there are given.
 * So no new operator or malloc is necessary (SIL 1). 
 */
static ListMapEntryJc* ctor_ListMapEntryJc(ListMapEntryJc* ythis, ObjectJc* obj, ListMapEntryJc* next, ListMapEntryJc* previous)
{ STACKTRC_ENTRY("ctor_ListMapEntryJc");
  if(ythis != null)
  { memset(ythis, 0, sizeof(ListMapEntryJc));
    //ythis->allocater = parentRef;
    SETREFJc(ythis->element, obj, ObjectJc);
    //SETREF_Jc(ythis->obj_Map, key, ObjectJc);
    ythis->next = next;
    ythis->previous = previous;
  }
  else
  { THROW1_s0(RuntimeException, "no memory", sizeof(ListMapEntryJc));
  }

  STACKTRC_LEAVE;
  return ythis;
}



/**Private method searches a new ListMapEntryJc and inializes it.
 * This isnot a standard algorithm in Java. In Java theire is ,,new LinkedList.Entry(obj, next, previous).
 * It is the same like here, but this method allocates the new Entry in the emptyEntries or in the blockHeap if there are given.
 * So no new operator or malloc is necessary (SIL 1). 
 */
#pragma warning(disable:4505) //unreferenced local function has been removed
static ListMapEntryJc* ctor_EE_ListMapEntryJc(ObjectJc* obj, ListMapEntryJc* right, ListMapEntryJc* left)
{ ListMapEntryJc* ythis = null;
  STACKTRC_ENTRY("ctor_ListMapEntryJc");
  if(ythis)
  { memset(ythis, 0, sizeof(ListMapEntryJc));
    //newEntry->allocater = parentRef;
    SETREFJc(ythis->key, obj, ObjectJc);
    //SETREF_Jc(ythis->obj_Map, key, ObjectJc);
    ythis->next = right;
    ythis->previous = left;
  }
  else
  { THROW1_s0(RuntimeException, "no memory", sizeof(ListMapEntryJc));
  }

  STACKTRC_LEAVE;
  return ythis;
}




/**Same as private java.util.LinkedList: private Entry<E> addBefore(E e, Entry<E> entry)
 */
static ListMapEntryJc* addBefore_LinkedListJc(LinkedListJc* ythis, ObjectJc* obj, ListMapEntryJc* entry, ThCxt* _thCxt)
{ ListMapEntryJc* newEntry;
  STACKTRC_TENTRY("addBefore_LinkedListJc");
  newEntry = new_ListMapEntryJc(&ythis->base.super);
  ctor_ListMapEntryJc(newEntry, obj, entry, entry->previous);   
  newEntry->allocater = &ythis->base.object;
  newEntry->previous->next = newEntry;
	newEntry->next->previous = newEntry;
	ythis->data.size++;
	ythis->base.super.modCount++;
  STACKTRC_LEAVE;
  return newEntry;
}


/**Same as java.util.LinkedList: add(obj);
 */
void add_LinkedListJcF(LinkedListJc* ythis, ObjectJc* obj, ThCxt* _thCxt)
{ addBefore_LinkedListJc(ythis, obj, &ythis->data.header, _thCxt);
}





/**Same as private java.util.LinkedList: Entry entry(int index);
 */
static ListMapEntryJc* entry_LinkedListJc(LinkedListJc* ythis, int index)
{ ListMapEntryJc* e = &ythis->data.header;
  bool bConfuse = false;

  if (index < 0 || index >= ythis->data.size)
  { STACKTRC_ENTRY("entry_LinkedListJc");
    THROW1_s0(IndexOutOfBoundsException, "Index",index);
    STACKTRC_LEAVE;
  }

  if(index < (ythis->data.size >>1))
  { //search from top
    int i;
    for (i = 0; i <= index; i++)
    { e = e->next; 
    }
  }
  else 
  { int i;
    for (i = ythis->data.size; i > index; i--)
    { e = e->previous;
    }
  }
  return e;
}






static void restitute_ListMapEntryJc(ListMapEntryJc** freePool, ListMapEntryJc* item)
{
  item->next = *freePool;
  *freePool = item;
}




/**Same as java.util.LinkedList: private E remove(Entry<E> e)
 */
static ObjectJc* remove_Entry_LinkedListJc(LinkedListJc* ythis, ListMapEntryJc* e, ThCxt* _thCxt) 
{ ObjectJc* result;
  STACKTRC_TENTRY("remove_Entry_LinkedListJc");
	if (e == &ythis->data.header)
	{ THROW1_s0(NoSuchElementException, "", 0);
  }
  result = REFJc(e->element);
	
  e->previous->next = e->next;
	e->next->previous = e->previous;
  e->next = e->previous = null;
  CLEARREFJc(e->element);
  if(ythis->base.super.refFreeEntryPool != null)
  { restitute_ListMapEntryJc(ythis->base.super.refFreeEntryPool, (ListMapEntryJc*)(e));
  } else if(ythis->base.super.nodePool != null) {
    free_ListMapEntryJc(ythis->base.super.nodePool, e, _thCxt);
  } else {
    THROW1_s0(IllegalArgumentException, "no strategie for allocation", 0);
    //free(e);
  }
	ythis->data.size--;
	ythis->base.super.modCount++;
  STACKTRC_LEAVE;
  return result;
}



ObjectJc* remove_i_LinkedListJcF(LinkedListJc* ythis, int index, ThCxt* _thCxt)
{ ListMapEntryJc* entry = entry_LinkedListJc(ythis, index);
  return remove_Entry_LinkedListJc(ythis, entry, _thCxt);
}















//METHOD_C LinkedListJc* newPool_ListMapEntryJc(int nrofEntries)
/**deprecated, see ctorO_nodePool_LinkedListJc. */
void initEntryPool_LinkedListJc(LinkedListJc* ythis, MemC mem, ThCxt* _thCxt)
{ //int bytes = sizeof(LinkedListJc) + sizeof(ListMapEntryJc) * nrofEntries;
  //void* address;
  //ListMapEntryJc* entries;
  int nrofEntries;
  STACKTRC_TENTRY("newPool_ListMapEntryJc");
  //address = (ListMapEntryJc*)malloc(bytes);
  if(PTR_MemC(mem, void) == null)
  { THROW1_s0(RuntimeException, "no memory", size_MemC(mem));
  }
  init0_MemC(mem);
  nrofEntries = size_MemC(mem) / sizeof(ListMapEntryJc);
  { int ii;
    ListMapEntryJc* actEntry = PTR_MemC(mem, ListMapEntryJc);
    ythis->base.super.theFreeEntryPool = actEntry;
    ythis->base.super.refFreeEntryPool = &ythis->base.super.theFreeEntryPool;
    for(ii=0; ii < (nrofEntries-1); ii++)
    { ListMapEntryJc* nextEntry = actEntry +1;
      actEntry->next = nextEntry;  //pointer to the next
      actEntry = nextEntry;                     //
    }
    //the last entry has entries->rigth_Map = 0xffffffff!
    actEntry->next = LAST_ListMapEntryJc;
  }
  STACKTRC_LEAVE;
}



void shareEntryPool_LinkedListJc(LinkedListJc* ythis, LinkedListJc* srcShare, ThCxt* _thCxt)
{ /*NOTE: the srcShare have to be that linkedlist holding the entryPool.
   * It may be possible to use a always shared List for reference of entry pool,
   * but the user should use the original List.
   */
  /*NOTE: *srcShare->data.theFreeEntryPool may contain null. It is possible to call initEntryPool later.
   */
  ythis->base.super.refFreeEntryPool = &srcShare->base.super.theFreeEntryPool; 
}


extern_C ClassJc const reflection_ListItr_LinkedListJc;
  

ListItr_LinkedListJc* ctorO_ListItr_LinkedListJc(struct LinkedListJc_t* outer, ObjectJc* othis, ThCxt* _thCxt)
{ ListItr_LinkedListJc* ythis = (ListItr_LinkedListJc*)othis;
  STACKTRC_TENTRY("ctorO_ListItr_LinkedListJc");
  ctorc_ObjectJc(othis);
  checkConsistence_ObjectJc(othis, sizeof(ListItr_LinkedListJc), &reflection_ListItr_LinkedListJc, _thCxt);
  ythis->outer = outer;
  ythis->expectedModCount = 0;
  ythis->lastReturned = null;
  ythis->next = null;
  ythis->nextIndex = 0;
  STACKTRC_LEAVE;
  return ythis;
}


#if defined(__CPLUSPLUS_Jcpp) && defined(__cplusplus)
  class IteratorJcpp* iteratorCpp_LinkedListJcF(LinkedListJc* ythis, IteratorJcpp* instanceToUse)
  { //if(!instanceof(instanceToUse, REFLECTION_ListImp_LinkedListJcpp)
    //{  THROW(ClassCastException, "fault instance", 0);
    ListItr_LinkedListJcpp* iter = static_cast<ListItr_LinkedListJcpp*>(instanceToUse);
    iter->reinit(ythis);
    return iter;
  }
#endif //__CPLUSPLUS_Jcpp



bool checkForComodification_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis)
{ //TODO
  return false;
}  


void reinit_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis, struct LinkedListJc_t* list)
{ ythis->outer = list;
  ythis->expectedModCount = list->base.super.modCount;
  ythis->next = list->data.header.next;
  ythis->lastReturned = &list->data.header;
  ythis->nextIndex = 0;
}



bool hasNext_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis, ThCxt* _thCxt)
{ return ythis->nextIndex != ythis->outer->data.size;
}


ObjectJc* next_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis, ThCxt* _thCxt)
{ ObjectJc* retVal;
  checkForComodification_ListItr_LinkedListJcF(ythis);
  if(ythis->nextIndex == ythis->outer->data.size)
  { STACKTRC_TENTRY("next_ListItr_LinkedListJcF");
    THROW1_s0(NoSuchElementException, "", 0); 
    STACKTRC_LEAVE;
  }
  ythis->lastReturned = ythis->next;
  ythis->next = ythis->next->next;
  ythis->nextIndex +=1;
  
  retVal = REFJc(ythis->lastReturned->element);
  return retVal;
}


void remove_ListItr_LinkedListJcF(ListItr_LinkedListJc* ythis, ThCxt* _thCxt)
{ ListMapEntryJc* lastNext;
  STACKTRC_TENTRY("remove_ListItr_LinkedListJcF");
  
  checkForComodification_ListItr_LinkedListJcF(ythis);
  lastNext = ythis->lastReturned->next;
  TRY { remove_Entry_LinkedListJc(ythis->outer, ythis->lastReturned, _thCxt);}_TRY
  CATCH(NoSuchElementException, e) 
  { THROW1_s0(IllegalStateException, "", 0);
  }
  END_TRY
  if (ythis->next == ythis->lastReturned)
  { ythis->next = lastNext;
  }
  else
  { ythis->nextIndex--;
    ythis->lastReturned = &ythis->outer->data.header;
    ythis->expectedModCount++;
	}
  STACKTRC_LEAVE;
}



#if defined(__CPLUSPLUS_Jcpp) && defined(__cplusplus)

ListItr_LinkedListJcpp::ListItr_LinkedListJcpp(LinkedListJc* outer)
{ ListItr_LinkedListJc* ythis = this;
  object.ownAddress = null;  //to force intialization.
  ctorO_ListItr_LinkedListJc(outer, &ythis->object, null); 
}


#endif //__CPLUSPLUS_Jcpp

#include <emC/Jc/genRefl/AbstractListJc.crefl>
#include <emC/Jc/genRefl/LinkedListJc.crefl>
#include <emC/Jc/genRefl/ListJc.crefl>
#include <emC/Jc/genRefl/ListMapEntryJc.crefl>
