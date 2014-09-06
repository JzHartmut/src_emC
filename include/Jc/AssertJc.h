#ifndef __AssertJc_h__
#define __AssertJc_h__

#include <Fwc/fw_Exception.h>
struct CharSequenceJc_t;

 #define stop_AssertJc()

#define exceptionInfo_AssertJc(TEXT, EXC, FIRST, NR, THCTX) exceptionInfo_B_AssertJc(TEXT, EXC, FIRST, NR, true, THCTX) 

METHOD_C struct CharSequenceJc_t* exceptionInfo_B_AssertJc(char const* text, ExceptionJc* exc, int firstLevel, int nrofLevels, bool bWithExceptiontext, ThCxt* _thCxt);


#endif  // __AssertJc_h__
