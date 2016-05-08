#ifndef __InspcTargetProxy_h__
#define __InspcTargetProxy_h__

#include <Jc/ObjectJc.h>
#include <Jc/ReflectionJc.h>
#include <Jc/ReflMemAccessJc.h>
#include <InspcJ2c/Inspector_Inspc.h>
#include <Ipc2C/InterProcessCommRxThread_Ipc.h>
#include <Ipc2C/InterProcessCommRx_Ifc_Ipc.h>
#include <Ipc/InterProcessComm.h>
#include <InspcTargetProxyTelg.h>


struct Inspector_Inspc_t;


typedef union TestUnion_t
{
	int32 val1, val2;
	struct
	{
    int32 b00000007:3;
		int32 b00003ff8:11;
		int32 b0007c000:5;  //uses bit 18..14, over 16-bit-border.
		int32 b00080000:1;
    int32 b7FF00000:11; 
    //one bit missing but the compiler uses the next word...
    int32 c00000007:3;
	};
}TestUnion;

  

/**The data of the Target proxy application itself. */
typedef struct Comm_InspcTargetProxy_t
{
  ObjectJc base;
  /**Tx buffer, this is the struct of the tx telegram to the target. */
  //AccessTxData_ReflMemAccessJc txData2target;
  TelgProxy2Target_Inspc_s txData2Target;

  MemC txData2TargetP;

  Address_InterProcessComm_s ipAddrTarget;

  
  /**Instanz zur Vermittlung des Receive-callback. */ 
  InterProcessCommRx_ifc_Ipc_s targetRx;

  /**Modul für Socketkommunikation mit dem eigentlichen Target. */
  InterProcessCommRxThread_Ipc_s* targetIpc;

  Inspector_Inspc_s theInspector;

  /**Management class for loading external reflection. */
  ExtReflectionJc_s extReflectionDsp;
  

} Comm_InspcTargetProxy_s;


void ctor_Comm_InspcTargetProxy(Comm_InspcTargetProxy_s* thiz);

/**The main data of the InspcTargetProxy-application, seen as root in the inspector. */
typedef struct Main_InspcTargetProxy_t
{ 
  ObjectJc object;

  void* _DSP_;

  Comm_InspcTargetProxy_s proxy;



} Main_InspcTargetProxy_s;


extern struct ClassJc_t const reflection_Main_InspcTargetProxy_s;

#endif //__InspcTargetProxy_h__
