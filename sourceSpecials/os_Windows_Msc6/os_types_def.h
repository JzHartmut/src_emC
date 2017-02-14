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
 * @content Definition of basicly types adequate to the operation system, cpu and compiler.
 *
 * @author Hartmut Schorrig
 *************************************************************************************************/


/**If only this file is included, include all files of this concept. */
#ifndef __applstdefJc_h__
  #include <applstdefJc.h>
#endif

#ifndef   __os_types_def_h__
#define   __os_types_def_h__
//CRuntimeJavalike/includeSpecials/os_Windows_Msc6/os_types_def.h





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

// Folgender Schalter ist gesetzt zur Auswahl des Compilers MSC6. Damit k?nnen spezifische Compilereigenschaften mittels bedingter Compilierung ber?cksichtigt werden.
#define __COMPILER_IS_MSC6__

#define MemUnit char            //sizeof(MemUnit) muss 1 sein!
#define BYTE_IN_MemUnit 1       //im PC gilt: 1 MemUnit = 1 Byte
#define BYTE_IN_MemUnit_sizeof 1

/**All types with fix byte-wide should be defined in a platform-valid form. It is the C99-standard here. */
#define int8_t    char
#define u_int8_t  unsigned char
#define int16_t   short int
#define u_int16_t unsigned short int
#define int32_t   long int
#define u_int32_t unsigned long int
#define int64_t __int64
#define uint64_t __int64

#define bool8_t char
#define bool16_t int16_t
#define char8_t   char
#define char16_t  unsigned char



/**The division of an int64-integer to its hi and lo part is platform depending. Big/little endian. */
typedef struct int64_hilo_t{ int32_t lo; int32_t hi; } int64_hilo;

/**Union of int64 and its fractions. */
typedef union int64_uhilo_t{ int64_t v; int64_hilo hilo; } int64_uhilo;



/**All types with fix byte-wide should be defined in a platform-valid form. */
#define uint8    unsigned char
#define uint16   unsigned short
#define uint32   unsigned long
#define uint64   __int64
#define int8     signed char
#define int16    short
#define int32    long
#define int64    __int64

//Standard-character and UTF16-character:
#define char8   char
#define char16  unsigned short
#define bool8   char
#define float32 float


  //see stdlib.h
  //#define min(X,Y) ((X)<(Y) ? (X) : (Y))
  //#define max(X,Y) ((X)>(Y) ? (X) : (Y)

/**int-type which can represent a standard pointer. */
#define intPTR uint32


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
//Hinweis: (void*)(0) kann nicht einem typisiertem Zeiger zugewiesen werden, wohl aber 0
#undef  NULL
#define NULL 0
#undef null
#define null 0

// Folgendes Define wird nach einer Struktur insbesondere f?r GNU-Compiler verwendet. Es ist f?r MSC6 leer,
// weil stattdessen ein pragma pack(1) verwendet werden muss.
#define GNU_PACKED





/**Ein EventHandle ist unter Windows ein HANDLE und dort als void* definiert. 
 * Der Anwender soll aber keine windows.h und ?hnliches einziehen sollen (zuviel M?ll),
 * daher hier die Zur?ckf?hrung auf die Schnittmenge zwischen windows.h und dem Rest der Welt.
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
#define OS_PtrVal_DEF(NAME, TYPE) struct NAME##_t { TYPE* ref; int32 val; } NAME


/**A const definition takes 3 arguments, but the type of them depends from operation system.
 * @param PTR a pointer from a type*-type.
 * @param TYPE the type of the pointer.
 * @param VAL a value from a int-type
 */
#define CONST_OS_PtrValue(PTR, TYPE, VAL) { (TYPE*) PTR, (int32)VAL}


#define value_OS_PtrValue(THIS) ((THIS).val)

#define PTR_OS_PtrValue(THIS, TYPE) ((TYPE*)(THIS).ref)

#define set_OS_PtrValue(THIS, PTR, INT) { (THIS).ref = (char*)(PTR); (THIS).val = (INT); } //(char* )

//NOTE: use a local variable to prevent twice call if SRC is a complex expression.
#define copy_OS_PtrValue(THIS, SRC) { OS_PtrValue const* src__ = &(SRC); (THIS).ref = src__->ref; (THIS).val = src__->val; }

#define setValue_OS_PtrValue(THIS, INT) { (THIS).val = (INT); }

#define setPtr_OS_PtrValue(THIS, PTR) { (THIS).ref = (char*)(PTR); }

/**Usage of inline for C++ compiler or static functions in headerfiles instead. Depends on compiler and target decision. */
#ifdef __cplusplus
  #define INLINE_Fwc inline
#else
  /**For C-compiling: build static routines, maybe the compiler optimized it to inline. */
  #define INLINE_Fwc static
#endif

#ifdef __cplusplus
  #define CONSTMember_Fwc
#else
  /**For C-compiling: build static routines, maybe the compiler optimized it to inline. */
  #define CONSTMember_Fwc const
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



#define fmaxf(A, B) ( (A) > (B) ? (A) : (B) )
#define fminf(A, B) ( (A) < (B) ? (A) : (B) )

#define fmax(A, B) ( (A) > (B) ? (A) : (B) )
#define fmin(A, B) ( (A) < (B) ? (A) : (B) )

#ifdef __cplusplus
#define max(A, B) ( (A) > (B) ? (A) : (B) )
#define min(A, B) ( (A) < (B) ? (A) : (B) )
#endif




#endif  //__os_types_def_h__
