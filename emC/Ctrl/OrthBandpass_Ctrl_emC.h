#ifndef __OrthBandpass_FB_h
#define __OrthBandpass_FB_h

#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <emC/Base/Math_emC.h>
#include <emC/Ctrl/Angle_Ctrl_emC.h>
#include <math.h>


extern bool isInit_global_;


/*CLASS_C OrthBandpassF_Ctrl_emC_s *************************************************************************************************************/

/**
 */
typedef struct Param_OrthBandpassF_Ctrl_emC_T
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
  //float fIa, fIb;

  /**Integrator factor from the other component.*/
  float fI_oth;

  /**Integrator factor (1.0f - factor from same component). This factor is ~ 0.00..., subtract from own compn. */
  float fI_own;

  /**Factors for magnitude and reciproce. */ 
  float fm, fmr;


} Param_OrthBandpassF_Ctrl_emC_s;

#ifndef ID_refl_Param_OrthBandpassF_Ctrl_emC
  #define ID_refl_Param_OrthBandpassF_Ctrl_emC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Param_OrthBandpassF_Ctrl_emC;
#endif




/**Initializes the Param_OrtOsc2_FB
 * @param Tstep
 * @simulink ctor.
 */
void ctor_Param_OrthBandpassF_Ctrl_emC(Param_OrthBandpassF_Ctrl_emC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m);



/**
 * @simulink Object-FB.
 */
static inline void setPeriod_Param_OrthBandpassF_Ctrl_emC(Param_OrthBandpassF_Ctrl_emC_s* thiz, float nStepsPeriod)
{ 
#ifndef __ignoreInCheader_zbnf__
  float fI1 = 2*PI_float_emC / nStepsPeriod;
  thiz->fq = 1.0f / (nStepsPeriod * thiz->tStepOrthi);
  thiz->fI_own = 1.0f - cosf(fI1); //the little rest to subtract
  thiz->fI_oth = sinf(fI1);    //forward gain from other compn, determines fq
  thiz->nStepsPeriod = nStepsPeriod;
#endif//__ignoreInCheader_zbnf__
}


/**
 * @simulink Object-FB.
 */
static inline void setFq_Param_OrthBandpassF_Ctrl_emC(Param_OrthBandpassF_Ctrl_emC_s* thiz, float fq)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  float fI1 = 2*PI_float_emC * thiz->tStepOrthi * fq;
  thiz->fI_own = 1.0f - cosf(fI1); //the little rest to subtract
  thiz->fI_oth = sinf(fI1);    //forward gain from other compn, determines fq
  thiz->fq = fq;
  thiz->nStepsPeriod = 1.0f / (fq * thiz->tStepOrthi); 
#endif//__ignoreInCheader_zbnf__

}


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Param_OrthBandpassF_Ctrl_emC : private Param_OrthBandpassF_Ctrl_emC_s {
  friend class OrthBandpassF_Ctrl_emC;
  public: 
  
  Param_OrthBandpassF_Ctrl_emC(int32 identObj, float Tstep, float tStepOrthi, float nom_m);

  void setPeriod(float nStepsPeriod) { setPeriod_Param_OrthBandpassF_Ctrl_emC(this, nStepsPeriod); }
  void setFq(float fq) { setFq_Param_OrthBandpassF_Ctrl_emC(this, fq); }

};
#endif //__cplusplus



/**Internal data of a OrthogonalOscillator.
 * @simulink no-bus 
 */
typedef struct OrthBandpassF_Ctrl_emC_T
{
  ObjectJc obj;  //:The base structure
  Param_OrthBandpassF_Ctrl_emC_s* par;  //:Reference to parameter, maybe calculated in other step time.
  Angle_abwmf_FB_Ctrl_emC* anglep;  //:Reference to angle, null is admissable.

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  float kA, kB;

  /**Stored values on step for evaluation. */
  float xadiff, xbdiff;

  float_complex yab;  //:Orthogonal components of oscillation. 
  float_complex ypq;  //:optional: Orthogonal components as fundamental values, after park-transformation with angle.
  float m, mr;        //:optional: Magnitude and its reciproke, if calculated
  //
  float b_;           //:internal b component

  int32 __spare;   //:for 8 Byte align
} OrthBandpassF_Ctrl_emC_s;


