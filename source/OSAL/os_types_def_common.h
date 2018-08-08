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
 * @content Definitions for basics, which maybe identical for all operation systems and compilers,
 * This file is include in <os_types_def.h>. Because that file is able to adjust in a project specific way,
 * the inclusion of this file can be changed. In that way the definitions in this file can be adapted.
 * Therefor it is not recommended to include this file directly in a users file. 
 *
 * @author Hartmut Schorrig
 */
#ifndef __os_types_def_common_h__
#define __os_types_def_common_h__


//plattformunabhaengige Ergaenzungen
//folgende Typen sind besser schreib- und lesbar
#define ushort unsigned short int
#define uint unsigned int
#define ulong unsigned long int


#define INLINE_Jc INLINE_Fwc

/**This macro guarantees that a boolean true value is represented by the value 1. Most of compilers realizes that, 
 * but it is not guaranteed in C or C++ standard.
 * The value 1 is necessary to represent a boolean value in an integer or bitfield in a defined kind.
 * The long variant guarantees it independent of the compiler. The short variant can be used if the compiler guarantees 
 * a value of 1 for boolean true.
 */
//NOTE: it should defined in compl_adaption.h because it may depend of compiler properties
//#define OSAL_bool1(COND) ((COND) ? 1 : 0) 
//#define OSAL_bool1(COND) (COND)


 
 /**Macros for C-labeling in C++-compilation:
 * *extern_C replaces a simple 'extern' with 'extern "C"' for C++
 * *C_TYPE creates a 'extern "C"' in C++ but nothing in C, for example used for 'extern "C" typedef method()'
 * *METHOD_C is deprecated, used for METHOD prototype declaration. 
 * Both extern_C or C_TYPE can be used there because a 'extern' designation in C is optional there.
 * extern_C_BLOCK_ and _END_extern_C_BLOCK can be written at start and end of a header-block
 *
 * This macros can be set to the C-form in C++ too, then all labels are created in the C++-manner. 
 * Then all sources should be compiled with C++, use only C++-libraries. 
 */
//NOTE: This part cannot be parsed by Cheader.zbnf because it defines the special keywords itself.
#ifndef __NoReflection__
#ifdef __cplusplus
  #define extern_C extern "C"
  #define C_TYPE extern "C"
  #define METHOD_C extern "C"
  #define extern_C_BLOCK_ extern "C" { 
  #define _END_extern_C_BLOCK } 
  #define INLINE_C inline
  //#define METHOD_C
#else
  #define extern_C extern
  #define C_TYPE
  #define METHOD_C
  #define extern_C_BLOCK_ 
  #define _END_extern_C_BLOCK 
  #ifndef INLINE_C  //may be defined in compl_adaption.h
    #define INLINE_C static  //a compiler may optimize static routines.
  #endif
#endif
#endif//__NoReflection__

#ifndef __cplusplus
  //If C-compiling is used, define the C++-keywords for C
  //NOTE: define bool false and true in the compl_adaption.h because it is possible that any other system file defines that too.
  //#define bool int
  //#define false 0
  //#define true (!false)
#endif



#define _INIT0_ = {0}

/**Presaves NaN for positiv values >0.01 */
#define DIVP01(divident, divisor) (divisor > 0.01f ? divident/divisor : divident/0.01f);


/**Presaves NaN for values >0.01 */
#define DIV01(divident, divisor) (fabsf(divisor) > 0.01f ? divident/divisor : divident/0.01f);


/**This Define is used to prevent reflection generation from any part of struct. */
#define ReflectionHidden 

/*@CLASS_C PtrVal @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Defines the struct type PtrVal_MemUnit.
 * This type provides basic working with memory allocation.
 * The Problem in C is: a Pointer to memory does not contain the information about the amount of memory.
 * It is a simple pointer only, often a void*. How many bytes are there, it is unknown.
 * The struct MemC contains the pointer to memory as MemUnit type and the amount of memory.
 * This struct is based on the
 * A PtrVal_MemUnit struct contains both:
 * * The pointer to the data as memory address unit.
 * * The size of data in memory.
 */
typedef OS_PtrVal_DEF(PtrVal_MemUnit, MemUnit);

/**Compatibility with older typedef of OS_PtrValue. */
#define OS_PtrValue PtrVal_MemUnit


/**An instance which contains null-values. */
extern OS_PtrValue null_OS_PtrValue;



/**Defines Struct_charPtr_Value.
 */
typedef OS_PtrVal_DEF(PtrVal_int8, int8);

typedef OS_PtrVal_DEF(PtrVal_int16, int16);

typedef OS_PtrVal_DEF(PtrVal_int32, int32);

typedef OS_PtrVal_DEF(PtrVal_int64, int64);

typedef OS_PtrVal_DEF(PtrVal_float, float);

typedef OS_PtrVal_DEF(PtrVal_double, double);

/*@CLASS_C Fwc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


#define max_Fwc(A, B) ( (A) > (B) ? (A) : (B) )
#define min_Fwc(A, B) ( (A) < (B) ? (A) : (B) )
#define abs_Fwc(A) ( (A) <0 ? -(A) : (A) )

//#define fmax(A, B) ( (A) > (B) ? (A) : (B) )
//#define fmin(A, B) ( (A) < (B) ? (A) : (B) )

//#ifdef __cplusplus
//#define max(A, B) ( (A) > (B) ? (A) : (B) )
//#define min(A, B) ( (A) < (B) ? (A) : (B) )
//#endif

/*@CLASS_C float_complex @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef DEFINED_float_complex
typedef struct float_complex_t{
  float re, im;
} float_complex;
#endif

/*@CLASS_C double_complex @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef DEFINED_double_complex
typedef struct double_complex_t{
  double re, im;
} double_complex;
#endif


//NOTE: all NAN makros should be defined in fw_assert.h which is platform-depending.



#endif  // __os_types_def_common_h__
