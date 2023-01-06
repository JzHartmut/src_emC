#include <emC/Ctrl/PIDf_Ctrl_emC.h>
#include <emC/Base/Math_emC.h>
#include <math.h>
#include <string.h>



void setLim64_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float yLim) {
  if(yLim > thiz->par->yMax) { yLim = thiz->par->yMax; }
  else if(yLim <0) { yLim = 0; }
  thiz->limf = yLim;
  if(thiz->yIntg > thiz->limf) {    // limit the integrator if it is now out of limit
    thiz->qI.qI64 = (int64)((int32)(thiz->par->fIx * yLim))<<32;
    thiz->yIntg = yLim;
  } else if(thiz->yIntg < -thiz->limf) {
    thiz->qI.qI64 = (int64)(-(int32)(thiz->par->fIx * yLim))<<32;
    thiz->yIntg = -yLim;
  }
}




void setIntg64_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float intg, bool set, bool hold, float* intg_y) 
{
  if(set) {
    if(intg > thiz->limf) { intg = thiz->limf; }
    else if(intg < -thiz->limf) { intg = -thiz->limf; }
    thiz->yIntg = intg;
    //int32 qI = (int32)(thiz->par->fIx * intg);            // set I part, convert float to int32
    //thiz->qIhi = qI;
    thiz->qI.qI64 = ((int64)(thiz->par->fIx * intg))<<32;                // Note: The I part is not limited      
    thiz->setIntg = 1;
    thiz->disableIntg = 1;
  } else {
    thiz->setIntg = 0;
    thiz->disableIntg = hold;
  }
  if(intg_y !=null) { *intg_y = thiz->yIntg; }
}





void step64_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float wx, float wxd, float* y_y)
{
  Par_PIDf_Ctrl_emC_s* par = thiz->par;
  ParFactors_PIDf_Ctrl_emC_s* f = par->f;  //contains all parameter consistently
  //                                   // === build smoothed input for D-part
  //
  float wxP = wx * f->kP;
  thiz->wxP = wxP;
  //                                   // == calculate D-Part
  float dx = (wxd - thiz->xds);            // the D part from smoothed input
  thiz->xds += dx;   // smooth the input
  float dxP = f->fD * dx;             // effective D part for control.
  if (dxP > thiz->limf) {              //limit it.
    dxP = thiz->limf;
  }
  else if (dxP < -thiz->limf) { 
    dxP = -thiz->limf; 
  }
  else {
  } //remain dxP
  thiz->dxP = dxP;
  //
  if(f->en ==0) {                      // if the controller is disabled, 
    thiz->xds = wxd;                   // the xds follows input, no smoothing. D part smoothing will start with 0.
    thiz->yIntg = 0;                   // set integrator states to 0
    thiz->qI.qI64 = 0;
    thiz->yctrl = 0;                   // set the output to 0                    
    //                                 // but left thiz->wxP unchanged to view
  }
  else {                               // controller is enabled, calculate all p+I+D
    float y = wxP + dxP + thiz->yIntg + thiz->yAdd;
    if(y >= thiz->limf)  {             // limitation
      y = thiz->limf;                  // limit the output
    }
    else if(y < -thiz->limf) {         // same for negative limit 
      y = -thiz->limf; 
    }
    else if(thiz->disableIntg ==0) {   // integrate for next step only if not limited
      int64 wxP64i = (int64)(f->fI * wxP * (float)(0x100000000LL));
      thiz->qI.qI64 += wxP64i;                        // integer for exact integration.
      thiz->yIntg = (int32)((thiz->qI.qI64)>>32) * thiz->par->fIy;  // float used. 
    } else { 
      //                               // for test, manual changed yIntg is taken.
      thiz->qI.qI64 = ((int64)(thiz->par->fIx * thiz->yIntg))<<32;    // Note: The I part is not limited      
    }
    thiz->yctrl = y;                   // store output, after maybe limitation
  }
  //
  //
  if(!thiz->open) {                // if the controller is losed, open loop only for test remains the y
    thiz->y = thiz->yctrl;              // use the calculated for output
  }
  *y_y = thiz->y;
}






