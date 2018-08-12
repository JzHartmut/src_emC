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
 *         Some editing and improvments were done in 2008 by Marcos Rodriguez.
 *         The improvement after 2008 was done by Hartmut Schorrig.
 *
 **copyright***************************************************************************************
 *
 * @changes
 * 2010-01-31 Hartmut corr: use int..BigEndian in OS_SOCKADDR because it should be big endian.
 * 2010-01-15 Hartmut corr: Überarbeitung der Socket-Adaption für Hynet mit Auswirkungen hier, meist Feinheiten.
 *
 */


#include "os_socket.h"
#include "os_error.h"
#undef INT32
#undef UINT32
#undef int64
#undef uint64

#include <Winsock2.h>


/* CONSTANTS *************************************************************************************/


/* MACROS ****************************************************************************************/
#define bzero(ptr,len)  memset( (void *) ptr, (int) 0, (int) len )

/* GLOBAL VARIABLES ******************************************************************************/


/* EXTERNALS *************************************************************************************/


/* PROTOTYPES ************************************************************************************/



/**Initializes a OS_SOCKADDR from an Address_InterProcessComm. */
void set_OS_SOCKADDR(OS_SOCKADDR* dst, uint32 ip, uint16 port)
{
  dst->address1 = port;
  dst->address2 = ip;
  memset(dst->internalData, 0, sizeof(dst->internalData));
}




/**Writes the windows address bytes to the addr.internaldata and returns it. */
static void OS_2_Win(OS_SOCKADDR const* addr, SOCKADDR_IN* sockaddr) {
  sockaddr->sin_family =                 AF_INET;
  setInt16BigEndian((int16BigEndian*) &sockaddr->sin_port, (int16)addr->address1);
  setInt32BigEndian((int32BigEndian*) &sockaddr->sin_addr, addr->address2);
}

static void Win_2_OS(SOCKADDR_IN* sockaddr, OS_SOCKADDR* addr)
{ addr->address1 = getInt16BigEndian((int16BigEndian*) &sockaddr->sin_port) & 0x0000ffff;
  addr->address2 = getInt32BigEndian((int32BigEndian*) &sockaddr->sin_addr);
}



#define negativeSign (1<<((sizeof(int)*8)-1))








int os_createServerSocket(OS_ServerSocket* so )
{ 
  int ret;
  WSADATA wsa;
	SOCKET hSocket;
	ret = WSAStartup(0x0002, &wsa);
	if(ret != 0){
    // WSAGetLastError should not be called, WSAStartup return an error code:
    ret |=negativeSign;  //should be negative
  } else {
    //WSAStartup is done, now create a socket:
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(hSocket == INVALID_SOCKET)
    { ret = WSAGetLastError() | negativeSign; //mark with negativ sign! Keep the rest of hex-readable value.
      so->socket.socket = OS_INVALID_SOCKET;
    } else {
      ret = 0;
      so->socket.socket = (int32)hSocket; //it is a socket.
    }
  }
  return ret;
}





//same as os_createServerSocket
int os_createStreamSocket(OS_StreamSocket* so )
{ 
  int ret;
  WSADATA wsa;
	SOCKET hSocket;
	ret = WSAStartup(0x0002, &wsa);
	if(ret != 0){
    // WSAGetLastError should not be called, WSAStartup return an error code:
    ret |=negativeSign;  //should be negative
  } else {
    //WSAStartup is done, now create a socket:
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(hSocket == INVALID_SOCKET)
    { ret = WSAGetLastError() | negativeSign; //mark with negativ sign! Keep the rest of hex-readable value.
      so->socket.socket = OS_INVALID_SOCKET;
    } else {
      ret = 0;
      so->socket.socket = (int32)hSocket; //it is a socket.
    }
  }
  return ret;
}



int os_createDatagramSocket(OS_DatagramSocket * so)
{ int ret;
  WSADATA wsa;
	SOCKET hSocket;
	ret = WSAStartup(0x0002, &wsa);
	if(ret != 0){
    // WSAGetLastError should not be called, WSAStartup return an error code:
    ret |=negativeSign;  //should be negative
  } else {
    //WSAStartup is done, now create a socket:
    hSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if(hSocket == INVALID_SOCKET)
    { ret = WSAGetLastError() | negativeSign; //mark with negativ sign! Keep the rest of hex-readable value.
      so->socket.socket = OS_INVALID_SOCKET;
    } else {
      ret = 0;
      so->socket.socket = (int32)hSocket; //it is a socket.
    }
  }
  return ret;
}


