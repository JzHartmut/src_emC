/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this software-package the LGPL Lesser General Public License, 
 * published by the Free Software Foundation is valid at first. 
 * This is valid, if no other special licence contract is agreed. It means: 
 * 1. You can use this source without any restriction for any desired purpose.  
 * 2. You can redistribute copies of this source to everybody.  
 * 3. Every user of this source, also the user of redistribute copies with or without payment, 
 *    must accept this license for further using.  
 * 4. But the LPGL ist not appropriate for a whole software product, 
 *    if this source is only a part of them. It means, the user must publish this part of source, 
 *    but don't need to publish the whole source of the own product.  
 * 5. You can study and modify (improve) this source for own using or for redistribution, 
 *    but you have to license the modified sources likewise under this LGPL Lesser General Public License.  
 * 6. You mustn't delete this Copyright/Copyleft inscription in this software package and in all source files. 
 *    If you need only a part of this software-package, you must place this Copyright/Copyleft inscription 
 *    at an easily noticeable position in the adequate file tree. 
 * 7. If you are changing and publishing the content of source files, 
 *    you mustn't delete the Copyright/Copyleft inscription inclusive the first author(s) in the source files. You have to write your changes and your name additionally in the description part for changes in the source files. If you use a part from source files as copy in your own files only, you have to name the author of that part of the sources in your sources. Furthermore you have to declare the usage of sources of the author in your product. 
 * Special licence agreements:
 *
 * If this software or a part of them will be used in a comprehensive software-package 
 * without free publishing of its content or usage, 
 * then a special licence agreement in any other form is possible and necessary. 
 * All developers and users of this software-package should agree to it, 
 * with subscribing a contract, which is stored by both partners in paper-written form. 
 * The state of existence of such a contract doesn't need to be published.
 * But a proper hint to the special licence agreement have to be stored at a position in the file-tree, 
 * which is able to visit from outside, if the content of the files are able to visit from outside too. 
 * If the sources and its usage and the licence is secrecy, it is okay too.
 *
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content This file contains the implementation of os_file.h for MS-Windows 
 *          using the lo-level un-buffered file-routines.
 * @version 0.94
 * list of changes:
 * 2010-05-23: JcHartmut creation from os_Windows/os_file.c, from the fopen-routines.
 *
 * This method bodies are placed inside Fwc because simple applications (Exception_emC.c)
 * call only this method from string, without other dependencies.
 */

//Styleguide: Include the own header first, it should include all necessary depending headers itself. 
#include <emC/Base/String_emC.h>


//Styleguide: Include all necessities for implementation, the standard headers at least.
#include <string.h>   //strncpy









int parseIntRadix_emC(const char* srcP, int size, int radix, int* parsedChars, char const* addChars)
{ int val = 0;
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
  
  if(addChars !=null) {
    int cc = *addChars;
    if(cc==' ') { st|=checkSpaceFirst; cc = *(++addChars); }
    else if(cc=='\n') { st|=checkWhitespaceFirst; cc = *(++addChars); }
    if(cc=='-') { st|=checkNegative; cc = *(++addChars); }
    else if(cc=='+') { st|=checkSign; cc = *(++addChars); }
    if(cc==' ') { st|=checkSpaceAfterSign; cc = *(++addChars); }
    if(cc=='x') { st|=checkHex; addChars +=1; }
  }
  int digit = -1;  //set to 0 if 0 detected
  char cc;
  const char* src = srcP;
  int maxDigit = (radix <=10) ? '0' + radix -1 : '9'; 
  while(size != 0 && (cc = *src++) !=0) {
    size -=1;
    if(cc <=' ') {
      if( (cc==' ' || cc=='\t') && st&(checkSpaceFirst|checkWhitespaceFirst|checkSpaceAfterSign) ) { cc=0; } //skipped
      else if((cc=='\t' || cc=='\n' || cc=='\r' || cc=='\f') && st&checkWhitespaceFirst) { cc=0; } //skipped
      //else: cc remains, test later in addChars
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
      if(addChars !=null) {
        st&= ~(checkSpaceFirst|checkWhitespaceFirst|checkSpaceAfterSign|checkHex);   // is detected
        digit = -1;             //do not detect 0 for 0x
        char const* addChars1 = addChars;
        char c1;                //check first addChars is "-" then accept "-" as sign
        do {                    //skip all chars in addChars as separator inside the number
          c1 = *addChars1++;
          if(c1==cc) {
            break;  //accepted
          }
        } while(c1 !=0);        //break addChars on 0-terminated
        if(c1 == 0) { break; }  //breaks the scanning, cc is not accepted if not found in addChars
      }
      else {
        break;                  //cc was not applicatble
      }
    }
  }
  if(st&bNegativ){ val = -val; }
  if(parsedChars !=null){              // write nr of parsed chars only if desired.
    *parsedChars = (int)(src - srcP) -1;  //note: src refers the next char after last because first read cc then check
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




const char* getConstChar_StringJc(const StringJc* thiz)
{ //int count;
  //const char* sRet = getCharsAndLength_StringJc(thiz, &count);
  const char* sRet = PTR_StringJc(*thiz);
  return sRet;
}




/**This method is adequat zI_StringJc, but it dedicated the String as persistent. */
StringJc toStringFromPersist_zI_StringJc(char const* buffer, int nrofChars)
{ StringJc ret;
  SET_StringJc(ret, buffer, (nrofChars & mLength_StringJc)); 
  return ret;
}






char const* getCharsAndLength_StringJc(StringJc const* thiz, int* length)
{ char const* chars = PTR_StringJc(*thiz);
  if(chars == null){
    *length = 0;
  } else {
    int val = thiz->val;
    int nChars = val & mLength_StringJc;
    if(nChars == kIs_0_terminated_StringJc) {
      nChars = strnlen_emC(chars, kMaxNrofChars_StringJc);
    }
    if(nChars <= kMaxNrofChars_StringJc) {
      *length = nChars;
    } else {
      //STACKTRC_ENTRY("getCharsAndLength_StringJc");
      //THROW
      *length = 0;  //not supported here: CharSeqJc
      return null;
    }
  }
  return(chars);  //may be null
}




bool isZeroTerminated_StringJc(StringJc const thiz)
{ char const* chars = PTR_StringJc(thiz);
  int nChars = VAL_StringJc(thiz) & mLength_StringJc;
  if(nChars == mLength_StringJc) { nChars = strnlen_emC(chars, mLength_StringJc); }
  return chars[nChars] == 0;
}







char const* getCharConst_StringJc(StringJc const thiz, char* const buffer, int const zBuffer)
{
  int len;
  char const* str = getCharsAndLength_StringJc(&thiz, &len);
  if(str[len] == 0){ return str;
  } else {
    if(len >= zBuffer){
      len = zBuffer -2;
      buffer[len-1] = '?';
    }
    memcpy(buffer, str, len);
    buffer[len] = 0;
    return buffer;
  }
}


