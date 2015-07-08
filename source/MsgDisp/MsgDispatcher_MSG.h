/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __MsgDisp_MsgDispatcher_MSG_h__
#define __MsgDisp_MsgDispatcher_MSG_h__

#include "Fwc/fw_MemC.h"        //basic concept

#include "Jc/ObjectJc.h"        //basic concept

#include "Jc/StringJc.h"        //used often

#include "Fwc/fw_Exception.h"   //basic concept


/* J2C: Forward declaration of struct ***********************************************/
struct ConcurrentLinkedQueueJc_t;
struct DispatcherThread_MsgDispatcher_MSG_t;
struct FileWriterJc_t;
struct LogMessageFW_t;
struct MsgDispatcher_MSG_t;
struct RunnableJc_t;
struct StringBufferJc_t;


/* J2C: includes *********************************************************/
#include "Jc/ThreadJc.h"  //superclass
#include "MsgDisp/MsgDispatcherCore_MSG.h"  //superclass


/*@CLASS_C DispatcherThread_MsgDispatcher_MSG @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct DispatcherThread_MsgDispatcher_MSG_t
{ 
  union { ObjectJc object; ThreadJc_s super;} base; 
  struct MsgDispatcher_MSG_t* outer;  //J2C: Reference to outer class, implicit in Java
  int32 cycleMillisec; 
} DispatcherThread_MsgDispatcher_MSG_s;
  

#define sizeof_DispatcherThread_MsgDispatcher_MSG_s sizeof(DispatcherThread_MsgDispatcher_MSG_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef DispatcherThread_MsgDispatcher_MSGREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define DispatcherThread_MsgDispatcher_MSGREFDEF
  struct DispatcherThread_MsgDispatcher_MSG_t;
  DEFINE_EnhancedRefJc(DispatcherThread_MsgDispatcher_MSG);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct DispatcherThread_MsgDispatcher_MSG_X_t { ObjectArrayJc head; DispatcherThread_MsgDispatcher_MSGREF data[50]; } DispatcherThread_MsgDispatcher_MSG_X;
typedef struct DispatcherThread_MsgDispatcher_MSG_Y_t { ObjectArrayJc head; DispatcherThread_MsgDispatcher_MSG_s data[50]; } DispatcherThread_MsgDispatcher_MSG_Y;

 extern_C struct ClassJc_t const reflection_DispatcherThread_MsgDispatcher_MSG_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_DispatcherThread_MsgDispatcher_MSG(OBJP) { CONST_ObjectJc(sizeof(DispatcherThread_MsgDispatcher_MSG_s), OBJP, &reflection_DispatcherThread_MsgDispatcher_MSG_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_DispatcherThread_MsgDispatcher_MSG_F(ObjectJc* othis, ThCxt* _thCxt);




/**Initializes the Thread for dispaching messages.*/
METHOD_C struct DispatcherThread_MsgDispatcher_MSG_t* ctorO_DispatcherThread_MsgDispatcher_MSG(struct MsgDispatcher_MSG_t* outer, ObjectJc* othis, int32 cycleMillisec, ThCxt* _thCxt);

/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C void run_DispatcherThread_MsgDispatcher_MSG_F(ObjectJc* ithis, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void run_DispatcherThread_MsgDispatcher_MSG(ObjectJc* ithis, ThCxt* _thCxt);


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Mtbl_DispatcherThread_MsgDispatcher_MSG[]; //marker for methodTable check
typedef struct Mtbl_DispatcherThread_MsgDispatcher_MSG_t
{ MtblHeadJc head;
  Mtbl_ThreadJc ThreadJc;
} Mtbl_DispatcherThread_MsgDispatcher_MSG;



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class DispatcherThread_MsgDispatcher_MSG : private DispatcherThread_MsgDispatcher_MSG_s
{ public:

  virtual void run(){ run_DispatcherThread_MsgDispatcher_MSG_F(&this->base.super.base.RunnableJc.base.object,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/



/*@CLASS_C MsgDispatcher_MSG @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct MsgDispatcher_MSG_t
{ 
  union { ObjectJc object; MsgDispatcherCore_MSG_s super;} base; 
  struct LogMessageFW_t* outputConsole;   /*A console output is standard everytime..*/
  int32 maxDst; 
} MsgDispatcher_MSG_s;
  

#define sizeof_MsgDispatcher_MSG_s sizeof(MsgDispatcher_MSG_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef MsgDispatcher_MSGREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define MsgDispatcher_MSGREFDEF
  struct MsgDispatcher_MSG_t;
  DEFINE_EnhancedRefJc(MsgDispatcher_MSG);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct MsgDispatcher_MSG_X_t { ObjectArrayJc head; MsgDispatcher_MSGREF data[50]; } MsgDispatcher_MSG_X;
typedef struct MsgDispatcher_MSG_Y_t { ObjectArrayJc head; MsgDispatcher_MSG_s data[50]; } MsgDispatcher_MSG_Y;

 extern_C struct ClassJc_t const reflection_MsgDispatcher_MSG_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_MsgDispatcher_MSG(OBJP) { CONST_ObjectJc(sizeof(MsgDispatcher_MSG_s), OBJP, &reflection_MsgDispatcher_MSG_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_MsgDispatcher_MSG_F(ObjectJc* othis, ThCxt* _thCxt);


#define version_MsgDispatcher_MSG 0x20120302  /*Version, history and license.*/


/**Initializes the instance.*/
METHOD_C struct MsgDispatcher_MSG_t* ctorO_MsgDispatcher_MSG(ObjectJc* othis, int32 maxDispatchEntries, int32 maxQueue, int32 maxOutputs, int32 nrofMixedOutputs, int32 msgIdentQueueOverflow, struct RunnableJc_t* runNoEntryMessage, ThCxt* _thCxt);

/**Gets the internal free entries for sharing with an other log output,*/
METHOD_C struct ConcurrentLinkedQueueJc_t* getSharedFreeEntries_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, ThCxt* _thCxt);

METHOD_C void setDefaults_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, StringJc fileOut, ThCxt* _thCxt);

/**inserts an ident range after given position:*/
METHOD_C int32 insertIdent_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, int32 idx, int32 fromIdent, int32 toIdent, ThCxt* _thCxt);

/**Sets a destination interface to a index for dispatching.*/
METHOD_C void setOutputRoutine_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, int32 dstIdx, StringJc name, bool bQueued, bool bText, struct LogMessageFW_t* dst, ThCxt* _thCxt);

/**Sets the output dispatch bits for the given message number range.*/
METHOD_C int32 setOutputRange_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, int32 fromIdent, int32 toIdent, int32 dst, int32 mode, int32 level, ThCxt* _thCxt);

