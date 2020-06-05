/************************************************************************************************
* Copyright/Copyleft:
*
* For this source the LGPL Lesser General Public License,
* published by the Free Software Foundation is valid.
* It means:
* 1) You can use this source without any restriction for any desired purpose.
* 2) You can redistribute copies of this source to everybody.
* 3) Every user of this source, also the user of redistribute copies
*    with or without payment, must accept this license for further using.
* 4) But the LPGL ist not appropriate for a whole software product,
*    if this source is only a part of them. It means, the user
*    must publish this part of source,
*    but don't need to publish the whole source of the own product.
* 5) You can study and modify (improve) this source
*    for own using or for redistribution, but you have to license the
*    modified sources likewise under this LGPL Lesser General Public License.
*    You mustn't delete this Copyright/Copyleft inscription in this source file.
*
* This source may be used also with another licence, if the author
* and all other here named co-authors have agreed to this contract.
* Especially a company can use a copy of this sources in its products without publishing.
* The user should have a underwritten contract therefore.
*
* @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
*
**end copyright***************************************************************************************
*
* This file contains only operations without dependencies to other CRJ files. 
*/
#include <applstdef_emC.h>
//#include <emC/Base/Object_emC.h>
#include <emC/Base/String_emC.h>
#include <string.h>  //C-standard

//Note: Implementation to search \0 in an limited range. 
int strnlen_emC  (  char const* text, int maxNrofChars)
{
  char const* text1 = text;
  char const* text9 = text + maxNrofChars;
  //optimization: test only one pointer register, which is incremented too
  while (text1 < text9 && *text1 != 0) { text1 += 1; }
  return (text1 - text);
}






StringJc zI_StringJc ( char const* src, int len)
{ StringJc ret;
  if(len < 0){ len = strnlen_emC(src, kMaxNrofChars_StringJc) - (-len) +1; } //nr of chars from end, -1 is till end. -2: without last char.
  else if(len >= mLength_StringJc) { len = mLength_StringJc -1; }  //limit it to max. 
  SET_StringJc(ret, src, (len & mLength_StringJc)); 
  return ret;
}



StringJc zMax_StringJc  (  char const* src, int max)
{
  StringJc ret;
  if(max > kMaxNrofChars_StringJc){ 
    max = kMaxNrofChars_StringJc;   //limit it, only for abstruse situation.  
  }
  int size = strnlen_emC(src, max);
  size |= mNonPersists__StringJc;
  SET_StringJc(ret, src, size);
  return ret;
}



int strncmp_emC ( char const* const text1, char const* const text2, int maxNrofChars)
{
  char const* text1a = (char const*) text1;
  char const* text2a = (char const*) text2;
  int maxNrofChars1 = maxNrofChars;
  char c1, c2;
  while(--maxNrofChars1 >=0 && (c1 = *text1a++) !=0 && (c2 = *text2a++) !=0
    && c1 == c2);
  //loop till end or till difference
  if(maxNrofChars1<0 || c1 == c2) return 0; //equal
  else if(c2 > c1) return maxNrofChars - maxNrofChars1;  //positive number, it is the position.
  else return maxNrofChars1 - maxNrofChars;  //negativ Number, abs is position of difference. 
  //int maddr = sizeof(int)-1;  //0x1 if int16, 0x0 if int-address-count
  //TODO: compare in int-memory-content, access with memory-boundary 
  //check first alignment
  //check whether 0 is contained, check mayNrofChars (-1, not limited)
  //if 0 contained, check last correct.
  //int val;
  //optimization: test only one pointer register, which is incremented too
  //return -1;  //TODO
}



