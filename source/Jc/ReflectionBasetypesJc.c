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
#include <os_types_def.h>
#include "Jc/ReflectionJc.h"



#include "Fwc/objectBaseC.h"


extern_C const ClassJc reflection_ObjectJc;  //the just defined reflection_
extern_C const ClassJc reflection_ClassJc;
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_ObjectJc_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_ObjectJc =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_ObjectJc)
, {
    { "objectIdentSize"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->objectIdentSize) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "ownAddress"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->ownAddress) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "offsetToStartAddr"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->offsetToStartAddr) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "idSyncHandles"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->idSyncHandles) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "reflectionClass"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->reflectionClass) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "memoryMng"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->memoryMng) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "dummy"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->dummy) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
} };


const ClassJc reflection_ObjectJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc)
, "ObjectJc"
, 0
, sizeof(ObjectJc)
, (FieldJcArray const*)&reflection_Fields_ObjectJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_MtblHeadJc;  //the just defined reflection_
const struct Reflection_Fields_MtblHeadJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_MtblHeadJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_MtblHeadJc)
, {
    { "sign"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((MtblHeadJc*)(0x1000))->sign) -(int32)(MtblHeadJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MtblHeadJc
    }
  , { "sizeTable"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((MtblHeadJc*)(0x1000))->sizeTable) -(int32)(MtblHeadJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MtblHeadJc
    }
} };


const ClassJc reflection_MtblHeadJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_MtblHeadJc, &reflection_ClassJc)
, "MtblHeadJc"
, 0
, sizeof(MtblHeadJc)
, (FieldJcArray const*)&reflection_Fields_MtblHeadJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




#include "Jc/ObjectJc.h"


extern_C const ClassJc reflection_ObjectArrayJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_ObjectArrayJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_ObjectArrayJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_ObjectArrayJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ObjectArrayJc*)(0x1000))->object) -(int32)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectArrayJc
    }
  , { "sizeElement"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectArrayJc*)(0x1000))->sizeElement) -(int32)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectArrayJc
    }
  , { "mode"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectArrayJc*)(0x1000))->mode) -(int32)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectArrayJc
    }
  , { "length"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectArrayJc*)(0x1000))->length) -(int32)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectArrayJc
    }
} };


const ClassJc reflection_ObjectArrayJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectArrayJc, &reflection_ClassJc)
, "ObjectArrayJc"
, 0
, sizeof(ObjectArrayJc)
, (FieldJcArray const*)&reflection_Fields_ObjectArrayJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_int8ARRAY;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectArrayJc;
const struct Reflection_Fields_int8ARRAY_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_int8ARRAY =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_int8ARRAY)
, {
    { "head"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectArrayJc
    , 0 //bitModifiers
    , (int16)((int32)(&((int8ARRAY*)(0x1000))->head) -(int32)(int8ARRAY*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_int8ARRAY
    }
  , { "data"
    , 256   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((int8ARRAY*)(0x1000))->data) -(int32)(int8ARRAY*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_int8ARRAY
    }
} };


const ClassJc reflection_int8ARRAY =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_int8ARRAY, &reflection_ClassJc)
, "int8ARRAY"
, 0
, sizeof(int8ARRAY)
, (FieldJcArray const*)&reflection_Fields_int8ARRAY  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ComparableJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_ComparableJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_ComparableJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_ComparableJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ComparableJc*)(0x1000))->object) -(int32)(ComparableJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ComparableJc
    }
} };


const ClassJc reflection_ComparableJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ComparableJc, &reflection_ClassJc)
, "ComparableJc"
, 0
, sizeof(ComparableJc)
, (FieldJcArray const*)&reflection_Fields_ComparableJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_CloseableJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_CloseableJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_CloseableJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_CloseableJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((CloseableJc*)(0x1000))->object) -(int32)(CloseableJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_CloseableJc
    }
} };


const ClassJc reflection_CloseableJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_CloseableJc, &reflection_ClassJc)
, "CloseableJc"
, 0
, sizeof(CloseableJc)
, (FieldJcArray const*)&reflection_Fields_CloseableJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};





#include "Jc/ReflectionJc.h"


extern_C const ClassJc reflection_FieldJc;  //the just defined reflection_
extern_C const ClassJc reflection_ClassJc;
extern_C const ClassJc reflection_ClassJc;
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




extern_C const ClassJc reflection_MethodJc;  //the just defined reflection_
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




extern_C const ClassJc reflection_ClassJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_MtblHeadJc;
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




extern_C const ClassJc reflection_Reflection__ObjectJc;  //the just defined reflection_
extern_C const ClassJc reflection_ClassJc;
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




extern_C const ClassJc reflection_ExtReflectionJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_OS_PtrValue;
extern_C const ClassJc reflection_Data_ExtReflectionJc;
extern_C const ClassJc reflection_ClassJc;
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




extern_C const ClassJc reflection_Data_ExtReflectionJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_ClassJc;
extern_C const ClassJc reflection_ClassJc;
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





