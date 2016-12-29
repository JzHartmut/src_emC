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
 *
 * @content: Implementation of BlockHeap-organization and allocation memory.
 *
 * @author JcHartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2008-04-15: JcHartmut creation from older sources
 *
 ****************************************************************************/
//#include "CRuntimeJavalike.h"
//#include "ThreadJc.h"
#include "BlockHeapJc_internal.h"
#include "Jc/StringJc.h"
#include "Fwc/fw_LogMessage.h"
#include <os_time.h>
#include "Fwc/fw_Exception.h"
#include <os_AtomicAccess.h>
#include <BlockHeap_PlatformSpec.h>

//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <Jc/ListMapEntryJc.h>  //definition of methods


static BlockHeapBlockJc* allocBlock_BlockHeapJc(BlockHeapJc* ythis, int sizeObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt);

//debug
static int stop()
{ return 5;
}

#define TESTMulitThread__
#ifdef TESTMulitThread__

  bool isTEST = false;
  BlockHeapBlockJc* testBlock;
  ListMapEntryJc* testNode;
  ListMapEntryJc* testNodes[100];
  int testCtListMapEntry = 0;

  void TEST_allocListMapEntrySecondThread(struct NodePoolJc_t* ithis, ThCxt* _thCxt)
  { if(!isTEST && ++testCtListMapEntry == 1){
      isTEST = true; //prevent recursively call
      testNode = alloc_ListMapEntryJc(ithis, _thCxt); 
      isTEST = false;
    }
  }

  void TEST_allocBlockSecondThread(BlockHeapJc* ythis, ThCxt* _thCxt)
  { if(!isTEST){
      isTEST = true; //prevent recursively call
      testBlock =  allocBlock_BlockHeapJc(ythis, 100, 10, "TEST_allocSecondThread", _thCxt);
      isTEST = false;
    }
  }


  void testLastAccess(struct NodePoolJc_t* ithis, ThCxt* _thCxt)
  { int ctAccess;
    for(ctAccess = 0; ctAccess < 50; ++ctAccess){
      testNodes[ctAccess] = alloc_ListMapEntryJc(ithis, _thCxt);
    }
    while(--ctAccess >=0){
      if(testNodes[ctAccess] != null){
        free_ListMapEntryJc(ithis, testNodes[ctAccess], _thCxt);
        testNodes[ctAccess] = null;
      } 
    }

  }


  /**Gaves free 1 node, which was allocated by testLastAccess(...)
   * to disturn the access.
   */
  void TEST_free1BlockListMapEntrySecondThread(struct NodePoolJc_t* ithis, ThCxt* _thCxt)
  {
    if(testNodes[5] != null){
      free_ListMapEntryJc(ithis, testNodes[5], _thCxt);
      testNodes[5] = null;
    } 
    
  }

#else
  #define TEST_allocSecondThread(XX)
#endif

static ListMapEntryJc* initMapEntryNodes_BlockHeapJc(BlockHeapJc* ythis, ThCxt* _thCxt);


#if defined(mBackRef_REF_ObjectJc)
  /**Definition of the methods setBackRef_ObjectJc and clearBackRef_ObjectJc inside.
    * It is possible that this file is not available in the user system.
    * Therefore do not include if not necessary.
  */
  //#include "ObjectrefJc.h"
#endif
//#include "ThreadJc.h"

#include "Fwc/fw_Exception.h"

typedef enum EBlockType_t
{
  kSizeSmallBlock_BlockHeap = 0x7e
, kReferencesStd_BlockHeap = 10
}EBlockType;


//BlockHeapJc* current_BlockHeapJc = null;



BlockHeapJc* current_BlockHeapJc(ThCxt* _thCxt)
{ return _thCxt->blockHeap;
}

BlockHeapJc* theBlockHeapList = null;


BlockHeapJc* setCurrent_BlockHeapJc(BlockHeapJc* heap, ThCxt* _thCxt)
{ BlockHeapJc* last = _thCxt->blockHeap;
  _thCxt->blockHeap = heap;
  return last;
}


METHOD_C void addHeap_BlockHeapJc(BlockHeapJc* ythis)
{
  ythis->nextHeap = theBlockHeapList;
  theBlockHeapList = ythis;
}


BlockHeapJc* first_BlockHeapJc()
{ return theBlockHeapList;
}

//static const int mBeginBlock_BlockHeap = ~(kSizeNormalBlock_BlockHeap-1);


