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
 * @content Declaration of mutex routines.
 * The implementation is os-specific. A mutex should regard a second call from the same thread.
 * It is more complex as a simple semaphore request. 
 * Some operation systems supports this request immediately. 
 * If a opeation system does know only the semaphore mechanism, the thread identification
 *   should be stored in a mutex structure.
 *
 * @author Hartmut Schorrig
 * @version sf-0.93
 * list of changes:
 * 2009-11-25 Hartmut:
 *   chg: os_createMutex(...) with char const* name
 *   chg: os_createWaitNotifyObject with char const* name
 * 2007-01-00: Hartmut creation
 *
 ************************************************************************************************/
#ifndef __os_sync_h__
#define __os_sync_h__
#include <os_types_def.h>

extern_C_BLOCK_

/**The type of a OS_Mutex is represented by a pointer to a not far defined struct which is defined OS-specific. */ 
typedef struct OS_Mutex_t const* OS_Mutex;


#include <os_types_def.h>
//#include "fw_MemC.h"


/**The type of a OS_HandleWaitNotify is represented by a pointer to a not far defined struct which is defined OS-specific. */ 
typedef struct OS_HandleWaitNotify_t const* OS_HandleWaitNotify;



/**Creates a mutex object.
 * @param name Name of the Mutex Object. In some operation systems this name should be unique. Please regard it, also in windows.
 * The mutex Object contains the necessary data for example a HANDLE etc.
 */
int os_createMutex(char const* name, OS_Mutex* pMutexID);
 
 
/**Deletes a mutex object.
 */
int os_deleteMutex(OS_Mutex mutexID);
 
 
/**locks a mutex. 
 * The contract is: 
 * * If the same thread tries to lock a mutex, it is okay. 
 * * Another thread waits until the owner thread calls os_unlockMutex(...).
 */
int os_lockMutex(OS_Mutex mutexID);


/**Unlocks the mutex. It is possible that a thread switch occurs, 
 * if another thread waits and it has a higher priority. 
 * In some implementations it is possible that the thread is checked. 
 * The same thread which calls os_lockMutex(...) should call os_unlockMutex(...).
 * If another thread unlocks, it is an error and an exception may be thrown.
 */
int os_unlockMutex(OS_Mutex mutexID);










/**creates a object for wait-notify Object. The inner type of such an Object is os-dependent.
 * Here only a forward declared struct pointer is knwon.
 * @return 0 if no error, or an error code.
 */
METHOD_C int os_createWaitNotifyObject(char const* name, OS_HandleWaitNotify* pWaitObject);


/**removes a object for wait-notify.
 */
METHOD_C int os_removeWaitNotifyObject(OS_HandleWaitNotify waitObject);





/** Waits for a notification.
 */

METHOD_C int os_wait(OS_HandleWaitNotify waitObject, OS_Mutex hMutex, uint32 milliseconds);


/** Notifies all waiting thread to continue.
 * @return 0 if successfull notified,
             >0 if notified with warning (possible notified but nobody waits).
             <0 if an system error occurs. This should not occur in a tested system.
 */
METHOD_C int os_notifyAll(OS_HandleWaitNotify waitObject, OS_Mutex hMutex);


/** Notifies only one waiting thread to continue.
 */
METHOD_C int os_notify(OS_HandleWaitNotify waitObject, OS_Mutex hMutex);


_END_extern_C_BLOCK


#endif  // __os_sync_h__
