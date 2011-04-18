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
 * @content Definition of memory access routines. 
 * This routines are implemented in a operation system specific way. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * list of changes:
 * 2010-03-01 Hartmut corr: int32_t os_getClockCnt(void) instead int64, it is enaugh and applicate-able to all systems.
 * 2010-02-26 Hartmut new: class MinMaxTime_Fwc os-independt, but useable at lo level.
 * 2010-02-26 Hartmut corr: ctor with return value
 * 2008-02-01: Hartmut creation 
 *
 ************************************************************************************************/
#ifndef __os_time_h__
#define __os_time_h__

#include <os_types_def.h>

extern_C_BLOCK_

/*@CLASS_C OS_TimeStamp @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/* Strukturen */
typedef struct OS_TimeStamp_t
{   /**Sekunden, gezählt seit dem 1. Januar 0:00 Uhr des Jahres 1970.
   * Das Startjahr ist aus der UNIX-Tradition heraus 1970. Das gibt jedoch ein Problem beim Umlauf auf einen negativen Wert etwa in 2038 
   * und einen Gesamtumlauf etwa in 2106. Das Jahr 2038 wird heute bei einer Anlagenstandzeit von 30 Jahren aus heutiger Zeit geradeso erreicht.
   * Es wird hier festgelegt, dass der Sekundenbezug immer auf 1970 orientiert ist, dabei aber eine Wiederholung bei Zählerumlauf stattfindet,
   * Der absolute Zeitpunkt muss auf das aktuellen Zeitraum orientiert sein. Damit liegen negative Werte aus Sicht des Jahres 2038 betrachtet
   * nicht im Jahre 1902..1970, sondern eben 2038..2106. Damit ist diese Kennzeichnung zeitlos verwendbar. 
   *
   * Für eine Zeitdifferenzbildung ist der Wert vorzeichenbehaftet zu verwenden, daher ist er hier auch vorzeichenbehaftet definiert.
   *
   * Schaltsekunden zählen mit, wenn das Bit 32 von nanoSeconds gesetzt ist.
   *  @bytepos=4 
 */
  int32_t time_sec;
  
  /**Zeit innerhalb einer Sekunde in Nanosekunden gezählt.
   * Um schnelle Vorgänge genau abzubilden, ist eine Genauigkeit von 1 Mikrosekunde häufig nicht ausreichend. 
   * Beispielsweise muss bei Parallelschaltung von Umrichtern eine Abweichung von Signalen über weitere Entfernungen 
   * von max. 100 ns erreicht werden, um Differenzströme zu vermeiden. 
   * Die tatsächliche Auflösung der Zeit hängt von den Hardwaregegebenheiten ab.
   * *Bit 29..0: Nanosekunden
   * *Bit 31: Wenn 1, dann stellt der Sekundenzähler einen Wert dar, der die Schaltsekunden seit 1970 mitzählt.
   * *Bit 31: Wenn 0, dann stellt der Sekundenzähler die kalendarisch gezählten Sekunden nach 1970 dar.
   *  @bytepos=0 
   */
  int32_t time_nsec;

  /**Nur die folgenden Bits in nanoseconds werden als Nanosekunden verwendet. */
  #define mNanoSeconds_OS_TimeStamp 0x3FFFFFFF

  /**If this bit is set, the TimeStamp is imprecise, it is in a phase of correction. */
  #define mCorrection_OS_TimeStamp 0x40000000

  /**Wenn in seconds die Schaltsekunden mitgezählt sind (also keine lineare Abbildung 3600*24 Sekunden pro Tag),
   * dann soll das folgenden Bit gesezt sein:
   */
  #define mLeapSeconds_OS_TimeStamp 0x80000000


} OS_TimeStamp;

//compatibility, 
#define OS_TimeStruct OS_TimeStamp

/**Initializes the timestamp with 0, it is a time 1. 1. 1970. */
OS_TimeStamp* ctorM_OS_TimeStamp(OS_PtrValue mem);