/**Reference to the array of all control structures of BlockHeaps. */
//BlockHeapJcARRAY* all_BlockHeap;




#define kOffsetData_BlockHeapBlockJc 0



#if defined(mBackRef_REF_ObjectJc)
  /** To support debugging, a type of REFP_ObjectJc-array is defined and used inside.
    * The number of elements is a arbitrary number, convenient for debugging.
    * The really number of elements is determined by using.
    */
  typedef REF_ObjectJc* REF_ObjectJc_array[20];
#endif


/*
xxxBlockHeapJcARRAY* new_BlockHeapJcARRAY(int nrofElements)
{ int nrofBytes = SIZEOF_BlockHeapJcARRAY(nrofElements);
  xxxBlockHeapJcARRAY* ptr = (xxxBlockHeapJcARRAY*)(alloc_MemC(nrofBytes).address);
  if(ptr != null)
  { ctor_ObjectArrayJc(&ptr->head, nrofElements, sizeof(BlockHeapJc), null, 0);
  }
  return ptr;
}
*/
/*
void* alloc_sBlockHeapJc(int size)
{ void* ptr;
  STACKTRC_ENTRY("alloc_sBlockHeapJc");
  if(current_BlockHeapJc != null)
  { ptr = alloc_BlockHeapJc(current_BlockHeapJc, size);
  }
  else
  { ptr = mallocFromOpSysJc(size);
  }
  STACKTRC_LEAVE; return(ptr);
}
*/
//BlockHeapJc* theDefaultBlockHeap;

/*
bool initall_BlockHeapJc(int nrofHeaps)
{ int nrofByteAllHeaps = sizeof_BlockHeapJcARRAYd(nrofHeaps);
  STACKTRC_ENTRY("initall_BlockHeap");

  all_BlockHeap = (BlockHeapJcARRAYd*)mallocFromOpSysJc(nrofByteAllHeaps);
  if(all_BlockHeap == null) THROW(RuntimeException, "no memory", false);
  all_BlockHeap->array.length = nrofHeaps;
  all_BlockHeap->array.sizeElement = sizeof(BlockHeapJc);
  //all_BlockHeap->array.mode = kDirect_ObjectArrayJc;
  memset(all_BlockHeap->data, 0, nrofHeaps * sizeof(BlockHeapJc));
  STACKTRC_LEAVE; return true;
}



void init_i_s_BlockHeapJc(int idxHeap, MemUnit* heap, int sizeHeap)
{
  BlockHeapJc* heapCtrl = get_BlockHeapJcARRAYd(all_BlockHeap, idxHeap);
  MemC memHeap = { sizeHeap, (struct MemAreaC_t*)heap};
  MemC memCtrl = { sizeof(BlockHeapJc), (struct MemAreaC_t*)heapCtrl};
  ctor_BlockHeapJc(memCtrl, memHeap, 0x400, 0x40);
}
*/

