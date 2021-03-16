#include <applstdef_emC.h>
#ifdef DEF_REFLECTION_FULL
#include <emC/Inspc/FB/DataStructBase_Inspc.h>
#include <emC/J1c/StringFunctionsJc.h>
#include <emC/J1c/StringPartScanJc.h>
#include <emC/OSAL/os_mem.h>


#include "emC/Inspc/FB/genRefl/DataStructBase_Inspc.crefl"


//"D F J I S B U W V Z C d  f j  i s b Z C"
//static const int8 zPrimitive[] = { 8,4,8,4,2,1,4,2,1,1,1,16,8,16,8,4,2,1,1};


void ctor_DataStructBase_Inspc  (  DataStructBase_Inspc_s* thiz, DefPortTypes_emC* fbInfo, int ixPort
  , int zVariable
  , char const* sVariableDef
){
  thiz->fBlockInfo = fbInfo;
  if(zVariable <=0){ zVariable = 1; }  //FB without inputs is stupid but possible. anylyzeInputDefinition(...) needs at least 1 slot.
  int zMem = zVariable * sizeof(VariableParam_DataStruct_Inspc_s);
  thiz->varParams = (VariableParam_DataStruct_Inspc_s*) os_allocMem(zMem);
  //
  bool bOutputVariable = (ixPort > fbInfo->nrofInputs);
  thiz->zVariable = (int16)analyzeVariableDef(z_StringJc(sVariableDef), thiz->varParams, zVariable, fbInfo, ixPort, bOutputVariable, kRun_EPropagatePortTypes_emC);
  thiz->varParams_debugView = (VariableParam_DataStruct_Inspc_Array*) thiz->varParams;


}

void dtor_DataStructBase_Inspc  (  DataStructBase_Inspc_s* thiz) {
  if (thiz->varParams) {
    os_freeMem(thiz->varParams);
  }
}




