#include <emC/Base/StringNum_emC.h>

#ifndef DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE



/**found an algorithm unusing division, because some divisions may be expensive in time
 * at some processors.
 */
int toString_int32_emC(char* buffer, int zBuffer, int32 value, int radix, int minNrofCharsAndFlags)
{
  char cc;
  ASSERT_emC(radix >=8, "radix should be >=8", radix, 0);
  //Array of values to test the position in digit. Fill it with 10, 100 etc if radix = 10
  //or 16, 256, 4096 etc. for radix = 16, or 8, 64 ,... for radix 8
  uint32 testValues[11];    //11 position necessary for radix = 8. It is in stack.
  uint32 uvalue = (uint32)value;

  int idxTestValues = 0;
  int nChars = 0;
  int minNrofChars = (minNrofCharsAndFlags < 0 ? -minNrofCharsAndFlags : minNrofCharsAndFlags) & 0x1f;  //max. 16 char possible
  int showSign = minNrofCharsAndFlags & m_showNegative_toString_int32_emC;
  if (minNrofCharsAndFlags < 0 || showSign) {
    if(value < 0) {
      uvalue = -value; //may be -0x80000000
      buffer[nChars++] = '-';
    } else if(showSign == k_showPositiveSpace_toString_int32_emC) {
      buffer[nChars++] = ' ';
    } else if(showSign == k_showPositivePlus_toString_int32_emC) {
      buffer[nChars++] = '+';
    }
  }
  //
  { //fill in digigts to detect positions in digit
    uint32 powerRadix = radix;
    uint32 powerRadixLast = 0;
    while (uvalue >= powerRadix
      && powerRadix > powerRadixLast  //prevent overflow.
      )
    {
      testValues[idxTestValues++] = powerRadix;
      powerRadixLast = powerRadix;
      powerRadix *= radix;
    }
  }
  //
  //idxTestValues is the number of digits -1, because testValues[0] contains 10.  
  char cLeading0 = minNrofCharsAndFlags & m_leadingSpace_toString_int32_emC ? ' ' : '0';
  { int nrofZero = minNrofChars - idxTestValues - 1;
    while (--nrofZero >= 0 && nChars < zBuffer) buffer[nChars++] = cLeading0;
  }
  //test input digit
  { uint32 test;
    while (--idxTestValues >= 0 && nChars < zBuffer)
    {
      cc = '0';
      test = testValues[idxTestValues];  //starts on the highest digit position (for ex. 1000 if the value is >=1000 but <10000
      while (uvalue >= test)
      {
        cc += 1;
        uvalue -= test;
      }
      if (cc > '9')
      {
        cc += ('a' - '9' - 1);
      }
      buffer[nChars++] = cc;
    }
  }
  cc = (char)('0' + uvalue); //last digit
  if (cc > '9')
  {
    cc += ('a' - '9' - 1);
  }
  if (nChars < zBuffer)
  {
    buffer[nChars++] = cc;
  }
  return nChars;
}





int toString_float_emC(char* buffer, int zBuffer, float value, char const* format)
{
  //TODO use format, either as % 2.5f or "-222.33"
  int32 vali = (int32)(value);
  int ixBuffer = toString_int32_emC(buffer, zBuffer, vali, 10, -3);
  int32 valf = (int32)((value - vali) * 100.0f);  //2 digits fractional
  if(ixBuffer < zBuffer) { buffer[ixBuffer++] = '.';  }      //write fract. part as integer.
  ixBuffer += toString_int32_emC(&buffer[ixBuffer], zBuffer - ixBuffer, valf, 10, 2);
  return ixBuffer;
}



