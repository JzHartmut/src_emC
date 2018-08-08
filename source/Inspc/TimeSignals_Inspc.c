#include "TimeSignals_Inspc.h"
#include <Inspc/FBaccess_Inspc.h>
#include <Jc/FileIoJc.h>
#include <Jc/StringJc.h>
#include <Fwc/objectBaseC.h>
#include <J1c/StringFunctionsJc.h>
#include <J1c/StringFunctions_CJc.h>
#include <stdlib.h>
#include <string.h>

#include "genRefl/Inspc/TimeSignals_Inspc.crefl"
//extern_C ClassJc const reflection_TimeSignals_Inspc;


TimeSignals_Inspc* XXXXXcreate_TimeSignals_Inspc(int zEntries)
{ TimeSignals_Inspc* thiz = null;
  //int zBytesEntries = zEntries * sizeof(Entry_TimeSignals_Inspc) + sizeof(ObjectArrayJc);
  Entries_TimeSignals_Inspc* entries = (Entries_TimeSignals_Inspc*)new_ObjectArrayJc(zEntries, sizeof(Entry_TimeSignals_Inspc), null, 0); //(Entry_TimeSignals_Inspc*)malloc(zBytesEntries);
  if(entries !=null) {
    //ctoro_ObjectArrayJc(&entries->head.object, zEntries, sizeof(Entry_TimeSignals_Inspc), null, 0);
    //memset(entries, 0, zBytesEntries);
    thiz = (TimeSignals_Inspc*)malloc(sizeof(TimeSignals_Inspc));
    if(thiz !=null) {
      memset(thiz, 0, sizeof(TimeSignals_Inspc));
      thiz->entries = entries;
    }
  }
  return thiz;
}

extern_C const ClassJc reflection_float_complex;  //the just defined reflection_





