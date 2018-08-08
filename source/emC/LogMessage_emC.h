/****************************************************************************
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
 * @author Hartmut Schorrig www.vishia.org
 * @version 0.91
 * list of changes:
 * 2008-05-00: www.vishia.de creation
 * 2009-11-25
 *   *new: ctorO_LogMessageFW(...)
 *   *new: int sendMsgTime(int ident, OS_TimeStamp timeMsg, const char* text, ...) for C++
 *
 * @content Definition of a interface for Logging and Messaging.
 *
 ****************************************************************************/
#ifndef __fw_LogMessage_h__
#define __fw_LogMessage_h__
#include <applstdef_emC.h>
//#include "fw_simpleC.h"
#include <Fwc/fw_Va_list.h>
//#include <Jc/ObjectJc.h>
#include "Fwc/objectBaseC.h"   //ObjectJc used.
#include "Fwc/fw_Exception.h"  //ThCxt used.
#include <os_time.h>  //struct OS_TimeStamp as argument

/*@CLASS_C LogMessageFW @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Interface for C-language.
 * This struct should used ones as marker struct for the interface.
 * The implementation classes have to be based on ObjectJc and should have a Method table in its reflections.
 * The method table definition is the really interface definition.
 */
typedef struct  LogMessageFW_t
{ 
  /**The implementation classes based on ObjectJc. Necessary for check.*/
  union{ ObjectJc object; } base;
}LogMessageFW_s;  //_i means an struct useable as interface

//Not used ... TODO idea? necessary? 
//typedef struct LogMessageFW_MREF_t { struct LogMessageFW_t* ref; struct Mtbl_LogMessageFW_t const* mtbl; } LogMessageFW_MREF;



/**Level of outputs.
 */
typedef enum ELevel_Message_ifcFW_t
{ kError_LogMessageFW = 1
, kWarning_LogMessageFW = 2
, kInfo_LogMessageFW = 3
, kFineInfo_LogMessageFW = 4
, kDebug_LogMessageFW = 4
, kFineDebug_LogMessageFW = 6
}eLevel_Message_ifcFW;


/**The constructor is only called as super constructor in all implementing classes. 
 * It is empty.
 */
METHOD_C LogMessageFW_s* ctorO_LogMessageFW(ObjectJc* othis, ThCxt* _thCxt);

/**C-routine to send a message to a log system without additional parameter.
 * @param identNumber The identnumber idents the source and kind of message.
                      It is possible to select the destination of message output by ident numbers.
                      It is also possible to select output texts in foreign languages on output system by ident number.
                      It is possible to mark "comming" and "going" from a message, using the positiv and negativ value of the number.
                      The positiv and negativ value should present the same identNumber.
 * @param text The default, immediate output text
 */
//bool sendMsg_z_LogMessageFW(struct LogMessageFW_t* ythis, int identNumber, const char* text, ThCxt* _thCxt);


/**C-routine to send a message to a log system without additional parameter.
 * @param text The default, immediate output text.
 */
#define sendMsg_z_LogMessageFW(YTHIS, ID, TEXT, _THCXT) sendMsg_LogMessageFW(YTHIS, ID, TEXT, "") 
//bool sendMsg_s_LogMessageFW(struct LogMessageFW_t* ythis, int identNumber, StringJc text, ThCxt* _thCxt);

//void sendMsg_LogMessage_FW(struct LogMessageFW_t* ythis, int identNumber, const char* text, ...);

/**C-routine to send a message to a log system with additional parameter.
 */
METHOD_C bool sendMsg_LogMessageFW(struct LogMessageFW_t* ythis
, int identNumber
, char const* const text
, char const* typeArgs
, ...
);


/**C-routine to send a message with a variable argument list. The text should match to the type of arguments.
 */
bool sendMsg_tzzv_LogMessageFW(struct LogMessageFW_t* ythis
, int identNumber
, OS_TimeStamp time
, char const* text
, char const* typeArgs
, ...
);


/**C-routine to send a message with given arguments in a variable argument list.
 *  This routine uses the method table to call the users implementation. 
 */
METHOD_C bool sendMsgVaList_LogMessageFW(struct LogMessageFW_t* ythis
, int32 identNumber
, OS_TimeStamp timestamp
, char const* text
, Va_listFW args
, ThCxt* _thCxt
);


/**C-routine to flush messages. This routine uses the method table to call the users implementation. */
void flush_LogMessageFW(LogMessageFW_s* ythis, ThCxt* _thCxt);

/**C-routine to close the message transfer.  This routine uses the method table to call the users implementation. */
void close_LogMessageFW(LogMessageFW_s* ythis, ThCxt* _thCxt);

/**C-routine to check the message transfer.  This routine uses the method table to call the users implementation. */
bool isOnline_LogMessageFW(LogMessageFW_s* ythis, ThCxt* _thCxt);

/**C-routine to flush messages. This is a default implementation to use in users method table. */
void flush_LogMessageFW_F(LogMessageFW_s* ythis, ThCxt* _thCxt);

