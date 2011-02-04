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
  if(_thCxt == null)
  { MemC memThreadContext = os_getCurrentUserThreadContext();  //this should not be occuring.
    _thCxt = PTR_MemC(memThreadContext, ThreadContextFW_s);
  }
  lastBuffer = _thCxt->bufferInThreadContext;
  _thCxt->bufferInThreadContext = newBuffer;
  return lastBuffer;  //NOTE: the user is responsible for saving its content.
}

METHOD_C MemC getUserBuffer_ThreadContextFw(ThCxt* _thCxt)
{ MemC buffer;
  if(_thCxt == null)
  { MemC memThreadContext = os_getCurrentUserThreadContext();  //this should not be occuring.
    _thCxt = PTR_MemC(memThreadContext, ThreadContextFW_s);
  }
  if(_thCxt->mode & mCheckBufferUsed_Mode_ThCxt){
    if(_thCxt->mode & mBufferUsed_Mode_ThCxt){
      THROW_s0(IllegalStateException, "Thread buffer not free", 0);
    }
    _thCxt->mode |= mBufferUsed_Mode_ThCxt;
  }
  buffer = _thCxt->bufferInThreadContext;
  if(PTR_MemC(buffer, void) == null)
  { buffer = alloc_MemC(2000);
    _thCxt->bufferInThreadContext = buffer;  //NOTE: struct-copy to save.
  }
  return buffer;  //NOTE: the user is responsible for saving its content.
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


/**Releases the buffer in ThreadContext. 
 */ 
METHOD_C bool releaseUserBuffer_ThreadContextFw(ThCxt* ythis)
{ bool ret = (ythis->mode & mBufferUsed_Mode_ThCxt) != 0;
  ythis->mode &= ~mCheckBufferUsed_Mode_ThCxt;
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
