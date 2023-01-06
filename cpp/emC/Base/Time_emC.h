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
 * 2017-12-03: Hartmut creation from OSAL/os_time.h 
 *
 ************************************************************************************************/
#ifndef __emC_fw_Time_h__
#define __emC_fw_Time_h__
#include <applstdef_emC.h>
//#include <OSAL/os_time.h>

/**This type is introduced because some processors (Texas Instruments) have 32 bit capabillity
 * but presents the int type with 16 bit.
 * The INT_shortTIME_emC is that type which is used for short times, the width of the internal clock counter.
 */
#ifndef INT_shortTIME_emC
  #define INT_shortTIME_emC  int32
  #define INT_shortTIME_NROFBITS_emC 32
#endif

#if (INT_shortTIME_NROFBITS_emC == 16)
  #define refl_INT_shortTIME_emC refl__int16Jc
#else
  #define refl_INT_shortTIME_emC refl__int32Jc
#endif


typedef struct TimeAbs_emC_T
{   /**Sekunden, gez?hlt seit dem 1. Januar 0:00 Uhr des Jahres 1970.
   * Das Startjahr ist aus der UNIX-Tradition heraus 1970. Das gibt jedoch ein Problem beim Umlauf auf einen negativen Wert etwa in 2038 
   * und einen Gesamtumlauf etwa in 2106. Das Jahr 2038 wird heute bei einer Anlagenstandzeit von 30 Jahren aus heutiger Zeit geradeso erreicht.
   * Es wird hier festgelegt, dass der Sekundenbezug immer auf 1970 orientiert ist, dabei aber eine Wiederholung bei Z?hlerumlauf stattfindet,
   * Der absolute Zeitpunkt muss auf das aktuellen Zeitraum orientiert sein. Damit liegen negative Werte aus Sicht des Jahres 2038 betrachtet
   * nicht im Jahre 1902..1970, sondern eben 2038..2106. Damit ist diese Kennzeichnung zeitlos verwendbar. 
   *
   * F?r eine Zeitdifferenzbildung ist der Wert vorzeichenbehaftet zu verwenden, daher ist er hier auch vorzeichenbehaftet definiert.
   *
   * Schaltsekunden z?hlen mit, wenn das Bit 32 von nanoSeconds gesetzt ist.
   */
  int32 time_sec;
  
  /**Zeit innerhalb einer Sekunde in Nanosekunden gez?hlt.
   * Um schnelle Vorg?nge genau abzubilden, ist eine Genauigkeit von 1 Mikrosekunde h?ufig nicht ausreichend. 
   * Beispielsweise muss bei Parallelschaltung von Umrichtern eine Abweichung von Signalen ?ber weitere Entfernungen 
   * von max. 100 ns erreicht werden, um Differenzstr?me zu vermeiden. 
   * Die tats?chliche Aufl?sung der Zeit h?ngt von den Hardwaregegebenheiten ab.
   * *Bit 29..0: Nanosekunden
   * *Bit 31: Wenn 1, dann stellt der Sekundenz?hler einen Wert dar, der die Schaltsekunden seit 1970 mitz?hlt.
   * *Bit 31: Wenn 0, dann stellt der Sekundenz?hler die kalendarisch gez?hlten Sekunden nach 1970 dar.
   */
  int32 time_nsec;

  /**Nur die folgenden Bits in nanoseconds werden als Nanosekunden verwendet. */
  #define mNanoSeconds_TimeAbs_emC 0x3FFFFFFF

  /**If this bit is set, the TimeStamp is imprecise, it is in a phase of correction. */
  #define mCorrection_TimeAbs_emC 0x40000000

  /**Wenn in seconds die Schaltsekunden mitgez?hlt sind (also keine lineare Abbildung 3600*24 Sekunden pro Tag),
   * dann soll das folgenden Bit gesezt sein:
   */
  #define mLeapSeconds_TimeAbs_emC 0x80000000


} TimeAbs_emC;


