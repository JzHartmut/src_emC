#ifndef __Wait_Inspc_h__
#define __Wait_Inspc_h__
#include <os_types_def.h>
#include <Jc/ObjectJc.h>
#include <Jc/ReflectionJc.h>
#include <Fwc/fw_String.h>








typedef struct Wait_Inspc_t
{ ObjectJc base;
  
  int32 isWaiting;

  int32 volatile timeWait;  

} Wait_Inspc;

/**Allocate and construct. */
Wait_Inspc* create_Wait_Inspc();


void ctor_Wait_Inspc(Wait_Inspc* thiz);


/**Register it in a FBaccessNode_Inspc, invoke one time after create. */
bool registerReflection_Wait_Inspc(Wait_Inspc* thiz, struct FBaccessNode_Inspc_t* reflNode);

void step_Wait_Inspc(Wait_Inspc volatile* thiz);

void free_Wait_Inspc(Wait_Inspc* thiz);



#endif //__Wait_Inspc_h__
