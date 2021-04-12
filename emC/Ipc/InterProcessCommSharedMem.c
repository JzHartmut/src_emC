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
 * @content: Implementation of the InterProcessComm for SharedMem.
 * @changes:
 * 2010-01-22 Hartmut: corr: Address_InterProcessComm::internalData were not use furthermore, instead the data in the main fields immediately. They are defined as big endian now.
 *
 */
//#define __DEBUGFILE__  //activate it if necessary!

#include <emC/Ipc/InterProcessComm.h>
#include <applStdef_emC.h>
#include "emC/Base/SimpleC_emC.h"
#include "emC/Base/MemC_emC.h"
#include <emC/Jc/ObjectJc.h>
#include <emC/OSAL/os_endian.h>

#undef byte
#undef boolean
#undef BOOL         
#undef PBOOL

//#include "OSSharedMem.h"  //include the os specific SharedMem adaption.

#include <emC/OSAL/os_mem.h>
#include <emC/OSAL/os_error.h>
#include <stdio.h>  //sscanf
#include <stdlib.h> //malloc

#include <string.h>   //using memset




const StringJc sSharedMem_InterProcessCommSharedMem = CONST_StringJc("SharedMem:", 7);

#ifdef DEF_ClassJc_Vtbl

extern const struct ClassJc_t refl_InterProcessCommSharedMem_s; 



/**This is the reference address to check the correct address in method table.
 */
//char const* const sign_Vtbl_InterProcessComm = &identText_sign_Vtbl_InterProcessComm;



/**The used type of SharedMemAddr is the same as defined in header! */
#define Address_InterProcessComm_SharedMem_s Address_InterProcessComm_s











Address_InterProcessComm_SharedMem_s* ctorM_zzi_Address_InterProcessComm_SharedMem_s(MemC rawMem, const char *protocol, char *sIpAdr, int nPort)
{
  Address_InterProcessComm_SharedMem_s* ythis = PTR_MemC(rawMem, Address_InterProcessComm_SharedMem_s);
  init0_MemC(rawMem);
  
  strcpy_emC(ythis->sType, protocol, sizeof(ythis->sType));

  

  ythis->address1 = nPort;

  return ythis;
}



Address_InterProcessComm_SharedMem_s* ctorM_zii_Address_InterProcessComm_SharedMem_s(MemC rawMem, const char *protocol, int32 ipAddr, int nPort)
{
  Address_InterProcessComm_SharedMem_s* ythis = PTR_MemC(rawMem, Address_InterProcessComm_SharedMem_s);
  init0_MemC(rawMem);

  strcpy_emC(ythis->sType, protocol, sizeof(ythis->sType));

  ythis->address1 = nPort;
  ythis->address2 = ipAddr;
  return ythis;
}


Address_InterProcessComm_s* ctorO_Address_InterProcessCommSharedMem(ObjectJc* othis, const char *protocol, int32 ipAddr, int nPort)
{ 
  Address_InterProcessComm_s* ythis = (Address_InterProcessComm_s*)othis; 
  STACKTRC_ENTRY("ctorO_Address_InterProcessCommSharedMem");
  checkConsistence_ObjectJc(othis, sizeof(Address_InterProcessComm_s), &refl_Address_InterProcessComm, _thCxt);

  strcpy_emC(ythis->sType, protocol, sizeof(ythis->sType));

  ythis->address1 = nPort;
  ythis->address2 = ipAddr;
  STACKTRC_LEAVE; return ythis;
}






//***************************************************************************************************************
/** This class implements the interprocess communication for SharedMems with UDP-IP telegrams on Windows.
*/
/**********************************************************************************/



typedef enum{ kDataBufferSize_InterProcessCommSharedMem_s = 1500}_eXYZ;



