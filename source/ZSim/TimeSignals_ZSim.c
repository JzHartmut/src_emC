#include "TimeSignals_ZSim.h"
#include <Inspc/FBaccess_Inspc.h>
#include <Jc/FileIoJc.h>
#include <Jc/StringJc.h>
#include <J1c/StringFunctionsJc.h>
#include <stdlib.h>
#include <string.h>

#include "TimeSignals_ZSim_Refl.crefl"

TimeSignals_ZSim* create_TimeSignals_ZSim(int zEntries)
{ TimeSignals_ZSim* thiz = null;
  //int zBytesEntries = zEntries * sizeof(Entry_TimeSignals_ZSim) + sizeof(ObjectArrayJc);
  Entries_TimeSignals_ZSim* entries = (Entries_TimeSignals_ZSim*)new_ObjectArrayJc(zEntries, sizeof(Entry_TimeSignals_ZSim), null, 0); //(Entry_TimeSignals_ZSim*)malloc(zBytesEntries);
  if(entries !=null) {
    //ctoro_ObjectArrayJc(&entries->head.object, zEntries, sizeof(Entry_TimeSignals_ZSim), null, 0);
    //memset(entries, 0, zBytesEntries);
    thiz = (TimeSignals_ZSim*)malloc(sizeof(TimeSignals_ZSim));
    if(thiz !=null) {
      memset(thiz, 0, sizeof(TimeSignals_ZSim));
      thiz->entries = entries;
    }
  }
  return thiz;
}


void ctor_TimeSignals_ZSim(TimeSignals_ZSim* thiz, int nrofEntries)
{
  Entries_TimeSignals_ZSim* entries = (Entries_TimeSignals_ZSim*)new_ObjectArrayJc(nrofEntries, sizeof(Entry_TimeSignals_ZSim), null, 0); //(Entry_TimeSignals_ZSim*)malloc(zBytesEntries);
  thiz->entries = entries;
  //now constructs.  
  ctor_TimeSignals_ZSim(thiz);
}

void ctor_TimeSignals_ZSim(TimeSignals_ZSim* thiz)
{
  strncpy(thiz->clazz.name, "TimeSignals_ZSim", sizeof(thiz->clazz.name));
  //thiz->fields.head.
  thiz->clazz.nSize = sizeof(*thiz);
  thiz->clazz.attributes = &thiz->fields;
  int ix;
  int nrofFields = 0;
  for(ix = 0; ix < ARRAYLEN_SimpleC(thiz->names); ++ix) {
    char const* name;
    if(thiz->names[ix][0] == 0){
      name =  "?";  //unused field
    } else {
      name = thiz->names[ix];
      nrofFields = ix;  //set lastly with the highest number of active field.
    }
    FieldJc* field = &thiz->fields.data[ix];
    field->type_ = REFLECTION_float;
    field->position = offset_MemAreaC(thiz, &thiz->y[ix]);
    strncpy(field->name, name, sizeof(field->name)-1);
  }
  FieldJc* field = &thiz->fields.data[++nrofFields];
  field->type_ = &reflection_TimeSignals_ZSim;  
  field->position = 0;
  strncpy(field->name, "thiz$TimeSignals_ZSim", sizeof(field->name)-1);
  thiz->fields.head.length = nrofFields +1;
}



bool registerReflection_TimeSignals_ZSim(TimeSignals_ZSim* thiz, struct FBaccessNode_Inspc_t* reflNode)
{ return registerRefl_FBaccessNode_Inspc(reflNode, thiz, thiz->nameRefl, &thiz->clazz);
}


#define MAXTIME 1e36f




