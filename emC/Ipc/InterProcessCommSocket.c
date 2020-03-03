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
 * @author: Hartmut Schorrig
 * @content: Implementation of the InterProcessComm for Socket.
 * @changes:
 * 2010-01-22 Hartmut: corr: Address_InterProcessComm::internalData were not use furthermore, instead the data in the main fields immediately. They are defined as big endian now.
 *
 */
//#define __DEBUGFILE__  //activate it if necessary!

#include "emC/Ipc/InterProcessCommSocket.h"

#include "emC/Base/SimpleC_emC.h"
#include "emC/Base/MemC_emC.h"
#include <emC/Jc/ObjectJc.h>
#include <emC/OSAL/os_endian.h>

#undef byte
#undef boolean
#undef BOOL         
#undef PBOOL

//#include "OSsocket.h"  //include the os specific socket adaption.

#include <emC/OSAL/os_mem.h>
#include <emC/OSAL/os_socket.h>
#include <emC/OSAL/os_error.h>
#include <stdio.h>  //sscanf
#include <stdlib.h> //malloc

#include <string.h>   //using memset





const StringJc sSocket_InterProcessCommSocket = CONST_StringJc("Socket:", 7);


extern const struct ClassJc_t reflection_InterProcessCommSocket_s; 



/**This is the reference address to check the correct address in method table.
 */
//char const* const sign_Mtbl_InterProcessComm = &identText_sign_Mtbl_InterProcessComm;



/**The used type of socketAddr is the same as defined in header! */
#define Address_InterProcessComm_Socket_s Address_InterProcessComm_s



int32 xxxgetAddress1_Address_InterProcessComm_SocketF(Address_InterProcessComm_s* ythis)
{ Address_InterProcessComm_Socket_s* adrSock = SIMPLE_CAST(Address_InterProcessComm_Socket_s*,ythis);
  return ythis->address1;
  //int16 ipPort = ntohs(((OS_SOCKADDR*)adrSock->internalData).sin_port);
  //return ipPort;
}

int32 xxxgetAddress2_Address_InterProcessComm_SocketF(Address_InterProcessComm_s* ythis)
{ Address_InterProcessComm_Socket_s* adrSock = SIMPLE_CAST(Address_InterProcessComm_Socket_s*, ythis);
  //TRICKY: this area is either a char[4] or a analogical unit with the same byte signification
  return ythis->address2;
  //int32 ipAddr = ntohl(*(int32*)(&((OS_SOCKADDR*)adrSock->internalData).sin_addr));
  //return ipAddr;
}

void xxxsetAddress1_Address_InterProcessComm_SocketF(Address_InterProcessComm_s* ythis, int32 address1)
{ //Address_InterProcessComm_Socket_s* adrSock = SIMPLE_CAST(Address_InterProcessComm_Socket_s*, ythis);
  ythis->address1 = address1;
  //TODO use only this information.
  //((OS_SOCKADDR*)adrSock->internalData)->sin_port = htons((int16)(address1));
}

void xxxsetAddress2_Address_InterProcessComm_SocketF(Address_InterProcessComm_s* ythis, int32 address2)
{ Address_InterProcessComm_Socket_s* adrSock = SIMPLE_CAST(Address_InterProcessComm_Socket_s*, ythis);
  ythis->address2 = address2;
  //TODO use only this information.
  //TRICKY: this area is either a char[4] or a analogical unit with the same byte signification
  //*(int32*)(&((OS_SOCKADDR*)adrSock->internalData)->sin_addr) = htonl(address2);  //Speichert ipAddr in Big endian
}




/**Initializes a OS_SOCKADDR from an Address_InterProcessComm. */
static void set_AddressIPC_OS_SOCKADDR(OS_SOCKADDR* dst, Address_InterProcessComm_s* src)
{
  set_OS_SOCKADDR(dst, src->address2, (uint16)src->address1); 
}


/**Get address from a OS_SOCKADDR to Address_InterProcessComm. */
static void set_OS_SOCKADDR_AddressIPC(Address_InterProcessComm_s* dst, OS_SOCKADDR* src)
{
  dst->address1 = src->address1; //getInt16BigEndian(&src->sin_port);
  dst->address2 = src->address2; //getInt32BigEndian(&src->sin_addr.s_addr);
}






Address_InterProcessComm_Socket_s* ctorM_zzi_Address_InterProcessComm_Socket_s(MemC rawMem, const char *protocol, char *sIpAdr, int nPort)
{
  Address_InterProcessComm_Socket_s* ythis = PTR_MemC(rawMem, Address_InterProcessComm_Socket_s);
  init0_MemC(rawMem);
  
  strcpy_emC(ythis->sType, protocol, sizeof(ythis->sType));

  

  //os_SOCKADDR->sa_family = AF_INET;
  //os_SOCKADDR->sin_port = FW_HTON16(nPort);
  //setInt16BigEndian((int16BigEndian*)&os_SOCKADDR->sin_port, nPort);
  ythis->address1 = nPort;
  //default use the address of "localhost"

  if (*sIpAdr == 0)
  { //no address specification
    //TRICKY: this area is either a char[4] or a analogical unit with the same byte signification
    //((OS_SOCKADDR*)ythis->internalData)->ip.addr32 =  kReceiveFromAll_OS_SOCKADDR;
    ythis->address2 = kReceiveFromAll_OS_SOCKADDR;
  }
  else
  { //((OS_SOCKADDR*)ythis->internalData)->sin_addr.S_un.S_addr =  inet_addr(sIpAdr); //INADDR_ANY;
    //convert a.b.c.d    to     d.c.b.a, and then to number
    int np1 = 0;
    int np2 = 0;
    int np3 = 0;
    int np4 = 0;
                                              //a    b      c     d
    sscanf(sIpAdr, " %d . %d . %d . %d ", &np1, &np2, &np3, &np4);
    ythis->address2 = (((uint32)np4)<<24) + (((uint32)np3)<<16) + (((uint32)np2)<<8) + np1;

  }
  return ythis;
}



