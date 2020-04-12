/**This source contains some operations with complex values and angles. */
#ifndef HEADERGUARD_Ctrl_Angle_FB
#define HEADERGUARD_Ctrl_Angle_FB
#include <string.h>  //memset
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <math.h>


/**calculation factor from rad to int32-angle: It is 180 degree / M_PI = 2147483648.0f / M_PI */
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
 * @param VAL32 angle between -0x80000000 (= 180° ) and 0x7fffffff (= 179.99°)
 * @return angle between -180° and  179.999°
 */
#define int32_to_grad(VAL32) (( (float)(((int32)(VAL32))) ) * (180.0f / k180_int32floatAngle))


/**Conversion from 32-bit-angle representation to float value in rad.
 * @param VAL32 angle between -0x80000000 (= 180° ) and 0x7fffffff (= 179.99°)
 * @return angle between -M_PI (=180°) and M_PI-0.000001 (= 179.999°)
 */
#define int32_to_rad(VAL32) (( (float)(((int32)(VAL32))) ) * (M_PI / k180_int32floatAngle))


/**Conversion from float value in radiant to 16-bit-angle representation.
 * @param RAD angle between -M_PI (=180°) and M_PI-0.000001 (= 179.999°) with possible overdrive (modulo 2*M_PI).
 * @return angle between -0x8000 (= 180° ) and 0x7fff (= 179.99°)
 * @Implementation notes: The higher bits if overdriven are removed. It is a general solution.
 */
#define rad_to_int16(RAD) ((int16)( (RAD) * (32768.0f / M_PI))) 


/**Conversion from float value in radiant to 32-bit-angle representation.
 * Reards radiant values from approximately -350..350.
 * Implementation note: 24 bits are used to convert float to integer, The result is shifted 8 bits to left.
 * @param RAD angle between -M_PI (=180°) and M_PI-0.000001 (= 179.999°) with possible overdrive (modulo 2*M_PI).
 * @return angle between -0x80000000 (= 180° ) and 0x7fffffff (= 179.99°)
 */
#define rad_to_int32(RAD) (((int32)( (RAD) * (32768.0f * 256 / M_PI))<<8))

/**Conversion from float value in grad to 32-bit-angle representation.
 * @param GRAD angle between -M_PI (=180°) and M_PI-0.000001 (= 179.999°) with possible overdrive (modulo 2*M_PI).
 * @return angle between -0x80000000 (= 180° ) and 0x7fffffff (= 179.99°)
 */
#define grad_to_int32(GRAD) ((int32)( (GRAD) * (k180_int32floatAngle / 180.0f)))

#define grad_to_rad(GRAD) ((GRAD) * (M_PI / 180.0f))

#define rad_to_grad(RAD) ((RAD) * (180.0f / M_PI))

#define mult_complex_FB(x1, x2, y) \
{ y.re = x1.re * x2.re - x1.im * x2.im; \
  y.im = x1.im * x2.re + x1.re * x2.im; \
}



/**This structure describes a complex signal value with its angle and magnitude.
 * @simulink bus
 */
typedef struct Angle_abwmf_FB_CtrlemC_T
{ 
  union { ObjectJc obj; };

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










#endif //HEADERGUARD_Ctrl_Angle_FB
