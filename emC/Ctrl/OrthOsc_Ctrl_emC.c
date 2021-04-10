#include "emC/Ctrl/OrthOsc_Ctrl_emC.h"

#ifdef DEF_REFLECTION_FULL
  #include "genRefl/OrthOsc_Ctrl_emC.crefl"
#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_Param_OrthOsc16_CtrlemC) //may defined in the *.refloffs.c file
  #define ID_refl_OrthOsc2_CtrlemC_CtrlemC 0
  #define ID_refl_Param_OrthOsc2_CtrlemC 0
  #define ID_refl_OrthOsc16_CtrlemC_CtrlemC 0
  #define ID_refl_Param_OrthOsc16_CtrlemC 0
  #define ID_refl_Adjustk_OrthOsc2_CtrlemC 0
  ClassJc const refl_OrthOsc16_CtrlemC_CtrlemC = INIZ_ClassJc(refl_OrthOsc16_CtrlemC_CtrlemC, "refl_OrthOsc16_CtrlemC_CtrlemC");
  ClassJc const refl_Param_OrthOsc16_CtrlemC = INIZ_ClassJc(refl_Param_OrthOsc16_CtrlemC, "refl_Param_OrthOsc16_CtrlemC");
  ClassJc const refl_OrthOsc2_CtrlemC_CtrlemC = INIZ_ClassJc(refl_OrthOsc2_CtrlemC_CtrlemC, "refl_OrthOsc2_CtrlemC_CtrlemC");
  ClassJc const refl_Param_OrthOsc2_CtrlemC = INIZ_ClassJc(refl_Param_OrthOsc2_CtrlemC, "refl_Param_OrthOsc2_CtrlemC");
  ClassJc const refl_Adjustk_OrthOsc2_CtrlemC = INIZ_ClassJc(refl_Adjustk_OrthOsc2_CtrlemC, "refl_Adjustk_OrthOsc2_CtrlemC");
#endif



void ctor_Param_OrthOsc2_CtrlemC(Param_OrthOsc2_CtrlemC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m)
{ 
  //Param_OrthOsc2_CtrlemC_s* thiz = thiz_y;  //use the output data as this. Initialize *this
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_Param_OrthOsc2_CtrlemC, identObj);
  setInitialized_ObjectJc(&thiz->obj); //no init routine exists.
  thiz->tStepOrthi = tStepOrthi;
  thiz->nom_m = nom_m;
  float f = 0.5f;
  thiz->fm = f / nom_m;
  thiz->fmr = 0;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
Param_OrthOsc2_CtrlemC::Param_OrthOsc2_CtrlemC(int32 identObj, float Tstep, float tStepOrthi, float nom_m) {
  ctor_Param_OrthOsc2_CtrlemC(this, identObj, Tstep, tStepOrthi, nom_m);
}
#endif //__cplusplus



OrthOsc2_CtrlemC_s* ctor_OrthOsc2_CtrlemC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep)
{ OrthOsc2_CtrlemC_s* thiz = (OrthOsc2_CtrlemC_s*) othiz;
  CTOR_ObjectJc(othiz, thiz, sizeof(*thiz), refl_OrthOsc2_CtrlemC, identObj);
  thiz->kA = kA;
  thiz->kB = kB;
  thiz->b_ = 0;
  thiz->yab.re = 0;
  thiz->yab.im = 0;
  thiz->ypq.re = 0;
  thiz->ypq.im = 0;
  thiz->m = 0;
  thiz->mr = 10.0f;
  return thiz;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
OrthOsc2_CtrlemC::OrthOsc2_CtrlemC(float kA, float kB, int32 identObj, float Tstep) {
  ctor_OrthOsc2_CtrlemC(&this->obj, kA, kB, identObj, Tstep);
}
#endif //__cplusplus



void ctor_Adjustk_OrthOsc2_CtrlemC(Adjustk_OrthOsc2_CtrlemC_s* thiz, int32 identObj, float max_e, float kHi, float kNormal, float Tstep, float Tdecay)
{
  CTOR_ObjectJc(&thiz->base, thiz, sizeof(*thiz), refl_Adjustk_OrthOsc2_CtrlemC, identObj);
  thiz->kHi = kHi;
  thiz->kNormal = kNormal;
  thiz->max_e = max_e;
  thiz->fdeday = Tstep / Tdecay;
  setInitialized_ObjectJc(&thiz->base); //no init routine exists.
}



bool init_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, Param_OrthOsc2_CtrlemC_s* par, Angle_abwmf_FB_CtrlemC* angle)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null && angle !=null) {
    //yet complete:
    thiz->par = par;
    thiz->anglep = angle;
    setInitialized_ObjectJc(&thiz->obj);
    return true;
  } 
  else {
    return false;
  }
}

bool init_NoAngle_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, Param_OrthOsc2_CtrlemC_s* par)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null) {
    //yet complete:
    thiz->par = par;
    thiz->anglep = null;
    setInitialized_ObjectJc(&thiz->obj);
    return true;
  } 
  else {
    return false;
  }
}




void ctor_Param_OrthOsc16_CtrlemC(Param_OrthOsc16_CtrlemC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m)
{ 
  //Param_OrthOsc16_CtrlemC_s* thiz = thiz_y;  //use the output data as this. Initialize *this
  CTOR_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), refl_Param_OrthOsc16_CtrlemC, identObj);
  setInitialized_ObjectJc(&thiz->obj); //no init routine exists.
  thiz->tStepOrthi = tStepOrthi;
  thiz->nom_m = nom_m;
  float f = 0.5f;
  thiz->fm = f / nom_m;
  thiz->fmr = 0;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
Param_OrthOsc16_CtrlemC::Param_OrthOsc16_CtrlemC(int32 identObj, float Tstep, float tStepOrthi, float nom_m) {
  ctor_Param_OrthOsc16_CtrlemC(this, identObj, Tstep, tStepOrthi, nom_m);
}
#endif //__cplusplus



OrthOsc16_CtrlemC_s* ctor_OrthOsc16_CtrlemC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep)
{ OrthOsc16_CtrlemC_s* thiz = (OrthOsc16_CtrlemC_s*) othiz;
  CTOR_ObjectJc(othiz, thiz, sizeof(*thiz), refl_OrthOsc16_CtrlemC, identObj);
  thiz->kA = (int16)(4096 * kA);
  thiz->kB = (int16)(4096 * kB);
  thiz->b_ = 0;
  thiz->yab.re = 0;
  thiz->yab.im = 0;
  return thiz;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
OrthOsc16_CtrlemC::OrthOsc16_CtrlemC(float kA, float kB, int32 identObj, float Tstep) {
  ctor_OrthOsc16_CtrlemC(&this->obj, kA, kB, identObj, Tstep);
}
#endif //__cplusplus



bool init_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, Param_OrthOsc16_CtrlemC_s* par, Angle_abgmf16_CtrlemC* angle)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null && angle !=null) {
    //yet complete:
    thiz->par = par;
    thiz->anglep = angle;
    setInitialized_ObjectJc(&thiz->obj);
    return true;
  } else {
    return false;
  }
}

bool init_NoAngle_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, Param_OrthOsc16_CtrlemC_s* par)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null) {
    //yet complete:
    thiz->par = par;
    thiz->anglep = null;
    setInitialized_ObjectJc(&thiz->obj);
    return true;
  } else {
    return false;
  }
}

