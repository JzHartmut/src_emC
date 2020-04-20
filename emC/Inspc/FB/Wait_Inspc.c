#include "Wait_Inspc.h"
#include <emC/Inspc/DataNode_Inspc.h>
#include <emC/OSAL/os_time.h>
#include <stdlib.h>
#include <string.h>

//generated reflection
#include "emC/Inspc/FB/genRefl/Wait_Inspc.crefl"

Wait_Inspc* create_Wait_Inspc()
{ Wait_Inspc* thiz = null;
  thiz = (Wait_Inspc*)malloc(sizeof(Wait_Inspc));
  if(thiz !=null) {
    memset(thiz, 0, sizeof(Wait_Inspc));
  }
  return thiz;
}



void ctor_Wait_Inspc(Wait_Inspc* thiz)
{
  thiz->stepsTillWait = 1;
}



bool registerReflection_Wait_Inspc(Wait_Inspc* thiz, struct DataNode_Inspc_t* reflNode)
{ return registerRefl_DataNode_Inspc(reflNode, thiz, "wait", &reflection_Wait_Inspc);
}


void init_Wait_Inspc(Wait_Inspc* thiz, struct DataNode_Inspc_t* reflNode)
{ registerRefl_DataNode_Inspc(reflNode, thiz, "wait", &reflection_Wait_Inspc);
  setInitialized_ObjectJc(&thiz->base);
}


 
void ctor_TillWait_Wait_Inspc(Wait_Inspc* thiz, float Tstep, int32 stepsTillFirstWait, int32 delay_ms)
{
  iniz_ObjectJc(&thiz->base, thiz, sizeof(Wait_Inspc), &reflection_Wait_Inspc, 0x0);
  thiz->stepsTillWait = stepsTillFirstWait;
  thiz->delay_ms = delay_ms;
}


void step_Wait_Inspc(Wait_Inspc volatile* thiz)
{
  if(thiz->stepsTillWait < 0){
    if(thiz->delay_ms >0) {
      os_delayThread(thiz->delay_ms);
    } //else  don't wait.
  }
  else {
    if(--thiz->stepsTillWait == 0) {
      if(thiz->delay_ms == 0) {
        while(thiz->stepsTillWait ==0) {  //only an access via inspector can set stepsTillWait to !=0
          thiz->isWaiting = 1;
          os_delayThread(10);
        }
        thiz->isWaiting = 0;  //stepsTillWait is either >0, then full speed till wait point, or <0 then less speed.
      }
      //else: next step is <0, less speed.
    } 
    // else: run with full speed if stepsTillWait >0
  }
}





void free_Wait_Inspc(Wait_Inspc* thiz)
{
  if(thiz !=null){
    free(thiz);
  }
}


