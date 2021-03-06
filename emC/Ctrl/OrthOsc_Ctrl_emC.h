#ifndef __OrthOsc_FB_h
#define __OrthOsc_FB_h

#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <emC/Base/Math_emC.h>
#include <emC/Ctrl/Angle_Ctrl_emC.h>
#include <math.h>


extern bool isInit_global_;


/*CLASS_C OrthOsc2_CtrlemC_s *************************************************************************************************************/

/**
 * @s imulink bus
 */
typedef struct Param_OrthOsc2_CtrlemC_T
{
  ObjectJc obj;

  /**Frquency and step time. */
  float tStepOrthi;

  /**The given frequency in step routine. Only for debug. 0.0 if nStepPeriod is given. */
  float fq;

  /**The given steps per period in step routine. Only for debug. 0.0 if fq is given. */
  float nStepsPeriod;

  /**Nominal value for magnitude.*/
  float nom_m;

  /**Integrator values form same signal, from other.*/
  float fIa, fIb;

  /**Integrator factor from the other component.*/
  float fIoth;

  /**Integrator factor (1.0f - factor from same component). This factor is ~ 0.00..., subtract from own compn. */
  float fIown;

  /**Factors for magnitude and reciproce. */ 
  float fm, fmr;


} Param_OrthOsc2_CtrlemC_s;

#ifndef ID_refl_Param_OrthOsc2_CtrlemC
  #define ID_refl_Param_OrthOsc2_CtrlemC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Param_OrthOsc2_CtrlemC;
#endif




/**Initializes the Param_OrtOsc2_FB
 * @param Tstep
 * @s imulink ctor
 */
void ctor_Param_OrthOsc2_CtrlemC(Param_OrthOsc2_CtrlemC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m);



/**
 * @s imulink Object-FB
 */
static inline void setPeriod_Param_OrthOsc2_CtrlemC(Param_OrthOsc2_CtrlemC_s* thiz, float nStepsPeriod)
{ 
#ifndef __ignoreInCheader_zbnf__
  float fI1 = 2*PI_float_emC / nStepsPeriod;
  float fIcos = cosf(fI1);
  float fIcorr = (fIcos +3) /4;
  float fIcorr2 = (fIcos +11) /12;
  //thiz->fq = 1.0f/ (thiz->tStepOrthi * nStepsPeriod);
  thiz->nStepsPeriod = nStepsPeriod;
  thiz->fIa = fI1 * fIcorr2 / fIcorr;
  thiz->fIb = fI1 * fIcorr2 * fIcorr;
#endif//__ignoreInCheader_zbnf__
}


/**
 * @s imulink Object-FB
 */
static inline void setFq_Param_OrthOsc2_CtrlemC(Param_OrthOsc2_CtrlemC_s* thiz, float fq)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  float fI1 = 2*PI_float_emC * thiz->tStepOrthi * fq;
  float fIcos = cosf(fI1);
  thiz->fIown = 1.0f - fIcos; //the little rest to subtract
  thiz->fIoth = sinf(fI1);    //forward gain from other compn, determines fq
  float fIcorr = (fIcos +3) /4;
  float fIcorr2 = (fIcos +11) /12;
  thiz->fq = fq;
  thiz->fIa = fI1 * fIcorr2 / fIcorr;
  thiz->fIb = fI1 * fIcorr2 * fIcorr;
#endif//__ignoreInCheader_zbnf__

}


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Param_OrthOsc2_CtrlemC : private Param_OrthOsc2_CtrlemC_s {
  friend class OrthOsc2_CtrlemC;
  public: 
  
  Param_OrthOsc2_CtrlemC(int32 identObj, float Tstep, float tStepOrthi, float nom_m);

  void setPeriod(float nStepsPeriod) { setPeriod_Param_OrthOsc2_CtrlemC(this, nStepsPeriod); }
  void setFq(float fq) { setFq_Param_OrthOsc2_CtrlemC(this, fq); }

};
#endif //__cplusplus



/**Internal data of a OrthogonalOscillator.
 * @s imulink no-bus 
 */
