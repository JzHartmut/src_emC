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
 * @dependencies: This source needs only basicly type definitions (os_types_def.h).
 * @version 0.91
 * list of changes:
 * 2010-01-19: Hartmut creation, the source were written in 1996, taken from old time2nn.c, part of source from fw_Formatter.c
 *
 ****************************************************************************/
#include "emC/Base/Timeconversions_emC.h"
#include <stdio.h>
#include <string.h>

/**
 * @changes 2010-01-19 Hartmut corr: taken from old time2nn.c
 */
int32 timeToSeconds_TimeBytes_emC(TimeBytes_emC* ythis, int32 nBaseYear, int32 offsetJan, bool GPS)
{ int nYear=ythis->year-nBaseYear;   //base time is 1.1.1970 at 00:00:00
  int nDayOfMonth[] = {
  	 0
		,31
		,31+28
		,31+28+31
		,31+28+31+30
		,31+28+31+30+31
    ,31+28+31+30+31+30
    ,31+28+31+30+31+30+31
    ,31+28+31+30+31+30+31+31
    ,31+28+31+30+31+30+31+31+30
    ,31+28+31+30+31+30+31+31+30+31
    ,31+28+31+30+31+30+31+31+30+31+30  //days of year to 1. december
    };
  uint32 nTime=
   +(nYear)              *365L*24L*60L*60L
   +((nYear+1)/4)        *  1L *24L*60L*60L //1 Tag pro vergang. Schaltjahr:
                                    //z.B. in 1973 für '72, nYear=3
   +nDayOfMonth[ythis->month-1]*24L*60L*60L //abgeschloss. Monate pro Jahr
   +(ythis->day-1)             *24L*60L*60L
   +ythis->hour                    *60L*60L
   +ythis->minute                     *60L
   +ythis->sec;
  if((nYear+2)%4==0 && ythis->month>2) nTime+=24L*60*60;
  //1 Day im Schaltjahr nach 29.2.

  return(nTime);
}


/**
 * @changes 2010-01-19 Hartmut corr: algorithm corrected, adjusted from fw_Formatter.c and old time2nn.c
 * @changes 2010-07-02 Hartmut chg: add parameter for GPS and offsetJan, but GPS it isn't used yet, todo
 */
void ctor_TimeBytes_emC ( TimeBytes_emC* ythis, int32 nTime, int32 nBaseYear, int32 offsetJan, bool GPS)
{ static const uint16 aMonth[]    ={31,28,31,30,31,30,31,31,30,31,30,31};
  static const uint16 aMonthSkip[]={31,29,31,30,31,30,31,31,30,31,30,31};
  uint16 nYear4,nYear;
  uint8 nMonth;
  const uint16* pDayOfMonth;
  
  //Millesekunden des Tages
  int nDays  = (int)(nTime / (24L*3600L));  //days after 01.01 of baseyear NOTE int is correct on 16-bit-int too!
  int32 nSec = nTime - nDays*(24L*3600L);       //seconds of the day

  nDays-=((nBaseYear%4)+1)*365+1;  //Bezug auf 1.1. nach 1. Schaltjahr Bezug auf 1.1.1973, wenn 1970 das Baseyear ist. 
                                  //Hinweis: vor 1973 erfolgt falsche Darstellung
  nYear4=(int16)(nDays/(4*365+1));         //Anzahl volle 4 Jahre
  nDays-=nYear4*(4*365+1);        //verbleibt Restzeit nach Schaltjahr
  nYear=(int16)(nDays/365);                //volle Jahre nach Schaltjahr
  if(nYear == 4)
  { //at last day, dec 31 of the last year, what is a sleep year, the nrof days = 1460 = 3*365 + 366 -1;  
    nYear = 3;  //That are 3 years of a period with 3 non-sleep year and the sleep year, not 4! 
  }
  nDays-=nYear*365;               //verbleibende Tage im Jahr

  nMonth=0;                       //zun"chst Index auf aMonth
  pDayOfMonth=aMonth;
  if(nYear==3) pDayOfMonth=aMonthSkip; //Schaltjahrestabelle
  while(nDays>=pDayOfMonth[nMonth])    //wenn zuviele Tage f?r Monat (1. Tag ab 0)
  { nDays-=pDayOfMonth[nMonth];        //dann diese subtr.
    nMonth++;                          //und index incr.
  }
  ythis->month=(int8)(nMonth+1);               //+1 da Index ab 0 war
  ythis->day=(int8)(nDays+1);                  //+1 da Anzahl Tage im Monat ab 0 war

  ythis->hour=(int8)(nSec/3600L); nSec-=3600L*ythis->hour;
  ythis->minute=(int8)(nSec/60);  nSec-=60*ythis->minute;
  ythis->sec=(int8)(nSec);


  ythis->year = (int16) (nYear + 
         ( ((nBaseYear+3)/4)*4 +1      //1. Jahr nach Schaltjahr nach baseyear
           +4*nYear4));                 //Jahre absolut nach  Christi Geburt
}


