#ifndef __checkStack_emC_h__
#define __checkStack_emC_h__
#include <applstdef_emC.h>

int buildCheckStack_emC(void* addr, int stacksize);

/**Set a breakpoint in this routine. An error situation needs debugging. 
 * For non debugging this routine checks and returns true for ok
 */
bool testCheckStack_emC(void* addr, int checkvalue, int stacksize);


#endif // __checkStack_emC_h__