/**C-routine to close the message transfer. This is a default implementation to use in users method table. */
void close_LogMessageFW_F(LogMessageFW_s* ythis, ThCxt* _thCxt);

/**C-routine to check the message transfer. This is a default implementation to use in users method table. */
bool isOnline_LogMessageFW_F(LogMessageFW_s* ythis, ThCxt* _thCxt);



/**Method type definition to send a message with given timestamp and parameter.
 */
typedef bool MT_sendMsg_time_LogMessageFW
( struct LogMessageFW_t* ithis
, int32 identNumber
, OS_TimeStamp timestamp
, char const* text
, char const* typeArgs
, ...
);


/**Method type definition to send a message with given timestamp and parameter.
 */
typedef bool MT_sendMsg_LogMessageFW
( struct LogMessageFW_t* ithis
, int32 identNumber
, char const* text
, char const* typeArgs
, ...
);


/**Method type definition to send a message with given timestamp and parameter.
 * This is the commonly kind of calling routine to send a message. Only this type of sendMsg-routine 
 * should be implemented by any implementation of LogMessage output. See [[MT_sendMsgVaList_LogMessageFW]]
 */
typedef bool MT_sendMsgVaList_LogMessageFW
( struct LogMessageFW_t* ithis
, int32 identNumber
, OS_TimeStamp timestamp
, char const* text
, Va_listFW args
, ThCxt* _thCxt
);


/**Method type definition to flush messages. This routine
 * should be implemented by any C-implementation of LogMessage output. See [[MT_sendMsgVaList_LogMessageFW]]
 */
typedef void MT_flush_LogMessageFW( struct LogMessageFW_t* ithis, ThCxt* _thCxt);


/**Method type definition to close messages. This routine
 * should be implemented by any C-implementation of LogMessage output. See [[MT_sendMsgVaList_LogMessageFW]]
 */
typedef void MT_close_LogMessageFW( struct LogMessageFW_t* ithis, ThCxt* _thCxt);

/**Method type definition to test a message output. This routine
 * should be implemented by any C-implementation of LogMessage output. See [[MT_sendMsgVaList_LogMessageFW]]
 */
typedef bool MT_isOnline_LogMessageFW( struct LogMessageFW_t* ithis, ThCxt* _thCxt);

/**This is a marker text. The content of text isn't important, but all implementations should use the same address
 * (value of field sign in Mtbl_LogMessageFW).
 */
//extern void const* const sign_Mtbl_LogMessageFW;
extern char const sign_Mtbl_LogMessageFW[];

/**const struct of method addresses. A constant instance of this struct should be a part of the Reflection-MethodTable
 * of implementation by any Log output.
 */
typedef struct Mtbl_LogMessageFW_t
{ 
  /**The value of sign must be identically with the address of the sign_Mtbl_Message_ifcFW-variable. Use it for safe access. */
  //void const* const* sign;
  /**The sizeTable is really an simple int. But all members of Method table are from pointer type. casted internally. 
   * Check of sizeTable makes possible to use older implementation versions with less methods.
   * NOTE: don't use a void*, because all is compatible with it and no errors are signated.
   */
  //struct Size_Mtbl_t* sizeTable;  

  MtblHeadJc head;
  /**Only this method should implemented. */
  MT_sendMsgVaList_LogMessageFW* sendMsgVaList;
  MT_flush_LogMessageFW* flush;
  MT_close_LogMessageFW* close;
  MT_isOnline_LogMessageFW* isOnline;
  MT_sendMsg_LogMessageFW* sendMsg;
  MT_sendMsg_time_LogMessageFW* sendMsgTime;
  Mtbl_ObjectJc ObjectJc;
}Mtbl_LogMessageFW;


/**Method-table-references *********************************************************/
#ifndef LogMessageFWMTBDEF
  #define LogMessageFWMTBDEF
  typedef struct LogMessageFWMTB_t { struct Mtbl_LogMessageFW_t const* mtbl; struct LogMessageFW_t* ref; } LogMessageFWMTB;
#endif


/* *******************************************************************************************************************/
/**C++-usage: */

#if defined(__CPLUSGEN) && defined(__cplusplus)


/**The C++-interface for Log or Message output.
 *
 * Implementation hint: All methods are virtual and are overrideable. 
 * But the default implementation calls the C-interface-method. There are 2 ways to implement:
 * * Implement in C++, override all virtual methods, don't consider a C-interface.
 * The method provide_LogMessageFW_i() may return null.
 * * Implement in C, override only provide_LogMessageFW_i() with the C-interface. 
 * * If an output is used in the Message Dispatcher, the C-routines are to implemented.
 */
class LogMessageFW
{
  /**Sends a message with variable but typed arguments.*/
  /*NOTE: virtual because binary downward compatibility. It does't be necessary. */
  public: virtual int sendMsgTyped(int ident, const char* text, char const* typeArgs, ...)
  { va_list args;
    va_start(args, typeArgs);
    sendMsgVaList(ident, os_getDateTime(), text, typeArgs, args); 
    return 0;
  } 