Address_InterProcessComm_Socket_s* ctorM_zii_Address_InterProcessComm_Socket_s(MemC rawMem, const char *protocol, int32 ipAddr, int nPort)
{
  Address_InterProcessComm_Socket_s* ythis = PTR_MemC(rawMem, Address_InterProcessComm_Socket_s);
  init0_MemC(rawMem);

  strcpy_emC(ythis->sType, protocol, sizeof(ythis->sType));

  //((OS_SOCKADDR*)ythis->internalData)->sa_family = AF_INET;
  //((OS_SOCKADDR*)ythis->internalData)->sin_port = FW_HTON16((uint16)nPort);               //Speichert nPort in Big endian order
  //NOTE: cast sin_port to int16BigEndian because it should be written as big endian, the concept isn*t known by microsoft.
  //NOTE: cast ythis->internalData to (OS_SOCKADDR*) because it is so.
  //setInt16BigEndian( (int16BigEndian*)( ((OS_SOCKADDR*)(ythis->internalData))->sin_port ), (uint16)nPort);               //Speichert nPort in Big endian order
  ythis->address1 = nPort;
  //*(uint32*)(&((OS_SOCKADDR*)ythis->internalData)->ip.sin_addr) = FW_HTON32(ipAddr);  //Speichert ipAddr in Big endian order
  ythis->address2 = ipAddr;
  return ythis;
}


Address_InterProcessComm_s* ctorO_Address_InterProcessCommSocket(ObjectJc* othis, const char *protocol, int32 ipAddr, int nPort)
{ 
  Address_InterProcessComm_s* ythis = (Address_InterProcessComm_s*)othis; 
  STACKTRC_ENTRY("ctorO_Address_InterProcessCommSocket");
  checkConsistence_ObjectJc(othis, sizeof(Address_InterProcessComm_s), &reflection_Address_InterProcessComm, _thCxt);

  strcpy_emC(ythis->sType, protocol, sizeof(ythis->sType));

  //((OS_SOCKADDR*)ythis->internalData)->sa_family = AF_INET;
  //((OS_SOCKADDR*)ythis->internalData)->sin_port = FW_HTON16((uint16)nPort);               //Speichert nPort in Big endian order
  ythis->address1 = nPort;
  //*(uint32*)(&((OS_SOCKADDR*)ythis->internalData)->ip.sin_addr) = FW_HTON32(ipAddr);  //Speichert ipAddr in Big endian order
  ythis->address2 = ipAddr;
  STACKTRC_LEAVE; return ythis;
}


/******************************************************************************************
 * Adaption off InterProcessCommCallback
 ******************************************************************************************/
#ifdef __cplusplus__
/*Implementation of C-methods uses the C++-Interface. */

void errorConnection_InterprocessCommCallbackAdapCpp(struct InterprocessCommCallback_t* ythis, int error)
{ InterProcessCommCallback* zthis = SIMPLE_CAST(InterProcessCommCallback*, ythis);  //directly use the impersonator type.
  zthis->errorConnection(error);
}

void readyConnection_InterprocessCommCallbackAdapCpp(struct InterprocessCommCallback_t* ythis, int info)
{ InterProcessCommCallback* zthis = SIMPLE_CAST(InterProcessCommCallback*, ythis);  //directly use the impersonator type.
  zthis->readyConnection(info);
}

void acknDataTrans_InterprocessCommCallbackAdapCpp(struct InterprocessCommCallback_t* ythis, int error)
{ InterProcessCommCallback* zthis = SIMPLE_CAST(InterProcessCommCallback*, ythis);  //directly use the impersonator type.
  zthis->acknDataTrans(error);
}

void dataAvailable_InterprocessCommCallbackAdapCpp(struct InterprocessCommCallback_t* ythis, int nrofBytes)
{ InterProcessCommCallback* zthis = SIMPLE_CAST(InterProcessCommCallback*, ythis);  //directly use the impersonator type.
  zthis->dataAvailable(nrofBytes);
}
#else
//pure C-variant - TODO not implemented yet. 
void errorConnection_InterprocessCommCallbackAdapCpp(struct InterprocessCommCallback_t* ythis, int error)
{ }

void readyConnection_InterprocessCommCallbackAdapCpp(struct InterprocessCommCallback_t* ythis, int info)
{ }

void acknDataTrans_InterprocessCommCallbackAdapCpp(struct InterprocessCommCallback_t* ythis, int error)
{ }

void dataAvailable_InterprocessCommCallbackAdapCpp(struct InterprocessCommCallback_t* ythis, int nrofBytes)
{ }

#endif //__cplusplus__


Mtbl_InterProcessCommCallback const mtbl_InterprocessCommCallbackAdapCpp =
{ errorConnection_InterprocessCommCallbackAdapCpp
, readyConnection_InterprocessCommCallbackAdapCpp
, acknDataTrans_InterprocessCommCallbackAdapCpp
, dataAvailable_InterprocessCommCallbackAdapCpp
};