int os_createRawSocket(OS_RawSocket * so)
{ int ret;
  WSADATA wsa;
	SOCKET hSocket;
	ret = WSAStartup(0x0002, &wsa);
	if(ret != 0){
    // WSAGetLastError should not be called, WSAStartup return an error code:
    ret |=negativeSign;  //should be negative
  } else {
    //WSAStartup is done, now create a socket:
    hSocket = socket(AF_INET, SOCK_RAW, 0);
    if(hSocket == INVALID_SOCKET)
    { ret = WSAGetLastError() | negativeSign; //mark with negativ sign! Keep the rest of hex-readable value.
      so->socket.socket = OS_INVALID_SOCKET;
    } else {
      ret = 0;
      so->socket.socket = (int32)hSocket; //it is a socket.
    }
  }
  return ret;
}


int os_bind(OS_Socket so, OS_SOCKADDR const* name)
{
	int iRetVal = 0;
	SOCKADDR_IN winAddr = {0};
//	OS_SOCKADDR sockaddr;
	int socklen = sizeof(winAddr);

	OS_2_Win(name, &winAddr);
	iRetVal = bind(so.socket, (SOCKADDR*)&winAddr, socklen);
	if (iRetVal == SOCKET_ERROR){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
  } else {
    iRetVal = 0;
  }
	return iRetVal;
}








int os_accept(OS_ServerSocket so, OS_SOCKADDR* dstAddr, OS_StreamSocket* soTcp)
{
	int32 iRetVal = 0;
	SOCKET hSocket;
	SOCKADDR_IN sockaddr;
	int len = sizeof(sockaddr);

	bzero(&sockaddr,sizeof(sockaddr));
	hSocket = accept( (SOCKET)so.socket.socket, (SOCKADDR*) &sockaddr, &len);
	if (hSocket == INVALID_SOCKET ){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
    soTcp->socket.socket = OS_INVALID_SOCKET;
  } else {
    iRetVal = 0;
    soTcp->socket.socket = (int32)hSocket;
  }
	Win_2_OS(&sockaddr, dstAddr);


	return iRetVal;
}






int os_close(OS_Socket so)
{
	int iRetVal = 0;

	iRetVal = closesocket( (SOCKET)so.socket );
	if (iRetVal == SOCKET_ERROR ){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
  } else {
    iRetVal = 0;
  }
	return iRetVal;
}





int os_connect(OS_StreamSocket so, OS_SOCKADDR const* dstAddr)
{

	/* No wait loop implemented, that schuld be done in the app level! */

	int iRetVal;
 	SOCKADDR_IN socketaddr = {0};


	int socklen = sizeof(socketaddr);
	OS_2_Win(dstAddr, &socketaddr);

	iRetVal = connect( (SOCKET)so.socket.socket, (struct sockaddr*) &socketaddr, socklen);
	if (iRetVal == SOCKET_ERROR){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
  } else {
    iRetVal = 0;
  }
	return iRetVal;
}





int os_ioctlsocket(OS_Socket so, int request, void* arg, int arglen)
{
	int iRetVal = 0;
	int option = FIONBIO;               /* nicht blockierend */
	unsigned long pn = *((char*)arg);   /* 1 = set NONBLOCKING, 0 = reset NONBLOCKING */

	iRetVal = ioctlsocket( (SOCKET)so.socket, option, &pn);
	if (iRetVal == SOCKET_ERROR ){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
  } else {
    iRetVal = 0;
  }
	return iRetVal;
}





int os_listen(OS_ServerSocket so, int backlog)
{
	int iRetVal = 0;

	iRetVal = listen( (SOCKET)so.socket.socket, backlog);
	if (iRetVal == SOCKET_ERROR){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
  } else {
    iRetVal = 0;
  }
	return iRetVal;
}



typedef struct _OS_SOCKSEL
{  uint16 se_inflags;
   uint16 se_outflags;
   OS_Socket se_fd;
   int       se_1reserved;
   uint32    se_user;
   uint32    se_2reserved;
} OS_SOCKSEL;


typedef struct _OS_LINGEROPT
{  int linger_on;				/* LINGER ON/OFF ( <>0 / 0 ) */	
   int linger_time;			/* Wait-Zeit in seconds */
} OS_LINGEROPT;



