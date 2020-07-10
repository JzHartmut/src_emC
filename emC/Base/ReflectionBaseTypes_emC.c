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
#include "emC/Base/Object_emC.h"

#ifdef DEF_REFLECTION_FULL  //Note: this feature is not able to use without full reflection support


/************************************************************************/
const ClassJc  refl__intJc =
{ CONST_ObjectJc(0, &refl__intJc, null)
  , "int"
  , 0 //Position of the data of this class itself, after some superclasses.
  , sizeof(int32)
  , null  //Attributes
  , null  //Methods
  , null  //superclass
  , null  //interfaces
  , 4 << kBitPrimitiv_Modifier_reflectJc
};



const ClassJc refl__booleanJc =
{ CONST_ObjectJc(0, &refl__booleanJc, null)

, "boolean"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(bool)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, 1<<kBitPrimitiv_Modifier_reflectJc
};


const ClassJc refl__voidJc =
{ CONST_ObjectJc(0, &refl__voidJc, null)

, "void"
, 0 //Position of the data of this class itself, after some superclasses.
, 0 //2018-07 sizeof a void type should be 0. If it is a pointer, then the pointer size is gotten like usual, not here! FAULTY: sizeof(void*) //size of a pointer
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, 0
};


const ClassJc refl__floatJc =
{ CONST_ObjectJc(0, &refl__floatJc, null)

  , "float"
  , 0 //Position of the data of this class itself, after some superclasses.
  , sizeof(float)
  , null  //Attributes
  , null  //Methods
  , null  //superclass
  , null  //interfaces
  , 4 << kBitPrimitiv_Modifier_reflectJc
};


const ClassJc refl__longJc =
{ CONST_ObjectJc(0, &refl__longJc, null)

, "long"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(int64)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, 8 << kBitPrimitiv_Modifier_reflectJc
};


const ClassJc refl__byteJc =
{ CONST_ObjectJc(0, &refl__byteJc, null)

, "byte"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(int8)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, 1 << kBitPrimitiv_Modifier_reflectJc
};


const ClassJc refl__shortJc =
{ CONST_ObjectJc(0, &refl__shortJc
, null)
, "short"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(int16)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, 2 << kBitPrimitiv_Modifier_reflectJc
};


const ClassJc refl__charJc =
{ CONST_ObjectJc(0, &refl__charJc
, null)
, "char"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(char)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, 1 << kBitPrimitiv_Modifier_reflectJc
};


const ClassJc refl__char16Jc =
{ CONST_ObjectJc(0, &refl__char16Jc
, null)
, "char16"
, 0 //Position of the data of this class itself, after some superclasses.
, 2
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, 2 << kBitPrimitiv_Modifier_reflectJc
};


const ClassJc refl__doubleJc =
{ CONST_ObjectJc(0, &refl__doubleJc
, null)
, "double"
, 0 //Position of the data of this class itself, after some superclasses.
, sizeof(double)
, null  //Attributes
, null  //Methods
, null  //superclass
, null  //interfaces
, 8 << kBitPrimitiv_Modifier_reflectJc
};


const ClassJc  refl_bitfieldJc =
{ CONST_ObjectJc(0, &refl__intJc, null)
  , "bitfield"
  , 0 //Position of the data of this class itself, after some superclasses.
  , sizeof(int32)
  , null  //Attributes
  , null  //Methods
  , null  //superclass
  , null  //interfaces
  , 7 << kBitPrimitiv_Modifier_reflectJc
};



#include "emC/Base/types_def_common.h"


extern_C const ClassJc refl_int64_hilo;  //the just defined refl_
const struct Reflection_Fields_int64_hilo_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_int64_hilo =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_int64_hilo)
, {
    { "lo"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(OFFSETinTYPE_MemUnit(int64_hilo, lo))
    , 0  //offsetToObjectifcBase
    , &refl_int64_hilo
    }
  , { "hi"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(OFFSETinTYPE_MemUnit(int64_hilo,hi))
    , 0  //offsetToObjectifcBase
    , &refl_int64_hilo
    }
} };


