
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "../src/TestReflectTargetCpp.h"

#if defined(__CPLUSGEN) && defined(__cplusplus)


extern_C const ClassJc reflection_SubData;

const struct Reflection_Fields_SubData_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_SubData =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_SubData)
, {
    { "x"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((SubData*)(0x1000))->x) -(int32)(SubData*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SubData
    }
  , { "y"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((SubData*)(0x1000))->y) -(int32)(SubData*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SubData
    }
  , { "a"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((SubData*)(0x1000))->a) -(int32)(SubData*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SubData
    }
  , { "b"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((SubData*)(0x1000))->b) -(int32)(SubData*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SubData
    }
} };


const ClassJc reflection_SubData =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_SubData, &reflection_ClassJc)
, "SubData"
, 0
, sizeof(SubData)
, (FieldJcArray const*)&reflection_Fields_SubData  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#endif //C++-class

#if defined(__CPLUSGEN) && defined(__cplusplus)

extern_C const ClassJc reflection_SubData;
extern_C const ClassJc reflection_Data2;

extern_C const ClassJc reflection_Main;

const struct Reflection_Fields_Main_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_Main =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_Main)
, {
    { "sibling"
    , 0   //no Array, no Bitfield
    , &reflection_SubData
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Main*)(0x1000))->sibling) -(int32)(static_cast<ObjectJc*>((Main*)0x1000)))
    , 0  //offsetToObjectifcBase
    , &reflection_Main
    }
  , { "data2"
    , 0   //no Array, no Bitfield
    , &reflection_Data2
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Main*)(0x1000))->data2) -(int32)(static_cast<ObjectJc*>((Main*)0x1000)))
    , 0  //offsetToObjectifcBase
    , &reflection_Main
    }
  , { "i"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Main*)(0x1000))->i) -(int32)(static_cast<ObjectJc*>((Main*)0x1000)))
    , 0  //offsetToObjectifcBase
    , &reflection_Main
    }
  , { "j"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Main*)(0x1000))->j) -(int32)(static_cast<ObjectJc*>((Main*)0x1000)))
    , 0  //offsetToObjectifcBase
    , &reflection_Main
    }
  , { "k"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Main*)(0x1000))->k) -(int32)(static_cast<ObjectJc*>((Main*)0x1000)))
    , 0  //offsetToObjectifcBase
    , &reflection_Main
    }
} };


const ClassJc reflection_Main =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Main, &reflection_ClassJc)
, "Main"
, (int)(static_cast<ObjectJc*>((Main*)0x1000)) - 0x1000     //posObjectJc
, sizeof(Main)
, (FieldJcArray const*)&reflection_Fields_Main  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#endif //C++-class

#if defined(__CPLUSGEN) && defined(__cplusplus)


extern_C const ClassJc reflection_Data2;

const struct Reflection_Fields_Data2_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_Data2 =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_Data2)
, {
    { "m"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data2*)(0x1000))->m) -(int32)(Data2*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data2
    }
  , { "n"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data2*)(0x1000))->n) -(int32)(Data2*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data2
    }
  , { "e"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data2*)(0x1000))->e) -(int32)(Data2*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data2
    }
  , { "f"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data2*)(0x1000))->f) -(int32)(Data2*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data2
    }
  , { "g"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data2*)(0x1000))->g) -(int32)(Data2*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data2
    }
} };


const ClassJc reflection_Data2 =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Data2, &reflection_ClassJc)
, "Data2"
, 0
, sizeof(Data2)
, (FieldJcArray const*)&reflection_Fields_Data2  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#endif //C++-class
