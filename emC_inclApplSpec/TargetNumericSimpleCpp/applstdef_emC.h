#ifndef HGUARD_applstdef_emC
#define HGUARD_applstdef_emC

//Uncomment to check whether used:
//#error Uses applCpp32_emC/applstdef_emC.h


/**Define the granularity of the ObjectJc base class: */
#define DEF_ObjectSimple_emC
//#define DEF_ObjectJc_SYNCHANDLE
//#define DEF_ObjectJcpp_REFLECTION
//#define DEF_ObjectJc_OWNADDRESS
//#define DEF_ObjectJc_LARGESIZE

/**Define of the offering of Reflection information: */
#define DEF_REFLECTION_NO
//#define DEF_REFLECTION_SIMPLE
//#define DEF_REFLECTION_OFFS
//#define DEF_REFLECTION_FULL


/**If set then the target should not use string operations */
//#define DEF_NO_StringUSAGE
//#define DEF_CharSeqJcCapabilities


/**If set, without complex thread context, without Stacktrace*/
#define DEF_ThreadContext_HEAP_emC
#define DEF_ThreadContext_STACKTRC
//#define DEF_ThreadContext_STACKUSAGE
//#define DEF_ThreadContext_STACKTRC_NO

/**Use the exception handling header file - or define the macros TRY, by yourself. */
/** If DEF_Exception_TRYCpp is setted, the TRY, CATCH and THROW makros use the C++ keywords
  * try, throw and catch. All sources, also the *.c-Sources of the CRuntimeJavalike,
  * may be compiled with a C++-Compiler.
  *
  * If DEF_Exception_longjmp is setted, the TRY, CATCH and THROW makros use
  * the longjmp version.  
  * It is also possible to use longjmp in a C++ environment,
  * but destructors of local stack instances in skipped subroutines are ignored.
  * It must be secured that no critical destructors are used, or a FINALLY is used there.
  * Another reason for using C++ exception handling in a PC environment is: Operation system exceptions.
  * On visual studio C++ compiler you should set the option /EHa and /TP for C++ compilation of C sources.
  * The C variant with longjmp should only used if C++ is not available.
  *
  * If DEF_Exception_NO is set, is is for well tested systems. 
  * Then THROW can create only a message in a runtime environment.
  */
#define DEF_Exception_TRYCpp
//#define DEF_Exception_longjmp
//#define DEF_Exception_NO


//If set, no assertion is done:
//#define ASSERT_IGNORE_emC

/**Selects working with Blockheap*/
//#define USE_BlockHeap_emC
//#define DEF_BlockHeap_GARBAGECOLLECTOR


/**To work with handle instead pointer in data struct and
 * It is especially for Simulink usage. 
 */
//#define DEF_Type_HandleADDR_emC uint32
//#define DEFINED_nrEntries_Handle2Ptr 1000
//#define DEF_HandlePtr64

//
//What to start as main:
//
#ifndef DEF_MainAppl
/**select only one of this to debug special tests: */
//#define DEF_XYZ
#define DEF_MainAppl
#endif //ndef DEF_MainAppl



/**Defines the type for the length or value in a struct{ addr, val} defined with STRUCT_AddrVal_emC(...). */
#define VALTYPE_AddrVal_emC int32


/**Bits of length of constant string adequate to VALTYPE_AddrVal_emC. 
 * It have to be a mask with set bits on right side (all last significant bits).
 * The next 2 bits left are used internally for designation of String.
 * see [[mNonPersists__StringJc]], [[mThreadContext__StringJc]].
 * See also [[kIsCharSequence_StringJc]]
 * The following bits left side are used for enhanced references, see kBitBackRef_ObjectJc and mBackRef_ObjectJc.
 * If enhanced references are not used, a StringJc can occupy all bits, for example all 16 bits for 16-bit-integer systems.
 */
#define mLength_StringJc 0x00003fff




/**This is to compile C++ classes of emC if __cplusplus is set.
  For C compilation this is ineffective because __cplusplus is necessary too*/
#define USE_cplusplus_emC
#define DEF_cplusplus_emC
#define DEF_CPP_COMPILE


#define DEFINED_getVarAddrType_CalcExpr

#define kMaxPathLength_FileDescription_OSAL 512
#define sizeSafetyArea_allocMemC 256


#include <compl_adaption.h>
#include <emC/Base/Assert_emC.h>
#include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>
#include <emC/Base/Exception_emC.h>



//including the project specific reflOffs.h defines DEF_REFLECTION_OFFS 
#ifdef DEF_REFLECTION_OFFS
  //contains DEF_REFLOFFS_...for all defined ClassJc
  #include <emC_Exmpl_Ctrl/genRefl/emC_Exmpl_Ctrl_reflOffs.cpp.h>
  //Note: the adequate *.reloffs.c should be part of the project:
#endif








#endif //HGUARD_applstdef_emC
