#ifndef __fw_handle_ptr64_TimeMeas_h__
#define __fw_handle_ptr64_TimeMeas_h__
#include <emC/Handle_ptr64_emC.h>
#ifdef __HandlePtr64__
  #ifndef DEFINED_nrTimeMeas_Handle2Ptr      //should be defined in applstdef_emC with another value.
    #define DEFINED_nrTimeMeas_Handle2Ptr 3
  #endif
 /**Initializes the Handle2Ptr mechanism with ix=1 for time measurement.
  * It is used for Simulink especially.
  * Invocation of INIT can be set on any location more than once, the first initializes. */
  #define INIT_TimeMeas_Handle2Ptr() if(handle2Ptr ==null) { initTimeMeas_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr); } 




/**Initializes. This routine should be invoked one time on startup. */
extern_C const char* initTimeMeas_Handle2Ptr(int nrofEntries);


#else

#endif //__HandlePtr64__

#endif //__fw_handle_ptr64_TimeMeas_h__
