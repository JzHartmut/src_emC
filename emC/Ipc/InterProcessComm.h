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
 *
 * @version 0.91
 * @content Interface for datablock- or stream oriented communication 
 *          between processes, threads or modules, implementable also for Socket..
 * @author Hartmut Schorrig, www.vishia.org
 *
 * list of changes:
 * 2009-11-25: Hartmut: new kReceiveFromAll_Address_InterProcessComm defined with 0
 * 2006...2009 some changes   
 * 2005-09-09: Hartmut creation
******************************************************************************/

/**The InterProcessComm-Interface.
 */
#ifndef __InterProcessComm_h__
#define __InterProcessComm_h__

/**The following file defines struct Object_Jc and class ObjectifcBase_Jcpp. */
#include <emC/Base/Object_emC.h>
#include <emC/Base/MemC_emC.h>
#include <emC/Base/String_emC.h>


struct InterProcessComm_t;
struct AddressInterProcessComm_t;

/**The address of a universal InterProcessComm is a struct with equal content for any characteristic of InterProcessComm.
 * The concretely technical usage may be different.
 * This allows to have a simple struct as outside representation.
 * The factory for an address can create a derived struct, which contains this struct as base, first member.
 * This struct has 48 Bytes.
 */
typedef struct Address_InterProcessComm_t
{
  /**Information about type and size for internal using. */
  //int32 objectIdentSize;

  /**12 bytes reserve, let it untouched. The Factory routine could use it.*/
  //int32 dummy[3];

  union{ ObjectJc object;} base;

  /**Adress parameter 1. Using Socket, this is the portnumber (bit 15..0).
   * The represantation of port respectively endian is the endian of implementation platform.
   */
  int32 address1;

  /**Adress parameter 2. Using Socket, this is the IP-address..
   * The represantation of IP respectively endian is the endian of implementation platform.
   * The hi word is represented in bit 31..24.
   */
  int32 address2;


  /**Type of communication or some special parameter in textual form. */
  char sType[20];

  /**Some internal data for inside representation. */
  char internalData[12];

}Address_InterProcessComm_s;

#define sizeof_Address_InterProcessComm_s sizeof(Address_InterProcessComm_s)

/**If reflections are available, it should stick to this declaration. */
extern_C struct ClassJc_t const refl_Address_InterProcessComm;

/**compatibility. */
#define Address_InterProcessComm Address_InterProcessComm_s


/**Constant for address2 used if receive from all sources should be done. 
 * This is identically with INADRANY in socket.h.
 */  
#define kReceiveFromAll_Address_InterProcessComm 0


#define sizeof_Address_InterProcessComm sizeof(Address_InterProcessComm_s)

METHOD_C Address_InterProcessComm_s* ctorO_Address_InterProcessComm(ObjectJc* othis, ThCxt* _thCxt);

METHOD_C Address_InterProcessComm_s* ctorO_s_Address_InterProcessComm(ObjectJc* othis, StringJc addr, ThCxt* _thCxt);

METHOD_C Address_InterProcessComm_s* ctorO_sI_Address_InterProcessComm(ObjectJc* othis, StringJc addr, int32 port, ThCxt* _thCxt);

METHOD_C Address_InterProcessComm_s* ctorO_II_Address_InterProcessComm(ObjectJc* othis, StringJc type, int32 port, int32 addr2, ThCxt* _thCxt);

METHOD_C Address_InterProcessComm_s* ctorO_ssI_Address_InterProcessComm(ObjectJc* othis, StringJc type, StringJc addr, int32 port, ThCxt* _thCxt);