int os_nselect(OS_SOCKSEL* selp, int cnt, int32 waitp)
{
	int retEvent = 1; // Event passiert
  int event;
   FD_SET fdr;
   FD_SET fdw;
   FD_SET fdx;

   TIMEVAL tv = {0, waitp};

	FD_ZERO(&fdr);
	FD_ZERO(&fdw);
	FD_ZERO(&fdx);

	FD_SET((SOCKET)selp->se_fd.socket, &fdr);

	selp->se_outflags = 0;
   
//	fdr.fd_count = 1;
//	fdr.fd_array[0] = selp->se_fd;

  event = select(0, &fdr, &fdw, &fdx, &tv);

	if(event == 0) // Timeout
	{
		selp->se_outflags = SO_TIMEOUT_NOTIFY;
		retEvent = 0;
	}
	else if(event == 1) // ein Socket geoeffnet
	{
		if(selp->se_inflags == SO_ACCEPT_NOTIFY)
		{
			selp->se_outflags = SO_ACCEPT_NOTIFY;
		}
		else
		{
			BYTE buf[2];
			event = recv(selp->se_fd.socket, (char*)buf, sizeof(buf), MSG_PEEK);
			if (event== SOCKET_ERROR)
			{
				int err = WSAGetLastError();
				//retEvent = SOCKET_ERROR; // MR. The encapsulation can only be an unknown error
        retEvent = err;
        if(retEvent >0){
          retEvent |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
        }
				switch (err)
				{
					case WSAESHUTDOWN:             
						selp->se_outflags  = SO_RSHUTDOWN_NOTIFY;
		//					selp->se_outflags  = WSHUTDOWN_NOTIFY;
						break;
					case WSAEWOULDBLOCK:           
					case WSAECONNABORTED:
					case WSAENETDOWN:
					case WSAENETRESET:
					case WSAETIMEDOUT:
					case WSAECONNRESET:
					case  WSAEINPROGRESS:
					case  WSAEALREADY:
					case  WSAENOTSOCK:
					case  WSAEDESTADDRREQ:
					case  WSAEMSGSIZE:
					case  WSAEPROTOTYPE:
					case  WSAENOPROTOOPT:
					case  WSAEPROTONOSUPPORT:
					case  WSAESOCKTNOSUPPORT:
					case  WSAEOPNOTSUPP:
					case  WSAEPFNOSUPPORT:
					case  WSAEAFNOSUPPORT:
					case  WSAEADDRINUSE:
					case  WSAEADDRNOTAVAIL:
					case  WSAENETUNREACH:
					case  WSAENOBUFS:
					case  WSAEISCONN:
					case  WSAENOTCONN:        
					case  WSAETOOMANYREFS:
					case  WSAECONNREFUSED:
					case  WSAELOOP:
					case  WSAENAMETOOLONG:
					case  WSAEHOSTDOWN:
					case  WSAEHOSTUNREACH:
					case  WSAENOTEMPTY:
					case  WSAEPROCLIM:
					case  WSAEUSERS:
					case  WSAEDQUOT:
					case  WSAESTALE:
					case  WSAEREMOTE:
						selp->se_outflags = SO_EXCEPT_NOTIFY;
						break;
					default: 
						selp->se_outflags = SO_EXCEPT_NOTIFY;
						break;
				} // switch-ende: error
			}
			else if(event == 0)
			{
				selp->se_outflags = SO_CLOSE_NOTIFY;
			}
			else if(event == 2)
			{
				selp->se_outflags = SO_READ_NOTIFY; // Daten angekommen
			}
			else
			{
				// defekte Daten
				selp->se_outflags = SO_EXCEPT_NOTIFY;
			}
		} // else-ende: Daten lesen um zu sehen was ist
	} // else-ende: ein Socket geoeffnet

	return (retEvent);
}





int os_recv(OS_StreamSocket so, void* buffer, int len, int flags)
{
	int iRetVal = 0;
	/* was ist mit den flags ?????????????? nicht kompatibel mit Rmos !! */
	iRetVal = recv( (SOCKET)so.socket.socket, (char*)buffer, len, flags);
	if (iRetVal == SOCKET_ERROR ){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
	}
	return iRetVal;  //error or number of bytes received
}