//***************************************************************************************************************
/** This class implements the interprocess communication for Sockets with UDP-IP telegrams on Windows.
*/
/**********************************************************************************/



typedef enum{ kDataBufferSize_InterProcessCommSocket_s = 1500}_eXYZ;



/**The C-struct with all data. C++ is implemented below based on this struct. */
typedef struct InterProcessCommSocket_t
{
  union{ InterProcessComm_s InterProcessComm; ObjectJc object; } ifc;
  
  Mtbl_InterProcessComm const* mtblInterProcessComm;

  /** True if the Socket startup is done, false on init. */
  bool bStartupDone;

  /** the used socket from windows. */
  OS_DatagramSocket mySocket;

  OS_StreamSocket myStreamSocket;

  OS_ServerSocket myServerSocket;

	Address_InterProcessComm_Socket_s* adrDest;

  /**This address comes from a remote device, it isn't known by programming.
   * It is the last sender address from UDP or the connection address from TCP-Server
   */
	Address_InterProcessComm_Socket_s* adrReceive;

	Address_InterProcessComm_Socket_s* adrMy;

  char sName[40];

  MemUnit rxBuffer[kDataBufferSize_InterProcessCommSocket_s];

  bool isFreeRxBuffer;

	int m_nSocketType; //SOCK_STREAM, SOCK_DGRAM

  #define kDatagram_InterProcessCommSocket 2
  #define kStream_InterProcessCommSocket 1


#ifdef __DEBUGFILE__
  /**Only for debug output*/
  FILE* fDebug;

  /**Only for debug output: counter of debug files.*/
  int nDebugFile;
#endif


  /** -1 bei UDP, 0 bei client, 1 bei einfachem Server, 2... bei Mehrfachserver */
  int nServerPorts;

  /**Handle des gelistene Serverports*/
  OS_StreamSocket openedServerPort;

}InterProcessCommSocket_s;



/***********************************************************************************************
 *forward declared subroutines only for the intern needed one.
 */
METHOD_C void freeData_InterProcessCommSocket(ObjectJc* ythis, MemC data);


METHOD_C MemC getDataBuffer_InterProcessCommSocket(InterProcessCommSocket_s* ythis);



/**This method supplies the last socket error, but always as negativ value.
   The negativ value is a flag for error. The method translateErrorMessage_InterProcessComm consideres the negativ value.
   The inside called osal method os_socketError() is os dependend and supplies a positive value mostly.
 */
static int socketError_InterProcessComm()
{ int retval = 0; //os_socketError();
  if(retval == 0)
  { retval = UnkonwError_InterProcessComm;
  }
  else if (retval >0)
  { retval = - retval;
  }
  return retval;
}



InterProcessComm_s* ctor_InterProcessCommSocket(InterProcessCommSocket_s* ythis, Address_InterProcessComm_Socket_s* ownAddress)
//InterProcessCommImplement::InterProcessCommImplement(Address_InterProcessComm_Socket_s* ownAddress)
{
  int zName;
  ythis->mtblInterProcessComm = &mtblInterProcessCommSocket.mtbl;
  ythis->adrMy = ownAddress;
  //((OS_SOCKADDR*)&ythis->adrMy->internalData)->sin_port = FW_HTON16((uint16)ythis->adrMy->address1);               //Speichert nPort in Big endian order
  //((OS_SOCKADDR*)&ythis->adrMy->internalData)->ip.addr32 = FW_HTON32(ythis->adrMy->address2);               //Speichert nPort in Big endian order

  //put the informations in ownAddress as name of instance, for reports and debugging.
  memset(ythis->sName, 0, sizeof(ythis->sName));
  zName =sprintf (ythis->sName, "%d.%d.%d.%d:%d "
                     , (int)((ownAddress->address2 >> 24) & 0xff)
                     , (int)((ownAddress->address2 >> 16) & 0xff)
                     , (int)((ownAddress->address2 >> 8) & 0xff)
                     , (int)((ownAddress->address2) & 0xff)
                     , (int)((ownAddress->address1 ))
                     //, (uint)(((OS_SOCKADDR*)ownAddress->internalData)->ip.sin_addr[0]) & 0xff
                     //, (uint)(((OS_SOCKADDR*)ownAddress->internalData)->ip.sin_addr[1]) & 0xff
                     //, (uint)(((OS_SOCKADDR*)ownAddress->internalData)->ip.sin_addr[2]) & 0xff
                     //, (uint)(((OS_SOCKADDR*)ownAddress->internalData)->ip.sin_addr[3]) & 0xff
                     //, (uint)FW_NTOH16(((OS_SOCKADDR*)ownAddress->internalData)->sin_port)
                     );
  if((zName > 0) && ((sizeof(ythis->sName) - zName -1) > 0)){ strcpy_emC(ythis->sName + zName, ownAddress->sType, sizeof(ythis->sName) - zName -1); }

  //check type in ownAddress, the result is setting of nServerPorts.
  if (strncmp(ownAddress->sType, "UDP", 3) == 0 || strncmp(ownAddress->sType, "udp", 3) == 0)
  { ythis->m_nSocketType = kDatagram_InterProcessCommSocket;
    ythis->nServerPorts = -1;  //UDP
  }
  else
  { ythis->m_nSocketType = kStream_InterProcessCommSocket;
    if(strcmp(ownAddress->sType, "TCPserver")== 0 || strcmp(ownAddress->sType, "tcpServer")== 0 )
    { ythis->nServerPorts = 1;
    }
    else
    { ythis->nServerPorts = 0;  //client
    }
  }

  freeData_InterProcessCommSocket(&ythis->ifc.object, build_MemC(ythis->rxBuffer, sizeof(ythis->rxBuffer)));

  ythis->mySocket.socket.socket = 0;
  ythis->adrDest = NULL;
  ythis->bStartupDone = false;

  #ifdef __DEBUGFILE__
    ythis->fDebug = null;
    ythis->nDebugFile = 1;
  #endif
  return &ythis->ifc.InterProcessComm;
}



