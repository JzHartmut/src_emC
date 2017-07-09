#ifndef __fw_handle_ptr64_h__
#define __fw_handle_ptr64_h__
/**This headerfile contains some definitions and static operations which are used to translate a 64-bit-pointer to a handle.
 * The handle is 32 bit. For a 32-bit-target system this translation is not necessary, because the 32-bit-ptr can be used as handle value immediately.
 * The translation of a pointer to a handle allows to use a 32-bit-connection between independent function blocks, which works with the same memory.
 * Especially it is firstly used for simulink S-functions running on the 64-bit-PC platform.
 */
//#include <OSAL/os_sharedmem.h> 
#include <compl_adaption.h>
#include <string.h>


typedef struct Entry_Handle2Ptr_t
{ union{ void* ptr; uint64 iptr; } p; 
  char name[32];
} Entry_Handle2Ptr;


/**This is the association table from handle to a 64-bit-memory address.
 * The instance of this type is present via shared memory in any S-function which uses this system.
 */
typedef struct Handle2Ptr_t{
  uint32 ixEnd; uint32 size;
  Entry_Handle2Ptr e[100];  //The size of the array is greater, adequate allocated shared memory.
} Handle2Ptr;

/**This pointer will be set with the shared memory address. */
extern Handle2Ptr* handle2Ptr;






/**Initializes. This routine should be invoked one time on startup. */
const char* init_Handle2Ptr(int nrofEntries);



/**Sub routine to register a pointer in the shared memory data.
 * @return the handle.
 */
#ifdef __HandlePtr64__
  #ifndef DEFINED_nrEntries_Handle2Ptr
    #define DEFINED_nrEntries_Handle2Ptr 1000
  #endif

  /**Invocation of INIT can be set on any location more than once, the first initializes. */
  #define INIT_Handle2Ptr() if(handle2Ptr ==null) { init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr); } 

  /**Sets the pointer and gets the handle. 
   * If the ptr is registered already, it is okay, */ 
  const char* setPtr_Handle2Ptr(void* ptr, char const* name, uint32* dstHandle);

  /**Sets the pointer to a determined handle. 
   * If the same ptr is registered already, it is okay, 
   * If the handle is used with another pointer already, an error message is returned.
   */ 
  const char* setPtrHandle_Handle2Ptr(void* ptr, uint32 handle, char const* name);

  /**Gets the handle for a given ptr. 
   * If the handleis unknown, dstHandle = 0 and an error is returned. */ 
  const char* handle_Handle2Ptr(void* ptr, uint32* dstHandle);

#else
  /**Invocation of INIT is empty because there is not Handle2Ptr. */
  #define INIT_Handle2Ptr(nrofEntries)  
  #define setPtr_Handle2Ptr(PTR, NAME, H) (*H=PTR, null)
  #define handle_Handle2Ptr(PTR, H) (*H=PTR, null)
#endif




#ifdef __HandlePtr64__
  const char* getPtr_Handle2Ptr(uint32 handle, void** dst);
  //#define PTR_Handle2Ptr(handle, TYPE) (handle > =0 && handle < handle2Ptr->ixEnd ? (TYPE*) handle2Ptr->ptr[handle] : null)
  #define PTR_Handle2Ptr(handle, TYPE) ((TYPE*) handle2Ptr->e[handle].p.ptr)
#else
  #define getPtr_Handle2Ptr(H, DST) (*DST=H, null)
  #define PTR_Handle2Ptr(handle, TYPE) ((TYPE*) handle)
#endif


/**Closes. This routine should be invoked one time on shutdown. */
void close_Hande2Ptr();



#endif //__fw_handle_ptr64_h__
