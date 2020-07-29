#include <emC/Ctrl/PIDf_Ctrl_emC.h>
#include <math.h>


#ifdef DEF_REFLECTION_FULL
//#ifndef DEF_REFLECTION_NOXX
#include "genRefl/PIDf_Ctrl_emC.crefl" 
#elif defined(DEF_REFLECTION_OFFS)
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_Par_PIDf_Ctrl_emC;
  extern_C ClassJc const refl_PIDf_Ctrl_emC;
#elif !defined(DEF_REFLECTION_NO)
  //Class definition only as type marker: Note the ident should be planned application-wide and used for instances too.
  ClassJc const refl_Par_PIDf_Ctrl_emC = INIZ_ClassJc(refl_Par_PIDf_Ctrl_emC, "Test_Ctrl");
  ClassJc const refl_PIDf_Ctrl_emC = INIZ_ClassJc(refl_PIDf_Ctrl_emC, "Test_Ctrl");
//#else
//  extern_C int const refl_Par_PID_Vtrl
#endif




Par_PIDf_Ctrl_emC_s* ctor_Par_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep)
{ //check before cast:
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(Par_PIDf_Ctrl_emC_s), refl_Par_PIDf_Ctrl_emC, 0), "faulty ObjectJc",0,0 );
  Par_PIDf_Ctrl_emC_s* thiz = (Par_PIDf_Ctrl_emC_s*)othiz;
  return thiz;
}


bool init_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float Tctrl_param, float yMax_param)
{ //check before cast:
  thiz->Tctrl = Tctrl_param;
  thiz->yMax = yMax_param;
  thiz->kP = 1.0f;
  thiz->T1d = 0.1f;
  thiz->Tn = 1.0f;
  thiz->Td = 0.1f;
  setInitialized_ObjectJc(&thiz->base.obj);
  return true;
}


/**step of PID controller
* @simulink Object-FB.
*/
void set_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float kP, float Tn_param, float Td_param, float Tsd_param, bool* man_y) {
  if(thiz->man == 0) {
    thiz->kP = kP;
    thiz->Tn = Tn_param;
    thiz->Td = Td_param;
    thiz->T1d = Tsd_param;
    thiz->limPbeforeD = 1;  //it is better to fast reach point with max controller output. 
  }
  if(man_y !=null) { *man_y = thiz->man ? 1 : 0; }
}




PIDf_Ctrl_emC_s* ctor_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep)
{
  PIDf_Ctrl_emC_s* thiz = (PIDf_Ctrl_emC_s*)othiz;
  CTOR_ObjectJc(othiz, othiz, sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, 0);
  thiz->Tstep = Tstep;
  thiz->lim = 1.0f;
  return thiz; 
}



bool init_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, Par_PIDf_Ctrl_emC_s* par) {
  bool bOk = par != null;
  if(bOk) {
    reparam_Par_PIDf_Ctrl_emC(par);
    thiz->par = par;
    thiz->lim = par->yMax;
    setInitialized_ObjectJc(&thiz->base.obj);
  }
  return bOk;
}



void reparam_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz) {
  thiz->i.fIy = thiz->yMax / (float)(0x40000000L);
  thiz->i.fIx = (float)(0x40000000L) / thiz->yMax;
  thiz->i.fI = thiz->Tn <=0 ? 0 : (int64)(thiz->i.fIx * (thiz->Tctrl / thiz->Tn)); // * (float)(0x100000000LL));
  thiz->i.fTsD = thiz->T1d <= 0 ? 1.0f : 1.0f - expf(-thiz->Tctrl / thiz->T1d);
  thiz->i.fD = (thiz->Td / thiz->Tctrl) * thiz->kP;
  thiz->i.dbgct_reparam +=1;
}


void setLim_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float yLim) {
  thiz->lim = yLim;
}





void step_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float wx, float* y_y)
{
  Par_PIDf_Ctrl_emC_s* par = thiz->par;
  float wxP = wx * par->kP;
  //limit to max output.
  if (wxP > thiz->lim) { wxP = thiz->lim; }
  else if (wxP < -thiz->lim) { wxP = -thiz->lim; }
  else {} //reamin wxP

  
  float dwxP = wxP - thiz->wxP;  //on limitation the dwxP is 0. It is better for increasing the process signal on max output.
  thiz->dwxP += (par->i.fTsD * (dwxP - thiz->dwxP));
  thiz->wxP = wxP;  //store for differenzial and to inspect
  float wxPD = wxP + (par->i.fD * thiz->dwxP);  //+ D-Part.

  //limit P + D.
  if (wxPD > thiz->lim) { wxPD = thiz->lim; }
  else if (wxPD < -thiz->lim) { wxPD = -thiz->lim; }
  else {} //remain wxPD
  thiz->wxPD = wxPD;  //to inspect.

  int32 wxP32 = (int32)(par->i.fIx * wxP);  //integer representation of wxP

  int32 wxPD32 = (int32)(par->i.fIx * wxPD);     //has never an overflow because wxPD is limited.
  int32 yImin, yImax;
  //limit it to 24 bit
  if (wxP32 < 0) { yImin = -0x40000000L - wxP32; yImax =  0x40000000L; }  //
  else {          yImax =  0x40000000L - wxP32; yImin = -0x40000000L; }
  thiz->wxPD32 = wxPD32;  //to inspect
  int64 xdI = (int64)(wxP * par->i.fI);
  int64 qI1 = thiz->qI + xdI;
  int32 qIhi = (int32)(qI1 >> 32);
  if (qIhi > yImax) { qIhi = yImax; qI1 = ((int64)qIhi) << 32; }
  else if (qIhi < yImin) { qIhi = yImin; qI1 = ((int64)qIhi) << 32; }
  else {} //remain qIhi
  thiz->qI = qI1;
  thiz->qIhi = qIhi;

  *y_y = thiz->y = par->i.fIy * (wxPD32 + qIhi);  //use hi part of integrator for output.
}