typedef struct OrthOsc2_CtrlemC_T
{
  ObjectJc obj;  //:The base structure
  Param_OrthOsc2_CtrlemC_s* par;  //:Reference to parameter, maybe calculated in other step time.
  Angle_abwmf_FB_CtrlemC* anglep;  //:Reference to angle, null is admissable.

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  float kA, kB;

  float_complex yab;  //:Orthogonal components of oscillation. 
  float_complex ypq;  //:optional: Orthogonal components as fundamental values, after park-transformation with angle.
  float m, mr;        //:optional: Magnitude and its reciproke, if calculated
  //
  float b_;           //:internal b component

  int32 __spare;   //:for 8 Byte align
} OrthOsc2_CtrlemC_s;


#ifndef ID_refl_OrthOsc2_CtrlemC
  #define ID_refl_OrthOsc2_CtrlemC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_OrthOsc2_CtrlemC;
#endif


/**@s imulink ctor
 */
OrthOsc2_CtrlemC_s* ctor_OrthOsc2_CtrlemC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep);


/**Prepares the instance data. 
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @s imulink init
 */
bool init_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, Param_OrthOsc2_CtrlemC_s* par, Angle_abwmf_FB_CtrlemC* angle);



/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step1_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, float xAdiff, float xBdiff)
  {
#ifndef __ignoreInCheader_zbnf__
  float b;
  Param_OrthOsc2_CtrlemC_s* par = thiz->par;
  thiz->yab.re += par->fIa * ( thiz->kA * xAdiff - thiz->b_);
  b = thiz->b_;
  thiz->b_ += par->fIb * ( thiz->kB * xBdiff + thiz->yab.re);
  thiz->yab.im = (thiz->b_ + b) /2;
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step2_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, float xAdiff, float xBdiff)
  {
#ifndef __ignoreInCheader_zbnf__
  Param_OrthOsc2_CtrlemC_s* par = thiz->par;
  float a = thiz->yab.re;
  thiz->yab.re += par->fIoth * ( thiz->kA * xAdiff - thiz->yab.im) - par->fIown * thiz->yab.re;
  thiz->yab.im += par->fIoth * ( thiz->kB * xBdiff + a           ) - par->fIown * thiz->yab.im;
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output.. 
 * @s imulink Object-FB, accel-tlc, step-in.
 */
static inline void step_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  if(thiz == null) return;
  step1_OrthOsc2_CtrlemC(thiz, xAdiff, xBdiff);
  *yaz_y = thiz->yab.re;
  if(ab_y){  *ab_y = thiz->yab; } 
#endif//__ignoreInCheader_zbnf__
}



/**Prepares the instance data. 
 * The output bus from simulink will be allocated in simulink respectively in the generated code.
 * Use the pointer to the existing output data, that are the instance data.
 * @param identObj any indetification number. For debug.
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @param thizh_y thiz as pointer.
 * @s imulink init
 */
bool init_NoAngle_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, Param_OrthOsc2_CtrlemC_s* par);

/**
 * @s imulink Object-FB, accel-tlc, step-in.
 */
static inline void stepNoAngle_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
{ 
#ifndef __ignoreInCheader_zbnf__  
  if(thiz == null) return;
  float b;
  Param_OrthOsc2_CtrlemC_s* par = thiz->par;
 	*yaz_y = thiz->yab.re += par->fIa * ( thiz->kA * xAdiff - thiz->b_);
	b = thiz->b_; 
  thiz->b_ += par->fIb * ( thiz->kB * xBdiff + thiz->yab.re);
  thiz->yab.im = (thiz->b_ + b) /2;
  if(ab_y){  *ab_y = thiz->yab; } 
#endif//__ignoreInCheader_zbnf__
}




//#define free_Param_OrthOsc2_CtrlemC()

//#define free_OrthOsc2_CtrlemC()



/**
 * @xxxsimulink Operation-FB, accel-tlc
 */
