/** This file determines how enhanced references are defined and used.*/
//#include "ObjectRefJc_PlatformSpec.h"
#include <emC/Jc/ObjectJc.h>

#define ObjectJc_YREFDEF
typedef struct ObjectJc_Y_t{ ObjectArrayJc head; ObjectJcREF data[50]; } ObjectJc_Y;
  typedef TYPE_EnhancedRefJc(ObjectJc_Y);



