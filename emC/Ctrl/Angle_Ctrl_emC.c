#include "emC/Ctrl/Angle_Ctrl_emC.h"
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <emC/Ctrl/T1_Ctrl_emC.h>

#ifdef DEF_REFLECTION_FULL
  #include "emC/Ctrl/genRefl/Angle_Ctrl_emC.crefl"
#elif defined(DEFINED_refl_Angle_abwmf_FB_Ctrl_emC)
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_Angle_abwmf_FB_Ctrl_emC;
//#elif !defined(DEF_REFLECTION_NO)
#elif !defined(DEF_REFLECTION_NO)
  //Class definition only as type marker:
  ClassJc const refl_Angle_abwmf_FB_Ctrl_emC = INIZ_ClassJc(refl_Angle_abwmf_FB_Ctrl_emC, "Angle_abwmf_FB_Ctrl_emC");
  ClassJc const refl_Angle_abgmf16_Ctrl_emC = INIZ_ClassJc(refl_Angle_abgmf16_Ctrl_emC, "Angle_abgmf16_Ctrl_emC");
#endif

//const ClassJc refl_Angle_abwmf_FB = { CONST_ObjectJc(0, (ObjectJc*)&refl_Angle_abwmf_FB.object, null), "Angle_abwmf_FB_Ctrl_emC", 0};


void ctor_Angle_abwmf_FB(Angle_abwmf_FB_Ctrl_emC* thiz, int32 identObj, float Tstep)
{ memset(thiz, 0, sizeof(*thiz)); 
  CTOR_ObjectJc(&thiz->base.obj, thiz, sizeof(*thiz), refl_Angle_abwmf_FB_Ctrl_emC, identObj);
  setInitialized_ObjectJc(&thiz->base.obj);
  thiz->m = 1.0f;  //default for only-angle
}


void ctor_Angle_abgmf16_Ctrl_emC(Angle_abgmf16_Ctrl_emC* thiz, int32 identObj, float Tstep)
{ memset(thiz, 0, sizeof(*thiz)); 
  CTOR_ObjectJc(&thiz->base.obj, thiz, sizeof(*thiz), refl_Angle_abgmf16_Ctrl_emC, identObj);
  setInitialized_ObjectJc(&thiz->base.obj);
  thiz->m = 1.0f;  //default for only-angle

}



