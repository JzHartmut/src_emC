#include <applstdef_emC.h>
#include <emC/OSAL/os_time.h>

//#include <tms320.h>


void os_delayThread(int ms) {
//  int16 dct = ms <<7;  //*128, nr of ticks
//  int16 start = TA0R;
//  while( (((int16)TA0R) - start) < dct){
    //do nothing, interrupt can occurring
//  }
}



void os_delayThreadClocks(int clocks) {
//  int16 start = TA0R;
//  while( (((int16)TA0R) - start) < clocks){
    //do nothing, interrupt can occurring
//  }
}


OS_TimeStruct  os_getDateTime(){
    OS_TimeStruct time = {0};
    return time;
}
