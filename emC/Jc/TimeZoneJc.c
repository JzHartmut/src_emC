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
 * @content adequate content of java/util/Locale.java
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.892
 */
#include "emC/Jc/TimeZoneJc.h"

#include <emC/Base/StringBase_emC.h>

const TimeZoneJc_s GMT_TimeZoneJc = CONST_TimeZoneJc( &GMT_TimeZoneJc, CONST_StringJc("GMT",3), 0, 0, false);
const TimeZoneJc_s MST_TimeZoneJc = CONST_TimeZoneJc( &MST_TimeZoneJc, CONST_StringJc("MST",3), 1, 0, true);


TimeZoneJc_s* getTimeZone_TimeZoneJc(StringJc name, ThCxt* _thCxt)
{
  if(equals_z_StringJc(name, "GMT")) return (TimeZoneJc_s*)&GMT_TimeZoneJc;
  else return (TimeZoneJc_s*)&GMT_TimeZoneJc;
}


#ifdef DEF_REFLECTION_FULL
  #include <emC/Jc/genRefl/TimeZoneJc.crefl>
#else
  ClassJc const refl_TimeZoneJc = INIZ_ClassJc(refl_TimeZoneJc, "TimeZoneJc");

#endif
