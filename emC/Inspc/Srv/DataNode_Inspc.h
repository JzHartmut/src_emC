#ifndef __DataNode_Inspc_h__
#define __DataNode_Inspc_h__
#include <emC/Base/Object_emC.h>
#include <emC/Jc/ReflectionJc.h>


struct DataNode_Inspc_t;
/**struct of references for Inspector access.
 * The references and their reflection informations can be added step by step. 
 */
typedef struct DataNode_Inspc_t
{ union{ ObjectJc object;} base;
  //struct ObjectJc_t* obj[10];

  /**Reference to the instances or sub nodes. It can be any type. */
  void* data[50];
  
  /**Instance of the Reflection definition of this node. It is not for a user instance. It is this node. */ 
  ClassJc clazz;

  struct {
    ObjectArrayJc head;
    ClassOffset_idxVtblJc clazz;
  } superclass;

  /**All fields of this node, it refers either the reflection class of the instances or the clazz of a sub node.
   * Note: The FieldsJC_Y definition contains less (10) fields staticly, whereby it is dynamicly possible.
   */ 
  FieldJc_Y fields;
  /**Rest to 100 fields in sum. */
  FieldJc _addFields[40];

} DataNode_Inspc;

//Compatibility:
#define FBaccessNode_Inspc DataNode_Inspc
#define FBaccessNode_Inspc_t DataNode_Inspc_t


/**Creates a new DataNode, its output should be registered either as root Node on Service_Inspc or as Object at any other DataNode. 
 * @simulink ctor
 */
DataNode_Inspc* ctor_DataNode_Inspc(DataNode_Inspc* thiz, int nrofObjects, float Tstep);



/**Creates a new DataNode, only a dummy for construction. 
 * @simulink Object-FB
 */
inline void create_DataNode_Inspc(struct DataNode_Inspc_t* thiz) { }







void addObjRefl_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, void* obj, ClassJc const* reflectionClass);



/**Registers an Object in the given node.
* @param name1_param first part of the name. The 2 parts of name offers the capability to use a instance name given in a variable
*   and a constant part of name for this block.
* @param name2_param second part of the name. Both parts are concatenated immediately. This is the name which is used for the block in the reflection tree.
* @param data It should be a reference to ObjectJc with valid reflection. The reflection are necessary to evaluate the data with inspector.
*  Note: The void type is yet necessary to accept any type of data. TODO use ObjectJc* instead void*.
* @param ok_y: It is checked as input. If not 0 then the add operation is performed already.
*    It can used to signal that data via reflection can be accessed now.
* @simulink Operation-FB, try-catch.
*/
void addObj_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, ObjectJc* data, int32* ok_y);




/**Checks whether thiz is the correct instance, via reflection. 
 * @return false if thiz is null or a faulty pointer. 
 */
bool checkObject_DataNode_Inspc(DataNode_Inspc* thiz);



/**Registers a Node.
 * @param name1_param first part of the name. The 2 parts of name offers the capability to use a instance name given in a variable 
 *   and a constant part of name for this block.  
 * @param name2_param second part of the name. Both parts are concatenated immediately. This is the name which is used for the block in the reflection tree. 
 * @param data It should be a reference to ObjectJc with valid reflection. The reflection are necessary to evaluate the data with inspector.
 *  Note: The void type is yet necessary to accept any type of data. TODO use ObjectJc* instead void*.
 * @  simulink Operation-FB
 */
void XXXadd_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, void const* data, int32* ok_y);

/**Registeres Reflection from any Object in a FBaccessNode for a runtime reflection tree. 
 * @param thiz Instance pointer for this method. null is admissiable here.
 * @param obj Any instance of a given struct which has reflection. It need not based on ObjectJc. 
 * @param name The identifier of the instance in this FBaccessNode. Name in reflection tree.
 * @param refl The reflection instance appropriate to the struct of the obj.
 * @return true if success. Especially thiz will be checked whether it is a valid reference. null is admissable for thiz.
 */
bool registerRefl_DataNode_Inspc(DataNode_Inspc* thiz, void* obj, char const* name, struct ClassJc_t const* refl);
#define registerRefl_FBaccessNode_Inspc registerRefl_DataNode_Inspc


#endif  //__DataNode_Inspc_h__
