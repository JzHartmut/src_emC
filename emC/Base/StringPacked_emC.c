#include <emC/Base/StringPacked_emC.h>



int strncmpPacked_emC ( MemUnit const* const text1, char const* const text2, int const maxNrofChars) {
  MemUnit const* text1a = text1;
  char const* text2a = text2;
  int maxNrofChars1 = maxNrofChars;
  char c1, c2;
  while(--maxNrofChars1 >=0 && (c2 = *text2a++) !=0) {
    MemUnit d1 = *text1a++;
    c1 = (char)(d1 & 0xff);  //d1 may be a char on byte access platform because MemUnit is a char
    if(c1 != c2) { break; }
    #ifdef MemUnit_16bit
      if(--maxNrofChars1 <0) { break; }
      c1 = (char)((d1 >>8) & 0xff);
      if( (c2 = *text2a++) ==0) { break; }
      if(c1 != c2) { break; }
    #endif
  }
  //loop till end or till difference
  if(maxNrofChars1<0 || c1 == c2) return 0; //equal
  else if(c2 > c1) return maxNrofChars - maxNrofChars1;  //positive number, it is the position.
  else return maxNrofChars1 - maxNrofChars;  //negativ Number, abs is position of difference.
}
