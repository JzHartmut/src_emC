#ifndef HGUARD_emC_Base__EventQu_emC
#define HGUARD_emC_Base__EventQu_emC
/**This header defines the interface to a simple event-task-system.
 * made by Hartmut Schorrig, www.vishia.org
 */

#include <applstdef_emC.h>
#include <emC/Base/Time_emC.h>


struct TaskConstData_emC_T;

//tag::EventTask_emC[]
/**The variable data for a task which can be activated. 
 * This is the event instance which can used immediately to poll in a simple task scheduler.
 * 
 * The variable data are referenced from a const [[struct TaskConstData_emC_T]].
 * Then one const TaskConstData_emC refers exact one instance of this struct. 
 * Activating the event is possible with a given time and priority.
 * Hence this data should be referenced and used only via the const TaskConstData_emC instance.
 */
typedef struct EventTask_emC_T {

  /**A priority counter, up counting, 0 = not activated, >0 should be activated, higher number <=126 is prior.
   * With that some events can be designated with an execution priority.
   * It enables another principle than First in First out.
   */
  uint8 ctPriority;

  /**The priotity use bits 6..0, max value 126*/
  #define mPrio_EventTask_emC 0x7f

  /**If this bit is set, the instance is of type EventTaskTime_emC_s, with time. */
  #define mTime_EventTask_emC 0x80


} EventTask_emC_s;
//end::EventTask_emC[]

#define ID_refl_EventTask_emC 0x0FE2
#ifndef DEF_REFLECTION_NO 
  extern_C ClassJc const refl_EventTask_emC;
#endif

/**Release this event instance independent whether it is activated or not.
 * A pending activation is cleaned.
 */
static inline void release_EventTask_emC(EventTask_emC_s* thiz) {
  thiz->ctPriority = 0;
}

/**Constructor for dynamic allocated data, sets all inactive.
 * For static initialization the {0} initialization with an initializer list is sufficient.
 */
extern_C void ctor_EventTask_emC(EventTask_emC_s* thiz, char const* idString);

/**Check whether this entry is free.
 * @return true if free, false if it is activated (in use). 
 */
static inline bool isFree_EventTask_emC(EventTask_emC_s* thiz, uint priority) {
  return (thiz->ctPriority == 0);
}



//tag::activate_EventTask_emC[]
/**Activates the entry if it is free. 
 * If the event is not free, in use, queued resp. activated this routine does nothing but returns false.
 * @param priority higher value till 254 means, execute it prior.
 *   But the priority will be counted up on each test.
 * @return true if activated, false if it is activated (in use) already. 
 */
static inline bool activate_EventTask_emC(EventTask_emC_s* thiz, uint priority) {
  if(thiz->ctPriority == 0) {
    ASSERT_emC(priority < mPrio_EventTask_emC, "priority faulty", 0, 0); 
    thiz->ctPriority = priority;
    return true;
  } else {
    return false;  // it is already activated.
  }
}
//end::activate_EventTask_emC[]


//tag::EventTaskTime_emC[]
/**The variable data for a task which can be activated. 
 * This is the event instance which can used immediately to poll in a simple task scheduler.
 * 
 * The variable data are referenced from a const [[struct TaskConstData_emC_T]].
 * Then one const TaskConstData_emC refers exact one instance of this struct. 
 * Activating the event is possible with a given time and priority.
 * Hence this data should be referenced and used only via the const TaskConstData_emC instance.
 */
typedef struct EventTaskTime_emC_T {

  /**Basic class with priority, same behavior. */
  EventTask_emC_s prio;

  /**A short time from which this task should be executed. 
   * This short time should be system width related to a wrapping short time counter
   * which allows also a relation to an absolute time. 
   * But the short time is more simple to execute. 
   * This cell is not counting, it is not a delay. 
   * It is a given time in the short time system to clarify when to start the task.
   * Therewith cyclically tasks are possible.
   */
  int timeExec;

} EventTaskTime_emC_s;
//end::EventTaskTime_emC[]


//tag::activate_EventTaskTime_emC[]
/**Activates the entry to a dedicated time if it is free.
 * If the event is not free, in use, queued resp. activated this routine does nothing but returns false.
 * Generally: The taks is started if the current time, incremented by the fast cyclically interrupt,
 * is greater or equal the registered time. It means if the registered time is in the past 
 * alreday while calling this routine, the activating will be done immediately (depending on priority).
 * The quest past or future is determined by the sign of the difference between the current time,
 * gotten via timeShortStepCycle_emC() minus the here registered time. If the difference is positive, 
 * the time is expired. A negativ difference means, future. Because of the wrapping property 
 * the half period can be used. A time difference > half wrapping period is not possible. 
 * The wrapping point itself is not a problem because differences are built without overflow in C(++) language,
 * it is anyway correct for signed integer.  
 * @param priority higher value till 126 means, execute it prior.
 *   But the priority will be counted up on each test.
 * @param time start time related to the global interrupt cycle time.
 * @return true if activated, false if it is activated (in use) already.
 */
