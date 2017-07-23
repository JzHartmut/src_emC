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
 * 2009-05-17: JcHartmut creation from OsWrapper.c
 *
 ****************************************************************************/
#ifndef __Jc_OsWrapperJc_h__
#define __Jc_OsWrapperJc_h__

#include <Jc/ObjectJc.h>
#include <Fwc/fw_Exception.h>
#include <os_thread.h>
#include <os_time.h>
#include <os_sync.h>
#include <os_waitnotify.h>
#include <Fwc/fw_ThreadContext.h>

/**Version and History.
 * 2015-08-16 JcHartmut: There is a mistake while creating a new [[synchronized(...)]]:
 *  The new id for a ObjectJc::idSyncHandles was stored before the handleMutex was set in the referred struct.
 *  That is not a problem on a single core processor because there is no reason to swith the thread context in this time.
 *  But on multicore processing it is possible that a second core runs a thread similar and uses the new stored idSyncHandles
 *  while the handleMutex is not set yet. Then a Nullpointer is given for [[os_lockMutex(...)]] and it crashed.
 *  A fast workarround is: wait 1 ms if the handleMutex==null to give time to finish the creation in the other thread.
 *  Correct fix is: firstly finish the structure for idSyncHandles, then set it to Object::idSyncHandles with an atomic testAndSet.
 *  If it is set already (from another thread in the same time), delete the own created structure data and use the alredy set data instead.
 */
#define VERSION_OsWrapperJc 0x20150816

/**Because only a int16 value is used in Object_Jc for wait and threading, but some operation systems uses 32 bit-handles,
 * a translation of handle to index is necessary. This type stores several types of OS_Handle.
 */
typedef struct HandleItem_t
{ /**union of several handles, all are pointers. */
  union
  { struct OS_HandleWaitNotify_t const* wait;
    struct OS_HandleThread_t const* thread_xxx;
    /**If it is a free handle, the pointer to the next free. */
    struct HandleItem_t* nextFree;
  }handle;


  //struct OS_HandleMutex_t const* handleMutex;
  struct OS_Mutex_t* handleMutex;

  /**Name for the handle, derived from index. */
  char name[8];
} HandleItem;



typedef struct OsWrapperJc_t
{

  struct OS_Mutex_t* mutexInitHandle;

  /**This handle addresses the next free handles, all free handles are queued. */
  HandleItem* volatile freeHandle;

  /**Nr of handles, initial 0, th initFreeHandleEntry() routine should be called! */
  int32 nrofHandle;

  int32 spare_align8;

  /**A static array of handles to assing int16-indices to handles.
   * It is upgradable later to a intelligent management.
   * TODO: Blocks of about 32..128 HandleItem allocated, a block managment. It will be simple.
   */
  HandleItem handleItemsJc[1024];  // some kByte


  /**The value to designate a not free item. */
  #define kNoFreeHandleItem ((HandleItem*)(-1))


}OsWrapperJc_s;


extern OsWrapperJc_s data_OsWrapperJc;

#endif //__Jc_OsWrapperJc_h__
