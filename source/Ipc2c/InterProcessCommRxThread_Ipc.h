/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __Ipc2c_InterProcessCommRxThread_Ipc_h__
#define __Ipc2c_InterProcessCommRxThread_Ipc_h__

#include "Fwc/fw_MemC.h"        //basic concept

#include "Jc/ObjectJc.h"        //basic concept

#include "Jc/StringJc.h"        //used often

#include "Fwc/fw_Exception.h"   //basic concept


/* J2C: Forward declaration of struct ***********************************************/
struct Address_InterProcessComm_t;
struct C_threadRoutine_InterProcessCommRxThread_Ipc_t;
struct InterProcessComm_t;
struct InterProcessCommRxThread_Ipc_t;
struct InterProcessCommRx_ifc_Ipc_t;
struct ThreadJc_t;


/* J2C: includes *********************************************************/
#include "Jc/ThreadJc.h"  //interface


/*@CLASS_C C_threadRoutine_InterProcessCommRxThread_Ipc @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct C_threadRoutine_InterProcessCommRxThread_Ipc_t
{ 
  union { ObjectJc object; RunnableJc_s RunnableJc;} base; 
  struct InterProcessCommRxThread_Ipc_t* outer;  //J2C: Reference to outer class, implicit in Java
} C_threadRoutine_InterProcessCommRxThread_Ipc_s;
  

#define sizeof_C_threadRoutine_InterProcessCommRxThread_Ipc_s sizeof(C_threadRoutine_InterProcessCommRxThread_Ipc_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef C_threadRoutine_InterProcessCommRxThread_IpcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define C_threadRoutine_InterProcessCommRxThread_IpcREFDEF
  struct C_threadRoutine_InterProcessCommRxThread_Ipc_t;
  DEFINE_EnhancedRefJc(C_threadRoutine_InterProcessCommRxThread_Ipc);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct C_threadRoutine_InterProcessCommRxThread_Ipc_X_t { ObjectArrayJc head; C_threadRoutine_InterProcessCommRxThread_IpcREF data[50]; } C_threadRoutine_InterProcessCommRxThread_Ipc_X;
typedef struct C_threadRoutine_InterProcessCommRxThread_Ipc_Y_t { ObjectArrayJc head; C_threadRoutine_InterProcessCommRxThread_Ipc_s data[50]; } C_threadRoutine_InterProcessCommRxThread_Ipc_Y;

 extern_C struct ClassJc_t const reflection_C_threadRoutine_InterProcessCommRxThread_Ipc_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_C_threadRoutine_InterProcessCommRxThread_Ipc(OBJP) { CONST_ObjectJc(sizeof(C_threadRoutine_InterProcessCommRxThread_Ipc_s), OBJP, &reflection_C_threadRoutine_InterProcessCommRxThread_Ipc_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_C_threadRoutine_InterProcessCommRxThread_Ipc_F(ObjectJc* othis, ThCxt* _thCxt);




/* J2C:Implementation of the method, used for an immediate non-dynamic call: */
METHOD_C void run_C_threadRoutine_InterProcessCommRxThread_Ipc_F(ObjectJc* ithis, ThCxt* _thCxt);
/* J2C:Call of the method at this class level, executes a dynamic call of the override-able method: */
METHOD_C void run_C_threadRoutine_InterProcessCommRxThread_Ipc(ObjectJc* ithis, ThCxt* _thCxt);


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Mtbl_C_threadRoutine_InterProcessCommRxThread_Ipc[]; //marker for methodTable check
typedef struct Mtbl_C_threadRoutine_InterProcessCommRxThread_Ipc_t
{ MtblHeadJc head;
  Mtbl_ObjectJc ObjectJc;
  //Method table of interfaces:
  Mtbl_RunnableJc RunnableJc;
} Mtbl_C_threadRoutine_InterProcessCommRxThread_Ipc;



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class C_threadRoutine_InterProcessCommRxThread_Ipc : private C_threadRoutine_InterProcessCommRxThread_Ipc_s
{ public:

  virtual void run(){ run_C_threadRoutine_InterProcessCommRxThread_Ipc_F(&this->base/*J2C:ifc*/.RunnableJc.base.object,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/


/**Default constructor. */
METHOD_C struct C_threadRoutine_InterProcessCommRxThread_Ipc_t* ctorO_C_threadRoutine_InterProcessCommRxThread_Ipc(struct InterProcessCommRxThread_Ipc_t* outer, ObjectJc* othis, ThCxt* _thCxt);


/*@CLASS_C InterProcessCommRxThread_Ipc @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct InterProcessCommRxThread_Ipc_t
{ 
  union { ObjectJc object; } base; 
  struct InterProcessCommRx_ifc_Ipc_t* execRxData;   /*Reference to the execute routine on receiving data. */
  char state;   /*State of function.*/
  bool bEnablePrintfOnComm; 
  struct InterProcessComm_t* ipc;   /**/
  int32 ctErrorTelg; 
  struct ThreadJc_t* thread;   /**/
  int32 nrofBytesReceived[1];   /**/
  int8 data_rxBuffer[1500];   /*Use a static receive buffer. It is important for C-applications. */
  PtrVal_int8 rxBuffer;   /*For C: store the reference and length of the SimpleArray in the next structure. */
  struct Address_InterProcessComm_t* myAnswerAddress;   /**/
  C_threadRoutine_InterProcessCommRxThread_Ipc_s threadRoutine; 
} InterProcessCommRxThread_Ipc_s;
  

#define sizeof_InterProcessCommRxThread_Ipc_s sizeof(InterProcessCommRxThread_Ipc_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef InterProcessCommRxThread_IpcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define InterProcessCommRxThread_IpcREFDEF
  struct InterProcessCommRxThread_Ipc_t;
  DEFINE_EnhancedRefJc(InterProcessCommRxThread_Ipc);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct InterProcessCommRxThread_Ipc_X_t { ObjectArrayJc head; InterProcessCommRxThread_IpcREF data[50]; } InterProcessCommRxThread_Ipc_X;
typedef struct InterProcessCommRxThread_Ipc_Y_t { ObjectArrayJc head; InterProcessCommRxThread_Ipc_s data[50]; } InterProcessCommRxThread_Ipc_Y;

 extern_C struct ClassJc_t const reflection_InterProcessCommRxThread_Ipc_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_InterProcessCommRxThread_Ipc(OBJP) { CONST_ObjectJc(sizeof(InterProcessCommRxThread_Ipc_s), OBJP, &reflection_InterProcessCommRxThread_Ipc_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_InterProcessCommRxThread_Ipc_F(ObjectJc* othis, ThCxt* _thCxt);


 extern StringJc version_InterProcessCommRxThread_Ipc;   /*Version, history and license.*/

//!!usage: static init code, invoke that one time in start of main.
void initStatic_InterProcessCommRxThread_Ipc();




/**Creates the communication but does not open it yet. See {@link #start()}
The InterProcessComm interface implementation is got depending on
<ul><li>the ownAddrIpc-string
<li>the existing InterProcessComm-Implementation, which analyzes the address-string.
<ul>
It means, the communication is not determined from this implementation, it depends
on the parameter of the ownAddrIpc and the possibilities. 
*/
METHOD_C struct InterProcessCommRxThread_Ipc_t* ctorO_InterProcessCommRxThread_Ipc(ObjectJc* othis, StringJc ownAddrIpc, struct InterProcessCommRx_ifc_Ipc_t* execRxData, ThCxt* _thCxt);

/**Static method to create invokes the constructor.
*/
METHOD_C struct InterProcessCommRxThread_Ipc_t* create_InterProcessCommRxThread_Ipc(/*J2C:static method*/ StringJc ownAddrIpc, struct InterProcessCommRx_ifc_Ipc_t* execRxData, ThCxt* _thCxt);

/**Create any destination address for the given InterprocessComm implementation. 
The Address should be stored in the users space and should be used for {@link #send(byte[], int, Address_InterProcessComm)}
*/
METHOD_C struct Address_InterProcessComm_t* createDstAddr_InterProcessCommRxThread_Ipc(InterProcessCommRxThread_Ipc_s* thiz, StringJc sAddr, ThCxt* _thCxt);

METHOD_C bool openComm_InterProcessCommRxThread_Ipc(InterProcessCommRxThread_Ipc_s* thiz, bool blocking, ThCxt* _thCxt);

/**Start opens the InterProcessComm and starts the receiver thread.
*/
METHOD_C bool start_InterProcessCommRxThread_Ipc(InterProcessCommRxThread_Ipc_s* thiz, ThCxt* _thCxt);

/**Send a telegram to the given dst. It delegates to {@link InterProcessComm#send(byte[], int, Address_InterProcessComm)}.
An address should be create using {@link #createDstAddr(String)}.
*/
METHOD_C int32 send_InterProcessCommRxThread_Ipc(InterProcessCommRxThread_Ipc_s* thiz, PtrVal_int8 data, int32 nrofBytesToSend, struct Address_InterProcessComm_t* dstAddr, ThCxt* _thCxt);

METHOD_C void runThread_InterProcessCommRxThread_Ipc(InterProcessCommRxThread_Ipc_s* thiz, ThCxt* _thCxt);

METHOD_C void receiveAndExecute_InterProcessCommRxThread_Ipc(InterProcessCommRxThread_Ipc_s* thiz, ThCxt* _thCxt);

/**Shutdown the communication, close the thread. This routine should be called 
either on shutdown of the whole system or on closing the inspector functionality.
The inspector functionality can be restarted calling {@link #start(Object)}.

*/
METHOD_C void shutdown_InterProcessCommRxThread_Ipc(InterProcessCommRxThread_Ipc_s* thiz, ThCxt* _thCxt);


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Mtbl_InterProcessCommRxThread_Ipc[]; //marker for methodTable check
typedef struct Mtbl_InterProcessCommRxThread_Ipc_t
{ MtblHeadJc head;
  Mtbl_ObjectJc ObjectJc;
} Mtbl_InterProcessCommRxThread_Ipc;



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class InterProcessCommRxThread_Ipc : private InterProcessCommRxThread_Ipc_s
{ public:

  struct Address_InterProcessComm_t* createDstAddr(StringJcpp sAddr){  return createDstAddr_InterProcessCommRxThread_Ipc(this, sAddr,  null/*_thCxt*/); }

  struct InterProcessCommRxThread_Ipc_t* create(StringJcpp ownAddrIpc, struct InterProcessCommRx_ifc_Ipc_t* execRxData){  return create_InterProcessCommRxThread_Ipc(ownAddrIpc, execRxData,  null/*_thCxt*/); }

  InterProcessCommRxThread_Ipc(StringJcpp ownAddrIpc, struct InterProcessCommRx_ifc_Ipc_t* execRxData){ init_ObjectJc(&this->base.object, sizeof(InterProcessCommRxThread_Ipc_s), 0); setReflection_ObjectJc(&this->base.object, &reflection_InterProcessCommRxThread_Ipc_s, 0); ctorO_InterProcessCommRxThread_Ipc(&this->base.object, ownAddrIpc, execRxData,  null/*_thCxt*/); }

  bool openComm(bool blocking){  return openComm_InterProcessCommRxThread_Ipc(this, blocking,  null/*_thCxt*/); }

  void receiveAndExecute(){ receiveAndExecute_InterProcessCommRxThread_Ipc(this,  null/*_thCxt*/); }

  void runThread(){ runThread_InterProcessCommRxThread_Ipc(this,  null/*_thCxt*/); }

  int32 send(PtrVal_int8 data, int32 nrofBytesToSend, struct Address_InterProcessComm_t* dstAddr){  return send_InterProcessCommRxThread_Ipc(this, data, nrofBytesToSend, dstAddr,  null/*_thCxt*/); }

  void shutdown(){ shutdown_InterProcessCommRxThread_Ipc(this,  null/*_thCxt*/); }

  bool start(){  return start_InterProcessCommRxThread_Ipc(this,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/

#endif //__Ipc2c_InterProcessCommRxThread_Ipc_h__
