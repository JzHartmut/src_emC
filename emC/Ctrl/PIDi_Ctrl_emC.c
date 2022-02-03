#include <emC/Ctrl/PIDi_Ctrl_emC.h>
#include <math.h>
#include <emC/Base/Assert_emC.h>
#include <emC/Base/Math_emC.h>


#ifdef DEF_REFLECTION_FULL
  #include <emC/Ctrl/genRefl/PIDi_Ctrl_emC.crefl>
#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_PIDi_Ctrl_emC) //may defined in the *.refloffs.c file
  //Class definition only as type marker: Note the ID_refl... may be used and should be planned application-wide.
  ClassJc const refl_Par_PIDi_Ctrl_emC = INIZ_ClassJc(refl_Par_PIDi_Ctrl_emC, "Test_Ctrl");
  ClassJc const refl_PIDi_Ctrl_emC = INIZ_ClassJc(refl_PIDi_Ctrl_emC, "Test_Ctrl");
#endif




Par_PIDi_Ctrl_emC_s* ctor_Par_PIDi_Ctrl_emC(ObjectJc* othiz, float Tstep)
{ //check before cast:
  ASSERT_emC(CHECKstrict_ObjectJc(othiz, sizeof(Par_PIDi_Ctrl_emC_s), refl_Par_PIDi_Ctrl_emC, 0), "faulty ObjectJc",0,0 );
  Par_PIDi_Ctrl_emC_s* thiz = (Par_PIDi_Ctrl_emC_s*)othiz;
  setInitialized_ObjectJc(othiz);
  return thiz;
}


//tag::init_Par_PIDf_Ctrl_emC[]
bool init_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz, float Tctrl_param
   ,INT_NUM_emC yMax_param, int numBits, float kP, float Tn, float Td, int dt, bool reset, bool openLoop_param)
{ 
  //ASSERT_emC(numBits >= INT_NUM_NROFBITS, "must not use 16 bit internal calculation if INT_NUM_emC is 32 bit", numBits, INT_NUM_NROFBITS); 
  thiz->Tctrl = Tctrl_param;
  thiz->yMax = yMax_param;
  thiz->numBits = numBits;             //16 or 32, resolution of numeric, should match to usage of either step16 or step32
  thiz->f12[0].open = thiz->f12[1].open = openLoop_param ? 1 : 0;

  thiz->ixf = 0;   // set to i[0] to first usage
  thiz->f12[0].en = reset? 1 : 0;   //set to no reset, to detect anyway first change!
  #if (INT_NUM_NROFBITS > 16)              // The y output is a int type anyway. 
    int32 valRangeYTest = 5000 << (numBits -0x10);  // Start with that value which is able to calculate in the given numeric bits
    ASSERT_emC(yMax_param <= 2*valRangeYTest, "valRange %d to high for calculation width %d", yMax_param, numBits);
    int ySh = 0;                       // Check the valRangeY against nr of Bits for Y
  #else
    INT_NUM_emC valRangeYTest = 5000;         // 16 bit int, start with that value which is able to calculate in 16 bit
    ASSERT_emC(yMax_param <=10000, "only 10000 as max valRange for 16-bit int type", yMax_param, 0);
    int ySh = numBits - 16;              // start with 0 or 16 as ySh
  #endif
  while( valRangeYTest > yMax_param) {   // for example 16 bit int, valRangeY = 1000, needs 11 bit (-1024...1023).
    ySh +=1; valRangeYTest >>=1;         // Hence ySh = 3 to shift the internal int range to the y range.
  }
  thiz->f12[0].nShy = thiz->f12[1].nShy = ySh;
  set_Par_PIDi_Ctrl_emC(thiz, kP, Tn, Td, dt, reset);  //note: initializes f := i[0]
  setInitialized_ObjectJc(&thiz->base.obj);
  return true;
}
//end::init_Par_PIDf_Ctrl_emC[]