InterProcessCommSocket_s* ctorO_InterProcessCommSocket(ObjectJc* othis, Address_InterProcessComm_s * addr, struct ThreadContext_emC_t* _thCxt)
{
  //InterProcessComm_s* ret;
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)othis;
  STACKTRC_TENTRY("ctorO_InterProcessCommSocket");
  checkConsistence_ObjectJc(othis, sizeof(InterProcessCommSocket_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_InterProcessCommSocket_s, sizeof(InterProcessCommSocket_s));  
  ctor_InterProcessCommSocket(ythis, addr);
  return ythis;
}



bool equals_InterProcessCommSocket(const struct Address_InterProcessComm_t* address1P, const struct Address_InterProcessComm_t* address2P)
//bool InterProcessCommImplement::equals(const struct Address_InterProcessComm_t* address1P, const struct Address_InterProcessComm_t* address2P)
{
  /*cast to realy derived class. addressP can only be an instance of Address_InterProcessComm
    because the FactorySocketInterProcessComm::makeOwnAddress is the only method to make instances.
  */
  Address_InterProcessComm_Socket_s* address1 = (Address_InterProcessComm_Socket_s*)(address1P);
  Address_InterProcessComm_Socket_s* address2 = (Address_InterProcessComm_Socket_s*)(address2P);

  if(  address1->address1 == address2->address2
    && address1->address2 == address2->address1
    )
  { return true;
  }
  else return false;
}


//int InterProcessCommImplement::open(struct Address_InterProcessComm_t* destAddress, bool isBlocking, InterProcessCommCallback* callback)
int open_InterProcessCommSocket
( ObjectJc* xthis
, Address_InterProcessComm_s* destAddress
, bool isBlocking
//, struct InterProcessCommCallback_t* objCallback
//, Mtbl_InterProcessCommCallback const* mtblCallback
)
{ //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSocket(). 
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)xthis;  
  int nRetVal = 0;
  if(ythis->mtblInterProcessComm != &mtblInterProcessCommSocket.mtbl)
  { return 0x80000001;  //error THRow may by better!!!
  }

  ythis->adrReceive = null;
  //ythis->openedServerPort = 0;

  ythis->adrDest = SIMPLE_CAST(Address_InterProcessComm_Socket_s*,destAddress);

  #if 0 //enthalten in os_socket.h for windows
  if(!bStartupDone)
  { WSADATA wsa;
    int nError = WSAStartup(0x0002, &wsa);
    if(nError != 0)
    { ErrorSocket();
      goto End;
    }
  }
  #endif

  /*cast to realy derived class. ownAddressP can only be an instance of Address_InterProcessComm
    because the FactorySocketInterProcessComm::makeOwnAddress is the only method to make instances.
  */
	if(ythis->mySocket.socket.socket == 0)
	{ //first open, create the socket:
		if (ythis->m_nSocketType == kStream_InterProcessCommSocket)
		{
			nRetVal = os_createStreamSocket(&ythis->myStreamSocket);

		}
		else // SOCK_DGRAM
		{
			nRetVal = os_createDatagramSocket(&ythis->mySocket);
    }

    if(nRetVal == OS_OK)
		{ nRetVal = os_setNonBlocking(ythis->mySocket, !isBlocking);
    }

    if(nRetVal >=0)
    {		//int nBindOk = bind(mySocket, adrMy->getSocketAddress(), adrMy->getSocketAddressSize());
  		//int nBindOk = os_bind(mySocket, (OSSOCKADDR*)(((OS_SOCKADDR*)ownAddress->internalData)), sizeof(adrMy->socketAddr));
  		OS_SOCKADDR addressee_sockadr;  //The destination address in form of os_socket-conventions.
      set_AddressIPC_OS_SOCKADDR(&addressee_sockadr, ythis->adrMy);
      nRetVal = os_bind(ythis->mySocket.socket, &addressee_sockadr);
      //nRetVal = os_bind(ythis->mySocket, ((OS_SOCKADDR*)ythis->adrMy->internalData), sizeof(OS_SOCKADDR));
    }

    if(nRetVal >=0 && ythis->m_nSocketType == kStream_InterProcessCommSocket)
    {
      if (ythis->nServerPorts == 0)
      { //TCP-client
        if(ythis->adrDest != null)
        { nRetVal = os_connect(ythis->myStreamSocket, /*(sockaddr*)*/(((OS_SOCKADDR*)ythis->adrDest->internalData)));
        }
        else
        { nRetVal = IllegalArgument_InterProcessComm;
        }
      }

      else if(ythis->nServerPorts >=1)
      { nRetVal = os_listen(ythis->myServerSocket, 0x7fffffff); //TODO ist das OK? SOMAXCONN);
      }

    }
	}

  #ifdef __DEBUGFILE__
  if(ythis->fDebug == null && ythis->nDebugFile >=0)
  { char sDebug[40] ={0};
    sprintf(sDebug,"DebugIpc\\ipc%i_%i", ythis->adrMy, ythis->nDebugFile++);
    ythis->fDebug = fopen(sDebug, "wb");  //null if no DebugIpc dir exists.
    if(ythis->fDebug == null)
    { ythis->nDebugFile = -1; //donot try on next open!
    }
  }
  #endif

  return nRetVal;

}







