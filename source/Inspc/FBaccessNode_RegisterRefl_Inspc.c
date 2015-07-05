#include "FBaccess_Inspc_priv.h"



void registerRefl_FBaccessNode_Inspc(struct FBaccessNode_Inspc_t* thiz, void* obj, char const* name, struct ClassJc_t const* refl){
 
  int ix = thiz->fields.head.length;
  thiz->data[ix] = obj;
  strncpy(thiz->fields.data[ix].name, name, sizeof(thiz->fields.data[ix].name));
  thiz->fields.data[ix].type_ = refl;
  thiz->fields.data[ix].bitModifiers = kReference_Modifier_reflectJc;
  thiz->fields.data[ix].position = ((MemUnit*)&thiz->data[ix]) - ((MemUnit*)thiz);

  thiz->fields.head.length = ix + 1;
}
