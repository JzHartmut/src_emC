#include <emC/OSAL/os_mem.h>
#include <stdlib.h>

void* os_allocMem(uint size){
    return malloc(size);
}

int os_freeMem(void const* pMemory){
    free((void*)pMemory);
    return 0;
}
