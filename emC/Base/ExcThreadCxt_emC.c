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
 * @content Implementation of a ThreadContext for os-level.
 *
 *
 * @author JcHartmut www.vishia.org
 * @version 0.83
 * list of changes:
 * 2009-10-00: Hartmut 
 *   del: some older versions of constructor
 *   new: optimizeString_ThCxt(...)
 * 2007-05-00: JcHartmut creation
 *
 ****************************************************************************/
#include <applstdef_emC.h>

//#include <emC/Base/SimpleC_emC.h>
#include <emC/OSAL/os_thread.h>
#include <emC/Base/MemC_emC.h>

#include <string.h>

//dependencies:
//* alloc_MemC referenced in function _getCurrent_ThreadContext_emC
//* init0_MemC referenced in function _getUserBuffer_ThreadContext_emC
//* null_MemC
//==>MemC_emC.c
//   * os_allocMem, os_freeMem,
//   ==> os_mem.c
//
//* os_getCurrentUserThreadContext referenced in function _getCurrent_ThreadContext_emC
//* os_setCurrentUserThreadContext referenced in function _getCurrent_ThreadContext_emC
//==>os_Thread.c os_Mutex.c os_Time.c
//
//* stop_AssertJc referenced in function _getUserBuffer_ThreadContext_emC
//==>stopAssert_emC_while0.c etc.
//
//* throw_s0Jc referenced in function _getUserBuffer_ThreadContext_emC
//==>emC/Exception_emC.c


#ifndef DEF_ThreadContext_SIMPLE


void ctor_StacktraceThreadContext_emC ( StacktraceThreadContext_emC_s* thiz)
{ thiz->maxNrofEntriesStacktraceBuffer = ARRAYLEN_emC(thiz->entries);
  thiz->mBitEntriesStacktrc = thiz->maxNrofEntriesStacktraceBuffer -1;
  //TODO assert that it is a power of 2!
}



void ctor_ThreadContext_emC  (  ThreadContext_emC_s* thiz, void const* topAddrStack)
{ //int offsStacktraceThCxt = OFFSETinDATA_MemUnit(ythis, stacktrc);
  
  /**The stacktrace-ThreadContext ist the last member. Its size may be different,
   * because the length of the array for stored Stacktrace entries may be different.
   * Calculate this size from the given size in mthis - offset of Stacktrace-ThCxt
   */
  //MemC mStacktraceThreadContext_emC = CONST_MemC(&ythis->stacktrc, size - offsStacktraceThCxt);

  //ythis->topmemAddrOfStack = (MemUnit*) &mthis; //the highest known address
  thiz->topmemAddrOfStack = (MemUnit*)topAddrStack;
  ctor_StacktraceThreadContext_emC(&thiz->stacktrc);
}


/**Sets a new buffer in Threadcontext.
 */
METHOD_C MemC setUserBuffer_ThreadContext_emC  (  MemC newBuffer, ThreadContext_emC_s* _thCxt)
{ MemC lastBuffer;
  if(_thCxt == null) { _thCxt = getCurrent_ThreadContext_emC(); }
  //UserBufferInThCxt_s* threadHeap = &_thCxt->threadheap;
  lastBuffer = _thCxt->threadheap.bufferAlloc;
  _thCxt->threadheap.bufferAlloc = newBuffer;  //should be cleaned outside.
  _thCxt->threadheap.addrFree = PTR_MemC(newBuffer, MemUnit);
  _thCxt->threadheap.bitAddrUsed = 0;
  return lastBuffer;  //NOTE: the user is responsible for saving its content.
}




