#include <emC/Base/EventTask_emC.h>



#ifdef DEF_REFLECTION_FULL
#include "emC/Base/genRefl/eventTask_emC.crefl"
#elif defined(XXXDEF_REFLECTION_OFFS)
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_EvListener_emC;
  extern_C ClassJc const refl_EvCreator_emC;
  extern_C ClassJc const refl_EvInstance_emC;
  extern_C ClassJc const refl_EvQueue_emC;
#else
  //Note: The ID_refl are defined in the header file.

 
  #ifndef DEF_REFLECTION_NO
  //ClassJc const refl_EvListener_emC = INIZ_ClassJc(refl_EvListener_emC, "EvListener_emC");
  //ClassJc const refl_EvCreator_emC = INIZ_ClassJc(refl_EvCreator_emC, "EvCreator_emC");
  ClassJc const refl_EvInstance_emC = INIZ_ClassJc(refl_EvInstance_emC, "EvInstance_emC");
  ClassJc const refl_EventTask_emC = INIZ_ClassJc(refl_EventTask_emC, "EventTask_emC");
  ClassJc const refl_EvQueue_emC = INIZ_ClassJc(refl_EvQueue_emC, "EvQueue_emC");
  #endif
#endif


char const signatureString_TaskConstData_emC[] = "signatureString_TaskConstData_emC";

void ctor_EventTask_emC(EventTask_emC_s* thiz, char const* idString) {
  release_EventTask_emC(thiz);
}



//chg2022-04-12: CtPriority=0 is inactive (default is 0). higher priority is greater value.
//tag::execPolling_EventTask_emC[]
void execPolling_EventTask_emC ( TaskConstData_emC const* const* evEntryArray, int nrofEntries) {
  TaskConstData_emC const* entryAct = null;
  int minPrio = 1;
  int ix = nrofEntries;
  //for(ix = 0; ix < nrofEntries; ++ix) {
  while(--ix >=0) {   // hint: Recommend loops count down as detecting zeros is easier instead ct up
    TaskConstData_emC const* entry = evEntryArray[ix];
    if(entry->signatureString != signatureString_TaskConstData_emC) {
      THROW_s0n(IllegalArgumentException, "faulty TaskConstantData", (int)(intPTR)(entry), 0);
    } else {
      EventTask_emC_s volatile* entryData = entry->evEntry;
      if(   entryData->ctPriority >0
        && (  (entryData->ctPriority & mTime_EventTask_emC) ==0  // use without time
           || (timeShortStepCycle_emC() - ((EventTaskTime_emC_s*)entryData)->timeExec) >0
        )  ) {                                                   // OR time should be expired
        if(entryData->ctPriority >= minPrio) {
          entryAct = entry;                        // only a candidate for execution yet.
          minPrio = entryData->ctPriority;         // check only tasks furthermore with higher or equal prio
        }                                          // but increase the prio of all on each check
        if(entryData->ctPriority <254) {
          entryData->ctPriority +=1;    //ct up priority, till it is the highest one
        }
      }
    }
  }
  if(entryAct !=null) {                          //any task found to activate
    EventTask_emC_s volatile* entryData = entryAct->evEntry;
    entryData->ctPriority = 0;                   // reset the prio, is started.
    entryAct->operation(entryAct);               // call execution.
  }
}
//end::execPolling_EventTask_emC[]




