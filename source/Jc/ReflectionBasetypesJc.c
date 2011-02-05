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


ClassJc const reflection_OS_PtrValue =
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

const Reflection__ObjectJc reflection__ObjectJc
=
{
  { CONST_ObjectJc(0  , &reflection__ObjectJc.clazz, null)
  , "ObjectJc"
  , 0 //Position of the data of this class itself, after some superclasses.
  , sizeof(int32)
  , null  //Attributes
  , null  //Methods
  , null  //superclass
  , null  //interfaces
  , 0 //modifiers
  }
, { (MT_void_Method_void)clone_ObjectJc_F
  , (MT_void_Method_void)equals_ObjectJc_F
  , (MT_void_Method_void)finalize_ObjectJc_F
  , (MT_void_Method_void)hashCode_ObjectJc_F
  , (MT_void_Method_void)toString_ObjectJc_F
  }
};




const ClassJc xxxreflection_ObjectJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &xxxreflection_ObjectJc, null)
, "ObjectJc"
, 0
, sizeof(ObjectJc)
, null  //attributes
, null  //method
, null  //superclass
, null  //interfaces
, mObjectJc_Modifier_reflectJc  //modifiers
};


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
