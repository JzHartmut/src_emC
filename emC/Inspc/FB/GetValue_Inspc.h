#ifndef __InspcGetValue_Inspc_h__
#define __InspcGetValue_Inspc_h__
#include <applstdef_emC.h>

struct DataNode_Inspc_t;

/*@CLASS_C GetValue_Inspc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct GetValue_Inspc_t {
  
  ObjectJc object;

  int32 statusNotFound;

  int32* addr[6];


} GetValue_Inspc;




/**
 * @simulink ctor
 */
void ctor_GetValue_Inspc(GetValue_Inspc* thiz, float Tstep);


/**
 * @simulink init
 */
bool init_GetValue_Inspc(GetValue_Inspc* thiz
  , StringJc path1_param, StringJc path2_param, StringJc path3_param, StringJc path4_param
  , StringJc path5_param, StringJc path6_param
  , int32 ok, ObjectJc* inspcNode)
;

/**
 * @simulink Object-FB, no-thizInit, no-thizStep.
 */
void get_GetValue_Inspc(GetValue_Inspc* thiz
  , float* val1_y, float* val2_y, float* val3_y, float* val4_y, float* val5_y, float* val6_y
  , int32* statusNotFound_y);



#endif // __InspcGetValue_Inspc_h__
