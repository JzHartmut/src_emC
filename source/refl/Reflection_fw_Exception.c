
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>



extern_C const ClassJc reflection_ExceptionJc;  //the just defined reflection_
extern_C const ClassJc reflection_StringJc;
const struct Reflection_Fields_ExceptionJc_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_ExceptionJc =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_ExceptionJc)
, {
    { "exceptionNr"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ExceptionJc*)(0x1000))->exceptionNr) -(int32)(ExceptionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExceptionJc
    }
  , { "exceptionMsg"
    , 0   //no Array, no Bitfield
    , &reflection_StringJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ExceptionJc*)(0x1000))->exceptionMsg) -(int32)(ExceptionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExceptionJc
    }
  , { "exceptionValue"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ExceptionJc*)(0x1000))->exceptionValue) -(int32)(ExceptionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExceptionJc
    }
} };


const ClassJc reflection_ExceptionJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ExceptionJc, &reflection_ClassJc)
, "ExceptionJc"
, 0
, sizeof(ExceptionJc)
, (FieldJcArray const*)&reflection_Fields_ExceptionJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_TryObjectJc;  //the just defined reflection_
extern_C const ClassJc reflection_ExceptionJc;
const struct Reflection_Fields_TryObjectJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_TryObjectJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_TryObjectJc)
, {
    { "exc"
    , 0   //no Array, no Bitfield
    , &reflection_ExceptionJc
    , 0 //bitModifiers
    , (int16)((int32)(&((TryObjectJc*)(0x1000))->exc) -(int32)(TryObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TryObjectJc
    }
  , { "excNrTestCatch"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TryObjectJc*)(0x1000))->excNrTestCatch) -(int32)(TryObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TryObjectJc
    }
} };


const ClassJc reflection_TryObjectJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TryObjectJc, &reflection_ClassJc)
, "TryObjectJc"
, 0
, sizeof(TryObjectJc)
, (FieldJcArray const*)&reflection_Fields_TryObjectJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_StacktraceJc;  //the just defined reflection_
const struct Reflection_Fields_StacktraceJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_StacktraceJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_StacktraceJc)
, {
    { "ix"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StacktraceJc*)(0x1000))->ix) -(int32)(StacktraceJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceJc
    }
  , { "ixPrev"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StacktraceJc*)(0x1000))->ixPrev) -(int32)(StacktraceJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceJc
    }
} };


const ClassJc reflection_StacktraceJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_StacktraceJc, &reflection_ClassJc)
, "StacktraceJc"
, 0
, sizeof(StacktraceJc)
, (FieldJcArray const*)&reflection_Fields_StacktraceJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "emC/ExceptionDefs.h"

#include "emC/ThreadContext_emC.h"


extern_C const ClassJc reflection_AddrUsed_ThreadContext_emC;  //the just defined reflection_
extern_C const ClassJc reflection_OS_PtrValue;
const struct Reflection_Fields_AddrUsed_ThreadContext_emC_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_AddrUsed_ThreadContext_emC =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_AddrUsed_ThreadContext_emC)
, {
    { "sign"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((AddrUsed_ThreadContext_emC*)(0x1000))->sign) -(int32)(AddrUsed_ThreadContext_emC*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AddrUsed_ThreadContext_emC
    }
  , { "used"
    , 0   //no Array, no Bitfield
    , &reflection_OS_PtrValue
    , 0 //bitModifiers
    , (int16)((int32)(&((AddrUsed_ThreadContext_emC*)(0x1000))->used) -(int32)(AddrUsed_ThreadContext_emC*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AddrUsed_ThreadContext_emC
    }
} };


const ClassJc reflection_AddrUsed_ThreadContext_emC =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_AddrUsed_ThreadContext_emC, &reflection_ClassJc)
, "AddrUsed_ThreadContext_emC"
, 0
, sizeof(AddrUsed_ThreadContext_emC)
, (FieldJcArray const*)&reflection_Fields_AddrUsed_ThreadContext_emC  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_StacktraceElementJc;  //the just defined reflection_
extern_C const ClassJc reflection_TryObjectJc;
const struct Reflection_Fields_StacktraceElementJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_StacktraceElementJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_StacktraceElementJc)
, {
    { "name"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((StacktraceElementJc*)(0x1000))->name) -(int32)(StacktraceElementJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceElementJc
    }
  , { "source"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((StacktraceElementJc*)(0x1000))->source) -(int32)(StacktraceElementJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceElementJc
    }
  , { "line"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StacktraceElementJc*)(0x1000))->line) -(int32)(StacktraceElementJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceElementJc
    }
  , { "tryObject"
    , 0   //no Array, no Bitfield
    , &reflection_TryObjectJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((StacktraceElementJc*)(0x1000))->tryObject) -(int32)(StacktraceElementJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceElementJc
    }
} };


