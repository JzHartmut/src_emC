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
 * @content java-like java/util/TimeZone.
 *
 * @author Hartmut Schorrig
 * @version 0.92
 * list of changes:
 * 2010-08-18: Hartmut creation
 *
 ****************************************************************************/
#ifndef __TimeZoneJc_h__
#define __TimeZoneJc_h__

//#include <emC/Base/ExceptionJc.h>
#include <emC/Jc/ObjectJc.h>

/*@CLASS_C TimeZoneJc @@@@@@@@@@@@@@@@@@@@@@@@*/

/**This struct represents an interface adequat to ,,java.lang.Runnable,,. 
 * It contains only a struct ObjectJc, it is to use in a ,,union{...},, commonly with the ,,ObjectJc,,-base of any struct.
 */
typedef struct TimeZoneJc_t
{ 
  union { ObjectJc object; } base; 
  int16 diffHours;
  int16 diffMinutes;
  StringJc name;
} TimeZoneJc_s;

#ifndef DEF_REFLECTION_NO
  extern_C const struct ClassJc_t refl_TimeZoneJc;
#endif
#ifndef ID_refl_TimeZoneJc 
  #define ID_refl_TimeZoneJc 0x0f00
#endif


/* Enhanced references *********************************************************/
#ifndef TimeZoneJcREFDEF
  #define TimeZoneJcREFDEF
  typedef TYPE_EnhancedRefJc(TimeZoneJc);
  //Should be compatible with non-enhanced ref using. typedef struct TimeZoneJcREF_t { ObjectRefValuesJc refbase; struct TimeZoneJc_t* ref; } TimeZoneJcREF;
#endif



#define INIZ_TimeZoneJc(OBJ, name, diffHour, diffMinute, bDayligthSaving) { { INIZ_ObjectJc(OBJ, refl_TimeZoneJc, sizeof(TimeZoneJc_s)) }, diffHour, diffMinute, name}


METHOD_C TimeZoneJc_s* getTimeZone_TimeZoneJc(StringJc name, ThCxt* _thCxt);


#endif  //__TimeZoneJc_h__
