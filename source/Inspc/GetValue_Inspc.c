#include "Inspc/GetValue_Inspc.h"
#include <InspcJ2c/SearchElement_Inspc.h>
#include <Inspc/DataNode_Inspc.h>
#include <Jc/ReflectionJc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void ctor_GetValue_Inspc(GetValue_Inspc* thiz)
{
  initReflection_ObjectJc(&thiz->object, thiz, sizeof(GetValue_Inspc), null, 0x0);
  thiz->addr = null;
}


void init_GetValue_Inspc(GetValue_Inspc* thiz, StringJc path_param, DataNode_Inspc* inspcNode)
{
  //FieldJc field;
  FieldJc const* field;
  int32 ix = 0;
  STACKTRC_ENTRY("init_GetValue_Inspc");
  if(inspcNode !=null) {
    //don't save, use only.
    thiz->object.isInitialized = 1;
    thiz->path = path_param;
    MemSegmJc mem = searchObject_SearchElement_Inspc(thiz->path, &inspcNode->object, &field, &ix, _thCxt); 
    if(field !=null) {
      void* addr = getMemoryIdent_FieldJc(field, mem, "I", ix);
        
      ClassJc const* fieldType = getType_FieldJc(field);
      
      if(fieldType == &reflection__floatJc) {
        thiz->addr = (long*)addr;
      }
    } else {
      thiz->addr = null;
    }
  } 
  STACKTRC_LEAVE;
}

void get_GetValue_Inspc(GetValue_Inspc* thiz, float* value_y){
  if(thiz->addr) { 
    *value_y = *(float*)thiz->addr;
  }
}