#ifndef ID_refl_OrthBandpassF_Ctrl_emC
  #define ID_refl_OrthBandpassF_Ctrl_emC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_OrthBandpassF_Ctrl_emC;
#endif


/**
 * @simulink ctor
 */
OrthBandpassF_Ctrl_emC_s* ctor_OrthBandpassF_Ctrl_emC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep);


/**Prepares the instance data. 
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @simulink init
 */
bool initSmlk_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, Param_OrthBandpassF_Ctrl_emC_s* par, Angle_abwmf_FB_Ctrl_emC* angle);


bool init_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, Param_OrthBandpassF_Ctrl_emC_s* par, Angle_abwmf_FB_Ctrl_emC* angle);

/**Prepares the instance data. 
 * @param par aggregation to the parameter.
 */
bool init_NoAngle_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, Param_OrthBandpassF_Ctrl_emC_s* par);





/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, float xAdiff, float xBdiff)
  {
#ifndef __ignoreInCheader_zbnf__
  Param_OrthBandpassF_Ctrl_emC_s* par = thiz->par;
  thiz->xadiff = xAdiff; thiz->xbdiff = xBdiff;    //store for evaluating (phase) and debug view
  float a = thiz->yab.re;
  thiz->yab.re += par->fI_oth * ( thiz->kA * xAdiff - thiz->yab.im) - par->fI_own * thiz->yab.re;
  thiz->yab.im += par->fI_oth * ( thiz->kB * xBdiff + a           ) - par->fI_own * thiz->yab.im;
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. for simulink S-Function with outputs. 
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output.. 
 * @simulink Object-FB, accel-tlc, step-in.
 */
static inline void stepSmlk_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  if(thiz == null) return;
  step_OrthBandpassF_Ctrl_emC(thiz, xAdiff, xBdiff);
  *yaz_y = thiz->yab.re;
  *ab_y = thiz->yab; 
#endif//__ignoreInCheader_zbnf__
}






//#define free_Param_OrthBandpassF_Ctrl_emC()

//#define free_OrthBandpassF_Ctrl_emC()

/**Sets the factors for input coupling.
 * This may be necessary in special situations, for example after changing inputs. 
 * @param kA Factor of influence of xadiff to the a component. 1.0 means approximately 1 period for switch on.
 * @param kB Same for the b component. 0.1 means approximately 10 period for switch on.
 * @simulink Operation-FB.
 */ 
static inline void setkAB_OrthBandpassF_Ctrl_emC ( OrthBandpassF_Ctrl_emC_s* thiz, float kA, float kB)
{
  thiz->kA = kA;
  thiz->kB = kB;
}


/**Sets the values of filter. 
 * This may be necessary in special situations, for example after changing inputs. 
 * @param set true only then set.
 * @param a the a component
 * @param b the a component
 * 
 * @simulink Operation-FB.
 */ 
static inline void set_OrthBandpassF_Ctrl_emC ( OrthBandpassF_Ctrl_emC_s* thiz, bool set, float a, float b)
{
  if(set) {
    thiz->yab.re = a;
    thiz->yab.im = b;
  }
}



/**Outputs the current ab vector of this.
 * @s imulink Operation-FB, accel-tlc
 */
static inline void ab_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, float run, float_complex* ab_y)
{ 
  ab_y->re = thiz->yab.re;
  ab_y->im = thiz->yab.im;
}



/**Outputs a value for phase error
 * @simulink Operation-FB, accel-tlc
 */
static inline void phase_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, float* ph_y)
{ 
  *ph_y = thiz->yab.im >=0 ? thiz->xadiff : - thiz->xadiff;
}




/**
 * @simulink Operation-FB, accel-tlc, step-in.
 */
static inline void calcMagn_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, float* m_y)
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
 * @simulink Operation-FB, accel-tlc, step-in.
 */
