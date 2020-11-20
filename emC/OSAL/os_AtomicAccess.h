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
 * @content Definition of atomic access routines. 
 * This routines are implemented at machine code level instruction appropriated to the CPU. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * list of changes:
 * 2008-02-01: Hartmut creation 
 *
 ************************************************************************************************/
#ifndef __os_AtomicAccess_h__
#define __os_AtomicAccess_h__
#include <applstdef_emC.h>
#include <emC/Base/Atomic_emC.h>
/*@CLASS_C AtomicReference @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

//#define AtomicReference struct AtomicReference_t*

//#define CONST_AtomicReference(VAL) { (struct AtomicReference_t*)&(VAL) }

//#define ATOMICREFERENCE ATOMICREFERENCE
#define ATOMICREFERENCE void* volatile*


#if defined(__CPLUSGEN) && defined(__cplusplus)

  #define CAST_AtomicReference(VARIABLE) ((ATOMICREFERENCE)(&(VARIABLE)))
#else
  //C: the cast to void* is accepted.
  #define CAST_AtomicReference(VARIABLE) ((ATOMICREFERENCE)(&(VARIABLE)))
#endif



#ifndef DEF_compareAndSet_AtomicInteger

/**Atomically sets the value to the given updated value if the current value == the expected value.
 * @param expect the expected value
 * @param update - the new value
 * @return true if successful. False return indicates that the actual value was not equal to the expected value.
 */
METHOD_C bool compareAndSet_AtomicReference(ATOMICREFERENCE reference, void* expect, void* update);



METHOD_C void* compareAndSwap_AtomicReference(ATOMICREFERENCE reference, void* expect, void* update);
//#define compareAndSet_AtomicReference(REF, EXPECT, UPDATE) compareAndSet_AtomicInteger((int32*)(REF), (int)(EXPECT), (int)(UPDATE))


/*@CLASS_C AtomicInteger @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**Atomically sets the value to the given updated value if the current value == the expected value.
 * @param expect the expected value
 * @param update - the new value
 * @return the old value if or not successfull. False return indicates that the actual value was not equal to the expected value.
 */
INLINE_emC bool compareAndSet_AtomicInt32(int32 volatile* reference, int32 expect, int32 update)
{ //use the same as compareAndSet_AtomicInteger because the sizeof and the content-kind is the same.
  int32 found = compareAndSwap_AtomicInt32((int32*)(reference), (int32)expect, (int32)update);
  return found == expect;
}
#endif  //DEF_compareAndSet_AtomicInteger





/**From bit 4; The Sequence number. */
#define kBitSeq_DoubleBufferingJc 4

#define _lockRd_DoubleBufferingJc 4
#define _lockWr_DoubleBufferingJc 8
#define _addSeq_DoubleBufferingJc (1<<kBitSeq_DoubleBufferingJc)


/*@INLINE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Lock the index for reading data in a double buffering system.
 * The double buffering system is used to prevent inconsistent data. 
 * * It should be never write to a buffer which is read in the same moment.
 * * It should be never read from a buffer which is written in the moment.
 * * Writing is alternate if no read is pending. Therefore a read operation while write is pending
 * reads the last written data.
 * This algorithm is proper if the writing operation is more frequent than the reading. 
 * The writing operation may be done in a fast interrupt. The reading operation can be taken a longer time.
 * But at least one complete writing operation should be able to proceed between two reading operations.
 * , Write:  00   11   11   00   11   00    00    00   00    11    11
 * , Read:       0000000000            11111111111111111    0000000000000
 * ,                   ^               ^______reads from 1 because writing to 0 is not ready.
 * ,                   |_______writes to 1 twice because buffer 0 is locked for read.              
 *
 * The index in var is incremented by 1 (only bit 0, 0 or 1 as index value). That index is returned.
 * The atomic access is neccesarry because only the appropriate bits should be changed in regarding the locking state.. 
 * In the moment of lock the index may be changed in selten cases.
 * Then this operation is repeat. The number of repetition is limited only to guaranteed prevent hanging.
 * @param var Variable which hold the index in bit 0 and a lock flag in bit1.
 * @return index to locked access. It is 0 or 1.
 */
