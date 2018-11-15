#include <OSAL/os_sharedmem.h>



#ifndef __DONOTUSE_REFLECTION__
//#include "genRefl/OSAL/os_sharedMem.crefl"
#else

#endif


//Note: after reflection, only for C-file:
#undef BOOL
#undef PBOOL
#undef boolean
#undef INT32
#undef UINT32
#undef int64
#undef uint64

#include <wtypes.h>
#include <Winbase.h>



//Important hint: It is presumed that the 'Multibyte Character set' (it means UTF-8) is set 
//in the Project properties - General - Project defaults - Character set of the compiler.
//The other possibility is using "'Unicode Character set' - it means UTF16.
//If UTF16 is selected, the casting from LPCSTR to (char*) forces an compile error. 


MemC os_createSharedMem(SharedMem_OSAL* thiz, const char* name, int size){
   HANDLE hMapFile;
   MemUnit* pBuf;
   thiz->addrSize.ref = null;  //default on nonexisting mem.
   thiz->name = name;

   hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 size + sizeof(int32),    // maximum object size (low-order DWORD), in this case requested size + size marker.
                 (char*)thiz->name);                   // name of mapping object
  if(hMapFile == null) {
    thiz->nError = GetLastError();
  } else {
    pBuf = (MemUnit*) MapViewOfFile(hMapFile,   // handle to map object
                      FILE_MAP_ALL_ACCESS, // read/write permission
                      0,
                      0,
                      size);
    if(pBuf == null) {
      CloseHandle(hMapFile);
      thiz->nError = GetLastError();
    } else {
      memset(pBuf, 0, size);
      *((int32*)(pBuf)) = size;   //Write the size in the first 4 bytes. 
      set_OS_PtrValue(thiz->addrSize, pBuf + sizeof(int32), size);  //return the buffer after the size entry.
      
      *(HANDLE*)thiz->data = hMapFile;
      *(void**)&thiz->data[4] = pBuf;
      *(int32*)&thiz->data[6] = size;

      thiz->nError = 0;
    }
  }
  return thiz->addrSize;
}





MemC os_accessSharedMem(SharedMem_OSAL* thiz, const char* name)
{
  thiz->addrSize.ref = null;  //default on nonexisting mem.
  HANDLE hMapFile;
   MemUnit* addr;

   thiz->name = name;
   hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
                   (char*)thiz->name);               // name of mapping object

  if (hMapFile == NULL)
  {
    thiz->nError = GetLastError();
  } else {

    addr =  (MemUnit*)MapViewOfFile(hMapFile, // handle to map object
               FILE_MAP_ALL_ACCESS,  // read/write permission
               0,
               0,
               *(int32*)&thiz->data[6]);

    if (addr == NULL)
    {
      thiz->nError = GetLastError();
      CloseHandle(hMapFile);
    } else {
      int32* pBufi = (int32*)(addr);
      int32 size = *pBufi;
      set_OS_PtrValue(thiz->addrSize, pBufi+1, size);
      
      *(HANDLE*)thiz->data = hMapFile; 
      *(void**)&thiz->data[4] = addr;
      *(int32*)&thiz->data[6] = size;
      
      thiz->nError = 0;
    }
  }
  return thiz->addrSize;
}






bool os_isReadySharedMem(SharedMem_OSAL* thiz)
{
  return thiz->error == null //no error known
  && thiz->nError == 0
  && *(HANDLE*)thiz->data !=0   //a handle is given
  && *(void**)&thiz->data[4] !=null;  //pointer to the memory is given.
}



void os_closeSharedMem(SharedMem_OSAL* thiz)
{
  int err = 0;
  void* addr = *(void**)(&thiz->data[4]);
  HANDLE hMapFile = *(HANDLE*)(thiz->data);
  //STACKTRC_ENTRY("os_closeAccessedSharedMem");
  UnmapViewOfFile(addr);

 
  //TRY{ 
    CloseHandle(hMapFile);
  //}_TRY
  //CATCH(Exception, exc){
  //  thiz->error = "Any problem on closing";
  //  thiz->nError = exc->exceptionNr;
  //}
  //END_TRY;
  memset(thiz->data, 0, sizeof(thiz->data));  //set handle and address to 0 
  //STACKTRC_LEAVE;
}