const ClassJc reflection_StacktraceElementJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_StacktraceElementJc, &reflection_ClassJc)
, "StacktraceElementJc"
, 0
, sizeof(StacktraceElementJc)
, (FieldJcArray const*)&reflection_Fields_StacktraceElementJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_StacktraceThreadContext_emC_s;  //the just defined reflection_
extern_C const ClassJc reflection_StacktraceElementJc;
const struct Reflection_Fields_StacktraceThreadContext_emC_s_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_StacktraceThreadContext_emC_s =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_StacktraceThreadContext_emC_s)
, {
    { "zEntries"
    , 0   //no Array, no Bitfield
    , REFLECTION_uint32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StacktraceThreadContext_emC_s*)(0x1000))->zEntries) -(int32)(StacktraceThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceThreadContext_emC_s
    }
  , { "maxNrofEntrie_tacktraceBuffer"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StacktraceThreadContext_emC_s*)(0x1000))->maxNrofEntriesStacktraceBuffer) -(int32)(StacktraceThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceThreadContext_emC_s
    }
  , { "entries"
    , 100   //nrofArrayElements
    , &reflection_StacktraceElementJc
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((StacktraceThreadContext_emC_s*)(0x1000))->entries) -(int32)(StacktraceThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceThreadContext_emC_s
    }
} };


const ClassJc reflection_StacktraceThreadContext_emC_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_StacktraceThreadContext_emC_s, &reflection_ClassJc)
, "StacktraceThreadContext_emC_s"
, 0
, sizeof(StacktraceThreadContext_emC_s)
, (FieldJcArray const*)&reflection_Fields_StacktraceThreadContext_emC_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ThreadContext_emC_s;  //the just defined reflection_
extern_C const ClassJc reflection_OS_PtrValue;
extern_C const ClassJc reflection_AddrUsed_ThreadContext_emC;
extern_C const ClassJc reflection_StacktraceThreadContext_emC_s;
const struct Reflection_Fields_ThreadContext_emC_s_t
{ ObjectArrayJc head;
  FieldJc data[9];
} reflection_Fields_ThreadContext_emC_s =
{ CONST_ObjectArrayJc(FieldJc, 9, OBJTYPE_FieldJc, null, &reflection_Fields_ThreadContext_emC_s)
, {
    { "bufferAlloc"
    , 0   //no Array, no Bitfield
    , &reflection_OS_PtrValue
    , 0 //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->bufferAlloc) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
  , { "addrUsed"
    , 30   //nrofArrayElements
    , &reflection_AddrUsed_ThreadContext_emC
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->addrUsed) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
  , { "bitAddrUsed"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->bitAddrUsed) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
  , { "addrFree"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->addrFree) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
  , { "ixLastAddrUsed"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->ixLastAddrUsed) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
  , { "mode"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->mode) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
  , { "blockHeap"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->blockHeap) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
  , { "topmemAddrOfStack"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->topmemAddrOfStack) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
  , { "stacktrc"
    , 0   //no Array, no Bitfield
    , &reflection_StacktraceThreadContext_emC_s
    , 0 //bitModifiers
    , (int16)((int32)(&((ThreadContext_emC_s*)(0x1000))->stacktrc) -(int32)(ThreadContext_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContext_emC_s
    }
} };


const ClassJc reflection_ThreadContext_emC_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ThreadContext_emC_s, &reflection_ClassJc)
, "ThreadContext_emC_s"
, 0
, sizeof(ThreadContext_emC_s)
, (FieldJcArray const*)&reflection_Fields_ThreadContext_emC_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};


