#ifndef HGUARD_compl_adaption
#define HGUARD_compl_adaption
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
 * 4) But the LPGL is not appropriate for a whole software product,
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
 * @content Definition of basicly types adequate to the operation system, cpu and compiler.
 * This file should be used with the Microsoft visual Studio 2015 or 2017 compiler 
 * and generated Simulink Sfunction for 64 bit.
 *
 * @author Hartmut Schorrig
 *************************************************************************************************/


//uncomment that to check whether this file is used for include:
//#error used_emC_cc_SmlkSfunc

//The following switch select the operation system in some sources.
#define __OS_IS_WINDOWS__

//The following switch select the compiler in some sources.
#define __COMPILER_IS_MSC15__
#define __COMPILER_IS_MSVC__

#define __Simulink__
#define PC_SIMULATION
#define __Smlk_Simulation__
#ifndef TEST_MODULE
  #undef TEST_MODULE
#endif







/**Some warnings should be disabled in default, because there are not the source of errors,
 * but present in normal software development.
 */
//#pragma warning(disable:4204) //nonstandard extension used : non-constant aggregate initializer TODO prevent






/**Some warnings should be disabled in default, because there are not the source of errors,
 * but present in normal software development.
 */
//#pragma warning(disable:4204) //nonstandard extension used : non-constant aggregate initializer TODO prevent


//C++
//#pragma warning(disable:4100) //unused argument

//C++
#pragma warning(disable:4068) //unknown pragma

#pragma warning(disable:4100) //4100: 'type' : unreferenced formal parameter
#pragma warning(disable:4127) //conditional expression is constant
#pragma warning(disable:4189) //local variable is initialized but not referenced
#pragma warning(disable:4201) //nonstandard extension used : nameless struct/union
#pragma warning(disable:4214) //nonstandard extension used : bit field types other than int
#pragma warning(disable:4244) //conversion from 'int' to 'char', possible loss of data specific for energy inits
#pragma warning(disable:4268) //'const' static/global data initialized with compiler generated default constructor fills the object with zeros
#pragma warning(disable:4310) //cast truncates constant value
#pragma warning(disable:4505) //unreferenced local function has been removed
#pragma warning(disable:4514) //unreferenced inline function has been removed
//#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4786) //identifier was truncated to '255' characters in the browser information
#pragma warning(disable:4996) //'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

#pragma warning(error:4002) //too many actual parameters for macro
#pragma warning(error:4003) //not enough actual parameters for macro
#pragma warning(error:4020) //too many actual parameters
//#pragma warning(disable:9025) //Command line warning D9025 : overriding '/EHs' with '/EHa'


/**Defintion of bool, false, true for C usage. */
#ifdef __cplusplus
  #define INLINE_emC inline
  #define CONSTMember_emC
#else
  /**For C-compiling: build static routines, maybe the compiler optimized it to inline. */
  #define CONSTMember_emC const
  /**For C-compiling: build static routines, maybe the compiler optimized it to inline. 
     It is for Visual Studio 6 from 1998. The C99-Standard declares inline features.
  */
  //#define inline static
  //#define INLINE_emC static
  #define INLINE_emC inline
  //If C-compiling is used, define the C++-keywords for C
  #define bool int
  #undef false
  #undef true
  #define false 0
  #define true (!false)
#endif
//#include the standard header from Visual studio firstly. 
//stdint.h defines int8_t etc. via typedef. 
//Because pragma once (or guard) the content of the files are not included again.
//They should be included firstly to cover its typedef by the typedef of simulink.
#include <stdint.h>  //C99-int types
#include <limits.h>  //proper to C99

//After including <stdint.h> the simulink header for standard types are included.
//The define an simulink-specific world of fix width integer types. int32_T, uint32_T etc.
#ifndef RTWTYPES_H  //Smlk defines the same struct twice, in tmwtypes.h and rtwtypes.h
  //prevent including rtwtypes.h because for PC platform tmwtypes.h contains the same proper definitions.
  #define RTWTYPES_H
  //#include <rtwtypes.h>  //from simulink
  #ifndef __TMWTYPES__  //Smlk defines the same struct twice, in tmwtypes.h and rtwtypes.h
    #include <tmwtypes.h>  
  #endif
#endif

//Both type worlds are present yet.
//Now define the C99 types via the simulink types via defined.
//Therewith it is the simulink typedef. The typedef of <stdint.h> are covered. 

#define uint      unsigned int
#define ulong     unsigned long

#define int8      int8_T
#define uint8     uint8_T
#define int8_t    int8_T
#define u_int8_t  uint8_T
#define uint8_t   int8_T

#define int16     int16_T
#define uint16    uint16_T
#define int16_t   int16_T
#define u_int16_t uint16_T
#define uint16_t  uint16_T

