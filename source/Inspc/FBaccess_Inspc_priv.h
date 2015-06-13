#ifndef __FBaccess_Inspc_priv_h__
#define __FBaccess_Inspc_priv_h__

#include <Inspc/FBaccess_Inspc.h>
#include <InspcJ2c/Inspector_Inspc.h>
#include <Fwc/objectBaseC.h>
#include <Jc/ReflectionJc.h>




typedef struct FBaccessNode_Inspc_t
{ ObjectJc super;
  //struct ObjectJc_t* obj[10];

  void* data[100];
  
#ifndef __NoReflection__
  ClassJc clazz;

  FieldJc_Y fields;
  FieldJc _addFields[90];
#endif//__NoReflection__

} FBaccessNode_Inspc;



typedef struct FBaccess_Inspc_t
{ ObjectJc super;
  FBaccessNode_Inspc* rootNode;
  Inspector_Inspc_s theInspector;
} FBaccess_Inspc;



#endif //__FBaccess_Inspc_priv_h__
