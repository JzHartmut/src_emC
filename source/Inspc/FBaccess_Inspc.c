#include "FBaccess_Inspc_priv.h"
#include <stdio.h>
#include <stdlib.h>


void alloc_FBaccess_Inspc(FBaccess_Inspc** thizp, int nrofObjects){
  allocSetRoot_FBaccess_Inspc(thizp, nrofObjects, null);
}

void allocSetRoot_FBaccess_Inspc(struct FBaccess_Inspc_t** thizp, int nrofObjects, ObjectJc* rootInspc)
{
  FBaccess_Inspc* thiz = (FBaccess_Inspc*)malloc(sizeof(FBaccess_Inspc));
  memset(thiz, 0, sizeof(FBaccess_Inspc));

  FBaccessNode_Inspc* rootNode = (FBaccessNode_Inspc*)malloc(sizeof(FBaccessNode_Inspc));
  memset(rootNode, 0, sizeof(FBaccessNode_Inspc));

  ctor_FBaccessNode_Inspc(&rootNode->super, nrofObjects);

  if(rootInspc == null){ rootInspc = &rootNode->super; }
  ctor_FBaccess_Inspc(&thiz->super, rootNode, rootInspc);  //the rootNode is the root for the Inspector per default.  
   
  *thizp = thiz;

}

extern_C ClassJc const reflection_FBaccess_Inspc;


/**Constructs and starts the Inspector service for Function Block access with allocated memory from thizo. 
 * @param rootNode The root node for all FB access. Should be given and intialized.
 * @param rootInspc The root struct for all access. It can be the same as rootNode, it can be another struct. Should be given and initialized. 
 */
FBaccess_Inspc* ctor_FBaccess_Inspc(ObjectJc* thizo, FBaccessNode_Inspc* rootNode, ObjectJc* rootInspc)
{
  STACKTRC_ENTRY("ctor_FBaccess_Inspc");
  char sIp[30];
  FBaccess_Inspc* thiz = (FBaccess_Inspc*) thizo; 
  initReflection_ObjectJc(thizo, thizo, sizeof(FBaccess_Inspc_t), &reflection_FBaccess_Inspc, 0xf0);
  thiz->rootNode = rootNode;

  strcpy(sIp, "UDP:0.0.0.0:60092");
  

  init_ObjectJc(&thiz->theInspector.base.object, sizeof(thiz->theInspector), 0);
  ctorO_Inspector_Inspc(&thiz->theInspector.base.object, s0_StringJc(sIp), _thCxt);


  start_Inspector_Inspc_F(&thiz->theInspector, rootInspc, _thCxt); 

  STACKTRC_LEAVE;
  return thiz;
}


void free_FBaccess_Inspc(FBaccess_Inspc* thiz)
{
  STACKTRC_ENTRY("ctor_FBaccess_Inspc");
  shutdown_Inspector_Inspc(&thiz->theInspector, _thCxt);
  free(thiz->rootNode);
  free(thiz);
  STACKTRC_LEAVE;
}


void ptrRootNode_FBaccess_Inspc(FBaccess_Inspc* thiz, FBaccessNode_Inspc** p_node)
{ *p_node = thiz->rootNode;
}