static inline void thizo_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, int32 dummyRun, OrthOsc2_CtrlemC_s* thiz_ybus)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  *thiz_ybus = *thiz;
#endif//__ignoreInCheader_zbnf__
}


/**Outputs the ab vector of this.
 * @s imulink Operation-FB, accel-tlc
 */
static inline void ab_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, float run, float_complex* ab_y)
{ 
  ab_y->re = thiz->yab.re;
  ab_y->im = thiz->yab.im;
}






/**
 * @s imulink Operation-FB, accel-tlc
 */
static inline void calcMagn_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, float step, float* m_y)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  float dm1 = thiz->par->fm * ((thiz->yab.re * thiz->yab.re) + (thiz->yab.im * thiz->yab.im) - (thiz->m * thiz->m));
  if(dm1 <=1.0 && dm1 >= -1.0) {
    //it is okay.
  } else if(dm1 < 10000000000.0) {
    dm1 = fminf(fmaxf(dm1, -1.0f), 1.0f);
  } else {
    //it is nan. Prevent problems. clear all.
    thiz->yab.re = thiz->yab.im = thiz->m = thiz->mr = dm1 = 0;
  }
  *m_y = thiz->m += dm1;
#endif//__ignoreInCheader_zbnf__
}


/**
 * @s imulink Operation-FB, accel-tlc
 */
static inline void calcpq_OrthOsc2_CtrlemC(OrthOsc2_CtrlemC_s* thiz, float step, float_complex* ypq_y)
{ 
  if(thiz == null || thiz->anglep == null) return;
  mult_complex_FB(thiz->yab, thiz->anglep->anb, thiz->ypq);
  *ypq_y = thiz->ypq;  //offer result to extra output.
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class OrthOsc2_CtrlemC : public OrthOsc2_CtrlemC_s {

  public: 
  
  OrthOsc2_CtrlemC(float kA, float kB, int32 identObj, float Tstep);

  /**Connect the association to par and angle.
   */
  bool init(Param_OrthOsc2_CtrlemC* par, Angle_abwmf_FB_CtrlemC* angle) {
    return init_OrthOsc2_CtrlemC(this, par, angle);
  }

  /**Connect the association only to par, angle remain null, then calcpq is not supported.
   */
  bool init(Param_OrthOsc2_CtrlemC* par) {
    return init_NoAngle_OrthOsc2_CtrlemC(this, par); 
  }

  void step(float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y) {
    step_OrthOsc2_CtrlemC(this, xAdiff, xBdiff, yaz_y, ab_y);
  }

  void step(float xAdiff, float xBdiff) {
    step2_OrthOsc2_CtrlemC(this, xAdiff, xBdiff);
  }



  void calcpq(float_complex* ypq_y) {
    calcpq_OrthOsc2_CtrlemC(this, 0.0f, ypq_y);
  }
};
#endif //__cplusplus



/**Parameter set for int16 Orthogonal oscillator
 * @simulink no-bus
 */
typedef struct Param_OrthOsc16_CtrlemC_T
{
  ObjectJc obj;

  /**Frquency and step time. */
  float tStepOrthi;

  /**The given frequency in step routine. Only for debug. 0.0 if nStepPeriod is given. */
  float fq;

  /**The given steps per period in step routine. Only for debug. 0.0 if fq is given. */
  float nStepsPeriod;

  /**Nominal value for magnitude.*/
  float nom_m;

  /**Integrator values form same signal, from other.*/
  uint16 fIcos, fIsin;

  /**Factors for magnitude and reciproce. */ 
  float fm, fmr;


} Param_OrthOsc16_CtrlemC_s;


#ifndef ID_refl_Param_OrthOsc16_CtrlemC
  #define ID_refl_Param_OrthOsc16_CtrlemC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Param_OrthOsc16_CtrlemC;
#endif




/**Initializes the Param_OrtOsc2_FB
 * @param Tstep
 * @simulink ctor
 */
void ctor_Param_OrthOsc16_CtrlemC(Param_OrthOsc16_CtrlemC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m);



/**
 * @s imulink Object-FB
 */
static inline void setPeriod_Param_OrthOsc16_CtrlemC(Param_OrthOsc16_CtrlemC_s* thiz, float nStepsPeriod)
{ 
#ifndef __ignoreInCheader_zbnf__
  float fI1 = 2*PI_float_emC / nStepsPeriod;
  float fIcos = cosf(fI1);
  //float fIcorr = (fIcos +3) /4;
  //float fIcorr2 = (fIcos +11) /12;
  //thiz->fq = 1.0f/ (thiz->tStepOrthi * nStepsPeriod);
  thiz->nStepsPeriod = nStepsPeriod;
  //thiz->fIa = fI1 * fIcorr2 / fIcorr;
  //thiz->fIb = fI1 * fIcorr2 * fIcorr;
#endif//__ignoreInCheader_zbnf__
}


/**
 * @simulink Object-FB
 */
static inline void setFq_Param_OrthOsc16_CtrlemC(Param_OrthOsc16_CtrlemC_s* thiz, float fq)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  float fI1 = 2*PI_float_emC * thiz->tStepOrthi * fq;  //rad of 1 Tstep
  //this value should be so exact as possible for feedback, sum of gain = 1.0, 
  float fIcos = cosf(fI1);       //hence using float. cos16_emC is inaccurate.
  float fIsin = sinf(fI1);
  thiz->fIsin = (uint16)(65536 * fIsin);
  thiz->fIcos = (uint16)(65536 * (1.0f - fIcos));
#endif//__ignoreInCheader_zbnf__

}


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Param_OrthOsc16_CtrlemC : public Param_OrthOsc16_CtrlemC_s {
  friend class OrthOsc16_CtrlemC;
  public: 
  
  Param_OrthOsc16_CtrlemC(int32 identObj, float Tstep, float tStepOrthi, float nom_m);

  void setPeriod(float nStepsPeriod) { setPeriod_Param_OrthOsc16_CtrlemC(this, nStepsPeriod); }
  void setFq(float fq) { setFq_Param_OrthOsc16_CtrlemC(this, fq); }

};
#endif //__cplusplus