const ClassJc refl_int64_hilo =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_int64_hilo, &refl_ClassJc)
, "int64_hilo"
, 0
, sizeof(int64_hilo)
, (FieldJcArray const*)&refl_Fields_int64_hilo  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc refl_int64_uhilo;  //the just defined refl_
extern_C const ClassJc refl_int64_hilo;
const struct Reflection_Fields_int64_uhilo_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_int64_uhilo =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_int64_uhilo)
, {
    { "v"
    , 0   //no Array, no Bitfield
    , REFLECTION_int64
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(OFFSETinTYPE_MemUnit(int64_uhilo,v))
    , 0  //offsetToObjectifcBase
    , &refl_int64_uhilo
    }
  , { "hilo"
    , 0   //no Array, no Bitfield
    , &refl_int64_hilo
    , 0 //bitModifiers
    , (int16)(OFFSETinTYPE_MemUnit(int64_uhilo,hilo))
    , 0  //offsetToObjectifcBase
    , &refl_int64_uhilo
    }
} };


const ClassJc refl_int64_uhilo =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_int64_uhilo, &refl_ClassJc)
, "int64_uhilo"
, 0
, sizeof(int64_uhilo)
, (FieldJcArray const*)&refl_Fields_int64_uhilo  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



const struct Reflection_Fields_float_complex_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_float_complex =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_float_complex)
, {
    { "re"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(0)
    , 0  //offsetToObjectifcBase
    , &refl_float_complex
    }
  , { "im"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(sizeof(float))
    , 0  //offsetToObjectifcBase
    , &refl_float_complex
    }
} };


const ClassJc refl_float_complex =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_float_complex, &refl_ClassJc)
, "float_complex"
, 0
, sizeof(float_complex)
, (FieldJcArray const*)&refl_Fields_float_complex  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};


const struct Reflection_Fields_double_complex_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_double_complex =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_double_complex)
, {
    { "re"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(0)
    , 0  //offsetToObjectifcBase
    , &refl_double_complex
    }
  , { "im"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(sizeof(double))
    , 0  //offsetToObjectifcBase
    , &refl_double_complex
    }
} };


const ClassJc refl_double_complex =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_double_complex, &refl_ClassJc)
, "double_complex"
, 0
, sizeof(double_complex)
, (FieldJcArray const*)&refl_Fields_double_complex  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};





#include "emC/Base/Object_emC.h"


extern_C const ClassJc refl_ObjectJc;  //the just defined refl_

extern_C const ClassJc refl_ObjectJc;  //the just defined refl_
extern_C const ClassJc refl_ClassJc;
const struct Reflection_Fields_ObjectJc_t
{ ObjectArrayJc head;
  FieldJc data[9];
} refl_Fields_ObjectJc =
{ CONST_ObjectArrayJc(FieldJc, 8, OBJTYPE_FieldJc, null, &refl_Fields_ObjectJc)
, {
    { "identSize"
    , 0   //no Array, no Bitfield
    , REFLECTION_uint32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ObjectJc*)(0x1000))->identSize) -(intptr_t)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectJc
    }
  #if defined(DEF_ObjectJcpp_REFLECTION) || defined(DEF_ObjectJc_SYNCHANDLE)
  , { "offsetToInstanceAddr"
    , 0x0 //bitfield nrofBits=16, bitPos=0.0
    , REFLECTION_uint16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ObjectJc*)(0x1000))->offsetToInstanceAddr) -(intptr_t)(ObjectJc*)0x1000) + sizeof(int32)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectJc
    }
  , { "idSyncHandles"
    , 0xc010 //bitfield nrofBits=12, bitPos=0.16
    , REFLECTION_uint16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ObjectJc*)(0x1000))->handleBits) -(intptr_t)(ObjectJc*)0x1000) + sizeof(int32)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectJc
    }
  #endif
  #ifdef DEF_ObjectJc_OWNADDRESS
  , { "ownAddress"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ObjectJc*)(0x1000))->ownAddress) -(intptr_t)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectJc
    }
  #endif
  , { "reflection"
    , 0   //no Array, no Bitfield
    , &refl_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((ObjectJc*)(0x1000))->reflection) -(intptr_t)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectJc
    }
} };


