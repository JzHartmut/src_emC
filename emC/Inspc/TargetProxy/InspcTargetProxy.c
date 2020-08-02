#ifdef DEF_INSPC_REMOTEACCESS
#include "InspcTargetProxy.h"
#include <emC/Base/ParseArgs_emC.h>
#include "emC/Jc/ObjectJc.h"
#include "emC/Jc/ReflectionJc.h"

//#include "InspcJ2c/ModulAcq_Inspc.h"
//#include "InspcJ2c/FactoryDevice_Inspc.h"
#include <emC/Ipc/Ipc2C/InterProcessCommRx_ifc_Ipc.h>
#include "Proxy2TargetSharedMem_Inspc.h"

#include <stdlib.h>
#include <stdio.h>

#include <emC/OSAL/os_mem.h>
#include <emC/OSAL/os_keyboard.h>

//#pragma comment(lib, "libMsc15_emC.lib")
//#pragma comment(lib, "ws2_32.lib")


#include "genRefl/InspcTargetProxy.crefl"
//additional crefl for references
//#include "genRefl/InspcTargetSimple/SharedMem2Target_Inspc.crefl"


InterProcessCommRx_ifc_Ipc_s targetRx = {{INIZ_ObjectJc(targetRx, refl_InterProcessCommRx_ifc_Ipc, 0)}};

/**Modul für Socketkommunikation mit dem eigentlichen Target. */
InterProcessCommRxThread_Ipc_s targetIpc = {{INIZ_ObjectJc(targetIpc, refl_InterProcessCommRxThread_Ipc, 0)}};

Inspector_Inspc_s theInspectorTargetProxy = 
{ {INIZ_ObjectJc(theInspectorTargetProxy, refl_Inspector_Inspc, 0)}};



InspcTargetProxy_s data = 
{ INIZ_ObjectJc(data, refl_InspcTargetProxy, 0)  //Object
, 0
, null  //_Target_
, null
, null
, {0}  //txData2Target
, {0}  //txData2TargetP
, {0}  //ipAddrTarget
, &targetRx
, 0,0,0  //seqnr, answer from target
, &targetIpc
, &theInspectorTargetProxy
, {0}  //extReflectionDsp
};

#ifndef InterProcessCommMTBDEF
  #define InterProcessCommMTBDEF
  typedef struct InterProcessCommMTB_t { struct Vtbl_InterProcessComm_t const* mtbl; struct InterProcessComm_t* ref; } InterProcessCommMTB;
#endif


extern_C const ClassJc refl_InspcTargetProxy;


/**Receive routine for target communication. */
METHOD_C static void execRxData_TargetRx(InterProcessCommRx_ifc_Ipc_s* thiz
  , int8ARRAY buffer, int32 nrofBytesReceived
  , struct Address_InterProcessComm_t* sender, ThCxt* _thCxt)
{
  STACKTRC_TENTRY("execRxData_TargetRx");
  ASSERT_emC(instanceof_ObjectJc(thiz->data, &refl_InspcTargetProxy), "data should be instanceof InspcTargetProxy", 0,0);
  InspcTargetProxy_s* data = (InspcTargetProxy_s*)thiz->data;
  TelgTarget2Proxy_Inspc_s* answer;
  if(nrofBytesReceived >= sizeof(*answer)) {
    answer = C_CAST(TelgTarget2Proxy_Inspc_s*, buffer.addr);
    synchronized_ObjectJc(&data->object);
    { bool bNotify = (data->answerWord_Target == -1); 
      data->seqnrRxTarget = getSeqnr_TelgTarget2Proxy_Inspc(answer);
      data->answerWord_Target = getInt32BigEndian(&answer->retValue);
      if(bNotify) { //the other thread is waiting.
        notify_ObjectJc(&data->object, _thCxt);
      }    
    } endSynchronized_ObjectJc(&data->object);
    printf("execRxData_TargetRx\n");
  } else {
    printf("error execRxData_TargetRx\n");
  }
  STACKTRC_LEAVE;
}



