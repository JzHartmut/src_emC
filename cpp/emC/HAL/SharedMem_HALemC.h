#ifndef HGUARD_SharedMem_HALemC
#define HGUARD_SharedMem_HALemC
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>



typedef struct SharedMem_HALemC_T {
  union { ObjectJc object; } base;

  void const* internalData;



} SharedMem_HALemC_s;


void* open_SharedMem_HALemC ( SharedMem_HALemC_s* thiz, char const* name, int size);


void close_SharedMem_HALemC(SharedMem_HALemC_s* thiz);


#endif //SharedMem_HALemC