int XXXanalyzeLineDef_DataStruct_Inspc  (  struct StringPartScanJc_t* sscan, Entry_DefPortType_emC const* portInfo
  , VariableParam_DataStruct_Inspc_s* varInfo
  , char* bufferDataPath, int zBufferDatapath
  , EDefPortTypes_emC cause, ThCxt* _thCxt) {
  STACKTRC_TENTRY("analyzeLineDef");
  Entry_DefPortType_emC* portInfoWr = varInfo ? null: (Entry_DefPortType_emC*) portInfo; //not const if varInfo not given 
  StringPartJc_s* sp = &sscan->base.super;
  int posDataPath = 0;
  bool bCheckPrimitivetype = true;
  seekNoWhitespaceOrComments_StringPartJc(sp, _thCxt);
  char cc = charAt_i_StringPartJc(&sp->base.CharSeqObjJc_ifc, 0, _thCxt);
  int nrPrimitive = 0;
  while (length_StringPartJc(sp, _thCxt) > 0 && cc != ',' && cc != ';') {  //text has some information.
    int pos = getCurrentPosition_StringPartJc(sp, _thCxt);  //may be a name
    //checks some parts of a line as alternatives in any order  { = | -23: | F2,2: | Type: | (StructType*) | name }
    if (cc == '=') {
      if (varInfo == null) { //port definition phase
        portInfoWr->newDefined_Tstep_Tinit = mInputInit_Entry_DefPortType_emC;
      }
      seekPos_StringPartJc(sp, 1, _thCxt);
    }
    else if (cc == '-') {
      seekPos_StringPartJc(sp, 1, _thCxt);
      if (scanOk_StringPartScanJc(scanPositivInteger_StringPartScanJc(sscan, _thCxt), _thCxt)) {
        if (varInfo) {
          varInfo->accessRights = (int8)getLastScannedIntegerNumber_StringPartScanJc(sscan, _thCxt);
        }
      }
      else {
        THROW_s0(IllegalArgumentException, "-23 digits expected after - for access rights at pos ", getCurrentPosition_StringPartJc(sp, _thCxt), 0);
      }
    }
    else if (cc == '('                           // the (structType*)
            && seekPos_StringPartJc(sp, 1, _thCxt)
            && scanStart_StringPartScanJc(sscan, _thCxt)
            && scanIdentifier_StringPartScanJc(sscan, _thCxt)
            && scan_Cs_StringPartScanJc(sscan, z_StringJc("*)"), _thCxt)
            && scanOk_StringPartScanJc(sscan , _thCxt)
            ) {
      Part_StringPartJc_s* cs = getLastScannedPart_StringPartScanJc(sscan, 1, _thCxt);
      if(varInfo !=null) {
        copyToBuffer_Part_StringPartJc(cs, varInfo->structType, 0, sizeof(varInfo->structType), _thCxt);
      }
    }
    //else if (cc == ':') {                        // follows the : type
    else if (bCheckPrimitivetype && (nrPrimitive = indexOf_C_StringJc(z_StringJc("DFJISBUWVZCdfjisbZC"), cc)) >= 0) {  //maybe special type identifier
      char typeChar = cc;
      seekPos_StringPartJc(sp, 1, _thCxt);
      int dimensions = 0;
      uint16 sizeArray[ARRAYLEN_emC(portInfo->sizeArray)] = {0,0};  //double of portInfo->sizeArray
                                                            //A primitive char is detected, after them a number for  array size can be following:
      while (scanOk_StringPartScanJc(scanPositivInteger_StringPartScanJc(scanStart_StringPartScanJc(sscan, _thCxt), _thCxt), _thCxt)) {
        sizeArray[dimensions] = (int16)getLastScannedIntegerNumber_StringPartScanJc(sscan, _thCxt);
        if (dimensions < ARRAYLEN_emC(sizeArray) - 1) { dimensions += 1; }  //simple prevent overflow, max 5 sizes, 
        seekNoWhitespaceOrComments_StringPartJc(sp, _thCxt);
        if (!scanOk_StringPartScanJc(scan_Cs_StringPartScanJc(sscan, z_StringJc(","), _thCxt), _thCxt)) {
          break;  //another char as ','
        }
      }
      //end char after F2:
      if (scanOk_StringPartScanJc(scan_Cs_StringPartScanJc(sscan, z_StringJc(":"), _thCxt), _thCxt)) {
        if(cause == kRun_EPropagatePortTypes_emC) {
          //The info is gotten from the port already. compare it:
          ASSERT(portInfo->type == typeChar);
          if(dimensions == 0) {
            ASSERT(portInfo->dimensions <=1); //may be 1 or 0
            ASSERT(portInfo->sizeArray[0] <=2);  //may be 1 or 0
          } else {
            ASSERT(portInfo->dimensions == dimensions);  //should be the same, else difference between intialized ports and info here.
            ASSERT(memcmp(portInfo->sizeArray,sizeArray, sizeof(portInfo->sizeArray))==0);
          }
        }
        else {
          portInfoWr->type = typeChar;  //it is a typeChar.
          portInfoWr->dimensions = dimensions;  //0 if no vector is given.
          memcpy(portInfoWr->sizeArray, sizeArray, sizeof(portInfo->sizeArray));
        }
        //seekPos_StringPartJc(sp, 1, _thCxt);
        seekNoWhitespaceOrComments_StringPartJc(sp, _thCxt);
      }
      else {
        setCurrentPosition_StringPartJc(sp, pos, _thCxt);  //parse this part newly.
        bCheckPrimitivetype = false;  //for next while loop.
      }
    }
    //
    //either the name or a Type: can be written instead F2:  
    else if (scanOk_StringPartScanJc(scanIdentifier_StringPartScanJc(scanStart_StringPartScanJc(sscan, _thCxt), _thCxt), _thCxt)) {
      Part_StringPartJc_s* cs = getLastScannedPart_StringPartScanJc(sscan, 1, _thCxt);
      seekNoWhitespaceOrComments_StringPartJc(sp, _thCxt);
      if (length_StringPartJc(sp, _thCxt) >0) {
        cc = charAt_i_StringPartJc(&sp->base.CharSeqObjJc_ifc, 0, _thCxt);
      }
      else {
        cc = ';';  //last ; missing, admissible.
      }
      if (cc == ':') { //Type of an handle-ref-input:
        if (varInfo) {
          copyToBuffer_Part_StringPartJc(cs, varInfo->typeRef, 0, sizeof(varInfo->typeRef), _thCxt);
        }
        else {
          portInfoWr->type = 'H';  //handle, use uint32
        }
        seekPos_StringPartJc(sp, 1, _thCxt);
      }
      else if (cc == ';' || cc == ',') {
        //variable is finished.
        //copy name
        if (varInfo) {
          copyToBuffer_Part_StringPartJc(cs, varInfo->name, 0, sizeof(varInfo->name), _thCxt);
        }
        if (varInfo == null) {
          portInfoWr->newDefined_Tstep_Tinit |= newDefined_Entry_DefPortType_emC;
        }
      }
      else if(cc == '.') { //datapath
        if(bufferDataPath !=null) {
          posDataPath = copyToBuffer_Part_StringPartJc(cs, bufferDataPath, posDataPath, zBufferDatapath, _thCxt);
          bufferDataPath[posDataPath++] = '.';
        }
        seekPos_StringPartJc(sp, 1, _thCxt);
      }
      else {
        THROW_s0(IllegalArgumentException, "faulty char detected in typeName on pos ", (int)getCurrentPosition_StringPartJc(sp, _thCxt), 0);
      }
    }
    else {
      THROW_s0(IllegalArgumentException, "faulty char detected in typeName on pos ", (int)getCurrentPosition_StringPartJc(sp, _thCxt), 0);
    }
    seekNoWhitespaceOrComments_StringPartJc(sp, _thCxt);
    cc = length_StringPartJc(sp, _thCxt) > 0 ? charAt_i_StringPartJc(&sp->base.CharSeqObjJc_ifc, 0, _thCxt) : ';';
  } //while cLine
  if(  varInfo !=null && varInfo->typeRef[0] ==0 
    && (portInfoWr ==null || portInfoWr->type == 0)) {    // No type: given, then the structType is outputted 
    strncpy(varInfo->typeRef, varInfo->structType, sizeof(varInfo->typeRef));
  }
  STACKTRC_RETURN posDataPath;
}




