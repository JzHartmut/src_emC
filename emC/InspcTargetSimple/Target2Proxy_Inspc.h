#ifndef __Inspc__Target2Proxy_Inspc_h__
#define __Inspc__Target2Proxy_Inspc_h__
#include <emC/InspcTargetSimple/IfcTargetProxy_Inspc.h>


typedef struct Target2Proxy_Inspc_t
{
  ObjectJc object;

  /**Gotten reference to the exchange data range. */
  TelgTarget2Proxy_Inspc_s* target2proxy;

  /**Gotten reference to the exchange data range. */
  TelgProxy2Target_Inspc_s const* proxy2target;

  /**The last sequence number of a command. If the seqnr in the telg is changed, a new command was received.
  * Note: The trigger for new data is not related to any event, but with polling the seqnr.
  * That approach is more simple, needs less organization effort.
  */
  int16 seqnrLast;

  int16 errorMsg;

  int16 lifeCt;


} Target2Proxy_Inspc;





/**In the user space the following array should be defined. It holds the reference to all offset arrays.
* Such an array is generated via the zbnfjax/jzTc/Cheader2Refl.jztxt.cmd reflection generator.
* The label is defined here to clarify the type especially for C++ compilation, both should have the same declaration.
*/
extern ClassJc const* const reflectionOffsetArrays[];

void step_Target2Proxy_Inspc(Target2Proxy_Inspc* thiz, void const* mainData
  , int32 const* reflectionOffset_MainData, ClassJc const* const* reflectionOffsetArrays);



#endif //__Inspc__Target2Proxy_Inspc_h__
