#ifndef HGUARD_emC_Ctrl_T1ish_Ctrl_emC
#define HGUARD_emC_Ctrl_T1ish_Ctrl_emC

#include <applstdef_emC.h>

/**It is the nominal value for 16 bit values. With it an overdrive of ~1.18 is possible.
 * 27720 = 2 * 2 * 2 * 3 * 3 * 5 * 7 * 11 ,
 *                         means divide by 2,3,5,6,7,8,9,10,11,12,14,15,16,18,20,22,24,27,28,30,32,33,35,36,40,42,44,45,50, 60,
 * (30240 =  32*5*7*3*3*3, means divide by 2,3,5,6,7,8,9,10,   12,14,15,16,18,20,   24,27,28,30,32,33,35,36,40,42 etc.
 */
#define NOM_i16_Ctrl_emC 27720


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
  union{ int32 dx32; struct { int16 dxlo, dxhi; } dx16;} dx;

  /**The output value and state variable.
   * qhi is the representative int16-part regarded to input.
   */
  union{ int32 q32; struct { int16 qlo, qhi; } q16;} q;


  /**Factor to multiply the difference (x-q) for one step.
   * This factor results of Tstep/Ts and the number of right shift of q nShq.
   * It is calculated as 65536 * Tstep/Ts for a 16 x 16 multiplication
   * to expand the 16-bit-x-value to 32 bit for q.
   * A value Ts = 0, it means without smoothing, results in 0xffff because only 16 bits are available.
   * The largest Ts is 65000 * Tstep, results in 1 for this value.
   * Larger Ts does not work.
   */
  uint16 fTs;

} T1i_Ctrl_emC_s;


extern_C T1i_Ctrl_emC_s* ctor_T1i_Ctrl_emC(void* addr);

extern_C void param_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, float Ts, float Tstep);

/**Step routine takes 16 bit */
static int16 step_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x);

/**Get dx after step calculation. step_T1i_Ctrl_emC(...) should be called before. */
static int16 dx_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x);


static inline int16 step_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x) {
  thiz->dx.dx32 = (uint32)(thiz->fTs) * ( x - thiz->q.q16.qhi);  //
  thiz->q.q32 += thiz->dx.dx32;
  return thiz->q.q16.qhi; //hi part 16 bit
}

static inline int16 dx_T1i_Ctrl_emC(T1i_Ctrl_emC_s* thiz, int16 x) {
  return thiz->dx.dx16.dxhi; 
}


#if defined(__cplusplus)

class T1i_Ctrl_emC : public T1i_Ctrl_emC_s {
  public: T1i_Ctrl_emC() { ctor_T1i_Ctrl_emC(static_cast<T1i_Ctrl_emC_s*>(this)); }

  public: void param ( float Ts, float Tstep) { param_T1i_Ctrl_emC(this, Ts, Tstep); }

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

extern_C void param_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz, float Ts, float Tstep);

static float step_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz, float x);


static inline float step_T1f_Ctrl_emC(T1f_Ctrl_emC_s* thiz, float x) {
  thiz->dx = (thiz->fTs * ( x - thiz->q));  //
  thiz->q += thiz->dx;
  return thiz->q;
}



#endif //HGUARD_emC_Ctrl_T1ish_Ctrl_emC
