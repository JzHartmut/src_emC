#include "FBaccess_Inspc_priv.h"
#include <stdio.h>
#include <stdlib.h>


void alloc_FBaccessNode_Inspc(struct FBaccess_InspcNode_t** thizp, int nrofObjects)
{
  STACKTRC_ENTRY("alloc_FBaccessNode_Inspc");

  FBaccessNode_Inspc* thiz = (FBaccessNode_Inspc*)malloc(sizeof(FBaccessNode_Inspc));
  memset(thiz, 0, sizeof(*thiz));


  STACKTRC_LEAVE;

}

extern_C struct ClassJc_t const reflection_FBaccessNode_Inspc;

FBaccessNode_Inspc* ctor_FBaccessNode_Inspc(ObjectJc* thizo, int nrofObjects)
{
  STACKTRC_ENTRY("ctor_FBaccessNode_Inspc");
  FBaccessNode_Inspc* thiz = (FBaccessNode_Inspc*) thizo; 
  //initReflection_ObjectJc(thizo, thizo, sizeof(FBaccessNode_Inspc_t), &reflection_FBaccessNode_Inspc, 0xf0);
  //use the own saved reflection to describe this struct
  initReflection_ObjectJc(thizo, thizo, sizeof(FBaccessNode_Inspc_t), &thiz->clazz, 0xf0);

  strcpy(thiz->clazz.name, "AccessNode_Inspc");
  thiz->fields.head.sizeElement = sizeof(void*);
  thiz->clazz.attributes = &thiz->fields;
  STACKTRC_LEAVE;
  return thiz;

}

void free_FBaccessNode_Inspc(FBaccessNode_Inspc* thiz)
{

  free(thiz);
}






void registerRefl_FBaccessNode_Inspc(struct FBaccessNode_Inspc_t* thiz, void* obj, char const* name, struct ClassJc_t const* refl){
 
  int ix = thiz->fields.head.length;
  thiz->data[ix] = obj;
  strncpy(thiz->fields.data[ix].name, name, sizeof(thiz->fields.data[ix].name));
  thiz->fields.data[ix].type_ = refl;
  thiz->fields.data[ix].bitModifiers = kReference_Modifier_reflectJc;
  thiz->fields.data[ix].position = ((MemUnit*)&thiz->data[ix]) - ((MemUnit*)thiz);

  thiz->fields.head.length = ix + 1;
}
