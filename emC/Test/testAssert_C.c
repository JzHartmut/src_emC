#include <emC/Test/testAssert.h>
#include <stdio.h>
#include <emC/Base/StringBase_emC.h>
#include <stdarg.h>



static char const* dirFile(char const* path) {
  int posSlash2 = -1;
  int posSlash1 = searchCharBack_emC(path, '/', -1); //from last char
  if(posSlash1 <0) posSlash1 = searchCharBack_emC(path, '\\', -1); //from last char
  if(posSlash1 >0) {
    posSlash2 = searchCharBack_emC(path, '/', posSlash1-1); //from last char
    if(posSlash2 <0) posSlash2 = searchCharBack_emC(path, '\\', posSlash1-1); //from last char
  }
  return path + posSlash2 +1;
}



void msgStartFileLine_testAssert_emC ( char const* msg, char const* file, int line){
  //print one dir + name of file.
  char const* filename = dirFile(file);
  printf("\nTest: %s: (%s @ %d) ...\n", msg, filename, line);
}


void msgEndFileLine_testAssert_emC ( bool ok){
  if(ok)printf("ok");
  else printf("ERROR");
}



bool expectMsgFileLine_testAssert_emC ( bool cond, char const* msg, char const* file, int line, ...) {
  char text[200];
  va_list args;
  va_start(args, line);
  vsnprintf(text, sizeof(text), msg, args);  //prepare the positive text maybe with variable args
  va_end(args);
  if(cond) { printf("  ok: %s\n", text ); }
  else {
    char const* filename = dirFile(file);
    printf("  ERROR: %s (@%d: %s)\n", text,  line, filename);
  }
  return cond;
}

bool XXXcheckMsgFileLine_testAssert_emC ( bool cond, char const* msg, char const* file, int line, int32 val1, int32 val2) {
  if(!cond) {
    printf("  ERROR: %s val1=%d=%8.8x val2 = %d=%8.8X (%s@%d)\n", msg,  val1, val1, val2, val2, dirFile(file), line);
  }
  return cond;
}


#ifdef DEFINED_Exception_emC
bool exceptionFileLine_testAssert_emC ( Exception_emC* exc, char const* file, int line) {
  #ifdef DEF_NO_StringUSAGE
    printf("EXCEPTION %d (%d, %d) @%d: %s\n", exc->exceptionNr, exc->exceptionValue, exc->val2, exc->line, exc->file );
  #else
    char buffer[100];  //in stack
    int nChars = copyToBuffer_StringJc(exc->exceptionMsg, 0, -1, buffer, sizeof(buffer)-1);
    buffer[nChars] = 0;
    printf("Test-EXCEPTION %d %s (%d, %d) @%d: %s\n", exc->exceptionNr, buffer, exc->exceptionValue, exc->val2, exc->line, exc->file );
  #endif
  #ifdef DEF_ThreadContext_STACKTRC
    printStackTrace_Exception_emC(exc, null);
  #endif
  return false;
}
#endif


CheckContinous_TEST::CheckContinous_TEST ( ) {
  this->start = -3;
  this->min = 9999999.9;
  this->max = -9999999.9;
}

void CheckContinous_TEST::checkCont ( double y) {
  this->y0 = this->y1;
  this->y1 = this->y2;
  this->y2 = this->y3;
  this->y3 = y;
  if(++start ==0) {
  } else if (start >0) {
    double ymid1 = (this->y2 + this->y0) /2;
    double ydiff1 = ymid1 - this->y1;
    double ymid2 = (this->y3 + this->y1) /2;
    double ydiff2 = ymid2 - this->y2;
    double ydd = ydiff2 - ydiff1;
    if(ydd > this->max) {
      this->max = ydd;
    }
    if(ydd < this->min) {
      this->min = ydd;
    }
  }


}
