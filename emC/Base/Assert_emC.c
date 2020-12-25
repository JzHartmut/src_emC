#include <applstdef_emC.h>
#include <emC/Base/Assert_emC.h>
#include <emC/Base/ExcThCxtBase_emC.h>

bool assert_s_emC(bool cond, char const* text, int val1, int val2, char const* file, int line) {
  if(!cond) { 
    THROW_s0nf(RuntimeException, text, val1, val2, file, line); 
  }
  return cond;
}
