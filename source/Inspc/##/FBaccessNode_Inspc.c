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



void free_FBaccessNode_Inspc(DataNode_Inspc* thiz)
{

  free(thiz);
}