int os_recvfrom(OS_DatagramSocket so, void* buffer, int len, int flags, OS_SOCKADDR* from)
{
	SOCKADDR_IN socketaddr;
	int nFromlenWin = sizeof(socketaddr);

	int iRetVal = recvfrom( (SOCKET)so.socket.socket, (char*)buffer, len, flags, (SOCKADDR*) &socketaddr, &nFromlenWin); 
	if (iRetVal == SOCKET_ERROR ){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
	}

	Win_2_OS(&socketaddr, from);

	return iRetVal;
}





int os_send(OS_StreamSocket so, void const* buffer, int len, int flags)
{
	int iRetVal = 0;

	/* was ist mit den flags ?????????????? nicht kompatibel mit Rmos !! */
	iRetVal = send( (SOCKET)so.socket.socket, (const char*)buffer, len, flags);
	if (iRetVal == SOCKET_ERROR){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
	}
	return iRetVal;
}





int os_sendto(OS_DatagramSocket so, void const* buffer, int len, int flags, OS_SOCKADDR const* to)
{
	int iRetVal;
   

	// returned value will be less than nSize if client cancels the reading
	SOCKADDR_IN socketaddr = {0};

	int nTolenWin = sizeof(socketaddr);
	OS_2_Win(to, &socketaddr);

	iRetVal = sendto( (SOCKET)so.socket.socket, (const char*)buffer, len, flags, (SOCKADDR*) &socketaddr, nTolenWin);
	if (iRetVal == SOCKET_ERROR){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
	}
	return iRetVal;
}






int os_setsockopt(OS_Socket so, int level, int optname, int* optval, int optlen)
{
	int iRetVal = 0;

	if ( (optname != SO_REUSEADDR) && (optname != SO_KEEPALIVE) && (optname != SO_LINGER) ){
			return OS_INVALID_PARAMETER;
	}
	
	if (optname == SO_LINGER){
		LINGER optvalWin;
		optvalWin.l_onoff = (uint16)((OS_LINGEROPT*)optval)->linger_on;
		optvalWin.l_linger = (uint16)((OS_LINGEROPT*)optval)->linger_time;  
    	iRetVal = setsockopt( (SOCKET)so.socket, level, optname, (const char*)&optvalWin, sizeof(LINGER));
	}
	else{
		char* optvalWin = (char*)optval;    
		iRetVal = setsockopt( (SOCKET)so.socket, level, optname, (const char*)optvalWin, sizeof(int)); // sizeof(int) for BOOL opt
	}
 
	if (iRetVal == SOCKET_ERROR){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
  } else {
    iRetVal = 0;
  }
	return iRetVal;
}





int os_shutdown (OS_Socket so, int how)
{
	int iRetVal = 0;

	switch(how){
	case SO_RECEIVE_DOWN:
		how = SD_RECEIVE;
		break;
	case SO_SEND_DOWN:
		how = SD_SEND;
		break;
	case SO_BOTH_DOWN:
		how = SD_BOTH;
		break;
	default:
		break;
	}
	iRetVal = shutdown( (SOCKET)so.socket, how );
	if (iRetVal == SOCKET_ERROR ){
  	iRetVal = WSAGetLastError();
    if(iRetVal >0){
      iRetVal |= negativeSign;  //mark with negativ sign! Keep the rest of hex-readable value.
    }
  } else {
    iRetVal = 0;
  }
	return iRetVal;
}







/**Sets the just now opend socket to blocking or non blocking mode.
 * The implementation calls a special ioctrl routine from the system layer.
 * The standard behavior of a socket is the blocking mode. But this routine
 * should be called everytime after os_open to assure that the socket is in the expected mode.
 * @param af The Socket.
 * @param bNonBlocking If true than sets to non blocking, if false than sets to blocking.
 */ 
int os_setNonBlocking(OS_DatagramSocket socket, bool bNonBlocking)
{ int retVal;
  if(bNonBlocking)
  { unsigned long argp = 1;
    retVal = ioctlsocket(socket.socket.socket, FIONBIO, &argp);
  }
  else
  { //blocking mode is the standard behavior ...
    retVal = 0;
  }
  return retVal;
}









int os_socketError()
{ //return errno;  //globale Variable (Threadsicherheit???)
  //link; http://msdn2.microsoft.com/en-us/library/ms741580.aspx
  return WSAGetLastError();
}




