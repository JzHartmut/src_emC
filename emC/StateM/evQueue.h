#ifndef DEF_evQueue_StateM_vishiaOrg
#define DEF_evQueue_StateM_vishiaOrg
#include <applstdef_emC.h>
#include <emC/OSAL/os_AtomicAccess.h> //implementations for lockfree mutex
#include <emC/Base/Object_emC.h>
#include <emC/Base/String_emC.h>


struct EvQueue_StateM_vishiaOrg_T;
struct EvInstance_StateM_vishiaOrg_T;



/*@CLASS_C EvQueue_StateM_vishiaOrg @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

typedef struct Entry_EvQueue_StateM_vishiaOrg_T {

  uint32 evIdent;

  /**It is the reference to the data, or maybe only a uint32-data item itself. */
  HandlePtr32Union_emC(ObjectJc) hdata;
} Entry_EvQueue_StateM_vishiaOrg_s;



typedef struct DebugArray_EvInstance_StateM_vishiaOrg_T {
  struct EvInstance_StateM_vishiaOrg_T* a[10];
} DebugArray_EvInstance_StateM_vishiaOrg_s;

typedef struct DebugArray_Entry_EvQueue_StateM_vishiaOrg_T {
  Entry_EvQueue_StateM_vishiaOrg_s a[10];
} DebugArray_Entry_EvQueue_StateM_vishiaOrg_s;



typedef struct EvQueue_StateM_vishiaOrg_T {

  union { ObjectJc obj; } base;

  uint16 sizeQueue;
  uint16 sizeInstances;
  
  int evCt;
  
  /**Index to read from queue.a[thiz->prd]. 
   * ** If prd==pwr, then the queue is empty. 
   * ** If queue.a[thiz->prd].evIdent ==0 a write is pending on this position, the queue is empty yet at the moment.
   * ** If prd!=pwr and queue.a[thiz->prd].evIdent !=0, it is the current entry. 
   * ** prd can be increment without lock.
   */
  int prd;  //use signed because difference building.

  /**Index of the next write position.
   * ** if (pwr+1) modulo sizeQueue == prd, then the queue is full. Add will be prevented.
   * **+ It means the last position in queue.a[..] will be never used. 
   * ** pwr is firstly incremented with atomicAccess to get a reservation for this position in pwrCurr
   * ** after them the position is filled, but queue.a[pwrCurrent].evIdent = x is set at last to confirm the completion. 
   * ** The width is int32 for 32-bit-Systems and 16 for 16-bit-Systems to use atomic access to memory.
   */
  int pwr; //+rd and wr-pointer

  union{ Entry_EvQueue_StateM_vishiaOrg_s* a; DebugArray_Entry_EvQueue_StateM_vishiaOrg_s* dbg; } queue;

  float Tstep;

  uint evIdForCreator;

  union{ struct EvInstance_StateM_vishiaOrg_T** a; DebugArray_EvInstance_StateM_vishiaOrg_s* dbg; } instances;




} EvQueue_StateM_vishiaOrg_s;



#define ID_refl_EvQueue_StateM_vishiaOrg 0x0FE3
#ifndef DEF_REFLECTION_NO 
  extern_C ClassJc const refl_EvQueue_StateM_vishiaOrg;
#endif

/**Initializes the queue.
 * @arg Tstep only for Graphical FBlock, not stored in FBlock 
 * @arg sizeQueue max nrof Events able to store for one evaluation cycle
 * @arg sizeListener max. nrof Listener able to add, TODO -1 then dynamically
 * @simulink ctor.
 */
extern_C EvQueue_StateM_vishiaOrg_s* ctor_EvQueue_StateM_vishiaOrg(ObjectJc* othiz, float Tstep, int sizeQueue, int sizeListener, ThCxt* _thCxt);

extern_C bool addEvInstance_EvQueue_StateM_vishiaOrg(EvQueue_StateM_vishiaOrg_s* thiz, struct EvInstance_StateM_vishiaOrg_T* evInstance, ThCxt* _thCxt);

