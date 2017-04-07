
#include <os_thread.h>
#include <os_sync.h>
#include <os_time.h>
#include <stdio.h>

typedef struct MainData {



  struct OS_Mutex_t* hMutexPrintf;

  struct OS_Mutex_t* hMutexNotify;

  OS_HandleWaitNotify hWaitNotify; 

  OS_HandleThread hthread1, hthread2;

  bool bRun;


  bool bNotify2;

  bool bWait2;

} MainData;


static MainData mainData = {0};




void printf0_MainData(MainData* thiz, char const* txt)
{
  static OS_HandleThread lastThread = 0;
  OS_HandleThread currentThread = os_getCurrentThreadHandle();
  os_lockMutex(thiz->hMutexPrintf);
  //Note: a printf should not interrupted by another thread. It is not threadsafe!
  //Therefore it have to be sorrounded with a mutex!
  if(currentThread != lastThread){
    printf("\n");
  }
  printf(txt);
  os_unlockMutex(thiz->hMutexPrintf);
  lastThread = currentThread;
}




int thread1Routine_MainData(void* thizvoid)
{
  MainData* thiz = (MainData*)thizvoid; 
  while(thiz->bRun) {
    //
    thiz->bNotify2 = true;
    //
    printf0_MainData(thiz, "_1_");
    { os_lockMutex(thiz->hMutexNotify);
      if(thiz->bWait2){
        os_notify(thiz->hWaitNotify, thiz->hMutexNotify);      
      }
      os_unlockMutex(thiz->hMutexNotify);
    }
    os_delayThread(1000);
    
  }
  return 0;
}




int thread2Routine_MainData(void* thizvoid)
{
  MainData* thiz = (MainData*)thizvoid; 
  while(thiz->bRun) {
    bool bWasNotified;
    { os_lockMutex(thiz->hMutexNotify);
      if(!thiz->bNotify2) {
        thiz->bWait2 = true;
        os_wait(thiz->hWaitNotify, thiz->hMutexNotify, 900);
        thiz->bWait2 = false;
      }
      bWasNotified = thiz->bNotify2; //store local whether it was notified
      thiz->bNotify2 = false;        //reset in mutex!
      os_unlockMutex(thiz->hMutexNotify);
    }
    if(bWasNotified) {
      printf0_MainData(thiz, "_notify-2_");
    } else {
      //wait was ended with timeout, not with notify:
      printf0_MainData(thiz, "_timeout-2_");
    }      
  }
  return 0;
}






int mainRoutine_MainData(MainData* thiz)
{
  int steps = 10;
  while(thiz->bRun) {
    os_delayThread(350);
    printf0_MainData(thiz, "_b_");
    if(--steps <0){
      thiz->bRun = 0;
    }
  }
  return 0;
}



void init_MainData(MainData* thiz) {

  thiz->bRun = true;
  //
  //create the handles firstly before start thread routines! They used them immediately!
  os_createMutex("mutexPrintf", &thiz->hMutexPrintf);
  os_createMutex("mutexNotify", &thiz->hMutexNotify);
  os_createWaitNotifyObject("waitnotify2", &thiz->hWaitNotify);
  //
  //create and start the threads.
  os_createThread(&thiz->hthread1, thread1Routine_MainData, &mainData, "thread1", 5, 10000);
  os_createThread(&thiz->hthread1, thread2Routine_MainData, &mainData, "thread2", 5, 10000);

}


void main(const char** args)
{

  init_MainData(&mainData);
  mainRoutine_MainData(&mainData);
}



