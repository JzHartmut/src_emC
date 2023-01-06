#include <applstdef_emC.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __TEST_DataStructMng_Inspc__

#include <emC/Inspc/FB/DataStruct_Inspc.h>
#include <emC/Inspc/FB/Access_DataStruct_Inspc.h>
#include <emC/Jc/FileIoJc.h> //test object
#include <emC/base/Handle_ptr64_emC.h>

FileJc_s fileinput = INIZ_FileJc;


void check(bool cond, char const* text) {
  if (!cond) {
    printf(text);
  }
}






void test_DataStructMng_Inspc() {
  STACKTRC_ENTRY("test_DataStructMng_Inspc");
  init_Handle2Ptr(1000);
  init_FileJc(&fileinput, z_StringJc("path/to/ExampleName.x"), _thCxt);
  uint32 handleFileInput = registerPtr_Handle2Ptr(&fileinput, "fileinput");
  //
  StringJc empty = INIZ_StringJc("", 0);
  //
  //
  //Super data mng
  //
  char const* const inputSuperdata = "superElememt20,superElement21, superElement22;           ";
  StringJc const typeSuperData = INIZ_StringJc("SuperData", 9);
  struct { DefPortTypes_emC head; Entry_DefPortType_emC __[12]; } portTypes_superData = { 0 };
  ctor_DefPortTypes_emC(&portTypes_superData.head, 12);
  definePortType_DataStructMng_Inspc(&portTypes_superData.head, kSetFromArg_EPropagatePortTypes_emC, inputSuperdata, 1,1); 
  strcpy(portTypes_superData.head.pathBlock, "portTypes_superData");
  //The following information came from Simulink port properties:
  portTypes_superData.head.ixInputStep = 1;
  portTypes_superData.head.entries[0].type = 'F';
  portTypes_superData.head.entries[0].dimensions = 1;
  portTypes_superData.head.entries[0].sizeArray[0] = 1;
  portTypes_superData.head.entries[1].type = 'F';
  portTypes_superData.head.entries[1].dimensions = 1;
  portTypes_superData.head.entries[1].sizeArray[0] = 2;
  portTypes_superData.head.entries[1].type = 'I';
  portTypes_superData.head.entries[1].dimensions = 1;
  portTypes_superData.head.entries[1].sizeArray[0] = 1;
  //
  DataStructMng_Inspc superdata = {{{{{{ INIZ_objReflId_ObjectJc(superdata, null, 0) }}}}}};
  ctor_DataStructMng_Inspc(&superdata, &portTypes_superData.head, inputSuperdata,1,1);
  //
  //
  //chained data2 of super Mng
  //
  char const* inputSuperdata2 = "superElement11, superElement12;           ";
  struct { DefPortTypes_emC head; Entry_DefPortType_emC __[12]; } portTypes_superData2 = { 0 };
  ctor_DefPortTypes_emC(&portTypes_superData2.head, 12);
  definePortType_DataStructMng_Inspc(&portTypes_superData2.head, kSetFromArg_EPropagatePortTypes_emC, inputSuperdata, 1,1); 
  strcpy(portTypes_superData2.head.pathBlock, "portTypes_superData2");
  //The following information came from Simulink port properties:
  portTypes_superData2.head.ixInputStep = 1;
  portTypes_superData2.head.entries[0].type = 'F';
  portTypes_superData2.head.entries[0].dimensions = 1;
  portTypes_superData2.head.entries[0].sizeArray[0] = 1;
  portTypes_superData2.head.entries[1].type = 'F';
  portTypes_superData2.head.entries[1].dimensions = 1;
  portTypes_superData2.head.entries[1].sizeArray[0] = 2;
  //
  DataStruct_Inspc superData2 = {{{{ INIZ_objReflId_ObjectJc(superData2, null, 0) }}}};
  ctor_DataStruct_Inspc(&superData2, &portTypes_superData2.head, z_StringJc("superd2"), inputSuperdata2);
  //
  //
  //chained data2 of data Mng
  //
  char const* inputdata2 = "F2: n2_1; n2_2; FileJc: = xFile; ";
  struct { DefPortTypes_emC head; Entry_DefPortType_emC __[12]; } portTypes_dataMng2 = { 0 };
  ctor_DefPortTypes_emC(&portTypes_dataMng2.head, 12);
  definePortType_DataStructMng_Inspc(&portTypes_dataMng2.head, kSetFromArg_EPropagatePortTypes_emC, inputSuperdata, 1,1); 
  strcpy(portTypes_dataMng2.head.pathBlock, "portTypes_dataMng2");
  //The following information came from Simulink port properties:
  portTypes_dataMng2.head.ixInputStep = 1;
  portTypes_dataMng2.head.entries[0].type = 'F';
  portTypes_dataMng2.head.entries[0].dimensions = 1;
  portTypes_dataMng2.head.entries[0].sizeArray[0] = 2;
  portTypes_dataMng2.head.entries[1].type = 'F';
  portTypes_dataMng2.head.entries[1].dimensions = 1;
  portTypes_dataMng2.head.entries[1].sizeArray[0] = 2;
  portTypes_dataMng2.head.entries[2].type = 'U';
  portTypes_dataMng2.head.entries[2].dimensions = 1;
  portTypes_dataMng2.head.entries[2].sizeArray[0] = 1;
  //
  DataStruct_Inspc data2 = {{{{ INIZ_objReflId_ObjectJc(data2, null, 0) }}}};
  ctor_DataStruct_Inspc(&data2, &portTypes_dataMng2.head, z_StringJc("d2"), inputdata2);
  //
  //
  //data Mng
  //
  char const* inputdata = "n1; =F2; -10 FileJc: = xFile; ObjectJc: ptr;           ";
  struct { DefPortTypes_emC head; Entry_DefPortType_emC __[12]; } portTypes_dataMng = { 0 };
  ctor_DefPortTypes_emC(&portTypes_dataMng.head, 12);
  definePortType_DataStructMng_Inspc(&portTypes_dataMng.head, kSetFromArg_EPropagatePortTypes_emC, inputdata, 1, 1);
  strcpy(portTypes_dataMng.head.pathBlock, "portTypes_dataMng");
  //The following information came from Simulink port properties:
  portTypes_dataMng.head.ixInputStep = 1;
  portTypes_dataMng.head.entries[0].type = 'F';
  portTypes_dataMng.head.entries[0].dimensions = 1;
  portTypes_dataMng.head.entries[0].sizeArray[0] = 1;
  portTypes_dataMng.head.entries[1].type = 'F';
  portTypes_dataMng.head.entries[1].dimensions = 1;
  portTypes_dataMng.head.entries[1].sizeArray[0] = 1;
  portTypes_dataMng.head.entries[2].type = 'U';
  portTypes_dataMng.head.entries[2].dimensions = 1;
  portTypes_dataMng.head.entries[2].sizeArray[0] = 1;
  portTypes_dataMng.head.entries[3].type = 'U';
  portTypes_dataMng.head.entries[3].dimensions = 1;
  portTypes_dataMng.head.entries[3].sizeArray[0] = 1;
  //
  DataStructMng_Inspc dataMng = { { { {{{ INIZ_objReflId_ObjectJc(dataMng, null, 0) }}} } } };
  StringJc sType = INIZ_StringJc("Type", 4);
  ctor_DataStructMng_Inspc(&dataMng, &portTypes_dataMng.head, inputdata, 1, 1);
  //
  //
  //init:
  //
  bool bInitDone;
  //connections between the DataStruct FBlocks
  UserHead_DataStructMng_Inspc* superRef = null;  //Data output of super-Mng
  DataStruct_Inspc* superRef2 = null;             //Data output of super-Data2
  UserHead_DataStructMng_Inspc* mngRef = null;     //Data output of the Mng
  DataStruct_Inspc* dataRef2 = null;             //Data output of the mng-data2 
  StringJc genSrc = INIZ_StringJc("T:/", 3);
  DataStruct_Inspc* terminator = (DataStruct_Inspc*)-1;  //terminator not used for superclass constellation.
  //
  bool bTestWithSubMng = 0;
  bool bTestWithChain = 1;
  //
  do {
    bInitDone = 1;
    bool bInit;

    if(bTestWithSubMng) {
      //The superdata has a chain, putput is superRef2
      //The superdata has data as derived instance, give data
      void const* const inputSuperData[10] = {0};
      uint32 hSuperPrevChain = registerPtr_Handle2Ptr(superRef2, "");
      uint32 hMng = registerPtr_Handle2Ptr(&dataMng, "");
      bInit = init_DataStructMng_Inspc(&superdata, genSrc, typeSuperData, &superRef, &hMng, hSuperPrevChain);
      bInitDone &= bInit; //Note: Do not write bInitDone &= init_DataStruct... because initData... should be processed.
    
      //The second member of superdata as chain.
      bInit = init_DataStruct_Inspc(&superData2, &superRef2);
      bInitDone &= bInit; //Note: Do not write bInitDone &= init_DataStruct... because initData... should be processed.
    } //endif

    //The master mng without derived, has this as derived dataut.
    //The second member of superdata as chain.
    float fConst = 1.234f;
    uint32 handlefInput = handle_Handle2Ptr(&fileinput);

    //DataStructMng_Inspc* subTypeMng = (DataStructMng_Inspc*)-1; //it is the subMng itself.
    struct DataStruct_Inspc_t* prevchain = bTestWithChain ? dataRef2 : &dataMng.base.super;  //Refer itself if no chain.
    uint32 hPrevChain = 0; if(prevchain) { hPrevChain = registerPtr_Handle2Ptr(prevchain, ""); }
    uint32 hSubTypeMng = -1; //registerPtr_Handle2Ptr(subTypeMng, "", &hSubTypeMng);
    bInit = init_DataStructMng_Inspc(&dataMng, genSrc, sType, &mngRef, &fConst, &handlefInput, &hSubTypeMng, &hPrevChain);
    bInitDone &= bInit;
    //
    if(bTestWithChain) {
      //executed after init...Mng:
      uint32 hPrev2Chain = -1;
      bInit = init_DataStruct_Inspc(&data2, &dataRef2, &handlefInput, &hPrev2Chain);
      bInitDone &= bInit; //Note: Do not write bInitDone &= init_DataStruct... because initData... should be processed.
    }
  } while(bInitDone == 0);





  StringJc d1 = z_StringJc("-22 F: (ParamOptimizer_ObjMod*) n1");
  Access_DataStruct_Inspc_s outdata_d1 = { { INIZ_objReflId_ObjectJc(outdata_d1, null, 0) } };
  DefPortTypes_emC portTypeOutData_d1 = { 0 };
  //portTypeOutData.entries = 1;
  portTypeOutData_d1.ixInputStep = 0;
  portTypeOutData_d1.entries[0].type = 'F';
  portTypeOutData_d1.entries[0].sizeType = 4;
  portTypeOutData_d1.entries[0].dimensions = 1;
  portTypeOutData_d1.entries[0].sizeArray[0] = 1;
  definePortType_Access_DataStruct_Inspc(&portTypeOutData_d1, kSetFromArg_EPropagatePortTypes_emC, d1);
  ctor_Access_DataStruct_Inspc(&outdata_d1.base.object, null_StringJc, 0.001f, &portTypeOutData_d1);
  initGet_Access_DataStruct_Inspc(&outdata_d1, d1, mngRef);


  StringJc d2 = INIZ_z_StringJc("F: n2_2");
  Access_DataStruct_Inspc_s outdata_d2 = { { INIZ_objReflId_ObjectJc(outdata_d2, null, 0) } };
  DefPortTypes_emC portTypeOutData_d2 = { 0 };
  //portTypeOutData.entries = 1;
  portTypeOutData_d2.ixInputStep = 0;
  portTypeOutData_d2.entries[0].type = 'F';
  portTypeOutData_d2.entries[0].sizeType = 4;
  portTypeOutData_d2.entries[0].dimensions = 1;
  portTypeOutData_d2.entries[0].sizeArray[0] = 2;
  ctor_Access_DataStruct_Inspc(&outdata_d2.base.object, null_StringJc, 0.001f, &portTypeOutData_d2);
  initGet_Access_DataStruct_Inspc(&outdata_d2, d2, mngRef);

  StringJc d3 = INIZ_z_StringJc("FileJc* xFile");
  Access_DataStruct_Inspc_s outdata_d3 = { { INIZ_objReflId_ObjectJc(outdata_d3, null, 0) } };
  DefPortTypes_emC portTypeOutData_d3 = { 0 };
  //portTypeOutData.entries = 1;
  portTypeOutData_d3.ixInputStep = 0;
  portTypeOutData_d3.entries[0].type = 'U';
  portTypeOutData_d3.entries[0].sizeType = 4;
  portTypeOutData_d3.entries[0].dimensions = 1;
  portTypeOutData_d3.entries[0].sizeArray[0] = 1;
  ctor_Access_DataStruct_Inspc(&outdata_d3.base.object, null_StringJc, 0.001f, &portTypeOutData_d3);
  initGet_Access_DataStruct_Inspc(&outdata_d3, d3, mngRef);

  //StringJc d4 = INIZ_z_StringJc("ptr");

  Access_DataStruct_Inspc_s setdata_d1 = { { INIZ_objReflId_ObjectJc(setdata_d1, null, 0) } };
  //portTypeOutData.entries = 1;
  ctor_Access_DataStruct_Inspc(&setdata_d1.base.object, null_StringJc, 0.001f, &portTypeOutData_d1);
  initSet_Access_DataStruct_Inspc(&setdata_d1, d1, mngRef);




  int32 error = 0;
  float testval = 0.25f, val2 = 0;;
  float ytestval = 0;
  for (int step = 0; step < 1100; ++step) {
    testval += 0.25f;
    void const* const input[10] = {&val2, &testval, 0};
    update_DataStruct_Inspc(&data2, &val2, &testval, &val2, &val2, &val2, &val2, &val2, &val2 );
    if (dataMng.ctGenSrc == 1 || superdata.ctGenSrc == 1)
      step += 0;
    step_DataStructMng_Inspc(&dataMng); //, &error);
    step_DataStructMng_Inspc(&superdata); //, &error);
    get_Access_DataStruct_Inspc(&outdata_d2, &ytestval);
    check(testval == ytestval, "error");
  }


  dtor_DataStructMng_Inspc(&dataMng);
  dtor_DataStructMng_Inspc(&superdata);
  dtor_DataStruct_Inspc(&data2);
  dtor_DataStruct_Inspc(&superData2);
  STACKTRC_RETURN;
}

#ifdef __TEST_DataStruct_Inspc__
void main() {
  STACKTRC_ENTRY("main");
  TRY {
    test_DataStructMng_Inspc();
  }_TRY
    CATCH(Exception, exc) {
    printStackTrace_ExceptionJc(exc, _thCxt);
  } END_TRY;
  STACKTRC_LEAVE;
}
#endif

#endif //__TEST_DataStructMng_Inspc__
