/**This source contains some operations with complex values and angles. */
#ifndef HEADERGUARD_Ctrl_Angle_FB
#define HEADERGUARD_Ctrl_Angle_FB
#include <string.h>  //memset
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <math.h>


/**calculation factor from rad to int32-angle: It is 180 degree / kPI_Angle_FB = 2147483648.0f / kPI_Angle_FB */
#define krPi_int32Angle 0x28BE60DC

#define kPI_Angle_FB 3.141592653f
#define k30_int32Angle 0x15555555
#define k60_int32Angle 0x2aaaaaaa
#define k90_int32Angle 0x40000000
#define k120_int32Angle 0x55555555
#define k180_int32Angle 0x80000000
#define k240_int32Angle 0xaaaaaaaa

#define k180_int32floatAngle 2147483648.0f


/**Conversion from 32-bit-angle representation to float value in grad.
 * @param VAL32 angle between -0x80000000 (= 180� ) and 0x7fffffff (= 179.99�)
 * @return angle between -180� and  179.999�
 */
#define int32_to_grad(VAL32) (( (float)(((int32)(VAL32))) ) * (180.0f / k180_int32floatAngle))


/**Conversion from 32-bit-angle representation to float value in rad.
 * @param VAL32 angle between -0x80000000 (= 180� ) and 0x7fffffff (= 179.99�)
 * @return angle between -kPI_Angle_FB (=180�) and kPI_Angle_FB-0.000001 (= 179.999�)
 */
#define int32_to_rad(VAL32) (( (float)(((int32)(VAL32))) ) * (kPI_Angle_FB / k180_int32floatAngle))


/**Conversion from float value in radiant to 16-bit-angle representation.
 * @param RAD angle between -kPI_Angle_FB (=180�) and kPI_Angle_FB-0.000001 (= 179.999�) with possible overdrive (modulo 2*kPI_Angle_FB).
 * @return angle between -0x8000 (= 180� ) and 0x7fff (= 179.99�)
 * @Implementation notes: The higher bits if overdriven are removed. It is a general solution.
 */
#define rad_to_int16(RAD) ((int16)( (RAD) * (32768.0f / kPI_Angle_FB))) 


/**Conversion from float value in radiant to 32-bit-angle representation.
 * Reards radiant values from approximately -350..350.
 * Implementation note: 24 bits are used to convert float to integer, The result is shifted 8 bits to left.
 * @param RAD angle between -kPI_Angle_FB (=180�) and kPI_Angle_FB-0.000001 (= 179.999�) with possible overdrive (modulo 2*kPI_Angle_FB).
 * @return angle between -0x80000000 (= 180� ) and 0x7fffffff (= 179.99�)
 */
#define rad_to_int32(RAD) (((int32)( (RAD) * (32768.0f * 256 / kPI_Angle_FB))<<8))

/**Conversion from float value in grad to 32-bit-angle representation.
 * @param GRAD angle between -kPI_Angle_FB (=180�) and kPI_Angle_FB-0.000001 (= 179.999�) with possible overdrive (modulo 2*kPI_Angle_FB).
 * @return angle between -0x80000000 (= 180� ) and 0x7fffffff (= 179.99�)
 */
#define grad_to_int32(GRAD) ((int32)( (GRAD) * (k180_int32floatAngle / 180.0f)))

#define grad_to_rad(GRAD) ((GRAD) * (kPI_Angle_FB / 180.0f))

#define rad_to_grad(RAD) ((RAD) * (180.0f / kPI_Angle_FB))

#define mult_complex_FB(x1, x2, y) \
{ y.re = x1.re * x2.re - x1.im * x2.im; \
  y.im = x1.im * x2.re + x1.re * x2.im; \
}




/* Alpha Beta Transformation (RST->AB)*/
//inline void rst2ab_i32_Angle_Ctrl_enC(int32* rst, int32_complex* ab) {
//  ab->re = 2/3.0f * (rst[0] - 0.5f * (rst[1] + rst[2]));
//  ab->im = 0.5773502692f * (rst[1] - rst[2]);
//}


#define kCos30_int16 ((int32)0xddb4) //value cos(30�) = 0.8660354 scaled to uint16 point pos 16

inline void ab2rst32_Angle_Ctrl_emC(int32_complex* ab, int32* rst) {
  rst[0] = ab->re;
  int32 re2 = -(ab->re >>1);  //-0.5 * re = -sin(30�) * re
  int32 im30 = kCos30_int16 * (int16)(ab->im >>16); //0.866 * im = cos(30�) * im
  rst[1] = re2 + im30;
  rst[2] = re2 - im30;
}                 //-0.8b = -S -0.5R


/**Converts 3~ voltages to ab-vector, but multiplicate with 1.5.
 * The multiplication is done by internal reason,
 * a really multiplication is saved because calculation time.
 * The input values may be given from a ADC with 15 bits used incl. sign.
 * input range 0xc000 ... 4000, ouput range 0xa000 .. 6000
 * The output values uses 16 bit incl. sign.
 * ab->re = r - 0.5*s - 0.5*t;
 * ab->im = (s - t) * 3/2 * 1/sqrt(3)
 * @return (r+s+t)/2
 */
