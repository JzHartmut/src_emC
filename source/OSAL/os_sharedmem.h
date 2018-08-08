#ifndef __os_sharedmem_h__
#define __os_sharedmem_h__
#include <applstdefJc.h>
#include <Fwc/fw_MemC.h>

/**This structure contains all data for the internal organization of a shared memory access. 
 * Data of this struct does not need to access by the user. Use the operations which uses this structure.
 * The user should create one of this structure for any shared mem access. 
 * The user have to be intialize it with {0}.
 */
typedef struct SharedMem_OSAL_t
{
  /**Memory space for a 128-bit-handle. Should be enough. */
  int32 data[8];

  /**The call may store an error message if it failes. The error is null on success. */
  char const* error;

  int32 nError;

  /**Memory Address. */
  MemC addrSize;
  
  /**The name of the shared memory is stored here persistent. The name may be composited on runtime. The length is max. 31 character, the last is 0. */
  char const* name; //[32];

} SharedMem_OSAL;



/**Creates a shared mem area inside the operation system. 
 * For special systems there may be special areas with defined names, only they can be used.
 * But for that cases 
 *
 * @param name a proper system wide valid name for the shared memory. It should be refer to a persistent location in memory. A "string literal" is persistent.
 * @param size of the shared memory in bytes. Usual it should be a multiple of 8 Bytes.
 * @return a pair of address and length to access the shared memory. If the address and length is 0, the shared memory is not ready.
 */
extern_C MemC os_createSharedMem(SharedMem_OSAL* thiz, const char* name, int size);


/**Accessed a shared mem area inside the operation system. 
 * For special systems there may be special predefined areas with deterministic names, only they may be able to use.
 * Because they are predefined, the [[os_createSharedMem(...)]] may be not necessary.
 * It is possible to get a pointer to a Dual Port Memory too with this operation.
 *
 * For a common purpose operation system any other process should be created this shared memory using [[os_createSharedMem(...)]]
 * or any other proper operation system call.
 *
 * For processes which has not a master, it is possible to check whether a named shared memory is existing.
 * If this method returns null respectively [[os_isReadySharedMem(...)]] returns false than this process can create the shared memory
 * invoking [[os_createSharedMem(...)]]. It is possible that this failes because another process has created the shared memory with this name yet simultaneously.
 * Therefor [[os_isReadySharedMem(...)]] should be checked again. If it is false too, then this routine should be called a second time.
 * But if the second invocation is faulty too, then an ressource error is 
 *
 * @param name a proper system wide valid name for the shared memory. It should be refer to a persistent location in memory. A "string literal" is persistent.
 * @return a pair of address and length to access the shared memory. If the address and length is 0, the shared memory is not ready.
 */
extern_C MemC os_accessSharedMem(SharedMem_OSAL* thiz, const char* name);


extern_C bool os_isReadySharedMem(SharedMem_OSAL* thiz);




/**Accesses or creates a shared mem area inside the operation system. 
 * For processes which has not a master, it is possible to check whether a named shared memory is existing.
 * If it is not exisiting, this routine invokes [[os_createSharedMem(...)]]. 
 * It is possible that this failes because another process has created the shared memory with this name yet simultaneously.
 * Therefor [[os_isReadySharedMem(...)]] is checked again. If it is false too, then this routine calls os_accessSharedMem(...) a second time.
 * But if the second invocation is faulty too, then an ressource error is given.
 *
 * @param name a proper system wide valid name for the shared memory.
 * @return a pair of address and length to access the shared memory. If the address and length is 0, the shared memory is not ready.
 */
extern_C MemC os_createOrAccessSharedMem(SharedMem_OSAL* thiz, const char* name, int size);

INLINE_Fwc MemC os_createOrAccessSharedMem(SharedMem_OSAL* thiz, const char* name, int size)
{
  MemC ret = os_accessSharedMem(thiz, name);
  if(os_isReadySharedMem(thiz)) return ret;
  //The shared memory may be not created, created it yet:
  ret = os_createSharedMem(thiz, name, size);
  if(os_isReadySharedMem(thiz)) return ret;
  //it is possible that the shared memory was created in the same time by another process, therefore:
  return os_accessSharedMem(thiz, name);  //try to access it now.
  //If it failes, test it outside.
}


extern_C void os_closeSharedMem(SharedMem_OSAL* thiz);



#endif //__os_sharedmem_h__
