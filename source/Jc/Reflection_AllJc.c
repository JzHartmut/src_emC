
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "Jc/AbstractListJc.h"


extern_C const ClassJc reflection_AbstractCollectionJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_ListMapEntryJc;
extern_C const ClassJc reflection_ListMapEntryJc;
const struct Reflection_Fields_AbstractCollectionJc_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_AbstractCollectionJc =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_AbstractCollectionJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((AbstractCollectionJc*)(0x1000))->object) -(int32)(AbstractCollectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AbstractCollectionJc
    }
  , { "modCount"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((AbstractCollectionJc*)(0x1000))->modCount) -(int32)(AbstractCollectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AbstractCollectionJc
    }
  , { "nodePool"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((AbstractCollectionJc*)(0x1000))->nodePool) -(int32)(AbstractCollectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AbstractCollectionJc
    }
  , { "refFreeEntryPool"
    , 0   //no Array, no Bitfield
    , &reflection_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((AbstractCollectionJc*)(0x1000))->refFreeEntryPool) -(int32)(AbstractCollectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AbstractCollectionJc
    }
  , { "theFreeEntryPool"
    , 0   //no Array, no Bitfield
    , &reflection_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((AbstractCollectionJc*)(0x1000))->theFreeEntryPool) -(int32)(AbstractCollectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AbstractCollectionJc
    }
} };


const ClassJc reflection_AbstractCollectionJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_AbstractCollectionJc, &reflection_ClassJc)
, "AbstractCollectionJc"
, 0
, sizeof(AbstractCollectionJc)
, (FieldJcArray const*)&reflection_Fields_AbstractCollectionJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Jc/ArraysJc.h"

#include "Jc/ComparatorJc.h"


extern_C const ClassJc reflection_ComparatorJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_ComparatorJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_ComparatorJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_ComparatorJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ComparatorJc*)(0x1000))->object) -(int32)(ComparatorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ComparatorJc
    }
} };


const ClassJc reflection_ComparatorJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ComparatorJc, &reflection_ClassJc)
, "ComparatorJc"
, 0
, sizeof(ComparatorJc)
, (FieldJcArray const*)&reflection_Fields_ComparatorJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Jc/ConcurrentLinkedQueueJc.h"


extern_C const ClassJc reflection_Node_ConcurrentLinkedQueueJc;  //the just defined reflection_
extern_C const ClassJc reflection_Node_ConcurrentLinkedQueueJc;
const struct Reflection_Fields_Node_ConcurrentLinkedQueueJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_Node_ConcurrentLinkedQueueJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_Node_ConcurrentLinkedQueueJc)
, {
    { "item"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((Node_ConcurrentLinkedQueueJc*)(0x1000))->item) -(int32)(Node_ConcurrentLinkedQueueJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Node_ConcurrentLinkedQueueJc
    }
  , { "next"
    , 0   //no Array, no Bitfield
    , &reflection_Node_ConcurrentLinkedQueueJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Node_ConcurrentLinkedQueueJc*)(0x1000))->next) -(int32)(Node_ConcurrentLinkedQueueJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Node_ConcurrentLinkedQueueJc
    }
} };


const ClassJc reflection_Node_ConcurrentLinkedQueueJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Node_ConcurrentLinkedQueueJc, &reflection_ClassJc)
, "Node_ConcurrentLinkedQueueJc"
, 0
, sizeof(Node_ConcurrentLinkedQueueJc)
, (FieldJcArray const*)&reflection_Fields_Node_ConcurrentLinkedQueueJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ConcurrentLinkedQueueJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_Node_ConcurrentLinkedQueueJc;
extern_C const ClassJc reflection_Node_ConcurrentLinkedQueueJc;
extern_C const ClassJc reflection_Node_ConcurrentLinkedQueueJc;
extern_C const ClassJc reflection_Node_ConcurrentLinkedQueueJc;
const struct Reflection_Fields_ConcurrentLinkedQueueJc_s_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_ConcurrentLinkedQueueJc_s =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_ConcurrentLinkedQueueJc_s)
, {
    { "head"
    , 0   //no Array, no Bitfield
    , &reflection_Node_ConcurrentLinkedQueueJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ConcurrentLinkedQueueJc_s*)(0x1000))->head) -(int32)(ConcurrentLinkedQueueJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ConcurrentLinkedQueueJc_s
    }
  , { "tail"
    , 0   //no Array, no Bitfield
    , &reflection_Node_ConcurrentLinkedQueueJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ConcurrentLinkedQueueJc_s*)(0x1000))->tail) -(int32)(ConcurrentLinkedQueueJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ConcurrentLinkedQueueJc_s
    }
  , { "refFreeNodePool"
    , 0   //no Array, no Bitfield
    , &reflection_Node_ConcurrentLinkedQueueJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ConcurrentLinkedQueueJc_s*)(0x1000))->refFreeNodePool) -(int32)(ConcurrentLinkedQueueJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ConcurrentLinkedQueueJc_s
    }
  , { "theFreeNodePool"
    , 0   //no Array, no Bitfield
    , &reflection_Node_ConcurrentLinkedQueueJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ConcurrentLinkedQueueJc_s*)(0x1000))->theFreeNodePool) -(int32)(ConcurrentLinkedQueueJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ConcurrentLinkedQueueJc_s
    }
} };


