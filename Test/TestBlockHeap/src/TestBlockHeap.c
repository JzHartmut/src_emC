#include "TestBlockHeap.h"
#include <Fwc/fw_SimpleC.h>
#include <Fwc/fw_MemC.h>
#include <BlockHeap/BlockHeapJc.h>

/**This routine demonstrates and tests a simple usage of all blocks 
 * in this routine without any referencing. 
 */
void alloc1(LogMessageFW_MREF log)
{ int ix;
  Data_s* data[15] = {0};   //a local array of references.
  STACKTRC_ENTRY("alloc1");
  //
  log.mtbl->sendMsg(log.ref, 1, "Test: Allocation of all blocks.", "");
  /**All blocks will be reserved. */
  for(ix=0; ix<ARRAYLEN(data); ++ix) {
    //alloc, the result is a MemC
    MemC memAllocated = allocMemC_BlockHeapJc(_thCxt->blockHeap, sizeof(Data_s), -1, "test", _thCxt);
    data[ix] = PTR_MemC(memAllocated, Data_s);  //store the pointer of type Data_s
  }
  /**...The blocks may be used in this thread. */
  /**The blocks are reserved. The GC mustn't free blocks, which are allocated just now, 
   * if it is run in another thread. */
  log.mtbl->sendMsg(log.ref, 2, "try to run GC, it shouldn't freed anything.", "");
  runUserCalledGc_BlockHeapJc(_thCxt);
  //
  /**All reserved blocks will be assigned to GC-access. Because it aren't referenced, it will be freed. 
   */
  log.mtbl->sendMsg(log.ref, 3, "activateGarbageCollectorAccess for all blocks.", "");
  for(ix=0; ix<ARRAYLEN(data); ++ix) {
    activateGarbageCollectorAccess_BlockHeapJc(data[ix], null);
  }
  /**The GC frees all blocks. */
  log.mtbl->sendMsg(log.ref, 2, "run GC, it should freed all:", "");
  runUserCalledGc_BlockHeapJc(_thCxt);
  STACKTRC_LEAVE;
}




/**This routine demonstrates and tests a simple usage of all blocks 
 * in this routine without any referencing. 
 */
void allocListNode(LogMessageFW_MREF log)
{ int ix;
  Data_s* data[15] = {0};   //a local array of references.
  STACKTRC_ENTRY("alloc1");
  //
  log.mtbl->sendMsg(log.ref, 1, "Test: Allocation of all blocks.", "");
  /**All blocks will be reserved. */
  for(ix=0; ix<ARRAYLEN(data); ++ix) {
    //alloc, the result is a MemC
    MemC memAllocated = allocMemC_BlockHeapJc(_thCxt->blockHeap, sizeof(Data_s), -1, "test", _thCxt);
    data[ix] = PTR_MemC(memAllocated, Data_s);  //store the pointer of type Data_s
  }
  /**...The blocks may be used in this thread. */
  /**The blocks are reserved. The GC mustn't free blocks, which are allocated just now, 
   * if it is run in another thread. */
  log.mtbl->sendMsg(log.ref, 2, "try to run GC, it shouldn't freed anything.", "");
  runUserCalledGc_BlockHeapJc(_thCxt);
  //
  /**All reserved blocks will be assigned to GC-access. Because it aren't referenced, it will be freed. 
   */
  log.mtbl->sendMsg(log.ref, 3, "activateGarbageCollectorAccess for all blocks.", "");
  for(ix=0; ix<ARRAYLEN(data); ++ix) {
    activateGarbageCollectorAccess_BlockHeapJc(data[ix], null);
  }
  /**The GC frees all blocks. */
  log.mtbl->sendMsg(log.ref, 2, "run GC, it should freed all:", "");
  runUserCalledGc_BlockHeapJc(_thCxt);
  STACKTRC_LEAVE;
}


