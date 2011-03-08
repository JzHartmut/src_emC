#include "TestAtomic.h"

#include <os_AtomicAccess.h>
#include <Fwc/fw_Exception.h>
#include <stdlib.h>
#include <Fwc/fw_SimpleC.h>

FifoQueue fifoQueue = {0};

QueueItem items[20];

QueueItem* itemRefs[20];

int nrUsage[20];

int thread = 1;

void add_FifoQueue(FifoQueue* ythis, QueueItem* item);
QueueItem* poll_FifoQueue(FifoQueue* ythis);


void disturbAddAfterFirstNull(int ix)
{ if(ix==0){
    add_FifoQueue(&fifoQueue, itemRefs[10]);
    itemRefs[10] = null;
  } 
  else if (ix == 5) {
    QueueItem* item = poll_FifoQueue(&fifoQueue);
    if(item != null){ itemRefs[item->ident] = item;}
  } 
}
        
void disturbAddAfterFirstNotNullLastNull(int ix)
{ if(ix==10){
    add_FifoQueue(&fifoQueue, itemRefs[11]);
    itemRefs[11] = null;
  }
}


/**If first==null, than last should be null too, and both are set by the added item.
 * But, while check first == null, another thread may be added.
 */
void disturbAddIfFirstNull()
{ thread +=1;
  if(thread == 2 && fifoQueue.first == null){
    add_FifoQueue(&fifoQueue, itemRefs[12]);
    itemRefs[12] = null;
  }
  thread -=1;
}

    
/**If first==null, than last should be null too, and both are set by the added item.
 * But, while check first == null, another thread may be added.
 */
void thread2add()
{ 
  thread +=1;
  if(thread ==2 ){
    int ix = 11;
    while(++ix < 20){
      if(itemRefs[ix] != null){  //search useable item.
        add_FifoQueue(&fifoQueue, itemRefs[ix]);
        itemRefs[ix] = null;
        break;
    } }
  }
  thread -=1;
}

    
void disturbRemoveIfOnlyOneElement()
{ if(fifoQueue.first == fifoQueue.last && fifoQueue.first == null){
    QueueItem* item = poll_FifoQueue(&fifoQueue);
    if(item != null){ itemRefs[item->ident] = item;}
  }
}
    



void checkQueue()
{ int ix;
  QueueItem* item = fifoQueue.first;
  QueueItem* next = item;
  STACKTRC_ENTRY("checkQueue");
  for(ix=0; ix<ARRAYLEN(nrUsage); ++ix){
    nrUsage[ix] = 0;
  }
  while(next !=null){
    item = next;
    if(item != null){
      int ix = item->ident;
      ASSERT(++nrUsage[ix] == 1);
      next = item->next;
    }
  };
  ASSERT(fifoQueue.last == item);
  STACKTRC_LEAVE;

}



void add_FifoQueue(FifoQueue* ythis, QueueItem* item)
{ bool bSuccess = false;
  int catastrophicCount = 10;
  do{
    QueueItem* first = ythis->first;
    QueueItem* last;
    QueueItem* next = null;
    disturbAddIfFirstNull();
    disturbRemoveIfOnlyOneElement();
    last = ythis->last;
    if(last!=null){ next=last->next; } 
    if(next == null){ 
      //normally, it is true, because the tail node is the last. But repeat on interrupt.
      item->next = null;
      if(first == null){
        //Than the queue is empty. last should be empty too. 
        //It should be set with this item too.
        bSuccess = compareAndSet_AtomicReference((void*volatile*)&ythis->first, null, item);
        if(bSuccess && last == null){
          disturbAddAfterFirstNull(item->ident);
          //try to set last with item.
          compareAndSet_AtomicReference((void*volatile*)&ythis->last, null, item);
          //if it is unsuccessfull, than ythis->last is not changed. it is ok.
        }
      } else { //first !=null
        if(last == null){ 
          //add in situation first==null, last ==null was interrupted,
          //Now complete the setting of last.
          disturbAddAfterFirstNotNullLastNull(item->ident);
          compareAndSet_AtomicReference((void*volatile*)&ythis->last, null, first); 
        } else {
          bSuccess = compareAndSet_AtomicReference((void*volatile*)&last->next, null, item);
          if(bSuccess){
            thread2add();
            compareAndSet_AtomicReference((void*volatile*)&ythis->last, last, item);
          }
        }
      }   
    } else {
      //The thread has interrupted another access to the the last reference,
      //before the last was set to the really end.
      //Therefore: Set the last to the next found strange entry.
      //after them the test will be repeated so long as next == null.
      compareAndSet_AtomicReference((void*volatile*)&ythis->last, last, next);
    }
  } while(!bSuccess && --catastrophicCount >=0);
   
}



QueueItem* poll_FifoQueue(FifoQueue* ythis)
{ bool bSuccess = false;
  QueueItem* first;
  QueueItem* last;
  QueueItem* second;
    
  int catastrophicCount = 10;
  do{
    first = ythis->first;
    last = ythis->last;
    second = first != null ? first->next: null;
    if(first != null){
      bSuccess = compareAndSet_AtomicReference((void*volatile*)&ythis->first, first, second);
      if(bSuccess && second == null){
        compareAndSet_AtomicReference((void*volatile*)&ythis->last, last, null);
      }
    }
  } while(!bSuccess && --catastrophicCount >=0);
  return first;   
}


void test1()
{
  int ix;
  QueueItem* item;
  STACKTRC_ENTRY("test1");

  //Initialize all items in its storage reservoire. 
  //The items contain the index of the reservoire.
  for(ix=0; ix < ARRAYLEN(items); ++ix){
    items[ix].ident=ix;
    itemRefs[ix] = &items[ix];
  }

  //Add 3 items. While that, the second and third thread will disturb the operation.
  //read the log! 
  for(ix=0; ix<3; ++ix){
    QueueItem* item = itemRefs[ix];
    itemRefs[ix] = null;
    add_FifoQueue(&fifoQueue, item);
  }
  checkQueue();

  do{
    item = poll_FifoQueue(&fifoQueue);
    if(item!=null){
      itemRefs[item->ident] = item; 
    }
  } while(item != null);


  for(ix=5; ix<8; ++ix){
    QueueItem* item = itemRefs[ix];
    itemRefs[ix] = null;
    add_FifoQueue(&fifoQueue, item);
  }
  checkQueue();



 
  STACKTRC_LEAVE;
}
