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
  /**This file fw_Exception.h should be included in the applstdef_emC.h. 
   * If this file is directly included, it needs the applstdef_emC.h. But the __fw_Exception_h__ guard should not be set firstly
   * to include the fw_Exception.h in the given order in applstddef.h
   */
  #include <applstdef_emC.h>
#endif


#include <emC/ExceptionDefs_emC.h>  //the constants for exception should be known.

#ifndef __fw_ExcStacktrcNo_h__
#define __fw_ExcStacktrcNo_h__
#define __fw_Exception_h__       //prevent including
//#define __fw_ThreadContext_h__   //prevent including

//#define __NOT_SUPPORTED_ThreadContext_emC__
#define __NOT_SUPPORTED_ExceptionJc__

#ifndef __StringJc_defined__
  //minimalistic definition of StringJc to use this type before including emC/StringJc
  typedef OS_PtrVal_DEF(StringJc, void const);
  #define __StringJc_defined__
#endif //ifdef isNull_StringJc

#include <emC/ExceptionDefs_emC.h>

//#include <emC/String.h>




#define ThCxt struct ThreadContext_emC_t
/**Because the operation may use a pointer variable named _thCxt it is defined here.
 * But it is initialized with null, because a ThreadContext is unknown, and it is a unknown forward type.
 */
#define STACKTRC_ENTRY(NAME) struct ThreadContext_emC_t* _thCxt = null;

/**For that the _thCxt variable is given in arguments of the operation */
#define STACKTRC_TENTRY(NAME)
#define STACKTRC_LEAVE
#define CALLINE

#define THCXT null

#define TRY 
#define _TRY {
/**The catch-code is never executed. With if(false) the compiler may/should optimize it. 
 */
#define CATCH(EXCEPTION, EXC_OBJ) } { ExceptionJc* EXC_OBJ = null; if(false)
#define FINALLY
#define END_TRY }

/**All THROW() macros force a return. Therewith the behavior of the operation is adequate to Exception handling.
 * But the calling routine is continued. It should check itself for sufficient conditions to work.
 */
#define THROW(EXCEPTION, STRING, VAL, ...)   { ExceptionJc exc = CONST_ExceptionJc(EXCEPTION, STRING, VAL); log_ExceptionJc(&exc, __FILE__, __LINE__); }
#define THROW_s0(EXCEPTION, TEXT, VAL, ...)  { ExceptionJc exc = CONST_ExceptionJc(EXCEPTION, CONST_z_StringJc(TEXT), VAL); log_ExceptionJc(&exc, __FILE__, __LINE__); }
#define THROW_s(EXCEPTION, STRING, VAL, ...) logException_emC(ident_##EXCEPTION##Jc, STRING, VAL, __FILE__, __LINE__) //; return __VA_ARGS__


/**The routines throw... are replaced by a routine which does not know the exception bit mask
 * but supplies a String with the exception name, proper for printf.
 */
#define throw_s0Jc(EXCEPTION, TEXT, VAL, STACKTRC, LINE)  throw_sJc_("##EXCEPTION##", z_StringJc(TEXT), VAL, LINE)
#define throw_sJc(EXCEPTION, TEXT, VAL, STACKTRC, LINE)  throw_sJc_("##EXCEPTION##", TEXT, VAL, LINE)
#define throw_EJc(EXCEPTION, EXCOBJ, VAL, STACKTRC, LINE)  throw_s0Jc_("##EXCEPTION##", "forward exception", VAL, LINE)




#define printStackTrace_ExceptionJc(ythis, _thCxt)
#define printStackTrace_P_ExceptionJc(ythis, out, _thCxt)
#define printStackTraceFile_ExceptionJc(ythis, out, _thCxt)
#define getMessage_ExceptionJc(YTHIS, THC) ((YTHIS)->exceptionMsg)




#endif //__fw_ExcStacktrcNo_h__
