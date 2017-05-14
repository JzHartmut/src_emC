#include "FBaccess_Inspc_priv.h"
#include <stdio.h>
#include <stdlib.h>


void alloc_FBaccessNode_Inspc(FBaccessNode_Inspc** thizp, int nrofObjects)
{
  STACKTRC_ENTRY("alloc_FBaccessNode_Inspc");

  FBaccessNode_Inspc* thiz = (FBaccessNode_Inspc*)malloc(sizeof(FBaccessNode_Inspc));
  memset(thiz, 0, sizeof(*thiz));


  STACKTRC_LEAVE;

}

//Note: don't use reflection here to prevent dependency to the whole inspector in an own mex64 file.
//extern_C struct ClassJc_t const reflection_FBaccessNode_Inspc;

FBaccessNode_Inspc* ctor_FBaccessNode_Inspc(ObjectJc* thizo, int nrofObjects)
{
  STACKTRC_ENTRY("ctor_FBaccessNode_Inspc");
  FBaccessNode_Inspc* thiz = (FBaccessNode_Inspc*) thizo; 
  //clazz is the container for reflections to register. This class hasn't standard reflections.
  strcpy(thiz->clazz.name, "FBaccessNode_Inspc");
  initReflection_ObjectJc(thizo, thizo, sizeof(FBaccessNode_Inspc), &thiz->clazz, 0xf0);

  thiz->fields.head.sizeElement = sizeof(void*);
  thiz->clazz.attributes = &thiz->fields;
  STACKTRC_LEAVE;
  return thiz;

}

void free_FBaccessNode_Inspc(FBaccessNode_Inspc* thiz)
{

  free(thiz);
}






