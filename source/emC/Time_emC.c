#include <emC/Time_emC.h>

#include <genRefl/emC/Time_emC.crefl>
#include <OSAL/os_time.h>


static Clock_MinMaxTime_emC* timeMeas = null;

void ctor_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz, int nrofEntries) {
  
  int size = sizeof(*thiz) + sizeof(thiz->times) * (nrofEntries - ARRAYLEN_emC(thiz->times));
  initReflection_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz), &reflection_Clock_MinMaxTime_emC, 0);
  thiz->nrofSlices = nrofEntries;
}



void init_Clock_MinMaxTime_emC(Clock_MinMaxTime_emC* thiz) {
  thiz->microSecondsPerClock = os_measureClock();
}



