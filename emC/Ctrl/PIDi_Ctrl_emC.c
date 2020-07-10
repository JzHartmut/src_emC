#include <emC/Ctrl/PIDi_Ctrl_emC.h>
#include <math.h>
#include <emC/Base/Assert_emC.h>

#ifndef ID_refl_Par_PIDi_Ctrl_emC
#define ID_refl_Par_PIDi_Ctrl_emC 0x0FC0
#define ID_refl_PIDi_Ctrl_emC 0x0FC1
#endif

#ifdef DEF_REFLECTION_FULL
//#ifndef DEF_REFLECTION_NOXX
#include "genRefl/pid_Ctrl.crefl" 
#elif defined(DEF_REFLECTION_OFFS)
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_Par_PIDi_Ctrl_emC;
  extern_C ClassJc const refl_PIDi_Ctrl_emC;
#elif !defined(DEF_REFLECTION_NO)
  //Class definition only as type marker: Note the ident should be planned application-wide and used for instances too.
  ClassJc const refl_Par_PIDi_Ctrl_emC = INIZ_ClassJc(refl_Par_PIDi_Ctrl_emC, "Test_Ctrl");
  ClassJc const refl_PIDi_Ctrl_emC = INIZ_ClassJc(refl_PIDi_Ctrl_emC, "Test_Ctrl");
//#else
//  extern_C int const refl_Par_PID_Vtrl
#endif




Par_PIDi_Ctrl_emC_s* ctor_Par_PIDi_Ctrl_emC(ObjectJc* othiz, float Tstep, int xBits, int yBits)
{
  Par_PIDi_Ctrl_emC_s* thiz = (Par_PIDi_Ctrl_emC_s*)othiz;
  iniz_ObjectJc(othiz, othiz, sizeof(Par_PIDi_Ctrl_emC_s), &refl_Par_PIDi_Ctrl_emC, 0);
  thiz->Tstep = Tstep;
  thiz->yBits = yBits;
  thiz->xBits = xBits;
  setInitialized_ObjectJc(othiz);
  return thiz;
}


/**step of PID controller
* @simulink Object-FB.
*/
void set_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz, float kP, float Tn_param, float Td_param, float Tsd_param, bool* man_y) {
  if(thiz->man == 0) { //possibility to disconnect parameter Setting with this operation, if parameter are given manually. 
    thiz->kP = kP;
    thiz->Tn = Tn_param;
    thiz->Td = Td_param;
    thiz->Tsd = Tsd_param;
    reparam_Par_PIDi_Ctrl_emC(thiz);  //calculate the derived values of the parameter.
    //thiz->limPbeforeD = 1;  //it is better to fast reach point with max controller output. 
  }
  if(man_y !=null) { *man_y = thiz->man ? 1 : 0; }
}


void reparam_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz) {
  MAYBE_UNUSED_emC int bitInt = 8*sizeof(int);
  thiz->i.nSh32y = 32 - thiz->yBits;
  //thiz->i.nShTsD = 32 - thiz->xBits;
  thiz->i.nShKp = thiz->yBits - thiz->xBits;
  thiz->i.kPi = (int)( (thiz->kP * ( ((uint32)1)<<thiz->i.nShKp) ) + 0.5f); //in range 1.0, for example nShKp = 4, step of 1/16
  thiz->i.fI = thiz->Tn <= 0 ? 0 : (int32)( ( ((uint32)1)<<thiz->i.nSh32y ) * (thiz->Tstep / thiz->Tn));
  //thiz->i.fI = thiz->Tn <=0 ? 0 : (int64)(thiz->i.fIx * (thiz->Tstep / thiz->Tn)); // * (float)(0x100000000LL));
  float fTs = 16.0f * ( (thiz->Tsd <= 0 ? 1.0f : 1.0f - expf(-thiz->Tstep / thiz->Tsd)) );
  int nShTs = thiz->i.nSh32y-4; //this 4 regards multiply with 16.0f
  int nShfTs = 4;
  while(fTs < 7.5f) { //solution of fD versus solution of dwxPD, fD has at least 6% step width
    fTs *=2.0f;    //lesser solution for fD, but better solution of dwxP, that is important.       
    nShTs -=1;     //nr of shift from y solution right to int32 for max. Ts-solution
    nShfTs +=1;
  }
  thiz->i.nShTs = nShTs; //this 4 regards fT1 <= 16
  thiz->i.nShfTs = nShfTs;  //fTs is lesser 16 but >=8. 
  thiz->i.fTsD = (int)( fTs + 0.5f);
  int fD = (int)(thiz->Td / thiz->Tstep); // * ( ((uint32)1)<<thiz->i.nShKp);
  int nShyD = thiz->i.nSh32y;
  while(fD > 31) { //solution of fD versus solution of dwxPD, fD has at least 6% step width
    fD >>=1;    //lesser solution for fD, but better solution of dwxP, that is important.       
    nShyD -=1;  //nr of shift from int32 to y solution
  }
  thiz->i.nShyD = nShyD -4;
  thiz->i.nShfTD = 4;  //fD is lesser 16. 
  thiz->i.fD = fD;
  thiz->i.dbgct_reparam +=1;
}




