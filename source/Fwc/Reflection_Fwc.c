
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "Fwc/fw_basic.h"

#include "Fwc/fw_Exception.h"


extern_C const ClassJc reflection_StacktraceElementJc;  //the just defined reflection_
const struct Reflection_Fields_StacktraceElementJc_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_StacktraceElementJc =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_StacktraceElementJc)
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
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StacktraceElementJc*)(0x1000))->line) -(int32)(StacktraceElementJc*)0x1000)
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




extern_C const ClassJc reflection_StacktraceThreadContext_s;  //the just defined reflection_
extern_C const ClassJc reflection_StacktraceJc;
extern_C const ClassJc reflection_StacktraceElementJc;
const struct Reflection_Fields_StacktraceThreadContext_s_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_StacktraceThreadContext_s =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_StacktraceThreadContext_s)
, {
    { "stacktrace"
    , 0   //no Array, no Bitfield
    , &reflection_StacktraceJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((StacktraceThreadContext_s*)(0x1000))->stacktrace) -(int32)(StacktraceThreadContext_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceThreadContext_s
    }
  , { "nrofEntriesStacktraceBuffer"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StacktraceThreadContext_s*)(0x1000))->nrofEntriesStacktraceBuffer) -(int32)(StacktraceThreadContext_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceThreadContext_s
    }
  , { "maxNrofEntrie_tacktraceBuffer"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StacktraceThreadContext_s*)(0x1000))->maxNrofEntriesStacktraceBuffer) -(int32)(StacktraceThreadContext_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceThreadContext_s
    }
  , { "stacktraceBuffer"
    , 100   //nrofArrayElements
    , &reflection_StacktraceElementJc
    , 0 |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((StacktraceThreadContext_s*)(0x1000))->stacktraceBuffer) -(int32)(StacktraceThreadContext_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceThreadContext_s
    }
} };


const ClassJc reflection_StacktraceThreadContext_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_StacktraceThreadContext_s, &reflection_ClassJc)
, "StacktraceThreadContext_s"
, 0
, sizeof(StacktraceThreadContext_s)
, (FieldJcArray const*)&reflection_Fields_StacktraceThreadContext_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_ExceptionJc;  //the just defined reflection_
extern_C const ClassJc reflection_StringJc;
extern_C const ClassJc reflection_StacktraceJc;
extern_C const ClassJc reflection_StacktraceElementJc;
const struct Reflection_Fields_ExceptionJc_t
{ ObjectArrayJc head;
  FieldJc data[6];
} reflection_Fields_ExceptionJc =
{ CONST_ObjectArrayJc(FieldJc, 6, OBJTYPE_FieldJc, null, &reflection_Fields_ExceptionJc)
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
  , { "backStacktrace"
    , 0   //no Array, no Bitfield
    , &reflection_StacktraceJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ExceptionJc*)(0x1000))->backStacktrace) -(int32)(ExceptionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExceptionJc
    }
  , { "nrofStacktraceEntries"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ExceptionJc*)(0x1000))->nrofStacktraceEntries) -(int32)(ExceptionJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ExceptionJc
    }
  , { "stacktraceEntries"
    , 0   //no Array, no Bitfield
    , &reflection_StacktraceElementJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ExceptionJc*)(0x1000))->stacktraceEntries) -(int32)(ExceptionJc*)0x1000)
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
  , { "exceptionNr"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TryObjectJc*)(0x1000))->exceptionNr) -(int32)(TryObjectJc*)0x1000)
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
extern_C const ClassJc reflection_StacktraceJc;
extern_C const ClassJc reflection_StacktraceElementJc;
extern_C const ClassJc reflection_TryObjectJc;
const struct Reflection_Fields_StacktraceJc_t
{ ObjectArrayJc head;
  FieldJc data[3];
} reflection_Fields_StacktraceJc =
{ CONST_ObjectArrayJc(FieldJc, 3, OBJTYPE_FieldJc, null, &reflection_Fields_StacktraceJc)
, {
    { "previous"
    , 0   //no Array, no Bitfield
    , &reflection_StacktraceJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((StacktraceJc*)(0x1000))->previous) -(int32)(StacktraceJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceJc
    }
  , { "entry"
    , 0   //no Array, no Bitfield
    , &reflection_StacktraceElementJc
    , 0 //bitModifiers
    , (int16)((int32)(&((StacktraceJc*)(0x1000))->entry) -(int32)(StacktraceJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StacktraceJc
    }
  , { "tryObject"
    , 0   //no Array, no Bitfield
    , &reflection_TryObjectJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((StacktraceJc*)(0x1000))->tryObject) -(int32)(StacktraceJc*)0x1000)
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



#include "Fwc/fw_Formatter.h"


extern_C const ClassJc reflection_ParseResultPrintfStyle_fwFormatter;  //the just defined reflection_
const struct Reflection_Fields_ParseResultPrintfStyle_fwFormatter_t
{ ObjectArrayJc head;
  FieldJc data[10];
} reflection_Fields_ParseResultPrintfStyle_fwFormatter =
{ CONST_ObjectArrayJc(FieldJc, 10, OBJTYPE_FieldJc, null, &reflection_Fields_ParseResultPrintfStyle_fwFormatter)
, {
    { "text-specifier"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->text.specifier) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "text-dummy"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->text.dummy) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "text-nrofChars"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->text.nrofChars) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "text-text"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->text.text) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "value-specifier"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->value.specifier) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "value-argument"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->value.argument) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "value-width"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->value.width) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "value-precision"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->value.precision) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "value-indexArg"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->value.indexArg) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
  , { "value-timeSpecifier"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ParseResultPrintfStyle_fwFormatter*)(0x1000))->value.timeSpecifier) -(int32)(ParseResultPrintfStyle_fwFormatter*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ParseResultPrintfStyle_fwFormatter
    }
} };


