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

  /**Frequency and step time. */
  float tStepOrthi;

  /**The given frequency in step routine. Only for debug. 0.0 if nStepPeriod is given. */
  float fq;

  /**The given steps per period in step routine. Only for debug. 0.0 if fq is given. */
  float nStepsPeriod;

  /**Factor for magnitued regards the nominal value.
   * It is 1/m_nom/2.
   */
  float fm;


  /**Integrator factor from the other component.*/
  float fI_oth;

  /**Adjust for the own component in one step time. Less, ~ 0.00... */
  float fI_own;

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
static inline void setFq_Param_OrthBandpassF_Ctrl_emC ( Param_OrthBandpassF_Ctrl_emC_s* thiz
                                                      , float fq)
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



/**Internal data of a Orthogonal Bandpass.
 * @simulink no-bus 
 */
typedef struct OrthBandpassF_Ctrl_emC_T
{
  ObjectJc obj;  //:The base structure
  Param_OrthBandpassF_Ctrl_emC_s* par;  //:Reference to parameter, maybe calculated in other step time.

  /**Input coupling factors. Note: kB should be negative for same difference B-X, A-X*/
  float kA, kB;

  /**Stored values on step for evaluation. */
  float xadiff;

  float m;        //:optional: Magnitude and its reciproke, if calculated

  float_complex yab;  //:Orthogonal components of oscillation. 


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
 * @simulink init.
 */
bool init_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, Param_OrthBandpassF_Ctrl_emC_s* par);






/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yab.re Signal
 * @param xBdiff 0 for only single input, or orthogonal difference from the other component
 */
static inline void step_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, float xAdiff, float xBdiff)
  {
#ifndef __ignoreInCheader_zbnf__
  Param_OrthBandpassF_Ctrl_emC_s* par = thiz->par;
  thiz->xadiff = xAdiff; //store for evaluating (phase) and debug view
  float a = thiz->yab.re;
  thiz->yab.re -= par->fI_own * thiz->yab.re;
  thiz->yab.re += par->fI_oth * ( thiz->kA * xAdiff - thiz->yab.im);
  thiz->yab.im -= par->fI_own * thiz->yab.im;
  thiz->yab.im += par->fI_oth * ( thiz->kB * xBdiff + a); 
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. for simulink S-Function with outputs. 
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output.. 
 * @simulink Object-FB, accel-tlc.
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
 * @simulink Operation-FB, accel-tlc
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




/**Calculates the magnitude in an iteration algorithm. 
 * Each step time is one iteration. 
 * The input values are usual not far changed from one to the next step time.  
 * @simulink Operation-FB, accel-tlc.
 */
static inline void calcMagn_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, float* m_y)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  //firstly calculate a estimation for the magnitude.
  //The real value is between this and 1.0 of the sum. It means it has an error from max. -30%
  //but this value is lesser than the real magnitude.
  float fm = thiz->par->fm;
  float mx = (fabsf(thiz->yab.re) + fabsf(thiz->yab.im)) * 0.707f;
  float dmx = mx - thiz->m; 
  if( (thiz->m * fm ) > 1.5f || fabsf(dmx) > thiz->m) {  //the difference is high in comparison to the magnitude,
    //then do not iterate. It may be infinite.
    thiz->m = mx;    //use the estimation. 
  } 
  else {   //the difference is < 0.5 * magnitude, then it is possible to iterate:
    //divide by 2 is the nearest approximation for change, it regards the fact
    //the derivation of sqrt is 1/2*x. Adding the derivation. 
    float m2 = (thiz->m * thiz->m);
    float ab2 = ((thiz->yab.re * thiz->yab.re) + (thiz->yab.im * thiz->yab.im));
    float dm = fm * (ab2 - m2);
    thiz->m += dm;   
  }
  *m_y = thiz->m;
#endif//__ignoreInCheader_zbnf__
}


/**
 * @simulink Operation-FB, accel-tlc.
 */