int toString_TimeAbs_emC ( char* buffer, int sizeBuffer, TimeAbs_emC const* time, char const* sFormat, int timeZoneAdjustHours)
{
  int lenFormat = (int)strlen(sFormat);
  TimeBytes_emC timeYsec;
  int maxPosBuffer = sizeBuffer;
  int posBuffer = 0;
  int nHour, nMonth;
  int32 nanos = time->time_nsec;
  STACKTRC_ENTRY("toStringFormat_DateFw");
  ctor_TimeBytes_emC(&timeYsec, seconds_TimeAbs_emC(*time), 1970, 0, isGPS_TimeAbs_emC(*time));

  { static const char* sMonthsFull[12] = {"January", "February", "March", "April", "May", "June"
                       , "July", "August", "September", "October", "November", "December"};
    static const char* sMonthsShort[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun"
                       , "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char sprintfBuffer[8];  //no more as 4 digits, but respect 4-byte-boundary
    nHour = timeYsec.hour;
    nMonth = timeYsec.month;
    while(lenFormat > 0)
    { //read and increment, decrement lenFormat
      char cFormat = *sFormat;
      int lenFormatToken = 1;
      sFormat +=1;
      lenFormat -=1;

      //detect number of equal chars one after another.
      while(lenFormat > 0 && *sFormat == cFormat)
      { lenFormatToken +=1;
        sFormat +=1;
        lenFormat -=1;
      }

      switch(cFormat)
      {
        case 'Y':
        case 'y':
        { int nYear = timeYsec.year;
          char const* format;
          if(lenFormatToken >=4)
          { //append_i_StringBufferJc(&buffer, nYear);
            format = "%4.4i";
          }
          else if(lenFormatToken >=2)
          { nYear -= 2000;
            if(nYear < 0) { nYear += 100; }
            if(nYear >= 100) { nYear -= 100; }
            //if(nYear < 10)
            { //append_c_StringBufferJc(&buffer, '0');
            }
            format = "%2.2i";
          }
          else
          { format = null;
          }
          if(format != null)
          { 
            int nrofChars = snprintf(sprintfBuffer, sizeof(sprintfBuffer), format, nYear);
            if(nrofChars > (maxPosBuffer - posBuffer))
            { nrofChars = maxPosBuffer - posBuffer; //truncate it.
            }
            memcpy(buffer+posBuffer, sprintfBuffer, nrofChars);
            posBuffer += nrofChars;
          }  
        } break;
        case 'M':
        { if(lenFormatToken >3)
          { int nrofChars = (int)strlen(sMonthsFull[nMonth-1]);
            if(nrofChars > (maxPosBuffer - posBuffer))
            { nrofChars = maxPosBuffer - posBuffer; //truncate it.
            }
            memcpy(buffer+posBuffer, sMonthsFull[nMonth-1], nrofChars);
            posBuffer += nrofChars;
          }
          else if(lenFormatToken ==3)
          { int nrofChars = (int)strlen(sMonthsShort[nMonth-1]);
            if(nrofChars > (maxPosBuffer - posBuffer))
            { nrofChars = maxPosBuffer - posBuffer; //truncate it.
            }
            memcpy(buffer+posBuffer, sMonthsShort[nMonth-1], nrofChars);
            posBuffer += nrofChars;
          }
          else
          {
            int nrofChars = snprintf(sprintfBuffer, sizeof(sprintfBuffer), "%2.2i", nMonth);
            if(nrofChars > (maxPosBuffer - posBuffer))
            { nrofChars = maxPosBuffer - posBuffer; //truncate it.
            }
            memcpy(buffer+posBuffer, sprintfBuffer, nrofChars);
            posBuffer += nrofChars;
          }
        } break;
        case 'd':
        { int nrofChars = snprintf(sprintfBuffer, sizeof(sprintfBuffer), "%2.2i", (int)timeYsec.day);
          if(nrofChars > (maxPosBuffer - posBuffer))
          { nrofChars = maxPosBuffer - posBuffer; //truncate it.
          }
          memcpy(buffer+posBuffer, sprintfBuffer, nrofChars);
          posBuffer += nrofChars;
        } break;
        case 'H': 
        case 'h':  //temporary: convert h like H because application errors exists.
        { int nrofChars = snprintf(sprintfBuffer, sizeof(sprintfBuffer), "%2.2i", nHour);
          if(nrofChars > (maxPosBuffer - posBuffer))
          { nrofChars = maxPosBuffer - posBuffer; //truncate it.
          }
          memcpy(buffer+posBuffer, sprintfBuffer, nrofChars);
          posBuffer += nrofChars;
        } break;
        case 'a':  //am/pm-Marker
        { const char* sAmPm = nHour >=12 ? "PM" : "AM";
          int nrofChars = 2;
          if(nrofChars > (maxPosBuffer - posBuffer))
          { nrofChars = maxPosBuffer - posBuffer; //truncate it.
          }
          memcpy(buffer+posBuffer, sAmPm, nrofChars);
          posBuffer += nrofChars;
        } break;
        case 'K':  //hour from 1 to 12
        { int nrofChars = snprintf(sprintfBuffer, sizeof(sprintfBuffer), "%2.2i", (int)(nHour >=12 ? nHour-11 : nHour+1));
          if(nrofChars > (maxPosBuffer - posBuffer))
          { nrofChars = maxPosBuffer - posBuffer; //truncate it.
          }
          memcpy(buffer+posBuffer, sprintfBuffer, nrofChars);
          posBuffer += nrofChars;
        } break;
        case 'm':
        { int nrofChars = snprintf(sprintfBuffer, sizeof(sprintfBuffer), "%2.2i", (int)timeYsec.minute);
          if(nrofChars > (maxPosBuffer - posBuffer))
          { nrofChars = maxPosBuffer - posBuffer; //truncate it.
          }
          memcpy(buffer+posBuffer, sprintfBuffer, nrofChars);
          posBuffer += nrofChars;
        } break;
        case 's':
        { int nrofChars = snprintf(sprintfBuffer, sizeof(sprintfBuffer), "%2.2i", (int)timeYsec.sec);
          if(nrofChars > (maxPosBuffer - posBuffer))
          { nrofChars = maxPosBuffer - posBuffer; //truncate it.
          }
          memcpy(buffer+posBuffer, sprintfBuffer, nrofChars);
          posBuffer += nrofChars;
        } break;
        case 'S':  //millisecond
        { const char* format;
          int millisec = (int)(nanos/1000000L); 
          if(millisec < 0){ millisec +=1000; }
          switch(lenFormatToken)
          { case 1: format = "%1.1u"; millisec /= 100; break;
            case 2: format = "%2.2u"; millisec /= 10; break;
            default: format = "%3.3u"; break;
          }
          { int nrofChars = snprintf(sprintfBuffer, sizeof(sprintfBuffer), format, millisec);
            if(nrofChars > (maxPosBuffer - posBuffer))
            { nrofChars = maxPosBuffer - posBuffer; //truncate it.
            }
            memcpy(buffer+posBuffer, sprintfBuffer, nrofChars);
            posBuffer += nrofChars;
          }
        } break;
        default:
        { //transform the character itself.
          while(--lenFormatToken >=0 && posBuffer < maxPosBuffer)
          { buffer[posBuffer++] = cFormat;
          }
        }
      }
      ASSERT_emC(posBuffer <= maxPosBuffer, "buffer overflow", posBuffer, maxPosBuffer);  //detect errors.
    }
    //NO! The buffer may be a part of a string! buffer[posBuffer] = 0;    
  }
  STACKTRC_LEAVE; return posBuffer;
}




/* old
{ static const uint16 aMonth[]    ={31,28,31,30,31,30,31,31,30,31,30};
  static const uint16 aMonthSkip[]={31,29,31,30,31,30,31,31,30,31,30};
  uint16 nYear4,nYear;
  byte nMonth;
  const uint16* pDayOfMonth;

  uint32 nSeconds=nTime%(24L*3600L);            //Sekunden des Tages
  uint16 nDays  =(uint16)(nTime/(24L*3600L));  //volle Tage

  nDays-=(int16)(3*365+1);                 //Bezug auf 1.1.1973 als 1. Jahr nach Schaltjahr
                                  //Hinweis: vor 1973 erfolgt falsche Darstellung
  nYear4=(int16)(nDays/(4*365+1));         //Anzahl volle 4 Jahre
  nDays-=(int16)(nYear4*(4*365+1));        //verbleibt Restzeit nach Schaltjahr
  nYear=(int16)(nDays/365);                //volle Jahre nach Schaltjahr
  nDays-=(int16)(nYear*365);               //verbleibende Tage im Jahr
  Time->nYear=(int16)(nBaseYear+4*nYear4+nYear);
  nMonth=0;                       //zunächst Index auf aMonth
  pDayOfMonth=aMonth;
  if(nYear==3) pDayOfMonth=aMonthSkip; //Schaltjahrestabelle
  while(nDays>=pDayOfMonth[nMonth])    //wenn zuviele Tage für Monat (1. Tag ab 0)
  { nDays-=pDayOfMonth[nMonth];        //dann diese subtr.
    nMonth++;                          //und index incr.
  }
  Time->nMonth=(char)(nMonth+1);               //+1 da Index ab 0 war
  Time->nDay=(char)(nDays+1);                  //+1 da Anzahl Tage im Monat ab 0 war

  Time->nHour=(byte)(nSeconds/3600L); nSeconds-=3600L*Time->nHour;
  Time->nMinute=(byte)(nSeconds/60);  nSeconds-=60*Time->nMinute;
  Time->nMilliSec=(uint16)(nSeconds*1000);
}
*/



