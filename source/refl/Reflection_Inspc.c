
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "Inspc/DataNode_Inspc.h"


extern_C const ClassJc reflection_DataNode_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_DataNode_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_DataNode_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_DataNode_Inspc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((DataNode_Inspc*)(0x1000))->object) -(int32)(DataNode_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_DataNode_Inspc
    }
  , { "data"
    , 100   //nrofArrayElements
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((DataNode_Inspc*)(0x1000))->data) -(int32)(DataNode_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_DataNode_Inspc
    }
} };


const ClassJc reflection_DataNode_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_DataNode_Inspc, &reflection_ClassJc)
, "DataNode_Inspc"
, 0
, sizeof(DataNode_Inspc)
, (FieldJcArray const*)&reflection_Fields_DataNode_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Inspc/FBaccess_Inspc.h"

#include "Inspc/FBaccess_Inspc_priv.h"


extern_C const ClassJc reflection_SimulationTime_Inspc;  //the just defined reflection_
const struct Reflection_Fields_SimulationTime_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_SimulationTime_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_SimulationTime_Inspc)
, {
    { "timeShort"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((SimulationTime_Inspc*)(0x1000))->timeShort) -(int32)(SimulationTime_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SimulationTime_Inspc
    }
  , { "timeSim"
    , 0   //no Array, no Bitfield
    , REFLECTION_double
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((SimulationTime_Inspc*)(0x1000))->timeSim) -(int32)(SimulationTime_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SimulationTime_Inspc
    }
} };


const ClassJc reflection_SimulationTime_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_SimulationTime_Inspc, &reflection_ClassJc)
, "SimulationTime_Inspc"
, 0
, sizeof(SimulationTime_Inspc)
, (FieldJcArray const*)&reflection_Fields_SimulationTime_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_FBaccess_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_DataNode_Inspc;
extern_C const ClassJc reflection_SimulationTime_Inspc;
extern_C const ClassJc reflection_Inspector_Inspc_s;
const struct Reflection_Fields_FBaccess_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_FBaccess_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_FBaccess_Inspc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((FBaccess_Inspc*)(0x1000))->object) -(int32)(FBaccess_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FBaccess_Inspc
    }
  , { "rootNode"
    , 0   //no Array, no Bitfield
    , &reflection_DataNode_Inspc
    , 0 //bitModifiers
    , (int16)((int32)(&((FBaccess_Inspc*)(0x1000))->rootNode) -(int32)(FBaccess_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FBaccess_Inspc
    }
  , { "simTime"
    , 0   //no Array, no Bitfield
    , &reflection_SimulationTime_Inspc
    , 0 //bitModifiers
    , (int16)((int32)(&((FBaccess_Inspc*)(0x1000))->simTime) -(int32)(FBaccess_Inspc*)0x1000)
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



#include "Inspc/FBaccess_Inspc_Refl.h"

#include "Inspc/GetValue_Inspc.h"


extern_C const ClassJc reflection_GetValue_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_GetValue_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_GetValue_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_GetValue_Inspc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((GetValue_Inspc*)(0x1000))->object) -(int32)(GetValue_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_GetValue_Inspc
    }
  , { "statusNotFound"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GetValue_Inspc*)(0x1000))->statusNotFound) -(int32)(GetValue_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_GetValue_Inspc
    }
  , { "addr"
    , 6   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((GetValue_Inspc*)(0x1000))->addr) -(int32)(GetValue_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_GetValue_Inspc
    }
} };


const ClassJc reflection_GetValue_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_GetValue_Inspc, &reflection_ClassJc)
, "GetValue_Inspc"
, 0
, sizeof(GetValue_Inspc)
, (FieldJcArray const*)&reflection_Fields_GetValue_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Inspc/InputValues_Inspc.h"


