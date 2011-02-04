#include <os_time.h>
#include "os_error.h"

/* Changes:
 * 2010-01-15 Hartmut adap os_FatalError (renamed, parameter)
 * 2010-01-15 Hartmut new null_OS_PtrValue supplied for user application.
 */


OS_TimeStamp* ctorM_OS_TimeStamp(OS_PtrValue mem)
{ int size = value_OS_PtrValue(mem);
  if (size < sizeof(OS_TimeStamp))
  { os_FatalError(-1, "OS_TimeStamp with fault size", size, 0);
    return null;
  }
  else {
    OS_TimeStamp* ythis = PTR_OS_PtrValue(mem, OS_TimeStamp);
    ythis->time_sec = 0;
    ythis->time_nsec = 0;
    return ythis;
  }
}


OS_PtrValue null_OS_PtrValue = CONST_OS_PtrValue(0, null);

