#include "TestBlockHeap.h"

#include <Fwc/fw_basic.h>
#include <Jc/StringJc.h>
#include <BlockHeap/BlockHeapJc_admin.h>
#include <io.h>
#include <fcntl.h>
//METHOD_C int32 main_TestAllConcepts_Test(/*static*/ StringJc_Y* args, ThCxt* _thCxt);


BlockHeapJc blockHeap;
    
/**Simple test of the BlockHeap to debug the working of allocation and garbage collection:
 */
void testBlockHeap1()
{
        //

}


void main()
{
  int logFile; // | O_TRUNC);
  struct LogMessageFW_t* log;
  STACKTRC_ENTRY("main");  //it ininitalizes the Stacktrace in the Thread-context automatically.
  { 
  /**The log file for garbage collector, use lo-level-file-io
   * because the lo-level-message-outputter is used here (not the real MsgDispatcher). 
   */
  chmod("testlog.txt", 0x1FF); //set file write.able, to delete it.
  unlink("testlog.txt");       //delete the file.
  logFile = open("testlog.txt", O_RDWR | O_CREAT); // | O_TRUNC);
  //Log output of the garbage collectors working in a file:.
  log = create_LogMessageStream_FW(logFile, _thCxt);
  
  /**Initializes one block heap. There may be more as one, but for the test environment only one.
   * The Blockheap is not a singleton, but there is a default Blockheap per thread.
   * In this example the blockheap-management structure is given as static data blockHeap, defined above.
   */
  init_ObjectJc(&blockHeap.base.object, sizeof(BlockHeapJc), 0);
  MemC memHeap = alloc_MemC(0x4000);            //alloc the space for all blocks of this heap.
  int sizeBlock = 0x400;                        //The block-size.
  int sizeSmallBlock = 0x7c;                    //Small block size. 8 Blocks per normal block.
  ctorO_BlockHeapJc(&blockHeap.base.object, memHeap, sizeBlock, sizeSmallBlock);
  
  //setLogMessageStreamput_BlockHeapJc(log, 2000, _thCxt);
  
  /**This heap is used in this thread. */
  setCurrent_BlockHeapJc(&blockHeap, _thCxt);
  
  /**Up to now an allocation is done in the BlockHeap. 
   * Before that, the allocation is done calling os_allocMem(...), which allocs from operation system.*/
  setRunMode_BlockHeapJc(&blockHeap, log, 2000);

   /**Test routines: */
  { LogMessageFW_MREF logMref = { log, &mtbl_LogMessageStream_FW.LogMessage_FW_i}; 
    
    testLastAccess((struct NodePoolJc_t*)&blockHeap, _thCxt); 
    //alloc1(logMref);
    testListMap(logMref);
  }
  
  
  close(logFile);
  }
  STACKTRC_LEAVE;
}