static inline void calcdq_OrthBandpassF_Ctrl_emC(OrthBandpassF_Ctrl_emC_s* thiz, Angle_abwmf_FB_Ctrl_emC* anglep, float_complex* ydq_y)
{ 
  if(thiz == null || anglep == null) return;
  mult_complex_FB(thiz->yab, anglep->anb, *ydq_y);
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class OrthBandpassF_Ctrl_emC : public OrthBandpassF_Ctrl_emC_s {

  public: 
  
  OrthBandpassF_Ctrl_emC(float kA, float kB, int32 identObj, float Tstep);

  /**Connect the association only to par, angle remain null, then calcdq is not supported.
   */
  bool init(Param_OrthBandpassF_Ctrl_emC* par) {
    return init_OrthBandpassF_Ctrl_emC(this, par); 
  }

  void step(float xAdiff, float xBdiff) {
    step_OrthBandpassF_Ctrl_emC(this, xAdiff, xBdiff);
  }



  void calcdq(float_complex* ydq_y, Angle_abwmf_FB_Ctrl_emC* anglep) {
    calcdq_OrthBandpassF_Ctrl_emC(this, anglep, ydq_y);
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

  /**The given steps per period in step routine. Only for debug.  */
  float nStepsPeriod;

  /**Integrator values form same signal, from other.*/
  uint16 fI_own, fI_oth;


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
void ctor_Param_OrthBandpass16_Ctrl_emC(Param_OrthBandpass16_Ctrl_emC_s* thiz, int32 identObj, float Tstep, float tStepOrthi);



/**
 * @simulink Object-FB
 */
static inline void setPeriod_Param_OrthBandpass16_Ctrl_emC(Param_OrthBandpass16_Ctrl_emC_s* thiz, float nStepsPeriod)
{ 
#ifndef __ignoreInCheader_zbnf__
  float fI1 = 2*PI_float_emC / nStepsPeriod;
  float fI_own = cosf(fI1);
  //float fIcorr = (fI_own +3) /4;
  //float fIcorr2 = (fI_own +11) /12;
  //thiz->fq = 1.0f/ (thiz->tStepOrthi * nStepsPeriod);
  thiz->nStepsPeriod = nStepsPeriod;
  //thiz->fIa = fI1 * fIcorr2 / fIcorr;
  //thiz->fIb = fI1 * fIcorr2 * fIcorr;
#endif//__ignoreInCheader_zbnf__
}


/**
 * @simulink Object-FB
 */
static inline void setFq_Param_OrthBandpass16_Ctrl_emC(Param_OrthBandpass16_Ctrl_emC_s* thiz, float fq)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  thiz->nStepsPeriod = 1.0f / (fq * thiz->tStepOrthi); 
  float fI1 = 2*PI_float_emC * thiz->tStepOrthi * fq;  //rad of 1 Tstep
  //this value should be so exact as possible for feedback, sum of gain = 1.0, 
  float fI_own = cosf(fI1);       //hence using float. cos16_emC is inaccurate.
  float fI_oth = sinf(fI1);
  thiz->fI_oth = (uint16)(65536 * fI_oth);
  thiz->fI_own = (uint16)(-65536 * (1.0f - fI_own));  //Note: negative because subtract
#endif//__ignoreInCheader_zbnf__
}


#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Param_OrthBandpass16_Ctrl_emC : public Param_OrthBandpass16_Ctrl_emC_s {
  friend class OrthBandpass16_Ctrl_emC;
  public: 
  
  Param_OrthBandpass16_Ctrl_emC(int32 identObj, float Tstep, float tStepOrthi);

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

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  int16 kA, kB;

  int32_complex yab;    //:Orthogonal components of oscillation. 
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
 * @simulink init.
 */
bool init_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, Param_OrthBandpass16_Ctrl_emC_s* par);


/**Sets the influence of input. 
 * @param kA kB
 * @simulink Operation-FB.
 */
extern_C void setkAB_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, float kA, float kB);






