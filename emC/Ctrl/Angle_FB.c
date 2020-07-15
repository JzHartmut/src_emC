#include "Angle_FB.h"
#include <applstdef_emC.h>
#include <emC/base/Object_emC.h>

#ifdef DEF_REFLECTION_FULL
  #include "genRefl/Angle_FB.crefl"
#elif defined(XXXDEF_REFLECTION_OFFS)
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_Angle_abwmf_FB_CtrlemC;
//#elif !defined(DEF_REFLECTION_NO)
#else
  //Class definition only as type marker:
  ClassJc const refl_Angle_abwmf_FB_CtrlemC = INIZ_ClassJc(refl_Angle_abwmf_FB_CtrlemC, "Angle_abwmf_FB_CtrlemC");
#endif

//const ClassJc refl_Angle_abwmf_FB = { CONST_ObjectJc(0, (ObjectJc*)&refl_Angle_abwmf_FB.object, null), "Angle_abwmf_FB_CtrlemC", 0};


void ctor_Angle_abwmf_FB(Angle_abwmf_FB_CtrlemC* thiz, int32 identObj, float Tstep)
{ memset(thiz, 0, sizeof(*thiz)); 
  ctor_ObjectJc(&thiz->obj, thiz, sizeof(*thiz), &refl_Angle_abwmf_FB_CtrlemC, identObj);
  setInitialized_ObjectJc(&thiz->obj);
  thiz->m = 1.0f;  //default for only-angle
}


