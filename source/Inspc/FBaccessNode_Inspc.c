#include "FBaccess_Inspc_priv.h"
#include <stdio.h>
#include <stdlib.h>


void alloc_FBaccessNode_Inspc(DataNode_Inspc** thizp, int nrofObjects)
{
  STACKTRC_ENTRY("alloc_FBaccessNode_Inspc");

  DataNode_Inspc* thiz = (DataNode_Inspc*)malloc(sizeof(DataNode_Inspc));
  memset(thiz, 0, sizeof(*thiz));


  STACKTRC_LEAVE;

}


DataNode_Inspc* ctor_DataNode_Inspc(DataNode_Inspc* thiz, int nrofObjects)
{
  STACKTRC_ENTRY("ctor_DataNode_Inspc");
  //DataNode_Inspc* thiz = (DataNode_Inspc*) thizo; 
  strcpy(thiz->clazz.name, "DataNode_Inspc");
  initReflection_ObjectJc(&thiz->object, thiz, sizeof(DataNode_Inspc), &thiz->clazz, 0xf0);

  thiz->fields.head.sizeElement = sizeof(void*);
  thiz->clazz.attributes = &thiz->fields;
  setInitialized_ObjectJc(&thiz->object);
  STACKTRC_LEAVE;
  return thiz;

}

void free_FBaccessNode_Inspc(DataNode_Inspc* thiz)
{

  free(thiz);
}






