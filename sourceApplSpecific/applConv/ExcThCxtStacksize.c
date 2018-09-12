#include <applstdef_emC.h>  //decides about struct of ThreadContext_emC

//Uses applspecific struct ThreadContext_emC:
int getCurrentStackDepth_ThreadContext_emC  (  ThreadContext_emC_s* thCxt) {
  if(thCxt == null) { thCxt = getCurrent_ThreadContext_emC(); }
  int ret = (int)(thCxt->topmemAddrOfStack - ((MemUnit*)&ret));  //casting allowed, it is not able to expect that stacksize > 32 kBye on a small resource 16 bit CPU
  if(thCxt->stacksizeMax < ret) { 
    thCxt->stacksizeMax = ret;   //store maximum
  }
  return ret;
}

int getMaxStackDepth_ThreadContext_emC  (  ThreadContext_emC_s* thCxt) {
  if (thCxt == null) { thCxt = getCurrent_ThreadContext_emC(); }
  getCurrentStackDepth_ThreadContext_emC(thCxt);
  return thCxt->stacksizeMax;
}

