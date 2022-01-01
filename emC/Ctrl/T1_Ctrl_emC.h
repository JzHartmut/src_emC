#ifndef HGUARD_emC_Ctrl_T1ish_Ctrl_emC
#define HGUARD_emC_Ctrl_T1ish_Ctrl_emC

#include <emC/Base/Object_emC.h>
#include <emC/Base/Math_emC.h>
#include <emC/Base/Endianness_emC.h>
#include <math.h>







/*@CLASS_C T1i_Ctrl_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * T1-Functionality in 16-bit integer for x and y and 32-bit-integer for q.
 * It is optimized for 16-bit-fixpoint processors
 * but proper to use also for floating point environments.
 * */




typedef struct T1i_Ctrl_emC_T {

  /**This value is only stored while param call. It is not used. */
  float Ts;


  /**The difference q-x for usage as smoothed differentiator.
   * dxhi is the representative int16-part regarded to input.
   */
  Endianess32_16_emC_s dx;

  /**The output value and state variable.
   * qhi is the representative int16-part regarded to input.
   */
  Endianess32_16_emC_s q;


  /**Factor to multiply the difference (x-q) for one step.
   * This factor is calculated as 65536 * (1.0f - expf(-Tstep / Ts))
   * to expand the 16-bit-x-value to 32 bit for q.
   * A value Ts = 0, it means without smoothing, results in 0xffff because only 16 bits are available.
   * The largest Ts is 65000 * Tstep, results in 1 for this value.
   * Larger Ts does not work.
   */
  Endianess32_16_emC_s fTs;

} T1i_Ctrl_emC_s;


/**Constructor for the T1i FBlock.
 * @simulink ctor.
 */
extern_C T1i_Ctrl_emC_s* ctor_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz);

/**Initialization for the T1i FBlock.
 * @param Ts_param smoothing time in units of Tstep, secons.
 * @param Tstep step time for this FBlock.
 * @simulink init
 */
extern_C bool param_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, float Ts_param, float Tstep);

/**Step routine for the T1 FBlock for 16 bit interger smoothing. */
static int16 step_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x);

static inline int16 step_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x) {
  thiz->dx.v32 = (uint32)(thiz->fTs.v16.hi) * ( x - thiz->q.v16.hi);  //
  thiz->q.v32 += thiz->dx.v32;
  return thiz->q.v16.hi; //hi part 16 bit
}

static inline int16 step32_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x) {
  thiz->dx.v32 = (int32)(((uint64)(thiz->fTs.v32) * (uint64)( (int32)(x<<16) - thiz->q.v32))>>32);
  thiz->q.v32 += thiz->dx.v32;
  return thiz->q.v16.hi; //hi part 16 bit
}

/**Get dx after step calculation. step_T1i_Ctrl_emC(...) should be called before. */
static int16 dx_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x);

static inline int16 dx_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x) {
  return thiz->dx.v16.hi; 
}



/**Step routine wrapper for simulink for 16 bit T1 smoothing FBlock. 
 * @simulink Object-FB, no-thizInit, no-thizStep.
 */
static inline void stepY_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x, int16* y_y) {
  *y_y = step_T1i_Ctrl_emC(thiz, x);
}




#if defined(__cplusplus)

class T1i_Ctrl_emC : public T1i_Ctrl_emC_s {
  public: T1i_Ctrl_emC ( float Ts ) { ctor_T1i_Ctrl_emC(static_cast<T1i_Ctrl_emC_s*>(this)); }

  public: void param ( float Ts, float Tstep ) { param_T1i_Ctrl_emC(this, Ts, Tstep); }

  public: int step ( int x ) { return step_T1i_Ctrl_emC(this, x); }
};
#endif //__cplusplus




/*@CLASS_C T1i_Ctrl_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * T1-Functionality in 32-bit integer for x, y and q
 * with special shift operations to improve accurance.
 * It is optimized for 16- or 32-bit-fixpoint processors
 * but proper to use also for floating point environments.
 * */

typedef struct T1ish_Ctrl_emC_T {

  /**This value is only stored while param call. It is not used. */
  float Ts;

  /**The difference q-x for usage as smoothed differentiator.
   * It is regarded to the xBit range as 32 bit value.
   */
  int32 dx;

  /**The output value and state variable.
   * It is regarded to the xBit range as 32 bit value.
   */
  int32 q;
  
  /**Factor to multiply the difference (x-q) for one step.
   * This factor results of Tstep/Ts and the number of right shift of q nShq.
   * If Ts = 1000*Tstep, the groth factor is approximately 0.001,
   * but with 14 right shift operations, fTs is 2^14 * 0.001 => 16 as integer.
   * The number of shift operations are determined by fsBits.
   * For this example fsBits = 5, it means the fTs is in range 16..31.
   * It determines the granularity of adjustment of Ts.
   */
  int32 fTs;
  
  /**Number of left-shift bits for x before subtraction with q.*/
  int nShx;

  /**Number of right-shift bits for q before subtraction with q.
   * nShx + nShq + xBits should be ==32
   */
  int nShq;

  /**Number of right-shift bits from q to y.
   * nSh32y + yBits should be ==32
   */
  int nSh32y;

} T1ish_Ctrl_emC_s;


