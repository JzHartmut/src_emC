#ifndef __platform_msgDisp_h__
#define __platform_msgDisp_h__
/**This file defines some platform specific macros which allows message creation and dispatching.
 * Hartmut Schorrig, created 2013-12-18
 */
 


#include <stdio.h>
#define msg4_MSG(MSG, VAL0, VAL1, VAL2, VAL3) printf("%S\n",MSG, VAL0, VAL1, VAL2, VAL3)
#define msg_MSG(MSG) printf("%s\n",MSG);



#endif //__platform_msgDisp_h__
