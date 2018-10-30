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
 * @content This file is a sample for the users CRuntimeJavalike_SysConventions.h.
 * The user may move or copy this file in its own file folder known by the include path
 * and modify it. In the comments the possibilities of modifications are explained.
 * @author Jchartmut www.vishia.org
 * @version 1.0
 * list of changes:
 * 2006-07-23: JcHartmut creation
 * 2006-09-24: JcHartmut modification
 * 2013-12-18: JcHartmut add BlockHeap_emC division
 *
 ****************************************************************************/
#ifndef __fw_SysConventions_h__
#define __fw_SysConventions_h__

#include <os_types_def.h>
	

//#define __CPLUSPLUSJcpp
#undef __CPLUSPLUSJcpp



/** If this define is setted, the TRY, CATCH and THROW makros use the C++ keywords
  * try, throw and catch. All sources, also the *.c-Sources of the CRuntimeJavalike,
  * must be compiled with a C++-Compiler.
  *
  * If the macro is not setted, the TRY, CATCH and THROW makros use
  * the longjmp version. See fw_Exception.h. It is also possible to use longjmp
  * in a C++ environment,
  * but destructors of local stack instances in skipped subroutines are ignored.
  * It must be secured that no critical destructors are used, or a FINALLY is used there.
  */
#ifdef __cplusplus
  #define __TRYCPPJc
#else
  #undef __TRYCPPJc
#endif

/**Under Test conditions, the check of Stacktrace consistence should be activated. 
 * Because a forgotten STACKTRC_LEAVE-macro call won't be detected else,
 * and the stacktrace is corrupt for later usage.
 * Deactivate this macro in release versions.
 */
#ifdef _DEBUG
  #define TEST_STACKTRCJc 
#else
  #undef TEST_STACKTRCJc
#endif	








/*@DEFINE BlockHeap_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Usage of the BlockHeap management or not and define the size of a block.
 * The size of a normal block in all BlockHeaps are the same. The size must be (!) a power of 2.
 */
#undef USE_BlockHeap_emC
#undef SIZEBLOCK_BlockHeap_emC
//#define SIZEBLOCK_BlockHeap_emC 0x400

#define NO_DYNAMICALLY_MEMORY

/**unused...TODO*/
//#define SMALL_DYNAMICALLY_MEMORY
//#define USE_DYNAMICALLY_MEMORY


/*@DEFINE EnhancedRefJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Macro to define the Types <TYPE>REF and <TYPE>REFP which can be used for enhanced references.
 * If the BlockHeap or adequate system is used, an enhanced reference
 * is a struct containing the pointer and an additional value. 
 * The usage of the macro is necessary to support both, enhanced and simple references in the same sources.
 * Note: The usage of the macro should be terminated with a colon. Example:
 * ,,DEFINE_EnhancedRefJc(MyType);,,
 * @param TYPE the identifier of the TYPE which should be referenced.
 */
#define DEFINE_EnhancedRefJc(TYPE) typedef struct TYPE##REF_t{struct TYPE##_t* ref;  int32 refbase; }TYPE##REF;  typedef TYPE##REF* TYPE##REFP

/**Macro to initialize the value of a defined reference staticly to null. */
#define NULL_REFJc { null, 0}


/**Makro to set a enhanced reference, able to use in primary sources for enhanced references or not enhanced references or C++. 
 * Note: The reference itself will be set an extra assignment tests the type by compiler.
 * Implementation note: The method ,,setBackRefIdxMtblJc(...),, checks whether the reference is used yet, it frees it first.
 * Calling ,,clearBackRefJc(...),, is not necessarry.
 */ 
#define SETREFJc(REF, OBJP, REFTYPE) { clearBackRefJc(&(REF)); (REF).ref = OBJP; setBackRefJc(&(REF), (REF).ref); }
//NOTE: important: do not use OBJP more as one, because it may be a complex method.
//therefore the following variant is false:
//#define SETREFJc(REF, OBJP, REFTYPE) { setBackRefIdxMtblJc(&(REF).refbase, OBJP, null); (REF).ref = OBJP; }
//#define SETREFJc(REF, OBJP, REFTYPE) { setBackRefIdxMtblJc(&(REF).refbase, OBJP, &reflection_##REFTYPE); (REF).ref = (REFTYPE*)OBJP; }


#define CLEARREFJc(REF) { clearBackRefJc(&(REF)); (REF).ref = null; }

/**Makro to set a enhanced reference to null. 
 * Note: because the makro should write in form
 *   CLEAR_REF(dst, value);
 * the ending semicolon is set outside the makro.
 * @param REF The reference as value
 */
#define CLEAR_REFJc(REF) clearBackRefJc(&(REF)); (REF).ref = null
     

/**Macro to access to an enhanced reference.
 * @param REF The enhanced reference-instance.
 * @return The reference value. 
 */
#define REFJc(REF) (REF).ref








#define nrofBit_EnhancedRefJc 32


/**Right shifted Bits representing the index of the backpointer from an object to the reference
 * inside the type ObjectRefValuesJc in enhanced references.
 * If this define is setted, the enhanced references are used.
 * This mask should be the left bits after mThreadContext__StringJc, mNonPersists__StringJc, mLength__StringJc
 * because Strings are used as enhanced references too!
*/
#define mRef_EnhancedRefJc              0xffff0000




/**Macro to define the reflection of the enhanced reference of any type, able to use in a C-File.
 * @param TYPE the type of the reference.
 */
#define DEFINE_REFLECTION_REF(TYPE) \
  extern_C struct ClassJc_t const reflection_##TYPE; \
  extern_C struct ClassJc_t const reflection_##TYPE##REF; \
  const struct Reflection_Fields_##TYPE##REF_t{ ObjectArrayJc head; FieldJc data[2];} reflection_Fields_##TYPE##REF = \
  { CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_##TYPE##REF) \
  , { { "refbase", 0 , &reflection__intJc, 0, 0, 0, &reflection_##TYPE##REF } \
    , { "ref", 0 , &reflection_##TYPE##, 0, 0, 0, &reflection_##TYPE##REF } \
  } }; \
  const ClassJc reflection_##TYPE##REF =\
  { CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_##TYPE##REF, null) \
  , "Ptr", 0, sizeof(TYPE##REF), (FieldJcArray const*)&reflection_Fields_##TYPE##REF \
  }








/*@DEFINE xxx @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


//#define PC_SIM
//#ifndef TEST_MODULE
//  #define TEST_MODULE
//#endif

#define SIMULINK



/* Maximal length of path in a FileIoJc-structure.
 * The minimal value is defined in os_file.h with kMaxPathLength_OS_FileDescription.
 * That is a minimal length for less systems. The struct FileIOJc has an additional
 * char[]-buffer after the OS_FileDescription-structure, which stores the path.
 * This parameter is the max. length, it have to be 
 * greater than kMaxPathLength_OS_FileDescription (=24).
 */
#define kMaxPathLength_FileJc 500

/** Define the length of namefield in Reflection*/
#define kLengthNAME_CLASS_ReflectionJc 32
#define kLengthNAME_FIELD_ReflectionJc 30
#define kLengthNAME_METHOD_ReflectionJc 32

#endif  // __fw_SysConventions_h__
