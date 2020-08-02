#ifndef __OrthOsc_FB_h
#define __OrthOsc_FB_h

#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <emC/Ctrl/Angle_Ctrl_emC.h>
#include <math.h>


extern bool isInit_global_;


/*CLASS_C OrthOsc2_FB_CtrlemC *************************************************************************************************************/

/**
 * @simulink bus
 */
typedef struct Param_OrthOsc2_FB_t
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

  /**Factors for magnitude and reciproce. */ 
  float fm, fmr;


} Param_OrthOsc2_FB;


#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Param_OrthOsc2_FB;
#endif




/**Initializes the Param_OrtOsc2_FB
 * @param Tstep
 * @simulink ctor
 */
void ctor_Param_OrthOsc2_FB(Param_OrthOsc2_FB* thiz, int32 identObj, float Tstep, float tStepOrthi, float nom_m);



/**
 * @simulink Object-FB
 */
inline void setPeriod_Param_OrthOsc2_FB(Param_OrthOsc2_FB* thiz, float nStepsPeriod)
{ 
#ifndef __ignoreInCheader_zbnf__
  float fI1 = 2*kPI_Angle_FB / nStepsPeriod;
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
 * @simulink Object-FB
 */
inline void setFq_Param_OrthOsc2_FB(Param_OrthOsc2_FB* thiz, float fq)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  float fI1 = 2*kPI_Angle_FB * thiz->tStepOrthi * fq;
  float fIcos = cosf(fI1);
  float fIcorr = (fIcos +3) /4;
  float fIcorr2 = (fIcos +11) /12;
  thiz->fq = fq;
  thiz->fIa = fI1 * fIcorr2 / fIcorr;
  thiz->fIb = fI1 * fIcorr2 * fIcorr;
#endif//__ignoreInCheader_zbnf__

}







/**Internal data of a OrthogonalOscillator.
 * @simulink no-bus 
 */
typedef struct OrthOsc2_FB_t
{
  ObjectJc obj;  //:The base structure
  Param_OrthOsc2_FB* par;  //:Reference to parameter, maybe calculated in other step time.
  Angle_abwmf_FB_CtrlemC* anglep;  //:Reference to angle, null is admissable.

  /**Couple factors. Note: kB should be negative for same difference B-X, A-X*/
  float kA, kB;

  float_complex yab;  //:Orthogonal components of oscillation. 
  float_complex ypq;  //:optional: Orthogonal components as fundamental values, after park-transformation with angle.
  float m, mr;        //:optional: Magnitude and its reciproke, if calculated
  //
  float b_;           //:internal b component

  int32 __spare;   //:for 8 Byte align
} OrthOsc2_FB_CtrlemC;


#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_OrthOsc2_FB_CtrlemC;
#endif


/**@simulink ctor
 */
OrthOsc2_FB_CtrlemC* ctor_OrthOsc2_FB(ObjectJc* othiz, float kA, float kB, int32 identObj, float Tstep);


/**Prepares the instance data. 
 * @param par aggregation to the parameter.
 * @param angle aggregation to instance which contains the angle of the signal.
 * @simulink init
 */
bool init_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, Param_OrthOsc2_FB* par, Angle_abwmf_FB_CtrlemC* angle);



/**Step routine. It calulates the stored values of Orthogonal Oscillation.
 * @param xAdiff Difference between Input and yaz_y Signal
 * @param xBdiff same as xAdiff for only single input, or orthogonal difference
 * @param yaz_y variable to store the a-Output.
 * @param ab_Y variable to store the complex orthogonal output.. 
 * @simulink Object-FB, accel-tlc, step-in.
 */
inline void step_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
  { 
#ifndef __ignoreInCheader_zbnf__ 
  if(thiz == null) return;
  float b;
  Param_OrthOsc2_FB* par = thiz->par;
 	*yaz_y = thiz->yab.re += par->fIa * ( thiz->kA * xAdiff - thiz->b_);
	b = thiz->b_; 
  thiz->b_ += par->fIb * ( thiz->kB * xBdiff + thiz->yab.re);
  thiz->yab.im = (thiz->b_ + b) /2;
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
 * @simulink init
 */
bool init_NoAngle_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, Param_OrthOsc2_FB* par);

/**
 * @simulink Object-FB, accel-tlc, step-in.
 */
inline void stepNoAngle_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, float xAdiff, float xBdiff, float* yaz_y, float_complex* ab_y)
{ 
#ifndef __ignoreInCheader_zbnf__  
  if(thiz == null) return;
  float b;
  Param_OrthOsc2_FB* par = thiz->par;
 	*yaz_y = thiz->yab.re += par->fIa * ( thiz->kA * xAdiff - thiz->b_);
	b = thiz->b_; 
  thiz->b_ += par->fIb * ( thiz->kB * xBdiff + thiz->yab.re);
  thiz->yab.im = (thiz->b_ + b) /2;
  if(ab_y){  *ab_y = thiz->yab; } 
#endif//__ignoreInCheader_zbnf__
}




//#define free_Param_OrthOsc2_FB()

//#define free_OrthOsc2_FB()



/**
 * @xxxsimulink Operation-FB, accel-tlc
 */
inline void thizo_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, int32 dummyRun, OrthOsc2_FB_CtrlemC* thiz_ybus)
{ 
#ifndef __ignoreInCheader_zbnf__ 
  *thiz_ybus = *thiz;
#endif//__ignoreInCheader_zbnf__
}


/**Outputs the ab vector of this.
 * @simulink Operation-FB, accel-tlc
 */
inline void ab_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, float run, float_complex* ab_y)
{ 
  ab_y->re = thiz->yab.re;
  ab_y->im = thiz->yab.im;
}






/**
 * @simulink Operation-FB, accel-tlc
 */
inline void calcMagn_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, float step, float* m_y)
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
 * @simulink Operation-FB, accel-tlc
 */
inline void calcpq_OrthOsc2_FB(OrthOsc2_FB_CtrlemC* thiz, float step, float_complex* ypq_y)
{ 
  if(thiz == null || thiz->anglep == null) return;
  mult_complex_FB(thiz->yab, thiz->anglep->anb, thiz->ypq);
  *ypq_y = thiz->ypq;  //offer result to extra output.
}





typedef struct Adjustk_OrthOsc2_FB_t
{
  ObjectJc base;

  float max_e;

  float fdeday;

  float kHi, kNormal;

} Adjustk_OrthOsc2_FB;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Adjustk_OrthOsc2_FB;
#endif



/**Checks the error between x Input and y of the Orthogonal Oscillators.
 * If the error is >= max_e, it sets the kA, kB of the Orthogonal oscillator to the kHi values.
 * Then it smoothes down.
 * @simulink ctor.
 */ 
void ctor_Adjustk_OrthOsc2_FB(Adjustk_OrthOsc2_FB* thiz, int32 identObj, float max_e, float kHi, float kNormal, float Tstep, float Tdecay);


/**Checks the error between x Input and y of the Orthogonal Oscillators.
 * If the error is >= max_e, it sets the kA, kB of the Orthogonal oscillator to the kHi values.
 * Then it smoothes down.
 * @simulink Object-FB.
 */ 
inline void step_Adjustk_OrthOsc2_FB(Adjustk_OrthOsc2_FB* thiz, OrthOsc2_FB_CtrlemC* orth, float e)
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
