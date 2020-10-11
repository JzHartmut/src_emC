#include <emC/OSAL/os_time.h>
//#include "os_error.h"
#include <applstdef_emC.h>
#include <emC/Base/MemC_emC.h>
#include <emC/Base/Object_emC.h>
#include <emC/Base/String_emC.h>

/* Changes:
 * 2010-01-15 Hartmut adap os_FatalError (renamed, parameter)
 * 2010-01-15 Hartmut new null_OS_PtrValue supplied for user application.
 */

#ifdef DEF_REFLECTION_FULL
  #include <emC/OSAL/genRefl/os_file.crefl>
#elif defined(DEF_REFLECTION_OFFS)
  //#include <emC/OSAL/genRefl/os_file.crefloffs>
#elif defined(DEF_REFLECTION_SIMPLE)
  //ClassJc const refl_xyz = INIZ_ClassJc(refl_xyz, "XYZ");
#endif


AddrVal_emC null_OS_PtrValue  =  INIZ_AddrVal_emC(null, 0);

AddrVal_emC null_AddrVal_emC  =  INIZ_AddrVal_emC(null, 0);

