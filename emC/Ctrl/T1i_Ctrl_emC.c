#include "emC/Ctrl/T1_Ctrl_emC.h"
#include <math.h>
#include <string.h>



T1i_Ctrl_emC_s* ctor_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz) {
  //assume addr refers enough and correct space
  //T1i_Ctrl_emC_s* thiz = C_CAST(T1i_Ctrl_emC_s*,addr);
  memset(thiz, 0, sizeof(T1i_Ctrl_emC_s));
  return thiz;
}






bool param_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, float Ts_param, float Tstep) {
  thiz->Ts = Ts_param;
  float fTs = (Ts_param <= 0 ? 1.0f : 1.0f - expf(-Tstep / Ts_param)) ;
  fTs *= 0x10000L;
  thiz->fTs = fTs >= 65535.5f ? 0xffff : (int16)( fTs + 0.5f);  //
  return true;
}










T1ish_Ctrl_emC_s* ctor_T1ish_Ctrl_emC(void* addr) {
  //assume addr refers enough and correct space
  T1ish_Ctrl_emC_s* thiz = C_CAST(T1ish_Ctrl_emC_s*,addr);
  memset(thiz, 0, sizeof(T1ish_Ctrl_emC_s));
  return thiz;
}






void param_T1ish_Ctrl_emC(T1ish_Ctrl_emC_s* thiz, float Ts, float Tstep, int fsBits, int xBits, int yBits) {
  thiz->Ts = Ts;
  thiz->nSh32y = 32 - yBits;
  float fsMax = (float)(1<<fsBits);  //value to check to get range of fsBits.
  float fTs = fsMax * ( (Ts <= 0 ? 1.0f : 1.0f - expf(-Tstep / Ts)) );
  int nShx = 32 - xBits - fsBits; //this 4 regards multiply with 16.0f
  int nShq = fsBits;
  float fsMaxHalf = fsMax / 2.0f;  //value to check to get range of fsBits.
  while(fTs <= fsMaxHalf) { 
    fTs *=2.0f;    //increase fTs to get integer muliplier in range 8..15, has at least 6% step width
    nShx -=1;      //shift x left to int32 position lesser, difference is lesser.
    nShq +=1;      //shift q right to adequate x left position more, difference is lesser.
  }
  thiz->nShx = nShx; //this 4 regards fT1 <= 16
  thiz->nShq = nShq;  //fTs is lesser 16 but >=8.
  thiz->fTs = (int)( fTs + 0.5f);  //in range 8..15
}