/*@CLASS_C InterProcessCommFactory @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct InterProcessCommFactory_t
{ union{ ObjectJc object;} base; 
}InterProcessCommFactory_s;

extern_C const struct ClassJc_t refl_InterProcessCommFactory;

InterProcessCommFactory_s* ctorO_InterProcessCommFactory(ObjectJc* othis, ThCxt* _thCxt);

InterProcessCommFactory_s* getInstance_InterProcessCommFactory();



typedef struct Address_InterProcessComm_t* MT_createAddress_InterProcessCommFactory(InterProcessCommFactory_s* thiz, StringJc protocolAndOwnAddr, ThCxt* _thCxt);

typedef struct Address_InterProcessComm_t* MT_createAddress_Port_InterProcessCommFactory(InterProcessCommFactory_s* thiz, StringJc protocolAndOwnAddr, int32 port, ThCxt* _thCxt);

/**Creates a instance.
   @param protocolAndOwnAddr String desribes the type and address.
   @return Instance of interface InterProcessComm or null on error.

 */
typedef struct InterProcessComm_t* MT_create_InterProcessCommFactory(InterProcessCommFactory_s* thiz, StringJc protocolAndOwnAddr, ThCxt* _thCxt);

typedef struct InterProcessComm_t* MT_create_Port_InterProcessCommFactory(InterProcessCommFactory_s* thiz, StringJc protocolAndOwnAddr, int32 port, ThCxt* _thCxt);

typedef struct InterProcessComm_t* MT_create_Addr_InterProcessCommFactory(InterProcessCommFactory_s* thiz, Address_InterProcessComm_s* ownAddress, ThCxt* _thCxt);



extern_C char const sign_Vtbl_InterProcessCommFactory[];


#ifdef DEF_ClassJc_Vtbl
typedef struct Vtbl_InterProcessCommFactory_t
{ VtblHeadJc head;
  

  MT_createAddress_InterProcessCommFactory* createAddress;
  MT_createAddress_Port_InterProcessCommFactory* createAddress_Port;
  MT_create_InterProcessCommFactory* create;
  MT_create_Port_InterProcessCommFactory* create_Port;
  MT_create_Addr_InterProcessCommFactory* create_Addr;

  Vtbl_ObjectJc ObjectJc;

} Vtbl_InterProcessCommFactory;
#endif //def DEF_ClassJc_Vtbl




#if defined(__CPLUSGEN) && defined(__cplusplus)

class InterProcessComm;



/** This class contains only static methods to make and destroy some instances of the InterProcessComm-classes.
  * This is a factory class ready to use especially for TCP-UDP and TCP-IP-Communication.
  * The methods will be found at link time. It is not an interface!
  * Please use special Factory classes to factory other type of instances of InterProcessComm.
*/
class FactorySocketInterProcessComm
{
  public: static InterProcessComm* createInterProcessComm(struct Address_InterProcessComm_t* ownAddress);

  /**makes in instance of a Address_InterProcessComm, localizes on own processor board.
   * Example: createAddress(30000, "UDP"); //PortNr, Local Address for UDP
   * The usage of params depends on implementation
   * @param iAdress: It is an ident on the local system assigned to a communication slot
   * @param sAdress: It is an ident on the local system assigned to a communication slot, (UDP, TCP...)
   */
  public: static struct Address_InterProcessComm_t* createAddress(int32 iAdress, const char* sAdress);//port, slot, ip-addr?

  /**makes in instance of a Address_InterProcessComm, localizes on own processor board.
   * Example: createAddress(30000, "UDP"); //PortNr, Local Address for UDP
   * The usage of params depends on implementation
   * @param adress: It is an ident on the local system assigned to a communication slot, on TCP or UDP the IP-adress
   * @param adress2: It is a second ident on the local system assigned to a communication slot, on TCP or UDP the port.
   * @param sAdress: It is an ident on the local system assigned to a communication slot, (UDP, TCP...)
   */
  public: static struct Address_InterProcessComm_t* createAddress(int32 adress, int32 adress2, const char* sAdress);//port, slot, ip-addr?

//  public: static Address_InterProcessComm* makeAddress();//port, slot, ip-addr?

