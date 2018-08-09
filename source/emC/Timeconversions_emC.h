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
 * @content Conversion routines between time representations.
 *
 * @author Hartmut Schorrig
 * @dependencies: This source needs only basicly type definitions (os_types_def.h) and os_time.h
 * @version 0.91
 * list of changes:
 * 2010-01-19: Hartmut creation, the source were written in 1996, taken from old time2nn.c, part of source from fw_Formatter.c
 *
 ****************************************************************************/

#include <applstdef_emC.h>  //Note: define before include-guards because applstdef_emC,h may include this file too.
//The following include guard prevent twice include especially if appöstdefJc.h includes this file already.
#ifndef __emC_fw_timeconversions_h__
#define __emC_fw_timeconversions_h__
#include <os_time.h>

/**Datum als Bytewerte zur Uebergabe
 * Note: The day of week can be calculated by divide the seconds by 24 * 3600 and than modulo 7. 
 * @since This struct was created from Hartmut Schorrig in 1996. Name at that time: _timeBytes, file INC/SYSTIME:H 
 * @change 
 * 2010-07-02 Hartmut chg: int8 sec instead of uint16 millisec: This struct should not used to store an continuous timestamp!
 *                    instead this the weekInYear is stored here.     
 * 1996-00-00 Hartmut This struct was created from Hartmut Schorrig in 1996. Name at that time: _timeBytes, file INC/SYSTIME:H 
 */
typedef struct TimeBytes_emC  
{ int16 year;       /*Jahr anno domini  */
  int8 month;       /*01 bis 12         */
  int8 day;         /*01 bis 31         */
  int8 hour;        /*00 bis 23         */
  int8 minute;      /*00 bis 59         */
  int8 sec;         /*0 bis 60          */
  /**Week in the year. */
  int8 weekInYear;   /*1 to 52           */
}TimeBytes_emC;         /*Struktur auf 4-Byte-boundary! Das sind 8 Byte.*/


/*Original comment from 1995: folg. fn konvertieren UNIX-Zeitformat in Datum und Zeit und zurueck,
  19971202 Borland-C unixtodos() nicht mehr verwenden, da dies 4..5 Std Zeitdifferenz
  beruecksichtigt, einschl. Sommer/Winterzeit fuer USA
  unixtodos() liefert keine exakte Datumsabbildung.
*/

int32 timeToSeconds_TimeBytes_emC(TimeBytes_emC* date, int32 nBaseYear, int32 offsetJan, bool GPS);

/**Converts the given seconds in year...second. It is the constructor of a instance of this type.
 * @param seconds The seconds in a continoues count, typical seconds from Jan, 1, 1970.
 * @param baseyear The year for start date. Mostly it should be the value 1970. 
 * @param offsetJan Number of seconds which should be added to second for the Jan, 1th of the baseyear.
 * @param GPS true than the leap seconds will be regarded. The table of leap seconds is given as default,
 *        But it is able to override globally in the application, see [[>setLeapSecondTable_TimeYearSecond_Formatter_FW]]
 */
void ctor_TimeBytes_emC(TimeBytes_emC* date, int32 seconds, int32 baseyear, int32 offsetJan, bool GPS);

#define timeFromSeconds_TimeBytes_emC(YTHIS, SEC, BASE) ctor_TimeBytes_emC(YTHIS, SEC, BASE, 0, false)

int32 timeToLong(TimeBytes_emC* date);
void timeFromLong(TimeBytes_emC* date, int32 nTime);





/**This method convers the timestamp to a readable format. It is enhanced respectively java.lang.Date, to simplify using.
 * The format characters are the same as java.text.SimpleDateFormat, but not all from there:
 * * yyyy Year with 4 digits like 1970 or 2007
 * * yy   Year with 2 digits like 70 or 07
 * * MMMM   Month in english full word like January, July, December
 * * MMM    Month in english short word like Jan, Jul, Dec
 * * M, MM  Month with 2 digits like 01, 07, 12
 * * D..DDD Day in the year from 1 o 366 using at least the number of D letters as digits, leading 0.
 * * d..dd  Day in the month from 1 o 31 using at least the number of D letters as digits, leading 0.
 * * F      Day of week from 1 o 7.
 * * EEEE   Day in Week
 * * EEE    Day in Week Mon, Tue
 * * a      Am/pm marker
 * * HH     Hour in Day 0..23
 * * kk     Hour in Day 1..24
 * * hh      Hour in am/pm 0..11
 * * kk      Hour in am/pm 1..12
 * * mm     Minute in hour
 * * ss     Second in minute
 * * SS     10 Millisecond in second.
 * * SSS    Millisecond in second.
 *
 * @param buffer The buffer in which the data string is written in. The buffer is not initialized. 
 *               Only the returned nr of chars are written, other content isn't changed.
 * @param sizeBuffer max. Number of chars which will be written at buffer. 
 * If the date string is longer as this param, the rest is not written. (No Exception).
 * @param time The time 
 * @param format String to determine the positions of the parts of readable date.
 * @param timeZoneAdjustHours Anzahl der Stunden für die Zeitzonenverschiebung.
                              Es wird davon ausgegangen, dass intern nach Greenwich Mean Time gespeichert ist.
              Die Angabe von 1 bedeutet eine Verschiebung in Richtung MEZ (Winter).
 * @return nr of chars written.
 */
int toStringFormat_Fw(char* buffer, int sizeBuffer, OS_TimeStamp const* time, char const* sFormat, int timeZoneAdjustHours);







#endif //__emC_fw_timeconversions_h__
