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
 * 0x7620 = 30240 =  32*5*7*3*3*3, means divide by 2,3,5,6,7,8,9,10,   12,14,15,16,18,20,   24,27,28,30,32,33,35,36,40,42 etc.
 * 
 * It is the nominal value for 16 bit values. With it an overdrive of ~1.18 is possible.
 * 0x6c48 = 27720 = 2 * 2 * 2 * 3 * 3 * 5 * 7 * 11 ,
 * means divide by 2,3,4,5,6,7,8,9,10,11,12,14,15,16,18,20,22,24,  ,28,30,32,33,35,36,40,42,44,45,50, 60,
 *
 * It is a nominal value which is often used for example in automation control 
 * 0x6c00 = 27648 =  3^3^*2^10^ = 3 * 3 * 2^10^ = 27 * 1024
 *
 * 0x6270 = 25200 = 2 * 2 * 2 * 2 * 3 * 3 * 5 * 5 * 7
 * means divide by 2,3,4,5,6,7,8,9,10,12,14,15,16,18,20,21,24,25,28,30,32,33,35,36,40,42,45,50,60,70,75,80,90,100
 *
 * 0x5a82 = 23170 = 7*5*2*331 this number multiplicated with itself is 1fffaa04 = ~ 0x4000 shifted <<1 and taken hi-part.
 *                  It is a candidate for sqrt usage
 */
#define NOM1_i16_Ctrl_emC 0x6270  //= 25200
#define NOM2_i16_Ctrl_emC 0x4000

/**Normalization with this value results in ~0x4000 if the number is multiplied with itself (quadrat). */
#define NOMqu_i16_Ctrl_emC 0x5a82 //23170

/**General scaling for fix point numbers 32 bit:
 * 1651507200 = 0x62700000 = (25200)<<16 = 2^12^ * 3 * 3 * 5 * 5 * 7
 */
#define NOM1_i32_Ctrl_emC 0x62700000  //1651507200


/**Normalization with this value results in 0x40000000 if the number is multiplied with itself (quadrat). */
#define NOMqu_i32_Ctrl_emC 0x5A827999 //it is sqrt(2) * 2^30 = 1518500249 



//Macros for fix point mult and add

/**Signed multiplication 16 * 16 => 32 bit. 
 * This is the common solution. It is possible that in compl_adaption.h is an __asm(...)-optimized version via #define.
 * The compiler may recognize, it is expected that (int32)(int16)((A) & 0xffff) is a 16 bit register access 
 * and it should use the 16 * 16 =>32 bit multiplication etc.
 * Hint: Mask with 0xffff is necessary, elsewhere the MS-Visual Studio may produce a runtime error depending on the type of A and B 
 * @param A any value (not necessary a left value) with int16 content
 * @param B second multiplicant beside A
 * @param R an int32 type left value (a variable).
 */
#ifndef muls16_emC
  #define muls16_emC(R, A, B) { R = ((int32)(int16)((A) & 0xffff) * (int32)(int16)((B) & 0xffff)); }
#endif

/**Unsigned multiplication 16 * 16 => 32 bit. Comments see also [[muls16_emC(...)]]
 * @param A any value (not necessary a left value) with int16 content
 * @param B second multiplicant beside A
 * @param R an int32 type left value (a variable).
 */
#ifndef mulu16_emC
  #define mulu16_emC(R, A, B) { R = ((uint32)(uint16)(A) * (uint32)(uint16)(B)); }
#endif

/**multiplication 32 * 32 => 32 bit. Comments see also [[muls16_emC(...)]]
 * This multiplication can be used if the sum of used bits in both values are <=32.
 * Then the result is proper, no overflow occurs. 
 * If the sign is expanded correctly the result is correct in sign anyway. 
 * Note: This kind of multiplication may support by special machine instructions by some processors. 
 * @param A any value (not necessary a left value) with int32 content
 * @param B second multiplicant beside A
 * @param R an int32 or uint32 type left value (a variable) filled with lo part of 64 bit result.
 */
#ifndef mul32lo_emC
  #define mul32lo_emC(R, A, B) { R = (uint32)(A) * (uint32)(B); }
#endif

/**Signed Multiplication 32 * 32 => 32 bit. Comments see also [[muls16_emC(...)]]
 * This multiplication can be used if the bits in A and B are right aligned,
 * and the result is presented in the high part of the int64 result.
 * Note: This kind of multiplication may support by special machine instructions by some processors. 
 * @param A any value (not necessary a left value) with int32 content
 * @param B second multiplicant beside A
 * @param R an int32 type left value (a variable) filled with lo part of 64 bit result.
 */