const ClassJc reflection_ConcurrentLinkedQueueJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ConcurrentLinkedQueueJc_s, &reflection_ClassJc)
, "ConcurrentLinkedQueueJc_s"
, 0
, sizeof(ConcurrentLinkedQueueJc_s)
, (FieldJcArray const*)&reflection_Fields_ConcurrentLinkedQueueJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/DateJc.h"


extern_C const ClassJc reflection_DateValuesJc;  //the just defined reflection_
const struct Reflection_Fields_DateValuesJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_DateValuesJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_DateValuesJc)
, {
    { "time_nsec"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((DateValuesJc*)(0x1000))->time_nsec) -(int32)(DateValuesJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_DateValuesJc
    }
  , { "time_sec"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((DateValuesJc*)(0x1000))->time_sec) -(int32)(DateValuesJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_DateValuesJc
    }
} };


const ClassJc reflection_DateValuesJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_DateValuesJc, &reflection_ClassJc)
, "DateValuesJc"
, 0
, sizeof(DateValuesJc)
, (FieldJcArray const*)&reflection_Fields_DateValuesJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_DateJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_OS_TimeStamp;
const struct Reflection_Fields_DateJc_s_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_DateJc_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_DateJc_s)
, {
    { "val"
    , 0   //no Array, no Bitfield
    , &reflection_OS_TimeStamp
    , 0 //bitModifiers
    , (int16)((int32)(&((DateJc_s*)(0x1000))->val) -(int32)(DateJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_DateJc_s
    }
} };


const ClassJc reflection_DateJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_DateJc_s, &reflection_ClassJc)
, "DateJc_s"
, 0
, sizeof(DateJc_s)
, (FieldJcArray const*)&reflection_Fields_DateJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_SimpleDateFormatJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_StringJc;
const struct Reflection_Fields_SimpleDateFormatJc_s_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_SimpleDateFormatJc_s =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_SimpleDateFormatJc_s)
, {
    { "sFormat"
    , 0   //no Array, no Bitfield
    , &reflection_StringJc
    , 0 //bitModifiers
    , (int16)((int32)(&((SimpleDateFormatJc_s*)(0x1000))->sFormat) -(int32)(SimpleDateFormatJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDateFormatJc_s
    }
  , { "timeZoneAdjustHours"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((SimpleDateFormatJc_s*)(0x1000))->timeZoneAdjustHours) -(int32)(SimpleDateFormatJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDateFormatJc_s
    }
} };


const ClassJc reflection_SimpleDateFormatJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_SimpleDateFormatJc_s, &reflection_ClassJc)
, "SimpleDateFormatJc_s"
, 0
, sizeof(SimpleDateFormatJc_s)
, (FieldJcArray const*)&reflection_Fields_SimpleDateFormatJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_TextFieldPositionJc_s;  //the just defined reflection_
const struct Reflection_Fields_TextFieldPositionJc_s_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_TextFieldPositionJc_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_TextFieldPositionJc_s)
, {
    { "x"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TextFieldPositionJc_s*)(0x1000))->x) -(int32)(TextFieldPositionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TextFieldPositionJc_s
    }
} };


const ClassJc reflection_TextFieldPositionJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TextFieldPositionJc_s, &reflection_ClassJc)
, "TextFieldPositionJc_s"
, 0
, sizeof(TextFieldPositionJc_s)
, (FieldJcArray const*)&reflection_Fields_TextFieldPositionJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/LocaleJc.h"


extern_C const ClassJc reflection_LocaleJc_s;  //the just defined reflection_
const struct Reflection_Fields_LocaleJc_s_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_LocaleJc_s =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_LocaleJc_s)
, {
    { "language"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((LocaleJc_s*)(0x1000))->language) -(int32)(LocaleJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_LocaleJc_s
    }
  , { "country"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((LocaleJc_s*)(0x1000))->country) -(int32)(LocaleJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_LocaleJc_s
    }
} };


const ClassJc reflection_LocaleJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_LocaleJc_s, &reflection_ClassJc)
, "LocaleJc_s"
, 0
, sizeof(LocaleJc_s)
, (FieldJcArray const*)&reflection_Fields_LocaleJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/SystemJc.h"


extern_C const ClassJc reflection_SystemJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_SystemJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_SystemJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_SystemJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((SystemJc*)(0x1000))->object) -(int32)(SystemJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SystemJc
    }
} };


const ClassJc reflection_SystemJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_SystemJc, &reflection_ClassJc)
, "SystemJc"
, 0
, sizeof(SystemJc)
, (FieldJcArray const*)&reflection_Fields_SystemJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Jc/ObjectJc.h"


extern_C const ClassJc reflection_ObjectArrayJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_ObjectArrayJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_ObjectArrayJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_ObjectArrayJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ObjectArrayJc*)(0x1000))->object) -(int32)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectArrayJc
    }
  , { "sizeElement"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectArrayJc*)(0x1000))->sizeElement) -(int32)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectArrayJc
    }
  , { "mode"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectArrayJc*)(0x1000))->mode) -(int32)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectArrayJc
    }
  , { "length"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectArrayJc*)(0x1000))->length) -(int32)(ObjectArrayJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectArrayJc
    }
} };