#define int32     int32_T
#define uint32    uint32_T
#define int32_t   int32_T
#define u_int32_t uint32_T
#define uint32_t  uint32_T

//Simulink does not know 64-bit-int, define types with standard-C compiler specific.
#define int64 __int64
#define uint64 __int64
#define int64_t __int64
#define u_int64_t __int64
#define uint64_t __int64

#define bool8    uint8_T
#define bool8_t  uint8_T
#define bool16   uint16_T
#define bool16_t uint16_T
//Standard-character and UTF16-character:
#define char8    uint8_T
#define char16   uint16_T
#define char8_t  uint8_T
#define char16_t uint16_T
#define float32  float

#undef INT_MAX  //was defined in limits.h
#undef INT_MIN
#define INT_MAX MAX_int32_T  //from rtwtypes.h
#define INT_MIN MIN_int32_T



/**This macro guarantees that a boolean true value is represented by the value 1. Most of compilers realizes that, 
 * but it is not guaranteed in C or C++ standard.
 * The value 1 is necessary to represent a boolean value in an integer or bitfield in a defined kind.
 * The long variant guarantees it independent of the compiler. The short variant can be used if the compiler guarantees 
 * a value of 1 for boolean true.
 */
#define bool1_emC(COND) ((COND) ? 1 : 0) 
#define OSAL_bool1(COND) ((COND) ? 1 : 0) 
//#define OSAL_bool1(COND) (COND)



/**It is a little or big-endian memory organisation: */
#undef OSAL_BIGENDIAN
#define OSAL_LITTLEENDIAN

/**This define is set because the memory organisation disallows a word boundary on non-word-addresses.
 * For example writing a int32 on a address 0x1005 is disallowed (not able to divide by sizeof(int32).
 */
//#define OSAL_MEMWORDBOUND

//This functions may be platform dependend but for all our platforms identical, also in C-Standard.
//do nut use platform specific headers. 
#define FW_OFFSET_OF(element, Type) (((int) &(((Type*)0x1000)->element))-0x1000)



/**Definition of the kind of memory addressing. 
 * MemUnit is the access to one memory cell with 1 address step.
 * One address step can address more as 8 bit for some embedded processors, 16 or 32 bit.
 */
#define MemUnit char            //sizeof(MemUnit) muss 1 sein!
#define BYTE_IN_MemUnit 1       //im PC gilt: 1 MemUnit = 1 Byte
#define BYTE_IN_MemUnit_sizeof 1
/**int-type which can represent a standard pointer. It is signed to support address difference calculation. */
#define intPTR long long
#define uintPTR unsigned long long
#define INT_HAS32BIT
#define DEF_DONOTDEF_intPTR  //intptr_t is defined unconditional in vcruntime.h of MS-VisualStudio.
//Application hint: do not use intptr_t in the application. 
#define _UINTPTR_T_DEFINED  //MS VS: prevent twice definition of uintptr_t in vadefs.h



/**The definition of the real number of bits for the intxx_t and uintxx_t is missing in the stdint.h, limits.h and in the C99 standard.
 * Only the sizes are defined there, but from sizes to bits it is not able to calculate.
 * The number of bits are necessary for shift operations. 
 * Note: The number of bits for an int16_t may not 16 in all platforms. 
 * There are platforms which only knows 32 bit data (for example DSP processors from Analog Devices).
 */
#define INT8_NROFBITS  8
#define INT16_NROFBITS 16
#define INT32_NROFBITS 32
#define INT64_NROFBITS 64
#define INT_NROFBITS   32

/**The definition of INTxx_MAX etc. is part of C99 and stdint.h (limits.h) 
 * But the definition of INT_MAX is missing.  But better use _emC as suffix.
 * For this compiler platform int is int32
 */
#define INT_MAX_emC INT32_MAX 
#define INT_MIN_emC INT32_MIN 
#define UINT_MAX_emC UINT32_MAX 

/**All types with fix byte-wide should be defined in a platform-valid form. It is the C99-standard here. 
 * Use the Simulink types from tmwtypes.h to aware compatibility with Simulink code.
 * Note: C99-compatible declaration is: u_TYPE_t
 */



/**The division of an int64-integer to its hi and lo part is platform depending. Big/little endian. */
typedef struct int64_hilo_t{ int32 lo; int32 hi; } int64_hilo;



#define DEFINED_float_complex     
#define float_complex creal32_T
#define DEFINED_double_complex
#define double_complex creal64_T






/**Definition of the really used types in variable argument lists. 
 * The GNU-Compiler uses abbreviated types, for example always int32 instead int16 and double instead float.
 * Especially in va_arg(..,TYP)-Makro.
 */
