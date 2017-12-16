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
 */
#ifndef __FormatterJc_h__
#define __FormatterJc_h__

#include <Jc/ObjectJc.h>
#include <Fwc/fw_String.h>
#include "Fwc/fw_Va_list.h" 

#include <Jc/LocaleJc.h>

#ifndef StringBuilderJcREFDEF
  //It is only a forward-declare-able reference, don't include the Jc/StringJc.h
  #define StringBuilderJcREFDEF
  typedef TYPE_EnhancedRefJc(StringBuilderJc);
#endif


/*@CLASS_C FormatterJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This class .
 */
typedef struct FormatterJc_t
{ union{ObjectJc object; };
  
  StringBuilderJcREF buffer;

  LocaleJcREF locale;

}FormatterJc_s;

extern_C ClassJc const reflection_FormatterJc_s;


METHOD_C FormatterJc_s* ctorO_Sb_FormatterJc(ObjectJc* othis, struct StringBuilderJc_t* buffer, struct ThreadContextFW_t* _thCxt);

METHOD_C FormatterJc_s* ctorO_SbLo_FormatterJc(ObjectJc* othis, struct StringBuilderJc_t* buffer, struct LocaleJc_t* locale, struct ThreadContextFW_t* _thCxt);

/**Formats with a given variable argument list. */
METHOD_C void format_FormatterJc(FormatterJc_s* ythis, StringJc text, Va_listFW args, struct ThreadContextFW_t* _thCxt);

/**Formats with variable arguments. */
METHOD_C void format_a_FormatterJc(FormatterJc_s* ythis, StringJc text, char const* typeArgs, ...);

/**Formats with variable arguments. */
METHOD_C void close_FormatterJc(FormatterJc_s* ythis, struct ThreadContextFW_t* _thCxt);


#endif  //__FormatterJc_h__
