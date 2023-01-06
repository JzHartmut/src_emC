#include <applstdef_emC.h>
#if defined(DEF_REFLECTION_FULL) && defined(DEF_HandlePtr64) && defined(DEF_ClassJc_Vtbl)  //may be used in 32 bit without DEF_HandlePtr64 too?
#include "TimeSignals_Inspc.h"
//#include <Inspc/DataNode_Inspc.h>
#include <emC/Inspc/FB/DataStructBase_Inspc.h>
#include <emC/Base/DefPortTypes_emC.h>
#include <emC/Jc/FileIoJc.h>
#include <emC/Jc/StringJc.h>
#include <emC/base/Object_emC.h>
#include <emC/J1c/StringFunctionsJc.h>
#include <emC/J1c/StringFunctions_CJc.h>
#include <emC/OSAL/os_mem.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "emC/Inspc/FB/genRefl/TimeSignals_Inspc.crefl"
//extern_C ClassJc const refl_TimeSignals_Inspc;



extern_C const ClassJc refl_float_complex;  //the just defined refl_





//new since 2017-07-29, reengineered 2018-09
void ctor_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float Tstep, struct DefPortTypes_emC_t* fbInfo, char const filepath[500], StringJc reflName, int zTimeData
  , char const outputDefinition[500]
) {
  STACKTRC_ENTRY("ctor_TimeSignals_Inspc");
  ctor_DataStructBase_Inspc(&thiz->base.super, fbInfo, fbInfo->ixOutputVarg, fbInfo->nrofOutputs, outputDefinition);
  //
  thiz->par.stepsDynew = 2048;     //Time-steps to re-adjust the dya. Proper to 2^11 * 2^11 accuracy of floating point:
  //The addition of ddya to dya is done 2018 times. It is a chain error of numeric: Any addition has an accuracy of about 2^-23.
  //2048 additions may cause an error of 2^-12. The value-ratio dya/ddya is in range till -2^11 ..0. 
  //It means after about 2048 adding steps the error of dya reaches the range of the value of ddya. 
  //Therefore the growth dya should be determine newly after this steps for a longer constant growth (ramp in output value).
  //  
  thiz->par.testAddStepSpline = 2; //Experience: With this adding time the correcture is more exact.
  //
  thiz->Tstep = Tstep;
  copyToBuffer_StringJc(reflName, 0, -1, thiz->nameModule, sizeof(thiz->nameModule));
  //now constructs.  
  memset(thiz->nrElements, 1, sizeof(thiz->nrElements));
  thiz->bitsComplexY = 0;
  init_immediate_ObjectArrayJc(&thiz->superThiz.head, 1, sizeof(thiz->superThiz.data[0])
        , &refl_ClassOffset_idxVtblJc, ID_refl_ClassOffset_idxVtblJc | mArrayId_ObjectJc);
  ctor_ClassOffset_idxVtblJc(&thiz->superThiz.data[0], &refl_TimeSignals_Inspc, 0x22, 0);
  ctor_Fields_super_ClassJc(&thiz->clazz, z_StringJc(thiz->nameModule), 0, &thiz->fields.head, &thiz->superThiz.head);
  //
  //int ixFields = 0;
  int zFields = fbInfo->nrofOutputs -1;  //last Field for thiz 
  //TODO alloc fields

  //unnecessary: int32 nrofValuesInt32 = evalSizes_DataStructBase_Inspc(&thiz->base.super);
  
  evalNamesCreateFields_DataStructBase_Inspc(&thiz->base.super, &thiz->fields, 0, _thCxt);
  //
  //fill the correct offset. The field should refer only a part of the current values, which are the output values on pins.
  for(int ix = 0; ix < thiz->base.super.zVariable; ++ix) {
    thiz->base.super.varParams[ix].ixInVal = ix;
    thiz->fields.data[ix].offsFieldInStruct = offset_MemAreaC(thiz, &thiz->curr[ix].ya);  
  }

  thiz->fields.head.length = thiz->base.super.zVariable; // +1;
  //
  //Set the created fields as reflection of thiz
  setReflection_ObjectJc(&thiz->base.object, &thiz->clazz, -1);
  //
  //{ //store file name as char const*
  //  int zFilepath = copyToBuffer_StringJc(filepath, 0, -1, thiz->filepath, sizeof(thiz->filepath)-1);
  //  thiz->filepath[zFilepath] = 0;
  //PRINTF2("TimeSignals - Filepath %s\n", thiz->filepath);
  readConfig_TimeSignals_Inspc(thiz, filepath);
  //}
  STACKTRC_RETURN;





}








