#include <emC/StateM/evQueue.h>

#include <stdlib.h> //malloc

#ifdef DEF_REFLECTION_FULL
#include "genRefl/evQueue.crefl"
#elif defined(XXXDEF_REFLECTION_OFFS)
  //The classes are defined in a project specific ...refloffs.c file:
  extern_C ClassJc const refl_EvListener_StateM_vishiaOrg;
  extern_C ClassJc const refl_EvCreator_StateM_vishiaOrg;
  extern_C ClassJc const refl_EvInstance_StateM_vishiaOrg;
  extern_C ClassJc const refl_EvQueue_StateM_vishiaOrg;
#else
  //Note: The ID_refl are defined in the header file.

 
  #ifndef DEF_REFLECTION_NO
  //ClassJc const refl_EvListener_StateM_vishiaOrg = INIZ_ClassJc(refl_EvListener_StateM_vishiaOrg, "EvListener_StateM_vishiaOrg");
  //ClassJc const refl_EvCreator_StateM_vishiaOrg = INIZ_ClassJc(refl_EvCreator_StateM_vishiaOrg, "EvCreator_StateM_vishiaOrg");
  ClassJc const refl_EvInstance_StateM_vishiaOrg = INIZ_ClassJc(refl_EvInstance_StateM_vishiaOrg, "EvInstance_StateM_vishiaOrg");
  ClassJc const refl_EvQueue_StateM_vishiaOrg = INIZ_ClassJc(refl_EvQueue_StateM_vishiaOrg, "EvQueue_StateM_vishiaOrg");
  #endif
#endif

EvQueue_StateM_vishiaOrg_s* ctor_EvQueue_StateM_vishiaOrg(ObjectJc* othiz, float Tstep, int sizeQueue, int sizeInstances, ThCxt* _thCxt){
  STACKTRC_TENTRY("ctor_EvQueue_StateM_vishiaOrg");
  EvQueue_StateM_vishiaOrg_s* thiz = null;
  if( CHECKinit_ObjectJc(othiz, sizeof(EvQueue_StateM_vishiaOrg_s), refl_EvQueue_StateM_vishiaOrg, 0)) {
    thiz = (EvQueue_StateM_vishiaOrg_s*)othiz;
    thiz->Tstep = Tstep;
    thiz->queue.a = (Entry_EvQueue_StateM_vishiaOrg_s*)alloc_MemC(sizeQueue * sizeof(Entry_EvQueue_StateM_vishiaOrg_s));
    thiz->sizeQueue = sizeQueue;
    thiz->prd = thiz->pwr = 0;
    thiz->instances.a = (EvInstance_StateM_vishiaOrg_s**)alloc_MemC(sizeInstances * sizeof(EvInstance_StateM_vishiaOrg_s*));
    thiz->sizeInstances = sizeInstances;
    setInitialized_ObjectJc(&thiz->base.obj);
  }
  STACKTRC_RETURN thiz;  //returns null if THROW is not possible and checkInit-error occurs.
}




bool addEvInstance_EvQueue_StateM_vishiaOrg(EvQueue_StateM_vishiaOrg_s* thiz, struct EvInstance_StateM_vishiaOrg_T* evInstance, ThCxt* _thCxt){
  if(evInstance->evId >= thiz->sizeInstances) {
    THROW_s0(IllegalArgumentException, "faulty evIdent: ", evInstance->evId, thiz->sizeInstances);
    return false;
  } else {
    thiz->instances.a[evInstance->evId] = evInstance;
    evInstance->stateInput = 0;  //mark as added.
  }
  return true;
}



bool checkForListener_EvQueue_StateM_vishiaOrg ( EvQueue_StateM_vishiaOrg_s* thiz, ThCxt* _thCxt){
  Entry_EvQueue_StateM_vishiaOrg_s* ev;
  //Note: dequeue only one event. 
  if( (ev = getNext_EvQueue_StateM_vishiaOrg(thiz)) !=null) {
    if(ev->evIdent <= thiz->sizeInstances) {
      EvInstance_StateM_vishiaOrg_s* evInstance = thiz->instances.a[ev->evIdent];
      if(evInstance !=null) {
        evInstance->hdata.h = ev->hdata.h; //The current data reference to the event, may be the same for all.
        evInstance->stateTrg = 1;      //notify event is given
        //The calling of the event is done on execution of the instance, hasEvent_EvInstance...(...)
      }
    }
    quitNext_EvQueue_StateM_vishiaOrg(thiz, _thCxt);
    return true;
  }
  else {
    return false; //no event in queue.
  }
}


