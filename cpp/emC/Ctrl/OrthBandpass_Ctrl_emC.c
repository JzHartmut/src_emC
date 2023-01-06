#include "emC/Ctrl/OrthBandpass_Ctrl_emC.h"



#ifdef DEF_REFLECTION_FULL
  #include <emC/Ctrl/genRefl/OrthBandpass_Ctrl_emC.crefl>
#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_Param_OrthBandpass16_Ctrl_emC) //may defined in the *.refloffs.c file
  ClassJc const refl_OrthBandpass16_Ctrl_emC = INIZ_ClassJc(refl_OrthBandpass16_Ctrl_emC, "refl_OrthBandpass16_Ctrl_emC");
  ClassJc const refl_Param_OrthBandpass16_Ctrl_emC = INIZ_ClassJc(refl_Param_OrthBandpass16_Ctrl_emC, "refl_Param_OrthBandpass16_Ctrl_emC");
  ClassJc const refl_OrthBandpassF_Ctrl_emC = INIZ_ClassJc(refl_OrthBandpassF_Ctrl_emC, "refl_OrthBandpassF_Ctrl_emC");
  ClassJc const refl_Param_OrthBandpassF_Ctrl_emC = INIZ_ClassJc(refl_Param_OrthBandpassF_Ctrl_emC, "refl_Param_OrthBandpassF_Ctrl_emC");
  ClassJc const refl_Adjustk_OrthBandpassF_Ctrl_emC = INIZ_ClassJc(refl_Adjustk_OrthBandpassF_Ctrl_emC, "refl_Adjustk_OrthBandpassF_Ctrl_emC");
  ClassJc const refl_OrthBandpass32_Ctrl_emC = INIZ_ClassJc(refl_OrthBandpass32_Ctrl_emC, "refl_OrthBandpass32_Ctrl_emC");
  ClassJc const refl_Param_OrthBandpass32_Ctrl_emC = INIZ_ClassJc(refl_Param_OrthBandpass32_Ctrl_emC, "refl_Param_OrthBandpass32_Ctrl_emC");
#endif



void ctor_Param_OrthBandpassF_Ctrl_emC(Param_OrthBandpassF_Ctrl_emC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m)
{ 
  //Param_OrthBandpassF_Ctrl_emC_s* thiz = thiz_y;  //use the output data as this. Initialize *this
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_Param_OrthBandpassF_Ctrl_emC, identObj);
  setInitialized_ObjectJc(&thiz->obj); //no init routine exists.
  thiz->tStepOrthi = tStepOrthi;
  thiz->fm = 0.5f / nom_m;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
Param_OrthBandpassF_Ctrl_emC::Param_OrthBandpassF_Ctrl_emC(int32 identObj, float Tstep, float tStepOrthi, float m_nom) {
  ctor_Param_OrthBandpassF_Ctrl_emC(this, identObj, Tstep, tStepOrthi, m_nom);
}
#endif //__cplusplus



OrthBandpassF_Ctrl_emC_s* ctor_OrthBandpassF_Ctrl_emC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep)
{ OrthBandpassF_Ctrl_emC_s* thiz = (OrthBandpassF_Ctrl_emC_s*) othiz;
  CTOR_ObjectJc(othiz, thiz, sizeof(*thiz), refl_OrthBandpassF_Ctrl_emC, identObj);
  thiz->kA = kA;
  thiz->kB = kB;
  thiz->xadiff = 0;
  thiz->yab.re = 0;
  thiz->yab.im = 0;
  thiz->m = 0;
  return thiz;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
OrthBandpassF_Ctrl_emC::OrthBandpassF_Ctrl_emC(float kA, float kB, int32 identObj, float Tstep) {
  ctor_OrthBandpassF_Ctrl_emC(&this->obj, kA, kB, identObj, Tstep);
}
#endif //__cplusplus



void ctor_Adjustk_OrthBandpassF_Ctrl_emC(Adjustk_OrthBandpassF_Ctrl_emC_s* thiz, int32 identObj, float max_e, float kHi, float kNormal, float Tstep, float Tdecay)
{
  CTOR_ObjectJc(&thiz->base, thiz, sizeof(*thiz), refl_Adjustk_OrthBandpassF_Ctrl_emC, identObj);
  thiz->kHi = kHi;
  thiz->kNormal = kNormal;
  thiz->max_e = max_e;
  thiz->fdeday = Tstep / Tdecay;
  setInitialized_ObjectJc(&thiz->base); //no init routine exists.
}



bool init_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, Param_OrthBandpassF_Ctrl_emC_s* par)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null) {
    //yet complete:
    thiz->par = par;
    setInitialized_ObjectJc(&thiz->obj);
    return true;
  } 
  else {
    return false;
  }
}



