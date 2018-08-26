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
 * list of changes:
 * 2006-05-00: JcHartmut creation
 *
 ****************************************************************************/
#include "Jc/DateJc.h"
//#include "Jc/StringBuilderJc.h"

#include <Jc/TimeZoneJc.h>
#include <string.h>
#include "os_time.h"
#include <emC/Timeconversions_emC.h>

extern_C struct ClassJc_t const reflection_DateJc_s;

METHOD_C void normalize_DateJc(DateJc_s* ythis)
{ if( ythis->val.time_nsec > 999999999L)
  { int seconds = ythis->val.time_nsec/1000000000L;
    ythis->val.time_sec += seconds;
    ythis->val.time_nsec -= 1000000000 * seconds;
  }
  else if( ythis->val.time_nsec < 0)
  { int seconds = ythis->val.time_nsec/1000000000L;
    ythis->val.time_sec -= seconds;
    ythis->val.time_nsec += 1000000000 * seconds;
  }
}


METHOD_C int compareTo_DateJc(DateJc_s* ythis, DateJc_s* when)
{
  normalize_DateJc(ythis);
  normalize_DateJc(when);
  if(ythis->val.time_sec > when->val.time_sec) return 1;
  else if(ythis->val.time_sec < when->val.time_sec) return -1;
  else
  {
    if(ythis->val.time_nsec > when->val.time_nsec) return 1;
    else if(ythis->val.time_nsec < when->val.time_nsec) return -1;
    else return 0;
  }
}



/**Constructs an instance with given time.*/
METHOD_C DateJc_s* ctor_i_DateJc(DateJc_s* ythis, int64 time)
{ init0p_MemC(ythis, sizeof(DateJc_s));
  ctorc_ObjectJc(&ythis->base.object);
  ythis->val.time_sec = (int32)(time/1000);
  ythis->val.time_nsec = (int32)(time - 1000 * ythis->val.time_sec);
  return ythis;
}

/**Constructs an instance with the system time.*/
METHOD_C DateJc_s* ctor_DateJc(DateJc_s* ythis)
{ init0p_MemC(ythis, sizeof(DateJc_s));
  ctorc_ObjectJc(&ythis->base.object);
  setSystemTime_DateJc(ythis);
  return ythis;
}


/**Constructs an instance with the system time.*/
DateJc_s* ctorO_DateJc(ObjectJc* othis, ThCxt* _thCxt)
{ DateJc_s* ythis = (DateJc_s*)othis;
  checkConsistence_ObjectJc(othis, sizeof(DateJc_s), &reflection_DateJc_s, _thCxt);  
  ctorc_ObjectJc(&ythis->base.object);
  init0p_MemC(othis+1, sizeof(DateJc_s) - sizeof(ObjectJc));
  setSystemTime_DateJc(ythis);
  return ythis;
}


DateJc_s* ctorO_I_DateJc(ObjectJc* othis, int64 milliSecAfter1970, ThCxt* _thCxt)
{ DateJc_s* ythis = (DateJc_s*)othis;
  int32 seconds;
  int32 milliseconds;
  STACKTRC_TENTRY("ctorO_I_DateJc");
  checkConsistence_ObjectJc(othis, sizeof(DateJc_s), &reflection_DateJc_s, _thCxt);  
  ctorc_ObjectJc(&ythis->base.object);
  init0p_MemC(othis+1, sizeof(DateJc_s) - sizeof(ObjectJc));
  seconds = (int32) milliSecAfter1970 / 1000;
  milliseconds = (int32) milliSecAfter1970 % 1000;
  ythis->val.time_sec = seconds;
  ythis->val.time_nsec = 1000000 * milliseconds;
  STACKTRC_LEAVE; return ythis;
}




/**Constructs an instance with reference to timestamp values. */
/*
METHOD_C DateJc_s* ctor_z_DateJc(DateJc_s* ythis, DateValuesJc* val)
{ ythis->val = val;
  memset(&ythis->valuesP, 0, sizeof(ythis->valuesP));
  return ythis;
}
*/

METHOD_C DateJc_s* ctor_Date_iiJc(DateJc_s* ythis, int32 seconds, uint32 nanoseconds)
{ init0p_MemC(ythis, sizeof(DateJc_s));
  ctorc_ObjectJc(&ythis->base.object);
  ythis->val.time_sec = seconds;
  ythis->val.time_nsec = nanoseconds;
  return ythis;
}




METHOD_C void setSystemTime_DateJc(DateJc_s* ythis)
{ ythis->val = os_getDateTime();  //that is a struct copy, using register.
  //ythis->timeString__[0] = 0;
}




StringJc toStringFormat_DateJc(DateJc_s* ythis, StringJc const formatP, int timeZoneAdjustHours, MemC mBuffer)
{ STACKTRC_ENTRY("toStringFormat_DateJc");
  { int lenFormat;
    char const* sFormat = getCharsAndLength_StringJc(&formatP,&lenFormat);
  
    char* buffer = PTR_MemC(mBuffer, char);
    int sizeBuffer = size_MemC(mBuffer);
  
    int posBuffer;
    posBuffer = toStringFormat_Fw(buffer, sizeBuffer, &ythis->val, sFormat, timeZoneAdjustHours);
    if(sFormat[lenFormat-1] == 0)
    { //the formatP contains a \0 at end, it is zero terminated. Terminate also the result!
      if(posBuffer < sizeBuffer)
      { buffer[posBuffer++] = 0;  //it may be some 0 chars at end of
      }   
    }
    { //returns a String.
      StringJc ret;
      INIT_StringJc(ret, buffer, posBuffer);
      STACKTRC_LEAVE; return ret;  //per value.
    }
  }
}


