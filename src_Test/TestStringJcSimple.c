#include <Fwc/fw_String.h>
#include <stdio.h>


int testStringJc(StringJc input)
{ char buffer[100];  //in stack
  copyToBuffer_StringJc(input, 0, -1, buffer, sizeof(buffer));
  printf(buffer);
  return 0;
}



/*
int testStringBuilderJc(StringJc input)
{
  INSTACK_StringBuilderJc(bu, 100);

  append_StringBuilderJc(&bu.u, input);

  return 0;

}
*/



void main(void)
{

  StringJc s1 = z_StringJc("example text");
  testStringJc(s1);

  //testStringBuilder(s1);
}