//new since 2017-07-29
void ctor_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float Tstep, char const filepath[200], StringJc reflName, int nrofEntries
, StringJc name1, StringJc name2, StringJc name3, StringJc name4
, StringJc name5, StringJc name6, StringJc name7, StringJc name8
, StringJc name9, StringJc name10, StringJc name11, StringJc name12
, StringJc name13, StringJc name14, StringJc name15, StringJc name16
)
{
  //PRINTF_OPEN("T:\\TimeSignals");
  StringJc names[16];
  int zName = copyToBuffer_StringJc(reflName, 0, -1, thiz->nameModule, sizeof(thiz->nameModule));
  names[0] = name1;   //copy extra arguments, use in for loop.
  names[1] = name2;
  names[2] = name3;
  names[3] = name4;
  names[4] = name5;
  names[5] = name6;
  names[6] = name7;
  names[7] = name8;
  names[8] = name9;
  names[9] = name10;
  names[10] = name11;
  names[11] = name12;
  names[12] = name13;
  names[13] = name14;
  names[14] = name15;
  names[15] = name16;
  Entries_TimeSignals_Inspc* entries = (Entries_TimeSignals_Inspc*)new_ObjectArrayJc(nrofEntries, sizeof(Entry_TimeSignals_Inspc), null, 0); //(Entry_TimeSignals_Inspc*)malloc(zBytesEntries);
  thiz->entries = entries;
  //now constructs.  
  memset(thiz->nrElements, 1, sizeof(thiz->nrElements));
  thiz->bitsComplexY = 0;
  strncpy(thiz->clazz.name, "TimeSignals_Inspc", sizeof(thiz->clazz.name));
  //thiz->fields.head.
  thiz->clazz.nSize = sizeof(*thiz);
  thiz->clazz.attributes = &thiz->fields;
  int ix;
  int nrofFields = 0;
  int zNames = sizeof(thiz->names[0]); //length of name field inclusive \0
  for(ix = 0; ix < ARRAYLEN_SimpleC(thiz->names); ++ix) {
    char const* name;
    int zName = length_StringJc(names[ix]);
    char nameBuffer[32] = {0};  //only used if necessary, if names[ix] is not 0-terminated.
    name = getCharConst_StringJc(names[ix], nameBuffer, 32);  //name is char const* from names[ix]
    if( zName == 0){
      name =  "?";  //unused field
    } else {
      char const* posColon = strchr(name, ':');
      if(posColon !=null) {
        int cComplex = name[0];
        int cVector;
        if (cComplex == 'C') { cVector = name[1]; }
        else { cVector = name[0]; }
        if (cVector >= '1' && cVector <= '6') {
          thiz->nrElements[ix] = cVector - '0';
        } else {
          thiz->nrElements[ix] = 1;
        }
        if(cComplex == 'C') {
          thiz->bitsComplexY |= 1<<ix; 
        }
        int nPosColon = posColon - name +1;  //Difference of char* 
        int nrChars = zName - nPosColon;
        //adjust the name,without type information.
        name += nPosColon;  //char const* shift.
        zName -= nPosColon;
      }
      if(zName >= ARRAYLEN_SimpleC(thiz->names[0])) {
        zName = ARRAYLEN_SimpleC(thiz->names[0])-1;
      } 
      strncpy(thiz->names[ix], name, zName);  //with 0-terminate
      nrofFields = ix;  //set lastly with the highest number of active field.
    }
    FieldJc* field = &thiz->fields.data[ix];
    field->type_ = (thiz->bitsComplexY & (1<<ix)) ? &reflection_float_complex : REFLECTION_float;
    field->position = offset_MemAreaC(thiz, &thiz->ya0[6*ix]);  //TRICKY: address ya0..ya15
    if(thiz->nrElements[ix] >1) {
      field->nrofArrayElementsOrBitfield_ = thiz->nrElements[ix];
      field->bitModifiers = kStaticArray_Modifier_reflectJc;
    } else {
      field->nrofArrayElementsOrBitfield_ = 0;
    }
    strncpy(field->name, name, sizeof(field->name)-1);
  }
  FieldJc* field = &thiz->fields.data[++nrofFields]; //the last visible field in Inspector is thiz itself.
  field->type_ = &reflection_TimeSignals_Inspc;  
  field->position = 0;
  strncpy(field->name, "thiz$TimeSignals_Inspc", sizeof(field->name)-1);
  thiz->fields.head.length = nrofFields +1;
  //
  //{ //store file name as char const*
  //  int zFilepath = copyToBuffer_StringJc(filepath, 0, -1, thiz->filepath, sizeof(thiz->filepath)-1);
  //  thiz->filepath[zFilepath] = 0;
    //PRINTF2("TimeSignals - Filepath %s\n", thiz->filepath);
  readConfig_TimeSignals_Inspc(thiz, filepath);
  //}
}



