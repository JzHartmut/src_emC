#ifndef __FBaccess_Inspc_priv_h__
#define __FBaccess_Inspc_priv_h__

#include <Inspc/FBaccess_Inspc.h>
#include <InspcJ2c/Inspector_Inspc.h>
#include <Fwc/objectBaseC.h>
#include <Jc/ReflectionJc.h>




typedef struct FBaccessNode_Inspc_t
{ ObjectJc super;
  //struct ObjectJc_t* obj[10];

  /**Reference to the instances or sub nodes. */
  void* data[100];
  
#ifndef __NoReflection__
  /**Instance of the Reflection definition of this node. It is not for a user instance. It is this node. */ 
  ClassJc clazz;
  /**All fields of this node, it refers either the reflection class of the instances or the clazz of a sub node. 
   * Note: The FieldsJC_Y definition contains less (10) fields staticly, whereby it is dynamicly possible.
   */ 
  FieldJc_Y fields;
  /**Rest to 100 fields in sum. */
  FieldJc _addFields[90];
#endif//__NoReflection__

} FBaccessNode_Inspc;


typedef struct FBaccess_Inspc_t
{ ObjectJc super;
  FBaccessNode_Inspc* rootNode;
  Inspector_Inspc_s theInspector;
} FBaccess_Inspc;



#endif //__FBaccess_Inspc_priv_h__
