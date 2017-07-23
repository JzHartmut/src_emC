#include <Fwc/fw_handle_ptr64.h>
#include <applstdefJc.h>
#include <OSAL/os_sharedmem.h> 
#include <Fwc/fw_SimpleC.h>

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
SharedMem_OSAL shMemHandle2Ptr = {0};

#ifdef DEFINED_nrEntries_Handle2Ptr

//char const* errorInit_Hand2Ptr = init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr);

#endif


/**Initializes. This routine should be invoked one time on startup. */
const char* init_Handle2Ptr(int nrofEntries)
{   //===============Get the address of the structure to convert handle values to pointer===============================
    //Note: If more as one instance of this FB will be created, the mdlStart is invoked for any instance.
    //      But there is only one static shMemHandle2Ptr. The first mdlStart creates it. Don't call twice!
    //       
    //
    if(!os_isReadySharedMem(&shMemHandle2Ptr)) {  //only if it is not created already:
      int sizeAlloc =  sizeof(Handle2Ptr)  //defined length 
                    + ((nrofEntries - ARRAYLEN_SimpleC(handle2Ptr->e)) //additional entries 
                      * sizeof(Entry_Handle2Ptr));
      MemC mHandle2Ptr = os_createOrAccessSharedMem(&shMemHandle2Ptr, "Smlk-SfuncHandle2Ptr-2017-02", sizeAlloc);
      handle2Ptr = PTR_OS_PtrValue(mHandle2Ptr, Handle2Ptr);
      if(!os_isReadySharedMem(&shMemHandle2Ptr) || handle2Ptr == null) {
        return "Handle2Ptr not possible, abort";
      }
      if(handle2Ptr->size == 0){ 
        handle2Ptr->size = nrofEntries; 
        handle2Ptr->ixEnd = 1;                    // TODO AtomicAccess if mulitple cores run more instances of such routines.
      }
    }
    if(handle2Ptr == null || handle2Ptr->size != 1000) {
      return "Handle2Ptr faulty or size faulty, abort";
    }
    return null; //successfull
}



/**Sub routine to get a handle from a registered pointer in the shared memory data.
 * @return the handle.
 */
const char* handle_Handle2Ptr(void* ptr, uint32* dstHandle) {
  bool found = false;
  if (handle2Ptr == null) return "Handle2Ptr: not initialized";
  uint32 ixEnd = handle2Ptr->ixEnd;
  uint32 ix;
  for(ix = 0; ix < ixEnd; ++ix) {
    if(handle2Ptr->e[ix].p.ptr == ptr) { 
      found = true;
      *dstHandle = ix;
      break;
    }
  } 
  //Note: if the ptr was found, return in for!
  if(!found) { //onyl if not found, all checked:
    *dstHandle = 0;
    return "Handle2Ptr: ptr not found, set handle = 0";
  }  
  return null;
}



/**Sub routine to register a pointer in the shared memory data.
 * @return the handle.
 */
const char* setPtr_Handle2Ptr(void* ptr, char const* name, uint32* dstHandle) {
  bool found = false;
  if (handle2Ptr == null) return "Handle2Ptr: not initialized";
  uint32 ixEnd = handle2Ptr->ixEnd;
  uint32 ix;
  for(ix = 0; ix < ixEnd; ++ix) {
    if(handle2Ptr->e[ix].p.ptr == ptr) { 
      found = true;
      break;
    }
  } 
  //Note: if the ptr was found, return in for!
  if(!found) { //onyl if not found, all checked:
    if(ix >= handle2Ptr->size) {
      return "Handle2Ptr: no more space: Sfunc=step_WaveMngIx_FB";
    }
    handle2Ptr->ixEnd = ix+1;    //TODO AtomicAccess if mulitple cores run more instances of such routines. 
    handle2Ptr->e[ix].p.ptr = ptr;
    strncpy(handle2Ptr->e[ix].name, name, sizeof(handle2Ptr->e[ix].name));
  }  
  *dstHandle = ix;
  return null;
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




const char* getPtr_Handle2Ptr(uint32 handle, void** dst)
{
  if (handle2Ptr == null) return "Handle2Ptr: not initialized";
  if (handle >= handle2Ptr->size || handle < 0) { //jzTc: check valid handle, note: 0 gets null-Pointer
    return "Handle2Ptr: Handle faulty.";
  }
  *dst = handle2Ptr->e[handle].p.ptr;  //pointer from handle
  return null;
}



/**Closes. This routine should be invoked one time on shutdown. */
void close_Hande2Ptr()
{
  //close the sharedmem handle:
  //Note: If more as one instance of this FB was created, the mdlTerminate is invoked for any instance.
  //      But there is only one static shMemHandle2Ptr. The first mdlTerminate removes it.
  //       
  if(os_isReadySharedMem(&shMemHandle2Ptr)) {
    int sizeData =  handle2Ptr->size * sizeof(Entry_Handle2Ptr);
    memset(handle2Ptr->e, 0, sizeData);  //in case of non deleted shared mem: Simulink is closed, use the handles newly.
    handle2Ptr->ixEnd = 0;
    os_closeSharedMem(&shMemHandle2Ptr);
  } //else: it is cleared and closed already.

}
 
#endif  //__HandlePtr64__
