/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 */

#include <applstdef_emC.h>
#ifdef DEF_REFLECTION_FULL  //only possible with reflection because Vtable is need

#include <emC/Jc/ReflectionJc.h>
#include <emC/Jc/ObjectJc.h>





extern_C const ClassJc refl_int8ARRAY;  //the just defined refl_
extern_C const ClassJc refl_ObjectArrayJc;
const struct Reflection_Fields_int8ARRAY_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_int8ARRAY =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_int8ARRAY)
, {
    { "head"
    , 0   //no Array, no Bitfield
    , &refl_ObjectArrayJc
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((int8_ObjArray*)(0x1000))->head) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_int8ARRAY
    }
  , { "data"
    , 256   //nrofArrayElements
    , &refl__int16Jc
    //, REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((int8_ObjArray*)(0x1000))->data) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_int8ARRAY
    }
} };


const ClassJc refl_int8ARRAY =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_int8ARRAY, &refl_ClassJc)
, "int8_ObjArray"
, 0
, sizeof(int8_ObjArray)
, (FieldJcArray const*)&refl_Fields_int8ARRAY  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};








#ifdef DEF_ClassJc_Vtbl

extern_C const ClassJc refl_ComparableJc;  //the just defined refl_
extern_C const ClassJc refl_ObjectJc;
const struct Reflection_Fields_ComparableJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} refl_Fields_ComparableJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_ComparableJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJc
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((ComparableJc*)(0x1000))->base.object) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ComparableJc
    }
} };


const ClassJc refl_ComparableJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ComparableJc, &refl_ClassJc)
, "ComparableJc"
, 0
, sizeof(ComparableJc)
, (FieldJcArray const*)&refl_Fields_ComparableJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc refl_AppendableJc;  //the just defined refl_
extern_C const ClassJc refl_ObjectJc;
const struct Reflection_Fields_AppendableJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} refl_Fields_AppendableJc_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_ComparableJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJc
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((AppendableJc_s*)(0x1000))->base.object) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_AppendableJc
    }
} };


const ClassJc refl_AppendableJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_AppendableJc, &refl_ClassJc)
, "AppendableJc_s"
, 0
, sizeof(AppendableJc_s)
, (FieldJcArray const*)&refl_Fields_AppendableJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc refl_CloseableJc;  //the just defined refl_
extern_C const ClassJc refl_ObjectJc;
const struct Reflection_Fields_CloseableJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} refl_Fields_CloseableJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_CloseableJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJc
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((CloseableJc*)(0x1000))->base.object) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_CloseableJc
    }
} };


const ClassJc refl_CloseableJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_CloseableJc, &refl_ClassJc)
, "CloseableJc"
, 0
, sizeof(CloseableJc)
, (FieldJcArray const*)&refl_Fields_CloseableJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



extern_C const ClassJc refl_FlushableJc;  //the just defined refl_
extern_C const ClassJc refl_ObjectJc;
const struct Reflection_Fields_FlushableJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} refl_Fields_FlushableJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_CloseableJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJc
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((FlushableJc*)(0x1000))->base.object) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_FlushableJc
    }
} };


const ClassJc refl_FlushableJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_FlushableJc, &refl_ClassJc)
, "FlushableJc"
, 0
, sizeof(FlushableJc)
, (FieldJcArray const*)&refl_Fields_FlushableJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


#endif //def DEF_ClassJc_Vtbl




#if 0
#include "emC/Jc/ReflectionJc.h"


extern_C const ClassJc refl_FieldJc;  //the just defined refl_
extern_C const ClassJc refl_ClassJc;
extern_C const ClassJc refl_ClassJc;
const struct Reflection_Fields_FieldJc_t
{ ObjectArrayJc head;
  FieldJc data[7];
} refl_Fields_FieldJc =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &refl_Fields_FieldJc)
, {
    { "name"
    , 30   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((FieldJc*)(0x1000))->name) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_FieldJc
    }
  , { "nrofArrayElementsOrBitfield_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((FieldJc*)(0x1000))->nrofArrayElementsOrBitfield_) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_FieldJc
    }
  , { "type_"
    , 0   //no Array, no Bitfield
    , &refl_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((FieldJc*)(0x1000))->type_) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_FieldJc
    }
  , { "bitModifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((FieldJc*)(0x1000))->bitModifiers) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_FieldJc
    }
  , { "position"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((FieldJc*)(0x1000))->offsFieldInStruct) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_FieldJc
    }
  , { "offsetToObjectifcBase"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((FieldJc*)(0x1000))->offsetToObjectifcBase) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_FieldJc
    }
  , { "declaringClass"
    , 0   //no Array, no Bitfield
    , &refl_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((FieldJc*)(0x1000))->declaringClass) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_FieldJc
    }
} };


