#include <applstdef_emC.h>
#ifdef DEF_INSPC_REMOTEACCESS
#include "InspcTargetProxy.h"
#include <emC/Base/ParseArgs_emC.h>
#include <emC/Base/StringPacked_emC.h>
#include "emC/Jc/ObjectJc.h"
#include "emC/Jc/ReflectionJc.h"
#include <emC/OSAL/os_file.h>

//#include <emC/AsciiMoni/AsciiMoni.h>
//#include <emC/Inspc/TargetProxy/AsciiMoniToTarget.h>

//#include "InspcJ2c/ModulAcq_Inspc.h"
//#include "InspcJ2c/FactoryDevice_Inspc.h"
#include <emC/Ipc/Ipc2C/InterProcessCommRx_ifc_Ipc.h>
#include "Proxy2TargetSharedMem_Inspc.h"

#include <stdlib.h>
#include <stdio.h>

#include <emC/OSAL/os_mem.h>
#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_keyboard.h>
#include <emC/HAL/Serial_HALemC.h>

//#pragma comment(lib, "libMsc15_emC.lib")
//#pragma comment(lib, "ws2_32.lib")


#include "genRefl/InspcTargetProxy.crefl"
//additional crefl for references
//#include "genRefl/InspcTargetSimple/SharedMem2Target_Inspc.crefl"


InterProcessCommRx_ifc_Ipc_s targetRx = {{INIZ_ObjectJc(targetRx, refl_InterProcessCommRx_ifc_Ipc, 0)}};

/**Modul f�r Socketkommunikation mit dem eigentlichen Target. */
InterProcessCommRxThread_Ipc_s targetIpc = {{INIZ_ObjectJc(targetIpc, refl_InterProcessCommRxThread_Ipc, 0)}};

Inspector_Inspc_s theInspectorTargetProxy = 
{ {INIZ_ObjectJc(theInspectorTargetProxy, refl_Inspector_Inspc, 0)}};

typedef struct Serial_InspcTargetProxy_T {
  int comPort;
  int console;
  char* consoleBuffer; 
  int zConsoleBuffer;
  char* rxBuffer; 
  int zRxBuffer;
  int ixRxBufferWritten;
  int nrRxTelg;         //number of rx telegrams after one command. 
  /**Receive buffer from target for a InspcTargetProxy communication. */
  TelgTarget2Proxy_Inspc_s* rxInspcFromTarget;
        
} Serial_InspcTargetProxy_s;



//Operation prototypes
extern void txCmdsFromFile(InspcTargetProxy_s* thiz, char const* filepath);

extern void processReceivedComport(Serial_InspcTargetProxy_s* thiz, int32 timeoutRxTargetPrx);

static Serial_InspcTargetProxy_s asciiMoni = { -1, -1};

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

Serial_HALemC_s serialComm = INIZ_Serial_HALemC(serialComm, 0, 0);  //for serial comm
Serial_HALemC_s serialCon = INIZ_Serial_HALemC(serialComm, 0, 1);   //for console I/O

extern_C const ClassJc refl_InspcTargetProxy;


bool bOnlyTarget_g = false;




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
      data->answerWord_Target = answer->retValue;
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



