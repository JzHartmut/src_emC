#ifndef __Inspc__Proxy2Target_Inspc_h__
#define __Inspc__Proxy2Target_Inspc_h__
#include <emC/InspcTargetSimple/IfcTargetProxy_Inspc.h>
#include <emC/OSAL/os_time.h>

typedef struct Proxy2Target_Inspc_t
{
  ObjectJc object;
  
  /**Gotten reference to the exchange data range. */
  TelgTarget2Proxy_Inspc_s const* target2proxy;

  /**Gotten reference to the exchange data range. */
  TelgProxy2Target_Inspc_s* proxy2target;

  /**The last sequence number of a command. If the seqnr in the telg is changed, a new command was received.
  * Note: The trigger for new data is not related to any event, but with polling the seqnr.
  * That approach is more simple, needs less organization effort.
  */
  //int16 seqnrRxLast;

  int16 seqnrTxTarget;

  int16 errorMsgTarget;

  int16 lifeCtTarget;

  int16 channelTarget;

  int32 ms_LastTimeCommunication;


} Proxy2Target_Inspc;



Proxy2Target_Inspc* ctor_Proxy2Target_Inspc(ObjectJc* thizo, ThCxt* _tCxt);

/**Gets the info from the target. */
int32 get_Proxy2Target_Inspc(Proxy2Target_Inspc* thiz, Cmd_InspcTargetProxy_e cmd, uint32 address, int32 input);

#endif //__Inspc__Proxy2Target_Inspc_h__
