#include "Inspc/GetValue_Inspc.h"
#include <InspcJ2c/SearchElement_Inspc.h>
#include <Inspc/DataNode_Inspc.h>
#include <Jc/ReflectionJc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <emC/SimpleC_emC.h>

void ctor_GetValue_Inspc(GetValue_Inspc* thiz, float Tstep)
{
  initReflection_ObjectJc(&thiz->object, thiz, sizeof(GetValue_Inspc), null, 0x0);
  memset(thiz->addr, 0, sizeof(thiz->addr));
}


void init_GetValue_Inspc(GetValue_Inspc* thiz 
  , StringJc path1_param, StringJc path2_param, StringJc path3_param, StringJc path4_param
  , StringJc path5_param, StringJc path6_param
  , DataNode_Inspc* inspcNode, int32 ok)
{
  //FieldJc field;
  FieldJc const* field;
  MemSegmJc mem;
  int32 ixPath = 0;
  STACKTRC_ENTRY("init_GetValue_Inspc");
  if(inspcNode !=null && ok) {
    //don't save, use only.
    setInitialized_ObjectJc(&thiz->object);
    thiz->statusNotFound = 0;
    StringJc path[6];
    path[0] = path1_param;
    path[1] = path2_param;
    path[2] = path3_param;
    path[3] = path4_param;
    path[4] = path5_param;
    path[5] = path6_param;
    for(ixPath=0; ixPath < ARRAYLEN_SimpleC(thiz->addr); ++ixPath) {
      int32 ixField = 0;
      TRY {
        field = null;
        mem = searchObject_SearchElement_Inspc(path[ixPath], &inspcNode->object, &field, &ixField, _thCxt); 
      } _TRY
      CATCH( Exception, exc) {
        field = null;
      } END_TRY;
      if(field !=null) {
        void* addr = getMemoryIdent_FieldJc(field, mem, "I", ixField);
        
        ClassJc const* fieldType = getType_FieldJc(field);
      
        if(fieldType == &reflection__floatJc) {
          thiz->addr[ixPath] = (int32*)addr;
        }
      } else {
        thiz->addr[ixPath] = null;
        thiz->statusNotFound |= 1<<ixPath;
      }
    } 
  }
  STACKTRC_LEAVE;
}



void get_GetValue_Inspc(GetValue_Inspc* thiz
  , float* val1_y, float* val2_y, float* val3_y, float* val4_y, float* val5_y, float* val6_y
  , int32* statusNotFound_y) {
  int ix;
  float val[6];
  for(ix=0; ix < ARRAYLEN_SimpleC(val); ++ix) {
    if(thiz->addr[ix]) { 
      val[ix] = *(float*)thiz->addr[ix];
    }
  }
  *val1_y = val[0];
  *val2_y = val[1];
  *val3_y = val[2];
  *val4_y = val[3];
  *val5_y = val[4];
  *val6_y = val[5];
  *statusNotFound_y = thiz->statusNotFound;
}

