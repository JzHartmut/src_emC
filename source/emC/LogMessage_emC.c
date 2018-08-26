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
 * @content This source contains routines to implement the LogMessage interface at C-level.
 * The LogMessageFW_s interface is an abstract C-like class. The not-abstract C-routines are contained here.
 * The iLogMessageFW interface is the C++ incarnation of the same interface, its non-abstract routines are implemented here.
 * Additional some helper routines for the MsgDispatcher_MSG are found here.       
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * list of changes:
 * 2009-10-00: Hartmut: corr: Implementation of constructor is empty, but the constructor call is generated automatically by Java2C.
 * 2008-04-22: Hartmut creation as poor implementation
 * 2008-12-01: Hartmut implementation of the LogMessage-Concept
 *
 ************************************************************************************************/

#include <emC/LogMessage_emC.h>
//#include "Jc/StringJc.h"
#include <emC/Formatter_emC.h>
//#include "OSAL/inc/os_time.h"
//
//#include <stdarg.h>
#include <string.h>
//#include <emC/ThreadContext_emC.h>


extern struct ClassJc_t const reflection_LogMessageFW_i;

LogMessageFW_s* ctorO_LogMessageFW(ObjectJc* othis, ThCxt* _thCxt)
{ return (LogMessageFW_s*)othis;
}


/**The ident text is only used by its address. The address is a part of the method table,
 * enter from linker there. The check of the correct address is a safety precaution.
 */
//const char identText_LogMessageFW[] = "LogMessage_FW";
const char sign_Mtbl_LogMessageFW[] = "LogMessage_FW";

/**This is the reference address to check the correct address in method table.
 */
//void const* const xxxsign_Mtbl_LogMessageFW = &identText_LogMessageFW;


/**This routine calls the virtual (dynamic called) C-routine. */
bool sendMsgVaList_LogMessageFW(struct LogMessageFW_t* ythis, int32 identNumber
, OS_TimeStamp timestamp
, char const* text
, Va_listFW args
, ThCxt* _thCxt)
{
  //this method checks the correctness of the instance data
  //and throws an exception if there is a memory overwritten error or initialization error:
  //The casting is deterministic because the type MyStruct is tested.
  Mtbl_LogMessageFW const* mtbl;
  bool bRet;
  STACKTRC_TENTRY("sendMsgVaList_LogMessageFW");
  MtblHeadJc const* mtblO = getMtbl_ObjectJc(&ythis->base.object, sign_Mtbl_LogMessageFW);
  mtbl = (Mtbl_LogMessageFW const*)mtblO;
  ASSERTJc_RET(mtbl != null && mtbl->head.sign == sign_Mtbl_LogMessageFW, (STACKTRC_LEAVE, false));
  //if(mtbl == null) THROW1_s0(IllegalArgumentException, "Method-table not found",0);
  //if(mtbl->sign != &sign_Mtbl_LogMessageFW) THROW1_s0(IllegalArgumentException, "The found Method-table is not correct", (int)mtbl);
  //sText = getCharConst_StringJc(text, uText, sizeof(uText));  //get the char const* from text.
  bRet = mtbl->sendMsgVaList(ythis,identNumber, timestamp, text, args, _thCxt);
  STACKTRC_LEAVE; 
  return bRet;

}



/**This routine calls the virtual (dynamic called) C-routine. */
void flush_LogMessageFW(LogMessageFW_s* ythis, ThCxt* _thCxt)
{
  //this method checks the correctness of the instance data
  //and throws an exception if there is a memory overwritten error or initialization error:
  //The casting is deterministic because the type MyStruct is tested.
  Mtbl_LogMessageFW const* mtbl;
  MtblHeadJc const* mtblO;
  STACKTRC_TENTRY("sendMsgVaList_LogMessageFW");
  mtblO = getMtbl_ObjectJc(&ythis->base.object, sign_Mtbl_LogMessageFW);
  mtbl = (Mtbl_LogMessageFW*)mtblO;
  if(mtbl == null) THROW1_s0(IllegalArgumentException, "Method-table not found",0);
  if(mtbl->head.sign != sign_Mtbl_LogMessageFW) THROW1_s0(IllegalArgumentException, "The found Method-table is not correct", (int)mtbl);
  if( (int)mtbl->head.sizeTable >= (OS_intPTR)(mtbl->flush) - (OS_intPTR)(mtbl))
  { mtbl->flush(ythis, _thCxt);
  }
  else
  { //The implementation have an older version of method table, call the default implementation:
    flush_LogMessageFW_F(ythis, _thCxt);
  }
  STACKTRC_LEAVE;

}



