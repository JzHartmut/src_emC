
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "../src/SecondCpuData.h"


extern_C const ClassJc reflection_SimpleDataDsp;  //the just defined reflection_
const struct Reflection_Fields_SimpleDataDsp_t
{ ObjectArrayJc head;
  FieldJc data[6];
} reflection_Fields_SimpleDataDsp =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &reflection_Fields_SimpleDataDsp)
, {
    { "a"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDataDsp
    }
  , { "b"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDataDsp
    }
  , { "c"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDataDsp
    }
  , { "d"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDataDsp
    }
  , { "e"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDataDsp
    }
  , { "f"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDataDsp
    }
} };


const ClassJc reflection_SimpleDataDsp =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_SimpleDataDsp, &reflection_ClassJc)
, "SimpleDataDsp"
, 0
, sizeof(SimpleDataDsp)
, (FieldJcArray const*)&reflection_Fields_SimpleDataDsp  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ExampleArrayElement;  //the just defined reflection_
extern_C const ClassJc reflection_ExampleData;
const struct Reflection_Fields_ExampleArrayElement_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_ExampleArrayElement =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_ExampleArrayElement)
, {
    { "a"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleArrayElement
    }
  , { "b"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleArrayElement
    }
  , { "c"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleArrayElement
    }
  , { "data"
    , 0   //no Array, no Bitfield
    , &reflection_ExampleData
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleArrayElement
    }
} };


const ClassJc reflection_ExampleArrayElement =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ExampleArrayElement, &reflection_ClassJc)
, "ExampleArrayElement"
, 0
, sizeof(ExampleArrayElement)
, (FieldJcArray const*)&reflection_Fields_ExampleArrayElement  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ExampleIntern;  //the just defined reflection_
extern_C const ClassJc reflection_ExampleArrayElement;
extern_C const ClassJc reflection_ExampleArrayElement;
const struct Reflection_Fields_ExampleIntern_t
{ ObjectArrayJc head;
  FieldJc data[12];
} reflection_Fields_ExampleIntern =
{ CONST_ObjectArrayJc(FieldJc, 12, OBJTYPE_FieldJc, null, &reflection_Fields_ExampleIntern)
, {
    { "i1"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "i2"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "x1"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "i3"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "i4"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "f1"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "intArray"
    , 20   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "pArray"
    , 20   //nrofArrayElements per Annotation
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc)| kReferencedContainer_Modifier_reflectJc |kStaticArray_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "pArray2"
    , 19   //nrofArrayElements per Annotation
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc)| kReferencedContainer_Modifier_reflectJc |kStaticArray_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "afterArray"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "dataArray"
    , 4   //nrofArrayElements
    , &reflection_ExampleArrayElement
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
  , { "pDataArray"
    , 4   //nrofArrayElements per Annotation
    , &reflection_ExampleArrayElement
    , 0| kReferencedContainer_Modifier_reflectJc |kStaticArray_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleIntern
    }
} };


const ClassJc reflection_ExampleIntern =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ExampleIntern, &reflection_ClassJc)
, "ExampleIntern"
, 0
, sizeof(ExampleIntern)
, (FieldJcArray const*)&reflection_Fields_ExampleIntern  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_BitFieldTest;  //the just defined reflection_
const struct Reflection_Fields_BitFieldTest_t
{ ObjectArrayJc head;
  FieldJc data[6];
} reflection_Fields_BitFieldTest =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &reflection_Fields_BitFieldTest)
, {
    { "ints"
    , 4   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_BitFieldTest
    }
  , { "bits-bit7_0"
    , 0x8000 //bitfield nrofBits=8, bitPos=0.0
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_BitFieldTest
    }
  , { "bits-bit11"
    , 0x100b //bitfield nrofBits=1, bitPos=1.3
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_BitFieldTest
    }
  , { "bits-bit16"
    , 0x4010 //bitfield nrofBits=4, bitPos=1.8
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_BitFieldTest
    }
  , { "bits-bit36"
    , 0x4024 //bitfield nrofBits=4, bitPos=4.4
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_BitFieldTest
    }
  , { "bits-bit64"
    , 0x4040 //bitfield nrofBits=4, bitPos=7.8
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_BitFieldTest
    }
} };


