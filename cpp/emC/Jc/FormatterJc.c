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
#include <emC/Jc/FormatterJc.h>

#ifndef DEF_NO_StringUSAGE

#include <emC/Base/Formatter_emC.h>
#include <emC/Jc/ReflectionJc.h>
#include <emC/Jc/StringBufferJc.h>
#include <emC/Base/Va_list_emC.h> 


extern_C ClassJc const refl_FormatterJc;
extern_C ClassJc const refl_StringBufferJc;

FormatterJc_s* ctorO_Sb_FormatterJc(ObjectJc* othis, struct StringBuilderJc_t* buffer, struct ThreadContext_emC_t* _thCxt)
{
  FormatterJc_s* ythis = (FormatterJc_s*)othis;
  STACKTRC_TENTRY("ctorO_Sb_FormatterJc");
  CHECKstrict_ObjectJc(othis, sizeof(FormatterJc_s), refl_FormatterJc, 0); 
  SETREFJc(ythis->buffer, buffer, StringBufferJc_s);
  STACKTRC_LEAVE; return ythis;
}

FormatterJc_s* ctorO_SbLo_FormatterJc(ObjectJc* othis, struct StringBuilderJc_t* buffer, struct LocaleJc_t* locale, struct ThreadContext_emC_t* _thCxt)
{
  FormatterJc_s* ythis = (FormatterJc_s*)othis;
  STACKTRC_TENTRY("ctorO_Sb_FormatterJc");
  CHECKstrict_ObjectJc(othis, sizeof(FormatterJc_s), refl_FormatterJc, 0); 
  SETREFJc(ythis->buffer, buffer, StringBufferJc_s);
  SETREFJc(ythis->locale, locale, LocaleJc);

  STACKTRC_LEAVE; return ythis;
}


void format_FormatterJc(FormatterJc_s* ythis, StringJc text, Va_listFW args, struct ThreadContext_emC_t* _thCxt)
{
  int sizeBuffer;
  int posBuffer;
  char* buffer;  //NOTE: The internal buffer of ythis->buffer will be used to change.
  int lenText;
  char const* sText;
  int nrofCharsFormat;
  StringBufferJc* sBuffer = REFJc(ythis->buffer);
  STACKTRC_TENTRY("ctorO_Sb_FormatterJc");
  buffer = getCharsSizeCount_StringBuilderJc(sBuffer, &sizeBuffer, &posBuffer);
  sText = getCharsAndLength_StringJc(&text, &lenText);
  nrofCharsFormat = format_va_arg_Formatter_FW(_thCxt, sText, lenText, buffer + posBuffer, sizeBuffer - posBuffer, args);
  _setCount_StringBuilderJc(sBuffer, posBuffer+ nrofCharsFormat);
  STACKTRC_LEAVE; 
}


void format_a_FormatterJc(FormatterJc_s* ythis, StringJc text, char const* typeArgs, ...)
{ va_list args;
  Va_listFW typedArgs;
  STACKTRC_ENTRY("sendMsg_iSzv_LogMessageFW");
  va_start(args, typeArgs);
  typedArgs.typeArgs = typeArgs;
  typedArgs.args = args;
  format_FormatterJc(ythis, text, typedArgs, THCXT);
  STACKTRC_LEAVE;
}


void close_FormatterJc(FormatterJc_s* ythis, struct ThreadContext_emC_t* _thCxt)
{
}


#ifdef DEF_REFLECTION_FULL
  #include "emC/Jc/genRefl/FormatterJc.crefl" 
#else
  #define ID_refl_FormatterJc 0x0FD0
  ClassJc const refl_FormatterJc = INIZ_ClassJc(refl_FormatterJc, "FormatterJc");


#endif

#endif //DEF_NO_StringUSAGE
