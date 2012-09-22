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
#include <os_types_def.h>
#include <os_time.h>

#include <wtypes.h>
#include <winbase.h>
#include <sys/timeb.h>


int32 os_milliTime()
{
  struct _timeb systime;
  int32 milliseconds;
  _ftime(&systime);           //get the time in milliseconds from system.
  //overflow because seconds after 1970 are in range 0x40000000, it is ok:
  milliseconds = (int32)(systime.time * 1000);
  milliseconds += systime.millitm;
  return milliseconds;

}


int32 os_getSeconds()
{
  struct _timeb systime;
  _ftime(&systime);           //get the time in milliseconds from system.
  //overflow because seconds after 1970 are in range 0x40000000, it is ok:
  return systime.time;

}



OS_TimeStamp os_getDateTime()
{ struct _timeb systime;
  OS_TimeStamp pDateTime;
  _ftime(&systime);

  pDateTime.time_sec = systime.time;
  pDateTime.time_nsec = (int32)(systime.millitm) * 1000000L;
  
  return pDateTime;
}


int32 os_getMicroTime(void)
{
	struct _timeb currTime;
	_ftime(&currTime);
	return (int32)(currTime.millitm)*1000L;
}


/**Gets a circular time information in clocks of the system.
 * @return a relativ value, the value can be used only for differnces.
 * The step-width of the return value depends from the CPU-clock.
 * The value should only be used for comparing times.
 */
int32 os_getClockCnt(void)
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
 

void os_delayThread(int32_t milliseconds)
{ Sleep(milliseconds);
}

