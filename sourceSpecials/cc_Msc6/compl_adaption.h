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

#ifndef   __os_types_def_h__
#define   __os_types_def_h__


/**Some warnings should be disabled in default, because there are not the source of errors,
 * but present in normal software development.
 */
#pragma warning(disable:4204) //nonstandard extension used : non-constant aggregate initializer TODO prevent


#pragma warning(disable:4100) //unused argument
#pragma warning(disable:4127) //conditional expression is constant
#pragma warning(disable:4214) //nonstandard extension used : bit field types other than int
#pragma warning(disable:4189) //local variable is initialized but not referenced
#pragma warning(disable:4201) //nonstandard extension used : nameless struct/union
#pragma warning(disable:4310) //cast truncates constant value

//C++
#pragma warning(disable:4514) //unreferenced inline function has been removed
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4268) //'const' static/global data initialized with compiler generated default constructor fills the object with zeros
#pragma warning(disable:4068) //unknown pragma
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //



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

// Folgender Schalter ist gesetzt zur Auswahl der Betriebssystemplattform Windows ist. Damit können Betriebssystemzugriffe bedingt compiliert werden.
#define __OS_IS_WINDOWS__

// Folgender Schalter ist gesetzt zur Auswahl des Compilers MSC6. Damit können spezifische Compilereigenschaften mittels bedingter Compilierung berücksichtigt werden.
#define __COMPILER_IS_MSC6__

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
typedef __int64              int64_t;
typedef __int64              uint64_t;
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
#define uint64 __int64
#define int8 signed char
#define int16 short
#define int32 long
#define int64 __int64
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

//Simulink types:
//#define char_T int8
//#define int_T int32
//#define int32_T int32
//typedef float real_T;
//#define real_T float
//#define real32_T float
//#define boolean_T bool

//#define UNUSED_PARAMETER(val)

  //see stdlib.h
  //#define min(X,Y) ((X)<(Y) ? (X) : (Y))
  //#define max(X,Y) ((X)>(Y) ? (X) : (Y)

/**int-type which can represent a standard pointer. */
#define intPTR uint32


/**Die Definition spezieller Typen für variable Argumentlisten ist daher notwendig, 
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


//NOTE: different math.h
  #define fmaxf(A, B) ( (A) > (B) ? (A) : (B) )
  #define fminf(A, B) ( (A) < (B) ? (A) : (B) )

  #define fmax(A, B) ( (A) > (B) ? (A) : (B) )
  #define fmin(A, B) ( (A) < (B) ? (A) : (B) )

  #ifndef __cplusplus
  #define max(A, B) ( (A) > (B) ? (A) : (B) )
  #define min(A, B) ( (A) < (B) ? (A) : (B) )
  #endif




#endif  //__os_types_def_h__
