#include <os_types_def.h>
#include "OSAL_UserExceptionAndDebug.h"

#include <stdio.h>

METHOD_C void debug__IndexOutOfBoundsException_OSALUserEXCEPT(char const* msg, int nr) {
  printf("%s %d\r", msg, nr); 
}

METHOD_C void stop_IndexOutOfBoundsException_OSALUserEXCEPT(int ix)
{
  printf("checkIndexOutOfBounds_UserEXCEPT failure: %d\n", ix);
}


void exec_DEBUGOUT2_OSALUserDEBUG(char const* STR, int32 VAL)
{
  printf(STR, VAL);
}