/**Internal data of a OrthogonalOscillator.
 * @simulink no-bus 
 */
typedef struct OrthOsc16_CtrlemC_T
{
  ObjectJc obj;  //:The base structure
  Param_OrthOsc16_CtrlemC_s* par;  //:Reference to parameter, maybe calculated in other step time.
  Angle_abgmf16_CtrlemC* anglep;   //:Reference to angle, null is admissable.

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  int16 kA, kB;

  int16_complex yab;    //:Orthogonal components of oscillation. 
  //int16 m, mr;        //:optional: Magnitude and its reciproke, if calculated
  //
  int16 b_;           //:internal b component

  int16 __spare;   //:for 8 Byte align
} OrthOsc16_CtrlemC_s;


#ifndef ID_refl_OrthOsc16_CtrlemC
  #define ID_refl_OrthOsc16_CtrlemC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_OrthOsc16_CtrlemC;
#endif


/**@simulink ctor
 */
OrthOsc16_CtrlemC_s* ctor_OrthOsc16_CtrlemC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep);


/**Prepares the instance data. 
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @simulink init
 */
bool init_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, Param_OrthOsc16_CtrlemC_s* par, Angle_abgmf16_CtrlemC* angle);



/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step1_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, int16 xAdiff, int16 xBdiff)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthOsc16_CtrlemC_s* par = thiz->par;
  int16 a1 = (int16)( ( (((thiz->kA * (int32)(xAdiff))>>12) - thiz->yab.im ) * par->fIsin ) >>16);
  int16 a2 = thiz->yab.re - (int16)((((int32)((thiz->yab.re ))) * par->fIcos) >>16); 
  int16 a = a1 + a2;
  int16 b1 = (int16)( ( ( ( (thiz->kB * (int32)(xBdiff)) >>12) + thiz->yab.re ) * par->fIsin ) >>16);
  int16 b2 = thiz->yab.im - (int16)((((int32)((thiz->yab.im ))) * par->fIcos) >>16);
  int16 b = b1 + b2;
  thiz->yab.re = a;         
  thiz->yab.im = b;         