/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, int16 xAdiff, int16 xBdiff)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthBandpass16_Ctrl_emC_s* par = thiz->par;
  int32 ad; 
  muls16_emC(ad, thiz->kA, xAdiff);  //input diff * kA
  ad = (ad >>12) - ((thiz->yab.im>>16)&0xffff);     // - other comp (im)
  muls16_emC(ad, (int16)(ad & 0xffff), par->fI_oth);  //increment of own comp (re) from adiff and im
  muls16add32_emC(ad, ((thiz->yab.re>>16) & 0xffff), par->fI_own);    //sub the little bit for stability
  int16 a = ((thiz->yab.re>>16) & 0xffff);
  thiz->yab.re += ad; //(int16)((ad>>16) & 0xffff);
  //
  int32 bd; 
  muls16_emC(bd, thiz->kB, xBdiff);  //input diff * kA
  bd = (bd >>12) + a;     // - other comp (im)
  muls16_emC(bd, (int16)(bd & 0xffff), par->fI_oth);  //increment of own comp (re) from adiff and im
  muls16add32_emC(bd, ((thiz->yab.im>>16) & 0xffff), par->fI_own);    //sub the little bit for stability
  thiz->yab.im += bd; //(int16)((bd>>16) & 0xffff);
#endif//__ignoreInCheader_zbnf__
}


/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output..
 * @simulink Object-FB, accel-tlc.
 */
static inline void stepSmlk_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, int16 xAdiff, int16 xBdiff, int16* yaz_y, int16_complex* ab_y)
  {
#ifndef __ignoreInCheader_zbnf__
  if(thiz == null) return;
  //int16 a = thiz->yab.re;
  step_OrthBandpass16_Ctrl_emC(thiz, xAdiff, xBdiff);
  if(ab_y){  ab_y->re = (int16)((thiz->yab.re >>16) & 0xffff); ab_y->im = (int16)((thiz->yab.im >>16) & 0xffff); } 
  *yaz_y = (int16)((thiz->yab.re >>16) & 0xffff);
#endif//__ignoreInCheader_zbnf__
}



/**Outputs the ab vector of this.
 * @simulink Operation-FB, accel-tlc
 */
static inline void ab_OrthBandpass16_Ctrl_emC(OrthBandpass16_Ctrl_emC_s* thiz, float_complex* ab_y)
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
  bool init(Param_OrthBandpass16_Ctrl_emC* par) {
    return init_OrthBandpass16_Ctrl_emC(this, par);
  }

  void setkAB(float kA, float kB) { setkAB_OrthBandpass16_Ctrl_emC(this, kA, kB); }

  void step(int16 xAdiff, int16 xBdiff) {
    step_OrthBandpass16_Ctrl_emC(this, xAdiff, xBdiff);
  }




};
#endif //__cplusplus


//=====================Orth32

/**Parameter set for int32 Orthogonal band pass
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

  float _align8;

  /**Integrator values form same signal, from other.*/
  int32 fI_oth, fI_own;


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
void ctor_Param_OrthBandpass32_Ctrl_emC(Param_OrthBandpass32_Ctrl_emC_s* thiz, int32 identObj, float Tstep, float tStepOrthi);



/**
 * @simulink Object-FB
 */
static inline void setPeriod_Param_OrthBandpass32_Ctrl_emC(Param_OrthBandpass32_Ctrl_emC_s* thiz, float nStepsPeriod)
{ 
#ifndef __ignoreInCheader_zbnf__
  float fI1 = 2*PI_float_emC / nStepsPeriod;
  //this value should be so exact as possible for feedback, sum of gain = 1.0,
  float fI_own = cosf(fI1);       //hence using float. cos16_emC is inaccurate.
  float fI_oth = sinf(fI1);
  thiz->fI_oth = (int32)(65536.0f * 65536 * fI_oth);
  thiz->fI_own = (int32)(-65536.0f * 65536 * (1.0f - fI_own));
  //float fIcorr = (fI_own +3) /4;
  //float fIcorr2 = (fI_own +11) /12;
  //thiz->fq = 1.0f/ (thiz->tStepOrthi * nStepsPeriod);
  thiz->nStepsPeriod = nStepsPeriod;
  //thiz->fIa = fI1 * fIcorr2 / fIcorr;
  //thiz->fIb = fI1 * fIcorr2 * fIcorr;
#endif//__ignoreInCheader_zbnf__
}