int close_InterProcessCommSocket(ObjectJc* xthis)
//int InterProcessCommImplement::close()
{
  //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSocket(). 
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)xthis;  
  int nRetVal = 0;

 	if (ythis->m_nSocketType == kStream_InterProcessCommSocket)
  {	os_shutdown( ythis->myStreamSocket.socket, SO_BOTH_DOWN);
  }
	if (os_close( ythis->mySocket.socket ) != 0)
  { nRetVal = socketError_InterProcessComm(); //negative return value
  }
  else
  { ythis->mySocket.socket.socket = 0;
	  ythis->adrDest = NULL;
  }
  return nRetVal;
}



//int InterProcessCommImplement::send(const void* data, int nBytes, Address_InterProcessComm_s* addressee /* = null */)
int send_InterProcessCommSocket(ObjectJc* xthis, MemC dataP, int nBytes, Address_InterProcessComm_s* addressee /* = null */)
{
  //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSocket(). 
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)xthis;  
  int nRet = -1;
  const void* data = PTR_MemC(dataP, void);

	//Address_InterProcessComm_Socket_s* addressee = SIMPLE_CAST(Address_InterProcessComm_Socket_s*,addresseeP);
  //OS_SOCKADDR* addressee_sockadr = (OS_SOCKADDR*)(addressee->internalData);

  if(ythis->nServerPorts >=1)
  { nRet = os_send(ythis->myStreamSocket, data, nBytes, 0);
  }
  else if (addressee != null)
  { OS_SOCKADDR addressee_sockadr;  //The destination address in form of os_socket-conventions.
    set_AddressIPC_OS_SOCKADDR(&addressee_sockadr, addressee);
    //Test-printf drin lassen und wegkommentieren!
    //printf("\n->IPC:%i bytes @%8.8X to %i.%i.%i.%i:%4.4X", nBytes, data, (uint)addressee_sockadr.sin_addr[0], (uint)addressee_sockadr.sin_addr[1], (uint)addressee_sockadr.sin_addr[2], (uint)addressee_sockadr.sin_addr[3], addressee_sockadr.sin_port);
    nRet = os_sendto(ythis->mySocket, (const char*)(data), nBytes, 0, &addressee_sockadr);
  }
  else
  {
    nRet = os_send(ythis->myStreamSocket, (const char*)(data), nBytes, 0);
  }
	if (nRet < 0)
	{
  	nRet = socketError_InterProcessComm(); //negative return value
    //ErrorSocket();
	}

  #ifdef __DEBUGFILE__
  if(ythis->fDebug != null)
  { fprintf(ythis->fDebug, "\n>>>>tx_%i: ", nBytes);
    fwrite(data, nBytes, 1, ythis->fDebug);
    fflush(ythis->fDebug);
  }
  #endif

  return nRet;  //nr of bytes if >=0 or error code if <0
}



