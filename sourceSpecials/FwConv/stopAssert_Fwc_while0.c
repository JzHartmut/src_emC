#include <fw_assert.h>
#include <Jc/ThreadJc.h>
#include <stdio.h>

//Stop with memory exception.


void stopAssert_Fwc(void){
  int* ptr = 0;
  while(true){
    printf("exception-stop...");
    sleep_ThreadJc(1000, null);
  }

  //*ptr =0;
}
