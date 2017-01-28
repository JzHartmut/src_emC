#ifndef __os_sharedmem_h__
#define __os_sharedmem_h__
#include <os_types_def.h>
#include <Fwc/fw_MemC.h>


typedef struct SharedMem_OSAL_t
{
  char const* name;
  /**Memory space for a 128-bit-handle. Should be enough. */
  int32 handle[4];

  /**The call may store an error message if it failes. The error is null on success. */
  char const* error;

  /**Memory Address. */
  MemC addrSize;

} SharedMem_OSAL;




int os_createSharedMem(SharedMem_OSAL* thiz);


bool os_deleteSharedMem(SharedMem_OSAL* thiz);


int os_accessSharedMem(SharedMem_OSAL* thiz);



int os_closeAccessSharedmem(SharedMem_OSAL* thiz);



#endif //__os_sharedmem_h__