//void* InterProcessCommImplement::receive(int* nrofBytes, Address_InterProcessComm_s* senderP /* =  null*/)
MemC receiveData_InterProcessCommSocket(ObjectJc* xthis, int32* nrofBytes, MemC buffer, Address_InterProcessComm_s* senderP /* =  null*/)
{
  STACKTRC_ENTRY("receiveData_InterProcessCommSocket");
  //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSocket(). 
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)xthis;  
  int nResult;
  int error = 0;
  /**If the input value of *nrofBytes >0, than a minimal amout of bytes is expected. New feature 2009-06. */ 
  int minNrofBytesToReceive = *nrofBytes;
  /**Result nr of bytes. */
  int nrofBytesReceived = 0;
  /**used receive data pointer. */
  MemC data = {0};

  Address_InterProcessComm_Socket_s* sender = SIMPLE_CAST(Address_InterProcessComm_Socket_s*,senderP);
  OS_SOCKADDR* sender_sockadr = senderP == null ? null : (OS_SOCKADDR*)(senderP->internalData);
  if(minNrofBytesToReceive < 0){ minNrofBytesToReceive = 0; }  //a normal case.
  /**feature. No more as a less nrof bytes should be expected. 
   * This test is to detect possible software errors. The user may forget to initialize *nrofBytes, 
   * than the receiver should wait and loop a long time and nobody may see this situation.
   * But a less nrof Bytes may received always. The feature of requesting a minimal nrofBytes is only sensfull 
   */
  ASSERT(minNrofBytesToReceive < 1000);     
  if(ythis->nServerPorts >=1 && ythis->openedServerPort.socket.socket == 0)
  {   //it is a TCP connection as server:
      if(error==0)
      { int nSockAddrLen = sizeof(*sender_sockadr);
        ythis->adrReceive = (Address_InterProcessComm_Socket_s*)malloc(sizeof(Address_InterProcessComm_Socket_s));
        //openedServerPort = os_accept(mySocket, (sockaddrRm*)&sender->socketAddr, &nSockAddrLen);
        error = os_accept(ythis->myServerSocket, sender_sockadr, &ythis->openedServerPort);
        if(error ==0)
        {
          if(senderP != null)
          { //Transfer the received address from client to the external representation of address.
            set_OS_SOCKADDR_AddressIPC(senderP, sender_sockadr);
            /*
            senderP->address1 = ntohs(sender_sockadr->sin_port);
            senderP->address2 = ((((uint32)sender_sockadr->sin_addr[0])<<24) & 0xff000000)
                              | ((((uint32)sender_sockadr->sin_addr[1])<<16) & 0x00ff0000)
                              | ((((uint32)sender_sockadr->sin_addr[2])<<8 ) & 0x0000ff00)
                              |            sender_sockadr->sin_addr[3];
            */
          }
          error = os_close(ythis->mySocket.socket);
          if(error != 0){ error = socketError_InterProcessComm(); }
          else
          { ythis->myStreamSocket = ythis->openedServerPort;
          }
        }
      }
  }

  if(error == 0)
  { int nrofBytesReceive;
    int nSocketAddrLength = 0;
    /**Cummulative data ptr to receive more as one time if a mindest amount of bytes are required. */
    MemUnit* dataCumm;
    /**desiration, data from buffer or internal. */
    bool bDataIntern;
    
    data = buffer;
    bDataIntern = data.addr == null;
    if(bDataIntern)
    {
      data = getDataBuffer_InterProcessCommSocket(ythis);
      nrofBytesReceive = kDataBufferSize_InterProcessCommSocket_s;
    }
    else
    { /**Given buffer, the number of data bytes should be given also! */
      nrofBytesReceive = size_MemC(buffer);
      ASSERT(nrofBytesReceive >0); 
    }
    dataCumm = PTR_MemC(data, MemUnit);
    if (sender != null)
    { nSocketAddrLength = sizeof(*sender_sockadr);}

    /**Loop to get the mindest number of bytes. */
    do
    { if(ythis->nServerPorts >=1)
      { nResult = os_recv(ythis->myStreamSocket,  (char*)(dataCumm), nrofBytesReceive, 0);
      }
      else if (senderP == null)
      { nResult = os_recv(ythis->myStreamSocket,  (char*)(dataCumm), nrofBytesReceive, 0);
      }
      else
      { nResult = os_recvfrom(ythis->mySocket, (char*)(dataCumm), nrofBytesReceive, 0, /*(sockaddr*)*/sender_sockadr);
        if(senderP != null)
        { //Transfer the received address from partner to the external representation of address.
          set_OS_SOCKADDR_AddressIPC(senderP, sender_sockadr);
          /*
          senderP->address1 = ntohs(sender_sockadr->sin_port);
          senderP->address2 = (((uint32)sender_sockadr->sin_addr[0])<<24)
                            + (((uint32)sender_sockadr->sin_addr[1])<<16)
                            + (((uint32)sender_sockadr->sin_addr[2])<<8)
                            +           sender_sockadr->sin_addr[3];
          */
          //let printf here, but comment it, to use for test
          //printf("\nIPC recvfrom(%i from %8.8X:%4.4X ", nResult, senderP->address2, senderP->address1);
        }
      }
      if(nResult >0)
      { nrofBytesReceived += nResult;
        nrofBytesReceive -= nResult;
        dataCumm += nResult;
      }
    } while(nResult >= 0 && nrofBytesReceived < minNrofBytesToReceive); ///@10-09-29 it should be correct
    //
    if(nResult <0)
    { //really an error.
      if(bDataIntern){
        freeData_InterProcessCommSocket(&ythis->ifc.object, data); 
      }
      setNull_MemC(data);
      error = socketError_InterProcessComm();  //the nError should be >0, converted to < 0
      //ErrorSocket();

    }
  }
  if(error != 0)
  { *nrofBytes = error < 0 ? error : -error;
  }
  else
  { *nrofBytes = nrofBytesReceived;
  }

  #ifdef __DEBUGFILE__
  if(ythis->fDebug != null)
  { if(error < 0)
    { fprintf(ythis->fDebug, "\n>>>>rxError_%i: ", -error);
    }
    else
    { fprintf(ythis->fDebug, "\n>>>>rx_%i: ", nResult);
      fwrite(PTR_MemC(data, void), nResult, 1, ythis->fDebug);
    }
    fflush(ythis->fDebug);
  }
  #endif
  STACKTRC_RETURN data; //build_MemC(data, nrofBytesReceived);
};




//void* InterProcessCommImplement::receive(int* nrofBytes, Address_InterProcessComm_s* senderP /* =  null*/)
MemC receive_InterProcessCommSocket(ObjectJc* ithis, int32* nrofBytes, Address_InterProcessComm_s* senderP /* =  null*/)
{ MemC nullBuffer = {0};
  *nrofBytes = 0; //default: receive the most available nrof data.
  return receiveData_InterProcessCommSocket(ithis, nrofBytes, nullBuffer, senderP);
}









//int InterProcessCommImplement::dataAvailable()
int dataAvailable_InterProcessCommSocket(ObjectJc* ythis)
{ return 0;
}


int abortReceive_InterProcessCommSocket(ObjectJc* ythis)
{
  return 0;
}


//int InterProcessCommImplement::checkConnection()
int checkConnection_InterProcessCommSocket(ObjectJc* ythis)
{ return 0;
}




//void* InterProcessCommImplement::getDataBuffer()
MemC getDataBuffer_InterProcessCommSocket(InterProcessCommSocket_s* ythis)
{ MemC ret = {0};
  if(ythis->isFreeRxBuffer == true)
  { ythis->isFreeRxBuffer = false;
    SET_MemC(ret, ythis->rxBuffer, sizeof(ythis->rxBuffer));
  }
  else
  { ALLOC_MemC(ret, kDataBufferSize_InterProcessCommSocket_s);
  }
  return ret;
}



