#include "InputValues_Inspc.h"
#include <Inspc/FBaccess_Inspc.h>
#include <Jc/FileIoJc.h>
#include <Jc/StringJc.h>
#include <J1c/StringFunctionsJc.h>
#include <stdlib.h>
#include <string.h>

#include "InputValues_Inspc_Refl.crefl"

InputValues_Inspc* create_InputValues_Inspc()
{ InputValues_Inspc* thiz = null;
  thiz = (InputValues_Inspc*)malloc(sizeof(InputValues_Inspc));
  if(thiz !=null) {
    memset(thiz, 0, sizeof(InputValues_Inspc));
  }
  return thiz;
}



void ctor_InputValues_Inspc(InputValues_Inspc* thiz)
{
  strncpy(thiz->clazz.name, "InputValues_Inspc", sizeof(thiz->clazz.name));
  //thiz->fields.head.
  thiz->clazz.nSize = sizeof(*thiz);
  thiz->clazz.attributes = &thiz->fields;
  int ix;
  int nrofFields = 0;
  for(ix = 0; ix < ARRAYLEN_SimpleC(thiz->names); ++ix) {
    char const* name;
    if(thiz->names[ix][0] == 0){
      name =  "?";  //unused field
    } else {
      name = thiz->names[ix];
      nrofFields = ix;  //set lastly with the highest number of active field.
    }
    FieldJc* field = &thiz->fields.data[ix];
    field->type_ = REFLECTION_float;
    field->position = offset_MemAreaC(thiz, &thiz->x[ix]);
    strncpy(field->name, name, sizeof(field->name)-1);
  }
  FieldJc* field = &thiz->fields.data[++nrofFields];
  field->type_ = &reflection_InputValues_Inspc;  
  field->position = 0;
  strncpy(field->name, "thiz$InputValues_Inspc", sizeof(field->name)-1);
  thiz->fields.head.length = nrofFields +1;
}



bool registerReflection_InputValues_Inspc(InputValues_Inspc* thiz, struct FBaccessNode_Inspc_t* reflNode)
{ return registerRefl_FBaccessNode_Inspc(reflNode, thiz, thiz->nameRefl, &thiz->clazz);
}









void free_InputValues_Inspc(InputValues_Inspc* thiz)
{
  if(thiz !=null){
    free(thiz);
  }
}



void test_InputValues_Inspc(struct FBaccessNode_Inspc_t* reflNode)
{

  static InputValues_Inspc* test = create_InputValues_Inspc();
  //strncpy(test->channels, "cUAN_on_CCP cOn_CBB_CCP", sizeof(test->channels));
  strncpy(test->nameRefl,"test_TimeSignals", sizeof(test->nameRefl));
  strncpy(test->names[0], "param1", sizeof(test->names[0]));
  strncpy(test->names[1], "cCmdA", sizeof(test->names[0]));
  strncpy(test->names[2], "wUm", sizeof(test->names[0]));
  strncpy(test->names[3], "wUw", sizeof(test->names[0]));
  ctor_InputValues_Inspc(test);
  
  registerReflection_InputValues_Inspc(test, reflNode);
  
  free_InputValues_Inspc(test);
}

