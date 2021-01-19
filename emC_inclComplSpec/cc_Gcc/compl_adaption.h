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
 *
 * @author Hartmut Schorrig
 *************************************************************************************************/


//uncomment that to check whether this file is used for include:
//#error File: emc/incComplSpecific/cc_Gcc/compl_adaption.h


/**Some warnings should be disabled in default, because there are not the source of errors,
 * but present in normal software development.
 */
//#pragma warning(disable:4204) //nonstandard extension used : non-constant aggregate initializer TODO prevent

//An variable may be unused because compiler switches, because debugging features etc.
//In any case an optimized compiling should remove it. If it is a writing mistake,
//  the expected variable shall be missing. It is not necessary as error hint.
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

//Usage of virtual may be point of vularibility, it should not be necessary only because of destructors.
//Usage of destructors with content is not recommended, because a faster longjmp ignore it. 
//Recommendation: Do not use destructors.
#ifdef __cplusplus
  #pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#endif

/**Some warnings should be disabled in default, because there are not the source of errors,
 * but present in normal software development.
 */

//#include the standard header from the standard include path. 
//stdint.h defines int8_t etc. via typedef. 
//Because pragma once (or guard) the content of the files are not included again.
//They should be included firstly to cover its typedef by the typedef of simulink.
#include <stdint.h>  //C99-int types
#include <limits.h>  //proper to C99

/**Defintion of bool, false, true for C usage. */
#ifdef __cplusplus
  #define INLINE_emC inline
  #define CONSTMember_emC
#else
  #define CONSTMember_emC const
  /**For C-compiling: build static routines, maybe the compiler optimized it to inline. 
   * See https://gcc.gnu.org/onlinedocs/gcc/Inline.html:
  */

  #define INLINE_emC static inline
  //If C-compiling is used, define the C++-keywords for C
  #define bool int
  #undef false
  #undef true
  #define false 0
  #define true (!false)
#endif

/**This macro guarantees that a boolean true value is represented by the value 1. Most of compilers realizes that, 
 * but it is not guaranteed in C or C++ standard.
 * The value 1 is necessary to represent a boolean value in an integer or bitfield in a defined kind.
 * The long variant guarantees it independent of the compiler. The short variant can be used if the compiler guarantees 
 * a value of 1 for boolean true.
 */
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

//The following switch select the compiler in some sources.
#define __COMPILER_IS_GCC__



#define MemUnit char            //sizeof(MemUnit) muss 1 sein!
#define BYTE_IN_MemUnit 1       //im PC gilt: 1 MemUnit = 1 Byte
#define BYTE_IN_MemUnit_sizeof 1


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
 * But the definition of INT_MAX is missing.
 */
//#define INT_MAX INT32_MAX 
//#define INT_MIN INT32_MIN 
//#define UINT_MAX UINT32_MAX 

/**All types with fix byte-wide should be defined in a platform-valid form. It is the C99-standard here. 
 * Use the Simulink types from tmwtypes.h to aware compatibility with Simulink code.
 * Note: C99-compatible declaration is: u_TYPE_t
 */
#define int8      int8_t
#define uint8     uint8_t

#define int16     int16_t
#define uint16    uint16_t

#define int32     int32_t
#define uint32    uint32_t

#define int64 long long
#define uint64 unsigned long long
//#define int64_t __int64
//#define uint64_t __int64

#define uint uint32_t

#define bool8    unsigned char
#define bool8_t  unsigned char
#define bool16   unsigned short
#define bool16_t unsigned short
//Standard-character and UTF16-character:
#define char8    char
#define char16   unsigned short
//Note: do not define char16_t, it is known in Gcc
//#define char8_t  char
//#define char16_t short
#define float32  float



/**The division of an int64-integer to its hi and lo part is platform depending. Big/little endian. */
typedef struct int64_hilo_t{ int32 lo; int32 hi; } int64_hilo;