/**Analyzes the given parameter in the text area and sets port info about the signal inputs.
*/
int analyzeVariableDef ( StringJc sVarDef
, VariableParam_DataStruct_Inspc_s* const varArray, int zVarArray
, DefPortTypes_emC* fbInfo, int ixPortStart, bool bOutput
, EDefPortTypes_emC cause
) {
  STACKTRC_ENTRY("analyeInputDefinition");
  int ixVar = 0;
  int ixPort = ixPortStart;
  StringPartScanJc_s  sscan = { 0 };
  StringPartJc_s* sp = &sscan.base.super;
  ctorO_Cs_StringPartScanJc(&sscan.base.object, sVarDef, _thCxt);
  setIgnoreEndlineComment_S_StringPartJc(sp, z_StringJc("//"), _thCxt);
  setIgnoreWhitespaces_StringPartJc(sp, true, _thCxt);
  //
  //loop over more as one entry.
  do {
    char cc = charAt_i_StringPartJc(&sp->base.CharSeqObjJc_ifc, 0, _thCxt); //first char is the end char of last line.
    if(cc == ';' || cc == ',') {
      seekPos_StringPartJc(sp, 1, _thCxt); //now skip over end char, but it is known.
    }
    seekNoWhitespaceOrComments_StringPartJc(sp, _thCxt);
    if( length_StringPartJc(sp, _thCxt) > 0 ) {
      Entry_DefPortType_emC* portInfo = &fbInfo->entries[ixPort];
      VariableParam_DataStruct_Inspc_s* varInfo = varArray == null ? null : &varArray[ixVar];
      if(varInfo) {
        varInfo->ePort = portInfo;
        portInfo->sType = varInfo->typeRef;  //Reference to the nested char[32]
        portInfo->sName = varInfo->name;     //Reference to the nested char[32]
      } else { //used for definePortType
        portInfo->sType = null;
        portInfo->sName = "???";
      }
      if(cause == kSetFromArg_EPropagatePortTypes_emC) {
        portInfo->type = 0;
        portInfo->newDefined_Tstep_Tinit = 0;
        portInfo->dimensions = -1;
        portInfo->Tstep = 0;
      }
      if(cc == ',' && ixVar >0) {
        //Duplicate the information from the last entry because , as separator:
        if(varArray) {
          VariableParam_DataStruct_Inspc_s* varInfoLast = &varArray[ixVar-1];
          varInfo->accessRights = varInfoLast->accessRights;
          memcpy(varInfo->typeRef, varInfoLast->typeRef, sizeof(varInfo->typeRef));
        } else {
          Entry_DefPortType_emC* portInfoLast = &fbInfo->entries[ixPort-1];
          portInfo->type = portInfoLast->type;
          portInfo->dimensions = portInfoLast->dimensions;
          memcpy(portInfo->sizeArray, portInfoLast->sizeArray, sizeof(portInfo->sizeArray));
          portInfo->newDefined_Tstep_Tinit = portInfoLast->newDefined_Tstep_Tinit;
        }
      } //if cc == ','
      //
      // ===>
      parseLineDef_DataStruct_Inspc(sp, portInfo, varInfo, null, 0, cause, _thCxt);
      //
      if(varArray==null) { //only in port initialization phase:
        if(bOutput) {
          int32 mBit = 1 << (ixPort - fbInfo->nrofInputs);
          //The entry defines mInputInit if a '=' is contained:
          if(fbInfo->entries[ixPort].newDefined_Tstep_Tinit & mOutputInit_Entry_DefPortType_emC) {
            fbInfo->mOutputVargInit   |= mBit; //store in bitmask
            fbInfo->nrofVargsInit +=1;
          } else { //no '=' contained, it is an update port.
            fbInfo->entries[ixPort].newDefined_Tstep_Tinit |= mOutputStep_Entry_DefPortType_emC;
            fbInfo->mOutputVargStep   |= mBit; 
            fbInfo->nrofVargsStep +=1;
          }
        } else {
          int32 mBit = 1 << ixPort;
          //The entry defines mInputInit if a '=' is contained:
          if(fbInfo->entries[ixPort].newDefined_Tstep_Tinit & mInputInit_Entry_DefPortType_emC) {
            fbInfo->mInputVargInit |= mBit; //store in bitmask
            fbInfo->mInputDataInit |= mBit;
            fbInfo->nrofVargsInit +=1;
          } else { //no '=' contained, it is an update port.
            fbInfo->entries[ixPort].newDefined_Tstep_Tinit |= mInputUpd_Entry_DefPortType_emC;
            fbInfo->mInputVargStep   |= mBit; 
            fbInfo->nrofVargsStep +=1;
          }
        }
      } 
      ixPort +=1;  //next input line
      ixVar +=1;
    } //if 
  } while(  length_StringPartJc(sp, _thCxt) > 0 );  //text has some information.
                                                    //while ( ...entry...)
  STACKTRC_RETURN ixVar;
}




