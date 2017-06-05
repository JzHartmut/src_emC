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
  int triggerPathChanged;

  /**The path in reflection to get the value. */
  StringJc path;

  /**Returned ident for getValueByIdent. */
  int32 ident;

  int32* addr;

} GetValue_Inspc;




/**
 * @simulink Sfunc
 */
void ctor_GetValue_Inspc(GetValue_Inspc* thiz);


/**
 * @simulink Sfunc
 */
void init_GetValue_Inspc(GetValue_Inspc* thiz, StringJc path_param, struct DataNode_Inspc_t* inspcNode);


/**
 * @simulink Sfunc
 */
void get_GetValue_Inspc(GetValue_Inspc* thiz, float* value_y);



#endif // __traceWr_traceWr_h__
