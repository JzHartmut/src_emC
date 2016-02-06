#include "Wait_Inspc.h"
#include <Inspc/FBaccess_Inspc.h>
#include <stdlib.h>
#include <string.h>

//generated reflection
#include "Wait_Inspc_Refl.crefl"

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
  thiz->timeWait = 1;
}



bool registerReflection_Wait_Inspc(Wait_Inspc* thiz, struct FBaccessNode_Inspc_t* reflNode)
{ return registerRefl_FBaccessNode_Inspc(reflNode, thiz, "wait", &reflection_Wait_Inspc);
}



void step_Wait_Inspc(Wait_Inspc volatile* thiz)
{
  if(thiz->timeWait < 0) return;  //don't wait
  else {
    if(--thiz->timeWait == 0) {
      while(thiz->timeWait ==0) {
        thiz->isWaiting = 1;
      }
    }
    thiz->isWaiting = 0;
  }
}





void free_Wait_Inspc(Wait_Inspc* thiz)
{
  if(thiz !=null){
    free(thiz);
  }
}