//left empty only set in a test routine. 
#ifndef TEST_INTR1_ADD_EVQUEUE_StateM_emC
#define TEST_INTR1_ADD_EVQUEUE_StateM_emC
#define TEST_INTR2_ADD_EVQUEUE_StateM_emC
#define TEST_INTR3_ADD_EVQUEUE_StateM_emC
#endif



/**Adds an event with given evIdent and data to the queue with atomic lockfree mutex.
* This operation can be invoked in any thread or interrupt.
* @arg idEvent to add to queue in the next free Entry_EvQueue_StateM_vishiaOrg.
* @arg hData will be stored in the entry.
* return false if no more space in queue. true on success.
*/
inline bool add_EvQueue_StateM_vishiaOrg ( EvQueue_StateM_vishiaOrg_s* thiz
  , uint16 idEvent, uint32 hData) {
  #ifndef NO_PARSE_ZbnfCheader
  int abortCt = 100;
  bool ok;
  if(idEvent >= thiz->sizeInstances) {
    THROW_s0n(IllegalArgumentException, "faulty event Id =", idEvent, thiz->sizeInstances);
    return false;  //for systems without exception handling 
  }
  int pwrCurr;  //The index where the event should be written to the queue.
  do {
    int volatile* ptr = &thiz->pwr;
    pwrCurr = thiz->pwr;
    TEST_INTR1_ADD_EVQUEUE_StateM_emC
      int pwrNext = pwrCurr + 1;
    if(pwrNext >= thiz->sizeQueue) { pwrNext =0; } //modulo
    if(pwrNext == thiz->prd) return false;              //RETURN: no more space in queue         
    ok = compareAndSet_AtomicInteger(ptr, pwrCurr, pwrNext); //set the pwr for next access.
  } while(!ok && --abortCt >=0); //repeat if another thread has used this position.
  if(abortCt <0) {
    //it is a problem of thread workload, compareAndSet does not work.
    THROW_s0n(IllegalStateException, "thread compareAndSet problem", 0, 0);
    return false; //RETURN for non-exception handling, THROW writes a log entry only.
  }
  //the pwrCurr is proper for this entry, another thread may increment thiz->pwr meanwhile
  //but the other thread uses the position after.
  Entry_EvQueue_StateM_vishiaOrg_s* e = &thiz->queue.a[pwrCurr];
  e->hdata.h = hData;   
  TEST_INTR2_ADD_EVQUEUE_StateM_emC
    e->evIdent = idEvent;     
  return true;
  #endif//NO_PARSE_ZbnfCheader
}
/**Returns the pointer to the current entry or null if the queue is empty.
* After evaluation of the referenced content the operation 
* [[quitNext_EvQueue_StateM_vishiaOrg(...)]] has to be invoked to increment the read
* position respectively to free the entry for writing on end of the queue.. 
*/
inline Entry_EvQueue_StateM_vishiaOrg_s* 
getNext_EvQueue_StateM_vishiaOrg ( EvQueue_StateM_vishiaOrg_s* thiz) {
  if(thiz->prd == thiz->pwr) return null;
  else {
    Entry_EvQueue_StateM_vishiaOrg_s* e = &thiz->queue.a[thiz->prd];
    if(e->evIdent == 0) return null; //the entry is not finished written on add
    else return e;
  }
} 

inline void quitNext_EvQueue_StateM_vishiaOrg ( EvQueue_StateM_vishiaOrg_s* thiz
, ThCxt* _thCxt) {
  ASSERTs_emC(thiz->prd != thiz->pwr, "faulty quit", thiz->prd, thiz->pwr);
  thiz->queue.a[thiz->prd].evIdent = 0;  //mark as unused firstly for next wr and rd after them.
  int32 prd = thiz->prd +1;
  if(prd >= thiz->sizeQueue){ prd -= thiz->sizeQueue; } //wrapping
  thiz->prd = prd;
  thiz->evCt +=1;  //only for debug 
}


/**Reads one event from queue and applies it to a registered listener. 
 * After this call the listener should be executed because of its event should be applied to destinations.
 * Further calls of this operation should be done after them maybe in the same cycle or in the next calculation cycle. 
 */
extern_C bool checkForListener_EvQueue_StateM_vishiaOrg(EvQueue_StateM_vishiaOrg_s* thiz, ThCxt* _thCxt);


