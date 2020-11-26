#include <emC/OSAL/Environment_OSALemC.h>
#include <stdlib.h>

//Note: This routine is part of OSAL because
//a specific embedded platform may need a specific implementation
char const* getEnvironment_OSALemC(char const* name) {
  return getenv(name);
}


