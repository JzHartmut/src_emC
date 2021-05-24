#include <emC/Test/testAssert.h>
#include <applstdef_emC.h>

struct { int id; int line; int val1; int val2; } errorTab[20];

int ixErrorTab = 0;


void msgStartFileLine_testAssert_emC ( char const* msg, char const* file, int line){

}

void msgEndFileLine_testAssert_emC ( bool ok) {

}

bool expectMsgFileLine_testAssert_emC ( bool cond, char const* msg, char const* file, int line, ...) {
  //va_list args;
  //va_start(args, line);
  //todo because of vargs description is necessary.
  //errorTab[ixErrorTab].id = id;
  errorTab[ixErrorTab].line = line;
  //todo errorTab[ixErrorTab].val1 = val1;
  //errorTab[ixErrorTab].val2 = val2;
  if(++ixErrorTab >= ARRAYLEN_emC(errorTab)) { ixErrorTab = ARRAYLEN_emC(errorTab)-1; }
  return true;
}



