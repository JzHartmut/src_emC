#include <Inspc/Service_Inspc.h>

Service_Inspc* ctor_Service_Inspc(Service_Inspc* thiz, float Tstep, StringJc sIp)
{
  STACKTRC_ENTRY("ctor_FBaccess_Inspc");
  initReflection_ObjectJc(&thiz->object, thiz, sizeof(Service_Inspc), &reflection_Service_Inspc, 0xf0);
  //init_ObjectJc(&thiz->theInspector.base.object, sizeof(thiz->theInspector), 0);
  ctorO_Inspector_Inspc(&thiz->theInspector.base.object, sIp, _thCxt);
  STACKTRC_LEAVE;
  return thiz;

}



char const* init_Service_Inspc(Service_Inspc* thiz, /*StringJc sIp_param, */DataNode_Inspc* rootNode)
{
  if(isInitialized_ObjectJc(&thiz->object) ==0 && rootNode !=null) {
    STACKTRC_ENTRY("step_Service_Inspc");
    setInitialized_ObjectJc(&thiz->object);  //Note: set it firstly to prevent twice initialization on thread switch in start_
    //see ctor: ctorO_Inspector_Inspc(&thiz->theInspector.base.object, sIp_param, _thCxt);
    thiz->rootNode = rootNode;
    registerRefl_DataNode_Inspc(rootNode, &thiz->simTime, "simTime", &reflection_SimTime_Inspc);
    //TEST  
    start_Inspector_Inspc_F(&thiz->theInspector, &rootNode->object, _thCxt); 
    STACKTRC_LEAVE;
  }
  return null;
}


void dtor_Service_Inspc(Service_Inspc* thiz)
{
  if(isInitialized_ObjectJc(&thiz->object)) {
    dtor_Inspector_Inspc(&thiz->theInspector);
  }
}


char const* step_Service_Inspc(Service_Inspc* thiz)
{ //left empty, nothing to do.
  thiz->simTime.timeShort +=1;
  return null;
}


