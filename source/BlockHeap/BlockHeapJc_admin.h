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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 * @content: All declarations to use from users system level to work with BlockHeap_emC
 * to administrate the block heap and the garbage collector.
 *
 * @author JcHartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2008-04-15: JcHartmut creation from older sources
 *
 ****************************************************************************/
/**This file describes the methods to call from outside to arrange and manage the BlockHeap_emC.
 */

#ifndef __BlockHeap_emC_h__
#define __BlockHeap_emC_h__
#include "Jc/ObjectJc.h"
#include "Jc/StringBufferJc.h"
#include "BlockHeap/BlockHeap_emC.h"

struct NodePoolJc_t;

/*@CLASS_C BlockHeap_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This is the control structure of one heap.
 * The user may have more as one heap, several moduls may used several heaps.
 * So a problem in one heap cause only a problem in the using moduls, not in the whole application.
 * If a algorithm calls a simple new, the BlockHeap in the OS_ThreadContext is used.
 * It is the current blockHeap.
 */
typedef struct BlockHeap_emC_t
{
  ObjectJc object;

  struct BlockHeap_emC_t* nextHeap;

  /** Index of this heap ctrl in the whole array of all heap ctrl*/
  int idxHeapCtrl;

  /** nr of Blocks, determine by calling init().
  */
  int zBlock;

  /** Size of a normal block. It must be a power of 2.
  */
  //int bytesNormalBlock;

  /** Size of a small block.
  */
  int bytesSmallBlock;

  /** Size of a mapentry block */
  #define XXXXXbytesMapEntryBlock_BlockHeap 24

  /** Mask of the adress of a normal Block. It is the complement of (bytesNormalBlock -1).
  */
  //int32 mAdressNormalBlock_BlockHeap;

  /** Mask of the adress of a small Block. It is the complement of (bytesSmallBlock -1).
  */
  int32 mAdressSmallBlock_BlockHeap;


  /** The begin of memory location of this heap */
  //MemAreaC* heapBegin;
  struct BlockHeapBlockJc_debugArray_t* heapBegin;

  /** The address after the heap */
  void* heapEnd;


  struct BlockHeapBlockJc_t* volatile firstFreeBlock;
  //struct BlockHeapBlockJc_t* lastFreeBlock;

  struct BlockHeapBlockJc_t* volatile firstFreeBlockSmall;
  //struct BlockHeapBlockJc_t* lastFreeBlockSmall;

  struct BlockHeapBlockJc_t* volatile firstFreeBlockMapEntry;
  struct BlockHeapBlockJc_t* lastFreeBlockMapEntry;

  struct ListMapEntryJc_t* volatile firstMapEntry;
  struct ListMapEntryJc_t* volatile lastMapEntry;

  /** Flag if the system is in initmode or not. In initmode no BlockHeap is used,
      instead all alloc-calls calls inside malloc().
  */
  int32 bitInitMode;

  int32 ctCollosionAlloc, ctCollosionFree;

  /**A LogMessage output for all garbage collection and allocation operations. */
  struct LogMessageFW_t* log;

  int kIdentMsgBase;

}BlockHeap_emC;


extern_C struct ClassJc_t const reflection_BlockHeap_emC;


/**inits a new allocated BlockHeap.
 * @param mem The memory  for the struct BlockHeap_emC, the control data of BlockHeap
 * @param wholeHeap The memory for the heap itself.
 * @param bytesNormalBlock number of bytes slated for a normal block.
 *                         It should be a value between 128...to max. 4096.
 *                         It have to be a power of 2.
 * @param bytesSmallBlock number of bytes slated for a small block.
 *                         It should be a value between 32...256.
 */
METHOD_C struct BlockHeap_emC_t* ctorO_BlockHeap_emC(ObjectJc* othis, MemC wholeHeap, int bytesNormalBlock, int bytesSmallBlock);




METHOD_C void setRunMode_BlockHeap_emC(BlockHeap_emC* ythis, struct LogMessageFW_t* log, int kIdentMsgBase);




/**Reports the state of one block.
 * This Method may be called in a while loop to test the utilization of the block heap.
 * @param idxBlock current index of block to test. Start with 0 and increment until the method returns null.
 * @param buffer The Buffer to put the info into. The buffer will be cleared before.
 * @return content of buffer as String or null if the idxBlock is invalid.
 */
METHOD_C StringJc report_BheapJc(BlockHeap_emC* ythis, int* idxBlockP, StringBufferJc* buffer);



/**sets a method called inside the running of garbage Collection after test of each block in a cluster.
 * This method is only used to test some special cases.
 */
METHOD_C void setTestMethod(MT_int_Method_int testMethod);

//Some test routines
void testLastAccess(struct NodePoolJc_t* ithis, ThCxt* _thCxt);

#endif  /*__BlockHeap_emC_h__*/