//tag::set_Par_PIDi_Ctrl_emC[]
/**set Parameter of PID controller
*/
void set_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz
  , float kP, float Tn_param, float Td, int dt, bool reset) {
  bool bChanged = false;
  //man=1 is used to change the values direct with Inspector
  if(  thiz->man == 0 
    && ( thiz->kP != kP || thiz->Tn != Tn_param || thiz->Td != Td
       || !(thiz->f->en) != reset 
       )) 
  { // if one of this is changed, then calculate newly. 
    thiz->kP = kP;
    thiz->Tn = Tn_param;
    thiz->Td = Td;
    thiz->dt = dt;
    bChanged = true;
  }
  if(thiz->man || bChanged) {          //== calculate newly derived values only on change and notify the change.
    MAYBE_UNUSED_emC int bitInt = 8*sizeof(INT_NUM_emC);
    ASSERT_emC(thiz->Tctrl >0, "Tctrl <=0", (int)thiz->Tctrl, 0);
    ParFactors_PIDi_Ctrl_emC_s* f = &thiz->f12[thiz->ixf];  //use the yet not active buffer of twice
    //
    f->nShP =0;
    float maxPIDf = 10000.0f * (1<<(thiz->numBits -16)); 
    if(thiz->numBits > INT_NUM_NROFBITS) {       //== 32 bit internal calculation with 16 bit int
      MAYBE_UNUSED_emC int maxfP = 1<<(INT_NUM_NROFBITS -2);      // this is anytime 0x4000
      int kPi = int(kP * 0x4 * (1 << (f->nShy -16)));                // kP 1.0 =: 4  
      while( kPi !=0) {
        f->nShP +=1; kPi >>=1;                   // shift 2 for kP = 1.0, shift 5 for kP = 8.0...15.999
      }
      f->fP = (INT_NUM_emC)(kP * (1 <<(16 - f->nShP + f->nShy -16)));  // plays the role of a mantissa
      float wxLim = maxPIDf / f->fP;             // calculate input limit from fP
      if(wxLim < (1<<(INT_NUM_NROFBITS-1))) {
        f->wxlim = (INT_NUM_emC)( wxLim);       // prevent numerical overflow
      } else {
        f->wxlim = 0x7fff;
      }
    } else {                                     //== 16 bit internal calculation with 16 bit int
      f->fP = (INT_NUM_emC)(kP * (1 <<f->nShy));    // nr of fractional bits depends on nShy. 
      f->wxlim = (INT_NUM_emC)( maxPIDf / f->fP);       // prevent numerical overflow
      //
      f->fD = (INT_NUM_emC)( (thiz->Td / thiz->Tctrl) * (1 <<f->nShy)  / thiz->dt);
        f->dxlim = f->fD ==0 ? (1LL<<(INT_NUM_NROFBITS-1))-1 :  //max value of INT_NUM_emC 
                   (INT_NUM_emC)( maxPIDf / f->fD);       // prevent numerical overflow
    }
    //                                           // Tn =0 should force no integration, Tn <= 2*Tctrl not admissible.
    if(thiz->Tn <= 2* thiz->Tctrl) {
      f->nShKI = 0;
      f->fI = 0;
    } else {
      float kI = thiz->Tctrl / thiz->Tn;
      int32 kI_intImage = *(C_CAST(int32*,&kI));
      int16 kI_exp16 = kI_intImage>>16;            // use 16 bit high part only for more optimization by compiler
      int shKI = (0x3fff - kI_exp16) >>7;          // use exponent from float presentation for shift. It is 5 for Tn = 16.1...32 * Tctrl
      int shBits = shKI + 4;                       // get at least a resolution of 1/16 for Tn. 
      int32 nPmin = (1<< (f->nShy-4));           // The value in intermediate for resolution 1/16 of kP
      //nPmin = (int32)(kP * nPmin);                 // it is greater if kP is greater
      while ( (1<<shBits) < nPmin) {               // so long as shBits are lesser, can increase resolution of Tn
        shBits +=1;
      }
      //if(shBits < f->nShy-1) {
      //  shBits = f->nShy-1;
      //}
      //else 
      if(shBits < (32 - thiz->numBits)) {          // 
        shBits = (32 - thiz->numBits);             // shBits = 0, no shift if kP is less. No shift for step16
      }
      f->nShKI = shBits - (32 - thiz->numBits) ;   // necessary to get a fractional part      
      f->fI = (INT_NUM_emC)(kI * (1<< shBits) + 0.5f); //(1<<shBits) mults to 16..32
    }
    //
    
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
    thiz->yLim = par->yMax;                      // initial value for limf, if setLim_PIDf_Ctrl_emC is not called
    //todo thiz->disableIntg = thiz->open = par->f->open ? 1 : 0;  //hint: f->open is only determined initially. 
    setInitialized_ObjectJc(&thiz->base.obj);
  }
  return bOk;
}