#ifndef muls32hi_emC
  #define muls32hi_emC(R, A, B) { R = (int32)(((int64)(int32)(A) * (int32)(B)) >>32); }
#endif

/**Unsigned Multiplication 32 * 32 => 32 bit. Comments see also [[muls16_emC(...)]]
 * This multiplication can be used if the bits in A and B are right aligned,
 * and the result is presented in the high part of the int64 result.
 * Note: This kind of multiplication may support by special machine instructions by some processors. 
 * @param A any value (not necessary a left value) with int32 content
 * @param B second multiplicant beside A
 * @param R an int32 type left value (a variable) filled with lo part of 64 bit result.
 */
#ifndef mulu32hi_emC
  #define mulu32hi_emC(R, A, B) { R = (uint32)(((uint64)(uint32)(A) * (uint32)(B)) >>32); }
#endif

/**Signed Multiplication 32 * 32 => 64 bit. Comments see also [[muls16_emC(...)]]
 * @param A any value (not necessary a left value) with int32 content
 * @param B second multiplicant beside A
 * @param R an int64 type left value (a variable) filled with 64 bit result.
 */
#ifndef muls32_64_emC
  #define muls32_64_emC(R, A, B) { R = ((int64)(int32)(A) * (int32)(B)); }
#endif

/**Unsigned Multiplication 32 * 32 => 64 bit. Comments see also [[muls16_emC(...)]]
 * @param A any value (not necessary a left value) with int32 content
 * @param B second multiplicant beside A
 * @param R an uint64 type left value (a variable) filled with 64 bit result.
 */
#ifndef mulu32_64_emC
  #define mulu32_64_emC(R, A, B) { R = ((uint64)(uint32)(A) * (uint32)(B)); }
#endif

//-----------------------------------------------------------------------------
//Macros for fix point mult and add
// This is the common solution. It is possible that in compl_adaption.h is an __asm(...)-optimized version via #define.

/**16 bit signed mult and add, but the mult result accumulated as 32 bit value.
 * Comment and param adequate [[muls16_emC(...)]]
 * @param R should have a value, the multiplication result is added.
 */
#ifndef muls16add32_emC
  #define muls16add32_emC(R, A, B) { R += ((int32)(int16)(A) * (int32)(int16)(B)); }
#endif

/**16 bit unsigned mult and add, but the mult result accumulated as 32 bit value.
 * Comment and param adequate [[mulu16_emC(...)]]
 * @param R should have a value, the multiplication result is added.
 */
#ifndef mulu16add32_emC
  #define mulu16add32_emC(R, A, B) { R += ((uint32)(uint16)(A) * (uint32)(uint16)(B)); }
#endif

/**32 bit mult and add, but the mult result accumulated as 32 bit value.
 * Comment and param adequate [[mul32lo_emC(...)]]
 * @param R should have a value, the multiplication result is added.
 */
#ifndef mul32addlo_emC
  #define mul32addlo_emC(R, A, B) { R += (uint32)(A) * (uint32)(B); }
#endif

/**32 bit signed mult and add, but the mult result accumulated as 32 bit value.
 * Comment and param adequate [[muls32hi_emC(...)]]
 * @param R should have a value, the multiplication result is added.
 */
#ifndef muls32addhi_emC
  #define muls32addhi_emC(R, A, B) { R += (int32)(((int64)(int32)(A) * (int32)(B)) >>32); }
#endif

/**32 bit unsigned mult and add, but the mult result accumulated as 32 bit value.
 * Comment and param adequate [[mulu32hi_emC(...)]]
 * @param R should have a value, the multiplication result is added.
 */
#ifndef mulu32addhi_emC
  #define mulu32addhi_emC(R, A, B) { R += (uint32)(((uint64)(uint32)(A) * (uint32)(B)) >>32); }
#endif

/**64 bit signed mult and add, but the mult result accumulated as 64 bit value.
 * Comment and param adequate [[muls32_64_emC(...)]]
 * @param R should have a value, the multiplication result is added.
 */
#ifndef muls32add64_emC
  #define muls32add64_emC(R, A, B) { R += ((int64)(int32)(A) * (int32)(B)); }
#endif

/**64 bit unsigned mult and add, but the mult result accumulated as 64 bit value.
 * Comment and param adequate [[mulu32_64_emC(...)]]
 * @param R should have a value, the multiplication result is added.
 */
