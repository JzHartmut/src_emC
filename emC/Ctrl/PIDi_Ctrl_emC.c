#include <emC/Ctrl/PIDi_Ctrl_emC.h>
#include <math.h>
#include <emC/Base/Assert_emC.h>


#ifdef DEF_REFLECTION_FULL
  #include <emC/Ctrl/genRefl/PIDi_Ctrl_emC.crefl>
#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_PIDi_Ctrl_emC) //may defined in the *.refloffs.c file
  //Class definition only as type marker: Note the ID_refl... may be used and should be planned application-wide.
  ClassJc const refl_Par_PIDi_Ctrl_emC = INIZ_ClassJc(refl_Par_PIDi_Ctrl_emC, "Test_Ctrl");
  ClassJc const refl_PIDi_Ctrl_emC = INIZ_ClassJc(refl_PIDi_Ctrl_emC, "Test_Ctrl");
#endif




Par_PIDi_Ctrl_emC_s* ctor_Par_PIDi_Ctrl_emC(ObjectJc* othiz, float Tstep, int xBits, int yBits)
{ //check before cast:
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(Par_PIDi_Ctrl_emC_s), refl_Par_PIDi_Ctrl_emC, 0), "faulty ObjectJc",0,0 );
  Par_PIDi_Ctrl_emC_s* thiz = (Par_PIDi_Ctrl_emC_s*)othiz;
  thiz->yBits = yBits;
  thiz->xBits = xBits;
  setInitialized_ObjectJc(othiz);
  return thiz;
}


//tag::init_Par_PIDf_Ctrl_emC[]
bool init_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz, float Tctrl_param
   , float kP, float Tn, float Td, float Tsd, bool reset, bool openLoop_param)
{ //check before cast:
  thiz->Tctrl = Tctrl_param;
  thiz->f12[0].open = thiz->f12[1].open = openLoop_param ? 1 : 0;

  thiz->ixf = 0;   // set to i[0] to first usage
  thiz->f12[0].en = reset? 1 : 0;   //set to no reset, to detect anyway first change!
  set_Par_PIDi_Ctrl_emC(thiz, kP, Tn, Td, Tsd, reset);  //note: initializes f := i[0]
  setInitialized_ObjectJc(&thiz->base.obj);
  return true;
}
//end::init_Par_PIDf_Ctrl_emC[]



//tag::set_Par_PIDi_Ctrl_emC[]
/**set Parameter of PID controller
*/
void set_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz
  , float kP, float Tn_param, float Td_param, float Tsd_param, bool reset) {
  bool bChanged = false;
  //man=1 is used to change the values direct with Inspector
  if(  thiz->man == 0 
    && ( thiz->kP != kP || thiz->Tn != Tn_param || thiz->Td != Td_param || thiz->Tsd != Tsd_param 
       || !(thiz->f->en) != reset 
       )) 
  { // if one of this is changed, then calculate newly. 
    thiz->kP = kP;
    thiz->Tn = Tn_param;
    thiz->Td = Td_param;
    thiz->Tsd = Tsd_param;
    bChanged = true;
  }
  if(thiz->man || bChanged) {          //== calculate newly derived values only on change and notify the change.
    MAYBE_UNUSED_emC int bitInt = 8*sizeof(int);
    ASSERT_emC(thiz->Tctrl >0, "Tctrl <=0", (int)thiz->Tctrl, 0);
    ParFactors_PIDi_Ctrl_emC_s* f = &thiz->f12[thiz->ixf];  //use the yet not active buffer of twice
    f->nSh32y = 32 - thiz->yBits;
    //f->nShTsD = 32 - thiz->xBits;
    f->nShKp = thiz->yBits - thiz->xBits;
    f->kPi = (int)( (thiz->kP * ( ((uint32)1)<<f->nShKp) ) + 0.5f); //in range 1.0, for example nShKp = 4, step of 1/16
    f->fI = thiz->Tn <= 0 ? 0 : (int32)( ( ((uint32)1)<<f->nSh32y ) * (thiz->Tctrl / thiz->Tn));
    //f->fI = thiz->Tn <=0 ? 0 : (int64)(f->fIx * (thiz->Tctrl / thiz->Tn)); // * (float)(0x100000000LL));
    float fTs = 16.0f * ( (thiz->Tsd <= 0 ? 1.0f : 1.0f - expf(-thiz->Tctrl / thiz->Tsd)) );
    int nShTs = f->nSh32y-4; //this 4 regards multiply with 16.0f
    int nShfTs = 4;
    while(fTs < 7.5f) { //solution of fD versus solution of dwxPD, fD has at least 6% step width
      fTs *=2.0f;    //lesser solution for fD, but better solution of dwxP, that is important.       
      nShTs -=1;     //nr of shift from y solution right to int32 for max. Ts-solution
      nShfTs +=1;
    }
    f->nShTs = nShTs; //this 4 regards fT1 <= 16
    f->nShfTs = nShfTs;  //fTs is lesser 16 but >=8. 
    f->fTsD = (int)( fTs + 0.5f);
    int fD = (int)(thiz->Td / thiz->Tctrl); // * ( ((uint32)1)<<f->nShKp);
    int nShyD = f->nSh32y;
    while(fD > 31) { //solution of fD versus solution of dwxPD, fD has at least 6% step width
      fD >>=1;    //lesser solution for fD, but better solution of dwxP, that is important.       
      nShyD -=1;  //nr of shift from int32 to y solution
    }
    f->nShyD = nShyD -4;
    f->nShfTD = 4;  //fD is lesser 16. 
    f->fD = fD;
    //thiz->dbgct_reparam +=1;
    thiz->f = f;                       // use this set complete immediately after calculation. 
    thiz->ixf = thiz->ixf==1 ? 0 : 1;  // use the other one for next change of values.
  }
}
//end::set_Par_PIDi_Ctrl_emC[]




