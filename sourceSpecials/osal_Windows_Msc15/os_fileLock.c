

#include <OSAL/os_file.h>

#include <fileapi.h>

int os_flock(OS_HandleFile file, struct FileLock_OSAL_t* lockObj)
{
  BOOL ok = LockFileEx();
}
