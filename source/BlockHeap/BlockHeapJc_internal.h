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
 * @content: internal used common definitions and declarations for the BlockHeap...c-sources.
 * This file should not be included at user level.
 *
 * @author JcHartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2008-04-15: JcHartmut creation from older sources
 *
 ****************************************************************************/
/**This file describes the internally structures of the BlockHeapJc concept.
 */

#ifndef __BlockHeapJc_i_h__
#define __BlockHeapJc_i_h__
#include <BlockHeap/BlockHeapJc.h>
#include <BlockHeap/BlockHeapJc_admin.h>

#include "Jc/ListMapEntryJc.h"

#include <os_time.h>

#define HEAP_BEGINSATPOWER2_RUNTIMEHEAP

typedef int32 ObjectRefValuesJc;

/**The enum construct defines some constants used as state value or state bit mask for a block in heap.
   The element BlockHeapBlockCtrlJc.typeAndSize contains this values and bits.
 */
typedef enum Type_BlockHeapBlockJc_t
{
    /** It is a block which isn't managed in garbage collection, and isn't a block inside the
        the BlockHeap-management.
    */
  kNoBlockHeapBlockJc_Type_Object   = 0x0

    /** If this bit is set, the Object is considered in the garbage collector.
        If this bit is not set, it should be deleted manually.
    */
, mConsideredInGarbage_Type_Object = 0x4000

    /** If this bit is set, the Object is handled actually in the garbage collector.
        If this object is used, especially any new references to this Object is created,
        the garbage collector must be informed to abort the actually test.
    */
  , mHandledInGarbage_Type_Object    = 0x8000

    /** If all bits are set it is a small block.*/
  , mSmallBlock_Type_Object          = 0x3000

    /** If inside small block this bit is set, it is a MapEntryBlock.*/
  , kMapEntryBlock_Type_BlockHeapBlockJc       = 0x1000


    /**If this bit is set, the block has got at least one reference. */
  , mIsReferenced                    = 0x800

    /** The bits describing the used size of the block in element typeAndSize.
      * The size includes sizeof(BlockHeapBlockCtrl) and the size of the data.
      * After them the backward references are stored.
    */
  , mMaxRef_BlockHeapJc                = 0x07FF


    /** It is a free block in Runtimeheap. In this case the pointer reflectionClass
        is really the pointer of the next free block (chains up list of free blocks).
    */
  ,kFree_Type_BlockHeapBlock                = 0x07FE


    /** It is a block which isn't managed in garbage collection, but it is a block inside the
        the BlockHeap-management.
    */
  ,kNoRefUse_Type_Object            = 0x07FB

    /** Any value less than kIsSize means, inside the number of bytes is stored
        inside the attribute typeAndSize and the Object is managed by garbage collection.
        In this case, after the Object until the end of the BlockHeap block a array of
        back references is stored there. This value is in respect to mSize_Type_Object.

    */
  ,kIsSize_Type_Object              = 0x07F8
} Type_BlockHeapBlockJc;





#define kLastBlockInGarbageCtest_BlockHeapJc ((BlockHeapBlockJc*)(0xfffffeee))

/**This enum construct defines constants of bit masks used at ...TODO
   The element BlockHeapBlockCtrlJc.heapidxAndMaxref contains this values and bits.
*/
typedef enum HeapidxAndMaxref_ObjectJc_BlockHeap_t
{ mMaxRef_ObjectJc_BlockHeap = 0x3ff
, mHeapIdx_ObjectJc_BlockHeap = 0xfc00
, kBitHeapIdx_ObjectJc_BlockHeap = 10
}HeapidxAndMaxref_ObjectJc_BlockHeap;


/**This struct is opportune to show the array of back references in debugger. 
 * It will be not necessary for poor C-programming, already ObjectJcREF** is useable.
 * But this struct shows the array as array. The size of backRefs is fictitiously, use this struct only as pointer!
 */
