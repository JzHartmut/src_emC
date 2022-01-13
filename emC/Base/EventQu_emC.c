#include <emC/Base/EventQu_emC.h>
#include <emC/Base/MemC_emC.h>
//#include <emC/Base/MemC_emC.h>

#if true

//#include <stdlib.h> //malloc

#ifdef DEF_REFLECTION_FULL
#include "emC/Base/genRefl/eventQu_emC.crefl"
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
  ClassJc const refl_EventData_emC = INIZ_ClassJc(refl_EventData_emC, "EventData_emC");
  ClassJc const refl_EvQueue_emC = INIZ_ClassJc(refl_EvQueue_emC, "EvQueue_emC");
  #endif
#endif



EventData_emC_s* ctor_EventData_emC(ObjectJc* othiz, char const* idString) {
  EventData_emC_s* thiz = (EventData_emC_s*) othiz;
  thiz->idString = idString;
  release_EventData_emC(thiz);
  return thiz;
}



bool init_EventData_emC(EventData_emC_s* thiz, HandleADDR_emC(int32) hdata, uint16 evIdent, struct EvQueue_emC_T* queue, uint16* evId_y) {
  STACKTRC_ENTRY("init_EvInstance_emC");
  thiz->evQueue = queue;  //maybe null
  thiz->eventIdent = evIdent;
  thiz->hdata = hdata;
  setInitialized_ObjectJc(&thiz->base.obj);
  STACKTRC_RETURN true;
}


EvQueue_emC_s* ctor_EvQueue_emC(ObjectJc* othiz, float Tstep, int sizeQueue){
  STACKTRC_ENTRY("ctor_EvQueue_emC");
  EvQueue_emC_s* thiz = null;
  ASSERT_emC( CHECKstrict_ObjectJc(othiz, sizeof(EvQueue_emC_s), refl_EvQueue_emC, 0)
    , "EvQueue_emC_s not correct initialized", getID_ObjectJc(othiz), (int)(intPTR)getClass_ObjectJc(othiz) );
  thiz = (EvQueue_emC_s*)othiz;
  ctor_RingBuffer_emC(&thiz->base.obj, sizeQueue);
  thiz->entries.a = (EventData_emC_s**)alloc_MemC(sizeof(EventData_emC_s**) * sizeQueue);
  thiz->Tstep = Tstep;
  //thiz->instances.a = (EvInstance_emC_s**)malloc(sizeInstances * sizeof(EvInstance_emC_s*));
  //thiz->sizeInstances = sizeInstances;
  setInitialized_ObjectJc(&thiz->base.obj);
  STACKTRC_RETURN thiz;  //returns null if THROW is not possible and checkInit-error occurs.
}


void dtor_EvQueue_emC(EvQueue_emC_s* thiz) {
  free_MemC(thiz->entries.a);
}




bool checkForListener_EvQueue_emC ( EvQueue_emC_s* thiz, ThCxt* _thCxt){
  //Note: dequeue only one event. 
  int ixEv;
  if( (ixEv = getNext_EvQueue_emC(thiz)) >=0) {
    EventData_emC_s* ev = thiz->entries.a[ixEv];
    if(ev !=null) {
      ev->ctPriority = 1;      //notify event is given
      //The calling of the event is done on execution of the instance, hasEvent_EvInstance...(...)
      quitNext_EvQueue_emC(thiz, ixEv);
    }
    return true;
  }
  else {
    return false; //no event in queue.
  }
}


//It is the implementation for the EvQueue SFunction in Simulink.
void status_EvQueue_emC(EvQueue_emC_s* thiz, int16* nrofEvents_y, int* ctEvents_y) {
  checkForListener_EvQueue_emC(thiz, null);
  status_RingBuffer_emC(&thiz->base.RingBuffer_emC, nrofEvents_y, ctEvents_y);
}








//This routine should not be used, because mex-S-Functions in Simulink have its own static space.
//Hence the id_Static is existing more as one for more as one mex-S-Function-type.
//Remain in comment as hint!
//static int getId_EvCreator_emC() {
//  static int id_Static = 1;
//  return ++id_Static;
//}






EvInstance_emC_s* ctor_EvInstance_emC(ObjectJc* othiz, int asListener, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_EvInstance_emC");
  EvInstance_emC_s* thiz = null;
  if( CHECKstrict_ObjectJc(othiz, sizeof(EvInstance_emC_s), refl_EvInstance_emC, 0) ) {
    thiz = (EvInstance_emC_s*)othiz;
    thiz->stateTrg = asListener ? 0x40 : 0x80;  //mark as not added yet.
  }
  STACKTRC_RETURN thiz;
}


#endif  //if 0

//Only its memory address is significant, content only for debugging.
char const* const signatureString_TaskConstData = "TaskConstData";


void execEvPolling ( TaskConstData_emC const* const* evEntryArray, int nrofEntries) {
  TaskConstData_emC const* entryAct = null;
  uint minPrio = 255;
  for(int ix = 0; ix < nrofEntries; ++ix) {
    TaskConstData_emC const* entry = evEntryArray[ix];
    EventData_emC_s* entryData = entry->evEntry;
    if(entryData->ctPriority < minPrio) {
      entryAct = entry;
      minPrio = entryData->ctPriority;
    }
    if(entryData->ctPriority >1 && entryData->ctPriority != (uint)-1) {
      entryData->ctPriority -=1;    //ct down priority, till it is the highest one
    }
  }
  if(entryAct !=null) {
    EventData_emC_s* entryData = entryAct->evEntry;
    entryData->ctPriority = 0;
    entryAct->operation(entryAct);
  }
}




