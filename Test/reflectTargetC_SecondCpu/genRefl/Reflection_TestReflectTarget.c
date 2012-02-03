
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "Reflection_TestReflectTarget.h"
#include "../src/TestReflectTarget.h"

const struct Reflection_Fields_TestUnion_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_TestUnion =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_TestUnion)
, {
    { "value"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestUnion*)(0x1000))->value) -(int32)(TestUnion*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestUnion
    }
  , { "b0"
    , 0x3000 //bitfield nrofBits=3, bitPos=0.0
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , (int16)0
    , 0  //offsetToObjectifcBase
    , &reflection_TestUnion
    }
  , { "b3"
    , 0xb003 //bitfield nrofBits=11, bitPos=0.3
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , (int16)0
    , 0  //offsetToObjectifcBase
    , &reflection_TestUnion
    }
  , { "b14"
    , 0x500e //bitfield nrofBits=5, bitPos=1.6
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , (int16)0
    , 0  //offsetToObjectifcBase
    , &reflection_TestUnion
    }
  , { "b19"
    , 0x1013 //bitfield nrofBits=1, bitPos=2.3
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , (int16)0
    , 0  //offsetToObjectifcBase
    , &reflection_TestUnion
    }
} };


const ClassJc reflection_TestUnion =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TestUnion, &reflection_ClassJc)
, "TestUnion"
, 0
, sizeof(TestUnion)
, (FieldJcArray const*)&reflection_Fields_TestUnion  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



extern const ClassJc reflection_ObjectJc;
extern const ClassJc reflection_Inspector_Inspc_s;
extern const ClassJc reflection_TestUnion;
extern const ClassJc reflection_WorkingThread_Inspc_s;
extern const ClassJc reflection_ExtReflectionJc_s;
const struct Reflection_Fields_TestInspector_t
{ ObjectArrayJc head;
  FieldJc data[19];
} reflection_Fields_TestInspector =
{ CONST_ObjectArrayJc(FieldJc, 19, OBJTYPE_FieldJc, null, &reflection_Fields_TestInspector)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->object) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "_DSP_"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->_DSP_) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "reflexAccess"
    , 0   //no Array, no Bitfield
    , &reflection_Inspector_Inspc_s
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->reflexAccess) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "x"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->x) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "y"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->y) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "a"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->a) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "b"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->b) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "c"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->c) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "zz"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->zz) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "dVal"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->dVal) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "i32Val"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->i32Val) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "i16Val"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->i16Val) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "i64Val"
    , 0   //no Array, no Bitfield
    , REFLECTION_int64
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->i64Val) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "int8Val"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->int8Val) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "bVal"
    , 0   //no Array, no Bitfield
    , REFLECTION_bool
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->bVal) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "testUnion"
    , 0   //no Array, no Bitfield
    , &reflection_TestUnion
    , 0 //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->testUnion) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "intArray"
    , 12   //nrofArrayElements
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->intArray) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "workingThread"
    , 0   //no Array, no Bitfield
    , &reflection_WorkingThread_Inspc_s
    , 0 //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->workingThread) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
  , { "extReflectionDsp"
    , 0   //no Array, no Bitfield
    , &reflection_ExtReflectionJc_s
    , 0 //bitModifiers
    , (int16)((int32)(&((TestInspector*)(0x1000))->extReflectionDsp) -(int32)(TestInspector*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TestInspector
    }
} };


const ClassJc reflection_TestInspector =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TestInspector, &reflection_ClassJc)
, "TestInspector"
, 0
, sizeof(TestInspector)
, (FieldJcArray const*)&reflection_Fields_TestInspector  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


