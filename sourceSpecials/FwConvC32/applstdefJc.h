#ifndef __applstdefJc_h__
#define __applstdefJc_h__


/**Some warnings should be disabled in default, because there are not the source of errors,
 * but present in normal software development.
 */
//#pragma warning(disable:4204) //nonstandard extension used : non-constant aggregate initializer TODO prevent


#pragma warning(disable:4100) //unused argument
//#pragma warning(disable:4127) //conditional expression is constant
#pragma warning(disable:4214) //nonstandard extension used : bit field types other than int
#pragma warning(disable:4189) //local variable is initialized but not referenced
#pragma warning(disable:4201) //nonstandard extension used : nameless struct/union
#pragma warning(disable:4310) //cast truncates constant value

//C++
#pragma warning(disable:4514) //unreferenced inline function has been removed
//#pragma warning(disable:4512) //assignment operator could not be generated
//#pragma warning(disable:4268) //'const' static/global data initialized with compiler generated default constructor fills the object with zeros
#pragma warning(disable:4068) //unknown pragma
#pragma warning(disable:4244) //conversion from '__int64' to 'double', possible loss of data
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //
#pragma warning(disable:4127) //




/**The compiler switch __CPLUSPLUSJcpp should set only if you want to work with the C++ variantes of Java2C translated files.
 * It is recommended also using a C++ compiler with C sources. Then do not set that compiler switch.
 */
//#define __CPLUSPLUSJcpp
#undef __CPLUSPLUSJcpp


/**The os_types_def.h should contain the compiler (and platform-) specific definitions of some data types with defined bit widhts.*/
#include <os_types_def.h>

/**Include this file always. It defines some types for C compilation compatible to C++. */
#include <os_types_def_common.h>

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

/**Use the exception handling header file - or define the macros TRY, by yourself. */
#include <Fwc/fw_Exception.h>

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


//NOTE: ASSERF_Fwc defined in fw_assert.h now.
//#define ASSERT_Fwc(COND) assertJc(COND)







#endif // __applstdefJc_h__