extern_C const ClassJc reflection_InputValues_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_InputValues_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[8];
} reflection_Fields_InputValues_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 8, OBJTYPE_FieldJc, null, &reflection_Fields_InputValues_Inspc)
, {
    { "base"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((InputValues_Inspc*)(0x1000))->base) -(int32)(InputValues_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InputValues_Inspc
    }
  , { "val"
    , 240   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((InputValues_Inspc*)(0x1000))->val) -(int32)(InputValues_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InputValues_Inspc
    }
  , { "errorCfg"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InputValues_Inspc*)(0x1000))->errorCfg) -(int32)(InputValues_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InputValues_Inspc
    }
  , { "nameRefl"
    , 32   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((InputValues_Inspc*)(0x1000))->nameRefl) -(int32)(InputValues_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InputValues_Inspc
    }
  , { "nrofElements"
    , 12   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((InputValues_Inspc*)(0x1000))->nrofElements) -(int32)(InputValues_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InputValues_Inspc
    }
  , { "dataType"
    , 16   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((InputValues_Inspc*)(0x1000))->dataType) -(int32)(InputValues_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InputValues_Inspc
    }
  , { "dataTypeSmlk"
    , 12   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((InputValues_Inspc*)(0x1000))->dataTypeSmlk) -(int32)(InputValues_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InputValues_Inspc
    }
  , { "names"
    , 12   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((InputValues_Inspc*)(0x1000))->names) -(int32)(InputValues_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InputValues_Inspc
    }
} };


const ClassJc reflection_InputValues_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_InputValues_Inspc, &reflection_ClassJc)
, "InputValues_Inspc"
, 0
, sizeof(InputValues_Inspc)
, (FieldJcArray const*)&reflection_Fields_InputValues_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Inspc/InputValues_Inspc_Refl.h"

#include "Inspc/InspcTargetProxyTelg.h"


extern_C const ClassJc reflection_TelgProxy2Target_Inspc_s;  //the just defined reflection_
const struct Reflection_Fields_TelgProxy2Target_Inspc_s_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_TelgProxy2Target_Inspc_s =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_TelgProxy2Target_Inspc_s)
, {
    { "length"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgProxy2Target_Inspc_s*)(0x1000))->length) -(int32)(TelgProxy2Target_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgProxy2Target_Inspc_s
    }
  , { "cmd"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgProxy2Target_Inspc_s*)(0x1000))->cmd) -(int32)(TelgProxy2Target_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgProxy2Target_Inspc_s
    }
  , { "seqnr"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgProxy2Target_Inspc_s*)(0x1000))->seqnr) -(int32)(TelgProxy2Target_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgProxy2Target_Inspc_s
    }
  , { "address"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgProxy2Target_Inspc_s*)(0x1000))->address) -(int32)(TelgProxy2Target_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgProxy2Target_Inspc_s
    }
  , { "value"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgProxy2Target_Inspc_s*)(0x1000))->value) -(int32)(TelgProxy2Target_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgProxy2Target_Inspc_s
    }
} };


const ClassJc reflection_TelgProxy2Target_Inspc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TelgProxy2Target_Inspc_s, &reflection_ClassJc)
, "TelgProxy2Target_Inspc_s"
, 0
, sizeof(TelgProxy2Target_Inspc_s)
, (FieldJcArray const*)&reflection_Fields_TelgProxy2Target_Inspc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_TelgTarget2Proxy_Inspc_s;  //the just defined reflection_
const struct Reflection_Fields_TelgTarget2Proxy_Inspc_s_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_TelgTarget2Proxy_Inspc_s =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_TelgTarget2Proxy_Inspc_s)
, {
    { "length"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgTarget2Proxy_Inspc_s*)(0x1000))->length) -(int32)(TelgTarget2Proxy_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgTarget2Proxy_Inspc_s
    }
  , { "cmd"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgTarget2Proxy_Inspc_s*)(0x1000))->cmd) -(int32)(TelgTarget2Proxy_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgTarget2Proxy_Inspc_s
    }
  , { "seqnr"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgTarget2Proxy_Inspc_s*)(0x1000))->seqnr) -(int32)(TelgTarget2Proxy_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgTarget2Proxy_Inspc_s
    }
  , { "retValue"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TelgTarget2Proxy_Inspc_s*)(0x1000))->retValue) -(int32)(TelgTarget2Proxy_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TelgTarget2Proxy_Inspc_s
    }
} };