void freeData_InterProcessCommSocket(ObjectJc* xthis, MemC data)
//void InterProcessCommImplement::freeData(void* data)
{
  //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSocket(). 
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)xthis;  
  if(PTR_MemC(data, char) == ythis->rxBuffer)
  { memset(&ythis->rxBuffer, 0, sizeof(ythis->rxBuffer));
    ythis->isFreeRxBuffer = true;
  }
  else
  { freeM_MemC(data);
  }
}



int capacityToSendWithoutBlocking_InterProcessCommSocket(ObjectJc* xthis, int nBytes)
{ //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSocket(). 
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)xthis;  
  
  if(ythis->m_nSocketType == kDatagram_InterProcessCommSocket)
  { return nBytes < 1400 ? nBytes : 1400;
  }
  else if(ythis->m_nSocketType == kStream_InterProcessCommSocket)
  { return nBytes;
  } 
  else
  { //no socket intialized:
    return 0;
  }
}


//const char* InterProcessCommImplement::translateErrorMsg(int nError)
const char* translateErrorMsg_InterProcessCommSocket(ObjectJc* ithis, int nError)
{
	if(nError < 0)
  { //some methods supply a negativ value instead positive socket error value
    //because a positive value is the number of bytes thereby.
    nError = - nError;
  }
  return os_translateSocketErrorMsg(nError);
}

//const char* InterProcessCommImplement::getName()
const char* getName_InterProcessCommSocket(ObjectJc* xthis)
{ //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSocket(). 
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)xthis;  
  return ythis->sName;
}


//struct Address_InterProcessComm_t const* InterProcessCommImplement::getOwnAddress()
struct Address_InterProcessComm_t const* getOwnAddress_InterProcessCommSocket(ObjectJc* xthis)
{ //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSocket(). 
  InterProcessCommSocket_s* ythis = (InterProcessCommSocket_s*)xthis;  
  return ythis->adrMy;
}


int flush_InterProcessCommSocket(ObjectJc* xthis)
{ return 0;
}



MemC getSendBuffer_InterProcessCommSocket(ObjectJc* ythis, int len)
{ MemC mem = {0, NULL};
  return mem; //not supported here.
}


Address_InterProcessComm_s* createAddressEmpty_InterProcessCommSocket(ObjectJc* ipcImpl)
{ Address_InterProcessComm_s* addr;
  ObjectJc* oAddr;
  STACKTRC_ENTRY("createAddressEmpty_InterProcessComm");
  oAddr = alloc_ObjectJc(sizeof(Address_InterProcessComm_s), 0, _thCxt);
  addr = ctorO_Address_InterProcessComm(oAddr, _thCxt);
  STACKTRC_LEAVE; return addr;
}



Address_InterProcessComm_s* createAddress_s_InterProcessCommSocket(ObjectJc* ipcImpl, StringJc sAddr)
{ Address_InterProcessComm_s* addr;
  ObjectJc* oAddr;
  STACKTRC_ENTRY("createAddress_s_InterProcessCommSocket");
  oAddr = alloc_ObjectJc(sizeof(Address_InterProcessComm_s), 0, _thCxt);
  addr = ctorO_s_Address_InterProcessComm(oAddr, sAddr, _thCxt);
  STACKTRC_LEAVE; return addr;
}

Address_InterProcessComm_s* createAddress_sI_InterProcessCommSocket(ObjectJc* ipcImpl, StringJc sAddr, int32 port)
{ Address_InterProcessComm_s* addr;
  ObjectJc* oAddr;
  STACKTRC_ENTRY("createAddress_sI_InterProcessCommSocket");
  oAddr = alloc_ObjectJc(sizeof(Address_InterProcessComm_s), 0, _thCxt);
  addr = ctorO_sI_Address_InterProcessComm(oAddr, sAddr, port, _thCxt);
  STACKTRC_LEAVE; return addr;
}


Address_InterProcessComm_s* createAddress_II_InterProcessCommSocket(ObjectJc* ipcImpl, int32 nAddr, int32 port)
{ Address_InterProcessComm_s* addr;
  ObjectJc* oAddr;
  STACKTRC_ENTRY("createAddress_I_InterProcessCommSocket");
  oAddr = alloc_ObjectJc(sizeof(Address_InterProcessComm_s), 0, _thCxt);
  addr = ctorO_II_Address_InterProcessComm(oAddr, sSocket_InterProcessCommSocket, nAddr, port, _thCxt);
  STACKTRC_LEAVE; return addr;
}






/**Define the mtbl_InterProcessComm for Sockets
 */
MtblDef_InterProcessCommSocket const mtblInterProcessCommSocket = {
//Mtbl_InterProcessComm const mtbl_InterProcessCommSocket =
{ { sign_Mtbl_InterProcessComm
  , (struct Size_Mtbl_t*)sizeof(Mtbl_InterProcessComm)
  }
, open_InterProcessCommSocket
, close_InterProcessCommSocket
, send_InterProcessCommSocket
, receive_InterProcessCommSocket
, freeData_InterProcessCommSocket
, checkConnection_InterProcessCommSocket
, capacityToSendWithoutBlocking_InterProcessCommSocket
, dataAvailable_InterProcessCommSocket
, abortReceive_InterProcessCommSocket
, getName_InterProcessCommSocket
, getOwnAddress_InterProcessCommSocket
, equals_InterProcessCommSocket
, translateErrorMsg_InterProcessCommSocket
, flush_InterProcessCommSocket
, receiveData_InterProcessCommSocket
, getSendBuffer_InterProcessCommSocket
, createAddressEmpty_InterProcessCommSocket
, createAddress_s_InterProcessCommSocket
, createAddress_sI_InterProcessCommSocket
, createAddress_II_InterProcessCommSocket
}, { signEnd_Mtbl_ObjectJc, null } }; //Mtbl
; 