METHOD_C BlockHeapJc* ctorO_BlockHeapJc(ObjectJc* othis, MemC wholeHeap, int bytesNormalBlock, int bytesSmallBlock)
{
  BlockHeapJc* ythis = (BlockHeapJc*)othis;
  
  int zBlock;
  struct MemAreaC_t* heap = PTR_MemC(wholeHeap, struct MemAreaC_t);
  int sizeHeap = size_MemC(wholeHeap);
  STACKTRC_ENTRY("ctor_BlockHeapJc");
  checkConsistence_ObjectJc(othis, sizeof(BlockHeapJc), &reflection_BlockHeapJc, _thCxt); 
  
  init0_MemC(wholeHeap);

  //:TODO: Test signifity of bytesNormalBlock and bytesSmallBlock!

  //SIZEBLOCK_BlockHeapJc = bytesNormalBlock;
  //ythis->mAdressNormalBlock_BlockHeap = ~(bytesNormalBlock -1);

  ythis->bytesSmallBlock = bytesSmallBlock;
  ythis->mAdressSmallBlock_BlockHeap = ~(bytesSmallBlock -1);

#ifdef HEAP_BEGINSATPOWER2_RUNTIMEHEAP
  //than all blocks start at a address which is alligned at the size of a block.
  //the deducing from any address inside the block to the begin of the block
  //is only a simple mask of address-bits then.
  if( ((intPTR)heap & (SIZEBLOCK_BlockHeapJc-1)) != 0)
  { //if the heap donot starts at a address with mask boundary, increment the address to the next boundary
    heap = (struct MemAreaC_t*)( ((int32)heap & ~(SIZEBLOCK_BlockHeapJc-1)) + bytesNormalBlock );
    //and reduce the number of blocks, because the end address should be less than the given one.
    sizeHeap -= bytesNormalBlock;
  }
#endif
  ythis->zBlock = zBlock = sizeHeap / bytesNormalBlock;
  ythis->heapBegin = (BlockHeapBlockJc_debugArray*)heap;
  ythis->heapEnd   = addOffset_MemAreaC(ythis->heapBegin, zBlock * bytesNormalBlock);


  //ythis->theGarbageCollectorThread = Thread::new_(ythis, "GarbageCollector");
  //ythis->theGarbageCollectorThread->setPriority(Thread::NORM_PRIORITY -1);

  //if(heap==0) throw new RuntimeException("BlockHeap::init(): no mem");

  //Object__BaseRefef::BlockHeapEnd = (MemUnit*)(heap) + zBlock * kSizeNormalBlockHeapBlockJc;

  ythis->firstFreeBlock = (BlockHeapBlockJc*)(heap);

  { //mark all free Blocks with a single linked list
    BlockHeapBlockJc* block = ythis->firstFreeBlock;
    int ii;
    for(ii=1; ii< zBlock; ii++)  //take the next block
    { BlockHeapBlockJc* nextBlock = (BlockHeapBlockJc*)(&((MemUnit*)heap)[ii * bytesNormalBlock]);
      block->heap = ythis;
      //bbb block->ctrl.typeAndSize = (int16)kFree_Type_BlockHeapBlock;
      block->typeOrMaxRef = kFree_Type_BlockHeapBlock;
      //bbb *(BlockHeapBlockJc**)(&block->data[0]) = nextBlock;
      block->nextBlock = nextBlock;
      block = nextBlock;
    }
    //handle the last block
    block->heap = ythis;
    //bbb block->ctrl.typeAndSize = (int16)kFree_Type_BlockHeapBlock;
    block->typeOrMaxRef = kFree_Type_BlockHeapBlock;
    //bbb block->data[0] = 0;     //the last block has no next.
    block->nextBlock = null;  //the last block has no next.
    //ythis->lastFreeBlock = block;  //append a free becoming block here.
  }

  //iLastSmallBlock = 0;
  //iNextNormalBlock = 1;


  initMapEntryNodes_BlockHeapJc(ythis, _thCxt);

  /*
  if(current_BlockHeapJc == null)
  { //the first initialized blockheap is the current.
    current_BlockHeapJc = ythis;
  }
  */

  //insert this heap in the chain of heaps.
  ythis->nextHeap = theBlockHeapList;  //null if it is the first one.
  theBlockHeapList = ythis;
  STACKTRC_LEAVE;
  return ythis;

}



bool checkSignificance_BlockHeapBlockJc(BlockHeapBlockJc* ythis, struct BlockHeapJc_t * ownHeap)
{
  ObjectJc* heapObj;
  if(ownHeap == null){ ownHeap = ythis->heap; }
  heapObj = &ownHeap->base.object;

  ASSERT(ownHeap == ythis->heap && ownHeap != null);

  ASSERT(instanceof_ObjectJc(heapObj, &reflection_BlockHeapJc));
  return true;
}


void setRunMode_BlockHeapJc(BlockHeapJc* ythis, struct LogMessageFW_t* log, int kIdentMsgBase)
{ ythis->log = log;
  ythis->kIdentMsgBase = kIdentMsgBase;

  ythis->bitInitMode = 0x1234abcd;
}



MemC alloc_s_sBlockHeapJc(int sizeObj, const char* sCallInfo, ThCxt* _thCxt)
{ //STACKTRC_NAME("alloc_s_BlockHeap")
  return alloc_iis_BlockHeapJc(current_BlockHeapJc(_thCxt), sizeObj, kReferencesStd_BlockHeap, sCallInfo, _thCxt);
}


ObjectJc* allocObject_s_sBlockHeapJc(int sizeObj, int identObj, const char* sCallInfo, ThCxt* _thCxt)
{ //STACKTRC_NAME("alloc_s_BlockHeap")
  return allocObject_IIs_BlockHeapJc(current_BlockHeapJc(_thCxt), sizeObj, identObj, kReferencesStd_BlockHeap, sCallInfo, _thCxt);
}


