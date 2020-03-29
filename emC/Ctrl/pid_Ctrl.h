#ifndef __Ctrl__pid_Ctrl_h__
#define __Ctrl__pid_Ctrl_h__

#include "emC/base/Object_emC.h"

/**Parameter of PID controller 
 * @simulink bus.
 */
typedef struct Par_PID_Ctrl_t
{

  union { ObjectJc obj; } base;

  float kP;
  
  float Tn;
  
  float Td;
  
  float T1d;

  float lim;

  /**If set then changes from outside are disabled. For Inspector access. */
  int32 man: 1;

  int32 limPbeforeD: 1;

} Par_PID_Ctrl_s;



/**ctor of PID controller
* @simulink ctor.
*/
Par_PID_Ctrl_s* ctor_Par_PID_Ctrl(ObjectJc* othiz, float Tstep);

/**step of PID controller
* @simulink Object-FB, no-thizStep.
*/
void set_Par_PID_Ctrl(Par_PID_Ctrl_s* thiz, float k, float lim, float Tn_param, float Td_param, float Tsd_param, bool* man_y);


/**Internal paramter depending factors. */
typedef struct Internal_PID_Ctrl_t {
  
  /**Factor kP for conversion to int32. */
  //float fP;
  
  /**Smoothing time for D-Part.*/
  float fTsD;

  /**Factor for D-Part including kP and Transformation to int32. */
  float fD;

  /**Factor for wxP for Integrator adding. */
  int64 fI;

  /**Factor from float-x to int64 and to float-y-scale. */
  float fIx, fIy;
} Internal_PID_Ctrl;


/**Main data of PID controller 
 * @simulink no-bus.
 */
typedef struct PID_Ctrl_t
{
  union { ObjectJc obj; } base;

  Par_PID_Ctrl_s* par;
  
  float Tstep;

  /**Smoothed differential. */
  float dwxP;

  /**Stored for D-part, to view input. */
  float wxP;

  /**Stored for D-part, to view input. */
  float wxPD;

  /**To view output. It is the same value as y_y arg of [[step_PID_Ctrl(...)]]. */
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

  /**Reference to the used internal factors. One of _internal[0] or ~[1]*/
  Internal_PID_Ctrl* f;

  Internal_PID_Ctrl _internal[2];


} PID_Ctrl_s;




/**ctor of PID controller 
 * @simulink ctor.
 */
PID_Ctrl_s* ctor_PID_Ctrl(ObjectJc* othiz, float Tstep);

/**init of PID controller
 * @param par the parameter Object, should be not null
 * @return false if par == null, true if initialized. 
 * @simulink init.
 */
bool init_PID_Ctrl(PID_Ctrl_s* thiz, Par_PID_Ctrl_s* par);

/**step of PID controller 
 * @simulink Object-FB.
 */
void step_PID_Ctrl(PID_Ctrl_s* thiz, float wx, float* y_y);

/**Takes new parameter and re-calculates internal values.
 * This routine is also called on [[init_PID_Ctrl(...)]]. 
 * @simulink Operation-FB, step-in.
 */
void reparam_PID_Ctrl(PID_Ctrl_s* thiz);


inline void get_wxP_PID_ctrl(PID_Ctrl_s* thiz, float* y) { *y = thiz->wxP;  }

#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
class PID_Ctrl : private PID_Ctrl_s, public ObjectifcBaseJcpp {

  PID_Ctrl(ObjectJc* othiz, float Tstep){ 
    init_ObjectJc(&this->base.obj, sizeof(PID_Ctrl_s), 0);  //should be initialized.
    ctor_PID_Ctrl(&this->base.obj, Tstep); //the initialized ObjectJc as arguement.
  }

  public: virtual ObjectJc* toObject(){ return &this->base.obj;}

  public: void init(Par_PID_Ctrl_s* par) { init_PID_Ctrl(this, par); }
  
  public: void step ( float wx, float* y_y){ step_PID_Ctrl(this, wx, y_y); }

  public: void reparam(Par_PID_Ctrl_s* par){ reparam_PID_Ctrl(this, par); }


};
#endif


#endif //__Ctrl__pid_Ctrl_h__
