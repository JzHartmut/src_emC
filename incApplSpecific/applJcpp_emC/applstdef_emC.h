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

//This block before <OSAL/os_types_def_common.h>
/**The compl_adaption.h should contain the compiler (and platform-) specific definitions of some data types with defined bit widhts.*/
#include <compl_adaption.h>

/**Include this file always. It defines some types for C compilation compatible to C++. */
#include <OSAL/os_types_def_common.h>

#include <sourceApplSpecific/applConv/assert_simpleStop.h>  //Note: after os_types_def_common because extern_C
//#include <sourceApplSpecific/applConv/assert_ignore.h>  //Note: after os_types_def_common because extern_C


/**An EnhancedRef maybe necessary for BlockHeap concept. Here defines some macros in a simple form. */
//Note: Include before fw_String.h because it is used there.
#include <sourceApplSpecific/applConv/EnhanceRef_simple.h>
//#include <sourceApplSpecific/applConv/EnhanceRef_Blockheap.h>

/**Define __NoCharSeqJcCapabilities__ only for simple systems with simple StringJc usage. */
//#define __NoCharSeqJcCapabilities__
//#define __NoStringJcCapabilities__



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

#include <sourceApplSpecific/applConv/ThreadContextStacktrc_emC.h>
#include <sourceApplSpecific/applConv/Exception_emC.h>
//#include <emC/ExcStacktrcNo.h>



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
//#include <sourceApplSpecific/applConv/definePrintFileMakros.h>
//#include <sourceApplSpecific/applConv/definePrintfMakros.h>
#include <sourceApplSpecific/applConv/definePrintfMakrosEmpty.h>


/**Maximal length of path in a FileDescription_OSAL-structure.
* NOTE: old name kMaxPathLength_OS_FileDescription
*/
#define kMaxPathLength_FileDescription_OSAL 480



#endif // __applstdef_emC_h__
