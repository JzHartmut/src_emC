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
#include "Fwc/fw_timeconversions.h"


/**
 * @changes 2010-01-19 Hartmut corr: taken from old time2nn.c
 */
int32 timeToSeconds_TimeBytes_Fwc(TimeBytes_Fwc* ythis, int32 nBaseYear, int32 offsetJan, bool GPS)
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
void ctor_TimeBytes_Fwc(TimeBytes_Fwc* ythis, int32 nTime, int32 nBaseYear, int32 offsetJan, bool GPS)
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



