#include <emC/OSAL/os_time.h>
//#include "os_error.h"
#include <applstdef_emC.h>
#include <emC/Base/MemC_emC.h>
#include <emC/Base/Object_emC.h>

float microsecondsPerClock_Time_emC = 0;

int32 clocksPerMicro_Time_emC = 0;

int32 clocksFloatPerMicro_Time_emC = 0;


/* Changes:
 * 2010-01-15 Hartmut adap os_FatalError (renamed, parameter)
 * 2010-01-15 Hartmut new null_OS_PtrValue supplied for user application.
 */

#ifdef DEF_REFLECTION_FULL
  #include <emC/OSAL/genRefl/os_time.crefl>  //include here, different Implementations on osal level.
  #include <emC/OSAL/genRefl/os_file.crefl>
#elif defined(DEF_REFLECTION_OFFS)
  #include <emC/OSAL/genRefl/os_time.crefloffs>  //include here, different Implementations on osal level.
  #include <emC/OSAL/genRefl/os_file.crefloffs>
#elif defined(DEF_REFLECTION_SIMPLE)
  ClassJc const reflection_xyz = INIZ_ClassJc(reflection_xyz, "XYZ");
#endif

OS_TimeStamp* ctorM_OS_TimeStamp  (  MemC mem)
{ int size = mem.val;
  if (size < sizeof(OS_TimeStamp))
  { THROW_s0n(IllegalArgumentException, "OS_TimeStamp with fault size", size, 0);
    return null;
  }
  else {
    OS_TimeStamp* ythis = ADDR_MemC(mem, OS_TimeStamp);
    ythis->time_sec = 0;
    ythis->time_nsec = 0;
    return ythis;
  }
}


AddrVal_emC null_OS_PtrValue  =  INIZ_AddrVal_emC(null, 0);

AddrVal_emC null_AddrVal_emC  =  INIZ_AddrVal_emC(null, 0);

