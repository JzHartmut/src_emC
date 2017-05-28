/**This file is the only one which should be added to a simulink-mex library to register a S-function for reflection.
 * The whole inspector binaries are not necessary therefore. They should not need in a extra binary image.
 */
#include "FBaccess_Inspc_priv.h"



bool registerRefl_FBaccessNode_Inspc(struct FBaccessNode_Inspc_t* thiz, void* obj, char const* name, struct ClassJc_t const* refl){
  if(!checkObject_FBaccessNode_Inspc(thiz)) return false;
  int ix = thiz->fields.head.length;  //the current length
  if(ix < ARRAYLEN_SimpleC(thiz->data)) {
    thiz->data[ix] = obj;
    strncpy(thiz->fields.data[ix].name, name, sizeof(thiz->fields.data[ix].name));
    thiz->fields.data[ix].type_ = refl;
    thiz->fields.data[ix].bitModifiers = kReference_Modifier_reflectJc;
    thiz->fields.data[ix].position = ((MemUnit*)&thiz->data[ix]) - ((MemUnit*)thiz);

    thiz->fields.head.length = ix + 1;
    return true;
  }
  else return false;
}



char const* registerNode_AccessNode_Inspc(FBaccessNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, void* data)
{ const char* error = null;
  int ix, ix1;
  struct ObjectJc_t* oData = (struct ObjectJc_t*) data;
  if(!checkObject_FBaccessNode_Inspc(thiz)) return "input 1 is not a FBaccessNode_Inspc";
  if(data == null || oData->ownAddress != data || oData->reflectionClass == null) {
    return "input 2: data is not based on ObjectJc, or it has not reflection information.";
  }
  ix = thiz->fields.head.length;  //the current length
  //check whether it is registered already. This routine may be called twice:
  for(ix1 = 0; ix1 < ix; ++ix1) {
    if(thiz->data[ix1] == oData) { 
      break;
    }
  } 
  if(ix1 == ix) { //onyl if not found, all checked:
    if(ix >= ARRAYLEN_SimpleC(thiz->data)) {
      return "too much registration in registerNode_AccessNode_Inspc(...)";
    }
    thiz->data[ix] = oData;
    { int nchars = copyToBuffer_StringJc(name1_param, 0, -1, thiz->fields.data[ix].name, sizeof(thiz->fields.data[ix].name));
      copyToBuffer_StringJc(name2_param, 0, -1, thiz->fields.data[ix].name+nchars, sizeof(thiz->fields.data[ix].name)-nchars); //the rest.
    }
    //strncpy(thiz->fields.data[ix].name, name, sizeof(thiz->fields.data[ix].name));  //TODO check length of name!!!
    thiz->fields.data[ix].type_ = oData->reflectionClass;
    thiz->fields.data[ix].bitModifiers = kReference_Modifier_reflectJc;
    thiz->fields.data[ix].position = ((MemUnit*)&thiz->data[ix]) - ((MemUnit*)thiz);

    thiz->fields.head.length = ix + 1;
  }
  return null; //successfull
}

bool checkObject_FBaccessNode_Inspc(struct FBaccessNode_Inspc_t* thiz){
  if(thiz == null) return false;
  if(thiz->object.ownAddress != &thiz->object) return false;
  //The instance should have reflection signature. Check the name of the reflection instance instead its pointer
  //to support multiple linking processes. (Simulink-mex-dll)
  if(strcmp(thiz->object.reflectionClass->name, "FBaccessNode_Inspc") !=0) return false;
  return true;
}
