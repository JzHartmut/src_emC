#include <emC/Ipc/SocketComm_Ipc_emC.h>

#include <emC/Base/Time_emC.h>

#include <stdio.h>

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
      thiz->ctRx += 1;                        // refresh ctTxStop, no stop.
      printf("^");
    }
  }

  return 0;
}


bool hasRxTelg (SocketComm_Ipc_emC_s* thiz) {
  int16 ctRx = thiz->ctRx;
  if(ctRx == thiz->ctRxLast) return false;
  else {
    thiz->ctRxLast = ctRx;
    return true;
  }
}

bool open_SocketComm_Ipc_emC(SocketComm_Ipc_emC_s* thiz, void* rxBuffer, int zRxBuffer, int rxTimeout_us) {
  thiz->error = os_createDatagramSocket(&thiz->so);
  if(thiz->error !=0) {
    return false;
  }
  thiz->error = bind_OS_Socket(thiz->so.socket, &thiz->ownAddr, rxTimeout_us);
  //printf("bind %d", thiz->error);
  if(rxBuffer !=null) {
    thiz->rxBuffer = rxBuffer;
    thiz->zRxBuffer = zRxBuffer;
    if(zRxBuffer >= sizeof(*thiz->headRx)) {
      thiz->headRx = (DatagramHead_Ipc_emC_s*) rxBuffer;
    }
    if(rxTimeout_us == 0) {                      // create an rx thread only if no rx timeout, because the rxThread does not need timeout
      thiz->errorRx = create_Thread_OSemC(&thiz->rxThread, "rxSoComm", rxThread, thiz, 5,0);
      start_Thread_OSemC(&thiz->rxThread);
    }
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


bool waitForRxAckn ( ) {
  int32 seqTx = 0;
  return false;
}

bool sendToDst_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz, void* data, int zData, int16 seqTx, int ctTxStop) {
  //if(++thiz->ctTx >= ctTxStop) {
  while( (seqTx - thiz->seqnrRx) > ctTxStop) { 
    printf("sleep... seqTx = %d", seqTx);
    if(thiz->rxThread.handleThread == null && thiz->headRx !=null) {
      int nrBytes = os_recvfrom(thiz->so, thiz->rxBuffer, thiz->zRxBuffer, 0, &thiz->senderAddrRx);
      if(nrBytes < 0) {
        thiz->errorRx = nrBytes & 0x7fffffff;
      } else if(nrBytes ==0) {                  // this is a timeout
        thiz->seqnrRx = seqTx;                  // to go forward with simulation, delayed 
      } else {
        thiz->ctRx += 1;                        // refresh ctTxStop, no stop.
        printf("^");
        thiz->seqnrRx = (int16)getInt32BigEndian(&thiz->headRx->seqnr);
      }
    }
    else {
      while( ctTxStop >0 && ++thiz->ctTx >= ctTxStop && thiz->ctTx < ctTxStop +20) { // timeout 20 ms
        sleep_Time_emC(1);
      }
    }
    thiz->ctTx = 0;
    printf(" seqRx=%d\n", thiz->seqnrRx);
  }
  
  thiz->error = os_sendto(thiz->so, data, zData, 0, &thiz->dstAddr);
  return thiz->error == 0;    
}

bool close_SocketComm_Ipc_emC (SocketComm_Ipc_emC_s* thiz) {
  thiz->error = os_close(thiz->so.socket);
  thiz->openOk = 0;
  return thiz->error ==0;
}