#ifdef NOT_DEFINED_IFC_IMPL_dataMETHOD1_ObjectJc
Vtbl_InterProcessCommRx_ifc_Ipc static const mtbl_execRxData_TargetRx = \
{ { sign_Vtbl_InterProcessCommRx_ifc_Ipc , (struct Size_Vtbl_t*)((0 +2) * sizeof(void*)) } \
, execRxData_TargetRx \
, { { sign_Vtbl_ObjectJc, (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) } \
  , clone_ObjectJc_F, equals_ObjectJc_F, finalize_ObjectJc_F, hashCode_ObjectJc_F \
  , toString_ObjectJc_F \
  } \
} /*, { signEnd_Vtbl_ObjectJc, null } }*/; \
\
\
extern_C struct ClassJc_t const refl_execRxData_TargetRx; \
static const struct Reflection_Fields_execRxData_TargetRx_t  \
{ ObjectArrayJc head; FieldJc data[1]; } refl_Fields_execRxData_TargetRx = \
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_execRxData_TargetRx) \
, { { "data" \
    , 0  \
    , &refl_ObjectJc \
    , kReference_Modifier_reflectJc  \
    , (int16)((int32)(intPTR)(&((InterProcessCommRx_ifc_Ipc_s*)(0x1000))->data) - (int32)(intPTR)(InterProcessCommRx_ifc_Ipc_s*)0x1000) \
    , 0   \
    , &refl_execRxData_TargetRx \
    } \
} }; \
const ClassJc refl_execRxData_TargetRx =  \
{ INIZ_ObjectJc(refl_execRxData_TargetRx, refl_ClassJc, 0) \
, "execRxData_TargetRx" \
,  0  \
, sizeof(InterProcessCommRx_ifc_Ipc_s) \
, (FieldJcArray const*)&refl_Fields_execRxData_TargetRx \
, null /*methods*/  \
, null /*superclasses */  \
, null  \
, 0     \
, &mtbl_execRxData_TargetRx.head   \
};
#else
//Assignment from a C method to a here defined instance of an interface via Reflection and method table. 
IFC_IMPL_dataMETHOD1_ObjectJc(InterProcessCommRx_ifc_Ipc, execRxData_TargetRx); 
#endif





void ctor_InspcTargetProxy(InspcTargetProxy_s* thiz)
{
  STACKTRC_ENTRY("ctor_InspcTargetProxy");
  //initialize the InterProcessComm with rxBuffer and the rx thread to/from the target.
  iniz_ObjectJc(&thiz->object, thiz, sizeof(*thiz), &refl_InspcTargetProxy, 0);
  iniz_ObjectJc(&thiz->targetRx->base.object, thiz->targetRx, sizeof(*thiz->targetRx)
               , &refl_InterProcessCommRx_ifc_Ipc, 0);
  ctorO_InterProcessCommRx_ifc_Ipc(&thiz->targetRx->base.object, _thCxt);
  setReflection_ObjectJc(&thiz->targetRx->base.object, &refl_execRxData_TargetRx, 0);
  thiz->targetRx->data = &thiz->object;  //the own data, can be used in the callback routine.
  thiz->targetIpc = create_InterProcessCommRxThread_Ipc(z_StringJc("UDP:127.0.0.1:60198"), thiz->targetRx, _thCxt);
  if(start_InterProcessCommRxThread_Ipc(thiz->targetIpc, _thCxt)) {
    printf("ok started ipc Target\n");
  }  
 //
  char const* sAddr = "127.0.0.1";
  SET_MemC(thiz->txData2TargetP, &thiz->txData2Target, sizeof(thiz->txData2Target));
  init_ObjectJc(&thiz->ipAddrTarget.base.object, sizeof(thiz->ipAddrTarget), 0);
  ctorO_ssI_Address_InterProcessComm(&thiz->ipAddrTarget.base.object, z_StringJc("UDP:"), z_StringJc(sAddr), 60199, _thCxt);
  //
  init_ObjectJc(&thiz->theInspector->base.object, sizeof(*thiz->theInspector), 0);
  ctorO_Inspector_Inspc(&data.theInspector->base.object, s0_StringJc("UDP:0.0.0.0:60092"), _thCxt);
  ctor_DataNode_Inspc(&thiz->rootNode, 10, 0.1f);
  //
  STACKTRC_LEAVE;
}


