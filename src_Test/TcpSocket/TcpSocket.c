

#include <os_Socket.h>
#include <os_thread.h>

static bool isError(char const* what, int error){
  if(error == 0) return false;
  else {
    printf("error on %s: %d\n", what, error & 0x7fffffff);
    return true;
  }
}







typedef struct ServiceForClient_t
{
  OS_HandleThread threadId;
  OS_SOCKADDR clientAddr;
  OS_StreamSocket soToClient;
  char buffer[1500];
} ServiceForClient;



int run_ServiceForClient(void* data)
{ ServiceForClient* thiz = (ServiceForClient*) data;
  bool bRun = 1;
  while(bRun) {
  
    int bytes = os_recv(thiz->soToClient, thiz->buffer, sizeof(thiz->buffer)-1, 0);
    if(bytes >0) { 
      thiz->buffer[bytes] = 0;
      printf(thiz->buffer);
    } else {
      printf("receive error %d\n", bytes &0x7fffffff);
      os_close(thiz->soToClient.socket);
      bRun = 0;
    }
  }
  return 0;
}



typedef struct ServerExample_t
{
  int32 ixServices;

  ServiceForClient services[20];


} ServerExample;




//Call from main: Initializes a server port, 
void actAs_ServerExample(ServerExample* thiz)
{

  bool bRun = 1;

  OS_ServerSocket serverSocket = { 0 };

  OS_SOCKADDR listenPort;

  int error = os_createServerSocket(&serverSocket);

  if(error !=0) {
    printf("error\n");
    return;
  }
  else {
    set_OS_SOCKADDR(&listenPort, 0x7f000001, 0xae00);
    if(isError("bind", os_bind(serverSocket.socket, &listenPort))) return;
    if(isError("listen", os_listen(serverSocket, 5))) return;

    while(bRun) {
      OS_StreamSocket connectSocket = { 0 };
      OS_SOCKADDR connectPort;
      if(isError("accept", os_accept(serverSocket, &connectPort, &connectSocket))){
        bRun = 0; 
      } else { 
        ServiceForClient* clientThread = &thiz->services[thiz->ixServices++];
        clientThread->soToClient = connectSocket;
        clientThread->clientAddr = connectPort;
        //create a thread for this connection.
        os_createThread(&clientThread->threadId, run_ServiceForClient, clientThread, "client", 100, 0);
      }
    }
  }
}





void actAsClient()
{
  bool bRun = 1;

  OS_StreamSocket clientSocket = { 0 };

  OS_SOCKADDR serverAddr = {0};

  OS_SOCKADDR clientAddr = {0};

  int error = os_createStreamSocket(&clientSocket);

  if(error !=0) {
    printf("error\n");
    return;
  }
  else {
    set_OS_SOCKADDR(&clientAddr, 0x7f000001, 0xae80);
    set_OS_SOCKADDR(&serverAddr, 0x7f000001, 0xae00);
    os_bind(clientSocket.socket, &clientAddr);
    error = os_connect(clientSocket, &serverAddr);
    if(error !=0) {
      printf("error connect = %d \n", error & 0x7fffffff);
      return;
    }
    else {
      char buffer[1500];
      int bytes = sprintf(buffer, "test\n");
      os_send(clientSocket, buffer, bytes, 0);
      os_shutdown(clientSocket.socket, SO_BOTH_DOWN);
      os_close(clientSocket.socket);
    }
  }
}







static ServerExample serverData = {0};




int main(int zargs, char** args)
{
  if(zargs >=2){
    if(args[1][0] == 's') { 
      actAs_ServerExample(&serverData);
    } else if(args[1][0] == 'c') { 
      actAsClient();
    }
  }
  return 0;
}

