#include <applstdef_emC.h>
#include <stdio.h>
#include <OSAL/os_time.h>
//Stop with memory exception.


void stopAssert_Fwc(void){
  int* ptr = 0;
  int cont = 1;  //possible set to 0 in debug
  while(cont){
    printf("exception-stop...");
    os_delayThread(1000);
  }

  //*ptr =0;
}



bool stop_AssertJc(void){
  int* ptr = 0;
  int cont = 1;  //possible set to 0 in debug
  while(cont){
    printf("exception-stop...");
    os_delayThread(1000);
  }
  return true;
  //*ptr =0;
}