int searchCharBack_emC ( char const* const text, char cc, int fromIx)
{
  char const* texte;
  if(fromIx <0) {
    int len = strnlen_emC(text, 1000);
    if(len + fromIx >=0) {
      texte = text + len + fromIx +1;
    } else {
      texte = text;
    }
  } else { 
    texte = text + fromIx +1;
  }
  while( --texte >= text) {
    if(*texte == cc) break;
  }
  return texte - text;


  //int const* texta = (int const*) (text + fromIx);
  //int maddr = sizeof(int)-1;  //0x1 if int16, 0x0 if int-address-count

  //int cci1 = cc; const int ccm1 = 0xff;
  //int cci2 = ((int)cc)<<8;  const int ccm2 = 0xff00;

  //while(texta >= (int const*)text) {
  //  int ci = *texta;
  //  if( (ci & ccm1) == cci1) break;

  //}
}



int searchChar_emC  (  char const* text, int zText, char cc)
{
  char const* text1 = text;
  char c1 = cc +1; //!=cc
  if (zText < 0) {
    zText = strnlen_emC(text, -zText);
  }
  char const* text9 = text + zText;
  //optimization: test only one pointer register, which is incremented too
  while (text1 < text9 && (c1 = *text1) != cc) {
    text1 += 1;
  }
  return c1 == cc ? text1 - text : -1; //maybe 0 if the request char is on the first position. -1 if not found.
}




/**Searches a String inside a given string with terminated length.
* NOTE: The standard-C doesn't contain such simple methods. strstr fails if the text isn't terminated with 0.
*/
int searchString_emC  (  char const* text, int zText, char const* ssearch, int zsearch)
{
  if (zText < 0) {
    zText = strnlen_emC(text, -zText);
  }
  if(zsearch < 0){ 
    zsearch = strnlen_emC(ssearch, -zsearch); 
  }
  char const* text9 = text + zText - zsearch+1;  //after last position where zsearch may be able to found. 
  char const* ssearch9 = ssearch + zsearch;
  //char const* s2 = ssearch + 1;
  char csearch1 = *ssearch;
  char const* text1 = text;                      //possible start of ssearch
  while (text1 < text9) {
    if(*text1 == csearch1) {
      //first char found
      char const* text2 = text1+1;       //pointer to compare with zsearch
      char const* ssearch2 = ssearch +1;
      while (ssearch2 < ssearch9 && *text2 == *ssearch2) {
        text2 +=1; ssearch2 +=1;     //character matches, increment
      }
      if (ssearch2 == ssearch9) {
        return (text1 - text);      //position of found string
      }
    }
    text1 = text1 +1;  //check next character in text whether it is csearch
  }
  return -1;  //not found.
}    
  
  
  
  
/*  
  //optimization: test only one pointer register, which is incremented too
  while (text3 <= text9 && text3 < text2) {
    cc = *ssearch;
    while (text1 < text9 && *text1 != cc) {
      text1 += 1;
    }
    text3 = text1 + 1;
    text2 = text1 + zsearch;
    s2 = ssearch + 1;
    while (text3 < text2 && *text3 == *s2) {
      text3 += 1;
      s2 += 1;
    }
  }
  if (text3 > text9) return -1;  //not found
  else return (text1 - text);    //maybe 0 if the request char is on the first position.
}

*/


//Note: effective and safe implementation, better then strncpy and strlcpy.
int strcpy_emC  (  char* dst, char const* src, int sizeOrNegLength)
{ if(sizeOrNegLength ==0) return 0;
  char const* src1 = src - 1;  //use pre-increment
  char const* src9 = src + (sizeOrNegLength < 0 ? -sizeOrNegLength -1 : sizeOrNegLength -1);  //exclusive max end address to use for char copy
  //src9 is the last used position to copy.
  char* dst1 = dst-1;  //use pre-increment
  //optimization: test only one pointer register, which is incremented too
  do { 
    *(++dst1) = *(++src1); 
  } while (src1 < src9 && *src1 != 0);
  if(src1 == src9 && sizeOrNegLength >0){ *dst1 = 0; src1 +=1; } //guarantees end-0, counts \0
  return (src1 - src);
}