#ifdef DEF_ClassJc_Vtbl
//
// The vtbl for a pure ObjectJc or for any other instance without overridden operation.
const VtblDef_ObjectJc vtbl_ObjectJc =
{ { { sign_Vtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
    , (struct Size_Vtbl_t*)((5 + 2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
//J2C: Dynamic methods of the class :ObjectJc:
  ,  clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_ObjectJc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
, { signEnd_Vtbl_ObjectJc, null }
};
#endif


const ClassJc refl_ObjectJc =
{ INIZ_ObjectJc(refl_ObjectJc, refl_ClassJc, OBJTYPE_ClassJc)
  //CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc)
, "ObjectJc"
, 0
, sizeof(ObjectJc)
, (FieldJcArray const*)&refl_Fields_ObjectJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
#ifdef DEF_ClassJc_Vtbl
, &vtbl_ObjectJc.tbl.head
#endif
};









extern_C const ClassJc refl_ObjectArrayJc;  //the just defined refl_
extern_C const ClassJc refl_ObjectJc;
const struct Reflection_Fields_ObjectArrayJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} refl_Fields_ObjectArrayJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &refl_Fields_ObjectArrayJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJc
    , 0 //bitModifiers
    , (int16)((intptr_t)(&((ObjectArrayJc*)(0x1000))->object) -(intptr_t)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectArrayJc
    }
  , { "sizeElement"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ObjectArrayJc*)(0x1000))->sizeElement) -(intptr_t)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectArrayJc
    }
  , { "mode"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ObjectArrayJc*)(0x1000))->mode) -(intptr_t)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectArrayJc
    }
  , { "length"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((ObjectArrayJc*)(0x1000))->length) -(intptr_t)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectArrayJc
    }
} };


extern_C const ClassJc refl_ObjectArrayJc;

		const ClassJc refl_ObjectArrayJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectArrayJc, &refl_ClassJc)
, "ObjectArrayJc"
, 0
, sizeof(ObjectArrayJc)
, (FieldJcArray const*)&refl_Fields_ObjectArrayJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


#ifdef DEF_ClassJc_Vtbl

extern_C const ClassJc refl_VtblHeadJc;  //the just defined refl_
const struct Reflection_Fields_VtblHeadJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_VtblHeadJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_VtblHeadJc)
, {
    { "sign"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((VtblHeadJc*)(0x1000))->sign) -(intptr_t)(VtblHeadJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_VtblHeadJc
    }
  , { "sizeTable"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((VtblHeadJc*)(0x1000))->sizeTable) -(intptr_t)(VtblHeadJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_VtblHeadJc
    }
} };


const ClassJc refl_VtblHeadJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_VtblHeadJc, &refl_ClassJc)
, "VtblHeadJc"
, 0
, sizeof(VtblHeadJc)
, (FieldJcArray const*)&refl_Fields_VtblHeadJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};
#endif

extern_C const ClassJc refl_ClassJc;
const ClassJc refl_ClassJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ClassJc, &refl_ClassJc)
, "ClassJc"
, 0
, sizeof(ClassJc)
, null //(FieldJcArray const*)&refl_Fields_ClassJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


extern_C ClassJc const refl_FieldJc;
const ClassJc refl_FieldJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(FieldJc), &refl_FieldJc, &refl_FieldJc)
, "FieldJc"
, 0
, sizeof(FieldJc)
, null //(FieldJcArray const*)&refl_Fields_ClassJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



extern_C ClassJc const refl_ClassOffset_idxVtblJc;
const ClassJc refl_ClassOffset_idxVtblJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(FieldJc), &refl_ClassOffset_idxVtblJc, &refl_ClassOffset_idxVtblJc)
, "ClassOffset_idxVtblJc"
, 0
, sizeof(ClassOffset_idxVtblJc)
, null //(FieldJcArray const*)&refl_Fields_ClassJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};





/* NOTE: The types inside OS_PtrValue are not fixed, but the names.
 */