static void parseLine_TimeSignals_ZSim(TimeSignals_ZSim* thiz, StringJc line, int posStart, ThCxt* _thCxt)
{ int32 posNext = posStart;
  STACKTRC_TENTRY("parseLine_TimeSignals_ZSim");
  int posColon = indexOf_CI_StringJc(line, ':', posStart);
  if(posColon > 0){ //time found.
    float time = parseFloat_SiiciY_StringFunctionsJc(line, posStart, posColon, '.', null, _thCxt);
    posNext = posColon +1;
    int maxWhileNext = 100;
    while(maxWhileNext >=0 && posNext >0) {
      int posName = indexNoWhitespace_StringFunctionsJc(*(CharSequenceJc_Ref*)&line, posNext, -1, _thCxt );
      posNext = indexAfterIdentifier_StringFunctionsJc(*(CharSequenceJc_Ref*)&line, posName, -1, null_StringJc, _thCxt );
      if(posNext > posName) {
        StringJc name = substring_StringJc(line, posName, posNext, _thCxt);
        int ixName = -1;
        int zNames = ARRAYLEN_SimpleC(thiz->names);
        while(++ixName < zNames && !equals_z_StringJc(name, thiz->names[ixName]));  //search name
        if(ixName < zNames) {
          int posValue = indexOf_CI_StringJc(line, '=', posNext) +1;
          if(posValue >0 ) { //if = not found, it is 0 because +1
            posValue = indexNoWhitespace_StringFunctionsJc(*(CharSequenceJc_Ref*)&line, posValue, -1, _thCxt );
            int32 nrofCharsParsed;
            float value = parseFloat_SiiciY_StringFunctionsJc(line, posValue, 99999, '.', &nrofCharsParsed, _thCxt);
            if(nrofCharsParsed > 0){ //a value scanned?
              //an entry necessary: Search position:
              int ixEntries = 0;
              while(ixEntries < thiz->entries->head.length && thiz->entries->data[ixEntries].time < time) { ixEntries +=1; }
              //ixEntries found:
              if(ixEntries < thiz->entries->head.length) {
                if(thiz->entries->data[ixEntries].time < MAXTIME) {
                  int zBytes = sizeof(Entry_TimeSignals_ZSim) * (thiz->entries->head.length - ixEntries -1);
                  if(zBytes > 0){
                    memmove(&thiz->entries->data[ixEntries+1], &thiz->entries->data[ixEntries], zBytes);  //memmove(dst, src, length) 
                  } else { //overwrite last entry, too much.
                    thiz->errorCfg |= 0x20000000;
                  }
                }
                Entry_TimeSignals_ZSim* entry = &thiz->entries->data[ixEntries];
                entry->time = time;
                entry->ixChannel = ixName;
                entry->value = value;
              }
            }
            posNext = posValue + nrofCharsParsed; //posNext after value.
          } 
          //else : posNext is after identifier
        } //if name found.
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





bool readConfig_TimeSignals_ZSim(TimeSignals_ZSim* thiz)
{
  STACKTRC_ENTRY("readConfig_TimeSignals_ZSim");
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
      Entry_TimeSignals_ZSim* entry = &thiz->entries->data[ixEntries];
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
          posStart = indexNoWhitespace_StringFunctionsJc(*(CharSequenceJc_Ref*)&line, posStart+6, -1, _thCxt );
          if(posStart < zLine && charAt_StringJc(line, posStart)!= '#') { //not a comment line 
            parseLine_TimeSignals_ZSim(thiz, line, posStart, _thCxt);
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




void step_TimeSignals_ZSim(TimeSignals_ZSim* thiz, float time)
{ int ixChannel;
  int maxWhile = 1000;
  while(--maxWhile >=0 && time >= thiz->stepNext && thiz->ixEntries < thiz->entries->head.length) { //kurze Abfrage in jeder step, normalerweise ist time < thiz->stepNext
    if(time < thiz->entries->data[thiz->ixEntries].time) {
      thiz->stepNext = thiz->entries->data[thiz->ixEntries].time;  //stepNext stand falsch. Richtig intialisieren.
    } else {
      Entry_TimeSignals_ZSim* entry = &thiz->entries->data[thiz->ixEntries]; //dieser entry ist dran.          
      ixChannel = entry->ixChannel;
      if(ixChannel >=0 && ixChannel < 16){ //assert correct work
        thiz->y[ixChannel] = entry->value;
        if(entry->value == 0){
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
    if(thiz->y[ixChannel] !=0){
      bits |= 1;
    }
  }
  thiz->yBits = bits;
}






void free_TimeSignals_ZSim(TimeSignals_ZSim* thiz)
{
  if(thiz !=null){
    free_ObjectArrayJc(&thiz->entries->head);
    free(thiz);
  }
}



void test_TimeSignals_ZSim(struct FBaccessNode_Inspc_t* reflNode)
{

  static TimeSignals_ZSim* test = create_TimeSignals_ZSim(100);
  //strncpy(test->channels, "cUAN_on_CCP cOn_CBB_CCP", sizeof(test->channels));
  strncpy(test->nameRefl,"test_TimeSignals", sizeof(test->nameRefl));
  strncpy(test->names[0], "cUAN_on_CCP", sizeof(test->names[0]));
  strncpy(test->names[1], "cOn_CBB_CCP", sizeof(test->names[0]));
  strncpy(test->names[2], "wUAm", sizeof(test->names[0]));
  strncpy(test->names[3], "wUAw", sizeof(test->names[0]));
  ctor_TimeSignals_ZSim(test);
  
  registerReflection_TimeSignals_ZSim(test, reflNode);
  
  strncpy(test->filepath, "D:\\SFC\\SBOX\\CCS_simulink\\data\\XRPDC\\simulink\\testScenarios\\Test_IA_UTT2\\stimuli_Test_IA_UTT2.m", sizeof(test->filepath));
  readConfig_TimeSignals_ZSim(test);
  for(int step = 0; step < 100; ++step) {
    step_TimeSignals_ZSim(test, 0.05f * step);
  }
  //free_TimeSignals_ZSim(test);
}

