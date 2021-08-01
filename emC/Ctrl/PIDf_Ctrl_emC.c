#include <emC/Ctrl/PIDf_Ctrl_emC.h>
#include <math.h>
#include <string.h>


#ifdef DEF_REFLECTION_FULL
//#ifndef DEF_REFLECTION_NOXX
#include <emC/Ctrl/genRefl/PIDf_Ctrl_emC.crefl>
#elif defined(DEFINED_refl_Par_PIDf_Ctrl_emC)  //DEF_REFLECTION_OFFS but special with this classes
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_Par_PIDf_Ctrl_emC;
  extern_C ClassJc const refl_ParFactors_PIDf_Ctrl_emC;
  extern_C ClassJc const refl_PIDf_Ctrl_emC;
#elif !defined(DEF_REFLECTION_NO)
  //Class definition only as type marker: Note the ident should be planned application-wide and used for instances too.
  ClassJc const refl_Par_PIDf_Ctrl_emC = INIZ_ClassJc(refl_Par_PIDf_Ctrl_emC, "Test_Ctrl");
  ClassJc const refl_ParFactors_PIDf_Ctrl_emC = INIZ_ClassJc(refl_ParFactors_PIDf_Ctrl_emC, "Test_Ctrl");
  ClassJc const refl_PIDf_Ctrl_emC = INIZ_ClassJc(refl_PIDf_Ctrl_emC, "Test_Ctrl");
//#else
//  extern_C int const refl_Par_PID_Vtrl
#endif




Par_PIDf_Ctrl_emC_s* ctor_Par_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep)
{ //check before cast:
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(Par_PIDf_Ctrl_emC_s), refl_Par_PIDf_Ctrl_emC, 0), "faulty ObjectJc",0,0 );
  Par_PIDf_Ctrl_emC_s* thiz = (Par_PIDf_Ctrl_emC_s*)othiz;
  //inner ObjectJc-based struct:
  CTOR_ObjectJc(&thiz->i[0].base.obj, &thiz->i, sizeof(thiz->i), refl_ParFactors_PIDf_Ctrl_emC, 1);
  CTOR_ObjectJc(&thiz->i[1].base.obj, &thiz->i, sizeof(thiz->i), refl_ParFactors_PIDf_Ctrl_emC, 1);
  return thiz;
}


bool init_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float Tctrl_param, float yMax_param
   , float kP, float Tn, float Td, float Tsd, bool reset, bool openLoop_param)
{ //check before cast:
  thiz->Tctrl = Tctrl_param;
  thiz->yMax = yMax_param;
  thiz->ixf = 0;   // set to i[0]
  if(openLoop_param) {               // default is 0, only for test set both 1 to reset manually
    thiz->open = thiz->noIntg = 1;
  } else {
    thiz->en = 1;               // default en=1 if reset FBlock is not used.
  }

  set_Par_PIDf_Ctrl_emC(thiz, kP, Tn, Td, Tsd, reset);
  thiz->f = &thiz->i[0];                // use swap buffer 0
  setInitialized_ObjectJc(&thiz->base.obj);
  return true;
}


/**step of PID controller
* @simulink Object-FB.
*/
void set_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float kP, float Tn_param, float Td_param, float Tsd_param, bool reset) {
  //if(!isLocked_ObjectJc(&thiz->i.base.obj)) { //do not change the current parameter yet. 
  if(reset) {
    thiz->en = 0;
  } else {
    thiz->en = 1;
  } 
  if(thiz->man == 0 && (thiz->kP != kP || thiz->Tn != Tn_param || thiz->Td != Td_param || thiz->T1d != Tsd_param )) 
  { // if one of this is changed, then calculate newly. 
      thiz->kP = kP;
      thiz->Tn = Tn_param;
      thiz->Td = Td_param;
      thiz->T1d = Tsd_param;
      //thiz->limPbeforeD = 1;  //it is better to fast reach point with max controller output. 
    ParFactors_PIDf_Ctrl_emC_s* f = &thiz->i[thiz->ixf];
    f->kP = thiz->kP;
    f->yMax = thiz->yMax;
    f->fIy = thiz->yMax / (float)(0x40000000L);
    f->fIx = (float)(0x40000000L) / thiz->yMax;   //for yMax the value is 0x40000000
    //fI is bit63..32 of multiplication. Stored as 32 bit. Related to yMax.                        
    f->fI = thiz->Tn <=thiz->Tctrl ? 0 : (int32)(/*f->fIx * */(thiz->Tctrl / thiz->Tn)* 4*(float)(0x40000000)); // * (float)(0x100000000LL));
    
    f->fTsD = thiz->T1d <= 0 ? 1.0f : 1.0f - expf(-thiz->Tctrl / thiz->T1d);
    f->fD = (thiz->Td / thiz->Tctrl); // * thiz->kP;
    thiz->dbgct_reparam +=1;
    thiz->f = f;                       // use this set complete immediately after calculation. 
    thiz->ixf = thiz->ixf==1 ? 0 : 1;  // use the other one for next change of values.
    //lock_ObjectJc(&f->base.obj);
  }
  //Output the pointer anyway also in case of lock, it should be determined.
  //if(parFactors_y){ *parFactors_y = thiz->f; }  //use the reference to the prepared inner data as event data reference
    //if(man_y !=null) { *man_y = thiz->man ? 1 : 0; }
}




