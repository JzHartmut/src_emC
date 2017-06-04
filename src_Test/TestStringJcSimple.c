#include <Fwc/fw_String.h>
#include <stdio.h>


int testStringJc(StringJc input)
{ char buffer[100];  //in stack
  int nChars = copyToBuffer_StringJc(input, 0, -1, buffer, sizeof(buffer)-1);
  buffer[nChars] = 0;  //0-termination necessary here.
  printf(buffer);
  return 0;
}








int testStringBuilderJc(StringJc input)
{

  struct{ StringBuilderJc u; char __addchars[96];} bu = {0};
  
  STACKTRC_ENTRY("testStringBuilderJc");
  ctor_addSize_StringBuilderJc(&bu.u, 96); 

  append_c_StringBuilderJc(&bu.u, input, _thCxt);

  CharSeqJc cbu = toCharSeqJc_StringBuilderJc(&bu.u);

  char buffer[100];  //in stack
  int nChars = copyToBuffer_CharSeqJc(cbu, 0, -1, buffer, sizeof(buffer)-1, _thCxt);
  buffer[nChars] = 0;  //0-termination necessary here.
  printf(buffer);
  
  STACKTRC_LEAVE;
  return 0;

}



void testConstants()
{
  ASSERT_Fwc(mLength__StringJc == 0x3fff);
  ASSERT_Fwc(kIs_0_terminated_StringJc == 0x3fff);
  ASSERT_Fwc(kIsStringBuilder_CharSeqJc == 0x3ffe);
  ASSERT_Fwc(kIsCharSeqJc_CharSeqJc == 0);
  ASSERT_Fwc(mIsCharSeqJcMtbl_CharSeqJc == 0);
  ASSERT_Fwc(mMtbl_CharSeqJc == 0);
  ASSERT_Fwc(kMaxNrofChars_StringJc == 0x3ffd);
  ASSERT_Fwc(mNonPersists__StringJc == 0x4000);
  ASSERT_Fwc(mThreadContext__StringJc == 0x8000);

}



void main(void)
{
  testConstants();
  StringJc s1 = z_StringJc("example text");
  testStringJc(s1);

  testStringBuilderJc(s1);
}



void stopAssert_Fwc(char const* file, int line)
{
  printf("Assertion failed at line %d in %s\n", line, file);
}