  /** Destroy a instance of InterProcessComm.
  */
  public: static bool destroyInterProcessComm(InterProcessComm* pIpc);

};

#endif //defined(__CPLUSGEN) && defined(__cplusplus)


//#define InterProcessCommFactory FactorySocketInterProcessComm




/*@CLASS_C InterProcessComm @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**Data of the InterProcessComm handler. Because it is an interface in C, the data are not defineable here.
 * But the Baseclass ObjectJc is used to get some base informations.
 * In the implementation of InterProcessComm, a C_CAST is necessary.
 */
typedef struct InterProcessComm_t
{ union{ ObjectJc object; } base;
}InterProcessComm_s;


#define InterProcessCommC_s InterProcessComm_s

/**Adaption reflection generator CHeader2Reflection does not support build of refl_InterProcessComm_i. */
#define refl_InterProcessComm refl_InterProcessComm 

/**not supported, unknown error. It occurs if the os routine failes, but no error is found. */
#define UnkonwError_InterProcessComm -0x7fff

/**Argument fault as rrror at level of the InterProcessComm-Wrapper. */
#define IllegalArgument_InterProcessComm -0x7ffe


/**This method is declared here, but not implemented. It is a prototype for a users commonly InterProcessComm factory,
 * depend on adress parameter.
 */
InterProcessComm_s* create_InterProcessComm(struct Address_InterProcessComm_t* ownAddress);

/**Define to document the blocking parameter by calling open. */
#define blocking_InterProcessComm true
#define receiverShouldbeBlocking_InterProcessComm 1

/**Define to document the blocking parameter by calling open. */
#define notBlocking_InterProcessComm false
#define receiverShouldbePolling_InterProcessComm 2


struct InterprocessCommCallback_t;

/**Notifies that the connection is aborted with an error.
 * @param error The error code should be used only to inform the user.
 *        It should be the same code as returned by open, send, receive.
 *        It means, it should be negative.
 */
METHOD_C typedef void MT_errorConnection_InterprocessCommCallback(struct InterprocessCommCallback_t* ythis, int error);

/**Notifies that the connection is established successfully.
 * @param info The info code should be used only to inform the user.
 *        It should be the same code as returned by open.
 *        It means, it should be positive.
 */
METHOD_C typedef void MT_readyConnection_InterprocessCommCallback(struct InterprocessCommCallback_t* ythis, int info);


/**Notifies that a send operation is successed or definitely failed.
 * @param error The error code should be used only to inform the user.
 *        It should be the same code as returned by open, send, receive.
 *        It means, it should be negative if an error is occured.
 *        If the value is 0 or positiv, it is a success message.
 */
METHOD_C typedef void MT_acknDataTrans_InterprocessCommCallback(struct InterprocessCommCallback_t* ythis, int error);


/**Notifies that data are available to receive.
 * @param nrofBytes This number is an information about the actual number of bytes.
 *        But the real number of bytes to receive is determined not util receive() is called.
 *        A value of 1 should also be admissible to indicate more than one byte is available.
 *        A value 0 or less should not be used.
 */
METHOD_C typedef void MT_dataAvailable_InterprocessCommCallback(struct InterprocessCommCallback_t* ythis, int nrofBytes);


/**jmp table to implement some different Address_InterProcessComm classes in C language.
 * This is a concept of polymorphism in comparison with with virtual tables in C++.
 */
typedef struct Vtbl_InterProcessCommCallback_t
{ 
  MT_errorConnection_InterprocessCommCallback* errorConnection;
  MT_readyConnection_InterprocessCommCallback* readyConnection;
  MT_acknDataTrans_InterprocessCommCallback*   acknDataTrans;
  MT_dataAvailable_InterprocessCommCallback*   dataAvailable;
}Vtbl_InterProcessCommCallback;


typedef struct InterProcessCommCallback_t
{ ObjectJc obj;
}InterProcessCommCallback_s;