INT_NUM_emC parseIntRadix_emC(const char* srcP, int size, int radix, int* parsedChars, char const* ctrlChars)
{ INT_NUM_emC val = 0;
  enum {
    bNegativ=1,
    checkNegative=2,
    checkSign=4,
    checkHex=8,
    checkSpaceFirst=0x10,
    checkWhitespaceFirst = 0x20,
    checkSpaceAfterSign = 0x40
  }; 
  char st = 0;
  
  if(ctrlChars !=null) {
    int cc = *ctrlChars;
    if(cc==' ') { st|=checkSpaceFirst; cc = *(++ctrlChars); }
    else if(cc=='\n') { st|=checkWhitespaceFirst; cc = *(++ctrlChars); }
    if(cc=='-') { st|=checkNegative; cc = *(++ctrlChars); }
    else if(cc=='+') { st|=checkSign; cc = *(++ctrlChars); }
    if(cc==' ') { st|=checkSpaceAfterSign; cc = *(++ctrlChars); }
    if(cc=='x') { st|=checkHex; ctrlChars +=1; }
  }
  int digit = -1;  //set to 0 if 0 detected
  char cc;
  const char* src = srcP;
  int maxDigit = (radix <=10) ? '0' + radix -1 : '9'; 
  while(size != 0 && (cc = *src) !=0) {  //hint: size=-1 as input is admissible, hence test !=0, not >0
    if(cc <=' ') {
      if( (cc==' ' || cc=='\t') && st&(checkSpaceFirst|checkWhitespaceFirst|checkSpaceAfterSign) ) { cc=0; } //skipped
      else if((cc=='\t' || cc=='\n' || cc=='\r' || cc=='\f') && st&checkWhitespaceFirst) { cc=0; } //skipped
      //else: cc remains, test later in ctrlChars
      //else { break; }        //not accepted. breaks the while loop. 
    }
    else if(st&checkHex && (cc == 'x' || cc == 'X') && digit ==0 && val == 0) {
      radix = 16;          //before: 0 is detected, no value before
      st&= ~(checkHex|checkSpaceFirst|checkWhitespaceFirst|checkSpaceAfterSign);   // is detected
      cc = 0;
    } 
    else if(cc=='-' && val ==0 && st&(checkNegative|checkSign)) {
      st|=bNegativ;
      st&= ~(checkNegative|checkSign|checkSpaceFirst|checkWhitespaceFirst);
      cc = 0;
    }
    else if(cc=='+' && val ==0 && st&(checkSign)) {
      st&= ~(checkNegative|checkSign|checkSpaceFirst|checkWhitespaceFirst);
      cc = 0;
    }
    else if( (digit = cc - '0') >=0 
           && (  cc <= maxDigit         // it is '9' for radix >=10
              || (radix >10 && (  (cc >= 'A' && (digit = (cc - 'A'+ 10)) <=radix)
                               || (cc >= 'a' && (digit = (cc - 'a'+ 10)) <=radix)
           )  )  )             ) {     // digit is 10..15 for radix = 16      
      val = radix * val + digit;
      st&= ~(checkSpaceFirst|checkWhitespaceFirst|checkSpaceAfterSign);   // is detected
      cc = 0;
    }
    if( cc !=0 ) {
      if(ctrlChars !=null) {
        st&= ~(checkSpaceFirst|checkWhitespaceFirst|checkSpaceAfterSign|checkHex);   // is detected
        digit = -1;             //do not detect 0 for 0x
        char const* addChars1 = ctrlChars;
        char c1;                //check first ctrlChars is "-" then accept "-" as sign
        do {                    //skip all chars in ctrlChars as separator inside the number
          c1 = *addChars1++;
        } while(c1 !=0 && c1 !=cc);   //search in ctrlChars till 0-terminated or on found c1
        if(c1 == 0) { 
          size =0;              //cc was not applicable also in the ctrlChars, break the while loop
        }
      }
      else {
        size =0;                //cc was not applicable, break the while loop
      }
    }
    if(size !=0) {
      size -=1;
      src +=1;                  //check next *src only if continue
    }
  }
  if(st&bNegativ){ val = -val; }
  if(parsedChars !=null){              // write nr of parsed chars only if desired.
    *parsedChars = (int)(src - srcP);  //note: src refers the not used char after last used.
  }
  return( val);
}


float parseFloat_emC(const char* src, int size, int* parsedCharsP)
{
  int parsedChars = 0;
  float ret;
  int zParsed;
  ret = (float)parseIntRadix_emC(src, size, 10, &zParsed, null);
  parsedChars += zParsed;  //maybe 0 if .123 is written
  src += zParsed; size -= zParsed;
  if(*src=='.'){
    float fracPart = (float)parseIntRadix_emC(src+1, size-1, 10, &zParsed, null);
    if(zParsed >0){
      switch(zParsed){
      case 1: fracPart *= 0.1f; break;
      case 2: fracPart *= 0.01f; break;
      case 3: fracPart *= 0.001f; break;
      case 4: fracPart *= 0.0001f; break;
      case 5: fracPart *= 1e-5f; break;
      case 6: fracPart *= 1e-6f; break;
      case 7: fracPart *= 1e-7f; break;
      case 8: fracPart *= 1e-8f; break;
      case 9: fracPart *= 1e-9f; break;
      case 10: fracPart *= 1e-10f; break;
      }
      ret += fracPart;
    }
    parsedChars += zParsed+1;  //maybe 0 if .123 is written
    src += zParsed+1; size -= zParsed-1;
  }
  //TODO exponent
  if(parsedCharsP !=null){
    *parsedCharsP = parsedChars;
  }
  return ret;
}







#endif //DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE
