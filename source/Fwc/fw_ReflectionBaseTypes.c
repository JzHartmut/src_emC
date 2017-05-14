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
#include <applstdefJc.h>
#include "Jc/ReflectionJc.h"


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


const struct Reflection_Fields_double_complex_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_double_complex =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_double_complex)
, {
    { "re"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(0)
    , 0  //offsetToObjectifcBase
    , &reflection_double_complex
    }
  , { "im"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)(sizeof(double))
    , 0  //offsetToObjectifcBase
    , &reflection_double_complex
    }
} };


const ClassJc reflection_double_complex =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_double_complex, &reflection_ClassJc)
, "double_complex"
, 0
, sizeof(double_complex)
, (FieldJcArray const*)&reflection_Fields_double_complex  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};





#include "Fwc/objectBaseC.h"


extern_C const ClassJc reflection_ObjectJc;  //the just defined reflection_

extern_C const ClassJc reflection_ObjectJc;  //the just defined reflection_
extern_C const ClassJc reflection_ClassJc;
const struct Reflection_Fields_ObjectJc_t
{ ObjectArrayJc head;
  FieldJc data[8];
} reflection_Fields_ObjectJc =
{ CONST_ObjectArrayJc(FieldJc, 8, OBJTYPE_FieldJc, null, &reflection_Fields_ObjectJc)
, {
    { "objectIdentSize"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->objectIdentSize) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "offsetToStartAddr"
    , 0x0 //bitfield nrofBits=16, bitPos=0.0
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->objectIdentSize) -(int32)(ObjectJc*)0x1000) + sizeof(int32)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "idSyncHandles"
    , 0xc010 //bitfield nrofBits=12, bitPos=1.8
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->objectIdentSize) -(int32)(ObjectJc*)0x1000) + sizeof(int32)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "memoryMng"
    , 0x401c //bitfield nrofBits=4, bitPos=2.12
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->objectIdentSize) -(int32)(ObjectJc*)0x1000) + sizeof(int32)
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
  , { "ownAddress_i"
    , 2   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->ownAddress_i) -(int32)(ObjectJc*)0x1000)
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
  , { "reflectionClass_i"
    , 2   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->reflectionClass_i) -(int32)(ObjectJc*)0x1000)
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


extern_C const ClassJc reflection_ObjectArrayJc;

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



const ClassJc reflection_ClassJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ClassJc, &reflection_ClassJc)
, "ClassJc"
, 0
, sizeof(ClassJc)
, null //(FieldJcArray const*)&reflection_Fields_ClassJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};