const ClassJc reflection_ObjectArrayJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectArrayJc, &reflection_ClassJc)
, "ObjectArrayJc"
, 0
, sizeof(ObjectArrayJc)
, (FieldJcArray const*)&reflection_Fields_ObjectArrayJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_int8ARRAY;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectArrayJc;
const struct Reflection_Fields_int8ARRAY_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_int8ARRAY =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_int8ARRAY)
, {
    { "head"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectArrayJc
    , 0 //bitModifiers
    , (int16)((int32)(&((int8ARRAY*)(0x1000))->head) -(int32)(int8ARRAY*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_int8ARRAY
    }
  , { "data"
    , 256   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((int8ARRAY*)(0x1000))->data) -(int32)(int8ARRAY*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_int8ARRAY
    }
} };


const ClassJc reflection_int8ARRAY =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_int8ARRAY, &reflection_ClassJc)
, "int8ARRAY"
, 0
, sizeof(int8ARRAY)
, (FieldJcArray const*)&reflection_Fields_int8ARRAY  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/LinkedListJc.h"


extern_C const ClassJc reflection_ListItr_LinkedListJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_LinkedListJc;
extern_C const ClassJc reflection_ListMapEntryJc;
extern_C const ClassJc reflection_ListMapEntryJc;
const struct Reflection_Fields_ListItr_LinkedListJc_t
{ ObjectArrayJc head;
  FieldJc data[6];
} reflection_Fields_ListItr_LinkedListJc =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &reflection_Fields_ListItr_LinkedListJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ListItr_LinkedListJc*)(0x1000))->object) -(int32)(ListItr_LinkedListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListItr_LinkedListJc
    }
  , { "outer"
    , 0   //no Array, no Bitfield
    , &reflection_LinkedListJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ListItr_LinkedListJc*)(0x1000))->outer) -(int32)(ListItr_LinkedListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListItr_LinkedListJc
    }
  , { "lastReturned"
    , 0   //no Array, no Bitfield
    , &reflection_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ListItr_LinkedListJc*)(0x1000))->lastReturned) -(int32)(ListItr_LinkedListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListItr_LinkedListJc
    }
  , { "next"
    , 0   //no Array, no Bitfield
    , &reflection_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ListItr_LinkedListJc*)(0x1000))->next) -(int32)(ListItr_LinkedListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListItr_LinkedListJc
    }
  , { "nextIndex"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ListItr_LinkedListJc*)(0x1000))->nextIndex) -(int32)(ListItr_LinkedListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListItr_LinkedListJc
    }
  , { "expectedModCount"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ListItr_LinkedListJc*)(0x1000))->expectedModCount) -(int32)(ListItr_LinkedListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListItr_LinkedListJc
    }
} };


const ClassJc reflection_ListItr_LinkedListJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ListItr_LinkedListJc, &reflection_ClassJc)
, "ListItr_LinkedListJc"
, 0
, sizeof(ListItr_LinkedListJc)
, (FieldJcArray const*)&reflection_Fields_ListItr_LinkedListJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_LinkedListJcD;  //the just defined reflection_
extern_C const ClassJc reflection_ListMapEntryJc;
const struct Reflection_Fields_LinkedListJcD_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_LinkedListJcD =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_LinkedListJcD)
, {
    { "header"
    , 0   //no Array, no Bitfield
    , &reflection_ListMapEntryJc
    , 0 //bitModifiers
    , (int16)((int32)(&((LinkedListJcD*)(0x1000))->header) -(int32)(LinkedListJcD*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_LinkedListJcD
    }
  , { "size"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((LinkedListJcD*)(0x1000))->size) -(int32)(LinkedListJcD*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_LinkedListJcD
    }
} };


const ClassJc reflection_LinkedListJcD =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_LinkedListJcD, &reflection_ClassJc)
, "LinkedListJcD"
, 0
, sizeof(LinkedListJcD)
, (FieldJcArray const*)&reflection_Fields_LinkedListJcD  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_LinkedListJc;  //the just defined reflection_
extern_C const ClassJc reflection_LinkedListJcD;
const struct Reflection_Fields_LinkedListJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_LinkedListJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_LinkedListJc)
, {
    { "data"
    , 0   //no Array, no Bitfield
    , &reflection_LinkedListJcD
    , 0 //bitModifiers
    , (int16)((int32)(&((LinkedListJc*)(0x1000))->data) -(int32)(LinkedListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_LinkedListJc
    }
} };


const ClassJc reflection_LinkedListJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_LinkedListJc, &reflection_ClassJc)
, "LinkedListJc"
, 0
, sizeof(LinkedListJc)
, (FieldJcArray const*)&reflection_Fields_LinkedListJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/ListIteratorJc.h"

#include "Jc/ListJc.h"


extern_C const ClassJc reflection_ListJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_ListJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_ListJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_ListJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ListJc*)(0x1000))->object) -(int32)(ListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListJc
    }
} };


const ClassJc reflection_ListJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ListJc, &reflection_ClassJc)
, "ListJc"
, 0
, sizeof(ListJc)
, (FieldJcArray const*)&reflection_Fields_ListJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_IteratorJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_IteratorJc_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_IteratorJc =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_IteratorJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((IteratorJc*)(0x1000))->object) -(int32)(IteratorJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_IteratorJc
    }
} };


