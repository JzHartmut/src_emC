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
 *   chg: createMutex_OSemC(...) with char const* name
 *   chg: createWaitNotifyObj_OSemC with char const* name
 * 2007-01-00: Hartmut creation
 *
 ************************************************************************************************/
#ifndef HGUARD_sync_OSemC
#define HGUARD_sync_OSemC
#include <applstdef_emC.h>
                             // OS-specific files must not included here!
#include <specific_OSemc.h>  //This is for OS-specific stuct definition, but commonly given elements

extern_C_BLOCK_

/**Version and History.
 * 2015-08-16 JcHartmut: The definition of Mutex_OSemC as pointer type is wrong, because it is not obvious what's that in C.
 *                       Therefore it is replaced by the struct Mutex_OSemC_T like usual for such. It is a reference (memory address) in any case.
 * 2006-00-00 JcHartmut created.
 */
static const int32 version_sync_OSemC = 0x20230105;




/**The type of a Mutex_OSemC is represented by a pointer to a not far defined struct which is defined OS-specific. */ 
struct Mutex_OSemC_T;
typedef struct Mutex_OSemC_T const* HandleMutex_OSemC;

#include <applstdef_emC.h>


/**The type of a HandleWaitNotify_OSemC is represented by a pointer to a not far defined struct which is defined OS-specific. */ 
typedef struct HandleWaitNotify_OSemC_T const* HandleWaitNotify_OSemC;



#ifndef  lockMutex_OSemC 
//Note: for simple processors without multithreading but with interrupt this identifier may define as macro in the compl_adaption.h or in the applstdef_emC.h
//Then it are not defined here.

/**Creates a mutex object.
 * @param name Name of the Mutex Object. In some operation systems this name should be unique. Please regard it, also in windows.
 * The mutex Object contains the necessary data for example a HANDLE etc.
 */
//struct Mutex_OSemC_T const* createMutex_OSemC(char const* name);
extern_C int createMutex_OSemC ( struct Mutex_OSemC_T* thiz, char const* name);
 
 
/**Deletes a mutex object.
 */
extern_C int deleteMutex_OSemC(struct Mutex_OSemC_T* thiz);
 

/**locks a mutex. 
 * The contract is: 
 * * If the same thread tries to lock a mutex, it is okay. 
 * * Another thread waits until the owner thread calls unlockMutex_OSemC(...).
 */
extern_C bool lockMutex_OSemC(struct Mutex_OSemC_T* thiz, int timeout_millisec);

/**Unlocks the mutex. It is possible that a thread switch occurs, 
 * if another thread waits and it has a higher priority. 
 * In some implementations it is possible that the thread is checked. 
 * The same thread which calls lockMutex_OSemC(...) should call unlockMutex_OSemC(...).
 * If another thread unlocks, it is an error and an exception may be thrown.
 */
extern_C bool unlockMutex_OSemC(struct Mutex_OSemC_T* thiz);
#endif










/**creates a object for wait-notify Object. The inner type of such an Object is os-dependent.
 * Here only a forward declared struct pointer is knwon.
 * @return 0 if no error, or an error code.
 */
METHOD_C int createWaitNotifyObj_OSemC(char const* name, HandleWaitNotify_OSemC* pWaitObject);


/**removes a object for wait-notify.
 */
METHOD_C int removeWaitNotifyObj_OSemC(HandleWaitNotify_OSemC waitObject);





/** Waits for a notification.
 */

METHOD_C int wait_OSemC(HandleWaitNotify_OSemC waitObject, struct Mutex_OSemC_T* hMutex, uint32 milliseconds);


/** Notifies all waiting thread to continue.
 * @return 0 if successfull notified,
             >0 if notified with warning (possible notified but nobody waits).
             <0 if an system error occurs. This should not occur in a tested system.
 */
METHOD_C int notifyAll_OSemC(HandleWaitNotify_OSemC waitObject, struct Mutex_OSemC_T* hMutex);


/** Notifies only one waiting thread to continue.
 */
METHOD_C int notify_OSemC(HandleWaitNotify_OSemC waitObject, struct Mutex_OSemC_T* hMutex);


_END_extern_C_BLOCK


#endif  // HGUARD_sync_OSemC
