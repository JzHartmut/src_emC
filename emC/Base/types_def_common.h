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
#ifndef HGUARD_emCBase_types_def_common
#define HGUARD_emCBase_types_def_common


//If no reflection are used, anyway DEF_REFLECTION_NO should be defined. 
#if !defined(DEF_REFLECTION_SIMPLE) && !defined(DEF_REFLECTION_OFFS) && !defined(DEF_REFLECTION_FULL) && !defined(DEF_REFLECTION_NO)
  #define DEF_REFLECTION_NO
#endif

//If reflection are given Object has Reflection. TODO remove DEF_ObjectJc_REFL..REF against immediately usage ifndef DEF_REFLECTION_NO
//#if !defined(DEF_REFLECTION_NO) && !!defined(DEF_REFLECTION_NO)
//  #define DEF_ObjectJc_REFL..REF
//  #undef DEF_ObjectJc_..SIMPLE
//#endif


//Yet always defined with the reflection, TODO maybe a variant if using virtual C++
#if defined(DEF_REFLECTION_FULL) && !defined(DEF_ClassJc_Vtbl)
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif

#if defined(DEF_ClassJc_Vtbl) && !defined(DEF_CharSeqJcCapabilities)
  //yet always defined with DEF_ClassJc_Vtbl, first one is necessary. 
  #define DEF_CharSeqJcCapabilities
#endif 


#ifndef VIRTUAL_emC  //empty definition, no virtual operations
  #ifdef DEF_USEvirtual_emC
    #define VIRTUAL_emC virtual
  #else
    #define VIRTUAL_emC
  #endif
#endif
#ifndef OVERRIDE_VIRTUAL_emC
  #ifdef DEF_USEvirtual_emC
    #define OVERRIDE_VIRTUAL_emC override
  #else
    #define OVERRIDE_VIRTUAL_emC
  #endif
#endif

#ifndef INT32_MAX            //This definition is given if stdint.h is included before
//define only the data types of stdint.h
#define int8_t int8
#define uint8_t uint8
#define int16_t int16
#define uint16_t uint16
#define int32_t int32
#define uint32_t uint32
#define int64_t int64
#define uint64_t uint64
#ifndef DEF_DONOTDEF_intPTR
  #define intptr_t intPTR
#endif
#ifndef DEF_DONOTDEF_uintPTR
  #define uintptr_t uintPTR
#endif
#endif  //INT32_MAX, stdint is included


//plattformunabhaengige Ergaenzungen
//folgende Typen sind besser schreib- und lesbar
//#define ushort unsigned short int
#ifndef uint
  #define uint unsigned int
#endif
//#define ulong unsigned long int



/**Union of int64 and its fractions. */
typedef union int64_uhilo_T { int64 v; int64_hilo hilo; } int64_uhilo;




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
  //#define C_CAST(TYPE, PTR) reinterpret_cast<TYPE>(const_cast<TYPE>(PTR))
  #define C_CAST(TYPE, PTR) reinterpret_cast<TYPE>(PTR)
  #define WR_CAST(TYPE, PTR) const_cast<TYPE>(PTR)
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
  #define C_CAST(TYPE, PTR) ((TYPE)(PTR))
  #define WR_CAST(TYPE, PTR) ((TYPE)(PTR))
  #define STATIC_CAST(TYPE, PTR) ((TYPE)(PTR))
#endif
//#endif//__NoReflection__


#ifndef OFFSET_IN_STRUCT
#define OFFSET_IN_STRUCT(TYPE, FIELD) ((int)(intptr_t)&(((TYPE*)0)->FIELD))
#define SIZEOF_IN_STRUCT(TYPE, FIELD) ((int)(sizeof((TYPE*)0)->FIELD))
#endif


//Note: definition of bool, true, false is compiler/system-specific. Removed from here. See compl_adaption.h


//========================================================================

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

typedef struct Addr8_emC_T { int32 c[2]; } Addr8_emC;



/**This definition defines a uint32 handle which is used instead a pointer for the 64-bit-System,
 * but in the 32-bit-System the handle value is equal the pointer value.
 * The generated code (from Simulink) uses the uint32 handle type, because the connection between blocks
 * is done with the uint32 handle connection. For internal data access with 64-bit-Pointer the Simulink S-Functions
 * translate the handle value to a pointer via a common pointer table. The handle is the index to the table entry. 
 * Used especially in Simulink S-Functions for bus elements and outputs which are references.
 * In this case, for a 32 bit system, both, the handle and pointer are accessible as union.
 * old: OS_HandlePtr
 * 
 */
