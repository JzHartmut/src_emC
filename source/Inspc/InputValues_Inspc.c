#include "InputValues_Inspc.h"
#include <Inspc/DataNode_Inspc.h>
#include <Jc/FileIoJc.h>
#include <Jc/StringJc.h>
#include <J1c/StringFunctionsJc.h>
#include <stdlib.h>
#include <string.h>

#include "genRefl/Inspc/InputValues_Inspc.crefl"

InputValues_Inspc* create_InputValues_Inspc()
{ InputValues_Inspc* thiz = null;
  thiz = (InputValues_Inspc*)malloc(sizeof(InputValues_Inspc));
  if(thiz !=null) {
    memset(thiz, 0, sizeof(InputValues_Inspc));
  }
  return thiz;
}



void ctorXXX_InputValues_Inspc(InputValues_Inspc* thiz)
{
  strcpy_emC(thiz->clazz.name, "InputValues_Inspc", sizeof(thiz->clazz.name));
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
    strcpy_emC(field->name, name, sizeof(field->name)-1);
  }
  FieldJc* field = &thiz->fields.data[++nrofFields];  //reference to thiz
  field->type_ = &reflection_InputValues_Inspc;  
  field->position = 0;
  strcpy_emC(field->name, "thiz$InputValues_Inspc", sizeof(field->name)-1);
  thiz->fields.head.length = nrofFields +1;  //data fields + reference to thiz
}



bool registerReflection_InputValues_Inspc(InputValues_Inspc* thiz, struct DataNode_Inspc_t* reflNode)
{ return registerRefl_DataNode_Inspc(reflNode, thiz, thiz->nameRefl, &thiz->clazz);
}



void ctor_InputValues_Inspc(InputValues_Inspc* thiz)
{
}



char const* init_InputValues_Inspc(InputValues_Inspc* thiz, struct DataNode_Inspc_t* dataNode
  , StringJc nameRefl
  , StringJc n1, StringJc n2, StringJc n3, StringJc n4, StringJc n5, StringJc n6
  , StringJc n7, StringJc n8, StringJc n9, StringJc n10, StringJc n11, StringJc n12
  , Entry_DefPortTypeJc* portTypes)
{ 
  StringJc names[12];
  names[0] = n1;   //using for(0..11)
  names[1] = n2;
  names[2] = n3;
  names[3] = n4;
  names[4] = n5;
  names[5] = n6;
  names[6] = n7;
  names[7] = n8;
  names[8] = n9;
  names[9] = n10;
  names[10] = n11;
  names[11] = n12;
  strcpy_emC(thiz->clazz.name, "InputValues_Inspc", sizeof(thiz->clazz.name));
  thiz->clazz.nSize = sizeof(*thiz);
  thiz->clazz.attributes = &thiz->fields;
  int ix;
  int ixField = 0;
  int posField = offset_MemAreaC(thiz, &thiz->val[0]);
  int posEnd = posField + sizeof(thiz->val);
  for(ix = 0; ix < ARRAYLEN_SimpleC(thiz->names); ++ix) {
    int zname; char const* name = getCharsAndLength_StringJc(&names[ix], &zname);
    if(zname == 0){
      name =  "?";  //unused field
      zname = 1;
    } else {
      ixField = ix;
    }
    FieldJc* field = &thiz->fields.data[ix];
    int nrofBytesType;
    if(name[0] == '*') {  //access to the content of a pointer.
      name += 1;  //without '*'
      zname -=1;
      field->type_ = REFLECTION_uint32;
      nrofBytesType = 4;
      field->nrofArrayElementsOrBitfield_ = 128;
      field->bitModifiers = kStaticArray_Modifier_reflectJc | kReference_Modifier_reflectJc;
    } else if(name[0] == '&') {  //access to the content of a pointer.
      name += 1;  //without '&'
      zname -=1;
      if(name[0] == '*') {
        name +=1; //without '*'
        zname -=1;
        //The difference &* vs. * is: on * in Simulink the input value is interpreted as reference. 
        //on &*: The input value is a reference, a bus. 
        //The Simulink mex routine is different how to interpret the inputs of the S-function.
        field->type_ = REFLECTION_uint32;
        nrofBytesType = 4;
        field->nrofArrayElementsOrBitfield_ = 128;
        field->bitModifiers = kStaticArray_Modifier_reflectJc | kReference_Modifier_reflectJc;
      } else {
        field->type_ = &reflection_ObjectJc;
        nrofBytesType = 4;
        field->nrofArrayElementsOrBitfield_ = 0;
        field->bitModifiers = kReference_Modifier_reflectJc;
      }
    } else {
      bool bComplex = portTypes[ix].type >= 'a';
      int cType;
      switch(portTypes[ix].type) {
        case 'D': nrofBytesType = 8; cType = kREFLECTION_double_ClassJc; break;
        case 'd': nrofBytesType = 8; cType = kREFLECTION_complexdouble_ClassJc; break;
        case 'F': nrofBytesType = 4; cType = kREFLECTION_float_ClassJc; break;
        case 'f': nrofBytesType = 4; cType = kREFLECTION_complexfloat_ClassJc; break;
        case 'I': nrofBytesType = 4; cType = kREFLECTION_int32_ClassJc; break;
        case 'i': nrofBytesType = 4; cType = kREFLECTION_int32_ClassJc; break;
        case '4': nrofBytesType = 4; cType = kREFLECTION_uint32_ClassJc; break;
        case 'S': nrofBytesType = 2; cType = kREFLECTION_int16_ClassJc; break;
        case '2': nrofBytesType = 2; cType = kREFLECTION_uint16_ClassJc; break;
        case 'B': nrofBytesType = 1; cType = kREFLECTION_int8_ClassJc; break;
        case '1': nrofBytesType = 1; cType = kREFLECTION_uint8_ClassJc; break;
        //Bus: type = 0x20
        default: cType = REFLECTION_uint32_ClassJc;
      } //switch
      if(bComplex) { nrofBytesType *=2; }
      field->type_ = ((struct ClassJc_t const*)cType); //REFLECTION_float;
      int sizeArray = portTypes[ix].sizeArray[0];
      if(sizeArray == 1 || sizeArray == 0) {
        field->nrofArrayElementsOrBitfield_ = 0;
      } else {
        field->nrofArrayElementsOrBitfield_ = sizeArray; //especially 0 for scalar.
        nrofBytesType *= sizeArray;
        field->bitModifiers = kStaticArray_Modifier_reflectJc;
      } 
    }
    if((posField + nrofBytesType)  < posEnd) {
      thiz->nrofbytesType[ix] = nrofBytesType;
      field->position = posField; //offset_MemAreaC(thiz, &thiz->val[kSizeX_InputValues_Inspc * ix]);
      nrofBytesType = (nrofBytesType + 3) & ~3;  //round up to 4-aligned
      posField += nrofBytesType;
      strcpy_emC(field->name, name, zname);
    } else {
      strcpy_emC(field->name, "?dataOverflow", sizeof(field->name));
    }
  }
  //reference to thiz
  FieldJc* field = &thiz->fields.data[++ixField];  //The next field.  
  field->type_ = &reflection_InputValues_Inspc;  
  field->position = 0;
  strcpy_emC(field->name, "thiz$InputValues_Inspc", sizeof(field->name)-1);
  thiz->fields.head.length = ixField +1;  //data fields + reference to thiz

  //register this data in the parent node:
  addObjRefl_DataNode_Inspc(dataNode, nameRefl, z_StringJc(""), thiz, &thiz->clazz);
  setInitialized_ObjectJc(&thiz->base);
  return null;
}


