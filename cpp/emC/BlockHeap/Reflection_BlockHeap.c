
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "../../source/BlockHeap/BlockHeap_emC_s.h"

#include "../../source/BlockHeap/BlockHeapJc_admin.h"


extern_C const ClassJc refl_BlockHeap_emC;  //the just defined refl_
extern_C const ClassJc refl_BlockHeapBlockJc_debugArray;
extern_C const ClassJc refl_BlockHeapBlockJc;
extern_C const ClassJc refl_BlockHeapBlockJc;
extern_C const ClassJc refl_BlockHeapBlockJc;
extern_C const ClassJc refl_BlockHeapBlockJc;
extern_C const ClassJc refl_ListMapEntryJc;
extern_C const ClassJc refl_ListMapEntryJc;
extern_C const ClassJc refl_LogMessageFW;
const struct Reflection_Fields_BlockHeap_emC_t
{ ObjectArrayJc head;
  FieldJc data[18];
} refl_Fields_BlockHeap_emC =
{ CONST_ObjectArrayJc(FieldJc, 18, OBJTYPE_FieldJc, null, &refl_Fields_BlockHeap_emC)
, {
    { "nextHeap"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->nextHeap) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "idxHeapCtrl"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->idxHeapCtrl) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "zBlock"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->zBlock) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "bytesSmallBlock"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->bytesSmallBlock) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "mAdressSmallBlock_BlockHeap"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->mAdressSmallBlock_BlockHeap) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "heapBegin"
    , 0   //no Array, no Bitfield
    , &refl_BlockHeapBlockJc_debugArray
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->heapBegin) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "heapEnd"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->heapEnd) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "firstFreeBlock"
    , 0   //no Array, no Bitfield
    , &refl_BlockHeapBlockJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->firstFreeBlock) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "firstFreeBlockSmall"
    , 0   //no Array, no Bitfield
    , &refl_BlockHeapBlockJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->firstFreeBlockSmall) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "firstFreeBlockMapEntry"
    , 0   //no Array, no Bitfield
    , &refl_BlockHeapBlockJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->firstFreeBlockMapEntry) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "lastFreeBlockMapEntry"
    , 0   //no Array, no Bitfield
    , &refl_BlockHeapBlockJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->lastFreeBlockMapEntry) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "firstMapEntry"
    , 0   //no Array, no Bitfield
    , &refl_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->firstMapEntry) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "lastMapEntry"
    , 0   //no Array, no Bitfield
    , &refl_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->lastMapEntry) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "bitInitMode"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->bitInitMode) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "ctCollosionAlloc"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->ctCollosionAlloc) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "ctCollosionFree"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->ctCollosionFree) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "log"
    , 0   //no Array, no Bitfield
    , &refl_LogMessageFW
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->log) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
  , { "kIdentMsgBase"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeap_emC_s*)(0x1000))->kIdentMsgBase) -(int32)(BlockHeap_emC_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeap_emC
    }
} };


const ClassJc refl_BlockHeap_emC =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_BlockHeap_emC, &refl_ClassJc)
, "BlockHeap_emC_s"
, 0
, sizeof(BlockHeap_emC_s)
, (FieldJcArray const*)&refl_Fields_BlockHeap_emC  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "BlockHeapJc_internal.h"


extern_C const ClassJc refl_ObjectJcREFArray;  //the just defined refl_
const struct Reflection_Fields_ObjectJcREFArray_t
{ ObjectArrayJc head;
  FieldJc data[1];
} refl_Fields_ObjectJcREFArray =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_ObjectJcREFArray)
, {
    { "data"
    , 10   //nrofArrayElements
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJcREFArray*)(0x1000))->data) -(int32)(ObjectJcREFArray*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_ObjectJcREFArray
    }
} };


const ClassJc refl_ObjectJcREFArray =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJcREFArray, &refl_ClassJc)
, "ObjectJcREFArray"
, 0
, sizeof(ObjectJcREFArray)
, (FieldJcArray const*)&refl_Fields_ObjectJcREFArray  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc refl_BlockHeapBlockJc;  //the just defined refl_
extern_C const ClassJc refl_BlockHeapBlockJc;
extern_C const ClassJc refl_ObjectJcREFArray;
extern_C const ClassJc refl_ObjectJc;
const struct Reflection_Fields_BlockHeapBlockJc_t
{ ObjectArrayJc head;
  FieldJc data[8];
} refl_Fields_BlockHeapBlockJc =
{ CONST_ObjectArrayJc(FieldJc, 8, OBJTYPE_FieldJc, null, &refl_Fields_BlockHeapBlockJc)
, {
    { "typeOrMaxRef"
    , 0   //no Array, no Bitfield
    , REFLECTION_uint16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc*)(0x1000))->typeOrMaxRef) -(int32)(BlockHeapBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc
    }
  , { "heapidxAndMaxref"
    , 0   //no Array, no Bitfield
    , REFLECTION_uint16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc*)(0x1000))->heapidxAndMaxref) -(int32)(BlockHeapBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc
    }
  , { "nextBlock"
    , 0   //no Array, no Bitfield
    , &refl_BlockHeapBlockJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc*)(0x1000))->nextBlock) -(int32)(BlockHeapBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc
    }
  , { "heap"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc*)(0x1000))->heap) -(int32)(BlockHeapBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc
    }
  , { "backRefs"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJcREFArray
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc*)(0x1000))->backRefs) -(int32)(BlockHeapBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc
    }
  , { "obj"
    , 0   //no Array, no Bitfield
    , &refl_ObjectJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc*)(0x1000))->obj) -(int32)(BlockHeapBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc
    }
  , { "sCreaterInfo"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc*)(0x1000))->sCreaterInfo) -(int32)(BlockHeapBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc
    }
  , { "timeCreation"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc*)(0x1000))->timeCreation) -(int32)(BlockHeapBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc
    }
} };