const ClassJc reflection_TelgTarget2Proxy_Inspc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TelgTarget2Proxy_Inspc_s, &reflection_ClassJc)
, "TelgTarget2Proxy_Inspc_s"
, 0
, sizeof(TelgTarget2Proxy_Inspc_s)
, (FieldJcArray const*)&reflection_Fields_TelgTarget2Proxy_Inspc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Inspc/InspcTargetTelg.h"


extern_C const ClassJc reflection_InspcTelgHead_Inspc_s;  //the just defined reflection_
const struct Reflection_Fields_InspcTelgHead_Inspc_s_t
{ ObjectArrayJc head;
  FieldJc data[6];
} reflection_Fields_InspcTelgHead_Inspc_s =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &reflection_Fields_InspcTelgHead_Inspc_s)
, {
    { "nrofBytes"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InspcTelgHead_Inspc_s*)(0x1000))->nrofBytes) -(int32)(InspcTelgHead_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcTelgHead_Inspc_s
    }
  , { "cmdTelg"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InspcTelgHead_Inspc_s*)(0x1000))->cmdTelg) -(int32)(InspcTelgHead_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcTelgHead_Inspc_s
    }
  , { "encryption"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InspcTelgHead_Inspc_s*)(0x1000))->encryption) -(int32)(InspcTelgHead_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcTelgHead_Inspc_s
    }
  , { "seqnr"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InspcTelgHead_Inspc_s*)(0x1000))->seqnr) -(int32)(InspcTelgHead_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcTelgHead_Inspc_s
    }
  , { "answernr"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InspcTelgHead_Inspc_s*)(0x1000))->answernr) -(int32)(InspcTelgHead_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcTelgHead_Inspc_s
    }
  , { "entrant"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((InspcTelgHead_Inspc_s*)(0x1000))->entrant) -(int32)(InspcTelgHead_Inspc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_InspcTelgHead_Inspc_s
    }
} };


const ClassJc reflection_InspcTelgHead_Inspc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_InspcTelgHead_Inspc_s, &reflection_ClassJc)
, "InspcTelgHead_Inspc_s"
, 0
, sizeof(InspcTelgHead_Inspc_s)
, (FieldJcArray const*)&reflection_Fields_InspcTelgHead_Inspc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Inspc/TimeSignals_Inspc.h"


extern_C const ClassJc reflection_Entry_TimeSignals_Inspc;  //the just defined reflection_
const struct Reflection_Fields_Entry_TimeSignals_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_Entry_TimeSignals_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_Entry_TimeSignals_Inspc)
, {
    { "time"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Entry_TimeSignals_Inspc*)(0x1000))->time) -(int32)(Entry_TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Entry_TimeSignals_Inspc
    }
  , { "ixChannel"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Entry_TimeSignals_Inspc*)(0x1000))->ixChannel) -(int32)(Entry_TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Entry_TimeSignals_Inspc
    }
  , { "type"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Entry_TimeSignals_Inspc*)(0x1000))->type) -(int32)(Entry_TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Entry_TimeSignals_Inspc
    }
  , { "ya"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Entry_TimeSignals_Inspc*)(0x1000))->ya) -(int32)(Entry_TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Entry_TimeSignals_Inspc
    }
} };


