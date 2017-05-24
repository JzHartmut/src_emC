#include <Fwc/fw_handle_ptr64.h>


/*The number of entries in the pointer table. 
 */
#define zEntries_Handle2Ptr 1000
/**This pointer will be set with the shared memory address.
 */
Handle2Ptr* handle2Ptr;



/**The length of the shared memory in byte. */
//TODO variable size of the Ptr2Handle via parameter or Simulink-Global variable. Then calculate it. The zEntries_Handle2Ptr is any number.
#define length_Handle2Ptr ((zEntries_Handle2Ptr - 100) * sizeof(void*) + sizeof(Handle2Ptr))


/**Organization structure for the shared memory. */
SharedMem_OSAL shMemHandle2Ptr;





/**Initializes. This routine should be invoked one time on startup. */
const char* init_Handle2Ptr(int nrofEntries)
{   //===============Get the address of the structure to convert handle values to pointer===============================
    //Note: If more as one instance of this FB will be created, the mdlStart is invoked for any instance.
    //      But there is only one static shMemHandle2Ptr. The first mdlStart creates it. Don't call twice!
    //       
    //
    if(!os_isReadySharedMem(&shMemHandle2Ptr)) {  //only if it is not created already:
      MemC mHandle2Ptr = os_createOrAccessSharedMem(&shMemHandle2Ptr, "Smlk-SfuncHandle2Ptr-2017-02", length_Handle2Ptr);
      handle2Ptr = PTR_OS_PtrValue(mHandle2Ptr, Handle2Ptr);
      if(!os_isReadySharedMem(&shMemHandle2Ptr) || handle2Ptr == null) {
        return "SharedMem for Handle to Pointer not possible, abort";
      }
      if(handle2Ptr->size == 0){ 
        handle2Ptr->size = zEntries_Handle2Ptr; 
        handle2Ptr->ixEnd = 1;                    // TODO AtomicAccess if mulitple cores run more instances of such routines.
      }
    }
    if(handle2Ptr == null || handle2Ptr->size != 1000) {
      return "SharedMem for Handle to Pointer faulty or size faulty, abort";
    }
    return null; //successfull
}



/**Sub routine to register a pointer in the shared memory data.
 * @return the handle.
 */
const char* getHandle_Handle2Ptr(void* ptr, uint32* dstHandle) {
  bool found = false;
  if (handle2Ptr == null) return "SharedMem for Handle to Pointer: not initialized";
  uint32 ixEnd = handle2Ptr->ixEnd;
  uint32 ix;
  for(ix = 0; ix < ixEnd; ++ix) {
    if(handle2Ptr->ptr[ix] == ptr) { 
      found = true;
      break;
    }
  } 
  //Note: if the ptr was found, return in for!
  if(!found) { //onyl if not found, all checked:
    if(ix >= handle2Ptr->size) {
      return "SharedMem for Handle to Pointer: no more space: Sfunc=step_WaveMngIx_FB";
    }
    handle2Ptr->ixEnd = ix+1;    //TODO AtomicAccess if mulitple cores run more instances of such routines. 
    handle2Ptr->ptr[ix] = ptr;
  }  
  *dstHandle = ix;
  return null;
}






const char* getPtr_Handle2Ptr(uint32 handle, void** dst)
{
  if (handle2Ptr == null) return "SharedMem for Handle to Pointer: not initialized";
  if (handle >= handle2Ptr->ixEnd) { //jzTc: check valid handle, note: 0 gets null-Pointer
    return "Handle faulty, abort: Sfunc=step_WaveMng_FB";
  }
  *dst = handle2Ptr->ptr[handle];  //pointer from handle
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
    memset(handle2Ptr, 0, length_Handle2Ptr);  //in case of non deleted shared mem: Simulink is closed, use the handles newly.
    os_closeSharedMem(&shMemHandle2Ptr);
  } //else: it is cleared and closed already.

}
 

