#include "InterProcessCommSocket.c"

/*******************************************************************************************************
 * Adaption of C++-calls
 ******************************************************************************************************/

/**The C++-Implementation calls the C-Implementation imediately. */
class InterProcessCommImplement : public InterProcessCommSocket_s, public InterProcessComm
{

  public: virtual struct InterProcessCommC_t* toInterProcessCommC()
  { return &this->ifc.InterProcessComm;
  }
  //private: void* getDataBuffer();

	public: InterProcessCommImplement(Address_InterProcessComm_Socket_s* ownAddress);

  /* implementation of the derived methods:
  */
  public:  virtual int open(struct Address_InterProcessComm_t* destAddress, bool isBlocking, InterProcessCommCallback* callback)
  { return open_InterProcessCommSocket(&this->ifc.InterProcessComm, destAddress,isBlocking, SIMPLE_CAST(InterProcessCommCallback_s*, callback), &mtbl_InterprocessCommCallbackAdapCpp); }

  public: virtual int close();

  public: virtual int send(const void* data, int nBytes, struct Address_InterProcessComm_t* destAddress);

  public: virtual void* receive(int* nrofBytes, struct Address_InterProcessComm_t* sender);

  public: virtual int abortReceive();

  public: virtual void freeData(void* data);

  public: virtual bool equals(const struct Address_InterProcessComm_t* address1, const struct Address_InterProcessComm_t* address2);

   public: virtual const int getLastError();

  public: virtual int dataAvailable();

  public: virtual int checkConnection();


  /**/

  //private: int ErrorSocket();

  public: virtual const char* translateErrorMsg(int error);

  public: virtual const char* getName();

  public: virtual struct Address_InterProcessComm_t const* getOwnAddress();

  /** Receives with given data buffer, see C-description.
  */
  public: virtual void* receive(int* nrofBytes, MemC buffer, struct Address_InterProcessComm_t* sender =  null);


};



InterProcessCommImplement::InterProcessCommImplement(Address_InterProcessComm_Socket_s* ownAddress)
{ ctor_InterProcessCommSocket(this, ownAddress);
}


bool InterProcessCommImplement::equals(const struct Address_InterProcessComm_t* address1P, const struct Address_InterProcessComm_t* address2P)
{ return equals_InterProcessCommSocket(address1P, address2P);
}


int InterProcessCommImplement::close()
{ return close_InterProcessCommSocket(&this->ifc.InterProcessComm);
}


int InterProcessCommImplement::send(const void* data, int nBytes, Address_InterProcessComm_s* addressee /* = null */)
{ return send_InterProcessCommSocket(&this->ifc.InterProcessComm, data, nBytes, addressee /* = null */);
}

void* InterProcessCommImplement::receive(int* nrofBytes, Address_InterProcessComm_s* senderP)
{ return receive_InterProcessCommSocket(&this->ifc.InterProcessComm, nrofBytes, senderP);
}

void* InterProcessCommImplement::receive(int* nrofBytes, MemC buffer, Address_InterProcessComm_s* senderP)
{ return receiveData_InterProcessCommSocket(&this->ifc.InterProcessComm, nrofBytes, buffer, senderP);
}

int InterProcessCommImplement::dataAvailable()
{ return dataAvailable_InterProcessCommSocket(&this->ifc.InterProcessComm);
}

int InterProcessCommImplement::checkConnection()
{ return checkConnection_InterProcessCommSocket(&this->ifc.InterProcessComm);
}


void InterProcessCommImplement::freeData(void* data)
{ freeData_InterProcessCommSocket(&this->ifc.InterProcessComm, data);
}

const char* InterProcessCommImplement::translateErrorMsg(int nError)
{ return translateErrorMsg_InterProcessCommSocket(nError);
}

struct Address_InterProcessComm_t const* InterProcessCommImplement::getOwnAddress()
{ return getOwnAddress_InterProcessCommSocket(&this->ifc.InterProcessComm);
}


const char* InterProcessCommImplement::getName()
{ return getName_InterProcessCommSocket(&this->ifc.InterProcessComm);
}


int InterProcessCommImplement::abortReceive()
{
  return 0;
}

const int InterProcessCommImplement::getLastError()
{
  return os_socketError();
}









InterProcessComm* FactorySocketInterProcessComm::createInterProcessComm(Address_InterProcessComm_s* ownAddress)
{
  //NOTE: Because the Address_InterProcessComm_Socket_s is the own possible type of Address, the cast is correct.
  Address_InterProcessComm_Socket_s* addr = SIMPLE_CAST(Address_InterProcessComm_Socket_s*,ownAddress);

  InterProcessComm* pIPC = new InterProcessCommImplement(addr);

  return pIPC;
}


bool FactorySocketInterProcessComm::destroyInterProcessComm(InterProcessComm* obj)
{
  delete obj;
  return true;
}










Address_InterProcessComm_s* FactorySocketInterProcessComm::createAddress(int32 iAdress, const char* sAdress)
{
  Address_InterProcessComm_Socket_s* pAddress = null;
// iAdress ist 0, wenn nicht dann ist das PortNr
  MemC mem = alloc_MemC(sizeof(Address_InterProcessComm_Socket_s));
  if(sAdress == null || *sAdress == 0)
  {
    Address_InterProcessComm_Socket_s* addr = ctor_s0ii_Address_InterProcessComm_Socket_s(mem, "", 0, 0);
    return addr;
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
        Address_InterProcessComm_Socket_s* addr = ctor_Address_InterProcessComm_Socket_s(mem, sProtocol, sIpAdr, nPort);
        return addr;
        //pAddress= new Address_InterProcessComm_Socket_s(sProtocol, sIpAdr, nPort);
      }
      else
      { printf("ungültige Addresse %s\n", sAdress);
        return null;
      }
    }
    else return null;
  }
}




Address_InterProcessComm_s* FactorySocketInterProcessComm::createAddress(int32 nPort, int32 ipAddr, const char* sType)
{
  Address_InterProcessComm_Socket_s* pAddress = null;
// iAdress ist 0, wenn nicht dann ist das PortNr
  //pAddress= (Address_InterProcessComm_s*)malloc(sizeof(Address_InterProcessComm_Socket_s));
  MemC mem = alloc_MemC(sizeof(Address_InterProcessComm_Socket_s));
  if(sType == null || *sType == 0)
  {
    Address_InterProcessComm_Socket_s* addr = ctor_s0ii_Address_InterProcessComm_Socket_s(mem, "", 0, 0);
    return addr;
  }
  else
  {
    Address_InterProcessComm_Socket_s* addr = ctor_s0ii_Address_InterProcessComm_Socket_s(mem, sType, ipAddr, nPort);
    return addr;
    //pAddress= new Address_InterProcessComm_Socket_s(sType, ipAddr, nPort);
  }
}





