#include "TestAtomic.h"

#include <Fwc/fw_Exception.h>

    

void main()
{
  STACKTRC_ENTRY("main");  //it ininitalizes the Stacktrace in the Thread-context automatically.
  //os_initLib();
  { //
    /**Test routines: */
    //alloc1();

    test1();
  }
  STACKTRC_LEAVE;

}


