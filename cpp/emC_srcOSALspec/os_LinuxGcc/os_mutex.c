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
#include <emC/OSAL/sync_OSemC.h>

//needed from os_adaption itself
#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_mem.h>
#include <emC/Base/Atomic_emC.h>
#include "emC_srcOSALspec/os_LinuxGcc/os_internal.h"

//Needed includes from os:
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>




//tag::createMutex[]
int createMutex_OSemC ( Mutex_OSemC_s* thiz, char const* pName) {
  int err = 0;
  thiz->name = pName;                //assume that the name-parameter is persistent! A simple "string literal"
  //
  MutexData_pthread* h = C_CAST(MutexData_pthread*, malloc(sizeof(MutexData_pthread)));
  err = pthread_mutexattr_init (&h->attr);
  //special: It does not compile, not commonly available
  //special? pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
  //special? pthread_mutexattr_setprotocol (&attr, PTHREAD_PRIO_INHERIT);
  if(err !=0){
    ERROR_SYSTEM_emC(0, "createMutex_OSemC attribute error ", err,0);
  }
  err = pthread_mutex_init (&h->m, &h->attr);
  thiz->osHandleMutex = h;             // store the handle for access!
  if(err !=0){
    ERROR_SYSTEM_emC(0, "createMutex_OSemC error", err,0);
  }
  return err;  //usual 0
}
//end::createMutex[]


//tag::deleteMutex[]
int deleteMutex_OSemC(Mutex_OSemC_s* thiz) {
  MutexData_pthread* hmutex = C_CAST(MutexData_pthread*, thiz->osHandleMutex);
  free(hmutex);
  thiz->osHandleMutex = null;                     // set it to null before destroy and:
  if(thiz->lockingThread !=null) {
    THROW_s0n(RuntimeException, "mutex is locked while deleting ", (int)(intPTR)thiz->lockingThread, (int)(intPTR)hmutex);  // not an ERROR_SYSTEM, a user error
  }
  int err = pthread_mutex_destroy(&hmutex->m);
  return err;
}
//end::deleteMutex[]




//tag::lockMutex[]
bool lockMutex_OSemC(Mutex_OSemC_s* thiz) {
  MutexData_pthread* hmutex = C_CAST(MutexData_pthread*, thiz->osHandleMutex);
  int error;
  Thread_OSemC* hthread = getCurrent_Thread_OSemC();
  if(thiz->lockingThread == hthread) {
    thiz->ctLock +=1;                            // reentrant lock, accept it, do not lock really
    return true;                                 // but count the number of locks.
  } else {
    error = pthread_mutex_lock(&hmutex->m);         // it was not locked by the own thread, lock or wait for lock
    //--------------------------------------------> now it is locked, or we have an error
    //                                           // write the own thread, under lock, using compareAndSwap to write it back to core RAM
    void*volatile* refThread = WR_CAST(void*volatile*,C_CAST(void const**, &thiz->lockingThread)); //Note: to execute atomic, should be volatile*
    void* givenThread = compareAndSwap_AtomicRef(refThread, null, hthread);   // expect null, then write
    if(error != 0){                              // error should be 0.
      ERROR_SYSTEM_emC(0, "unknown error in pthread_mutex_lock ", error, 0);  // Note: the thread should be noted for debugging
      return false;
    } else if(givenThread != null) {             // then also compareAndSwap has failed
      ERROR_SYSTEM_emC(0, "lockMutex_OSemC htread not 0", 0,0);
      return false;
    } else {
      thiz->ctLock = 1;                          // assert that the mutex should be free before, it is the first lock.
      return true;
    }
  }
}
//end::lockMutex[]






//tag::unlockMutex[]
bool unlockMutex_OSemC(Mutex_OSemC_s* thiz) {
  MutexData_pthread* hmutex = C_CAST(MutexData_pthread*, thiz->osHandleMutex);
  Thread_OSemC const* hthread = getCurrent_Thread_OSemC();
  //----------------------------------------------- Expect, we are under lock, all other is faulty
  if(hthread != thiz->lockingThread) {           // check if the thread is correct, do not unlock the faulty mutex
    THROW_s0n(RuntimeException, "faulty thread on unlock ", (int)(intPTR)hthread, 0);  // not an ERROR_SYSTEM, a user error
    return false;
  }
  if(--thiz->ctLock >0) {
    return true;                                 // successfully unlock of an reentrant lock of the same thread. Locking is still active.
  } else {
    thiz->lockingThread = null;                  // now it will be really unlocked (set lockingThread = null before unlock, under mutex!)
    int error = pthread_mutex_unlock(&hmutex->m);
    if(error != 0){
      ERROR_SYSTEM_emC(0, "unknown error in pthread_mutex_unlock ", error, 0);
      return false;
    }
  }
  return true;
}
//end::unlockMutex[]


//tag::lockFirst[]
bool lockMutexFirst_OSemC  ( struct Mutex_OSemC_T* thiz) {
  bool ok = lockMutex_OSemC(thiz);
  ASSERT_emC(thiz->ctLock ==1, "unlockMutexFirst ctLock !=1", thiz->ctLock, 0);
  return ok;
}


bool unlockMutexFirst_OSemC  ( struct Mutex_OSemC_T* thiz) {
  ASSERT_emC(thiz->ctLock ==1, "unlockMutexFirst ctLock !=1", thiz->ctLock, 0);
  return unlockMutex_OSemC(thiz);
}
//end::lockFirst[]


