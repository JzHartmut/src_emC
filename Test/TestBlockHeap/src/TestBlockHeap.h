#ifndef __TestBlockHeap_h__
#define __TestBlockHeap_h__
#include <os_types_def.h>
#include <Fwc/fw_LogMessage.h>

struct Data2;

typedef struct DataIntern_t
{ ObjectJc object;
  int32 x,y;
  struct Data2* ref2;
}DataIntern_s;



typedef struct Data_t
{ ObjectJc object;
  
  DataIntern_s dataIntern;
}Data_s;


typedef struct Data2
{ ObjectJc object;
  
  DataIntern_s* ref1;
}Data2_s;


void alloc1(LogMessageFW_MREF log);

void testListMap(LogMessageFW_MREF log);


#endif  //__TestBlockHeap_h__
