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
 * @content: Handling on fatal error
 *
 * @author Hartmut Schorrig, Pinzberg, Germany, www.vishia.org
 *
 * @version 0.93
 * list of changes:
 * 2021-10-02: Hartmut creation/move from src/test/cpp/emC_TestAll/test_exitError.c
 *
 ****************************************************************************/
#include <applstdef_emC.h>
#include <stdio.h>
#include <stdlib.h>


/**Handling of a system error for an application which runs under an operation system.
 * It assumes that a console output is possible to gather and an error value can be handled
 * by the caller of the application.
 */
void errorSystem_emC_  (  int errorCode, const char* description, int value1, int value2, char const* file, int line) {
  printf("ERROR SYSTEM: %d %s %d, %d @%s:%d", errorCode, description, value1, value2, file, line);
  exit(255);
}



#ifndef DEF_NO_THCXT_STACKTRC_EXC_emC
/**Handling of an uncatched exception (CATCH block was not found).
 * Then the application should be aborted.
 * But before the exception is written on console with printf.
 * It assumes that a console output is possible to gather and an error value can be handled
 * by the caller of the application.
 */
void uncatched_Exception_emC  (  Exception_emC* thiz, ThreadContext_emC_s* _thCxt) {
#ifdef DEF_NO_StringUSAGE
  printf("ERROR uncatched Exception @%s:%d", thiz->file, thiz->line);
#else
  char buffer[300] = { 0 };
  writeException(buffer, sizeof(buffer), thiz, __FILE__, __LINE__, _thCxt);
  printf(buffer);
  ERROR_SYSTEM_emC(thiz->exceptionNr, "program abort", 0,0);
#endif
}
#endif
