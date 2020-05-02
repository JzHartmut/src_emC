#include <applstdef_emC.h>
#include <emC/Base/ExcThCxtBase_emC.h>
#include <emC/Base/String_emC.h>

bool assert_s_emC(bool cond, char const* text, int val1, int val2) {
  if(!cond) { 
    THROW_s0n(RuntimeException, text, val1, val2); 
  }
  return cond;
}