/**Sets the output from a String content.*/
METHOD_C StringJc setOutputFromString_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, StringJc ctrl, struct StringBufferJc_t* errorBuffer, ThCxt* _thCxt);

/**Writes the msg dispatching outputs in file.*/
METHOD_C bool reportOutput_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, struct FileWriterJc_t* file, ThCxt* _thCxt);

/**Completes a destination bit mask with the information, whether any destinations are used*/
METHOD_C int32 completeDispatchInThreadBits_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, int32 dstBits, ThCxt* _thCxt);

/**It's a debug helper. The method is empty, but it is a mark to set a breakpoint. */
METHOD_C void stop_MsgDispatcher_MSG(MsgDispatcher_MSG_s* thiz, ThCxt* _thCxt);

/**close and flush forces the dispatching of the messages in the queue.*/
METHOD_C void close_MsgDispatcher_MSG(LogMessageFW_i* ithis, ThCxt* _thCxt);

/**flush forces the dispatching of the messages in the queue.*/
METHOD_C void flush_MsgDispatcher_MSG(LogMessageFW_i* ithis, ThCxt* _thCxt);


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Mtbl_MsgDispatcher_MSG[]; //marker for methodTable check
typedef struct Mtbl_MsgDispatcher_MSG_t
{ MtblHeadJc head;
  Mtbl_MsgDispatcherCore_MSG MsgDispatcherCore_MSG;
} Mtbl_MsgDispatcher_MSG;



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class MsgDispatcher_MSG : private MsgDispatcher_MSG_s
{ public:

  void close(){ close_MsgDispatcher_MSG(&this->base.super.base.LogMessageFW,  null/*_thCxt*/); }

  int32 completeDispatchInThreadBits(int32 dstBits){  return completeDispatchInThreadBits_MsgDispatcher_MSG(this, dstBits,  null/*_thCxt*/); }

  MsgDispatcher_MSG(int32 maxDispatchEntries, int32 maxQueue, int32 maxOutputs, int32 nrofMixedOutputs, int32 msgIdentQueueOverflow, struct RunnableJc_t* runNoEntryMessage){ init_ObjectJc(&this->base.object, sizeof(MsgDispatcher_MSG_s), 0); setReflection_ObjectJc(&this->base.object, &reflection_MsgDispatcher_MSG_s, 0); ctorO_MsgDispatcher_MSG(&this->base.object, maxDispatchEntries, maxQueue, maxOutputs, nrofMixedOutputs, msgIdentQueueOverflow, runNoEntryMessage,  null/*_thCxt*/); }

  void flush(){ flush_MsgDispatcher_MSG(&this->base.super.base.LogMessageFW,  null/*_thCxt*/); }

  struct ConcurrentLinkedQueueJc_t* getSharedFreeEntries(){  return getSharedFreeEntries_MsgDispatcher_MSG(this,  null/*_thCxt*/); }

  int32 insertIdent(int32 idx, int32 fromIdent, int32 toIdent){  return insertIdent_MsgDispatcher_MSG(this, idx, fromIdent, toIdent,  null/*_thCxt*/); }

  bool reportOutput(struct FileWriterJc_t* file){  return reportOutput_MsgDispatcher_MSG(this, file,  null/*_thCxt*/); }

  void setDefaults(StringJcpp fileOut){ setDefaults_MsgDispatcher_MSG(this, fileOut,  null/*_thCxt*/); }

  StringJc setOutputFromString(StringJcpp ctrl, struct StringBufferJc_t* errorBuffer){  return setOutputFromString_MsgDispatcher_MSG(this, ctrl, errorBuffer,  null/*_thCxt*/); }

  int32 setOutputRange(int32 fromIdent, int32 toIdent, int32 dst, int32 mode, int32 level){  return setOutputRange_MsgDispatcher_MSG(this, fromIdent, toIdent, dst, mode, level,  null/*_thCxt*/); }

  void setOutputRoutine(int32 dstIdx, StringJcpp name, bool bQueued, bool bText, struct LogMessageFW_t* dst){ setOutputRoutine_MsgDispatcher_MSG(this, dstIdx, name, bQueued, bText, dst,  null/*_thCxt*/); }

  void stop(){ stop_MsgDispatcher_MSG(this,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/

#endif //__MsgDisp_MsgDispatcher_MSG_h__