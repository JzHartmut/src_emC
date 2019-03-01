#include <emC/Handle_ptr64_emC.h>
#include <applstdef_emC.h>
#ifdef __SIMULINK_SFN__
  #include <OSAL/os_sharedmem.h> 
#else
  #include <stdlib.h>
#endif
#include <emC/SimpleC_emC.h>
#include <emC/time_emC.h>
#include <OSAL/os_mem.h>
#include <OSAL/os_time.h>


#ifdef __HandlePtr64__  //compile only if operations are not replaced by macros.
/*The number of entries in the pointer table. 
 */
//#define zEntries_Handle2Ptr 1000
/**This pointer will be set with the shared memory address.
 */
Handle2Ptr* handle2Ptr = null;



/**The length of the shared memory in byte. */
//TODO variable size of the Ptr2Handle via parameter or Simulink-Global variable. Then calculate it. The zEntries_Handle2Ptr is any number.
//#define length_Handle2Ptr ((zEntries_Handle2Ptr - 100) * sizeof(void*) + sizeof(Handle2Ptr))


/**Organization structure for the shared memory. */
#ifdef __SIMULINK_SFN__
  SharedMem_OSAL shMemHandle2Ptr = {0};
#endif

#ifdef DEFINED_nrEntries_Handle2Ptr

//char const* errorInit_Hand2Ptr = init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr);

#endif


/**Initializes. This routine should be invoked one time on startup. */
const char* init_Handle2Ptr(int nrofEntries)
{   
  int sizeAlloc = sizeof(Handle2Ptr)  //defined length 
    + ((nrofEntries - ARRAYLEN_SimpleC(handle2Ptr->e)) //additional entries 
      * sizeof(Entry_Handle2Ptr));
  #ifdef __SIMULINK_SFN__

    //===============Get the address of the structure to convert handle values to pointer===============================
    //Note: If more as one instance of this FB will be created, the mdlStart is invoked for any instance.
    //      But there is only one static shMemHandle2Ptr. The first mdlStart creates it. Don't call twice!
    //       
    //
    if(!os_isReadySharedMem(&shMemHandle2Ptr)) {  //only if it is not created already:
      MemC mHandle2Ptr = os_createOrAccessSharedMem(&shMemHandle2Ptr, "Smlk-SfuncHandle2Ptr-2017-02", sizeAlloc);
      handle2Ptr = PTR_OS_PtrValue(mHandle2Ptr, Handle2Ptr);
      if(!os_isReadySharedMem(&shMemHandle2Ptr) || handle2Ptr == null) {
        return "Handle2Ptr not possible, abort";
      }
    }
  #else  //else __SIMULINK_SFN__
    handle2Ptr = (Handle2Ptr*)malloc(sizeAlloc);
    memset(handle2Ptr, 0, sizeAlloc);
  #endif //__SIMULINK_SFN__
  if (handle2Ptr->size == 0 && handle2Ptr->sizeEntry == 0) {
    handle2Ptr->sizeEntry = sizeof(handle2Ptr->e[0]);
    handle2Ptr->sizeAll = sizeAlloc;
    handle2Ptr->size = nrofEntries;
    handle2Ptr->ixEnd = 1;                    // TODO AtomicAccess if mulitple cores run more instances of such routines.
  }
  if (handle2Ptr == null
    || handle2Ptr->size != nrofEntries
    || handle2Ptr->sizeEntry != sizeof(handle2Ptr->e[0])
    //|| handle2Ptr->sizeAll != sizeAlloc
    ) {
    return "Handle2Ptr faulty or size faulty, abort";
  }
  else {
    return null; //successfull
  }
}



/**Initializes. This routine should be invoked one time on startup. */
const char* initTimeMeas_Handle2Ptr(int nrofEntries) {
  char const* error = init_Handle2Ptr(nrofEntries);
  if(error) return error;
  if(strcmp(handle2Ptr->e[1].name, "__timeMeas")!=0) {  //possible that another dll has initialize already.
    Clock_MinMaxTime_emC* time = (Clock_MinMaxTime_emC*)os_allocMem(sizeof(Clock_MinMaxTime_emC) + (DEFINED_nrTimeMeas_Handle2Ptr * sizeof(MinMaxTime_emC)));
    ctor_Clock_MinMaxTime_emC(time, DEFINED_nrTimeMeas_Handle2Ptr);
    uint32 handle;
    registerPtr_Handle2Ptr(time, "__timeMeas", &handle);
    ASSERT(handle == 1);
  }
  return null;
}


