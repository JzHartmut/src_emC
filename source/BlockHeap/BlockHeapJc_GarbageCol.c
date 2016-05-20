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
 * @content: implementation of the garbage collector.
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
#include <Fwc/fw_LogMessage.h>
#include <Fwc/fw_Exception.h>
#include <Jc/StringJc.h>
#include <Jc/SystemJc.h>
#include <BlockHeap_PlatformSpec.h>

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>








void activateGC_ObjectJc(void const* objP, void const* exclAddr, ThCxt* _thCxt)
//void activateGarbageCollectorAccess_BlockHeapJc(void const* objP, void const* exclAddr)
{
  BlockHeapJc* heap = null;
  BlockHeapBlockJc* block;

  block = searchBlockHeapBlock_BlockHeapJc(objP, &heap);
  if(block != null){
    if(exclAddr == null) {
      block->typeOrMaxRef |= mConsideredInGarbage_Type_Object;
    } else  {
      //TODO don't call deduce, but test whether the exclAddr is in block range. calc-time!
      BlockHeapBlockJc* blockExcl = searchBlockHeapBlock_BlockHeapJc(exclAddr, &heap);
      if(blockExcl != block) { 
        activateGC_BlockHeapBlockJc(block);
      } else {
        //do nothing, because the block is returned.
      }
    }
  }
  else
  { //do nothing, it may be alloced in startup time.
  }

}



static void flushFullReportBuffer(GarbageCollectorJc* ythis, int sizeUsed, ThCxt* _thCxt)
{ if(ythis->idxReportBuffer >= (int)(sizeof(ythis->reportBuffer) - sizeUsed))
  { sendMsg_z_LogMessageFW(ythis->log, ythis->kIdentMsgBase + identMsgGcWork_BlockHeapJc, ythis->reportBuffer, _thCxt);
    ythis->idxReportBuffer = sprintf(ythis->reportBuffer, "...GC; ");
  }
}





static bool testBlock_GarbageCollectorJc(GarbageCollectorJc* ythis, BlockHeapBlockJc* block)
{ int maxBackref = block->typeOrMaxRef & mMaxRef_BlockHeapJc;
  int idxBackref = 0;
  bool bInUse = false;
  STACKTRC_ENTRY("testBlock_GarbageCollectorJc");

  do
  { //test any back reference. If it is a reference from another block, mark it.
    //if it is a reference outside any blockheaps, the block is used.
    //ObjectJcREF* ref = block->head.backRefs[idxBackref];  //the backRef contains a reference to the reference to this block.
    ObjectJcREF* ref = block->backRefs->data[idxBackref];  //the backRef contains a reference to the reference to this block.
    if(ref != null)
    { //look where the reference to this block is located:
      BlockHeapJc* retHeap;
      BlockHeapBlockJc* blockWithReference = searchBlockHeapBlock_BlockHeapJc(ref, &retHeap);
      if(  retHeap != null    //the reference is in any heap.
        && (blockWithReference->typeOrMaxRef & mConsideredInGarbage_Type_Object) //the block is to be tested in GC
        )
      { /** The reference to this block is located in another or this block.
         *  It is possible that this other block is referenced from any other or not.
         *  The blockWithReference builds a cluster with all the other blocks with references between it.
         *  If any block of the cluster have a reference outside, the blocks are used.
         *  But if no reference from outside is found, all of the blocks of the cluster are freed.
         */
        if( blockWithReference->nextBlock == null) //and the block isnot already observed by GC
        { blockWithReference->nextBlock = block->nextBlock;
          block->nextBlock = blockWithReference;
          { //report:
            flushFullReportBuffer(ythis, 32, _thCxt);
            ythis->idxReportBuffer += sprintf(ythis->reportBuffer + ythis->idxReportBuffer, " + %p ", blockWithReference);
          }
        }
        else
        { /**The block is already the queue and part of the cluster.
           * It will be tested later.
           */
        }
        flushFullReportBuffer(ythis, 32, _thCxt);
        ythis->idxReportBuffer += sprintf(ythis->reportBuffer + ythis->idxReportBuffer, " blk=%p(%p), ", ref, retHeap);
      }
      else
      { /**A reference outside a GC-controlled block indicates, that the block is referenced, in use.
         * Therefore all blocks of the cluster are used.
         */
        bInUse = true;
        flushFullReportBuffer(ythis, 32, _thCxt);
        ythis->idxReportBuffer += sprintf(ythis->reportBuffer + ythis->idxReportBuffer, " ext=%p, ", ref);
      }
    }
  }while(!bInUse && ++idxBackref < maxBackref);
  STACKTRC_LEAVE; return bInUse;
}






