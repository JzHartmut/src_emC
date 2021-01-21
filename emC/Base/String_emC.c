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

StringJc const null_StringJc = NULL_StringJc;


StringJc const empty_StringJc = INIZ_StringJc("", 0);









int parseIntRadix_emC(const char* srcP, int size, int radix, int* parsedChars)
{ int val = 0;
  bool bNegativ;
  int digit;
  char cc;
	const char* src = srcP;
  int maxDigit = (radix <=10) ? '0' + radix -1 : '9'; 
  //int maxHexDigitLower = 'A' + radix - 11; 
  //int maxHexDigitUpper = 'a' + radix - 11; 
  if(*src == '-') { src+=1; size -=1; bNegativ = true; }
  else { bNegativ = false; }
  while(size > 0 && (digit = (cc = *src) - '0') >=0 
       && (  cc <= maxDigit 
          || (radix >10 && (  (cc >= 'A' && (digit = (cc - 'A'+ 10)) <=radix)
                           || (cc >= 'a' && (digit = (cc - 'a'+ 10)) <=radix)
       )  )  )             )
  { val = radix * val + digit;
    src+=1;
    size -=1;
  }
  if(bNegativ){ val = -val; }
  if(parsedChars !=null){
		*parsedChars = (int)(src - srcP);
	}
  return( val);
}


float parseFloat_emC(const char* src, int size, int* parsedCharsP)
{
	int parsedChars = 0;
	float ret;
	int zParsed;
  ret = (float)parseIntRadix_emC(src, size, 10, &zParsed);
	parsedChars += zParsed;  //maybe 0 if .123 is written
  src += zParsed; size -= zParsed;
  if(*src=='.'){
	  float fracPart = (float)parseIntRadix_emC(src+1, size-1, 10, &zParsed);
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