  /**Sends a message with given timestamp.*/
  /*HINT: not virtual because always redirected to the main virtual routine.*/
  public: int sendMsgTyped(int ident, OS_TimeStamp timestamp, const char* text, char const* typeArgs, ...)
  { va_list args;
    va_start(args, typeArgs);
    sendMsgVaList(ident, timestamp, text, typeArgs, args); 
    return 0;
  } 

  /**Sends a message with variable but typed arguments.*/
  /*NOTE: virtual because binary downward compatibility. It does't be necessary. */
  public: virtual int sendMsg(int ident, const char* text, ...)
  { va_list args;
    va_start(args, text);
    sendMsgVaList(ident, os_getDateTime(), text, null, args); 
    return 0;
  } 

  /**Sends a message with variable but typed arguments.*/
  /*NOTE: virtual because binary downward compatibility. It does't be necessary. */
  public: int sendMsgTime(int ident, OS_TimeStamp timeMsg, const char* text, ...)
  { va_list args;
    va_start(args, text);
    sendMsgVaList(ident, timeMsg, text, null, args); 
    return 0;
  } 

  
  /**Sends a message with timestamp and referenced variable arguments.
   * The standard implementation of this routine calls the C-routine. They uses the C-Method table for virtual call.
   * A user specific Implementation need only implement this method, the other ones are redirected to this routine.
   * @param text The text may outputted. 
   * @param typeArgs The type of the arguments in args. It may be null, than the types are detected from the text in a printf-style.
   * @param args Variable arguments-pointer adequat to vsprintf. Use va_start() from stdarg.h to get it from a variable argument list.
   */
  public: virtual void sendMsgVaList(int32 ident, OS_TimeStamp timestamp, const char* text, const char* typeArgs, va_list args);

  /**This method should be overridden. It may return null, if only the C++-Interface should used. */
  public: virtual LogMessageFW_s* provide_LogMessageFW_i()=0; 

  /**The standard implementation of this routine calls the C-routine. They uses the C-Method table for virtual call.*/
  public: virtual void flush();

  /**The standard implementation of this routine calls the C-routine. They uses the C-Method table for virtual call.*/
  public: virtual void close();

  /**The standard implementation of this routine calls the C-routine. They uses the C-Method table for virtual call.*/
  public: virtual bool isOnline();

  //public: virtual int hexDump(int ident, void* pBuffer, int length, int bytesPerWord)=0;
    

  
};



#endif  //__CPLUSGEN

/*@DEFINE LogMessageConsole @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**LogMessageConsole: Methods
 */

/**Initializes a file output.
 * @param othis reference to the instance, the size should be known in the ObjectJc-base. ObjectJc should be initialized already.
 *        If this parameter is null, an instance will be created in heap.
 */
METHOD_C LogMessageFW_s* ctorO_LogMessageConsole(ObjectJc* othis);

/**Initializes a file output.
 * @param othis reference to the instance, the size should be known in the ObjectJc-base. ObjectJc should be initialized already.
 *        If this parameter is null, an instance will be created in heap.
 * @param sFileName: If it contains a part between $...$, it is the pattern for timestamp, see java.text.SimpleDateFormat.
 * @param nrofSecondsToFlush: A flush of content isn't written immediate, so the file is not visible outside. 
 *        This parameter defines, after how many seconds of a first not flushed write the file will be flushed.
 *        Note: A flush won't be done automatically, only if a new message is written. Reason: No extra thread is used.
 *        The value 0 means: flush any message immediately.
 * @param nrofHoursPerFile: After this time a new file will be created 
 */
METHOD_C LogMessageFW_s* xxxctorO_LogMessageFile(ObjectJc* othis
, StringJc sFileName
, int nrofSecondsToFlush
, int nrofHoursPerFile
);

/**
 * @param outChn The output channel for low-level-File-IO, 2 is stdout, 3 is error-output.
 */
LogMessageFW_s* create_LogMessageStream_FW(int outChn, ThCxt* _thCxt);
LogMessageFW_s* create_LogMessageConsole(ThCxt* _thCxt);

extern int* out_FileDescriptorJc;

typedef struct Mtbl_LogMessageStream_FW_t
{ MtblHeadJc head;
  Mtbl_LogMessageFW LogMessage_FW_i;
  MtblHeadJc end;
} Mtbl_LogMessageStream_FW;


extern struct Mtbl_LogMessageStream_FW_t const mtbl_LogMessageStream_FW;



/*@CLASS_C MsgDispatcher_MSG ************************************************************************
 *Additional methods, there are not able to translate java2c
 */

/**The MsgDispatcher is defined and implemented in another files. But here an additional access routine is defined,
 */
struct MsgDispatcher_MSG_t;
LogMessageFW_s* xxxconvertFromMsgDispatcher_LogMessageFW(struct MsgDispatcher_MSG_t* src, ThCxt* _thCxt);

int _prepareOutputText_LogMessageFW
( char* buffer, int zBuffer
, int32 ident
, OS_TimeStamp time
, char const* text
, Va_listFW args
, ThCxt* _thCxt
);

//, int ident, StringJc text, OS_TimeStruct time
//, char const* typeArgs, va_list  args);



#endif /*__LogMessageFW_h__*/
