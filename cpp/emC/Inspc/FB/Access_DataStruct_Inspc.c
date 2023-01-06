#include <applstdef_emC.h>
#if defined(DEF_REFLECTION_FULL) && defined(DEF_HandlePtr64) && defined(DEF_ClassJc_Vtbl)  //may be used in 32 bit without DEF_HandlePtr64 too?
#include <emC/Inspc/FB/Access_DataStruct_Inspc.h>
#include <emC/Inspc/J2c/SearchElement_Inspc.h>
#include <emC/J1c/StringFunctionsJc.h>
#include <emC/J1c/StringPartScanJc.h>
#include <emC/OSAL/os_mem.h>

#include "emC/Inspc/FB/genRefl/Access_DataStruct_Inspc.crefl"




//Note: arg type not used here, but for definePortType_Access_DataStruct_Inspc to define here for Simulink SfH
Access_DataStruct_Inspc_s* ctor_Access_DataStruct_Inspc(ObjectJc* othiz, /*StringJc type,*/ StringJc header_param, float Tstep, struct DefPortTypes_emC_t const* fblockInfo) {
  Access_DataStruct_Inspc_s* thiz = (Access_DataStruct_Inspc_s*)othiz;
  STACKTRC_ENTRY("ctor_Access_DataStruct_Inspc");
  thiz->fblockInfo = fblockInfo;
  iniz_ObjectJc(othiz, thiz, sizeof(*thiz), &refl_Access_DataStruct_Inspc, 0);
  thiz->ctRepeatInit = 100;
  STACKTRC_RETURN thiz;
}



//Note: arg type not used here, but for definePortType_Access_DataStruct_Inspc to define here for Simulink SfH
Access_DataStruct_Inspc_s* ctorTinit_Access_DataStruct_Inspc(ObjectJc* othiz, StringJc header_param, struct DefPortTypes_emC_t const* fblockInfo) {
  Access_DataStruct_Inspc_s* thiz = (Access_DataStruct_Inspc_s*)othiz;
  STACKTRC_ENTRY("ctorTinit_Access_DataStruct_Inspc");
  thiz->fblockInfo = fblockInfo;
  iniz_ObjectJc(othiz, thiz, sizeof(*thiz), &refl_Access_DataStruct_Inspc, 0);
  thiz->ctRepeatInit = 100;
  STACKTRC_RETURN thiz;
}



void dtor_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s const* thiz) {
}




//It is a common routine for get and set, distinguish due to nrofOutputs
char const* definePortType_Access_DataStruct_Inspc(DefPortTypes_emC* defPortTypes, EDefPortTypes_emC cause, StringJc typeName_param)
{
  STACKTRC_ENTRY("definePortType_Access_DataStruct_Inspc");
  int ix = defPortTypes->nrofOutputs > 0 ? defPortTypes->ixOutputStep //it is a set FB with step input
    : defPortTypes->ixInputStep;  //it is a get FB with step Output.
  StringPartScanJc_s  sscan = { 0 };
  StringPartJc_s* sp = &sscan.base.super;
  ctorO_Cs_StringPartScanJc(&sscan.base.object, typeName_param, _thCxt);
  setIgnoreEndlineComment_S_StringPartJc(sp, z_StringJc("//"), _thCxt);
  setIgnoreWhitespaces_StringPartJc(sp, true, _thCxt);
  parseLineDef_DataStruct_Inspc(sp, &defPortTypes->entries[ix], null, null, 0, cause, _thCxt);
  //char const* err = parse_Entry_DefPortType_emC(&defPortTypes->entries[ix], typeName_param, _thCxt);
  STACKTRC_RETURN null;
}