bool equals_zI_StringJc  (  const StringJc ythis, const char* strCmp, int valueCmp  )
{ int countThis = VAL_StringJc(ythis) & mLength_StringJc; 
  int countCmp = valueCmp & mLength_StringJc;
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength_StringJc){
    countThis = strnlen_emC(strThis, mLength_StringJc);
  }
  if(countCmp == mLength_StringJc){
    countCmp = strnlen_emC(strCmp, countThis+1);
  }
  if(countCmp != countThis)
  { return(false);
  }
  else if(strThis == strCmp){
    return true;  //same length and same addresses of text.
  }
  else
  { bool bRet = memcmp(strThis, strCmp, countCmp) == 0;
    return(bRet);
  }
}



int copyToBuffer_StringJc  (  const StringJc thiz, int start, int end, char* buffer, int sizeBuffer)
{ //STACKTRC_ENTRY("copyToBuffer_StringJc");
  int nChars = VAL_StringJc(thiz) & mLength_StringJc;
  if (nChars == kIs_0_terminated_StringJc) {
    char const* str = thiz.addr.str;
    nChars = strnlen_emC(str, sizeBuffer);
  }
  //it is a StringJc
  //faster operation with memcpy instead check of isStringJc for any character.
  char const* str = thiz.addr.str;
  if (end < 0) {
    end = nChars + end + 1;  //end=-1 results in end = nChars
  }
  else if (end > nChars) {
    end = nChars;
  }
  if (end > start) {
    int nrofBytes = end - start;
    if (nrofBytes > sizeBuffer) {
      nrofBytes = sizeBuffer;
    }
    memcpy(buffer, str + start, nrofBytes);
    //STACKTRC_LEAVE; 
    return nrofBytes;
  }
  else {
    //STACKTRC_LEAVE; 
    return 0;
  }
}



int skipWhitespaces_emC  (  char const* text, int maxNrofChars)
{
  char const* text1 = text;
  char const* text9 = text + maxNrofChars;
  //optimization: test only one pointer register, which is incremented too
  while (text1 < text9 && *text1 <= 0x20) {
    text1 += 1;
  }
  return (text1 - text);    //maybe 0 if the request char is on the first position.
}


int trimRightWhitespaces_emC  (  char const* text, int maxNrofChars)
{
  char const* text1 = text + maxNrofChars - 1;
  //optimization: test only one pointer register, which is incremented too
  while (text1 >= text && *text1 <= 0x20) {
    text1 -= 1;
  }
  return (text1 - text + 1);    //maybe 0 if there are only whitespaces.
}





/** found an algorithm unusing division, because some divisions may be expensive in time
* at some processors.
*/
int toString_int32_emC(char* buffer, int zBuffer, int32 value, int radix, int minNrofCharsAndNegative, ThCxt* _thCxt)
{
  char cc;
  /**Array of values to test the position in digit. Fill it with 10, 100 etc if radix = 10;*/
  uint32 testValues[32]; //max 32
  uint32 uvalue;

  int idxTestValues = 0;
  int nChars = 0;
  int minNrofChars;
  STACKTRC_TENTRY("toString_int32_emC");
  if (minNrofCharsAndNegative < 0 && value < 0)
  {
    uvalue = -value; //may be -0x80000000
    buffer[nChars++] = '-';
  }
  else
  {
    uvalue = value;
  }
  minNrofChars = minNrofCharsAndNegative < 0 ? -minNrofCharsAndNegative : minNrofCharsAndNegative;
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
  { int nrofZero = minNrofChars - idxTestValues - 1;
  while (--nrofZero >= 0 && nChars < zBuffer) buffer[nChars++] = '0';
  }
  //test input digit
  { uint32 test;
  while (--idxTestValues >= 0 && nChars < zBuffer)
  {
    cc = '0';
    test = testValues[idxTestValues];
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
  STACKTRC_RETURN nChars;
}





