#include "InputValues_Inspc.h"
#include <Inspc/FBaccess_Inspc.h>
#include <Inspc/DataNode_Inspc.h>
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
    if(name[0] == '*') {  //access to the content of a pointer.
      name = name+1;  //without '*'
      field->type_ = REFLECTION_uint32;
      field->nrofArrayElementsOrBitfield_ = 128;
      field->bitModifiers = kStaticArray_Modifier_reflectJc | kReference_Modifier_reflectJc;
    } else if(name[0] == '&') {  //access to the content of a pointer.
      name += 1;  //without '&'
      if(name[0] == '*') {
        name +=1; //without '*'
        //The difference &* vs. * is: on * in Simulink the input value is interpreted as reference. 
        //on &*: The input value is a reference, a bus. 
        //The Simulink mex routine is different how to interpret the inputs of the S-function.
        field->type_ = REFLECTION_uint32;
        field->nrofArrayElementsOrBitfield_ = 128;
        field->bitModifiers = kStaticArray_Modifier_reflectJc | kReference_Modifier_reflectJc;
      } else {
        field->type_ = &reflection_ObjectJc;
        field->nrofArrayElementsOrBitfield_ = 0;
        field->bitModifiers = kReference_Modifier_reflectJc;
      }
    } else {
      //The dataType[...] should be stored before invocation of the ctor.
      field->type_ = ((struct ClassJc_t const*)thiz->dataType[ix]); //REFLECTION_float;
      if(thiz->nrofElements[ix] == 1) {
        field->nrofArrayElementsOrBitfield_ = 0;
      } else {
        field->nrofArrayElementsOrBitfield_ = thiz->nrofElements[ix];
        field->bitModifiers = kStaticArray_Modifier_reflectJc;
      } 
      /*
      if(thiz->nrofElements[ix] == 1 && thiz->dataType[ix] != 'F') {
        field->nrofArrayElementsOrBitfield_ = 0;
        field->bitModifiers = 0;
      } else if(thiz->dataType[ix] == 'F') { //Float complex
        field->nrofArrayElementsOrBitfield_ = 2 * thiz->nrofElements[ix];
        field->bitModifiers = kStaticArray_Modifier_reflectJc;
      } else {
        field->nrofArrayElementsOrBitfield_ = thiz->nrofElements[ix];
        field->bitModifiers = kStaticArray_Modifier_reflectJc;
      }
      */
    }
    field->position = offset_MemAreaC(thiz, &thiz->val[kSizeX_InputValues_Inspc * ix]);
    strncpy(field->name, name, sizeof(field->name)-1);
  }
  FieldJc* field = &thiz->fields.data[++nrofFields];  //reference to thiz
  field->type_ = &reflection_InputValues_Inspc;  
  field->position = 0;
  strncpy(field->name, "thiz$InputValues_Inspc", sizeof(field->name)-1);
  thiz->fields.head.length = nrofFields +1;  //data fields + reference to thiz
}



bool registerReflection_InputValues_Inspc(InputValues_Inspc* thiz, struct DataNode_Inspc_t* reflNode)
{ return registerRefl_DataNode_Inspc(reflNode, thiz, thiz->nameRefl, &thiz->clazz);
}









void free_InputValues_Inspc(InputValues_Inspc* thiz)
{
  if(thiz !=null){
    free(thiz);
  }
}



void test_InputValues_Inspc(struct DataNode_Inspc_t* reflNode)
{

  static InputValues_Inspc* test;
  test = create_InputValues_Inspc();
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