#ifndef mulu32add64_emC
  #define mulu32add64_emC(R, A, B) { R += ((uint64)(uint32)(A) * (uint32)(B)); }
#endif


/**Using this macro is necessary in the statment block where the saturating macros are used.
 * For standard C it defines a variable bool bSat_emC = false; which is set in the saturation macros.
 * For using optimized assembler statements this macro can be left empty. No effort.
 */
#ifndef DEFsatCheck_emC
  #define DEFsatCheck_emC bool bSat_emC = false;
#endif

/**This macro can be used to clear the saturation flag after some saturating operation.
 * In ARM technology it should clear the Q flag.
 */
#ifndef clearSatCheck_emC
  #define clearSatCheck_emC() { bSat_emC = false; }
#endif

/**This macro can be used to check the saturation flag after some saturating operation.
 * In ARM technology it should present the Q flag as boolean value.
 */
#ifndef satCheck_emC
  #define satCheck_emC() bSat_emC
#endif


/**Saturated additon of signed values. 
 * It limits the result to 0x7fff or 0x8000.
 * If the sign would be changed though both inputs has the same sign, the limitation is done.
 * If both inputs have different sign, never an overflow occurs. 0 + 0x8000 is also correctly 0x8000.
 * This macro should be used anytime an addition should not overflow.
 */
#ifndef adds16sat_emC
  #define adds16sat_emC(R, A, B) { int16 a = (A); int16 b = (B); R = a + b; \
  if(((a^b) &0x8000)==0) { if((a ^ R)&0x8000) { R = a & 0x8000 ? (int16)(0x8000): 0x7FFF; bSat_emC = true;}} \
  }   
#endif


/**Saturated additon of unsigned values. 
 * It limits the result to 0xffff.
 * If the result is lesser as the input, the limitation is done.
 * The result is always greater or equal as the input on unsigned addition.
 * This macro should be used anytime an addition should not overflow.
 */
#ifndef addu16sat_emC
  #define addu16sat_emC(R, A, B) { uint16 a = (A); uint16 b = (B);  R = (a + b) & 0xffff; \
  if(R < a || R < b) { R = 0xFFFF; bSat_emC = true; } \
  }   
#endif


/**Saturated additon of unsigned values. 
 * It limits the result to 0xffff.
 * If the result is lesser as the input, the limitation is done.
 * The result is always greater or equal as the input on unsigned addition.
 * This macro should be used anytime an addition should not overflow.
 */
#ifndef subu16sat_emC
  #define subu16sat_emC(R, A, B) { uint16 a = (A); uint16 b = (B);  R = (a - b) & 0xffff; \
  if(R > a ) { R = 0; bSat_emC = true; } \
  }   
#endif


/**
 */
#define PI_emC 3.141592653589793

#define PI_float_emC 3.1415927f

extern_C int16 cos16_emC ( int16 angle);

#define sin16_emC(ANGLE) cos16_emC((ANGLE)-0x4000)

/**Builds the atan2 from normalized values. 
 * Because normalization it does not use a division. 
 * Instead it builds the arcus via asin(x16) from the proper segment via linear interpolation.
 */
extern_C int16 atan2nom16_emC ( int16_complex x );

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

#define angle16_rad_emC(RAD) (int16)((RAD) * (32768.0f/PI_float_emC) ) 

#define angle32_rad_emC(RAD) (int32)((RAD) * (65536.0f * 32768.0f/PI_float_emC) )

#define radf_angle16_emC(ANGLE16) ((ANGLE16)* (PI_float_emC / 0x8000)) 

#define gradf_angle16_emC(ANGLE16) ((ANGLE16)* (180.0f / 0x8000)) 




/*@CLASS_C Nom_float_complex @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
typedef struct Nom_float_complex_T {

  /**The nominal value from input. */
  float_complex xnom;

  /**The revers magnitude*/
  float rmagn;

  /**Limit the amplifier, elsewhere it oscillates*/
  float xmaxqu;

  /**Factor to corr rmagn. */
  float f;

} Nom_float_complex_s;

/**
 * @simulink ctor
 */
static inline void ctor_Nom_float_complex(Nom_float_complex_s* thiz) {
  thiz->rmagn = 1.0f;
  thiz->xnom.re = 0;
  thiz->xnom.im = 0;
  thiz->xmaxqu = 1.8f;
  thiz->f = 0.5f;
}