#define XXXXHandlePtr_emC(TYPE, NAME) uint32 NAME    //for find / search: HandlePtr_emC ( TYPE, NAME)




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
#ifdef DEF_Type_HandleADDR_emC
  #define HandleADDR_emC(TYPE) DEF_Type_HandleADDR_emC
  //Note: <emC/Base/types_def_common.h> should be included before in this file.
  #define DEF_HandlePtr64
  #include <emC/Base/Handle_ptr64_emC.h>
#else //not DEF_Type_HandleADDR_emC
  /**The HandleADDR_emC is the type reference.*/
  #define HandleADDR_emC(TYPE) TYPE*

  /**It presents the TYPE-correct address as pointer in C/++*/
  #define addr_HandleADDR_emC(HANDLE, TYPE) (HANDLE)

  /**It presents an integer value as handle, may be identical with the address. */
  #define handle_HandleADDR_emC(HANDLE) ((intPTR)(HANDLE))


  //copied from emC/Base/Handle_ptr64_emC.h, ndef DEF_HandlePtr64. It is the older definition, but more complete.
  /**Invocation of INIT is empty because there is not Handle2Ptr. */
  #define INIT_Handle2Ptr()  
  
  /**Registeres the pointer and gets the handle.
   * For the 32 bit version the pointer are not registered, the pointer value is the handle.
   * @param PTR given pointer as void*
   * @param NAME unused here because nothing is registered.
   * @param H Address of the handle, type is uint32*. The handle will be set with the pointer value.
   * @return null, no error
   * If the ptr is registered already, it is okay. The name will be ignored then, it returns the given handle. 
   */ 
  #define registerPtr_Handle2Ptr(PTR, NAME) (uint32)(PTR)
  //old: setPtr_Handle2Ptr

  #define debug_Handle2Ptr(H, N1, N2, TEXT)  //empty.
  
  #define handle_Handle2Ptr(PTR) ((uint32)PTR)

  /**Delivers the handle to the given pointer, only for 32-bit-Target system.
   * The handle is the same value as the 32 bit pointer. It is delivered as uint32.
   */
  #define HANDLE_Handle2Ptr(PTR) ((uint32)PTR) 
  /**This is the variant to get a pointer from handle for 32-bit-systems. The pointer is the same value as the handle.
   * The macro delivers null for 'no error'.
   * @param H handle as uint32 value. The value is the memory address.
   * @param P_PTR address of the pointer. The address should be given as type void**
   */  
  #define getPtr_Handle2Ptr(H, P_PTR) ( *(P_PTR)= (void*)(H), null)
  #define ptr_Handle2Ptr(HANDLE) ((void*)(HANDLE)) 
  #define PTR_Handle2Ptr(handle, TYPE) ((TYPE*) handle)
  #define PTRclr_Handle2Ptr(handle, TYPE) ((TYPE*) handle)
  
  /**For a 64 bit system using indices for handle it removes the address. For 32 it does nothing. Returns the pointer. */
  #define clearHandle_Handle2Ptr(HANDLE)



#endif  //DEF_HandlePtr64





/**Default definition int32 as the type for the length or value 
 * in a struct{ addr, val} defined with STRUCT_AddrVal_emC(...). */
#ifndef VALTYPE_AddrVal_emC            //possible to define in applstdef_emC.h
  #define VALTYPE_AddrVal_emC int32    //the default
#endif

/**This macro defines a struct with a pointer to the given type and a integer number.
 * Usual it can be used to describe exactly an 1-dimensional array. The integer number is the number of elements,
 * the size in memory is (sizeof(TYPE) * numberOfElements). 
 * This struct should pass with 2 register for call by value or return by value, usual supported by the compiler.
 */
#define STRUCT_AddrVal_emC(NAME, TYPE) struct NAME##_T { TYPE* addr; VALTYPE_AddrVal_emC val; } NAME



/**The type AddrVal_emC handles with a address (pointer) for a 8 byte alignment. */
typedef STRUCT_AddrVal_emC(AddrVal_emC, Addr8_emC);

#define INIZ_AddrVal_emC(ADDR, VAL) { (Addr8_emC*)(intPTR)(ADDR), VAL }

#define ADDR_AddrVal_emC(THIS, TYPE) ((TYPE*)(THIS).addr)

#define VAL_AddrVal_emC(THIS) ((THIS).val)

#define SET_AddrVal_emC(THIS, ADDR, VAL) { (THIS).addr = (Addr8_emC*)(intPTR)(ADDR); (THIS).val = VAL; }

#define SETADDR_AddrVal_emC(THIS, ADDR) ( (THIS).addr = (Addr8_emC*)(intPTR)(ADDR) )