void txCmdsFromFile ( InspcTargetProxy_s* thiz, char const* filepath) {
  STACKTRC_ENTRY("txCmdsFromFile");
  OS_HandleFile fh = os_fopenToRead(filepath);
  if(fh ==null) {
    printf("\ncannot read the file\n");
  } else {
    char buffer[128] = {0};
    int zBuffer = sizeof(buffer);
    bool eof = false;
    int zChars = 0;
    int ix = 0;
    do {
      if(!eof) {
        int zread = os_fread(fh, buffer, zBuffer - ix);
        if(zread >0) { zChars += zread; }
        else { eof = true; }
      }
      while(ix < zChars) {
        char cc = buffer[ix++];
        if(cc != '\n' && cc != '\r' && ix == zChars && zChars < zBuffer) {  // end of buffer reached.
          buffer[ix] = cc = '\r';               // terminate anyway the last line.
          ix +=1;
        }
        if(cc == '\n' || cc == '\r') {
          buffer[ix-1] = '\r';           // serial comm need \r for cmd termination
          if(ix >0) {
            txChars_Serial_HALemC(asciiMoni.comPort, buffer, 0, ix); //incl 'r'
            asciiMoni.nrRxTelg = 0;    // 0 after transmit
            buffer[ix-1] = 0;          //terminate for printf
            printf("   >"); printf(buffer); printf("\n");
            ASSERT_emC(zChars >=0 && zChars < zBuffer, "assert", 0,0); 
            while( ix < zChars && ((cc = buffer[ix]) == '\n' || cc=='\r')) { ix +=1; }  //skip over further \r\n 
            memcpy(buffer, buffer+ix, zChars-ix); // shift content to begin.
            zChars -= ix;
            ix = 0;
            //
            sleep_ThreadJc(10, _thCxt);          // show response from the target:
            if (asciiMoni.comPort >= 0 && thiz->targetComm->ms_LastTimeTx == 0) { //only if no comm pending from Inspc
              processReceivedComport(&asciiMoni, thiz->targetComm->ms_LastTimeTx); //note: forceComm_Proxy2Target_Inspc calls this also
            }
          }
        }
      } //while to search line end.
    } while(zChars >0);  //while over file
  }
  os_fclose(fh);
  STACKTRC_RETURN;
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
  
  if(bOnlyTarget_g) {
    int32 receive = 0; //accessTarget_Inspc(getRootInstance_InspcTargetProxy, 1, null, 0);
    //                                             //Set segm=1 as root addr
    //With this construction only the target is visible. 
    setAddr32Segm_MemSegmJc(rootAddr, 0, 1);
    rootClass = null; //extReflectionClasses_ReflectionJc[0]->data[ixClass -1]; //get from loaded reflection file.
  } else {
    //A free configable DataNode is used as root.
    //One element is set to thiz, it is the inspcTargetProxy itself.
    registerRefl_DataNode_Inspc(&thiz->rootNode, thiz, "all", getClass_ObjectJc(&thiz->object));
    rootClass = getClass_ObjectJc(&thiz->rootNode.base.object);
    setAddrSegm_MemSegmJc(rootAddr, &thiz->rootNode.base.object, 0);
  }
  start_Inspector_Inspc_F(thiz->theInspector, rootClass, rootAddr, _thCxt);
  //int ixClass = accessTarget_Inspc(getRootType_InspcTargetProxy, 1, null, 0);
  //if(ixClass >0) {
  //} else {
  //  printf("Communication to target failed\n");
  //}
  STACKTRC_RETURN;
}



struct Args_t {
  char const* sPathRefl;
  char const* sTargetidSharedmem;
  char const* sComPort;
  char const* sTargetIp;
} args = {0};


Ctrl_ParseArgs const cmdArgs[] = 
{ {"--help", "InspcTargetProxy for Communication with slave, made by Hartmut Schorrig, 2020-12", null, null}
, {"-refl:", "path/to/reflection.bin", &args.sPathRefl, null}
, {"-idsh:", "Target identifier String for shared mem Access", &args.sTargetidSharedmem, null}
, {"-com:", "COM port communication", &args.sComPort, null}
, {"-ip:", "Target identifier String for Socket Access", &args.sTargetIp, null}
};




#ifdef MAIN_InspcTargetProxy

#include <emC/HAL/Serial_HALemC.h>
#include <emC/Base/Time_emC.h>



/**initializes COM if argument -com:7 is given. 
 * @arg sComport it is only a digit.
 */
static void initializeComPort(char const* sComPort) {
  asciiMoni.comPort = sComPort[0] - '0';
  asciiMoni.console = 0;
  int error;
  serialComm.baud = 115200;
  serialComm.bytePattern = ParityNoStop1_Serial_HALemC;
  serialComm.dir = toReadWrite_Serial_HALemC;
  serialComm.channel = asciiMoni.comPort;
  error = open_Com_HALemC(&serialComm.base.comm_HAL_emC);
  if(error ==0) {
    printf("target serial over COM%d\n", asciiMoni.comPort);
    //                                 //Prepare receiving from comPort, it is expected.
    asciiMoni.zRxBuffer = 512;
    asciiMoni.rxBuffer = (char*)malloc(asciiMoni.zRxBuffer);
    ASSERT_emC(data.targetComm->target2proxy !=null, "target2proxy should be intialized", 0,0);
    //                                 //Writes into given receive buffer maybe from sharedMem.
    asciiMoni.rxInspcFromTarget = data.targetComm->target2proxy; 

    //prepareRx_Serial_HALemC(asciiMoni.comPort, asciiMoni.rxBuffer, asciiMoni.zRxBuffer, 0);
    //                                 //Open the console for debugging
    serialCon.bytePattern = ParityNoStop1_Serial_HALemC;
    serialCon.channel = asciiMoni.console;
    serialCon.dir = toRead_Serial_HALemC;
    error = open_Com_HALemC(&serialCon.base.comm_HAL_emC);
    if(error ==0) {
      asciiMoni.zConsoleBuffer = 200;  //path for file should match
      asciiMoni.consoleBuffer = (char*)malloc(asciiMoni.zConsoleBuffer);
      //prepareRx_Serial_HALemC(asciiMoni.console, asciiMoni.consoleBuffer, asciiMoni.zConsoleBuffer, 0); 
          
    } else {
      printf("ERROR CON open fails. No ascii command possible. \n");
      asciiMoni.console = -1;
    }
  } else {
    printf("ERROR target serial over COM%d\n", asciiMoni.comPort);
    asciiMoni.comPort = -1;
  }
}