#endif//__ignoreInCheader_zbnf__
}



/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step2_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, int16 xAdiff, int16 xBdiff)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthOsc16_CtrlemC_s* par = thiz->par;
  int32 ad; 
  muls16_emC(ad, thiz->kA, xAdiff);  //input diff * kA
  ad = (ad >>12) - thiz->yab.im;     // - other comp (im)
  muls16_emC(ad, (int16)(ad & 0xffff), par->fIsin);  //increment of own comp (re) from adiff and im
  muls16add32_emC(ad, thiz->yab.re, -par->fIcos);    //sub the little bit for stability
  int16 a = thiz->yab.re;
  thiz->yab.re += (int16)((ad>>16) & 0xffff);
  //
  int32 bd; 
  muls16_emC(bd, thiz->kB, xBdiff);  //input diff * kA
  bd = (bd >>12) + a;     // - other comp (im)
  muls16_emC(bd, (int16)(bd & 0xffff), par->fIsin);  //increment of own comp (re) from adiff and im
  muls16add32_emC(bd, thiz->yab.im, -par->fIcos);    //sub the little bit for stability
  thiz->yab.im += (int16)((bd>>16) & 0xffff);
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output..
 * @simulink Object-FB, accel-tlc, step-in.
 */
static inline void step_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, int16 xAdiff, int16 xBdiff, int16* yaz_y, int16_complex* ab_y)
  {
#ifndef __ignoreInCheader_zbnf__
  if(thiz == null) return;
  int16 a = thiz->yab.re;
  step1_OrthOsc16_CtrlemC(thiz, xAdiff, xBdiff);
  if(ab_y){  *ab_y = thiz->yab; } 
  *yaz_y = a;
#endif//__ignoreInCheader_zbnf__
}



/**Prepares the instance data. 
 * The output bus from simulink will be allocated in simulink respectively in the generated code.
 * Use the pointer to the existing output data, that are the instance data.
 * @param identObj any indetification number. For debug.
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @param thizh_y thiz as pointer.
 * @s imulink init
 */
bool init_NoAngle_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, Param_OrthOsc16_CtrlemC_s* par);

/**
 * @s imulink Object-FB, accel-tlc, step-in.
 */
static inline void stepNoAngle_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
{ 
#ifndef __ignoreInCheader_zbnf__  
#endif//__ignoreInCheader_zbnf__
}




//#define free_Param_OrthOsc16_CtrlemC()

//#define free_OrthOsc16_CtrlemC()



/**
 * @xxxsimulink Operation-FB, accel-tlc
 */
static inline void thizo_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, int32 dummyRun, OrthOsc16_CtrlemC_s* thiz_ybus)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  *thiz_ybus = *thiz;
#endif//__ignoreInCheader_zbnf__
}


/**Outputs the ab vector of this.
 * @s imulink Operation-FB, accel-tlc
 */
static inline void ab_OrthOsc16_CtrlemC(OrthOsc16_CtrlemC_s* thiz, float run, float_complex* ab_y)
{ 
  ab_y->re = thiz->yab.re;
  ab_y->im = thiz->yab.im;
}











#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class OrthOsc16_CtrlemC : public OrthOsc16_CtrlemC_s {

  public: 
  
  OrthOsc16_CtrlemC(float kA, float kB, int32 identObj, float Tstep);

  /**Connect the association to par and angle.
   */
  bool init(Param_OrthOsc16_CtrlemC* par, Angle_abgmf16_CtrlemC* angle) {
    return init_OrthOsc16_CtrlemC(this, par, angle);
  }

  /**Connect the association only to par, angle remain null, then calcpq is not supported.
   */
  bool init(Param_OrthOsc16_CtrlemC* par) {
    return init_NoAngle_OrthOsc16_CtrlemC(this, par); 
  }

  void step(int16 xAdiff, int16 xBdiff, int16* yaz_y, int16_complex* ab_y) {
    step_OrthOsc16_CtrlemC(this, xAdiff, xBdiff, yaz_y, ab_y);
  }



  void step(int16 xAdiff, int16 xBdiff) {
    step2_OrthOsc16_CtrlemC(this, xAdiff, xBdiff);
  }



};
#endif //__cplusplus