#define DEFINED_float_complex     
//#define float_complex creal32_T
typedef struct float_complex_t { float re; float im; } float_complex; 
#define DEFINED_double_complex
//#define double_complex creal64_T
typedef struct double_complex_t { double re; double im; } double_complex; 







/**int-type which can represent a standard pointer. It is signed to support address difference calculation. */
#define intPTR intptr_t


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
#define NULL 0
#undef null
#ifdef __cplusplus
  #define null 0
#else
  #define null ((void*)0)
#endif

// weil stattdessen ein pragma pack(1) verwendet werden muss.
#define GNU_PACKED

#define MAYBE_UNUSED_emC __attribute__((unused))

#define USED_emC

/**It is an attribute before a function definition to determine
 * that the function should be placed in a section which is linked
 * to a RAM location but load into the FLASH memory.
 * This section must be copied on startup to run successfully.
 * It is a designation for embedded hardware with lesser but fast RAM.
 */
#define RAMFUNC_emC

#define OFFSET_IN_STRUCT(TYPE, FIELD) ((int)(intptr_t)&(((TYPE*)0)->FIELD))



/**Ein EventHandle is a HANDLE defined as void*. 
 * The user should not include windows.h or such. 
 */
#define OS_HandleEvent void*   



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
 */
#define HandlePtr_emC(TYPE, NAME) union {uint32 NAME; TYPE* p##NAME;}


/**Possibility to store a pointer (a memory address) as handle if desired. 
 * It depends from the target system. 
 * If dll are used and independent linked objects are existing, especially if dll are used,
 * and graphical programming is used (that is especially in Simulink S-Functions), 
 * then a memory address should be present by a handle, the handle is converted to the address 
 * via a central table which contains all addresses of instances, common for all dll. 
 * In that case the Handle_ADDR_emC is an uint32, and the TYPE is not relevant. 
 * This system is supported by emC/Base/Handle_prt64_emC.*. 
 * For simple applications it is defined with the immediately access, maybe with 64-bit-addresses.
 *
 * Here it is immediately the 64-bit-address with the proper type (important for debug).
 */
//In Handle_ptr64_emC.h: activate the macros to use the replacement of Pointer with an uint32-handle. Because Adresses need 64 bit.
#ifdef DEF_HandlePtr64
  #define HandleADDR_emC(TYPE) uint32

  #include <emC/Base/Handle_ptr64_emC.h>
#else //not DEF_HandlePtr64
#define HandleADDR_emC(TYPE) TYPE*

/**It presents the TYPE-correct address as pointer in C/++*/
#define ptr_HandleADDR_emC(HANDLE, TYPE) (HANDLE)

/**It presents an integer value as handle, may be identical with the address. */
#define handle_HandleADDR_emC(HANDLE) ((intPTR)(HANDLE))
#endif  //DEF_HandlePtr64





/**Bits of length of constant string adequate to VALTYPE_AddrVal_emC. 
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


/**This file includes common definition valid for any compiler independent of applstdef_emC.h
 * as enhancement of C or C++. For example bool, true and false are defined in a C compilation. */


#include <emC/Base/types_def_common.h>


#define DEF_compareAndSet_AtomicInteger
//This is implemented in emC_srcOSALspec/hw_Intel_x86_Gcc/os_atomic.c:
extern_C int32 compareAndSwap_AtomicInteger(int32 volatile* reference, int32 expect, int32 update);

extern_C int64 compareAndSwap_AtomicInt64(int64 volatile* reference, int64 expect, int64 update);

//extern_C bool compareAndSet_AtomicRef(void* volatile* reference, void* expect, void* update);

//see https://gcc.gnu.org/onlinedocs/gcc-4.1.1/gcc/Atomic-Builtins.html

INLINE_emC bool compareAndSet_AtomicRef(void* volatile* reference, void* expect, void* update) {
  return __sync_bool_compare_and_swap (reference, expect, update);
}


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



#endif  //HEADERGUARD_compl_adaption_h