void setParam_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, Par_PIDi_Ctrl_emC_s const* par) {
  ASSERT_emC(par != null, "par cannot be null", 0, 0);
  thiz->par = par;
}





void setLim_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, INT_NUM_emC yLim) {
  thiz->yLim = yLim;
}


//tag::step16_PIDi_Ctrl_emC[]
//Note: this routine is copied to RAM and runs in RAM in embedded target, sometimes faster.
RAMFUNC_emC INT_NUM_emC step16_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, INT_NUM_emC wx, INT_NUM_emC dwx)
{
  ParFactors_PIDi_Ctrl_emC_s* f = thiz->par->f;  //contains all parameter consistently
  //Note: Limitation: Use 16 bit int for small processors and 32 bit int for larger. 
  INT_NUM_emC y;
  
  //tag::step16P_PIDi_Ctrl_emC[]
  int16 wxP;                          //== Build wxP in limited form, base for P + I + D
  if(wx > f->wxlim) {                 // limit the input, should not cause overflow for kPi multiplication
    wxP = f->wxlim * f->fP;           // use the max. able to present value
  } else if (wx < -f->wxlim) {        // wxlim is ~ max int value/kPi
    wxP = - f->wxlim * f->fP;
  }
  else {
    wxP = wx * f->fP;                 //== P part mult can never overflow because checked against wxlim
  }
  //end::step16P_PIDi_Ctrl_emC[]
  //
  #ifdef DEF_TestVal_PIDi_Ctrl_emC
    thiz->wxP = wxP;
  #endif
  //
  if(dwx !=0) {
    dwx +=0;
  }
  //                                   //== D-Part
  int16 dwxP;
  if(dwx >= f->dxlim) {                  // limit the input, should not cause overflow for kPi multiplication
    dwxP = f->dxlim * f->fD;            // use the max. able to present value
  } else if(dwx <= -f->dxlim) {                  // limit the input, should not cause overflow for kPi multiplication
    dwxP = - f->dxlim * f->fD;            // use the max. able to present value
  }
  else {
    dwxP = f->fD * dwx;                 //== P part mult can never overflow because checked against wxlim
  }
  #ifdef DEF_TestVal_PIDi_Ctrl_emC
    thiz->dxP = dwxP;                     // store for viewing
  #endif
  //                                   //== I-Part
  if(f->en ==0) {                      // if the controller is disabled, 
    thiz->qI = 0;                      // set integrator states to 0
    y = 0;                             // set the output to 0                    
    //                                 // but left thiz->wxP unchanged to view
  }
  else {                               // controller is enabled, calculate all P + I +D
    //tag::step16I_PIDi_Ctrl_emC[]
    int16 yI = (int16)(thiz->qI >> 16);// access hi 16 bit from qI
    y = ((wxP + yI + dwxP) >> f->nShy);// output of P + I + D shifted to output range
    if(y >= thiz->yLim) {              // check limitaiton
      y = thiz->yLim;                  // on limit do not integrate, hold the I-part
    } 
    else if (y <=  -thiz->yLim) {
      y = -thiz->yLim;
    }
    else { //if(thiz->disableIntg ==0) {   // only if output is not limited, integrate the I-Part.
      int32 wxId;                      // nShKI is 0 in width range, only >0 for Tn >= 5000 * Tctrl
      muls16_emC(wxId, wxP >> f->nShKI, f->fI);   // growth for integrator in 32 bit width.
      thiz->qI += wxId;                // integrate
    }
    //end::step16I_PIDi_Ctrl_emC[]
    
  }  
  return thiz->y = y;  //use hi part of integrator for output.
}
//end::step16_PIDi_Ctrl_emC[]