/**This routine calls the virtual (dynamic called) C-routine. */
void close_LogMessageFW(LogMessageFW_s* ythis, ThCxt* _thCxt)
{
  //this method checks the correctness of the instance data
  //and throws an exception if there is a memory overwritten error or initialization error:
  //The casting is deterministic because the type MyStruct is tested.
  Mtbl_LogMessageFW* mtbl;
  MtblHeadJc const* mtblO;
  STACKTRC_TENTRY("sendMsgVaList_LogMessageFW");
  mtblO = getMtbl_ObjectJc(&ythis->base.object, sign_Mtbl_LogMessageFW);
  mtbl = (Mtbl_LogMessageFW*)mtblO;
  if(mtbl == null) THROW1_s0(IllegalArgumentException, "Method-table not found",0);
  if(mtbl->head.sign != sign_Mtbl_LogMessageFW) THROW1_s0(IllegalArgumentException, "The found Method-table is not correct", (int)mtbl);
  if( (int)mtbl->head.sizeTable >= (int)((OS_intPTR)(mtbl->close) - (OS_intPTR)(mtbl)))
  { mtbl->close(ythis, _thCxt);
  }
  else
  { //The implementation have an older version of method table, call the default implementation:
    close_LogMessageFW_F(ythis, _thCxt);
  }
  STACKTRC_LEAVE;

}



/**This routine calls the virtual (dynamic called) C-routine. */
bool isOnline_LogMessageFW(LogMessageFW_s* ythis, ThCxt* _thCxt)
{
  //this method checks the correctness of the instance data
  //and throws an exception if there is a memory overwritten error or initialization error:
  //The casting is deterministic because the type MyStruct is tested.
  bool isOnline;
  Mtbl_LogMessageFW* mtbl;
  MtblHeadJc const* mtblO;
  STACKTRC_TENTRY("sendMsgVaList_LogMessageFW");
  mtblO = getMtbl_ObjectJc(&ythis->base.object, sign_Mtbl_LogMessageFW);
  mtbl = (Mtbl_LogMessageFW*)mtblO;
  if(mtbl == null) THROW1_s0(IllegalArgumentException, "Method-table not found",0);
  if(mtbl->head.sign != sign_Mtbl_LogMessageFW) THROW1_s0(IllegalArgumentException, "The found Method-table is not correct", (int)mtbl);
  if( (int)mtbl->head.sizeTable >= (int)((OS_intPTR)(mtbl->isOnline) - (OS_intPTR)(mtbl)))
  { isOnline = mtbl->isOnline(ythis, _thCxt);
  }
  else
  { //The implementation have an older version of method table, call the default implementation:
    isOnline = isOnline_LogMessageFW_F(ythis, _thCxt);
  }
  STACKTRC_LEAVE; return isOnline;

}



/**Implementation of calling with variable arguments. */
bool sendMsg_LogMessageFW(struct LogMessageFW_t* ythis
, int identNumber
, char const* const text
//, StringJc const text
, char const* typeArgs
, ...
)
{ //represent the variable arguments as a reference to the VaArgBuffer-type, the instance is located in stack.
  //VaArgBuffer* args = (VaArgBuffer*)(addOffset_MemAreaC(&text, sizeof(text)));
  bool ok;
  //Va_listFW vaArgs = CONST_Va_listFW(args);  /*store the variable arguments in a Va_list to handle for next call.*/
  va_list args;
  Va_listFW typedArgs;
  STACKTRC_ENTRY("sendMsg_iSzv_LogMessageFW");
  va_start(args, typeArgs);
  typedArgs.typeArgs = typeArgs;
  typedArgs.args = args;
  ok = sendMsgVaList_LogMessageFW(ythis, identNumber, os_getDateTime(), text, typedArgs, _thCxt);
  STACKTRC_LEAVE; return ok;
}



/**Implementation of calling with variable arguments. */
bool sendMsg_tzzv_LogMessageFW(struct LogMessageFW_t* ithis
, int identNumber
, OS_TimeStamp time
, char const* text
, char const* typeArgs
, ...
)
{ //represent the variable arguments as a reference to the VaArgBuffer-type, the instance is located in stack.
  //VaArgBuffer* args = (VaArgBuffer*)(addOffset_MemAreaC(&text, sizeof(text)));
  bool ok;
  va_list args;
  Va_listFW typedArgs;
  Mtbl_LogMessageFW const* mtbl;
  STACKTRC_ENTRY("sendMsg_tzzv_LogMessageFW");
  mtbl = (Mtbl_LogMessageFW const*)getMtbl_ObjectJc(&ithis->base.object, sign_Mtbl_LogMessageFW);
  va_start(args, typeArgs);
  typedArgs.typeArgs = typeArgs;  //given!
  typedArgs.args = args;
  ok = mtbl->sendMsgVaList(ithis, identNumber, time, text, typedArgs, _thCxt);
  //ok = false;
  STACKTRC_LEAVE; return ok;
}




