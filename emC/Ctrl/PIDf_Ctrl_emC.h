#ifndef __Ctrl__pid_Ctrl_h__
#define __Ctrl__pid_Ctrl_h__

//#include "emC/Base/Object_emC.h"
#include <applstdef_emC.h>

/**This struct contains the used factors for the PID control calculated from the parameters.
 * It is an internal data struct used for message transfer of factors. 
 */
typedef struct ParFactors_PIDf_Ctrl_emC_T {

  union{ ObjectJc obj;} base;
  
  float kP;

  /**Smoothing time for D-Part.*/
  float fTsD;

  /**Factor for D-Part including kP and Transformation to int32. */
  float fD;

  /**Factor for wxP for Integrator adding. */
  int64 fI;
  
  /**Factor from float-x to int64 and to float-y-scale. */
  float fIx, fIy;

  /**Maximal value for the y output. The integrator in the PID uses fix point 64 bit for high accuracy.
   * This value is used to build the correct factors from float to fix point. 
   */
  float yMax;

} ParFactors_PIDf_Ctrl_emC_s;

#ifndef ID_refl_ParFactors_PIDf_Ctrl_emC
  #define ID_refl_ParFactors_PIDf_Ctrl_emC 0x1
#endif
extern_C ParFactors_PIDf_Ctrl_emC_s* ctor_ParFactors_PIDf_Ctrl_emC(ObjectJc* othiz);


/**Parameter of PID controller 
 * @simulink bus.
 */
typedef struct Par_PIDf_Ctrl_emC_T
{

  union { ObjectJc obj; } base;

  /**for debugging and check: The used step time for calcualation of the factors. */
  float Tctrl;

  /**Maximal value for the y output. The integrator in the PID uses fix point 64 bit for high accuracy.
   * This value is used to build the correct factors from float to fix point. 
   */
  float yMax;

  /**Primary and used parameter: P-gain. */
  float kP;
  
  /**Primary parameter: Nachstellzeit. used: fI. */
  float Tn;
  
  float Td;
  
  float T1d;

  /**Internal paramter depending factors. */
  ParFactors_PIDf_Ctrl_emC_s i;

  int dbgct_reparam;


  /**If set then changes from outside are disabled. For Inspector access. */
  uint man: 1;

  //uint limPbeforeD: 1;

} Par_PIDf_Ctrl_emC_s;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Par_PIDf_Ctrl_emC;
#endif

#ifndef ID_refl_Par_PIDf_Ctrl_emC  //may be defined in *.reflOffs.h
#define ID_refl_Par_PIDf_Ctrl_emC 0x0FC0
#endif

/**ctor of Par_PID controller
 * @param Tstep it is necessary as Simulink parameter to define the association to a defined step time.
 *        It is the time to call the Operation-FB. It is [[set_Par_PIDf_Ctrl_emC(...)]].
 *        But the argument is not used here. The value is really only necessary for simulink:
 * * For 4diac, the step time is determined by the event connections.
 * * For C/++ usage the step time is determined by the calling sequence. 
 * @simulink ctor.
 */
extern_C Par_PIDf_Ctrl_emC_s* ctor_Par_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep);

/**init of PID controller
 * @param Tstep_param It is the Tstep time of the controller, which should be regard on calculation of the factors. 
 * @simulink init
 */
extern_C bool init_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float Tctrl_param, float yMax_param
  , float kP, float Tn, float Td, float Tsd, ParFactors_PIDf_Ctrl_emC_s** parFactors_y );

/**step of PID controller
* @simulink Object-FB, no-thizStep.
*/
extern_C void set_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float kP, float Tn, float Td, float Tsd, ParFactors_PIDf_Ctrl_emC_s** parFactors_y );


#if defined(DEF_CPP_COMPILE) && defined(__cplusplus)
class Par_PIDf_Ctrl_emC : public Par_PIDf_Ctrl_emC_s {

  /**Constructs.
   */
  public: Par_PIDf_Ctrl_emC (int idObj, float Tstep, float yNom ) {
    CTOR_ObjectJc(&this->base.obj, this, sizeof(Par_PIDf_Ctrl_emC_s), refl_Par_PIDf_Ctrl_emC, idObj);  //should be initialized.
    ctor_Par_PIDf_Ctrl_emC(&this->base.obj, Tstep); //the initialized ObjectJc as arguement.
  }

  public: bool init (float Tstep, float yNom ) {
    init_Par_PIDf_Ctrl_emC(this, Tstep, yNom); //the initialized ObjectJc as arguement.
  }

  /**Constructs as base class of any inherited controller.
   * @arg objectJc forces calling CTOR_ObjectJc(...) in the inherited class ctor.
   */
  public: Par_PIDf_Ctrl_emC ( ObjectJc* objectJc) {
    ctor_Par_PIDf_Ctrl_emC(&this->base.obj, 0.001f); //the initialized ObjectJc as arguement.
  }


  public: void set(float kP, float Tn_param, float Td_param, float Tsd_param, bool* man_y) {
    set_Par_PIDf_Ctrl_emC(this, kP, Tn_param, Td_param, Tsd_param, null);
  }

  public: void reparam(){ reparam_Par_PIDf_Ctrl_emC(this); }



};
#endif





