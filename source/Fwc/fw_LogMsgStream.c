/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content Log Message at any os-low-level-stream-ouput. 
 *
 * @author Hartmut Schorrig, Germany, Pinzberg
 * @version sf-0.83
 * list of changes:
 * 2008-04-22: Hartmut creation as poor implementation
 * 2008-12-01: Hartmut implementation of the LogMessage-Concept
 *
 ************************************************************************************************/


//include the own header at first to test its correct dependencies.
#include <Fwc/fw_LogMessage.h>

#include <Fwc/fw_Exception.h>
#include <Jc/ReflectionJc.h>
//#include "fw_basic.h"
#include <Fwc/objectBaseC.h>
#include <Fwc/fw_Formatter.h>

#include "Jc/ObjectJc.h"
#include <string.h>
//#include "fw_date.h"
#include <stdio.h>
//#include <io.h>

typedef struct LogMessageStream_FW_t
{
  /**The C-like-Interfaces. 
   * NOTE: More as one are a unit, because there content are congruent
   *       and they have to be start at begin of struct because casting.
   */  
  union
  { /**The data based on object, necessary for check. */
    ObjectJc object;
    /**C-Interface-struct for Log-Output. */
    LogMessageFW_i logStateFw;
  } base;

  /**The output channel for low-level-File-IO, 2 is stdout, 3 is error-output. */
  int32 outChn;

  /**Temporary buffer for 1 line, used inside run. It contains the last outputted line. */
  char buffer[1000];


}LogMessageStream_FW_s;

int out_FileDescriptorJc_val = 1;

int* out_FileDescriptorJc = &out_FileDescriptorJc_val;


extern int const sizeof_LogMessageStream_FW;
int const sizeof_LogMessageStream_FW = sizeof(LogMessageStream_FW_s);


/*@INTERNAL_PROTOTYPES LogMessageStream_FW ************************************************************/
/**Check wether the instanceof is correct, return the type-correct reference. */

METHOD_C LogMessageStream_FW_s* castO_LogMessageStream_FW(ObjectJc* zthis);


extern ClassJc const reflection_LogMessageStream_FW;



//LogMessageStream_FW_s* 
LogMessageFW_i* ctorO_LogMessageStream_FW(ObjectJc* othis, int outChn)
{ extern ClassJc const reflection_LogMessageStream_FW;
  LogMessageStream_FW_s* ythis = (LogMessageStream_FW_s*)othis;
  STACKTRC_ENTRY("");
  checkConsistence_ObjectJc(othis, sizeof(LogMessageStream_FW_s), &reflection_LogMessageStream_FW, _thCxt);
  setReflection_ObjectJc(othis, &reflection_LogMessageStream_FW, 0);
  ythis->outChn = outChn;
  STACKTRC_LEAVE; return &ythis->base.logStateFw;
}


LogMessageFW_i* create_LogMessageStream_FW(int outChn, ThCxt* _thCxt)
{ ObjectJc* othis;
  LogMessageFW_i* out;
  STACKTRC_TENTRY("create_LogMessageStream_FW");
  othis = alloc_ObjectJc(sizeof(LogMessageStream_FW_s), 0, _thCxt);
  out = ctorO_LogMessageStream_FW(othis, outChn); 
  STACKTRC_LEAVE; return out;

}




LogMessageStream_FW_s* castO_LogMessageStream_FW(ObjectJc* zthis)
{ LogMessageStream_FW_s* ythis = (LogMessageStream_FW_s*)zthis;
  //TODO check type via reflection, fast algorithm because used in any interface method.
  ASSERT(instanceof_ObjectJc(zthis, &reflection_LogMessageStream_FW));
  //ASSERT(ythis->mtbl == &mtbl_MsgDispatcher_MSG);  //an derivated class isnot accepted! 
  return ythis;
}




/**Write to stream. This routine should only be called in the MsgDispatcher_MSG.run()-Method.
 */ 
bool sendMsgVaList_LogMessageStream_FW
( struct LogMessageFW_t* ithis
, int32 identNumber
, OS_TimeStamp timestamp
, char const* text
, Va_listFW args
//, struct VaArgBuffer_t const* const args
, ThCxt* _thCxt
)
{ 
  LogMessageStream_FW_s* ythis = castO_LogMessageStream_FW(&ithis->base.object); //(MsgDispatcher_MSG_s*)zthis;
  int posBuffer;
  int nChars;
  //os_setCurrentThreadContext(_threadContext);
  //int lengthBuffer;
  char* buffer2;
  int maxBuffer = sizeof(ythis->buffer);
  STACKTRC_TENTRY("sendMsgVaList_LogMessageStream_FW");
  
  nChars = posBuffer = toStringFormat_Fw(ythis->buffer, maxBuffer, &timestamp, "\nYY-MM-dd-hh:mm:ss.SSS: ", 2);
  buffer2 = ythis->buffer + posBuffer;
  maxBuffer -= posBuffer;

  posBuffer = sprintf(buffer2, "%5.5i :", identNumber);
  buffer2 += posBuffer; 
  maxBuffer -= posBuffer;
  nChars += posBuffer;
  { //va_list argList;
    //argList = (char*)args;  //TODO preliminary for Msc6
    posBuffer = _prepareOutputText_LogMessageFW(buffer2, maxBuffer, identNumber, timestamp, text, args, _thCxt); 
    nChars += posBuffer;
  }
  //printf(ythis->buffer);
  write(ythis->outChn, ythis->buffer, nChars);
  //flush(ythis->outChn);
  STACKTRC_LEAVE; return true;
}


