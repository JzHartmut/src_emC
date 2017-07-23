#include <Inspc/Service_Inspc.h>

Service_Inspc* ctor_Service_Inspc(Service_Inspc* thiz/*, StringJc sIp*/, float Tstep)
{
  STACKTRC_ENTRY("ctor_FBaccess_Inspc");
  //char sIp[30];
  //Service_Inspc* thiz = (Service_Inspc*) thiz; 
  initReflection_ObjectJc(&thiz->object, thiz, sizeof(Service_Inspc), &reflection_Service_Inspc, 0xf0);
  //ctor_DataNode_Inspc(&thiz->rootNode, 50);
  //strcpy(sIp, "UDP:0.0.0.0:60092");
  

  init_ObjectJc(&thiz->theInspector.base.object, sizeof(thiz->theInspector), 0);


  STACKTRC_LEAVE;
  return thiz;

}



char const* init_Service_Inspc(Service_Inspc* thiz, StringJc sIp_param, DataNode_Inspc* rootNode)
{
  if(isInitialized_ObjectJc(&thiz->object) ==0 && rootNode !=null) {
    STACKTRC_ENTRY("step_Service_Inspc");
    setInitialized_ObjectJc(&thiz->object);  //Note: set it firstly to prevent twice initialization on thread switch in start_
    ctorO_Inspector_Inspc(&thiz->theInspector.base.object, sIp_param, _thCxt);
    setInitialized_ObjectJc(&thiz->theInspector.base.object);
    thiz->rootNode = rootNode;
    registerRefl_DataNode_Inspc(rootNode, &thiz->simTime, "simTime", &reflection_SimTime_Inspc);
    start_Inspector_Inspc_F(&thiz->theInspector, &rootNode->object, _thCxt); 
    STACKTRC_LEAVE;
  }
  return null;
}


void terminate_Service_Inspc(Service_Inspc* thiz)
{
  terminate_Inspector_Inspc(&thiz->theInspector);
}


char const* step_Service_Inspc(Service_Inspc* thiz)
{ //left empty, nothing to do.
  thiz->simTime.timeShort +=1;
  return null;
}


