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
 * compare the value at *reference to expect, swap with update if successful
 */
int compareAndSwap_AtomicInt(int volatile* reference, int expect, int update)
{ __typeof (*reference) ret;
  __asm __volatile ( "lock cmpxchgl %2, %1"
           : "=a" (ret), "=m" (*reference)
           : "r" (update), "m" (*reference), "0" (expect));
  return ret;
}


int32 compareAndSwap_AtomicInt32(int32 volatile* reference, int32 expect, int32 update)
{ __typeof (*reference) ret;
  __asm __volatile ( "lock cmpxchgl %2, %1"
           : "=a" (ret), "=m" (*reference)
           : "r" (update), "m" (*reference), "0" (expect));
  return ret;
}






/////**Implementation compareAndSet_AtomicReference:
//// * Using of a specific machine instruction dependency of the processor. Than it is also good for Multiprocessing.
//// * Here a simple way.
//// */
////void* compareAndSwap_AtomicReference(void* volatile* reference, void* expect, void* update)
////{ //use the same as compareAndSet_AtomicInteger because the sizeof and the content-kind is the same.
////  return (void*)compareAndSwap_AtomicInteger((int32*)(reference), (int32)expect, (int32)update);
////
////}
////
////
////
/////**Implementation compareAndSet_AtomicReference:
//// * Using of a specific machine instruction dependency of the processor. Than it is also good for Multiprocessing.
//// * Here a simple way.
//// */
////bool compareAndSet_AtomicReference(void* volatile* reference, void* expect, void* update)
////{ //use the same as compareAndSet_AtomicInteger because the sizeof and the content-kind is the same.
////  int32 found = compareAndSwap_AtomicInteger((int32*)(reference), (int32)expect, (int32)update);
////  return found == (int32)expect;
////}
////