const ClassJc refl_FieldJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_FieldJc, &refl_ClassJc)
, "FieldJc"
, 0
, sizeof(FieldJc)
, (FieldJcArray const*)&refl_Fields_FieldJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};
#endif //0

#if 0 //TODO

extern_C const ClassJc refl_MethodJc;  //the just defined refl_
const struct Reflection_Fields_MethodJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} refl_Fields_MethodJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &refl_Fields_MethodJc)
, {
    { "name"
    , 32   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((MethodJc*)(0x1000))->name) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_MethodJc
    }
  , { "bModifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((MethodJc*)(0x1000))->bModifiers) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_MethodJc
    }
  , { "adress"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((MethodJc*)(0x1000))->adress) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_MethodJc
    }
  , { "eType"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((MethodJc*)(0x1000))->eType) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_MethodJc
    }
} };


const ClassJc refl_MethodJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_MethodJc, &refl_ClassJc)
, "MethodJc"
, 0
, sizeof(MethodJc)
, (FieldJcArray const*)&refl_Fields_MethodJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};

#endif
/*

extern_C const ClassJc refl_ClassJc;  //the just defined refl_
extern_C const ClassJc refl_ObjectJc;
extern_C const ClassJc refl_VtblHeadJc;
const struct Reflection_Fields_ClassJc_t
{ ObjectArrayJc head;
  FieldJc data[10];
} refl_Fields_ClassJc =
{ CONST_ObjectArrayJc(FieldJc, 10, OBJTYPE_FieldJc, null, &refl_Fields_ClassJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJc
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->object) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "name"
    , 32   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->name) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "posObjectBase"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->posObjectBase) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "nSize"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->nSize) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "attributes"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->attributes) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "methods"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->methods) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "superClasses"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->superClasses) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "interfaces"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->interfaces) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "modifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->modifiers) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
  , { "mtbl"
    , 0   //no Array, no Bitfield
    , &refl_VtblHeadJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ClassJc*)(0x1000))->mtbl) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ClassJc
    }
} };


const ClassJc refl_ClassJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ClassJc, &refl_ClassJc)
, "ClassJc"
, 0
, sizeof(ClassJc)
, (FieldJcArray const*)&refl_Fields_ClassJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


*/




extern_C const ClassJc refl_ExtReflectionJc;  //the just defined refl_
extern_C const ClassJc refl_OS_PtrValue;
extern_C const ClassJc refl_Data_ExtReflectionJc;
extern_C const ClassJc refl_ClassJc;
const struct Reflection_Fields_ExtReflectionJc
{ ObjectArrayJc head;
  FieldJc data[5];
} refl_Fields_ExtReflectionJc =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &refl_Fields_ExtReflectionJc)
, {
    { "ct"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ExtReflectionJc_s*)(0x1000))->ct) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ExtReflectionJc
    }
  , { "errorRelocationExtRefl"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ExtReflectionJc_s*)(0x1000))->errorRelocationExtRefl) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ExtReflectionJc
    }
  , { "extReflectionBuffer"
    , 0   //no Array, no Bitfield
    , &refl_OS_PtrValue
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((ExtReflectionJc_s*)(0x1000))->extReflectionBuffer) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ExtReflectionJc
    }
  , { "extReflectionData"
    , 0   //no Array, no Bitfield
    , &refl_Data_ExtReflectionJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ExtReflectionJc_s*)(0x1000))->extReflectionData) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ExtReflectionJc
    }
  , { "extReflection"
    , 0   //no Array, no Bitfield
    , &refl_ClassJc
    , 0| kObjectArrayJc_Modifier_reflectJc| kReferencedContainer_Modifier_reflectJc| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ExtReflectionJc_s*)(0x1000))->extReflection) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ExtReflectionJc
    }
} };


