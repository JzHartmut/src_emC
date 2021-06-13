/**This file offers a socmd.exe which sends a command via socket connection
 * and UDP telegram to a receiver.
 * The receiver is often a Java program which executes this cmd
 * for any desired control operation.
 * Such a socmd.exe helps to integrate a Java process in any desired environment
 * which can execute commands from the OS. That is true for many script base applications.
 * Made by Hartmut Schorrig, Germany, www.vishia.org
 * Copyright/left LPGL license.
 * This license remark also in the executable must not deleted.
 */
#include <applstdef_emC.h>
#include <emC/OSAL/os_socket.h>
#include <emC/J1c/StringPartScanJc.h>
#include <stdio.h>
#include <stdlib.h>
 
/**The data of args: */


typedef struct SocketCmd_T {
  OS_DatagramSocket soOwn;
  
  OS_SOCKADDR addrOwn;

  OS_SOCKADDR addrDst;

  /**The string given own address as cmdline argument. */
  char const* sAddrOwn;
  
  /**The string given destination address as cmdline argument. */
  char const* sAddrDst;
  
  int zTxArgs;
  char txArgs[200];  //reference to cmdArgs
} SocketCmd_s;

SocketCmd_s dataAppl = {0};


void prepAddr(char const* sAddr, OS_SOCKADDR* soAddr) {
  STACKTRC_ENTRY("prepDstAddr");
  StringJc sIp = INIZ_z_StringJc(sAddr);
  StringPartScanJc spIp(sIp);
  bool bOk = true; 
  int32 ipAddr, port;
  if(spIp.scanInteger().scanChar('.').scanOk()) {
    int32 n1, n2, n3, n4;
    n1 = (int32)spIp.getLastScannedIntegerNumber();
    bOk = spIp.scanInteger().scanChar('.').scanOk();
    if(bOk) {
      n2 = (int32)spIp.getLastScannedIntegerNumber();
      bOk = spIp.scanInteger().scanChar('.').scanOk();
      if(bOk) {
        n3 = (int32)spIp.getLastScannedIntegerNumber();
        bOk = spIp.scanInteger().scanOk();
        if(bOk) {
          n4 = (int32)spIp.getLastScannedIntegerNumber();
          ipAddr = (n1<<24) | (n2 <<16) | (n3<<8) | n4;
        }
      }
    }
  }
  else if(spIp.scan("0x").scanHex(8).scanOk()) {
    port = (int32)spIp.getLastScannedIntegerNumber();
  } else {
    bOk = false;
  }
  if(bOk && spIp.scanChar(':').scanHexOrDecimal(8).scanOk()) {
    port = (int32)spIp.getLastScannedIntegerNumber();  //portnr
  } else {
    bOk = false;
  }
  if(bOk) {
    set_OS_SOCKADDR(soAddr, ipAddr, port);
  } 
  else { 
    THROW_s0(IllegalArgumentException, "error ip syntax, \"UDP:127.0.0.1:12345\"", 0, 0);
  }
  
  STACKTRC_RETURN;
}



void openSocket(SocketCmd_s* thiz) {
  STACKTRC_ENTRY("openSocket");
  int ok = os_createDatagramSocket(&thiz->soOwn);
  if(ok !=0) THROW_s0(IllegalArgumentException, "open own socket fails", ok, 0);
  ok = os_bind(thiz->soOwn.socket, &thiz->addrOwn);
  if(ok !=0) THROW_s0(IllegalArgumentException, "bind own socket fails", ok, 0);
  STACKTRC_RETURN;
}



void txCmd(SocketCmd_s* thiz) {
  STACKTRC_ENTRY("txCmd");
  
  int ok = os_sendto(thiz->soOwn, thiz->txArgs, thiz->zTxArgs, 0, &thiz->addrDst);
  if(ok <0) THROW_s0(IllegalArgumentException, "tx via fails", ok, 0);
  
  STACKTRC_RETURN;
}






 
void main(int nArgs, char** argsCmd) {
  STACKTRC_ROOT_ENTRY("socketcmd");
  SocketCmd_s* thiz = &dataAppl;
  int erret = 0;
  TRY {
    if(nArgs == 1) {
    } else {
      for(int ixArg = 1; ixArg < nArgs; ++ixArg) {           // == evaluate cmd args
        char const* argCmd = argsCmd[ixArg];
        if(strncmp(argCmd, "-dst", 4)==0) {                   // store the dst address -ip:192.168.3.4:12345
          if(strnlen_emC(argCmd, 30) >4) {                   // either with this argument
            thiz->sAddrDst = argCmd+5;  //after separator char
          } else {
            thiz->sAddrDst = argsCmd[++ixArg];               // or from next arg
          }
        }
        else if(strncmp(argCmd, "-own", 4)==0) {                   // store the dst address -ip:192.168.3.4:12345
          if(strnlen_emC(argCmd, 30) >4) {                   // either with this argument
            thiz->sAddrOwn = argCmd+5;  //after separator char
          } else {
            thiz->sAddrOwn = argsCmd[++ixArg];               // or from next arg
          }
        }
        else {
          //                                                 // it is an argument to forward to dst
          if(thiz->zTxArgs < sizeof(thiz->addrDst)-4) {      // copy as one string, 
            thiz->txArgs[thiz->zTxArgs++] = '\"';            // always surrounded with "arg", maybe necessary.
            thiz->zTxArgs += strpncpy_emC(thiz->txArgs, thiz->zTxArgs, sizeof(thiz->addrDst)-2, argCmd, -1);
            thiz->zTxArgs += strpncpy_emC(thiz->txArgs, thiz->zTxArgs, sizeof(thiz->addrDst)-2, "\" ", -1);
          }
        }
      }
    }
    prepAddr(thiz->sAddrOwn, &thiz->addrOwn);
    prepAddr(thiz->sAddrDst, &thiz->addrDst);
    openSocket(thiz);
    printf("ok open socket %s\n", thiz->sAddrOwn);
    txCmd(thiz);
    printf("ok tx to %s: %s\n", thiz->sAddrDst, thiz->txArgs);
  }_TRY
  CATCH(Exception, exc) {
    printStackTrace_Exception_emC(exc, _thCxt);
  }
  END_TRY
  STACKTRC_RETURN;
}





void errorSystem_emC_  (  int errorCode, const char* description, int value1, int value2, char const* file, int line) {
  printf("ERROR SYSTEM: %d %s %d, %d @%s:%d", errorCode, description, value1, value2, file, line);
  exit(255);
}



//Note: The uncatched_Exception should be assigned to the application frame. It is not a part of a library.
//It should terminate the application, but some resources should be freed. The application frame may known which resources.
void uncatched_Exception_emC  (  Exception_emC* thiz, ThreadContext_emC_s* _thCxt) {
#ifdef DEF_NO_StringJcCapabilities
  printf("ERROR uncatched Exception @%s:%d", thiz->file, thiz->line);
#else
  char buffer[300] = { 0 };
  writeException(buffer, sizeof(buffer), thiz, __FILE__, __LINE__, _thCxt);
  printf(buffer);
#endif
}

