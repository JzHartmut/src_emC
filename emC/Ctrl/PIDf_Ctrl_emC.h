#ifndef __Ctrl__pid_Ctrl_h__
#define __Ctrl__pid_Ctrl_h__

#include "emC/Base/Object_emC.h"


//tag::ParFactors_PIDf_Ctrl_emC[]
/**This struct contains the used factors for the PID control calculated from the parameters.
 * It is an internal data struct used for message transfer of factors. 
 */
typedef struct ParFactors_PIDf_Ctrl_emC_T {

  /**Copied kP from input arguments. */
  float kP;

  /**Smoothing factor for D-Part.*/
  float fTsD;

  /**Factor for D-Part including kP and Transformation to int32. */
  float fPD;

  /**Factor for wxP for Integrator adding. used for 64 bit multiplication result.
   * Note fix point multiplication  */
  float fI;

  /**0=disable or reset, 1=enable. 
   * It is the negate reset argument of set_Par_PIDf_Ctrl_emC(..., reset); or reset_... */
  int8 en;

  /**Stored only initially for bout parameter sets */
  int8 open;
  
  /**Notify a change*/
  int8 chg;

  int8 _spare_[sizeof(void*) -3];  //alignment to sizeof(ptr)
  
} ParFactors_PIDf_Ctrl_emC_s;
//end::ParFactors_PIDf_Ctrl_emC[]



//tag::Par_PIDf_Ctrl_emC[]
/**Parameter of PID controller 
 */
typedef struct Par_PIDf_Ctrl_emC_T
{

  union { ObjectJc obj; } base;

  //union { uint32 v; Bits_Par_PIDf_Ctrl_emC_s b; } bits;

  //union { uint32 i32;
    //struct 
    //{ 
      int8 ixf;
    /**If set then changes from outside are disabled. For Inspector access. */
    int8 man;
      int8 _spare_[2];
  int32 dbgct_reparam;

//    };
//  } bits;

  /**for debugging and check: The used step time for calcualation of the factors. */
  float Tctrl;

  /**Maximal value for the y output. The integrator in the PID uses fix point 64 bit for high accuracy.
   * This value is used to build the correct factors from float to fix point. 
   */
  float yMax;

    /**Factor from float-x to int64 and to float-y-scale. */
  float fIx, fIy;



  /**Primary and used parameter: P-gain. */
  float kP;
  
  /**Primary parameter: Nachstellzeit. used: fI. */
  float Tn;
  
  float Td;
  
  float T1d;

  /**Internal paramter depending factors. */
  ParFactors_PIDf_Ctrl_emC_s* f;
  ParFactors_PIDf_Ctrl_emC_s i[2];



  //uint limPbeforeD: 1;

} Par_PIDf_Ctrl_emC_s;
//end::Par_PIDf_Ctrl_emC[]

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_Par_PIDf_Ctrl_emC;
#endif

#ifndef ID_refl_Par_PIDf_Ctrl_emC  //may be defined in *.reflOffs.h
  #define ID_refl_Par_PIDf_Ctrl_emC 0x0FC0
#endif

#define INIZ_Par_PIDf_Ctrl_emC(THIZ, ID) { { INIZ_ObjectJc(THIZ, refl_Par_PIDf_Ctrl_emC, ID)}, 0} 


/**ctor of Par_PID controller
 * @param Tstep it is necessary as Simulink parameter to define the association to a defined step time.
 *        It is the time to call the Operation-FB. It is [[set_Par_PIDf_Ctrl_emC(...)]].
 *        But the argument is not used here. The value is really only necessary for simulink:
 * * For 4diac, the step time is determined by the event connections.
 * * For C/++ usage the step time is determined by the calling sequence. 
 * @simulink ctor.
 */
extern_C Par_PIDf_Ctrl_emC_s* ctor_Par_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep);

/**init of parameter FBlock for the PID controller
 * @param Tstep_param It is the Tstep time of the controller, which should be regard on calculation of the factors. 
 * @simulink init
 */
extern_C bool init_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float Tctrl_param, float yMax_param
  , float kP, float Tn, float Td, float Tsd, bool reset, bool openLoop_param );

/**step of parameter FBlock for the PID controller for actual changed parameter
 * @simulink Object-FB, no-thizStep.
 */
extern_C void set_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float kP, float Tn, float Td, float Tsd, bool reset);

//tag::reset_Par_PIDf_Ctrl_emC[]
/**Reset or run all controller which are related to this parameter FBlock. 
 * This operation can be called in any thread. It takes effect immediately. 
 * To combine reset with parameter values you can also use set_Par_PIDf_Ctrl_emC(...).
 */
INLINE_emC void reset_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, bool reset) {
  thiz->f->en = reset? 0 : 1;
}
//end::reset_Par_PIDf_Ctrl_emC[]


//tag::cpptor_Par_PIDf_Ctrl_emC[]
#if defined(DEF_cplusplus_emC) && defined(__cplusplus)
class Par_PIDf_Ctrl_emC : public Par_PIDf_Ctrl_emC_s {

  /**Constructs.
   */
  public: Par_PIDf_Ctrl_emC (int idObj, float Tstep, float yNom ) {
    CTOR_ObjectJc(&this->base.obj, this, sizeof(Par_PIDf_Ctrl_emC_s), refl_Par_PIDf_Ctrl_emC, idObj);  //should be initialized.
    ctor_Par_PIDf_Ctrl_emC(&this->base.obj, Tstep); //the initialized ObjectJc as arguement.
  }
  //end::cpptor_Par_PIDf_Ctrl_emC[]

