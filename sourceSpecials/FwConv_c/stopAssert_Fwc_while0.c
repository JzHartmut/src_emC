#include <fw_assert.h>
#include <stdio.h>
#include <OSAL/os_time.h>
//Stop with memory exception.


void stopAssert_Fwc(void){
  int* ptr = 0;
  while(true){
    printf("exception-stop...");
    os_delayThread(1000);
  }

  //*ptr =0;
}