//checks all serial received characters and evaluates it. 
void processReceivedComport(Serial_InspcTargetProxy_s* thiz
    , int32 timeoutRxTargetPrx) {

  int zRx = stepRx_Serial_HALemC(thiz->comPort);
  if(zRx >0) {                         // Some character stored.
    bool bNewline = false;
    char cc;                           // get all character one after another which are stored in the serial buffer
    while( (cc = getChar_Serial_HALemC(thiz->comPort))>=0) {
    //int ix = thiz->ixRxBufferWritten;
      bool rxNew = false;
      if(cc == '\r') {
        if(++thiz->nrRxTelg >1) {
          putchar('\n');                  // if newline was read in this loop, it is in the currently output, write it. 
        } else {
          bNewline = true;
        }
        //printf("\n");                            //output new line to console.
        zRx -=1;
        //ix +=1;
        rxNew = true;
      } 
      else if(cc == '\n') {
        zRx -=1;
        //ix +=1;
        rxNew = true;
      } 
      else if(cc >= ' ') {
        if(bNewline) {
          putchar('\n');                  // if newline was read in this loop, it is in the currently output, write it. 
          bNewline = false;              // but do not write the last newline.
        }
        putchar(cc);                             //output to console
        zRx -=1;
        //ix +=1;
      }
      else if(  timeoutRxTargetPrx !=0 ) {      //if a TelgTarget2Proxy_Inspc_s is expected:
        int zRxInspcFromTarget = (sizeof(*thiz->rxInspcFromTarget) * BYTE_IN_MemUnit);
        if( zRx >= (zRxInspcFromTarget-1) ) { //a complete answer is received 
          //                                     
          MemUnit* dst = (MemUnit*)thiz->rxInspcFromTarget;
          *dst++ = cc;                           // the first byte is the gotten character (8 bit)
          getData_Serial_HALemC(thiz->comPort, dst, 0, zRxInspcFromTarget-1); //all following bytes
          rxNew = true;
        } else {                                 
          int32 delay = os_milliTime() - timeoutRxTargetPrx;
          if(delay > 1000) {
            rxNew = true; 
          }
          printf(".");
          break;
          //try next, till 16 chars.
        }
      } else {                                   // character <0x20 received, but not expected:
        printf("? %2.2x\n", cc);  //unexpected
        rxNew = true;
      }
    } //while
    if(bNewline) {
      printf("   >");                    //output after written line because console creates the newline.
    }
    //if(rxNew) {
      //                                         //preserve furthermore containing chars using ix.
      //prepareRx_Serial_HALemC(thiz->comPort, thiz->rxBuffer, thiz->zRxBuffer, ix);
      //Note: copies furthermore chars to start of rxBuffer
      //ix = 0;
    //}
    //thiz->ixRxBufferWritten = ix;
  }
}



