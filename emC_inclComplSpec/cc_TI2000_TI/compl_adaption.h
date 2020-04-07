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


/**If only this file is included, include all files of this concept. */
#ifndef __applstdef_emC_h__
  #include <applstdef_emC.h>
#endif

#define GCC_TI2000

#ifndef   __compl_adaption_h__
#define   __compl_adaption_h__
//#include <msp2000.h>


#include <stdint.h>  //C99-int types
#include <limits.h>  //proper to C99

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

//The following switch select the operation system in some sources.
#define __OS_IS_WINDOWS__

//The following switch select the compiler in some sources.
#define __COMPILER_IS_TI2000__



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
#define INT_MAX_emC INT32_MAX 
#define INT_MIN_emC INT32_MIN 
#define UINT_MAX_emC UINT32_MAX 

/**All types with fix byte-wide should be defined in a platform-valid form. It is the C99-standard here. 
 * Use the Simulink types from tmwtypes.h to aware compatibility with Simulink code.
 * Note: C99-compatible declaration is: u_TYPE_t
 */
#define int8      int16_t  //NOTE: int8_t not defined.
#define uint8     uint16_t //NOTE: int16_t not defined.

#define int16     int16_t
#define uint16    uint16_t

#define int32     int32_t
#define uint32    uint32_t

#define int64 int64_t
#define uint64 int64_t

#define uint uint32_t


#define bool8    unsigned char
#define bool8_t  unsigned char
#define bool16   unsigned short
#define bool16_t unsigned short
//Standard-character and UTF16-character:
#define char8    char
#define char16   unsigned short
#define char8_t  char
#define char16_t short
#define float32  float



/**The division of an int64-integer to its hi and lo part is platform depending. Big/little endian. */
typedef struct int64_hilo_t{ int32 lo; int32 hi; } int64_hilo;

/**Union of int64 and its fractions. */
typedef union int64_uhilo_t{ int64 v; int64_hilo hilo; } int64_uhilo;


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
#define null 0

// Folgendes Define wird nach einer Struktur insbesondere for the GNU-Compiler verwendet. Es ist f�r MSC6 leer,
// weil stattdessen ein pragma pack(1) verwendet werden muss.
#define GNU_PACKED

#define OFFSET_IN_STRUCT(TYPE, FIELD) ((int)(intptr_t)&(((TYPE*)0)->FIELD))

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
#define VALTYPE_AddrVal_emC int
#define STRUCT_AddrVal_emC(NAME, TYPE) struct NAME##_T { TYPE* addr; VALTYPE_AddrVal_emC val; } NAME



/**This definition defines a uint32 handle which is used instead a pointer for the 64-bit-System,
 * but in the 32-bit-System the handle value is equal the pointer value.
 * The generated code (from Simulink) uses the uint32 handle type, because the connection between blocks
 * is done with the uint32 handle connection. For internal data access with 64-bit-Pointer the Simulink S-Functions
 * translate the handle value to a pointer via a common pointer table. The handle is the index to the table entry. 
 * Used especially in Simulink S-Functions for bus elements and outputs which are references.
 */
#define HandlePtr_emC(TYPE, NAME) union {TYPE* p##NAME; uint32 NAME; }







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


#define DEF_compareAndSet_AtomicInteger
INLINE_emC bool compareAndSet_AtomicInteger(int volatile* reference, int expect, int update){
  //simple implementation, not atomic, but able to test. TODO ASM-Instructions with Disable Interrupt necessary.
  bool bUpdated;
  bUpdated = *reference == expect; if(bUpdated){ *reference = update; }  //This line should be atomic.
  return bUpdated;
}


INLINE_emC bool compareAndSet_AtomicInt32(int32 volatile* reference, int32 expect, int32 update){
  //simple implementation, not atomic, but able to test. TODO ASM-Instructions with Disable Interrupt necessary.
  bool bUpdated;
  bUpdated = *reference == expect; if(bUpdated){ *reference = update; }  //This line should be atomic.
  return bUpdated;
}


INLINE_emC bool compareAndSet_AtomicInt64(int64 volatile* reference, int64 expect, int64 update){
  //simple implementation, not atomic, but able to test. TODO ASM-Instructions with Disable Interrupt necessary.
  bool bUpdated;
  bUpdated = *reference == expect; if(bUpdated){ *reference = update; }  //This line should be atomic.
  return bUpdated;
}

INLINE_emC bool compareAndSet_AtomicInt16(int volatile* reference, int16 expect, int16 update){
  //simple implementation, not atomic, but able to test. TODO ASM-Instructions with Disable Interrupt necessary.
  bool bUpdated;
  bUpdated = *reference == expect; if(bUpdated){ *reference = update; }  //This line should be atomic.
  return bUpdated;
}


INLINE_emC bool compareAndSet_AtomicRef(void volatile** reference, void* expect, void* update){
  //simple implementation, not atomic, but able to test. TODO ASM-Instructions with Disable Interrupt necessary.
  bool bUpdated;
  bUpdated = *reference == expect; if(bUpdated){ *reference = update; }  //This line should be atomic.
  return bUpdated;
}





/**Special: instead mutex use interrupt disable. */
/*---------------------------------------------------------------------------*/
/* MSP430/430X Intrinsics                                                    */
/*---------------------------------------------------------------------------*/
//void             __disable_interrupt(void);
//void             __enable_interrupt(void);
//#include <intrinsics.h>  //compiler-specific definitions
#define os_createMutex(NAME) null
#define os_lockMutex(M, TIME) (__disable_interrupt(), true)
#define os_unlockMutex(M) __enable_interrupt()


/**Use the TA0R for MC_2: Mode 2: continues from 0 to 0xffff->0 */
#define os_getClockCnt() ((int16)TA0R)

#include <emC/Base/os_types_def_common.h>

#endif  //__compl_adaption_h__
