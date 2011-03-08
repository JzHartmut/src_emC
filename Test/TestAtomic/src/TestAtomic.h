#ifndef __TestAtomic_h__
#define __TestAtomic_h__
#include <os_types_def.h>


void test1();


typedef struct QueueItem_t
{
  struct QueueItem_t* volatile next;
  
  int32 ident;
}QueueItem;


typedef struct FifoQueue_t
{
  QueueItem* volatile first;
  QueueItem* volatile last;

}FifoQueue;


#endif  //__TestAtomic_h__
