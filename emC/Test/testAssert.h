#ifndef HEADERGUARD_org_vishia_emC_Test_testAssert
#define HEADERGUARD_org_vishia_emC_Test_testAssert
#include <applstdef_emC.h>

/**Outputs a short message "Test: ident" starting with newline. */
extern_C void TEST(char const* ident);



#ifdef __cplusplus


#include <iostream>

#define EXPECT_TRUE(VAL) if(EXPECT_TRUEmsg1(VAL, __FILE__, __LINE__)) std::cerr

#define EXPECT_FALSE(VAL) if(EXPECT_TRUEmsg1(!(VAL), __FILE__, __LINE__)) std::cerr

void EXPECT_TRUEmsg(bool val, char const* msg);

void EXPECT_FALSEmsg(bool val, char const* msg);

bool EXPECT_TRUEmsg1(bool val, char const* msg, int line);

void EXPECT_FALSEmsg1(bool val, char const* msg, int line);

#endif  //__cplusplus


extern_C void expectMsgFileLine_testAssert_emC(char const* msg, char const* file, int line);

#define EXPECTs_TRUE(COND, MSG) if(!(COND)) expectMsgFileLine_testAssert_emC(MSG, __FILE__, __LINE__)

#define EXPECTs_FALSE(COND, MSG) if((COND)) expectMsgFileLine_testAssert_emC(MSG, __FILE__, __LINE__)





#endif //HEADERGUARD_org_vishia_emC_Test_testAssert