//tag::step32_PIDi_Ctrl_emC[]
//Note: this routine is copied to RAM and runs in RAM in embedded target, sometimes faster.
RAMFUNC_emC INT_NUM_emC step32_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, INT_NUM_emC wx, INT_NUM_emC dwx)
{
  ParFactors_PIDi_Ctrl_emC_s* f = thiz->par->f;  //contains all parameter consistently
  //Note: Limitation: Use 16 bit INT_NUM_emC for small processors and 32 bit INT_NUM_emC for larger. 
  INT_NUM_emC y;
  
  //tag::step32P_PIDi_Ctrl_emC[]
  int32 wxP;                           //== Build wxP in limited form, base for P + I + D
  if(wx > f->wxlim) {                  // limit the input, should not cause overflow for kPi multiplication
    wxP = f->wxlim * f->fP;            // use the max. able to present value
  } else if (wx < -f->wxlim) {         // wxlim is ~ max INT_NUM_emC value/kPi
    wxP = - f->wxlim * f->fP;
  }
  else {
    #if (INT_NUM_NROFBITS ==16)
      muls16_emC(wxP, wx, f->fP);      // calc 32 bit <= 16 * 16 bit
      wxP <<= f->nShP;                 // for kP=1 <<4, shift is necessary because operands are only 16 bit.
    #else
      mul32lo_emC(wxP, wx, f->fP);     // calc 32 bit <= 32 * 32 bit but inputs are limited, no more as 32 bit result.
    #endif                             // P part mult can never overflow because checked against wxlim
  }
  //end::step32P_PIDi_Ctrl_emC[]
  //
  #ifdef DEF_TestVal_PIDi_Ctrl_emC
    thiz->wxP = (INT_NUM_emC)(wxP >> (INT32_NROFBITS - INT_NUM_NROFBITS));  //store as INT_NUM_emC, maybe 16 or 32 bit
  #endif
  //
  //if(dwx !=0) {
  //  dwx +=0;
  //}
  //                                   // D-Part
  int32 dwxP;
  if(dwx >= f->dxlim) {                  // limit the input, should not cause overflow for kPi multiplication
    dwxP = f->dxlim * f->fD;            // use the max. able to present value
  } else if(dwx <= -f->dxlim) {                  // limit the input, should not cause overflow for kPi multiplication
    dwxP = - f->dxlim * f->fD;            // use the max. able to present value
  }
  else {
    dwxP = f->fD * dwx;                 //== P part mult can never overflow because checked against wxlim
  }
  #ifdef DEF_TestVal_PIDi_Ctrl_emC
    thiz->dxP = dwxP;                     // store for viewing
  #endif
  //I-Part
  if(f->en ==0) {                      // if the controller is disabled, 
    thiz->qI = 0;                      // set integrator states to 0
    y = 0;                             // set the output to 0                    
    //                                 // but left thiz->wxP unchanged to view
  }
  else {                               // controller is enabled, calculate all P + I +D
    //tag::step32I_PIDi_Ctrl_emC[]
    int32 yI = thiz->qI;               // take the I-part as state, from last sampling time
    y = (INT_NUM_emC)((wxP + yI + dwxP) >> f->nShy);  //output P + I + D, shifted to output range
    if(y >= thiz->yLim) {              // limitation of output:
      y = thiz->yLim;                  // set output, then do not change the I-part.
    } 
    else if (y <=  -thiz->yLim) {
      y = -thiz->yLim;
    }
    else { //if(thiz->disableIntg ==0) {   // do integration, because not in limitaiton
      // growth for integrator. Because of tuning nShKI, fI it does never overflow in 32 bit.
      // It is important first shift the wxP, then multiply. The lost of precession is not so important.
      // Elsewhere it needs evaluation of 64 bit result, not proper for cheap processors. 
      int32 wxId; mul32lo_emC(wxId, wxP >> f->nShKI, f->fI);  
      thiz->qI += wxId;                    //integrate
    }  
    //end::step32I_PIDi_Ctrl_emC[]
  }
  //y += thiz->yD;  //add after limitation, does never force overflow. 
  //ASSERT_emC(y <= thiz->yLim && y >= -thiz->yLim, "faulty output PIDi", y, thiz->yLim);
  return thiz->y = y;  //use hi part of integrator for output.
}
//end::step32_PIDi_Ctrl_emC[]