const ClassJc reflection_Entry_TimeSignals_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Entry_TimeSignals_Inspc, &reflection_ClassJc)
, "Entry_TimeSignals_Inspc"
, 0
, sizeof(Entry_TimeSignals_Inspc)
, (FieldJcArray const*)&reflection_Fields_Entry_TimeSignals_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_Entries_TimeSignals_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectArrayJc;
extern_C const ClassJc reflection_Entry_TimeSignals_Inspc;
const struct Reflection_Fields_Entries_TimeSignals_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_Entries_TimeSignals_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_Entries_TimeSignals_Inspc)
, {
    { "head"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectArrayJc
    , 0 //bitModifiers
    , (int16)((int32)(&((Entries_TimeSignals_Inspc*)(0x1000))->head) -(int32)(Entries_TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Entries_TimeSignals_Inspc
    }
  , { "data"
    , 20   //nrofArrayElements
    , &reflection_Entry_TimeSignals_Inspc
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Entries_TimeSignals_Inspc*)(0x1000))->data) -(int32)(Entries_TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Entries_TimeSignals_Inspc
    }
} };


const ClassJc reflection_Entries_TimeSignals_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Entries_TimeSignals_Inspc, &reflection_ClassJc)
, "Entries_TimeSignals_Inspc"
, 0
, sizeof(Entries_TimeSignals_Inspc)
, (FieldJcArray const*)&reflection_Fields_Entries_TimeSignals_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_TimeSignals_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_Entries_TimeSignals_Inspc;
const struct Reflection_Fields_TimeSignals_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[28];
} reflection_Fields_TimeSignals_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 28, OBJTYPE_FieldJc, null, &reflection_Fields_TimeSignals_Inspc)
, {
    { "base"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->base) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "yBits"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->yBits) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "dummy1"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->dummy1) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya0"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya0) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya1"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya1) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya2"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya2) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya3"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya3) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya4"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya4) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya5"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya5) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya6"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya6) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya7"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya7) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya8"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya8) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya9"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya9) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya10"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya10) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya11"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya11) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya12"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya12) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya13"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya13) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya14"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya14) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ya15"
    , 6   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ya15) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "stepNext"
    , 0   //no Array, no Bitfield
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->stepNext) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "errorCfg"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->errorCfg) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "ixEntries"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->ixEntries) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "nameModule"
    , 32   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->nameModule) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "names"
    , 16   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->names) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "bitsComplexY"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->bitsComplexY) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "nrElements"
    , 16   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->nrElements) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "filepath"
    , 200   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->filepath) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
  , { "entries"
    , 0   //no Array, no Bitfield
    , &reflection_Entries_TimeSignals_Inspc
    , 0 //bitModifiers
    , (int16)((int32)(&((TimeSignals_Inspc*)(0x1000))->entries) -(int32)(TimeSignals_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeSignals_Inspc
    }
} };


const ClassJc reflection_TimeSignals_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TimeSignals_Inspc, &reflection_ClassJc)
, "TimeSignals_Inspc"
, 0
, sizeof(TimeSignals_Inspc)
, (FieldJcArray const*)&reflection_Fields_TimeSignals_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Inspc/TimeSignals_Inspc_Refl.h"

#include "Inspc/Wait_Inspc.h"


extern_C const ClassJc reflection_Wait_Inspc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_Wait_Inspc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_Wait_Inspc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_Wait_Inspc)
, {
    { "base"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((Wait_Inspc*)(0x1000))->base) -(int32)(Wait_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Wait_Inspc
    }
  , { "isWaiting"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Wait_Inspc*)(0x1000))->isWaiting) -(int32)(Wait_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Wait_Inspc
    }
  , { "stepsTillWait"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Wait_Inspc*)(0x1000))->stepsTillWait) -(int32)(Wait_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Wait_Inspc
    }
  , { "delay_ms"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Wait_Inspc*)(0x1000))->delay_ms) -(int32)(Wait_Inspc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Wait_Inspc
    }
} };


const ClassJc reflection_Wait_Inspc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Wait_Inspc, &reflection_ClassJc)
, "Wait_Inspc"
, 0
, sizeof(Wait_Inspc)
, (FieldJcArray const*)&reflection_Fields_Wait_Inspc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Inspc/Wait_Inspc_Refl.h"
