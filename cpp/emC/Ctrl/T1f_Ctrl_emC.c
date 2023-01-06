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







T2f_Ctrl_emC_s* ctor_T2f_Ctrl_emC(void* addr) {
  //assume addr refers enough and correct space
  T2f_Ctrl_emC_s* thiz = C_CAST(T2f_Ctrl_emC_s*,addr);
  memset(thiz, 0, sizeof(T2f_Ctrl_emC_s));
  return thiz;
}



void param_T2f_Ctrl_emC(T2f_Ctrl_emC_s* thiz, float Ts1, float Ts2, float Tstep) {
  thiz->Ts1 = Ts1;
  thiz->Ts2 = Ts2;
  thiz->fTs1 = ( (Ts1 <= 0 ? 1.0f : 1.0f - expf(-Tstep / Ts1)) );
  thiz->fTs2 = ( (Ts2 <= 0 ? 1.0f : 1.0f - expf(-Tstep / Ts2)) );
}



SmoothGainf_Ctrl_emC_s* ctor_SmoothGainf_Ctrl_emC ( ObjectJc* othiz, float Tslow, float Tshigh, float Tstep ) {
  SmoothGainf_Ctrl_emC_s* thiz = C_CAST(SmoothGainf_Ctrl_emC_s*, othiz);
  param_SmoothGainf_Ctrl_emC(thiz, Tslow, Tshigh, Tstep);
  return thiz;
}


