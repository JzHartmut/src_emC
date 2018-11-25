
/*This file is generated from Header2Reflection. */
#define protected public  //only active inside this compilation unit
#define private public    //  to enable the access to all elements.
#include <Jc/ReflectionJc.h>
#include <stddef.h>
#include "OSAL/os_AtomicAccess.h"

#include "OSAL/os_endian.h"

#include "OSAL/os_error.h"

#include "OSAL/os_file.h"

#include <genRefl/OSAL/os_time.crefl>


extern_C const ClassJc reflection_FileDescription_OSAL;  //the just defined reflection_
extern_C const ClassJc reflection_OS_TimeStamp;
const struct Reflection_Fields_FileDescription_OSAL_t
{ ObjectArrayJc head;
  FieldJc data[7];
} reflection_Fields_FileDescription_OSAL =
{ CONST_ObjectArrayJc(FieldJc, 7, OBJTYPE_FieldJc, null, &reflection_Fields_FileDescription_OSAL)
, {
    { "fileLength"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileDescription_OSAL*)(0x1000))->fileLength) -(int32)(FileDescription_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileDescription_OSAL
    }
  , { "flags"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileDescription_OSAL*)(0x1000))->flags) -(int32)(FileDescription_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileDescription_OSAL
    }
  , { "timeChanged"
    , 0   //no Array, no Bitfield
    , &reflection_OS_TimeStamp
    , 0 //bitModifiers
    , (int16)((int32)(&((FileDescription_OSAL*)(0x1000))->timeChanged) -(int32)(FileDescription_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileDescription_OSAL
    }
  , { "ptr1"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FileDescription_OSAL*)(0x1000))->ptr1) -(int32)(FileDescription_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileDescription_OSAL
    }
  , { "posNameInPath"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileDescription_OSAL*)(0x1000))->posNameInPath) -(int32)(FileDescription_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileDescription_OSAL
    }
  , { "posRelatPathInPath"
    , 0   //no Array, no Bitfield
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileDescription_OSAL*)(0x1000))->posRelatPathInPath) -(int32)(FileDescription_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileDescription_OSAL
    }
  , { "absPath"
    , 0   //nrofArrayElements
    , REFLECTION_int8
    , (1<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileDescription_OSAL*)(0x1000))->absPath) -(int32)(FileDescription_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileDescription_OSAL
    }
} };


const ClassJc reflection_FileDescription_OSAL =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FileDescription_OSAL, &reflection_ClassJc)
, "FileDescription_OSAL"
, 0
, sizeof(FileDescription_OSAL)
, (FieldJcArray const*)&reflection_Fields_FileDescription_OSAL  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};




extern_C const ClassJc reflection_FileLock_OSAL;  //the just defined reflection_
const struct Reflection_Fields_FileLock_OSAL_t
{ ObjectArrayJc head;
  FieldJc data[5];
} reflection_Fields_FileLock_OSAL =
{ CONST_ObjectArrayJc(FieldJc, 5, OBJTYPE_FieldJc, null, &reflection_Fields_FileLock_OSAL)
, {
    { "hFile_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileLock_OSAL*)(0x1000))->hFile_) -(int32)(FileLock_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileLock_OSAL
    }
  , { "ptr_"
    , 0   //no Array, no Bitfield
    , REFLECTION_void
    , (8<<kBitPrimitiv_Modifier_reflectJc)| mReference_Modifier_reflectJc //bitModifiers
    , (int16)((int32)(&((FileLock_OSAL*)(0x1000))->ptr_) -(int32)(FileLock_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileLock_OSAL
    }
  , { "position_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileLock_OSAL*)(0x1000))->position_) -(int32)(FileLock_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileLock_OSAL
    }
  , { "size_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileLock_OSAL*)(0x1000))->size_) -(int32)(FileLock_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileLock_OSAL
    }
  , { "flags_"
    , 0   //no Array, no Bitfield
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((FileLock_OSAL*)(0x1000))->flags_) -(int32)(FileLock_OSAL*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_FileLock_OSAL
    }
} };


const ClassJc reflection_FileLock_OSAL =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_FileLock_OSAL, &reflection_ClassJc)
, "FileLock_OSAL"
, 0
, sizeof(FileLock_OSAL)
, (FieldJcArray const*)&reflection_Fields_FileLock_OSAL  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};



#include "OSAL/os_mem.h"

#include "OSAL/os_socket.h"


extern_C const ClassJc reflection_OS_SOCKADDR;  //the just defined reflection_
const struct Reflection_Fields_OS_SOCKADDR_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_OS_SOCKADDR =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_OS_SOCKADDR)
, {
    { "sin_zero"
    , 2   //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) |kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc //bitModifiers
    , 0 //(int16)((int32)(&((OS_SOCKADDR*)(0x1000))->sin_zero) -(int32)(OS_SOCKADDR*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_OS_SOCKADDR
    }
} };


const ClassJc reflection_OS_SOCKADDR =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_OS_SOCKADDR, &reflection_ClassJc)
, "OS_SOCKADDR"
, 0
, sizeof(OS_SOCKADDR)
, (FieldJcArray const*)&reflection_Fields_OS_SOCKADDR  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
};






#include "OSAL/os_sync.h"

#include "OSAL/os_thread.h"

