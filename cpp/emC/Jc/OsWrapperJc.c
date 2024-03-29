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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 * @content: This file contains all methods from CRuntimeJavalike which have access to the operation system level.
 * Only the routines here uses the os_wrapper.h and are dependent on it. All other routines are os-independent.
 * The os_wrapper.h defines the interface to the operation system in a os-independently way.
 * But the os_wrapper.h may be adapted to os-requirements in the future. So only this source is involved.
 *
 * @author Jchartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2008-04-22: JcHartmut adap: changes from objectBaseC.h
 * 2008-03-15: JcHartmut creation
 *
 ****************************************************************************/
#include <applstdef_emC.h>




#include "emC/Jc/OsWrapperJc.h"
//#ifdef DEF_ObjectJc_SYNCHANDLE

#include <emC/Base/SimpleC_emC.h>
#include <emC/Base/StringBase_emC.h>
//#include <Jc/ObjectJc.h>

#include <emC/OSAL/thread_OSemC.h>
#include <emC/OSAL/os_time.h>
#include <emC/OSAL/sync_OSemC.h>
#include <emC/OSAL/os_AtomicAccess.h>

#include <string.h>


#ifdef DEF_ObjectJc_SYNCHANDLE
//It works only if the ObjectJc has the SyncHandle.
//Yet 2023-07-03 refactored but not tested. Not used yet.

OsWrapperJc_s data_OsWrapperJc = { 0 };



/**This routine is called only onetime after startup. */
int initFreeHandleEntry  (  )
{ int zHandleItems = ARRAYLEN_emC(data_OsWrapperJc.handleItemsJc);
  int ii;
  data_OsWrapperJc.handleItemsJc[0].nextFree = kNoFreeHandleItem;  //let the first unused, no using of index 0!
  data_OsWrapperJc.freeHandle = &data_OsWrapperJc.handleItemsJc[1];
  for(ii = 1; ii < zHandleItems -1; ii++)
  { data_OsWrapperJc.handleItemsJc[ii].nextFree = &(data_OsWrapperJc.handleItemsJc[ii+1]);
  }
  data_OsWrapperJc.handleItemsJc[ii].nextFree = kNoFreeHandleItem;  //the last one.
  return zHandleItems;
}






/**gets a free handle.
 * @param idx the returned index.
 */
HandleItem* getFreeHandleEntry  (  int16* idx)
{ //this operation have to be executed under mutex:
  HandleItem* theHandleItem;
  if(data_OsWrapperJc.nrofHandle == 0) {  //if not 0, it is initialized. Use it. Short quest.
    //if 0, it is possible that another thread does the same. Repeat the quest with mutex.
    Mutex_OSemC_s mutexInitHandle;         //local ref
    createMutex_OSemC(&mutexInitHandle, "JcinitHandle");
    //try to set the local ref,
    //void* mutexInitHandleVoid = WR_CAST(void*, C_CAST(void const*, mutexInitHandle));
    if(null != compareAndSwap_AtomicRef((void* volatile*)&data_OsWrapperJc.mutexInitHandle.osHandleMutex, null, mutexInitHandle.osHandleMutex)) {
      //yet a mutex was created from another thread already.
      deleteMutex_OSemC(&mutexInitHandle);  //delete the own one.
      //mutexInitHandle = data_OsWrapperJc.mutexInitHandle;  //use the existing from the ohter thread.
    } else {
      //the handle is successfully set. Now set also the rest (if given)
      memcpy(&data_OsWrapperJc.mutexInitHandle, &mutexInitHandle, sizeof(data_OsWrapperJc.mutexInitHandle));
    }
    //There is only one determined mutex instance 
    { lockMutex_OSemC(&data_OsWrapperJc.mutexInitHandle);  
      //repeat the quest and the initialization under mutex.
      if(data_OsWrapperJc.nrofHandle == 0) {
        data_OsWrapperJc.nrofHandle = initFreeHandleEntry();
      }
      unlockMutex_OSemC(&data_OsWrapperJc.mutexInitHandle);  
    }
  }
  int tryCt = 10000;
  do { 
    theHandleItem = data_OsWrapperJc.freeHandle;
    if(theHandleItem == kNoFreeHandleItem)
    { *idx = -2;  //TODO passenden Win-error
      return null;
    }
    HandleItem* nextFree = theHandleItem->nextFree;  //it may be null if there is no more handle.
    if(compareAndSwap_AtomicRef((void* volatile*)&(data_OsWrapperJc.freeHandle), theHandleItem, nextFree) == theHandleItem ) {
      break;  //if succeeded
    }
  } while(--tryCt > 0);
  if(tryCt == -1) {
    *idx = -2;  //too many try, only in catastrophical situation. But the while should be broken!
    return null;
  }
  else 
  { int idxHandle = (int)(theHandleItem - data_OsWrapperJc.handleItemsJc);
    if(idxHandle < 0 || idxHandle >= ARRAYLEN(data_OsWrapperJc.handleItemsJc))
    { STACKTRC_ENTRY("getFreeHandleEntry");
      THROW1_s0(RuntimeException, "corrupt handles",idxHandle);
    }
    *idx = (int16)(idxHandle);
    memset(theHandleItem, 0, sizeof(*theHandleItem));
    return theHandleItem;
  }
}





