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
 * @content Bodies of mutex routines for Windows-XP and Windows-2000.
 * The implementation is os-specific. A mutex should regard a second call from the same thread.
 * It is more complex as a simple semaphore request. 
 * Some operation systems supports this request immediately. 
 * If a opeation system does know only the semaphore mechanism, the thread identification
 *   should be stored in a mutex structure.
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * list of changes:
 * 2008-02-01: Hartmut creation 
 *
 ************************************************************************************************/
//the own include file firstly
#include <emC/OSAL/os_sync.h>

//needed from os_adaption itself
#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include "emC_srcOSALspec/os_LinuxGcc/os_internal.h"

//Needed includes from os:
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

OS_Mutex_s* os_createMutex(char const* pName) //, struct OS_Mutex_t** pMutex)
{
    OS_Mutex_s* mutex;
    const int zMutex = sizeof(struct OS_Mutex_t);
    
    mutex = (OS_Mutex_s*)malloc(zMutex);
    mutex->name = pName;             //assume that the name-parameter is persistent! A simple "string literal"
    pthread_mutexattr_init (&mutex->attr);
    //special? pthread_mutexattr_settype(&mutex->attr, PTHREAD_MUTEX_RECURSIVE_NP);
    //special? pthread_mutexattr_setprotocol (&mutex->attr, PTHREAD_PRIO_INHERIT);
    pthread_mutex_init (&mutex->mutex, &mutex->attr);

    //any error possible?

    //*pMutex = mutex;  //set the address of the mutex object in the reference variable to return
    return mutex;
}


void os_deleteMutex(OS_Mutex_s* mutex)
{   //TODO
  free(mutex);

}




bool os_lockMutex(OS_Mutex_s* mutexP, int timeout_millisec)
{ //TODO timeout
  OS_Mutex_s* mutex = (OS_Mutex_s*)mutexP; //the non-const variant.
  int error;
  if (timeout_millisec != 0) {
    struct timespec timeoutTime;
    clock_gettime(CLOCK_REALTIME, &timeoutTime);
    int sec = timeout_millisec / 1000;
    timeout_millisec -= sec*1000;  //module 1000
    timeoutTime.tv_nsec += 1000000 * timeout_millisec;
    if (timeoutTime.tv_nsec >= 1000000000) {
      timeoutTime.tv_nsec -= 1000000000;
      timeoutTime.tv_sec +=1;
    }
    timeoutTime.tv_sec += sec;
    error = pthread_mutex_timedlock(&mutex->mutex, &timeoutTime);
    if (error == 0) { //check wether the  mutex is locked
    //#error
    //this is not ready yet. Problem see https://stackoverflow.com/questions/2821263/lock-a-mutex-multiple-times-in-the-same-thread
    }
  }
  error = pthread_mutex_lock(&mutex->mutex);
  if(error != 0){
    THROW_s0n(RuntimeException, "unknown error in pthread_mutex_lock ", error, 0);
    //os_notifyError(OS_UNKNOWN_ERROR, OS_TEXT_UNKNOWN_ERROR, error, 0);
    return false;
  } else {
      return true;
  }
}


void os_unlockMutex(OS_Mutex_s* mutexP)
{
  OS_Mutex_s* mutex = (OS_Mutex_s*)mutexP; //the non-const variant.
  int error = pthread_mutex_unlock(&mutex->mutex);
  if(error != 0){
    THROW_s0n(RuntimeException, "unknown error in pthread_mutex_unlock ", error, 0);
    //os_notifyError(OS_UNKNOWN_ERROR, "os_unlockMutex: ERROR: Faild thread releases the mutex, win-error=%d\n", error, 0);
  }
}