void step_InputValues_Inspc(InputValues_Inspc* thiz
     , void const* x1, void const* x2, void const* x3, void const* x4, void const* x5, void const* x6
     , void const* x7, void const* x8, void const* x9, void const* x10, void const* x11, void const* x12
     )
{
  int ixField = 0;
  int nrofbytesType = thiz->nrofbytesType[0];
  memcpy(&thiz->val[ixField], x1, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[1];
  memcpy(&thiz->val[ixField], x2, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[2];
  memcpy(&thiz->val[ixField], x3, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[3];
  memcpy(&thiz->val[ixField], x4, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[4];
  memcpy(&thiz->val[ixField], x5, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[5];
  memcpy(&thiz->val[ixField], x6, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[6];
  memcpy(&thiz->val[ixField], x7, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[7];
  memcpy(&thiz->val[ixField], x8, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[8];
  memcpy(&thiz->val[ixField], x9, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[9];
  memcpy(&thiz->val[ixField], x10, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[10];
  memcpy(&thiz->val[ixField], x11, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;
  //
  nrofbytesType = thiz->nrofbytesType[11];
  memcpy(&thiz->val[ixField], x12, nrofbytesType);
  ixField += (nrofbytesType + 3) >>2;

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
  strcpy_emC(test->nameRefl,"test_TimeSignals", sizeof(test->nameRefl));
  strcpy_emC(test->names[0], "param1", sizeof(test->names[0]));
  strcpy_emC(test->names[1], "cCmdA", sizeof(test->names[0]));
  strcpy_emC(test->names[2], "wUm", sizeof(test->names[0]));
  strcpy_emC(test->names[3], "wUw", sizeof(test->names[0]));
  ctorXXX_InputValues_Inspc(test);
  
  registerReflection_InputValues_Inspc(test, reflNode);
  
  free_InputValues_Inspc(test);
}