/**Main data of PID controller 
 * @simulink no-bus.
 */
typedef struct PIDf_Ctrl_emC_t
{
  union { ObjectJc obj; } base;

  ParFactors_PIDf_Ctrl_emC_s* parNew;
  
  /**Currently used factors. */
  ParFactors_PIDf_Ctrl_emC_s f;

  /**Current limitation of output. */
  float lim;


  float Tstep;

  /**Smoothed differential. */
  float dwxP;

  /**Stored for D-part, to view input. */
  float wxP;

  /**Stored for D-part, to view input. */
  float wxPD;

  /**To view output. It is the same value as y_y arg of [[step_PIDf_Ctrl_emC(...)]]. */
  float y;

  /**Value of the integrator. */
  int64 qI;

  /**Limited output from I fix point. To view. */
  int32 qIhi;

  /**Limited output from P and D fix point. To view. */
  int32 wxP32, wxPD32;
  
  /**Value of the differentiator. */
  float qD1;
  
  int32 dbgct_reparam;



} PIDf_Ctrl_emC_s;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_PIDf_Ctrl_emC;
#endif

#ifndef ID_refl_PIDf_Ctrl_emC  //may be defined in *.reflOffs.h
#define ID_refl_PIDf_Ctrl_emC 0x0FC1
#endif


/**ctor of PID controller 
 * @param Tstep it is necessary as Simulink parameter to define the association to a defined step time.
 *        It is the time to call the Operation-FB. It is [[set_Par_PIDf_Ctrl_emC(...)]].
 *        But the argument is not used here. The value is really only necessary for simulink:
 * * For 4diac, the step time is determined by the event connections.
 * * For C/++ usage the step time is determined by the calling sequence. 
 * * This parameter (used for simulink) should be equal to Tctrl_param of init_Par_PIDf_Ctrl_emC(...). 
 * @simulink ctor.
 */
extern_C PIDf_Ctrl_emC_s* ctor_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep);

/**init of PID controller
 * @param par the parameter Object, should be not null
 * @return false if par == null, true if initialized. 
 * @simulink init.
 */
extern_C bool init_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, ParFactors_PIDf_Ctrl_emC_s* par);

/**set Limitation of PID controller 
 * @simulink Operation-FB.
 */
extern_C void setLim_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float lim);

/**step of PID controller 
 * @simulink Object-FB.
 */
extern_C void step_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float wx, float* y_y);


/**Offers a new parameter set for this controller. 
 * This operation can be called any time in any thread. 
 * @par null or reference to given parameter set, may be either immediately inside the Par_PIDf_Ctrl_emC FBlock
 *      or in a event data structure. The event data are freed or the parameter FBlock is unlocked
 *      in this routine for the possibility to reuse the location for new parameter or event preparation.
 *      If par == null this operation does nothing.  
 * @simulink Operation-FB.
 */
extern_C void param_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, ParFactors_PIDf_Ctrl_emC_s* parNew);


extern_C void get_wxP_PID_ctrl(PIDf_Ctrl_emC_s const* thiz, float* y);

INLINE_emC void get_wxP_PID_ctrl(PIDf_Ctrl_emC_s const* thiz, float* y) { *y = thiz->wxP;  }

#if defined(DEF_CPP_COMPILE) && defined(__cplusplus)
class PIDf_Ctrl_emC : public PIDf_Ctrl_emC_s {

  /**Constructs.
   */
  public: PIDf_Ctrl_emC (int idObj ) {
    CTOR_ObjectJc(&this->base.obj, this, sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, idObj);  //should be initialized.
    ctor_PIDf_Ctrl_emC(&this->base.obj, 0.1234f); //the initialized ObjectJc as arguement.
  }

  /**Constructs as base class of any inherited controller.
   * @arg objectJc forces calling CTOR_ObjectJc(...) in the inherited class ctor.
   */
  protected: PIDf_Ctrl_emC ( ObjectJc* objectJc ) {
    ctor_PIDf_Ctrl_emC(&this->base.obj, 0.1234f); //the initialized ObjectJc as arguement.
  }

  /**Constructs with given parameter reference.
   * @arg objectJc forces calling CTOR_ObjectJc(...) in the inherited class ctor.
   */
  public: PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s const* par, int idObj){
    CTOR_ObjectJc(&this->base.obj, this, sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, idObj);  //should be initialized.
    ctor_PIDf_Ctrl_emC(&this->base.obj, Tstep); //the initialized ObjectJc as arguement.
  }

  /**Constructs with given parameter reference.
  * @arg objectJc forces calling CTOR_ObjectJc(...) in the inherited class ctor.
  */
  protected: PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s const* par, ObjectJc* objectJc){
    ctor_PIDf_Ctrl_emC(&this->base.obj, Tstep); //the initialized ObjectJc as arguement.
  }

  public: void init(Par_PIDf_Ctrl_emC_s* par) { init_PIDf_Ctrl_emC(this, par); }
  
  public: void step ( float wx, float* y_y){ step_PIDf_Ctrl_emC(this, wx, y_y); }

  //public: void reparam(Par_PIDf_Ctrl_emC_s* par){ reparam_PIDf_Ctrl_emC(this, par); }


};
#endif


#endif //__Ctrl__pid_Ctrl_h__