//typedef int MT_open_InterProcessComm(InterProcessComm_i* ythis, struct Address_InterProcessComm_t* destAddress, bool isBlocking, struct InterProcessCommCallback_t* callbackObj, Vtbl_InterProcessCommCallback const* mtblCallBack);
typedef int MT_open_InterProcessComm(ObjectJc* ithis, struct Address_InterProcessComm_t* destAddress, bool isBlocking);
typedef int MT_close_InterProcessComm(ObjectJc* ithis);


/**Sends Data.
   @param data The data to be sent. The user should not touch the buffer after calling here.
          Note: The number of bytes to send is given in nBytes, not in the length-element of data.
          But the length of data is tested for significance. If it is to less, an exception is thrown.
   @param nBytes The number of bytes to be send. It should be >=0.
   @param addressee The addressee, the receiver of the message. If isn't use and should be null 
                    if it is a established connection (for ex. socket TCP). 
   @return Nr of Bytes sendet, if >=0. If <0 its an error code.

 */
typedef int MT_send_InterProcessComm(ObjectJc* ithis, MemC data, int nBytes, Address_InterProcessComm_s* addressee /* = null */);


/**Receive data.
 */
typedef MemC MT_receive_InterProcessComm(ObjectJc* ithis, int32* nrofBytes, Address_InterProcessComm_s* senderP);

/**Receives data. It is the second form with possible given buffer and the possibility to determine the number of receive bytes.
 * This form may be used in any case, it substitutes the form without data-param.
 * @param nrofBytes Reference to an int-variable which contains the number of bytes.
 *        * INPUT: if 0, than the greatest available data block is received and returned.
 *        * INPUT: if >0, than exact the requested nr of bytes are returned. In non-blocking mode, null is returned, if bytes are available, but to less bytes.
 *        * OUTPUT: <0, than an error is occured.
 *        * OUTPUT: >=0, than the number of bytes is returned. 
 * @param data if not null, than this given buffer is used to copy to it. In this case freeData() mustn't call.
 *        If null, than the internal buffer is returned.
 * @return The pointer to data, return null if no data are available and the non-blocking-mode is set or receive is aborted.
 *        returns data if data-param isn't null.  
 */
typedef MemC MT_receiveData_InterProcessComm(ObjectJc* ithis, int32* nrofBytes, MemC buffer, Address_InterProcessComm_s* senderP);
typedef void MT_freeData_InterProcessComm(ObjectJc* ithis, MemC data);

typedef int MT_checkConnection_InterProcessComm(ObjectJc* ithis);
typedef int MT_capacityToSendWithoutBlocking_InterProcessComm(ObjectJc* ithis, int nrofBytesToSend);
typedef int MT_dataAvailable_InterProcessComm(ObjectJc* ithis);
typedef int MT_abortReceive_InterProcessComm(ObjectJc* ithis);

typedef const char* MT_getName_InterProcessComm(ObjectJc* ithis);
typedef struct Address_InterProcessComm_t const* MT_getOwnAddress_InterProcessComm(ObjectJc* ithis);

typedef bool MT_equals_InterProcessComm(const struct Address_InterProcessComm_t* address1P, const struct Address_InterProcessComm_t* address2P);
typedef const char* MT_translateErrorMsg_InterProcessComm(ObjectJc* ithis, int nError);

typedef int MT_flush_InterProcessComm(ObjectJc* ithis);

typedef MemC MT_getSendBuffer_InterProcessComm(ObjectJc* ithis, int len);

typedef struct Address_InterProcessComm_t* MT_createAddressEmpty_InterProcessComm(ObjectJc* ithis);

typedef struct Address_InterProcessComm_t* MT_createAddress_s_InterProcessComm(ObjectJc* ithis, StringJc sAddr);

//typedef struct Address_InterProcessComm_t* MT_createAddress_z_InterProcessComm(ObjectJc* ithis, char const* sAddr);

