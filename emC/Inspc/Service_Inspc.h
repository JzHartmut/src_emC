#ifndef __Service_Inspc_h__
#define __Service_Inspc_h__
#include <emC/Inspc/DataNode_Inspc.h>
#include <emC/Inspc/J2c/Inspector_Inspc.h>
#include <emC/Base/Time_emC.h>



//extern_C ClassJc const refl_SimTime_Inspc;


/*@CLASS_C Service_Inspc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

struct Service_Inspc_t;

typedef struct Service_Inspc_t
{ ObjectJc object;
  SimTime_emC simTime;
#ifndef __NoReflection__
  DataNode_Inspc* rootNode;  //only void* pointer
#endif//__NoReflection__

  Inspector_Inspc_s theInspector;
} Service_Inspc;




extern_C ClassJc const refl_Service_Inspc;
extern_C ClassJc const refl_SimulationTime_Inspc;


/**Ctor creates the socket and thread for Inspector service on target or simulink.
 * @simulink ctor
 */
Service_Inspc* ctor_Service_Inspc(Service_Inspc* thiz, float Tstep, StringJc sIp_param);


/**The step routine gets only the time from Simulation.
 * @simulink init
 */
bool init_Service_Inspc(Service_Inspc* thiz, struct DataNode_Inspc_t* rootNode);

/**The terminate routine closes the thread and the Socket connection..
 * @simulink dtor
 */
void dtor_Service_Inspc(Service_Inspc* thiz);

/**The step routine gets only the time from Simulation.
 * @simulink Object-FB
 */
void step_Service_Inspc(struct Service_Inspc_t* thiz, uint16* state_y, uint16* ctCheck_y);



#endif  // __Service_Inspc_h__
