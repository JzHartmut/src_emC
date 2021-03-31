#include <emC/Test/testAssert.h>
#include <stdio.h>
#include <emC/Base/StringBase_emC.h>


void XXXxxxxTEST(char const* ident){
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
  char const* filename = dirFile(file);
  printf("\nTest: %s: (%s @ %d) ...\n", msg, filename, line);
}


void msgEndFileLine_testAssert_emC ( bool ok){
  if(ok)printf("ok");
}



bool expectMsgFileLine_testAssert_emC ( bool cond, char const* msg, char const* file, int line) {
  if(cond) { printf("  ok: %s\n", msg ); }
  else {
    char const* filename = dirFile(file);
    printf("  ERROR: %s (%s@%d)\n", msg,  filename, line);
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
bool exceptionFileLine_testAssert_emC ( Exception_emC* exc, char const* file, int line) {
  printf("  EXCEPTION:\n");
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