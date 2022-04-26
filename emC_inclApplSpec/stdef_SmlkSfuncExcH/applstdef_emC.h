#ifndef HGUARD_applstdef_emC
#define HGUARD_applstdef_emC
/**This headerfile contains all standard definition for usage the emC - embedded multiplatform C(++) - basicly source system.
 * It is for a Applications in C(++) 
 * with 64 bit memory addresses on PC 
 * with Reflection, StringJc
 * with Excpetion handling with C++ throw to support asynchron exceptions. 
 * It is for S-Functions in Simulink with exception handling. 
 */


//Note: uncomment that to check whether this file is included:
//#error used_Jc_stdef_SmlkSfuncExcH


/**Define the granularity of the ObjectJc base class: */
//#define DEF_ObjectSimple_emC
//#define DEF_ObjectJc_SIMPLE
//#define DEF_ObjectJc_REFLREF
#define DEF_ObjectJc_SYNCHANDLE
#define DEF_ObjectJcpp_REFLECTION
#define DEF_ObjectJc_OWNADDRESS
#define DEF_ObjectJc_LARGESIZE

/**Define of the offering of Reflection information: */
//#define DEF_REFLECTION_NO
//#define DEF_REFLECTION_SIMPLE
//#define DEF_REFLECTION_OFFS
#define DEF_REFLECTION_FULL


//If set then the target should not use string operations
//#define DEF_NO_StringUSAGE
//#define DEF_NO_StringJcCapabilities


/**If set, without complex thread context, without Stacktrace*/
#define DEF_ThreadContext_HEAP_emC
#define DEF_ThreadContext_STACKTRC
//#define DEF_ThreadContext_STACKUSAGE
//#define DEF_ThreadContext_STACKTRC_NO

#define DEF_Exception_TRYCpp
//#define DEF_Exception_longjmp
//#define DEF_Exception_NO


//If set, no assertion is done:
//#define ASSERT_IGNORE_emC

/**Selects working with Blockheap*/
//#define USE_BlockHeap_emC
//#define DEF_BlockHeap_GARBAGECOLLECTOR

#if defined(DEF_REFLECTION_FULL)
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif


//This block before <emC/Base/types_def_common.h>
#include <tmwtypes.h>  //from simulink
#define DEFINED_float_complex     
#define float_complex creal32_T
#define DEFINED_double_complex
#define double_complex creal64_T

//To work with handle instead pointer in data struct and 
#define DEF_Type_HandleADDR_emC uint32
#define DEF_HandlePtr64
#ifndef DEFINED_nrEntries_Handle2Ptr
  #define DEFINED_nrEntries_Handle2Ptr 1000
#endif

/**With this compiler switch the reflection should be included or not. DEF_REFLECTION_NO may be set by compiler options. */
//#define DEF_REFLECTION_NO
#if !defined(DEF_REFLECTION_NO) && !defined(DEF_REFLECTION_OFFS) && !defined(DEF_REFLECTION_SIMPLE) 
  #define DEF_REFLECTION_FULL
#endif



/**This is to compile C++ classes of emC if __cplusplus is set.
  For C compilation this is ineffective because __cplusplus is necessary too*/
#define USE_cplusplus_emC
#define DEF_cplusplus_emC
#define DEF_CPP_COMPILE


#define DEFINED_getVarAddrType_CalcExpr

#define kMaxPathLength_FileDescription_OSAL 512
#define sizeSafetyArea_allocMemC 256


#include <compl_adaption.h>
#ifndef HGUARD_emCBase_types_def_common
  #include <emC/Base/types_def_common.h>    // should be normally included in compl_adaption.h
#endif

//This header defines all basics derived from the settings here:
#include <emC/Base/applstdef_common.h>






//#include <emC_srcApplSpec/applConv/definePrintFileMakros.h>
//#include <emC_srcApplSpec/applConv/definePrintfMakros.h>
#include <emC_srcApplSpec/applConv/definePrintfMakrosEmpty.h>


//extern_C void stop_DebugutilJc(struct ThreadContext_emC_t* _thCxt);


/**This define is set escpecially for compilation sources to use in mex64 dll. */
#define __SIMULINK_SFN__


#endif // HGUARD_applstdef_emC

