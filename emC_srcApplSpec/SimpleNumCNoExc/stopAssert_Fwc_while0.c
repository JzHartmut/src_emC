#include <applstdef_emC.h>
#include <stdio.h>
#include <emC/OSAL/os_time.h>
//Stop with memory exception.

#error do not use furthermore


void stopAssert_emC(void){
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

void uncatched_ExceptionJc(ExceptionJc* ythis, ThreadContext_emC_s* _thCxt)
{
  printf("uncatchedException: %8.8X - thread stopped", (uint)ythis->exceptionNr);
  os_FatalError(-1, "uncatchedException: - thread stopped", (uint)ythis->exceptionNr, 0);
  exit(255);
}