#define SETVAL_AddrVal_emC(THIS, VAL) ( (THIS).val = VAL )



//Compatibility:
#define OS_PtrValue AddrVal_emC

/**Compatibility with older typedef of OS_PtrValue. */
//#define OS_PtrValue PtrVal_MemUnit


#ifndef STRUCT_AddrVal_emC  //force deprecated compatibility
  #define STRUCT_AddrVal_emC(NAME, TYPE) OS_PtrVal_DEF(NAME, TYPE)
#endif

#ifdef DEF_HandlePtr64
  #define XXXXHandlePtr32Union_emC(TYPE) union {uint32 h; }
#else
  #define XXXXHandlePtr32Union_emC(TYPE) union {uint32 h; TYPE* p; }
#endif


/**An instance which contains null-values. */
extern AddrVal_emC null_AddrVal_emC;



/**Defines a struct with a byte address and the length. */
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
#define CHAR4_emC(C1, C2, C3, C4)  ((((uint32)C4)<<24) | (( ((uint32)C3)& 0xff)<<16) | (((uint16)C2)<<8) | ((C1) & 0xff))




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

/*@CLASS_C int32_complex @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef DEFINED_int32_complex
typedef struct int32_complex_T {
  int32 re, im;
} int32_complex;
#endif

/*@CLASS_C int16_complex @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef DEFINED_int16_complex
typedef struct int16_complex_T {
  int16 re, im;
} int16_complex;
#endif

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


static inline int dbgstop_emC(){ return -1; }

//#if defined(DEF_ObjectJc_..SIMPLE) || !defined(DEF_ObjectJc_FULLCAPABILITY)
//# if defined(DEF_ObjectJcpp_REFLECTION) || defined(DEF_ObjectJc_SYNCHANDLE) || defined(DEF_ObjectJc_OWNADDRESS)
//#   error DEF_ObjectJc_..SIMPLE was defined together with one of the other DEF_ObjectJc...
//# endif
//#elif !!defined(DEF_REFLECTION_NO) 
//#  define DEF_ObjectJc_REFL..REF
//#endif



//definition of StringJc to use this type before including emC/StringJc
typedef struct StringJc_T { 
  union CharSeqTypes_T { 
    char const* str; 
    struct StringBuilderJc_t* bu; 
    struct ObjectJc_T const* obj; 
    #ifdef __cplusplus
    class CharSequenceJc* csq;
    #endif
  } addr; 
  VALTYPE_AddrVal_emC val;    //Note: Use same type as in STRUCT_AddrVal_emC 
} StringJc;
#define DEFINED_StringJc_emC

//old: typedef STRUCT_AddrVal_emC(StringJc, char const);


/**StringJc object containing null-values. */
extern_C StringJc const null_StringJc;

/**StringJc object containing an empty String, ref to  "", lenght = 0 */
extern_C StringJc const empty_StringJc;



/**Initializer-Macro for constant StringJc, initialize the StringJc-reference to a zero-terminated text.
 * The length of the text
 * is not stored inside StringJc, the length bits are setted to there maximum 
 * (value of ,,mLength_StringJc,,, see ,,fw_Platform_conventions.h,,)
 * to detect this constellation.
 * @param TEXT should be a text-literal only. If it references a char-array, 
 *             a problem with persistence may existing.
 */
#define INIZ_z_StringJc(TEXT) { TEXT, kIs_0_terminated_StringJc}
#define CONST_z_StringJc(TEXT) INIZ_z_StringJc(TEXT)

/**Initializer-Macro for constant StringJc, initialize the StringJc-reference to a text with known length.
 * Using this macro instead ,,CONST_StringJc(...),, saves calculation time to calculate the ,,strlen(),,.
 * @param TEXT should be a text-literal only. If it references a char-array, 
 *             a problem with persistence may existing.
 * @param LEN The length as number. Do not use methods like strlen(...)
 *            to determine the length, because this is a const-initializing-macro.
 *            In C++, methods are syntaxtically able to use, but it produces more machine code
 *            and the definition cannot store in a const segment. In C it is an error.
 */
#define INIZ_StringJc(TEXT, LEN) { {TEXT}, LEN }
#define CONST_StringJc(TEXT, LEN) INIZ_StringJc(TEXT, LEN)
#define NULL_StringJc { {null}, 0}



//NOTE: do nothing include here additinally, the user should decide what is included in its applstdef_emC.h!
//#include <emC/Base/Assert_emC.h>

#endif  //HGUARD_emCBase_types_def_common