/**The C-struct with all data. C++ is implemented below based on this struct. */
typedef struct InterProcessCommSharedMem_t
{
  union{ InterProcessComm_s InterProcessComm; ObjectJc object; } ifc;
  
  Vtbl_InterProcessComm const* mtblInterProcessComm;

  /** True if the SharedMem startup is done, false on init. */
  bool bStartupDone;

  /** the used SharedMem from windows. */
  //OS_SharedMem mySharedMem;

	Address_InterProcessComm_SharedMem_s* adrDest;

  /**This address comes from a remote device, it isn't known by programming.
   * It is the last sender address from UDP or the connection address from TCP-Server
   */
	Address_InterProcessComm_SharedMem_s* adrReceive;

	Address_InterProcessComm_SharedMem_s* adrMy;

  char sName[40];

  MemUnit rxBuffer[kDataBufferSize_InterProcessCommSharedMem_s];

  bool isFreeRxBuffer;

	int m_nSharedMemType; //SOCK_STREAM, SOCK_DGRAM


#ifdef __DEBUGFILE__
  /**Only for debug output*/
  FILE* fDebug;

  /**Only for debug output: counter of debug files.*/
  int nDebugFile;
#endif


  /** -1 bei UDP, 0 bei client, 1 bei einfachem Server, 2... bei Mehrfachserver */
  int nServerPorts;


}InterProcessCommSharedMem_s;



/***********************************************************************************************
 *forward declared subroutines only for the intern needed one.
 */
METHOD_C void freeData_InterProcessCommSharedMem(ObjectJc* ythis, MemC data);


METHOD_C MemC getDataBuffer_InterProcessCommSharedMem(InterProcessCommSharedMem_s* ythis);



/**This method supplies the last SharedMem error, but always as negativ value.
   The negativ value is a flag for error. The method translateErrorMessage_InterProcessComm consideres the negativ value.
   The inside called osal method os_SharedMemError() is os dependend and supplies a positive value mostly.
 */
static int SharedMemError_InterProcessComm()
{ int retval = 0; //os_SharedMemError();
  if(retval == 0)
  { retval = UnkonwError_InterProcessComm;
  }
  else if (retval >0)
  { retval = - retval;
  }
  return retval;
}



InterProcessComm_s* ctor_InterProcessCommSharedMem(InterProcessCommSharedMem_s* ythis, Address_InterProcessComm_SharedMem_s* ownAddress)
//InterProcessCommImplement::InterProcessCommImplement(Address_InterProcessComm_SharedMem_s* ownAddress)
{
  //int zName;
  //ythis->mtblInterProcessComm = &mtblInterProcessCommSharedMem.mtbl;
  ythis->adrMy = ownAddress;

  //put the informations in ownAddress as name of instance, for reports and debugging.
  memset(ythis->sName, 0, sizeof(ythis->sName));
  freeData_InterProcessCommSharedMem(&ythis->ifc.object, build_MemC(ythis->rxBuffer, sizeof(ythis->rxBuffer)));

  //ythis->mySharedMem = 0;
  ythis->adrDest = NULL;
  ythis->bStartupDone = false;

  #ifdef __DEBUGFILE__
    ythis->fDebug = null;
    ythis->nDebugFile = 1;
  #endif
  return &ythis->ifc.InterProcessComm;
}