extern_C ClassJc const refl_OS_PtrValue;
const struct Reflection_Fields_OS_PtrValue_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_OS_PtrValue =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_OS_PtrValue)
, {
    { "ref"
    , 0 //nrofArrayElements
    , &refl__voidJc
    , (1<<kBitPrimitiv_Modifier_reflectJc)| kReference_Modifier_reflectJc //bitModifiers
    , (int16)((intptr_t)(&((OS_PtrValue*)(0x1000))->addr) - (intptr_t)(OS_PtrValue*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_OS_PtrValue
    }
  , { "val"
    , 0 //nrofArrayElements
    , &refl__voidJc
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((intptr_t)(&((OS_PtrValue*)(0x1000))->val) - (intptr_t)(OS_PtrValue*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_OS_PtrValue
    }

} };


extern_C ClassJc const refl_OS_PtrValue =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_OS_PtrValue, null)
, "OS_PtrValue"
, 0     //posObjectJc
, sizeof(OS_PtrValue)
, (FieldJcArray const*)&refl_Fields_OS_PtrValue  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
};




/**A StringJc is always a OS_PtrValue, but a extra type is used..
 */
extern_C ClassJc const refl_StringJc;
const struct Reflection_Fields_StringJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} refl_Fields_StringJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_StringJc)
, {
    { "OS_PtrValue"
    , 0 //nrofArrayElements
    , &refl_OS_PtrValue
    , kEmbedded_Modifier_reflectJc //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &refl_StringJc
    }
} };


ClassJc const refl_StringJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_StringJc, null)
, "StringJc"
, 0     //posObjectJc
, sizeof(StringJc)
, (FieldJcArray const*)&refl_Fields_StringJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
#ifdef DEF_ClassJc_Vtbl
, null  //Vtbl
#endif
};

ClassJc const refl_CharSeqJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_StringJc, null)
, "CharSeqJc"
, 0     //posObjectJc
, sizeof(StringJc)
, (FieldJcArray const*)&refl_Fields_StringJc  //same as StringJc: attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
#ifdef DEF_ClassJc_Vtbl
, null  //Vtbl
#endif
};

/**A StringJc is always a OS_PtrValue, but a extra type is used..
 */
extern_C ClassJc const refl_MemSegmJc;
const struct Reflection_Fields_MemSegmJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} refl_Fields_MemSegmJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_MemSegmJc)
, {
    { "OS_PtrValue"
    , 0 //nrofArrayElements
    , &refl_OS_PtrValue
    , kEmbedded_Modifier_reflectJc //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &refl_MemSegmJc
    }
} };


ClassJc const refl_MemSegmJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_MemSegmJc, null)
, "MemSegmJc"
, 0     //posObjectJc
, sizeof(MemSegmJc)
, (FieldJcArray const*)&refl_Fields_MemSegmJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
#ifdef DEF_ClassJc_Vtbl
, null  //Vtbl
#endif
};

/**A int64 consists of 2 int32, the inspector doesn't know the type yet.
 */
extern_C ClassJc const refl_int64;
const struct Reflection_Fields_int64_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_int64 =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_int64)
, {
    { "lo"
    , 0 //nrofArrayElements
    , REFLECTION_uint32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &refl_int64
    }
  , { "hi"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &refl_int64
    }
} };


ClassJc const refl_int64 =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_int64, null)
, "int64"
, 0     //posObjectJc
, sizeof(int64)
, (FieldJcArray const*)&refl_Fields_int64  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
#ifdef DEF_ClassJc_Vtbl
, null  //Vtbl
#endif
};




/**A int64 consists of 2 int32, the inspector doesn't know the type yet. 
 */
extern_C ClassJc const refl_uint64;
const struct Reflection_Fields_uint64_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_uint64 =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_int64)
, {
    { "lo"
    , 0 //nrofArrayElements
    , REFLECTION_uint32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &refl_int64
    }
  , { "hi"
    , 0 //nrofArrayElements
    , REFLECTION_uint32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &refl_int64
    }
} };


ClassJc const refl_uint64 =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_int64, null)
, "int64"
, 0     //posObjectJc
, sizeof(int64)
, (FieldJcArray const*)&refl_Fields_uint64  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0x0  //modifiers
#ifdef DEF_ClassJc_Vtbl
, null  //Vtbl
#endif
};


#elif defined(DEF_REFLECTION_OFFS)

//This is necessary to recognize this type.
ClassJc const refl_ClassJc = INIZ_ClassJc(refl_ClassJc, "ClassJc");

#elsif !defined(DEF_REFLECTION_NO)

ClassJc const refl_ClassJc = INIZ_ClassJc(refl_ClassJc, "ClassJc");

#endif //not DEF_REFLECTION_FULL