void startTime_Clock_MinMaxTime(int slice_param, float* time_y) {
  STACKTRC_ENTRY("startTime_Clock_MinNaxTime");
  Clock_MinMaxTime_emC* thiz = (Clock_MinMaxTime_emC*)ptr_Handle2Ptr(1);
  checkStrict_ObjectJc(&thiz->base.object, 0, 0, &reflection_Clock_MinMaxTime_emC, _thCxt);
  if (thiz->microSecondsPerClock == 0) {
    init_Clock_MinMaxTime_emC(thiz);
  }
  if(slice_param < 0 || slice_param >= thiz->nrofSlices) {
    THROW_s0(IllegalArgumentException, "faulty slice_param=", slice_param, thiz->nrofSlices);
    slice_param = thiz->nrofSlices -1;
  }
  cyclTime_MinMaxTime_emC(&thiz->times[slice_param], os_getClockCnt());
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
  mesTime_I_MinMaxTime_emC(&thiz->times[slice_param], os_getClockCnt(), timestep);
  *time_y = thiz->microSecondsPerClock * timestep;
}





void debug_Handle2Ptr(uint32 handle, int32 dbg1, int32 dbg2, char const* dbginfo) {
  if (handle2Ptr == null) { init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr); }
  if(handle >=0 && handle < handle2Ptr->size) {
    if(dbg1 !=0) { handle2Ptr->e[handle].dbg1 = dbg1; }
    if(dbg2 !=0) { handle2Ptr->e[handle].dbg2 = dbg2; }
    if(dbginfo !=null) { handle2Ptr->e[handle].dbginfo = dbginfo; }
  }
}


/**Sub routine to get a handle from a registered pointer in the shared memory data.
 * @return the handle.
 */
const char* handle_Handle2Ptr(void const* ptr, uint32* dstHandle) {
  bool found = false;
  if (handle2Ptr == null){ return "Handle2Ptr: not initialized"; }
  else {
    uint32 ixEnd = handle2Ptr->ixEnd;
    uint32 ix;
    for(ix = 0; ix < ixEnd; ++ix) {
      if(handle2Ptr->e[ix].p.ptr == ptr) { 
        found = true;
        *dstHandle = ix;
        break;
      }
    } 
    if(!found) { //onyl if not found, all checked:
      *dstHandle = 0;
      return "Handle2Ptr: ptr not found, set handle = 0";
    } else {  
      return null;
    }
  }
}



uint32 PRIV_retHandle_Handle2Ptr(void const* ptr) {
  uint32 dstHandle = 0;
  bool found = false;
  if (handle2Ptr == null) { init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr); }
  {
    uint32 ixEnd = handle2Ptr->ixEnd;
    uint32 ix;
    for(ix = 0; ix < ixEnd; ++ix) {
      if(handle2Ptr->e[ix].p.ptr == ptr) { 
        found = true;
        dstHandle = ix;
        break;
      }
    } 
  }
  return dstHandle;
}




/**Sub routine to register a pointer in the shared memory data.
 * @return the handle.
 */
const char* registerPtr_Handle2Ptr(void* ptr, char const* name, uint32* dstHandle) {
  bool found = false;
  if (ptr == null) {
    if(dstHandle) { *dstHandle = -1; }
    return null;
  }
  if (handle2Ptr == null) { return "Handle2Ptr: not initialized"; }
  else {
    uint32 ixEnd = handle2Ptr->ixEnd;
    uint32 ixFree = 0;
    uint32 ix;
    for(ix = 1; ix < ixEnd; ++ix) {
      if(handle2Ptr->e[ix].p.ptr == ptr) { 
        found = true;
        break;
      }
      else if (handle2Ptr->e[ix].p.ptr == null) {
        ixFree = ix;
      }
    } 
    //Note: if the ptr was found, return in for!
    if (found) {
      if(dstHandle) { *dstHandle = ix; }
    }
    else { //!found, onyl if not found, all checked:
      if(ixFree == 0 && ix >= handle2Ptr->size) {
        return "Handle2Ptr: no more space";
      }
      if (ixFree == 0) {
        ixFree = ix;   //append on end
        handle2Ptr->ixEnd = ix + 1;    //TODO AtomicAccess if mulitple cores run more instances of such routines. 
      }
      handle2Ptr->e[ixFree].p.ptr = ptr;
      strncpy(handle2Ptr->e[ixFree].name, name, sizeof(handle2Ptr->e[ix].name));
      if(dstHandle) { *dstHandle = ixFree; }
    }
    return null;
  }
}




