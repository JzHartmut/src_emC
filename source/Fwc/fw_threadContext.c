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
#include <Fwc/fw_ThreadContext.h>
#include <Fwc/fw_SimpleC.h>
#include <Fwc/fw_MemC.h>
#include <fw_assert.h>
#include <os_thread.h>

#include <string.h>

ThreadContextFW_s* ctorM_ThreadContextFW(MemC mthis)
{ ThreadContextFW_s* ythis = PTR_MemC(mthis, ThreadContextFW_s);
  int size = size_MemC(mthis);
  int offsStacktraceThCxt = OFFSETinDATA_MemUnit(ythis, stacktraceThreadContext);
  
  /**The stacktrace-ThreadContext ist the last member. Its size may be different,
   * because the length of the array for stored Stacktrace entries may be different.
   * Calculate this size from the given size in mthis - offset of Stacktrace-ThCxt
   */
  MemC mStacktraceThreadContext = CONST_MemC(&ythis->stacktraceThreadContext, size - offsStacktraceThCxt);

  ythis->topmemAddrOfStack = &mthis; //the highest known address
  ctorM_StacktraceThreadContext(mStacktraceThreadContext);
  return ythis;
}


/**Sets a new buffer in Threadcontext.
 */
METHOD_C MemC setUserBuffer_ThreadContextFw(MemC newBuffer, ThCxt* _thCxt)
{ MemC lastBuffer;
  if(_thCxt == null) { _thCxt = getCurrent_ThreadContextFW(); }
  lastBuffer = _thCxt->bufferAlloc;
  _thCxt->bufferAlloc = newBuffer;
  _thCxt->addrFree = PTR_MemC(newBuffer, MemUnit);
  _thCxt->bitAddrUsed = 0;
  memset(_thCxt->addrFree, 0, sizeof(_thCxt->addrFree));
  return lastBuffer;  //NOTE: the user is responsible for saving its content.
}




METHOD_C MemC getUserBuffer_ThreadContextFw(int size, ThCxt* _thCxt)
{ ASSERT_s0_Fwc(size >= -1, "faulty size argument", size);
  if(_thCxt == null) { _thCxt = getCurrent_ThreadContextFW(); }
  if(_thCxt->bufferAlloc.ref == null) {
    setUserBuffer_ThreadContextFw(alloc_MemC(2000), _thCxt);
  }
  { MemUnit* endBuffer = END_MemC(_thCxt->bufferAlloc);
    int sizeFree = endBuffer - _thCxt->addrFree;
    int mask = 0x1;
    int ix = 0;
    int ixLastUsed = -1;
    if(size ==0){  //special arguments
      size = sizeFree;
    } else if(size == -1) {
      size = sizeFree/2; 
    }
    while(ix < ARRAYLEN_SimpleC(_thCxt->addrUsed)) {
      if((_thCxt->bitAddrUsed & mask) ==0) {
        //free found
        int maskCheck = ~(mask -1);  //all high bits. 1=:0xffffffff 2:=0xfffffffe
        if((_thCxt->bitAddrUsed & maskCheck)==0) {
          //this and all higher bits are 0 too. Then the rest of buffer in thread context is to use:
          if(size <= sizeFree) {
            MemUnit* addr = _thCxt->addrFree;
            MemC ret = CONST_MemC(addr, size);
            _thCxt->addrFree += size;
            _thCxt->bitAddrUsed |= 1 << ix;
            set_MemC(_thCxt->addrUsed[ix], addr,size);  //store the found range.
            return ret; //NOTE: the user is responsible for saving its content.
          } 
        } else if(size_MemC(_thCxt->addrUsed[ix]) == (uint)size) {
          //a free block inside with exactly the same size, reuse it.
          _thCxt->bitAddrUsed |= mask;
          return _thCxt->addrUsed[ix];  
        }
      }
      ix +=1; mask <<=1;
    }
  }
  { //The algorithm has returned if a buffer was found.
    //This line is reached only if nothing is found.
    THROW_s0(IllegalStateException, "nothing free in ThreadContext", size);
    return null_MemC;
  }





/*
    int mask = 0xffffffff;
    int ix = 0;
    //search for the last block after them all are free. don't use a free block between -?TODO
    while( (_thCxt->bitAddrUsed & mask) !=0) { //the while breaks at least if mask ==0 after 32 shift in any case.
      ix +=1; mask <<=1;                       //shifts 0 from right to left.
    }
    if(ix < ARRAYLEN_SimpleC(_thCxt->addrUsed)) { //found
      MemUnit* addr = _thCxt->addrFree;
      MemC ret = CONST_MemC(addr, size);
      _thCxt->addrFree += size;
      _thCxt->bitAddrUsed |= 1 << ix;
      set_MemC(_thCxt->addrUsed[ix], addr,size);  //store the found range.
      return ret; //NOTE: the user is responsible for saving its content.
    } else {
      THROW_s0(IllegalStateException, "To much allocation blocks in ThreadContext", 0);
      return null_MemC;
    }
  } 
  else {
    THROW_s0(IllegalStateException, "Nothing free", 0);
    return null_MemC;
  }
*/
}



