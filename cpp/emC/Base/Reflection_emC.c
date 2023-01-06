#include <emC/Base/Object_emC.h>
#include <emC/Base/String_emC.h>


//see javaSrc_vishiaBase/org.vishia.reflect.Java2C.nrofBytesScalarTypes.
const char typeCharsScalarTypes_ClassJc[0x50] =
{ '\0', 'L', 'J', 'J', 'I', 'U', 'S', 'W', 'B', 'V', 'I', 'U' 
, 'F', 'D'  //float, double
, 'C', 'A'  //char8, char16
//0x10
, '\0', 's', 'i', 'j'
, 'f', 'd'  //float-complex, double-complex
, 'Z', 'Y'  //bool, bitfield
, 'L'  //ObjectJcpp
, 'L', 'L', 'L', 'L'
, 's', 'o', 't'  //1d: StringJc, PtrValue
};



#ifdef DEF_REFLECTION_FULL

const ClassJc* simpleTypes_ClassJc[kREFLECTION_LastConstant] =
{ null    //0x0
, &refl__voidJc  //0x1
, &refl__int64Jc          //0x2
, &refl__uint64Jc         //0x3
, &refl__int32Jc          //0x4
, &refl__uint32Jc         //0x5
, &refl__int16Jc          //0x6
, &refl__uint16Jc         //0x7
, &refl__int8Jc           //0x8
, &refl__uint8Jc          //0x9
, &refl__intJc            //0xa
, &refl__uintJc           //0xb
, &refl__floatJc          //0xc
, &refl__doubleJc         //0xd
, &refl__charJc           //0xe
, &refl__char16Jc         //0xf
, null                          //0x10
, null  //0x11  reserve short-complex
, null  //0x12  int-complex
, null  //0x13  long-complex
, &refl_float_complex    //0x14
, &refl_double_complex  //0x15
, &refl__boolJc           //0x16
, &refl_bitfieldJc      //0x17
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
, &refl__ObjectifcBaseJcpp  //0x18
#else
, null
#endif
, &refl_ObjectJc  //0x19
, &refl_ObjectJc  //0x1a
, &refl__ObjectArrayJc  //0x1b
, null  //0x1c   //reserviert evtl Object_ArrayJcpp
, &refl_StringJc  //0x1d
, &refl_OS_PtrValue  //0x1e
, null  //0x1f
, &refl_ClassJc  //0x20
, null  //0x21
, null  //0x22
, null  //0x23
, null  //0x24
, null  //0x25
, null  //0x26
, null  //0x27
, null  //0x28
, null  //0x29
, null  //0x2a
, null  //0x2b
, null  //0x2c
, null  //0x2d
, null  //0x2e
, null  //0x2f
, null  //0x30
, null  //0x31
, null  //0x32
, null  //0x33
, null  //0x34
, null  //0x35
, null  //0x36
, null  //0x37
, null  //0x38
, null  //0x39
, null  //0x3a
, null  //0x3b
, null  //0x3c
, null  //0x3d
, null  //0x3e
, null  //0x3f
, null  //0x40
, &refl_ObjectJc             //0x41
, &refl_ObjectJc        //0x42
, null             //0x43
, null //&refl__ObjectRefValuesJc"    //0x44
, &refl_ClassJc              //0x45
, null  //0x46
, null  //0x47
, null  //0x48
, null  //0x49
, null  //0x4a
, null  //0x4b
, null  //0x4c
, null  //0x4d
, null  //0x4e
, null  //0x4f
};

//see javaSrc_vishiaBase/org.vishia.reflect.Java2C.nrofBytesScalarTypes.
const int nrofBytesScalarTypes_ClassJc[] =
{ 0, 0, 8, 8, 4, 4, 2, 2, 1, 1, 4, 4
, 4, 8  //float, double
, 1, 2  //char8, char16
, 8     //StringJc?
, 0,0,0,0,0  //0x11..0x15
, 1     //boolean represented with 1 byte
, 4     //bitfield supplied with 4 bytes
,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 
};







ClassJc const* really_ClassJc ( ClassJc const* thiz) {
  ClassJc const* thizReally;
  if (((intptr_t)(thiz)) < kREFLECTION_LastConstant)
  {
    thizReally = simpleTypes_ClassJc[(int)(intptr_t)(thiz)];
  }
  else { thizReally = thiz; }
  //maybe check siginificance of thizReally:
  return thizReally;
}





const FieldJc* getDeclaredField_ClassJc ( ClassJc const* thiz, StringJc sName)
{ int ii;
  bool bFound = false;
  const FieldJc* field = null;
  STACKTRC_ENTRY("getDeclaredField_ClassJc");
  //for(ii=0; !bFound && ii< thiz->attributes->array.length; ii++)
  if(thiz->attributes != null)
  { for(ii=0; !bFound && ii< thiz->attributes->head.length; ii++)
    { //StringJcRef sNameField;
      const char* sNameField;
      //field = get_FieldJc_Y(thiz->attributes,ii);
      field = &thiz->attributes->data[ii];
      sNameField = getName_FieldJc(field);
      //if(equals_StringJc(&sNameField,sName_ROOT))
      if(equals_z_StringJc(sName, sNameField))
      { bFound= true;
      }
    }
  }
  if(!bFound)  //also if attributes == null
  { //THROW_s(NoSuchFieldException, *sName,0); 
    field = null;
  }
  STACKTRC_LEAVE;
  return field;
}



/**Implementation hint: It is possible, that the type indent is a simple integer number,
   than return the correct representation!
 */
ClassJc const* getType_FieldJc ( FieldJc const* thiz)
{ ClassJc const* type = thiz->type_;
  if( ((intptr_t)(type)) < kREFLECTION_LastConstant )
  { type = simpleTypes_ClassJc[(int)(intptr_t)(type)];
  }
  return type;
}

char typeChar_FieldJc ( FieldJc const* thiz){
  if( ((intptr_t)(thiz->type_)) < kREFLECTION_LastConstant )
  { return typeCharsScalarTypes_ClassJc[(int)(intptr_t)(thiz->type_)];
  }
  else return 'L';
}


#endif //not DEF_REFLECTION_NO


