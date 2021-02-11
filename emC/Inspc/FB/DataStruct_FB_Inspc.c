#include <applstdef_emC.h>
#ifdef DEF_REFLECTION_FULL
#include <emC/Inspc/FB/DataStruct_Inspc.h>
#include <emC/OSAL/os_mem.h>
#include <emC/base/Handle_ptr64_emC.h>

uint32 initSimple_DataStructFB_Inspc ( int nrofInputs, char const* param) 
{
  STACKTRC_ENTRY("initSimple_DataStructFB_Inspc");
  int sizePortInfo = sizeof(DefPortTypes_emC) + (nrofInputs -1) * sizeof(Entry_DefPortType_emC);
  DefPortTypes_emC* portInfo = (DefPortTypes_emC*)os_allocMem(sizePortInfo);
  portInfo->nrofInputs = nrofInputs;
  DataStructMng_Inspc* thiz = (DataStructMng_Inspc*)os_allocMem(sizeof(DataStructMng_Inspc));
  ctor_DataStructMng_Inspc(thiz, portInfo, param, 0, 0);
  init_DataStructMng_Inspc(thiz, null_StringJc, z_StringJc(param), null);
  //convert to handle, for outsize ref
  uint32 hthis = registerPtr_Handle2Ptr(thiz, "NNN");
 
  STACKTRC_RETURN hthis;
}

#endif //DEF_REFLECTION_FULL