static inline void calcpq_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, float_complex* ypq_y)
{ 
  if(thiz == null || thiz->anglep == null) return;
  mult_complex_FB(thiz->yab, thiz->anglep->anb, thiz->ypq);
  *ypq_y = thiz->ypq;  //offer result to extra output.
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class OrthBandpassF_Ctrl_emC : public OrthBandpassF_Ctrl_emC_s {

  public: 
  
  OrthBandpassF_Ctrl_emC(float kA, float kB, int32 identObj, float Tstep);

  /**Connect the association to par and angle.
   */
  bool init(Param_OrthBandpassF_Ctrl_emC* par, Angle_abwmf_FB_Ctrl_emC* angle) {
    return init_OrthBandpassF_Ctrl_emC(this, par, angle);
  }

  /**Connect the association only to par, angle remain null, then calcpq is not supported.
   */
  bool init(Param_OrthBandpassF_Ctrl_emC* par) {
    return init_NoAngle_OrthBandpassF_Ctrl_emC(this, par); 
  }

  void step(float xAdiff, float xBdiff) {
    step_OrthBandpassF_Ctrl_emC(this, xAdiff, xBdiff);
  }



  void calcpq(float_complex* ypq_y) {
    calcpq_OrthBandpassF_Ctrl_emC(this, ypq_y);
  }
};
#endif //__cplusplus



/**Parameter set for int16 Orthogonal oscillator
 * @simulink no-bus
 */
typedef struct Param_OrthBandpass16_Ctrl_emC_T
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


} Param_OrthBandpass16_Ctrl_emC_s;


#ifndef ID_refl_Param_OrthBandpass16_Ctrl_emC
  #define ID_refl_Param_OrthBandpass16_Ctrl_emC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Param_OrthBandpass16_Ctrl_emC;
#endif




/**Initializes the Param_OrtOsc2_FB
 * @param Tstep
 * @simulink ctor
 */
void ctor_Param_OrthBandpass16_Ctrl_emC(Param_OrthBandpass16_Ctrl_emC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m);



/**
 * @s imulink Object-FB
 */
static inline void setPeriod_Param_OrthBandpass16_Ctrl_emC(Param_OrthBandpass16_Ctrl_emC_s* thiz, float nStepsPeriod)
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
 * @s imulink Object-FB
 */
static inline void setFq_Param_OrthBandpass16_Ctrl_emC(Param_OrthBandpass16_Ctrl_emC_s* thiz, float fq)
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
class Param_OrthBandpass16_Ctrl_emC : public Param_OrthBandpass16_Ctrl_emC_s {
  friend class OrthBandpass16_Ctrl_emC;
  public: 
  
  Param_OrthBandpass16_Ctrl_emC(int32 identObj, float Tstep, float tStepOrthi, float nom_m);

  void setPeriod(float nStepsPeriod) { setPeriod_Param_OrthBandpass16_Ctrl_emC(this, nStepsPeriod); }
  void setFq(float fq) { setFq_Param_OrthBandpass16_Ctrl_emC(this, fq); }

};
#endif //__cplusplus



/**Internal data of a OrthogonalOscillator.
 * @simulink no-bus 
 */
typedef struct OrthBandpass16_Ctrl_emC_T
{
  ObjectJc obj;  //:The base structure
  Param_OrthBandpass16_Ctrl_emC_s* par;  //:Reference to parameter, maybe calculated in other step time.
  Angle_abgmf16_Ctrl_emC* anglep;   //:Reference to angle, null is admissable.

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  int16 kA, kB;

  int32_complex yab;    //:Orthogonal components of oscillation. 
  //int16 m, mr;        //:optional: Magnitude and its reciproke, if calculated
  //
  //int16 b_;           //:internal b component

  //int16 __spare;   //:for 8 Byte align
} OrthBandpass16_Ctrl_emC_s;


#ifndef ID_refl_OrthBandpass16_Ctrl_emC
  #define ID_refl_OrthBandpass16_Ctrl_emC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_OrthBandpass16_Ctrl_emC;
#endif


/**@simulink ctor
 */
OrthBandpass16_Ctrl_emC_s* ctor_OrthBandpass16_Ctrl_emC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep);


/**Prepares the instance data. 
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @simulink init
 */
bool init_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, Param_OrthBandpass16_Ctrl_emC_s* par, Angle_abgmf16_Ctrl_emC* angle);


/**Sets the influence of input. 
 * @param kA kB
 * @s imulink Operation-FB.
 */
extern_C void setkAB_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, float kA, float kB);



