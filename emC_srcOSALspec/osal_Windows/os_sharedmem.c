#include <emC/OSAL/os_sharedmem.h>



#ifndef DEF_REFLECTION_NO
  //#include "genRefl/OSAL/os_sharedMem.crefl"
  //Do not include the crefl here, they are not necessary here. 
  //If the crefl are need for associated data it should be included in the main context of the application.
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

#undef UNICODE  //don't use WString

#include <wtypes.h>
#include <Winbase.h>



//Important hint: It is presumed that the 'Multibyte Character set' (it means UTF-8) is set 
//in the Project properties - General - Project defaults - Character set of the compiler.
//The other possibility is using "'Unicode Character set' - it means UTF16.
//If UTF16 is selected, the casting from LPCSTR to (char*) forces an compile error. 


MemC os_createSharedMem(SharedMem_OSAL* thiz, const char* name, int sizeUser){
   HANDLE hMapFile;
   MemUnit* pBuf;
   SET_MemC(thiz->addrSize, null, 0);  //default on nonexisting mem.
   strncpy(thiz->name, name, sizeof(thiz->name));
   int sizeSharedMem = ((sizeUser +7) & ~0x07) + 8; //round up to 8-byte boundary and add 8
   hMapFile = CreateFileMapping(
                 INVALID_HANDLE_VALUE,    // use paging file
                 NULL,                    // default security
                 PAGE_READWRITE,          // read/write access
                 0,                       // maximum object size (high-order DWORD)
                 sizeSharedMem,    // maximum object size (low-order DWORD), in this case requested size + size marker.
                 thiz->name);                   // name of mapping object
  if(hMapFile == null) {
    thiz->nError = GetLastError();
  } else {
    pBuf = (MemUnit*) MapViewOfFile(hMapFile,   // handle to map object
                      FILE_MAP_ALL_ACCESS, // read/write permission
                      0,
                      0,
                      sizeSharedMem);
    if(pBuf == null) {
      CloseHandle(hMapFile);
      thiz->nError = GetLastError();
    } else {
      memset(pBuf, 0, sizeSharedMem);
      *((int32*)(pBuf)) = sizeUser;   //Write the size in the first 4 bytes. 
      //Always use 8 byte for the size information, align to 8 of the netto buffer, for 32 bit system too.
      SET_MemC(thiz->addrSize, (void*)(((intptr_t)pBuf) + 8), sizeUser);  //return the buffer after the size entry.
      
      *(HANDLE*)thiz->data = hMapFile;
      *(void**)&thiz->data[4] = pBuf;
      *(int32*)&thiz->data[6] = sizeSharedMem;

      thiz->nError = 0;
    }
  }
  return thiz->addrSize;
}





MemC os_accessSharedMem(SharedMem_OSAL* thiz, const char* name)
{
  SET_MemC(thiz->addrSize, null, 0);  //default on nonexisting mem.
  HANDLE hMapFile;
   MemUnit* addr;

   strncpy(thiz->name, name, sizeof(thiz->name));
   hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
                   thiz->name);               // name of mapping object

  if (hMapFile == NULL)
  {
    thiz->nError = GetLastError();
  } else {

    addr =  (MemUnit*)MapViewOfFile(hMapFile, // handle to map object
               FILE_MAP_ALL_ACCESS,  // read/write permission
               0,
               0,
               0 );  //Comment in MS-Docu: " If this parameter is 0 (zero), the mapping extends from the specified offset to the end of the file mapping."  //*(int32*)&thiz->data[6]);

    if (addr == NULL)
    {
      thiz->nError = GetLastError();
      CloseHandle(hMapFile);
    } else {
      int32* pBufi = (int32*)(addr);
      int32 sizeUser = *pBufi;  //The stored size on creation of the other side
      //Always use 8 byte for the size information, align to 8 of the netto buffer, for 32 bit system too.
      SET_MemC(thiz->addrSize, (void*)(((intptr_t)pBufi) + 8), sizeUser);  //return the buffer after the size entry.
      
      *(HANDLE*)thiz->data = hMapFile; 
      *(void**)&thiz->data[4] = addr;
      int sizeSharedMem = ((sizeUser +7) & ~0x07) + 8; //round up to 8-byte boundary and add 8
      *(int32*)&thiz->data[6] = sizeSharedMem; //it may be the origin size of this sharedMem area.
      
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