/**gets the handle to the index.
 */
HandleItem* getHandleEntry  (  int idx)
{ if(idx < 0 || idx > ARRAYLEN(data_OsWrapperJc.handleItemsJc))
  { STACKTRC_ENTRY("getHandleEntry");
    THROW1_s0(RuntimeException, "error fault idx for handle", idx);
  }
  return &data_OsWrapperJc.handleItemsJc[idx];
}




void releaseHandleEntry  (  int16 idx)
{
  HandleItem* currNextFree;
  HandleItem* releaseHandle = &data_OsWrapperJc.handleItemsJc[idx];
  if(releaseHandle->handleMutex.osHandleMutex) {
    deleteMutex_OSemC(&releaseHandle->handleMutex);
  }
  if(releaseHandle->handleWaitNotify.osHandleWaitNotify) {
    deleteWaitNotifyObj_OSemC(&releaseHandle->handleWaitNotify);
  }
  int tryCt = 10000;
  while(--tryCt > 0) {
    currNextFree = data_OsWrapperJc.freeHandle;
    releaseHandle->nextFree = currNextFree;  //referes the next next then 
    if(compareAndSwap_AtomicRef((void* volatile*)&(data_OsWrapperJc.freeHandle), currNextFree, releaseHandle) == currNextFree) {
      break;  //if succeeded
    }
    if(tryCt == -1) {
      //on too many try loops, do nothing, the system is instable already. The handle is not released.
      tryCt -=1;  //set breakpoint here.
    }
  }
}



/**************************************************************************************************/
/* Implementations of ObjectJc.h
*/

#ifndef DEF_ObjectJc_SYNCHANDLE
  //use instead identSize
  //Note: do not define such one on header file level! Should only visible locally
  #define handleBits identSize
#endif


/**This is the only one routine which changed the ObjectJc data, 
 * but only one time if the handle is not set. 
 * Hint: thiz is changed in handleBits if they are not used till now.
 */
INLINE_emC HandleItem* getHandleExist_ObjectJc ( ObjectJc const* thiz) {
  HandleItem* handle = null;
  int err = 0;
  int16 ixHandle = thiz->handleBits & mSyncHandle_ObjectJc;
  if(ixHandle == kNoSyncHandles_ObjectJc) {
    return null;
  } else {
    handle = getHandleEntry(ixHandle);
    return handle;
  }
}


/**This is the only one routine which changed the ObjectJc data, 
 * but only one time if the handle is not set. 
 * Hint: thiz is changed in handleBits if they are not used till now.
 */
INLINE_emC HandleItem* getHandle_ObjectJc ( ObjectJc const* thiz) {
  HandleItem* handle = null;
  int16 ixHandle = thiz->handleBits & mSyncHandle_ObjectJc;
  if(ixHandle == kNoSyncHandles_ObjectJc) {
    handle = getFreeHandleEntry(&ixHandle);  //ixHandle set with valid index.
    if(ixHandle <= 0) {
      STACKTRC_ENTRY("getHandleAndLock_ObjectJc");
      THROW1_s0(RuntimeException, "error no handle", 0);
      STACKTRC_LEAVE;
      return null; //no handle available
    } else {
      int16 newValue, oldValue;
      int tryCt = 1000;
      #ifndef DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE
        strcpy_emC(handle->name, "Jc_00", sizeof(handle->name));
        handle->name[5] = (char)(((ixHandle >>6)  & 0x3f) + '0');
        handle->name[6] = (char)(((ixHandle    )  & 0x3f) + '0');
      #endif
      bool bAnyOtherHasAlreadyLocked = false;
      while(--tryCt > 0) {
        //composite the newValue with the changed ixHandle and the unchanged other bits:
        oldValue = thiz->handleBits | mSyncHandle_ObjectJc;
        newValue = (oldValue & ~mSyncHandle_ObjectJc) | ixHandle;  
        //cast from uint16* to int16*
        int16 currentValue = compareAndSwap_AtomicInt16((int16*)&thiz->handleBits, oldValue, newValue); 
        if(currentValue == oldValue){
          break;  //success, the current value was the old value as expected.
        }
        bAnyOtherHasAlreadyLocked = (currentValue & mSyncHandle_ObjectJc ) != mSyncHandle_ObjectJc;
        if(bAnyOtherHasAlreadyLocked) {
          break;                           // the value cannot be written because another thread has written.
        }
      }
      if(tryCt ==-1) {
        STACKTRC_ENTRY("getHandleAndLock_ObjectJc");
        THROW1_s0(RuntimeException, "error set idSyncHandle", 0);
        STACKTRC_LEAVE;
        return null;
      }
      if(bAnyOtherHasAlreadyLocked) {
        //Another thread has set the ixHandle already in this short time
        //this thread has also already locked the mutex, elsewhere the index was not gotten.
        releaseHandleEntry(ixHandle);                                // push back the current gotten handle.
        ixHandle = thiz->handleBits & mSyncHandle_ObjectJc;          //Take the current
        handle = getHandleEntry(ixHandle);  //the existing handle.
        // hence it waits here to lock.
      }
    }
  }
  else if(ixHandle >0) {
    handle = getHandleEntry(ixHandle);  //the existing handle.
  }
  return handle;
}