//This routine will be only used in an experience environment, especially in Simulink Sfunction.
//For a fast application special code will be generated. 
//It is a common routine for get and set, distinguish due to nrofOutputs
bool initObj_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, Entry_DefPortType_emC const* portProps
  , StringJc name_param, ObjectJc* data) {
  STACKTRC_ENTRY("initObj_Access_DataStruct_Inspc");
  if (data == null) {                                    //yet null on input, not ready  
    STACKTRC_RETURN false;                               //not initialized till now, repeat access later
  }
  //VariableParam_DataStruct_Inspc_s typenameinfo = {0};
  char accessPath1[48] = {0};
  StringPartScanJc_s  sscan = { 0 };
  StringPartJc_s* sp = &sscan.base.super;
  ctorO_Cs_StringPartScanJc(&sscan.base.object, name_param, _thCxt);
  setIgnoreEndlineComment_S_StringPartJc(sp, z_StringJc("//"), _thCxt);
  setIgnoreWhitespaces_StringPartJc(sp, true, _thCxt);
  parseLineDef_DataStruct_Inspc(sp, portProps, &thiz->typenameinfo, accessPath1, sizeof(accessPath1)-1,  kRun_EPropagatePortTypes_emC, _thCxt);


  bool ready = false;  //init ready
  int32 ixField = 0;    
  MemSegmJc mem;
  thiz->portProps = *portProps;  //struct copy.
  if(thiz->typenameinfo.structType[0] !=0) {
    if(!instanceof_s_ObjectJc(data, thiz->typenameinfo.structType)) {
      THROW_s0(ClassCastException, "input type fault ", 0,0);
    } 
  }
  StringJc accessPath = z_StringJc(accessPath1); //extractAccessPath_TypeName_emC(name_param, _thCxt);
  if (thiz->err == null) { // no error in ctor
    ClassJc const* clazz = getClass_ObjectJc(data);
    MemSegmJc dataAddr; setAddrSegm_MemSegmJc(dataAddr, data, 0);  //no extern Access
    MemC dataM = getMemC_ObjectJc(data);                   // it is the range of the UserDataBlock in the DataMng_Inspc
    thiz->field = null;
    if (length_StringJc(accessPath) > 0) {                 // Accesspath given, it means the variable is in a referenced Object
      mem = searchObject_SearchElement_Inspc(accessPath, clazz, dataAddr, &thiz->field, &ixField, _thCxt);
      if (ixField == kNullPointerInPath_SearchElement_Inspc) {
        thiz->err = "null pointer in access path";
        STACKTRC_RETURN false;                             //not initialized till now, repeat access later
      }
      else if (thiz->field == null) { 
        thiz->err = "faulty datapath_param"; 
      } else {                                             // exchange dataAddr and dataM with the accessed Object 
        dataAddr = getObjAndClass_FieldJc(thiz->field, mem, &clazz, "I", -1);
        if (dataAddr.addr.a == null) {                         //either on input or  
          thiz->field = null; //force recall
          STACKTRC_RETURN false;                               //not initialized till now, repeat access later
        }
        dataM = build_MemC(dataAddr.addr.a, clazz->nSize); //the range of the refered object, to check addr in range of MemC
      }
    } 
    StringJc nameElement = zMax_StringJc(thiz->typenameinfo.name, sizeof(thiz->typenameinfo.name));
    if( length_StringJc(nameElement) == 0) {               // name not given, it means input addr should be returned.
      if(dataAddr.addr.a !=data) {
        THROW_s0(IllegalArgumentException, "faulty: path given, no element given", 0, 0);
      }           
      thiz->addr = data;                                   //will be evaluated outside: return handle of data
      thiz->zBytes = 0;
      ready = true;
    }
    else {
      if (dataAddr.addr.a != null) {                         //either on input or  
        mem = searchObject_SearchElement_Inspc(nameElement, clazz, dataAddr, &thiz->field, &ixField, _thCxt);
      }
      if (thiz->err == null && thiz->field != null && ixField >= -1) { //Note: ixField == -1 means, no index. <-1 is error

        MemSegmJc addrMem = getAddressElement_FieldJc(thiz->field, mem, "I", ixField); //Note: ixField may be -1
        void* addr = ADDR_MemSegmJc(addrMem, void); //Note: ignore segment information, always in own segment, no remote access.
        int nBytesData;
        if (thiz->field->bitModifiers & mReference_Modifier_reflectJc) {
          if(isHandleRef_FieldJc(thiz->field)) {
            nBytesData = 4;  //a reference is stored as handle or it is a int32 address space on target.
          } else {
            nBytesData = sizeof(void*);  //size of a reference.
          }
        }
        else {
          ClassJc const* fieldType = getType_FieldJc(thiz->field);
          nBytesData = fieldType->nSize;
          char typeField = typeChar_FieldJc(thiz->field);
          if(thiz->portProps.type != typeField) {
            thiz->err = "type faulty ";
            THROW_s0(IllegalArgumentException, thiz->err, thiz->portProps.type, typeField);
          }
        }
        if (thiz->err == null) {
          int arraysizeField = getStaticArraySize_FieldJc(thiz->field);
          if (arraysizeField == 0) { arraysizeField = 1; }
          int sizeField = nBytesData * arraysizeField;     // size of the element as scalar or field from Reflection
          int sizeType = thiz->portProps.sizeType;
          int dimensionsUsed = thiz->portProps.dimensions - thiz->typenameinfo.dimensionUsed;
          for (int ixDim = 0; ixDim < dimensionsUsed; ++ixDim) {
            sizeType *= thiz->portProps.sizeArray[ixDim];
          }
          if (sizeType == 0) {
            thiz->err = "dimension error";
          } else {
            thiz->zBytes = MIN_emC(sizeField, sizeType);
            checkAddress_MemC(&dataM, addr, thiz->zBytes);  //causes an exception on faulty addr
            thiz->addr = addr;
          }
        }
        ready = thiz->err == null; //true for register.
      }
      else if (ixField == kNullPointerInPath_SearchElement_Inspc) {
        //it is especially if the FBs before are not initialized:
        THROW_s0(IllegalArgumentException, "should not entry here", 0, 0);

        thiz->field = null;     //really not found.
        //ready == false, repeat the access, not all members may be initialized yet.
      }
      else {
        thiz->addr = null;
        if(thiz->err == null) {  //if field == null 
          thiz->err = "element not found"; 
        }
      }
    }
  }
  if(thiz->err !=null) {
    THROW_s0(IllegalArgumentException, thiz->err, 0, 0);
  }
  STACKTRC_RETURN ready;
}