void dtor_TimeSignals_Inspc(TimeSignals_Inspc* thiz) {
  for (int ixChn = 0; ixChn < 16; ++ixChn) {
    TimeData_TimeSignals_Inspc* data = &thiz->timeData[ixChn];
    if(data->entriesChn !=null) {
      for(int ixEntry = 0; ixEntry < data->zEntryChn; ++ixEntry){
        free(data->entriesChn->d[ixEntry]);
      }
      free(data->entriesChn);
    }
  }
}




char const* definePortTypes_TimeSignals_Inspc  (  struct DefPortTypes_emC_t* fbInfo, enum EDefPortTypes_emC_t cause
  , char const outputDefinition[500]
) {
  int zEntries = MIN_emC(32, fbInfo->zEntries); //the number of entries from the SfH-Wrapper
  fbInfo->ixInputStep = 0;
  fbInfo->ixInputStep2 = 0;
  fbInfo->ixInputUpd = 0;
  fbInfo->ixInputInit = 0; //Inspc input
  fbInfo->nrofInputs = 0;
  //first output port 0 is the error state.
  set_DefPortTypes_emC(fbInfo, 0, 'U', "error", null, "", 0, mOutputStep_Entry_DefPortType_emC);
  //
  // ===>
  zEntries = analyzeVariableDef(z_StringJc(outputDefinition), null, fbInfo, fbInfo->nrofInputs +1, true, cause);
  //
  fbInfo->mOutputInit |= fbInfo->mOutputVargInit;
  fbInfo->mOutputStep |= fbInfo->mOutputVargStep;
  //
  fbInfo->nrofOutputs = zEntries+2;
  fbInfo->ixOutputStep = 0;
  fbInfo->ixOutputStep2 = zEntries;
  fbInfo->ixOutputInit = zEntries;
  fbInfo->ixOutputThizInit = zEntries+1;
  //output ports:
  set_DefPortTypes_emC(fbInfo, zEntries+1, 'H', "thiz", null, "", 0, mOutputInit_Entry_DefPortType_emC);
  return null;
}



bool init_TimeSignals_Inspc(TimeSignals_Inspc* thiz) //, struct DataNode_Inspc_t* reflNode)
{
  //if(reflNode == null) return false;
  //if(((intptr_t)reflNode)==-1) { reflNode = null; } //-1 admissible, then nothing regisztered
  //registerRefl_DataNode_Inspc(reflNode, thiz, thiz->nameModule, &thiz->clazz);
  setInitialized_ObjectJc(&thiz->base.object);
  return true;
}








static int createNewEntry(TimeSignals_Inspc* thiz, int ixChn, float time) {
  TimeData_TimeSignals_Inspc* dataChn = &thiz->timeData[ixChn];
  if (dataChn->entriesChn == null) {
    int allocBytes = 1000 * sizeof(Entry_TimeSignals_Inspc*);
    Array_Entry_TimeSignals_Inspc* arrayEntries = (Array_Entry_TimeSignals_Inspc*) malloc(allocBytes);
    memset(arrayEntries, 0, allocBytes);
    dataChn->entriesChn = arrayEntries; //casting admissible, same type of pointer.
    if(time >0.0f) {
      Entry_TimeSignals_Inspc* entry0 = (Entry_TimeSignals_Inspc*) malloc(sizeof(Entry_TimeSignals_Inspc));
      memset(entry0, 0, sizeof(*entry0));
      dataChn->entriesChn->d[0] = entry0;
      dataChn->zEntryChn = 1;
    } else {
      dataChn->zEntryChn = 0;
    }
  }
  int ixEntry = 0;
  while (ixEntry < dataChn->zEntryChn && dataChn->entriesChn->d[ixEntry]->timeStart <= time){
    ixEntry +=1;  //search in time.
  }
  if(ixEntry < dataChn->zEntryChn){
    //move entries later
    memmove(&dataChn->entriesChn->d[ixEntry + 1], &dataChn->entriesChn->d[ixEntry], sizeof(void*) * (dataChn->zEntryChn - ixEntry));  //memmove(dst, src, length) 
  }
  dataChn->zEntryChn +=1;
  Entry_TimeSignals_Inspc* entry = (Entry_TimeSignals_Inspc*)malloc(sizeof(Entry_TimeSignals_Inspc));
  memset(entry, 0, sizeof(Entry_TimeSignals_Inspc));
  dataChn->entriesChn->d[ixEntry] = entry;
  return ixEntry;
}