/**Initializes the timestamp with 0, it is a time 1. 1. 1970. */
#define INIT_OS_TimeStamp(THIS) (memset(&THIS, 0, sizeof(THIS)))

/**Initializes the timestamp with the current time. */
#define INIT_now_OS_TimeStamp(THIS, VALUE) (THIS = os_getDateTime())

/**Initializes the timestamp with the given time. */
#define INIT_time_OS_TimeStamp(THIS, SRC) (THIS = SRC)

/**Assigns the SRC to THIS. */
#define set_OS_TimeStamp(THIS, SRC) (THIS = SRC)

/**Gets the value of seconds of a OS_TimeStamp. Note: do not use the value itself because encapsulating. */
#define seconds_OS_TimeStamp(THIS) ((THIS).time_sec)

/**Gets the value of nanoseconds of a OS_TimeStamp. Note: do not use the value itself because encapsulating. */
#define nanoSeconds_OS_TimeStamp(THIS) ((THIS).time_nsec & mNanoSeconds_OS_TimeStamp)

#define isGPS_OS_TimeStamp(THIS) (((THIS).time_nsec & mLeapSeconds_OS_TimeStamp) != 0)

#define isImprecise_OS_TimeStamp(THIS) (((THIS).time_nsec & mCorrection_OS_TimeStamp) != 0)

/**Sets a GPS-Time-value to a OS_TimeStamp. 
 * The time from GPS positioning follows the TAI (InternationalAtomic Time), 
 * with a constant difference of 19 seconds, without any leap seconds. Why 19 seconds? It's historical.
 * In technical systems a strict uniformly continuous time counter is better to than the UTC.
 */
#define setGPS_OS_TimeStamp(THIS, SEC, NSEC) { (THIS).time_sec = (SEC); (THIS).time_nsec = (NSEC) | mLeapSeconds_OS_TimeStamp; }

/**Sets a UTC-Time-value to a OS_TimeStamp. 
 * UTC (= <a href="http://en.wikipedia.org/wiki/Coordinated_Universal_Time">Coordinated Universal Time</a> ) 
 * follows the caesium atomic clock, 
 * but it is coordinated with the earth rotation. respectively it follows the simple division 
 * of 1 year into 365 * 24* 3600 seconds and 366 * 24 * 3600 seconds in a leap year.
 * If leap seconds are occurred, the second count of UTC is the same for 2 seconds.
 * In computer systems, often UTC is used, because the unix-time also count simple seconds
 * without regarding of leap seconds. 
 */
#define setUTC_OS_TimeStamp(THIS, SEC, NSEC) { (THIS).time_sec = (SEC); (THIS).time_nsec = (NSEC); }


/**Gets the systems time. */
OS_TimeStruct os_getDateTime(void);


/**Sets or adjsuts the time of the system.
 * @param pDataTime If isOffset is 0, it is the set-time.
 *        If offset is -1 or +1, it is an offset (seconds from current time).
 * @param isOffset -1 or +1, than the time will be adjusted with seconds and nanoseconds in pDataTime.
          0 than the time will be set.
 * @return 0 if ok, negativ value on error.
 */
int os_setDateTime(OS_TimeStruct const* pDateTime, int isOffset);


/**Gets a circular time information in milliseconds.
 * @return a relativ value, the value can be used only for differnces.
 */
int32_t os_getMilliTime(void);
int32_t os_milliTime(void); 

/**Gets a circular time information in microseconds.
 * @return a relativ value, the value can be used only for differnces.
 */
int32_t os_getMicroTime(void);
int32_t os_microTime(void);
 
/**Gets a circular time information in clocks of the system.
 * @return a relativ value, the value can be used only for differnces.
 * The step-width of the return value depends from the CPU-clock.
 * The value should only be used for comparing times.
 *
 * Example: If the clock counts with 10 nanoseconds, a difference is valid in 20 seconds 
 */
int32_t os_getClockCnt(void);
//int32_t os_getClockTime(void);
 

/**Delays a thread for a number of milliseconds.
 * @param timeOut sleep time in milliseconds.
 */
