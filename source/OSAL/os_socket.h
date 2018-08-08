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
 * @author This OS-Interface was created by Alfred Schaffrina anno 2005/2006. 
 *         It was used and improved by Hartmut Schorrig, www.vishia.org in 2007/2008.
 *         Some editing and improvments were done in 2008 by Marcos Rodriguez.
 *         The improvement after 2008 was done by Hartmut Schorrig.
 *
 **copyright***************************************************************************************
 * @content This header describes an interface for socket communication, 
 *          which supplies operation-system-independent calls. The using software is portable.
 *          The socket communication is defined as a quasi-standard similar in most of the operation systems,
 *          but few differences prevent a compatible usage. Therefore a wrapper is nice to have.
 *          The implementation of this routines are the wrapper to the special operation system.
 * @version 1.00
 *
 ****************************************************************************/

#ifndef __os_socket_h__
#define __os_socket_h__
#include <applstdef_emC.h>


#include <os_endian.h>


/**Version and history:
 * * 2012-02-20 Hartmut chg: use const* for all references which doesn't change the referred data.
 *   The implementations should be changed in that way. Recompile necessary.
 * * 2012-02-10 Hartmut chg: OS_SOCKADDR now linux/BSD-compatible. The applications should be adjusted
 *   because the names are changed to get compatibility with the linux/BSD-standard. Sorry that this decision
 *   are not done in the past.
 * * 2008-00-00 Hartmut improved
 * * 2008 00-00 Marcos improved
 * * 2005-00-00 Alfred created
 */
#define version_os_socket_h 0x20120220;

extern_C_BLOCK_

/* Konstanten */

#define OSS_OK                 0  /* Return erfoglreiche OP */

#define SO_IONBIO              10 /* temp values */

#define SO_MSG_BLOCKING        20
#define SO_MSG_NONBLOCKING     21

#define SO_READ_NOTIFY         ((unsigned short)0x1)   /* read data available */
#define SO_WRITE_NOTIFY        ((unsigned short)0x2)   /* write data space available */
#define SO_ACCEPT_NOTIFY       ((unsigned short)0x4)   /* connection request awaits */
#define SO_CLOSE_NOTIFY        ((unsigned short)0x8)   /* close down completed */
#define SO_CONNECT_NOTIFY      ((unsigned short)0x10)  /* connection completed */
#define SO_EXCEPT_NOTIFY       ((unsigned short)0x20)  /* exception has occurred */
#define SO_RSHUTDOWN_NOTIFY    ((unsigned short)0x40)  /* read direction shutdown by peer */
#define SO_TIMEOUT_NOTIFY      ((unsigned short)0x80)  /* request has timed out */
#define SO_WSHUTDOWN_NOTIFY    ((unsigned short)0x100) /* write direction shutdown by peer */

#define SO_RECEIVE_DOWN        0 /* os_shutdown: Empfangsfunktion eines Sockets unterbinden */
#define SO_SEND_DOWN           1 /* os_shutdown: Sendefunktion eines Sockets unterbinden */
#define SO_BOTH_DOWN           2 /* os_shutdown: Sende- und Empfangsfunktion eines Sockets unterbinden */


#define SO_IPNET               2 /**Adequate AF_INET */



#define OS_INVALID_SOCKET -1

typedef struct OS_Socket_t
{ int32 socket;
} OS_Socket;

typedef struct OS_DatagramSocket_t
{ OS_Socket socket;
} OS_DatagramSocket;



typedef struct OS_ServerSocket_t
{ OS_Socket socket;
} OS_ServerSocket;


typedef struct OS_StreamSocket_t
{ OS_Socket socket;
} OS_StreamSocket;

typedef struct OS_RawSocket_t
{ OS_Socket socket;
} OS_RawSocket;




/* Types */
//typedef int32 OS_SOCKET; 


typedef enum OS_SocketError_t
{
  OSSE_NOTCONN = -0x7f01   
, OSSE_WOULDBLOCK = -0x7f02
, OSSE_INVALIDSOCKET = -0x7f03
, OSSE_INVALIDPORT = -0x7f04
, OSSE_INVALIDADDRESS = -0x7f05
} OS_SocketError_e;


