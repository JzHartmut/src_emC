#ifndef __applstdefJc_h__
#define __applstdefJc_h__

//Uncomment to check whether used:
//#error Uses srcApplInspc/applstdef_emC.h


/**The compiler switch __CPLUSPLUSJcpp should set only if you want to work with the C++ variantes of Java2C translated files.
 * It is recommended also using a C++ compiler with C sources. Then do not set that compiler switch.
 */
//#define __CPLUSPLUSJcpp
#undef __CPLUSPLUSJcpp


//This block before <OSAL/os_types_def_common.h>
/**The os_types_def.h should contain the compiler (and platform-) specific definitions of some data types with defined bit widhts.*/
#include <compl_adaption.h>

#define DEFINED_float_complex     
#define float_complex creal32_T
#define DEFINED_double_complex
#define double_complex creal64_T
/**Include this file always. It defines some types for C compilation compatible to C++. */
#include <OSAL/os_types_def_common.h>

#include <fw_assert.h>  //Note: after os_types_def_common because extern_C



/**Include this file always. It defines some things usefull for all sources. */
#include <Fwc/fw_SimpleC.h>
#include <Fwc/fw_MemC.h>



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
#ifdef __cplusplus
  #define __TRYCPPJc
#else
  #undef __TRYCPPJc  //cannot be used on C language
#endif

//Include before fw_String.h because it is used there.
#include <FwConv_h\EnhanceRef_BlockHeap.h>
/**Define StringJc firstly, especially before fw_Exception.h> */
#include <Fwc/fw_String.h>
/**Use the exception handling header file - or define the macros TRY, by yourself. */
#include <Fwc/fw_threadContext.h>
#include <Fwc/fw_Exception.h>
//#include <Fwc/fw_ExcStacktrcNo.h>


//Use full capability for ObjectJc, necessary for Pointer check and reflection.
#include <Fwc/objectBaseC.h>


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


//PRINTX
#include <FwConv_h/definePrintFileMakros.h>
//#include <FwConv_h/definePrintfMakros.h>


extern_C void stop_DebugutilJc(struct ThreadContextFW_t* _thCxt);

#define kMaxPathLength_FileJc 500


INLINE_Fwc int stopNAN(){ return 0; }

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



#endif // __applstdefJc_h__