//=====================Orth32

/**Parameter set for int32 Orthogonal oscillator
 * @simulink no-bus
 */
typedef struct Param_OrthOsc32_CtrlemC_T
{
  ObjectJc obj;

  /**Frquency and step time. */
  float tStepOrthi;

  /**The given frequency in step routine. Only for debug. 0.0 if nStepPeriod is given. */
  float fq;

  /**The given steps per period in step routine. Only for debug. 0.0 if fq is given. */
  float nStepsPeriod;

  /**Nominal value for magnitude.*/
  float nom_m;

  /**Integrator values form same signal, from other.*/
  int32 fIcos, fIsin;

  /**Factors for magnitude and reciproce. */ 
  float fm, fmr;


} Param_OrthOsc32_CtrlemC_s;


#ifndef ID_refl_Param_OrthOsc32_CtrlemC
  #define ID_refl_Param_OrthOsc32_CtrlemC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Param_OrthOsc32_CtrlemC;
#endif




/**Initializes the Param_OrtOsc2_FB
 * @param Tstep
 * @simulink ctor
 */
void ctor_Param_OrthOsc32_CtrlemC(Param_OrthOsc32_CtrlemC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m);



/**
 * @s imulink Object-FB
 */
static inline void setPeriod_Param_OrthOsc32_CtrlemC(Param_OrthOsc32_CtrlemC_s* thiz, float nStepsPeriod)
{ 
#ifndef __ignoreInCheader_zbnf__
  float fI1 = 2*PI_float_emC / nStepsPeriod;
  //this value should be so exact as possible for feedback, sum of gain = 1.0,
  float fIcos = cosf(fI1);       //hence using float. cos16_emC is inaccurate.
  float fIsin = sinf(fI1);
  thiz->fIsin = (int32)(65536.0f * 65536 * fIsin);
  thiz->fIcos = (int32)(-65536.0f * 65536 * (1.0f - fIcos));
  //float fIcorr = (fIcos +3) /4;
  //float fIcorr2 = (fIcos +11) /12;
  //thiz->fq = 1.0f/ (thiz->tStepOrthi * nStepsPeriod);
  thiz->nStepsPeriod = nStepsPeriod;
  //thiz->fIa = fI1 * fIcorr2 / fIcorr;
  //thiz->fIb = fI1 * fIcorr2 * fIcorr;
#endif//__ignoreInCheader_zbnf__
}


/**
 * @simulink Object-FB
 */
static inline void setFq_Param_OrthOsc32_CtrlemC(Param_OrthOsc32_CtrlemC_s* thiz, float fq)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  thiz->fq = fq;
  float fI1 = 2*PI_float_emC * thiz->tStepOrthi * fq;  //rad of 1 Tstep
  //this value should be so exact as possible for feedback, sum of gain = 1.0, 
  float fIcos = cosf(fI1);       //hence using float. cos16_emC is inaccurate.
  float fIsin = sinf(fI1);
  thiz->fIsin = (int32)(65536.0f * 65536 * fIsin);
  thiz->fIcos = (int32)(-65536.0f * 65536 * (1.0f - fIcos));
#endif//__ignoreInCheader_zbnf__

}


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Param_OrthOsc32_CtrlemC : public Param_OrthOsc32_CtrlemC_s {
  friend class OrthOsc16_CtrlemC;
  public: 
  
  Param_OrthOsc32_CtrlemC(int32 identObj, float Tstep, float tStepOrthi, float nom_m);

  void setPeriod(float nStepsPeriod) { setPeriod_Param_OrthOsc32_CtrlemC(this, nStepsPeriod); }
  void setFq(float fq) { setFq_Param_OrthOsc32_CtrlemC(this, fq); }

};
#endif //__cplusplus