InterProcessCommSharedMem_s* ctorO_InterProcessCommSharedMem(ObjectJc* othis, Address_InterProcessComm_s * addr, struct ThreadContext_emC_t* _thCxt)
{
  //InterProcessComm_s* ret;
  InterProcessCommSharedMem_s* ythis = (InterProcessCommSharedMem_s*)othis;
  STACKTRC_TENTRY("ctorO_InterProcessCommSharedMem");
  checkConsistence_ObjectJc(othis, sizeof(InterProcessCommSharedMem_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &refl_InterProcessCommSharedMem_s, sizeof(InterProcessCommSharedMem_s));  
  ctor_InterProcessCommSharedMem(ythis, addr);
  return ythis;
}



bool equals_InterProcessCommSharedMem(const struct Address_InterProcessComm_t* address1P, const struct Address_InterProcessComm_t* address2P)
{
  /*cast to realy derived class. addressP can only be an instance of Address_InterProcessComm
    because the FactorySharedMemInterProcessComm::makeOwnAddress is the only method to make instances.
  */
  Address_InterProcessComm_SharedMem_s* address1 = (Address_InterProcessComm_SharedMem_s*)(address1P);
  Address_InterProcessComm_SharedMem_s* address2 = (Address_InterProcessComm_SharedMem_s*)(address2P);

  if(  address1->address1 == address2->address2
    && address1->address2 == address2->address1
    )
  { return true;
  }
  else return false;
}


//int InterProcessCommImplement::open(struct Address_InterProcessComm_t* destAddress, bool isBlocking, InterProcessCommCallback* callback)
int open_InterProcessCommSharedMem
( ObjectJc* xthis
, Address_InterProcessComm_s* destAddress
, bool isBlocking
//, struct InterProcessCommCallback_t* objCallback
//, Vtbl_InterProcessCommCallback const* mtblCallback
)
{ //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSharedMem(). 
  InterProcessCommSharedMem_s* ythis = (InterProcessCommSharedMem_s*)xthis;  
  int nRetVal = 0x80000000; //error
  //if(ythis->mtblInterProcessComm != &mtblInterProcessCommSharedMem.mtbl)
  { return 0x80000001;  //error THRow may by better!!!
  }

  ythis->adrReceive = null;
  /*cast to realy derived class. ownAddressP can only be an instance of Address_InterProcessComm
    because the FactorySharedMemInterProcessComm::makeOwnAddress is the only method to make instances.
  */
  return nRetVal;

}







int close_InterProcessCommSharedMem(ObjectJc* xthis)
//int InterProcessCommImplement::close()
{
  //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSharedMem(). 
  InterProcessCommSharedMem_s* ythis = (InterProcessCommSharedMem_s*)xthis;  
  int nRetVal = 0;

  return nRetVal;
}



//int InterProcessCommImplement::send(const void* data, int nBytes, Address_InterProcessComm_s* addressee /* = null */)
int send_InterProcessCommSharedMem(ObjectJc* xthis, MemC dataP, int nBytes, Address_InterProcessComm_s* addressee /* = null */)
{
  //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSharedMem(). 
  InterProcessCommSharedMem_s* ythis = (InterProcessCommSharedMem_s*)xthis;  
  int nRet = -1;
  const void* data = PTR_MemC(dataP, void);

  return nRet;  //nr of bytes if >=0 or error code if <0
}



//void* InterProcessCommImplement::receive(int* nrofBytes, Address_InterProcessComm_s* senderP /* =  null*/)
MemC receiveData_InterProcessCommSharedMem(ObjectJc* xthis, int32* nrofBytes, MemC buffer, Address_InterProcessComm_s* senderP /* =  null*/)
{
  //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSharedMem(). 
  return null_MemC; //build_MemC(data, nrofBytesReceived);
};




//void* InterProcessCommImplement::receive(int* nrofBytes, Address_InterProcessComm_s* senderP /* =  null*/)
MemC receive_InterProcessCommSharedMem(ObjectJc* ithis, int32* nrofBytes, Address_InterProcessComm_s* senderP /* =  null*/)
{ MemC nullBuffer = {0};
  *nrofBytes = 0; //default: receive the most available nrof data.
  return receiveData_InterProcessCommSharedMem(ithis, nrofBytes, nullBuffer, senderP);
}









//int InterProcessCommImplement::dataAvailable()
int dataAvailable_InterProcessCommSharedMem(ObjectJc* ythis)
{ return 0;
}


int abortReceive_InterProcessCommSharedMem(ObjectJc* ythis)
{
  return 0;
}


//int InterProcessCommImplement::checkConnection()
int checkConnection_InterProcessCommSharedMem(ObjectJc* ythis)
{ return 0;
}




//void* InterProcessCommImplement::getDataBuffer()
MemC getDataBuffer_InterProcessCommSharedMem(InterProcessCommSharedMem_s* ythis)
{ MemC buffer; 
  if(ythis->isFreeRxBuffer == true)
  { ythis->isFreeRxBuffer = false;
    SET_MemC(buffer, ythis->rxBuffer, sizeof(ythis->rxBuffer));
  }
  else
  { ALLOC_MemC(buffer, kDataBufferSize_InterProcessCommSharedMem_s);
  }
  return buffer; //PTR_MemC(buffer, void);
}



void freeData_InterProcessCommSharedMem(ObjectJc* xthis, MemC dataP)
//void InterProcessCommImplement::freeData(void* data)
{
  void* data = PTR_MemC(dataP, void);
  //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSharedMem(). 
  InterProcessCommSharedMem_s* ythis = (InterProcessCommSharedMem_s*)xthis;  
  if(data == ythis->rxBuffer)
  { memset(&ythis->rxBuffer, 0, sizeof(ythis->rxBuffer));
    ythis->isFreeRxBuffer = true;
  }
  else
  { MemC mem = build_MemC(data, -1); //{ -1, (MemAreaC*)data};
    freeM_MemC(mem);
  }
}



int capacityToSendWithoutBlocking_InterProcessCommSharedMem(ObjectJc* xthis, int nBytes)
{ //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSharedMem(). 
  InterProcessCommSharedMem_s* ythis = (InterProcessCommSharedMem_s*)xthis;  
  
  { //no SharedMem intialized:
    return 0;
  }
}


//const char* InterProcessCommImplement::translateErrorMsg(int nError)
const char* translateErrorMsg_InterProcessCommSharedMem(ObjectJc* ithis, int nError)
{
	if(nError < 0)
  { //some methods supply a negativ value instead positive SharedMem error value
    //because a positive value is the number of bytes thereby.
    nError = - nError;
  }
  return null; //os_translateSharedMemErrorMsg(nError);
}

//const char* InterProcessCommImplement::getName()
const char* getName_InterProcessCommSharedMem(ObjectJc* xthis)
{ //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSharedMem(). 
  InterProcessCommSharedMem_s* ythis = (InterProcessCommSharedMem_s*)xthis;  
  return ythis->sName;
}


//struct Address_InterProcessComm_t const* InterProcessCommImplement::getOwnAddress()
struct Address_InterProcessComm_t const* getOwnAddress_InterProcessCommSharedMem(ObjectJc* xthis)
{ //cast from impersonator type, because this methods are only called with such an instance, supplied from create_InterProcessCommSharedMem(). 
  InterProcessCommSharedMem_s* ythis = (InterProcessCommSharedMem_s*)xthis;  
  return ythis->adrMy;
}


int flush_InterProcessCommSharedMem(ObjectJc* xthis)
{ return 0;
}



MemC getSendBuffer_InterProcessCommSharedMem(ObjectJc* ythis, int len)
{ MemC mem = {0, NULL};
  return mem; //not supported here.
}


Address_InterProcessComm_s* createAddressEmpty_InterProcessCommSharedMem(ObjectJc* ipcImpl)
{ Address_InterProcessComm_s* addr;
  ObjectJc* oAddr;
  STACKTRC_ENTRY("createAddressEmpty_InterProcessComm");
  oAddr = alloc_ObjectJc(sizeof(Address_InterProcessComm_s), 0, _thCxt);
  addr = ctorO_Address_InterProcessComm(oAddr, _thCxt);
  STACKTRC_LEAVE; return addr;
}



Address_InterProcessComm_s* createAddress_s_InterProcessCommSharedMem(ObjectJc* ipcImpl, StringJc sAddr)
{ Address_InterProcessComm_s* addr;
  ObjectJc* oAddr;
  STACKTRC_ENTRY("createAddress_s_InterProcessCommSharedMem");
  oAddr = alloc_ObjectJc(sizeof(Address_InterProcessComm_s), 0, _thCxt);
  addr = ctorO_s_Address_InterProcessComm(oAddr, sAddr, _thCxt);
  STACKTRC_LEAVE; return addr;
}

Address_InterProcessComm_s* createAddress_sI_InterProcessCommSharedMem(ObjectJc* ipcImpl, StringJc sAddr, int32 port)
{ Address_InterProcessComm_s* addr;
  ObjectJc* oAddr;
  STACKTRC_ENTRY("createAddress_sI_InterProcessCommSharedMem");
  oAddr = alloc_ObjectJc(sizeof(Address_InterProcessComm_s), 0, _thCxt);
  addr = ctorO_sI_Address_InterProcessComm(oAddr, sAddr, port, _thCxt);
  STACKTRC_LEAVE; return addr;
}


Address_InterProcessComm_s* createAddress_II_InterProcessCommSharedMem(ObjectJc* ipcImpl, int32 nAddr, int32 port)
{ Address_InterProcessComm_s* addr;
  ObjectJc* oAddr;
  STACKTRC_ENTRY("createAddress_I_InterProcessCommSharedMem");
  oAddr = alloc_ObjectJc(sizeof(Address_InterProcessComm_s), 0, _thCxt);
  addr = ctorO_II_Address_InterProcessComm(oAddr, sSharedMem_InterProcessCommSharedMem, nAddr, port, _thCxt);
  STACKTRC_LEAVE; return addr;
}






/**Define the mtbl_InterProcessComm for SharedMems
 */

#include <emC/Jc/ReflectionJc.h>
const ClassJc refl_InterProcessCommSharedMem_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc) 
, "InterProcessCommSharedMem_s"
,  0 //position of ObjectJc
, sizeof(InterProcessCommSharedMem_s)
, null //(FieldJcArray const*)&refl_Fields_InterProcessCommSharedMem_s
, null //method
, null //&superclasses_InterProcessCommSharedMem_s.head.object //superclass
, null //interfaces
, 0    //modifiers
//, &mtblInterProcessCommSharedMem.mtbl.head
};






