//#include <applstdefJc.h>
#include <FwConv_h/ObjectJc_simple.h>

ObjectJc* initReflection_ObjectJc(ObjectJc* thiz, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj)
{

  thiz->identification = identObj;

  return thiz;
}