const char* os_translateSocketErrorMsg(int nError)
{
  const char* sError;
  switch(nError & ~negativeSign)
	{
	case WSAEACCES: sError = "Permission denied."; break;
	case WSAEADDRINUSE: sError = "Address already in use."; break;
	case WSAEADDRNOTAVAIL: sError = "Cannot assign requested address."; break;
	case WSAEAFNOSUPPORT: sError = "Address family not supported by protocol family."; break;
	case WSAEALREADY: sError = "Operation already in progress."; break;
	case WSAECONNABORTED: sError = "Software caused connection abort."; break;
	case WSAECONNREFUSED: sError = "Connection refused."; break;
	case WSAECONNRESET: sError = "Connection reset by peer."; break;
	case WSAEDESTADDRREQ: sError = "Destination address required."; break;
	case WSAEFAULT:	sError = "Bad address."; break;
	case WSAEHOSTDOWN: sError = "Host is down."; break;
	case WSAEHOSTUNREACH: sError = "No route to host."; break;
	case WSAEINPROGRESS: sError = "Operation now in progress."; break;
	case WSAEINTR: sError = "Interrupted function call."; break;
	case WSAEINVAL: sError = "Invalid argument."; break;
	case WSAEISCONN: sError = "Socket is already connected."; break;
	case WSAEMFILE: sError = "Too many open files."; break;
	case WSAEMSGSIZE: sError = "Message too long."; break;
	case WSAENETDOWN: sError = "Network is down."; break;
	case WSAENETRESET: sError = "Network dropped connection on reset."; break;
	case WSAENETUNREACH: sError = "Network is unreachable."; break;
	case WSAENOBUFS: sError = "No buffer space available."; break;
	case WSAENOPROTOOPT: sError = "Bad protocol option."; break;
	case WSAENOTCONN: sError = "Socket is not connected."; break;
	case WSAENOTSOCK: sError = "Socket operation on non-socket."; break;
	case WSAEOPNOTSUPP: sError = "Operation not supported."; break;
	case WSAEPFNOSUPPORT: sError = "Protocol family not supported."; break;
	case WSAEPROCLIM: sError = "Too many processes."; break;
	case WSAEPROTONOSUPPORT: sError = "Protocol not supported."; break;
	case WSAEPROTOTYPE: sError = "Protocol wrong type for socket."; break;
	case WSAESHUTDOWN: sError = "Cannot send after socket shutdown."; break;
	case WSAESOCKTNOSUPPORT: sError = "Socket type not supported."; break;
	case WSAETIMEDOUT: sError = "Connection timed out."; break;
	case WSATYPE_NOT_FOUND: sError = "Class type not found."; break;
	case WSAEWOULDBLOCK: sError = "Resource temporarily unavailable."; break;
	case WSAHOST_NOT_FOUND: sError = "Host not found."; break;
	case WSA_INVALID_HANDLE: sError = "Specified event object handle is invalid."; break;
	case WSA_INVALID_PARAMETER: sError = "One or more parameters are invalid."; break;
	case WSAEINVALIDPROCTABLE: sError = "Invalid procedure table from service provider."; break;
	case WSAEINVALIDPROVIDER: sError = "Invalid service provider version number."; break;
	case WSA_IO_INCOMPLETE: sError = "Overlapped I/O event object not in signaled state."; break;
	case WSA_IO_PENDING: sError = "Overlapped operations will complete later."; break;
	case WSA_NOT_ENOUGH_MEMORY: sError = "Insufficient memory available."; break;
	case WSANOTINITIALISED: sError = "Successful WSAStartup not yet performed."; break;
	case WSANO_DATA: sError = "Valid name, no data record of requested type."; break;
	case WSANO_RECOVERY: sError = "This is a non-recoverable error."; break;
	case WSAEPROVIDERFAILEDINIT: sError = "Unable to initialize a service provider."; break;
	case WSASYSCALLFAILURE: sError = "System call failure."; break;
	case WSASYSNOTREADY: sError = "Network subsystem is unavailable."; break;
	case WSATRY_AGAIN: sError = "Non-authoritative host not found."; break;
	case WSAVERNOTSUPPORTED: sError = "WINSOCK.DLL version out of range."; break;
	case WSAEDISCON: sError = "Graceful shutdown in progress."; break;
	case WSA_OPERATION_ABORTED: sError = "Overlapped operation aborted."; break;
	default: sError = "unknown Error";
  }
  return sError;

}


