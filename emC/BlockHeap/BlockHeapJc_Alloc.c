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
#include "emC/Jc/StringJc.h"
//#include "emC/Base/LogMessage.h"
#include <emC/OSAL/os_time.h>

#include <emC/OSAL/os_AtomicAccess.h>
//#include <BlockHeap_PlatformSpec.h>

#ifdef USE_BlockHeap_emC


//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <emC/Jc/ListMapEntryJc.h>  //definition of methods




#ifdef DEF_REFLECTION_FULL
ClassJc const reflection_BlockHeap_emC = INIZtypeOnly_ClassJc(reflection_BlockHeap_emC, "relection_BlockHeap_emC");

#else //not DEF_REFLECTION_FULL

ClassJc const reflection_BlockHeap_emC = INIZtypeOnly_ClassJc(reflection_BlockHeap_emC, "relection_BlockHeap_emC");

#endif //not DEF_REFLECTION_FULL


static BlockHeapBlockJc* allocBlock_BlockHeap_emC(BlockHeap_emC_s* thiz, int sizeObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt);

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

  void TEST_allocBlockSecondThread(BlockHeap_emC_s* thiz, ThCxt* _thCxt)
  { if(!isTEST){
      isTEST = true; //prevent recursively call
      testBlock =  allocBlock_BlockHeap_emC(thiz, 100, 10, "TEST_allocSecondThread", _thCxt);
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

static ListMapEntryJc* initMapEntryNodes_BlockHeap_emC(BlockHeap_emC_s* thiz, ThCxt* _thCxt);


#if defined(mBackRef_REF_ObjectJc)
  /**Definition of the methods setBackRef_ObjectJc and clearBackRef_ObjectJc inside.
    * It is possible that this file is not available in the user system.
    * Therefore do not include if not necessary.
  */
  //#include "ObjectrefJc.h"
#endif
//#include "ThreadJc.h"



typedef enum EBlockType_t
{
  kSizeSmallBlock_BlockHeap = 0x7e
, kReferencesStd_BlockHeap = 10
}EBlockType;


//BlockHeap_emC_s* current_BlockHeap_emC = null;



BlockHeap_emC_s* current_BlockHeap_emC(ThCxt* _thCxt)
{ return _thCxt==null || _thCxt->blockHeap==null 
       ? theBlockHeapList   //first or only one entry, null is Assertion-error
       : _thCxt->blockHeap;
}

BlockHeap_emC_s* theBlockHeapList = null;


BlockHeap_emC_s* setCurrent_BlockHeap_emC(BlockHeap_emC_s* heap, ThCxt* _thCxt)
{ BlockHeap_emC_s* last = _thCxt->blockHeap;
  _thCxt->blockHeap = heap;
  return last;
}


METHOD_C void addHeap_BlockHeap_emC(BlockHeap_emC_s* thiz)
{
  thiz->nextHeap = theBlockHeapList;
  theBlockHeapList = thiz;
}


BlockHeap_emC_s* first_BlockHeap_emC()
{ return theBlockHeapList;
}

//static const int mBeginBlock_BlockHeap = ~(kSizeNormalBlock_BlockHeap-1);


/**Reference to the array of all control structures of BlockHeaps. */
//BlockHeap_emCARRAY* all_BlockHeap;




#define kOffsetData_BlockHeapBlockJc 0



#if defined(mBackRef_REF_ObjectJc)
  /** To support debugging, a type of REFP_ObjectJc-array is defined and used inside.
    * The number of elements is a arbitrary number, convenient for debugging.
    * The really number of elements is determined by using.
    */
  typedef REF_ObjectJc* REF_ObjectJc_array[20];
#endif


/*
xxxBlockHeap_emCARRAY* new_BlockHeap_emCARRAY(int nrofElements)
{ int nrofBytes = SIZEOF_BlockHeap_emCARRAY(nrofElements);
  xxxBlockHeap_emCARRAY* ptr = (xxxBlockHeap_emCARRAY*)(alloc_MemC(nrofBytes).address);
  if(ptr != null)
  { ctor_ObjectArrayJc(&ptr->head, nrofElements, sizeof(BlockHeap_emC_s), null, 0);
  }
  return ptr;
}
*/
/*
void* alloc_sBlockHeap_emC(int size)
{ void* ptr;
  STACKTRC_ENTRY("alloc_sBlockHeap_emC");
  if(current_BlockHeap_emC != null)
  { ptr = alloc_BlockHeap_emC(current_BlockHeap_emC, size);
  }
  else
  { ptr = mallocFromOpSysJc(size);
  }
  STACKTRC_LEAVE; return(ptr);
}
*/
//BlockHeap_emC_s* theDefaultBlockHeap;

/*
bool initall_BlockHeap_emC(int nrofHeaps)
{ int nrofByteAllHeaps = sizeof_BlockHeap_emCARRAYd(nrofHeaps);
  STACKTRC_ENTRY("initall_BlockHeap");

  all_BlockHeap = (BlockHeap_emCARRAYd*)mallocFromOpSysJc(nrofByteAllHeaps);
  if(all_BlockHeap == null) THROW(RuntimeException, "no memory", false);
  all_BlockHeap->array.length = nrofHeaps;
  all_BlockHeap->array.sizeElement = sizeof(BlockHeap_emC_s);
  //all_BlockHeap->array.mode = kDirect_ObjectArrayJc;
  memset(all_BlockHeap->data, 0, nrofHeaps * sizeof(BlockHeap_emC_s));
  STACKTRC_LEAVE; return true;
}



void init_i_s_BlockHeap_emC(int idxHeap, MemUnit* heap, int sizeHeap)
{
  BlockHeap_emC_s* heapCtrl = get_BlockHeap_emCARRAYd(all_BlockHeap, idxHeap);
  MemC memHeap = { sizeHeap, (struct MemAreaC_t*)heap};
  MemC memCtrl = { sizeof(BlockHeap_emC_s), (struct MemAreaC_t*)heapCtrl};
  ctor_BlockHeap_emC(memCtrl, memHeap, 0x400, 0x40);
}
*/

METHOD_C BlockHeap_emC_s* ctorO_BlockHeap_emC(ObjectJc* othis, MemC wholeHeap, int bytesNormalBlock, int bytesSmallBlock)
{
  BlockHeap_emC_s* thiz = (BlockHeap_emC_s*)othis;
  
  int zBlock;
  struct MemAreaC_t* heap = PTR_MemC(wholeHeap, struct MemAreaC_t);
  int sizeHeap = size_MemC(wholeHeap);
  STACKTRC_ENTRY("ctor_BlockHeap_emC");
  checkInit_ObjectJc(othis, sizeof(BlockHeap_emC_s), &reflection_BlockHeap_emC, 0, _thCxt); 
  
  init0_MemC(wholeHeap);

  //:TODO: Test signifity of bytesNormalBlock and bytesSmallBlock!

  //thiz->bytesNormalBlock = bytesNormalBlock;
  //thiz->mAdressNormalBlock_BlockHeap = ~(bytesNormalBlock -1);

  #ifdef HEAP_BEGINSATPOWER2_RUNTIMEHEAP
    int testBytes = bytesNormalBlock;
    while( (testBytes & 1) ==0) { testBytes >>=1; }
    ASSERTs_emC(testBytes ==1, "BlockHeap: bytesNormalBlock should be power of 2", bytesNormalBlock, 0);
  #endif
  thiz->bytesNormalBlock = bytesNormalBlock;
  thiz->bytesSmallBlock = bytesSmallBlock;
  thiz->mAdressSmallBlock_BlockHeap = ~(bytesSmallBlock -1);

#ifdef HEAP_BEGINSATPOWER2_RUNTIMEHEAP
  //than all blocks start at a address which is alligned at the size of a block.
  //the deducing from any address inside the block to the begin of the block
  //is only a simple mask of address-bits then.
  if( ((intPTR)heap & (bytesNormalBlock-1)) != 0)
  { //if the heap donot starts at a address with mask boundary, increment the address to the next boundary
    heap = (struct MemAreaC_t*)( ((intPTR)heap & ~(bytesNormalBlock-1)) + bytesNormalBlock );
    //and reduce the number of blocks, because the end address should be less than the given one.
    sizeHeap -= bytesNormalBlock;
  }
#endif
  thiz->zBlock = zBlock = sizeHeap / bytesNormalBlock;
  thiz->heapBegin = (BlockHeapBlockJc_debugArray*)heap;
  thiz->heapEnd   = addOffset_MemAreaC(thiz->heapBegin, zBlock * bytesNormalBlock);


  //thiz->theGarbageCollectorThread = Thread::new_(thiz, "GarbageCollector");
  //thiz->theGarbageCollectorThread->setPriority(Thread::NORM_PRIORITY -1);

  //if(heap==0) throw new RuntimeException("BlockHeap::init(): no mem");

  //Object__BaseRefef::BlockHeapEnd = (MemUnit*)(heap) + zBlock * kSizeNormalBlockHeapBlockJc;

  thiz->firstFreeBlock = (BlockHeapBlockJc*)(heap);

  { //mark all free Blocks with a single linked list
    BlockHeapBlockJc* block = thiz->firstFreeBlock;
    int ii;
    for(ii=1; ii< zBlock; ii++)  //take the next block
    { BlockHeapBlockJc* nextBlock = (BlockHeapBlockJc*)(&((MemUnit*)heap)[ii * bytesNormalBlock]);
      block->heap = thiz;
      //bbb block->ctrl.typeAndSize = (int16)kFree_Type_BlockHeapBlock;
      block->typeOrMaxRef = kFree_Type_BlockHeapBlock;
      //bbb *(BlockHeapBlockJc**)(&block->data[0]) = nextBlock;
      block->nextBlock = nextBlock;
      block = nextBlock;
    }
    //handle the last block
    block->heap = thiz;
    //bbb block->ctrl.typeAndSize = (int16)kFree_Type_BlockHeapBlock;
    block->typeOrMaxRef = kFree_Type_BlockHeapBlock;
    //bbb block->data[0] = 0;     //the last block has no next.
    block->nextBlock = null;  //the last block has no next.
    //thiz->lastFreeBlock = block;  //append a free becoming block here.
  }

  //iLastSmallBlock = 0;
  //iNextNormalBlock = 1;


  initMapEntryNodes_BlockHeap_emC(thiz, _thCxt);

  /*
  if(current_BlockHeap_emC == null)
  { //the first initialized blockheap is the current.
    current_BlockHeap_emC = thiz;
  }
  */

  //insert this heap in the chain of heaps.
  thiz->nextHeap = theBlockHeapList;  //null if it is the first one.
  theBlockHeapList = thiz;
  STACKTRC_LEAVE;
  return thiz;

}



bool checkSignificance_BlockHeapBlockJc(BlockHeapBlockJc* thiz, struct BlockHeap_emC_T * ownHeap)
{
  //ObjectJc* heapObj;
  //if(ownHeap == null){ ownHeap = thiz->heap; }
  //heapObj = &ownHeap->base.object;

  return ASSERT_emC(ownHeap == thiz->heap && ownHeap != null, "not a heap Block", 0, 0);

  //ASSERTJc_RET(instanceof_ObjectJc(heapObj, &reflection_BlockHeap_emC), false);
  //return true;
}


void setRunMode_BlockHeap_emC(BlockHeap_emC_s* thiz, struct LogMessageFW_t* log, int kIdentMsgBase)
{ thiz->log = log;
  thiz->kIdentMsgBase = kIdentMsgBase;

  thiz->bitInitMode = 0x1234abcd;
}



void setRunModeAll_BlockHeap_emC() {
  BlockHeap_emC_s* bh = theBlockHeapList;
  while(bh !=null) {
    setRunMode_BlockHeap_emC(bh, null, 0);
    bh = bh->nextHeap;
  }
}


MemC alloc_s_sBlockHeap_emC(int sizeObj, const char* sCallInfo, ThCxt* _thCxt)
{ //STACKTRC_NAME("alloc_s_BlockHeap")
  return alloc_iis_BlockHeap_emC(current_BlockHeap_emC(_thCxt), sizeObj, kReferencesStd_BlockHeap, sCallInfo, _thCxt);
}


ObjectJc* allocObject_s_sBlockHeap_emC(int sizeObj, int identObj, const char* sCallInfo, ThCxt* _thCxt)
{ //STACKTRC_NAME("alloc_s_BlockHeap")
  return allocObject_IIs_BlockHeap_emC(current_BlockHeap_emC(_thCxt), sizeObj, identObj, kReferencesStd_BlockHeap, sCallInfo, _thCxt);
}


ObjectJc* alloc_ObjectJc(const int size, const int32 typeInstanceIdent, ThCxt* _thCxt)
{ ObjectJc* othis;
  STACKTRC_TENTRY("alloc_ObjectJc");
  #ifdef DEF_ThreadContextStracktrc_emC  
    const char* sCallingMethodName = getCallingMethodName_StacktraceThreadContext_emC( &_thCxt->stacktrc, 1);  
  #else
    const char* sCallingMethodName = "ThCxtNoStacktrc";
  #endif
  othis = allocObject_s_sBlockHeap_emC(size, typeInstanceIdent, sCallingMethodName, _thCxt);
   
  STACKTRC_LEAVE; return othis;
}





int setRunMode_ObjectJc(ThCxt* _thCxt)
{
  BlockHeap_emC_s* blockHeap = theBlockHeapList;
  while(blockHeap !=null){
    setRunMode_BlockHeap_emC(blockHeap, null, 0);
    blockHeap = blockHeap->nextHeap;
  }
  return 0;
}

MemC alloc_s_BlockHeap_emC(BlockHeap_emC_s* thiz, int sizeObj, const char* sCallInfo, ThCxt* _thCxt)
{ //STACKTRC_NAME("alloc_BlockHeap")
  return alloc_iis_BlockHeap_emC(thiz, sizeObj, kReferencesStd_BlockHeap, sCallInfo, _thCxt);
}




MemC alloc_iis_BlockHeap_emC(BlockHeap_emC_s* thiz, int sizeObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt)
{ ObjectJc* obj = allocObject_IIs_BlockHeap_emC(thiz, sizeObj, -1, nrofReferences, sCallInfo, _thCxt); 
  MemC ret = build_MemC(obj, getSizeInfo_ObjectJc(obj));
  return ret;
}



int nrofFreeBlocks_BlockHeap_emC(BlockHeap_emC_s* thiz) {
  int nr = 0;
  BlockHeapBlockJc* freeBlock;
  int catastropicCt1 = 20;
  do {
    freeBlock = thiz->firstFreeBlock;
    nr = 0;
    while(freeBlock !=null && nr < thiz->zBlock) { //Note: limit to max nrof blocks. 
      nr +=1;
      BlockHeapBlockJc* nextFreeBlock = freeBlock->nextBlock;
      if(nextFreeBlock == freeBlock) { //detect a used block
        nr = -1;  //repeat
        break;
      }
      freeBlock = nextFreeBlock;
    }
  } while(nr <0 && --catastropicCt1 >=0);
  ASSERT_emC(catastropicCt1 >=0, "", 0,0);
  return nr;
}




/**Allocates one block. 
 * @param sizeObj detects whether a small block is sufficient. Determines the nrofReferences.
 *        special specification: -1: use a normal block with given nrofReferences
 *                               -2: use a small block with given nrofReferences
 * @param nrofReferences: The minimum of number of references to all objects, which should be stored in the block.
 *        If the sizeObj is less, more references can be stored. It is because, the size of the block is constant.
 * @return the Block.
 */
static BlockHeapBlockJc* allocBlock_BlockHeap_emC(BlockHeap_emC_s* thiz, int sizeObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt)
{ BlockHeapBlockJc* retBlock;
  //ObjectJc* retObj;
  bool bRetry = false;
  STACKTRC_TENTRY("alloc_ii_BlockHeap");
  if(sizeObj == -1)
  { //BBB sizeObj = thiz->bytesNormalBlock - sizeof(BlockHeapBlockCtrlJc) - nrofReferences * sizeof(ObjectJc*);
    sizeObj = thiz->bytesNormalBlock - nrofBytesHead_BlockHeapBlockJc - nrofReferences * sizeof(ObjectJcREF*);
  }
  else if(sizeObj == -2)
  { sizeObj = kSizeSmallBlock_BlockHeap - nrofReferences * sizeof(ObjectJcREF*);
  }
  do {
    int maxRef = 0;
    int sizeBlock = 0;
    int minSizeBlock = nrofBytesHead_BlockHeapBlockJc + sizeObj + nrofReferences * sizeof(ObjectJcREF*);  //add the size of the references array to the requested size.
    retBlock = null;
    if(minSizeBlock > (thiz->bytesNormalBlock - kOffsetData_BlockHeapBlockJc)) {
     THROW1_s0(RuntimeException, "BlockHeap::alloc(): size to large", minSizeBlock);
    } else if(minSizeBlock >= 0) //Object::kSizeNormalBlockHeapBlockJc / 8)
    { //after the atomare instruction the first Free Block is no longer available
      //for other threads. So no lock are necessary.
      //bbb maxRef = (thiz->bytesNormalBlock - sizeof(BlockHeapBlockCtrlJc) - sizeObj) / sizeof(ObjectJc*);
      bool bSuccess;
      int catastrophicRepeatCount = 1000;
      sizeBlock = thiz->bytesNormalBlock;
      maxRef = (sizeBlock - nrofBytesHead_BlockHeapBlockJc - sizeObj) / sizeof(ObjectJcREF*);
      //disableSwitch_Thread();
      do
      { retBlock = thiz->firstFreeBlock;
        if(retBlock !=null)
        { void* nextFreeBlock = retBlock->nextBlock;
          //try to set the next block as newly first one:
          /*
          int lastValue;
          int ref = (int)(thiz->firstFreeBlock);
          XcompareAndSwap_AtomicInteger(lastValue, ref, retBlock, nextFreeBlock);
          */
          //bSuccess = compareAndSet_AtomicRef(CAST_AtomicReference(thiz->firstFreeBlock), retBlock, nextFreeBlock);
          bSuccess = compareAndSet_AtomicRef((void*volatile*)&thiz->firstFreeBlock, retBlock, nextFreeBlock);
        }
        else { bSuccess = true; } //no block, no change.

      } while(!bSuccess && --catastrophicRepeatCount >=0);  //repeat if compareAndSet fails.
      if(catastrophicRepeatCount < 0){
        THROW1_s0(RuntimeException,"compareAndSet-fail",0);
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
      retBlock->heap = thiz;
      retBlock->heapidxAndMaxref = (int16)(maxRef + (thiz->idxHeapCtrl << kBitHeapIdx_ObjectJc_BlockHeap));
      //retBlock->nextBlock  = null;  //NOTE: it had contain the pointer to the next retBlock and is now used as backRef
      retBlock->nextBlock  = retBlock;  //refer itself to note, it is not in queue of free blocks.
      retBlock->sCreaterInfo = sCallInfo;
      retBlock->timeCreation = os_getDateTime().time_sec;
      retBlock->backRefs = (ObjectJcREFArray*)addOffset_MemAreaC(retBlock,  sizeof(BlockHeapBlockJc));
      //bbb ret.address = (struct MemAreaC_t*)(block->data);  //returns the Adress of data within BlockHeapBlockJc
    }
    else
    { /**No free block found. */
      retBlock = null;
      #ifdef DEF_BlockHeapGc_emC
      bRetry = runUserCalledGc_BlockHeap_emC(_thCxt);
      #endif
      if(!bRetry) {
        retBlock = null;
        THROW1_s0(RuntimeException, "BlockHeap::alloc(): no memblock", 0);
      }
    }
  }while(retBlock == null && bRetry);  //repeat it if a block isn't found but the garbage collector was successfull.
  STACKTRC_LEAVE; return retBlock;
}



MemC allocMemC_BlockHeap_emC(BlockHeap_emC_s* thiz, int sizeObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt)
{ MemC ret;
  if(thiz == null || thiz->bitInitMode != 0x1234abcd)
  { //init-mode
    SET_MemC(ret, alloc_MemC(sizeObj), sizeObj);
  }
  else
  { //alloc a Block in the BlockHeap-pool:
    void* retBlock;
    int offsetObjToBlock = thiz->bytesNormalBlock - sizeObj;
    BlockHeapBlockJc* block = allocBlock_BlockHeap_emC(thiz, sizeObj, nrofReferences, sCallInfo, _thCxt);
    if(block !=null) {
      //arrange the data at end of the block!
      retBlock = addOffset_MemAreaC(block, offsetObjToBlock);;
      SET_MemC(ret, retBlock, sizeObj);
    } else {
      SET_MemC(ret, null, 0);
    }
  }
  return ret;
}



ObjectJc* allocObject_IIs_BlockHeap_emC(BlockHeap_emC_s* thiz, int sizeObj, int identObj, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt)
{ ObjectJc* retObj;
  if(sizeObj == -1)
  { sizeObj = thiz->bytesNormalBlock - nrofBytesHead_BlockHeapBlockJc - nrofReferences * sizeof(ObjectJcREF*);
  }
  else if(sizeObj == -2)
  { sizeObj = kSizeSmallBlock_BlockHeap - nrofReferences * sizeof(ObjectJcREF*);
  }
  if(thiz == null || thiz->bitInitMode != 0x1234abcd)
  { retObj = (ObjectJc*)alloc_MemC(sizeObj);
    if(retObj !=null){
      ClassJc const* refl = null;  //do not mark with reflection, because it is not given here.
      iniz_ObjectJc(retObj, retObj, sizeObj, refl, identObj);
    }
  }
  else
  { //alloc a Block in the BlockHeap-pool:
    int offsetObjToBlock = thiz->bytesNormalBlock - sizeObj;
    BlockHeapBlockJc* block = allocBlock_BlockHeap_emC(thiz, sizeObj, nrofReferences, sCallInfo, _thCxt);
    if(block !=null) {
      //arrange the data at end of the block!
      retObj = C_CAST(ObjectJc*, addOffset_MemAreaC(block, offsetObjToBlock));
      ClassJc const* refl = null;  //do not mark with reflection, because it is not given here.
      iniz_ObjectJc(retObj, retObj, sizeObj, refl, identObj);
      block->obj = retObj;  //notice the pointer to the allocating Object, to run finalize if it is freed.
      //necessary ? retObj->blockHeapBlock = block;
      if(thiz->log != null)
      {
        /**It isn't good, because that complex algorithm may alloc too. TODO: sendmsg without any alloc here or special solution */
        //sendMsg_tzzv_LogMessageFW(thiz->log, thiz->kIdentMsgBase + identMsgAlloc_BlockHeap_emC, os_getDateTime()
        //  , "alloc_BlockHeap; block=%p; size=%d; id=%d; caller=%s; firstFree %p"
        //  , "PIIzP", block, sizeObj, identObj, sCallInfo, thiz->firstFreeBlock
        //  ); 
      }
    } else {
      retObj = null;
    }
  }
  return retObj;
}




  
void free_BlockHeap_emC(BlockHeap_emC_s* thiz, BlockHeapBlockJc* block, ThCxt* _thCxt)
{ bool bSuccess;
  int catastrophicRepeatCount = 1000;
  BlockHeapBlockJc* firstFreeBlockCurrent;
  STACKTRC_TENTRY("free_BlockHeap_emC");
  block->typeOrMaxRef = kFree_Type_BlockHeapBlock;
  block->heapidxAndMaxref = 0;
  do {
    firstFreeBlockCurrent = thiz->firstFreeBlock;  //may be null, if heap is empty.
    //bbb block->ctrl.typeAndSize = kFree_Type_BlockHeapBlock;
    //bbb block->data[0] = 0;
    block->nextBlock = firstFreeBlockCurrent;  //the current first will be the second then.
    bSuccess = compareAndSet_AtomicRef(CAST_AtomicReference(thiz->firstFreeBlock), firstFreeBlockCurrent, block);
  } while(!bSuccess && --catastrophicRepeatCount >=0);
  if(catastrophicRepeatCount < 0){
    THROW1_s0(RuntimeException,"compareAndSet-fail",0);
  }
  STACKTRC_LEAVE;
}




bool free_sBlockHeap_emC(void const* obj, ThCxt* _thCxt)
{
  BlockHeap_emC_s* heap = null;
  BlockHeapBlockJc* block;
  
  block = searchBlockHeapBlock_BlockHeap_emC(obj, &heap);
  if(heap != null)
  { free_BlockHeap_emC(heap, block, _thCxt);
    return true;
  }
  else
  { //not a block from BlockHeap, use free
    return false;
  }
}





MemC getRestBlock_ObjectJc(ObjectJc* thiz, int size, ThCxt* _thCxt)
{ MemC retMem;
  STACKTRC_TENTRY("restSizeBlock_ObjectJc");
  { BlockHeap_emC_s* retHeap;
    BlockHeapBlockJc* block = searchBlockHeapBlock_BlockHeap_emC(thiz, &retHeap);
    if(block == null)
    { SET_MemC(retMem, 0, null);
    }
    else
    { int nrofBytes;
      int nrofBackRefs;
      void* addr;
      if(size < 0)
      { nrofBackRefs = -size;
        nrofBytes = ((block->typeOrMaxRef & mMaxRef_BlockHeap_emC) - nrofBackRefs) * sizeof(ObjectJcREF**);
      }
      else
      { nrofBytes = size;
        nrofBackRefs = (block->typeOrMaxRef & mMaxRef_BlockHeap_emC) - (nrofBytes * sizeof(ObjectJcREF**));
      }
      if(nrofBytes <0 || nrofBackRefs < 0) THROW1_s0(IllegalArgumentException, "unaccomplishable request of rest block size", size);
      block->typeOrMaxRef = (int16)((block->typeOrMaxRef & ~ mMaxRef_BlockHeap_emC) | nrofBackRefs);
      addr = addOffset_MemAreaC(thiz, -nrofBytes);
      SET_MemC(retMem, addr, nrofBytes);
    }
  }
  STACKTRC_LEAVE; return retMem;
}



void setLogMessageOutput_BlockHeap_emC(struct LogMessageFW_t* log, int msgBase, ThCxt* _thCxt)
{ 
  
  BlockHeap_emC_s* currentBlockHeap = _thCxt->blockHeap;
  currentBlockHeap->log = log;
}





/*****************************************************************************
*
*
*/



#include "emC/Jc/ListMapEntryJc.h"  //includes pkgSystem/Object.h, pkgSystem/String.h





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


struct NodePoolJc_t* current_NodePool_ListMapEntryJc(struct ThreadContext_emC_t* _thCxt)
{ return (struct NodePoolJc_t*) current_BlockHeap_emC(_thCxt);
}



static ListMapEntryJc* initMapEntryNodes_BlockHeap_emC(BlockHeap_emC_s* thiz, ThCxt* _thCxt)
{ ListMapEntryJc* retBlock;
  int ixNode;
  int nrofNode = (thiz->bytesNormalBlock - sizeof(BlockHeapBlockJc)) / sizeof(ListMapEntryJc);
  ListMapEntryJc* next;
      
  BlockHeapBlockJc* block = allocBlock_BlockHeap_emC(thiz, -1, 0, "alloc_ListMapEntryJc", _thCxt);
  block->typeOrMaxRef = kMapEntryBlock_Type_BlockHeapBlockJc + 1;
  //data content of the allocated block is newBlock,
  retBlock = (ListMapEntryJc*)(block+1);  //casting: address after head
  if(thiz->firstMapEntry == null){
    //it is initial
    ASSERTs_emC(thiz->lastMapEntry == null, "BlockHeap lastMapEntry not null", (int)(intptr_t)thiz->lastMapEntry, 0);
    thiz->firstMapEntry = thiz->lastMapEntry = retBlock;
  }
  //the retBlock is the first block of 
  //retBlock = &newBlock->entries[0]; 
  for(ixNode = 1; ixNode < nrofNode; ++ixNode){ 
    next = &retBlock[ixNode];
    //free all new blocks upon the next.
    free_ListMapEntryJc((struct NodePoolJc_t*)thiz, next, _thCxt);
  }
  return retBlock;
}





ListMapEntryJc* alloc_ListMapEntryJc(struct NodePoolJc_t* ithis, ThCxt* _thCxt)
{ BlockHeap_emC_s* thiz = (BlockHeap_emC_s*)ithis;  //conversion allowed because the reference is getted with current_NodePool_ListMapEntryJc
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
      //bbb maxRef = (thiz->bytesNormalBlock - sizeof(BlockHeapBlockCtrlJc) - sizeObj) / sizeof(ObjectJc*);
      bool bSuccess = false;
      int catastrophicRepeatCount = 1000; 
      do
      { retBlock = thiz->firstMapEntry;
        lastBlock = thiz->lastMapEntry;
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
            compareAndSet_AtomicRef(CAST_AtomicReference(thiz->lastMapEntry), lastBlock, secondBlock);  
          }
        } else {
          //fist and lastMapEntry referes to different nodes, There should be a node available!
          //try to set the next block as newly first one:
          bSuccess = compareAndSet_AtomicRef(CAST_AtomicReference(thiz->firstMapEntry), retBlock, secondBlock);
        }
      } while(!bSuccess && --catastrophicRepeatCount >=0);  //repeat if compareAndSet fails.
      if(catastrophicRepeatCount < 0){
        THROW1_s0(RuntimeException,"compareAndSet-fail",0);
      }  
    }
    if(retBlock == null){
      //nolistMapEntry-Block available, then allocated a normal block and use it for ListMapEntries:
      //MapEntryBlockJc* newBlock;
      retBlock = initMapEntryNodes_BlockHeap_emC(thiz, _thCxt);
    
    }
  //}while(retBlock == null && bRetry);  //repeat it if a block isn't found but the garbage collector was successfull.
  STACKTRC_LEAVE; return retBlock;
}




