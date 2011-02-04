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
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#ifndef __ComparatorJc_h__
#define __ComparatorJc_h__


#include "Jc/ObjectJc.h"

/*@CLASS_C ComparatorJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct ComparatorJc_t
{ ObjectJc object;
}ComparatorJc;

  
/**C-Variant of java.util.Comparator. The data are the same as ObjectJc, but the methods. */

/**compares 2 instances of the implemented class. See [[java.util.Comparator.compare(T,T)]].
 * @return a negative integer, zero, or a positive integer as the first argument is less than, equal to, or greater than the second.
 */
typedef int MT_compare_ComparatorJc(ComparatorJc* ythis, const void* o1, const void* o2);
//typedef int MT_compare_ComparatorJc(ObjectJc* ythis, const void* o1, const void* o2);

/**compares 2 instances of the implemented class. See [[java.util.Comparator.equals(T,T)]].
 * @return true only if the specified object is also a comparator and it imposes the same ordering as this comparator.
 */
typedef bool MT_equals_ComparatorJc(ComparatorJc* ythis, const void* o1, const void* o2);
//typedef bool MT_equals_ComparatorJc(ObjectJc* ythis, const void* obj);

  /**The call of virtual methods are simplified in user sources and equal writeable using C o C++-concepts,
   * but the realization of dynamic call is implemented with Reflection data and the virtual table.
   */
  #define compare_ComparatorJc(REF, O1, O2) (((MT_compare_ComparatorJc*)((REF).ref->reflectionClass->mtbl[0 + (REF).refbase & mIdxMtbl_ObjectJc])) ((REF).ref, O1, O2))
  #define equals_ComparatorJc(REF, O1, O2)  (((MT_equals_ComparatorJc*) ((REF).ref->reflectionClass->mtbl[1 + (REF).refbase & mIdxMtbl_ObjectJc])) ((REF).ref, O1, O2))


/**The MethodTable (virtual table) of the Comparator-Methods have to be embedded in the jump Table of a implemented class.*/
typedef struct Mtbl_ComparatorJc_t
{ MT_compare_ComparatorJc*   compare;
  MT_equals_ComparatorJc*   equals;
} Mtbl_ComparatorJc;



/*@CLASS_CPP ComparatorJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#if defined(__CPLUSPLUS_Jcpp) && defined(__cplusplus)


//TYPEDEF_INTERFACE_Jcpp(Comparator_Jc)
typedef class Comparator_Jcpp* Comparator_JcppRef; 
typedef class Comparator_Jcpp* Comparator_JcppRefp; 

class  ComparatorJcpp: public ObjectifcBaseJcpp 
{ public:
  /**Compare two instances. The type may be anything, the right implementation should know it.
   */
  virtual int compare(const void* o1, const void* o2)=0;
  virtual bool equals(const void* o1, const void* o2)=0;
};

#else

  //only C: If a routine should use the C++ class in C++, in C they should use the C-equivalent.
  #define ComparatorJcpp ComparatorJc


#endif  //__CPLUSPLUS_Jcpp





#endif  //__ComparatorJc_h__