extern_C T1ish_Ctrl_emC_s* ctor_T1ish_Ctrl_emC(void* addr);

extern_C void param_T1ish_Ctrl_emC(T1ish_Ctrl_emC_s* thiz, float Ts, float Tstep, int fsBits, int xBits, int yBits);

static int step_T1ish_Ctrl_emC(T1ish_Ctrl_emC_s* thiz, int x);


static inline int step_T1ish_Ctrl_emC(T1ish_Ctrl_emC_s* thiz, int x) {
  thiz->dx = (thiz->fTs * ( (((int32)x) << thiz->nShx) - (thiz->q >> thiz->nShq)));  //
  thiz->q += thiz->dx;
  return (int)(thiz->q >> thiz->nSh32y);
}




typedef struct T1f_Ctrl_emC_T {

  float Ts;

  float dx;
  float q;

  float fTs;


} T1f_Ctrl_emC_s;


extern_C T1f_Ctrl_emC_s* ctor_T1f_Ctrl_emC(void* addr);

extern_C void param_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz, float Ts_param, float Tstep);

static float step_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz, float x);

static float get_dx_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz);


//tag::step_T1f_Ctrl_emC[]
static inline float step_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz, float x) {
  thiz->dx = (thiz->fTs * ( x - thiz->q));  //
  thiz->q += thiz->dx;
  return thiz->q;
}


static inline float get_dx_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz) {
  return thiz->dx;  //regard step is executed before!
}
//end::step_T1f_Ctrl_emC[]


typedef struct T2f_Ctrl_emC_T {

  float Ts1, Ts2;

  float dx;
  float q1, y;

  float fTs1, fTs2;


} T2f_Ctrl_emC_s;


extern_C T2f_Ctrl_emC_s* ctor_T2f_Ctrl_emC(void* addr);

extern_C void param_T2f_Ctrl_emC(T2f_Ctrl_emC_s* thiz, float Ts1_param, float Ts2_param, float Tstep);

static float step_T2f_Ctrl_emC(T2f_Ctrl_emC_s* thiz, float x);

static float get_dx_T2f_Ctrl_emC(T2f_Ctrl_emC_s* thiz);

//tag::step_T2f_Ctrl_emC[]
static inline float step_T2f_Ctrl_emC(T2f_Ctrl_emC_s* thiz, float x) {
  float dx1 = (thiz->fTs1 * ( x - thiz->q1));  //
  thiz->q1 += dx1;
  thiz->dx = (thiz->fTs2 * ( thiz->q1 - thiz->y));  //
  thiz->y += thiz->dx;
  return thiz->y;
}


static inline float get_dx_T2f_Ctrl_emC(T2f_Ctrl_emC_s* thiz) {
  return thiz->dx;  //regard step is executed before!
}
//end::step_T2f_Ctrl_emC[]




//==========================================================================================
//  Delayf_Ctrl_emC

//tag::Delayf_Ctrl_emC[]
/**Data for simple delay of a float value. 
 * It should be used to built a differential of a signal using a greater distance.
 * This is the same as built a differential between two averaged values.
 * 
 */
typedef struct Delayf_Ctrl_emC_T {
  union { ObjectJc obj; } base;
  
  /**Currently wrapping index, after step it refers to the new given value.*/
  int ix;
  
  /**Number of stored float values in values[]. */
  int nsize;

  /**This is the array to store values. The array is continued after the structure data
   * by offering a greater memory area is defined here. This is checked in the constructor.
   */
  float values[2];

} Delayf_Ctrl_emC_s;


#define INIZ_Delayf_Ctrl_emC(THIZ, ID) { { INIZ_ObjectJc(THIZ, refl_Delayf_Ctrl_emC, ID)}, 0} 


/**Constructor for Delayf_Ctrl_emC.
 * It presumes initialized memory of the ObjectJc base struct, see also the C++ constructor 
 * and the INIZ_Delayf_Ctrl_emC(...) macro for static intialization. 
 * To get dynamic memory for C-only data you can also use ALLOC_ObjectJc(...).
 * @param size Number of elements in the delay-array, max. possible delay.
 * @param sizeMem The size of the associated data structure which is referred by othiz. 
 *        It is tested and should match to the size parameter. 
 */
INLINE_emC Delayf_Ctrl_emC_s* ctor_Delayf_Ctrl_emC ( ObjectJc* othiz, int size, int sizeMem ) {
#ifndef __ignoreInCheader_zbnf__
  ASSERT_emC(sizeMem >= (size-2) * sizeof(float) + sizeof(Delayf_Ctrl_emC_s), "faulty size on Delayf_Ctrl_emC", size, sizeMem); 
  Delayf_Ctrl_emC_s* thiz = C_CAST(Delayf_Ctrl_emC_s*, othiz);
  thiz->nsize = size;
  return thiz;
#endif//__ignoreInCheader_zbnf__
}



