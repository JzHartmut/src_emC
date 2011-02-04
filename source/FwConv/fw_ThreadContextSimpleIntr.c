/**This file completes some platform-specific routines, 
 * which may be specially in a simple given environment.
 * 
 */



/*-------------------------------------------------------------------------------------------------*/
/**The implementation of thread behaviour is done for a simple system, which works only in interrupt levels,
 * at example a Signalprocessor.
 */
#include <OSAL/inc/os_thread.h>


/**This variable may be set if an interrupt-routine is started, 
 * and will be restored with the previous value if it is finihed.
 * Therefore the varible contains the index of the interrupt routine always.
 * The value 0 represents the back loop.
 */
int currentThread = 0;

/**There may be only 3 interrupt routines and the back loop.*/
OS_ValuePtr treadContextsOfTheInterruptLevels[4];


METHOD_C OS_ValuePtr os_getCurrentUserThreadContext()
{
  return treadContextsOfTheInterruptLevels[currentThread];
}

METHOD_C int os_setCurrentUserThreadContext(OS_ValuePtr mem)
{
  treadContextsOfTheInterruptLevels[currentThread] = mem;
  return 0;
}