METHOD_C void setTimeNanoseconds_DateJc(DateJc_s* ythis, int32 seconds, int32 nanoseconds)
{ ythis->val.time_sec = seconds;
  ythis->val.time_nsec = nanoseconds;
}













extern_C struct ClassJc_t const reflection_SimpleDateFormatJc_s;

SimpleDateFormatJc_s* ctorO_SimpleDateFormatJc(ObjectJc* othis, ThCxt* _thCxt)
{
  SimpleDateFormatJc_s* ythis = (SimpleDateFormatJc_s*)othis;
  STACKTRC_TENTRY("ctorO_SimpleDateFormatJc");
  checkConsistence_ObjectJc(othis, sizeof(SimpleDateFormatJc_s), &reflection_SimpleDateFormatJc_s, _thCxt); 
  STACKTRC_LEAVE; return ythis;
}

SimpleDateFormatJc_s* ctorO_s_SimpleDateFormatJc(ObjectJc* othis, StringJc sFormat, ThCxt* _thCxt)
{
  SimpleDateFormatJc_s* ythis = (SimpleDateFormatJc_s*)othis;
  STACKTRC_TENTRY("ctorO_S_SimpleDateFormatJc");
  checkConsistence_ObjectJc(othis, sizeof(SimpleDateFormatJc_s), &reflection_SimpleDateFormatJc_s, _thCxt); 
  set_StringJc(&ythis->sFormat, sFormat);
  STACKTRC_LEAVE; return ythis;
}


void setTimeZone_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, TimeZoneJc_s* timeZone, ThCxt* _thCxt)
{
  ythis->timeZoneAdjustHours = timeZone->diffHours;
}


void applyPattern_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, StringJc pattern, ThCxt* _thCxt)
{
  STACKTRC_TENTRY("applyPattern_SimpleDateFormatJc");
  set_StringJc(&ythis->sFormat, pattern);
  STACKTRC_LEAVE;
}

void format_u_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, DateJc_s* timeStamp, StringBuilderJc* buffer, struct TextFieldPositionJc_t* field, ThCxt* _thCxt)
{
  STACKTRC_TENTRY("format_Sb_SimpleDateFormatJc");
  format_tu_SimpleDateFormatJc(ythis, timeStamp->val, buffer, field, _thCxt);
  STACKTRC_LEAVE;
}

void format_tu_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, OS_TimeStamp timeStamp, StringBuilderJc* sBuffer, struct TextFieldPositionJc_t* field, ThCxt* _thCxt)
{ STACKTRC_TENTRY("format_tSb_SimpleDateFormatJc");
  { int lenFormat;
    char const* sFormat = getCharsAndLength_StringJc(&ythis->sFormat, &lenFormat);
  
    int sizeBuffer;
    char* buffer = getCharsAndSize_StringBuilderJc(sBuffer, &sizeBuffer);
    
    int posBuffer;
    posBuffer = toStringFormat_Fw(buffer, sizeBuffer, &timeStamp, sFormat, ythis->timeZoneAdjustHours);
    sBuffer->_count = (int16)posBuffer;
  }
  STACKTRC_LEAVE;
}



StringJc format_SimpleDateFormatJc(SimpleDateFormatJc_s* ythis, OS_TimeStamp timeStamp, ThCxt* _thCxt)
{ StringBuilderJc* buffer;
  STACKTRC_TENTRY("format_SimpleDateFormatJc");
  buffer = threadBuffer_StringBuilderJc("format_SimpleDateFormatJc", _thCxt);
  format_tu_SimpleDateFormatJc(ythis, timeStamp, buffer, null,_thCxt);
  STACKTRC_LEAVE; return toStringMarkPersist_StringBuilderJc(&buffer->base.object, _thCxt);
}


extern_C struct ClassJc_t const reflection_TextFieldPositionJc_s;

TextFieldPositionJc_s* ctorO_TextFieldPositionJc(ObjectJc* othis, int field, ThCxt* _thCxt)
{
  TextFieldPositionJc_s* ythis = (TextFieldPositionJc_s*)othis;
  STACKTRC_TENTRY("ctorO_TextFieldPositionJc_s");
  checkConsistence_ObjectJc(othis, sizeof(TextFieldPositionJc_s), &reflection_TextFieldPositionJc_s, _thCxt); 
  STACKTRC_LEAVE; return ythis;
}



int64 UTC_DateJc(int year, int month, int day, int hour, int minute, int second)
{
	int32 secondsSince1970;
  TimeBytes_emC time;
  time.year = (int16)year;
  time.month = (int8)month;
  time.day = (int8)day;
  time.hour = (int8)hour;
  time.minute = (int8)minute;
  time.sec = (int8)second;
  time.weekInYear = -1;
  secondsSince1970 = timeToSeconds_TimeBytes_emC(&time, 1970, 0, false);
  return 1000 * (int64)secondsSince1970;
}



#include <genRefl/Jc/DateJc.crefl>
