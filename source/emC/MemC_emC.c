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
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content Access to memory with address and size.
 *
 * @author JcHartmut www.vishia.org
 * @version 0.81ad
 * list of changes:
 * 2007-10-01: JcHartmut creation
 *
 ****************************************************************************/
#include <emC/MemC_emC.h>
#include <OSAL/os_mem.h>
#include <string.h>
#ifdef SIZEBLOCK_BlockHeap_emC
  #include <BlockHeap/BlockHeap_emC.h>  //for free(ptr)
#endif


MemC null_MemC = {0};


/**It is a small additinal head structure to the allocated data for debug and management. */
typedef struct Alloc_MemC_t
{
  char const* sign;
  intptr_t size;
  void* dummy[2];
} Alloc_MemC_s;


char const sign_Alloc_MemC[] = "Alloc_MemC";


void* alloc_MemC(int size) {
  int allocSize = sizeof(Alloc_MemC_s) + size + sizeSafetyArea_allocMemC;
  Alloc_MemC_s* ptr = (Alloc_MemC_s*)os_allocMem(allocSize);
  if(ptr !=null) {
    memset(ptr, 0, size + sizeof(Alloc_MemC_s));
    intptr_t memend = ((intptr_t) ptr ) + sizeof(Alloc_MemC_s) + size;
    memset((void*)memend, 0xaa, sizeSafetyArea_allocMemC);
    ptr->sign = sign_Alloc_MemC;
    ptr->size = size;
    return ptr + 1;  //after OS_AllocMem_s
  }
  else return null; 
}






int free_MemC  (  void const* addr)
{ MemC buffer;
  if(addr == null) return 0;
  //
  MemUnit* ptr = (MemUnit*)addr;
  #ifndef __NOT_SUPPORTED_ThreadContext_emC__
  ThCxt* _thCxt = getCurrent_ThreadContext_emC();
  if(_thCxt->mode & mCheckBufferUsed_Mode_ThCxt){
    if(_thCxt->mode & mBufferUsed_Mode_ThCxt){
      THROW1_s0(IllegalStateException, "Thread buffer not free", 0);
    }
    _thCxt->mode |= mBufferUsed_Mode_ThCxt;
  }
  buffer = _thCxt->bufferAlloc;
  MemUnit const* bufferStart = buffer.ref; //PTR_MemC(buffer, MemUnit);
  MemUnit const* bufferEnd = bufferStart + buffer.size; //size_MemC(buffer);
  
  
  if(ptr >= bufferStart && ptr < bufferEnd) {
    releaseUserBuffer_ThreadContext_emC(ptr, _thCxt);
    return 3;
  }
  #else 
  if(false) {}
  #endif
  //
  #ifdef SIZEBLOCK_BlockHeap_emC
  else if(free_sBlockHeap_emC(ptr, _thCxt)) { //try to free a block in blockheap
    return 2;
  }
  #endif

  else { //seems to be a os_alloc
    Alloc_MemC_s* ptrAlloc = ((Alloc_MemC_s*) ptr)-1;
    if(ptrAlloc->sign == sign_Alloc_MemC) {
      intptr_t memend = ((intptr_t) ptr ) + ptrAlloc->size;
      int32* addrCheck = (int32*)memend;
      int ct = (sizeSafetyArea_allocMemC)/4;
      while (--ct >= 0) {
        if (*addrCheck != 0xaaaaaaaa) {
          addrCheck +=0;   // <================== set a breakpoint here.
        }
        addrCheck +=1;
      }
      os_freeMem(ptr);
      return 1;
    } else {
      return 4;
    }
  }

}



MemC init0_MemC(MemC mem)
{ memset(mem.ref, 0, mem.size);
  return mem;
}

void init0p_MemC(void* ptr, int size)
{ memset(ptr, 0, size);
}





void __errorAddress_MemC(MemC* memC, void* addr, int nrofBytes) { 
  STACKTRC_ENTRY("errorAddress_MemC");
  char const* error = "???"; 
  int offset = (MemUnit*)addr - memC->ref;
  if(offset + nrofBytes > memC->size) { error = "nrofBytes behind end"; }
  else if(offset >= memC->size)       { error = "address behind mem";   }
  else if(offset < 0)                 { error = "address before mem";   }
  else if(nrofBytes < 0)              { error = "nrofBytes negative";   }
  THROW_s0(IndexOutOfBoundsException, error, offset, nrofBytes);
  STACKTRC_LEAVE; 
}



void __throw_MemC(char const* error, int val1, int val2) {
  STACKTRC_ENTRY("throw_MemC");
  THROW_s0(IllegalArgumentException, error, val1, val2);
  STACKTRC_LEAVE; 

}