const ClassJc reflection_IteratorJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_IteratorJc, &reflection_ClassJc)
, "IteratorJc"
, 0
, sizeof(IteratorJc)
, (FieldJcArray const*)&reflection_Fields_IteratorJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Jc/ListMapEntryJc.h"


extern_C const ClassJc reflection_ListMapEntryJc;  //the just defined reflection_
extern_C const ClassJc reflection_ListMapEntryJc;
extern_C const ClassJc reflection_ListMapEntryJc;
extern_C const ClassJc reflection_ListMapEntryJc;
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_ListMapEntryJc_t
{ ObjectArrayJc head;
  FieldJc data[6];
} reflection_Fields_ListMapEntryJc =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &reflection_Fields_ListMapEntryJc)
, {
    { "parent"
    , 0   //no Array, no Bitfield
    , &reflection_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ListMapEntryJc*)(0x1000))->parent) -(int32)(ListMapEntryJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListMapEntryJc
    }
  , { "previous"
    , 0   //no Array, no Bitfield
    , &reflection_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ListMapEntryJc*)(0x1000))->previous) -(int32)(ListMapEntryJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListMapEntryJc
    }
  , { "next"
    , 0   //no Array, no Bitfield
    , &reflection_ListMapEntryJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ListMapEntryJc*)(0x1000))->next) -(int32)(ListMapEntryJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListMapEntryJc
    }
  , { "allocater"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ListMapEntryJc*)(0x1000))->allocater) -(int32)(ListMapEntryJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListMapEntryJc
    }
  , { "key"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((ListMapEntryJc*)(0x1000))->key) -(int32)(ListMapEntryJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListMapEntryJc
    }
  , { "element"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((ListMapEntryJc*)(0x1000))->element) -(int32)(ListMapEntryJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListMapEntryJc
    }
} };


const ClassJc reflection_ListMapEntryJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ListMapEntryJc, &reflection_ClassJc)
, "ListMapEntryJc"
, 0
, sizeof(ListMapEntryJc)
, (FieldJcArray const*)&reflection_Fields_ListMapEntryJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/ReflectionJc.h"


extern_C const ClassJc reflection_FieldJc;  //the just defined reflection_
extern_C const ClassJc reflection_ClassJc;
extern_C const ClassJc reflection_ClassJc;
const struct Reflection_Fields_FieldJc_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_FieldJc =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_FieldJc)
, {
    { "name"
    , 30   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->name) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "nrofArrayElementsOrBitfield_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->nrofArrayElementsOrBitfield_) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "type_"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->type_) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "bitModifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->bitModifiers) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "position"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->position) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "offsetToObjectifcBase"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->offsetToObjectifcBase) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
  , { "declaringClass"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FieldJc*)(0x1000))->declaringClass) -(int32)(FieldJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FieldJc
    }
} };


const ClassJc reflection_FieldJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FieldJc, &reflection_ClassJc)
, "FieldJc"
, 0
, sizeof(FieldJc)
, (FieldJcArray const*)&reflection_Fields_FieldJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_MethodJc;  //the just defined reflection_
const struct Reflection_Fields_MethodJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_MethodJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_MethodJc)
, {
    { "name"
    , 32   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((MethodJc*)(0x1000))->name) -(int32)(MethodJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MethodJc
    }
  , { "bModifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((MethodJc*)(0x1000))->bModifiers) -(int32)(MethodJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MethodJc
    }
  , { "adress"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((MethodJc*)(0x1000))->adress) -(int32)(MethodJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MethodJc
    }
  , { "eType"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((MethodJc*)(0x1000))->eType) -(int32)(MethodJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MethodJc
    }
} };


const ClassJc reflection_MethodJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_MethodJc, &reflection_ClassJc)
, "MethodJc"
, 0
, sizeof(MethodJc)
, (FieldJcArray const*)&reflection_Fields_MethodJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ClassJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_MtblHeadJc;
const struct Reflection_Fields_ClassJc_t
{ ObjectArrayJc head;
  FieldJc data[10];
} reflection_Fields_ClassJc =
{ CONST_ObjectArrayJc(FieldJc, 10, OBJTYPE_FieldJc, null, &reflection_Fields_ClassJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->object) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "name"
    , 32   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->name) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "posObjectBase"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->posObjectBase) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "nSize"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->nSize) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "attributes"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->attributes) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "methods"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->methods) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "superClasses"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->superClasses) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "interfaces"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->interfaces) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "modifiers"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->modifiers) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
  , { "mtbl"
    , 0   //no Array, no Bitfield
    , &reflection_MtblHeadJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ClassJc*)(0x1000))->mtbl) -(int32)(ClassJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ClassJc
    }
} };


const ClassJc reflection_ClassJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ClassJc, &reflection_ClassJc)
, "ClassJc"
, 0
, sizeof(ClassJc)
, (FieldJcArray const*)&reflection_Fields_ClassJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_Reflection__ObjectJc;  //the just defined reflection_
extern_C const ClassJc reflection_ClassJc;
const struct Reflection_Fields_Reflection__ObjectJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_Reflection__ObjectJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_Reflection__ObjectJc)
, {
    { "clazz"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0 //bitModifiers
    , (int16)((int32)(&((Reflection__ObjectJc*)(0x1000))->clazz) -(int32)(Reflection__ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Reflection__ObjectJc
    }
  , { "vtbl"
    , 5   //nrofArrayElements
    , REFLECTION_void
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Reflection__ObjectJc*)(0x1000))->vtbl) -(int32)(Reflection__ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Reflection__ObjectJc
    }
} };


