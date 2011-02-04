
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "Reflection_AllJcTEST.h"
#include "Jc/ReflectionJc.h"

extern const ClassJc reflection_ClassJc;
extern const ClassJc reflection_ClassJc;
const struct Reflection_Fields_FieldJc_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_FieldJc =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_FieldJc)
, {
    { "name"
    , 30   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->name) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "nrofArrayElementsOrBitfield_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->nrofArrayElementsOrBitfield_) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "type_"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->type_) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "bitModifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->bitModifiers) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "position"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->position) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "offsetToObjectifcBase"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->offsetToObjectifcBase) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "declaringClass"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->declaringClass) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
} };


const ClassJc reflection_FieldJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FieldJc, &reflection_ClassJc)
, "FieldJc"
, 0
, sizeof(FieldJc)
, (FieldJcArray const*)&reflection_Fields_FieldJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



const struct Reflection_Fields_MethodJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_MethodJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_MethodJc)
, {
    { "name"
    , 32   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((MethodJc*)(0x1000))->name) -(int32)(MethodJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MethodJc
    }
  , { "bModifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((MethodJc*)(0x1000))->bModifiers) -(int32)(MethodJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MethodJc
    }
  , { "adress"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((MethodJc*)(0x1000))->adress) -(int32)(MethodJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MethodJc
    }
  , { "eType"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((MethodJc*)(0x1000))->eType) -(int32)(MethodJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MethodJc
    }
} };


const ClassJc reflection_MethodJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_MethodJc, &reflection_ClassJc)
, "MethodJc"
, 0
, sizeof(MethodJc)
, (FieldJcArray const*)&reflection_Fields_MethodJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



extern const ClassJc reflection_ObjectJc;
extern const ClassJc reflection_MtblHeadJc;
const struct Reflection_Fields_ClassJc_t
{ ObjectArrayJc head;
  FieldJc data[10];
} reflection_Fields_ClassJc =
{ CONST_ObjectArrayJc(FieldJc, 10, OBJTYPE_FieldJc, null, &reflection_Fields_ClassJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->object) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "name"
    , 32   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->name) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "posObjectBase"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->posObjectBase) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "nSize"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->nSize) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "attributes"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->attributes) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "methods"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->methods) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "superClasses"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->superClasses) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "interfaces"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->interfaces) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "modifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->modifiers) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "mtbl"
    , 0   //no Array, no Bitfield
    , &reflection_MtblHeadJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->mtbl) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
} };


const ClassJc reflection_ClassJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ClassJc, &reflection_ClassJc)
, "ClassJc"
, 0
, sizeof(ClassJc)
, (FieldJcArray const*)&reflection_Fields_ClassJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



extern const ClassJc reflection_ClassJc;
const struct Reflection_Fields_Reflection__ObjectJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_Reflection__ObjectJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_Reflection__ObjectJc)
, {
    { "clazz"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0 //bitModifiers
    , (int16)((int32)(&((Reflection__ObjectJc*)(0x1000))->clazz) -(int32)(Reflection__ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Reflection__ObjectJc
    }
  , { "vtbl"
    , 5   //nrofArrayElements
    , REFLECTION_void
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Reflection__ObjectJc*)(0x1000))->vtbl) -(int32)(Reflection__ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Reflection__ObjectJc
    }
} };


const ClassJc reflection_Reflection__ObjectJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Reflection__ObjectJc, &reflection_ClassJc)
, "Reflection__ObjectJc"
, 0
, sizeof(Reflection__ObjectJc)
, (FieldJcArray const*)&reflection_Fields_Reflection__ObjectJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



extern const ClassJc reflection_OS_PtrValue;
extern const ClassJc reflection_Data_ExtReflectionJc;
extern const ClassJc reflection_ClassJc;
const struct Reflection_Fields_ExtReflectionJc_s_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_ExtReflectionJc_s =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_ExtReflectionJc_s)
, {
    { "ct"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->ct) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
  , { "errorRelocationExtRefl"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->errorRelocationExtRefl) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
  , { "extReflectionBuffer"
    , 0   //no Array, no Bitfield
    , &reflection_OS_PtrValue
    , 0 //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->extReflectionBuffer) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
  , { "extReflectionData"
    , 0   //no Array, no Bitfield
    , &reflection_Data_ExtReflectionJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->extReflectionData) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
  , { "extReflection"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| kObjectArrayJc_Modifier_reflectJc| kReferencedContainer_Modifier_reflectJc| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->extReflection) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
} };


const ClassJc reflection_ExtReflectionJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ExtReflectionJc_s, &reflection_ClassJc)
, "ExtReflectionJc_s"
, 0
, sizeof(ExtReflectionJc_s)
, (FieldJcArray const*)&reflection_Fields_ExtReflectionJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



extern const ClassJc reflection_ObjectJc;
extern const ClassJc reflection_ClassJc;
extern const ClassJc reflection_ClassJc;
const struct Reflection_Fields_Data_ExtReflectionJc_t
{ ObjectArrayJc head;
  FieldJc data[6];
} reflection_Fields_Data_ExtReflectionJc =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &reflection_Fields_Data_ExtReflectionJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->object) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "sign"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->sign) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "nrofRelocEntries"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->nrofRelocEntries) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "arrayClasses"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| kObjectArrayJc_Modifier_reflectJc| kReferencedContainer_Modifier_reflectJc| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->arrayClasses) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "classDataBlock"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->classDataBlock) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "relocateAddr"
    , 10   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->relocateAddr) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
} };


const ClassJc reflection_Data_ExtReflectionJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Data_ExtReflectionJc, &reflection_ClassJc)
, "Data_ExtReflectionJc"
, 0
, sizeof(Data_ExtReflectionJc)
, (FieldJcArray const*)&reflection_Fields_Data_ExtReflectionJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