/* NOTE: The types inside OS_PtrValue are not fixed, but the names.
 */
extern_C ClassJc const reflection_OS_PtrValue;
const struct Reflection_Fields_OS_PtrValue_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_OS_PtrValue =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_OS_PtrValue)
, {
    { "ptr__"
    , 0 //nrofArrayElements
    , REFLECTION_void
    , (1<<kBitPrimitiv_Modifier_reflectJc)| kReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((OS_PtrValue*)(0x1000))->ptr__) - (int32)(OS_PtrValue*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_OS_PtrValue
    }
  , { "value__"
    , 0 //nrofArrayElements
    , REFLECTION_void
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((OS_PtrValue*)(0x1000))->value__) - (int32)(OS_PtrValue*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_OS_PtrValue
    }

} };


extern_C ClassJc const reflection_OS_PtrValue =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_OS_PtrValue, null)
, "OS_PtrValue"
, 0     //posObjectJc
, sizeof(OS_PtrValue)
, (FieldJcArray const*)&reflection_Fields_OS_PtrValue  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
, null  //Mtbl
};




/**A StringJc is always a OS_PtrValue, but a extra type is used..
 */
extern_C ClassJc const reflection_StringJc;
const struct Reflection_Fields_StringJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_StringJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_StringJc)
, {
    { "OS_PtrValue"
    , 0 //nrofArrayElements
    , &reflection_OS_PtrValue
    , kEmbedded_Modifier_reflectJc //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &reflection_StringJc
    }
} };


ClassJc const reflection_StringJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_StringJc, null)
, "StringJc"
, 0     //posObjectJc
, sizeof(StringJc)
, (FieldJcArray const*)&reflection_Fields_StringJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
, null  //Mtbl
};

/**A StringJc is always a OS_PtrValue, but a extra type is used..
 */
extern_C ClassJc const reflection_MemSegmJc;
const struct Reflection_Fields_MemSegmJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_MemSegmJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_MemSegmJc)
, {
    { "OS_PtrValue"
    , 0 //nrofArrayElements
    , &reflection_OS_PtrValue
    , kEmbedded_Modifier_reflectJc //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &reflection_MemSegmJc
    }
} };


ClassJc const reflection_MemSegmJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_MemSegmJc, null)
, "MemSegmJc"
, 0     //posObjectJc
, sizeof(MemSegmJc)
, (FieldJcArray const*)&reflection_Fields_MemSegmJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
, null  //Mtbl
};

/**A int64 consists of 2 int32, the inspector doesn't know the type yet.
 */
extern_C ClassJc const reflection_int64;
const struct Reflection_Fields_int64_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_int64 =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_int64)
, {
    { "lo"
    , 0 //nrofArrayElements
    , REFLECTION_uint32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &reflection_int64
    }
  , { "hi"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &reflection_int64
    }
} };


ClassJc const reflection_int64 =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_int64, null)
, "int64"
, 0     //posObjectJc
, sizeof(int64)
, (FieldJcArray const*)&reflection_Fields_int64  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
, null  //Mtbl
};




/**A int64 consists of 2 int32, the inspector doesn't know the type yet. 
 */
extern_C ClassJc const reflection_uint64;
const struct Reflection_Fields_uint64_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_uint64 =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_int64)
, {
    { "lo"
    , 0 //nrofArrayElements
    , REFLECTION_uint32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &reflection_int64
    }
  , { "hi"
    , 0 //nrofArrayElements
    , REFLECTION_uint32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &reflection_int64
    }
} };


ClassJc const reflection_uint64 =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_int64, null)
, "int64"
, 0     //posObjectJc
, sizeof(int64)
, (FieldJcArray const*)&reflection_Fields_uint64  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
, null  //Mtbl
};




extern_C const ClassJc reflection_int64_hilo;  //the just defined reflection_
const struct Reflection_Fields_int64_hilo_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_int64_hilo =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_int64_hilo)
, {
    { "lo"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(OFFSETinTYPE_MemUnit(int64_hilo, lo))
    , 0  //offsetToObjectifcBase
    , &reflection_int64_hilo
    }
  , { "hi"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(OFFSETinTYPE_MemUnit(int64_hilo,hi))
    , 0  //offsetToObjectifcBase
    , &reflection_int64_hilo
    }
} };


const ClassJc reflection_int64_hilo =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_int64_hilo, &reflection_ClassJc)
, "int64_hilo"
, 0
, sizeof(int64_hilo)
, (FieldJcArray const*)&reflection_Fields_int64_hilo  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_int64_uhilo;  //the just defined reflection_
extern_C const ClassJc reflection_int64_hilo;
const struct Reflection_Fields_int64_uhilo_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_int64_uhilo =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_int64_uhilo)
, {
    { "v"
    , 0   //no Array, no Bitfield
    , REFLECTION_int64
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(OFFSETinTYPE_MemUnit(int64_uhilo,v))
    , 0  //offsetToObjectifcBase
    , &reflection_int64_uhilo
    }
  , { "hilo"
    , 0   //no Array, no Bitfield
    , &reflection_int64_hilo
    , 0 //bitModifiers
    , (int16)(OFFSETinTYPE_MemUnit(int64_uhilo,hilo))
    , 0  //offsetToObjectifcBase
    , &reflection_int64_uhilo
    }
} };


