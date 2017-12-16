#ifndef __Service_Inspc_h__
#define __Service_Inspc_h__
#include <Inspc/DataNode_Inspc.h>
#include <InspcJ2c/Inspector_Inspc.h>
#include <Fwc/fw_Time.h>



extern_C ClassJc const reflection_SimTime_Inspc;


/*@CLASS_C Service_Inspc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

struct Service_Inspc_t;

typedef struct Service_Inspc_t
{ ObjectJc object;
  SimTime_Fwc simTime;
#ifndef __NoReflection__
  DataNode_Inspc* rootNode;  //only void* pointer
#endif//__NoReflection__

  Inspector_Inspc_s theInspector;
} Service_Inspc;




extern_C ClassJc const reflection_Service_Inspc;
extern_C ClassJc const reflection_SimulationTime_Inspc;


/**Ctor creates the socket and thread for Inspector service on target or simulink.
 * @simulink ctor
 */
Service_Inspc* ctor_Service_Inspc(Service_Inspc* thiz, float Tstep, StringJc sIp_param);


/**The step routine gets only the time from Simulation.
 * @simulink init
 */
char const* init_Service_Inspc(Service_Inspc* thiz, struct DataNode_Inspc_t* rootNode);

/**The terminate routine closes the thread and the Socket connection..
 * @simulink dtor
 */
void dtor_Service_Inspc(Service_Inspc* thiz);

/**The step routine gets only the time from Simulation.
 * @simulink Object-FB
 */
char const* step_Service_Inspc(struct Service_Inspc_t* thiz);



#endif  // __Service_Inspc_h__
