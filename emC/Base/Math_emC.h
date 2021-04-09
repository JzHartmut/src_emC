#ifndef HGUARD_emC_Base__Math_emC
#define HGUARD_emC_Base__Math_emC
#include <compl_adaption.h>

/**General scaling for fix point numbers 16 bit:
 * Often the nominal value of physical values is 1.0. Usual some overdrive exists. 
 * Hence it is not proper to use only a range from -1.0 .. 0.9999 as 0x8000 .. 0x7FFF. 
 * On the other hand -2.0 .. 1.999 is also not proper.
 * Sometimes the abibity to divide a value without fractional by 3, 5 or such may be interesting. 
 * Hence for map the value 1.0 a proper integer value should be used. It is this definition.
 *  
 * It is the nominal value for 16 bit values. With it an overdrive of ~1.08 is possible.
 * 30240 =  32*5*7*3*3*3, means divide by 2,3,5,6,7,8,9,10,   12,14,15,16,18,20,   24,27,28,30,32,33,35,36,40,42 etc.
 * 
 * It is the nominal value for 16 bit values. With it an overdrive of ~1.18 is possible.
 * 27720 = 2 * 2 * 2 * 3 * 3 * 5 * 7 * 11 ,
 * means divide by 2,3,4,5,6,7,8,9,10,11,12,14,15,16,18,20,22,24,  ,28,30,32,33,35,36,40,42,44,45,50, 60,
 *
 * 25200 = 2 * 2 * 2 * 2 * 3 * 3 * 5 * 5 * 7
 * means divide by 2,3,4,5,6,7,8,9,10,12,14,15,16,18,20,21,24,25,28,30,32,33,35,36,40,42,45,50,60,70,75,80,90,100
 *
 * 23170 = 0x5ab2 = 7*5*2*331 this number multiplicated with itself is 3fff. It is a candidate for sqrt 
 
 */
#define NOM_i16_Ctrl_emC 25200

/**General scaling for fix point numbers 32 bit:
 * 1651507200 = 0x62700000 = (25200)<<16 = 2^12^ * 3 * 3 * 5 * 5 * 7
 */
#define NOM_i32_Ctrl_emC 1651507200


/**
 */
#define PI_emC 3.141592653589793

#define PI_float_emC 3.1415927f

extern_C int16 cos16_emC ( int16 angle);

#define sin16_emC(ANGLE) cos16_emC((ANGLE)-0x4000)

/**sqare root.
 * The sqrt can only be performed for unsigned values. 
 * The nominal value is defined with 0x4000 as 1.0. 
 * It means 0x4000 == sqrt_emC(0x4000).
 * The sqrt(0xffff) results in about 0x7fff. 
 * It means calculation with quadrats can use the unsigned range 0x8000...0xFFFF
 * But the result after sqrt can be simple used as signed value again. 
 * 
 */
extern_C int16 sqrt16_emC ( uint16 val);

/**Reverse square root:  1 / sqrt(x).
 * This function is proper if the magnitude of a signal should be normalized to 1.0.
 * The result value is only used for multiplication with the inputs. A division (necesssary be sqrt) is prevented.
 * The rsqrt can only be performed for unsigned values. 
 * It means calculation with quadrats can use the unsigned range 0x8000...0xFFFF
 * But the result after sqrt can be simple used as signed value again. 
 * The nominal value is defined with 0x4000 as 1.0. 
 * It means 0x4000 == rsqrt_emC(0x4000).
 * The rsqrt(0xffff) results in about 0x1001. It is 1/4.0 => 0.25
 * An input value <= 0.5 results in 0x7fff which is the max output (1.9997) 
 * 
 */
extern_C int16 rsqrt16_emC ( int16 val);

extern_C int32 cos32_emC ( int32 angle);

#define angle16_degree_emC(GR) (int16)(((GR)/90.0f) * 0x4000) 

#define angle16_rad_emC(GR) (int16)(((GR)/PI_float_emC/2) * 0x4000) 

#define radf_angle16_emC(GR) ((GR)* (PI_float_emC / 0x8000)) 

#define gradf_angle16_emC(GR) ((GR)* (180.0f / 0x8000)) 

/**Fast square root */
float Q_rsqrt ( float number);

#endif //HGUARD_emC_Base__Math_emC
