#ifndef HGUARD_PIDi_Ctrl_emC
#define HGUARD_PIDi_Ctrl_emC

#include <emC/Base/Object_emC.h>
#include <emC/Base/Math_emC.h>


//tag::ParFactors_PIDi_Ctrl_emC[]
/**This struct contains the used factors for the PID control calculated from the parameters.
 * It is an internal data struct used for message transfer of factors. 
 */
typedef struct ParFactors_PIDi_Ctrl_emC_T {
  
  /**Limitation of the input value wx (controlling error) to calculate the P part. 
   * This value is depending on fPi. 
   * It is calcualted that the range of P-part is at last < 1/3 from the INT_NUM_emC range.
   * That is max. 10000 or max 655860000 for the P part.
   */
  INT_NUM_emC wxlim;  //new
  
  INT_NUM_emC dxlim;
  
  
  INT_NUM_emC fP;


  /**Factor for D-Part including kP and Transformation to int32. */
  INT_NUM_emC fD;

  /**number of right shift from the intermediate representation (32 or 16 bit)
   * for integration growth. */ 
  int8 nShKI;

  /**Number of right shift from the intermediate representation (32 or 16 bit) to the y output.*/
  int8 nShy;

  /**Number of right shift for wxP proper to fTs*/
  //int8 nShfTs;

  /**Number of right shift for wxP, (nShTD + nShfTD) == nSh32y */
  //int8 nShTs;

  /**Number of right shift for dwxP proper to fTD*/
  //int8 nShfTD;

  /**Number of right shift for yD, (nShTD + nShfTD) == nSh32y */
  int8 nShP,nShD;

  int8 en, open, _spare_[2];


  /**Factor for wxP for Integrator adding. */
  int32 fI;

} ParFactors_PIDi_Ctrl_emC_s;
//end::ParFactors_PIDi_Ctrl_emC[]


//tag::Par_PIDi_Ctrl_emC[]
/**Parameter of PID controller 
 * @simulink bus.
 */
typedef struct Par_PIDi_Ctrl_emC_t
{

  union { ObjectJc obj; } base;

  /**Tstep of the controller, used step time for calcualation of the factors. */
  float Tctrl;

  /**Maximal value for the y output. 
   * This value is used to build the correct factors and bit shifts from float to fix point. 
   */
  INT_NUM_emC yMax;

  //int xBits, yBits;

  /**Primary and used parameter: P-gain. */
  float kP;
  
  /**Primary parameter: Nachstellzeit. used: fI. */
  float Tn;
  
  //float Tsd;

  float Td;

  /**Number of steps for the difference how the differential input is built.*/
  INT_NUM_emC dt;
  
  /**Bit width for internal multiplier for Tsd. Use at least 4 bits to assure a step width
   * from 8..15. Use more bits for more solution of Td value. But do not use more than 8.
   *
   */
  int kBitTsd;

  /**Internal paramter depending factors. */
  ParFactors_PIDi_Ctrl_emC_s* f;

  ParFactors_PIDi_Ctrl_emC_s f12[2];

  /**If set then changes from outside are disabled. For Inspector access. */
  uint8 man;
  uint8 ixf;
  uint8 numBits;
  uint8 _spare_[8/*sizeof(void*)*/ - 3];  //spare till pointer size


} Par_PIDi_Ctrl_emC_s;
//end::Par_PIDi_Ctrl_emC[]



#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Par_PIDi_Ctrl_emC;
#endif

#ifndef ID_refl_Par_PIDi_Ctrl_emC  //may be defined in *.reflOffs.h
#define ID_refl_Par_PIDi_Ctrl_emC 0x0FC2
#endif


#define INIZ_Par_PIDi_Ctrl_emC(THIZ, ID) { { INIZ_ObjectJc(THIZ, refl_Par_PIDi_Ctrl_emC, ID)}, 0} 