/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step1_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, int16 xAdiff, int16 xBdiff)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthBandpass16_Ctrl_emC_s* par = thiz->par;
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
static inline void step2_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, int16 xAdiff, int16 xBdiff)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthBandpass16_Ctrl_emC_s* par = thiz->par;
  int32 ad; 
  muls16_emC(ad, thiz->kA, xAdiff);  //input diff * kA
  ad = (ad >>12) - ((thiz->yab.im>>16)&0xffff);     // - other comp (im)
  muls16_emC(ad, (int16)(ad & 0xffff), par->fIsin);  //increment of own comp (re) from adiff and im
  muls16add32_emC(ad, ((thiz->yab.re>>16) & 0xffff), -par->fIcos);    //sub the little bit for stability
  int16 a = ((thiz->yab.re>>16) & 0xffff);
  thiz->yab.re += ad; //(int16)((ad>>16) & 0xffff);
  //
  int32 bd; 
  muls16_emC(bd, thiz->kB, xBdiff);  //input diff * kA
  bd = (bd >>12) + a;     // - other comp (im)
  muls16_emC(bd, (int16)(bd & 0xffff), par->fIsin);  //increment of own comp (re) from adiff and im
  muls16add32_emC(bd, ((thiz->yab.im>>16) & 0xffff), -par->fIcos);    //sub the little bit for stability
  thiz->yab.im += bd; //(int16)((bd>>16) & 0xffff);
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output..
 * @s imulink Object-FB, accel-tlc, step-in.
 */
static inline void step_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, int16 xAdiff, int16 xBdiff, int16* yaz_y, int16_complex* ab_y)
  {
#ifndef __ignoreInCheader_zbnf__
  if(thiz == null) return;
  //int16 a = thiz->yab.re;
  step2_OrthBandpass16_Ctrl_emC(thiz, xAdiff, xBdiff);
  if(ab_y){  ab_y->re = (int16)((thiz->yab.re >>16) & 0xffff); ab_y->im = (int16)((thiz->yab.im >>16) & 0xffff); } 
  *yaz_y = (int16)((thiz->yab.re >>16) & 0xffff);
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
bool init_NoAngle_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, Param_OrthBandpass16_Ctrl_emC_s* par);

/**
 * @s imulink Object-FB, accel-tlc, step-in.
 */
static inline void stepNoAngle_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
{ 
#ifndef __ignoreInCheader_zbnf__  
#endif//__ignoreInCheader_zbnf__
}


/**Outputs the ab vector of this.
 * @s imulink Operation-FB, accel-tlc
 */
static inline void ab_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, float run, float_complex* ab_y)
{ 
  ab_y->re = (int16)((thiz->yab.re >>16) & 0xffff);
  ab_y->im = (int16)((thiz->yab.im >>16) & 0xffff);
}











#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class OrthBandpass16_Ctrl_emC : public OrthBandpass16_Ctrl_emC_s {

  public: 
  
  OrthBandpass16_Ctrl_emC(float kA, float kB, int32 identObj, float Tstep);

  /**Connect the association to par and angle.
   */
  bool init(Param_OrthBandpass16_Ctrl_emC* par, Angle_abgmf16_Ctrl_emC* angle) {
    return init_OrthBandpass16_Ctrl_emC(this, par, angle);
  }

  /**Connect the association only to par, angle remain null, then calcpq is not supported.
   */
  bool init(Param_OrthBandpass16_Ctrl_emC* par) {
    return init_NoAngle_OrthBandpass16_Ctrl_emC(this, par); 
  }

  void setkAB(float kA, float kB) { setkAB_OrthBandpass16_Ctrl_emC(this, kA, kB); }

  void step(int16 xAdiff, int16 xBdiff, int16* yaz_y, int16_complex* ab_y) {
    step_OrthBandpass16_Ctrl_emC(this, xAdiff, xBdiff, yaz_y, ab_y);
  }



  void step(int16 xAdiff, int16 xBdiff) {
    step2_OrthBandpass16_Ctrl_emC(this, xAdiff, xBdiff);
  }



};
#endif //__cplusplus


//=====================Orth32

/**Parameter set for int32 Orthogonal oscillator
 * @simulink no-bus
 */
typedef struct Param_OrthBandpass32_Ctrl_emC_T
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


} Param_OrthBandpass32_Ctrl_emC_s;


#ifndef ID_refl_Param_OrthBandpass32_Ctrl_emC
  #define ID_refl_Param_OrthBandpass32_Ctrl_emC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Param_OrthBandpass32_Ctrl_emC;