#define char_va_list char 
#define bool_va_list bool
#define int8_va_list signed char
#define int16_va_list short
#define float_va_list float

//NULL soll nach wie vor fuer einen 0-Zeiger verwendet werden duerfen.
//Hinweis: In C++ kann (void*)(0) nicht einem typisiertem Zeiger zugewiesen werden, wohl aber 0
#undef  NULL
#undef null
#ifdef __cplusplus
#define NULL 0
#define null 0
#else  //C-compiler
  #define NULL ((void*)0)
  #define null ((void*)0)
#endif 

// Folgendes Define wird nach einer Struktur insbesondere f�r GNU-Compiler verwendet. Es ist f�r MSC6 leer,
// weil stattdessen ein pragma pack(1) verwendet werden muss.
#define GNU_PACKED

//NOTE: This is the std definition in emC/Base/types_def_common.h, There also SIZEOF_IN_STRUCT
//#define OFFSET_IN_STRUCT(TYPE, FIELD) ((int)(intptr_t)&(((TYPE*)0)->FIELD))
/**To mark variables which are calculated but not used in any kind. 
 * Sometimes they may be part of an assertions which is switched off,
 * But also sometimes only for information on debugging. 
 * This is a pragma for gcc to prevent a warning. In visual studio not regarded.
 */
#define MAYBE_UNUSED_emC

/**Hint that this variable always is used. */
#define USED_emC

/**It is an attribute before a function definition to determine
 * that the function should be placed in a section which is linked
 * to a RAM location but load into the FLASH memory.
 * This section must be copied on startup to run successfully.
 * It is a designation for embedded hardware with lesser but fast RAM.
 */
#define RAMFUNC_emC

#define OFFSET_IN_STRUCT(TYPE, FIELD) ((int)(intptr_t)&(((TYPE*)0)->FIELD))
#define SIZEOF_IN_STRUCT(TYPE, FIELD) ((int)(sizeof((TYPE*)0)->FIELD))

/**Prevent process a NaN-value (not a number).
 * The NaN-check should be done processor-specific. Therefore this is a part of os_types_def.h
 * @param value the value to check and return in normal case
 * @param valueinstead This value is returned if value==nan
 * @param check a left-value (variable) which will be increment in the nan-situation for check. 
 * @return valueinstead or value.
 */
#define NNAN(value, valueinstead, check) (value < 1000000000.0f ? value : ((check) +=1, valueinstead))


/**Condition if value is not NAN
 * @param value to test
 * @param check a left-value (variable) which will be increment in the nan-situation for check. 
 */
#define ifNNAN(value, check) (value < 100000000.0f ? true :  ((check) +=1, false))


/**Prevent process a NaN-value maybe only in debug mode.
 * The NaN-check should be done processor-specific. Therefore this is a part of os_types_def.h
 * It calls stopNAN especially for debug at PC
 * @param value the value to check and return
 * @return value anytime.
 */
#define ASSERT_NNAN_F(value) (value < 100000000000.0f ? value : stopNAN(), value)





/**Ein EventHandle is a HANDLE defined as void*. 
 * The user should not include windows.h or such. 
 */
#define OS_HandleEvent void*   


//It is for math.h of Visual Studio, elsewhere M_PI is not defined (special incompatibility of VS)
#define _USE_MATH_DEFINES

/**A OS_intPTR is the representation of a pointer in a int variable. 
 * Often a pointer is representable in a normal int, 
 * but there may be some segmentation and other designations.
 * Using this type, the programming expresses what it is meaned.
 */
#define OS_intPTR intptr_t



/**This macro defines a struct with a pointer to the given type and a integer number.
 * Usual it can be used to describe exactly an 1-dimensional array. The integer number is the number of elements,
 * the size in memory is (sizeof(TYPE) * numberOfElements). 
 * This struct should pass with 2 register for call by value or return by value, usual supported by the compiler.
 */
#define VALTYPE_AddrVal_emC int32
#define STRUCT_AddrVal_emC(NAME, TYPE) struct NAME##_T { TYPE* addr; VALTYPE_AddrVal_emC val; } NAME



/**This definition defines a uint32 handle which is used instead a pointer for the 64-bit-System,
 * but in the 32-bit-System the handle value is equal the pointer value.
 * The generated code (from Simulink) uses the uint32 handle type, because the connection between blocks
 * is done with the uint32 handle connection. For internal data access with 64-bit-Pointer the Simulink S-Functions
 * translate the handle value to a pointer via a common pointer table. The handle is the index to the table entry. 
 * Used especially in Simulink S-Functions for bus elements and outputs which are references.
 * In this case, for a 32 bit system, both, the handle and pointer are accessible as union.
 * old: OS_HandlePtr
 * search: HandlePtr_emC ( TYPE, NAME)
 */