extern_C int16 info_EvQueue_StateM_vishiaOrg(EvQueue_StateM_vishiaOrg_s* thiz, int16* ctEvents_y);



/**A routine to view the status. It is especially for Modelling to see what's happen and to have a step routine.
 * @simulink Object-FB, no-thizStep.
 */
extern_C void status__EvQueue_StateM_vishiaOrg(EvQueue_StateM_vishiaOrg_s* thiz, int16* nrofEvents_y, int16* ctEvents_y);




/*@CLASS_C EvInstance_StateM_vishiaOrg @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct EvInstance_StateM_vishiaOrg_T {

  union { ObjectJc obj; } base;

  struct EvQueue_StateM_vishiaOrg_T* evQueue;

  float Tstep;

  uint16 evId;

  uint8 stateInput;

  uint8 stateTrg;

  int ctEvents;  //Note: use signed int to enable build differences on overflow!


  HandlePtr32Union_emC(ObjectJc) hdata;


} EvInstance_StateM_vishiaOrg_s;

#define ID_refl_EvInstance_StateM_vishiaOrg 0x0FE2
#ifndef DEF_REFLECTION_NO 
  extern_C ClassJc const refl_EvInstance_StateM_vishiaOrg;
#endif

/**Initializes an instance of an event.
 * @arg asListener true (!=0) then it should be registered in the queue as listener too, =0 then only to add events.
 * @simulink ctor.
 */
extern_C EvInstance_StateM_vishiaOrg_s* ctor_EvInstance_StateM_vishiaOrg(ObjectJc* othiz, int asListener, ThCxt* _thCxt);


/**Connects the EvQueue to the Instance on initialize phase.
 * @arg hdata given data handle (reference) 
 * @arg evIdent ==0 then the ident will be gotten as next free slot from the queue-registration
 *              !=0 then it have to be <= the number of listener for events in the queue and this slot should be free.
 * @arg queue The instance is related anyway to a queue, either to create event entries in the queue, 
 *            or to get events from the queue for call, or both.
 * @arg evId_y output the real gotten event evIdent.  
 * @simulink init.
 */
extern_C bool init_EvInstance_StateM_vishiaOrg(EvInstance_StateM_vishiaOrg_s* thiz, uint32 hdata, uint16 evIdent, EvQueue_StateM_vishiaOrg_s* queue, uint16* evId_y);


/**Creates an event on rising edge of signal.
* @simulink Object-FB, no-thizStep.
*/
inline void trgRising_EvInstance_StateM_vishiaOrg(EvInstance_StateM_vishiaOrg_s* thiz, bool signal) {
  if(signal){
    if(thiz->stateInput==0) {
      add_EvQueue_StateM_vishiaOrg(thiz->evQueue, thiz->evId, thiz->hdata.h);
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
inline void dataCall_EvInstance_StateM_vishiaOrg(EvInstance_StateM_vishiaOrg_s* thiz) {
  //empty, should only forward the thiz-output.
}



/**Creates an event on any call. It is for an called subsystem in Simulink 
* which is called on an output event of a Statechart-FBlock.
* @simulink Operation-FB.
*/
inline void trgCall_EvInstance_StateM_vishiaOrg(EvInstance_StateM_vishiaOrg_s* thiz) {
  add_EvQueue_StateM_vishiaOrg(thiz->evQueue, thiz->evId, thiz->hdata.h);
}



inline bool isAddedToQueue_EvInstance_StateM_vishiaOrg(EvInstance_StateM_vishiaOrg_s* thiz) {
  return thiz->stateTrg < 0x40; 
}

/**Returns the hdata if an event was applied after calling [[checkForListener_EvQueue_StateM_vishiaOrg(...)]].
* A further call returns 0.
* @return 0 if it has not an event.
* @simulink Operation-FB, fnCallTrg.
*/
inline uint32 hasEvent_EvInstance_StateM_vishiaOrg(EvInstance_StateM_vishiaOrg_s* thiz, uint32* hdata_y, int32* ctEv_y) {
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







#endif //DEF_evQueue_StateM_vishiaOrg