bool init_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz
  , Entry_DefPortType_emC const* portProps
  , bool bSet
  , StringJc typeName_param 
  , struct UserHead_DataStructMng_Inspc_t* data
  , uint32* handle_y) {
  bool bInit = false;
  STACKTRC_ENTRY("init_Access_DataStruct_Inspc");
  if (--thiz->ctRepeatInit < 0) {
    thiz->err = "does not initialize in 100 time, maybe faulty connection on input or faulty name ";
    THROW_s0(IllegalArgumentException, thiz->err, 0, 0);
  }
  //if (thiz->field == null && thiz->err == null && data !=null) {
    bInit = initObj_Access_DataStruct_Inspc(thiz, portProps, typeName_param, &data->base.object);
    //found is false if the field is not found in the whole path. 
    if (!bInit && thiz->err != null) { //non thrown error, error is stored, it is initialized without field.
      setInitialized_ObjectJc(&thiz->base.object);  //do not repeat the access. err is set.
      bInit = true;
    }
    else if (bInit) {
      //successfull
      if(thiz->addr ==null) {  
        THROW_s0(IllegalArgumentException, "unexpected: is initialized but addr ==null", 0, 0);
      }
      if(handle_y !=null) {                      // output to set in Tinit
        uint32 yHandle;
        if(thiz->addr == data) {                 // returns data itself, but as handle:
          yHandle = handle_Handle2Ptr(data);     // data has a handle anyway.
        } 
        else {
          yHandle = *(uint32*)thiz->addr;        //Address in the source DataStruct, read the handle there.
        } 
        if (yHandle != 0) {                      //It should be !=0 for initializing
          *handle_y = yHandle;
          setInitialized_ObjectJc(&thiz->base.object);  //ok
        } else {                                   
          bInit = false;                         // if the handle is 0, repeat initialization.
        }
      }
      else {
        if(thiz->addr == data) {
          THROW_s0(IllegalArgumentException, "return thiz not supported. Use instead getTinit_DataStruct_Inspc", 0, 0);
        }
       
        if(bSet) {
          registerSetData_DataStructMng_Inspc(data->thiz1, thiz);
        }
        setInitialized_ObjectJc(&thiz->base.object);  //ok
      }
    }
    else {
      //no error, no field, initialize again.
    }
  //}
  if (thiz->err) {
    THROW_s0(IllegalArgumentException, thiz->err, 0, 0);
  }
  STACKTRC_RETURN bInit;
}



