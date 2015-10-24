
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "Inspc/FBaccess_Inspc.h"

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



#include "Inspc/InspcGetValue.h"


extern_C const ClassJc reflection_InspcGetValue_Inspc;  //the just defined reflection_
const struct Reflection_Fields_InspcGetValue_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_InspcGetValue_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_InspcGetValue_Inspc)
, {
    { "variableSimulink"
    , 32   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((InspcGetValue_Inspc*)(0x1000))->variableSimulink) -(int32)(InspcGetValue_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcGetValue_Inspc
    }
  , { "triggerPathChanged"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InspcGetValue_Inspc*)(0x1000))->triggerPathChanged) -(int32)(InspcGetValue_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcGetValue_Inspc
    }
  , { "path"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((InspcGetValue_Inspc*)(0x1000))->path) -(int32)(InspcGetValue_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcGetValue_Inspc
    }
  , { "ident"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InspcGetValue_Inspc*)(0x1000))->ident) -(int32)(InspcGetValue_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcGetValue_Inspc
    }
} };


const ClassJc reflection_InspcGetValue_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_InspcGetValue_Inspc, &reflection_ClassJc)
, "InspcGetValue_Inspc"
, 0
, sizeof(InspcGetValue_Inspc)
, (FieldJcArray const*)&reflection_Fields_InspcGetValue_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};