inline int16 rst2abn16_Angle_Ctrl_emC(int16 rst[3], int16_complex* ab) {
  ab->re = rst[0] - (rst[1]>>1) - (rst[2]>>1);
  int32 im32;
  muls16_emC(im32, rst[1] - rst[2], 0x6ed9);  //0x6ed9 = 0x8000 * 3/2*(1/sqrt(3))
  ab->im = im32 >>15;
  return (rst[0] + rst[1] + rst[2])>>1;
}



/**This structure describes a complex signal value with its angle and magnitude.
 * @simulink bus
 */
typedef struct Angle_abwmf_FB_CtrlemC_T
{ 
  union { ObjectJc obj; } base;

  /**rotating normal vector (magnitude = 1) for the given angle. */
  float_complex ab;
 
  /**revers rotating normal vector (magnitude = 1) for the given angle. The im-Component is negative. */
  float_complex anb;

  /**Angle in int32. */
  int32 wi;

  /**Angle in radiant. */
  float wrad;

  /**Magnitude of a signal. It is 1.0 if only an angle is given. */
  float m;

  /**Frequency of the signal. It should be a middle value of the angle difference per step. */
  float fq;

} Angle_abwmf_FB_CtrlemC;


#ifndef ID_refl_Angle_abwmf_FB_CtrlemC
  #define ID_refl_Angle_abwmf_FB_CtrlemC 0x0fC4
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Angle_abwmf_FB_CtrlemC;
#endif



/**sets the angle values with given integer angle. 
 * The output bus from simulink will be allocated in simulink respectively in the generated code.
 * Use the pointer to the existing output data, that are the instance data.
 * @param input the angle
 * @simulink ctor
 */
void ctor_Angle_abwmf_FB(Angle_abwmf_FB_CtrlemC* thiz, int32 identObj, float Tstep);


/**sets the angle values with given integer angle. 
 * The output bus from simulink will be allocated in simulink respectively in the generated code.
 * Use the pointer to the existing output data, that are the instance data.
 * @param input the angle
 * @param fq associated frequency parameter.
 * @simulink Object-FB, accel-tlc
 */
inline void set_Angle_abwmf_FB(Angle_abwmf_FB_CtrlemC* thiz, int32 wi, float fq, float m, float* wrad_y) //, float_complex* ab_y)
{
#ifndef __reflectionHidden__ 
   thiz->wi = wi;
   float wrad = int32_to_rad(wi);
   thiz->wrad = wrad;
   thiz->ab.re = thiz->anb.re = cosf(wrad);
   thiz->anb.im = - (thiz->ab.im = sinf(wrad));
   thiz->fq = fq;
   thiz->m = m;
   *wrad_y = sizeof(void*); //wrad;
#endif
}










/**This structure describes a complex signal value with its angle and magnitude.
 * @simulink no-bus
 */
typedef struct Angle_abgmf16_CtrlemC_T
{ 
  union { ObjectJc obj; } base;

  /**rotating normal vector (magnitude = 1) for the given angle. */
  float_complex ab;
 
  /**revers rotating normal vector (magnitude = 1) for the given angle. The im-Component is negative. */
  float_complex anb;

  /**Angle in int32. */
  int32 wi;

  /**Angle in radiant. */
  float wrad;

  /**Magnitude of a signal. It is 1.0 if only an angle is given. */
  float m;

  /**Frequency of the signal. It should be a middle value of the angle difference per step. */
  float fq;

} Angle_abgmf16_CtrlemC;


#ifndef ID_refl_Angle_abgmf16_CtrlemC
  #define ID_refl_Angle_abgmf16_CtrlemC 0x0fC5
#endif

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Angle_abgmf16_CtrlemC;
#endif



/**sets the angle values with given integer angle. 
 * The output bus from simulink will be allocated in simulink respectively in the generated code.
 * Use the pointer to the existing output data, that are the instance data.
 * @param input the angle
 * @simulink ctor
 */
void ctor_Angle_abgmf16_CtrlemC(Angle_abgmf16_CtrlemC* thiz, int32 identObj, float Tstep);


/**sets the angle values with given integer angle. 
 * The output bus from simulink will be allocated in simulink respectively in the generated code.
 * Use the pointer to the existing output data, that are the instance data.
 * @param input the angle
 * @param fq associated frequency parameter.
 * @simulink Object-FB, accel-tlc
 */
inline void set_Angle_abgmf16_CtrlemC(Angle_abgmf16_CtrlemC* thiz, int32 wi, float fq, float m, float* wrad_y) //, float_complex* ab_y)
{
#ifndef __reflectionHidden__ 
   thiz->wi = wi;
   float wrad = int32_to_rad(wi);
   thiz->wrad = wrad;
   thiz->ab.re = thiz->anb.re = cosf(wrad);
   thiz->anb.im = - (thiz->ab.im = sinf(wrad));
   thiz->fq = fq;
   thiz->m = m;
   *wrad_y = sizeof(void*); //wrad;
#endif
}










#endif //HEADERGUARD_Ctrl_Angle_FB
