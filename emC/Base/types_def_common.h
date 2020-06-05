/*@NoReflection*/
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
//#define ushort unsigned short int
#ifndef uint
//  #define uint unsigned int
#endif
//#define ulong unsigned long int

/**It calculates the number of defined array elements from any type. 
 * @param ARRAY any array instance defined with TYPE ARRAY[SIZE];
 * @return SIZE
 */
#define ARRAYLEN_emC(ARRAY) (uint)(sizeof(ARRAY) / sizeof((ARRAY)[0]))


/**Builds the value 0xffffffff for a pointer (0xffffffffffffffff for 64 bit)
 * to build a non-null-pointer but able to detect as ISvalidPTR_emC(ptr).
 * Some routines are not invoked in intialize phase if the any input is null-pointer, 
 * but they need the information 'pointer not use'.
 * The routine should check [[ISvalidPTR_emC(...)]]. */
#define INVALID_NOT_nullPTR_emC(TYPE) ((TYPE*)(intptr_t)-1)


/**checks any pointer/reference and returns false if the pointer is either null
 * or it is a value between -2, -1, 1 in the range of target addresses (0xffffffff etc. for 32 bit).
 * With them a pointer is able to build which is not null but not valid. */
//Note: mask with ~3 = 0xff..fffc. It is 0 only for values -2, -1, 0, 1
#define ISvalidPTR_emC(PTR) (((((intptr_t)(PTR))+2) & ~3 )!=0)

/**The compiler optimizes it because the return value should not used. */
inline int unused_emC(int arg){ return arg; }


#define DEF

#define INLINE_Jc INLINE_emC

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
//NOTE: This part cannot be parsed by Cheader.zbnf because it defines the special keywords itself. Note: It should not be parsed by Cheader.zbnf
//#ifndef __NoReflection__
#ifdef __cplusplus
  #ifdef DEF_CPP_COMPILE  //If the apropriate C-sources are compiled as C++
    /**C-Sources are compiled with C++, C++ linker label is desired.*/
    #define extern_CCpp extern
  #else                   //If all C-Sources are compiled with C
    /**C-Sources are compiled with C*/
    #define extern_CCpp extern "C"
  #endif
  #define extern_C extern "C"
  #define C_TYPE extern "C"
  #define METHOD_C extern "C"
  #define extern_C_BLOCK_ extern "C" { 
  #define _END_extern_C_BLOCK } 
  #define INLINE_C inline
  //#define C_CAST(TYPE, PTR) reinterpret_cast<TYPE>(const_cast<TYPE>(PTR))
  #define FORCED_CAST(TYPE, PTR) reinterpret_cast<TYPE>(PTR)
  #define C_CAST(TYPE, PTR) reinterpret_cast<TYPE>(PTR)
  #define STATIC_CAST(TYPE, PTR) static_cast<TYPE>(PTR)
  //#define METHOD_C
#else
  #define extern_C extern
  /**Use this macro for extern declarations and function prototypes which are implemented in a C-Source
   * which may be compiled as C++, and the C++ linker label is desired. 
   */
  #define extern_CCpp extern
  #define C_TYPE
  #define METHOD_C
  #define extern_C_BLOCK_ 
  #define _END_extern_C_BLOCK 
  #ifndef INLINE_C  //may be defined in compl_adaption.h
    #define INLINE_C static  //a compiler may optimize static routines.
  #endif
  #define FORCED_CAST(TYPE, PTR) (TYPE)(PTR)
  #define C_CAST(TYPE, PTR) (TYPE)(PTR)
  #define STATIC_CAST(TYPE, PTR) (TYPE)(PTR)
#endif
//#endif//__NoReflection__

//Note: definition of bool, true, false is compiler/system-specific. Removed from here. See compl_adaption.h


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
//typedef STRUCT_AddrVal_emC(PtrVal_MemUnit, MemUnit);

typedef struct Addr8_emC_T { int32_t c[2]; } Addr8_emC;

/**The type AddrVal_emC handles with a address (pointer) for a 8 byte alignment. */
typedef STRUCT_AddrVal_emC(AddrVal_emC, Addr8_emC);

