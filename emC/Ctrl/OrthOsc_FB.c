#include "OrthOsc_FB.h"

#ifdef DEF_REFLECTION_FULL
#include "genRefl/OrthOsc_FB.crefl"
#else
  #define ID_refl_OrthOsc2_FB_CtrlemC 0
  #define ID_refl_Param_OrthOsc2_FB_CtrlemC 0
  #define ID_refl_Adjustk_OrthOsc2_FB_CtrlemC 0
  ClassJc const refl_OrthOsc2_FB_CtrlemC = INIZ_ClassJc(refl_OrthOsc2_FB_CtrlemC, "refl_OrthOsc2_FB");
  ClassJc const refl_Param_OrthOsc2_FB_CtrlemC = INIZ_ClassJc(refl_Param_OrthOsc2_FB_CtrlemC, "refl_Param_OrthOsc2_FB");
  ClassJc const refl_Adjustk_OrthOsc2_FB_CtrlemC = INIZ_ClassJc(refl_Adjustk_OrthOsc2_FB_CtrlemC, "refl_Adjustk_OrthOsc2_FB");
#endif



void ctor_Param_OrthOsc2_FB(Param_OrthOsc2_FB* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m)
{ 
  //Param_OrthOsc2_FB* thiz = thiz_y;  //use the output data as this. Initialize *this
  iniz_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), &refl_Param_OrthOsc2_FB_CtrlemC, identObj);
  setInitialized_ObjectJc(&thiz->obj); //no init routine exists.
  thiz->tStepOrthi = tStepOrthi;
  thiz->nom_m = nom_m;
  float f = 0.5f;
  thiz->fm = f / nom_m;
  thiz->fmr = 0;
}



OrthOsc2_FB_CtrlemC* ctor_OrthOsc2_FB(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep)
{ OrthOsc2_FB_CtrlemC* thiz = (OrthOsc2_FB_CtrlemC*) othiz;
  iniz_ObjectJc(othiz, thiz, sizeof(*thiz), &refl_OrthOsc2_FB_CtrlemC, identObj);
  thiz->kA = kA;
  thiz->kB = kB;
  return thiz;
}



void ctor_Adjustk_OrthOsc2_FB(Adjustk_OrthOsc2_FB* thiz, int32 identObj, float max_e, float kHi, float kNormal, float Tstep, float Tdecay)
{
  iniz_ObjectJc(&thiz->base, thiz, sizeof(*thiz), &refl_Adjustk_OrthOsc2_FB_CtrlemC, identObj);
  thiz->kHi = kHi;
  thiz->kNormal = kNormal;
  thiz->max_e = max_e;
  thiz->fdeday = Tstep / Tdecay;
  setInitialized_ObjectJc(&thiz->base); //no init routine exists.
}



bool init_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, Param_OrthOsc2_FB* par, Angle_abwmf_FB_CtrlemC* angle)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null && angle !=null) {
    //yet complete:
    thiz->par = par;
    thiz->anglep = angle;
    setInitialized_ObjectJc(&thiz->obj);
  }
  return true;
}

bool init_NoAngle_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, Param_OrthOsc2_FB* par)
{ 
  if( ! isInitialized_ObjectJc(&thiz->obj) && par !=null) {
    //yet complete:
    thiz->par = par;
    thiz->anglep = null;
    setInitialized_ObjectJc(&thiz->obj);
  }
  return true;
}