const ClassJc reflection_Reflection__ObjectJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Reflection__ObjectJc, &reflection_ClassJc)
, "Reflection__ObjectJc"
, 0
, sizeof(Reflection__ObjectJc)
, (FieldJcArray const*)&reflection_Fields_Reflection__ObjectJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ExtReflectionJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_OS_PtrValue;
extern_C const ClassJc reflection_Data_ExtReflectionJc;
extern_C const ClassJc reflection_ClassJc;
const struct Reflection_Fields_ExtReflectionJc_s_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_ExtReflectionJc_s =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_ExtReflectionJc_s)
, {
    { "ct"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->ct) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
  , { "errorRelocationExtRefl"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->errorRelocationExtRefl) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
  , { "extReflectionBuffer"
    , 0   //no Array, no Bitfield
    , &reflection_OS_PtrValue
    , 0 //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->extReflectionBuffer) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
  , { "extReflectionData"
    , 0   //no Array, no Bitfield
    , &reflection_Data_ExtReflectionJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->extReflectionData) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
  , { "extReflection"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| kObjectArrayJc_Modifier_reflectJc| kReferencedContainer_Modifier_reflectJc| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ExtReflectionJc_s*)(0x1000))->extReflection) -(int32)(ExtReflectionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExtReflectionJc_s
    }
} };


const ClassJc reflection_ExtReflectionJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ExtReflectionJc_s, &reflection_ClassJc)
, "ExtReflectionJc_s"
, 0
, sizeof(ExtReflectionJc_s)
, (FieldJcArray const*)&reflection_Fields_ExtReflectionJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_Data_ExtReflectionJc;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_ClassJc;
extern_C const ClassJc reflection_ClassJc;
const struct Reflection_Fields_Data_ExtReflectionJc_t
{ ObjectArrayJc head;
  FieldJc data[6];
} reflection_Fields_Data_ExtReflectionJc =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &reflection_Fields_Data_ExtReflectionJc)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->object) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "sign"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->sign) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "nrofRelocEntries"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->nrofRelocEntries) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "arrayClasses"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| kObjectArrayJc_Modifier_reflectJc| kReferencedContainer_Modifier_reflectJc| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->arrayClasses) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "classDataBlock"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->classDataBlock) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
  , { "relocateAddr"
    , 10   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Data_ExtReflectionJc*)(0x1000))->relocateAddr) -(int32)(Data_ExtReflectionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Data_ExtReflectionJc
    }
} };


const ClassJc reflection_Data_ExtReflectionJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Data_ExtReflectionJc, &reflection_ClassJc)
, "Data_ExtReflectionJc"
, 0
, sizeof(Data_ExtReflectionJc)
, (FieldJcArray const*)&reflection_Fields_Data_ExtReflectionJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Jc/ReflMemAccessJc.h"


extern_C const ClassJc reflection_Access1TxData_ReflMemAccessJc;  //the just defined reflection_
const struct Reflection_Fields_Access1TxData_ReflMemAccessJc_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_Access1TxData_ReflMemAccessJc =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_Access1TxData_ReflMemAccessJc)
, {
    { "cmd"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Access1TxData_ReflMemAccessJc*)(0x1000))->cmd) -(int32)(Access1TxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Access1TxData_ReflMemAccessJc
    }
  , { "address"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Access1TxData_ReflMemAccessJc*)(0x1000))->address) -(int32)(Access1TxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Access1TxData_ReflMemAccessJc
    }
  , { "input"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Access1TxData_ReflMemAccessJc*)(0x1000))->input) -(int32)(Access1TxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Access1TxData_ReflMemAccessJc
    }
} };


const ClassJc reflection_Access1TxData_ReflMemAccessJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Access1TxData_ReflMemAccessJc, &reflection_ClassJc)
, "Access1TxData_ReflMemAccessJc"
, 0
, sizeof(Access1TxData_ReflMemAccessJc)
, (FieldJcArray const*)&reflection_Fields_Access1TxData_ReflMemAccessJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_AccessTxData_ReflMemAccessJc;  //the just defined reflection_
extern_C const ClassJc reflection_Access1TxData_ReflMemAccessJc;
const struct Reflection_Fields_AccessTxData_ReflMemAccessJc_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_AccessTxData_ReflMemAccessJc =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_AccessTxData_ReflMemAccessJc)
, {
    { "heartBeat"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((AccessTxData_ReflMemAccessJc*)(0x1000))->heartBeat) -(int32)(AccessTxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AccessTxData_ReflMemAccessJc
    }
  , { "seqNrofData"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((AccessTxData_ReflMemAccessJc*)(0x1000))->seqNrofData) -(int32)(AccessTxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AccessTxData_ReflMemAccessJc
    }
  , { "data"
    , 10   //nrofArrayElements
    , &reflection_Access1TxData_ReflMemAccessJc
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((AccessTxData_ReflMemAccessJc*)(0x1000))->data) -(int32)(AccessTxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AccessTxData_ReflMemAccessJc
    }
} };


