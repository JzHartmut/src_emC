#include <emC/Ctrl/PIDf_Ctrl_emC.h>
#include <emC/Base/Math_emC.h>
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
  ClassJc const refl_Par_PIDf_Ctrl_emC = INIZ_ClassJc(refl_Par_PIDf_Ctrl_emC, "Par_PIDf_Ctrl_emC");
  //ClassJc const refl_ParFactors_PIDf_Ctrl_emC = INIZ_ClassJc(refl_ParFactors_PIDf_Ctrl_emC, "ParFactors_PIDf_Ctrl_emC");
  ClassJc const refl_PIDf_Ctrl_emC = INIZ_ClassJc(refl_PIDf_Ctrl_emC, "PIDf_Ctrl_emC");
//#else
//  extern_C int const refl_Par_PID_Vtrl
#endif

//This is the max used value for the integrator. 
//Par_PIDf_Ctrl_emC_s.fIy is set so that this maps the given yMax for the output of the controller.
//Note that a range should be reserved (0x07ffffff) for adding one value to the integrator. 
//It means ParFactors_PIDf_Ctrl_emC_s.fI shold be <= 0x07fffffff/0x78000000, that is <= 1/16. Tn >= 16*Tstep. This is tested.
#define INTG_MAX 0x78000000L


//tag::ctor_Par_PIDf_Ctrl_emC[]
Par_PIDf_Ctrl_emC_s* ctor_Par_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep)
{ //check before cast:
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(Par_PIDf_Ctrl_emC_s), refl_Par_PIDf_Ctrl_emC, 0), "faulty ObjectJc",0,0 );
  Par_PIDf_Ctrl_emC_s* thiz = (Par_PIDf_Ctrl_emC_s*)othiz;
  return thiz;
}
//end::ctor_Par_PIDf_Ctrl_emC[]


//tag::init_Par_PIDf_Ctrl_emC[]
bool init_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float Tctrl_param, float yMax_param
   , float kP, float Tn, float Td, float dt, bool reset, bool openLoop_param)
{ //check before cast:
  thiz->Tctrl = Tctrl_param;
  thiz->yMax = yMax_param;
  thiz->fIy = thiz->yMax / (float)(INTG_MAX);
  thiz->fIx = (float)(INTG_MAX) / thiz->yMax;   //for yMax the value is INTG_MAX no overflow because limitation.
  thiz->i[0].open = thiz->i[1].open = openLoop_param ? 1 : 0;

  thiz->ixf = 0;   // set to i[0] to first usage
  thiz->i[0].en = reset? 1 : 0;   //set to no reset, to detect anyway first change!
  set_Par_PIDf_Ctrl_emC(thiz, kP, Tn, Td, dt, reset);  //note: initializes f := i[0]
  setInitialized_ObjectJc(&thiz->base.obj);
  return true;
}
//end::init_Par_PIDf_Ctrl_emC[]


//tag::set_Par_PIDf_Ctrl_emC[]
/**set Parameter of PID controller
*/
void set_Par_PIDf_Ctrl_emC ( Par_PIDf_Ctrl_emC_s* thiz
  , float kP, float Tn, float Td, float dt, bool reset ) {
  bool bChanged = false;
  //man=1 is used to change the values direct with Inspector
  if(  thiz->man == 0 
    && ( thiz->kP != kP || thiz->Tn != Tn || thiz->Td != Td || thiz->dt != dt  
       || !(thiz->f->en) != reset 
       )) 
  { // if one of this is changed, then calculate newly. 
    thiz->kP = kP;
    thiz->Tn = Tn;
    thiz->Td = Td;
    thiz->dt = dt;
    bChanged = true;
  }
  if(thiz->man || bChanged) {          //== calculate newly derived values only on change and notify the change.
    ParFactors_PIDf_Ctrl_emC_s* f = &thiz->i[thiz->ixf];  //use the yet not active buffer of twice
    f->en = reset? 0 : 1;
    f->kP = thiz->kP;                  //A less value, especially 0 means "no integration" such as Tn very high.
    f->fI = thiz->Tn <= 16*thiz->Tctrl ? 0 : thiz->fIx * (thiz->Tctrl / thiz->Tn);
    //Note: Tn > 16*Tctrl because elsewhere an additional overflow check may be necessary in runtime.
    // It depends on the definition of INTG_MAX. 16 is tuned to 0x78000000 
    //Tn is usual > 16*Tctrl.
    ASSERT_emC(thiz->Tn > 16*thiz->Tctrl || thiz->Tn ==0, "", (int)(thiz->Tn/thiz->Tctrl), (int)(thiz->Tctrl * 1000000));
    f->fD = thiz->kP * (thiz->Td / thiz->dt);
    //fTsd is a value in range 0.000... 1.0
    //
    thiz->dbgct_reparam +=1;
    thiz->f = f;                       // use this set complete immediately after calculation. 
    thiz->ixf = thiz->ixf==1 ? 0 : 1;  // use the other one for next change of values.
  }
}
//end::set_Par_PIDf_Ctrl_emC[]