//The nrofInputPorts is 1, index for first output in dst is 1.
int defOutputPorts_TimeSignals_Inspc(DefPortTypesJc* dst
, StringJc name1, StringJc name2, StringJc name3, StringJc name4
, StringJc name5, StringJc name6, StringJc name7, StringJc name8
, StringJc name9, StringJc name10, StringJc name11, StringJc name12
, StringJc name13, StringJc name14, StringJc name15, StringJc name16
)
{ int zDst = dst->size;
  Entry_DefPortTypeJc* adst = dst->entries;
  int ix;
  StringJc names[16];
  names[0] = name1;   //copy extra arguments, use in for loop.
  names[1] = name2;
  names[2] = name3;
  names[3] = name4;
  names[4] = name5;
  names[5] = name6;
  names[6] = name7;
  names[7] = name8;
  names[8] = name9;
  names[9] = name10;
  names[10] = name11;
  names[11] = name12;
  names[12] = name13;
  names[13] = name14;
  names[14] = name15;
  names[15] = name16;
  if(zDst >= 18) {  //only run for 1 Input + 17 Ouput ports, not for bits_TimeSignals_Inspc(...) 
    for(ix = 0; ix < 16; ++ix) {  //ix = 0 .. for output port from 0
      int ixdst = ix +1;  //nrofInput = 1, from output arg 0, adequate to step routine argument list! no-thizInit, no-thizStep is set. 
      if(ixdst >= zDst) { ixdst = 0; } //fatal, unexpected.
      char const* name;
      int zName = length_StringJc(names[ix]);
      if( zName == 0){
        name =  "?";  //unused field
        adst[ixdst].type = 'F';  //float output by default. Note: All outputs should be determined.
        adst[ixdst].sizeType = sizeof(float);
        adst[ixdst].dimensions = 1;
        adst[ixdst].sizeArray[0] = 1;
        adst[ixdst].newDefined = 1;
      } else {
        char nameBuffer[32] = {0};
        char const* name = getCharConst_StringJc(names[ix], nameBuffer, 32); 
        char const* posColon = strchr(name, ':');
        if(posColon !=null) {
          int cComplex = name[0];
          int cVector;
          if (cComplex == 'C') { cVector = name[1]; }
        else { cComplex = 0; cVector = name[0]; }
          if (cVector >= '1' && cVector <= '6') {
            adst[ixdst].sizeArray[0] = cVector - '0';
          }
          else { 
            adst[ixdst].sizeArray[0] = 0; //scalar 
          }
          adst[ixdst].type = 'F';
          adst[ixdst].sizeType = sizeof(float);
          if(cComplex) {
            adst[ixdst].type += 'a'-'A';
            adst[ixdst].sizeType *= 2;
          } 
        }
        else {
          adst[ixdst].type = 'F'; //standard is simple float
          adst[ixdst].sizeArray[0] = 0;
        }
        adst[ixdst].newDefined = 1;
      } 
    }
  }
  return zDst;
}




char const* init_TimeSignals_Inspc(TimeSignals_Inspc* thiz, struct DataNode_Inspc_t* reflNode)
{
  registerRefl_DataNode_Inspc(reflNode, thiz, thiz->nameModule, &thiz->clazz);
  setInitialized_ObjectJc(&thiz->base);
  return null;
}






bool XXXXXregisterReflection_TimeSignals_Inspc(TimeSignals_Inspc* thiz, struct DataNode_Inspc_t* reflNode)
{ return registerRefl_DataNode_Inspc(reflNode, thiz, thiz->nameModule, &thiz->clazz);
}


#define MAXTIME 1e36f




