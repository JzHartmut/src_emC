#include <fw_assert.h>


//Stop with memory exception.


void stopAssert_Fwc(void){
  int* ptr = 0;
  *ptr =0;
}