ObjectJc* alloc_ObjectJc(const int size, const int32 typeInstanceIdent, ThCxt* _thCxt)
{ ObjectJc* othis;
  STACKTRC_TENTRY("alloc_ObjectJc");
  { const char* sCallingMethodName = getCallingMethodName_StacktraceThreadContext( &_thCxt->stacktrc, 1);  
    othis = allocObject_s_sBlockHeapJc(size, typeInstanceIdent, sCallingMethodName, _thCxt);
  }
  STACKTRC_LEAVE; return othis;
}





int setRunMode_ObjectJc(ThCxt* _thCxt)
{
  BlockHeapJc* blockHeap = theBlockHeapList;
  while(blockHeap !=null){
    setRunMode_BlockHeapJc(blockHeap, null, 0);
    blockHeap = blockHeap->nextHeap;
  }
  return 0;
}

MemC alloc_s_BlockHeapJc(BlockHeapJc* ythis, int sizeObj, const char* sCallInfo, ThCxt* _thCxt)
{ //STACKTRC_NAME("alloc_BlockHeap")
  return alloc_iis_BlockHeapJc(ythis, sizeObj, kReferencesStd_BlockHeap, sCallInfo, _thCxt);
}




MemC alloc_iis_BlockHeapJc(BlockHeapJc* ythis, int sizeObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt)
{ ObjectJc* obj = allocObject_IIs_BlockHeapJc(ythis, sizeObj, -1, nrofReferences, sCallInfo, _thCxt); 
  MemC ret = build_MemC(obj, getSizeInfo_ObjectJc(obj));
  return ret;
}


/**Allocates one block. 
 * @param sizeObj detects whether a small block is sufficient. Determines the nrofReferences.
 *        special specification: -1: use a normal block with given nrofReferences
 *                               -2: use a small block with given nrofReferences
 * @param nrofReferences: The minimum of number of references to all objects, which should be stored in the block.
 *        If the sizeObj is less, more references can be stored. It is because, the size of the block is constant.
 * @return the Block.
 */
static BlockHeapBlockJc* allocBlock_BlockHeapJc(BlockHeapJc* ythis, int sizeObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt)
{ BlockHeapBlockJc* retBlock;
  //ObjectJc* retObj;
  bool bRetry;
  STACKTRC_TENTRY("alloc_ii_BlockHeap");
  if(sizeObj == -1)
  { //BBB sizeObj = SIZEBLOCK_BlockHeapJc - sizeof(BlockHeapBlockCtrlJc) - nrofReferences * sizeof(ObjectJc*);
    sizeObj = SIZEBLOCK_BlockHeapJc - nrofBytesHead_BlockHeapBlockJc - nrofReferences * sizeof(ObjectJcREF*);
  }
  else if(sizeObj == -2)
  { sizeObj = kSizeSmallBlock_BlockHeap - nrofReferences * sizeof(ObjectJcREF*);
  }
  do {
    int maxRef = 0;
    int sizeBlock = 0;
    int minSizeBlock = nrofBytesHead_BlockHeapBlockJc + sizeObj + nrofReferences * sizeof(ObjectJcREF*);  //add the size of the references array to the requested size.
    retBlock = null;
    if(minSizeBlock > (SIZEBLOCK_BlockHeapJc - kOffsetData_BlockHeapBlockJc))
     THROW_s0(RuntimeException, "BlockHeap::alloc(): size to large", minSizeBlock);
    else if(minSizeBlock >= 0) //Object::kSizeNormalBlockHeapBlockJc / 8)
    { //after the atomare instruction the first Free Block is no longer available
      //for other threads. So no lock are necessary.
      //bbb maxRef = (SIZEBLOCK_BlockHeapJc - sizeof(BlockHeapBlockCtrlJc) - sizeObj) / sizeof(ObjectJc*);
      bool bSuccess;
      int catastrophicRepeatCount = 1000;
      sizeBlock = SIZEBLOCK_BlockHeapJc;
      maxRef = (sizeBlock - nrofBytesHead_BlockHeapBlockJc - sizeObj) / sizeof(ObjectJcREF*);
      //disableSwitch_Thread();
      do
      { retBlock = ythis->firstFreeBlock;
        if(retBlock !=null)
        { void* nextFreeBlock = retBlock->nextBlock;
          //try to set the next block as newly first one:
          /*
          int lastValue;
          int ref = (int)(ythis->firstFreeBlock);
          XcompareAndSwap_AtomicInteger(lastValue, ref, retBlock, nextFreeBlock);
          */
          bSuccess = compareAndSet_AtomicReference(CAST_AtomicReference(ythis->firstFreeBlock), retBlock, nextFreeBlock);
        }
        else { bSuccess = true; } //no block, no change.

      } while(!bSuccess && --catastrophicRepeatCount >=0);  //repeat if compareAndSet fails.
      if(catastrophicRepeatCount < 0){
        THROW_s0(RuntimeException,"compareAndSet-fail",0);
      }
    }
    else
    { //small block
      maxRef = 0x1;
      sizeBlock = 0x1; //TODO
    }
    if(retBlock != null)
    { bRetry = false;
      memset(retBlock, 0, sizeBlock);
      retBlock->typeOrMaxRef = (int16)maxRef;
      #ifdef __RUNTIMEHEAP_TEST__
        retBlock->references__debug = null;
      #endif
      retBlock->heap = ythis;
      retBlock->heapidxAndMaxref = (int16)(maxRef + (ythis->idxHeapCtrl << kBitHeapIdx_ObjectJc_BlockHeap));
      retBlock->nextBlock  = null;  //NOTE: it had contain the pointer to the next retBlock and is now used as backRef
      retBlock->sCreaterInfo = sCallInfo;
      retBlock->timeCreation = os_getDateTime().time_sec;
      retBlock->backRefs = (ObjectJcREFArray*)addOffset_MemAreaC(retBlock,  sizeof(BlockHeapBlockJc));
      //bbb ret.address = (struct MemAreaC_t*)(block->data);  //returns the Adress of data within BlockHeapBlockJc
    }
    else
    { /**No free block found. */
      retBlock = null;
      bRetry = runUserCalledGc_BlockHeapJc(_thCxt);
      if(!bRetry) {
        retBlock = null;
        THROW_s0(RuntimeException, "BlockHeap::alloc(): no memblock", 0);
      }
    }
  }while(retBlock == null && bRetry);  //repeat it if a block isn't found but the garbage collector was successfull.
  STACKTRC_LEAVE; return retBlock;
}