/**Another possibility to deal with the time.
 * The timeAbs is Java-related in milliseconds since 1970, hence sufficient for the next centuries.
 * The timeShort is currently incremented in a application specific time unit.
 * The time unit is the cycle of the fastest interrupt in embedded control
 * and maybe for example 50 µs or 1 ms. It is never adjusted,
 * so that time differences are always proper in the possible range.
 *
 */
typedef struct TimeAbsShort_emC_T {
  /**this is the absolute time from 1970-01-01 in milliseconds
   * which is related to the incremental shortTime for the given value.
   * This value should be proper in second ranges, updated after ~ 1 second.
   */
  int64 timeAbs;       //

  /**ShortTime value association to the given timeAbs. */
  int32 timeShortAbs;

  /**Short time to work for example in milliseconds sufficient for +- 23 days
   * or in 50 µs sufficient for one day. .
   * Note: int16 can only mapped to 30 seconds for 1 ms period, too less.
   * The currently short time has the advantage that it is not corrected
   * if the absolute time is adjusted.
   * Time differences with the shortTime are unconditionally correct. */
  int32 timeShort;

} TimeAbsShort_emC_s;






/**Sets from the current computer time so exact as possible. */
void setCurrent_TimeAbs_emC ( TimeAbs_emC* time);


/**Adds a number of micro seconds to the time. 
 * @param usec positive or negative, range +- 35 min
 */
static inline void addMicroSec_TimeAbs_emC ( TimeAbs_emC* thiz, int32 usec) {
  int32 sec = 0;
  if(usec >= 1000000) {
    sec = usec / 1000000;
    usec -= 1000000 * sec;
  }
  else if(usec <= -1000000) {
    sec = usec / 1000000;
    usec -= 1000000 * sec;
  } 
  thiz->time_sec += sec;
  int32 nanosec = (thiz->time_nsec & 0x3FFFFFFF) + 1000 * usec;
  if(nanosec > 1000000000) {  //3B9A'CA00
    nanosec -= 1000000000;
    thiz->time_sec +=1;
  } else if(nanosec <0) {
    nanosec += 1000000000;
    thiz->time_sec -=1;
  }
  thiz->time_nsec = (thiz->time_nsec & 0xc0000000) + nanosec;
}



/**Adds a number of micro seconds to the time. 
 * @param cmp first time, diff to thiz is build
 * @return difference in micro seconds, about +-35 min. Maybe limited to min or max
 */
static inline int32 diffMicroSec_TimeAbs_emC ( TimeAbs_emC* thiz, TimeAbs_emC* cmp) {
  int32 diff_sec = thiz->time_sec - cmp->time_sec;
  int32 diff_nsec = (thiz->time_nsec & 0x3fffffff) - (cmp->time_nsec & 0x3fffffff);
  if(diff_sec > 2147) { return 2147 * (int32)(1000000); }
  else if(diff_sec < -2147) { return -2147 * 1000000; }
  else { return diff_sec * 1000000 + ( diff_nsec + 500) / 1000; }
}



/**Delays the execution of this thread with yield to other for given number of milliseconds.
 * This operation have to be implemented os-specific( (os_time.c)
 */
extern_C void sleep_Time_emC ( int32 msec );


/**Delays the execution of this thread with yield to other for given number of microseconds.
 * This operation have to be implemented os-specific( (os_time.c)
 */
extern_C void sleepMicroSec_Time_emC ( int32 usec );

#ifndef microsecondsPerClock_Time_emC  //may be defined as const literal
/**This value is set for the given environment (CPU, depends on clock) after calling measureClock_Time_emC().
 * It is used for some operations, especially nanoTime_emC().
 */
extern float microsecondsPerClock_Time_emC;
#endif

#ifndef clocksPerMicro_Time_emC  //may be defined as const literal
/**This value is set for the given environment (CPU, depends on clock) after calling measureClock_Time_emC().
* It is used for some operations, especially addMicrosec_Time_emC().
* The resolution is limited. On a not fast CPU there may be for example 21 clocks per microsecond, 
* the more exact value may be a real value of 21.245 but it is proper for integer arithmetic. 
*/
extern int clocksPerMicro_Time_emC;
#endif

