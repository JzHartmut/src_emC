#ifndef HGUARD_SocketComm_Ipc_emC
#define HGUARD_SocketComm_Ipc_emC
#include <applstdef_emC.h>
#include <emC/Ipc/DatagramHead_Ipc_emC.h>
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

  int16 ctTx;      //: counts sendToDst_SocketComm_Ipc_emC(...) calls.
  int16 ctTxMax;   //: wait after this number of sendToDst_SocketComm_Ipc_emC(...) if seqnrRx is lesser

  int16 ctRx;      //: counts rx_SocketComm_Ipc_emC(...) calls.
  int16 ctRxLast;

  int16 dummy;
  int16 seqnrRx;

  /**It is possible to use this kind of telegram head (first 16 byte). That enables synchronization of tx and rx
   * via the given sequence number in the head. 
   * The reference to headTx is set with sendToDst_SocketComm_Ipc_emC(...),
   * the reference to headRx is set with open_SocketComm_Ipc_emC(...) with given rxBuffer address and a length >=16
   */
  DatagramHead_Ipc_emC_s* headTx, * headRx;

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
 * @param rxTimeout_us timeout for rx call
 */
bool open_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, void* rxBuffer, int zRxBuffer, int rxTimeout_us);

/**Sets the address where sendToDst_SocketComm_Ipc_emC(...) should use.
 */
void setAddrDst_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, uint32 addr, uint16 port);

/**Transmisson of one telegram to the given setAddrDst_SocketComm_Ipc_emC(...)
 * @param data data to transmit, should be set already in the correct byte order (usual big endian) in memory.
 * @param zData number of bytes to transmit from data
 * @param ctTxStop if >0 then transmit waits till 2*ctTxStop with 10 ms delay
 *   if the SocketComm_Ipc_emC::ctTx is >= this value.
 *  The SocketComm_Ipc_emC::ctTx will be set to 0 on any received telegram. 
 */ 
bool sendToDst_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, void* data, int zData, int16 seqnr, int ctTxStop);

/**Returns true if a new telegram was received.
 * If this is quest faster than the normal telegram communication it can access now the rxData which are written newly.
 * If the timing of call is slower, then it may be possible that the data are overridden again meanwhile
 * if the communication is not synchronized by itself (it means the counterpart transmits only on request).
 */
bool hasRxTelg (SocketComm_Ipc_emC_s* thiz);

static inline void setSeqnrRx ( SocketComm_Ipc_emC_s* thiz, int seqnr) { thiz->seqnrRx = seqnr; }

/**close the socket, close a running receive thread. */
bool close_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz);

#endif //HGUARD_SocketComm_Ipc_emC
