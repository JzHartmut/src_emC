#include <emC/Ctrl/pid_Ctrl.h>
#include <math.h>

#ifndef ID_refl_Par_PID_Ctrl
#define ID_refl_Par_PID_Ctrl 0x0FA0
#define ID_refl_PID_Ctrl 0x0FA1
#endif

#ifdef DEF_REFLECTION_FULL
//#ifndef DEF_REFLECTION_NOXX
#include "genRefl/pid_Ctrl.crefl" 
#elif defined(DEF_REFLECTION_OFFS)
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_Par_PID_Ctrl;
  extern_C ClassJc const refl_PID_Ctrl;
#else
  //Class definition only as type marker: Note the ident should be planned application-wide and used for instances too.
  ClassJc const refl_Par_PID_Ctrl = INIZ_ClassJc(refl_Par_PID_Ctrl, "Test_Ctrl");
  ClassJc const refl_PID_Ctrl = INIZ_ClassJc(refl_PID_Ctrl, "Test_Ctrl");
#endif




Par_PID_Ctrl_s* ctor_Par_PID_Ctrl(ObjectJc* othiz, float Tstep)
{
  Par_PID_Ctrl_s* thiz = (Par_PID_Ctrl_s*)othiz;
  iniz_ObjectJc(othiz, othiz, sizeof(Par_PID_Ctrl_s), &refl_Par_PID_Ctrl, 0);
  thiz->kP = 1.0f;
  thiz->T1d = 0.1f;
  thiz->Tn = 1.0f;
  thiz->Td = 0.1f;
  thiz->lim = 1.0f;
  setInitialized_ObjectJc(othiz);
  return thiz;
}


/**step of PID controller
* @simulink Object-FB.
*/
void set_Par_PID_Ctrl(Par_PID_Ctrl_s* thiz, float kP, float lim, float Tn_param, float Td_param, float Tsd_param, bool* man_y) {
  if(thiz->man == 0) {
    thiz->kP = kP;
    thiz->lim = lim;
    thiz->Tn = Tn_param;
    thiz->Td = Td_param;
    thiz->T1d = Tsd_param;
    thiz->limPbeforeD = 1;  //it is better to fast reach point with max controller output. 
  }
  *man_y = thiz->man ? 1 : 0;
}




PID_Ctrl_s* ctor_PID_Ctrl(ObjectJc* othiz, float Tstep)
{
  PID_Ctrl_s* thiz = (PID_Ctrl_s*)othiz;
  iniz_ObjectJc(othiz, othiz, sizeof(PID_Ctrl_s), &refl_PID_Ctrl, 0);
  thiz->Tstep = Tstep;
  return thiz; 
}



bool init_PID_Ctrl(PID_Ctrl_s* thiz, Par_PID_Ctrl_s* par) {
  if(par == null) return false;
  thiz->par = par;
  reparam_PID_Ctrl(thiz);
  setInitialized_ObjectJc(&thiz->base.obj);
  return true;
}



void reparam_PID_Ctrl(PID_Ctrl_s* thiz) {
  Par_PID_Ctrl_s* par = thiz->par;
  Internal_PID_Ctrl* fn = &thiz->_internal[0];
  if(fn == thiz->f){ fn = &thiz->_internal[1]; } //use the other one.
  fn->fIy = par->lim / (float)(0x40000000L);
  fn->fIx = (float)(0x40000000L) / par->lim;
  fn->fI = par->Tn <=0 ? 0 : fn->fIx * (int64)(thiz->Tstep / par->Tn * (float)(0x100000000LL));
  fn->fTsD = par->T1d <= 0 ? 1.0f : 1.0f - expf(-thiz->Tstep / par->T1d);
  fn->fD = par->Td / thiz->Tstep * par->kP;
  thiz->f = fn; //atomic switch for using in step
  thiz->par = par; //store associated parameter.
  thiz->dbgct_reparam +=1;
}




void step_PID_Ctrl(PID_Ctrl_s* thiz, float wx, float* y_y)
{
  Internal_PID_Ctrl* f = thiz->f;
  Par_PID_Ctrl_s* par = thiz->par;
  float wxP = wx * par->kP;
  //limit to max output.
  if(thiz->par->limPbeforeD){
    if (wxP > par->lim) { wxP = par->lim; }
    else if (wxP < -par->lim) { wxP = -par->lim; }
  }
  
  
  float dwxP = wxP - thiz->wxP;  //on limitation the dwxP is 0. It is better for increasing the process signal on max output.
  thiz->dwxP += f->fTsD * (dwxP - thiz->dwxP);
  thiz->wxP = wxP;  //store for differenzial and to inspect
  float wxPD = wxP + f->fD * thiz->dwxP;  //+ D-Part.

                                         //limit to may output.
  if (wxPD > par->lim) { wxPD = par->lim; }
  else if (wxPD < -par->lim) { wxPD = -par->lim; }
  thiz->wxPD = wxPD;  //to inspect.

  //limit to max output.
  if (!thiz->par->limPbeforeD) {
    if (wxP > par->lim) { wxP = par->lim; }
    else if (wxP < -par->lim) { wxP = -par->lim; }
  }
  int32 wxP32 = f->fIx * wxP;

  int32 wxPD32 = f->fIx * wxPD;     //has never an overflow because wxP is limited.
  int32 yImin, yImax;
  //limit it to 24 bit
  if (wxP32 < 0) { yImin = -0x40000000L - wxP32; yImax =  0x3fffffffL; }
  else {          yImax =  0x3fffffffL - wxP32; yImin = -0x40000000L; }
  thiz->wxPD32 = wxPD32;  //to inspect
  int64 xdI = wxP * f->fI;
  int64 qI1 = thiz->qI + xdI;
  int32 qIhi = (int32)(qI1 >> 32);
  if (qIhi > yImax) { qI1 = ((int64)yImax) << 32; }
  else if (qIhi < yImin) { qI1 = ((int64)yImin) << 32;
  }
  thiz->qI = qI1;
  thiz->qIhi = qIhi;

  *y_y = thiz->y = f->fIy * (wxPD32 + qIhi);  //use hi part of integrator for output.
}

