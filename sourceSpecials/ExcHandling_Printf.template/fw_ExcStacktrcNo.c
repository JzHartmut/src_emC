
#include <applstdefJc.h>
#include <stdio.h>

void throw_sJc_(char const* exceptionNr, StringJc msg, int value, int line)
{
}



void throw_s0Jc_(char const* exceptionNr, const char* msg, int value, int line)
{
}


char const* errorFile;

int errorFileline = -1;

char const* errorText;


void assertJc(bool condition)
{
  if(!condition) {
    errorText = "assertJc-fails";
    

  }

}


//#include <stdlib.h>
//#include <os_mem.h>
//void* os_allocMem(uint size) { return malloc(size); }

//int os_freeMem(void const* addr) { free((void*)addr); return 0; }


#if 0
//Note: in extra file! It is contained in os_thread too!
PtrVal_MemUnit threadContext;

PtrVal_MemUnit os_getCurrentUserThreadContext()
{
  return threadContext;
}

/**Sets the users thread context. This method can only be called one time for each thread.
 * @return error OS_UNEXPECTED_CALL if the users thread context is set already.
 */
METHOD_C int os_setCurrentUserThreadContext(OS_PtrValue mem)
{

  threadContext = mem;
  return 0;
}
#endif





