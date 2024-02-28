#ifndef HGUARD_SocketComm_Ipc_emC
#define HGUARD_SocketComm_Ipc_emC
#include <applstdef_emC.h>
#include <emC/OSAL/os_socket.h>
#include <emC/OSAL/thread_OSemC.h>

/**This struct is a simple socket implementation with the OSAL interface of emC
 * for datagram socket communication (UDP) with dedicated tx calls
 * and a rx thread with a callback routine. 
 * It is at least for simple communication of a controller with any program on PC via Ethernet. 
 */
typedef struct SocketComm_Ipc_emC_T {
  
  int16 error;     //: if not 0 any error is occured while open and send
  int16 errorRx;   //: if not 0 then any error is occured while create rx thread and receive

  int16 openOk;    //: it is used as boolean, 1 = open Ok, no error, 0=closed
  int16 zRxBuffer; //: size of the given rxBuffer, see open_SocketComm_Ipc_emC(...) 

  void* rxBuffer;  //: the buffer for receive, parameter from open_SocketComm_Ipc_emC(...)


  OS_SOCKADDR ownAddr;        //: the own socket, often 127.0.0.1 for local host, with port
  OS_SOCKADDR dstAddr;        //: a given destination address which is used for sendToDst_SocketComm_Ipc_emC(...)
  OS_SOCKADDR senderAddrRx;   //: the sender of a received telegram
  OS_DatagramSocket so;       //: the socket interface due to os_socket.h

  Thread_OSemC rxThread;      //: Thread organization for the receiver thread.

} SocketComm_Ipc_emC_s;

/**constructs emtpy data with given own address. */
void ctor_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, uint32 ownAddr, uint16 ownPort);

/**opens the socket
 * @param rxBuffer null or given, if given the rx thread will be created.
 * @param zRxBuffer size of the buffer, maybe lesser than 1500 Byte.
 */
bool open_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, void* rxBuffer, int zRxBuffer);

/**Sets the address where sendToDst_SocketComm_Ipc_emC(...) should use.
 */
void setAddrDst_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, uint32 addr, uint16 port);

/**Transmisson of one telegram to the given setAddrDst_SocketComm_Ipc_emC(...)
 */ 
bool sendToDst_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, void* data, int zData);

/**close the socket, close a running receive thread. */
bool close_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz);

#endif //HGUARD_SocketComm_Ipc_emC
