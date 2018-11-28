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


/**One Entry in the table of pointer [[Handle2Ptr]].
 */
typedef struct Entry_Handle2Ptr_t
{ union{ void* ptr; uint64 iptr; } p; 
  char name[32];
  int32 dbg1, dbg2;
  char const* dbginfo;

} Entry_Handle2Ptr;


/**This is the association table from handle to a 64-bit-memory address.
 * The instance of this type is present via shared memory in any S-function which uses this system.
 */
typedef struct Handle2Ptr_t{
  uint32 ixEnd; uint32 size;
  uint32 sizeEntry; uint32 sizeAll;
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

  /**Sets the pointer to a given handle. 
   * If the same ptr is registered already, it is okay, 
   * If the handle is used with another pointer already, an error message is returned.
   * 
   */ 
  const char* XXX_setPtrHandle_Handle2Ptr(void* ptr, uint32 handle, char const* name);

#else
#endif




#ifdef __HandlePtr64__
  /**Invocation of INIT can be set on any location more than once, the first initializes. */
  #define INIT_Handle2Ptr() if(handle2Ptr ==null) { init_Handle2Ptr(DEFINED_nrEntries_Handle2Ptr); } 

  /**Registeres the pointer and gets the handle. 
   * If the ptr is registered already, it is okay. The name will be ignored then, it returns the given handle. 
   */ 
  const char* registerPtr_Handle2Ptr(void* ptr, char const* name, uint32* dstHandle);
  //old: setPtr_Handle2Ptr

  void debug_Handle2Ptr(uint32 handle, int32 dbg1, int32 dbg2, char const* dbginfo);

  /**Gets the handle for a given and already registered pointer. 
   * If the pointer is unknown, dstHandle = 0 and an error is returned. */ 
  const char* handle_Handle2Ptr(void* ptr, uint32* dstHandle);

  /**Internal method for the macro [[HANDLE_Handle2Ptr]] */
  uint32 PRIV_retHandle_Handle2Ptr(void* ptr);

  /**Delivers the handle to the given pointer. 
   * This operation is intent to invoke in compiled sources where a error message is not able to process. 
   * An error is not expected. If any error occurs the return ptr is null. 
   */
  #define HANDLE_Handle2Ptr(PTR) PRIV_retHandle_Handle2Ptr(PTR) 


  /**This operation is intent to invoke in sources which contains an error message possibility with aborting,
   * especially in Simulink S-functions.
   * @param dst address, content will be set to null if handle == (uint)-1 = 0xffffffff. 
   * *      is set to null if return not null (error)
   * *      is set to the pointer appropriate to the handle.
   * @return null if no error, not null: an error message.  
   */
  const char* getPtr_Handle2Ptr(uint32 handle, void** dst);
  
  /**Internal method for the macro [[PTR_Handle2Ptr]] */
  void* PRIV_retPtr_Handle2Ptr(uint32 handle);
  
  /**Gets the pointer to a given handle. This operation is intent to invoke in compiled sources where a error message is not able to process. 
   * An error is not expected. If any error occurs the return ptr is null. 
   * This macro is used in the sources for compatibility wihth 32 bit target systems.
   */ 
  #define PTR_Handle2Ptr(handle, TYPE) ((TYPE*) PRIV_retPtr_Handle2Ptr(handle))
#else
  /**Invocation of INIT is empty because there is not Handle2Ptr. */
  #define INIT_Handle2Ptr()  
  
  /**Registeres the pointer and gets the handle.
   * For the 32 bit version the pointer are not registered, the pointer value is the handle.
   * @param PTR given pointer as void*
   * @param NAME unused here because nothing is registered.
   * @param H Address of the handle, type is uint32*. The handle will be set with the pointer value.
   * @return null, no error
   * If the ptr is registered already, it is okay. The name will be ignored then, it returns the given handle. 
   */ 
  #define registerPtr_Handle2Ptr(PTR, NAME, H) (*(H)=(uint32)(PTR), null)
  //old: setPtr_Handle2Ptr

  #define debug_Handle2Ptr(H, N1, N2, TEXT)  //empty.
  
  #define handle_Handle2Ptr(PTR, H) (*H=(uint32)PTR, null)

  /**Delivers the handle to the given pointer, only for 32-bit-Target system.
   * The handle is the same value as the 32 bit pointer. It is delivered as uint32.
   */
  #define HANDLE_Handle2Ptr(PTR) ((uint32)PTR) 
  /**This is the variant to get a pointer from handle for 32-bit-systems. The pointer is the same value as the handle.
   * The macro delivers null for 'no error'.
   * @param H handle as uint32 value. The value is the memory address.
   * @param P_PTR address of the pointer. The address should be given as type void**
   */  
  #define getPtr_Handle2Ptr(H, P_PTR) ( *(P_PTR)= (void*)(H), null)
  #define PTR_Handle2Ptr(handle, TYPE) ((TYPE*) handle)
#endif


/**Closes. This routine should be invoked one time on shutdown. */
void close_Hande2Ptr();



#endif //__fw_handle_ptr64_h__
