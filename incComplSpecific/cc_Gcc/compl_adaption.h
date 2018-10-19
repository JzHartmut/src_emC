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

#ifndef   __os_types_def_h__
#define   __os_types_def_h__
//File: CRuntimeJavalike/includeSpecials/os_Windows_Gcc/os_types_def.h

/**Some warnings should be disabled in default, because there are not the source of errors,
 * but present in normal software development.
 */


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

// Folgender Schalter ist gesetzt zur Auswahl der Betriebssystemplattform Windows ist. Damit k?nnen Betriebssystemzugriffe bedingt compiliert werden.
#define __OS_IS_WINDOWS__

// Folgender Schalter ist gesetzt zur Auswahl des Compilers GCC. Damit k?nnen spezifische Compilereigenschaften mittels bedingter Compilierung ber?cksichtigt werden.
#define __COMPILER_IS_GCC__

#define MemUnit char            //sizeof(MemUnit) muss 1 sein!
#define BYTE_IN_MemUnit 1       //im PC gilt: 1 MemUnit = 1 Byte

/**All types with fix byte-wide should be defined in a platform-valid form. It is the C99-standard here. */
typedef unsigned char        uint8_t;
typedef unsigned short       u_int16_t;
typedef unsigned long        uint32_t;    //type identifier faulty, u_int32_t is C99
typedef unsigned long        u_int32_t;

typedef char                 char8_t;   //Standard-C-char
typedef unsigned short       char16_t;  //UTF16-char

typedef signed char          int8_t;
typedef short                int16_t;
typedef long                 int32_t;

#define int64_t long long
#define uint64_t unsigned long long
#define bool8_t char
#define bool16_t int16_t


/**The division of an int64-integer to its hi and lo part is platform depending. Big/little endian. */
typedef struct int64_hilo_t{ int32_t lo; int32_t hi; } int64_hilo;

/**Union of int64 and its fractions. */
typedef union int64_uhilo_t{ int64_t v; int64_hilo hilo; } int64_uhilo;



/**All types with fix byte-wide should be defined in a platform-valid form. */
#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned long
#define uint64 unsigned long long
#define int8 signed char
#define int16 short
#define int32 long
#define int64 long long
//Standard-character and UTF16-character:
#define char8 char
#define char16 unsigned short
#define bool8 char
#ifndef __cplusplus
  //If C-compiling is used, define the C++-keywords for C
  #define bool int
  #define false 0
  #define true (!false)
#endif


  //see stdlib.h
  //#define min(X,Y) ((X)<(Y) ? (X) : (Y))
  //#define max(X,Y) ((X)>(Y) ? (X) : (Y)

/**int-type which can represent a standard pointer. */
#define intPTR uint32


/**Die Definition spezieller Typen f?r variable Argumentlisten ist daher notwendig,
 * weil der GNU-Compiler bei variablen Argumenten die hier genannten Typen jeweils promoted.
 * Verwendung nur in va_arg(..,TYP)-Makro.
 */
typedef char                 char_va_list;
typedef bool                 bool_va_list;
typedef signed char          int8_va_list;
typedef short                int16_va_list;
//typedef float                float_va_list;
typedef double                float_va_list;


typedef float                float32;

//NULL soll nach wie vor fuer einen 0-Zeiger verwendet werden duerfen.
//Hinweis: (void*)(0) kann nicht einem typisiertem Zeiger zugewiesen werden, wohl aber 0
#undef  NULL
#define NULL 0
#undef null
#define null 0

// Folgendes Define wird nach einer Struktur insbesondere f?r GNU-Compiler verwendet. Es ist f?r MSC6 leer,
// weil stattdessen ein pragma pack(1) verwendet werden muss.
#define GNU_PACKED





/**Ein EventHandle is a HANDLE defined as void*. 
 * The user should not include windows.h or such. 
 */
#define OS_HandleEvent void*   



/**A OS_intPTR is the representation of a pointer in a int variable. 
 * Often a pointer is representable in a normal int, 
 * but there may be some segmentation and other designations.
 * Using this type, the programming expresses what it is meaned.
 */
#define OS_intPTR int



