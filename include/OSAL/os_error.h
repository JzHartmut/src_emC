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
 * @maintainer: Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content Definition of error numbers. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * list of changes:
 * 2010-02-26 Hartmut new: os_NotifyError is defined here, because it is able to use from user too.
 * 2009-11-25 Hartmut Schorrig
 *   corr: Weitere Fehlercodes
 *   new: Socket-Fehlercodes: Hier sollten nicht alle betriebssystemspezifischen Codes auf allgemeine umgesetzt werden, 
 *     sondern nur die allgemeingültigen. Alle anderen Fehlercodes als Sub-code nicht umgesetzt melden,
 *     die Software sollte direkt darauf nicht reagieren. Das ganze ist noch nicht richtig durchdesignet.
 *   new: Fehlermeldung mit Routinen ähnlich wie es in der Hynet-OS-Schale getan wird, aber hier über Funktionspointer,
 *     dazu gibt es:
 *   new: os_setErrorRoutine(..) (zuvor in os_thread.c vordefiniert)
 *   new: Routine, um aus Anwendersicht dem OS einen fatalen error zu melden:
 *     os_FatalError(...) 
 * 2008-02-01: Hartmut creation 
 *
 ************************************************************************************************/

#ifndef __os_error_h__
#define __os_error_h__

#include <os_types_def.h>

//Funktion-Fehlercode
#define OS_OK                  0
#define OS_SYSTEM_ERROR      -100	// System Fehler.
#define OS_INVALID_PARAMETER -101	// Ein Parameter war ungültig.
#define OS_INVALID_STRING	   -102	// Ein String ist nicht innerhalb der vorgegebenen Größe.
#define OS_INVALID_HANDLE    -103	// Das Objekt-Handle ist ungültig.
//#define OS_INVALID_STATE     -104	// Der Objekt-Sustand ist ungültig für diese Operation.
//#define OS_TEST_NOT_OK       -105	// Testbedingungen nicht erfüllt.
#define OS_GOT_TIMEOUT       -106	// Der Aufruf wurde nach dem eingestellten Timeout abgebrochen.
//#define OS_QUEUE_EXIST       -107	// Die Message-Queue existiert bereits für diesen Thread.
//#define OS_QUEUE_NOT_EXIST   -108	// Die Message-Queue dieses Thread existiert nicht.
#define OS_RESOURCE_BUSY     -109	// In diesem Objekt stehen noch Nachrichten, oder ein Thread wartet.
//#define OS_QUEUE_FULL        -110	// Die Message–Queue ist voll.
//#define OS_QUEUE_EMPTY       -111	// Die Message-Queue enthält keine Nachricht
//#define OS_NAME_EXIST        -112	// Der Name existiert bereits.
#define OS_NAME_NOT_EXIST    -113	// Der angegebene Name existiert im System nicht.
//#define OS_MAILBOX_FULL      -114	// Die Anforderung überschreitet die eingetragene Grenze der Mailbox.
//#define OS_MAILBOX_EMPTY     -115	// Die Mailbox enthält keine Nachricht (wenn timeOut = 0).
#define OS_INVALID_POINTER   -116	// Zeiger zu Resource ungültig.
#define OS_UNEXPECTED_CALL   -117	// Aufruf an dieser Stelle nicht erwartet/statthaft.
#define OSAL_Wait_FaultMutex -120	
#define OSAL_TEXT_Wait_FaultMutex "Fault mutex while calling os_wait."	
#define OS_UNKNOWN_ERROR     -200	// Undefinierte Fehlermeldung
#define OS_TEXT_UNKNOWN_ERROR     "error from operation system"
#define OS_NOT_IMPLEMENTED   -201	
#define OS_TEXT_NOT_IMPLEMENTED   "This function is not implemented yet."	
#define OSAL_NoMemory        -202	
#define OSAL_TEXT_NoMemory        "No memory."	
#define OSAL_FaultMemoryPtr   -203	
#define OSAL_TEXT_FaultMemoryPtr  "Fault memory pointer."	

#define OS_SOCKETERROR       -280
#define OS_TEXT_SOCKETERROR       "Any unexpected socket error, param1=os-specific error-code, param1=socket-id"

/**All Warnings can be ignored by user. They mustn't be used in software algorithm.
 * In debug situations it is possible to evaluate it.
 */
typedef enum OS_ReturnCodes_t
{ OS_WARNING_NOTIFY_TooManyPosts =     10001
, OS_WARNING_NOTIFY_NothingIsWaiting = 10002
}OS_ReturnCodes;  


/**Type of routine to present non-fatal or fatal errors in a deep system level. 
 * * The users calling point of this routine isn't able to provide immediately here, 
 * because this routine is called in a system routine. The text-parameter here should be shown
 * which system routine it is, in conclusion with the error description. 
 */
typedef void MT_os_Error(int errorCode, const char* description, int value1, int value2);


/**Sets a routine, which is called if the OSAL layer or maybe the RTOS itself detects an error of any call,
 * which may be able to catch. At example the user may note the error in a list for debugging,
 * or an exception is thrown to catch the error at user level. This routine should only call on startup of the system.
 * NOTE: An wrapper to call this routine in the OSAL-layer is defined in the OSAL's internal Header ,,os_internal_common.h,,.
 */
METHOD_C int os_setErrorRoutine(MT_os_Error* routine);


/**This routine will be called in error situations of the OSAL-Adaption and maybe in the RTOS immediately. 
 * The routine will be redirected to the user-defined routine given with ,,os_setErrorRoutine(...),,
 * If the routine is set. If no, this routine does nothing. It means, it is not the only way of error detection.
 * The other way is to test the return code of os_methods.
 */
void os_notifyError(int errorCode, const char* description, int value1, int value2);



/**Stops the execution of the executable respectively the whole application because no error handling is possible.
 * This routine should only called in unexpected situations, where the engine may only be stopped.
 *
 * This routine is used in the OSAL- or OS-Layer itself only for errors, which are fatal and not expectable.
 * This routine should be used from the users layer in adequate fatal situations.
 * The OSAL or OS doesn't call this routine in situations of errors which are able to catch.
 * 
 * The implementation of this routine should be done depending from the users requirements or special test requirements
 * to the whole system. It should be hard coded and really stop the execution.
 */
METHOD_C void os_FatalSysError(int errorCode, const char* description, int value1, int value2);


/**Stops the execution of a thread because no error handling is possible.
 * This routine should only called in unexpected situations, where the thread may only be stopped..
 * The distiction to ,,os_FatalSysError(...),, is: Only the calling thread is stopped,
 * where the other threads maybe continued still. It may be possible, that the system were instable,
 * but other threads may able to use to debug this situation. The application may be wrong.. 
 *
 * This routine is used in the OSAL- or OS-Layer itself only for errors, which are fatal and not expectable.
 * This routine should be used from the users layer in adequate fatal situations.
 * The OSAL or OS doesn't call this routine in situations of errors which are able to catch.
 * 
 * The implementation of this routine should be done depending from the users requirements or special test requirements
 * to the whole system. It should be hard coded and really stop the execution.
 */
METHOD_C void os_FatalError(int errorCode, const char* description, int value1, int value2);



#endif // __os_error_h__
