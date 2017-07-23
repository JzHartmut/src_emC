#include "TimeSignals_Inspc.h"
#include <Inspc/FBaccess_Inspc.h>
#include <Jc/FileIoJc.h>
#include <Jc/StringJc.h>
#include <J1c/StringFunctionsJc.h>
#include <J1c/StringFunctions_CJc.h>
#include <stdlib.h>
#include <string.h>

#include "TimeSignals_Inspc_Refl.crefl"

TimeSignals_Inspc* create_TimeSignals_Inspc(int zEntries)
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



void ctor_TimeSignals_Inspc(TimeSignals_Inspc* thiz, int nrofEntries)
{
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
    if(thiz->names[ix][0] == 0){
      name =  "?";  //unused field
    } else {
      char const* posColon = strchr(thiz->names[ix], ':');
      if(posColon !=null) {
        int cComplex = thiz->names[ix][0];
        int cVector;
        if (cComplex == 'C') { cVector = thiz->names[ix][1]; }
        else { cVector = thiz->names[ix][0]; }
        if (cVector >= '1' && cVector <= '6') {
          thiz->nrElements[ix] = cVector - '0';
        } else {
          thiz->nrElements[ix] = 1;
        }
        if(cComplex == 'C') {
          thiz->bitsComplexY |= 1<<ix; 
        }
        int nPosColon = posColon - thiz->names[ix]; 
        int nrChars = zNames - nPosColon;
        //adjust the name,without type information.
        memmove(thiz->names[ix], &thiz->names[ix][nPosColon+1], zNames - nPosColon -1);
        memset(&thiz->names[ix][zNames - nPosColon -1], 0, nPosColon+1);
      }
      name = thiz->names[ix];
      nrofFields = ix;  //set lastly with the highest number of active field.
    }
    FieldJc* field = &thiz->fields.data[ix];
    field->type_ = (thiz->bitsComplexY & (1<<ix)) ? &reflection_float_complex : REFLECTION_float;
    field->position = offset_MemAreaC(thiz, &thiz->ya0[6*ix]);  //TRICKY: address ya0..ya15
    field->nrofArrayElementsOrBitfield_ = thiz->nrElements[ix];
    strncpy(field->name, name, sizeof(field->name)-1);
  }
  FieldJc* field = &thiz->fields.data[++nrofFields];
  field->type_ = &reflection_TimeSignals_Inspc;  
  field->position = 0;
  strncpy(field->name, "thiz$TimeSignals_Inspc", sizeof(field->name)-1);
  thiz->fields.head.length = nrofFields +1;
}



bool registerReflection_TimeSignals_Inspc(TimeSignals_Inspc* thiz, struct DataNode_Inspc_t* reflNode)
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
                    thiz->errorCfg |= 0x20000000;
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
            thiz->errorCfg = 0x20000;
          }
        } //faulty module.
      } //name not exists.
      //search next variable:
      posNext = indexOf_CI_StringJc(line, ',', posNext) +1;  //0 if not found, then abort while. Else: more as one variable with the same time.
    }
    if(maxWhileNext <0){
      thiz->errorCfg |= 0x40000000;
    }
  }
  STACKTRC_LEAVE;
}





bool readConfig_TimeSignals_Inspc(TimeSignals_Inspc* thiz)
{
  STACKTRC_ENTRY("readConfig_TimeSignals_Inspc");
  if(thiz->filepath == null || thiz->filepath[0] == 0){
    thiz->errorCfg = 0x01000000;
    return false;
  }
  OS_HandleFile hfile = os_fopenToRead(thiz->filepath);
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
        thiz->errorCfg +=1; 
      }
      END_TRY
    }
    if(maxWhileLines <0){
      thiz->errorCfg |= 0x80000000;
    }
    //it would not close the file because the file is given outside:
    //close_BufferedReaderJc(&reader);
    os_fclose(hfile);
    return true;
  } else {
    thiz->errorCfg = 0x02000000;
    return false;
  }  
  STACKTRC_LEAVE;
}




void step_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float time)
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
        thiz->errorCfg |= 0x10000;
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






void free_TimeSignals_Inspc(TimeSignals_Inspc* thiz)
{
  if(thiz !=null){
    free_ObjectArrayJc(&thiz->entries->head);
    free(thiz);
  }
}



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