/**implements from ObjectJc.h. */
void wait_ObjectJc  (  ObjectJc* obj, int milliseconds, ThCxt* _thCxt)
{ //TODO test wether the thread has the monitor.
  // wait should only be called if lock is given, see Java.
  HandleItem* handle;
  STACKTRC_TENTRY("wait_ObjectJc");
  handle = getHandleExist_ObjectJc(obj);                   //the existing handle.
  if(handle == null) {                                     // the handle should be given because thiz should be locked.
    THROW1_s0(RuntimeException, "wait should be called under mutex", 0);
    return;
  }
  if(handle->handleWaitNotify.osHandleWaitNotify ==0) {
    createWaitNotifyObj_OSemC(handle->name, &handle->handleWaitNotify);
  }
  wait_OSemC(&handle->handleWaitNotify, &handle->handleMutex, milliseconds);
  STACKTRC_LEAVE;
}




void notify_ObjectJc  (  ObjectJc* obj, ThCxt* _thCxt)
{ //TODO it is possible that more as one thread waits, implement a list of threads.
  STACKTRC_TENTRY("notify_ObjectJc");
  uint16 handleObj = (obj->handleBits & mSyncHandle_ObjectJc);
  if(handleObj != kNoSyncHandles_ObjectJc) {
    HandleItem* handle = getHandleEntry(handleObj);
    notify_OSemC(&handle->handleWaitNotify, &handle->handleMutex);
  }
  STACKTRC_LEAVE;
}



void notifyAll_ObjectJc  (  ObjectJc* obj, ThCxt* _thCxt)
{ //TODO it is possible that more as one thread waits, implement a list of threads.
  STACKTRC_TENTRY("notifyAll_ObjectJc");
  uint16 handleObj = (obj->handleBits & mSyncHandle_ObjectJc);
  if(handleObj != kNoSyncHandles_ObjectJc)
  { HandleItem* handle = getHandleEntry(handleObj);
    notifyAll_OSemC(&handle->handleWaitNotify, &handle->handleMutex);
  }
  STACKTRC_LEAVE;
}











/**implements from ObjectJc.h. */
void synchronized  (  ObjectJc* obj)
{ HandleItem* handle;
  handle = getHandle_ObjectJc(obj);
  if(handle == null) {
    STACKTRC_ENTRY("synchronized");
    THROW1_s0(RuntimeException, "error get Handle", 0);
    STACKTRC_LEAVE;
    return;
  } else {
    createMutex_OSemC(&handle->handleMutex, handle->name);   // create only if not yet created.
    lockMutex_OSemC(&handle->handleMutex);                   // either lock as first or wait for lock here. 
  }
}








void synchronizedEnd  (  ObjectJc* obj)
{
  HandleItem* handle;
  STACKTRC_ENTRY("synchronizedEnd");
  handle = getHandleExist_ObjectJc(obj);
  if(handle == null) {
    THROW1_s0(RuntimeException, "synchronizedEnd, it is not synchronized",0);
    return;
  }
  unlockMutex_OSemC(&handle->handleMutex);
  //Now it is possible to give the handleData back to the handleItems resource
  // because it is no more used. ... todo later
  STACKTRC_LEAVE;
}








void sleep_Thread_Jc  (  int32 millisecond)
{ STACKTRC_ENTRY("sleep_Thread_Jc");
  os_delayThread(millisecond);
  STACKTRC_LEAVE;
}


#endif //DEF_ObjectJc_SYNCHANDLE
