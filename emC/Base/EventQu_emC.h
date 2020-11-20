#ifndef HGUARD_emC_Base__EventQu_emC
#define HGUARD_emC_Base__EventQu_emC
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
#include <emC/Base/RingBuffer_emC.h>

//#include <emC/Base/String_emC.h>


struct EvQueue_emC_T;
struct EvInstance_emC_T;



/**The variable data for one event which can be activated. 
 * This is the event instance which can used immediately to poll in a simple task scheduler
 * or which can be referenced in a queue. 
 *
 * One using variant is, the variable data are referenced from a const [[struct TaskConstData_emC_T]].
 * Then one const TaskConstData_emC refers exact one instance of this struct. 
 * Activating the event is written in this class, but the queuing will be done 
 * with the const TaskConstData_emC* reference. 
 * Hence this data should be used only via the const TaskConstData_emC const* reference
 */
typedef struct EventData_emC_T {

  union { ObjectJc obj; } base;

  /**If an event queue will be used, then an event instance can/should be associated
   * to a determined queue. Hence it is only necessary to activate the event instance,
   * the enqueue is done automatically. No effort in user programming.
   * Hence it is not a difference in user programming, only in startup, 
   * whether a queue is used or not.
   * This element is left null, if a queue is not used.
   */
  struct EvQueue_emC_T* evQueue;

  /**Associated step time (for Simulink ?) TODO necessary? */
  float Tstep;

  char const* idString;

  /**A priority counter, down counting, if 0 it is prior.
   * With that some events can be designated with an execution priority.
   * It enables another principle than First in First out.
   * (uint)-1 (max. integer value) if the event is free, unused. 
   */
  uint8 ctPriority;

  uint8 stateInp;

  /**Identification of the event. 
   */
  uint eventIdent;

  //uint8 stateInput;

  int ctEvents;  //Note: use signed int to enable build differences on overflow!

  /**The destination instance for the event. */
  HandleADDR_emC(ObjectJc) hdst;

  /**Possible additional event data. */
  HandleADDR_emC(int32) hdata;
  //int32* hdata;

  /**The time stamp of the event from the source. */
  int32 timestamp;

} EventData_emC_s;

#define ID_refl_EventData_emC 0x0FE2
#ifndef DEF_REFLECTION_NO 
  extern_C ClassJc const refl_EventData_emC;
#endif


static inline void release_EventData_emC(EventData_emC_s* thiz) {
  thiz->ctPriority = (uint8)-1;
  thiz->eventIdent = 0;
  thiz->timestamp = 0;
}

extern_C EventData_emC_s* ctor_EventData_emC(ObjectJc* othiz, char const* idString);

extern_C bool init_EventData_emC(EventData_emC_s* thiz, HandleADDR_emC(int32) hdata, uint16 evIdent, struct EvQueue_emC_T* queue, uint16* evId_y);

/**Check wheter this entry is free. 
 * @return true if free, false if it is activated (in use). 
 */
static inline bool isFree_EventData_emC(EventData_emC_s* thiz, uint priority) {
  return (thiz->ctPriority == ((uint)-1));
}




/**Activates the entry if it is free. 
 * If the event is not free, in use, queued resp. activated this routine does nothing but returns false.
 * @param priority 1 means, execute it immediately, >1: all other events < priority are firstly prior.
 * @return true if activated, false if it is activated (in use) already. 
 */
static inline bool activate_EventData_emC(EventData_emC_s* thiz, uint priority) {
  if(thiz->ctPriority == ((uint)-1)) {
    thiz->ctPriority = priority;
    return true;
  } else {
    return false;  //not able to activate
  }
}





/**The common form of the event callback operation, which is executed by the event. 
 * @param entryData The event entry. It should be freed during this operation, if the data are gotten.
 *        use lockfree compareAndSwap to inform about gotten data.
 *        invoke release_EventData_emC(...) if you have gotten all associated data. 
 */
//typedef void TaskOperation_emC(struct TaskConstData_emC_T const* entryConstData);
typedef void (*TaskOperation_emC)(struct TaskConstData_emC_T const* entryConstData);

/**Structure for const area (Flash, read only) for an event. 
 * This structure contains a pointer to the event operation which should not able to destroy by any obscure software error. 
 * The associated event data are stored in RAM.
 */
typedef struct TaskConstData_emC_T {

  /**It is for safetry check if the pointer to this const data are managed in data area. */
  char const* const signatureString;

  /**The operation to call with the event. */
  TaskOperation_emC operation;

  
  ObjectJc* thizData;
  
  /**Reference to the event entry which have current data for activating.*/
  EventData_emC_s* const evEntry;
} TaskConstData_emC;

