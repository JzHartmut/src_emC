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
 * @content definition of user interface for exception handling
 * @author Jchartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 
 * 2017-01-21: Hartmut creation
 *
 ****************************************************************************/
#ifndef __applstdefJc_h__
  /**This file fw_Exception.h should be included in the applstdefJc.h. 
   * If this file is directly included, it needs the applstdefJc.h. But the __fw_Exception_h__ guard should not be set firstly
   * to include the fw_Exception.h in the given order in applstddef.h
   */
  #include <applstdefJc.h>
#endif

#ifndef __fw_ExcStacktrcNo_h__
#define __fw_ExcStacktrcNo_h__
#define __fw_Exception_h__       //prevent including
#define __fw_ThreadContext_h__   //prevent including

#define __NOT_SUPPORTED_ThreadContextFw__
#define __NOT_SUPPORTED_ExceptionJc__


#include <Fwc/fw_String.h>

/**The Exception data contains all data of exception but references to the stacktrace.
 *
 */
typedef struct ExceptionJc_t
{
  /**Bit mask of the exception. There are a maximum of 32 Exception types. Every Exception is represented by one bit.
     See enum definition of ExceptionMasksJc.
   */
  int32 exceptionNr;

  /**The user message of the exception.
   */
  StringJc exceptionMsg;

  /**The user value of the exception.
   */
  int32 exceptionValue;

}ExceptionJc;




#include <Fwc/fw_String.h>

#define ThCxt struct ThreadContextFW_t
#define STACKTRC_ENTRY(NAME) struct ThreadContextFW_t* _thCxt = null;
#define STACKTRC_TENTRY(NAME)
#define STACKTRC_LEAVE
#define CALLINE

#define THCXT null

#define TRY 
#define _TRY {
#define CATCH(EXCEPTION, EXC_OBJ) } { ExceptionJc* EXC_OBJ = null; if(false)
#define FINALLY
#define END_TRY }

#define THROW(EXCEPTION, TEXT, VAL)  throw_sJc_("##EXCEPTION##", TEXT, VAL, __LINE__)
#define THROW_s0(EXCEPTION, TEXT, VAL)  throw_s0Jc_("##EXCEPTION##", TEXT, VAL, __LINE__)
#define THROW_s(EXCEPTION, TEXT, VAL)  throw_sJc_("##EXCEPTION##", TEXT, VAL, __LINE__)

#define throw_s0Jc(EXCEPTION, TEXT, VAL, STACKTRC, LINE)  throw_s0Jc_("##EXCEPTION##", TEXT, VAL, LINE)
#define throw_sJc(EXCEPTION, TEXT, VAL, STACKTRC, LINE)  throw_sJc_("##EXCEPTION##", TEXT, VAL, LINE)

/**It's the same as in Java: Keyword assert, the condition should be true. */
METHOD_C void assertJc(bool condition);
#ifndef ASSERT
  /**The macro ASSERT may be defined user specific. */
  #define ASSERT(COND) assertJc(COND)
#endif



METHOD_C void throw_sJc_(char const* exceptionNr, StringJc msg, int value, int line);
METHOD_C void throw_s0Jc_(char const* exceptionNr, const char* msg, int value, int line);



#define printStackTrace_ExceptionJc(ythis, _thCxt)
#define printStackTraceFile_ExceptionJc(ythis, out, _thCxt)
#define getMessage_ExceptionJc(YTHIS, THC) ((YTHIS)->exceptionMsg)




#endif //__fw_ExcStacktrcNo_h__
