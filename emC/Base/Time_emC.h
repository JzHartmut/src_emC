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
#include <emC/Base/Object_emC.h>
//#include <OSAL/os_time.h>

/**This value is set for the given environment (CPU, depends on clock) after calling measureClock_Time_emC().
 * It is used for some operations, especially nanoTime_emC().
 */
extern float microsecondsPerClock_Time_emC;

/**This value is set for the given environment (CPU, depends on clock) after calling measureClock_Time_emC().
* It is used for some operations, especially addMicrosec_Time_emC().
* The resolution is limited. On a not fast CPU there may be for example 21 clocks per microsecond, 
* the more exact value may be a real value of 21.245 but it is proper for integer arithmetic. 
*/
extern int clocksPerMicro_Time_emC;

/**This value is set for the given environment (CPU, depends on clock) after calling measureClock_Time_emC().
* It is used for some operations, especially addFloatMicrosec_Time_emC().
*/
extern int clocksFloatPerMicro_Time_emC;

/**Measures the duration of 1 clock which is used for [[os_getClockCnt()]].
* This routine needs some calculation time, up to 1 second. It should be invoked only on start.
* @param meastime in ms, determines the accuracy
* @return true if it has measured exactly 1 second.  
*/ 
bool measureClock_Time_emC(int meastime);


void waitClock_Time_emC(int32 tillClockCt);

/**Adds the given time offset to the current given clockCt. Use this faster operation for lower values of micros instead [[addFloatMicrosec_Time_emC(...)]] 
 * for a fast only integer multiplication.  
 * @param clockCt any value gotten from [[os_getClockCnt()]]
 * @param micros number of micro seconds. The value should not be higher than about 10000000 (1 second) because the range of clockCt should be regarded.
 *   Negative values for time in the past are possible if necessary.
 */
inline int32 addMicrosec_Time_emC(int32 clockCt, int32 micros) { return clockCt + micros * clocksPerMicro_Time_emC; }


/**Adds the given time offset to the current given clockCt. use this operation instead [[addMicrosec_Time_emC(...)]] 
 * to get a higher precision for larger values of micros. 
 * @param clockCt any value gotten from [[os_getClockCnt()]]
 * @param micros number of micro seconds. The value should not be higher than about 10000000 (1 second) because the range of clockCt should be regarded.
 *   Negative values for time in the past are possible if necessary.
 */
inline int32 addFloatMicrosec_Time_emC(int32 clockCt, int32 micros) { return clockCt + (int32)(micros * clocksFloatPerMicro_Time_emC); }


inline float microDiffofClock_Time_emC(int32_t clockDiff) { return clockDiff * microsecondsPerClock_Time_emC; }

inline float microDiffLongofClock_Time_emC(int64_t clockDiff) { return clockDiff * microsecondsPerClock_Time_emC; }


typedef struct SimTime_emC_t
{
  int32 timeShort;

  int32 spare1_8aligned;  //for 8-byte-Alignment.

  double timeSim;

} SimTime_emC;


extern_C ClassJc const reflection_SimTime_emC;


/*@CLASS_C MinMaxTime_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



typedef struct MinMaxCalcTime_emC_t
{
  uint minCalcTime;

  uint midCalcTime;

  uint actCalcTime;

  uint maxCalcTime;

} MinMaxCalcTime_emC;





typedef struct MinMaxTime_emC_t
{
  int ct;

  int _lastTime;
  //uint minminCyclTime;

  uint minCyclTime;

  uint actCyclTime;

  uint midCyclTime;

  uint maxCyclTime;

  //uint maxmaxCyclTime;

  MinMaxCalcTime_emC calc;

} MinMaxTime_emC;





inline void init_MinMaxTime_emC(MinMaxTime_emC* thiz)
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
* invoke with (..., os_getClockCnt()) 
*/
inline void cyclTime_MinMaxTime_emC(MinMaxTime_emC* thiz, int time)        
{ uint cyclTime = (uint)(time - thiz->_lastTime); 
  thiz->ct +=1;  
  thiz->actCyclTime = cyclTime;  
  if(cyclTime > thiz->maxCyclTime) { thiz->maxCyclTime = cyclTime; }  
  if(cyclTime < thiz->minCyclTime || thiz->maxCyclTime == 0) { thiz->minCyclTime = cyclTime; }
  thiz->midCyclTime += cyclTime - (thiz->midCyclTime>>10);            
  thiz->_lastTime = time;                  
}

/**With given time. */
inline void cyclTime_fast_MinMaxTime_emC(MinMaxTime_emC* thiz, int time)        
{ uint cyclTime = (uint)((time) - thiz->_lastTime); 
  thiz->ct +=1; 
  thiz->actCyclTime = cyclTime;  
  if(cyclTime > thiz->maxCyclTime && cyclTime < (thiz->midCyclTime >>9)) { thiz->maxCyclTime = cyclTime; }  
  //if(cyclTime > thiz->maxmaxCyclTime){ thiz->maxmaxCyclTime = cyclTime; } 
  if(cyclTime < thiz->minCyclTime && cyclTime > (thiz->midCyclTime >>11)){ thiz->minCyclTime = cyclTime; }  
  //if(cyclTime < thiz->minminCyclTime){ thiz->minminCyclTime = cyclTime; } 
  thiz->midCyclTime += (cyclTime - (thiz->midCyclTime >>10));            
  thiz->_lastTime = time;                  
}


/**With given time. */
inline void set_MinMaxCalcTime_emC(MinMaxCalcTime_emC* thiz, int timeStart, int time)
{ uint calcTime = (uint)(time - timeStart); 
  thiz->actCalcTime = calcTime;  
  if(calcTime > thiz->maxCalcTime) { thiz->maxCalcTime = calcTime; }  
  if(calcTime < thiz->minCalcTime || thiz->minCalcTime == 0) { thiz->minCalcTime = calcTime; }
  thiz->midCalcTime += (calcTime - (thiz->midCalcTime >>10));            
}

/**With given time. */
inline void calcTime_MinMaxTime_emC(MinMaxTime_emC* thiz, int time)
{
  set_MinMaxCalcTime_emC(&thiz->calc, time, thiz->_lastTime);
}

/**Stores middle value of difference time in any variable, without min and max.
* @param VAR variable to store middle time 
*/
#define mesTimeMid_I_MinMaxTime_emC(thiz, time, VAR, VARMID)        \
{ VAR = (time) - (thiz)->_lastTime; \
  VARMID += VAR - (VARMID >>10);            \
}

/**Stores difference time in any variable, without min and max. 
* @param VAR variable to store middle time 
*/
#define mesTime_I_MinMaxTime_emC(thiz, time, VAR)        \
{ VAR = (time) - (thiz)->_lastTime; \
}



typedef struct Clock_MinMaxTime_emC_t {

  union { ObjectJc object; } base;

  float microSecondsPerClock;

  int32 nrofSlices;

  /**3 nested instances for time measurements in 3 time slots. More are possible. */
  MinMaxTime_emC times[3];
} Clock_MinMaxTime_emC;

extern_C ClassJc const reflection_Clock_MinMaxTime_emC;

void ctor_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz, int nrofEntries);


void init_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz);


/**
 * @simulink Operation-FB, step-in.
 */
void startTime_Clock_MinMaxTime(int slice_param, float* time_y);

/**
* @simulink Operation-FB, step-in.
*/
void measTime_Clock_MinMaxTime(int slice_param, float* time_y);






#endif  //Headerguard