void ctor_Param_OrthBandpass16_Ctrl_emC(Param_OrthBandpass16_Ctrl_emC_s* thiz, int32 identObj, float Tstep, float tStepOrthi)
{ 
  //Param_OrthBandpass16_Ctrl_emC_s* thiz = thiz_y;  //use the output data as this. Initialize *this
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_Param_OrthBandpass16_Ctrl_emC, identObj);
  setInitialized_ObjectJc(&thiz->obj); //no init routine exists.
  thiz->tStepOrthi = tStepOrthi;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
Param_OrthBandpass16_Ctrl_emC::Param_OrthBandpass16_Ctrl_emC(int32 identObj, float Tstep, float tStepOrthi) {
  ctor_Param_OrthBandpass16_Ctrl_emC(this, identObj, Tstep, tStepOrthi);
}
#endif //__cplusplus





OrthBandpass16_Ctrl_emC_s* ctor_OrthBandpass16_Ctrl_emC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep)
{ OrthBandpass16_Ctrl_emC_s* thiz = (OrthBandpass16_Ctrl_emC_s*) othiz;
  CTOR_ObjectJc(othiz, thiz, sizeof(*thiz), refl_OrthBandpass16_Ctrl_emC, identObj);
  //thiz->b_ = 0;
  setkAB_OrthBandpass16_Ctrl_emC(thiz, kA, kB);
  thiz->yab.re = 0;
  thiz->yab.im = 0;
  return thiz;
}

void setkAB_OrthBandpass16_Ctrl_emC ( OrthBandpass16_Ctrl_emC_s* thiz, float kA, float kB)
{
  thiz->kA = fabsf(kA) < 8.0f ? (int16)(0x1000 * kA) : 0;
  thiz->kB = fabsf(kB) < 8.0f ? (int16)(0x1000 * kB) : 0;
}

#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
OrthBandpass16_Ctrl_emC::OrthBandpass16_Ctrl_emC(float kA, float kB, int32 identObj, float Tstep) {
  ctor_OrthBandpass16_Ctrl_emC(&this->obj, kA, kB, identObj, Tstep);
}
#endif //__cplusplus



bool init_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, Param_OrthBandpass16_Ctrl_emC_s* par)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null) {
    //yet complete:
    thiz->par = par;
    setInitialized_ObjectJc(&thiz->obj);
    return true;
  } else {
    return false;
  }
}




void ctor_Param_OrthBandpass32_Ctrl_emC(Param_OrthBandpass32_Ctrl_emC_s* thiz, int32 identObj, float Tstep, float tStepOrthi)
{ 
  //Param_OrthBandpass16_Ctrl_emC_s* thiz = thiz_y;  //use the output data as this. Initialize *this
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_Param_OrthBandpass32_Ctrl_emC, identObj);
  setInitialized_ObjectJc(&thiz->obj); //no init routine exists.
  thiz->tStepOrthi = tStepOrthi;
  float f = 0.5f;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
Param_OrthBandpass32_Ctrl_emC::Param_OrthBandpass32_Ctrl_emC(int32 identObj, float Tstep, float tStepOrthi) {
  ctor_Param_OrthBandpass32_Ctrl_emC(this, identObj, Tstep, tStepOrthi);
}
#endif //__cplusplus


