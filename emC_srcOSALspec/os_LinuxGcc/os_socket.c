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
 * @author This OS-Implementation was created by Alfred Schaffrina anno 2005/2006. 
 *         It was used and improved by Hartmut Schorrig, www.vishia.org in 2007/2008.
 *         Some editing and improvements were done in 2008 by Marcos Rodriguez.
 *         The improvement after 2008 was done by Hartmut Schorrig.
 *
 **copyright***************************************************************************************
 *
 * @changes
 * 2010-01-31 Hartmut corr: use int..BigEndian in OS_SOCKADDR because it should be big endian.
 * 2010-01-15 Hartmut corr: �berarbeitung der Socket-Adaption f�r Hynet mit Auswirkungen hier, meist Feinheiten.
 *
 */


#include "os_socket.h"
#include "os_error.h"
#include <sys/socket.h>
#include <errno.h>
#include <linux/in.h> //Linux internet
#include <unistd.h>   //for close,
#include <fcntl.h>

struct sockaddr_in;

struct XXXin_addr {
    unsigned long s_addr;          // load with inet_pton()
};


struct XXXsockaddr_in {
    short            sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};


struct XXXin6_addr {
    unsigned char   s6_addr[16];   // load with inet_pton()
};

// IPv6 AF_INET6 sockets:

struct sockaddr_in6 {
    u_int16_t       sin6_family;   // address family, AF_INET6
    u_int16_t       sin6_port;     // port number, Network Byte Order
    u_int32_t       sin6_flowinfo; // IPv6 flow information
    struct XXXin6_addr sin6_addr;     // IPv6 address
    u_int32_t       sin6_scope_id; // Scope ID
};





#define bzero(ptr,len)  memset( (void *) ptr, (int) 0, (int) len )



#define negativeSign 0x80000000  //(1<<((sizeof(int)*8)-1))


/*
void copyAddrTo_SOCKADDR(struct sockaddr_in const* addrsys, OS_SOCKADDR* addr_OSAL)
{ //note:
  addr_OSAL->sin_port = (int16BigEndian)addrsys->sin_port;
  //A change of byte order may possible here. But it is both big endian.
  addr_OSAL->ip.add32 = (int32BigEndian)addrsys->sin_addr;
  //NOTE: Nucleus-net knows a char* name as 'machine's name', it isn't use here.
}


void copyAddrTo_addr_struct(OS_SOCKADDR const* addr_OSAL, struct sockaddr * addr_NU)
{ //note:
  addr_NU->family = NU_FAMILY_IP;
  addr_NU->port = addr_OSAL->sin_port;
  //NOTE: Nucleus-net knows constant MAX_ADDRESS_SIZE. Here only ip-4 is supported.
  //NOTE: In OS-Layer the first ip address should be located in that byte, which is the MSB in a normal int32 representation.
  //A change of byte order may possible here. But in the yet known implementatin it isn't regarded well.
  addr_NU->id.is_ip_addrs[0] = addr_OSAL->ip.sin_addr[0];
  addr_NU->id.is_ip_addrs[1] = addr_OSAL->ip.sin_addr[1];
  addr_NU->id.is_ip_addrs[2] = addr_OSAL->ip.sin_addr[2];
  addr_NU->id.is_ip_addrs[3] = addr_OSAL->ip.sin_addr[3];
}

*/





int os_createStreamSocket(OS_SOCKET* so )
{ 
  int ret;
  int hSocket;
  //WSAStartup is done, now create a socket:
  hSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(hSocket == -1)
  { ret = errno | negativeSign; //mark with negativ sign! Keep the rest of hex-readable value.
    *so = OS_INVALID_SOCKET;
  } else {
    ret = 0;
    *so = (OS_SOCKET)hSocket; //it is a socket.
  }
  return ret;
}



int os_createDatagramSocket(OS_SOCKET * so)
{
  int ret;
  int hSocket;
  //WSAStartup is done, now create a socket:
  hSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if(hSocket == -1)
  { ret = errno | negativeSign; //mark with negativ sign! Keep the rest of hex-readable value.
    *so = OS_INVALID_SOCKET;
  } else {
    ret = 0;
    *so = (OS_SOCKET)hSocket; //it is a socket.
  }
  return ret;
}


