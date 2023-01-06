#include <emC/Base/Handle_ptr64_emC.h>
#include <applstdef_emC.h>
#ifdef __HandlePtr64_SharedMem__
  //If the Handle2Ptr should be used in dispersed dll where no common global reference is possible,
  //Or for some other reason,  create the Handle2Ptr-table in shared Memory. 
  //The referenced data can be, but not necessary located in any shared memory too. It depends on theire usage.
  #include <emC/OSAL/os_sharedmem.h> 
  #include <emC/OSAL/os_mem.h>
#else
  #include <stdlib.h>  //malloc
#endif



#ifdef DEF_HandlePtr64  //compile only if operations are not replaced by simple macros. Especially for 64-bit pointer.


#ifdef DEFINED_nrEntries_Handle2Ptr
  /**Invocation of INIT can be set on any location more than once, the first initializes. */
  #define INIT_Handle2Ptr() (handle2Ptr !=null || init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr) == null) 
#else 
  //If the nrEntries is not predefined, the init_Handle2Ptr should be done already before first usage. Exception if not done. 
  bool throwNotInit(){ THROW_s0n(IllegalStateException, "Handle2Ptr not initialized, no default size knwon", 0, 0); return false; }
  #define INIT_Handle2Ptr() (handle2Ptr !=null || throwNotInit())
#endif





/**This pointer will be set with the shared memory address if the shared memory is created already.
 * The pointer itself, the address of the shared memory, is static global for the linked unit (dll, exe).
 * If the shared memory is created or found already, this reference is not null.
 */
Handle2Ptr* handle2Ptr = null;



/**The length of the shared memory in byte. */

/**Organization structure for the shared memory global for exe or dll. */
#ifdef __HandlePtr64_SharedMem__
  SharedMem_OSAL shMemHandle2Ptr = {0};
#endif



/**Initializes. This routine should be invoked one time on startup. */
const char* init_Handle2Ptr(uint nrofEntries)
{ if(handle2Ptr !=null) return null; //repeated init call.
  STACKTRC_ENTRY("init_Handle2Ptr");  
  char const* error = null;
  //
  int sizeAlloc = sizeof(Handle2Ptr)  //defined length 
    + ((nrofEntries - (sizeof(handle2Ptr->e) / sizeof(handle2Ptr->e[0]))) //additional entries 
      * sizeof(Entry_Handle2Ptr));
  #ifdef __HandlePtr64_SharedMem__
    //For Simulink S-Functions there is no global central data available because any C-routine has its own dll.
    //Hence use shared memory. 
    if(!os_isReadySharedMem(&shMemHandle2Ptr)) {  //only if it is not created already:
      MemC mHandle2Ptr = os_createOrAccessSharedMem(&shMemHandle2Ptr, "Smlk-SfuncHandle2Ptr-2017-02", sizeAlloc);
      handle2Ptr = PTR_MemC(mHandle2Ptr, Handle2Ptr);
      if(!os_isReadySharedMem(&shMemHandle2Ptr) || handle2Ptr == null) {
        error = "Handle2Ptr not possible, abort";
        THROW_s0(IllegalArgumentException, error, sizeAlloc, 0);
      }
    }
  #else  //else __HandlePtr64_SharedMem__
    //normal system without shared memory and without algorithm in dll
    handle2Ptr = (Handle2Ptr*)malloc(sizeAlloc);
    if(handle2Ptr == null) {
      error = "no memory for Handle2Ptr";
      THROW_s0(IllegalArgumentException, error, sizeAlloc, 0);
    } else {
      memset(handle2Ptr, 0, sizeAlloc);
    }
  #endif //__HandlePtr64_SharedMem__
  if(error == null) {
    if (handle2Ptr->size == 0 && handle2Ptr->sizeEntry == 0) {
      //it is newly created here, then initialize. 
      handle2Ptr->sizeEntry = sizeof(handle2Ptr->e[0]);  //size of one entry for check 
      handle2Ptr->sizeAll = sizeAlloc;
      handle2Ptr->size = nrofEntries;
      handle2Ptr->ixEnd = 1;                    // TODO AtomicAccess if mulitple cores run more instances of such routines.
    }
    if ( handle2Ptr->size != nrofEntries
      || handle2Ptr->sizeEntry != sizeof(handle2Ptr->e[0])
      ) {
      THROW_s0(IllegalArgumentException, "Handle2Ptr faulty or size faulty, abort", (int)(intptr_t)handle2Ptr, handle2Ptr->size);
      STACKTRC_RETURN "Handle2Ptr faulty or size faulty, abort";
    }
  }
  STACKTRC_RETURN error;  //null if successfull, error only if THROW is not active
}