const ClassJc reflection_ParseResultPrintfStyle_fwFormatter =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ParseResultPrintfStyle_fwFormatter, &reflection_ClassJc)
, "ParseResultPr_Style_fwFormatter"
, 0
, sizeof(ParseResultPrintfStyle_fwFormatter)
, (FieldJcArray const*)&reflection_Fields_ParseResultPrintfStyle_fwFormatter  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Fwc/fw_LogMessage.h"


extern_C const ClassJc reflection_LogMessageFW_i;  //the just defined reflection_
const ClassJc reflection_LogMessageFW_i =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_LogMessageFW_i, &reflection_ClassJc)
, "LogMessageFW_i"
, 0
, sizeof(LogMessageFW_i)
, null  //attributes
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Fwc/fw_MemC.h"

#include "Fwc/fw_Readline.h"


extern_C const ClassJc reflection_ReadLine_Fwc;  //the just defined reflection_
const struct Reflection_Fields_ReadLine_Fwc_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_ReadLine_Fwc =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_ReadLine_Fwc)
, {
    { "file"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ReadLine_Fwc*)(0x1000))->file) -(int32)(ReadLine_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ReadLine_Fwc
    }
  , { "endOfFile"
    , 0   //no Array, no Bitfield
    , REFLECTION_bool
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ReadLine_Fwc*)(0x1000))->endOfFile) -(int32)(ReadLine_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ReadLine_Fwc
    }
  , { "buffer"
    , 4096   //nrofArrayElements
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ReadLine_Fwc*)(0x1000))->buffer) -(int32)(ReadLine_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ReadLine_Fwc
    }
  , { "posBuffer"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ReadLine_Fwc*)(0x1000))->posBuffer) -(int32)(ReadLine_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ReadLine_Fwc
    }
  , { "endBuffer"
    , 0   //no Array, no Bitfield
    , REFLECTION_int
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ReadLine_Fwc*)(0x1000))->endBuffer) -(int32)(ReadLine_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ReadLine_Fwc
    }
} };


const ClassJc reflection_ReadLine_Fwc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ReadLine_Fwc, &reflection_ClassJc)
, "ReadLine_Fwc"
, 0
, sizeof(ReadLine_Fwc)
, (FieldJcArray const*)&reflection_Fields_ReadLine_Fwc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Fwc/fw_SimpleC.h"