/**ctor of PID controller
 * @param Tstep the step (sample) time which will be used for step_PIDi_Ctrl_emC().
 *        The internal factors are regarded to the Tstep
 * @param xBits Number of bits which are used for the input value.
          The difference (yBits - xBits) determines the solution of the KP value for calculation.
          yBits must be greater or equal xBits, whereby greater is recommended.
          If yBits == xBits, the solution of KP is only integer (1.0, 2.0 etc.)
          If (yBits - xBits) ==2 then the solution is 0.25, which enables values starting from 0.25 for KP for integer calculation.
          It means yBits = xBits is only recommended on a higher KP usage.
          Usual the y value can be at least 16 bit width whereby the x value is the solution of the ADC, often 12 bits.
 * @param yBits Number of bits which will be used for the output value. 
 *        yBits must >= xBits. 
 *        The internal integrator has 32 bit. 
 *        The growth factor for the I-Part and the smoothing value for D-Part is an integer value 
 *        which's ==1 means a Tn = Tstep * of 2 power of (32 - yBits). This is the limitation for Tn and Tds.
 *        For yBits=16 the Tn can be 65000 * Tstep (6.5 seconds on 100 ?s Tstep).
 *        For yBits=22 the Tn <= 1000 * Tstep is necessary.
 *        Hence a bit width of 16 (for following 16-bit-integer calculation) till 20..22 is recommended. 
 * @simulink ctor.
 */
extern_C Par_PIDi_Ctrl_emC_s* ctor_Par_PIDi_Ctrl_emC(ObjectJc* othiz, float Tstep);

/**init of parameter FBlock for the PID controller
 * @param Tstep_param It is the Tstep time of the controller, which should be regard on calculation of the factors. 
 * @param yMax_param the expected value range (including negative) for the output. 
 *        It must not > 10000 for 16 bit int representation and not > 655'360'000 for 32 bit. 
 * @param numBits It is either 16 or 32 depending on the used step operation. 
 * @simulink init
 */
extern_C bool init_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz, float Tctrl_param
  , INT_NUM_emC yMax_param, int numBits, float kP, float Tn, float Td, int dt, bool reset, bool openLoop_param );

/**step of PID controller
* @simulink Object-FB, no-thizStep.
*/
extern_C void set_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz, float kP, float Tn, float Td, int dt, bool reset);


//tag::reset_Par_PIDf_Ctrl_emC[]
/**Reset or run all controller which are related to this parameter FBlock. 
 * This operation can be called in any thread. 
 * It takes effect on the next step_PIDi_Ctrl_emC(...) on all related controller. 
 * To combine reset with parameter values you can also use set_Par_PIDf_Ctrl_emC(...).
 */
INLINE_emC void reset_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz, bool reset) {
  thiz->f->en = reset? 0 : 1;
}
//end::reset_Par_PIDf_Ctrl_emC[]


//tag::PIDi_Ctrl_emC[]
/**Main data of PID controller 
 * @simulink no-bus.
 */
typedef struct PIDi_Ctrl_emC_t
{
  union { ObjectJc obj; } base;

  Par_PIDi_Ctrl_emC_s const* par;
  
  /**Limitation value of y output. The output is never greater or lesser its negative equivalent.
   * The I part will be limited too. */
  INT_NUM_emC yLim;

  INT_NUM_emC wx;

  INT_NUM_emC wxd;

  /**Stored smoothed P-Part, to view input and calculate D.
   * It is possible that it is other normed. */
  int32 wxds1, wxPs;

  /**Only for view, current raw dwx related to wxPs norming.*/
  int32 dwxPs;

  /**Stored for D-part, to view input. */
  //float wxPD;

  INT_NUM_emC yD;

  /**To view output. It is the same value as y_y arg of [[step_PIDi_Ctrl_emC(...)]]. */
  INT_NUM_emC y;

  /**Value of the integrator. */
  int32 qI;

  uint8 disableIntg;
  
  
  #ifdef DEF_TestVal_PIDi_Ctrl_emC
  INT_NUM_emC wxP;
  INT_NUM_emC dxP;
  #endif

  /**Limited output from P and D fix point. To view. */
  //int32 wxP32, wxPD32;
  
  /**Value of the differentiator. */
  //float qD1;
  

} PIDi_Ctrl_emC_s;
//end::PIDi_Ctrl_emC[]

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_PIDi_Ctrl_emC;
#endif

