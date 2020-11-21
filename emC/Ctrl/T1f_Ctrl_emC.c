#include "emC/Ctrl/T1_Ctrl_emC.h"
#include <math.h>
#include <string.h>

T1f_Ctrl_emC_s* ctor_T1f_Ctrl_emC(void* addr) {
  //assume addr refers enough and correct space
  T1f_Ctrl_emC_s* thiz = C_CAST(T1f_Ctrl_emC_s*,addr);
  memset(thiz, 0, sizeof(T1f_Ctrl_emC_s));
  return thiz;
}






void param_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz, float Ts, float Tstep) {
  thiz->Ts = Ts;
  float fTs = ( (Ts <= 0 ? 1.0f : 1.0f - expf(-Tstep / Ts)) );
  thiz->fTs = fTs;  //in range 8..15
}
