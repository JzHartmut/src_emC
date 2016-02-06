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


#include "OsWrapperJc.h"

#include <Jc/ObjectJc.h>
#include <Fwc/fw_Exception.h>
#include <os_thread.h>
#include <os_time.h>
#include <os_sync.h>
#include <os_waitnotify.h>
#include <Fwc/fw_ThreadContext.h>

#include <string.h>

OsWrapperJc_s data_OsWrapperJc = { 0 };


/**This routine is called only onetime after startup. */
int initFreeHandleEntry()
{ int zHandleItems = ARRAYLEN(data_OsWrapperJc.handleItemsJc);
  int ii;
  data_OsWrapperJc.handleItemsJc[0].handle.nextFree = kNoFreeHandleItem;  //let the first unused, no using of index 0!
  data_OsWrapperJc.freeHandle.handle.nextFree = &data_OsWrapperJc.handleItemsJc[1];
  for(ii = 1; ii < zHandleItems -1; ii++)
  { data_OsWrapperJc.handleItemsJc[ii].handle.nextFree = &(data_OsWrapperJc.handleItemsJc[ii+1]);
  }
  data_OsWrapperJc.handleItemsJc[ii].handle.nextFree = kNoFreeHandleItem;  //the last one.
  return zHandleItems;
}






/**gets a free handle.
 * @param idx the returned index.
 */
HandleItem* getFreeHandleEntry(int16* idx)
{ //this operation have to be executed under mutex:
  HandleItem* theHandleItem;
  if(data_OsWrapperJc.nrofHandle == 0)
  { data_OsWrapperJc.nrofHandle = initFreeHandleEntry();
  }
  theHandleItem = data_OsWrapperJc.freeHandle.handle.nextFree;
  if(theHandleItem == kNoFreeHandleItem)
  { *idx = -1;  //TODO passenden Win-error
    return null;
  }
  else
  { HandleItem* nextFree = theHandleItem->handle.nextFree;  //it may be null if there is no more handle.
    data_OsWrapperJc.freeHandle.handle.nextFree = nextFree;
    //here mutex release!
    { int idxHandle = theHandleItem - data_OsWrapperJc.handleItemsJc;
      if(idxHandle < 0 || idxHandle >= ARRAYLEN(data_OsWrapperJc.handleItemsJc))
      { STACKTRC_ENTRY("getFreeHandleEntry");
        THROW_s0(RuntimeException, "corrupt handles",idxHandle);
      }
      *idx = (int16)(idxHandle);
    }
    memset(theHandleItem, 0, sizeof(*theHandleItem));
    return theHandleItem;
  }
}


/**gets the handle to the index.
 */
HandleItem* getHandleEntry(int idx)
{ if(idx < 0 || idx > ARRAYLEN(data_OsWrapperJc.handleItemsJc))
  { STACKTRC_ENTRY("getHandleEntry");
    THROW_s0(RuntimeException, "error fault idx for handle", idx);
  }
  return &data_OsWrapperJc.handleItemsJc[idx];
}


/**************************************************************************************************/
/* Implementations of ObjectJc.h
*/


/**implements from ObjectJc.h. */
void wait_ObjectJc(ObjectJc* obj, int milliseconds, ThCxt* _thCxt)
{ //TODO test wether the thread has the monitor.
  HandleItem* handle;
  STACKTRC_TENTRY("wait_ObjectJc");
  if(obj->idSyncHandles == kNoSyncHandles_ObjectJc)
  { handle = getFreeHandleEntry(&obj->idSyncHandles);
  }
  else
  { handle = getHandleEntry(obj->idSyncHandles);
  }
  if(handle->handle.wait == null)
  { int error = os_createWaitNotifyObject("unknown", &handle->handle.wait);
    if(error != 0)
    { //it may be throwable
      THROW_s0(RuntimeException, "error os_createWaitNotifyObject", error);
    }
  }
  if(handle->handleMutex == null)
  { int error = os_createMutex(null, &handle->handleMutex);
    if(error != 0)
    { //it may be throwable
      THROW_s0(RuntimeException, "error os_createMutex", error);
    }
  }
  os_wait(handle->handle.wait, handle->handleMutex, milliseconds);
  STACKTRC_LEAVE;
}




void notify_ObjectJc(ObjectJc* obj, ThCxt* _thCxt)
{ //TODO it is possible that more as one thread waits, implement a list of threads.
  STACKTRC_TENTRY("notify_ObjectJc");
  if(obj->idSyncHandles != kNoSyncHandles_ObjectJc)
  { HandleItem* handle = getHandleEntry(obj->idSyncHandles);
    if(handle->handle.wait != null && handle->handleMutex != null)
    {
      os_notify(handle->handle.wait, handle->handleMutex);
    }
  }
  STACKTRC_LEAVE;
}



void notifyAll_ObjectJc(ObjectJc* obj, ThCxt* _thCxt)
{ //TODO it is possible that more as one thread waits, implement a list of threads.
  STACKTRC_TENTRY("notifyAll_ObjectJc");
  if(obj->idSyncHandles != kNoSyncHandles_ObjectJc)
  { HandleItem* handle = getHandleEntry(obj->idSyncHandles);
    if(handle->handle.wait != null && handle->handleMutex != null)
    {
      os_notify(handle->handle.wait, handle->handleMutex);
    }
  }
  STACKTRC_LEAVE;
}











/**implements from ObjectJc.h. */
void synchronized(ObjectJc* obj)
{ //TODO test wether the thread has the monitor.
  HandleItem* handle;
  if(obj->idSyncHandles == kNoSyncHandles_ObjectJc)
  { handle = getFreeHandleEntry(&obj->idSyncHandles);
    if (handle !=null)
    { char name[9];
      int error;
      strcpy(name, "JcW__000");
      name[5] = (char)((obj->idSyncHandles >>12 & 0x3f) + '0');
      name[6] = (char)((obj->idSyncHandles >>6  & 0x3f) + '0');
      name[7] = (char)((obj->idSyncHandles      & 0x3f) + '0');
      error = os_createMutex(name, &handle->handleMutex);
      if(error != 0)
      { //it may be throwable
        STACKTRC_ENTRY("synchronized_ObjectJc");
        THROW_s0(RuntimeException, "error os_createMutex", error);
      }
    }
    else {
      //no handles available 
    }
  }
  else
  { handle = getHandleEntry(obj->idSyncHandles);
    //its possible that another thread has written the idSyncHandles just now
    //but the handleMutex is not set yet.
    //the wait a short time:
    if(handle->handleMutex == null){
      os_delayThread(1);
    }
  }
  if (handle != null){
    os_lockMutex(handle->handleMutex);
  }
  else {
    //TODO no handles found, yet: without mutex
  }
}








void synchronizedEnd(ObjectJc* obj)
{
  STACKTRC_ENTRY("synchronizedEnd");
  //if(obj == &allThreads_Rtos.object)
  {
  }
  //else
  {
    if(obj->idSyncHandles != kNoSyncHandles_ObjectJc)
    { HandleItem* handleItem = getHandleEntry(obj->idSyncHandles);
      os_unlockMutex(handleItem->handleMutex);
    }
  }
  STACKTRC_LEAVE;
}








void sleep_Thread_Jc(int32 millisecond)
{ STACKTRC_ENTRY("sleep_Thread_Jc");
  os_delayThread(millisecond);
  STACKTRC_LEAVE;
}
