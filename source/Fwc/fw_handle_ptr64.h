#ifndef __fw_handle_ptr64_h__
#define __fw_handle_ptr64_h__
/**This headerfile contains some definitions and static operations which are used to translate a 64-bit-pointer to a handle.
 * The handle is 32 bit. For a 32-bit-target system this translation is not necessary, because the 32-bit-ptr can be used as handle value immediately.
 * The translation of a pointer to a handle allows to use a 32-bit-connection between independent function blocks, which works with the same memory.
 * Especially it is firstly used for simulink S-functions running on the 64-bit-PC platform.
 */
#include <OSAL/os_sharedmem.h> 
#include <string.h>


/**This is the association table from handle to a 64-bit-memory address.
 * The instance of this type is present via shared memory in any S-function which uses this system.
 */
typedef struct Handle2Ptr_t{
  uint32 ixEnd; uint32 size;
  void* ptr[100];  //The size of the array is greater, adequate allocated shared memory.
} Handle2Ptr;







/**Initializes. This routine should be invoked one time on startup. */
const char* init_Handle2Ptr(int nrofEntries);



/**Sub routine to register a pointer in the shared memory data.
 * @return the handle.
 */
const char* getHandle_Handle2Ptr(void* ptr, uint32* dstHandle);






const char* getPtr_Handle2Ptr(uint32 handle, void** dst);



/**Closes. This routine should be invoked one time on shutdown. */
void close_Hande2Ptr();



#endif //__fw_handle_ptr64_h__
