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
 * @content This file contains the implementation of error handling for the OSAL-wrapper.
 *          The error handling depends on the realities of the given system and its environment.
 *          Therefore an adaption for several platforms may be necessary here.
 
 * @author Hartmut Schorrig www.vishia.org
 * @version 0.94
 * list of changes:
 * 2011-01-07 Hartmut chg: Written in an extra file, before them, it was stored in os_thread.c
 * 2010-01-15 Hartmut corr: errorhandling should be improved! Usage of  printf in a file? It was resolved already. Depends on system.
 * 2007-10-01: Hartmut creation (concept)
 *
 ****************************************************************************/

#include <os_error.h>
#undef boolean
//#include <wtypes.h>
//#include <winbase.h>
#include <stdio.h>

MT_os_Error* users_os_Error = null;

int os_setErrorRoutine(MT_os_Error* routine)
{
  users_os_Error = routine;
  return 0;
}



void os_notifyError_FileLine(int errorCode, const char* description, int value1, int value2, char const* file, int line)
{ if(users_os_Error != null)
  { //call the users routine:
    users_os_Error(errorCode, description, value1, value2);
  }
  else
  { //If no user routine is known, the error should be detect by the return code of the os-routines.
    if(description == null){
      description = "";
    }
    printf("Error %d: %s, %d, %d in file %s: %d", errorCode, description, value1, value2, file, line);
  }  
}

/*
void os_Error(const char* text, int value)
{ printf("\nFATAL SYSTEM ERROR %s: %i=%8.8X\nTHREAD STOPPED\n", text, value, value);
  *(int*)0 = 0;
}
*/
void os_userError(const char* text, int value)
{ printf("\nUSER SYSTEM ERROR %s: %i=%8.8X\nTHREAD STOPPED\n", text, value, value);
}



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