#ifndef clocksFloatPerMicro_Time_emC  //may be defined as const literal
/**This value is set for the given environment (CPU, depends on clock) after calling measureClock_Time_emC().
* It is used for some operations, especially addFloatMicrosec_Time_emC().
*/
extern float clocksFloatPerMicro_Time_emC;
#endif


/**Gets a circular time information in clocks of the system.
 * @return a relativ value, the value can be used only for differnces.
 * The step-width of the return value depends from the CPU-clock.
 * The value should only be used for comparing times.
 *
 * Example: If the clock counts with 10 nanoseconds, a difference is valid in 20 seconds 
 */
#ifndef getClockCnt_Time_emC  //it may be a macro for fast access in special targets
  extern_C INT_shortTIME_emC getClockCnt_Time_emC ( void );
#endif


/**Measures the duration of 1 clock which is used for [[getClockCnt_Time_emC()]].
* This routine needs some calculation time, up to 1 second. It should be invoked only on start.
* @param meastime in ms, determines the accuracy
* @return true if it has measured exactly 1 second.  
*/ 
extern_C bool measureClock_Time_emC(INT_shortTIME_emC meastime);


extern_C void waitClock_Time_emC(int32 tillClockCt);


/**Adds the given time offset to the current given clockCt. Use this faster operation for lower values of micros instead [[addFloatMicrosec_Time_emC(...)]] 
 * for a fast only integer multiplication.  
 * @param clockCt any value gotten from [[getClockCnt_Time_emC()]]
 * @param micros number of micro seconds. The value should not be higher than about 10000000 (1 second) because the range of clockCt should be regarded.
 *   Negative values for time in the past are possible if necessary.
 */
static int32 addMicrosec_Time_emC(int32 clockCt, int32 micros);
//Hint need prototype decl because MISRA
INLINE_emC int32 addMicrosec_Time_emC(int32 clockCt, int32 micros) { return clockCt + micros * clocksPerMicro_Time_emC; }


/**Adds the given time offset to the current given clockCt. use this operation instead [[addMicrosec_Time_emC(...)]] 
 * to get a higher precision for larger values of micros. 
 * @param clockCt any value gotten from [[getClockCnt_Time_emC()]]
 * @param micros number of micro seconds. The value should not be higher than about 10000000 (1 second) because the range of clockCt should be regarded.
 *   Negative values for time in the past are possible if necessary.
 */
static int32 addFloatMicrosec_Time_emC(int32 clockCt, int32 micros);
INLINE_emC int32 addFloatMicrosec_Time_emC(int32 clockCt, int32 micros) { return (clockCt + (int32)(micros * clocksFloatPerMicro_Time_emC)); }

static float microDiffofClock_Time_emC(int32 clockDiff);
INLINE_emC float microDiffofClock_Time_emC(int32 clockDiff) { return (clockDiff * microsecondsPerClock_Time_emC); }

static float microDiffLongofClock_Time_emC(int64 clockDiff);
INLINE_emC float microDiffLongofClock_Time_emC(int64 clockDiff) { return (clockDiff * microsecondsPerClock_Time_emC); }


typedef struct SimTime_emC_t
{
  int32 timeShort;

  int32 spare1_8aligned;  //for 8-byte-Alignment.

  double timeSim;

} SimTime_emC;


//extern_C ClassJc const refl_SimTime_emC;

/*@CLASS_C TimeShortStepCycle_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#ifndef timeShortStepCycle_emC  //may be defined application specific and simple in applstdef_emC.h

//tag::timeShortStepCycle_emC[]
/**Returns a wrapping short time counting with the fast interrupt cycle. 
 * This operation must be defined in a target- and application specific way, 
 * it means usual in the organization of main, interrupts and threads.
 */
int timeShortStepCycle_emC ( );
//end::timeShortStepCycle_emC[]

#endif //timeShortStepCycle_emC

