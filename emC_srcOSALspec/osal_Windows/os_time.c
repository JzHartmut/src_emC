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
 * @content This file contains the implementation of os_time.h for MS-Windows.
 * @author Hartmut Schorrig
 * @version 0.81ad
 * list of changes:
 * 2007-10-01: JcHartmut creation
 *
 ****************************************************************************/
#include <applstdef_emC.h>
#include <emC/OSAL/os_time.h>

#undef INT32
#undef UINT32
#undef int64
#undef uint64

#include <wtypes.h>
#include <winbase.h>
#include <sys/timeb.h>

/**It is defined in Time_emC.c*/
extern float microsecondsPerClock_Time_emC;



int32 os_milliTime()
{
  struct _timeb systime;
  int32 milliseconds;
  _ftime_s(&systime);           //get the time in milliseconds from system.
  //overflow because seconds after 1970 are in range 0x40000000, it is ok:
  milliseconds = (int32)(systime.time * 1000);
  milliseconds += systime.millitm;
  return milliseconds;

}


int32 os_getSeconds()
{
  struct _timeb systime;
  _ftime_s(&systime);           //get the time in milliseconds from system.
  //overflow because seconds after 1970 are in range 0x40000000, it is ok:
  return systime.time;

}



OS_TimeStamp os_getDateTime()
{ struct _timeb systime;
  OS_TimeStamp pDateTime;
  _ftime_s(&systime);

  pDateTime.time_sec = systime.time;
  pDateTime.time_nsec = (int32)(systime.millitm) * 1000000L;
  
  return pDateTime;
}


int32 os_microTime ( void)
{
	struct _timeb currTime;
	_ftime_s(&currTime);
	return (int32)(currTime.millitm)*1000L;
}


/**Gets a circular time information in clocks of the system.
* @return a relativ value, the value can be used only for differnces.
* The step-width of the return value depends from the CPU-clock.
* The value should only be used for comparing times.
*/
int32 getClockCnt_Time_emC ( void)
{
  LARGE_INTEGER performanceCount;
  if(QueryPerformanceCounter(&performanceCount))
  { return (int32)performanceCount.QuadPart; //QuadPart see winnt.h of Visual Studio 6
  }          
  else
  { int error =GetLastError();
  //printf("\nFATAL ERROR QueryPerformanceCounter: %d", error);
  return -1;
  }
}


/**Gets a circular time information in clocks of the system.
* @return a relativ value, the value can be used only for differnces.
* The step-width of the return value depends from the CPU-clock.
* The value should only be used for comparing times.
*/
int64_t os_getLongClockCnt(void)
{
  LARGE_INTEGER performanceCount;
  if(QueryPerformanceCounter(&performanceCount))
  { return (int64_t)performanceCount.QuadPart; //QuadPart see winnt.h of Visual Studio 6
  }          
  else
  { int error =GetLastError();
    //printf("\nFATAL ERROR QueryPerformanceCounter: %d", error);
    return -1;
  }
}



void os_delayThread(int milliseconds) { 
  if(milliseconds < 50 && microsecondsPerClock_Time_emC != 0) {
    int clocks = (int)(milliseconds * 1000.0f/microsecondsPerClock_Time_emC);
    os_delayThreadClocks(clocks);
  }
  else {
    Sleep(milliseconds);
  }
}



void os_delayThreadClocks(int timeOutClocks) {
  int clockstart = getClockCnt_Time_emC();
  do { //at least on sleep, important in debug
    Sleep(0);   //forces a thread change if necessary. Needs some time.
  } while ((getClockCnt_Time_emC() - clockstart) < timeOutClocks); //waits till clockCount.
}