const ClassJc reflection_AccessTxData_ReflMemAccessJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_AccessTxData_ReflMemAccessJc, &reflection_ClassJc)
, "AccessTxData_ReflMemAccessJc"
, 0
, sizeof(AccessTxData_ReflMemAccessJc)
, (FieldJcArray const*)&reflection_Fields_AccessTxData_ReflMemAccessJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_Access1RxData_ReflMemAccessJc;  //the just defined reflection_
const struct Reflection_Fields_Access1RxData_ReflMemAccessJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_Access1RxData_ReflMemAccessJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_Access1RxData_ReflMemAccessJc)
, {
    { "lo"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Access1RxData_ReflMemAccessJc*)(0x1000))->lo) -(int32)(Access1RxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Access1RxData_ReflMemAccessJc
    }
  , { "hi"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Access1RxData_ReflMemAccessJc*)(0x1000))->hi) -(int32)(Access1RxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Access1RxData_ReflMemAccessJc
    }
} };


const ClassJc reflection_Access1RxData_ReflMemAccessJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Access1RxData_ReflMemAccessJc, &reflection_ClassJc)
, "Access1RxData_ReflMemAccessJc"
, 0
, sizeof(Access1RxData_ReflMemAccessJc)
, (FieldJcArray const*)&reflection_Fields_Access1RxData_ReflMemAccessJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_AccessRxData_ReflMemAccessJc;  //the just defined reflection_
extern_C const ClassJc reflection_Access1RxData_ReflMemAccessJc;
const struct Reflection_Fields_AccessRxData_ReflMemAccessJc_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_AccessRxData_ReflMemAccessJc =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_AccessRxData_ReflMemAccessJc)
, {
    { "heartBeat"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((AccessRxData_ReflMemAccessJc*)(0x1000))->heartBeat) -(int32)(AccessRxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AccessRxData_ReflMemAccessJc
    }
  , { "seqNrofData"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((AccessRxData_ReflMemAccessJc*)(0x1000))->seqNrofData) -(int32)(AccessRxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AccessRxData_ReflMemAccessJc
    }
  , { "data"
    , 10   //nrofArrayElements
    , &reflection_Access1RxData_ReflMemAccessJc
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((AccessRxData_ReflMemAccessJc*)(0x1000))->data) -(int32)(AccessRxData_ReflMemAccessJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_AccessRxData_ReflMemAccessJc
    }
} };


const ClassJc reflection_AccessRxData_ReflMemAccessJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_AccessRxData_ReflMemAccessJc, &reflection_ClassJc)
, "AccessRxData_ReflMemAccessJc"
, 0
, sizeof(AccessRxData_ReflMemAccessJc)
, (FieldJcArray const*)&reflection_Fields_AccessRxData_ReflMemAccessJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_MemAccessDebugJc;  //the just defined reflection_
const struct Reflection_Fields_MemAccessDebugJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_MemAccessDebugJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_MemAccessDebugJc)
, {
    { "cmd"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((MemAccessDebugJc*)(0x1000))->cmd) -(int32)(MemAccessDebugJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MemAccessDebugJc
    }
  , { "address"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((MemAccessDebugJc*)(0x1000))->address) -(int32)(MemAccessDebugJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MemAccessDebugJc
    }
  , { "input"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((MemAccessDebugJc*)(0x1000))->input) -(int32)(MemAccessDebugJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MemAccessDebugJc
    }
  , { "output"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((MemAccessDebugJc*)(0x1000))->output) -(int32)(MemAccessDebugJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MemAccessDebugJc
    }
} };


const ClassJc reflection_MemAccessDebugJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_MemAccessDebugJc, &reflection_ClassJc)
, "MemAccessDebugJc"
, 0
, sizeof(MemAccessDebugJc)
, (FieldJcArray const*)&reflection_Fields_MemAccessDebugJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_MemAccessArrayDebugJc;  //the just defined reflection_
extern_C const ClassJc reflection_MemAccessDebugJc;
const struct Reflection_Fields_MemAccessArrayDebugJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_MemAccessArrayDebugJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_MemAccessArrayDebugJc)
, {
    { "ix"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((MemAccessArrayDebugJc*)(0x1000))->ix) -(int32)(MemAccessArrayDebugJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MemAccessArrayDebugJc
    }
  , { "item"
    , 20   //nrofArrayElements
    , &reflection_MemAccessDebugJc
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((MemAccessArrayDebugJc*)(0x1000))->item) -(int32)(MemAccessArrayDebugJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MemAccessArrayDebugJc
    }
} };


const ClassJc reflection_MemAccessArrayDebugJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_MemAccessArrayDebugJc, &reflection_ClassJc)
, "MemAccessArrayDebugJc"
, 0
, sizeof(MemAccessArrayDebugJc)
, (FieldJcArray const*)&reflection_Fields_MemAccessArrayDebugJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/FileIoJc.h"


extern_C const ClassJc reflection_FileJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_FileDescription_OSAL;
const struct Reflection_Fields_FileJc_s_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_FileJc_s =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_FileJc_s)
, {
    { "fileDescription"
    , 0   //no Array, no Bitfield
    , &reflection_FileDescription_OSAL
    , 0 //bitModifiers
    , (int16)((int32)(&((FileJc_s*)(0x1000))->fileDescription) -(int32)(FileJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileJc_s
    }
  , { "_additionalBuffer_"
    , 0   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileJc_s*)(0x1000))->_additionalBuffer_) -(int32)(FileJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileJc_s
    }
} };