//tag::ctor_PIDf_Ctrl_emC[]
PIDf_Ctrl_emC_s* ctor_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep)
{
  //check before cast:
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, 0), "faulty ObjectJc",0,0 );
  PIDf_Ctrl_emC_s* thiz = (PIDf_Ctrl_emC_s*)othiz;
  //should be done outside! CTOR_ObjectJc(othiz, othiz, sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, 0);
  //inner ObjectJc-based struct:
  //CTOR_ObjectJc(&thiz->f.base.obj, &thiz->f, sizeof(thiz->f), refl_ParFactors_PIDf_Ctrl_emC, 1);
  thiz->Tstep = Tstep;  //park it here.
  return thiz; 
}
//end::ctor_PIDf_Ctrl_emC[]





//tag::init_PIDf_Ctrl_emC[]
bool init_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, Par_PIDf_Ctrl_emC_s* par) {
  bool bOk = (par != null && isInitialized_ObjectJc(&par->base.obj));  //paramter should be already initialized
  if(bOk) {
    ASSERT_TEST_emC(par->f !=null, "f should be set", 0, 0);
    thiz->par = par;  
    //                                           // compare Tstep stored in yctrl with par->Tctrl, should be the same
    ASSERT_emC(par->Tctrl == thiz->Tstep, "faulty Tstep", (int)(par->Tctrl * 10000000), (int)(thiz->yctrl*1000000)); 
    //It cleans only a bit. The rest is done in another time slice.
    thiz->limf = par->yMax;                      // initial value for limf, if setLim_PIDf_Ctrl_emC is not called
    thiz->disableIntg = thiz->open = par->f->open ? 1 : 0;  //hint: f->open is only determined initially. 
    setInitialized_ObjectJc(&thiz->base.obj);
  }
  return bOk;
}
//end::init_PIDf_Ctrl_emC[]



//tag::setLim_PIDf_Ctrl_emC[]
void setLim_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float yLim) {
  if(yLim > thiz->par->yMax) { yLim = thiz->par->yMax; }
  else if(yLim <0) { yLim = 0; }
  if(yLim < thiz->limf) {              //== check the integrator only on lesser limit
    //note: on increasing the integrator is never faulty. Save calc time.
    if(thiz->yIntg > yLim) {     // limit the integrator if it is now out of limit
      thiz->qI.qI32 = (int32)(thiz->par->fIx * yLim);
      thiz->yIntg = yLim;
    } else if(thiz->yIntg < -yLim) {
      thiz->qI.qI32 = -(int32)(thiz->par->fIx * yLim);
      thiz->yIntg = -yLim;
    }
  }
  thiz->limf = yLim;                   // now set it!
}
//end::setLim_PIDf_Ctrl_emC[]




//tag::setIntg_PIDf_Ctrl_emC[]
void setIntg_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float intg, bool set, bool hold, float* intg_y) 
{
  if(set) {
    if(intg > thiz->limf) { intg = thiz->limf; }
    else if(intg < -thiz->limf) { intg = -thiz->limf; }
    thiz->yIntg = intg;
    int32 qI = (int32)(thiz->par->fIx * intg);            // set I part, convert float to int32
    thiz->qI.qI32 = qI;                // Note: The I part is not limited      
    thiz->setIntg = 1;
    thiz->disableIntg = 1;
  } else {
    thiz->setIntg = 0;
    thiz->disableIntg = hold;
  }
  if(intg_y !=null) { *intg_y = thiz->yIntg; }
}
//end::setIntg_PIDf_Ctrl_emC[]