typedef struct Address_InterProcessComm_t* MT_createAddress_sI_InterProcessComm(ObjectJc* ithis, StringJc sAddr, int32 port);

typedef struct Address_InterProcessComm_t* MT_createAddress_I_InterProcessComm(ObjectJc* ithis, int32 iAddr, int32 port);



/**This is a marker text. The content of text isn't important, but all implementations should use the same address
 * (value of field sign in Vtbl_LogMessageFW).
 */
extern_C char const sign_Vtbl_InterProcessComm[];



#ifdef DEF_ClassJc_Vtbl
typedef struct Vtbl_InterProcessComm_t
{ VtblHeadJc head;
  
  /**The value of sign must be identically with the address of the sign_Vtbl_Message_ifcFW-variable. Use it for safe access. */
  //char const* const* sign;
  /**The sizeTable is really an simple int. But all members of Method table are from pointer type. casted internally. 
   * Check of sizeTable makes possible to use older implementation versions with less methods.
   * NOTE: don't use a void*, because all is compatible with it and no errors are signated.
   */
  //struct Size_Vtbl_t* sizeTable;  

  MT_open_InterProcessComm* open;
  MT_close_InterProcessComm* close;
  MT_send_InterProcessComm* send;
  MT_receive_InterProcessComm* receive;
  MT_freeData_InterProcessComm* freeData;

  MT_checkConnection_InterProcessComm* checkConnection;
  MT_capacityToSendWithoutBlocking_InterProcessComm* capacityToSendWithoutBlocking;
  MT_dataAvailable_InterProcessComm* dataAvailable;
  MT_abortReceive_InterProcessComm* abortReceive;

  MT_getName_InterProcessComm* getName;
  MT_getOwnAddress_InterProcessComm* getOwnAddress;
  MT_equals_InterProcessComm* equals;
  MT_translateErrorMsg_InterProcessComm* translateErrorMsg;
  MT_flush_InterProcessComm* flush;
  MT_receiveData_InterProcessComm* receiveData;
  MT_getSendBuffer_InterProcessComm* getSendBuffer;

  MT_createAddressEmpty_InterProcessComm* createAddressEmpty;
  MT_createAddress_s_InterProcessComm* createAddress_s;
  //MT_createAddress_z_InterProcessComm* createAddressEmpty_z;
  MT_createAddress_sI_InterProcessComm* createAddress_si;
  MT_createAddress_I_InterProcessComm* createAddress_i;
} Vtbl_InterProcessComm;
#endif //def DEF_ClassJc_Vtbl


#if defined(__CPLUSGEN) && defined(__cplusplus)

/** This interface may be implemented by users classes to accept messages from a interprocesscomm.
 *  The generally contract is: If the user is attempt to poll only, the reference to this interfaces
 *  can be supplied as null.
 */
class InterProcessCommCallback
{

  /**Notifies that the connection is aborted with an error.
   * @param error The error code should be used only to inform the user.
   *        It should be the same code as returned by open, send, receive.
   *        It means, it should be negative.
   */
  public: virtual void errorConnection(int error) =0;

  /**Notifies that the connection is established successfully.
   * @param info The info code should be used only to inform the user.
   *        It should be the same code as returned by open.
   *        It means, it should be positive.
   */
  public: virtual void readyConnection(int info) =0;


  /**Notifies that a send operation is successed or definitely failed.
   * @param error The error code should be used only to inform the user.
   *        It should be the same code as returned by open, send, receive.
   *        It means, it should be negative if an error is occured.
   *        If the value is 0 or positiv, it is a success message.
   */
  public: virtual void acknDataTrans(int error) =0;


  /**Notifies that data are available to receive.
   * @param nrofBytes This number is an information about the actual number of bytes.
   *        But the real number of bytes to receive is determined not util receive() is called.
   *        A value of 1 should also be admissible to indicate more than one byte is available.
   *        A value 0 or less should not be used.
   */
  public: virtual void dataAvailable(int nrofBytes) =0;


};