#ifndef ID_refl_PIDi_Ctrl_emC  //may be defined in *.reflOffs.h
#define ID_refl_PIDi_Ctrl_emC 0x0FC3
#endif


#define INIZ_PIDi_Ctrl_emC(THIZ, ID) { { INIZ_ObjectJc(THIZ, refl_PIDi_Ctrl_emC, ID)}, 0} 


/**ctor of PID controller 
 * @arg par the initial parameter set. It is possible that it is null.
 *          Then setParam_PIDi_Ctrl_emC must be call with a valid reference afterwards.
 * @simulink ctor.
 */
extern_C PIDi_Ctrl_emC_s* ctor_PIDi_Ctrl_emC(ObjectJc* othiz);

/**Initialize all aggregations
 * @param par the parameter Object, should be not null
 * @return false if par == null, true if initialized.
 * @simulink init
 */
extern_C bool init_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, Par_PIDi_Ctrl_emC_s const* par);

/**set or switch parameter of the PID controller
 * @param par the parameter Object, should be not null
 * @return false if par == null, true if initialized. 
 * @ xxsimulink init.
 */
extern_C void setParam_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, Par_PIDi_Ctrl_emC_s const* par);

/**Sets the limitation value for the output.*/
extern_C void setLim_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, INT_NUM_emC yLim);

/**step of PID controller 
 * @simulink Object-FB.
 */
extern_C INT_NUM_emC step16_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, INT_NUM_emC wx, INT_NUM_emC dwx);

/**step of PID controller 
 * @simulink Object-FB.
 */
extern_C INT_NUM_emC step32_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, INT_NUM_emC wx, INT_NUM_emC wxd);


/**Gets the y result. */
INLINE_emC INT_NUM_emC getY_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz) { return thiz->y; }


/**step of PID controller 
 * @simulink Object-FB.
 */
INLINE_emC void stepY_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, INT_NUM_emC wx, INT_NUM_emC* y_y) {
  step32_PIDi_Ctrl_emC(thiz, wx, wx);
  *y_y = thiz->y;
}

static void get_wxP_PID_ctrl(PIDi_Ctrl_emC_s const* thiz, INT_NUM_emC* y);

static inline void get_wxP_PID_ctrl(PIDi_Ctrl_emC_s const* thiz, INT_NUM_emC* y) { *y = thiz->wxPs;  }

#if defined(DEF_CPP_COMPILE) && defined(__cplusplus)
class PIDi_Ctrl_emC : public PIDi_Ctrl_emC_s { //, public ObjectifcBaseJcpp {


  public: PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s const* par){
    ObjectJc* obj = CTOR_ObjectJc(&this->base.obj, this, sizeof(PIDi_Ctrl_emC_s), refl_PIDi_Ctrl_emC, 0);  //should be initialized.
    ctor_PIDi_Ctrl_emC(obj); //the initialized ObjectJc as arguement.
    init_PIDi_Ctrl_emC(this, par); //the initialized ObjectJc as arguement.
  }

  public: void setParam ( Par_PIDi_Ctrl_emC_s* par) { setParam_PIDi_Ctrl_emC(this, par); }
  
  public: void step32 ( INT_NUM_emC wx, INT_NUM_emC* y_y){ step32_PIDi_Ctrl_emC(this, wx, wx); }

  public: void step16 ( INT_NUM_emC wx, INT_NUM_emC* y_y){ step16_PIDi_Ctrl_emC(this, wx, wx); }

  //public: void reparam(Par_PIDi_Ctrl_emC_s* par){ reparam_PIDi_Ctrl_emC(this, par); }


};
#endif


#endif //HGUARD_PIDi_Ctrl_emC