//************************************************************************************************
// FactorySharedMemInterProcessComm
//


Address_InterProcessComm_s* ctor_Address_InterProcessComm_SharedMem_s(MemC mem, int32 iAdress, const char* sAdress)
{
  Address_InterProcessComm_SharedMem_s* pAddress = PTR_MemC(mem, Address_InterProcessComm_SharedMem_s);
  //if(mem.size < sizeof(Address_InterProcessComm_SharedMem_s) ) THROW(
// iAdress ist 0, wenn nicht dann ist das PortNr
  if(sAdress == null || *sAdress == 0)
  {
    //pAddress= new Address_InterProcessComm_SharedMem_s("", "", 0);
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
        //pAddress= new Address_InterProcessComm_SharedMem_s(sProtocol, sIpAdr, nPort);
      }
      else
      { printf("ung�ltige Addresse %s\n", sAdress);
      }
    }
  }
  return pAddress;
}


/* to remove
InterProcessCommSet_Ipc* create_Set_InterProcessCommSharedMem_Ipc(char const* protocol, int32 ipAddr, int nPort)
{
  STACKTRC_ENTRY("create_Set_InterProcessCommSharedMem_Ipc");
  StringJc type = z_StringJc(protocol);
  InterProcessCommSet_Ipc* thiz = (InterProcessCommSet_Ipc*)malloc(sizeof(InterProcessCommSet_Ipc));
  thiz->rxBuffer.ptr__ = & thiz->data_rxBuffer[0]; thiz->rxBuffer.value__ = sizeof( thiz->data_rxBuffer) / sizeof(thiz->data_rxBuffer[0]);
  ObjectJc* oAnsweraddr = alloc_ObjectJc(sizeof_Address_InterProcessComm_s, 0, _thCxt); 
  thiz->myAnswerAddress = ctorO_II_Address_InterProcessComm(oAnsweraddr, type, ipAddr, nPort, _thCxt);
  Address_InterProcessComm* ownAddr = ctorO_II_Address_InterProcessComm(alloc_ObjectJc(sizeof_Address_InterProcessComm_s, 0, _thCxt), type, ipAddr, nPort, _thCxt);
  //thiz->myAnswerAddress = createAddressSharedMem_InterProcessCommFactorySharedMem_Ipc_F(null_StringJc, protocolAndOwnAddr, nPort, _thCxt);
  ObjectJc* oipc = alloc_ObjectJc(sizeof_InterProcessCommSharedMem_s, 0, _thCxt);
  thiz->ipc = &ctorO_InterProcessCommSharedMem(oipc, ownAddr, _thCxt)->ifc.InterProcessComm;
  
  
  
  STACKTRC_LEAVE;
  return thiz;
}

*/




//#include "../Ipc2c/InterProcessCommFactorySharedMem_Ipc.h"


InterProcessCommFactory_s* XXXgetInstance_InterProcessCommFactory()
{
  return null; // iFactory;
}


#endif //def DEF_ClassJc_Vtbl