int os_createIpSocket(OS_SOCKET * so)
{
  int ret;
  int hSocket;
  //WSAStartup is done, now create a socket:
  hSocket = socket(AF_INET, SOCK_RAW, 0);
  if(hSocket == -1)
  { ret = errno | negativeSign; //mark with negativ sign! Keep the rest of hex-readable value.
    *so = OS_INVALID_SOCKET;
  } else {
    ret = 0;
    *so = (OS_SOCKET)hSocket; //it is a socket.
  }
  return ret;
}



int os_bind(OS_SOCKET so, OS_SOCKADDR const* addr)
{
  int socklen = sizeof(*addr);

  int ok = bind(so, ( struct sockaddr const*)addr, socklen);
  if(ok==-1){
      ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
  return ok;
}


int os_accept(OS_SOCKET so, OS_SOCKADDR* dstAddr, OS_SOCKET* soTcp)
{
  size_t dstLen = sizeof(*dstAddr);
  int tcpSocket = accept(so, (struct sockaddr*)dstAddr, &dstLen);
  if(tcpSocket !=-1){
    *soTcp = tcpSocket;
    return 0;
  } else {
    *soTcp = OS_INVALID_SOCKET;
    return errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
}




int os_close(OS_SOCKET so)
{
  int ok = close(so);
  if(ok==-1){
      ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
  return ok;
}




int os_connect(OS_SOCKET so, OS_SOCKADDR const* dstAddr)
{
  int ok = connect( so, (struct sockaddr*) &dstAddr, sizeof(*dstAddr));
  if(ok==-1){
      ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
  return ok;
}





int os_listen(OS_SOCKET so, int backlog)
{
  int ok = listen( so, backlog);
  if(ok==-1){
      ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
  return ok;
}







int os_recv(OS_SOCKET so, void* buffer, int len, int flags)
{
  int ok = recv( so, (char*)buffer, len, flags);
  if(ok < 0){
      ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
  return ok;

}





int os_recvfrom(OS_SOCKET so, void* buffer, int len, int flags, OS_SOCKADDR* from)
{
  size_t lenAddr = sizeof(*from);
  int ok = recvfrom( so, (char*)buffer, len, flags, (struct sockaddr*) from, &lenAddr);
  if(ok < 0){
      ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
  return ok;
}





int os_send(OS_SOCKET so, void const* buffer, int len, int flags)
{
  int ok = send( so, (const char*)buffer, len, flags);
  if(ok < 0){
      ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
  return ok;
}





int os_sendto(OS_SOCKET so, void const* buffer, int len, int flags, OS_SOCKADDR const* to)
{
  size_t lenAddr = sizeof(*to);
  int ok = sendto( so, (const char*)buffer, len, flags, (struct sockaddr*) to, lenAddr);
  if(ok < 0){
      ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
  }
  return ok;
}




/**Sets the just now opend socket to blocking or non blocking mode.
 * The implementation calls a special ioctrl routine from the system layer.
 * The standard behavior of a socket is the blocking mode. But this routine
 * should be called everytime after os_open to assure that the socket is in the expected mode.
 * @param af The Socket.
 * @param bNonBlocking If true than sets to non blocking, if false than sets to blocking.
 */
int os_setNonBlocking(OS_SOCKET socket, bool bNonBlocking)
{ int retVal;
  if(bNonBlocking)
  { retVal = fcntl(socket, O_NONBLOCK);
  }
  else
  { //blocking mode is the standard behavior ...
    retVal = 0;
  }
  return retVal;
}




int os_shutdown (OS_SOCKET so, int how)
{
        int ok = 0;

        switch(how){
        case SO_RECEIVE_DOWN:
                how = SHUT_RD;
                break;
        case SO_SEND_DOWN:
                how = SHUT_WR;
                break;
        case SO_BOTH_DOWN:
                how = SHUT_RDWR;
                break;
        default:
                break;
        }
        ok = shutdown( so, how );
        if(ok < 0){
            ok = errno | negativeSign;  //mark with negative sign! Keep the rest of hex-readable value.
        }
        return ok;
}



#include <asm-generic/errno.h>

const char* os_translateSocketErrorMsg(int nError)
{
  const char* sError;
  switch(nError & ~negativeSign)
  {
    case EPROTONOSUPPORT: sError = "Protocol not supported"; break;
    case 0x7fffffff: sError = "Permission denied."; break;
    default: sError = "unknown socket error";
  } //switch
  return sError;
}