//It is the implementation for the EvQueue SFunction in Simulink.
void status__EvQueue_StateM_vishiaOrg(EvQueue_StateM_vishiaOrg_s* thiz, int16* nrofEvents_y, int16* ctEvents_y) {
  STACKTRC_ENTRY("");
  checkForListener_EvQueue_StateM_vishiaOrg(thiz, _thCxt);
  //Output the state
  int n = thiz->pwr-thiz->prd;
  if(n<0) { n+= thiz->sizeQueue; }
  *(nrofEvents_y) = n;
  *(ctEvents_y) = thiz->evCt;
  STACKTRC_LEAVE;
}



//It is the implementation for the EvQueue SFunction in Simulink.
int16 info_EvQueue_StateM_vishiaOrg(EvQueue_StateM_vishiaOrg_s* thiz, int16* ctEvents_y) {
  //Output the state
  int n = thiz->pwr-thiz->prd;
  if(n<0) { n+= thiz->sizeQueue; }
  if(ctEvents_y !=null) { *(ctEvents_y) = thiz->evCt; }
  return (int16)n;
}








//This routine should not be used, because mex-S-Functions in Simulink have its own static space.
//Hence the id_Static is existing more as one for more as one mex-S-Function-type.
//Remain in comment as hint!
//static int getId_EvCreator_StateM_vishiaOrg() {
//  static int id_Static = 1;
//  return ++id_Static;
//}






EvInstance_StateM_vishiaOrg_s* ctor_EvInstance_StateM_vishiaOrg(ObjectJc* othiz, int asListener, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_EvInstance_StateM_vishiaOrg");
  EvInstance_StateM_vishiaOrg_s* thiz = null;
  if( CHECKinit_ObjectJc(othiz, sizeof(EvInstance_StateM_vishiaOrg_s), refl_EvInstance_StateM_vishiaOrg, 0) ) {
    thiz = (EvInstance_StateM_vishiaOrg_s*)othiz;
    thiz->stateTrg = asListener ? 0x40 : 0x80;  //mark as not added yet.
  }
  STACKTRC_RETURN thiz;
}


bool init_EvInstance_StateM_vishiaOrg(EvInstance_StateM_vishiaOrg_s* thiz, uint32 hdata, uint16 evIdent, EvQueue_StateM_vishiaOrg_s* queue, uint16* evId_y) {
  STACKTRC_ENTRY("init_EvInstance_StateM_vishiaOrg");
  if(queue == null || hdata == 0) { 
    STACKTRC_RETURN false;
  } else {
    bool bOk;
    thiz->evQueue = queue;
    thiz->hdata.h = hdata;
    if(evIdent == 0) {
      //increment, note: queue->instances.a[0] is left empty yet.  
      while(++queue->evIdForCreator < queue->sizeInstances && queue->instances.a[queue->evIdForCreator] !=null){}
      thiz->evId = queue->evIdForCreator;  //Maybe faulty for the event queue, test 
    }
    else {
      thiz->evId = evIdent;
    }
    bOk = thiz->evId < queue->sizeInstances;
    if(evId_y !=null){ *evId_y = thiz->evId; }
    if(!bOk) { 
      THROW_s0(IllegalArgumentException, "faulty event ident=", thiz->evId, queue->sizeInstances);
      //Note: returns false and does not setInitialized_ObjectJc(...) on systems without exception handling 
    } else {
      if(thiz->stateTrg == 0x40) { //add only if initialized as Listener
        addEvInstance_EvQueue_StateM_vishiaOrg(queue, thiz, _thCxt);
        thiz->stateTrg = 0x20;  //for debug: added but never receive an event.
      } else {
        //This instance is used to add events to the queue, not for listen.
        //startTrg remains to the intial value 0x80
      }
      setInitialized_ObjectJc(&thiz->base.obj);
    }
    STACKTRC_RETURN bOk;
  }
}