typedef struct ObjectJcREFArray_t
{
  ObjectJcREF* data[10]; //fictitiously size, depends on typeOrMaxRef
} ObjectJcREFArray;

/** One block of the runtime Heap.
*/
typedef struct BlockHeapBlockJc_t
{



  /** The type and size info. This cell is used especially in the BlockHeap-management.
    * For simple Objects in normal heap or stack this value is set to 0.
    * *listeneintrag
    * @see Type_BlockHeapBlockJc (definition of enums in BlockHeapJc.h)
  */
  //uint16 typeAndSize;
  uint16 typeOrMaxRef;

  /** The number of the heap ctrl and the max nr of references,
    * if it is management by BlockHeapJc.
  */
  /** old:A ident number of the object. It may be the ident number of the creating component
      or a special number given by the users construction. This number may be helpfull by
      debugging in memory. It is only setted and is not used for algorith in the software.
  */
  uint16 heapidxAndMaxref;

  /**The nextBlock-pointer is used
   * *to reference the next free block in the queue of free blocks
   * *to reference the next tested block by running GC.
   */
  struct BlockHeapBlockJc_t* nextBlock; 
  
  /**The heap. */
  struct BlockHeapJc_t* heap; 
  

  /**The array of backrefs inside this block. */
  ObjectJcREFArray* backRefs;

  /**The object which uses this block. Before freed, finalize_Object is to be called. 
   * If it is null, there is allocated a non-ObjectJc-based instance.
   */
  ObjectJc* obj;

  /**pointer to a constant string, which helps to debug if a block is used and not freed.
   */
  const char* sCreaterInfo;

  /**Time of creation of usage this block. */
  int32 timeCreation;

  /**Reference to either the next free block or the next block in garbage collection test,
   * which references the tested blocks. This pointer is null if the block is used
   * and the garbage collector has not tested the block just now.
   * If the block is used and this reference is set, the garbage collector have to be signaled
   * about a new usage of the block.
   */
} BlockHeapBlockJc;

/**nr of bytes as overhead. */
#define nrofBytesHead_BlockHeapBlockJc sizeof(BlockHeapBlockJc)

#define deduce_BlockHeapBlockJc(ADDR) (BlockHeapBlockJc*)( ((intPTR)(ADDR)) & ~(SIZEBLOCK_BlockHeapJc-1));


bool checkSignificance_BlockHeapBlockJc(BlockHeapBlockJc* ythis, BlockHeapJc* ownHeap);


/** One block of the runtime Heap.
*/
typedef struct BlockHeapWholeBlockJc_t
{
  /**The control data of one block are outside the useable data for instances. 
   * It is the overhead for controlling the block heap. 
   */
  BlockHeapBlockJc blockCtrl;

  union
  { /**The users object is placed at begin. */
    ObjectJc userObject;
  
    //ObjectJcREF* backRefs[32]; //fictitiously size, depends on typeOrMaxRef

    ListMapEntryJc mapEntry[4];    //fictitiously size, depends on typeOrMaxRef

  } head;

  #define RESTSIZE_BlockHeapWholeBlockJc (0x100 - (4*sizeof(ListMapEntryJc) + sizeof(BlockHeapBlockJc))/4)

  int32 rest[RESTSIZE_BlockHeapWholeBlockJc];    //fictitiously size to 0x400 byte blocksize






  /** The control data are always used, on start of block.*/
  //BlockHeapBlockCtrlJc ctrl;

  /** data[0] is used for a chained list to detect if the block is free.
      The rest is useable for debugging. The size of the data array is an any desired number,
      well for debugging.
  */
  //int32 data[20];
} BlockHeapWholeBlockJc;



//use it only at pointer. The size is a fictitiously to see some blocks in debugger.
typedef struct BlockHeapBlockJc_debugArray_t
{ BlockHeapWholeBlockJc block[100];
}BlockHeapBlockJc_debugArray;