PIDi_Ctrl_emC_s* ctor_PIDi_Ctrl_emC(ObjectJc* othiz)
{
  PIDi_Ctrl_emC_s* thiz = (PIDi_Ctrl_emC_s*)othiz;
  iniz_ObjectJc(othiz, othiz, sizeof(PIDi_Ctrl_emC_s), &refl_PIDi_Ctrl_emC, 0);
  return thiz; 
}



bool setParam_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, Par_PIDi_Ctrl_emC_s* par) {
  bool bOk = par != null;
  if(bOk) {
    thiz->par = par;
    setLim_PIDi_Ctrl_emC(thiz, thiz->yLim);  //reparam internal wxMax, wxMin with new parameter.
    setInitialized_ObjectJc(&thiz->base.obj);
  }
  return bOk;
}





void setLim_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, int yLim) {
  thiz->yLim = yLim;
}




RAMFUNC_emC void step_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, int wx, int* y_y)
{
  Par_PIDi_Ctrl_emC_s* par = thiz->par;
  int y;
  //Note: necessary to use int32 for wxP becauuse multiply is not limited yet.
  //The wx can use the full xBit range, kPi may be large.
  int32 wxP = ((int32)wx) * par->i.kPi;  //P-Part not limited does not overflow because check before.
  //The smoothed wxP has the full 32 bit range. It is used for differtiation, 
  //maybe used too for monitoring or for evaluation of the controller accuracy.
  //fTsD is a positive value. 
  //wxPs does never overflow because it is subtract before and muliplied with a enough less factor.
  thiz->wx = wx;  //only for debug.
  if(wxP > thiz->yLim) {
    y = thiz->yLim;
    thiz->qI = 0;
    thiz->yD = 0;
    //                              !-- use limited wxP == y for wxPs
    thiz->dwxPs = (par->i.fTsD * ( (y << par->i.nShTs) - (thiz->wxPs >> par->i.nShfTs)));  //wxPs is nShTsD bits more left.
    thiz->wxPs += thiz->dwxPs;
  }
  else if(wxP < -thiz->yLim) {
    y= -thiz->yLim;
    thiz->qI = 0;
    thiz->yD = 0;
    //                              !-- use limited wxP == y for wxPs
    thiz->dwxPs = (par->i.fTsD * ( (y << par->i.nShTs) - (thiz->wxPs >> par->i.nShfTs)));  //wxPs is nShTsD bits more left.
    thiz->wxPs += thiz->dwxPs;
  }
  else {
    //The pure D part without D-gain can be upto 32 bit width 
    thiz->dwxPs = (par->i.fTsD * ( (wxP << par->i.nShTs) - (thiz->wxPs >> par->i.nShfTs)));  //wxPs is nShTsD bits more left.
    thiz->wxPs += thiz->dwxPs; //store it for next step
    thiz->yD = ( (thiz->dwxPs >> par->i.nShfTD) * par->i.fD) >> par->i.nShyD;  //D-Part multiplied
    //I-Part
    thiz->qI += (wxP * par->i.fI);
    int yI = thiz->qI >> par->i.nSh32y;
    y = wxP;
    if(yI > (thiz->yLim - y)) {
      yI = thiz->yLim - y; 
      thiz->qI = yI << par->i.nSh32y;
    } 
    else if(yI < (-thiz->yLim - y)) {
      yI = -thiz->yLim - y; 
      thiz->qI = yI << par->i.nSh32y;
    } 
    else {}
    y += yI;
    if(thiz->yD > (thiz->yLim - y)) {
      thiz->yD = thiz->yLim - y; 
    } 
    else if(thiz->yD < (-thiz->yLim - y)) {
      thiz->yD = -thiz->yLim - y; 
    }
    y += thiz->yD;  //add after limitation, does never force overflow. 
    ASSERT_emC(y <= thiz->yLim && y >= -thiz->yLim, "faulty output PIDi", y, thiz->yLim);
  }
  *y_y = thiz->y = y;  //use hi part of integrator for output.
}