/**Releases the buffer in ThreadContext. 
 */ 
METHOD_C bool releaseUserBuffer_ThreadContextFw(void const* data, ThCxt* _thCxt)
{ if(_thCxt == null) {
    _thCxt = getCurrent_ThreadContextFW();
  }
  bool released = false;
  int mask = 0x1;
  int ix = 0;
  int ixLastUsed = -1;
  while(ix < ARRAYLEN_SimpleC(_thCxt->addrUsed)) {
    if((_thCxt->bitAddrUsed & mask) !=0) {
      void const* addr = PTR_MemC(_thCxt->addrUsed[ix], void const);
      if(addr == data) {
        _thCxt->bitAddrUsed &= ~mask;  //reset bit
        int maskCheck = ~(mask -1);  //all higher bits.
        if( (_thCxt->bitAddrUsed & maskCheck) ==0) {
          //all higher ranges are not used:
          int nrFree = ARRAYLEN_SimpleC(_thCxt->addrUsed) - (ixLastUsed+1); 
          _thCxt->addrFree =  _thCxt->addrUsed[ixLastUsed+1].ref;
          memset(&_thCxt->addrUsed[ixLastUsed+1], 0, nrFree * sizeof(_thCxt->addrUsed[0]));  //now delete unnecessary infos.
        }
        released = true;
        ix = 32766;  //break; 
      } else {
        ixLastUsed = ix;  //the last used block.
      }
    }
    ix +=1; mask <<=1;
  }
  return released;
}





/**This mehtod is necessary because the user shouldn't know the struct ThreadContext. 
 * It should be hidden, but the embedded part of threadcontext for Stacktrace handling 
 * should be known in all user routines because it is used inline-like.
 */
ThreadContextFW_s* getCurrent_ThreadContextFW()
{ ThreadContextFW_s* thC;
  MemC memThreadContext = os_getCurrentUserThreadContext();  //The users thread context is managed but not knwon in detail from osal.
  thC = PTR_MemC(memThreadContext, ThreadContextFW_s);
  if(thC == null)
  { memThreadContext = alloc_MemC(sizeof(ThreadContextFW_s));
    os_setCurrentUserThreadContext(memThreadContext);  
    ctorM_ThreadContextFW(memThreadContext);
    thC = PTR_MemC(memThreadContext, ThreadContextFW_s);
  }
  return thC;  //it is a embedded struct inside the whole ThreadContext.
}



METHOD_C bool setCheckingUserBuffer_ThreadContextFw(ThCxt* ythis, bool value)
{ bool ret = (ythis->mode & mCheckBufferUsed_Mode_ThCxt)!=0;
  if(value) { ythis->mode |= mCheckBufferUsed_Mode_ThCxt; }
  else      { ythis->mode &= ~mCheckBufferUsed_Mode_ThCxt; }
  return ret;
}



bool xxxoptimizeString_ThCxt(ThCxt* ythis, bool value)
{ bool ret = ythis->mode & mOptimizeToString_Mode_ThCxt;
  if(value) { ythis->mode |= mOptimizeToString_Mode_ThCxt; }
  else      { ythis->mode &= ~mOptimizeToString_Mode_ThCxt; }
  return ret;
}

bool isOptimizeString_ThCxt(ThCxt* ythis)
{ return ythis->mode & mOptimizeToString_Mode_ThCxt;
}