static inline bool activate_EventTaskTime_emC(EventTaskTime_emC_s* thiz, uint priority, int time) {
  if(thiz->prio.ctPriority == 0) {
    ASSERT_emC(priority < mPrio_EventTask_emC, "priority faulty", 0, 0); 
    thiz->timeExec = time;
    thiz->prio.ctPriority = priority | mTime_EventTask_emC;
    return true;
  } else {
    return false;  // it is already activated.
  }
}
//end::activate_EventTaskTime_emC[]



//tag::activateDelayed_EventTaskTime_emC[]
/**Activates the entry with a delay due to the current time if it is free. 
 * @param priority higher value till 126 means, execute it prior.
 *   But the priority will be counted up on each test.
 * @param delay start time delay related to the global interrupt cycle time. 
 * @return true if activated, false if it is activated (in use) already. 
 */
static inline bool activateDelayed_EventTaskTime_emC(EventTaskTime_emC_s* thiz, uint priority, int delay) {
  if(thiz->prio.ctPriority == 0) {
    ASSERT_emC(priority < mPrio_EventTask_emC, "priority faulty", 0, 0);
    thiz->timeExec = timeShortStepCycle_emC() + delay;
    thiz->prio.ctPriority = priority | mTime_EventTask_emC;
    return true;
  } else {
    return false;  // it is already activated.
  }
}
//end::activateDelayed_EventTaskTime_emC[]


//tag::activateCycle_EventTaskTime_emC[]
/**Activates the entry to a next cycle time if it is free. 
 * @param priority higher value till 126 means, execute it prior.
 *   But the priority will be counted up on each test.
 * @param cyclediff start time added to the last start time. This builds a stable cycle time.  
 * @return true if activated, false if it is activated (in use) already. 
 */
static inline bool activateCycle_EventTaskTime_emC(EventTaskTime_emC_s* thiz, uint priority, int cycletime) {
  if(thiz->prio.ctPriority == 0) {
    ASSERT_emC(priority < mPrio_EventTask_emC, "priority faulty", 0, 0); 
    thiz->timeExec += cycletime;
    thiz->prio.ctPriority = priority | mTime_EventTask_emC;
    return true;
  } else {
    return false;  // it is already activated.
  }
}
//end::activateCycle_EventTaskTime_emC[]



/**The common form of the event callback operation, which is executed by the event. 
 * @param entryData The event entry. It should be freed during this operation, if the data are gotten.
 *        use lockfree compareAndSwap to inform about gotten data.
 *        invoke release_EventTask_emC(...) if you have gotten all associated data.
 */
typedef void TaskOperation_emC(struct TaskConstData_emC_T const* entryConstData);

//tag::TaskConstData_emC[]
/**Structure for const area (Flash, read only) for a given task.
 * This structure contains a pointer to the task operation which should not able to destroy by any obscure software error.
 * The associated event data are stored in RAM.
 */
typedef struct TaskConstData_emC_T {

  /**It is for safetry check if the pointer to this const data are managed in data area. */
  char const* signatureString;

 
  /**The operation to call with the event. @noReflection */
  TaskOperation_emC* operation;

  /**data to use with the task operation. Can be null.
   * In C programming only static data on a known memory address can be used here.
   * This is also recommended for const in flash.
   */
  ObjectJc volatile* thizData;
  
  /**Reference to the event entry which may have current data for activating.
   * It is necessary for polling over all given TaskConstData_emC instances. */
  EventTask_emC_s volatile* const evEntry;
} TaskConstData_emC;
//end::TaskConstData_emC[]

extern_C char const* const signatureString_TaskConstData_emC;
//extern_C char const signatureString_TaskConstData[];


/**Initializer for the const data. */
//#define INIZ_TaskConstData_emC(OPER, THIZ, EVENT_DATA) { OPER, THIZ, EVENT_DATA }
#define INIZ_TaskConstData_emC(OPER, THIZ, EVENT_DATA) { signatureString_TaskConstData_emC, OPER, THIZ, EVENT_DATA }


/**Executes the polling of all given tasks and call the highest prior task.
 * The event with the highest priority >0 will be started.
 * All events with priority >0 will be count up in priority,
 * so that older events will be prior in comparison the newer ones if they are activated with the same priority.
 * @param evTaskArray This is an array of all entries given as pointer.
 *   Note that the evTask const data can be dispersed in the software.
 *   A central array with all entries is needed. This is used here.
 * @param nrofEntries length of this array. Use ARRAYLEN_emC(evTaskArray) for a const given array.
 */
extern_C void execPolling_EventTask_emC ( TaskConstData_emC const* const* evTaskArray, int nrofEntries);





#endif //HGUARD_emC_Base__EventQu_emC
