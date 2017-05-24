#include "FBaccess_Inspc_priv.h"
#include <stdio.h>
#include <stdlib.h>

void alloc_FBaccess_Inspc_vorlaeufig_in_Simulink(FBaccess_Inspc** thizp, int nrofObjects){
  allocSetRoot_FBaccess_Inspc(thizp, nrofObjects, null,"UDP:0.0.0.0:60094");
}

void alloc_FBaccess_Inspc(FBaccess_Inspc** thizp, int nrofObjects, const char* sIp){
  allocSetRoot_FBaccess_Inspc(thizp, nrofObjects, null,sIp);
}

void allocSetRoot_FBaccess_Inspc(struct FBaccess_Inspc_t** thizp, int nrofObjects, ObjectJc* rootInspc, const char* sIp)
{
  FBaccess_Inspc* thiz = (FBaccess_Inspc*)malloc(sizeof(FBaccess_Inspc));
  memset(thiz, 0, sizeof(FBaccess_Inspc));

  FBaccessNode_Inspc* rootNode = (FBaccessNode_Inspc*)malloc(sizeof(FBaccessNode_Inspc));
  memset(rootNode, 0, sizeof(FBaccessNode_Inspc));

  ctor_FBaccessNode_Inspc(&rootNode->object, nrofObjects);

  if(rootInspc == null){ rootInspc = &rootNode->object; }
  ctor_FBaccess_Inspc(&thiz->object, rootNode, rootInspc,sIp);  //the rootNode is the root for the Inspector per default.  
   
  *thizp = thiz;

}

//Note: defined in the FBaccess_Inspc_refl.c
extern_C ClassJc const reflection_FBaccess_Inspc;
extern_C ClassJc const reflection_SimulationTime_Inspc;


/**Constructs and starts the Inspector service for Function Block access with allocated memory from thizo. 
 * @param rootNode The root node for all FB access. Should be given and intialized.
 * @param rootInspc The root struct for all access. It can be the same as rootNode, it can be another struct. Should be given and initialized. 
 */
FBaccess_Inspc* ctor_FBaccess_Inspc(ObjectJc* thizo, FBaccessNode_Inspc* rootNode, ObjectJc* rootInspc, const char* sIp)
{
  STACKTRC_ENTRY("ctor_FBaccess_Inspc");
  //char sIp[30];
  FBaccess_Inspc* thiz = (FBaccess_Inspc*) thizo; 
  initReflection_ObjectJc(thizo, thizo, sizeof(FBaccess_Inspc), &reflection_FBaccess_Inspc, 0xf0);
  thiz->rootNode = rootNode;
  thiz->object.isInitialized = 1;
  registerRefl_FBaccessNode_Inspc(rootNode, &thiz->simTime, "simTime", &reflection_SimulationTime_Inspc);
  //strcpy(sIp, "UDP:0.0.0.0:60092");
  

  init_ObjectJc(&thiz->theInspector.base.object, sizeof(thiz->theInspector), 0);
  ctorO_Inspector_Inspc(&thiz->theInspector.base.object, s0_StringJc(sIp), _thCxt);
  thiz->theInspector.base.object.isInitialized = 1;

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


void setTime_FBaccess_Inspc(FBaccess_Inspc* thiz, double seconds) {
  if(thiz !=null && thiz->rootNode !=null) {
    thiz->simTime.timeSim = seconds;
    thiz->simTime.timeShort = (int32)(seconds * 1000);  //1 ms step, time may be seconds of simulation.
  }
}


#include "FBaccess_Inspc_Refl.crefl"
