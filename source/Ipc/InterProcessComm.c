
/*
 * Default implements.
 */

#include "Ipc/InterProcessComm.h"
#include "Ipc/InterProcessCommSocket.h"
#include <Jc/ObjectJc.h>
#include <Jc/StringJc.h>
#include <stdio.h>

char const sign_Mtbl_InterProcessCommFactory[] = "Mtbl_InterProcessCommFactory";

char const sign_Mtbl_InterProcessCommFactoryAccessor[] = "Mtbl_InterProcessCommFactoryAccessor";

Address_InterProcessComm_s* ctorO_Address_InterProcessComm(ObjectJc* othis, ThCxt* _thCxt)
{
  Address_InterProcessComm_s* ythis = (Address_InterProcessComm_s*) othis;
  STACKTRC_TENTRY("ctorO_Address_InterProcessComm");
  checkConsistence_ObjectJc(othis, sizeof(Address_InterProcessComm), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_Address_InterProcessComm_s, sizeof(Address_InterProcessComm_s));  
  STACKTRC_LEAVE; return ythis;
}



METHOD_C Address_InterProcessComm_s* ctorO_s_Address_InterProcessComm(ObjectJc* othis, StringJc addr, ThCxt* _thCxt)
{
  Address_InterProcessComm_s* thiz = (Address_InterProcessComm_s*) othis;
  STACKTRC_TENTRY("ctorO_Address_InterProcessComm");
  checkConsistence_ObjectJc(othis, sizeof(Address_InterProcessComm), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_Address_InterProcessComm_s, sizeof(Address_InterProcessComm_s));  
  int sizeAddr;
  char const* charsAddr = getCharsAndLength_StringJc(&addr, &sizeAddr);
  if (charsAddr == null || sizeAddr == 0)
  { //no address specification
    thiz->address1 = thiz->address2 = 0;
  }
  else
  { int np1 = 0, np2 = 0, np3 = 0, np4 = 0;
    int port = 0;
    sscanf(charsAddr, "%d . %d . %d . %d : %d", &np1, &np2, &np3, &np4, &port);
    //Note: The IPv4-Address is stored as int32, the left is the high byte of integer unless little or big endian!
    thiz->address2 = (((uint32)np1)<<24) + (((uint32)np2)<<16) + (((uint32)np3)<<8) + np4;
    thiz->address1 = port;
  }
  STACKTRC_LEAVE; return thiz;
}

Address_InterProcessComm_s* ctorO_sI_Address_InterProcessComm(ObjectJc* othis, StringJc addr, int32 port, ThCxt* _thCxt)
{
  Address_InterProcessComm_s* ythis = (Address_InterProcessComm_s*) othis;
  STACKTRC_TENTRY("ctorO_Address_InterProcessComm");
  checkConsistence_ObjectJc(othis, sizeof(Address_InterProcessComm), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_Address_InterProcessComm_s, sizeof(Address_InterProcessComm_s));  
  
  
  ythis->address2 = port;
  
  STACKTRC_LEAVE; return ythis;
}




Address_InterProcessComm_s* ctorO_ssI_Address_InterProcessComm(ObjectJc* othis, StringJc type, StringJc addr, int32 port, ThCxt* _thCxt)
{
  Address_InterProcessComm_s* ythis = (Address_InterProcessComm_s*) othis;
  char const* charsType;
  int sizeType;
  char const* charsAddr;
  int sizeAddr;
  STACKTRC_TENTRY("ctorO_Address_InterProcessComm");
  checkConsistence_ObjectJc(othis, sizeof(Address_InterProcessComm), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_Address_InterProcessComm_s, sizeof(Address_InterProcessComm_s));  
  
  charsType = getCharsAndLength_StringJc(&type, &sizeType);
  if(sizeType >= sizeof(ythis->sType)) { sizeType = sizeof(ythis->sType) -1; } //limit it.
  strncpy(ythis->sType, charsType, sizeType);

  

  //os_SOCKADDR->sa_family = AF_INET;
  //os_SOCKADDR->sin_port = FW_HTON16(nPort);
  //setInt16BigEndian((int16BigEndian*)&os_SOCKADDR->sin_port, nPort);
  ythis->address1 = port;
  //default use the address of "localhost"

  charsAddr = getCharsAndLength_StringJc(&addr, &sizeAddr);
  if (charsAddr == null || sizeAddr == 0)
  { //no address specification
    //TRICKY: this area is either a char[4] or a analogical unit with the same byte signification
    //((OS_SOCKADDR*)ythis->internalData)->ip.addr32 =  kReceiveFromAll_OS_SOCKADDR;
    ythis->address2 = 0; //kReceiveFromAll_OS_SOCKADDR;
  }
  else
  { int np1 = 0, np2 = 0, np3 = 0, np4 = 0;
    sscanf(charsAddr, " %d . %d . %d . %d ", &np1, &np2, &np3, &np4);
    //Note: The IPv4-Address is stored as int32, the left is the high byte of integer unless little or big endian!
    ythis->address2 = (((uint32)np1)<<24) + (((uint32)np2)<<16) + (((uint32)np3)<<8) + np4;

  }
  STACKTRC_LEAVE; return ythis;
}

Address_InterProcessComm_s* ctorO_II_Address_InterProcessComm(ObjectJc* othis, StringJc type, int32 addr1, int32 addr2, ThCxt* _thCxt)
{
  Address_InterProcessComm_s* ythis = (Address_InterProcessComm_s*) othis;
  STACKTRC_TENTRY("ctorO_Address_InterProcessComm");
  checkConsistence_ObjectJc(othis, sizeof(Address_InterProcessComm), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_Address_InterProcessComm_s, sizeof(Address_InterProcessComm_s));  
  ythis->address1 = addr1;
  ythis->address2 = addr2;

  STACKTRC_LEAVE; return ythis;
}










#if defined(__CPLUSGEN) && defined(__cplusplus)

MemC InterProcessComm::receive(int32* nrofBytes, Address_InterProcessComm_s* sender)
{
  MemC buffer = CONST_MemC(0, null);
  nrofBytes = 0;
  return receive(nrofBytes, buffer, sender);
}

#endif //__cplusplus




InterProcessCommFactoryAccessor* ctorO_InterProcessCommFactoryAccessor(ObjectJc* othis, ThCxt* _thCxt)
{
  InterProcessCommFactoryAccessor* ythis = (InterProcessCommFactoryAccessor*)othis;
  checkConsistence_ObjectJc(othis, sizeof(InterProcessCommFactoryAccessor), &reflection_InterProcessCommFactoryAccessor, null);
  return ythis;
}