static void XXXXXXXcalcKABOrthBandpass32_Ctrl_emC (OrthBandpass32_Ctrl_emC_s* thiz,  float kA, float kB) 
{
  int32 kA_IEEE754 = *(int32*)&kA;
  int32 kB_IEEE754 = *(int32*)&kB;
  int32 exp_kAB_IEEE754 = kA_IEEE754 & 0x7F800000; 
  //int32 recexp_kAB_IEEE754 = (0x3F800000 - exp_kAB_IEEE754) + 0x3F000000;
  int sh = (exp_kAB_IEEE754 - 0x3f800000) >>23;  //0 for 0.5..1, max
  //float normKAB = *(float*) &recexp_kAB_IEEE754;
  int32 kAi = ((kA_IEEE754 & 0x007FFFFF) << 6);
  kAi |= 0x40000000;
  if(kA <0) kAi = -kAi;
  thiz->kA = kAi;

}


OrthBandpass32_Ctrl_emC_s* ctor_OrthBandpass32_Ctrl_emC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep)
{ OrthBandpass32_Ctrl_emC_s* thiz = (OrthBandpass32_Ctrl_emC_s*) othiz;
  CTOR_ObjectJc(othiz, thiz, sizeof(*thiz), refl_OrthBandpass32_Ctrl_emC, identObj);
  //calcKABOrthBandpass32_Ctrl_emC(thiz, kA, kB);
  //thiz->kA = (int16)(4096 * kA);
  //thiz->kB = (int16)(4096 * kB);
  setkAB_OrthBandpass32_Ctrl_emC(thiz, kA, kB);
  thiz->yab.re = 0;
  thiz->yab.im = 0;
  return thiz;
}

void setkAB_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, float kA, float kB){
  //max value of kA = 15.9999 is mapped to 0x7FFFFFFF, regard sign, hence sign from float
  thiz->kA = fabsf(kA) < 16.0 ? (int32)(0x08000000 * kA) : *(int32*)(&kA) | 0x7fffffff;  
  thiz->kB = fabsf(kB) < 16.0 ? (int32)(0x08000000 * kB) : *(int32*)(&kB) | 0x7fffffff;
}

#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
OrthBandpass32_Ctrl_emC::OrthBandpass32_Ctrl_emC(float kA, float kB, int32 identObj, float Tstep) {
  ctor_OrthBandpass32_Ctrl_emC(&this->obj, kA, kB, identObj, Tstep);
}
#endif //__cplusplus



bool init_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, Param_OrthBandpass32_Ctrl_emC_s* par)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null) {
    //yet complete:
    thiz->par = par;
    setInitialized_ObjectJc(&thiz->obj);
    return true;
  } else {
    return false;
  }
}


void setFq_Param_OrthBandpass32_Ctrl_emC(Param_OrthBandpass32_Ctrl_emC_s* thiz, float fq)
{ 
  thiz->fq = fq;
  #ifdef USE_float_OrthBandpass32_Ctrl_emC
    float fI1 = 2*PI_float_emC * thiz->tStepOrthi * fq;  //rad of 1 Tstep
    float fI_oth = sinf(fI1) * 1.00000f;
    int32 fI_oth32 = (int32)(65536.0f * 65536 * sh4m * fI_oth + 0.5f);
    float fI_own = 1.0 - cosf(dI1);
    int32 fI_own32 = (int32)(-65536.0f * 65536 * sh4m * (fI_own) - 0.5f);
  #else
    double fI1 = 2*PI_emC * thiz->tStepOrthi * fq;  //rad of 1 Tstep
    double fI_oth = sin(fI1);
    int32 fI_oth32 = (int32)(65536.0 * 65536 * fI_oth + 0.5);
    double fI_own = 1.0 - cos(fI1);    //note: negative value for fI_own32
    int32 fI_own32 = (int32)(-65536.0 * 65536 * (fI_own) - 0.5);
  #endif
  thiz->fI_oth = fI_oth32;
  thiz->fI_own = fI_own32;
}