PIDf_Ctrl_emC_s* ctor_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep)
{
  //check before cast:
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, 0), "faulty ObjectJc",0,0 );
  PIDf_Ctrl_emC_s* thiz = (PIDf_Ctrl_emC_s*)othiz;
  //should be done outside! CTOR_ObjectJc(othiz, othiz, sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, 0);
  //inner ObjectJc-based struct:
  //CTOR_ObjectJc(&thiz->f.base.obj, &thiz->f, sizeof(thiz->f), refl_ParFactors_PIDf_Ctrl_emC, 1);
  thiz->Tstep = Tstep;
  thiz->lim = 1.0f;
  return thiz; 
}





bool init_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, Par_PIDf_Ctrl_emC_s* par) {
  bool bOk = par != null;
  if(bOk) {
    thiz->par = par;  //it is a memcpy
    //It cleans only a bit. The rest is done in another time slice.
    thiz->lim = par->yMax;
    unlock_ObjectJc(&par->base.obj);
    setInitialized_ObjectJc(&thiz->base.obj);
  }
  return bOk;
}



void setLim_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float yLim) {
  thiz->lim = yLim;
}


//void param_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, ParFactors_PIDf_Ctrl_emC_s* par) {
//  if(par !=null && memcmp(par, &thiz->f, sizeof(thiz->f)) !=0) { //both have same type!
//    //only if there is a difference, set the event.
//    thiz->parNew = par;
//  } else {
//    unlock_ObjectJc(&par->base.obj); //should be unlocked, nobody does it elsewhere!
//  }
//}




void step_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float wx, float* y_y, float* ctrl_y)
{
  ParFactors_PIDf_Ctrl_emC_s* f = thiz->par->f;
  float wxP = wx * f->kP;
  //limit to max output.
  if (wxP > thiz->lim) { wxP = thiz->lim; }
  else if (wxP < -thiz->lim) { wxP = -thiz->lim; }
  else {} //reamin wxP

  
  float dwxP = wxP - thiz->wxP;  //on limitation the dwxP is 0. It is better for increasing the process signal on max output.
  thiz->dwxP += (f->fTsD * (dwxP - thiz->dwxP));
  thiz->wxP = wxP;  //store for differenzial and to inspect
  if(thiz->par->en ==0) {
    thiz->dwxP = 0;     //no differentiation on hold, 0 on reset
    thiz->qI = 0;
    thiz->wxPD32 = 0;   //0 on reset, unchange on hold.
  }
  else {
    float wxPD = wxP + (f->fD * thiz->dwxP);  //+ D-Part.

    //limit P + D.
    if (wxPD > thiz->lim) { wxPD = thiz->lim; }
    else if (wxPD < -thiz->lim) { wxPD = -thiz->lim; }
    else {} //remain wxPD
    thiz->wxPD = wxPD;  //to inspect.

    int32 wxP32 = (int32)(f->fIx * wxP);  //integer representation of wxP

    int32 wxPD32 = (int32)(f->fIx * wxPD);     //has never an overflow because wxPD is limited.
    int32 yImin, yImax;
    //limit it to 24 bit
    if (wxP32 < 0) { yImin = -0x40000000L - wxP32; yImax =  0x40000000L; }  //
    else {          yImax =  0x40000000L - wxP32; yImin = -0x40000000L; }
    thiz->wxPD32 = wxPD32;  //to inspect
    if(thiz->par->noIntg ==0) {
      int64 xdI = wxP32 * (((int64)f->fI));
      int64 qI1 = thiz->qI + xdI;
      int32 qIhi = (int32)(qI1 >> 32);
      if (qIhi > yImax) { qIhi = yImax; qI1 = ((int64)qIhi) << 32; }
      else if (qIhi < yImin) { qIhi = yImin; qI1 = ((int64)qIhi) << 32; }
      else {} //remain qIhi
      thiz->qI = qI1;
      thiz->qIhi = qIhi;
    }
  }
  *ctrl_y = thiz->yctrl = f->fIy * (thiz->wxPD32 + (int32)(thiz->qI >>32));  //use hi part of integrator for output.
  if(thiz->par->open) 
  {
    if(thiz->yAdd !=null) {
      thiz->y = *(float*)thiz->yAdd;
    }
    else { //left thiz->y unchanged, manual change via Inspector is possible 
    }
  }
  else 
  {
    thiz->y = thiz->yctrl;
    if(thiz->yAdd !=null) {
      thiz->y += *(float*)thiz->yAdd;
    }
  }
  *y_y = thiz->y;
}