MemC allocMemC_BlockHeapJc(BlockHeapJc* ythis, int sizeObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt)
{ MemC ret;
  if(ythis == null || ythis->bitInitMode != 0x1234abcd)
  { //init-mode
    ret = alloc_MemC(sizeObj);
  }
  else
  { //alloc a Block in the BlockHeap-pool:
    void* retBlock;
    int offsetObjToBlock = SIZEBLOCK_BlockHeapJc - sizeObj;
    BlockHeapBlockJc* block = allocBlock_BlockHeapJc(ythis, sizeObj, nrofReferences, sCallInfo, _thCxt);
    if(block !=null) {
      //arrange the data at end of the block!
      retBlock = addOffset_MemAreaC(block, offsetObjToBlock);;
      set_MemC(ret, retBlock, sizeObj);
    } else {
      set_MemC(ret, null, 0);
    }
  }
  return ret;
}



ObjectJc* allocObject_IIs_BlockHeapJc(BlockHeapJc* ythis, int sizeObj, int identObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt)
{ ObjectJc* retObj;
  if(sizeObj == -1)
  { sizeObj = SIZEBLOCK_BlockHeapJc - nrofBytesHead_BlockHeapBlockJc - nrofReferences * sizeof(ObjectJcREF*);
  }
  else if(sizeObj == -2)
  { sizeObj = kSizeSmallBlock_BlockHeap - nrofReferences * sizeof(ObjectJcREF*);
  }
  if(ythis == null || ythis->bitInitMode != 0x1234abcd)
  { retObj = PTR_MemC(alloc_MemC(sizeObj), ObjectJc);
    if(retObj !=null){
      init_ObjectJc(retObj, sizeObj, identObj);
    }
  }
  else
  { //alloc a Block in the BlockHeap-pool:
    int offsetObjToBlock = SIZEBLOCK_BlockHeapJc - sizeObj;
    BlockHeapBlockJc* block = allocBlock_BlockHeapJc(ythis, sizeObj, nrofReferences, sCallInfo, _thCxt);
    if(block !=null) {
      //arrange the data at end of the block!
      retObj = SIMPLE_CAST(ObjectJc*, addOffset_MemAreaC(block, offsetObjToBlock));
      ctorc_ObjectJc(retObj);
      setSizeAndIdent_ObjectJc(retObj, sizeObj, identObj);
      block->obj = retObj;  //notice the pointer to the allocating Object, to run finalize if it is freed.
      //necessary ? retObj->blockHeapBlock = block;
      if(ythis->log != null)
      {
        /**It isn't good, because that complex algorithm may alloc too. TODO: sendmsg without any alloc here or special solution */
        sendMsg_tzzv_LogMessageFW(ythis->log, ythis->kIdentMsgBase + identMsgAlloc_BlockHeapJc, os_getDateTime()
          , "alloc_BlockHeap; block=%p; size=%d; id=%d; caller=%s; firstFree %p"
          , "PIIzP", block, sizeObj, identObj, sCallInfo, ythis->firstFreeBlock
          ); 
      }
    } else {
      retObj = null;
    }
  }
  return retObj;
}




  
void free_BlockHeapJc(BlockHeapJc* ythis, BlockHeapBlockJc* block, ThCxt* _thCxt)
{ bool bSuccess;
  int catastrophicRepeatCount = 1000;
  BlockHeapBlockJc* firstFreeBlockCurrent;
  STACKTRC_TENTRY("free_BlockHeapJc");
  block->typeOrMaxRef = kFree_Type_BlockHeapBlock;
  block->heapidxAndMaxref = 0;
  do {
    firstFreeBlockCurrent = ythis->firstFreeBlock;  //may be null, if heap is empty.
    //bbb block->ctrl.typeAndSize = kFree_Type_BlockHeapBlock;
    //bbb block->data[0] = 0;
    block->nextBlock = firstFreeBlockCurrent;  //the current first will be the second then.
    bSuccess = compareAndSet_AtomicReference(CAST_AtomicReference(ythis->firstFreeBlock), firstFreeBlockCurrent, block);
  } while(!bSuccess && --catastrophicRepeatCount >=0);
  if(catastrophicRepeatCount < 0){
    THROW_s0(RuntimeException,"compareAndSet-fail",0);
  }
  STACKTRC_LEAVE;
}