static void parseLine_TimeSignals_Inspc(TimeSignals_Inspc* thiz, StringJc line, int posStart, int ixStartEntries[16], ThCxt* _thCxt)
{ int zLine = length_StringJc(line);
  int pos = posStart;
  STACKTRC_TENTRY("parseLine_TimeSignals_Inspc");
  int parsedCharsTime = 0;
  float time = parseFloat_CsiiciY_StringFunctions_CJc(line, pos, zLine, '.', &parsedCharsTime, _thCxt);
  float timespline;
  pos = indexNoWhitespace_StringFunctionsJc(line, pos + parsedCharsTime, -1, _thCxt);
  if(charAt_StringJc(line, pos) == '-') {  //a timeCorr given. Start of spline or correction.
    pos = indexNoWhitespace_StringFunctionsJc(line, pos +1, -1, _thCxt);
    timespline = parseFloat_CsiiciY_StringFunctions_CJc(line, pos, zLine, '.', null, _thCxt);
  } else {
    timespline = 0;  //no spline
  }
  int posColon = indexOf_CI_StringJc(line, ':', pos);
  if(posColon > 0 && parsedCharsTime >0) { //time found.
    pos = posColon +1;
    int maxWhileNext = 100;
    while(maxWhileNext >=0 && pos >0) { //search value asignments, pos is position after separator for values.
      int posName = indexNoWhitespace_StringFunctionsJc(line, pos, -1, _thCxt );
      pos = indexAfterIdentifier_StringFunctionsJc(line, posName, -1, null_StringJc, _thCxt );
      if(pos > posName && pos < zLine && charAt_StringJc(line, pos) == '.') {
        StringJc nameModule = substring_StringJc(line, posName, pos, _thCxt);
        if(equals_z_StringJc(nameModule, thiz->nameModule)) {
          posName = pos +1; //name inside moduel.
          pos = indexAfterIdentifier_StringFunctionsJc(line, posName, -1, null_StringJc, _thCxt );
          StringJc name = substring_StringJc(line, posName, pos, _thCxt);
          int ixName = -1;
          int zNames = thiz->base.super.zVariable;
          while(++ixName < zNames && !equals_z_StringJc(name, thiz->base.super.varParams[ixName].name));  //search name
          if(ixName < zNames) {
            //name in line found in this stimuli block:
            int posValue = indexOf_CI_StringJc(line, '=', pos) +1;
            if(posValue >0 ) { //if = not found, it is 0 because +1
              //an entry necessary: Search position:
              int ixEntry = createNewEntry(thiz, ixName, time);
              Entry_TimeSignals_Inspc* entry = thiz->timeData[ixName].entriesChn->d[ixEntry];
              entry->timeStart = time;
              int ixStartEntry = -1;  //no ramp
              if (charAt_StringJc(line, posValue) == '>') {  //ramp to target
                if (time > 0) {
                  entry->ramp = 1; //this entry should be reached with a ramp, not with jump
                  entry->timespline = timespline; //may be 0
                }
                posValue +=1;
              }
              
              int zValues = ARRAYLEN_emC(((Entry_TimeSignals_Inspc*)0)->ya);
              int ixValue = 0;
              int32 nrofCharsParsed;
              do {
                posValue = indexNoWhitespace_StringFunctionsJc(line, posValue, -1, _thCxt );
                float value = parseFloat_CsiiciY_StringFunctions_CJc(line, posValue, 99999, '.', &nrofCharsParsed, _thCxt);
                if(nrofCharsParsed > 0  //a value scanned?
                  && entry !=null       //an entry found? on not found entry parse the values but don't store.
                  ) {
                  entry->ya[ixValue++] = value;
                }
                //pos after value and spaces.
                //don't check ',' it is the separator between names.
                pos = indexNoWhitespace_StringFunctionsJc(line, posValue + nrofCharsParsed, -1, _thCxt );
                posValue = pos;
              } while(ixValue < zValues && nrofCharsParsed >0);
            }
          } else { //name in module not found though the module was found:
            thiz->errorCfg = mNameNotFound_TimeSignals_Inspc;
          }
        } //faulty module.
      } //name not exists.
      //search next variable:
      pos = indexOf_CI_StringJc(line, ',', pos) +1;  //0 if not found, then abort while. Else: more as one variable with the same time.
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
    //    
    StringJc line;
    int maxWhileLines = 100000;
    int ixStartEntries[16] = {-1};
    while( line = readLine_BufferedReaderJc(&reader, _thCxt)  //Note: statement in while, separated with ,
         , --maxWhileLines >=0 && !isNull_StringJc(line)      //condition.
         ){
      TRY {
        int zLine = length_StringJc(line);
        int32 posStart = indexOf_z_StringJc(line, "%time:");
        if(posStart >=0){
          posStart = indexNoWhitespace_StringFunctionsJc(line, posStart+6, -1, _thCxt );
          if(posStart < zLine && charAt_StringJc(line, posStart)!= '#') { //not a comment line 
            parseLine_TimeSignals_Inspc(thiz, line, posStart, ixStartEntries, _thCxt);
          }
        }
      }_TRY
      CATCH(Exception, exc) {
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



inline void setSpline_TimeSignals_Inspc(TimeSignals_Inspc* thiz, CurrValues_TimeSignals_Inspc* curr, int ixv, float dyNew) {

  curr->dyaNew[ixv] = dyNew;  //store only for debug.
  curr->stepsSplineEnd = -curr->stepsSpline;
  float ddya = (dyNew - curr->dya[ixv]) / (2 * curr->stepsSpline);  //change of dya per step for linear change
  if(thiz->par.testNoJergLim){
    //this is only to demonstrate which effect has a missing jerk limitation.
    curr->ddya[ixv] = ddya;
    curr->dddya[ixv] = 0;
  }
  else {
    curr->dddya[ixv] = ddya * 2 / curr->stepsSpline;
  }

}




static bool calcTargetSettings(TimeSignals_Inspc* thiz, TimeData_TimeSignals_Inspc* dataChn, Entry_TimeSignals_Inspc* entry, CurrValues_TimeSignals_Inspc* curr) {
  Array_Entry_TimeSignals_Inspc* entries = dataChn->entriesChn;
  Entry_TimeSignals_Inspc* entryNext = entries->d[dataChn->ixCurrent];
  Entry_TimeSignals_Inspc* entryNext2 = dataChn->ixCurrent + 1 < dataChn->zEntryChn ? entries->d[dataChn->ixCurrent + 1] : entryNext;
  curr->time_Target = entryNext->timeStart;
  float steps = (entryNext->timeStart - entry->timeStart) / thiz->Tstep;
  curr->stepsToTarget = (int32)(steps + 0.5f); //round up, +1 because predecrement.
  if (entryNext->ramp != 0 && curr->stepsToTarget >= 1) {
    if (entry->timespline == 0) {
      curr->stepsCalcdynew = 0;  //to force calculate dya on first usage.
      curr->stepsSpline = INT32_MAX;
      curr->dbgSel |= noSplineEntry_DbgSel_TimeSignals_Inspc;
    }
    else {
      //use the spline to the current point, from last.
      curr->stepsCalcdynew = curr->stepsSplineStart + 6;  //same time from start to point to end spline. But 6 steps more, spline should ended in anycase
      curr->dbgSel |= splineEntry_DbgSel_TimeSignals_Inspc;
    }
    //
    if (entryNext->timespline == 0) {  //no spline
      curr->stepsSplineStart = -1;
      curr->dbgSel |= noSplineNextEntry_DbgSel_TimeSignals_Inspc;
    }
    else {
      int32 stepsSplineMax = INT32_MAX;  //if no next2 exists
      if (entryNext2 != entryNext) {
        float steps2 = (entryNext2->timeStart - entryNext->timeStart) / thiz->Tstep;
        stepsSplineMax = (int32)(steps2)-2; //full spline to near next point maximal
        if (entryNext2->timespline >0) {
          curr->dbgSel |= checksplineLengthNextEntry_DbgSel_TimeSignals_Inspc;
          int32 stepsSpline3 = (int32)(entryNext2->timespline / thiz->Tstep);
          if (stepsSpline3 > stepsSplineMax / 2) {
            curr->dbgSel |= reduceSplineLengthNextNextEntry_DbgSel_TimeSignals_Inspc;
            stepsSpline3 = stepsSplineMax / 2;  //maximal spline on next2
          }
          stepsSplineMax -= stepsSpline3;  //regard spline to next2, subtract at max stepsSplineMax/2
        }
      }
      curr->dbgSel |= splineNextEntry_DbgSel_TimeSignals_Inspc;
      curr->stepsSplineStart = (int32)(entryNext->timespline / thiz->Tstep + 0.5f);
      if (curr->stepsSplineStart >= stepsSplineMax) {
        curr->dbgSel |= reduceSplineLengthNextEntry_DbgSel_TimeSignals_Inspc;
        curr->stepsSplineStart = stepsSplineMax;
      }
    }
    for (int ixv = 0; ixv < 6; ++ixv) { //set all target info for the next point with ramp
      curr->yt[ixv] = entryNext->ya[ixv];       //the target point for this ramp.  or level. On last entry it is the same as entry
      curr->dyx[ixv] = (entryNext->ya[ixv] - entry->ya[ixv]) / (entryNext->timeStart - entry->timeStart);
      if (entryNext2->ramp && !(entryNext2 == entryNext)) {  //the target for next is a ramp
        float dtimeAfterTarget = entryNext2->timeStart - entryNext->timeStart;
        curr->dbgSel |= rampNextEntryVal_DbgSel_TimeSignals_Inspc;
        curr->dyt[ixv] = dtimeAfterTarget <= 0 ? 0 : (entryNext2->ya[ixv] - entryNext->ya[ixv]) / dtimeAfterTarget * thiz->Tstep;
      }
      else {
        curr->dyt[ixv] = 0;  //after target there is no next entry or a jump. 
      }
    }
    return false;
  }
  else {
    curr->dbgSel |= noRampNextEntry_DbgSel_TimeSignals_Inspc;
    curr->stepsCalcdynew = INT32_MAX;             //no calculate dya
    steps = 0;                                    //no ramp to target. 
    curr->stepsSplineStart = 0;
    return true;
  }
}



static void setValuesFromEntry(TimeSignals_Inspc* thiz, Entry_TimeSignals_Inspc* entry, bool bNoRampToNext, CurrValues_TimeSignals_Inspc* curr) {
  for (int ixv = 0; ixv < 6; ++ixv) {
    //all point settings from the current point
    //which are not set 
    curr->ystart[ixv] = entry->ya[ixv];
    //but set the dy after target anyway for splining:
    //
    if (entry->timespline == 0) {
      curr->dbgSel |= noSplineEntryVal_DbgSel_TimeSignals_Inspc;
      curr->dddya[ixv] = curr->ddya[ixv] = 0;
    } //else remain ddya, used by spline. set to 0 after spline 
      //
    if (!entry->ramp) {
      //this entry is reached without a ramp, therefore set the value from end as current one.
      //It is a jump level.
      curr->dbgSel |= jmpEntryVal_DbgSel_TimeSignals_Inspc;
      curr->ya[ixv] = curr->yb[ixv] = curr->ystart[ixv];         //The value level from here with jump to level.
      curr->yd[ixv] = 0;                         //The delta remain 0
    }
    else {
      // do not set ys[ixv] because it should be reached already assumed so exactly as possible.
      // dya will be set firstly in caluclate output values because curr->stepsCalcdynew is 0, will be decrented to -1.
    }
    //continue with ramp?
    if (bNoRampToNext) {
      curr->dbgSel |= noRampNextEntryVal_DbgSel_TimeSignals_Inspc;
      curr->dyx[ixv] = 0;  //no growth
      curr->dyt[ixv] = 0;  //after target there is no next entry or a jump. 
      if (entry->timespline == 0) {  //no ramp to next or last entry, and no timespline in current: 
        curr->dbgSel |= noSplineEntryVal_DbgSel_TimeSignals_Inspc;
        curr->dya[ixv] = 0;         //has no growth
        curr->ya[ixv] = curr->yb[ixv] = curr->ystart[ixv]; //The exact value from entry independet whether there was a ramp before or not.
        curr->yd[ixv] = 0;          //The delta remain 0
      }
    }
  }
}





static Entry_TimeSignals_Inspc* checkNextEntryChn_TimeSignals_Inspc(TimeSignals_Inspc* thiz, int ixChn, float time)
{
  TimeData_TimeSignals_Inspc* dataChn = &thiz->timeData[ixChn];
  if(dataChn->ixCurrent >= dataChn->zEntryChn) { 
    return null;  //no more entries.
  } else {
    Array_Entry_TimeSignals_Inspc* entries = dataChn->entriesChn;
    Entry_TimeSignals_Inspc* entry = entries->d[dataChn->ixCurrent];
    if(time < entry->timeStart) { 
      return null; 
    } else {
      //next entry found:
      CurrValues_TimeSignals_Inspc* curr = &thiz->curr[ixChn];
      curr->dbgSel = (curr->dbgSel+1 ) & ct_DbgSel_TimeSignals_Inspc;
      if (ixChn == thiz->debug.ixChnCheckEntry) {
        dataChn->ixCurrent += 0;  //NOP-statement, only for breakpoint, debugger-helper.
      }
      dataChn->ixCurrent +=1;  //next check start on that entry.
      float steps;
      curr->time_Start = entry->timeStart;
      bool bNoRampToNext;
      if(dataChn->ixCurrent < dataChn->zEntryChn) {
        bNoRampToNext = calcTargetSettings(thiz, dataChn, entry, curr);
      } else { //no next entry exists, it is the last one.
        curr->dbgSel |= noNextEntry_DbgSel_TimeSignals_Inspc;
        bNoRampToNext = true;
        steps = 0;
        //entryNext2 = entryNext = entry; //use same info, no ramp anyway, steps is 0.
        curr->time_Target = time + 10.0f; //time_Target should be set. Assume 10 seconds. It ist not a ramp.
        curr->stepsToTarget = INT32_MAX;
        curr->stepsSplineStart = 0;
        for (int ixv = 0; ixv < 6; ++ixv) { //set all target info for the last point
          curr->yt[ixv] = entry->ya[ixv];       //the target point for this ramp.  or level. On last entry it is the same as entry
        }
      }
      setValuesFromEntry(thiz, entry, bNoRampToNext, curr);
      return entry;  //it is actual.
} } }



void values_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float _simtime
  //, void* val1_y, void* val2_y, void* val3_y, void* val4_y
  //, void* val5_y, void* val6_y, void* val7_y, void* val8_y
  //, void* val9_y, void* val10_y, void* val11_y, void* val12_y
  //, void* val13_y, void* val14_y, void* val15_y, void* val16_y
  , int32* error_y, int _zVaargs_, ...
){
  va_list varg;
  va_start(varg, _zVaargs_);
  //void* out[16];
  for(int ixChn = 0; ixChn < thiz->base.super.zVariable; ++ixChn){
    void* addr = va_arg(varg, void*); //vport_x[ix];
    checkNextEntryChn_TimeSignals_Inspc(thiz, ixChn, _simtime);
    CurrValues_TimeSignals_Inspc* curr = &thiz->curr[ixChn];
    bool bStartSpline = false;
    curr->stepsToTarget -= 1;
    if (curr->stepsToTarget == curr->stepsSplineStart) {
      curr->stepsCalcdynew = INT32_MAX;  //the dy will be determined by the spline algorithm.
      curr->stepsSpline = curr->stepsSplineStart + thiz->par.testAddStepSpline;
      bStartSpline = true;
    }
    bool bEndSpline = curr->stepsSpline == curr->stepsSplineEnd;
    //
    bool bSplining = curr->stepsSpline < INT32_MAX;
    if(bSplining) { curr->stepsSpline -=1; } //if 0 then spline down.
    //
    bool calcdynew = false;
    if (--curr->stepsCalcdynew <0 ) {
      curr->stepsCalcdynew = thiz->par.stepsDynew; //calculate after thiz->par.stepsDynew steps, 1/(2000 * 2000) is about the accuracy of float numbers. 
      calcdynew = true;
    }
    float steps = 0;
    float dtime = 0;
    //
    //output:
    //
    ClassJc const* type = getType_FieldJc(&thiz->fields.data[ixChn]);
    int z = thiz->fields.data[ixChn].nrofArrayElementsOrBitfield_;
    if (z == 0) { z = 1; }
    if (type == &refl__floatJc || type == &refl_float_complex) {
      if(type == &refl_float_complex) {
        z *=2;  //handle float_complex as vector with 2 elements.
      }
      curr->dbg_zValues = z;
      if (z > 6) { z = 1; }
      float* outAddr = (float*)addr;
      for (int ixv = 0; ixv < z; ++ixv) {
        if(curr->dyx[ixv] ==0) {
          outAddr[ixv] = curr->ya[ixv];          // simple output the current value, no ramp no spline
        }
        else {
          if (bStartSpline) {
            float yb = curr->yt[ixv] + curr->dyt[ixv] * curr->stepsSplineStart;  //target point after end of spline.
            curr->yd[ixv] = curr->ya[ixv] - yb;
            curr->yb[ixv] = yb;
            setSpline_TimeSignals_Inspc(thiz, curr, ixv, curr->dyt[ixv]);
          }
          else if (calcdynew) {
            //curr->ddya[ixv] = curr->dddya[ixv] = 0;
            float y1 = curr->dyx[ixv] * (_simtime + thiz->par.stepsDynew * thiz->Tstep - curr->time_Start)
                     + curr->ystart[ixv];
            float dyaNew = (y1 - curr->ya[ixv]) / thiz->par.stepsDynew;
            if(curr->stepsSpline == INT32_MAX || thiz->par.testNoJergLim){
              curr->dya[ixv] = dyaNew;              //No spline in start point, then set dy immediately. 
            } else { 
              curr->stepsSpline = 100;              //spline in start point, use spline in curve after it too.
              setSpline_TimeSignals_Inspc(thiz, curr, ixv, dyaNew);
            }
            curr->yd[ixv] = curr->ya[ixv] - y1;
            curr->yb[ixv] = y1;
          }
          //
          //output and ramp.
          outAddr[ixv] = curr->ya[ixv];     //firstly output the current value
          if(bSplining) { //curr->dddya[ixv] !=0 || thiz->par.testNoJergLim && curr->ddya[ixv] !=0) { //spline runs for this ixv
            if (curr->stepsSpline == 0) {
              curr->dddya[ixv] *= -1.0f;      //acceleration down to 0
            }
            else if(bEndSpline) {
              //new dya should be reached. ddya should be near 0.
              curr->dddya[ixv] = curr->ddya[ixv] = 0;  //set change of dya to 0. constant growth (velocity). 
            }
            curr->ddya[ixv] += curr->dddya[ixv];
            curr->dya[ixv] += curr->ddya[ixv];
          }
          curr->yd[ixv] += curr->dya[ixv];  //then add dya. It is always correct. If no ram, then dya[..] = 0.
          if(curr->yd[ixv] !=0) {
            curr->ya[ixv] = curr->yb[ixv] + curr->yd[ixv];
          } //else: don't change ya, it can be changed by inspector user operations if the output is constant, no ramp.
        //
        }
      } //for ixv
    }
  }
}





void bits_TimeSignals_Inspc(TimeSignals_Inspc* thiz, float _simtime
, uint16* bits_y
, int32* error_y
)
{
  int ix;
  //TODO checkNewEntry_TimeSignals_Inspc(thiz, _simtime);
  int16 bits = 0; 
  //The variables ya0, ya1 ... are arranged one after another.
  //The memory layout is the same like an array ya[16][6];
  {
    for(ix=15; ix >=0; --ix) {
       int ix1 = 6 * ix;
       bits <<=1;
       if(thiz->curr[ix].ystart[0]) { bits |=1; }
    }
  }
  *bits_y = bits;
  *error_y = thiz->errorCfg;
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

#endif //DEF_REFLECTION_FULL