static void mainloop(InspcTargetProxy_s* thiz) {
  STACKTRC_ENTRY("mainloop");
  //int iTime;
  if (asciiMoni.console >= 0) {                // receive from console, till RETURN is pressed (Windows property)
    int nrConChars = stepRx_Serial_HALemC(asciiMoni.console);
    if (nrConChars >0) {                      // evaluate cmd from console
      for (int ix = 0; ix < nrConChars; ++ix) {
        char cc = getChar_Serial_HALemC(asciiMoni.console);
        asciiMoni.consoleBuffer[ix] = cc;
        if (cc == '\r' //ENTER key
          || ix == (asciiMoni.zConsoleBuffer - 1)                 //all full
          ) {
          asciiMoni.consoleBuffer[ix + 1] = 0;
          //printf(asciiMoni.consoleBuffer);   //echo    
                                             //                                 //send the command to target: 
          if (cc == '\r') {
            if(strncmp_emC("cmdfile:", asciiMoni.consoleBuffer, 8)==0) {
              asciiMoni.consoleBuffer[ix] =0;      // terminate the file name
              txCmdsFromFile(thiz, asciiMoni.consoleBuffer +8);
            } else {  
              txChars_Serial_HALemC(asciiMoni.comPort, asciiMoni.consoleBuffer, 0, ix + 1); //incl 'r'
              asciiMoni.nrRxTelg = 0;            // 0 after transmit
              //printf("\n");                      //echo newline 
            }
          }
          else {
            printf(" ???\n");                  //echo error too long line 
          }

          //                                 //prepare console for next line
          //prepareRx_Serial_HALemC(asciiMoni.console, asciiMoni.consoleBuffer, asciiMoni.zConsoleBuffer, 0); 
          break; //for
        }
      }
    }
  }
  sleep_ThreadJc(10, _thCxt);
  if (asciiMoni.comPort >= 0 && thiz->targetComm->ms_LastTimeTx == 0) { //only if no comm pending from Inspc
    processReceivedComport(&asciiMoni, thiz->targetComm->ms_LastTimeTx); //note: forceComm_Proxy2Target_Inspc calls this also
  }
  #if 0
  if (os_keyState('A')) {
    printf("A");
  }
  else if (os_keyState('C')) {
    printf("\n");  //clear screen
  }
  else if (os_keyState(0x71)) {  //in Windows: F2
    thiz->targetComm->modeShowComm = !thiz->targetComm->modeShowComm;
  }
  #endif
  //  for (iTime = 0; iTime < 50; iTime++)
  { //TODO capture_ProgressionValue_Inspc(data.progrValue1);
  }
  STACKTRC_RETURN;
}






int main(int nArgs, char** argsCmd)
{
  //testSerial();
  int erret = 0;
  eval_ParseArgs(cmdArgs, ARRAYLEN_emC(cmdArgs), argsCmd, nArgs);
  //StringJc sExtReflectionFile = CONST_z_StringJc("D:/vishia/smlk/Smlk_ObjO_Inspc/test/+ObjOModule_ExmplCtrl/Cprj/genRefl/refl1.bin");
  if (args.sPathRefl == null || args.sTargetidSharedmem == null) {
    printf("  error arguments, -refl: and -idsh: are necessary. ");
    return 4;
  }
  StringJc sExtReflectionFile = z_StringJc(args.sPathRefl);
  int headerOffset = 0;
	//checkIndexOutOfBounds_OSALUserEXCEPT(headerOffset, -1);
  //StringJc sExtReflectionFile = CONST_z_StringJc("xxx");
	//int headerOffset = 0x70;
	STACKTRC_ROOT_ENTRY("main");
  TRY {
      
    if(args.sTargetidSharedmem !=null) {
      char const* targetName = args.sTargetidSharedmem; //"InspcTarget2Proxy";
      ObjectJc* proxyShObj = alloc_ObjectJc(sizeof(Proxy2TargetSharedMem_Inspc), 0, THCXT);
      Proxy2TargetSharedMem_Inspc* prxSh = ctor_Proxy2TargetSharedMem_Inspc(proxyShObj, targetName, THCXT);
      data.commImpl.shMem_a = prxSh;
      data.targetComm = &prxSh->super;
    }
    if(args.sComPort !=null) {
      initializeComPort(args.sComPort);
      
    }
    //                                           //TargetProxy ShardedMem
    init_ObjectJc(&data.object, sizeof(data), 0);
    setReflection_ObjectJc(&data.object, &refl_InspcTargetProxy, 0);

    ctor_InspcTargetProxy(&data);
    char const* sError = load_ExtReflectionJc(&data.extReflectionDsp, sExtReflectionFile, headerOffset);
    if(sError == null) {
	    printf("success: %s\n", args.sPathRefl);
      data._Target_ = (void*)(-1);
      //registerRefl_DataNode_Inspc(&data.rootNode, data._Target_, "target", thiz->obj.reflectionClass);
      init_InspcTargetProxy(&data);
    } else {
      printf("error refl: %s file=%s", sError, args.sPathRefl);
    }
      //
    //====>>
    data.bRun = 1;
    while (data.bRun) {
      mainloop(&data);
    } //while

    if(asciiMoni.console >=0) { close_Serial_HAL_emC(asciiMoni.console); }
    if(asciiMoni.comPort >=0) { close_Serial_HAL_emC(asciiMoni.comPort); }
    if(asciiMoni.consoleBuffer !=null) { free(asciiMoni.consoleBuffer); }
    if(asciiMoni.rxBuffer !=null) { free(asciiMoni.rxBuffer); }


  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_Exception_emC(exc, _thCxt);
    printf("unexpected error");
  }
  FINALLY{
    if(data.commImpl.shMem_a){ dtor_Proxy2TargetSharedMem_Inspc(data.commImpl.shMem_a); }
  }
  END_TRY;

  STACKTRC_RETURN erret;
}