#endif




/**Initializes the Param_OrtOsc2_FB
 * @param Tstep
 * @simulink ctor
 */
void ctor_Param_OrthBandpass32_Ctrl_emC(Param_OrthBandpass32_Ctrl_emC_s* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m);



/**
 * @s imulink Object-FB
 */
static inline void setPeriod_Param_OrthBandpass32_Ctrl_emC(Param_OrthBandpass32_Ctrl_emC_s* thiz, float nStepsPeriod)
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
 * @s imulink Object-FB
 */
extern_C void setFq_Param_OrthBandpass32_Ctrl_emC(Param_OrthBandpass32_Ctrl_emC_s* thiz, float fq);





#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Param_OrthBandpass32_Ctrl_emC : public Param_OrthBandpass32_Ctrl_emC_s {
  friend class OrthBandpass16_Ctrl_emC;
  public: 
  
  Param_OrthBandpass32_Ctrl_emC(int32 identObj, float Tstep, float tStepOrthi, float nom_m);

  void setPeriod(float nStepsPeriod) { setPeriod_Param_OrthBandpass32_Ctrl_emC(this, nStepsPeriod); }
  void setFq(float fq) { setFq_Param_OrthBandpass32_Ctrl_emC(this, fq); }

};
#endif //__cplusplus



/**Internal data of a OrthogonalOscillator.
 * @simulink no-bus 
 */
typedef struct OrthBandpass32_Ctrl_emC_T
{
  ObjectJc obj;  //:The base structure
  Param_OrthBandpass32_Ctrl_emC_s* par;  //:Reference to parameter, maybe calculated in other step time.
  Angle_abgmf16_Ctrl_emC* anglep;   //:Reference to angle, null is admissable.

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  int32 kA, kB;

  /**Stored from input step_... for ph_ output. */
  int32 xAdiff, xBdiff;

  int32_complex yab;    //:Orthogonal components of oscillation. 

} OrthBandpass32_Ctrl_emC_s;


#ifndef ID_refl_OrthBandpass32_Ctrl_emC
  #define ID_refl_OrthBandpass32_Ctrl_emC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_OrthBandpass32_Ctrl_emC;
#endif


/**@simulink ctor
 */
OrthBandpass32_Ctrl_emC_s* ctor_OrthBandpass32_Ctrl_emC(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep);


/**Prepares the instance data. 
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @simulink init
 */
bool init_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, Param_OrthBandpass32_Ctrl_emC_s* par, Angle_abgmf16_Ctrl_emC* angle);


/**Sets the influence of input. 
 * @param kA kB
 * @s imulink Operation-FB.
 */
extern_C void setkAB_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, float kA, float kB);


#define sh4 0
#define sh4m 1

/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, int32 xAdiff, int32 xBdiff)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthBandpass32_Ctrl_emC_s* par = thiz->par;
  int32 ad; 
  thiz->xAdiff = xAdiff; thiz->xBdiff = xBdiff;
  muls32hi_emC(ad, thiz->kA, xAdiff);  //input diff * kA
  if(ad < 0x04000000 && ad > -0x04000000) { ad <<=5; }
  else ad = ad <0 ? 0x80000000 : 0x7fffffff;  //limit it if too large.
  ad -= thiz->yab.im;     // - other comp (im)
  muls32hi_emC(ad, ad, par->fIsin);    // increment of own comp (re) from adiff and im
  muls32addhi_emC(ad, thiz->yab.re, (par->fIcos));    //sub the little bit for stability
  int32 a = thiz->yab.re;              
  thiz->yab.re += (ad >>sh4); // + ((ad & 0x8) >>3);
  //
  int32 bd; 
  muls32hi_emC(bd, thiz->kB, xBdiff);    // input diff * kA
  if(bd < 0x04000000 && bd > -0x04000000) { bd <<=5; }
  else bd = bd <0 ? 0x80000000 : 0x7fffffff;  //limit it if too large.
  bd += a;                   // + other comp (re)
  muls32hi_emC(bd, bd, par->fIsin);    // increment of own comp (re) from adiff and im
  muls32addhi_emC(bd, thiz->yab.im, (par->fIcos));    //sub the little bit for stability
  thiz->yab.im += (bd >>sh4); // + ((bd & 0x8) >>3);                  //note: fIcos is negative, hence sub
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void XXXstep2_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, int32 xAdiff, int32 xBdiff)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthBandpass32_Ctrl_emC_s* par = thiz->par;
  int32 ad; 
  muls16_emC(ad, thiz->kA, xAdiff>>4);    // input diff * kA 
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
 * @s imulink Object-FB, accel-tlc, step-in.
 */