/*@CLASS_C MinMaxTime_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



typedef struct MinMaxCalcTime_emC_T
{
  uint minCalcTime;

  uint ctSpikes;

  uint32 midCalcTime;

  uint actCalcTime;

  uint maxCalcTime;

} MinMaxCalcTime_emC;





typedef struct MinMaxTime_emC_t
{
    INT_shortTIME_emC ct;

  INT_shortTIME_emC _lastTime;
  //uint minminCyclTime;

  uint minCyclTime;

  uint actCyclTime;

  uint32 midCyclTime;

  uint maxCyclTime;

  //uint maxmaxCyclTime;

  MinMaxCalcTime_emC calc;

} MinMaxTime_emC;



static void ctor_MinMaxTime_emC(MinMaxTime_emC volatile* thiz);

INLINE_emC void ctor_MinMaxTime_emC(MinMaxTime_emC volatile* thiz)
{ thiz->maxCyclTime = 0;  
  //thiz->maxmaxCyclTime = 0;  
  thiz->calc.maxCalcTime = 0;  
  thiz->midCyclTime = 0;  
  thiz->actCyclTime = 0;  
  thiz->calc.midCalcTime = 0;  
  thiz->minCyclTime = (uint)(-1);  //uint max
  //thiz->minminCyclTime = 0x7FFFFFFF;   
  thiz->calc.minCalcTime = (uint)(-1);  //uint max
  thiz->_lastTime = 0;                  
}



/**
* invoke with (..., getClockCnt_Time_emC()) 
*/
static void cyclTime_MinMaxTime_emC ( MinMaxTime_emC volatile* thiz, INT_shortTIME_emC time);

INLINE_emC void cyclTime_MinMaxTime_emC(MinMaxTime_emC volatile* thiz, INT_shortTIME_emC time)
{ uint cyclTime = (uint)(time - thiz->_lastTime);
  thiz->ct +=1;  
  thiz->actCyclTime = cyclTime;  
  if(cyclTime > thiz->maxCyclTime) { thiz->maxCyclTime = cyclTime; }  
  if((cyclTime < thiz->minCyclTime) || (thiz->maxCyclTime == 0)) { thiz->minCyclTime = cyclTime; }
  thiz->midCyclTime += (cyclTime - (thiz->midCyclTime>>10));
  thiz->_lastTime = time;                  
}

/**With given time. */
static void cyclTime_fast_MinMaxTime_emC(MinMaxTime_emC volatile* thiz, INT_shortTIME_emC time);
INLINE_emC void cyclTime_fast_MinMaxTime_emC(MinMaxTime_emC volatile* thiz, INT_shortTIME_emC time)
{ uint cyclTime = (uint)((time) - thiz->_lastTime); 
  thiz->ct +=1; 
  thiz->actCyclTime = cyclTime;  
  if((cyclTime > thiz->maxCyclTime) && (cyclTime < (thiz->midCyclTime >>9))) { thiz->maxCyclTime = cyclTime; }
  //if(cyclTime > thiz->maxmaxCyclTime){ thiz->maxmaxCyclTime = cyclTime; } 
  if((cyclTime < thiz->minCyclTime) && (cyclTime > (thiz->midCyclTime >>11))){ thiz->minCyclTime = cyclTime; }
  //if(cyclTime < thiz->minminCyclTime){ thiz->minminCyclTime = cyclTime; } 
  thiz->midCyclTime += (cyclTime - (thiz->midCyclTime >>10));            
  thiz->_lastTime = time;                  
}


/**With given time. */
static void set_MinMaxCalcTime_emC(MinMaxCalcTime_emC volatile* thiz, INT_shortTIME_emC timeStart, INT_shortTIME_emC time);

INLINE_emC void set_MinMaxCalcTime_emC(MinMaxCalcTime_emC volatile* thiz, INT_shortTIME_emC timeStart, INT_shortTIME_emC time)
{ uint calcTime = (uint)(time - timeStart); 
  thiz->actCalcTime = calcTime;  
  if(calcTime > thiz->maxCalcTime) { thiz->maxCalcTime = calcTime; }  
  if((calcTime < thiz->minCalcTime) || (thiz->minCalcTime == 0)) { thiz->minCalcTime = calcTime; }
  thiz->midCalcTime += (calcTime - (thiz->midCalcTime >>10));      
}


