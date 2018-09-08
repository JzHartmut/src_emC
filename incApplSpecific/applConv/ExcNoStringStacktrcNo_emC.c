#include <applstdef_emC.h>

typedef struct ExceptionStore_t {
  ExceptionJc first;
  ExceptionJc last;
  uint ctException;
} ExceptionStore;

ExceptionStore exceptionStore_g = {0};

void logSimple_ExceptionJc(int exc, int32 value, char const* file, int line) {
  if (exceptionStore_g.ctException == 0) {
    exceptionStore_g.ctException = 1;
    exceptionStore_g.first.exceptionNr = exc;
    exceptionStore_g.first.exceptionValue = value;
    //TODO exceptionStore_g.first.file = file;
    //exceptionStore_g.first.line = line;
  }
  else {
    //stop at max number, do not write 0!
    if( (exceptionStore_g.ctException +=1) ==0) { exceptionStore_g.ctException = (uint)-1; }
    exceptionStore_g.last.exceptionNr = exc;
    exceptionStore_g.last.exceptionValue = value;
    //exceptionStore_g.last.file = file;
    //exceptionStore_g.last.line = line;
  }
  
}


void ctor_ThreadContext_emC(struct ThreadContext_emC_t* thiz, void const* topStack) {
  //all remain 0
}
