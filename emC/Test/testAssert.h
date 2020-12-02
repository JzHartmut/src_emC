#ifndef HEADERGUARD_org_vishia_emC_Test_testAssert
#define HEADERGUARD_org_vishia_emC_Test_testAssert
#include <applstdef_emC.h>

/**Outputs a short message "Test: ident" starting with newline. */
extern_C void XXXXTEST(char const* ident);


#ifdef __cplusplus


//#include <iostream>

#if 0
#define EXPECT_TRUE(VAL) if(EXPECT_TRUEmsg1(VAL, __FILE__, __LINE__)) std::cerr

#define EXPECT_FALSE(VAL) if(EXPECT_TRUEmsg1(!(VAL), __FILE__, __LINE__)) std::cerr
#endif

void EXPECT_TRUEmsg(bool val, char const* msg);

void EXPECT_FALSEmsg(bool val, char const* msg);

bool EXPECT_TRUEmsg1(bool val, char const* msg, int line);

void EXPECT_FALSEmsg1(bool val, char const* msg, int line);

#endif  //__cplusplus

extern_C void msgStartFileLine_testAssert_emC ( char const* msg, char const* file, int line);

/**Output always a test starting with "  ok " if cond==true*/
extern_C bool expectMsgFileLine_testAssert_emC ( bool cond, char const* msg, char const* file, int line);

/**Output only a text if cond ==false, silent if ok. */
extern_C bool checkMsgFileLine_testAssert_emC ( bool cond, char const* msg, char const* file, int line);

#ifdef DEFINED_Exception_emC  //else ist is not available, for simple tests.
extern_C bool exceptionFileLine_testAssert_emC ( ExceptionJc* exc, char const* file, int line);
#endif

extern_C void msgEndFileLine_testAssert_emC ( bool ok);

#define TEST_START(MSG) bool bTESTok = true; msgStartFileLine_testAssert_emC(MSG, __FILE__, __LINE__)

/**Test, output ok MSG if ok, only on error with file and line. */
#define TEST_TRUE(COND, MSG) if(!expectMsgFileLine_testAssert_emC(COND, MSG, __FILE__, __LINE__)) bTESTok = false;

/**Checks only, output only if error*/
#define CHECK_TRUE(COND, MSG) if(!checkMsgFileLine_testAssert_emC(COND, MSG, __FILE__, __LINE__)) bTESTok = false;

#define EXPECTs_FALSE(COND, MSG) if((COND)) expectMsgFileLine_testAssert_emC(MSG, __FILE__, __LINE__)

#define TEST_END msgEndFileLine_testAssert_emC(bTESTok)

#define TEST_EXC(EXC) exceptionFileLine_testAssert_emC(EXC, __FILE__, __LINE__)


static inline bool check_testAssert(float val, float cmp, float accuracy) {
  float diff = val - cmp;
  return diff < accuracy && diff > -accuracy; 
}

#endif //HEADERGUARD_org_vishia_emC_Test_testAssert
