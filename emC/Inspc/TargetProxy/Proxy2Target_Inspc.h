#ifndef __Inspc__Proxy2Target_Inspc_h__
#define __Inspc__Proxy2Target_Inspc_h__
#include <emC/InspcTargetSimple/IfcTargetProxy_Inspc.h>
#include <emC/OSAL/os_time.h>


#if 0 //idea of a flexible force communication routine.
//It is not necessary because the only one implementation may use a static linked routine, see 
/**Operation to force communcation*/
typedef void OperForceComm_Proxy2Target_Inspc();

extern_C char const* const signature_ForceComm_Proxy2Target_Inspc;


typedef struct ForceComm_Proxy2Target_Inspc_T {
  char const* const signature;
  OperForceComm_Proxy2Target_Inspc * operForceComm;
} ForceComm_Proxy2Target_Inspc_s;
#endif

/**This are the relevant core data for a communication with a target.
 * It is used for the routine [[get_Proxy2Target_Inspc(...)]]
 * which is called in [[accessTarget_Inspc(...)]] as specific implementation from the Inspector sources.
 * The way to accessing the target is not the point of interest here, only the data exchange. 
 * Hence this routine is universal for the InspcTargetProxy concept, 
 * also able to use in a communication processer immediately coupled with a DSP processor (via DualPortMemory, FPGA, SPI etc).
 */
typedef struct Proxy2Target_Inspc_t
{
  ObjectJc object;
  
  /**Gotten reference to the exchange data range. */
  TelgTarget2Proxy_Inspc_s* target2proxy;

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

  //align-8
  int16 xxbReqPending;

  int32 ms_LastTimeCommunication;

  int32 ms_LastTimeTx;

  /**timeout, if 0 then wait for ever for answer, only for debug. */
  int32 ms_timeout;


} Proxy2Target_Inspc;



Proxy2Target_Inspc* ctor_Proxy2Target_Inspc(ObjectJc* thizo, ThCxt* _tCxt);

/**Gets the info from the target. */
int32 get_Proxy2Target_Inspc(Proxy2Target_Inspc* thiz, Cmd_InspcTargetProxy_e cmd, uint32 address, int32 input);


/**This routine should be provided by the application
* to force: start or execute the communication with the target.
* It will be invoked in the Inspc core sources.
* May be the communication is executed in another thread.
* Then this routine should contain the wait and notify with timeout.
* The routine can block for a small time peace, but not for longer.
* The timeout should be in range of a few milliseconds,
* otherwise the whole Inspector access blocks.
* @return true if successfully, false: Communication failse.
*/
extern_C bool forceComm_Proxy2Target_Inspc(Proxy2Target_Inspc* thiz, Cmd_InspcTargetProxy_e cmd);




#endif //__Inspc__Proxy2Target_Inspc_h__