const ClassJc refl_BlockHeapBlockJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_BlockHeapBlockJc, &refl_ClassJc)
, "BlockHeapBlockJc"
, 0
, sizeof(BlockHeapBlockJc)
, (FieldJcArray const*)&refl_Fields_BlockHeapBlockJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc refl_BlockHeapWholeBlockJc;  //the just defined refl_
extern_C const ClassJc refl_BlockHeapBlockJc;
const struct Reflection_Fields_BlockHeapWholeBlockJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} refl_Fields_BlockHeapWholeBlockJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_BlockHeapWholeBlockJc)
, {
    { "blockCtrl"
    , 0   //no Array, no Bitfield
    , &refl_BlockHeapBlockJc
    , 0 //bitModifiers
    , (int16)((int32)(&((BlockHeapWholeBlockJc*)(0x1000))->blockCtrl) -(int32)(BlockHeapWholeBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapWholeBlockJc
    }
  , { "rest"
    , 0   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BlockHeapWholeBlockJc*)(0x1000))->rest) -(int32)(BlockHeapWholeBlockJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapWholeBlockJc
    }
} };


const ClassJc refl_BlockHeapWholeBlockJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_BlockHeapWholeBlockJc, &refl_ClassJc)
, "BlockHeapWholeBlockJc"
, 0
, sizeof(BlockHeapWholeBlockJc)
, (FieldJcArray const*)&refl_Fields_BlockHeapWholeBlockJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc refl_BlockHeapBlockJc_debugArray;  //the just defined refl_
extern_C const ClassJc refl_BlockHeapWholeBlockJc;
const struct Reflection_Fields_BlockHeapBlockJc_debugArray_t
{ ObjectArrayJc head;
  FieldJc data[1];
} refl_Fields_BlockHeapBlockJc_debugArray =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_BlockHeapBlockJc_debugArray)
, {
    { "block"
    , 100   //nrofArrayElements
    , &refl_BlockHeapWholeBlockJc
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BlockHeapBlockJc_debugArray*)(0x1000))->block) -(int32)(BlockHeapBlockJc_debugArray*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_BlockHeapBlockJc_debugArray
    }
} };


const ClassJc refl_BlockHeapBlockJc_debugArray =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_BlockHeapBlockJc_debugArray, &refl_ClassJc)
, "BlockHeapBlockJc_debugArray"
, 0
, sizeof(BlockHeapBlockJc_debugArray)
, (FieldJcArray const*)&refl_Fields_BlockHeapBlockJc_debugArray  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc refl_GarbageCollectorJc;  //the just defined refl_
extern_C const ClassJc refl_OS_TimeStamp;
extern_C const ClassJc refl_OS_TimeStamp;
extern_C const ClassJc refl_LogMessageFW;
const struct Reflection_Fields_GarbageCollectorJc_t
{ ObjectArrayJc head;
  FieldJc data[17];
} refl_Fields_GarbageCollectorJc =
{ CONST_ObjectArrayJc(FieldJc, 17, OBJTYPE_FieldJc, null, &refl_Fields_GarbageCollectorJc)
, {
    { "idxBlock"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->idxBlock) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "idxReportBuffer"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->idxReportBuffer) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "reportBuffer"
    , 1000   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->reportBuffer) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "testedHeap"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->testedHeap) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "testMethod"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->testMethod) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "countStep"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->countStep) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "bAbortTest"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->bAbortTest) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "bAbortTestBecauseUserCall"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->bAbortTestBecauseUserCall) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "dummy"
    , 2   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->dummy) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "ctFreeBlocks"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->ctFreeBlocks) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "ctNonGcBlocks"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->ctNonGcBlocks) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "ctFreedBlocks"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->ctFreedBlocks) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "ctUsedBlocks"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->ctUsedBlocks) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "startTime"
    , 0   //no Array, no Bitfield
    , &refl_OS_TimeStamp
    , 0 //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->startTime) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "endTime"
    , 0   //no Array, no Bitfield
    , &refl_OS_TimeStamp
    , 0 //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->endTime) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "log"
    , 0   //no Array, no Bitfield
    , &refl_LogMessageFW
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->log) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
  , { "kIdentMsgBase"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((GarbageCollectorJc*)(0x1000))->kIdentMsgBase) -(int32)(GarbageCollectorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &refl_GarbageCollectorJc
    }
} };


const ClassJc refl_GarbageCollectorJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_GarbageCollectorJc, &refl_ClassJc)
, "GarbageCollectorJc"
, 0
, sizeof(GarbageCollectorJc)
, (FieldJcArray const*)&refl_Fields_GarbageCollectorJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Reflection_BlockHeap.h"
