#ifndef __Ctrl__pid_Ctrl_h__
#define __Ctrl__pid_Ctrl_h__

//#include "emC/Base/Object_emC.h"
#include <applstdef_emC.h>

/**Parameter of PID controller 
 * @simulink bus.
 */
typedef struct Par_PIDf_Ctrl_emC_T
{

  union { ObjectJc obj; } base;

  /**for debugging and check: The used step time for calcualation of the factors. */
  float Tstep;

  /**Primary and used parameter: P-gain. */
  float kP;
  
  /**Primary parameter: Nachstellzeit. used: fI. */
  float Tn;
  
  float Td;
  
  float T1d;

  float lim;

  /**Internal paramter depending factors. */
  struct Internal_PIDf_Ctrl_emC_t {

    /**Smoothing time for D-Part.*/
    float fTsD;

    /**Factor for D-Part including kP and Transformation to int32. */
    float fD;

    /**Factor for wxP for Integrator adding. */
    int64 fI;

    /**Factor from float-x to int64 and to float-y-scale. */
    float fIx, fIy;

    int dbgct_reparam;
  } i;


  /**If set then changes from outside are disabled. For Inspector access. */
  int man: 1;

  int limPbeforeD: 1;

} Par_PIDf_Ctrl_emC_s;



/**ctor of PID controller
* @simulink ctor.
*/
extern_C Par_PIDf_Ctrl_emC_s* ctor_Par_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep);

/**step of PID controller
* @simulink Object-FB, no-thizStep.
*/
extern_C void set_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz, float kP, float lim, float Tn_param, float Td_param, float Tsd_param, bool* man_y);

/**Takes new parameter and re-calculates internal values.
 * This routine is also called on [[init_PIDf_Ctrl_emC(...)]].
 * @simulink Operation-FB, step-in.
 */
extern_C void reparam_Par_PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s* thiz);



/**Main data of PID controller 
 * @simulink no-bus.
 */
typedef struct PIDf_Ctrl_emC_t
{
  union { ObjectJc obj; } base;

  Par_PIDf_Ctrl_emC_s* par;
  
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




/**ctor of PID controller 
 * @simulink ctor.
 */
extern_C PIDf_Ctrl_emC_s* ctor_PIDf_Ctrl_emC(ObjectJc* othiz, float Tstep);

/**init of PID controller
 * @param par the parameter Object, should be not null
 * @return false if par == null, true if initialized. 
 * @simulink init.
 */
extern_C bool init_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, Par_PIDf_Ctrl_emC_s* par);

/**step of PID controller 
 * @simulink Object-FB.
 */
extern_C void step_PIDf_Ctrl_emC(PIDf_Ctrl_emC_s* thiz, float wx, float* y_y);

extern_C void get_wxP_PID_ctrl(PIDf_Ctrl_emC_s const* thiz, float* y);

INLINE_emC void get_wxP_PID_ctrl(PIDf_Ctrl_emC_s const* thiz, float* y) { *y = thiz->wxP;  }

#if defined(DEF_CPP_COMPILE) && defined(__cplusplus)
class PIDf_Ctrl_emC : public PIDf_Ctrl_emC_s { //, public ObjectifcBaseJcpp {

  public: PIDf_Ctrl_emC(){
    iniz_ObjectJc(&this->base.obj, thiz, sizeof(PIDf_Ctrl_emC_s), &refl_PIDf_Ctrl_emC, 0);  //should be initialized.
    ctor_PIDf_Ctrl_emC(&this->base.obj, 0.1234f); //the initialized ObjectJc as arguement.
  }

  public: PIDf_Ctrl_emC(Par_PIDf_Ctrl_emC_s const* par){
    iniz_ObjectJc(&this->base.obj, thiz, sizeof(PIDf_Ctrl_emC_s), &refl_PIDf_Ctrl_emC, 0);  //should be initialized.
    ctor_PIDf_Ctrl_emC(&this->base.obj, Tstep); //the initialized ObjectJc as arguement.
  }

  public: virtual ObjectJc* toObject(){ return &this->base.obj;}

  public: void init(Par_PIDf_Ctrl_emC_s* par) { init_PIDf_Ctrl_emC(this, par); }
  
  public: void step ( float wx, float* y_y){ step_PIDf_Ctrl_emC(this, wx, y_y); }

  //public: void reparam(Par_PIDf_Ctrl_emC_s* par){ reparam_PIDf_Ctrl_emC(this, par); }


};
#endif


#endif //__Ctrl__pid_Ctrl_h__
