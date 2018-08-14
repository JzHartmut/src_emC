#ifndef __applstdef_emC_h__
#define __applstdef_emC_h__
/**This headerfile contains all standard definition for usage the CRJ - CRuntimeJavalike - basicly system.
 * It is for ordinary S-Functions in Simulink without exception handling. 
 */

//Note: uncomment that to check whether this file is included:
//#error used_JC_stdef_SmlkSfunc

/**The compiler switch __CPLUSPLUSJcpp should set only if you want to work with the C++ variantes of Java2C translated files.
 * It is recommended also using a C++ compiler with C sources. Then do not set that compiler switch.
 */
//#define __CPLUSPLUSJcpp
#undef __CPLUSPLUSJcpp


//This block before <OSAL/os_types_def_common.h>
/**The compl_adaption.h should contain the compiler (and platform-) specific definitions of some data types with defined bit widhts.*/
#include <compl_adaption.h>

//This block before <OSAL/os_types_def_common.h>
#ifndef __TMWTYPES__  //Smlk defines the same struct twice, in tmwtypes.h and rtwtypes.h
  #include <tmwtypes.h>  //from simulink
#endif
#define DEFINED_float_complex     
#define float_complex creal32_T
#define DEFINED_double_complex
#define double_complex creal64_T


//NOTE: ASSERF_emC defined in fw_assert.h now.
//#define ASSERT_emC(COND) assertJc(COND)

/**Include this file always. It defines some types for C compilation compatible to C++. */
#include <OSAL/os_types_def_common.h>

#include <incApplSpecific/applConv/assert_ignore.h>  //Note: after os_types_def_common because extern_C


/**An EnhancedRef maybe necessary for BlockHeap concept. Here defines some macros in a simple form. */
//Include before fw_String.h because it is used there.
#include <incApplSpecific/applConv/EnhanceRef_simple.h>


/**Define __NoCharSeqJcCapabilities__ only for simple systems with simple StringJc usage. */
//#define __NoCharSeqJcCapabilities__



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

#include <emC/threadContext.h>
//#include <emC/Exception_emC.h>
#include <emC/ExcStacktrcNo.h>



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




/**Use the <fw_handle_ptr64.h> to deal with 32-bit-handle instead pointer.*/
#define __HandlePtr64__
#define DEFINED_nrEntries_Handle2Ptr 1000

//#include <appl_emC_h/definePrintFileMakros.h>
//#include <appl_emC_h/definePrintfMakros.h>
#include <appl_emC_h/definePrintfMakrosEmpty.h>

//extern_C void stop_DebugutilJc(struct ThreadContext_emC_t* _thCxt);


#define kMaxPathLength_FileJc 500

/**This define is set escpecially for compilation sources to use in mex64 dll. */
#define __SIMULINK_SFN__

#endif // __applstdef_emC_h__