static void parseLine_TimeSignals_Inspc(TimeSignals_Inspc* thiz, StringJc line, int posStart, ThCxt* _thCxt)
{ int zLine = length_StringJc(line);
  int posNext = posStart;
  STACKTRC_TENTRY("parseLine_TimeSignals_Inspc");
  int posColon = indexOf_CI_StringJc(line, ':', posStart);
  if(posColon > 0){ //time found.
    float time = parseFloat_CsiiciY_StringFunctions_CJc(line, posStart, posColon, '.', null, _thCxt);
    posNext = posColon +1;
    int maxWhileNext = 100;
    while(maxWhileNext >=0 && posNext >0) { //search value asignments, posNext is position after separator for values.
      int posName = indexNoWhitespace_StringFunctionsJc(line, posNext, -1, _thCxt );
      posNext = indexAfterIdentifier_StringFunctionsJc(line, posName, -1, null_StringJc, _thCxt );
      if(posNext > posName && posNext < zLine && charAt_StringJc(line, posNext) == '.') {
        StringJc nameModule = substring_StringJc(line, posName, posNext, _thCxt);
        if(equals_z_StringJc(nameModule, thiz->nameModule)) {
          posName = posNext +1; //name inside moduel.
          posNext = indexAfterIdentifier_StringFunctionsJc(line, posName, -1, null_StringJc, _thCxt );
          StringJc name = substring_StringJc(line, posName, posNext, _thCxt);
          int ixName = -1;
          int zNames = ARRAYLEN_SimpleC(thiz->names);
          while(++ixName < zNames && !equals_z_StringJc(name, thiz->names[ixName]));  //search name
          if(ixName < zNames) {
            //name in line found in this stimuli block:
            int posValue = indexOf_CI_StringJc(line, '=', posNext) +1;
            if(posValue >0 ) { //if = not found, it is 0 because +1
              //an entry necessary: Search position:
              int ixEntries = 0;
              while(ixEntries < thiz->entries->head.length && thiz->entries->data[ixEntries].time < time) { ixEntries +=1; }
              //ixEntries found:
              Entry_TimeSignals_Inspc* entry;
              if(ixEntries < thiz->entries->head.length) {
                if(thiz->entries->data[ixEntries].time < MAXTIME) {
                  int zBytes = sizeof(Entry_TimeSignals_Inspc) * (thiz->entries->head.length - ixEntries -1);
                  if(zBytes > 0){
                    memmove(&thiz->entries->data[ixEntries+1], &thiz->entries->data[ixEntries], zBytes);  //memmove(dst, src, length) 
                  } else { //overwrite last entry, too much.
                    thiz->errorCfg |= mTooMuchEntries_TimeSignals_Inspc;  //too much entries
                  }
                }
                entry = &thiz->entries->data[ixEntries];
              } else {
                entry = null; //no space.
              }
              int zValues = ARRAYLEN_SimpleC(((Entry_TimeSignals_Inspc*)0)->ya);
              int ixValue = 0;
              int32 nrofCharsParsed;
              do {
                posValue = indexNoWhitespace_StringFunctionsJc(line, posValue, -1, _thCxt );
                float value = parseFloat_CsiiciY_StringFunctions_CJc(line, posValue, 99999, '.', &nrofCharsParsed, _thCxt);
                if(nrofCharsParsed > 0  //a value scanned?
                  && entry !=null       //an entry found? on not found entry parse the values but don't store.
                  ) {
                  entry->time = time;
                  entry->ixChannel = ixName;
                  entry->ya[ixValue++] = value;
                }
                //posNext after value and spaces.
                posNext = indexNoWhitespace_StringFunctionsJc(line, posValue + nrofCharsParsed, -1, _thCxt );
                //don't check ',' it is the separator between names.
                //if(charAt_StringJc(line, posNext) == ',') {
                //  posNext = indexNoWhitespace_StringFunctionsJc(*(CharSequenceJc_Ref*)&line, posNext + 1, -1, _thCxt );
                //}
                posValue = posNext;
              } while(ixValue < zValues && nrofCharsParsed >0);
            }
          } else { //name in module not found though the module was found:
            thiz->errorCfg = mNameNotFound_TimeSignals_Inspc;
          }
        } //faulty module.
      } //name not exists.
      //search next variable:
      posNext = indexOf_CI_StringJc(line, ',', posNext) +1;  //0 if not found, then abort while. Else: more as one variable with the same time.
    }
    if(maxWhileNext <0){
      thiz->errorCfg |= mTooManyEntriesInLine_TimeSignals_Inspc; //too much lines
    }
  }
  STACKTRC_LEAVE;
}





