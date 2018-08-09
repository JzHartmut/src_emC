#ifndef __AssertJc_h__
#define __AssertJc_h__

#include <emC/Exception.h>

// #define stop_AssertJc()

#define exceptionInfo_AssertJc(TEXT, EXC, FIRST, NR, THCTX) exceptionInfo_B_AssertJc(TEXT, EXC, FIRST, NR, true, THCTX) 

METHOD_C StringJc exceptionInfo_B_AssertJc(char const* text, struct ExceptionJc_t* exc, int firstLevel, int nrofLevels, bool bWithExceptiontext, ThCxt* _thCxt);


#define illegalArgument_I_RetOrExceptionJc(COND, VAL, TXT, THCXT) (COND ? (VAL) : (VAL))

#endif  // __AssertJc_h__