/**Internal data of a OrthogonalOscillator.
 * @simulink no-bus 
 */
typedef struct OrthOsc32_CtrlemC_T
{
  ObjectJc obj;  //:The base structure
  Param_OrthOsc32_CtrlemC_s* par;  //:Reference to parameter, maybe calculated in other step time.
  Angle_abgmf16_CtrlemC* anglep;   //:Reference to angle, null is admissable.

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  int16 kA, kB;

  int32_complex yab;    //:Orthogonal components of oscillation. 

} OrthOsc32_CtrlemC_s;


#ifndef ID_refl_OrthOsc32_CtrlemC
  #define ID_refl_OrthOsc32_CtrlemC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_OrthOsc32_CtrlemC;
#endif


/**@simulink ctor
 */
OrthOsc32_CtrlemC_s* ctor_OrthOsc32_CtrlemC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep);


/**Prepares the instance data. 
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @simulink init
 */
bool init_OrthOsc32_CtrlemC(OrthOsc32_CtrlemC_s* thiz, Param_OrthOsc32_CtrlemC_s* par, Angle_abgmf16_CtrlemC* angle);






/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step2_OrthOsc32_CtrlemC(OrthOsc32_CtrlemC_s* thiz, int16 xAdiff, int16 xBdiff)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthOsc32_CtrlemC_s* par = thiz->par;
  int32 ad; 
  muls16_emC(ad, thiz->kA, xAdiff);    // input diff * kA
  ad = (ad <<4) - thiz->yab.im;        // - other comp (im)
  //muls32hi_emC(ad, ad, par->fIsin);    // increment of own comp (re) from adiff and im
  { union II64 { int64 r64; struct II32 { int32 lo; uint32 hi; } r32;} R64;
    R64.r64 = ((int64)(int32)(ad) * (int64)(int32)(par->fIsin));
    ad = R64.r32.hi;
  }

  muls32addhi_emC(ad, thiz->yab.re, (par->fIcos));    //sub the little bit for stability
  int32 a = thiz->yab.re;              //note: fIcos is negative, hence sub
  thiz->yab.re += ad;                  // integrate first comp, re
  //
  int32 bd; 
  muls16_emC(bd, thiz->kB, xBdiff);    // input diff * kA
  bd = (bd <<4) + a;                   // - other comp (im)
  muls32hi_emC(bd, bd, par->fIsin);    // increment of own comp (re) from adiff and im
  muls32addhi_emC(bd, thiz->yab.im, (par->fIcos));    //sub the little bit for stability
  thiz->yab.im += bd;                  //note: fIcos is negative, hence sub
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output..
 * @simulink Object-FB, accel-tlc, step-in.
 */
static inline void step_OrthOsc32_CtrlemC(OrthOsc32_CtrlemC_s* thiz, int16 xAdiff, int16 xBdiff, int16* yaz_y, int16_complex* ab_y)
  {
#ifndef __ignoreInCheader_zbnf__
  if(thiz == null) return;
  int16 a = (int16)(thiz->yab.re>>16);
  step2_OrthOsc32_CtrlemC(thiz, xAdiff, xBdiff);
  if(ab_y){  ab_y->re = (int16)(thiz->yab.re>>16); ab_y->im = (int16)(thiz->yab.im>>16); } 
  *yaz_y = a;
#endif//__ignoreInCheader_zbnf__
}



/**Prepares the instance data. 
 * The output bus from simulink will be allocated in simulink respectively in the generated code.
 * Use the pointer to the existing output data, that are the instance data.
 * @param identObj any indetification number. For debug.
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @param thizh_y thiz as pointer.
 * @s imulink init
 */
bool init_NoAngle_OrthOsc32_CtrlemC(OrthOsc32_CtrlemC_s* thiz, Param_OrthOsc32_CtrlemC_s* par);

/**
 * @s imulink Object-FB, accel-tlc, step-in.
 */