/**This macro defines a struct with a pointer to the given type and a integer number.
 * Usual it can be used to describe exactly an 1-dimensional array. The integer number is the number of elements,
 * the size in memory is (sizeof(TYPE) * numberOfElements). 
 * This struct should pass with 2 register for call by value or return by value, usual supported by the compiler.
 */
#define OS_PtrValue_DEF(NAME, TYPE) struct NAME##_t { TYPE* ref; int32 val; } NAME
#define OS_PtrVal_DEF OS_PtrValue_DEF

/**A const definition takes 3 arguments, but the type of them depends from operation system.
 * @param PTR a pointer from a type*-type.
 * @param TYPE the type of the pointer.
 * @param VAL a value from a int-type
 */
#define INIZ_OS_PtrValue(PTR, TYPE, VAL) { (TYPE*) PTR, (int32)VAL}

#define CONST_OS_PtrValue(PTR, TYPE, VAL) INIZ_OS_PtrValue(PTR, TYPE, VAL)





#define value_OS_PtrValue(THIS) ((THIS).val)

#define PTR_OS_PtrValue(THIS, TYPE) ((TYPE*)(THIS).ref)

#define set_OS_PtrValue(THIS, PTR, INT) { (THIS).ref = (char*)(PTR); (THIS).val = (INT); } //(char* )

//NOTE: use a local variable to prevent twice call if SRC is a complex expression.
#define copy_OS_PtrValue(THIS, SRC) { OS_PtrValue const* src__ = &(SRC); (THIS).ref = src__->ref; (THIS).val = src__->val; }

#define setValue_OS_PtrValue(THIS, INT) { (THIS).val = (INT); }

#define setPtr_OS_PtrValue(THIS, PTR) { (THIS).ref = (char*)(PTR); }

/**This definition defines a uint32 handle which is used instead a pointer for the 64-bit-System,
 * but in the 32-bit-System the handle value is equal the pointer value.
 * The generated code (from Simulink) uses the uint32 handle type, because the connection between blocks
 * is done with the uint32 handle connection. For internal data access with 64-bit-Pointer the Simulink S-Functions
 * translate the handle value to a pointer via a common pointer table. The handle is the index to the table entry. 
 * Used especially in Simulink S-Functions for bus elements and outputs which are references.
 */
#define HandlePtr_emC(TYPE, NAME) union {TYPE* p##NAME; uint32 NAME; }

/**Usage of inline for C++ compiler or static functions in headerfiles instead. Depends on compiler and target decision. */
#ifdef __cplusplus
  #define INLINE_emC inline
#else
  /**For C-compiling: build static routines, maybe the compiler optimized it to inline. */
  #define INLINE_emC static
#endif

#ifdef __cplusplus
  #define CONSTMember_emC
#else
  /**For C-compiling: build static routines, maybe the compiler optimized it to inline. */
  #define CONSTMember_emC const
#endif


/**Bits of length of constant string in a OS_PtrValue-struct. It depends from the length of val
 * It have to be a mask with set bits on right side (all last significant bits).
 * The next 2 bits left are used internally for designation of String.
 * The following bits left side are used for enhanced references, see kBitBackRef_ObjectJc and mBackRef_ObjectJc. 
 * If enhanced references are not used, a StringJc can occupy all bits, for example all 16 bits for 16-bit-integer systems.
 */
#define mLength__StringJc                 0x00003fff

/**Maximal length of path in a FileDescription_OSAL-structure.
 * NOTE: old name kMaxPathLength_OS_FileDescription
 */
#define kMaxPathLength_FileDescription_OSAL 480

//#define abs(X) (X <0 ? -X :X)


/**Include the common definitions in its pure form. */
#include <OSAL/os_types_def_common.h>

/**This file can be additinally modified by the user to determine how debugging and exception handling should processed. 
 * Either this file is defined in the users area 
 * or one of the source paths of CRuntimeJavalike is added to the include path where an exemplare of this file is provided.
 * See CRuntimeJavalike/sourceSpecials/ExcHandling_No.template or CRuntimeJavalike/sourceSpecials/ExcHandling_Printf.template
 */ 
#include <OSAL_UserExceptionAndDebug.h>



#endif  //__os_types_def_h__
