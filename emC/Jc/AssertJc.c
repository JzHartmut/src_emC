#include <emC/Jc/AssertJc.h>

#include <emC/Jc/StringJc.h>


#if !defined(DEF_NO_Exception_emC) || !defined(DEF_NO_ThreadContext_STACKTRC_emC)
StringJc exceptionInfo_B_AssertJc(char const* text, Exception_emC* exc, int firstLevel, int nrofLevels, bool bWithExceptiontext, ThCxt* _thCxt)
{
  return null_StringJc; //TODO
}
#endif


