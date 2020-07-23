#ifndef HGUARD_PIDi_Ctrl_emC
#define HGUARD_PIDi_Ctrl_emC

//#include "emC/Base/Object_emC.h"
#include <applstdef_emC.h>

/**Parameter of PID controller 
 * @simulink bus.
 */
typedef struct Par_PIDi_Ctrl_emC_t
{

  union { ObjectJc obj; } base;

  /**for debugging and check: The used step time for calcualation of the factors. */
  float Tstep;

  int xBits, yBits;

  /**Primary and used parameter: P-gain. */
  float kP;
  
  /**Primary parameter: Nachstellzeit. used: fI. */
  float Tn;
  
  float Tsd;

  float Td;
  
  /**Bit width for internal multiplier for Tsd. Use at least 4 bits to assure a step width
   * from 8..15. Use more bits for more solution of Td value. But do not use more than 8.
   *
   */
  int kBitTsd;

  /**Internal paramter depending factors. */
  struct Internal_PIDi_Ctrl_emC_t {

    int kPi;

    /**number of Bit shift for adaption wx-input to internal data. */ 
    int nShKp;

    /**Number of right shift from the 32 bit representation to the y output.*/
    int nSh32y;

    /**Number of right shift for wxP proper to fTs*/
    int nShfTs;

    /**Number of right shift for wxP, (nShTD + nShfTD) == nSh32y */
    int nShTs;

    /**Number of right shift for dwxP proper to fTD*/
    int nShfTD;

    /**Number of right shift for yD, (nShTD + nShfTD) == nSh32y */
    int nShyD;

    /**Smoothing time for D-Part.*/
    int fTsD;

    /**Factor for D-Part including kP and Transformation to int32. */
    int fD;

    /**Factor for wxP for Integrator adding. */
    int32 fI;

    /**Factor from float-x to int64 and to float-y-scale. */
    //float fIx, fIy;

    int dbgct_reparam;
  } i;


  /**If set then changes from outside are disabled. For Inspector access. */
  uint man: 1;

} Par_PIDi_Ctrl_emC_s;

#ifndef ID_refl_Par_PIDi_Ctrl_emC  //may be defined in *.reflOffs.h
#define ID_refl_Par_PIDi_Ctrl_emC 0x0FC2
#endif

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
extern_C Par_PIDi_Ctrl_emC_s* ctor_Par_PIDi_Ctrl_emC(ObjectJc* othiz, float Tstep, int xBits, int yBits);

/**step of PID controller
* @simulink Object-FB, no-thizStep.
*/
extern_C void set_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz, float kP, float Tn_param, float Td_param, float Tsd_param, bool* man_y);

/**Takes new parameter and re-calculates internal values.
 * This routine is also called on [[init_PIDi_Ctrl_emC(...)]].
 * @simulink Operation-FB, step-in.
 */
extern_C void reparam_Par_PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s* thiz);



/**Main data of PID controller 
 * @simulink no-bus.
 */
typedef struct PIDi_Ctrl_emC_t
{
  union { ObjectJc obj; } base;

  Par_PIDi_Ctrl_emC_s const* par;
  
  /**Limitation value of y output. The output is never greater or lesser its negative equivalent.
   * The I part will be limited too. */
  int yLim;

  int wx;

  /**Stored smoothed P-Part, to view input and calculate D.
   * It is possible that it is other normed. */
  int32 wxPs;

  /**Only for view, current raw dwx related to wxPs norming.*/
  int32 dwxPs;

  /**Stored for D-part, to view input. */
  //float wxPD;

  int yD;

  /**To view output. It is the same value as y_y arg of [[step_PIDi_Ctrl_emC(...)]]. */
  int y;

  /**Value of the integrator. */
  int32 qI;


  /**Limited output from P and D fix point. To view. */
  //int32 wxP32, wxPD32;
  
  /**Value of the differentiator. */
  //float qD1;
  
  int32 dbgct_reparam;



} PIDi_Ctrl_emC_s;

#ifndef ID_refl_PIDi_Ctrl_emC  //may be defined in *.reflOffs.h
#define ID_refl_PIDi_Ctrl_emC 0x0FC3
#endif


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
extern_C void setLim_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, int yLim);

/**step of PID controller 
 * @simulink Object-FB.
 */
extern_C void step_PIDi_Ctrl_emC(PIDi_Ctrl_emC_s* thiz, int wx, int* y_y);

static void get_wxP_PID_ctrl(PIDi_Ctrl_emC_s const* thiz, int* y);

static inline void get_wxP_PID_ctrl(PIDi_Ctrl_emC_s const* thiz, int* y) { *y = thiz->wxPs;  }

#if defined(DEF_CPP_COMPILE) && defined(__cplusplus)
class PIDi_Ctrl_emC : public PIDi_Ctrl_emC_s { //, public ObjectifcBaseJcpp {


  public: PIDi_Ctrl_emC(Par_PIDi_Ctrl_emC_s const* par){
    ObjectJc* obj = CTOR_ObjectJc(&this->base.obj, this, sizeof(PIDi_Ctrl_emC_s), refl_PIDi_Ctrl_emC, 0);  //should be initialized.
    ctor_PIDi_Ctrl_emC(obj); //the initialized ObjectJc as arguement.
    init_PIDi_Ctrl_emC(this, par); //the initialized ObjectJc as arguement.
  }

  public: void setParam ( Par_PIDi_Ctrl_emC_s* par) { setParam_PIDi_Ctrl_emC(this, par); }
  
  public: void step ( int wx, int* y_y){ step_PIDi_Ctrl_emC(this, wx, y_y); }

  //public: void reparam(Par_PIDi_Ctrl_emC_s* par){ reparam_PIDi_Ctrl_emC(this, par); }


};
#endif


#endif //HGUARD_PIDi_Ctrl_emC
