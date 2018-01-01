/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content Definition of memory access routines. 
 * This routines are implemented in a operation system specific way. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * 2012-09-09: Hartmut creation from Java org.vishia.util.Event 
 *
 ************************************************************************************************/
#ifndef __fw_Event_h__
#define __fw_Event_h__
#include <applstdefJc.h>
#include <Fwc/objectBaseC.h>

/**This structure describes a full qualified event which may be a base strucure (super class) of an derivated event.
 * It is similar like srcJava_vishiaBase/org/vishia/event/Event.
 */
typedef struct Event_Fwc_t{
  
  /**The base class object contains the type of the event, using reflection. */
  ObjectJc object;

  struct EventSource_Fwc_t* source;

  struct Event_Fwc_t* opponent;

  struct EventThread_t* evDstThread;

  struct EventConsumer_t* evDst;

  int32_t cmde;

  int32_t dateCreation;

} Event_Fwc;



/*@CLASS_C EventQueueSimple @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/




/**A more simple approach of an event is: An event is only a integer value. This is proper for embedded applications
 * which does not deal with events yet or often.
 * Thread safety: It is recommended to write only in one thread. It is possible to divide a fast thread in more caclulation cycle times.
 * Elsewhere a semaphore should be used.
 */
typedef struct EventQueueSimple_Fwc_t
{
  /**Write and read index. If both are equal, then the queue is empty.
   * The indices are always in range 0... zQueue-1.
   * 
   */
  int ixWrEvent, ixRdEvent;  //write and read index.
  /**Size of the queue. */
  int zEvents; 
  
  /**Array for 20 events to store. This array can be increased by definition of some more memory as int array[] 
   * after this struct instance in an hyper struct.
   */
  int events[20]; 
} EventQueueSimple_Fwc;


/**Constructs.
 * @param sizeMemAdditonal number of memory locations (bytes) after this struct which are used to store events. 0 if no additonal space is given.
 */
void ctor_EventQueueSimple_Fwc(EventQueueSimple_Fwc* thiz, int sizeMemAdditional);



/**Store an event in a queue.
 * @return false then the queue is full. This situation should not be occure elsewhere on a software error. 
 *   The amount of events which are generated between the steps of the state machine should be limited.
 *   If the statemachine runs, the queue will be cleared always. Typically only 1 event is in the queue.  
 */
bool offer_EventQueueSimple_Fwc(EventQueueSimple_Fwc* thiz, int event);

/**reads an event from a queue. It returns 0 if the queue is empty. */
int read_EventQueueSimple_Fwc(EventQueueSimple_Fwc* thiz);
  




#endif  //Headerguard