//tag::step_Delayf_Ctrl_emC[]
/**Get the delayed value of a input in the past, put the new value for delay.
 * This routine should only be called one time per step time. 
 * @param delay number of step times to the past for the output
 * @param x the new input 
 * @return the value from past due to delay. 
 */
INLINE_emC float step_Delayf_Ctrl_emC ( Delayf_Ctrl_emC_s* thiz, int delay, float x ) {
#ifndef __ignoreInCheader_zbnf__
  ASSERT_emC(delay >0 && delay < thiz->nsize, "faulty delay value", delay, thiz->nsize);
  int ixold = thiz->ix - delay + 1;
  if(ixold <0) { ixold += thiz->nsize; }
  float val = thiz->values[ixold];
  int ixnew = thiz->ix +1;
  if(ixnew >= thiz->nsize) { ixnew = 0; }  // wrap arround 0
  thiz->ix = ixnew;
  thiz->values[ixnew] = x;
  return val;
#endif//__ignoreInCheader_zbnf__
}
//end::step_Delayf_Ctrl_emC[]
//end::Delayf_Ctrl_emC[]


//==========================================================================================
//  Delayi_Ctrl_emC

//tag::Delayi_Ctrl_emC[]
typedef struct Delayi_Ctrl_emC_T {
  union { ObjectJc obj; } base;
  int ix;
  int nsize;

  int values[2];

} Delayi_Ctrl_emC_s;


#define INIZ_Delayi_Ctrl_emC(THIZ, ID) { { INIZ_ObjectJc(THIZ, refl_Delayi_Ctrl_emC, ID)}, 0} 



INLINE_emC Delayi_Ctrl_emC_s* ctor_Delayi_Ctrl_emC ( ObjectJc* othiz, int size, int sizeMem ) {
#ifndef __ignoreInCheader_zbnf__
  ASSERT_emC(sizeMem >= (size-2) * sizeof(int) + sizeof(Delayi_Ctrl_emC_s), "faulty size on Delayi_Ctrl_emC", size, sizeMem); 
  Delayi_Ctrl_emC_s* thiz = C_CAST(Delayi_Ctrl_emC_s*, othiz);
  thiz->nsize = size;
  return thiz;
#endif//__ignoreInCheader_zbnf__
}



//tag::step_Delayi_Ctrl_emC[]
INLINE_emC int step_Delayi_Ctrl_emC ( Delayi_Ctrl_emC_s* thiz, int delay, int x ) {
#ifndef __ignoreInCheader_zbnf__
  ASSERT_emC(delay >0 && delay < thiz->nsize, "faulty delay value", delay, thiz->nsize);
  int ixold = thiz->ix - delay + 1;
  if(ixold <0) { ixold += thiz->nsize; }
  int val = thiz->values[ixold];
  int ixnew = thiz->ix +1;
  if(ixnew >= thiz->nsize) { ixnew = 0; }  // wrap arround 0
  thiz->ix = ixnew;
  thiz->values[ixnew] = x;
  return val;
#endif//__ignoreInCheader_zbnf__
}
//end::step_Delayi_Ctrl_emC[]
//end::Delayi_Ctrl_emC[]



//tag::SmoothGainf_Ctrl_emC[]
typedef struct SmoothGainf_Ctrl_emC_T {
  union { ObjectJc obj; } base;
  float gq;
  float fTslow, fTshigh;

  /**Value for test. If the x value is lesser, than the gain is smoothed to the lower gain. 
   * If one time the value is greater, the higher gain is used immediately. 
   */
  float xmin;
} SmoothGainf_Ctrl_emC_s;

#define INIZ_SmoothGainf_Ctrl_emC(THIZ, ID) { { INIZ_ObjectJc(THIZ, refl_SmoothGainf_Ctrl_emC, ID)}, 0} 


extern_C SmoothGainf_Ctrl_emC_s* ctor_SmoothGainf_Ctrl_emC ( ObjectJc* othiz, float Tslow, float Tshigh, float Tstep );



INLINE_emC void param_SmoothGainf_Ctrl_emC ( SmoothGainf_Ctrl_emC_s* thiz, float Tslow, float Tshigh, float Tstep ) {
  thiz->fTslow = Tslow < Tstep ? 1.0f: Tstep / Tslow;
  thiz->fTshigh = Tshigh < Tstep ? 1.0f: Tstep / Tshigh;
}

//tag::step_SmoothGainf_Ctrl_emC[]
INLINE_emC float step_SmoothGainf_Ctrl_emC ( SmoothGainf_Ctrl_emC_s* thiz, float x, float gainhigh, float gainlow, float minx ) {
  if (fabsf(x) < minx) {
    thiz->gq += thiz->fTslow * (gainlow - thiz->gq);      // smooth it down to gainlow
  }
  else {
    thiz->gq += thiz->fTshigh * (gainhigh - thiz->gq);      // smooth it down to gainlow
  }
  return x * thiz->gq;
}
//end::step_SmoothGainf_Ctrl_emC[]
//end::SmoothGainf_Ctrl_emC[]

#endif //HGUARD_emC_Ctrl_T1ish_Ctrl_emC
