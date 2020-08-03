/**This file is the only one which should be added to a simulink-mex library to register a S-function for reflection.
 * The whole inspector binaries are not necessary therefore. They should not need in a extra binary image.
 */
#include <emC/Inspc/Srv/DataNode_Inspc.h>
#include <emC/Inspc/Srv/CheckPwd_Inspc.h>

#include <string.h>
#include <emC/base/String_emC.h>

#include "genRefl/DataNode_Inspc.crefl"


DataNode_Inspc* ctor_DataNode_Inspc(DataNode_Inspc* thiz, int nrofObjects, float Tstep)
{ //Tstep is only dummy, for simulink.
  STACKTRC_ENTRY("ctor_DataNode_Inspc");
  //DataNode_Inspc* thiz = (DataNode_Inspc*) thizo; 
  //strcpy_emC(thiz->clazz.name, "DataNode_Inspc", -(int)sizeof(thiz->clazz.name));
  //fill the local given superclass and class data.
  init_immediate_ObjectArrayJc(&thiz->superclass.head, 1, sizeof(thiz->superclass.clazz)
        , &refl_ClassOffset_idxVtblJc, ID_refl_ClassOffset_idxVtblJc | mArrayId_ObjectJc);
  ctor_ClassOffset_idxVtblJc(&thiz->superclass.clazz, &refl_ObjectJc, kDevlpAccess_CheckPwd_Inspc, 0);
  ctor_Fields_super_ClassJc(&thiz->clazz, z_StringJc("DataNode_Inspc"), sizeof(*thiz), &thiz->fields.head, &thiz->superclass.head);
  iniz_ObjectJc(&thiz->base.object, thiz, sizeof(DataNode_Inspc), &thiz->clazz, 0xf0);

  //thiz->fields.head.sizeElement = sizeof(void*);
  //thiz->clazz.attributes = &thiz->fields;
  setInitialized_ObjectJc(&thiz->base.object);
  STACKTRC_LEAVE;
  return thiz;

}


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
      strcpy_emC(thiz->fields.data[ix].name, name, -(int)sizeof(thiz->fields.data[ix].name));
      thiz->fields.data[ix].type_ = refl;
      thiz->fields.data[ix].bitModifiers = kReference_Modifier_reflectJc;
      thiz->fields.data[ix].offsFieldInStruct = ((MemUnit*)&thiz->data[ix]) - ((MemUnit*)thiz);

      thiz->fields.head.length = ix + 1;
      return true;
    }
  }
  return false;
}



void XXXadd_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, void const* data, int32* ok_y)
{
  addObj_DataNode_Inspc(thiz, name1_param, name2_param, (struct ObjectJc_t*) data, ok_y); 
}

void addObj_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, ObjectJc* obj, int32* ok_y)
{ STACKTRC_ENTRY("addObj_DataNode_Inspc")
  if((ok_y == null || *ok_y == 0) && obj !=null) {
    const char* error = null;
    if(!checkObject_DataNode_Inspc(thiz)) { 
      THROW_s0(IllegalArgumentException, "input 1 is not a DataNode_Inspc",0,0);
      STACKTRC_RETURN;
    }
    if(obj->reflection == null) {
      THROW_s0( IllegalArgumentException, "input 3: obj may not based on ObjectJc, it has not reflection information.", 0, 0);
      STACKTRC_RETURN;
    }
    #ifdef DEF_ObjectJc_OWNADDRESS
    if(obj->ownAddress != obj) {
      THROW_s0( IllegalArgumentException, "input 3: obj.ownAddress is fault.", (int)(intPTR)obj->ownAddress, (int)(intPTR)obj);
      STACKTRC_RETURN;
    }
    #endif
    if(isInitialized_ObjectJc(&thiz->base.object)) {
      if(ok_y){ *ok_y = 1; }
      addObjRefl_DataNode_Inspc(thiz, name1_param, name2_param, obj, obj->reflection);
    } 
  }   
  STACKTRC_RETURN;
}




void addObjRefl_DataNode_Inspc(DataNode_Inspc* thiz, StringJc name1_param, StringJc name2_param, void* obj, ClassJc const* reflectionClass)
{ int ix, ix1;
  STACKTRC_ENTRY("addObjRefl_DataNode_Inspc");
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
      THROW_s0(IllegalArgumentException, "too much registration in registerNode_AccessNode_Inspc(...)",0,0);
      STACKTRC_RETURN;
    }
    thiz->data[ix] = obj;
    { int nchars = copyToBuffer_StringJc(name1_param, 0, -1, thiz->fields.data[ix].name, sizeof(thiz->fields.data[ix].name));
      copyToBuffer_StringJc(name2_param, 0, -1, thiz->fields.data[ix].name+nchars, sizeof(thiz->fields.data[ix].name)-nchars); //the rest.
    }
    thiz->fields.data[ix].type_ = reflectionClass;
    thiz->fields.data[ix].bitModifiers = kReference_Modifier_reflectJc;
    thiz->fields.data[ix].offsFieldInStruct = ((MemUnit*)&thiz->data[ix]) - ((MemUnit*)thiz);

    thiz->fields.head.length = ix + 1;
  }
  STACKTRC_RETURN;
}



bool checkObject_DataNode_Inspc(struct DataNode_Inspc_t* thiz){
  if(thiz == null) return false;
  #ifdef DEF_ObjectJc_OWNADDRESS
  if(thiz->base.object.ownAddress != &thiz->base.object) return false;
  #endif
  //The instance should have reflection signature. Check the name of the reflection instance instead its pointer
  //to support multiple linking processes. (Simulink-mex-dll)
  if(strcmp(thiz->base.object.reflection->name, "DataNode_Inspc") !=0) return false;
  return true;
}