MemC getUserBuffer_ThreadContext_emC ( int size, char const* sign, struct ThreadContext_emC_t*  _thCxt)
{ ASSERT_emC(size >= -1, "faulty size argument", size,0);
  if(_thCxt == null) { _thCxt = getCurrent_ThreadContext_emC(); }
  UserBufferInThCxt_s* threadHeap = &_thCxt->threadheap;
  if( ISNULL_MemC(threadHeap->bufferAlloc) ) {
    MemC alloc; ALLOC_MemC(alloc, 2000);
    setUserBuffer_ThreadContext_emC(alloc, _thCxt);
  }
  { MemUnit* endBuffer = PTR_MemC(threadHeap->bufferAlloc, MemUnit) + threadHeap->bufferAlloc.val;  //Addr after buffer.
    int sizeFree = (int)(endBuffer - threadHeap->addrFree);
    int mask = 0x1;
    int ix = 0;
    if(size ==0){  //special arguments
      size = sizeFree;
    } else if(size == -1) {
      size = sizeFree/2; 
    }
    size = (size + 7) & 0xfffffff8;  //align next /8
    while(ix < (int)ARRAYLEN_emC(threadHeap->addrUsed)) {
      if((threadHeap->bitAddrUsed & mask) ==0) {
        //free found
        int maskCheck = ~(mask -1);  //all high bits. 1=:0xffffffff 2:=0xfffffffe
        if((threadHeap->bitAddrUsed & maskCheck)==0) {
          //this and all higher bits are 0 too. Then the rest of buffer in thread context is to use:
          if(size <= sizeFree) {
            MemUnit* addr = threadHeap->addrFree;
            MemC ret = { (Addr8_emC*)addr, size};
            threadHeap->addrFree += size;
            threadHeap->bitAddrUsed |= 1 << ix;
            threadHeap->addrUsed[ix].sign = sign;
            threadHeap->ixLastAddrUsed = (int16)ix;
            SET_MemC(threadHeap->addrUsed[ix].used, addr, size);
            init0_MemC(ret);
            return ret; //NOTE: the user is responsible for saving its content.
          } 
        } else if(size_MemC(threadHeap->addrUsed[ix].used) == (VALTYPE_AddrVal_emC)size) {
          //a free block inside with exactly the same size, reuse it.
          threadHeap->bitAddrUsed |= mask;
          init0_MemC(threadHeap->addrUsed[ix].used);
          return threadHeap->addrUsed[ix].used;  
        }
      }
      ix +=1; mask <<=1;
    }
  }
  { //The algorithm has returned if a buffer was found.
    //This line is reached only if nothing is found.
    return null_MemC;
  }
}



METHOD_C void reduceLastUserBuffer_ThreadContext_emC  (  void* ptr, int size, ThreadContext_emC_s* _thCxt)
{ if(_thCxt == null) { _thCxt = getCurrent_ThreadContext_emC(); }
  UserBufferInThCxt_s* threadHeap = &_thCxt->threadheap;
  if(size & 0x7) { size += 8-(size & 0x7); }
  //MemUnit* endBuffer = END_MemC(_thCxt->bufferAlloc);
  AddrUsed_ThreadContext_emC* e = &threadHeap->addrUsed[threadHeap->ixLastAddrUsed]; 
  if(PTR_MemC(e->used, void) == ptr) {
    //ASSERT_s0_emC(e->used.ref == ptr , "reduceLastUserBuffer_ThreadContext_emC: faulty ptr", (int32)ptr);
    threadHeap->addrFree = (MemUnit*) ptr + size;
    e->used.val = size;
  }
}




/**Releases the buffer in ThreadContext. 
 */ 
