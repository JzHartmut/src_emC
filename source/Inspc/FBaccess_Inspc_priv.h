#ifndef __FBaccess_Inspc_priv_h__
#define __FBaccess_Inspc_priv_h__

#include <Inspc/FBaccess_Inspc.h>
#include <InspcJ2c/Inspector_Inspc.h>
#include <Fwc/objectBaseC.h>
#include <Jc/ReflectionJc.h>

#include <Inspc/DataNode_Inspc.h>

typedef struct SimulationTime_Inspc_t
{
  int32 timeShort;

  double timeSim;

} SimulationTime_Inspc;





typedef struct FBaccess_Inspc_t
{ ObjectJc object;
  DataNode_Inspc* rootNode;
  SimulationTime_Inspc simTime;
  Inspector_Inspc_s theInspector;
} FBaccess_Inspc;



#endif //__FBaccess_Inspc_priv_h__
