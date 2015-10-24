
#include "InspcTargetProxy.h"

#include "Jc/ObjectJc.h"
#include "Jc/ReflectionJc.h"

//#include "InspcJ2c/ModulAcq_Inspc.h"
//#include "InspcJ2c/FactoryDevice_Inspc.h"
#include <Ipc2C/InterProcessCommRx_ifc_Ipc.h>
#include <stdlib.h>
#include <stdio.h>

Main_InspcTargetProxy_s data;

#ifndef InterProcessCommMTBDEF
  #define InterProcessCommMTBDEF
  typedef struct InterProcessCommMTB_t { struct Mtbl_InterProcessComm_t const* mtbl; struct InterProcessComm_t* ref; } InterProcessCommMTB;
#endif


extern_C const ClassJc reflection_Comm_InspcTargetProxy_s;
/**Receive routine for target communication. */
METHOD_C static void execRxData_TargetRx(InterProcessCommRx_ifc_Ipc_s* thiz
  , PtrVal_int8 buffer, int32 nrofBytesReceived
  , struct Address_InterProcessComm_t* sender, ThCxt* _thCxt)
{
  
  ASSERT(instanceof_ObjectJc(thiz->data, &reflection_Comm_InspcTargetProxy_s));
  Comm_InspcTargetProxy_s* data = (Comm_InspcTargetProxy_s*)thiz->data;

  printf("execRxData_TargetRx\n");
}


//Assignment from a C method to a here defined instance of an interface via Reflection and method table. 
IFC_IMPL_dataMETHOD1_ObjectJc(InterProcessCommRx_ifc_Ipc, execRxData_TargetRx); 






void ctor_Comm_InspcTargetProxy(Comm_InspcTargetProxy_s* thiz)
{
  STACKTRC_ENTRY("ctor_Comm_InspcTargetProxy");
  //initialize the InterProcessComm with rxBuffer and the rx thread to/from the target.
  initReflection_ObjectJc(&thiz->base, thiz, sizeof(*thiz), &reflection_Comm_InspcTargetProxy_s, 0);
  ctorO_InterProcessCommRx_ifc_Ipc(&thiz->targetRx.base.object, _thCxt);
  setReflection_ObjectJc(&thiz->targetRx.base.object, &reflection_execRxData_TargetRx, 0);
  thiz->targetRx.data = &thiz->base;  //the own data, can be used in the callback routine.
  thiz->targetIpc = create_InterProcessCommRxThread_Ipc(z_StringJc("UDP:127.0.0.1:60198"), &thiz->targetRx, _thCxt);
  if(start_InterProcessCommRxThread_Ipc(thiz->targetIpc, _thCxt)) {
    printf("ok started ipc Target\n");
  }  
 //
  char const* sAddr = "127.0.0.1";
  set_MemC(thiz->txData2TargetP, &thiz->txData2Target, sizeof(thiz->txData2Target));
  init_ObjectJc(&thiz->ipAddrTarget.base.object, sizeof(thiz->ipAddrTarget), 0);
  ctorO_ssI_Address_InterProcessComm(&thiz->ipAddrTarget.base.object, z_StringJc("UDP:"), z_StringJc(sAddr), 60199, _thCxt);
  //
  init_ObjectJc(&thiz->theInspector.base.object, sizeof(thiz->theInspector), 0);
  ctorO_Inspector_Inspc(&data.proxy.theInspector.base.object, s0_StringJc("UDP:0.0.0.0:60094"), _thCxt);
  //
  STACKTRC_LEAVE;
}




void main()
{ StringJc sExtReflectionFile = CONST_z_StringJc("reflTarget/ReflOffsetTarget.bin");
	int headerOffset = 0;
	//StringJc sExtReflectionFile = CONST_z_StringJc("xxx");
	//int headerOffset = 0x70;
	STACKTRC_ENTRY("main");
  init_ObjectJc(&data.object, sizeof(data), 0);
  setReflection_ObjectJc(&data.object, &reflection_Main_InspcTargetProxy_s, 0);

  ctor_Comm_InspcTargetProxy(&data.proxy);
  if(load_ExtReflectionJc(&data.proxy.extReflectionDsp, sExtReflectionFile, headerOffset)==null){
    data._DSP_ = (void*)(-1);
  }
  start_Inspector_Inspc_F(&data.proxy.theInspector, &data.object, _thCxt); 

  while(true)
  { int iTime;
    sleep_ThreadJc(10, _thCxt);
    for(iTime = 0; iTime < 50; iTime++)
    { //TODO capture_ProgressionValue_Inspc(data.progrValue1);
    }
  }

  STACKTRC_LEAVE;
}






/**Request any info which has max. 4 byte return value. 
 * This routine will be called from inside ReflMemAccessJc.c for all Reflection access to outside memory.
 */
int32 getInfo_Comm_InspcTargetProxy(Comm_InspcTargetProxy_s* thiz, Cmd_RemoteCpuJc_e cmd, struct RemoteAddressJc* address, int32 input)
{ int32 ret = -1;
  TelgProxy2Target_Inspc_s* txTelg = &thiz->txData2Target;
  int16 nrofBytesTx = 16+12;
  setInt16BigEndian(&txTelg->head.cmdTelg,0x80);
  setInt32BigEndian(&txTelg->head.seqnr, getInt32BigEndian(&txTelg->head.seqnr) + 1);
  setInt16BigEndian(&txTelg->head.nrofBytes, nrofBytesTx);
  setInt16BigEndian(&txTelg->items[0].cmd, (int16)cmd);
  setInt16BigEndian(&txTelg->items[0].length, sizeof(ItemProxy2Target_Inspc_s));
  setInt32BigEndian(&txTelg->items[0].address, (int32)address);
  setInt32BigEndian(&txTelg->items[0].setValue, input);
  InterProcessCommMTB ipcMtbl; 
  SETMTBJc(ipcMtbl, data.proxy.targetIpc->ipc, InterProcessComm);  //access to derived methods.
  ret = ipcMtbl.mtbl->send(&ipcMtbl.ref->base.object, data.proxy.txData2TargetP, 16+12, &thiz->ipAddrTarget);
  return ret;
}




/**Request any info which has max. 4 byte return value. 
 * This routine will be called from inside ReflMemAccessJc.c for all Reflection access to outside memory.
 */
int32 getInfo_RemoteCpuJc(Cmd_RemoteCpuJc_e cmd, int device, struct RemoteAddressJc* address, int32 input)
{ return getInfo_Comm_InspcTargetProxy(&data.proxy, cmd, address, input);
}