bool XXXinitTinit_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, StringJc typeName_param
  , struct UserHead_DataStructMng_Inspc_t* data, uint32* handle_y) {
  bool bInit = false;
  STACKTRC_ENTRY("init_Access_DataStruct_Inspc");
  if (--thiz->ctRepeatInit < 0) {
    thiz->err = "does not initialize in 100 time, maybe faulty connection on input or faulty name ";
    THROW_s0(IllegalArgumentException, thiz->err, 0, 0);
  }
  if(data !=null) {
    if (thiz->field == null && thiz->err == null) {
      bInit = initObj_Access_DataStruct_Inspc(thiz, &thiz->fblockInfo->entries[thiz->fblockInfo->ixOutputStep], typeName_param, &data->base.object);
    }
    else {
      bInit = thiz->field != null;
    }
    //
    if (!bInit && thiz->err != null) {
      setInitialized_ObjectJc(&thiz->base.object);  //do not repeat the access. err is set.
      bInit = true;
    }
    else if (bInit) {
      //successfull
      uint32 yHandle;
      if(thiz->addr ==null) {  
        THROW_s0(IllegalArgumentException, "unexpected: is initialized but addr ==null", 0, 0);
      }
      else if(thiz->addr == data) {                   // returns data itself, but as handle:
        yHandle = handle_Handle2Ptr(data);       // data has a handle anyway.
      } 
      else {
        yHandle = *(uint32*)thiz->addr;          //Address in the source DataStruct, read the handle there.
      } 
      if (yHandle != 0) {                        //It should be !=0 for initializing
        *handle_y = yHandle;
        setInitialized_ObjectJc(&thiz->base.object);  //ok
        bInit = true;
      } else {                                   // if the handle is 0, repeat initialization.  
      }
    }
    else {
      //no error, no field, initialize again.
    }
  }
  if (thiz->err) {
    THROW_s0(IllegalArgumentException, thiz->err, 0, 0);
  }
  STACKTRC_RETURN bInit;
}




