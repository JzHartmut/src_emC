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


bool checkObject_FBaccessNode_Inspc(struct FBaccessNode_Inspc_t* thiz){
  if(thiz == null) return false;
  if(thiz->super.ownAddress != &thiz->super) return false;
  //The instance should have reflection signature. Check the name of the reflection instance instead its pointer
  //to support multiple linking processes. (Simulink-mex-dll)
  if(strcmp(thiz->super.reflectionClass->name, "AccessNode_Inspc") !=0) return false;
  return true;
}
