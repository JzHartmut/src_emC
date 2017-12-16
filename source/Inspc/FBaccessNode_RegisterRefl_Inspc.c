/**This file is the only one which should be added to a simulink-mex library to register a S-function for reflection.
 * The whole inspector binaries are not necessary therefore. They should not need in a extra binary image.
 */
#include <Inspc/DataNode_Inspc.h>
#include <Inspc/FBaccess_Inspc.h>
#include <string.h>
#include <fwc/fw_String.h>


bool registerRefl_DataNode_Inspc(struct DataNode_Inspc_t* thiz, void* obj, char const* name, struct ClassJc_t const* refl){
  if(!checkObject_DataNode_Inspc(thiz)) return false;
  int ix1;
  int ix = thiz->fields.head.length;  //the current length
  //check whether it is registered already. This routine may be called twice:
  for(ix1 = 0; ix1 < ix; ++ix1) {
    if(thiz->data[ix1] == obj) { 
      break;
    }
  } 
  if(ix1 == ix) { //onyl if not found, all checked:
    if(ix < ARRAYLEN_SimpleC(thiz->data)) {
      thiz->data[ix] = obj;
      strncpy(thiz->fields.data[ix].name, name, sizeof(thiz->fields.data[ix].name));
      thiz->fields.data[ix].type_ = refl;
      thiz->fields.data[ix].bitModifiers = kReference_Modifier_reflectJc;
      thiz->fields.data[ix].position = ((MemUnit*)&thiz->data[ix]) - ((MemUnit*)thiz);

      thiz->fields.head.length = ix + 1;
      return true;
    }
  }
  return false;
}



char const* add_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, void const* data, int32* ok_y)
{
  return addObj_DataNode_Inspc(thiz, name1_param, name2_param, (struct ObjectJc_t*) data, ok_y); 
}

char const* addObj_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, ObjectJc* obj, int32* ok_y)
{ 
  if(*ok_y == 0) {
    const char* error = null;
    if(!checkObject_DataNode_Inspc(thiz)) { return "input 1 is not a DataNode_Inspc"; }
    if(obj == null || obj->ownAddress != obj || obj->reflectionClass == null) {
      return "input 3: obj is not based on ObjectJc, or it has not reflection information.";
    }
    if(isInitialized_ObjectJc(&thiz->object)) {
      *ok_y = 1;
      return addObjRefl_DataNode_Inspc(thiz, name1_param, name2_param, obj, obj->reflectionClass);
    } else return null;
  } else return null; //do nothing. 
}




char const* addObjRefl_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, void* obj, ClassJc const* reflectionClass)
{ int ix, ix1;
  //same algorithm as above, but with 2 StringJc
  ix = thiz->fields.head.length;  //the current length
  //check whether it is registered already. This routine may be called twice:
  for(ix1 = 0; ix1 < ix; ++ix1) {
    if(thiz->data[ix1] == obj) { 
      break;
    }
  } 
  if(ix1 == ix) { //onyl if not found, all checked:
    if(ix >= ARRAYLEN_SimpleC(thiz->data)) {
      return "too much registration in registerNode_AccessNode_Inspc(...)";
    }
    thiz->data[ix] = obj;
    { int nchars = copyToBuffer_StringJc(name1_param, 0, -1, thiz->fields.data[ix].name, sizeof(thiz->fields.data[ix].name));
      copyToBuffer_StringJc(name2_param, 0, -1, thiz->fields.data[ix].name+nchars, sizeof(thiz->fields.data[ix].name)-nchars); //the rest.
    }
    //strncpy(thiz->fields.data[ix].name, name, sizeof(thiz->fields.data[ix].name));  //TODO check length of name!!!
    thiz->fields.data[ix].type_ = reflectionClass;
    thiz->fields.data[ix].bitModifiers = kReference_Modifier_reflectJc;
    thiz->fields.data[ix].position = ((MemUnit*)&thiz->data[ix]) - ((MemUnit*)thiz);

    thiz->fields.head.length = ix + 1;
  }
  return null;
}



bool checkObject_DataNode_Inspc(struct DataNode_Inspc_t* thiz){
  if(thiz == null) return false;
  if(thiz->object.ownAddress != &thiz->object) return false;
  //The instance should have reflection signature. Check the name of the reflection instance instead its pointer
  //to support multiple linking processes. (Simulink-mex-dll)
  if(strcmp(thiz->object.reflectionClass->name, "DataNode_Inspc") !=0) return false;
  return true;
}
