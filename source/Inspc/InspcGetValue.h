#ifndef __InspcGetValue_Inspc_h__
#define __InspcGetValue_Inspc_h__
#include <os_types_def.h>


/*@CLASS_C InspcGetValue_Inspc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct InspcGetValue_Inspc_t {
  
  /**Name in workspace. */
  char variableSimulink[32];

  /**If changed then get the path. */
  int triggerPathChanged;

  /**The path in reflection to get the value. */
  char const* path;

  /**Returned ident for getValueByIdent. */
  int32 ident;

} InspcGetValue_Inspc;



typedef struct InspcGetValue_Inspc_t* P_InspcGetValue_Inspc; 


void alloc_InspcGetValue_Inspc(P_InspcGetValue_Inspc* thizw, int32 nrVariable);


void get_InspcGetValue_Inspc(P_InspcGetValue_Inspc thiz, float* value);

void free_InspcGetValue_Inspc(P_InspcGetValue_Inspc thiz);



#endif // __traceWr_traceWr_h__
