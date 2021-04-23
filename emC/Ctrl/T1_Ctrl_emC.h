#ifndef HGUARD_emC_Ctrl_T1ish_Ctrl_emC
#define HGUARD_emC_Ctrl_T1ish_Ctrl_emC

#include <applstdef_emC.h>
#include <emC/Base/Math_emC.h>
#include <emC/Base/Endianness_emC.h>

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


static inline float step_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz, float x) {
  thiz->dx = (thiz->fTs * ( x - thiz->q));  //
  thiz->q += thiz->dx;
  return thiz->q;
}



#endif //HGUARD_emC_Ctrl_T1ish_Ctrl_emC
