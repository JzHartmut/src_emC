#ifndef __InspcTargetProxy_h__
#define __InspcTargetProxy_h__

#include <emC/Jc/ObjectJc.h>
#include <emC/Jc/ReflectionJc.h>
#include <emC/Jc/ReflMemAccessJc.h>
#include <emC/Inspc/J2c/Inspector_Inspc.h>
#include <emC/Ipc2C/InterProcessCommRxThread_Ipc.h>
#include <emC/Ipc2C/InterProcessCommRx_Ifc_Ipc.h>
#include <emC/Ipc/InterProcessComm.h>
#include <emC/InspcTargetSimple/IfcTargetProxy_Inspc.h>
#include <emC/Inspc/DataNode_Inspc.h>
#include "Proxy2Target_Inspc.h"

struct Inspector_Inspc_t;



/**The data of the Target proxy communication. */
typedef struct InspcTargetProxy_t
{
  ObjectJc object;
  
  int32 bRun;

  void* _Target_;

  /**Refers the communication buffer and the communication instance.
   * It is the super class of either sharedMem, serial or Socket Communication.
   */
  Proxy2Target_Inspc* targetComm;

  //#ifndef __cplusplus
  /**Communication implementation. One is used.*/
  struct {
    struct Proxy2TargetSharedMem_Inspc_t* shMem;
  } commImpl;
  //#endif

  /**Tx buffer, this is the struct of the tx telegram to the target. */
  TelgProxy2Target_Inspc_s txData2Target;

  MemC txData2TargetP;

  Address_InterProcessComm_s ipAddrTarget;

  
  /**Instanz zur Vermittlung des Receive-callback. */ 
  InterProcessCommRx_ifc_Ipc_s* targetRx;

  /**A send and receive seqnr. */
  int16 seqnrTxTarget, seqnrRxTarget;

  /**The answer word of the target. */
  int32 answerWord_Target;

  /**Modul für Socketkommunikation mit dem eigentlichen Target. */
  InterProcessCommRxThread_Ipc_s* targetIpc;

  /**The inspector service module. */
  Inspector_Inspc_s* theInspector;

  /**The root node presented in Inspector tree 
   * @refl: void. because it gets the reflection info from registered nodes.
   */
  DataNode_Inspc rootNode;

  /**Management class for loading external reflection. */
  ExtReflectionJc_s extReflectionDsp;
  

} InspcTargetProxy_s;


void ctor_InspcTargetProxy(InspcTargetProxy_s* thiz);

void dtor_InspcTargetProxy(InspcTargetProxy_s* thiz);


#ifdef __cplusplus

class InspcTargetProxy : InspcTargetProxy_s {

  public: virtual int32 accessTarget(Cmd_InspcTargetProxy_e cmd, int device, struct RemoteAddressJc* address, int32 input) =0;

};


class InspcTargetProxySharedMem : InspcTargetProxy {

  private: struct Proxy2TargetSharedMem_Inspc_t* shMem;

  public: InspcTargetProxySharedMem(ThCxt* _thCxt);

  protected: int32 accessTarget(Cmd_InspcTargetProxy_e cmd, int device, struct RemoteAddressJc* address, int32 input);

};


#endif //__cplusplus

/**The main data of the InspcTargetProxy-application, seen as root in the inspector. */


extern struct ClassJc_t const refl_Main_InspcTargetProxy_s;

#endif //__InspcTargetProxy_h__
