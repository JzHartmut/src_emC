#include <emC/Ctrl/FuncGen_Ctrl_emC.h>

#include <emC/Base/Assert_emC.h>
#include <emC/Ctrl/Angle_Ctrl_emC.h>



#ifdef DEF_REFLECTION_FULL
#include <emC/Ctrl/genRefl/FuncGen_Ctrl_emC.crefl>
#elif defined(DEFINED_refl_FuncGen_Ctrl_emC)  //DEF_REFLECTION_OFFS but special with this classes
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_FuncGen_Ctrl_emC;
#elif !defined(DEF_REFLECTION_NO)
  //Class definition only as type marker: Note the ident should be planned application-wide and used for instances too.
  ClassJc const refl_FuncGen_Ctrl_emC = INIZ_ClassJc(refl_PIDf_Ctrl_emC, "Test_Ctrl");
//#else
//  extern_C int const refl_Par_PID_Vtrl
#endif


FuncGen_Ctrl_emC_s* ctor_FuncGen_Ctrl_emC(ObjectJc* othiz, float Tstep)
{
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(FuncGen_Ctrl_emC_s), refl_FuncGen_Ctrl_emC, 0), "faulty ObjectJc",0,0 );
  FuncGen_Ctrl_emC_s* thiz = C_CAST(FuncGen_Ctrl_emC_s*, othiz);
  thiz->Tstep = Tstep;
  thiz->yAddr = &thiz->y;
  return thiz;
}

void doparam_FuncGen_Ctrl_emC(FuncGen_Ctrl_emC_s* thiz)
{
  thiz->dangle = (int32)(thiz->fq * thiz->Tstep * 4.0f * (float)(0x40000000));
  thiz->type.isParametrized = 1;
}