#define INIZ_AddrVal_emC(ADDR, VAL) { (Addr8_emC*)(ADDR), VAL }

#define ADDR_AddrVal_emC(THIS, TYPE) ((TYPE*)(THIS).addr)

#define VAL_AddrVal_emC(THIS) ((THIS).val)

#define SET_AddrVal_emC(THIS, ADDR, VAL) { (THIS).addr = (THIS).addr = (Addr8_emC*)(ADDR); (THIS).val = VAL; }

#define SETADDR_AddrVal_emC(THIS, ADDR) ( (THIS).addr = (THIS).addr = (Addr8_emC*)(ADDR) )

#define SETVAL_AddrVal_emC(THIS, VAL) ( (THIS).addr = (THIS).val = VAL )



//Compatibility:
#define OS_PtrValue AddrVal_emC

/**Compatibility with older typedef of OS_PtrValue. */
//#define OS_PtrValue PtrVal_MemUnit


#ifndef STRUCT_AddrVal_emC  //force deprecated compatibility
  #define STRUCT_AddrVal_emC(NAME, TYPE) OS_PtrVal_DEF(NAME, TYPE)
#endif

#ifdef DEF_HandlePtr64
  #define HandlePtr32Union_emC(TYPE) union {uint32 h; }
#else
  #define HandlePtr32Union_emC(TYPE) union {uint32 h; TYPE* p; }
#endif


/**An instance which contains null-values. */
extern AddrVal_emC null_AddrVal_emC;



/**Defines Struct_charPtr_Value.
 */
typedef STRUCT_AddrVal_emC(int8ARRAY, int8);

typedef STRUCT_AddrVal_emC(int16ARRAY, int16);

typedef STRUCT_AddrVal_emC(int32ARRAY, int32);

typedef STRUCT_AddrVal_emC(int64ARRAY, int64);

typedef STRUCT_AddrVal_emC(floatARRAY, float);

typedef STRUCT_AddrVal_emC(doubleARRAY, double);


/**Possibility to store characters (ASCII) in an uint32-value. It is especially for processors
 * which have a non-byte-addressing step, so that a char is 16 or 32 bit.
 * If the character array should be accessed with another processor architecture,
 * may be because of transferred data, or Dual-Port-Memory-Access, the char[] should be bytewise.
 * For a byte addressing mode with char as byte it can be immediately accessed as char const*
 */
#define char4_emC uint32

/**Build a member of a char4_emC array, or build a 4-char-const in an uint32*/
#define CHAR4_emC(C1, C2, C3, C4)  ((((uint32)C4)<<24) | (( ((uint32)C3)& 0xff)<<16) | (((uint16)C2)<<8) | (C1) & 0xff)




/*@CLASS_C Fwc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


#define MAX_emC(A, B) ( (A) > (B) ? (A) : (B) )
#define MIN_emC(A, B) ( (A) < (B) ? (A) : (B) )
#define ABS_emC(A) ( (A) <0 ? -(A) : (A) )

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


inline int dbgstop_emC(){ return -1; }

#ifdef DEF_ObjectJc_SIMPLE
# if defined(DEF_ObjectJcpp_REFLECTION) || defined(DEF_ObjectJc_SYNCHANDLE) || defined(DEF_ObjectJc_REFLREF) || defined(DEF_ObjectJc_OWNADDRESS)
#   error DEF_ObjectJc_SIMPLE was defined together with one of the other DEF_ObjectJc...
# endif
#elif !defined(DEF_ObjectJc_REFLREF) 
#  define DEF_ObjectJc_REFLREF
#endif


//definition of StringJc to use this type before including emC/StringJc
typedef struct StringJc_T { 
  union CharSeqTypes_T { 
    char const* str; 
    struct StringBuilderJc_t* bu; 
    struct ObjectJc_T const* obj; 
  } addr; 
  VALTYPE_AddrVal_emC val;    //Note: Use same type as in STRUCT_AddrVal_emC 
} StringJc;
//old: typedef STRUCT_AddrVal_emC(StringJc, char const);


#include <emC/Base/Assert_emC.h>

#endif  // __os_types_def_common_h__