const ClassJc reflection_FileJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FileJc_s, &reflection_ClassJc)
, "FileJc_s"
, 0
, sizeof(FileJc_s)
, (FieldJcArray const*)&reflection_Fields_FileJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_OutputStreamJc_s;  //the just defined reflection_
const ClassJc reflection_OutputStreamJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_OutputStreamJc_s, &reflection_ClassJc)
, "OutputStreamJc_s"
, 0
, sizeof(OutputStreamJc_s)
, null  //attributes
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_FileOutputStreamJc_s;  //the just defined reflection_
const struct Reflection_Fields_FileOutputStreamJc_s_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_FileOutputStreamJc_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_FileOutputStreamJc_s)
, {
    { "file"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileOutputStreamJc_s*)(0x1000))->file) -(int32)(FileOutputStreamJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileOutputStreamJc_s
    }
} };


const ClassJc reflection_FileOutputStreamJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FileOutputStreamJc_s, &reflection_ClassJc)
, "FileOutputStreamJc_s"
, 0
, sizeof(FileOutputStreamJc_s)
, (FieldJcArray const*)&reflection_Fields_FileOutputStreamJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_FileWriterJc_s;  //the just defined reflection_
const struct Reflection_Fields_FileWriterJc_s_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_FileWriterJc_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_FileWriterJc_s)
, {
    { "file"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileWriterJc_s*)(0x1000))->file) -(int32)(FileWriterJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileWriterJc_s
    }
} };


const ClassJc reflection_FileWriterJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FileWriterJc_s, &reflection_ClassJc)
, "FileWriterJc_s"
, 0
, sizeof(FileWriterJc_s)
, (FieldJcArray const*)&reflection_Fields_FileWriterJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_FileReaderJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_FileReaderJc_s_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_FileReaderJc_s =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_FileReaderJc_s)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((FileReaderJc_s*)(0x1000))->object) -(int32)(FileReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileReaderJc_s
    }
  , { "file_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileReaderJc_s*)(0x1000))->file_) -(int32)(FileReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileReaderJc_s
    }
  , { "lenFile_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileReaderJc_s*)(0x1000))->lenFile_) -(int32)(FileReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileReaderJc_s
    }
  , { "bEof_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileReaderJc_s*)(0x1000))->bEof_) -(int32)(FileReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileReaderJc_s
    }
  , { "modCount_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileReaderJc_s*)(0x1000))->modCount_) -(int32)(FileReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileReaderJc_s
    }
} };


const ClassJc reflection_FileReaderJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FileReaderJc_s, &reflection_ClassJc)
, "FileReaderJc_s"
, 0
, sizeof(FileReaderJc_s)
, (FieldJcArray const*)&reflection_Fields_FileReaderJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_BufferedReaderJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_OS_PtrValue;
extern_C const ClassJc reflection_FileReaderJc_s;
const struct Reflection_Fields_BufferedReaderJc_s_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_BufferedReaderJc_s =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_BufferedReaderJc_s)
, {
    { "object"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0 //bitModifiers
    , (int16)((int32)(&((BufferedReaderJc_s*)(0x1000))->object) -(int32)(BufferedReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_BufferedReaderJc_s
    }
  , { "lenBuffer"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BufferedReaderJc_s*)(0x1000))->lenBuffer) -(int32)(BufferedReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_BufferedReaderJc_s
    }
  , { "lenLine"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BufferedReaderJc_s*)(0x1000))->lenLine) -(int32)(BufferedReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_BufferedReaderJc_s
    }
  , { "bFinish"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BufferedReaderJc_s*)(0x1000))->bFinish) -(int32)(BufferedReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_BufferedReaderJc_s
    }
  , { "buffer"
    , 0   //no Array, no Bitfield
    , &reflection_OS_PtrValue
    , 0 //bitModifiers
    , (int16)((int32)(&((BufferedReaderJc_s*)(0x1000))->buffer) -(int32)(BufferedReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_BufferedReaderJc_s
    }
  , { "input"
    , 0   //no Array, no Bitfield
    , &reflection_FileReaderJc_s
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((BufferedReaderJc_s*)(0x1000))->input) -(int32)(BufferedReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_BufferedReaderJc_s
    }
  , { "modCountInput"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((BufferedReaderJc_s*)(0x1000))->modCountInput) -(int32)(BufferedReaderJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_BufferedReaderJc_s
    }
} };


const ClassJc reflection_BufferedReaderJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_BufferedReaderJc_s, &reflection_ClassJc)
, "BufferedReaderJc_s"
, 0
, sizeof(BufferedReaderJc_s)
, (FieldJcArray const*)&reflection_Fields_BufferedReaderJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};



#include "Jc/ThreadJc.h"


