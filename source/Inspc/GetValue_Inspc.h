#ifndef __InspcGetValue_Inspc_h__
#define __InspcGetValue_Inspc_h__
#include <applstdefJc.h>

struct DataNode_Inspc_t;

/*@CLASS_C GetValue_Inspc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct GetValue_Inspc_t {
  
  ObjectJc object;
  /**Name in workspace. */
  //char variableSimulink[32];

  /**If changed then get the path. */
  //int triggerPathChanged;

  /**The path in reflection to get the value. */
  //StringJc path;

  /**Returned ident for getValueByIdent. */
  //int32 ident;

  int32 statusNotFound;

  int32* addr[6];


} GetValue_Inspc;




/**
 * @simulink Sfunc
 */
void ctor_GetValue_Inspc(GetValue_Inspc* thiz, float Tstep);


/**
 * @simulink Sfunc
 */
void init_GetValue_Inspc(GetValue_Inspc* thiz
  , StringJc path1_param, StringJc path2_param, StringJc path3_param, StringJc path4_param
  , StringJc path5_param, StringJc path6_param
  , struct DataNode_Inspc_t* inspcNode, int32 ok)
;

/**
 * @simulink Sfunc
 */
void get_GetValue_Inspc(GetValue_Inspc* thiz, int32* statusNotFound_y
  , float* val1_y, float* val2_y, float* val3_y, float* val4_y, float* val5_y, float* val6_y);



#endif // __InspcGetValue_Inspc_h__