BlockHeapBlockJc* getBlockFromAddr_BlockHeap_emC(BlockHeap_emC_s* thiz, void* addr) {
  intPTR offs = OFFSET_MemUnit(thiz->heapBegin, addr);
  int posInBlock = offs % thiz->bytesNormalBlock;
  MemUnit* blockAddr = ADD_OFFSET_MemUnit(addr, -posInBlock);
  BlockHeapBlockJc* block = (BlockHeapBlockJc*)blockAddr;
  ASSERT_emC(block->heap == thiz,  "not a heap Block", posInBlock, offs);
  return block;
}




void free_ListMapEntryJc(struct NodePoolJc_t*ithis, ListMapEntryJc* node, struct ThreadContext_emC_t* _thCxt)
{ BlockHeap_emC_s* thiz = (BlockHeap_emC_s*)ithis;  //conversion allowed because the reference is getted with current_NodePool_ListMapEntryJc
  bool bSuccess;
  int catastrophicRepeatCount = 1000;
  BlockHeapBlockJc* block;
  int nrofFreeNodesInBlock;
  //The next value is a constant, calculated by compiler:
  int halfNrofNodesInBlock = ((thiz->bytesNormalBlock-sizeof(BlockHeapBlockJc))/sizeof(ListMapEntryJc)/2);
  STACKTRC_TENTRY("free_BlockHeap_emC");
  
  block = getBlockFromAddr_BlockHeap_emC(thiz, node);  //TODO: deduce_BlockHeapBlockJc(node);
  node->allocater = null;
  nrofFreeNodesInBlock = block->typeOrMaxRef & mMaxRef_BlockHeap_emC;
  
  if(nrofFreeNodesInBlock > halfNrofNodesInBlock)
  { //append the node on end if the block has more as half nodes non-allocated. 
    //Than this block isn't used to get a next node, but another.
    //So statistically, this block get all nodes free, 
    //and than it can be freed as whole block.
    node->next = null;  //add as last node, it mustn't reference any other.
    do{
      ListMapEntryJc* tail = thiz->lastMapEntry;
      ListMapEntryJc* next = tail->next;
      bSuccess = false;  //TODO test it.
      if(tail == thiz->lastMapEntry){
        if(next == null){
          if(compareAndSet_AtomicRef(CAST_AtomicReference(tail->next), next, node)){
            compareAndSet_AtomicRef(CAST_AtomicReference(thiz->lastMapEntry), tail, node);
            bSuccess = true;
         }
        } else {
          //The thread has interrupted another access to the the lastMapEntry reference,
          //before the lastMapEntry was set to the really end.
          //Therefore: //set the lastMapEntry to the next found strange entry.
          //after them the test will be repeated so long as next == null.
          compareAndSet_AtomicRef(CAST_AtomicReference(thiz->lastMapEntry), tail, next);
      } }
    } while(!bSuccess && --catastrophicRepeatCount >=0);
  } else {
    //append the node on top if the block has more as half nodes allocated..
    do {
      ListMapEntryJc* firstFreeNodeCurrent;
      firstFreeNodeCurrent = thiz->firstMapEntry;  //may be null, if heap is empty.
      node->next = firstFreeNodeCurrent;            //the current first will be the second then.
      bSuccess = compareAndSet_AtomicRef(CAST_AtomicReference(thiz->firstMapEntry), firstFreeNodeCurrent, node);
      if(bSuccess && firstFreeNodeCurrent == thiz->lastMapEntry){
        //the list was empty, now
        stop();
      }
      //The lastFreeNodeCurrent isn't affected, at least it references the only one node before enqueue.
    } while(!bSuccess && --catastrophicRepeatCount >=0);
  }
  block->typeOrMaxRef +=1;  //count up free blocks.
  ASSERT_emC((block->typeOrMaxRef & mSmallBlock_Type_Object)==kMapEntryBlock_Type_BlockHeapBlockJc
            , "", 0, 0 ); //it will be faulty if the count of blocks fails.
  if(catastrophicRepeatCount < 0){
    THROW1_s0(RuntimeException,"compareAndSet-fail",0);
  }
  STACKTRC_LEAVE;
}