bool free_sBlockHeapJc(void const* obj, ThCxt* _thCxt)
{
  BlockHeapJc* heap = null;
  BlockHeapBlockJc* block;
  
  block = searchBlockHeapBlock_BlockHeapJc(obj, &heap);
  if(heap != null)
  { free_BlockHeapJc(heap, block, _thCxt);
    return true;
  }
  else
  { //not a block from BlockHeap, use free
    return false;
  }
}





MemC getRestBlock_ObjectJc(ObjectJc* ythis, int size, ThCxt* _thCxt)
{ MemC retMem;
  STACKTRC_TENTRY("restSizeBlock_ObjectJc");
  { BlockHeapJc* retHeap;
    BlockHeapBlockJc* block = searchBlockHeapBlock_BlockHeapJc(ythis, &retHeap);
    if(block == null)
    { set_MemC(retMem, 0, null);
    }
    else
    { int nrofBytes;
      int nrofBackRefs;
      void* addr;
      if(size < 0)
      { nrofBackRefs = -size;
        nrofBytes = ((block->typeOrMaxRef & mMaxRef_BlockHeapJc) - nrofBackRefs) * sizeof(ObjectJcREF**);
      }
      else
      { nrofBytes = size;
        nrofBackRefs = (block->typeOrMaxRef & mMaxRef_BlockHeapJc) - (nrofBytes * sizeof(ObjectJcREF**));
      }
      if(nrofBytes <0 || nrofBackRefs < 0) THROW_s0(IllegalArgumentException, "unaccomplishable request of rest block size", size);
      block->typeOrMaxRef = (int16)((block->typeOrMaxRef & ~ mMaxRef_BlockHeapJc) | nrofBackRefs);
      addr = addOffset_MemAreaC(ythis, -nrofBytes);
      set_MemC(retMem, addr, nrofBytes);
    }
  }
  STACKTRC_LEAVE; return retMem;
}



void setLogMessageOutput_BlockHeapJc(struct LogMessageFW_t* log, int msgBase, ThCxt* _thCxt)
{ 
  
  BlockHeapJc* currentBlockHeap = _thCxt->blockHeap;
  currentBlockHeap->log = log;
}





/*****************************************************************************
*
*
*/



#include "Jc/ListMapEntryJc.h"  //includes pkgSystem/Object.h, pkgSystem/String.h