/**This structure is a os-independent structure for the socket address. 
 * It is compatible with the specification of sockaddr_in in Linux and some other operation systems.
 * They follow the BSD convention. If the os-specific structure is compatible with this,
 * the user-defined socket address can be used immediately internally.
 * But if the os uses another, maybe fine different struct, nevertheless this type should use in the application.
 * The implementation of the socket routines for the operation system copies the data of this struct
 * in a stack-local temporary os-specific struct and back again. The application should not be used
 * that os-specifics.
 *
 * Additionally it is regarded that any processor may be addressing only 32-bit-words. Some special processors (DSP)
 * do so. In that case the same memory layout is produced, but the port and the family is joined to one field.
 * Usual it is initialized with a constant only. That constant should be set to the proper value which contains
 * the port and the family (port in lo bytes.).
 *
 * The structure uses the int32BigEndian definition to secure that only a big endian value is stored,
 * see [[inc/os_endian.h]].
 */
typedef struct XXXXOS_SOCKADDR_t
{
  #ifdef OS_ONLY32Bit
  /**For processors with only 32 bit addressing, combine 2 16 bits. The memory layout is compatible. */
  int32BigEndian sin_port;
  #else
  /**The length of the address. sometimes it isn't use by the network implementation
   * because the length is given as extra parameter too.
   */
  //int8_t sin_len;
  /**The family of protocoll, usual 2 = SO_IPNET, in socket.h AF_INET. */
  int16_t sin_family;   //SO_IPNET for all Ip-net-connections.
  int16BigEndian sin_port;
  #endif
  /**The byte order should be non-changed. Changing of byte order in the implementation! This is not fact yet, only idea. */
  union ip_t {
  #ifndef OS_ONLY32Bit
    int8  b_addr[4];
  #endif
    int32BigEndian s_addr; } sin_addr;
  /**That are 8 fill bytes to regard compatibility to BSD and linux definition.
   * This bytes should be initialized with 0 and it should be unused.*/
  int32_t sin_zero[2];
} XXXXOS_SOCKADDR;



typedef struct OS_SOCKADDR_t
{
  /**Adress parameter 1. Using Socket, this is the portnumber (bit 15..0).
   * The represantation of port respectively endian is the endian of implementation platform.
   */
  int32 address1;

  /**Adress parameter 2. Using Socket, this is the IP-address..
   * The represantation of IP respectively endian is the endian of implementation platform.
   * The hi word is represented in bit 31..24.
   */
  int32 address2;

  /**Some internal data for inside representation. */
  MemUnit internalData[24];

} OS_SOCKADDR;







void set_OS_SOCKADDR(OS_SOCKADDR* dst, uint32 ip, uint16 port);



/**Constant for sind_addr if receive from all sources should be done. 
 * This is identically with INADRANY in socket.h.
 */  
#define kReceiveFromAll_OS_SOCKADDR 0



#define xxxDGRAM_OS_SOCKET 2  //Like SOCK_DGRAM in socket.h

#define xxxSTREAM_OS_SOCKET 1  //Like STREAM_DGRAM in socket.h


//NOTE: don't use the ntohl etc. methods, they are unsafe because there is no test of necessity on compile time.
//The better concept is: Use int32-values as parameter were a 4-Byte-IP-Address is need. 
//For the socket-specific address structures, use byte-variable in case to the os-implementation.
//See also os_endian.h This header solves the problem of endian not only for socket communication.

#define xxx_ntohl(x) ((unsigned long int) ((((unsigned long int)(x) & 0x000000ffU) << 24) | \
                                        (((unsigned long int)(x) & 0x0000ff00U) <<  8) | \
                                        (((unsigned long int)(x) & 0x00ff0000U) >>  8) | \
                                        (((unsigned long int)(x) & 0xff000000U) >> 24)))
#define xxx_htonl(x) xxx_ntohl(x)


/**Creates a Server-Socket. The operation system reserves memory for handling the socket
 * and returns a handle for it.
 * @param so reference for return-Identifier number for the socket from the operation system.
 * @return: 0 = ok; < 0= Error code. The error code is the specific error code from the operation system,
 *          Additional the sign-bit is set to get a negative value. 
 *          The error code should not be evaluated to programm a specific error handling.
 *          Only the return status ok/nok should be evaluated.
 *          But the error code should be shown in a user error message. 
 *          The user should know the specific error identifier of the operation system.
 */
int os_createServerSocket(OS_ServerSocket* so);



/**Creates a Stream-Socket. A Stream Socket is intent to connect to a ServerSocket on the opposite.
 * @param so reference for return-Identifier number for the socket from the operation system.
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket.
 */
METHOD_C int os_createStreamSocket(OS_StreamSocket* so);


