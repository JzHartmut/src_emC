#include <emC/Base/RingBuffer_emC.h>
#include <emC/Base/Assert_emC.h>
#include <emC/Base/MemC_emC.h>
#include <stdlib.h>  //malloc

RingBuffer_emC_s* ctor_RingBuffer_emC ( ObjectJc* othiz, int nrofEntries ) {
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(RingBuffer_emC_s), refl_RingBuffer_emC, 0)
      , "RingBuffer_emC_s not correct initialized", othiz->identSize, (int)(intPTR)getClass_ObjectJc(othiz) );
  RingBuffer_emC_s* thiz = (RingBuffer_emC_s*) othiz;
  thiz->nrofEntries = nrofEntries;
  thiz->ixRd = thiz->ixWr = 0;
  return thiz;
}



//It is the implementation for the RingBuffer SFunction in Simulink.
void status_RingBuffer_emC(RingBuffer_emC_s* thiz, int16* nrofEntries_y, int* ctModify_y) {
  //Output the state
  int n = thiz->ixWr - thiz->ixRd;
  if(n<0) { n+= thiz->nrofEntries; }
  *(nrofEntries_y) = n;
  *ctModify_y = thiz->ctModify;
}



//It is the implementation for the RingBuffer SFunction in Simulink.
int16 info_RingBuffer_emC(RingBuffer_emC_s* thiz, int16* ctModify_y) {
  //Output the state
  int n = thiz->ixWr - thiz->ixRd;
  if(n<0) { n+= thiz->nrofEntries; }
  if(ctModify_y !=null) { *(ctModify_y) = thiz->ctModify; }
  return (int16)n;
}