/** This interface is the applicable interface to realize a communication between processes at the same processor board
  *  or between processes via network using UDP/IP.
  * In generally, realization of this class is hardware-depended.
  * An implementation with socket communications (using java.net.Socket*) exists.
  * But the user can realize its own solutions based on this interface, at example
  * with using dual port RAM-communication at system level.
*/
class InterProcessComm: /*public InterProcessCommC, */public ObjectJcpp
{

  /** constant define the using of local communication */
 // public: enum{ kLocalCommunication = -1};


  /** Opens the mailbox. Only called at startup.
      @param destAddress the address to which the communication is established
             if no fix destination <connectionless-based>, then destination = null,
      @param isBlocking, if == true then receive is blocking
             If the implementation doesn't support Blockin/NonBlocking Error occurs.
      @return null if successfull, else ErrorMsg
  */
  public: virtual int open(struct Address_InterProcessComm_t* destAddress, bool isBlocking = true, InterProcessCommCallback* callback = null)=0;

  /** connection-based byte streams need to be connected
  */
  //public: virtual void connect(const DestinationAddress_InterProcessComm* myDestinationAddress)=0;

  /** Closes the mailbox, only to be called on shutdown of the application.
  */
  public: virtual int close()=0;


  /**Sends Data.
     The destination adress is defined on open.
     If a listener is associated with this class, the data will be forwarded to the users evaluation method
     defined in the implementation of the listener. So a evaluation may be execute directly without consideration of the users software
     and without consideration of the realization in this class.
     If no listener is associated, the data will be sent in the kind of realization of this class.
     @param data The data to be sent. The user should not touch the buffer after calling here.
            Note: The number of bytes to send is given in nBytes, not in the length-element of data.
            But the length of data is tested for significance. If it is to less, an exception is thrown.
     @param nBytes The number of bytes to be send.
     @param addressee The addressee, the receiver of the message.
     @return Nr of Bytes sendet, if >=0. If <0 its an error code.

   */
  public: virtual int send( MemC data, int nBytes, struct Address_InterProcessComm_t* destAddress = null)=0; //DestinationAddress_InterProcessComm
//  public: virtual int send(const void* data, int nBytes)=0; //


  /** Tests wether data are available to receive. This is the alternativ method for polling
    * instead of the callback methods dataAvailable() from the callback interface.
    * This method can return 0 also if data are receiveable, if the implementation donot support such quest.
    * @return value less 0: error code, the connection is not available.
    *         If the value is >0, data are available. If 0, no data are available.
    *
    */
  public: virtual int dataAvailable()=0;

  /** Receives a Datagram.
      This method blocks until a Datagram is received or it returns null, see open( isBlocking) .
      If a Datagram is received, the content of the Datagram will copied into the appropriated buffer.
      @param data out: The reference to the buffer containing data is assigned to this referencepointer.
             On error, the reference is not valid. The user should call destroy on this object if it is never used.
      @param sender Buffer for the sender of the message.
      @return Nr of Bytes sendet, if >=0. If <0 its an error code.
  */
  public: virtual MemC receive(int32* nrofBytes, struct Address_InterProcessComm_t* sender =  null); //SenderAddress_InterProcessComm

  /** Abort receiving function
   */
  public: virtual int abortReceive() = 0;


  /** Checks the connection. This is the alternativ method for polling
    * instead of the callback methods errorConnection() and readyConnection().
    * @return value less 0: error code, the connection is not available.
    *         If the value is >=0, the connection is established.
    *
    */
  public: virtual int checkConnection() = 0;


  /** Relinguishes the data buffer, after it is evaluated.
      @param data The buffer delivered from receive!
  */
  public: virtual void freeData(MemC data)=0;