bool readConfig_TimeSignals_Inspc(TimeSignals_Inspc* thiz, char const* filepath)
{
  STACKTRC_ENTRY("readConfig_TimeSignals_Inspc");
  //if(thiz->filepath == null || thiz->filepath[0] == 0){
  if(filepath[0] == 0) {
    thiz->errorCfg = mNoFileName_TimeSignal_Inspc;  //file parameter missing
    return false;
  }
  OS_HandleFile hfile = os_fopenToRead(filepath);
  if(hfile !=0){

    FileReaderJc_s fileReader = {0};
    BufferedReaderJc_s reader = {0};

    char buffer[1000] = {0};

    ctorO_FileReaderJc(&fileReader.object, hfile, _thCxt);
    ctorO_BufferedReaderJc(&reader.object, &fileReader, build_MemC(buffer, sizeof(buffer)), _thCxt);
    //fill all with maxtime initially
    int ixEntries = -1;
    while(++ixEntries < thiz->entries->head.length){
      Entry_TimeSignals_Inspc* entry = &thiz->entries->data[ixEntries];
      entry->time = MAXTIME;  //1 millionen Simulationssekunden.
    }
    //    
    StringJc line;
    int maxWhileLines = 100000;
    while( line = readLine_BufferedReaderJc(&reader, _thCxt)  //Note: statement in while, separated with ,
         , --maxWhileLines >=0 && !isNull_StringJc(line)      //condition.
         ){
      TRY {
        int zLine = length_StringJc(line);
        int32 posStart = indexOf_z_StringJc(line, "%time:");
        if(posStart >=0){
          posStart = indexNoWhitespace_StringFunctionsJc(line, posStart+6, -1, _thCxt );
          if(posStart < zLine && charAt_StringJc(line, posStart)!= '#') { //not a comment line 
            parseLine_TimeSignals_Inspc(thiz, line, posStart, _thCxt);
          }
        }
      }_TRY
      CATCH(ExceptionJc, exc) {
        thiz->errorCfg |= mExceptionReadFile_TimeSignal_Inspc; 
      }
      END_TRY
    }
    if(maxWhileLines <0){
      thiz->errorCfg |= mTooManyLines_TimeSignals_Inspc;
    }
    //it would not close the file because the file is given outside:
    //close_BufferedReaderJc(&reader);
    os_fclose(hfile);
    STACKTRC_LEAVE;
    return true;
  } else {
    thiz->errorCfg = mFileNotFound_TimeSignal_Inspc;  //file not found.
    STACKTRC_LEAVE;
    return false;
  }  
}


void dtor_TimeSignals_Inspc(TimeSignals_Inspc* thiz)
{ //PRINTF_CLOSE();
}



static void checkNewEntry_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float time)
{ int ixChannel;
  int maxWhile = 1000;
  while(--maxWhile >=0 && time >= thiz->stepNext && thiz->ixEntries < thiz->entries->head.length) { //kurze Abfrage in jeder step, normalerweise ist time < thiz->stepNext
    if(time < thiz->entries->data[thiz->ixEntries].time) {
      thiz->stepNext = thiz->entries->data[thiz->ixEntries].time;  //stepNext stand falsch. Richtig intialisieren.
    } else {
      Entry_TimeSignals_Inspc* entry = &thiz->entries->data[thiz->ixEntries]; //dieser entry ist dran.          
      ixChannel = entry->ixChannel;
      if(ixChannel >=0 && ixChannel < 16){ //assert correct work
        int ix;
        for(ix = 0; ix < zya_TimeSignals_Inspc; ++ix)
        {
          thiz->ya0[zya_TimeSignals_Inspc * ixChannel + ix] = entry->ya[ix];  // vector of [6]  TRICKY: address ya0..ya15
        }
        if(entry->ya[0] == 0){
          thiz->yBits &= ~(1 << entry->ixChannel);  //ruecksetzen dieses Bits
        } else {
          thiz->yBits |= (1 << entry->ixChannel);  //setzen dieses Bits
        }
      } else {
        thiz->errorCfg |= mInternalError1_TimeSignals_Inspc;
      }
      thiz->ixEntries +=1;  //check next.
      thiz->stepNext = thiz->entries->data[thiz->ixEntries].time;
    }
  }
  int16 bits = 0;
  for(ixChannel =15; ixChannel >=0; --ixChannel){ //show floats in bits, always, floats may be changed by reflection.
    bits <<=1;
    if(thiz->ya0[zya_TimeSignals_Inspc * ixChannel] !=0){
      bits |= 1;
    }
  }
  thiz->yBits = bits;
}




