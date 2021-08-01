#ifndef HGUARD_FuncGen_Ctrl_emC
#define HGUARD_FuncGen_Ctrl_emC
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <emC/Ctrl/Angle_Ctrl_emC.h>

typedef struct FuncGen_Ctrl_emC_T
{
  union { ObjectJc obj; } base;
  /**Step time for one calculation*/
  float Tstep; 

  /**Parametrized frequency and magnitude and offset. */
  float fq, magn, offs;

  union 
  { int32 i32; 
    struct 
    { uint32 isParametrized : 1;
      uint32 square: 1;
      uint32 cos: 1;
    };
  } type;

  float y;

  float* yAddr;

  int32 angle;

  /**Add angle per step*/
  int32 dangle;


} FuncGen_Ctrl_emC_s;

#ifndef DEF_REFLECTION_NO
  extern_C ClassJc const refl_FuncGen_Ctrl_emC;
#endif

#ifndef ID_refl_FuncGen_Ctrl_emC  //may be defined in *.reflOffs.h
  #define ID_refl_FuncGen_Ctrl_emC 0x0FC6
#endif


/**
 * @simulink ctor.
 */
extern_C FuncGen_Ctrl_emC_s* ctor_FuncGen_Ctrl_emC(ObjectJc* othiz, float Tstep);

/**Internal param routine called also if isParametrized is detected as 0 changed by Inspector. */
extern_C void doparam_FuncGen_Ctrl_emC(FuncGen_Ctrl_emC_s* thiz);


/**
 * @simulink Operation-FB.
 */
inline void param_FuncGen_Ctrl_emC(FuncGen_Ctrl_emC_s* thiz, float fq, float magn, int32 type) 
{
  thiz->fq = fq; thiz->magn = magn;
  thiz->type.i32 = type; 
  doparam_FuncGen_Ctrl_emC(thiz);
}



/**
 * @simulink Object-FB, no-thizStep.
 */
inline void step_FuncGen_Ctrl_emC(FuncGen_Ctrl_emC_s* thiz, float* y_y) {

  thiz->angle += thiz->dangle;
  if(thiz->type.isParametrized ==0) {
    doparam_FuncGen_Ctrl_emC(thiz);
  }
  if(thiz->type.cos) 
  {
    float cosval = cosf(int32_to_rad(thiz->angle));
    *y_y = thiz->y = cosval * thiz->magn + thiz->offs;
  } 
  else if(thiz->type.square) 
  { 
    *y_y = thiz->y = thiz->magn + thiz->offs * (thiz->angle>=0 ? 1.0f: -1.0f);
  }
  else 
  { //do nothing, dont change output. Free for manual setting
    *y_y = thiz->y;
  }
}



#endif //HGUARD_FunGen_Ctrl_emC
