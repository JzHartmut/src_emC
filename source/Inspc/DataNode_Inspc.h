#ifndef __DataNode_Inspc_h__
#define __DataNode_Inspc_h__
#include <Fwc/objectBaseC.h>
#include <Jc/ReflectionJc.h>

/**struct of references for Inspector access.
 * The references and their reflection informations can be added step by step. 
 */
typedef struct DataNode_Inspc_t
{ ObjectJc object;
  //struct ObjectJc_t* obj[10];

  /**Reference to the instances or sub nodes. It can be any type. */
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

} DataNode_Inspc;

//Compatibility:
#define FBaccessNode_Inspc DataNode_Inspc
#define FBaccessNode_Inspc_t DataNode_Inspc_t


DataNode_Inspc* ctor_DataNode_Inspc(ObjectJc* thizo, int nrofObjects);



/**Registers an Object in the given node.
 * @param name1_param first part of the name. The 2 parts of name offers the capability to use a instance name given in a variable 
 *   and a constant part of name for this block.  
 * @param name2_param second part of the name. Both parts are concatenated immediately. This is the name which is used for the block in the reflection tree. 
 * @param data It should be a reference to ObjectJc with valid reflection. The reflection are necessary to evaluate the data with inspector.
 *  Note: The void type is yet necessary to accept any type of data. TODO use ObjectJc* instead void*.
 * @simulink Sfunc
 */
char const* addObj_DataNode_Inspc(struct DataNode_Inspc_t* thiz, StringJc name1_param, StringJc name2_param, ObjectJc* data);



#endif  //__DataNode_Inspc_h__
