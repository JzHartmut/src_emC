#include <emC/MemC_emC.h>
#include <os_mem.h>

#ifdef SIZEBLOCK_BlockHeap_emC
  #include <BlockHeap/BlockHeap_emC.h>  //for free(ptr)
#endif

int free_MemC(void const* addr)
{ MemC buffer;
  MemUnit* ptr = (MemUnit*)addr;
  #ifndef __NOT_SUPPORTED_ThreadContext_emC__
    ThCxt* _thCxt = getCurrent_ThreadContext_emC();
    if(_thCxt->mode & mCheckBufferUsed_Mode_ThCxt){
      if(_thCxt->mode & mBufferUsed_Mode_ThCxt){
        THROW_s0(IllegalStateException, "Thread buffer not free", 0);
      }
      _thCxt->mode |= mBufferUsed_Mode_ThCxt;
    }
    buffer = _thCxt->bufferAlloc;
    MemUnit const* bufferStart = PTR_MemC(buffer, MemUnit);
    MemUnit const* bufferEnd = bufferStart + size_MemC(buffer);
    if(ptr >= bufferStart && ptr < bufferEnd) {
      releaseUserBuffer_ThreadContext_emC(ptr, _thCxt);
      return 3;
    }
  #else 
    if(false) {}
  #endif
  #ifdef SIZEBLOCK_BlockHeap_emC
    else if(free_sBlockHeap_emC(ptr, _thCxt)) { //try to free a block in blockheap
      return 2;
    }
  #endif

  else   
  {
    //it seems to be a normal allocation.
    os_freeMem(ptr);
    return 1;
  }
}