/**This method starts with one block and collects and tests all blocks, there have back references to the first block
 * or to a always tested block of the cluster. If no reference from outside is found to any block of the cluster,
 * the method returns false. All tested blocks are marked started with the first block with a chain of blocks,
 * using the nextBlock-association of the BlockHeapBlockJc-struct.
 * Therefore started from the first block the cluster is known from outside.
 *
 * @param block The first block to test.
 * @return true if a outside reference is found.
 */
static bool testBlockCluster_GarbageCollectorJc(GarbageCollectorJc* ythis, BlockHeapBlockJc* block, bool bUserCall)
{
  BlockHeapBlockJc* firstBlock = block;
  bool bInUse = false;
  STACKTRC_ENTRY("testBlockCluster_GarbageCollectorJc");
  block->nextBlock = kLastBlockInGarbageCtest_BlockHeapJc;  //mark it with !=null
  { //report:
    if(ythis->idxReportBuffer >0)
    { sendMsg_z_LogMessageFW(ythis->log, 1001, ythis->reportBuffer, _thCxt);
    }
    ythis->idxReportBuffer = sprintf(ythis->reportBuffer, "GC-test; block=%p;", block);
  }
  do
  { /* test all blocks of a cluster which are referencing one to another,
     * pick up all this blocks and test wether a from outside is found to a block of this cluster
     */
    ythis->countStep +=1;
    bInUse = testBlock_GarbageCollectorJc(ythis, block);
    if(ythis->testMethod != null)
    { ythis->testMethod(ythis->countStep);
    }
    //either all references are tested, and no external reference is found, or a external reference is found.
    if(!bInUse)
    { /**no exterenal reference is found, but the cluster of blocks may increased, test the next:
       */
      block = block->nextBlock;
    }
  }while(  !bInUse                                        //break if any block is used, than the cluster is used.
        && block != kLastBlockInGarbageCtest_BlockHeapJc  //break if all blocks of the cluster are tested.
        && !theGarbageCollectorJc.bAbortTest              //break if any block in cluster is reused.
        && !theGarbageCollectorJc.bAbortTestBecauseUserCall //break if System.gc() is called.
        );
  //
  if(!bUserCall && (theGarbageCollectorJc.bAbortTest || theGarbageCollectorJc.bAbortTestBecauseUserCall))
  { /**Abort the test because a higher priority call executes the gc. */
    flushFullReportBuffer(ythis, 32, _thCxt);
    ythis->idxReportBuffer += sprintf(ythis->reportBuffer + ythis->idxReportBuffer, " -abort because reuse of any block");
    bInUse = true;
  }
  //
  if(bInUse)
  { /* At least one block of this cluster of blocks is used from outside, or the test is aborted:
     * Than all blocks of the cluster are used, because the others are used from blocks.
     * Or the test is aborted because a block of the cluster is resused in any way. The test have to repeat than.
     * Thad do not delete it.
     * But the queue of blocks should be disintegrated.
     */
    do
    { //remove the chain of tested blocks from the blocks to prevent disturbance of a later check.
      block = firstBlock;
      firstBlock = block->nextBlock;
      block->nextBlock = null;
    } while(firstBlock != kLastBlockInGarbageCtest_BlockHeapJc);
    theGarbageCollectorJc.bAbortTest = false;
    theGarbageCollectorJc.bAbortTestBecauseUserCall = false;
  }
  else
  { //all blocks were tested, they are not referenced from outside.
    do
    { BlockHeapJc* blockHeap;
      block = firstBlock;      //process all blocks of the cluster.
      searchBlockHeapBlock_BlockHeapJc(block, &blockHeap);  //to get the heap control structure.
      firstBlock = block->nextBlock;
      if(block->obj != null)
      { Mtbl_ObjectJc const* mtbl;
        CALLINE; mtbl = (Mtbl_ObjectJc const*)getMtbl_ObjectJc(block->obj, sign_Mtbl_ObjectJc);
        //mtbl may be null if no reflection of obj is given.
        if(mtbl != null)
        { mtbl->finalize(block->obj, _thCxt);
        }
      }
      //call finalize
      memset(block, 0, SIZEBLOCK_BlockHeapJc);
      free_BlockHeapJc(blockHeap, block, _thCxt);
      { //report
        char* reportBufferPos = ythis->reportBuffer + ythis->idxReportBuffer;
        flushFullReportBuffer(ythis, 32, _thCxt);
        ythis->idxReportBuffer += sprintf(reportBufferPos, " => freed=%p", block);
      }
      
    } while(firstBlock != kLastBlockInGarbageCtest_BlockHeapJc);
  }/*while: test all references from outside to all blocks of this cluster*/
  //
  STACKTRC_LEAVE; return bInUse;
}





