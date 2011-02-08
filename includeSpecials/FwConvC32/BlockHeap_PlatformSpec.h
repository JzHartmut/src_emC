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
 * @content: All declarations to use from user level to work with BlockHeapJc
 * for References of ObjectJc and derivated classes for C-language.
 * The references are used for garbage collection and virtual methods in C.
 *
 * @author JcHartmut www.vishia.org
 *
 ****************************************************************************/
#ifndef __ObjectRefJc__h
#define __ObjectRefJc__h

/**NOTE: This file is also included in ObjectJc.h, but in this case the __ObjectJc__ is set.
 */
#ifndef __ObjectJc_h__
  #include "ObjectJc.h"
#endif

#include <Fwc/fw_MemC.h>

/**Usage of the BlockHeap management or not and define the size of a block.
 * The size of a normal block in all BlockHeaps are the same. The size must be (!) a power of 2.
 */
#define USE_BlockHeapJc
#define SIZEBLOCK_BlockHeapJc 0x400
//#undef SIZEBLOCK_BlockHeapJc

//#define NO_DYNAMICALLY_MEMORY

/**unused...TODO*/
#define SMALL_DYNAMICALLY_MEMORY
//#define USE_DYNAMICALLY_MEMORY

/**It can be used as a  part of a struct, union or typedef. */
#define STRUCT_REFJc(TYPE) { ObjectRefValuesJc refbase; TYPE* ref; }

/** Bits representing the start index of a interface inside a C-like-virtual table
    inside the type ObjectRefValuesJc in enhanced references.
  * If this define is setted, the enhanced references are used.
*/
#define mIdxMtbl_ObjectJc              0x0000ffff

/** Nr of bitposition to shift the bits to the right, it should be complemental to mIdxMtbl_ObjectRef*/
#define kBitBackRef_ObjectJc 16
//#undef kBitBackRef_ObjectJc
/** Bits of index of backward reference, justified after shifting. */




/** Right shifted Bits representing the index of the backpointer from an object to the reference
    inside the type ObjectRefValuesJc in enhanced references.
  * If this define is setted, the enhanced references are used.
*/
#define mBackRef_ObjectJc              0xffff0000
//#undef mBackRef_ObjectJc




struct StringBufferJc_t;

/**This file is included inside ObjectJc.h only if the appropriate defines
  , #if defined(mBackRef_ObjectJc) || defined(mIdxMtbl_ObjectJc)
  are setted in the file ,,CRuntimeJavalike_SysConventions.h,,.
  In this cases the enhanced references are used.

  This file should not be included directly from user.
*/

/*@CLASS_C ObjectJcREF @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/




/**Makro to set a enhanced reference. 
 * Note: because the makro should write in form
 *   ASSIGN_REF(dst, value);
 * the ending semicolon is set outside the makro.
 * @param REF The reference as value
 * @param OBJP pointer to the instance (a pointer) 
 */
#define xxxASSIGN_REFJc(REF, OBJP) if((REF).ref != null) clearBackRefJc(&((REF).refbase)); (REF).ref = (OBJP); setBackRefJc(&(REF).refbase, (REF).ref)



/**Makro to set an StringJc, it may be an enhanced reference. 
 * Note: because the makro should write in form
 *   SETREF_STRINGJc(dst, value);
 * the ending semicolon is set outside the makro.
 *
 * Implemenation note: A StringJc is defined as OS_ValuePtr, see ,,Fwc/fw_String.h,,. That definition is presumed here. 
 * @param DST The dst StringJc per reference.
 * @param STR The string as value 
 */
#define xxxSETREF_StringJc(DST, STR) if((DST)->value__ != null) clearBackRefJc(&(DST)->value__); *(DST) = STR; setBackRefJc(&(DST)->value__, (STR).ptr__)
#define xxxASSIGN_STRINGJc(REF, STR) if((REF).ref != null) clearBackRefJc(&((REF).value__)); REF = STR; setBackRefJc(&(REF).value__, (STR).ptr__)

     

#include <Fwc/fw_Exception.h>
#include <Blockheap/BlockHeapJc.h>


#endif //__ObjectRefJc__h
