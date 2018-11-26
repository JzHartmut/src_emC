/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @maintainer Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content This file contains the implementation of os_mem for MS-Windows.
 * @author Hartmut Schorrig
 * @version 0.81d
 * list of changes:
 * 2007-10-01: Hartmut creation
 *
 ****************************************************************************/
#include <OSAL/os_mem.h>

#undef INT32
#undef UINT32
#undef int64
#undef uint64

#include <wtypes.h>
#include <winbase.h>


char const sign_AllocMem[] = "OS_AllocMem";

typedef struct OS_AllocMem_t
{
  char const* sign;
  void* dummy[3];
} OS_AllocMem_s;



void* os_allocMem  (  uint size)
{
  OS_AllocMem_s* ptr = (OS_AllocMem_s*)LocalAlloc(LMEM_FIXED, size + sizeof(OS_AllocMem_s));   //malloc(size);  //
  if(ptr == null)
  { int error = GetLastError();
  } else {
    memset(ptr, 0, size + sizeof(OS_AllocMem_s));
    ptr->sign = sign_AllocMem;
  }
  return ptr + 1;  //after OS_AllocMem_s
}



int os_freeMem  (  void const* ptr)
{
  OS_AllocMem_s* ptrAlloc = ((OS_AllocMem_s*) ptr)-1;
  if(ptrAlloc->sign == sign_AllocMem) {
    void* ok = GlobalFree((void*)ptrAlloc);   //malloc(size);
    if(ok == NULL)
    { return 0;
    }
    else
    { return -1;
    }
  }
  else {
    return 0; //nothing to free, maybe a const pointer.
  }
}