extern_C const ClassJc reflection_Int32Array256;  //the just defined reflection_
const struct Reflection_Fields_Int32Array256_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_Int32Array256 =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_Int32Array256)
, {
    { "data"
    , 256   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Int32Array256*)(0x1000))->data) -(int32)(Int32Array256*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Int32Array256
    }
} };


const ClassJc reflection_Int32Array256 =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Int32Array256, &reflection_ClassJc)
, "Int32Array256"
, 0
, sizeof(Int32Array256)
, (FieldJcArray const*)&reflection_Fields_Int32Array256  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_FloatArray256;  //the just defined reflection_
const struct Reflection_Fields_FloatArray256_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_FloatArray256 =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_FloatArray256)
, {
    { "data"
    , 256   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FloatArray256*)(0x1000))->data) -(int32)(FloatArray256*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FloatArray256
    }
} };


const ClassJc reflection_FloatArray256 =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FloatArray256, &reflection_ClassJc)
, "FloatArray256"
, 0
, sizeof(FloatArray256)
, (FieldJcArray const*)&reflection_Fields_FloatArray256  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_FloatArray20;  //the just defined reflection_
const struct Reflection_Fields_FloatArray20_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_FloatArray20 =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_FloatArray20)
, {
    { "data"
    , 20   //nrofArrayElements
    , REFLECTION_float
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FloatArray20*)(0x1000))->data) -(int32)(FloatArray20*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FloatArray20
    }
} };


const ClassJc reflection_FloatArray20 =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FloatArray20, &reflection_ClassJc)
, "FloatArray20"
, 0
, sizeof(FloatArray20)
, (FieldJcArray const*)&reflection_Fields_FloatArray20  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Fwc/fw_String.h"

#include "Fwc/fw_ThreadContext.h"


extern_C const ClassJc reflection_ThreadContextFW_s;  //the just defined reflection_
extern_C const ClassJc reflection_OS_PtrValue;
extern_C const ClassJc reflection_StacktraceThreadContext_s;
const struct Reflection_Fields_ThreadContextFW_s_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_ThreadContextFW_s =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_ThreadContextFW_s)
, {
    { "bufferInThreadContext"
    , 0   //no Array, no Bitfield
    , &reflection_OS_PtrValue
    , 0 //bitModifiers
    , (int16)((int32)(&((ThreadContextFW_s*)(0x1000))->bufferInThreadContext) -(int32)(ThreadContextFW_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContextFW_s
    }
  , { "blockHeap"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ThreadContextFW_s*)(0x1000))->blockHeap) -(int32)(ThreadContextFW_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContextFW_s
    }
  , { "mode"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ThreadContextFW_s*)(0x1000))->mode) -(int32)(ThreadContextFW_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContextFW_s
    }
  , { "topmemAddrOfStack"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ThreadContextFW_s*)(0x1000))->topmemAddrOfStack) -(int32)(ThreadContextFW_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContextFW_s
    }
  , { "stacktraceThreadContext"
    , 0   //no Array, no Bitfield
    , &reflection_StacktraceThreadContext_s
    , 0 //bitModifiers
    , (int16)((int32)(&((ThreadContextFW_s*)(0x1000))->stacktraceThreadContext) -(int32)(ThreadContextFW_s*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ThreadContextFW_s
    }
} };


const ClassJc reflection_ThreadContextFW_s =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ThreadContextFW_s, &reflection_ClassJc)
, "ThreadContextFW_s"
, 0
, sizeof(ThreadContextFW_s)
, (FieldJcArray const*)&reflection_Fields_ThreadContextFW_s  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Fwc/fw_timeconversions.h"