extern_C char const* const signatureString_TaskConstData;


/**Initializer for the const data. */
#define INIZ_TaskConstData_emC(OPER, THIZ, EVENT_DATA) { signatureString_TaskConstData, OPER, THIZ, EVENT_DATA }


extern_C void execEvPolling ( TaskConstData_emC const* const* evEntryArray, int nrofEntries);


/*@CLASS_C EvQueue_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

typedef struct XXXXEntry_EvQueue_emC_T {

  /**Identification, the type of the event. */
  uint32 evIdent;

  /**It is the reference to the data, or maybe only an uint32-data item itself. */
  HandleADDR_emC(ObjectJc) hdata;
} XXXXEntry_EvQueue_emC_s;






typedef struct DebugArray_EvInstance_emC_T {
  struct EvInstance_emC_T* a[10];
} DebugArray_EvInstance_emC_s;

typedef struct DebugArray_Entry_EvQueue_emC_T {
  EventData_emC_s* a[10];
} DebugArray_Entry_EvQueue_emC_s;



typedef struct EvQueue_emC_T {

  union { RingBuffer_emC_s RingBuffer_emC; ObjectJc obj; } base;

  uint sizeInstances;
  
  union{ EventData_emC_s** a; DebugArray_Entry_EvQueue_emC_s* dbg; } entries;

  float Tstep;

  uint evIdForCreator;

//  union{ struct EvInstance_emC_T** a;
//         DebugArray_EvInstance_emC_s* dbg; } instances;




} EvQueue_emC_s;

#define INIZ_EvQueue_emC(OBJ, REFL, ID) { { INIZ_RingBuffer_emC(OBJ, REFL, ID) } }

#define ID_refl_EvQueue_emC 0x0FE3
#ifndef DEF_REFLECTION_NO 
  extern_C ClassJc const refl_EvQueue_emC;
#endif

/**Initializes the queue.
 * @arg Tstep only for Graphical FBlock, not stored in FBlock 
 * @arg sizeQueue max nrof Events able to store for one evaluation cycle
 * @simulink ctor.
 */
extern_C EvQueue_emC_s* ctor_EvQueue_emC(ObjectJc* othiz, float Tstep, int sizeQueue);

/**Initializes the queue.
 * @simulink dtor.
 */
extern_C void dtor_EvQueue_emC(EvQueue_emC_s* thiz);

//extern_C bool addEvInstance_EvQueue_emC(EvQueue_emC_s* thiz, struct EvInstance_emC_T* evInstance, ThCxt* _thCxt);

//left empty only set in a test routine. 
#ifndef TEST_INTR1_ADD_EVQUEUE_StateM_emC
#define TEST_INTR1_ADD_EVQUEUE_StateM_emC
#define TEST_INTR2_ADD_EVQUEUE_StateM_emC
#define TEST_INTR3_ADD_EVQUEUE_StateM_emC
#endif



/**Adds an event with given evIdent and data to the queue with atomic lockfree mutex.
 * This operation can be invoked in any thread or interrupt.
 * @arg idEvent to add to queue in the next free Entry_EvQueue_emC.
 * @arg hData will be stored in the entry.
 * return false if no more space in queue. true on success.
 */
static inline bool add_EvQueue_emC ( EvQueue_emC_s* thiz, EventData_emC_s* event) {
  #ifndef NO_PARSE_ZbnfCheader
  int ixAdd = add_RingBuffer_emC(&thiz->base.RingBuffer_emC);
  if(ixAdd >=0) {
    thiz->entries.a[ixAdd] = event;
    return true;
  }
  else {
    return false;
  }
  #endif//NO_PARSE_ZbnfCheader
}






/**Returns the pointer to the current entry or null if the queue is empty.
 * After evaluation of the referenced content the operation 
 * [[quitNext_EvQueue_emC(...)]] has to be invoked to increment the read
 * position respectively to free the entry for writing on end of the queue.. 
 */
static inline int
getNext_EvQueue_emC ( EvQueue_emC_s* thiz) {
  return next_RingBuffer_emC(&thiz->base.RingBuffer_emC);
//  if(ixEvent >=0)
//  Entry_EvQueue_emC_s* entry = C_CAST(Entry_EvQueue_emC_s*, e);
//  if(entry ==null || entry->evIdent == 0) return null; //the entry is not finished written on add
//  else return entry;
} 




