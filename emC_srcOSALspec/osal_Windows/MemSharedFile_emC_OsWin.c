

#include <applstdef_emC.h>
#include <emC/HAL/SharedMem_HALemC.h>
#include <emC/Base/MemC_emC.h>
#include <stdio.h>


//Windows-specific includes
#undef INT32
#undef UINT32
#undef int64
#undef uint64

#include <wtypes.h>
#include <winbase.h>
#include <winerror.h>

//docu common, see:
//https://dzone.com/articles/myth-busting-memory-mapped-files-and-shared-memory

typedef struct Internal_SharedMem_WindowsAdaptemC_T {

  char const* significance;

  HANDLE hFile;

  HANDLE hMap;

  int nError;

} Internal_SharedMem_WindowsAdaptemC_s;


static char const* significanceMemShared = "MemSharedFile_emC_OsWin_2021-07"; 
//yet only experience


void* open_SharedMem_HALemC ( SharedMem_HALemC_s* thiz, char const* name, int size ) {
  Internal_SharedMem_WindowsAdaptemC_s* thizd = allocDATA_MemC(Internal_SharedMem_WindowsAdaptemC_s);
  thizd->significance = significanceMemShared;
  thiz->internalData = thizd;

  //https://stackoverflow.com/questions/39268051/windows-createfile-dynamic-share-mode-while-the-file-is-open

  int mode = 0;
  int shareMode = FILE_SHARE_READ; //FILE_SHARE_WRITE; //then another cannot open the file, it is not shared, the share is locked for access
  LPSECURITY_ATTRIBUTES securityAttrib = null;
  int flags = OPEN_ALWAYS; //FILE_FLAG_OVERLAPPED | 
  thizd->hFile = CreateFile( name, GENERIC_READ | GENERIC_WRITE
  , shareMode, securityAttrib, flags, mode, NULL );
  if(thizd->hFile == INVALID_HANDLE_VALUE) {
    thizd->nError = GetLastError();
    return null;
  }
  else {
    thizd->hMap = CreateFileMapping(thizd->hFile, 
    NULL,                    // default security
          PAGE_READWRITE,          // read/write access
          0,                       // maximum object size (high-order DWORD)
          size,                // maximum object size (low-order DWORD)
          "mapping_name"); 

   void* pBuf = MapViewOfFile(thizd->hMap,   // handle to map object
          FILE_MAP_ALL_ACCESS, // read/write permission
          0,
          0,
          size);
    return pBuf;
  }
}



void close_SharedMem_HALemC(SharedMem_HALemC_s* thiz) {
  Internal_SharedMem_WindowsAdaptemC_s* thizd = WR_CAST(Internal_SharedMem_WindowsAdaptemC_s*, C_CAST(Internal_SharedMem_WindowsAdaptemC_s const*, thiz->internalData)); 
  if(thizd == null || thizd->significance != significanceMemShared) {
    THROW_s0n(IllegalArgumentException, "faulty handle", (int)(intPTR)thizd, 0);
  }
  int ok = 1;
  if(thizd->hMap !=null) {
    ok = CancelIoEx(thizd->hMap, 0);
    ok = CloseHandle(thizd->hMap);
    if(!ok) {
      THROW_s0n(IllegalArgumentException, "close faulty", 0, 0);
    } else {
      thizd->hMap = null;
    }
  }
  if(thizd->hFile !=null) {
    ok = CancelIoEx(thizd->hFile, 0);
    ok = CloseHandle(thizd->hFile);
    if(!ok) {
      THROW_s0n(IllegalArgumentException, "close faulty", 0, 0);
    } else {
      thizd->hFile = null;
    }
  }
  free_MemC(thizd);
}