static inline void stepNoAngle_OrthOsc32_CtrlemC(OrthOsc32_CtrlemC_s* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
{ 
#ifndef __ignoreInCheader_zbnf__  
#endif//__ignoreInCheader_zbnf__
}




//#define free_Param_OrthOsc32_CtrlemC()

//#define free_OrthOsc32_CtrlemC()



/**
 * @xxxsimulink Operation-FB, accel-tlc
 */
static inline void thizo_OrthOsc32_CtrlemC(OrthOsc32_CtrlemC_s* thiz, int32 dummyRun, OrthOsc32_CtrlemC_s* thiz_ybus)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  *thiz_ybus = *thiz;
#endif//__ignoreInCheader_zbnf__
}


/**Outputs the ab vector of this.
 * @s imulink Operation-FB, accel-tlc
 */
static inline void ab_OrthOsc32_CtrlemC(OrthOsc32_CtrlemC_s* thiz, float run, int16_complex* ab_y)
{ 
  ab_y->re = (int16)(thiz->yab.re>>16);
  ab_y->im = (int16)(thiz->yab.im>>16);
}











#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class OrthOsc32_CtrlemC : public OrthOsc32_CtrlemC_s {

  public: 
  
  OrthOsc32_CtrlemC(float kA, float kB, int32 identObj, float Tstep);

  /**Connect the association to par and angle.
   */
  bool init(Param_OrthOsc32_CtrlemC* par, Angle_abgmf16_CtrlemC* angle) {
    return init_OrthOsc32_CtrlemC(this, par, angle);
  }

  /**Connect the association only to par, angle remain null, then calcpq is not supported.
   */
  bool init(Param_OrthOsc32_CtrlemC* par) {
    return init_NoAngle_OrthOsc32_CtrlemC(this, par); 
  }

  void step(int16 xAdiff, int16 xBdiff, int16* yaz_y, int16_complex* ab_y) {
    step_OrthOsc32_CtrlemC(this, xAdiff, xBdiff, yaz_y, ab_y);
  }



  void step(int16 xAdiff, int16 xBdiff) {
    step2_OrthOsc32_CtrlemC(this, xAdiff, xBdiff);
  }



};
#endif //__cplusplus




//================

typedef struct Adjustk_OrthOsc2_CtrlemC_T
{
  ObjectJc base;

  float max_e;

  float fdeday;

  float kHi, kNormal;

} Adjustk_OrthOsc2_CtrlemC_s;

#ifndef ID_refl_Adjustk_OrthOsc2_CtrlemC
  #define ID_refl_Adjustk_OrthOsc2_CtrlemC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Adjustk_OrthOsc2_CtrlemC;
#endif



/**Checks the error between x Input and y of the Orthogonal Oscillators.
 * If the error is >= max_e, it sets the kA, kB of the Orthogonal oscillator to the kHi values.
 * Then it smoothes down.
 * @s imulink ctor.
 */ 
void ctor_Adjustk_OrthOsc2_CtrlemC(Adjustk_OrthOsc2_CtrlemC_s* thiz, int32 identObj, float max_e, float kHi, float kNormal, float Tstep, float Tdecay);


/**Checks the error between x Input and y of the Orthogonal Oscillators.
 * If the error is >= max_e, it sets the kA, kB of the Orthogonal oscillator to the kHi values.
 * Then it smoothes down.
 * @s imulink Object-FB.
 */ 
static inline void step_Adjustk_OrthOsc2_CtrlemC(Adjustk_OrthOsc2_CtrlemC_s* thiz, OrthOsc2_CtrlemC_s* orth, float e)
{ if(orth == null) return; //especially first step
  if(fabsf(e) >= thiz->max_e) {
    orth->kA = thiz->kHi; orth->kB = -thiz->kHi;
  } else if(orth->kA > thiz->kNormal) {
    orth->kA += thiz->fdeday * (0.99f * thiz->kNormal - orth->kA);  //T1 smoothing
    orth->kB = - orth->kA;
  } else if(orth->kA < thiz->kNormal) {
    orth->kA = thiz->kNormal; orth->kB = -thiz->kNormal;
  }
}



#endif //__OrthOsc_FB_h
