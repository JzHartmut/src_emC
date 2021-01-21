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
 * @content Definition of event handling. 
 *
 * @author Hartmut Schorrig
 * @version
 * 2012-09-09: Hartmut creation from Java org.vishia.util.Event 
 *
 ************************************************************************************************/

#include <emC/Base/Event_emC.h>
#include <emC/Base/SimpleC_emC.h>
#include <string.h>



void ctor_EventQueueSimple_emC(EventQueueSimple_emC* thiz, int sizeMemAdditional) 
{ int bytes = sizeof(EventQueueSimple_emC) + sizeMemAdditional;  //sizeAdditional is number of bytes respecitvely mem locations.
  memset(thiz, 0, bytes);  
  thiz->zEvents = (sizeMemAdditional / sizeof(int)) + ARRAYLEN_emC(thiz->events);
}


bool offer_EventQueueSimple_emC(EventQueueSimple_emC* thiz, int event)
{
  int ixWrNew = thiz->ixWrEvent +1;
  if(ixWrNew >= thiz->zEvents) { ixWrNew = 0; } //wrap
  if(ixWrNew != thiz->ixRdEvent) {
    thiz->events[thiz->ixWrEvent] = event;
    thiz->ixWrEvent = ixWrNew;  //Note: if there are exactly 1 writing and one reading thread, it is safe to store the ixWr after set event.
    return true;
  } else {
    //next write would set ixWr == ixRd, it means the queue is empty, respectively it is written too much.
    return false;
  }
}



int read_EventQueueSimple_emC(EventQueueSimple_emC* thiz)
{ if(thiz->ixRdEvent != thiz->ixWrEvent) {
    return thiz->events[thiz->ixRdEvent++];  //Note: Post-increment. ixRdEvent refers the next current one.
  } 
  else{
    return 0;  //no event.
  }
}

