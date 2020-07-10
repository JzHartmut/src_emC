#include <emC/Test/testAssert.h>
#include <stdio.h>
#include <emC/Base/StringBase_emC.h>


void TEST(char const* ident){
  printf("\nTest: %s ...", ident);
}



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
  printf("\nTest: %s: (%s @ %d) ...\n", msg, dirFile(file), line);
}


void msgEndFileLine_testAssert_emC ( bool ok){
  if(ok)printf("ok");
}



bool expectMsgFileLine_testAssert_emC ( bool cond, char const* msg, char const* file, int line) {
  if(cond) { printf("  ok: %s\n", msg ); }
  else {
    printf("  ERROR: %s (%s@%d)\n", msg,  dirFile(file), line);
  }
  return cond;
}

bool checkMsgFileLine_testAssert_emC ( bool cond, char const* msg, char const* file, int line) {
  if(!cond) {
    printf("  ERROR: %s (%s@%d)\n", msg,  dirFile(file), line);
  }
  return cond;
}


#ifdef DEFINED_Exception_emC
bool exceptionFileLine_testAssert_emC ( ExceptionJc* exc, char const* file, int line) {
  printf("  EXCEPTION:\n");
  return false;
}
#endif