#include <emC/Jc/ReflectionJc.h>
const ClassJc reflection_InterProcessCommSocket_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc) 
, "InterProcessCommSocket_s"
,  0 //position of ObjectJc
, sizeof(InterProcessCommSocket_s)
, null //(FieldJcArray const*)&reflection_Fields_InterProcessCommSocket_s
, null //method
, null //(ClassOffset_idxMtblJcARRAY*)&superclasses_InterProcessCommSocket_s //superclass
, null //interfaces
, 0    //modifiers
, &mtblInterProcessCommSocket.mtbl.head
};






//************************************************************************************************
// FactorySocketInterProcessComm
//


Address_InterProcessComm_s* ctor_Address_InterProcessComm_Socket_s(MemC mem, int32 iAdress, const char* sAdress)
{
  Address_InterProcessComm_Socket_s* pAddress = PTR_MemC(mem, Address_InterProcessComm_Socket_s);
  //if(mem.size < sizeof(Address_InterProcessComm_Socket_s) ) THROW(
// iAdress ist 0, wenn nicht dann ist das PortNr
  if(sAdress == null || *sAdress == 0)
  {
    //pAddress= new Address_InterProcessComm_Socket_s("", "", 0);
  }
  else
  { char sProtocol[100] = {0};
    char sIpAdr[100] = "";
    char sPortNr[100] = {0};
    int nPort = -1;

    int n = sscanf(sAdress, " %[^: ] :// %[^ :] : %i", sProtocol, sIpAdr, &nPort);

    //Port wurde uber parameter iAdress ubergeben
    if (nPort == -1)
      nPort = iAdress;

    if (sIpAdr != null && nPort > -1)
    {
      //unterscheiden sProtocol (TCP, UDP)
      if (  strcmp(sProtocol,"UDP")==0 || strcmp(sProtocol,"udp") == 0
         || strcmp(sProtocol,"TCP")==0 || strcmp(sProtocol,"tcp") == 0
         || strcmp(sProtocol,"TCPserver")==0 || strcmp(sProtocol,"tcpServer") == 0
         )
      {
        //pAddress= new Address_InterProcessComm_Socket_s(sProtocol, sIpAdr, nPort);
      }
      else
      { printf("ung�ltige Addresse %s\n", sAdress);
      }
    }
  }
  return pAddress;
}


/* to remove
InterProcessCommSet_Ipc* create_Set_InterProcessCommSocket_Ipc(char const* protocol, int32 ipAddr, int nPort)
{
  STACKTRC_ENTRY("create_Set_InterProcessCommSocket_Ipc");
  StringJc type = z_StringJc(protocol);
  InterProcessCommSet_Ipc* thiz = (InterProcessCommSet_Ipc*)malloc(sizeof(InterProcessCommSet_Ipc));
  thiz->rxBuffer.ptr__ = & thiz->data_rxBuffer[0]; thiz->rxBuffer.value__ = sizeof( thiz->data_rxBuffer) / sizeof(thiz->data_rxBuffer[0]);
  ObjectJc* oAnsweraddr = alloc_ObjectJc(sizeof_Address_InterProcessComm_s, 0, _thCxt); 
  thiz->myAnswerAddress = ctorO_II_Address_InterProcessComm(oAnsweraddr, type, ipAddr, nPort, _thCxt);
  Address_InterProcessComm* ownAddr = ctorO_II_Address_InterProcessComm(alloc_ObjectJc(sizeof_Address_InterProcessComm_s, 0, _thCxt), type, ipAddr, nPort, _thCxt);
  //thiz->myAnswerAddress = createAddressSocket_InterProcessCommFactorySocket_Ipc_F(null_StringJc, protocolAndOwnAddr, nPort, _thCxt);
  ObjectJc* oipc = alloc_ObjectJc(sizeof_InterProcessCommSocket_s, 0, _thCxt);
  thiz->ipc = &ctorO_InterProcessCommSocket(oipc, ownAddr, _thCxt)->ifc.InterProcessComm;
  
  
  
  STACKTRC_LEAVE;
  return thiz;
}

*/




#include "../Ipc2c/InterProcessCommFactorySocket_Ipc.h"

InterProcessCommFactory_s* getInstance_InterProcessCommFactory()
{
  ObjectJc* oFactory = alloc_ObjectJc(sizeof(InterProcessCommFactorySocket_Ipc_s), 0, null);
  InterProcessCommFactorySocket_Ipc_s* factory = ctorO_InterProcessCommFactorySocket_Ipc(oFactory, null);
  InterProcessCommFactory_s* iFactory = &factory->base.super; //InterProcessCommFactory;
  return  iFactory;
}

InterProcessComm_s* create_InterProcessCommSocket(Address_InterProcessComm_s* ownAddress)
{ MemC mIpc; ALLOC_MemC(mIpc, sizeof(InterProcessCommSocket_s));
  return ctor_InterProcessCommSocket(PTR_MemC(mIpc, InterProcessCommSocket_s), ownAddress);
  //InterProcessCommSocket_s* ipc = (InterProcessCommSocket_s*)malloc(sizeof(InterProcessCommSocket_s));
  //return ctor_InterProcessCommSocket(ipc, ownAddress);
}