typedef struct XXXMapEntryBlockJc_t
{ ObjectJc object;
  //friend class BlockHeap;
  /** a defined Nr of MapEntry_*/

  /** The really number of entries depends on the actual size of a runtimeheap block*/
  ListMapEntryJc entries[ 20//( BlockHeap::kSizeNormalBlockHeapBlockJc    //size of a block altogether
                      //- sizeof(ObjectJc)     //baseclass of this class
                      //) / sizeof(MapEntryJc)
                   ];   //count of chars defined in src.
  //virtual ~MapEntryBlock(){}
}XXXMapEntryBlockJc;


struct NodePoolJc_t* current_NodePool_ListMapEntryJc(struct ThreadContextFW_t* _thCxt)
{ return (struct NodePoolJc_t*) current_BlockHeapJc(_thCxt);
}



static ListMapEntryJc* initMapEntryNodes_BlockHeapJc(BlockHeapJc* ythis, ThCxt* _thCxt)
{ ListMapEntryJc* retBlock;
  int ixNode;
  int nrofNode = (SIZEBLOCK_BlockHeapJc - sizeof(BlockHeapBlockJc)) / sizeof(ListMapEntryJc);
  ListMapEntryJc* next;
      
  BlockHeapBlockJc* block = allocBlock_BlockHeapJc(ythis, -1, 0, "alloc_ListMapEntryJc", _thCxt);
  block->typeOrMaxRef = kMapEntryBlock_Type_BlockHeapBlockJc + 1;
  //data content of the allocated block is newBlock,
  retBlock = (ListMapEntryJc*)(block+1);  //casting: address after head
  if(ythis->firstMapEntry == null){
    //it is initial
    ASSERT(ythis->lastMapEntry == null);
    ythis->firstMapEntry = ythis->lastMapEntry = retBlock;
  }
  //the retBlock is the first block of 
  //retBlock = &newBlock->entries[0]; 
  for(ixNode = 1; ixNode < nrofNode; ++ixNode){ 
    next = &retBlock[ixNode];
    //free all new blocks upon the next.
    free_ListMapEntryJc((struct NodePoolJc_t*)ythis, next, _thCxt);
  }
  return retBlock;
}





ListMapEntryJc* alloc_ListMapEntryJc(struct NodePoolJc_t* ithis, ThCxt* _thCxt)
{ BlockHeapJc* ythis = (BlockHeapJc*)ithis;  //conversion allowed because the reference is getted with current_NodePool_ListMapEntryJc
  ListMapEntryJc* retBlock;
  ListMapEntryJc* secondBlock;
  //ListMapEntryJc* nextBlock;
  ListMapEntryJc* lastBlock;
  //ObjectJc* retObj;
  //bool bRetry;
  STACKTRC_TENTRY("alloc_ii_BlockHeap");
  //do {
    retBlock = null;
    { //after the atomare instruction the first Free Block is no longer available
      //for other threads. So no lock are necessary.
      //bbb maxRef = (SIZEBLOCK_BlockHeapJc - sizeof(BlockHeapBlockCtrlJc) - sizeObj) / sizeof(ObjectJc*);
      bool bSuccess = false;
      int catastrophicRepeatCount = 1000; 
      do
      { retBlock = ythis->firstMapEntry;
        lastBlock = ythis->lastMapEntry;
        secondBlock = retBlock->next;
        if(retBlock == lastBlock){
          //only one node in list, it has to remain there.
          if(secondBlock == null){
            retBlock = null;
            bSuccess = true;  //no block, no change. It is success regarding atomic-trying.
          } else {
            //the first block have a next, though fist == last. 
            //It means, that this thread has interrupted another thread, 
            //which has added a free block, but it hasn't adjust the lastMapEntry-ref just now.
            //adjust it instead. The try again.
            compareAndSet_AtomicReference(CAST_AtomicReference(ythis->lastMapEntry), lastBlock, secondBlock);  
          }
        } else {
          //fist and lastMapEntry referes to different nodes, There should be a node available!
          //try to set the next block as newly first one:
          bSuccess = compareAndSet_AtomicReference(CAST_AtomicReference(ythis->firstMapEntry), retBlock, secondBlock);
        }
      } while(!bSuccess && --catastrophicRepeatCount >=0);  //repeat if compareAndSet fails.
      if(catastrophicRepeatCount < 0){
        THROW_s0(RuntimeException,"compareAndSet-fail",0);
      }  
    }
    if(retBlock == null){
      //nolistMapEntry-Block available, then allocated a normal block and use it for ListMapEntries:
      //MapEntryBlockJc* newBlock;
      retBlock = initMapEntryNodes_BlockHeapJc(ythis, _thCxt);
    
    }
  //}while(retBlock == null && bRetry);  //repeat it if a block isn't found but the garbage collector was successfull.
  STACKTRC_LEAVE; return retBlock;
}