/**Returns nrofValues .
*/
int32 evalSizes_DataStructBase_Inspc  (  DataStructBase_Inspc_s* thiz) {
  int nrofValues = 0;
  for (int ixArg = 0; ixArg < thiz->zVariable; ++ixArg) {
    Entry_DefPortType_emC const* portInfo = thiz->varParams[ixArg].ePort;
    int nrofBytesVal = 0;
    //define the type , it is defined for special cases already.
    bool bComplex = portInfo->type >= 'a';
    int cType;
    char cTypeChar = portInfo->type; //from Port
    switch (cTypeChar) {
    case 'D': nrofBytesVal = 8; cType = kREFLECTION_double_ClassJc; break;
    case 'd': nrofBytesVal = 16; cType = kREFLECTION_complexdouble_ClassJc; break;
    case 'F': nrofBytesVal = 4; cType = kREFLECTION_float_ClassJc; break;
    case 'f': nrofBytesVal = 8; cType = kREFLECTION_complexfloat_ClassJc; break;
    case 'I': nrofBytesVal = 4; cType = kREFLECTION_int32_ClassJc; break;
    case 'i': nrofBytesVal = 8; cType = kREFLECTION_int32_ClassJc; break;
    case 'U': nrofBytesVal = 4; cType = kREFLECTION_uint32_ClassJc; break;
    case 'S': nrofBytesVal = 2; cType = kREFLECTION_int16_ClassJc; break;
    case 'W': nrofBytesVal = 2; cType = kREFLECTION_uint16_ClassJc; break;
    case 'B': nrofBytesVal = 1; cType = kREFLECTION_int8_ClassJc; break;
    case 'V': nrofBytesVal = 1; cType = kREFLECTION_uint8_ClassJc; break;
    case 'C': nrofBytesVal = 1; cType = kREFLECTION_char_ClassJc; break;
    case 'Z': nrofBytesVal = 1; cType = kREFLECTION_boolean_ClassJc; break;
    case 'H': nrofBytesVal = 4; cType = kREFLECTION_uint32_ClassJc; break;
      //Bus: type = 0x20
    default: cType = REFLECTION_uint32_ClassJc; nrofBytesVal = 4; 
    } //switch
    int sizeArray = portInfo->sizeArray[0]; //0 possible if scalar. 
    if (sizeArray > 1) {                           //==1: remain 0 for scalar.
      nrofBytesVal *= sizeArray;
    }
    thiz->varParams[ixArg].nrofBytesValue = nrofBytesVal;
    nrofValues += (nrofBytesVal +3)>>2;
  }
  return nrofValues;  //counts in 4-byte-steps
}