void debug_Handle2Ptr(uint32 handle, int32 dbg1, int32 dbg2, char const* dbginfo) {
  if (INIT_Handle2Ptr() && handle >=0 && handle < handle2Ptr->size) {
    if(dbg1 !=0) { handle2Ptr->e[handle].dbg1 = dbg1; }
    if(dbg2 !=0) { handle2Ptr->e[handle].dbg2 = dbg2; }
    if(dbginfo !=null) { handle2Ptr->e[handle].dbginfo = dbginfo; }
  }
}


uint32 handle_Handle2Ptr(void const* ptr) {
  uint32 dstHandle = 0;
  if (ptr == null) {
    return -1;    //The value -1 as handle is a null-Pointer. 0 is a unknwon handle.
  }
  if (INIT_Handle2Ptr()) {
    bool found = false;
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
uint32 registerPtr_Handle2Ptr(void* ptr, char const* name) {
  uint32 dstHandle = 0;
  bool found = false;
  if (ptr == null) {
    return -1;    //The value -1 as handle is a null-Pointer. 0 is a unknwon handle.
  }
  STACKTRC_ENTRY("registerPtr_Handle2Ptr");
  if(INIT_Handle2Ptr()) {
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
      dstHandle = ix;
    }
    else { //!found, onyl if not found, all checked:
      if(ixFree == 0 && ix >= handle2Ptr->size) {
        THROW_s0(IllegalStateException, "Handle2Ptr: no more space", handle2Ptr->size, 0);
      } else {
        if (ixFree == 0) {
          ixFree = ix;   //append on end
          handle2Ptr->ixEnd = ix + 1;    //TODO AtomicAccess if mulitple cores run more instances of such routines. 
        }
        handle2Ptr->e[ixFree].p.ptr = ptr;
        strncpy(handle2Ptr->e[ixFree].name, name, sizeof(handle2Ptr->e[ix].name));
        dstHandle = ixFree; 
      }
    }
  }
  STACKTRC_RETURN dstHandle;
}




void* ptr_Handle2Ptr(uint32 handle)
{ void* ret = null;
  if (handle == (uint32)(-1)) { return null; } //special case: -1 gets null-Pointer
  else if (handle == (uint32)(-2)) { return INVALID_NOT_nullPTR_emC(void); } //special case: -2 gets 0xffffffff invalid-Pointer
  else if(INIT_Handle2Ptr()) {
    if (handle >= handle2Ptr->size) { //jzTc: check valid handle, 
      THROW_s0n(IllegalArgumentException, "Handle2Ptr: Handle faulty.", (int)handle, (int)handle2Ptr->size);   
    }
    else {
      ret = handle2Ptr->e[handle].p.ptr;  //pointer from handle
    }
  }
  return ret;
}



void* clearHandle_Handle2Ptr(uint32 handle)
{
  void* ptr = ptr_Handle2Ptr(handle);
  if(ptr !=null) {
    handle2Ptr->e[handle].p.ptr = null;
    handle2Ptr->e[handle].dbginfo = null;
    handle2Ptr->e[handle].dbg2 = 0;
    memset(handle2Ptr->e[handle].name, 0, sizeof(handle2Ptr->e[handle].name));
  }
  return ptr;
}



void close_Hande2Ptr()
{
  #ifdef __HandlePtr64_SharedMem__
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
  #else  //else not __HandlePtr64_SharedMem__
    free(handle2Ptr);
  #endif //__HandlePtr64_SharedMem__

}
 
#endif  //DEF_HandlePtr64
