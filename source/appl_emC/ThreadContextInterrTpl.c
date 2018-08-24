#include <incApplSpecific/applConv/ExcStacktrcNo_emC.h>
#include <OSAL/os_thread.h>


//Note: This source should only used on Windows if threads are not used (not using os_threa.c) 
//It is a template for organization of a ThreadContext of a simple CPU without Operation system, with hardware interrupts.


/**Structure for ThreadContexts for Main and 2 Interrupts. */
typedef struct ThCxt_Application_t {

  /**The pointer to the current ThreadContext. */
  ThreadContext_emC_s* currThCxt;

  ThreadContext_emC_s thCxtMain;

  ThreadContext_emC_s thCxtIntr1;

  ThreadContext_emC_s thCxtIntr2;
}ThCxt_Application_s;

/**public static definition*/
ThCxt_Application_s thCxtAppl_g = { &thCxtAppl_g.thCxtMain, { 0 }, { 0 }, { 0 } };

/**A template how to use. */
void interrupt_handler() {
  ThreadContext_emC_s* thCxtRestore = thCxtAppl_g.currThCxt;
  thCxtAppl_g.currThCxt = &thCxtAppl_g.thCxtIntr1;
  
  //the statements of the Interrupt
  
  thCxtAppl_g.currThCxt = thCxtRestore;
  //end of interrupt
}



ThreadContext_emC_s* getCurrent_ThreadContext_emC  ()
{
  return thCxtAppl_g.currThCxt;  
}



bool stop_AssertJc( ){
  return false;
}