/**Creates a Datagram-Socket. The operation system reserves memory for handling the socket
 * and returns a handle for it.
 * @param so reference for return-Identifier number for the socket from the operation system.
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket.
 */
METHOD_C int os_createDatagramSocket(OS_DatagramSocket* so);



/**Creates a Ip-Socket (Raw-Socket, whether UDP nor TCP). 
 * The operation system reserves memory for handling the socket
 * and returns a handle for it.
 * @param so reference for return-Identifier number for the socket from the operation system.
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket.
 */
METHOD_C int os_createRawSocket(OS_RawSocket* so);



/**Sets the just now opend socket to blocking or non blocking mode.
 * The implementation calls a special ioctrl routine from the system layer.
 * The standard behavior of a socket is the blocking mode. But this routine
 * should be called everytime after os_open to assure that the socket is in the expected mode.
 * @param so The Socket.
 * @param bNonBlocking If true than sets to non blocking, if false than sets to blocking.
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket. 
 */
METHOD_C int os_setNonBlocking(OS_DatagramSocket so, bool bNonBlocking);



/**Forces acception of connection via TCP. The request waits until the connection is established.
 * @param so Socket-Deskriptor.
 * @param dstAddr R�ckgabe des Socket-Namens der verbundenen Einheit in einer Struktur vom 
 * @param soTcp Socket-Deskriptor f�r zustande gekommene Verbindung
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket. 
 */
METHOD_C int os_accept(OS_ServerSocket so, OS_SOCKADDR* dstAddr, OS_StreamSocket* soTcp);




/**Assigns a local port to the opened but not bound socket.
 * @param so Socket-identifier.
 * @param ownAddr The own port address. If the 0.0.0.0 is used as IP-Address,
 *        then the port will be established on all available own IP-addresses. 
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket. 
 */
METHOD_C int os_bind(OS_Socket so, OS_SOCKADDR const* ownAddr);



/**Close the socket. Frees the memory for this socket in the operation system.
 * The socket-handle must not use furthermore, if the operation is successfull.
 * @param so Socket-identifier.
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket. 
 */
METHOD_C int os_close(OS_Socket so);



/**Forces a TCP-connection to the given destination address. This routine is called by a TCP-client.
 * @param so Socket-identifier.
 * @param dstAddr The requested port and address. 
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket. 
 */
METHOD_C int os_connect(OS_StreamSocket so, OS_SOCKADDR const* dstAddr);


METHOD_C int os_ioctlsocket(OS_Socket so, int request, void* arg, int arglen);


/**Force listening to incomming requests (TCP-Server). 
 * After them os_accept(...) can be called to accept TCP-requests from clients.
 * @param backlog Number of requests, which can be stored without call of os_accept.  
 *        If backlog = 0 the automaticly acknowledge of request won't be done.
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket. 
 */
METHOD_C int os_listen(OS_ServerSocket so, int backlog);


/**Waits for some events on sockets.
 * @param selp pointer to an array of OS_SOCKSEL structs.
 * @param cnt number of OS_SOCKSEL structs in selp.
 * @param waitp pointer to Timeout (in ms.) 
 *    =0 no wait
 *    >0 number of milliseconds to wait for events.
 *    -1 wait always.
 * @return: 0 = ok; < 0= Error code. See remarks on os_createStreamSocket. 
 */
//METHOD_C int os_nselect(OS_SOCKSEL* selp, int cnt, int32 waitp);


/**Receives from a socket.
 */
METHOD_C int os_recv(OS_StreamSocket so, void* buffer, int len, int flags);


/**Receives from a socket.
 */
METHOD_C int os_recvfrom(OS_DatagramSocket so, void* buffer, int len, int flags, OS_SOCKADDR* from);


/**Send.
 */
METHOD_C int os_send(OS_StreamSocket so, void const* buffer, int len, int flags);


/**Send.
 */
METHOD_C int os_sendto(OS_DatagramSocket so, void const* buffer, int len, int flags, OS_SOCKADDR const* to);


//METHOD_C int os_setsockopt(OS_SOCKET so, int level, int optname, int* optval, int optlen);


/**Closes a connection for TCP. */
METHOD_C int os_shutdown (OS_Socket so, int how);


/**Translates the operation-system-specific error number in a english text. */
METHOD_C char const* os_translateSocketErrorMsg(int nError);

_END_extern_C_BLOCK

#endif //__os_socket_h__