/**Run of one garbage collection action. 
 * All free blocks till the first used block are checked.
 * One used block and all its associated blocks are checked. 
 * @return 0-if a block is handled, but not freed.
 *         1-if a block is handled and freed.
 *         2-if the end is found
 */
static int garbageCollection__GarbageCollectorJc(GarbageCollectorJc* ythis, bool bUserCall, ThCxt* _thCxt)
{
  int success;

  BlockHeapBlockJc* block;
  bool bInUse = false;
  LogMessageFWMTB mlog = {0};
  STACKTRC_TENTRY("garbageCollection_BlockHeapJc");

  if(ythis->log !=null) {
    mlog.ref = ythis->log;
    mlog.mtbl = (Mtbl_LogMessageFW const*)getMtbl_ObjectJc(&mlog.ref->base.object, sign_Mtbl_LogMessageFW);
  }


  if(ythis->testedHeap == null)
  { //Either the first or a new wrapping of check is started.
    ythis->testedHeap = theBlockHeapList;
    ythis->log = ythis->testedHeap->log;
    ythis->kIdentMsgBase = ythis->testedHeap->kIdentMsgBase;
    ythis->idxBlock = -1;
    ythis->ctFreeBlocks = 0;
    ythis->ctNonGcBlocks = 0;
    ythis->ctFreedBlocks = 0;
    ythis->ctUsedBlocks = 0;
    ythis->startTime = os_getDateTime();
  }  //load on first run.

  do
  { //this loop searches the next used block.
    if(++ythis->idxBlock >= ythis->testedHeap->zBlock)
    { //evaluate the next heap
      //it is a wrapping call, report the state found before:
      OS_TimeStamp endTime = ythis->endTime = os_getDateTime();
      int32 dTime = 1000 * (endTime.time_sec - ythis->startTime.time_sec)
                  + ((nanoSeconds_OS_TimeStamp(endTime) - nanoSeconds_OS_TimeStamp(ythis->startTime))/1000000);
      flushFullReportBuffer(&theGarbageCollectorJc, 1, _thCxt);
      if(ythis->log !=null) {
        mlog.mtbl->sendMsgTime(mlog.ref,ythis->kIdentMsgBase + identMsgReport_BlockHeapJc
        , endTime
        , "GC-result, %d millisec: size/free/used/nonGc = %d / %d / %d / %d, freed=%d"
        , "IIIIII"
        , dTime
        , ythis->idxBlock
        , theGarbageCollectorJc.ctFreeBlocks
        , theGarbageCollectorJc.ctUsedBlocks
        , theGarbageCollectorJc.ctNonGcBlocks
        , theGarbageCollectorJc.ctFreedBlocks
        );
        flush_LogMessageFW(theGarbageCollectorJc.log, _thCxt);
      }
      ythis->idxBlock = 0;
      ythis->testedHeap = ythis->testedHeap->nextHeap;  //null at end
      if(ythis->testedHeap != null)
      { ythis->log = ythis->testedHeap->log;
        ythis->kIdentMsgBase = ythis->testedHeap->kIdentMsgBase;
      }
    }
    block = ythis->testedHeap == null ? null : (BlockHeapBlockJc*)( addOffset_MemAreaC(ythis->testedHeap->heapBegin, ythis->idxBlock * SIZEBLOCK_BlockHeapJc));
    success = -1;
    if(block != null){
      if(block->typeOrMaxRef == kFree_Type_BlockHeapBlock){
        ythis->ctFreeBlocks +=1;
      } else if((block->typeOrMaxRef & mSmallBlock_Type_Object) != 0) { 
        //TODO: handle small blocks. Test whether all blocks are free.
      }else if((block->typeOrMaxRef & mConsideredInGarbage_Type_Object) == 0) {
        ythis->ctNonGcBlocks +=1;
        if(mlog.ref != null){
          mlog.mtbl->sendMsg(mlog.ref,ythis->kIdentMsgBase + identMsgBlockNoGc_BlockHeapJc, "GC: block non-GC, addr=%8.8X, created at=%tR from %s"
            , "PIz", block, block->timeCreation, block->sCreaterInfo);
        }
      } else {
        success = checkGcBlockUsed_BlockHeapJc;
      }
    } else {
      success = checkGcFinished_BlockHeapJc;
    }
  } while( success < 0);         //break if all heaps are pass through.

  if(block != null)
  { //a used block is found.
    if(testBlockCluster_GarbageCollectorJc(ythis, block, bUserCall)){
      success = checkGcBlockUsed_BlockHeapJc;
      ythis->ctUsedBlocks +=1;
    } else { 
      success = checkGcBlockFreed_BlockHeapJc;
      ythis->ctFreedBlocks +=1;
    }
    if(ythis->log != null) {
      if(success == checkGcBlockFreed_BlockHeapJc)
      { //all blocks were tested, they are not referenced from outside.
        sendMsg_z_LogMessageFW(ythis->log, ythis->kIdentMsgBase + identMsgBlockFree_BlockHeapJc, ythis->reportBuffer, _thCxt);
      }/*while: test all references from outside to all blocks of this cluster*/
      else
      {
        sendMsg_z_LogMessageFW(ythis->log, ythis->kIdentMsgBase + identMsgGcWork_BlockHeapJc, ythis->reportBuffer, _thCxt);
      }
    }
  }/*if a used block is found. */
  else {
    success = checkGcFinished_BlockHeapJc;  //end is found.
  }
  STACKTRC_LEAVE;
  return success;
  //return block != null && !bInUse;  //true if a block is freed.
}