int defTlcParams_Access_DataStruct_Inspc(DefPortTypes_emC* portInfo_tlcParam
  , char const* keys_tlcParam[5], void const* values_tlcParam[5]
  , char buffer_tlcParam[500], int zBuffer_tlcParam
  , char header_param[200]
  , StringJc name_param
) {
  //int pos;
  int zChars = 0;
  int posBuffer = 0;
  STACKTRC_ENTRY("defTlcParams_Access_DataStruct_Inspc");
  //
  VariableParam_DataStruct_Inspc_s info = {0};
  int ix = portInfo_tlcParam->nrofOutputs > 0 ? portInfo_tlcParam->ixOutputStep //it is a set FB with step input
    : portInfo_tlcParam->ixInputStep;  //it is a get FB with step Output.
  StringPartScanJc_s  sscan = { 0 };
  StringPartJc_s* sp = &sscan.base.super;
  ctorO_Cs_StringPartScanJc(&sscan.base.object, name_param, _thCxt);
  setIgnoreEndlineComment_S_StringPartJc(sp, z_StringJc("//"), _thCxt);
  setIgnoreWhitespaces_StringPartJc(sp, true, _thCxt);
  zChars = parseLineDef_DataStruct_Inspc(sp, &portInfo_tlcParam->entries[ix], &info, buffer_tlcParam, zBuffer_tlcParam, kRun_EPropagatePortTypes_emC, _thCxt);
  //
  keys_tlcParam[3] = "datapath_param";
  values_tlcParam[3] = buffer_tlcParam;
  //StringJc accessPath = extractAccessPath_TypeName_emC(name_param, _thCxt);
  //zChars = copyToBuffer_StringJc(accessPath, 0, kMaxNrofChars_StringJc, buffer_tlcParam + posBuffer, zBuffer_tlcParam - posBuffer) + 1;
  posBuffer += zChars +1;
  //
  //
  keys_tlcParam[0] = "typeData_param";
  values_tlcParam[0] = buffer_tlcParam + posBuffer;
  zChars = strncpy_emC(buffer_tlcParam + posBuffer, info.typeRef, zBuffer_tlcParam - posBuffer);
  //StringJc typeData = extractType_TypeName_emC(name_param, _thCxt);
  //zChars = copyToBuffer_StringJc(typeData, 0, kMaxNrofChars_StringJc, buffer_tlcParam + posBuffer, zBuffer_tlcParam - posBuffer);
  posBuffer += zChars +1;
  //
  keys_tlcParam[1] = "header_param";
  values_tlcParam[1] = header_param;
  //
  keys_tlcParam[2] = "typeDataIn_param";
  values_tlcParam[2] = buffer_tlcParam + posBuffer;
  zChars = strncpy_emC(buffer_tlcParam + posBuffer, info.structType, zBuffer_tlcParam - posBuffer);
  //StringJc typeDataIn = extractStructType_TypeName_emC(name_param, _thCxt);
  //zChars = copyToBuffer_StringJc(typeDataIn, 0, kMaxNrofChars_StringJc, buffer_tlcParam + posBuffer, zBuffer_tlcParam - posBuffer);
  posBuffer += zChars +1;
  //
  keys_tlcParam[4] = "name_param";
  values_tlcParam[4] = buffer_tlcParam + posBuffer;
  zChars = strncpy_emC(buffer_tlcParam + posBuffer, info.name, zBuffer_tlcParam - posBuffer);
  //StringJc name = extractName_TypeName_emC(name_param, _thCxt);
  //zChars = copyToBuffer_StringJc(name, 0, kMaxNrofChars_StringJc, buffer_tlcParam + posBuffer, zBuffer_tlcParam - posBuffer);
  posBuffer += zChars +1;
  //
  STACKTRC_RETURN posBuffer;
}




int defTlcParams_TinitAccess_DataStruct_Inspc(DefPortTypes_emC* portInfo_tlcParam
, char const* keys_tlcParam[5], void const* values_tlcParam[5]
, char buffer_tlcParam[500], int zBuffer_tlcParam
, char header_param[200], StringJc typeName_param
) {
  return defTlcParams_Access_DataStruct_Inspc(portInfo_tlcParam, keys_tlcParam, values_tlcParam
  , buffer_tlcParam, zBuffer_tlcParam, header_param, typeName_param);
}



void wait_Access_DataStruct_Inspc(Access_DataStruct_Inspc_s* thiz, int32 us_wait_param, int32 ms_timeout_param, void* y_y) 
{ 
  ASSERT_emC(thiz->zBytes ==4, "wait_Access_DataStruct only available for int32", thiz->zBytes, 0);
  int32* value = C_CAST(int32*, thiz->addr);
  if(*value <=0) {
    *value = 0;                 // wait request not currently hold on 0; do nothing
  } else if (--(*value) ==0) {  // wait request reaches 0, wait for ever from simulink view
    int ctTimeout = ms_timeout_param * 1000 / us_wait_param;  //0: wait forever till value !=0
    while(*value ==0 && (ctTimeout ==0 || --ctTimeout >0)) {
      //ctTimeout ==0 true: waits forever, ctTimeout >0: waits till ==0, aborts if it reaches 0 by predecrement.   
      // value: only an access form outside (via inspector or shared mem) can change this value
      sleepMicroSec_Time_emC(us_wait_param);   // yied other threads and processes.
    }
    if(*value ==0) {
      *value = 1;               // comes from timeout. Wait again.
    }
  } else {
    //                       //value >0, do nothing.
  }
  memcpy(y_y, value, thiz->zBytes);   // show the decremented value till wait. 
}



#endif //DEF_REFLECTION_FULL
