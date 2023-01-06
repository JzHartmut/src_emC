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
 * 2012-04-05 Hartmut new: os_getSeconds(): seconds are able to process with a
 *   32-bit integer. They are supported in most of operation systems. It is the originally unix concept
 *   for the timestamp. It should be available if measurements of seconds are enough and proper to use.
 * 2010-03-01 Hartmut corr: int32_t getClockCnt_Time_emC(void) instead int64, it is enaugh and applicate-able to all systems.
 * 2010-02-26 Hartmut new: class MinMaxTime_emC os-independt, but useable at lo level.
 * 2010-02-26 Hartmut corr: ctor with return value
 * 2008-02-01: Hartmut creation 
 *
 ************************************************************************************************/
#ifndef __os_time_h__
#define __os_time_h__

#include <applstdef_emC.h>
//#include <emC/Base/MemC_emC.h>
#include <emC/Base/Time_emC.h>

extern_C_BLOCK_

/*@CLASS_C OS_TimeStamp @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#define OS_TimeStamp TimeAbs_emC
#define OS_TimeStamp_T TimeAbs_emC_T

//compatibility, 
#define OS_TimeStruct OS_TimeStamp

/**Initializes the timestamp with 0, it is a time 1. 1. 1970. */
//TimeAbs_emC* ctorM_TimeAbs_emC(MemC mem);

/**Initializes the timestamp with 0, it is a time 1. 1. 1970. */
#define INIT_TimeAbs_emC(THIS) (memset(&THIS, 0, sizeof(THIS)))

/**Initializes the timestamp with the current time. */
#define INIT_now_TimeAbs_emC(THIS, VALUE) (THIS = os_getDateTime())

/**Initializes the timestamp with the given time. */
#define INIT_time_TimeAbs_emC(THIS, SRC) (THIS = SRC)

/**Assigns the SRC to THIS. */
#define set_TimeAbs_emC(THIS, SRC) (THIS = SRC)

/**Gets the value of seconds of a OS_TimeStamp. Note: do not use the value itself because encapsulating. */
#define seconds_TimeAbs_emC(THIS) ((THIS).time_sec)

/**Gets the value of nanoseconds of a OS_TimeStamp. Note: do not use the value itself because encapsulating. */
#define nanoSeconds_TimeAbs_emC(THIS) ((THIS).time_nsec & mNanoSeconds_TimeAbs_emC)

#define isGPS_TimeAbs_emC(THIS) (((THIS).time_nsec & mLeapSeconds_TimeAbs_emC) != 0)

#define isImprecise_TimeAbs_emC(THIS) (((THIS).time_nsec & mCorrection_TimeAbs_emC) != 0)

/**Sets a GPS-Time-value to a OS_TimeStamp. 
 * The time from GPS positioning follows the TAI (InternationalAtomic Time), 
 * with a constant difference of 19 seconds, without any leap seconds. Why 19 seconds? It's historical.
 * In technical systems a strict uniformly continuous time counter is better to than the UTC.
 */
#define setGPS_TimeAbs_emC(THIS, SEC, NSEC) { (THIS).time_sec = (SEC); (THIS).time_nsec = (NSEC) | mLeapSeconds_TimeAbs_emC; }

/**Sets a UTC-Time-value to a OS_TimeStamp. 
 * UTC (= <a href="http://en.wikipedia.org/wiki/Coordinated_Universal_Time">Coordinated Universal Time</a> ) 
 * follows the caesium atomic clock, 
 * but it is coordinated with the earth rotation. respectively it follows the simple division 
 * of 1 year into 365 * 24* 3600 seconds and 366 * 24 * 3600 seconds in a leap year.
 * If leap seconds are occurred, the second count of UTC is the same for 2 seconds.
 * In computer systems, often UTC is used, because the unix-time also count simple seconds
 * without regarding of leap seconds. 
 */
#define setUTC_TimeAbs_emC(THIS, SEC, NSEC) { (THIS).time_sec = (SEC); (THIS).time_nsec = (NSEC); }


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


/**Gets the seconds after a base year. */
int32_t os_getSeconds(void);

/**Gets a circular time information in milliseconds.
 * @return a relativ value, the value can be used only for differnces  up to 23 days..
 */
int32_t os_milliTime(void); 
#define os_getMilliTime() os_milliTime();

/**Gets a circular time information in microseconds.
 * @return a relativ value, the value can be used only for differnces up to 35 min.
 */
int32_t os_microTime(void);
#define os_getMicroTime() os_microTime();
 
 


#define os_sleep(TIME) sleep_Time_emC(TIME);

#define os_delayThread(MILLISEC) sleep_Time_emC(MILLISEC)




_END_extern_C_BLOCK


/**Regard a special platform variant, which may define macros instead prototypes: */
#ifdef PLATFORM_os_time_h
#include "PLATFORM_os_time.h"
#endif

#endif //__os_time_h__
