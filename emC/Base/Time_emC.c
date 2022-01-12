#include <emC/Base/Time_emC.h>
#include <emC/Base/MemC_emC.h>

#ifdef DEF_REFLECTION_FULL
  //Note: only for full reflection the const ClassJc refl_... should be compiled 
  //to found by the linker for references to this struct. 
  //They are unecessary for initializations because of the data instances do not based on ObjectJc.
  #include <emC/Base/genRefl/Time_emC.crefl>
  #include <emC/OSAL/genRefl/os_time.crefl>  //include here, different Implementations on osal level.
#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_Clock_MinMaxTime_emC)
  ClassJc const refl_Clock_MinMaxTime_emC = INIZ_ClassJc(refl_Clock_MinMaxTime_emC, "Clock_MinMaxTime_emC");
#endif


#include <emC/OSAL/os_time.h>

#ifndef microsecondsPerClock_Time_emC  //can be a const literal as macro
float microsecondsPerClock_Time_emC = 0;

int clocksPerMicro_Time_emC = 0;

float clocksFloatPerMicro_Time_emC = 0;
#endif


OS_TimeStamp* ctorM_OS_TimeStamp  (  MemC mem)
{ int size = mem.val;
  if (size < (int)sizeof(OS_TimeStamp))
  { THROW_s0n(IllegalArgumentException, "OS_TimeStamp with fault size", size, 0);
    return null;
  }
  else {
    OS_TimeStamp* ythis = ADDR_MemC(mem, TimeAbs_emC);
    ythis->time_sec = 0;
    ythis->time_nsec = 0;
    return ythis;
  }
}


void ctor_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz, int nrofEntries) {
  
  //int size = sizeof(*thiz) + sizeof(thiz->times) * (nrofEntries - ARRAYLEN_emC(thiz->times));
  CTOR_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz), refl_Clock_MinMaxTime_emC, 0);
  thiz->nrofSlices = nrofEntries;
}


#ifndef microsecondsPerClock_Time_emC  //can be a const literal as macro
bool measureClock_Time_emC(int meastime) { 
  float tclock;
  int startTime, endTime;
  int time = os_milliTime();
  int32_t dclock = 0;
  while(time == (startTime = os_milliTime()));  //wait till os_milliTime is changed, begin of a new millisec
  int clockstart = getClockCnt_Time_emC();
  if(meastime > 10) {
    os_delayThread(meastime - 10);   //wait for other threads to action.
  }
  int32 clockend;
  while((( endTime = os_milliTime()) - startTime) < meastime){} //wait till os_milliTime is changed second.
  { clockend = getClockCnt_Time_emC();
    dclock = clockend - clockstart;    //number of clocks
    tclock = 1000.0f * (float)(endTime - startTime) / dclock;
  }
  microsecondsPerClock_Time_emC = tclock;
  clocksFloatPerMicro_Time_emC = (dclock / 1000000.0f);
  clocksPerMicro_Time_emC = (int)(clocksFloatPerMicro_Time_emC+0.5f);  //round up and down, it is a less number.
  if((endTime - startTime) > 1000) return false;  //non exact 1 sec
  else return true;
}  
#endif




void init_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz) {
  //thiz->microSecondsPerClock = 
  measureClock_Time_emC(1000);
}