void evalNamesCreateFields_DataStructBase_Inspc  (  DataStructBase_Inspc_s* thiz, FieldJcArray* fields, int ixFieldStart, ThCxt* _thCxt) { 
  STACKTRC_TENTRY("evalNamesCreateFields_DataStructBase_Inspc");
  int ixField = ixFieldStart;
  for (int ixArg = 0; ixArg < thiz->zVariable; ++ixArg) {
    Entry_DefPortType_emC const* portInfo = thiz->varParams[ixArg].ePort;
    thiz->varParams[ixArg].ixField = ixField;
    FieldJc* field = &fields->data[ixField];  //was allocated. Filled with 0 yet.
                                              //Note: an element for ixData is sizeof(int32)
    field->bitModifiers = 0;
    field->type_ = null; //not defined yet.
    field->nrofArrayElementsOrBitfield_ = 0; //default: scalar
    int nrofBytesVal = 0;
    //
    if (thiz->varParams[ixArg].typeRef[0] !=0) { //type is given
      char cType = portInfo->type;
      if (cType == 'U' || cType == 'H') { //und an uint32 input: it's a handle
        field->bitModifiers |= kHandlePtr_Modifier_reflectJc | kReference_Modifier_reflectJc;  //mark handle in reflection
                                                                                               //create, set and fill typeClass
        ClassJc* typeClass = (ClassJc*)os_allocMem(sizeof(ClassJc)); //new typeclass, may be exists with same name anywhere else
        field->type_ = typeClass;
        typeClass->modifiers = mObjectJc_Modifier_reflectJc;  //take runtime type from src.
        strncpy_emC(typeClass->name, thiz->varParams[ixArg].typeRef, sizeof(typeClass->name));
        nrofBytesVal = sizeof(uint32); //handle
      }
      else { //any other type then uint32
             //thiz->dataTypeSmlkInput[ixArg] = 'P'; //Pointer
             //TODO: this branch is not used and not tested. It is not ready to use yet. Not a requirement (?)
        THROW_s0(IllegalArgumentException, "A type reference can only be used with handle", cType, ixArg);
        field->bitModifiers |= kStaticArray_Modifier_reflectJc | kReference_Modifier_reflectJc;
        nrofBytesVal = sizeof(void*); //pointer
      }
    }
    if (thiz->varParams[ixArg].accessRights > 0) {
      int acc = thiz->varParams[ixArg].accessRights;
      if(acc <8){
        field->bitModifiers |= (acc << kBitAccessLevel_Modifier_FieldJc) & mAccessLevel_Modifier_FieldJc;
      } else {
        int acc1 = (acc / 10) %10;
        if(acc1>7){ acc1 = 7; }
        field->bitModifiers |= (acc1 << kBitAccessLevel_Modifier_FieldJc) & mAccessLevel_Modifier_FieldJc;
        int accChg = acc % 10;  //modulo
        if (accChg>7) { accChg = 7; }
        field->bitModifiers |= (accChg << kBitChangeLevel_Modifier_FieldJc) & mChangeLevel_Modifier_FieldJc;
      }
    }
    //
    if (field->type_ == null) {
      //define the type , it is defined for special cases already.
      bool bComplex = portInfo->type >= 'a';
      int cType;
      char cTypeChar = portInfo->type; //from Port
      switch (cTypeChar) {
      case 'D': nrofBytesVal = 8; cType = kREFLECTION_double_ClassJc; break;
      case 'd': nrofBytesVal = 16; cType = kREFLECTION_complexdouble_ClassJc; break;
      case 'F': nrofBytesVal = 4; cType = kREFLECTION_float_ClassJc; break;
      case 'f': nrofBytesVal = 8; cType = kREFLECTION_complexfloat_ClassJc; break;
      case 'I': nrofBytesVal = 4; cType = kREFLECTION_int32_ClassJc; break;
      case 'i': nrofBytesVal = 8; cType = kREFLECTION_int32_ClassJc; break;
      case 'U': nrofBytesVal = 4; cType = kREFLECTION_uint32_ClassJc; break;
      case 'S': nrofBytesVal = 2; cType = kREFLECTION_int16_ClassJc; break;
      case 'W': nrofBytesVal = 2; cType = kREFLECTION_uint16_ClassJc; break;
      case 'B': nrofBytesVal = 1; cType = kREFLECTION_int8_ClassJc; break;
      case 'V': nrofBytesVal = 1; cType = kREFLECTION_uint8_ClassJc; break;
      case 'C': nrofBytesVal = 1; cType = kREFLECTION_char_ClassJc; break;
      case 'Z': nrofBytesVal = 1; cType = kREFLECTION_boolean_ClassJc; break;
      case 'H': nrofBytesVal = 4; cType = kREFLECTION_uint32_ClassJc; break;
        //Bus: type = 0x20
      default: cType = REFLECTION_uint32_ClassJc; nrofBytesVal = 4; 
      } //switch
      *(intptr_t*)&field->type_ = cType; //casting: store identifier for basic type.;
    }
    if (field->nrofArrayElementsOrBitfield_ == 0) {  //already special determined do not change. 
      int sizeArray = portInfo->sizeArray[0]; //0 possible if scalar. 
      if (sizeArray > 1) {                           //==1: remain 0 for scalar.
        nrofBytesVal *= sizeArray;
        field->nrofArrayElementsOrBitfield_ = sizeArray;
        field->bitModifiers |= kStaticArray_Modifier_reflectJc;
      }
    }
    thiz->varParams[ixArg].nrofBytesValue = nrofBytesVal;
    strncpy_emC(field->name, thiz->varParams[ixArg].name, sizeof(field->name));
    ixField += 1;
  } //for
  STACKTRC_RETURN; // (ixField<<16) + ixData;
}


#endif //DEF_REFLECTION_FULL