bool sendMsg_time_LogMessageStream_FW
( struct LogMessageFW_t* ithis
, int32 identNumber
, OS_TimeStamp timestamp
, char const* text
, char const* typeArgs
, ...
)
{ //represent the variable arguments as a reference to the VaArgBuffer-type, the instance is located in stack.
  //VaArgBuffer* args = (VaArgBuffer*)(addOffset_MemAreaC(&text, sizeof(text)));
  bool ok;
  va_list args;
  Va_listFW typedArgs;
  STACKTRC_ENTRY("sendMsg_time_LogMessageStream_FW");
  va_start(args, typeArgs);
  typedArgs.typeArgs = typeArgs;
  typedArgs.args = args;
  ok = sendMsgVaList_LogMessageStream_FW(ithis, identNumber, timestamp, text, typedArgs, _thCxt);
  STACKTRC_LEAVE; return ok;
}


/**Method type definition to send a message with given timestamp and parameter.
 */
bool sendMsg_LogMessageStream_FW
( struct LogMessageFW_t* ithis
, int32 identNumber
, char const* text
, char const* typeArgs
, ...
)
{ //represent the variable arguments as a reference to the VaArgBuffer-type, the instance is located in stack.
  //VaArgBuffer* args = (VaArgBuffer*)(addOffset_MemAreaC(&text, sizeof(text)));
  bool ok;
  va_list args;
  Va_listFW typedArgs;
  STACKTRC_ENTRY("sendMsg_time_LogMessageStream_FW");
  va_start(args, typeArgs);
  typedArgs.typeArgs = typeArgs;
  typedArgs.args = args;
  ok = sendMsgVaList_LogMessageStream_FW(ithis, identNumber, os_getDateTime(), text, typedArgs, _thCxt);
  STACKTRC_LEAVE; return ok;
}




bool isOnline_LogMessageStream_FW_F(LogMessageFW_i* ythis, ThCxt* _thCxt)
{ //do noting.
  return true; //everytime online.
}


void flush_LogMessageStream_FW_F(LogMessageFW_i* ythis, ThCxt* _thCxt)
{ //do noting.
}


void close_LogMessageStream_FW_F(LogMessageFW_i* ythis, ThCxt* _thCxt)
{ //do noting.
}




/*@REFLECTION LogMessageStream_FW ************************************************************/

char const sign_Mtbl_LogMessageStream_FW[] = "sign_Mtbl_LogMessageStream_FW";


/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
/*
struct Mtbl_LogMessageStream_FW_t
{ MtblHeadJc head;
  Mtbl_LogMessageFW LogMessage_FW_i;
  MtblHeadJc end;
} const mtbl_LogMessageStream_FW
*/
Mtbl_LogMessageStream_FW const mtbl_LogMessageStream_FW
=
{ { sign_Mtbl_LogMessageStream_FW
  , (struct Size_Mtbl_t*)( (0+2) * sizeof(void*)) 
  }
, { { sign_Mtbl_LogMessageFW
    , (struct Size_Mtbl_t*)( (4+2)  * sizeof(void*))
    }
  , sendMsgVaList_LogMessageStream_FW
  , flush_LogMessageStream_FW_F
  , close_LogMessageStream_FW_F
  , isOnline_LogMessageStream_FW_F
  , sendMsg_LogMessageStream_FW
  , sendMsg_time_LogMessageStream_FW
  , { { sign_Mtbl_ObjectJc, (struct Size_Mtbl_t*)( (5+2)  * sizeof(void*))}
    , clone_ObjectJc_F
    , equals_ObjectJc_F
    , finalize_ObjectJc_F
    , hashCode_ObjectJc_F
    , toString_ObjectJc_F
    }
  }
  , { signEnd_Mtbl_ObjectJc, null}
};


extern ClassJc const reflection_LogMessageFW_i;

static struct interfaces_LogMessageStream_FW_t
{ /** Base data of every array */
  ObjectArrayJc head;
  ClassOffset_idxMtblJc data[1];
}interfaces_LogMessageStream_FW =
{ CONST_ObjectArrayJc(ClassOffset_idxMtblJc, 1, OBJTYPE_ClassOffset_idxMtblJc, null, null)
, { {&reflection_LogMessageFW_i, OFFSET_Mtbl(struct Mtbl_LogMessageStream_FW_t, LogMessage_FW_i) }
  }
};


   
ClassJc const reflection_LogMessageStream_FW =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_LogMessageStream_FW, &reflection_ClassJc)
, "LogMessageStream_FW"
, 0     //posObjectJc
, sizeof(LogMessageStream_FW_s)
, null  //attributes and associations
, null  //method
, null  //superclass
, (ClassOffset_idxMtblJcARRAY*)&interfaces_LogMessageStream_FW  //interfaces
, 0x4000000  //modifiers
, &mtbl_LogMessageStream_FW.head
};


