
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "Ipc/InterProcessComm.h"


extern_C const ClassJc reflection_Address_InterProcessComm;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_Address_InterProcessComm_s_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_Address_InterProcessComm_s =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_Address_InterProcessComm_s)
, {
    { "base-object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->base.object) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm
    }
  , { "address1"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->address1) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm
    }
  , { "address2"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->address2) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm
    }
  , { "sType"
    , 20   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->sType) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm
    }
  , { "internalData"
    , 12   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->internalData) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm
    }
} };


const ClassJc reflection_Address_InterProcessComm =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Address_InterProcessComm, &reflection_ClassJc)
, "Address_InterProcessComm_s"
, 0
, sizeof(Address_InterProcessComm_s)
, (FieldJcArray const*)&reflection_Fields_Address_InterProcessComm_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_InterProcessCommFactory;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_InterProcessCommFactory_s_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_InterProcessCommFactory_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_InterProcessCommFactory_s)
, {
    { "base-object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((InterProcessCommFactory_s*)(0x1000))->base.object) -(int32)(InterProcessCommFactory_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InterProcessCommFactory
    }
} };


const ClassJc reflection_InterProcessCommFactory =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_InterProcessCommFactory, &reflection_ClassJc)
, "InterProcessCommFactory_s"
, 0
, sizeof(InterProcessCommFactory_s)
, (FieldJcArray const*)&reflection_Fields_InterProcessCommFactory_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_InterProcessComm;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_InterProcessComm_s_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_InterProcessComm_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_InterProcessComm_s)
, {
    { "base-object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((InterProcessComm_s*)(0x1000))->base.object) -(int32)(InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InterProcessComm
    }
} };


const ClassJc reflection_InterProcessComm =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_InterProcessComm, &reflection_ClassJc)
, "InterProcessComm_s"
, 0
, sizeof(InterProcessComm_s)
, (FieldJcArray const*)&reflection_Fields_InterProcessComm_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