METHOD_C bool releaseUserBuffer_ThreadContext_emC  (  void const* data, ThreadContext_emC_s* _thCxt)
{ if(_thCxt == null) {
    _thCxt = getCurrent_ThreadContext_emC();
  }
  UserBufferInThCxt_s* threadHeap = &_thCxt->threadheap;
  bool released = false;
  //try to free the last used position, often it is successfully.
  int ix = threadHeap->ixLastAddrUsed >=0 ? threadHeap->ixLastAddrUsed : 0;
  int mask = 0x1 << ix;
  int ixLastUsed = -1;
  while(ix < (int)ARRAYLEN_emC(threadHeap->addrUsed)) {
    if((threadHeap->bitAddrUsed & mask) !=0) {
      void const* addr = PTR_MemC(threadHeap->addrUsed[ix].used, MemUnit const);
      void const* endAddr = (void const*)addOffset_MemC(threadHeap->addrUsed[ix].used, threadHeap->addrUsed[ix].used.val);  //addr after used
      if(data >= addr && data < endAddr) {
        init0_MemC(threadHeap->addrUsed[ix].used);  //remove content. Initialize with 0
        threadHeap->addrUsed[ix].sign = 0;
        threadHeap->bitAddrUsed &= ~mask;  //reset bit
        int maskCheck = ~(mask -1);  //all higher bits.
        if( (threadHeap->bitAddrUsed & maskCheck) ==0) {
          //all higher ranges are not used:
          int nrFree = ARRAYLEN_emC(threadHeap->addrUsed) - (ixLastUsed+1); 
          threadHeap->addrFree =  PTR_MemC(threadHeap->addrUsed[ixLastUsed+1].used, MemUnit);
          //delete all entries of addrUsed, set to 0 (set MemC-content to 0)
          memset(&threadHeap->addrUsed[ixLastUsed+1], 0, nrFree * sizeof(threadHeap->addrUsed[0]));  
        }
        released = true;
        ix = 32766;  //break; 
      } else {
        ixLastUsed = ix;  //the last used block.
      }
    }
    if(ix == threadHeap->ixLastAddrUsed) { 
      //not successfully, start from 0, forgot ixLastAddrUsed. 
      ix = 0; threadHeap->ixLastAddrUsed = -1; mask = 0x1; 
    }
    else { ix +=1; mask <<=1; }
  }
  return released;
}






METHOD_C bool setCheckingUserBuffer_ThreadContext_emC  (  ThreadContext_emC_s* ythis, bool value)
{ bool ret = (ythis->threadheap.mode & mCheckBufferUsed_Mode_ThCxt)!=0;
  if(value) { ythis->threadheap.mode |= mCheckBufferUsed_Mode_ThCxt; }
  else      { ythis->threadheap.mode &= ~mCheckBufferUsed_Mode_ThCxt; }
  return ret;
}



bool xxxoptimizeString_ThCxt  (  ThreadContext_emC_s* ythis, bool value)
{ bool ret = ythis->threadheap.mode & mOptimizeToString_Mode_ThCxt;
  if(value) { ythis->threadheap.mode |= mOptimizeToString_Mode_ThCxt; }
  else      { ythis->threadheap.mode &= ~mOptimizeToString_Mode_ThCxt; }
  return ret;
}

bool isOptimizeString_ThCxt  (  ThreadContext_emC_s* ythis)
{ return ythis->threadheap.mode & mOptimizeToString_Mode_ThCxt;
}



#else 

void ctor_ThreadContext_emC(struct ThreadContext_emC_t* thiz, void const* topStack) {
  //all remain 0
  thiz->topmemAddrOfStack = C_CAST(MemUnit const*, topStack);
}

#endif //DEF_ThreadContext_STACKTRC


ExceptionStore exceptionStore_g = {0};

void logSimple_Exception_emC(int exc, StringJc msg, int32 value, int val2, char const* file, int line) {
  if (exceptionStore_g.ctException == 0) {
    exceptionStore_g.ctException = 1;
    exceptionStore_g.first.exceptionNr = exc;
    exceptionStore_g.first.exceptionValue = value;
    exceptionStore_g.first.file = file;
    exceptionStore_g.first.line = line;
  }
  else {
    //stop at max number, do not write 0!
    if( (exceptionStore_g.ctException +=1) ==0) { exceptionStore_g.ctException = (uint)-1; }
    exceptionStore_g.last.exceptionNr = exc;
    exceptionStore_g.last.exceptionValue = value;
    exceptionStore_g.last.file = file;
    exceptionStore_g.last.line = line;
  }

}