const char* setPtrHandle_Handle2Ptr(void* ptr, uint32 handle, char const* name)
{
  if (handle2Ptr == null) return "Handle2Ptr: not initialized";
  if(handle2Ptr->e[handle].p.ptr == null) {
    handle2Ptr->e[handle].p.ptr = ptr;
    strncpy(handle2Ptr->e[handle].name, name, sizeof(handle2Ptr->e[handle].name));
    return null;
  }
  else if( handle2Ptr->e[handle].p.ptr == ptr) {
    return null;
  } 
  else {
    return("Handle2Ptr: handle already used");
  }
}




const char* getPtr_Handle2Ptr(uint32 handle, void ** dst)
{
  if (handle2Ptr == null) { return "Handle2Ptr: not initialized"; }
  else if (handle == 0) { *dst = null; return null; }                 //handle 0 is pointer null
  else if (handle == (uint32)(-1)) { *dst = null /*(void*)-1*/; return null; } //special case: given but invalid pointer. 
  else if (handle >= handle2Ptr->size || handle < 0) { //jzTc: check valid handle, note: 0 gets null-Pointer
    return "Handle2Ptr: Handle faulty.";
  }
  else {
    *dst = handle2Ptr->e[handle].p.ptr;  //pointer from handle
    return null;
  }
}


void* ptr_Handle2Ptr(uint32 handle)
{
  if (handle2Ptr == null) { init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr); }
  if (handle == (uint32)(-1)) { return null; } //special case: null should be.
  else if (handle >= handle2Ptr->size) { //jzTc: check valid handle, note: -1 gets null-Pointer
                                         //PRINTX2(0, "PRIV_retPtr_Handle2Ptr faulty Handle = %d\n", handle);
    return null; //"Handle2Ptr: Handle faulty.";
  }
  else {
    //PRINTX2(0, "PRIV_retPtr_Handle2Ptr ok Handle = %d\n", handle);
    return handle2Ptr->e[handle].p.ptr;  //pointer from handle
  }
}

void* clearHandle_Handle2Ptr(uint32 handle)
{
  //if (handle2Ptr == null) { init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr); }
  if (handle == (uint32)(-1)) { return null; } //special case: null should be.
  else if (handle >= handle2Ptr->size) { //jzTc: check valid handle, note: -1 gets null-Pointer
                                         //PRINTX2(0, "PRIV_retPtr_Handle2Ptr faulty Handle = %d\n", handle);
    return null; //"Handle2Ptr: Handle faulty.";
  }
  else {
    //PRINTX2(0, "PRIV_retPtr_Handle2Ptr ok Handle = %d\n", handle);
    void* ret = handle2Ptr->e[handle].p.ptr;  //pointer from handle
    handle2Ptr->e[handle].p.ptr = null;
    handle2Ptr->e[handle].dbginfo = null;
    handle2Ptr->e[handle].dbg2 = 0;
    memset(handle2Ptr->e[handle].name, 0, sizeof(handle2Ptr->e[handle].name));
    return ret;
  }
}


//#define __SIMULINK_SFN__

void close_Hande2Ptr()
{
  #ifdef __SIMULINK_SFN__
    //close the sharedmem handle:
    //Note: If more as one instance of this FB was created, the mdlTerminate is invoked for any instance.
    //      But there is only one static shMemHandle2Ptr. The first mdlTerminate removes it.
    //       
    if(handle2Ptr !=null && os_isReadySharedMem(&shMemHandle2Ptr)) {
      int sizeData =  handle2Ptr->size * sizeof(Entry_Handle2Ptr);
      bool clear = true;
      for (uint ix = 0; ix < handle2Ptr->size; ++ix) {
        if (handle2Ptr->e[ix].p.ptr != null && strcmp(handle2Ptr->e[ix].name, "__timeMeas")!=0) {
          clear = false;
          break;
        }
      }
      if(clear) {
        if(strcmp(handle2Ptr->e[1].name, "__timeMeas")==0) {
          os_freeMem(handle2Ptr->e[1].p.ptr);
        }
        memset(handle2Ptr->e, 0, sizeData);  //in case of non deleted shared mem: Simulink is closed, use the handles newly.
        handle2Ptr->ixEnd = 1;
        os_closeSharedMem(&shMemHandle2Ptr);
        handle2Ptr = null;  //should created newly.
      }
    } //else: it is cleared and closed already.
  #else  //else not __SIMULINK_SFN__
    free(handle2Ptr);
  #endif //__SIMULINK_SFN__

}
 
#endif  //__HandlePtr64__