extern_C const ClassJc reflection_RunnableJc_s;  //the just defined reflection_
const ClassJc reflection_RunnableJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_RunnableJc_s, &reflection_ClassJc)
, "RunnableJc_s"
, 0
, sizeof(RunnableJc_s)
, null  //attributes
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ThreadJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_StringJc;
const struct Reflection_Fields_ThreadJc_s_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_ThreadJc_s =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_ThreadJc_s)
, {
    { "hThread"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((ThreadJc_s*)(0x1000))->hThread) -(int32)(ThreadJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadJc_s
    }
  , { "name"
    , 0   //no Array, no Bitfield
    , &reflection_StringJc
    , 0 //bitModifiers
    , (int16)((int32)(&((ThreadJc_s*)(0x1000))->name) -(int32)(ThreadJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadJc_s
    }
  , { "target"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((ThreadJc_s*)(0x1000))->target) -(int32)(ThreadJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadJc_s
    }
  , { "stackSize"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ThreadJc_s*)(0x1000))->stackSize) -(int32)(ThreadJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadJc_s
    }
  , { "state"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ThreadJc_s*)(0x1000))->state) -(int32)(ThreadJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadJc_s
    }
  , { "nPriority"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ThreadJc_s*)(0x1000))->nPriority) -(int32)(ThreadJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadJc_s
    }
  , { "sCalledName"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ThreadJc_s*)(0x1000))->sCalledName) -(int32)(ThreadJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadJc_s
    }
} };


const ClassJc reflection_ThreadJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ThreadJc_s, &reflection_ClassJc)
, "ThreadJc_s"
, 0
, sizeof(ThreadJc_s)
, (FieldJcArray const*)&reflection_Fields_ThreadJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/FormatterJc.h"


extern_C const ClassJc reflection_FormatterJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_StringBuilderJcREF;
extern_C const ClassJc reflection_LocaleJcREF;
const struct Reflection_Fields_FormatterJc_s_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_FormatterJc_s =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_FormatterJc_s)
, {
    { "buffer"
    , 0   //no Array, no Bitfield
    , &reflection_StringBuilderJcREF
    , 0 //bitModifiers
    , (int16)((int32)(&((FormatterJc_s*)(0x1000))->buffer) -(int32)(FormatterJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FormatterJc_s
    }
  , { "locale"
    , 0   //no Array, no Bitfield
    , &reflection_LocaleJcREF
    , 0 //bitModifiers
    , (int16)((int32)(&((FormatterJc_s*)(0x1000))->locale) -(int32)(FormatterJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FormatterJc_s
    }
} };


const ClassJc reflection_FormatterJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FormatterJc_s, &reflection_ClassJc)
, "FormatterJc_s"
, 0
, sizeof(FormatterJc_s)
, (FieldJcArray const*)&reflection_Fields_FormatterJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/TimeZoneJc.h"


extern_C const ClassJc reflection_TimeZoneJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_StringJc;
const struct Reflection_Fields_TimeZoneJc_s_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_TimeZoneJc_s =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_TimeZoneJc_s)
, {
    { "diffHours"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeZoneJc_s*)(0x1000))->diffHours) -(int32)(TimeZoneJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeZoneJc_s
    }
  , { "diffMinutes"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeZoneJc_s*)(0x1000))->diffMinutes) -(int32)(TimeZoneJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeZoneJc_s
    }
  , { "name"
    , 0   //no Array, no Bitfield
    , &reflection_StringJc
    , 0 //bitModifiers
    , (int16)((int32)(&((TimeZoneJc_s*)(0x1000))->name) -(int32)(TimeZoneJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeZoneJc_s
    }
} };


const ClassJc reflection_TimeZoneJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TimeZoneJc_s, &reflection_ClassJc)
, "TimeZoneJc_s"
, 0
, sizeof(TimeZoneJc_s)
, (FieldJcArray const*)&reflection_Fields_TimeZoneJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "MsgDisp/VaArgBuffer.h"


extern_C const ClassJc reflection_VaArgBuffer_Data_s;  //the just defined reflection_
const struct Reflection_Fields_VaArgBuffer_Data_s_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_VaArgBuffer_Data_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_VaArgBuffer_Data_s)
, {
    { "v"
    , 17   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((VaArgBuffer_Data_s*)(0x1000))->v) -(int32)(VaArgBuffer_Data_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_VaArgBuffer_Data_s
    }
} };


const ClassJc reflection_VaArgBuffer_Data_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_VaArgBuffer_Data_s, &reflection_ClassJc)
, "VaArgBuffer_Data_s"
, 0
, sizeof(VaArgBuffer_Data_s)
, (FieldJcArray const*)&reflection_Fields_VaArgBuffer_Data_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_VaArgBuffer;  //the just defined reflection_
extern_C const ClassJc reflection_VaArgBuffer_Data_s;
const struct Reflection_Fields_VaArgBuffer_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_VaArgBuffer =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_VaArgBuffer)
, {
    { "sType"
    , 16   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((VaArgBuffer*)(0x1000))->sType) -(int32)(VaArgBuffer*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_VaArgBuffer
    }
  , { "data"
    , 0   //no Array, no Bitfield
    , &reflection_VaArgBuffer_Data_s
    , 0 //bitModifiers
    , (int16)((int32)(&((VaArgBuffer*)(0x1000))->data) -(int32)(VaArgBuffer*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_VaArgBuffer
    }
} };


const ClassJc reflection_VaArgBuffer =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_VaArgBuffer, &reflection_ClassJc)
, "VaArgBuffer"
, 0
, sizeof(VaArgBuffer)
, (FieldJcArray const*)&reflection_Fields_VaArgBuffer  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};