extern_C const ClassJc reflection_TimeBytes_Fwc;  //the just defined reflection_
const struct Reflection_Fields_TimeBytes_Fwc_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_TimeBytes_Fwc =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_TimeBytes_Fwc)
, {
    { "year"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeBytes_Fwc*)(0x1000))->year) -(int32)(TimeBytes_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeBytes_Fwc
    }
  , { "month"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeBytes_Fwc*)(0x1000))->month) -(int32)(TimeBytes_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeBytes_Fwc
    }
  , { "day"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeBytes_Fwc*)(0x1000))->day) -(int32)(TimeBytes_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeBytes_Fwc
    }
  , { "hour"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeBytes_Fwc*)(0x1000))->hour) -(int32)(TimeBytes_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeBytes_Fwc
    }
  , { "minute"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeBytes_Fwc*)(0x1000))->minute) -(int32)(TimeBytes_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeBytes_Fwc
    }
  , { "sec"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeBytes_Fwc*)(0x1000))->sec) -(int32)(TimeBytes_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeBytes_Fwc
    }
  , { "weekInYear"
    , 0   //no Array, no Bitfield
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((TimeBytes_Fwc*)(0x1000))->weekInYear) -(int32)(TimeBytes_Fwc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_TimeBytes_Fwc
    }
} };


const ClassJc reflection_TimeBytes_Fwc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_TimeBytes_Fwc, &reflection_ClassJc)
, "TimeBytes_Fwc"
, 0
, sizeof(TimeBytes_Fwc)
, (FieldJcArray const*)&reflection_Fields_TimeBytes_Fwc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Fwc/fw_Va_list.h"


extern_C const ClassJc reflection_Va_listFW;  //the just defined reflection_
const struct Reflection_Fields_Va_listFW_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_Va_listFW =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_Va_listFW)
, {
    { "typeArgs"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((Va_listFW*)(0x1000))->typeArgs) -(int32)(Va_listFW*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Va_listFW
    }
  , { "args"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((Va_listFW*)(0x1000))->args) -(int32)(Va_listFW*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_Va_listFW
    }
} };


const ClassJc reflection_Va_listFW =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_Va_listFW, &reflection_ClassJc)
, "Va_listFW"
, 0
, sizeof(Va_listFW)
, (FieldJcArray const*)&reflection_Fields_Va_listFW  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "Fwc/objectBaseC.h"


extern_C const ClassJc reflection_ObjectJc;  //the just defined reflection_
extern_C const ClassJc reflection_ClassJc;
extern_C const ClassJc reflection_ObjectJc;
const struct Reflection_Fields_ObjectJc_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_ObjectJc =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_ObjectJc)
, {
    { "objectIdentSize"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->objectIdentSize) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "ownAddress"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->ownAddress) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "offsetToStartAddr"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->offsetToStartAddr) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "idSyncHandles"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->idSyncHandles) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "reflectionClass"
    , 0   //no Array, no Bitfield
    , &reflection_ClassJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->reflectionClass) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "memoryMng"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc
    , 0| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->memoryMng) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
  , { "dummy"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((ObjectJc*)(0x1000))->dummy) -(int32)(ObjectJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJc
    }
} };


const ClassJc reflection_ObjectJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc)
, "ObjectJc"
, 0
, sizeof(ObjectJc)
, (FieldJcArray const*)&reflection_Fields_ObjectJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0  |mObjectJc_Modifier_reflectJc
};




extern_C const ClassJc reflection_MtblHeadJc;  //the just defined reflection_
const struct Reflection_Fields_MtblHeadJc_t
{ ObjectArrayJc head;
  FieldJc data[2];
} reflection_Fields_MtblHeadJc =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_MtblHeadJc)
, {
    { "sign"
    , 0   //no Array, no Bitfield
    , REFLECTION_char
    , (1<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((MtblHeadJc*)(0x1000))->sign) -(int32)(MtblHeadJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MtblHeadJc
    }
  , { "sizeTable"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((MtblHeadJc*)(0x1000))->sizeTable) -(int32)(MtblHeadJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_MtblHeadJc
    }
} };


const ClassJc reflection_MtblHeadJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_MtblHeadJc, &reflection_ClassJc)
, "MtblHeadJc"
, 0
, sizeof(MtblHeadJc)
, (FieldJcArray const*)&reflection_Fields_MtblHeadJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};


