#include "TestListMap.h"
#include "TestBlockHeap.h"
#include <Fwc/fw_SimpleC.h>
#include <Fwc/fw_MemC.h>
//#include <BlockHeap/BlockHeapJc.h>

#include <Jc/LinkedListJc.h> 
#include <Jc/SystemJc.h>          //gc_SystemJc() 
/**This routine demonstrates and tests a simple usage of LinkedList
 */
void testListMap(LogMessageFW_MREF log)
{ int ix;
  DataIntern_s* data;
  LinkedListJc list;
  STACKTRC_ENTRY("testListMap");
  init_ObjectJc(&list.base.object, sizeof(LinkedListJc),0);
  ctorO_LinkedListJc(&list.base.object);  

  for(ix=0; ix < 10; ++ix){
    data = (DataIntern_s*)alloc_ObjectJc(sizeof(DataIntern_s), 0, _thCxt);
    add_LinkedListJcF(&list, &data->object, _thCxt);
    //it is neccesary to transfer the responsibility to the garbage collector, 
    //after the data are referenced.
    activateGC_ObjectJc(data, null, _thCxt);
  }

  gc_SystemJc(_thCxt);

  while(size_LinkedListJcF(&list) >0){
    data = (DataIntern_s*)remove_LinkedListJcF(&list, _thCxt);
    
  }
  gc_SystemJc(_thCxt);
  
  STACKTRC_LEAVE;

}


