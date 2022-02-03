#include <emC/Base/Handle_ptr64_TimeMeas_emC.h>
#include <applstdef_emC.h>
#include <emC/Base/SimpleC_emC.h>
#include <emC/Base/Time_emC.h>
#include <emC/OSAL/os_mem.h>
#include <emC/OSAL/os_time.h>


#ifdef DEF_HandlePtr64  //compile only if operations are not replaced by macros.

/**Initializes. This routine should be invoked one time on startup. */
const char* initTimeMeas_Handle2Ptr(int nrofEntries) {
  STACKTRC_ENTRY("initTimeMeas_Handle2Ptr");
  char const* error = init_Handle2Ptr(nrofEntries);
  if(error == null) {
    if(strcmp(handle2Ptr->e[1].name, "__timeMeas")!=0) {  //possible that another dll has initialize already.
      Clock_MinMaxTime_emC* time = (Clock_MinMaxTime_emC*)os_allocMem(sizeof(Clock_MinMaxTime_emC) + (DEFINED_nrTimeMeas_Handle2Ptr * sizeof(MinMaxTime_emC)));
      ctor_Clock_MinMaxTime_emC(time, DEFINED_nrTimeMeas_Handle2Ptr);
      uint32 handle = registerPtr_Handle2Ptr(time, "__timeMeas");
      ASSERT_emC(handle == 1, "initTimeMeas_Handle2Ptr should be the first handle", handle, 0);
    }
  }
  STACKTRC_RETURN error;
}

extern_C ClassJc const refl_Clock_MinMaxTime_emC;

void startTime_Clock_MinMaxTime(int slice_param, float* time_y) {
  STACKTRC_ENTRY("startTime_Clock_MinNaxTime");
  Clock_MinMaxTime_emC* thiz = (Clock_MinMaxTime_emC*)ptr_Handle2Ptr(1);
  CHECKstrict_ObjectJc(&thiz->base.obj, 0, refl_Clock_MinMaxTime_emC, 0);
  if (thiz->microSecondsPerClock == 0) {
    init_Clock_MinMaxTime_emC(thiz);
  }
  if(slice_param < 0 || slice_param >= thiz->nrofSlices) {
    THROW_s0(IllegalArgumentException, "faulty slice_param=", slice_param, thiz->nrofSlices);
    slice_param = thiz->nrofSlices -1;
  }
  cyclTime_MinMaxTime_emC(&thiz->times[slice_param], getClockCnt_Time_emC());
  *time_y = thiz->microSecondsPerClock * thiz->times[slice_param].midCyclTime;
  STACKTRC_RETURN;
}




void measTime_Clock_MinMaxTime(int slice_param, float* time_y) {
  Clock_MinMaxTime_emC* thiz = (Clock_MinMaxTime_emC*)ptr_Handle2Ptr(1); //don't check admissibility, it is checked in startTime_Clock_MinMaxTime already.
  if(slice_param < 0 || slice_param >= thiz->nrofSlices) {
    STACKTRC_ENTRY("startTime_Clock_MinNaxTime");
    THROW_s0(IllegalArgumentException, "faulty slice_param=", slice_param, thiz->nrofSlices);
    STACKTRC_LEAVE;
    slice_param = thiz->nrofSlices -1;
  }
  int timestep;
  mesTime_I_MinMaxTime_emC(&thiz->times[slice_param], getClockCnt_Time_emC(), timestep);
  *time_y = thiz->microSecondsPerClock * timestep;
}



#endif  //DEF_HandlePtr64
