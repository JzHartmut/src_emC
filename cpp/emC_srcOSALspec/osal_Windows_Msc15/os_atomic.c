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
 * @content This file contains the implementation of os_atomicAccess for MS-Windows.
 * @author Jchartmut www.vishia.org
 * @version 0.81ad
 * list of changes:
 * 2007-10-01: JcHartmut creation
 *
 ****************************************************************************/

#include <emC/OSAL/os_AtomicAccess.h>

#undef int64
#undef uint64
#undef INT32
#undef UINT32

#include <wtypes.h>
#include <winbase.h>


/**Implementation compareAndSet_AtomicInteger:
 * Using of a specific machine instruction dependency of the processor. Than it is also good for Multiprocessing.
 * Here a simple way.
 */
bool xxxcompareAndSet_AtomicInteger(int32 volatile* reference, int32 expect, int32 update)
{ bool bOk = true;
  //Threadwechselsperre ...
  if(*reference == expect)
  { *reference = update;
  }
  else
  { bOk = false;
  }
  //Threadwechselsperre aufheben
  return bOk;

}


/*Quelle: http://www.cs.cornell.edu/courses/cs414/2001SP/minithread_md.c
          http://www.pktek.net/docs/intel/instr/cmpxchg.html
CMPXCHG - Compare and Exchange

        Usage:  CMPXCHG dest,src  (486+)
        Modifies flags: AF CF OF PF SF ZF

        Compares the accumulator (8-32 bits) with dest.  If equal the
        dest is loaded with src, otherwise the accumulator is loaded
        with dest.

                                 Clocks                 Size
        Operands         808x  286   386   486          Bytes

        reg,reg           -     -     -     6             2
        mem,reg           -     -     -     7             2

        - add 3 clocks if the mem,reg comparison fails
*/



/*
 * compare and swap
 * 
 * compare the value at *x to oldval, swap with
 * newval if successful
 */


//Note: The interlocked operations works with uint, hence cast.


int32 compareAndSwap_AtomicInteger(int32 volatile* reference, int32 expect, int32 update) {
  return InterlockedCompareExchange((unsigned volatile long*)reference, (unsigned long)update, (unsigned long)expect);  
}

int16 compareAndSwap_AtomicInt16(int16 volatile* reference, int16 expect, int16 update) {
  return InterlockedCompareExchange16(reference, (uint16)update, (uint16)expect);  
}

int32 compareAndSwap_AtomicInt32(int32 volatile* reference, int32 expect, int32 update) {
  return InterlockedCompareExchange((uint32*)reference, (uint32)update, (uint32)expect);  
}

int compareAndSwap_AtomicInt(int volatile* reference, int expect, int update) {
  return InterlockedCompareExchange((unsigned volatile int*)reference, (unsigned int)update, (unsigned int)expect);  
}



LONGLONG compareAndSwap_AtomicInt64(LONGLONG volatile* reference, LONGLONG expect, LONGLONG update)
{
  return InterlockedCompareExchange64(reference, update, expect);  
}








/**Implementation compareAndSet_AtomicReference:
 * Using of a specific machine instruction dependency of the processor. Than it is also good for Multiprocessing.
 * Here a simple way.
 */
//void* compareAndSwap_AtomicRef(struct AtomicReference_t volatile* reference, void volatile* expect, void volatile* update)
void* compareAndSwap_AtomicRef(void* volatile* reference, void* expect, void* update)
{ //use the same as compareAndSet_AtomicInteger because the sizeof and the content-kind is the same.
  return InterlockedCompareExchangePointer(reference, update, expect);
}




// bool compareAndSet_AtomicInteger(int volatile* reference, int expect, int update){
//  //Note: unsigned long is uint32 for this compiler
//  unsigned long read = InterlockedCompareExchange((unsigned volatile long*)reference, (unsigned long)update, (unsigned long)expect);  
//  return read == (unsigned long)update;
//}
//
//
// bool compareAndSet_AtomicInt32(int32 volatile* reference, int32 expect, int32 update){
//  //Note: unsigned long is uint32 for this compiler
//  unsigned long read = InterlockedCompareExchange((unsigned volatile long*)reference, (unsigned long)update, (unsigned long)expect);  
//  return read == (unsigned long)update;
//}
//

// bool compareAndSet_AtomicInt64(LONGLONG volatile* reference, LONGLONG expect, LONGLONG update){
//  //Note: unsigned long is uint32 for this compiler
//  LONGLONG read = InterlockedCompareExchange64((LONGLONG volatile*)reference, (LONGLONG)update, (LONGLONG)expect);  
//  return read == (LONGLONG)update;
//}

//Implementation note:
//Because the platform does only offer a 32 bit width memory access, 
//it reads the word-32 on memory and builds the expected word with the other 16 bits read and expect.
//Then it executes the compareAndSwap with the word-32.
//If the other 16 bit are changed but the expected bits are unchanged,
//nevertheless it repeats the access because it is not possible to write only 16 bit.
//The propability to execute an access twice because it may be unnecessary because expect is only factor 2 at least.
// 
#if 0 //old form uses only Int32 access.
int16 compareAndSwap_AtomicInt16(int16 volatile* reference, int16 expect, int16 update){
  //Note: more difficult because memory is 32 bit
  unsigned long expect32, update32;
  if( (((intptr_t)reference) & 0x3) == 0) { //read write lo word
    expect32 = *(reference +1); //read associate hi word
    expect32 = (expect32 <<16) | update; 
    update32 = *(reference +1); //read associate hi word
    update32 = (update32 <<16) | update; 
  } else {
    expect32 = update;
    expect32 = (expect32 <<16) | *(reference -1);  //read associate lo word 
    update32 = update;
    update32 = (update32 <<16) | *(reference -1);  //read associate lo word 
  }
  //compare and swap the whole 32 bit memory location, assume that the other word is not change in the same time
  //or repeat the access (unnecessary) if the other word is changed only. That is not a functional error, 
  //only a little bit more calculation time because unnecesarry repetition.
  unsigned long read = InterlockedCompareExchange((unsigned volatile long*)reference, update32, expect32);  
  return (((intptr_t)reference) & 0x3) == 0 ? (int16)(read) : (int16)(read >>16) ;
}
#endif

 bool compareAndSet_AtomicRef(void* volatile* reference, void* expect, void* update){
  //simple implementation, not atomic, but able to test. TODO ASM-Instructions with Disable Interrupt necessary.
  void* read = InterlockedCompareExchangePointer(reference, update, expect);
  return read == expect;
}