/**
 * @simulink Object-FB
 */
extern_C void setFq_Param_OrthBandpass32_Ctrl_emC(Param_OrthBandpass32_Ctrl_emC_s* thiz, float fq);





#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Param_OrthBandpass32_Ctrl_emC : public Param_OrthBandpass32_Ctrl_emC_s {
  friend class OrthBandpass16_Ctrl_emC;
  public: 
  
  Param_OrthBandpass32_Ctrl_emC(int32 identObj, float Tstep, float tStepOrthi);

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
  //Angle_abgmf16_Ctrl_emC* anglep;   //:Reference to angle, null is admissable.

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  int32 kA, kB;

  /**Stored from input step_... for ph_ output. */
  int32 xAdiff;

  int32 m;

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
 * @simulink init
 */
bool init_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, Param_OrthBandpass32_Ctrl_emC_s* par);



/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 */
static inline void step_OrthBandpass32_Ctrl_emC ( OrthBandpass32_Ctrl_emC_s* thiz
                                                , int32 xAdiff, int32 xBdiff)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  Param_OrthBandpass32_Ctrl_emC_s* par = thiz->par;
  int32 ad; 
  thiz->xAdiff = xAdiff;
  muls32hi_emC(ad, thiz->kA, xAdiff);  //input diff * kA
  if(ad < 0x04000000 && ad > -0x04000000) { ad <<=5; }
  else ad = ad <0 ? 0x80000000 : 0x7fffffff;  //limit it if too large.
  ad -= thiz->yab.im;                   // - other comp (im)
  muls32hi_emC(ad, ad, par->fI_oth);    // increment of own comp (re) from adiff and im
  muls32addhi_emC(ad, thiz->yab.re, (par->fI_own));    //sub the little bit for stability
  int32 a = thiz->yab.re;              
  thiz->yab.re += ad; 
  //
  int32 bd; 
  muls32hi_emC(bd, thiz->kB, xBdiff);   // input diff * kB
  if(bd < 0x04000000 && bd > -0x04000000) { bd <<=5; }
  else bd = bd <0 ? 0x80000000 : 0x7fffffff;  //limit it if too large.
  bd += a;                              // + other comp (re)
  muls32hi_emC(bd, bd, par->fI_oth);    // increment of own comp (re) from adiff and im
  muls32addhi_emC(bd, thiz->yab.im, (par->fI_own));    //sub the little bit for stability
  thiz->yab.im += bd;                   
#endif//__ignoreInCheader_zbnf__
}



/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output..
 * @simulink Object-FB, accel-tlc.
 */
static inline void stepSmlk_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, int32 xAdiff, int32 xBdiff, int32_complex* ab_y)
  {
#ifndef __ignoreInCheader_zbnf__
  if(thiz == null) return;
  step_OrthBandpass32_Ctrl_emC(thiz, xAdiff, xBdiff);
  if(ab_y){  ab_y->re = thiz->yab.re; ab_y->im = thiz->yab.im; } 
#endif//__ignoreInCheader_zbnf__
}



/**Sets the influence of input. 
 * @param kA kB
 * @simulink Operation-FB.
 */
extern_C void setkAB_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, float kA, float kB);





/**Outputs the ab vector of this.
 * @simulink Operation-FB, accel-tlc
 */
static inline void ab_OrthBandpass32_Ctrl_emC(OrthBandpass32_Ctrl_emC_s* thiz, float run, int32_complex* ab_y)
{ 
  ab_y->re = thiz->yab.re;
  ab_y->im = thiz->yab.im;
}



/**Outputs a value for phase error
 * @simulink Operation-FB, accel-tlc
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
  bool init(Param_OrthBandpass32_Ctrl_emC* par) {
    return init_OrthBandpass32_Ctrl_emC(this, par);
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