PIDi_Ctrl_emC_s* ctor_PIDi_Ctrl_emC(ObjectJc* othiz)
{
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(PIDi_Ctrl_emC_s), refl_PIDi_Ctrl_emC, 0), "faulty ObjectJc", 0,0);
  //after assertion it can be used.
  PIDi_Ctrl_emC_s* thiz = (PIDi_Ctrl_emC_s*)othiz;
  return thiz; 
}



bool init_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, Par_PIDi_Ctrl_emC_s const* par) {
  bool bOk = par != null;
  if(bOk) {
    thiz->par = par;
    setInitialized_ObjectJc(&thiz->base.obj);
  }
  return bOk;
}


void setParam_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, Par_PIDi_Ctrl_emC_s const* par) {
  ASSERT_emC(par != null, "par cannot be null", 0, 0);
  thiz->par = par;
}





void setLim_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, int yLim) {
  thiz->yLim = yLim;
}


//tag::step_PIDi_Ctrl_emC[]
//Note: this routine is copied to RAM and runs in RAM in embedded target, sometimes faster.
RAMFUNC_emC int step_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, int wx, int wxd)
{
  ParFactors_PIDi_Ctrl_emC_s* f = thiz->par->f;  //contains all parameter consistently
  int y;
  
  int wx1 = wx;                        //== Limit the input to prevent overflow for kPi
  int wxP;
  if(wx > f->wxlim) {
    wx1 = f->wxlim;
    wxP = f->wxlim * f->kPi;
  } else if (wx < -f->wxlim) {
    wx1 = - f->wxlim;
    wxP = - f->wxlim * f->kPi;
  }
  else {
    wxP = wx * f->kPi;                //== P part mult can never overflow because tuned wxlim, kPi
  }
  //
  #ifdef DEF_TestVal_PIDi_Ctrl_emC
    thiz->wxP = wxP;
  #endif
  //I-Part
  int yI = thiz->qI >> 16; //f->nSh32y;
  y = wxP + yI;
  if(y >= thiz->yLim) {
    y = thiz->yLim;
  } 
  else if (y <=  -thiz->yLim) {
    y = -thiz->yLim;
  }
  else {
    int32 wxId = wxP * f->fI;                // growth for integrator. It is 32 bit width maybe >0x10000.
    thiz->qI += wxId;                    //integrate
  }  
  //y += thiz->yD;  //add after limitation, does never force overflow. 
  //ASSERT_emC(y <= thiz->yLim && y >= -thiz->yLim, "faulty output PIDi", y, thiz->yLim);
  return thiz->y = y >> f->nSh32y;  //use hi part of integrator for output.
}
//end::step_PIDi_Ctrl_emC[]



//Note: this routine is copied to RAM and runs in RAM in embedded target, sometimes faster.
RAMFUNC_emC int oldstep_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, int wx, int wxd)
{
  ParFactors_PIDi_Ctrl_emC_s* f = thiz->par->f;  //contains all parameter consistently
  int y;
  int32 wxP = 0;
  //Note: necessary to use int32 for wxP becauuse multiply is not limited yet.
  //The wx can use the full xBit range, kPi may be large.
  //old int32 wxP = ((int32)wx) * f->kPi;  //P-Part not limited does not overflow because check before.
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
    thiz->dwxPs = (f->fTsD * ( (y << f->nShTs) - (thiz->wxPs >> f->nShfTs)));  //wxPs is nShTsD bits more left.
    thiz->wxPs += thiz->dwxPs;
  }
  else if(wxP < -thiz->yLim) {
    y= -thiz->yLim;
    thiz->qI = 0;
    thiz->yD = 0;
    //                              !-- use limited wxP == y for wxPs
    thiz->dwxPs = (f->fTsD * ( (y << f->nShTs) - (thiz->wxPs >> f->nShfTs)));  //wxPs is nShTsD bits more left.
    thiz->wxPs += thiz->dwxPs;
  }
  else {
    //The pure D part without D-gain can be upto 32 bit width 
    thiz->dwxPs = (f->fTsD * ( (wxP << f->nShTs) - (thiz->wxPs >> f->nShfTs)));  //wxPs is nShTsD bits more left.
    thiz->wxPs += thiz->dwxPs; //store it for next step
    thiz->yD = ( (thiz->dwxPs >> f->nShfTD) * f->fD) >> f->nShyD;  //D-Part multiplied
    //I-Part
    thiz->qI += (wxP * f->fI);
    int yI = thiz->qI >> f->nSh32y;
    y = wxP;
    if(yI > (thiz->yLim - y)) {
      yI = thiz->yLim - y; 
      thiz->qI = yI << f->nSh32y;
    } 
    else if(yI < (-thiz->yLim - y)) {
      yI = -thiz->yLim - y; 
      thiz->qI = yI << f->nSh32y;
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
  return thiz->y = y;  //use hi part of integrator for output.
}

