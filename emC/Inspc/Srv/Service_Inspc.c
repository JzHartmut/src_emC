#include <applstdef_emC.h>
#ifdef DEF_ClassJc_Vtbl
//NOTE: This file can only be used with full capability of emC, not for simple applications.
//      It is only necessary to full including the Inspc symbolic access on target

#include "emc/Inspc/Srv/Service_Inspc.h"


#include "genRefl/Service_Inspc.crefl"

Service_Inspc* ctor_Service_Inspc(Service_Inspc* thiz, float Tstep, StringJc sIp)
{
  STACKTRC_ENTRY("ctor_FBaccess_Inspc");
  iniz_ObjectJc(&thiz->object, thiz, sizeof(Service_Inspc), &refl_Service_Inspc, 0xf0);
  //init_ObjectJc(&thiz->theInspector.base.object, sizeof(thiz->theInspector), 0);
  ctorO_Inspector_Inspc(&thiz->theInspector.base.object, sIp, _thCxt);
  STACKTRC_LEAVE;
  return thiz;

}



bool init_Service_Inspc(Service_Inspc* thiz, struct DataNode_Inspc_t* rootNode)
{
  if(isInitialized_ObjectJc(&thiz->object) ==0 && rootNode !=null) {
    STACKTRC_ENTRY("step_Service_Inspc");
    setInitialized_ObjectJc(&thiz->object);  //Note: set it firstly to prevent twice initialization on thread switch in start_
    //see ctor: ctorO_Inspector_Inspc(&thiz->theInspector.base.object, sIp_param, _thCxt);
    thiz->rootNode = rootNode;
    registerRefl_DataNode_Inspc(rootNode, &thiz->simTime, "simTime", &refl_SimTime_emC);
    //TEST  
    ClassJc const* rootClazz = getClass_ObjectJc(&rootNode->base.object);
    MemSegmJc rootAddr;
    setAddrSegm_MemSegmJc(rootAddr, rootNode, 0);
    start_Inspector_Inspc_F(&thiz->theInspector, rootClazz, rootAddr, _thCxt); 
    STACKTRC_RETURN true;
  }
  else {
    return isInitialized_ObjectJc(&thiz->object);  //true if initialized.
  }
}


void dtor_Service_Inspc(Service_Inspc* thiz)
{
  if(isInitialized_ObjectJc(&thiz->object)) {
    dtor_Inspector_Inspc(&thiz->theInspector);
  }
}


void step_Service_Inspc(Service_Inspc* thiz, uint16* state_y, uint16* ctCheck_y)
{ //left empty, nothing to do.
  thiz->simTime.timeShort +=1;
  if (state_y != null) { *state_y = thiz->theInspector.comm.state; }
  if (ctCheck_y != null) { *ctCheck_y = thiz->theInspector.comm.ctCheck; }
  return;
}

#endif //def DEF_ClassJc_Vtbl