void free_ListMapEntryJc(struct NodePoolJc_t*ithis, ListMapEntryJc* node, struct ThreadContextFW_t* _thCxt)
{ BlockHeapJc* ythis = (BlockHeapJc*)ithis;  //conversion allowed because the reference is getted with current_NodePool_ListMapEntryJc
  bool bSuccess;
  int catastrophicRepeatCount = 1000;
  BlockHeapBlockJc* block;
  int nrofFreeNodesInBlock;
  //The next value is a constant, calculated by compiler:
  int halfNrofNodesInBlock = ((SIZEBLOCK_BlockHeapJc-sizeof(BlockHeapBlockJc))/sizeof(ListMapEntryJc)/2);
  STACKTRC_TENTRY("free_BlockHeapJc");
  
  block = deduce_BlockHeapBlockJc(node);
  checkSignificance_BlockHeapBlockJc(block, ythis);
  node->allocater = null;
  nrofFreeNodesInBlock = block->typeOrMaxRef & mMaxRef_BlockHeapJc;
  
  if(nrofFreeNodesInBlock > halfNrofNodesInBlock)
  { //append the node on end if the block has more as half nodes non-allocated. 
    //Than this block isn't used to get a next node, but another.
    //So statistically, this block get all nodes free, 
    //and than it can be freed as whole block.
    node->next = null;  //add as last node, it mustn't reference any other.
    do{
      ListMapEntryJc* tail = ythis->lastMapEntry;
      ListMapEntryJc* next = tail->next;
      bSuccess = false;  //TODO test it.
      if(tail == ythis->lastMapEntry){
        if(next == null){
          if(compareAndSet_AtomicReference(CAST_AtomicReference(tail->next), next, node)){
            compareAndSet_AtomicReference(CAST_AtomicReference(ythis->lastMapEntry), tail, node);
            bSuccess = true;
         }
        } else {
          //The thread has interrupted another access to the the lastMapEntry reference,
          //before the lastMapEntry was set to the really end.
          //Therefore: //set the lastMapEntry to the next found strange entry.
          //after them the test will be repeated so long as next == null.
          compareAndSet_AtomicReference(CAST_AtomicReference(ythis->lastMapEntry), tail, next);
      } }
    } while(!bSuccess && --catastrophicRepeatCount >=0);
  } else {
    //append the node on top if the block has more as half nodes allocated..
    do {
      ListMapEntryJc* firstFreeNodeCurrent;
      firstFreeNodeCurrent = ythis->firstMapEntry;  //may be null, if heap is empty.
      node->next = firstFreeNodeCurrent;            //the current first will be the second then.
      bSuccess = compareAndSet_AtomicReference(CAST_AtomicReference(ythis->firstMapEntry), firstFreeNodeCurrent, node);
      if(bSuccess && firstFreeNodeCurrent == ythis->lastMapEntry){
        //the list was empty, now
        stop();
      }
      //The lastFreeNodeCurrent isn't affected, at least it references the only one node before enqueue.
    } while(!bSuccess && --catastrophicRepeatCount >=0);
  }
  block->typeOrMaxRef +=1;  //count up free blocks.
  ASSERT((block->typeOrMaxRef & mSmallBlock_Type_Object)==kMapEntryBlock_Type_BlockHeapBlockJc); //it will be faulty if the count of blocks fails.
  if(catastrophicRepeatCount < 0){
    THROW_s0(RuntimeException,"compareAndSet-fail",0);
  }
  STACKTRC_LEAVE;
}



#if 0
/** redirect malloc*/
void * malloc(size_t size)
//void* malloc(size_t size)
{ return mallocFromOpSysJc(size);
}


void free(void* ptr)
{ freeFromOpSysJc(ptr);
}
#endif

#if defined(xx__CPLUSPLUSJcpp) && defined(__cplusplus)
  void* ::new(size_t size)
  { return mallocFromOpSysJc(size);
  }

  void ::delete(void* ptr)
  { freeFromOpSysJc(ptr);
  }
#endif  //__CPLUSPLUSJcpp