  public: bool init (float Tstep, float yNom, float kP, float Tn_param, float Td_param, float Tsd_param, bool reset, bool openLoop ) {
    return init_Par_PIDf_Ctrl_emC(this, Tstep, yNom, kP, Tn_param, Td_param, Tsd_param, reset, openLoop); //the initialized ObjectJc as arguement.
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



};
#endif




//tag::PIDf_Ctrl_emC[]
/**Main data of PID controller 
 * @simulink no-bus.
 */
typedef struct PIDf_Ctrl_emC_t
{
  union { ObjectJc obj; } base;

  /**Aggregation to parameter. */
  Par_PIDf_Ctrl_emC_s* par;
  
  /**Current limitation of output (state). */
  float limf;

  /**Smoothed differential (state). */
  float xds;

  /**Non limited P part kP*wx. Interdediate value, not a state. */
  float wxP;

  /**Stored for D-part, to view input. Interdediate value, not a state. */
  float dxP;

  /**float representation for the integrator (state if disableIntg). */
  float yIntg;

  /**To view the control output in open loop state. Interdediate value, not a state. */
  float yctrl;

  /**Value of the integrator (state). @boundary 8. Useable with 64 or 32 bit. */
  union { int64 qI64; int32 qI32; } qI;

  /*A space for a adding value maybe referred manually by pyAdd. */
  float yAdd;
  
  int8 setIntg, disableIntg, open; 
  int8 _sp_[1];   //at least 8 bit boundary

  /**The current output of the controller, hold if open is set. */
  float y;
  
  /**This value is only set in construction, should inform about the step time. */
  float Tstep;


} PIDf_Ctrl_emC_s;
//end::PIDf_Ctrl_emC[]



#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_PIDf_Ctrl_emC;
#endif

#ifndef ID_refl_PIDf_Ctrl_emC  //may be defined in *.reflOffs.h
#define ID_refl_PIDf_Ctrl_emC 0x0FC1
#endif


#define INIZ_PIDf_Ctrl_emC(THIZ, ID) { { INIZ_ObjectJc(THIZ, refl_PIDf_Ctrl_emC, ID)}, 0} 


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
 * @param openLoop_param: normally false, only true for tests. Then the y_y is not set, only ctrl_y.
 *           
 * @return false if par == null, true if initialized. 
 * @simulink init.
 */
extern_C bool init_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, Par_PIDf_Ctrl_emC_s* par);

/**set Limitation of PID controller 
 * @simulink Operation-FB.
 */
extern_C void setIntg_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float intg, bool set, bool hold, float* intg_y);

/**set Limitation of PID controller 
 * @simulink Operation-FB.
 */
extern_C void setLim_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float lim);

/**step of PID controller 
 */
extern_C void step_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float wx, float wxd);


/**Gets the y result. */
INLINE_emC float getY_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz) { return thiz->y; }

/**step of PID controller especially to use in a Simulink S-Function. 
 * Note: The S-Function needs the returned value as pointer.
 * @simulink Object-FB.
 */
INLINE_emC void stepY_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float wx, float wxd, float* y_y){
  step_PIDf_Ctrl_emC(thiz, wx, wxd);
  *y_y = thiz->y;
}


/**Offers a new parameter set for this controller. 
 * This operation can be called any time in any thread. 
 * @par null or reference to given parameter set, may be either immediately inside the Par_PIDf_Ctrl_emC FBlock
 *      or in a event data structure. The event data are freed or the parameter FBlock is unlocked
 *      in this routine for the possibility to reuse the location for new parameter or event preparation.
 *      If par == null this operation does nothing.  
 * @s imulink Operation-FB.
 */
//extern_C void param_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, ParFactors_PIDf_Ctrl_emC_s* parNew);


static inline void get_wxP_PID_ctrl(PIDf_Ctrl_emC_s const* thiz, float* y);

INLINE_emC void get_wxP_PID_ctrl(PIDf_Ctrl_emC_s const* thiz, float* y) { *y = thiz->wxP;  }


/**set Limitation of PID controller 
 * @simulink Operation-FB.
 */
extern_C void setIntg64_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float intg, bool set, bool hold, float* intg_y);

/**set Limitation of PID controller 
 * @simulink Operation-FB.
 */
extern_C void setLim64_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float lim);

/**step of PID controller 
 * @simulink Object-FB.
 */
extern_C void step64_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float wx, float x, float* y_y);




//tag::class_PIDf_Ctrl_emC[]
#if defined(DEF_CPP_COMPILE) && defined(__cplusplus)
class PIDf_Ctrl_emC : public PIDf_Ctrl_emC_s {

  /**Constructs.
   */
  public: PIDf_Ctrl_emC (int idObj, float Tstep) {
    CTOR_ObjectJc(&this->base.obj, this, sizeof(PIDf_Ctrl_emC_s), refl_PIDf_Ctrl_emC, idObj);  //should be initialized.
    ctor_PIDf_Ctrl_emC(&this->base.obj, Tstep); //the initialized ObjectJc as arguement.
  }

  /**Constructs as base class of any inherited controller.
   * @arg objectJc forces calling CTOR_ObjectJc(...) in the inherited class ctor.
   */
  protected: PIDf_Ctrl_emC ( ObjectJc* objectJc, float Tstep ) {
    ctor_PIDf_Ctrl_emC(&this->base.obj, Tstep); //the initialized ObjectJc as arguement.
  }


  public: void init(Par_PIDf_Ctrl_emC_s* par) { init_PIDf_Ctrl_emC(this, par); }
  
  public: void step ( float wx, float wxd){ step_PIDf_Ctrl_emC(this, wx, wxd); }

  public: float y ( float wx){ return getY_PIDf_Ctrl_emC(this); }

};
#endif
//end::class_PIDf_Ctrl_emC[]





#endif //__Ctrl__pid_Ctrl_h__
