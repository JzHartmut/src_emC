#include <emC/Base/Time_emC.h>

#ifdef DEF_REFLECTION_FULL
  //Note: only for full reflection the const ClassJc refl_... should be compiled 
  //to found by the linker for references to this struct. 
  //They are unecessary for initializations because of the data instances do not based on ObjectJc.
  #include <emC/Base/genRefl/Time_emC.crefl>
#elif defined(DEF_refl_Clock_MinMaxTime_emC)
  extern_C ClassJc const refl_Clock_MinMaxTime_emC;
#elif defined(DEF_ObjectJc_REFLREF)
  ClassJc const refl_Clock_MinMaxTime_emC = INIZ_ClassJc(refl_Clock_MinMaxTime_emC, "Clock_MinMaxTime_emC");
#endif


#include <emC/OSAL/os_time.h>


//static Clock_MinMaxTime_emC* timeMeas = null;


void ctor_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz, int nrofEntries) {
  
  //int size = sizeof(*thiz) + sizeof(thiz->times) * (nrofEntries - ARRAYLEN_emC(thiz->times));
  CTOR_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz), refl_Clock_MinMaxTime_emC, 0);
  thiz->nrofSlices = nrofEntries;
}


bool measureClock_Time_emC(int meastime) { 
  float tclock;
  int startTime, endTime;
  int time = os_milliTime();
  int32_t dclock = 0;
  while(time == (startTime = os_milliTime()));  //wait till os_milliTime is changed, begin of a new millisec
  int clockstart = os_getClockCnt();
  if(meastime > 10) {
    os_delayThread(meastime - 10);   //wait for other threads to action.
  }
  int32 clockend;
  while((( endTime = os_milliTime()) - startTime) < meastime){} //wait till os_milliTime is changed second.
  { clockend = os_getClockCnt();
    dclock = clockend - clockstart;    //number of clocks
    tclock = 1000.0f * (float)(endTime - startTime) / dclock;
  }
  microsecondsPerClock_Time_emC = tclock;
  clocksPerMicro_Time_emC = dclock / 1000000;
  clocksFloatPerMicro_Time_emC = (int)(dclock / 1000000.0f);
  if((endTime - startTime) > 1000) return false;  //non exact 1 sec
  else return true;
}  





void init_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz) {
  thiz->microSecondsPerClock = measureClock_Time_emC(1000);
}