void dtor_InspcTargetProxy(InspcTargetProxy_s* thiz)
{
  
}


void init_InspcTargetProxy(InspcTargetProxy_s* thiz)
{
  STACKTRC_ENTRY("init_InspcTargetProxy");
  MemSegmJc rootAddr = {0}; 
  ClassJc const* rootClass = null;
  //for internal access too:
  //registerRefl_DataNode_Inspc(&thiz->rootNode, thiz, "all", thiz->object.reflectionClass);
  //rootClass = getClass_ObjectJc(&thiz->rootNode.base.object);
  //setAddrSegm_MemSegmJc(rootAddr, &thiz->rootNode.base.object, 0);
  
  int32 receive = 0; //accessTarget_Inspc(getRootInstance_InspcTargetProxy, 1, null, 0);
  setAddr32Segm_MemSegmJc(rootAddr, receive, 1);
  //int ixClass = accessTarget_Inspc(getRootType_InspcTargetProxy, 1, null, 0);
  //if(ixClass >0) {
    rootClass = null; //extReflectionClasses_ReflectionJc[0]->data[ixClass -1]; //get from loaded reflection file.
    start_Inspector_Inspc_F(thiz->theInspector, rootClass, rootAddr, _thCxt);
  //} else {
  //  printf("Communication to target failed\n");
  //}
  STACKTRC_RETURN;
}



struct Args_t {
  char const* sPathRefl;
  char const* sTargetidSharedmem;
  char const* sTargetIp;
} args = {0};


Ctrl_ParseArgs const cmdArgs[] = 
{ {"--help", "InspcTargetProxy for Communication with slave, made by Hartmut Schorrig, 2019-03", null, null}
, {"-refl:", "path/to/reflection.bin", &args.sPathRefl, null}
, {"-idsh:", "Target identifier String for shared mem Access", &args.sTargetidSharedmem, null}
, {"-ip:", "Target identifier String for Socket Access", &args.sTargetIp, null}
};




#ifdef MAIN_InspcTargetProxy
//void main_InspcTargetProxy()
int main(int nArgs, char** argsCmd)
{
  int erret = 0;
  eval_ParseArgs(cmdArgs, ARRAYLEN_emC(cmdArgs), argsCmd, nArgs);
  //StringJc sExtReflectionFile = CONST_z_StringJc("D:/vishia/smlk/Smlk_ObjO_Inspc/test/+ObjOModule_ExmplCtrl/Cprj/genRefl/refl1.bin");
  if (args.sPathRefl == null || args.sTargetidSharedmem == null) {
    printf("  error arguments, -refl: and -idsh: are necessary. ");
    return 4;
  }
  StringJc sExtReflectionFile = z_StringJc(args.sPathRefl);
  char const* targetName = args.sTargetidSharedmem; //"InspcTarget2Proxy";
  int headerOffset = 0;
	//checkIndexOutOfBounds_OSALUserEXCEPT(headerOffset, -1);
  //StringJc sExtReflectionFile = CONST_z_StringJc("xxx");
	//int headerOffset = 0x70;
	STACKTRC_ROOT_ENTRY("main");
  TRY {
    //#ifndef __cplusplus
      ObjectJc* proxySh = alloc_ObjectJc(sizeof(Proxy2TargetSharedMem_Inspc), 0, THCXT);
      data.commImpl.shMem = ctor_Proxy2TargetSharedMem_Inspc(proxySh, targetName, THCXT);
      data.targetComm = (Proxy2Target_Inspc*)proxySh;
    //#endif

    init_ObjectJc(&data.object, sizeof(data), 0);
    setReflection_ObjectJc(&data.object, &refl_InspcTargetProxy, 0);

    ctor_InspcTargetProxy(&data);
    //
    //====>>
    char const* sError = load_ExtReflectionJc(&data.extReflectionDsp, sExtReflectionFile, headerOffset);
    if(sError == null) {
	    data._Target_ = (void*)(-1);
      //registerRefl_DataNode_Inspc(&data.rootNode, data._Target_, "target", thiz->obj.reflectionClass);
      init_InspcTargetProxy(&data);
      data.bRun = 1;
      while (data.bRun)
      {
        int iTime;
        sleep_ThreadJc(100, _thCxt);
        if(os_keyState('A')) {
          printf("A");
        } else if(os_keyState('C')) {
          printf("\n");  //clear screen
        }

        for (iTime = 0; iTime < 50; iTime++)
        { //TODO capture_ProgressionValue_Inspc(data.progrValue1);
        }
      }

    } else {
      printf("error refl: %s file=%s", sError, args.sPathRefl);
      erret = 5;
    }


  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_ExceptionJc(exc, _thCxt);
    printf("unexpected error");
  }
  FINALLY{
    if(data.commImpl.shMem){ dtor_Proxy2TargetSharedMem_Inspc(data.commImpl.shMem); }
  }
  END_TRY;

  STACKTRC_RETURN erret;
}

