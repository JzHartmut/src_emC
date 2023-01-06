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
 * @content Implementation of System conventions, this file may be user specific.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg
 * @version sf-0.83
 * list of changes:
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#include <applstdef_emC.h>

#include <emC/OSAL/os_error.h>
#include <emC/OSAL/os_time.h>
#include <stdio.h>


/**Stops the execution of the executable respectively the whole application because no error handling is possible.
 * This routine should only called in unexpected situations, where the engine may only stopped.
 */
void os_FatalSysError(int errorCode, const char* description, int value1, int value2)
{
  printf("os_FatalSysError %d:", errorCode);
  printf(description, value1, value2);
  printf("\nstop system with memory exception\n");
  *((int*)0) = 0;
  
}


/**Stops the execution of a thread because no error handling is possible.
 * This routine should only called in unexpected situations, where the thread or the engine may only stopped only.
 * The distiction to ,,os_FatalSysError(...),, is: it is possible that only the thread is stopped,
 * where the other threads maybe continued still. It may be possible, that the system were instable. 
 *
 * The implementation of this routine should be done depending from the users requirements to the system
 * in the OSAL-Layer. 
 */
void os_FatalError(int errorCode, const char* description, int value1, int value2)
{
  int run = 1;
  int ct = 0;
  printf("os_FatalSysError %d:", errorCode);
  printf(description, value1, value2);
  printf("\nwhile-loop\n");
  while( run)
  { printf("ERROR STOP  since %d sec \n", ++ct);
    os_delayThread(1000);
  }
  
}


void uncatched_ExceptionJc(ExceptionJc* ythis, ThreadContext_emC_s* _thCxt)
{
  printf("uncatchedException: %8.8X - thread stopped", (uint)ythis->exceptionNr);
  os_FatalError(-1, "uncatchedException: - thread stopped", (uint)ythis->exceptionNr, 0);
}