/*@CLASS_C BlockHeapJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/** A static pointer to a chained list of heap control structures. */
extern BlockHeapJc* theBlockHeapList;




/*======================= Methods =============================================*/

METHOD_C void addHeap_BlockHeapJc(BlockHeapJc* ythis);

METHOD_C bool initall_BlockHeapJc(int nrofHeaps);

METHOD_C void init_i_s_BlockHeapJc(int idxHeap, void* heap, int size);


/** private method, searches the appropriate BlockHeap and...*/
//see ObjectRefJc.h METHOD_C BlockHeapBlockJc* deduceBlockHeapBlockFromObject(void const* objP, BlockHeapJc** retHeap);


/** Returns true if the object is inside the given BlockHeap*/
//#define isInside_BlockHeapJc(ythis, obj) (obj >= (void*)(ythis->heapBegin) && obj < (void*)(ythis->heapEnd))



typedef struct BlockHeapJcARRAY_t
{ ObjectArrayJc head;
  BlockHeapJc* data[20];
}xxxBlockHeapJcARRAY;



#define BlockHeapJcARRAY_s(NRofELEMENTS) struct{ ObjectArrayJc array; BlockHeapJc* data[NRofELEMENTS];}



//#define BlockHeapJconst(NRofELEMENTS) { const_Array_Base(NRofELEMENTS, sizeof(BlockHeapJc*)), {0}}

/** Gets the element with given Index. The element is the value itself, of type 'int32'*/
//#define get_BlockHeapJca(ARRAY,IX) (*(BlockHeap**)(get_i_Array_Base(&ARRAY->array, IX)))

/** Sets the element with given Index*/
//#define set_BlockHeapJca(ARRAY,IX, VAL) (*(BlockHeapJc**)(get_i_Array_Base(&((ARRAY)->array), IX)) = VAL)

/** Gets the sizeof of the instance with given nr of elements. It is a static-like method.
 * @param SIZE number of elements
*/
#define SIZEOF_BlockHeapJcARRAY(SIZE) (sizeof(ObjectArrayJc) + SIZE * sizeof(BlockHeapJc**))

/** Create a new Instance with the given number of elements
 * @param size number of elements
*/

//METHOD_C BlockHeapJcARRAY* new_BlockHeapJcARRAY(int size);

/*@CLASS_C GarbageCollectorJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct GarbageCollectorJc_t
{
  int idxBlock;

  int32 idxReportBuffer;
  char reportBuffer[1000];

  /**The actual tested heap. */
  BlockHeapJc* testedHeap;



  /**A method to call inside Garbage Collection to test some special cases.
   * The int param is the number of step.
   */
  MT_int_Method_int testMethod;

  /**Counts the number of steps in test each block in a cluster, use to test. */
  int32 countStep;

  /**If this variable is set, the actual test of clusters is to be aborted,
   * because a already tested and therefore not used block is used new.
   */
  int8 bAbortTest;
  int8 bAbortTestBecauseUserCall;
  int8 dummy[2]; //alignment.

  int32 ctFreeBlocks;
  int32 ctNonGcBlocks;

  int32 ctFreedBlocks;
  int32 ctUsedBlocks;

  OS_TimeStamp startTime, endTime;

  /**A LogMessage output for all garbage collection and allocation operations. It is a copy from actual BlockHeapJc. */
  struct LogMessageFW_t* log;

  int kIdentMsgBase;

}GarbageCollectorJc;

/**A singleton instance exists. */
extern GarbageCollectorJc theGarbageCollectorJc;



#define identMsgReport_BlockHeapJc 1
#define identMsgAlloc_BlockHeapJc 2

#define identMsgGcWork_BlockHeapJc 4
#define identMsgBlockFree_BlockHeapJc 5
#define identMsgBlockNoGc_BlockHeapJc 6
#define identMsgBlockUsed_BlockHeapJc 7
#define identMsgReportBlocks_BlockHeapJc 8  //user called GC





#endif //__BlockHeapJc_i_h__