void errorSystem_emC_  (  int errorCode, const char* description, int value1, int value2, char const* file, int line) {
  printf("ERROR SYSTEM: %d %s %d, %d @%s:%d", errorCode, description, value1, value2, file, line);
  exit(255);
}



//Note: The uncatched_Exception should be assigned to the application frame. It is not a part of a library.
//It should terminate the application, but some resources should be freed. The application frame may known which resources.
void uncatched_Exception_emC  (  Exception_emC* thiz, ThreadContext_emC_s* _thCxt) {
#ifdef DEF_NO_StringJcCapabilities
  printf("ERROR uncatched Exception @%s:%d", thiz->file, thiz->line);
#else
  char buffer[300] = { 0 };
  writeException(buffer, sizeof(buffer), thiz, __FILE__, __LINE__, _thCxt);
  printf(buffer);
#endif
}


void os_notifyError_FileLine  (  int errorCode, const char* description, int value1, int value2, char const* file, int line)
{
  //if (users_os_Error != null)
  //{ //call the users routine:
  //  users_os_Error(errorCode, description, value1, value2);
  //}
  //else
  { //If no user routine is known, the error should be detect by the return code of the os-routines.
    if (description == null) {
      description = "";
    }
    printf("Error %d: %s, %d, %d in file %s: %d", errorCode, description, value1, value2, file, line);
  }
}



#endif




/**Request any info which has max. 4 byte return value. 
 * This routine will be called from inside ReflMemAccessJc.c for all Reflection access to outside memory.
 */
