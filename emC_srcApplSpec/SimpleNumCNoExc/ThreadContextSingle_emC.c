#include <applstdef_emC.h>

//Note: This source should used if an application or dll with own static memory runs only in 1 thread.
//No switch of context, instead a static one.

ThreadContext_emC_s thCxtMain = {0};



ThreadContext_emC_s* getCurrent_ThreadContext_emC  ()
{
  return &thCxtMain;  
}