/**Tests if the objP is inside any BlockHeap, ascertains the block base address and
* the block number if it is a small block.
*
* This is a core algorithm of BlockHeap. It imagins as complex, but it is simple:
* * At first it must be detect, if the object is located in any Blockheap generally and in which one.
*   To detect this, all known Blockheap adress ranges should be compared with the address of the given Object.
*   But in users systems, there will be only one or few BlockHeaps, 1..5 is realistic.
*   To find out the BlockHeap_emC_s-control structures, there are chained in a queue
*   started with the global reference theBlockHeapList. The BlockHeap_emC_s control structure contains
*   the start and end address of the heap area in the users memory space.
*   Now it is a simple address compare operation to detect wether the Object is in this area.
* * If the Object is located in a Blockheap, the size of blocks is known.
*   The Object doesnot start at the begin adress of the block, because there are some control bytes
*   and the array of back references is located from start position.
*   It is possible, that the Object is an embedded structure inside another Object and this other Object
*   occupies the block primary. The essential is, this Object is located in a block, it don't care where exactly.
* * To detect which block, a masking of memory address is done. It is a fast algorithm.
*   It requires, that the block size is a power of 2. This requirement is considered in construction of BlockHeap.
*   It is possible, that the border adresses of the heap memory area are also power of 2.
*   In this case the address of the Object can be simple masked to get the block start address.
* * This getted block start address is the start address of a normal block.
*   But it is possible that the Object is member of a small block. There are some small blocks in one normal block.
*   It can be detect wether the large block is a container of small blocks to test a bit at BlockHeapBlockJc::typeOrMaxRef.
*   If it is not a small-block-container, the block is detect and the algorithm is returned.
* * If it is a small-block-container, the correct small block will be detected by knowing its size.
*   It needs a few more calculation time.
*
* @param objP any address in memomry space
* @param retHeap output pointer to set the dedicated BlockHeap control structure.
* @param retNumber output pointer to set the block number of a small block.
* @return base address of the block. It is always the base address of a normal block.
*/