/**Implementation of calling with variable arguments. */
bool xxxsendMsg_z_LogMessageFW(struct LogMessageFW_t* ithis, int identNumber, const char* text, ThCxt* _thCxt)
{
  Mtbl_LogMessageFW const* mtbl;
  bool bOk;
  STACKTRC_TENTRY("sendMsg_z_LogMessageFW");
  mtbl = (Mtbl_LogMessageFW const*)getMtbl_ObjectJc(&ithis->base.object, sign_Mtbl_LogMessageFW);
  
  bOk = mtbl->sendMsg(ithis, identNumber, text, "");  //emtpy type info!
  STACKTRC_LEAVE;
  return bOk;
}

/**Implementation of calling with variable arguments. */
bool xxxsendMsg_S_LogMessageFW(struct LogMessageFW_t* ythis, int identNumber, StringJc text, ThCxt* _thCxt)
{
  //return sendMsg_Szv_LogMessageFW(ythis, identNumber, text, "");  //emtpy type info!
  return false;
}




/**C-routine to flush messages. This is a default implementation to use in users method table. */
void flush_LogMessageFW_F(LogMessageFW_s* ythis, ThCxt* _thCxt)
{ //do noting.
}

/**C-routine to close the message transfer. This is a default implementation to use in users method table. */
void close_LogMessageFW_F(LogMessageFW_s* ythis, ThCxt* _thCxt)
{ //do noting.
}


/**C-routine to check the message transfer. This is a default implementation to use in users method table. */
bool isOnline_LogMessageFW_F(LogMessageFW_s* ythis, ThCxt* _thCxt)
{ //do noting.
  return true; //everytime online.
}




/*@CLASS_C MsgDispatcher_MSG ************************************************************************
 *Additional methods, there are not able to translate java2c
 */

int _prepareOutputText_LogMessageFW
( char* buffer, int zBuffer
, int32 ident
, OS_TimeStamp time
, char const* sText
, Va_listFW args
, ThCxt* _thCxt
)
//(char* buffer, int zBuffer, int ident, StringJc text, OS_TimeStruct time
//, char const* typeArgs, va_list args
{
  int nrofChars;
  int zText = strlen(sText);
  //char const* sText = getCharsAndLength_StringJc(&text, &zText);
  //const char* text1 = text.ref; 
  //char const* arg1 = *(char const**)(&args->v[0]);
  STACKTRC_TENTRY("_prepareOutputText_MsgDispatcher_MSG");
  //if( true )//arg1 == typedVaArg_ObjectJc)
  { nrofChars = format_va_arg_Formatter_FW(_thCxt, sText, zText, buffer, zBuffer, args);
  }
  //else
  { //This routine is not available in all systems, especially not in Rmos.
    //nrofChars = _snprintf(buffer, zBuffer, sText, *args);  //11*4 bytes per value.
    //if(nrofChars > zBuffer)
    { 
    }
  }
  STACKTRC_LEAVE; return nrofChars;
}





#if defined(__CPLUSGEN) && defined(__cplusplus)




void LogMessageFW::sendMsgVaList(int32 ident, OS_TimeStamp timestamp, const char* text, const char* typeArgs, va_list args)
{ Va_listFW typedArgs;
  LogMessageFW_s* ithis = provide_LogMessageFW_i();
  typedArgs.typeArgs = typeArgs; //the type info
  typedArgs.args = args;         //the va_list
  sendMsgVaList_LogMessageFW(ithis, ident, timestamp, text, typedArgs, null); 
} 



/**Standardimplementation calls the C-variant of close(). 
 */
void LogMessageFW::close()
{ LogMessageFW_s* ithis = provide_LogMessageFW_i();
  close_LogMessageFW(ithis, null);
}


/**Standardimplementation calls the C-variant of flush(). 
 */
void LogMessageFW::flush()
{ LogMessageFW_s* ithis = provide_LogMessageFW_i();
  flush_LogMessageFW(ithis, null);
}


/**Standardimplementation calls the C-variant of isOnline(). 
 */
bool LogMessageFW::isOnline()
{ LogMessageFW_s* ithis = provide_LogMessageFW_i();
  return isOnline_LogMessageFW(ithis, null);
}



#endif  //__CPLUSGEN    

#include "genRefl/emC/LogMessage_emC.crefl"



