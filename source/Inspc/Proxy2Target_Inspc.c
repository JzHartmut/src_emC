#include "Inspc/Proxy2Target_Inspc.h"


#ifndef __DONOTUSE_REFLECTION__
#include "Inspc/Proxy2Target_Inspc.crefl"
#else

#endif



Proxy2Target_Inspc* ctor_Proxy2Target_Inspc(ObjectJc* thizo, ThCxt* _thCxt) {
  STACKTRC_TENTRY("ctor_Proxy2Target_Inspc");
  checkInit_ObjectJc(thizo, sizeof(Proxy2Target_Inspc), 0, &reflection_Proxy2Target_Inspc, THCXT);
  STACKTRC_RETURN (Proxy2Target_Inspc*) thizo;
}
