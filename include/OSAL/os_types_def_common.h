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
  #define INLINE_C static
#endif
#endif//__NoReflection__

#define _INIT0_ = {0}

/**Presaves NaN for positiv values >0.01 */
#define DIVP01(divident, divisor) (divisor > 0.01f ? divident/divisor : divident/0.01f);


/**Presaves NaN for values >0.01 */
#define DIV01(divident, divisor) (fabsf(divisor) > 0.01f ? divident/divisor : divident/0.01f);


/**An instance which contains null-values. */
extern_C OS_PtrValue null_OS_PtrValue;

/**This Define is used to prevent reflection generation from any part of struct. */
#define ReflectionHidden 

/*@CLASS_C PtrVal @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Defines Struct_charPtr_Value.
 */
typedef PtrVal_TYPE(PtrVal_int8, int8);

typedef PtrVal_TYPE(PtrVal_int16, int16);

typedef PtrVal_TYPE(PtrVal_int32, int32);

typedef PtrVal_TYPE(PtrVal_int64, int64);

typedef PtrVal_TYPE(PtrVal_float, float);

typedef PtrVal_TYPE(PtrVal_double, double);

/*@CLASS_C float_complex @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
typedef struct float_complex_t{
  float re, im;
} float_complex;

/*@CLASS_C double_complex @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
typedef struct double_complex_t{
  double re, im;
} double_complex;

#endif  // __os_types_def_common_h__