/**Build the nominal vector from a given vector.
 * It uses the pre-calculated thiz->rmagn factor and stores thiz->xnom.
 * After them it calculates the magnitude of thiz->xnom and compares with 1.0 (0x4000)
 * and adjust the thiz->rmagn factor.
 * @param x any vector in range 0.5003..1.9993 (0x2000 .. 0x7fff)
 * @chg all thiz
 * @simulink Operation_FB
 */
static inline void step_Nom_float_complex(Nom_float_complex_s* thiz, float_complex x) {

  thiz->xnom.re = thiz->rmagn * x.re;
  thiz->xnom.im = thiz->rmagn * x.im;
  float xqu = thiz->xnom.re * thiz->xnom.re + thiz->xnom.im * thiz->xnom.im;    //re*re + im*im
  if(xqu > thiz->xmaxqu) { xqu = thiz->xmaxqu; }
  thiz->rmagn += thiz->f * thiz->rmagn * (1.0f - xqu);
}

#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Nom_float_complex : public Nom_float_complex_s {

  public: Nom_float_complex ( ) {
    ctor_Nom_float_complex(this);
  }

  public: void step (  float_complex x) { step_Nom_float_complex(this, x); }
};
#endif //__cplusplus



/*@CLASS_C Nom_int16_complex @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
typedef struct Nom_int16_complex_T {

  /**The nominal value from input. */
  int16_complex xnom;

  /**The magnitude and revers magnitude*/
  int16 magn, rmagn;

} Nom_int16_complex_s;

/**
 * @simulink ctor
 */
static inline void ctor_Nom_int16_complex(Nom_int16_complex_s* thiz) {
  thiz->rmagn = 0x4000;  //1.0
  thiz->xnom.re = 0;
  thiz->xnom.im = 0;
}

/**Build the nominal vector from a given vector.
 * It uses the pre-calculated thiz->rmagn factor and stores thiz->xnom.
 * After them it calculates the magnitude of thiz->xnom and compares with 1.0 (0x4000)
 * and adjust the thiz->rmagn factor.  
 * @param x any vector in range 0.5003..1.9993 (0x2000 .. 0x7fff)
 * @chg all thiz
 * @simulink Operation_FB
 */
static inline void step_Nom_int16_complex(Nom_int16_complex_s* thiz, int16_complex x) {
  DEFsatCheck_emC;
      
  int32 nom;                        //firstly build nominal value with given rm 
  muls16_emC(nom, thiz->rmagn, x.re); 
  thiz->xnom.re = (int16)((nom >>14) & 0xffff);
  muls16_emC(nom, thiz->rmagn, x.im); 
  thiz->xnom.im = (int16)((nom >>14) & 0xffff);
  int32 xqu;                       // secondly adjust rm, so that abs(nom.re, nom.im) == 1.0
  muls16_emC(xqu, thiz->xnom.re, thiz->xnom.re);         //nominal 1.0 =^ 0x1000'0000
  muls16add32_emC(xqu, thiz->xnom.im, thiz->xnom.im);    //re*re + im*im
  adds16sat_emC(thiz->rmagn, thiz->rmagn, ((0x10000000 - xqu)>>16)&0xffff);  //adjust rm in feedback
  //important: Use saturated addition, because an overflow can occure on incrementation. 
  //If the magnitued of the input is <0.5, the max. value of rmagn is 0x7fff. 
  //important: >>16 is the gain of this closed loop. It is the limit of gain. 
  //if >>15 is used, the time to settling to the correct value is a little bit longer. 
  //It depends of the normalization. 
}



/**Builds and returns the magnitude to the last given vector.
 * This routine should be invoked one time after step_Nom_int16_complex(...) to build the magnitude too.
 * It can be used also for a simple reciproke in range 0.5..2 by setting the thiz->rmagn value manually.
 */
static inline int16 magn_Nom_int16_complex(Nom_int16_complex_s* thiz) {
  DEFsatCheck_emC;
  int32 nom;
  mulu16_emC(nom, thiz->rmagn, thiz->magn); 
  adds16sat_emC(thiz->magn, thiz->magn, ((0x10000000 - nom)>>16)&0xffff);  //adjust rm in feedback
  return thiz->magn;
}



#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Nom_int16_complex : public Nom_int16_complex_s {

  public: Nom_int16_complex ( ) {
    ctor_Nom_int16_complex(this);
  }

  public: void step (  int16_complex x) { step_Nom_int16_complex(this, x); }
};
#endif //__cplusplus



/*@CLASS_C Q_rsqrt @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Fast square root */
float Q_rsqrt ( float number);

#endif //HGUARD_emC_Base__Math_emC
