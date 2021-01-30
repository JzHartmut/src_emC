#ifndef HGUARD_applstdef_emC
#define HGUARD_applstdef_emC
/**This headerfile contains all standard definition for usage the emC - embedded multiplatform C(++) - basicly source system.
 * It is for a Applications in C(++) 
 * with 64 bit memory addresses on PC 
 * with Reflection, StringJc
 * with Excpetion handling with C++ throw to support asynchron exceptions. 
 */

//Note: uncomment that to check whether this file is included:
//#error Uses stdef_ApplCpp64/applstdef_emC.h


/**Define the granularity of the ObjectJc base class: */
//#define DEF_ObjectSimple_emC
//#define DEF_ObjectJc_SIMPLE
#define DEF_ObjectJc_REFLREF
#define DEF_ObjectJc_SYNCHANDLE
#define DEF_ObjectJcpp_REFLECTION
#define DEF_ObjectJc_OWNADDRESS
#define DEF_ObjectJc_LARGESIZE

/**Define of the offering of Reflection information: */
//#define DEF_REFLECTION_NO
//#define DEF_REFLECTION_SIMPLE
//#define DEF_REFLECTION_OFFS
#define DEF_REFLECTION_FULL
#if defined(DEF_REFLECTION_FULL)
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif


/**If set then the target should not use string operations */
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


//To work with handle instead pointer in data struct and 
#define DEF_Type_HandleADDR_emC uint32
#ifndef DEFINED_nrEntries_Handle2Ptr
  #define DEFINED_nrEntries_Handle2Ptr 1000
#endif
//#define DEF_HandlePtr64




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



/**Maximal length of path in a FileDescription_OSAL-structure. */
 // NOTE: old name kMaxPathLength_OS_FileDescription
#define kMaxPathLength_FileDescription_OSAL 480

/**size of a safety area inside any allocMem data range. It can be 0. Set for debug and check approaches. */
#define sizeSafetyArea_allocMemC 4096

#include <compl_adaption.h>
#include <emC/Base/Assert_emC.h>
#include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>
#include <emC/Base/Exception_emC.h>




#define abs_complex(VAL) sqrtf( (VAL).re * (VAL).re + (VAL).im * (VAL).im )



//#include <emC_srcApplSpec/applConv/definePrintFileMakros.h>
//#include <emC_srcApplSpec/applConv/definePrintfMakros.h>
#include <emC_srcApplSpec/applConv/definePrintfMakrosEmpty.h>


//extern_C void stop_DebugutilJc(struct ThreadContext_emC_t* _thCxt);




#endif // HGUARD_applstdef_emC
