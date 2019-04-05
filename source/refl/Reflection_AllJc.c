
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
    , REFLECTION_int32
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




extern_C const ClassJc reflection_SimpleDateFormatJc;  //the just defined reflection_
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
    , &reflection_SimpleDateFormatJc
    }
  , { "timeZoneAdjustHours"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((SimpleDateFormatJc_s*)(0x1000))->timeZoneAdjustHours) -(int32)(SimpleDateFormatJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_SimpleDateFormatJc
    }
} };


const ClassJc reflection_SimpleDateFormatJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_SimpleDateFormatJc, &reflection_ClassJc)
, "SimpleDateFormatJc_s"
, 0
, sizeof(SimpleDateFormatJc_s)
, (FieldJcArray const*)&reflection_Fields_SimpleDateFormatJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_TextFieldPositionJc;  //the just defined reflection_
const struct Reflection_Fields_TextFieldPositionJc_s_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_TextFieldPositionJc_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_TextFieldPositionJc_s)
, {
    { "x"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TextFieldPositionJc_s*)(0x1000))->x) -(int32)(TextFieldPositionJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TextFieldPositionJc
    }
} };


const ClassJc reflection_TextFieldPositionJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TextFieldPositionJc, &reflection_ClassJc)
, "TextFieldPositionJc_s"
, 0
, sizeof(TextFieldPositionJc_s)
, (FieldJcArray const*)&reflection_Fields_TextFieldPositionJc_s  //attributes and associations
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
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ListItr_LinkedListJc*)(0x1000))->nextIndex) -(int32)(ListItr_LinkedListJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ListItr_LinkedListJc
    }
  , { "expectedModCount"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
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
    , REFLECTION_int32
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



#include "Jc/OsWrapperJc.h"


extern_C const ClassJc reflection_HandleItem;  //the just defined reflection_
const struct Reflection_Fields_HandleItem_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_HandleItem =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_HandleItem)
, {
    { "handleMutex"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((HandleItem*)(0x1000))->handleMutex) -(int32)(HandleItem*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_HandleItem
    }
} };


const ClassJc reflection_HandleItem =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_HandleItem, &reflection_ClassJc)
, "HandleItem"
, 0
, sizeof(HandleItem)
, (FieldJcArray const*)&reflection_Fields_HandleItem  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_OsWrapperJc_s;  //the just defined reflection_
extern_C const ClassJc reflection_HandleItem;
extern_C const ClassJc reflection_HandleItem;
const struct Reflection_Fields_OsWrapperJc_s_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_OsWrapperJc_s =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_OsWrapperJc_s)
, {
    { "handleItemsJc"
    , 1024   //nrofArrayElements
    , &reflection_HandleItem
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((OsWrapperJc_s*)(0x1000))->handleItemsJc) -(int32)(OsWrapperJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_OsWrapperJc_s
    }
  , { "freeHandle"
    , 0   //no Array, no Bitfield
    , &reflection_HandleItem
    , 0 //bitModifiers
    , (int16)((int32)(&((OsWrapperJc_s*)(0x1000))->freeHandle) -(int32)(OsWrapperJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_OsWrapperJc_s
    }
  , { "nrofHandle"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((OsWrapperJc_s*)(0x1000))->nrofHandle) -(int32)(OsWrapperJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_OsWrapperJc_s
    }
} };


const ClassJc reflection_OsWrapperJc_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_OsWrapperJc_s, &reflection_ClassJc)
, "OsWrapperJc_s"
, 0
, sizeof(OsWrapperJc_s)
, (FieldJcArray const*)&reflection_Fields_OsWrapperJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};





#include "Jc/FormatterJc.h"


extern_C const ClassJc reflection_FormatterJc;  //the just defined reflection_
extern_C const ClassJc reflection_StringBuilderJcREF;
extern_C const ClassJc reflection_LocaleJcREF;
static const struct Reflection_Fields_FormatterJc_s_t
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
    , &reflection_FormatterJc
    }
  , { "locale"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0 //bitModifiers
    , (int16)((int32)(&((FormatterJc_s*)(0x1000))->locale) -(int32)(FormatterJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FormatterJc
    }
} };


const ClassJc reflection_FormatterJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FormatterJc, &reflection_ClassJc)
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


extern_C const ClassJc reflection_TimeZoneJc;  //the just defined reflection_
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
    , &reflection_TimeZoneJc
    }
  , { "diffMinutes"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeZoneJc_s*)(0x1000))->diffMinutes) -(int32)(TimeZoneJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeZoneJc
    }
  , { "name"
    , 0   //no Array, no Bitfield
    , &reflection_StringJc
    , 0 //bitModifiers
    , (int16)((int32)(&((TimeZoneJc_s*)(0x1000))->name) -(int32)(TimeZoneJc_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeZoneJc
    }
} };


const ClassJc reflection_TimeZoneJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TimeZoneJc, &reflection_ClassJc)
, "TimeZoneJc_s"
, 0
, sizeof(TimeZoneJc_s)
, (FieldJcArray const*)&reflection_Fields_TimeZoneJc_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Jc/StringJc_intern.h"

#include "emC/VaArgBuffer.h"


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
    , REFLECTION_int8
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