#define HandlePtr_emC(TYPE, NAME) uint32 NAME;




/**Bits of length of constant string in a OS_PtrValue-struct. It depends from the length of val
 * It have to be a mask with set bits on right side (all last significant bits).
 * The next 2 bits left are used internally for designation of String.
 * see [[mNonPersists__StringJc]], [[mThreadContext__StringJc]].
 * See also [[kIsCharSequence_StringJc]]
 * The following bits left side are used for enhanced references, see kBitBackRef_ObjectJc and mBackRef_ObjectJc. 
 * If enhanced references are not used, a StringJc can occupy all bits, for example all 16 bits for 16-bit-integer systems.
 */
#define mLength_StringJc                 0x00003fff



#ifndef TRUE
  #define TRUE true
  #define FALSE false
#endif

//In Handle_ptr64_emC.h: activate the macros to use the replacement of Pointer with an uint32-handle. Because Adresses need 64 bit.
#define DEF_HandlePtr64
#define __HandlePtr64_SharedMem__

/**This file includes common definition valid for any compiler independent of applstdef_emC.h
 * as enhancement of C or C++. For example bool, true and false are defined in a C compilation. */
#include <emC/Base/types_def_common.h>


#define DEF_compareAndSet_AtomicInteger
//This is implemented in emC_srcOSALspec/hw_Intel_x86_Gcc/os_atomic.c:
extern_C int32 compareAndSwap_AtomicInteger(int32 volatile* reference, int32 expect, int32 update);

extern_C int64 compareAndSwap_AtomicInt64(int64 volatile* reference, int64 expect, int64 update);

extern_C bool compareAndSet_AtomicRef(void* volatile* reference, void* expect, void* update);

INLINE_emC bool compareAndSet_AtomicInteger(int volatile* reference, int expect, int update) {
  int32 read = compareAndSwap_AtomicInteger((int32 volatile*)reference, expect, update);
  return read == expect;
}

INLINE_emC bool compareAndSet_AtomicInt32(int32 volatile* reference, int32 expect, int32 update){
  int32 read = compareAndSwap_AtomicInteger(reference, expect, update);
  return read == expect;
}



INLINE_emC bool compareAndSet_AtomicInt64(int64 volatile* reference, int64 expect, int64 update){
  int64 read = compareAndSwap_AtomicInt64(reference, expect, update);
  return read == expect;
}

//The processor allows only a 32-bit-compare and set. To execute it for a given 16-bit-location
//it is supposed that the other half word is stable. 
//Hence it is read as expected and written unchanged with update. 
//If the other part is changed in another thread, the compare and set system call failes,
//Hence it is repeated in the outer loop with the same expected situation. 
//It is expected that the second access may be okay. 
//Only if the other half word is extremly volatile, this approach fails.  
INLINE_emC bool compareAndSet_AtomicInt16(int16 volatile* reference, int16 expect, int16 update){
  //Note: more difficult because memory is 32 bit
  int32 volatile* ref32;  //need to be int32 because call compareAndSet_AtomicInt32
  uint32 expect32, update32;
  if( (((intptr_t)reference) & 0x3) == 2) { //read write hi word
    ref32 = (int32 volatile*)(reference-1);       //use the lower address 
    uint32 refLo = (*ref32 & 0x0000ffff); //suppose that the lower content is not changed.
    expect32 = refLo | (((uint32)expect)<<16);
    update32 = refLo | (((uint32)update)<<16);
  } else {
    ref32 = (int32 volatile*)(reference);          //use the same address 
    uint32 refHi = (*ref32 & 0xffff0000); //suppose that the higher content is not changed.
    expect32 = refHi | ((uint16)expect);
    update32 = refHi | ((uint16)update);  //never expand the sign, hence use uint.
  }
  //compare and swap the whole 32 bit memory location, assume that the other word is not change in the same time
  //or repeat the access (unnecessary) if the other word is changed only. That is not a functional error, 
  //only a little bit more calculation time because unnecesarry repetition.
  return compareAndSet_AtomicInt32(ref32, expect32, update32);
}



//INLINE_emC bool compareAndSet_AtomicRef(void* volatile* reference, void* expect, void* update){
//  //NOTE casting from void* to int32_t is ok because this file is for 32-bit-Systems.
//  if(sizeof(void*) != sizeof(int32)) {
//    return false;
//  }
//  int32 read = compareAndSwap_AtomicInteger((int32_t*)reference, (int32_t)expect, (int32_t)update);
//  return read == (int32_t)expect;
//}



#endif  //HGUARD_compl_adaption
