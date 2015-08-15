#include "Inspc/InspcGetValue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __Simulink__
  #undef int32_T
  #undef INT32_T
  #undef uint32_T
  #undef UINT32_T
  #include <mex.h>
#endif


void alloc_InspcGetValue_Inspc(P_InspcGetValue_Inspc* thizw, int32 nrVariable){
  P_InspcGetValue_Inspc thiz = (P_InspcGetValue_Inspc)malloc(sizeof(InspcGetValue_Inspc));
  memset(thiz, 0, sizeof(InspcGetValue_Inspc));
  sprintf(thiz->variableSimulink, "InspcGetValue_%d", nrVariable);
  *thizw = thiz;
}


void get_InspcGetValue_Inspc(P_InspcGetValue_Inspc thiz, int32 trigger, float* value) {
  if(trigger != thiz->triggerPathChanged) {
    #ifdef __Simulink__
      mxArray const* mxPath = mexGetVariablePtr("base", thiz->variableSimulink);
      thiz->path = mxArrayToString(mxPath);
    #endif
  }
}


void free_InspcGetValue_Inspc(P_InspcGetValue_Inspc thiz){
  free(thiz);
}