INLINE_emC void setPreventSpikes_MinMaxCalcTime_emC(MinMaxCalcTime_emC volatile* thiz, INT_shortTIME_emC timeStart, INT_shortTIME_emC time)
{ uint calcTime = (uint)(time - timeStart); 
  thiz->actCalcTime = calcTime;  
  if(calcTime > thiz->maxCalcTime) { thiz->maxCalcTime = calcTime; }  
  if((calcTime < thiz->minCalcTime) || (thiz->minCalcTime == 0)) { thiz->minCalcTime = calcTime; }
  uint midcalctime2Cmp = thiz->midCalcTime >>9; //the compare value.
  if(calcTime > midcalctime2Cmp || calcTime < (midcalctime2Cmp >>2)) {
    if(++thiz->ctSpikes > 10) { //ten times one after another
      thiz->midCalcTime = ((uint32)calcTime) <<10; //set it newly it is not a spike.
    } 
  } else {
    thiz->ctSpikes = 0;
    thiz->midCalcTime += (calcTime - (thiz->midCalcTime >>10)); //smooth time 1024     
  } 
}

/**With given time. */
static void calcTime_MinMaxTime_emC(MinMaxTime_emC volatile* thiz, INT_shortTIME_emC time);
INLINE_emC void calcTime_MinMaxTime_emC(MinMaxTime_emC volatile* thiz, INT_shortTIME_emC time)
{
  set_MinMaxCalcTime_emC(&thiz->calc, thiz->_lastTime, time);
}

/**Stores middle value of difference time in any variable, without min and max.
* @param VAR variable to store middle time 
*/
#define mesTimeMid_I_MinMaxTime_emC(thiz, time, VAR, VARMID)        \
{ (VAR) = (time) - (thiz)->_lastTime; \
  (VARMID) += (VAR) - ((VARMID) >>10);            \
}

/**Stores difference time in any variable, without min and max. 
* @param VAR variable to store middle time 
*/
#define mesTime_I_MinMaxTime_emC(thiz, time, VAR)        \
{ (VAR) = (time) - (thiz)->_lastTime; \
}

/**Stores difference time in any variable, without min and max.
* @param VAR variable to store middle time
*/
#define timeAfterStart_MinMaxTime_emC(thiz, time)        \
( (time) - (thiz)->_lastTime )


typedef struct Clock_MinMaxTime_emC_T {

  union{ObjectJc obj; } base;

  float microSecondsPerClock;

  int32 nrofSlices;

  /**3 nested instances for time measurements in 3 time slots. More are possible. */
  MinMaxTime_emC times[3];
} Clock_MinMaxTime_emC;

#if !defined(DEF_NO_ObjectJc_emC) && !defined(DEF_REFLECTION_NO) //&& !defined(DEFINED_refl_Clock_MinMaxTime_emC)
  extern_C ClassJc const refl_Clock_MinMaxTime_emC;
  #define reflection_Clock_MinMaxTime_emC refl_Clock_MinMaxTime_emC
#endif
#ifndef ID_refl_Clock_MinMaxTime_emC
  #define ID_refl_Clock_MinMaxTime_emC 0x0FF6 
#endif


extern_C void ctor_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz, int nrofEntries);


extern_C void init_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz);


/**
 * @simulink Operation-FB, step-in.
 */
extern_C void startTime_Clock_MinMaxTime(int slice_param, float* time_y);

/**
* @simulink Operation-FB, step-in.
*/
extern_C void measTime_Clock_MinMaxTime(int slice_param, float* time_y);


typedef struct MeasRunTimeFBlock_T {

  /**Number of executions for the routine. */
  int nrExec;

  /**Any specific number to control what is executed. */
  int whatExec;

  /**Two start values for execution. */
  int val1, val2;

  float valf1, valf2;

} MeasRunTimeFBlock_s;





#endif  //Headerguard