const ClassJc reflection_BitFieldTest =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_BitFieldTest, &reflection_ClassJc)
, "BitFieldTest"
, 0
, sizeof(BitFieldTest)
, (FieldJcArray const*)&reflection_Fields_BitFieldTest  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ExampleData;  //the just defined reflection_
extern_C const ClassJc reflection_BitFieldTest;
extern_C const ClassJc reflection_ExampleIntern;
extern_C const ClassJc reflection_ExampleIntern;
const struct Reflection_Fields_ExampleData_t
{ ObjectArrayJc head;
  FieldJc data[10];
} reflection_Fields_ExampleData =
{ CONST_ObjectArrayJc(FieldJc, 10, OBJTYPE_FieldJc, null, &reflection_Fields_ExampleData)
, {
    { "value1"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "value2"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "fValue"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "p_value2"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "p_fValue"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "bitField"
    , 0   //no Array, no Bitfield
    , &reflection_BitFieldTest
    , 0 //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "iData"
    , 5   //nrofArrayElements
    , &reflection_ExampleIntern
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "iDataRef"
    , 5   //nrofArrayElements
    , &reflection_ExampleIntern
    , 0| mReference_Modifier_reflectJc |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "testArray"
    , 5   //nrofArrayElements per Annotation
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc)| kReferencedContainer_Modifier_reflectJc |kStaticArray_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
  , { "dValue"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleData
    }
} };


const ClassJc reflection_ExampleData =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ExampleData, &reflection_ClassJc)
, "ExampleData"
, 0
, sizeof(ExampleData)
, (FieldJcArray const*)&reflection_Fields_ExampleData  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ExampleUnion;  //the just defined reflection_
const struct Reflection_Fields_ExampleUnion_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_ExampleUnion =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_ExampleUnion)
, {
    { "first"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleUnion
    }
  , { "bit1"
    , 0x1000 //bitfield nrofBits=1, bitPos=0.0
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleUnion
    }
  , { "bit2"
    , 0x500e //bitfield nrofBits=5, bitPos=1.6
    , REFLECTION_BITFIELD
    , kBitfield_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_ExampleUnion
    }
} };


const ClassJc reflection_ExampleUnion =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ExampleUnion, &reflection_ClassJc)
, "ExampleUnion"
, 0
, sizeof(ExampleUnion)
, (FieldJcArray const*)&reflection_Fields_ExampleUnion  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_MainSecondCpu;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_ExampleData;
extern_C const ClassJc reflection_ExampleIntern;
extern_C const ClassJc reflection_SimpleDataDsp;
extern_C const ClassJc reflection_ExampleUnion;
const struct Reflection_Fields_MainSecondCpu_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_MainSecondCpu =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_MainSecondCpu)
, {
    { "Object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_MainSecondCpu
    }
  , { "data1"
    , 0   //no Array, no Bitfield
    , &reflection_ExampleData
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_MainSecondCpu
    }
  , { "data2"
    , 0   //no Array, no Bitfield
    , &reflection_ExampleIntern
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_MainSecondCpu
    }
  , { "simpleDataArray"
    , 5   //nrofArrayElements per Annotation
    , &reflection_SimpleDataDsp
    , 0| kReferencedContainer_Modifier_reflectJc |kStaticArray_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_MainSecondCpu
    }
  , { "testunion"
    , 0   //no Array, no Bitfield
    , &reflection_ExampleUnion
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_MainSecondCpu
    }
  , { "x"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_MainSecondCpu
    }
  , { "y"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , -1   //offset in extra file
    , 0  //offsetToObjectifcBase
    , &reflection_MainSecondCpu
    }
} };


const ClassJc reflection_MainSecondCpu =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_MainSecondCpu, &reflection_ClassJc)
, "MainSecondCpu"
, 0
, sizeof(MainSecondCpu)
, (FieldJcArray const*)&reflection_Fields_MainSecondCpu  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


