#include <applstdefJc.h>
#include <stdio.h>

int checkThrow(int x)
{ if (x<0) {
    x=0;
    THROW_s0(IllegalArgumentException, "", x);
  }
  return x;
}




int checkTry(int x)
{
  int ret;
  TRY {
    ret = checkThrow(x);
  } _TRY
  CATCH(IllegalArgumentException, exc) {
    printf("faulty");
    ret = -1; 
  }
  END_TRY
  return ret;
}



int fnFaultyPtr()
{ int* ptr = 0;
  *ptr = 123;
  return *ptr;
}



void main(char const** args)
{

  checkTry(-2);

}