static inline void stepSim_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, int32 xAdiff, int32 xBdiff, int32_complex* ab_y)
  {
#ifndef __ignoreInCheader_zbnf__
  if(thiz == null) return;
  step_OrthBandpass32_Ctrl_emC(thiz, xAdiff, xBdiff);
  if(ab_y){  ab_y->re = thiz->yab.re; ab_y->im = thiz->yab.im; } 
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
bool init_NoAngle_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, Param_OrthBandpass32_Ctrl_emC_s* par);

/**
 * @s imulink Object-FB, accel-tlc, step-in.
 */
static inline void stepNoAngle_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
{ 
#ifndef __ignoreInCheader_zbnf__  
#endif//__ignoreInCheader_zbnf__
}




/**Outputs the ab vector of this.
 * @s imulink Operation-FB, accel-tlc
 */
static inline void ab_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, float run, int32_complex* ab_y)
{ 
  ab_y->re = thiz->yab.re;
  ab_y->im = thiz->yab.im;
}



/**Outputs a value for phase error
 * @s imulink Operation-FB, accel-tlc
 */
static inline void phase_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, int32* ph_y)
{ 
  *ph_y = thiz->yab.im >=0 ? thiz->xAdiff : - thiz->xAdiff;
}











#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class OrthBandpass32_Ctrl_emC : public OrthBandpass32_Ctrl_emC_s {

  public: 
  
  OrthBandpass32_Ctrl_emC(float kA, float kB, int32 identObj, float Tstep);

  /**Connect the association to par and angle.
   */
  bool init(Param_OrthBandpass32_Ctrl_emC* par, Angle_abgmf16_Ctrl_emC* angle) {
    return init_OrthBandpass32_Ctrl_emC(this, par, angle);
  }

  /**Connect the association only to par, angle remain null, then calcpq is not supported.
   */
  bool init(Param_OrthBandpass32_Ctrl_emC* par) {
    return init_NoAngle_OrthBandpass32_Ctrl_emC(this, par); 
  }


  void setkAB(float kA, float kB) { setkAB_OrthBandpass32_Ctrl_emC(this, kA, kB); }

  void step(int32 xAdiff, int32 xBdiff) {
    step_OrthBandpass32_Ctrl_emC(this, xAdiff, xBdiff);
  }



};
#endif //__cplusplus




//================

typedef struct Adjustk_OrthBandpassF_Ctrl_emC_T
{
  ObjectJc base;

  float max_e;

  float fdeday;

  float kHi, kNormal;

} Adjustk_OrthBandpassF_Ctrl_emC_s;

#ifndef ID_refl_Adjustk_OrthBandpassF_Ctrl_emC
  #define ID_refl_Adjustk_OrthBandpassF_Ctrl_emC 0
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Adjustk_OrthBandpassF_Ctrl_emC;
#endif



/**Checks the error between x Input and y of the Orthogonal Oscillators.
 * If the error is >= max_e, it sets the kA, kB of the Orthogonal oscillator to the kHi values.
 * Then it smoothes down.
 * @s imulink ctor.
 */ 
void ctor_Adjustk_OrthBandpassF_Ctrl_emC(Adjustk_OrthBandpassF_Ctrl_emC_s* thiz, int32 identObj, float max_e, float kHi, float kNormal, float Tstep, float Tdecay);


/**Checks the error between x Input and y of the Orthogonal Oscillators.
 * If the error is >= max_e, it sets the kA, kB of the Orthogonal oscillator to the kHi values.
 * Then it smoothes down.
 * @s imulink Object-FB.
 */ 
static inline void step_Adjustk_OrthBandpassF_Ctrl_emC(Adjustk_OrthBandpassF_Ctrl_emC_s* thiz, OrthBandpassF_Ctrl_emC_s* orth, float e)
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



#endif //__OrthBandpass_FB_h