INLINE_emC int32 lockRead_DoubleBufferingJc(int32 volatile* var)
{
  int abortCt = 100;
  int32 val, valNew;
  do {
    val = *var;
    if(val & _lockWr_DoubleBufferingJc) { //write is pending
      valNew = (val ^1) | _lockRd_DoubleBufferingJc;  //read from the other buffer, store the locked read index. 
    } else {
      valNew = val | _lockRd_DoubleBufferingJc;  //Bit for lock, don't change the locked read index.
    }
  } while(!compareAndSet_AtomicInt32(var, val, valNew) && --abortCt >=0);  //repeate till see unchanged val.
  //don't evaluate abortCt. It is only to prevent hang in a non expected case.
  return valNew & 1; //retVal ;
}


/**Unlock the index for reading. Now the index can be incremented by writing. 
 */
INLINE_emC void unlockRead_DoubleBufferingJc(int32 volatile* var) {
  int32 val, valNew;
  int abortCt = 100;
  do {
    val = *var;
    valNew = val & ~_lockRd_DoubleBufferingJc;  //reset lock bit
  } while(!compareAndSet_AtomicInt32(var, val, valNew)  && --abortCt >=0);
}



/**Lock double buffering for write operation.
 * If a read operation is pending, it returns the other index. Write always in a non read buffer.
 * If read is not pending, it increments the index. Therefore while pending write the older buffer is used for read.
 * 
 * This operation increments a sequence number at once. 
 * @return the full index value, sequence number from bit kBitSeq_DoubleBufferingJc, index in bit 0.
 *   Note: build the index with ret & 1.
 */
INLINE_Jc int32 lockWrite_DoubleBufferingJc(int32 volatile* var)
{
  int abortCt = 100;
  int32 val, valNew, retVal;
  do {
    val = *var;
    if(val & _lockRd_DoubleBufferingJc) { //lock read:
      valNew = (val | _lockWr_DoubleBufferingJc) + _addSeq_DoubleBufferingJc;   //don't increment bit 0 (buffer index) because it is locked.
      retVal = valNew ^ 1;          //but use the other index for write.   
    } else {
      retVal = valNew = ((val ^ 1) | _lockWr_DoubleBufferingJc) + _addSeq_DoubleBufferingJc;  //Increment sequence number
    }
  } while(!compareAndSet_AtomicInt32(var, val, valNew) && --abortCt >=0);  //repeate till see unchanged val.
  return retVal;
}


/**Unlocks the write operation
 * If the read operation is locked, only the write lock is reset. 
 * If no read operation is pending, it stores the given ixWr.
 * @param ixWr the used write index,
 * @return number of while loops for atomic access, only for debug..
 */
INLINE_emC int unlockWrite_DoubleBufferingJc(int32 volatile* var, int32 ixWr)
{
  int abortCt = 100;
  int32 val, valNew;
  do {
    val = *var;
    if(val & _lockRd_DoubleBufferingJc) { //lock read:
      valNew = val & ~_lockWr_DoubleBufferingJc;   //only unlock write bit.
    } else {
      valNew = ((val & ~1) | (ixWr & 1)) & ~_lockWr_DoubleBufferingJc;   //store the write index.
    }
  } while(!compareAndSet_AtomicInt32(var, val, valNew) && --abortCt >=0);  //repeate till see unchanged val.
  return 100-abortCt;
}



/**Regard a special platform variant, which may define macros instead prototypes: */
#ifdef PLATFORM_os_AtomicAccess_h
#include "PLATFORM_os_AtomicAccess.h"
#endif


/*@END*/

#endif //__os_AtomicAccess_h__