const ClassJc refl_ExtReflectionJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ExtReflectionJc, &refl_ClassJc)
, "ExtReflectionJc"
, 0
, sizeof(ExtReflectionJc_s)
, (FieldJcArray const*)&refl_Fields_ExtReflectionJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc refl_Data_ExtReflectionJc;  //the just defined refl_
extern_C const ClassJc refl_ObjectJc;
extern_C const ClassJc refl_ClassJc;
extern_C const ClassJc refl_ClassJc;
const struct Reflection_Fields_Data_ExtReflectionJc_t
{ ObjectArrayJc head;
  FieldJc data[6];
} refl_Fields_Data_ExtReflectionJc =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &refl_Fields_Data_ExtReflectionJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJc
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((Data_ExtReflectionJc*)(0x1000))->object) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_ExtReflectionJc
    }
  , { "sign"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((Data_ExtReflectionJc*)(0x1000))->sign) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_ExtReflectionJc
    }
  , { "nrofRelocEntries"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((Data_ExtReflectionJc*)(0x1000))->nrofRelocEntries) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_ExtReflectionJc
    }
  , { "arrayClasses"
    , 0   //no Array, no Bitfield
    , &refl_ClassJc
    , 0| kObjectArrayJc_Modifier_reflectJc| kReferencedContainer_Modifier_reflectJc| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_ExtReflectionJc*)(0x1000))->arrayClasses) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_ExtReflectionJc
    }
  , { "classDataBlock"
    , 0   //no Array, no Bitfield
    , &refl_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_ExtReflectionJc*)(0x1000))->classDataBlock) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_ExtReflectionJc
    }
  , { "relocateAddr"
    , 10   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((Data_ExtReflectionJc*)(0x1000))->relocateAddr) - 0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_Data_ExtReflectionJc
    }
} };


const ClassJc refl_Data_ExtReflectionJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_Data_ExtReflectionJc, &refl_ClassJc)
, "Data_ExtReflectionJc"
, 0
, sizeof(Data_ExtReflectionJc)
, (FieldJcArray const*)&refl_Fields_Data_ExtReflectionJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};











  //extern struct ClassJc_t const refl_int16;


  extern_C const struct ClassJc_t refl_int16_Y;
  const struct Reflection_Fields_int16_Y_t{ ObjectArrayJc head; FieldJc data[2];} refl_Fields_int16_Y =
  { CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_int16_Y)
  , { { "head", 0 , &refl_ObjectArrayJc, 0, 0, 0, &refl_int16_Y }
    , { "data", 0 , REFLECTION_int16, 0, 0, 0, &refl_int16_Y }
  } };
  const ClassJc refl_int16_Y =
  { CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_int16_Y, null)
  , "Ptr", 0, sizeof(int16_Y), (FieldJcArray const*)&refl_Fields_int16_Y
  };



//DEFINE_REFLECTION_ARRAYJc(int8);

  extern_C const struct ClassJc_t refl_int8_Y;
  const struct Reflection_Fields_int8_Y_t { ObjectArrayJc head; FieldJc data[2]; } refl_Fields_int8_Y =
  { CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_int8_Y)
    ,{ { "head", 0 , &refl_ObjectArrayJc, 0, 0, 0, &refl_int8_Y }
    ,{ "data", 0 , &refl__int8Jc, 0, 0, 0, &refl_int8_Y }
    } };
  const ClassJc refl_int8_Y =
  { CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_int8_Y, null)
    , "Ptr", 0, sizeof(int16_Y), (FieldJcArray const*)&refl_Fields_int8_Y
  };


#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

const ClassJc refl__ObjectifcBaseJcpp =
{ CONST_ObjectJc(0, &refl__ObjectifcBaseJcpp, null)
, "ObjectifcBaseJcpp"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(ObjectifcBaseJcpp)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mINTERFACE_Modifier_reflectJc
};
#endif

#if 0
const struct ReflectionFieldJc_t reflectionFieldJc
=
{ CONST_dataonly_ClassJc("[LFieldJc", FieldJc)
, { clone_Object_F
  , equals_Object_F
  , finalize_Object_F
  , hashCode_Object_F
  , toString_Object_F
  }
, { CONST_ARRAYJc(FieldJc, 2) //CONST_ObjectJc(0,0), 2, sizeof(FieldJc), 0
  , { CONST_FieldJc(FieldJc, "bitModifiers", bitModifiers, int, 0)
    , CONST_FieldJc(FieldJc, "position", position, int, 0)
    }
  }

};
#endif


//#include <Jc/LocaleJc.h>
//extern_C ClassJc const refl_LocaleJc;
//DEFINE_REFLECTION_REF(LocaleJc);

#endif //#ifdef DEF_ObjectJcpp_REFLECTION  //only possible with reflection because Vtable is need
