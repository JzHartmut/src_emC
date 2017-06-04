#ifndef FBaccessNode_Inspc_data_h__
#define FBaccessNode_Inspc_data_h__
#include <Fwc/objectBaseC.h>
#include <Jc/ReflectionJc.h>

/**Struktur einer Node für Reflection in einem Simulationssystem. 
 * Attention: If this struct was changed, all dynamic libraries should recompiled which uses it!!! 
 * Especially it are all libs which contains 'FPaccessNode_RegisterRefl_Inspc.c'. That may be much.
 */
typedef struct FBaccessNode_Inspc_t
{ ObjectJc object;
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



#endif  //FBaccessNode_Inspc_data_h__