int32 getInfo_InspcTargetProxy(InspcTargetProxy_s* thiz, Cmd_InspcTargetProxy_e cmd, RemoteAddress_Inspc_emC address, int32 input)
{ int32 ret = -1;
  TelgProxy2Target_Inspc_s* txTelg = &thiz->txData2Target;
  int16 nrofBytesTx = (int16)sizeof(thiz->txData2Target);
  txTelg->address = address.addrTarget;
  txTelg->value = input;
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
 * ===> This routine will be called from inside ReflMemAccessJc.c for all Reflection access to outside memory.
 */
int32 accessTarget_Inspc ( Cmd_InspcTargetProxy_e cmd, int device, uint32 address, int32 input)
{ 
  int zRxAsciiMoni = -1;
  if(asciiMoni.comPort >0) {        //preserve up to now chars.
    //zRxAsciiMoni = stepRx_Serial_HALemC(asciiMoni.comPort);
    //                                           //in between use the serial com for Target Proxy
    //prepareRx_Serial_HALemC(asciiMoni.comPort, data.targetComm->target2proxy, sizeof(*data.targetComm->target2proxy), 0);
  }
  //
  int32 result =  get_Proxy2Target_Inspc(&data.commImpl.shMem_a->super, cmd, address, input);
  //return getInfo_InspcTargetProxy(&data, cmd, address, input);
  //furthermore received characters: store newly in buffer before.
  if(zRxAsciiMoni >=0) {
    //prepareRx_Serial_HALemC(asciiMoni.comPort, asciiMoni.rxBuffer, asciiMoni.zRxBuffer, zRxAsciiMoni);
  }
  return result;
}


//Texts for printf
static char const* cmdTxt[] =
{ "0"
, "getRootAddr"  // 1
, "getRootType"  // 2
, "getType    "  // 3
, "getSizeOffs"  // 4
, "getLenArray"  // 5
, "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"
, "getByte    "  // 0x10
, "getInt16   "  // 0x11
, "getInt32   "  // 0x12
, "getInt64   "  // 0x13
, "getFloat   "  // 0x14
, "getDouble  "  // 0x15
, "getRef     "  // 0x16
, "getBitfild "  // 0x17
, "setByte    "  // 0x18
, "setInt16   "  // 0x19
, "setInt32   "  // 0x1a
, "setInt64   "  // 0x1b
, "setFloat   "  // 0x1c
, "setDouble  "  // 0x1d
, "setRef     "  // 0x1e
, "setBitfild "  // 0x1f

};



//This routine is invoked inside get_Proxy2Target_Inspc(...) to communicate.
//It is implemented due to the needs of this application, the inspector target proxy.
//Hence it uses the source-local but static data.
bool forceComm_Proxy2Target_Inspc(Proxy2Target_Inspc* thiz, Cmd_InspcTargetProxy_e cmd) {
  //The target will be read this information in about the next few micro to milliseconds.
  //No: It is a poor polling. 
  //applies the send data in a specific way
  //prepareRx_Serial_HALemC(asciiMoni.comPort, (MemUnit*)thiz->target2proxy, sizeof(*thiz->target2proxy), 0);
  TelgProxy2Target_Inspc_s* txTelg = thiz->proxy2target;
  if(thiz->modeShowComm) {
    printf("tx: %8.8x=%s addr=%8.8x %8.8x %8.8x ...", txTelg->length_seq_cmd, cmdTxt[((int)cmd) & 0x1f], txTelg->address, txTelg->valueHi, txTelg->value);
  }
  thiz->ms_LastTimeTx = os_getMilliTime();       //marking uses the other com
  if (thiz->ms_LastTimeTx == 0) { thiz->ms_LastTimeTx = 1; } //marks pending, should be !=0
  if (asciiMoni.comPort >0) {
    int32 escTx = 0x011b;
    txData_Serial_HALemC(asciiMoni.comPort, &escTx, 0, 2);   //with esc 01 the target detects the InspcTargetTeleg
    int nrofBytesTx = (int)sizeof(*txTelg);
    txData_Serial_HALemC(asciiMoni.comPort, txTelg, 0, nrofBytesTx);
    sleepMicroSec_Time_emC(4000);  //wait 4 ms for tx and rx.
  }
  int seqnrtarget = -1;
  bool hasReceived = false;
  TelgTarget2Proxy_Inspc_s const* rxTelg = thiz->target2proxy;
  int timeout = thiz->ms_timeout;  //seconds
  do {
    sleepMicroSec_Time_emC(1000);  //wait a little moment.
    if (asciiMoni.comPort >0) {
      processReceivedComport(&asciiMoni, thiz->ms_LastTimeTx);
      //int zRx = stepRx_Serial_HALemC(asciiMoni.comPort);
      //if (zRx >= sizeof((*rxTelg))) {
        //The thiz->target2proxy area will be set by the communication thread. 
        //whereby the seqnr need be set as last. 
        seqnrtarget = getSeqnr_TelgTarget2Proxy_Inspc(rxTelg);
        hasReceived = seqnrtarget == thiz->seqnrTxTarget;
      //}
    } else {
      //                               //shard mem communication.
      //The seqnr was set as last, test it.                             
      seqnrtarget = getSeqnr_TelgTarget2Proxy_Inspc(rxTelg);
      hasReceived = seqnrtarget == thiz->seqnrTxTarget;
    }
    if (timeout == 3) {
      timeout += 0;   //debug break
    }
  } while (!hasReceived && --timeout != 0);  //note: if starts with 0, loop for ever.
  
  if (timeout == 0) {
    printf("Timeout target seqtx=%2.2X seqrx=%2.2X\n", thiz->seqnrTxTarget, seqnrtarget);
    thiz->ms_LastTimeTx = 0;
  }
  else {
    int32 milliseconds = thiz->ms_LastTimeCommunication;
    thiz->ms_LastTimeCommunication = os_getMilliTime();
    int32 timediff = thiz->ms_LastTimeCommunication - milliseconds;
    int32 timediffRx = thiz->ms_LastTimeCommunication - thiz->ms_LastTimeTx;
    thiz->ms_LastTimeTx = 0;                     //no more pending.
    if (thiz->modeShowComm) {
      if (timediff > 1000) {
        //printf("\n");
      }
      //printf("%8.8x %s-@%8.8x x=%8.8x ret=%8.8x\n", (int)cmd, cmdTxt[((int)cmd) & 0x1f], address, input, value);
      printf("%2.3fs: %8.8x addr=%8.8x %8.8x val=%8.8x\n", 0.001f*timediffRx, rxTelg->length_seq_cmd, rxTelg->error__lifeCt, rxTelg->retValueHi, rxTelg->retValue);
    }
  }
  return timeout > 0; //then true
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
