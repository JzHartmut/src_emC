#include <emC/CheckStack_emC.h> 
#include <applstdef_emC.h>

int buildCheckStack_emC(void* addr, int stacksize)
{
  int ret = 0;
  intptr_t addr0 = (intptr_t)addr;
  intptr_t mask = stacksize -1;     //stacksize 0x10000 is mask 0x00ffff
  addr0 &= ~(sizeof(int) -1);       //preserve boundary.
  addr0 += sizeof(int);             //start at next after boundary-addr.
  while( (addr0 & mask) !=0) { //The end of stack is not reached. 
    ret += *(int*)addr0;   //simple: checksum
    addr0 += sizeof(int);             //start at next after boundary-addr.
  }
  return ret;
}




bool testCheckStack_emC(void* addr, int checkvalue, int stacksize)
{
  int check2 = 0;
  intptr_t addr0 = (intptr_t)addr;
  intptr_t mask = stacksize -1;   
  addr0 &= ~(sizeof(int) -1);       //preserve boundary.
  addr0 += sizeof(int);             //start at next after boundary-addr.
  while( (addr0 & mask) !=0) { //The end of stack is not reached. stacksize 0x10000 is mask 0x00ffff
    check2 += *(int*)addr0;         //simple: checksum
    addr0 += sizeof(int);             //start at next after boundary-addr.
  }
  if(check2 != checkvalue) {
    return false;  // <============== set a breakpoint here!!!
  } else {
    return true;
  }
}