METHOD_C BlockHeapBlockJc* searchBlockHeapBlock_BlockHeap_emC(void const* objP, BlockHeap_emC_s** retHeap){ 
  BlockHeapBlockJc* block = null;
  struct MemAreaC_t const* obj = (struct MemAreaC_t const*)(objP);
  BlockHeap_emC_s* heap;

  heap = theBlockHeapList;
  while(heap != null && block == null)
  { //check whether the block is member of the heap, it is in its address range of blocks:
    if( ((void const*)heap->heapBegin) <= objP && ((void*)obj) < heap->heapEnd)
    { //it is in this heap:
      #ifdef HEAP_BEGINSATPOWER2_RUNTIMEHEAP
      block = (BlockHeapBlockJc*)(((intPTR)(obj)) & ~(heap->bytesNormalBlock-1));
      #else
      #error do not compile
      block = (BlockHeapBlockJc*)
        ( ( ( ((MemUnit*)obj) - ((MemUnit*)heap->heapBegin)) & ~(thiz->bytesNormalBlock-1)
        ) + ((MemUnit*)heap->heapBegin)
        ) ;
      #endif
      //bbb if( (block->ctrl.typeAndSize & mSmallBlock_Type_Object) == mSmallBlock_Type_Object)
      if( (block->typeOrMaxRef & mSmallBlock_Type_Object) == mSmallBlock_Type_Object)
      { /*The block begins with the info, it is a block containing small blocks:
        use the small block mask.
        */
        #ifdef HEAP_BEGINSATPOWER2_RUNTIMEHEAP
        block = (BlockHeapBlockJc*)(((intPTR)(obj)) & heap->mAdressSmallBlock_BlockHeap);
        #else
        #error do not compile
        block = (BlockHeapBlockJc*)
          ( ( (((MemUnit*)obj) - ((MemUnit*)heap->heapBegin)) & heap->mAdressSmallBlock_BlockHeap
          ) + heap->heapBegin
          ) ;
        #endif
      }
      //bbb else if( (block->ctrl.typeAndSize & mSmallBlock_Type_Object) == kMapEntryBlock_Type_Object)
      else if( (block->typeOrMaxRef & mSmallBlock_Type_Object) == kMapEntryBlock_Type_BlockHeapBlockJc)
      { /*The block begins with the info, it is a block containing small blocks:
        use the small block mask.
        */
        struct MemAreaC_t* nextBlock;

        //bbb block = (BlockHeapBlockJc*) ( &block->data[1]);
        block = null; //TODO (BlockHeapBlockJc*) ( &block->backRefs[1]);
        nextBlock = addOffset_MemAreaC((struct MemAreaC_t*)(block), sizeof(ListMapEntryJc));
        while(nextBlock < obj)
        { block = (BlockHeapBlockJc*)(nextBlock); //may be the right one.
        nextBlock = addOffset_MemAreaC(block, sizeof(ListMapEntryJc));

        //nextBlock += bytesMapEntryBlock_BlockHeap;
        }
      }
    }
    else
    { // not in this heap
      heap = heap->nextHeap;
    }
  }
  *retHeap = heap;
  return block;
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

#endif   //USE_BlockHeap_emC