void values_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float _simtime
, void* val1_y, void* val2_y, void* val3_y, void* val4_y
, void* val5_y, void* val6_y, void* val7_y, void* val8_y
, void* val9_y, void* val10_y, void* val11_y, void* val12_y
, void* val13_y, void* val14_y, void* val15_y, void* val16_y
, int32* error_y
)
{
  int ix;
  void* out[16];
  float* ya = &thiz->ya0[0];
  out[0] = val1_y;
  out[1] = val2_y;
  out[2] = val3_y;
  out[3] = val4_y;
  out[4] = val5_y;
  out[5] = val6_y;
  out[6] = val7_y;
  out[7] = val8_y;
  out[8] = val9_y;
  out[9] = val10_y;
  out[10] = val11_y;
  out[11] = val12_y;
  out[12] = val13_y;
  out[13] = val14_y;
  out[14] = val15_y;
  out[15] = val16_y;
  checkNewEntry_TimeSignals_Inspc(thiz, _simtime);
  for(ix=0; ix < 16; ++ix) {
    int ixv;
    int ix1 = 6 * ix;
    ClassJc const* type = getType_FieldJc(&thiz->fields.data[ix]);
    int z = thiz->fields.data[ix].nrofArrayElementsOrBitfield_;
    if(z == 0) { z = 1; }
    if(type == &reflection__floatJc)      { 
      if(z > 6) { z = 1;} 
      for(ixv = 0; ixv < z; ++ixv) { 
        float* outAddr = (float*)(out[ix]);
        float val = ya[ix1 + ixv];
        outAddr[ixv] = val; 
        val = 0; //dummy, will be optimized. step for debug
      } 
    } else if(type == &reflection_float_complex) { 
      if(z > 3) { z = 1;} 
      for(ixv = 0; ixv < z; ++ixv) { 
        float_complex* outAddr = (float_complex*)(out[ix]);
        float_complex* val = (float_complex*)&ya[ix1 + 2 * ixv];   //use float array for float_complex
        outAddr[ixv] = *val; //it is a memcpy
        val = null; //dummy, will be optimized. step for debug  
      } 
    }
    else { 
      thiz->errorCfg |= (0x1 << ix); 
    }
  }
  *error_y = thiz->errorCfg;
}





void bits_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float _simtime
, uint16* bits_y
, int32* error_y
)
{
  int ix;
  checkNewEntry_TimeSignals_Inspc(thiz, _simtime);
  int16 bits = 0; 
  //The variables ya0, ya1 ... are arranged one after another.
  //The memory layout is the same like an array ya[16][6];
  float* ya = thiz->ya0;  
  if((thiz->ya1 - ya) !=6) {
    thiz->errorCfg |= mFaultyMemoryLayout_TimeSignals_Inspc;
  } //else 
  {
    for(ix=15; ix >=0; --ix) {
       int ix1 = 6 * ix;
       bits <<=1;
       if(ya[ix1]) { bits |=1; }
    }
  }
  *bits_y = bits;
  *error_y = thiz->errorCfg;
}





void XXXXXfree_TimeSignals_Inspc(TimeSignals_Inspc* thiz)
{
  if(thiz !=null){
    free_ObjectArrayJc(&thiz->entries->head);
    free(thiz);
  }
}


#if 0 //it is old
void test_TimeSignals_Inspc(struct DataNode_Inspc_t* reflNode, char const* path)
{

  static TimeSignals_Inspc* test;
  test = create_TimeSignals_Inspc(100);
  //strncpy(test->channels, "cUAN_on_CCP cOn_CBB_CCP", sizeof(test->channels));
  strncpy(test->nameModule,"test_TimeSignals", sizeof(test->nameModule));
  strncpy(test->names[0], "param1", sizeof(test->names[0]));
  strncpy(test->names[1], "cCmdA", sizeof(test->names[0]));
  strncpy(test->names[2], "C2:wUpq", sizeof(test->names[0]));
  strncpy(test->names[3], "2:wUw", sizeof(test->names[0]));
  ctor_TimeSignals_Inspc(test, 100);
  
  registerReflection_TimeSignals_Inspc(test, reflNode);
  
  strncpy(test->filepath, path, sizeof(test->filepath));
  readConfig_TimeSignals_Inspc(test);
  for(int step = 0; step < 100; ++step) {
    step_TimeSignals_Inspc(test, 0.05f * step);
  }
  //free_TimeSignals_Inspc(test);
}
#endif