/**A static instance of the singleton garbage collector class. */
GarbageCollectorJc theGarbageCollectorJc = {0};


void gc_SystemJc(ThCxt* _thCxt){ runUserCalledGc_BlockHeapJc(_thCxt); }


bool runUserCalledGc_BlockHeapJc(ThCxt* _thCxt)
{ /**Runs in a loop only if */
  bool bAnyFreed = false;
  int success;
  STACKTRC_TENTRY("runUserCalledGc_BlockHeapJc");
  theGarbageCollectorJc.bAbortTestBecauseUserCall = true; //abort a test in the thread of gc
  theGarbageCollectorJc.testedHeap = null; //start from first entry.
  do {
    success = garbageCollection_BlockHeapJc(true, _thCxt);
    if(success == 1) {
      bAnyFreed = true;
    }
  } while(success != 2);  //loop while any block is handled.
  if(theGarbageCollectorJc.log != null) {
    if(theGarbageCollectorJc.log != null){
      flushFullReportBuffer(&theGarbageCollectorJc, 1, _thCxt);
      sendMsg_tzzv_LogMessageFW(theGarbageCollectorJc.log, theGarbageCollectorJc.kIdentMsgBase + identMsgReportBlocks_BlockHeapJc
      , os_getDateTime()
      , "user called GC runs, free/used/nonGc = %d / %d / %d, freed=%d"
      , "IIII"
      , theGarbageCollectorJc.ctFreeBlocks
      , theGarbageCollectorJc.ctUsedBlocks
      , theGarbageCollectorJc.ctNonGcBlocks
      , theGarbageCollectorJc.ctFreedBlocks
      );
      flush_LogMessageFW(theGarbageCollectorJc.log, _thCxt);
    }
  }
  STACKTRC_LEAVE; return bAnyFreed;
}





int garbageCollection_BlockHeapJc(bool bUserCall, ThCxt* _thCxt)
{
  /**A buffer to write reports running GC. */
  int success;
  theGarbageCollectorJc.idxReportBuffer = 0;
  success = garbageCollection__GarbageCollectorJc(&theGarbageCollectorJc, bUserCall, _thCxt);
  return success;
}


void setTestMethod(MT_int_Method_int testMethod)
{ theGarbageCollectorJc.testMethod = testMethod;
}


StringJc report_BheapJc(BlockHeapJc* ythis, int* idxBlockP, StringBufferJc* buffer)
{ StringJc ret = null_StringJc;
  int idxBlock = *idxBlockP;
  bool bSearch = true;
  STACKTRC_ENTRY("report_BheapJc");
  if(idxBlock < 0) THROW_s0(IndexOutOfBoundsException,"",idxBlock);
  while(bSearch)
  { if(idxBlock >= ythis->zBlock)
    { ret = null_StringJc; idxBlock = -1; bSearch = false;
    }
    else
    { BlockHeapBlockJc* block = (BlockHeapBlockJc*)(&ythis->heapBegin[idxBlock]);
      if( block->typeOrMaxRef != kFree_Type_BlockHeapBlock)
      { //found a used block, report it:
        setLength_StringBuilderJc(buffer, 0, _thCxt);

      }
      else
      { idxBlock +=1;
      }
    }
  }

  STACKTRC_LEAVE; return ret;

}





