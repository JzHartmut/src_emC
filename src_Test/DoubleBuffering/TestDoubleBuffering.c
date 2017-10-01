#include <applstdefJc.h>
#include <os_atomicAccess.h>
#include <os_thread.h>
#include <os_sync.h>
#include <os_time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MainData {



  struct OS_Mutex_t* hMutexPrintf;

  OS_HandleThread hthread1;

  bool bRun;


  int32 buffer[2][10];
  int32 ixBuffer;

  int step;

} MainData;


static MainData mainData = {0};



//Helper for thread safe printf
//Note: a printf should not interrupted by another thread. It is not threadsafe!
//Therefore it have to be sorrounded with a mutex!
void printf0_MainData(MainData* thiz, char const* txt)
{
  os_lockMutex(thiz->hMutexPrintf);
  printf(txt);
  os_unlockMutex(thiz->hMutexPrintf);
}


//Helper for thread safe printf
void printf1_MainData(MainData* thiz, char const* txt, int32 val)
{
  os_lockMutex(thiz->hMutexPrintf);
  printf(txt, val);
  os_unlockMutex(thiz->hMutexPrintf);
}







void writeBuffer(MainData* thiz);


/**The readBuffer operation is invoked in a thread. It needs more time as the interrupt cycle.
 * In this example any read word operation is delayed by 1 ms. Therefore it needs about 10 ms calculation time.
 * It will be interrupted with a write operation either selten or always, depending on the interrupt cycle.
 * The routine writes a message on start of line with the sequence number.
 */
void readBuffer(MainData* thiz)
{
  int ix = lockRead_DoubleBufferingJc(&thiz->ixBuffer); //get and lock
  char const* txt = ix==0? "a":"b";
  int32 sum = 0;
  int ixdata;
  printf1_MainData(thiz, "\n rd:%d: ", thiz->buffer[ix][0]); //show the sequence number
  for(ixdata = 1; ixdata < 10; ++ixdata) {
    printf0_MainData(thiz, txt);
    sum += thiz->buffer[ix][ixdata];
    os_delayThread(1);   //let space for interrupt routine (here in a thread), ennable thread change.
  }
//  ASSERT_zI_Fwc(sum == 0, "\nconsistence error\n", sum);
  if(sum !=0) {
    STOP_zI_Fwc("", sum);  
  }
  unlockRead_DoubleBufferingJc(&thiz->ixBuffer);
}



/**The writeBuffer operation is invoked in the 'interrupt'. It is done in the PC test environment with a cycle in a thread.
 *
 */
void writeBuffer(MainData* thiz)
{
  int ixseq = lockWrite_DoubleBufferingJc(&thiz->ixBuffer);
  int ix = ixseq &1;
  int seq = ixseq >>kBitSeq_DoubleBufferingJc; 
  printf0_MainData(thiz, ix==0? "0":"1");
  int32 sum = 0;
  int ixdata;
  for(ixdata = 0; ixdata < 10; ++ixdata) {
    int32 val;
    if(ixdata == 0) {
      val = seq;
    } else if(ixdata < 9) {
      val = rand();
      sum += val;
    } else {
      val = -sum;  //the sum over all is 0, this is the condition for consistence.
    }
    thiz->buffer[ix][ixdata] = val;
  }
  unlockWrite_DoubleBufferingJc(&thiz->ixBuffer, ix);
}




/**This is the test routine which represents a thread routine
 */
int intrRoutine_MainData(MainData* thiz)
{
  writeBuffer(thiz);
  return 0;
}


/**This is the test routine which represents a thread routine
 */
int threadRoutine_MainData(MainData* thiz)
{
  int steps = 40;
  while(thiz->bRun) {
    os_delayThread(8); //107);
    readBuffer(thiz);  //because it contains wait(2), it needs about 20 ms.
    //printf0_MainData(thiz, "_b_");
    if(--steps <0){
      thiz->bRun = 0;
    }
  }
  return 0;
}



//This is the test routine which represents a cyclically interrupt.invocation. 
int intrWrapper_MainData(void* thizvoid)
{
  MainData* thiz = (MainData*)thizvoid; 
  while(thiz->bRun) {
    os_delayThread(8);
    intrRoutine_MainData(thiz);
    
  }
  return 0;
}


void init_MainData(MainData* thiz) {

  thiz->bRun = true;
  //
  //create the handles firstly before start thread routines! They used them immediately!
  os_createMutex("mutexPrintf", &thiz->hMutexPrintf);
  //
  //create and start the threads.
  os_createThread(&thiz->hthread1, intrWrapper_MainData, &mainData, "thread1", 5, 10000);

}


void main(const char** args)
{

  srand((uint) os_milliTime());  //Intializes C-random generator, use the current time for seed

  init_MainData(&mainData);
  threadRoutine_MainData(&mainData);
}








#include <stdio.h>
void message_zI_Fwc(char const* file, int line, char const* text, int value)
{ //NOTE: printf is not thread safe!
  os_lockMutex(mainData.hMutexPrintf);
  printf("stop at %d in %s: %8.8x %s\n", line, file, value, text); 
  os_unlockMutex(mainData.hMutexPrintf);
}
