#include <Jc/StringBufferJc.h>



void testReplaceStringBuilder()
{
  STACKTRC_ENTRY("testReplaceStringBuilder");
  struct { StringBuilderJc b; char _[20];} u;
  init_ObjectJc(&u.b.base.object, sizeof(u), 0);
  ctorO_StringBuilderJc(&u.b.base.object, _thCxt);

  replace_cII_StringBuilderJc(&u.b, 0, -1, z_CharSeqJc("first ABC"), -4, -1, _thCxt);

  STACKTRC_LEAVE;
}






int main_Test_StringJc()
//int main()
{ testReplaceStringBuilder();
  return 0;
}