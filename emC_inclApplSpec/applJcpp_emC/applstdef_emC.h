#ifndef __applstdef_emC_h__
#define __applstdef_emC_h__

//Uncomment to check whether used:
//#error Uses applCpp32_emC/applstdef_emC.h


/**The compiler switch __CPLUSPLUSJcpp should set only if you want to work with the C++ variantes of Java2C translated files.
 * It is recommended also using a C++ compiler with C sources. Then do not set that compiler switch.
 */
#define __CPLUSPLUSJcpp
//#undef __CPLUSPLUSJcpp
//#define __cplusplus

#ifndef DEF_ObjectJc_FULL  //prevent warning if defined as compiler argument.
#define DEF_ObjectJc_FULL
#endif
//This block before <OSAL/types_def_common.h>
/**The compl_adaption.h should contain the compiler (and platform-) specific definitions of some data types with defined bit widhts.*/
#include <compl_adaption.h>



/**Define __NoCharSeqJcCapabilities__ only for simple systems with simple StringJc usage. */
//#define __NoCharSeqJcCapabilities__
//#define __NoStringJcCapabilities__

/**An EnhancedRef maybe necessary for BlockHeap concept. Here defines some macros in a simple form. */
//Note: Include before fw_String.h because it is used there.
#include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>
//#include <emC_srcApplSpec/applConv/EnhanceRef_Blockheap.h>


//#include <emC_srcApplSpec/applConv/assert_ignore.h>  //Note: after types_def_common because extern_C
//#include <emC_srcApplSpec/applConv/assert_simpleStop.h>  //Note: after types_def_common because extern_C
#include <emC_srcApplSpec/applConv/assert_THROW.h>  //Note: after types_def_common because extern_C


/**Use the exception handling header file - or define the macros TRY, by yourself. */
/** If this define is setted, the TRY, CATCH and THROW makros use the C++ keywords
  * try, throw and catch. All sources, also the *.c-Sources of the CRuntimeJavalike,
  * may be compiled with a C++-Compiler.
  *
  * If the macro is not setted, the TRY, CATCH and THROW makros use
  * the longjmp version. See fw_Exception.h. 
  * It is also possible to use longjmp in a C++ environment,
  * but destructors of local stack instances in skipped subroutines are ignored.
  * It must be secured that no critical destructors are used, or a FINALLY is used there.
  * Another reason for using C++ exception handling in a PC environment is: Operation system exceptions.
  * On visual studio C++ compiler you should set the option /EHa and /TP for C++ compilation of C sources.
  * The C variant with longjmp should only used if C++ is not available.
  */
#define __TRYCPPJc

#ifdef DEF_ThreadContext_SIMPLE
  #include <emC_srcApplSpec/SimpleNumCNoExc/ExcStacktrcNo_emC.h>
#else
  #include <emC_srcApplSpec/applConv/ThreadContextStacktrc_emC.h>
  #include <emC_srcApplSpec/applConv/Exception_emC.h>
#endif


/**Under Test conditions, the check of Stacktrace consistence should be activated. 
 * Because a forgotten STACKTRC_LEAVE-macro call won't be detected else,
 * and the stacktrace is corrupt for later usage.
 * Deactivate this macro in release versions.
 */
#ifdef _DEBUG
  #define TEST_STACKTRCJc 
#else
  #undef TEST_STACKTRCJc
#endif	


#define abs_complex(VAL) sqrtf( (VAL).re * (VAL).re + (VAL).im * (VAL).im )


/**Use the <fw_handle_ptr64.h> to deal with 32-bit-handle instead pointer.*/
//#define __HandlePtr64__
//#define DEFINED_nrEntries_Handle2Ptr 1000

//PRINTX
//#include <emC_srcApplSpec/applConv/definePrintFileMakros.h>
//#include <emC_srcApplSpec/applConv/definePrintfMakros.h>
#include <emC_srcApplSpec/applConv/definePrintfMakrosEmpty.h>


/**Maximal length of path in a FileDescription_OSAL-structure.
* NOTE: old name kMaxPathLength_OS_FileDescription
*/
#define kMaxPathLength_FileDescription_OSAL 480


/**size of a safety area inside any allocMem data range. It can be 0. Set for debug and check approaches. */
#ifndef sizeSafetyArea_allocMemC
#define sizeSafetyArea_allocMemC 4096
#endif



//#include <string.h> //memcpy
//#include <emC/Base/SystemInit_emC.h>
//#include <emC/Base/Handle_ptr64_emC.h>

#endif // __applstdef_emC_h__