const ClassJc reflection_int64_uhilo =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_int64_uhilo, &reflection_ClassJc)
, "int64_uhilo"
, 0
, sizeof(int64_uhilo)
, (FieldJcArray const*)&reflection_Fields_int64_uhilo  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};







  //extern struct ClassJc_t const reflection_int16;


  extern_C const struct ClassJc_t reflection_int16_Y;
  const struct Reflection_Fields_int16_Y_t{ ObjectArrayJc head; FieldJc data[2];} reflection_Fields_int16_Y =
  { CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_int16_Y)
  , { { "head", 0 , &reflection_ObjectArrayJc, 0, 0, 0, &reflection_int16_Y }
    , { "data", 0 , &reflection_int16, 0, 0, 0, &reflection_int16_Y }
  } };
  const ClassJc reflection_int16_Y =
  { CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_int16_Y, null)
  , "Ptr", 0, sizeof(int16_Y), (FieldJcArray const*)&reflection_Fields_int16_Y
  };



DEFINE_REFLECTION_ARRAYJc(int8);

/************************************************************************/
const ClassJc  reflection__intJc =
{ CONST_ObjectJc(0, &reflection__intJc, null)
  , "int"
  , 0 //Position of the data of this class itself, after some superclasses.
  , sizeof(int32)
  , null  //Attributes
  , null  //Methods
  , null  //superclass
  , null  //interfaces
  , mPrimitiv_Modifier_reflectJc
};



const ClassJc reflection__booleanJc =
{ CONST_ObjectJc(0, &reflection__booleanJc, null)

, "boolean"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(bool)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mPrimitiv_Modifier_reflectJc
};


const ClassJc reflection__voidJc =
{ CONST_ObjectJc(0, &reflection__voidJc, null)

, "void"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(void*) //size of a pointer
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mPrimitiv_Modifier_reflectJc
};


const ClassJc reflection__floatJc =
{ CONST_ObjectJc(0, &reflection__floatJc, null)

  , "float"
  , 0 //Position of the data of this class itself, after some superclasses.
  , sizeof(int32)
  , null  //Attributes
  , null  //Methods
  , null  //superclass
  , null  //interfaces
  , mPrimitiv_Modifier_reflectJc
};


const ClassJc reflection__longJc =
{ CONST_ObjectJc(0, &reflection__longJc, null)

, "long"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(int32)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mPrimitiv_Modifier_reflectJc
};


const ClassJc reflection__byteJc =
{ CONST_ObjectJc(0, &reflection__byteJc, null)

, "byte"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(int32)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mPrimitiv_Modifier_reflectJc
};


const ClassJc reflection__shortJc =
{ CONST_ObjectJc(0, &reflection__shortJc
, null)
, "short"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(int32)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mPrimitiv_Modifier_reflectJc
};


const ClassJc reflection__charJc =
{ CONST_ObjectJc(0, &reflection__charJc
, null)
, "char"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(char)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mPrimitiv_Modifier_reflectJc
};


const ClassJc reflection__char16Jc =
{ CONST_ObjectJc(0, &reflection__char16Jc
, null)
, "char16"
, 0 //Position of the data of this class itself, after some superclasses.
, 2
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mPrimitiv_Modifier_reflectJc
};


const ClassJc reflection__doubleJc =
{ CONST_ObjectJc(0, &reflection__doubleJc
, null)
, "double"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(double)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, mPrimitiv_Modifier_reflectJc
};


const ClassJc  reflection_bitfieldJc =
{ CONST_ObjectJc(0, &reflection__intJc, null)
  , "bitfield"
  , 0 //Position of the data of this class itself, after some superclasses.
  , sizeof(int32)
  , null  //Attributes
  , null  //Methods
  , null  //superclass
  , null  //interfaces
  , mPrimitiv_Modifier_reflectJc
};



#include "OSAL/os_types_def_common.h"


const struct Reflection_Fields_float_complex_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_float_complex =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_float_complex)
, {
    { "re"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(0)
    , 0  //offsetToObjectifcBase
    , &reflection_float_complex
    }
  , { "im"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(sizeof(float))
    , 0  //offsetToObjectifcBase
    , &reflection_float_complex
    }
} };


const ClassJc reflection_float_complex =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_float_complex, &reflection_ClassJc)
, "float_complex"
, 0
, sizeof(float_complex)
, (FieldJcArray const*)&reflection_Fields_float_complex  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};






#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

const ClassJc reflection__ObjectifcBaseJcpp =
{ CONST_ObjectJc(0, &reflection__ObjectifcBaseJcpp, null)
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


#include <Jc/LocaleJc.h>
//extern_C ClassJc const reflection_LocaleJc_s;
//DEFINE_REFLECTION_REF(LocaleJc);
