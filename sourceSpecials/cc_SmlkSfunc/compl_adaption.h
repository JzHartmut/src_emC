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

#ifndef   __compl_adaption_h__
#define   __compl_adaption_h__

/**Some warnings should be disabled in default, because there are not the source of errors,
 * but present in normal software development.
 */
//#pragma warning(disable:4204) //nonstandard extension used : non-constant aggregate initializer TODO prevent


//#pragma warning(disable:4100) //unused argument
#pragma warning(disable:4127) //conditional expression is constant
#pragma warning(disable:4214) //nonstandard extension used : bit field types other than int
#pragma warning(disable:4189) //local variable is initialized but not referenced
#pragma warning(disable:4201) //nonstandard extension used : nameless struct/union
#pragma warning(disable:4310) //cast truncates constant value

//C++
#pragma warning(disable:4514) //unreferenced inline function has been removed
//#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4268) //'const' static/global data initialized with compiler generated default constructor fills the object with zeros
#pragma warning(disable:4068) //unknown pragma

#pragma warning(disable:4244) //conversion from 'int' to 'char', possible loss of data specific for energy inits
#pragma warning(disable:4100) //4100: 'type' : unreferenced formal parameter
#pragma warning(disable:4505) //unreferenced local function has been removed
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4390) //





/**This macro guarantees that a boolean true value is represented by the value 1. Most of compilers realizes that, 
 * but it is not guaranteed in C or C++ standard.
 * The value 1 is necessary to represent a boolean value in an integer or bitfield in a defined kind.
 * The long variant guarantees it independent of the compiler. The short variant can be used if the compiler guarantees 
 * a value of 1 for boolean true.
 */
#define OSAL_bool1(COND) ((COND) ? 1 : 0) 
//#define OSAL_bool1(COND) (COND)

#ifndef __cplusplus
  //If C-compiling is used, define the C++-keywords for C
  //Note: regard that any other system file may define that too.
  //Note defined in Matlab\R2016a\extern\include\tmwtypes.h
  #define bool int
  #ifndef false
    #define false 0
    #define true (!false)
  #endif  
#endif


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

// Folgender Schalter ist gesetzt zur Auswahl der Betriebssystemplattform Windows ist. Damit können Betriebssystemzugriffe bedingt compiliert werden.
#define __OS_IS_WINDOWS__

// Folgender Schalter ist gesetzt zur Auswahl des Compilers MSC6. Damit können spezifische Compilereigenschaften mittels bedingter Compilierung berücksichtigt werden.
#define __COMPILER_IS_MSC10__


#define __Simulink__
#ifndef TEST_MODULE
  #undef TEST_MODULE
#endif


// Folgender Schalter ist gesetzt zur Auswahl der C++-Compilierung. In einigen Quellen kann es einen Unterschied geben, wenn eine C-Abbildung der Quellen
// berücksichtigt werden muss. Das standardgemäß definierte Makro __cplusplus ist nicht immer für dieses Zweck verwendbar, da auch der Einsatz der C++-Compilierung
// für eine C-Abbildung erfolgen kann. Wenn die Gesamt-Source (beispielsweise ein Headerfile) gegebenenfalls auch als C-Abbildung
// compiliert werden muss, dann müssen alle Teile, die nur unter C++ lauffähig sind, mit diesem Schalter bedingt compiliert werden.
//#define __CPLUSGEN

#define MemUnit char            //sizeof(MemUnit) muss 1 sein!
#define BYTE_IN_MemUnit 1       //im PC gilt: 1 MemUnit = 1 Byte
#define BYTE_IN_MemUnit_sizeof 1

/**All types with fix byte-wide should be defined in a platform-valid form. It is the C99-standard here. */
#define int8_t    char
#define u_int8_t  unsigned char
#define uint8_t  unsigned char
#define int16_t   short int
#define u_int16_t unsigned short int
#define uint16_t unsigned short int
#define int32_t   long int
#define u_int32_t unsigned long int
#define uint32_t unsigned long int
#define int64_t __int64
#define u_int64_t __int64
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
#define bool8 char
#define float32 float


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

// Folgendes Define wird nach einer Struktur insbesondere für GNU-Compiler verwendet. Es ist für MSC6 leer,
// weil stattdessen ein pragma pack(1) verwendet werden muss.
#define GNU_PACKED


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





/**Ein EventHandle ist unter Windows ein HANDLE und dort als void* definiert. 
 * Der Anwender soll aber keine windows.h und ähnliches einziehen sollen (zuviel Müll), 
 * daher hier die Zurückführung auf die Schnittmenge zwischen windows.h und dem Rest der Welt.
 */
#define OS_HandleEvent void*   



/**A OS_intPTR is the representation of a pointer in a int variable. 
 * Often a pointer is representable in a normal int, 
 * but there may be some segmentation and other designations.
 * Using this type, the programming expresses what it is meaned.
 */
#define OS_intPTR int64



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

/**This definition defines a uint32 handle which is used instead a pointer for the 64-bit-System,
 * but in the 32-bit-System the handle value is equal the pointer value.
 * The generated code (from Simulink) uses the uint32 handle type, because the connection between blocks
 * is done with the uint32 handle connection. For internal data access with 64-bit-Pointer the Simulink S-Functions
 * translate the handle value to a pointer via a common pointer table. The handle is the index to the table entry. 
 * Used especially in Simulink S-Functions for bus elements and outputs which are references.
 */
#define OS_HandlePtr(TYPE, NAME) uint32 NAME





/**Bits of length of constant string in a OS_PtrValue-struct. It depends from the length of val
 * It have to be a mask with set bits on right side (all last significant bits).
 * The next 2 bits left are used internally for designation of String.
 * see [[mNonPersists__StringJc]], [[mThreadContext__StringJc]].
 * See also [[kIsCharSequence_StringJc]]
 * The following bits left side are used for enhanced references, see kBitBackRef_ObjectJc and mBackRef_ObjectJc. 
 * If enhanced references are not used, a StringJc can occupy all bits, for example all 16 bits for 16-bit-integer systems.
 */
#define mLength__StringJc                 0x00003fff

/**Maximal length of path in a FileDescription_OSAL-structure.
 * NOTE: old name kMaxPathLength_OS_FileDescription
 */
#define kMaxPathLength_FileDescription_OSAL 480


/*
#define fmaxf(A, B) ( (A) > (B) ? (A) : (B) )
#define fminf(A, B) ( (A) < (B) ? (A) : (B) )

#define fmax(A, B) ( (A) > (B) ? (A) : (B) )
#define fmin(A, B) ( (A) < (B) ? (A) : (B) )

#ifdef __cplusplus
#define max(A, B) ( (A) > (B) ? (A) : (B) )
#define min(A, B) ( (A) < (B) ? (A) : (B) )
#endif
*/

#ifndef TRUE
  #define TRUE true
  #define FALSE false
#endif

/**Yet in simulink an untyped input/output handle which is a pointer can only be stored as double.
 * use conversion:
 *  SIMUPTR ptr = *(SIMUPTR*)&reference; //reference is any Type* reference.
 */
typedef double SIMUPTR;

#define creal32_T float_complex_t
#ifndef CREAL32_T
  #define CREAL32_T creal32_T
#endif

#endif  //__compl_adaption_h__
