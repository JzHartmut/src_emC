#include <emC/OSAL/os_sharedmem.h>

#include <sys/ipc.h>
#include <sys/shm.h>

MemC os_createSharedMem(SharedMem_OSAL* thiz, const char* name, int sizeUser){

  //docu see https://ccppcoding.blogspot.com/2013/03/linux-shared-memory.html
  MemC ret;
  void* addr;
  int64 key = 123;

  int id = shmget(key, sizeUser, 0x666 |  IPC_CREAT );
  addr = shmat(id, null, SHM_RND);
  SET_MemC(ret, addr, sizeUser);

  return ret;

}
