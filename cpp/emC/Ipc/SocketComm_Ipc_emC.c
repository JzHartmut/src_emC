#include <emC/Ipc/SocketComm_Ipc_emC.h>

int stop(){ return 0;}

void ctor_SocketComm_Ipc_emC(SocketComm_Ipc_emC_s* thiz, uint32 ownAddr, uint16 ownPort) {
  memset(thiz, 0, sizeof(SocketComm_Ipc_emC_s));
  set_OS_SOCKADDR(&thiz->ownAddr, ownAddr, ownPort);
}


int rxThread (void* data) {
  SocketComm_Ipc_emC_s* thiz = (SocketComm_Ipc_emC_s*) data;
  while(thiz->openOk) {
    int nrBytes = os_recvfrom(thiz->so, thiz->rxBuffer, thiz->zRxBuffer, 0, &thiz->senderAddrRx);
    if(nrBytes < 0) {
      thiz->errorRx = nrBytes;
    } else {
      stop();
    }
  }

  return 0;
}


bool open_SocketComm_Ipc_emC(SocketComm_Ipc_emC_s* thiz, void* rxBuffer, int zRxBuffer) {
  thiz->error = os_createDatagramSocket(&thiz->so);
  if(thiz->error !=0) {
    return false;
  }
  thiz->error = os_bind(thiz->so.socket, &thiz->ownAddr);
  //printf("bind %d", thiz->error);
  if(rxBuffer !=null) {
    thiz->rxBuffer = rxBuffer;
    thiz->zRxBuffer = zRxBuffer;
    thiz->errorRx = create_Thread_OSemC(&thiz->rxThread, "rxSoComm", rxThread, thiz, 5,0);
    start_Thread_OSemC(&thiz->rxThread);
  }
  if(thiz->error ==0){
    thiz->openOk = 1;
    return true;
  } else {
    return false;
  }
}

void setAddrDst_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, uint32 addr, uint16 port) {
  set_OS_SOCKADDR(&thiz->dstAddr, addr, port);
}

bool sendToDst_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, void* data, int zData) {
  thiz->error = os_sendto(thiz->so, data, zData, 0, &thiz->dstAddr);
  return thiz->error == 0;    
}

bool close_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz) {
  thiz->error = os_close(thiz->so.socket);
  thiz->openOk = 0;
  return thiz->error ==0;
}


