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
 * 2008-04-22: JcHartmut new: routine to test the consistence of stacktrace.
 * 2007-07-00: JcHartmut creation
 *
 ****************************************************************************/
#ifndef __ListJc_h__
#define __ListJc_h__



#include "emC/Jc/ObjectJc.h"
#include "emC/Jc/ReflectionJc.h"  //includes pkgSystem/Object.h, pkgSystem/String.h



/*@CLASS_C ListJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct ListJc_t
{ ObjectJc object;
}ListJc;

extern_C ClassJc const reflection_ListJc;



typedef void (*Method_add_i_List)(ListJc* ythis, int ix, ObjectJc* obj);

typedef int MT_size_ListJc(ListJc* ythis, ThCxt* _thCxt);
typedef struct IteratorJc_t* MT_iterator_ListJc(ListJc* ythis, ThCxt* _thCxt);

/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Vtbl_ListJc_t
{ Vtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
  MT_size_ListJc* size;
  MT_iterator_ListJc* iterator;
} Vtbl_ListJc;



#define size_ListJc(YTHIS, THC) ((Vtbl_ListJc*)getVtbl_ObjectJc(&(YTHIS)->object, &reflection_ListJc))->size(YTHIS, THC)
#define iterator_ListJc(YTHIS, THC) ((Vtbl_ListJc*)getVtbl_ObjectJc(&(YTHIS)->object, &reflection_ListJc))->iterator(YTHIS, THC)



/*@CLASS_CPP ListJcpp @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#if defined(__CPLUSPLUS_Jcpp) && defined(__cplusplus)

class  ListJcpp: public ObjectJcpp
{
  public:

  virtual class ListIterator* listIterator(int index)=0;
  virtual class ListIterator* listIterator()=0;
  virtual class Iterator* iterator()=0;
  virtual void add(int ix, ObjectJcREFP obj)=0;
  virtual void add(ObjectJcREFP obj)=0;
  virtual ObjectJcREFP set(int index, ObjectJcREFP element)=0;


  virtual void clear()=0;
  virtual ObjectJcREFP remove(int ix)=0;
  virtual bool remove(ObjectJcREFP)=0;
  virtual ObjectJcREFP removeFirst()=0;
  virtual ObjectJcREFP removeLast()=0;
  virtual int size()=0;
  virtual ObjectJcREFP get(int ix)=0;
  virtual int indexOf(ObjectJcREFP)=0;
  //int indexOf(Object& obj){ return indexOf(&obj); }
  virtual bool isEmpty()=0;
};

#endif  //__CPLUSPLUS_Jcpp




/*@CLASS_C IteratorJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct IteratorJc_t
{ ObjectJc object;
}IteratorJc;

extern_C ClassJc const reflection_IteratorJc;



typedef bool MT_hasNext_IteratorJc(IteratorJc* ythis, ThCxt* _thCxt);
typedef ObjectJc* MT_next_IteratorJc(IteratorJc* ythis, ThCxt* _thCxt);
typedef void MT_remove_IteratorJc(IteratorJc* ythis, ThCxt* _thCxt);

typedef struct Vtbl_IteratorJc_t
{ Vtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
  MT_hasNext_IteratorJc* hasNext;
  MT_next_IteratorJc* next;
  MT_remove_IteratorJc* remove;
} Vtbl_IteratorJc;

#define hasNext_IteratorJc(YTHIS, THC) ((Vtbl_IteratorJc*)getVtbl_ObjectJc(&(YTHIS)->object, &reflection_IteratorJc))->hasNext(YTHIS, THC)
#define next_IteratorJc(YTHIS, THC) ((Vtbl_IteratorJc*)getVtbl_ObjectJc(&(YTHIS)->object, &reflection_IteratorJc))->next(YTHIS, THC)
#define remove_IteratorJc(YTHIS, THC) ((Vtbl_IteratorJc*)getVtbl_ObjectJc(&(YTHIS)->object, &reflection_IteratorJc))->remove(YTHIS, THC)


#endif  //__List_Jc_h__