static inline void quitNext_EvQueue_emC ( EvQueue_emC_s* thiz, int ixEvent ) {
  quitNext_RingBuffer_emC(&thiz->base.RingBuffer_emC, ixEvent);
}


/**Reads one event from queue and applies it to a registered listener. 
 * After this call the listener should be executed because of its event should be applied to destinations.
 * Further calls of this operation should be done after them maybe in the same cycle or in the next calculation cycle. 
 */
extern_C bool checkForListener_EvQueue_emC(EvQueue_emC_s* thiz, ThCxt* _thCxt);



/**A routine to view the status. It is especially for Modelling to see what's happen and to have a step routine.
 * @simulink Object-FB, no-thizStep.
 */
extern_C void status_EvQueue_emC(EvQueue_emC_s* thiz, int16* nrofEvents_y, int* ctEvents_y);




/*@CLASS_C EvInstance_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct EvInstance_emC_T {

  union { ObjectJc obj; } base;

  struct EvQueue_emC_T* evQueue;

  float Tstep;

  uint16 evId;

  uint8 stateInput;

  uint8 stateTrg;

  int ctEvents;  //Note: use signed int to enable build differences on overflow!


  HandleADDR_emC(ObjectJc) hdata;


} EvInstance_emC_s;

#define ID_refl_EvInstance_emC 0x0FE2
#ifndef DEF_REFLECTION_NO 
  extern_C ClassJc const refl_EvInstance_emC;
#endif

/**Initializes an instance of an event.
 * @arg asListener true (!=0) then it should be registered in the queue as listener too, =0 then only to add events.
 * @simulink ctor.
 */
extern_C EvInstance_emC_s* ctor_EvInstance_emC(ObjectJc* othiz, int asListener, ThCxt* _thCxt);


/**Connects the EvQueue to the Instance on initialize phase.
 * @arg hdata given data handle (reference) 
 * @arg evIdent ==0 then the ident will be gotten as next free slot from the queue-registration
 *              !=0 then it have to be <= the number of listener for events in the queue and this slot should be free.
 * @arg queue The instance is related anyway to a queue, either to create event entries in the queue, 
 *            or to get events from the queue for call, or both.
 * @arg evId_y output the real gotten event evIdent.  
 * @simulink init.
 */
extern_C bool init_EvInstance_emC(EvInstance_emC_s* thiz, uint32 hdata, uint16 evIdent, EvQueue_emC_s* queue, uint16* evId_y);


/**Creates an event on rising edge of signal.
* @simulink Object-FB, no-thizStep.
*/
inline void trgRising_EvInstance_emC(EvInstance_emC_s* thiz, bool signal) {
  if(signal){
    if(thiz->stateInput==0) {
//TODO      add_EvQueue_emC(thiz->evQueue, thiz->evId, thiz->hdata.h);
      thiz->stateInput = 1; 
    }
  } else if(thiz->stateInput) {
    thiz->stateInput = 0;
  }
}


/**Creates an event on any call. It is for an called subsystem in Simulink 
* which is called on an output event of a Statechart-FBlock.
* @simulink Object-FB, no-thizStep.
*/
inline void dataCall_EvInstance_emC(EvInstance_emC_s* thiz) {
  //empty, should only forward the thiz-output.
}



/**Creates an event on any call. It is for an called subsystem in Simulink 
* which is called on an output event of a Statechart-FBlock.
* @simulink Operation-FB.
*/
inline void trgCall_EvInstance_emC(EvInstance_emC_s* thiz) {
//TODO  add_EvQueue_emC(thiz->evQueue, thiz->evId, thiz->hdata.h);
}



inline bool isAddedToQueue_EvInstance_emC(EvInstance_emC_s* thiz) {
  return thiz->stateTrg < 0x40; 
}


#if 0
/**Returns the hdata if an event was applied 
 * after calling [[checkForListener_EvQueue_emC(...)]].
 * A further call returns 0.
 * @return 0 if it has not an event.
 * @simulink Operation-FB, fnCallTrg.
 */
inline uint32 hasEvent_EvInstance_emC (
  EvInstance_emC_s* thiz, uint32* hdata_y, int32* ctEv_y) {
  if(thiz->stateTrg ==1) {
    thiz->stateTrg = 0;
    thiz->ctEvents +=1;
    if(hdata_y !=null) { 
      *hdata_y = thiz->hdata.h;
    }
    if(ctEv_y !=null) { 
      *ctEv_y = thiz->ctEvents;
    }
    return thiz->hdata.h;
  } else {
    return 0;
  }
}
#endif






#endif //HGUARD_emC_Base__EventQu_emC