void os_delayThread(int32_t timeOut);
#define os_sleep(TIME) os_delayThread(TIME);




/*@CLASS_C MinMaxTime_Fwc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/




typedef struct MinMaxTime_Fwc_t
{
  int32_t ct;
  
  uint32_t minminCyclTime;

  uint32_t minCyclTime;

  uint32_t midCyclTime;

  uint32_t maxmaxCyclTime;
  
  uint32_t maxCyclTime;

  uint32_t minCalcTime;

  uint32_t midCalcTime;

  uint32_t maxCalcTime;

  uint32_t actCyclTime;

  int32_t _lastTime;


}MinMaxTime_Fwc;

#define init_MinMaxTime_Fwc(YTHIS)        \
{ (YTHIS)->maxCyclTime = 0;  \
  (YTHIS)->maxmaxCyclTime = 0;  \
  (YTHIS)->maxCalcTime = 0;  \
  (YTHIS)->midCyclTime = 0;  \
  (YTHIS)->actCyclTime = 0;  \
  (YTHIS)->midCalcTime = 0;  \
  (YTHIS)->minCyclTime = 0x7FFFFFFF;   \
  (YTHIS)->minminCyclTime = 0x7FFFFFFF;   \
  (YTHIS)->minCalcTime = 0x7FFFFFFF;  \
  (YTHIS)->_lastTime = 0;                  \
}


#define cyclTime_MinMaxTime_Fwc(YTHIS)        \
{ int32_t time = (int32_t)os_getClockCnt();       \
  uint32_t cyclTime = time - (YTHIS)->_lastTime; \
  (YTHIS)->ct +=1;  \
  (YTHIS)->actCyclTime = cyclTime;  \
  if(cyclTime > (YTHIS)->maxCyclTime) { (YTHIS)->maxCyclTime = cyclTime; }  \
  if(cyclTime < (YTHIS)->minCyclTime) { (YTHIS)->minCyclTime = cyclTime; }  \
  (YTHIS)->midCyclTime += cyclTime - ((YTHIS)->midCyclTime>>10);            \
  (YTHIS)->_lastTime = time;                  \
}

/**With given time. */
#define cyclTime_fast_MinMaxTime_Fwc(YTHIS, time)        \
{ uint32_t cyclTime = (time) - (YTHIS)->_lastTime; \
  (YTHIS)->ct +=1; \
  (YTHIS)->actCyclTime = cyclTime;  \
  if(cyclTime > (YTHIS)->maxCyclTime && cyclTime < ((YTHIS)->midCyclTime >>9)) { (YTHIS)->maxCyclTime = cyclTime; }  \
  if(cyclTime > (YTHIS)->maxmaxCyclTime){ (YTHIS)->maxmaxCyclTime = cyclTime; } \
  if(cyclTime < (YTHIS)->minCyclTime && cyclTime > ((YTHIS)->midCyclTime >>11)) { (YTHIS)->minCyclTime = cyclTime; }  \
  if(cyclTime < (YTHIS)->minminCyclTime){ (YTHIS)->minminCyclTime = cyclTime; } \
  (YTHIS)->midCyclTime += (cyclTime - ((YTHIS)->midCyclTime >>10));            \
  (YTHIS)->_lastTime = time;                  \
}


/**With given time. */
#define calcTime_fast_MinMaxTime_Fwc(YTHIS, time)        \
{ uint32_t calcTime = (time) - (YTHIS)->_lastTime; \
  if(calcTime > (YTHIS)->maxCalcTime) { (YTHIS)->maxCalcTime = calcTime; }  \
  if(calcTime < (YTHIS)->minCalcTime) { (YTHIS)->minCalcTime = calcTime; }  \
  (YTHIS)->midCalcTime += (calcTime - ((YTHIS)->midCalcTime >>10));            \
}

_END_extern_C_BLOCK


/**Regard a special platform variant, which may define macros instead prototypes: */
#ifdef PLATFORM_os_time_h
#include "PLATFORM_os_time.h"
#endif

#endif //__os_time_h__
