#include <emC/Test/testAssert.h>
#include <stdio.h>


void TEST(char const* ident){
  printf("\nTest: %s ...", ident);
}



void expectMsgFileLine_testAssert_emC(char const* msg, char const* file, int line) {
  printf("\n%s@%d: %s", file, line, msg);

} 
