#include <os_sharedmem.h>

#undef BOOL
#undef PBOOL
#undef boolean
#undef INT32
#undef UINT32
#undef int64
#undef uint64

#include <wtypes.h>
#include <Winbase.h>


int os_createSharedMem(SharedMem_OSAL* thiz){
   int ret = 0;
   HANDLE hMapFile;
   MemUnit* pBuf;

   hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 size_MemC(thiz->addrSize),                    // maximum object size (low-order DWORD)
                 thiz->name);                   // name of mapping object
  if(hMapFile == null) {
    ret = GetLastError();
  } else {
    pBuf = (MemUnit*) MapViewOfFile(hMapFile,   // handle to map object
                      FILE_MAP_ALL_ACCESS, // read/write permission
                      0,
                      0,
                      size_MemC(thiz->addrSize));
    if(pBuf == null) {
      CloseHandle(hMapFile);
      ret = GetLastError();
      return false;
    } else {
      thiz->addrSize.ref = pBuf; 
    }
  }
  return ret;
}



int os_closeSharedMem(SharedMem_OSAL* thiz)
{

  UnmapViewOfFile(PTR_MemC(thiz->addrSize, void));

   CloseHandle(thiz->handle);

  return true;
}


int os_removeSharedMem(char const* name)
{


  return true;
}




int os_accessSharedMem(SharedMem_OSAL* thiz)
{
   int ret = 0;
   HANDLE hMapFile;
   MemUnit* addr;

   hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
                   thiz->name);               // name of mapping object

   if (hMapFile == NULL)
   {
     //
   }

   addr =  (MemUnit*)MapViewOfFile(hMapFile, // handle to map object
               FILE_MAP_ALL_ACCESS,  // read/write permission
               0,
               0,
               size_MemC(thiz->addrSize));

   if (addr == NULL)
   {
      ret = GetLastError();
      CloseHandle(hMapFile);
   } else {
      thiz->addrSize.ref = addr;   //success.
         
   }
  return ret;
}