  /** Compare the address to another address, returns true if it is the same address.
    * This method can used to compare a known address with a sender address from InterProcessComm::receive().
    * @param address1 The address to compare.
    * @param address2 The address to compare.
    * return true if the addresses describes the same communication slot. On Pc that is the same IP-Address and the same port.
   */
  public: virtual bool equals(const struct Address_InterProcessComm_t* address1, const struct Address_InterProcessComm_t* address2)=0;
          //operator ==

  //public: virtual const char* getLastErrorMsg(){ return ""; }
  public: virtual InterProcessComm_s* toInterProcessCommC(){ return null; }

  public: virtual const char* translateErrorMsg(int error) = 0;

  /**Argument fault as rrror at level of the InterProcessComm-Wrapper. */
  #define IllegalArgument_InterProcessComm -0x7ffe

  public: virtual const char* getName() = 0;

  //public: virtual const char* getReceiveErrorMsg(bool clearIt);
  //public: virtual const char* getSendErrorMsg(bool clearIt);

  /**Tests wether a next send is done without blocking.
   * If the transfer medium supports this test and it has a limited capacity, the method is helpfull to use.
   * If the medium doesnot support such quest, the nrofBytes is returned. It means, it has a capacity. send is possible
   * but it is not guarented that the send doesnot block.
   * @return nrofBytes of capacity to send without blocking, but not greater than argument nrofBytesToSend.
   *         0 if the next send call will be blocked.
   *         negativ value if any error.
   */
  public: virtual int capacityToSendWithoutBlocking(int nrofBytesToSend){ return nrofBytesToSend; }


  /**Gets the own address of this interProcessComm, it are the receive parameters.
   * The knowledge of receive address may be necessary at user level
   *   if the information about a other receive adress should be communicate to the partner.
   * In most cases the partner knows the sender adress (back-info-argument of receive) from the implementation level,
   *   but in some cases (2-simplex-Ports TCP/UDP) the receive adress is the address getted here.
   */
  public: virtual struct Address_InterProcessComm_t const* getOwnAddress(){ return null; }


  /**Flushs send data to destination. */
  public: virtual int flush(){ return 0; }


  /** Receives with given data buffer, see C-description.
  */
  public: virtual MemC receive(int32* nrofBytes, MemC buffer, struct Address_InterProcessComm_t* sender =  null)=0;


  /**Gets a buffer for send. */
  public: virtual MemC getSendBuffer(int len){ return build_MemC(null, 0);} 

};






/**Class to support transmission in OSI level 5, supports also multipart transmission */
class InterProcessCommOrder : public InterProcessComm
{

  /**Opens a order to transport. This is a OSI-level-5 communication support.
   * All send and receive operations after open are relating to this open call.
   * @param ident A string-identifier.
   * @param nrofBytes Whole number of bytes to transfer, -1 if this number is unknown.
   *        If the nrofBytes is unknown, the summ of send determines it.
   */
  public: virtual int openOrder(const char* ident, int nrofBytes) =0;

  public: virtual int closeOrder()=0;


};

#endif //defined(__CPLUSGEN) && defined(__cplusplus)


/*@CLASS_C InterProcessCommSet_Ipc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
//Only idea, remove it!

/**This is a ready-to-use set for an InterProcessComm communication with receive buffer etc. 
 * The data can be gotten via some factory methods.
 * Use &this->ipc for interprocessComm - routines.
 * /
typedef struct InterProcessCommSet_Ipc_t
{
  union { ObjectJc object; } base; 
  
  struct InterProcessComm_t* ipc;   
  int32 ctErrorTelg; 
  struct ThreadJc_t* thread;   
  int32 nrofBytesReceived[1];   
  int8 data_rxBuffer[1500];   //Use a static receive buffer. It is important for C-applications. 
  int8ARRAY rxBuffer;   //For C: store the reference and length of the SimpleArray in the next structure. 
  struct Address_InterProcessComm_t* myAnswerAddress;   /



}InterProcessCommSet_Ipc;

*/


#endif  /* __InterProcessComm_h__ */