#endif




/**Request any info which has max. 4 byte return value. 
 * This routine will be called from inside ReflMemAccessJc.c for all Reflection access to outside memory.
 */
int32 getInfo_InspcTargetProxy(InspcTargetProxy_s* thiz, Cmd_InspcTargetProxy_e cmd, RemoteAddress_Inspc_emC address, int32 input)
{ int32 ret = -1;
  TelgProxy2Target_Inspc_s* txTelg = &thiz->txData2Target;
  int16 nrofBytesTx = (int16)sizeof(thiz->txData2Target);
  setInt32BigEndian(&txTelg->address, address.addrTarget);
  setInt32BigEndian(&txTelg->value, input);
  setCmdSeqnr_TelgProxy2Target_Inspc(txTelg, cmd, ++thiz->seqnrTxTarget);
  InterProcessCommMTB ipcVtbl;
  SETMTBJc(ipcVtbl, data.targetIpc->ipc, InterProcessComm);  //access to derived methods.
  //send the request to the 2CPU-target
  thiz->answerWord_Target = 0;  //clear before receive, note: -1 on wait
  int nrofBytesSend = ipcVtbl.mtbl->send(&ipcVtbl.ref->base.object, data.txData2TargetP, 16+12, &thiz->ipAddrTarget);
  //wait for receiving an answer, but with timeout.
  { synchronized_ObjectJc(&thiz->object);
    if(thiz->seqnrRxTarget != thiz->seqnrTxTarget) {
      thiz->answerWord_Target =-1;  //mutex, set to -1, then wait.
      wait_ObjectJc(&thiz->object, 500, null);
    }
    endSynchronized_ObjectJc(&thiz->object);
    if(thiz->seqnrRxTarget != thiz->seqnrTxTarget) {
      printf("no answer target seqnr=%4.4X\n", thiz->seqnrTxTarget);
    }
  }
  return thiz->answerWord_Target;
}




/**Request any info which has max. 4 byte return value. 
 * This routine will be called from inside ReflMemAccessJc.c for all Reflection access to outside memory.
 */
int32 accessTarget_Inspc ( Cmd_InspcTargetProxy_e cmd, int device, uint32 address, int32 input)
{ 
  return get_Proxy2Target_Inspc(&data.commImpl.shMem->super, cmd, address, input);
  //return getInfo_InspcTargetProxy(&data, cmd, address, input);
}

#ifdef __cplusplus

InspcTargetProxySharedMem::InspcTargetProxySharedMem(ThCxt* _thCxt) {
  STACKTRC_TENTRY("InspcTargetProxySharedMem::ctor")
  ObjectJc* proxySh = alloc_ObjectJc(sizeof(Proxy2TargetSharedMem_Inspc), 0, THCXT);
  this->shMem = ctor_Proxy2TargetSharedMem_Inspc(proxySh, "Test_TargetProxyInspc", THCXT);
  STACKTRC_RETURN;
}


int32 InspcTargetProxySharedMem::accessTarget(Cmd_InspcTargetProxy_e cmd, int device, uint32 address, int32 input) {
  return get_Proxy2Target_Inspc(&this->shMem->super, cmd, address, input);
}
#endif
#endif //DEF_INSPC_REMOTEACCESS