//tag::step_PIDf_Ctrl_emC[]
/**This is the core routine for PIDf ctrl, getting the built dx as value. 
 * It is static also to enable compiler optimization. 
 * @param wx Input for P and I
 * @param dx Input for D-part as already built and smoothed differential
 * @return y value. 
 */
float step_PIDf_Ctrl_emC ( PIDf_Ctrl_emC_s* thiz, float wx, float dx)
{
  ParFactors_PIDf_Ctrl_emC_s* f = thiz->par->f;
  float wxP = wx * f->kP;              //== P-Part
  thiz->wxP = wxP;

  float dxP = f->fD * dx;             // effective D part for control with kP and Td/Tstep.
  if (dxP > thiz->limf) {              // limit it.
    dxP = thiz->limf;
  }
  else if (dxP < -thiz->limf) { 
    dxP = -thiz->limf; 
  }

  float y;
  //end::stepD_PIDf_Ctrl_emC[]
  if(f->en ==0) {                      // if the controller is disabled, 
    thiz->yIntg = 0;                   // set integrator states to 0
    thiz->qI.qI32 = 0;
    thiz->yctrl = y = 0;               // set the output to 0                    
    //                                 // but left thiz->wxP unchanged to view
  }
  else {                               // controller is enabled, calculate all P + I +D
    //tag::Intg_step_PIDf_Ctrl_emC[]
    y = wxP + dxP + thiz->yIntg + thiz->yAdd;
    if(y >= thiz->limf)  {             // limitation necessary:
      y = thiz->limf;                  // limit the output
      if(thiz->qI.qI32 > INTG_MAX) {
        thiz->qI.qI32 = INTG_MAX;        // limit the integrator, 
      }
    }
    else if(y < -thiz->limf) {         // same for negative limit 
      y = -thiz->limf; 
      if (thiz->qI.qI32 < -INTG_MAX) {
          thiz->qI.qI32 = -INTG_MAX;
      }
    }
    else if(thiz->disableIntg ==0) {   // integrate for next step only if not limited
      int32 wxP32i = (int32)(f->fI * wxP); //growth for integrator
      //Note: It is possible that a possible limitation was not detected just now, 
      //but it is effective in the next step time.
      //Then the following is true: 
      //1) The max. value for qI32 in this moment is INTG_MAX correspond to fIy and fIx.
      //   An numeric overflow can never occur if Tn > 32 * Tstep (16 >= INTG_MAX/(0x7fffffff-INTG_MAX) 0x7e00/0x01ff)
      //   That is a very less Tn, it is tested on parametrizing.
      //2) An overdrive of the integrator for one step can occure 
      //   because the integration is done after limit check. 
      //   But this is only one time, only the integration of one Tstep.
      //   It is not effective for wind-up because it is integrated back 
      //   in the next step time after left limitation.
      //ASSERT_TEST_emC(wxP32i <= 0x01ffffff && wxP32i >= -0x01ffffff, "overflow possible", wxP32i, thiz->qI.qI32 );
      thiz->qI.qI32 += wxP32i;         // use integer for exact integration.
      thiz->yIntg = (int32)((thiz->qI.qI32)) * thiz->par->fIy;  // float used. 
    } 
    else { 
      //                               // for test, manual changed yIntg is taken.
      thiz->qI.qI32 = (int32)(thiz->par->fIx * thiz->yIntg);    // Note: The I part is not limited      
    }
    thiz->yctrl = y;                   // store output, after maybe limited
    //end::Intg_step_PIDf_Ctrl_emC[]
  }
  thiz->dxP = dxP;                     // store for viewing
  //
  //
  if(!thiz->open) {                // if the controller is losed, open loop only for test remains the y
    thiz->y = y;              // use the calculated for output
  }
  return y;
  
}
//end::step_PIDf_Ctrl_emC[]




