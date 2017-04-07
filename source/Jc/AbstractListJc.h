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
 * list of changes:
 * 2005-05-00: JcHartmut creation
 *
 ****************************************************************************/
#ifndef JAVACPP_ABSTRACTLIST_H_
#define JAVACPP_ABSTRACTLIST_H_

#ifndef JAVACPP_JcLASS_H_
  #include "Jc/ReflectionJc.h"  //includes pkgSystem/Object.h, pkgSystem/String.h
#endif

#ifndef JAVACPP_LIST_H_
  #include "Jc/ListJc.h"  //includes pkgSystem/Object.h, pkgSystem/String.h
#endif


typedef struct AbstractCollectionJc_t
{ ObjectJc object;
  //int nSize;
  /**from java.util.AbstractList: */
  int modCount;

  /**Access to a pool of free Entries to link, getted from a BlockHeapJc.
   * This attribute may be null if no determined blockHeap should be used.
   * If both, blockHeap and freeEntryPool are null, the standard BlockHeapJc is used.
   */
  struct NodePoolJc_t* nodePool;
  
  /**Access to a pool of free Entries to link, getted from a fix ListMapEntryJc-pool.
   * This attribute may be null if no fix pool should be used.
   */
  struct ListMapEntryJc_t** refFreeEntryPool;

  /**The pool of free Entries to link, setted with method initEntryPool_LinkedListJc().
   * This attribute is only used for the LinkedList holding the freeEntryPool.
   */
  struct ListMapEntryJc_t* theFreeEntryPool;
} AbstractCollectionJc;


/**TODO define AbstractListJc. */
#define AbstractListJc AbstractCollectionJc



#ifdef __JcPLUS_Jc_RUNTIMEJAVALIKE__

/*
class  AbstractList: public Object_Jc, public List
{ protected:
  int nSize;

  //public: operator Object_Jc*(){ return this; } //always based on Object
  public:
  virtual class ListIterator* listIterator(int index){ return 0;}
  virtual class ListIterator* listIterator(){ return 0;}
  virtual class Iterator* iterator(){ return 0;}
  virtual void add(int ix, Object_r* obj){}
  virtual void add(Object_r* obj){}
  virtual Object_r* set(int index, Object_r* element)=0;
  virtual void clear(){}
  virtual Object_r* remove(int ix){ return 0;}
  virtual bool remove(Object_r*){ return 0; }
  virtual Object_r* removeFirst(){ return 0; }
  virtual Object_r* removeLast(){ return 0; }
  virtual Object_r* get(int ix){ return 0; }
  virtual int indexOf(Object_r*){ return 0; }
  //int indexOf(Object& obj){ return indexOf(&obj); }



  int size(){ return nSize; }
  bool isEmpty(){ return( nSize==0 ? true: false); }
};
//typedef Template_ref <AbstractList> AbstractList_ref;
*/
#endif //__JcPLUS_JcRUNTIMEJAVALIKE__


#endif
