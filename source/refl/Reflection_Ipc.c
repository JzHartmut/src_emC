
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "Ipc/InterProcessComm.h"


extern_C const ClassJc reflection_Address_InterProcessComm_s;  //the just defined reflection_
const struct Reflection_Fields_Address_InterProcessComm_s_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_Address_InterProcessComm_s =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_Address_InterProcessComm_s)
, {
    { "address1"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->address1) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm_s
    }
  , { "address2"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->address2) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm_s
    }
  , { "sType"
    , 20   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->sType) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm_s
    }
  , { "internalData"
    , 12   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Address_InterProcessComm_s*)(0x1000))->internalData) -(int32)(Address_InterProcessComm_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Address_InterProcessComm_s
    }
} };


const ClassJc reflection_Address_InterProcessComm_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Address_InterProcessComm_s, &reflection_ClassJc)
, "Address_InterProcessComm_s"
, 0
, sizeof(Address_InterProcessComm_s)
, (FieldJcArray const*)&reflection_Fields_Address_InterProcessComm_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_InterProcessCommFactory_i;  //the just defined reflection_
const ClassJc reflection_InterProcessCommFactory_i =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_InterProcessCommFactory_i, &reflection_ClassJc)
, "InterProcessCommFactory_i"
, 0
, sizeof(InterProcessCommFactory_i)
, null  //attributes
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_InterProcessCommFactoryAccessor;  //the just defined reflection_
const ClassJc reflection_InterProcessCommFactoryAccessor =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_InterProcessCommFactoryAccessor, &reflection_ClassJc)
, "InterProcessCommFactoryAccessor"
, 0
, sizeof(InterProcessCommFactoryAccessor)
, null  //attributes
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_InterProcessComm_i;  //the just defined reflection_
const ClassJc reflection_InterProcessComm_i =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_InterProcessComm_i, &reflection_ClassJc)
, "InterProcessComm_i"
, 0
, sizeof(InterProcessComm_i)
, null  //attributes
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Inspc/FBaccess_Inspc_priv.h"


extern_C const ClassJc reflection_FBaccessNode_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_FBaccessNode_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_FBaccessNode_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_FBaccessNode_Inspc)
, {
    { "super"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((FBaccessNode_Inspc*)(0x1000))->super) -(int32)(FBaccessNode_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FBaccessNode_Inspc
    }
  , { "data"
    , 100   //nrofArrayElements
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FBaccessNode_Inspc*)(0x1000))->data) -(int32)(FBaccessNode_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FBaccessNode_Inspc
    }
} };


const ClassJc reflection_FBaccessNode_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FBaccessNode_Inspc, &reflection_ClassJc)
, "FBaccessNode_Inspc"
, 0
, sizeof(FBaccessNode_Inspc)
, (FieldJcArray const*)&reflection_Fields_FBaccessNode_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_FBaccess_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_FBaccessNode_Inspc;
extern_C const ClassJc reflection_Inspector_Inspc_s;
const struct Reflection_Fields_FBaccess_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_FBaccess_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_FBaccess_Inspc)
, {
    { "super"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((FBaccess_Inspc*)(0x1000))->super) -(int32)(FBaccess_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FBaccess_Inspc
    }
  , { "rootNode"
    , 0   //no Array, no Bitfield
    , &reflection_FBaccessNode_Inspc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FBaccess_Inspc*)(0x1000))->rootNode) -(int32)(FBaccess_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FBaccess_Inspc
    }
  , { "theInspector"
    , 0   //no Array, no Bitfield
    , &reflection_Inspector_Inspc_s
    , 0 //bitModifiers
    , (int16)((int32)(&((FBaccess_Inspc*)(0x1000))->theInspector) -(int32)(FBaccess_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FBaccess_Inspc
    }
} };


const ClassJc reflection_FBaccess_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FBaccess_Inspc, &reflection_ClassJc)
, "FBaccess_Inspc"
, 0
, sizeof(FBaccess_Inspc)
, (FieldJcArray const*)&reflection_Fields_FBaccess_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};


