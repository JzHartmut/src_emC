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
 * This method bodies are placed inside Fwc because simple applications (ExceptionJc.c)
 * call only this method from string, without other dependencies.
 */

//Styleguide: Include the own header first, it should include all necessary depending headers itself. 
#include <Fwc/fw_String.h>

#ifndef __NoCharSeqJcCapabilities__  
  //contains any function declarations here called:
  #include <Jc/StringJc.h>
  //contains ObjectJc definition.
  #include <Fwc/objectBaseC.h>
#endif

//Styleguide: Include all necessities for implementation, the standard headers at least.
#include <string.h>   //strncpy
struct Mtbl_CharSeqJc_t;

extern ClassJc const reflection_StringBuilderJc;


StringJc const null_StringJc = NULL_StringJc;




int strlen_Fwc(char const* text, int maxNrofChars)
{ register char const* text1 = text;
  register char const* text9 = text + maxNrofChars;
  //optimization: test only one pointer register, which is incremented too
  while(text1 < text9 && *text1 != 0){ text1+=1;}
  return (text1 - text);
}


/**Searches a character inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods. strchr fails if the text isn't terminated with 0.
 */
int searchChar_Fwc(char const* text, int maxNrofChars, char cc)
{ register char const* text1 = text;
  register char const* text9 = text + maxNrofChars;
  //optimization: test only one pointer register, which is incremented too
  while(text1 < text9 && *text1 != cc){ 
		text1+=1;
	}
  if(text1 >= text9) return -1;  //not found
	else return (text1 - text);    //maybe 0 if the request char is on the first position.
}




/**Searches a String inside a given string with terminated length.
 * NOTE: The standard-C doesn't contain such simple methods. strstr fails if the text isn't terminated with 0.
 */
int searchString_Fwc(char const* text, int maxNrofChars, char const* ss, int zs)
{ register char const* text1 = text;
  register char const* text2 = text + zs;
  register char const* text3 = text + 1;
  register char const* s2 = ss +1;
  register char const* text9 = text + maxNrofChars;
  register char cc;
  //optimization: test only one pointer register, which is incremented too
  while( text3 <= text9 && text3 < text2){
    cc = *ss;
    while(text1 < text9 && *text1 != cc){ 
		  text1+=1;
	  }
    text3 = text1 +1;
    text2 = text1 + zs;
    s2 = ss +1;
    while(text3 < text2 && *text3 == *s2){
      text3 +=1; 
      s2 +=1;
    }
  }
  if(text3 > text9) return -1;  //not found
	else return (text1 - text);    //maybe 0 if the request char is on the first position.
}




int skipWhitespaces_Fwc(char const* text, int maxNrofChars)
{ register char const* text1 = text;
  register char const* text9 = text + maxNrofChars;
  //optimization: test only one pointer register, which is incremented too
  while(text1 < text9 && *text1 <= 0x20){ 
		text1+=1;
	}
	return (text1 - text);    //maybe 0 if the request char is on the first position.
}


int trimRightWhitespaces_Fwc(char const* text, int maxNrofChars)
{ register char const* text1 = text + maxNrofChars-1;
  //optimization: test only one pointer register, which is incremented too
  while(text1 >= text && *text1 <= 0x20){ 
		text1-=1;
	}
	return (text1 - text +1);    //maybe 0 if there are only whitespaces.
}





int parseIntRadix_Fwc(const char* srcP, int size, int radix, int* parsedChars)
{ int val = 0;
  bool bNegativ;
  int digit;
  char cc;
	const char* src = srcP;
  int maxDigit = (radix <=10) ? '0' + radix -1 : '9'; 
  int maxHexDigitLower = 'A' + radix - 11; 
  int maxHexDigitUpper = 'a' + radix - 11; 
  if(*src == '-') { src+=1; size -=1; bNegativ = true; }
  else { bNegativ = false; }
  while(size > 0 && (digit = (cc = *src) - '0') >=0 
       && (  cc <= maxDigit 
          || (radix >10 && (  cc >= 'A' && (digit = (cc - 'A'+ 10)) <=radix
                           || cc >= 'a' && (digit = (cc - 'a'+ 10)) <=radix)
       )  )                )
  { val = radix * val + digit;
    src+=1;
    size -=1;
  }
  if(bNegativ){ val = -val; }
  if(parsedChars !=null){
		*parsedChars = src - srcP;
	}
  return( val);
}


float parseFloat_Fwc(const char* src, int size, int* parsedCharsP)
{
	int parsedChars = 0;
	float ret;
	int zParsed;
  ret = (float)parseIntRadix_Fwc(src, size, 10, &zParsed);
	parsedChars += zParsed;  //maybe 0 if .123 is written
  src += zParsed; size -= zParsed;
  if(*src=='.'){
	  float fracPart = (float)parseIntRadix_Fwc(src+1, size-1, 10, &zParsed);
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



int _length_PRIV_CharSeqJc(CharSeqJc thiz, ThCxt* _thCxt){
  int val = value_OS_PtrValue(thiz) & mLength__StringJc;
  if(val == kIs_0_terminated_StringJc) { 
    val = strlen_Fwc(PTR_OS_PtrValue(thiz, char const), kMaxNrofChars_StringJc); 
  }
  if(val <= kMaxNrofChars_StringJc) return val;
  #ifdef __NoCharSeqJcCapabilities__
    else { ASSERTJc(val == kIsStringBuilder_CharSeqJc);
      return length_StringBuilderJc(PTR_OS_PtrValue(thiz, StringBuilderJc));
    }
  #else
    else if(val == kIsStringBuilder_CharSeqJc) {
      return length_StringBuilderJc(PTR_OS_PtrValue(thiz, StringBuilderJc));
    } else {
      ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
      struct Mtbl_CharSeqJc_t const* mthiz = getMtbl_CharSeqJc(thiz, _thCxt);
      return mthiz->length(othiz, _thCxt);
    }
  #endif
}




char _charAt_PRIV_CharSeqJc(CharSeqJc thiz, int pos, struct ThreadContextFW_t* _thCxt)
{
  int val = value_OS_PtrValue(thiz) & mLength__StringJc;
  if(val == kIs_0_terminated_StringJc) { 
    val = strlen_Fwc(PTR_OS_PtrValue(thiz, char const), kMaxNrofChars_StringJc); 
  }
  if(val <= kMaxNrofChars_StringJc) {
    if(pos <= val) return PTR_OS_PtrValue(thiz, char const)[pos];
    else {
      STACKTRC_ENTRY("charAt_CharSeqJc");
      THROW_s0(IndexOutOfBoundsException, "", pos);
      STACKTRC_LEAVE;
      return 0; 
    }
  }
  #ifdef __NoCharSeqJcCapabilities__
    else { ASSERTJc(val == kIsStringBuilder_CharSeqJc);
      return charAt_StringBuilderJc(PTR_OS_PtrValue(thiz, StringBuilderJc), pos, _thCxt);
    }
  #else
    else if(val == kIsStringBuilder_CharSeqJc) {
      return charAt_StringBuilderJc(PTR_OS_PtrValue(thiz, StringBuilderJc), pos, _thCxt);
    } else {
      ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
      struct Mtbl_CharSeqJc_t const* mthiz = getMtbl_CharSeqJc(thiz, _thCxt);
      return mthiz->charAt(othiz, pos, _thCxt);
    }
  #endif
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
  set_OS_PtrValue(ret, buffer, (nrofChars & mLength__StringJc)); 
  return ret;
}






char const* getCharsAndLength_StringJc(StringJc const* thiz, int* length)
{ char const* chars = PTR_StringJc(*thiz);
  if(chars == null){
    *length = 0;
  } else {
    int val = VAL_StringJc(*thiz);
    int nChars = val & mLength__StringJc;
    if(nChars == kIs_0_terminated_StringJc) {
      nChars = strlen_Fwc(chars, kMaxNrofChars_StringJc);
    }
    else if(nChars <= kMaxNrofChars_StringJc) {
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
  int nChars = VAL_StringJc(thiz) & mLength__StringJc;
  if(nChars == mLength__StringJc) { nChars = strlen_Fwc(chars, mLength__StringJc); }
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




void ctor_addSize_StringBuilderJc(StringBuilderJc* thiz, int addSize)
{
  initReflection_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz) + addSize, &reflection_StringBuilderJc, 0);
  thiz->size = sizeof(thiz->value) + addSize;
  thiz->_mode = 0;  //no mode bits yet initialize
  thiz->_count = 0;
  memset(thiz->value.direct, 0, thiz->size);  //guaranteed 0-terminated NOTE it should be assumed that the instance is set to 0
}

void ctor_Buffer_StringBuilderJc(StringBuilderJc* thiz, char* buffer, int size)
{
  initReflection_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz), &reflection_StringBuilderJc, 0);
  thiz->size = -size;
  thiz->_mode = 0;  //no mode bits yet initialize
  thiz->_count = 0;
  thiz->value.buffer = buffer;  //guaranteed 0-terminated NOTE it should be assumed that the instance is set to 0
  memset(buffer, 0, size);
}








METHOD_C void clear_StringBuilderJc(StringBuilderJc* thiz)
{ char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int size = (thiz->size < 0 ? -thiz->size : thiz->size);
  memset(buffer, 0, size);
  thiz->_count = 0;
}




char charAt_StringBuilderJc(StringBuilderJc* thiz, int index, ThCxt* _thCxt)
{ char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int count = thiz->_count;
  STACKTRC_TENTRY("charAt_StringBuilderJc");
  if(index < 0 || index >=count) THROW_s0(IndexOutOfBoundsException, "", index);
  STACKTRC_LEAVE; return buffer[index];
}




void setCharAt_StringBuilderJc(StringBuilderJc* thiz, int index, char ch, ThCxt* _thCxt)
{ char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int size = (thiz->size < 0 ? -thiz->size : thiz->size);
  STACKTRC_TENTRY("setCharAt_StringBuilderJc");

  if(index >= size || index <0)
  { //StringJc msg = s0_StringJc("StringBuffer to many chars");
    THROW_s0(IndexOutOfBoundsException, "index fault", index);
  }
  buffer[index] = ch;

  STACKTRC_LEAVE;
}




/**reads the nrofChars and the reference into local variable. Static subroutine for inner organisation:*/
char* getCharsAndSize_StringBuilderJc(StringBuilderJc* thiz, int* size)
{ char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  *size = (thiz->size < 0 ? -thiz->size : thiz->size);
  return( buffer);
}


char* chars_StringBuilderJc(StringBuilderJc* thiz)
{ char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  return( buffer);
}


char* getCharsAndCount_StringBuilderJc(StringBuilderJc* thiz, int* count)
{ char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  //*count = (thiz->count < 0 ? -thiz->count : thiz->count);
  *count = thiz->_count;
  ;
  return( buffer);
}

char* getCharsSizeCount_StringBuilderJc(StringBuilderJc* thiz, int* size, int* count)
{ char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  *size = (thiz->size < 0 ? -thiz->size : thiz->size);
  //*count = (thiz->count < 0 ? -thiz->count : thiz->count);
  *count = thiz->_count;
  return( buffer);
}


void _setCount_StringBuilderJc(StringBuilderJc* thiz, int count)
{ thiz->_count = (int16)((thiz->_count & ~mLength__StringJc) | count);
}




int capacity_StringBuilderJc(StringBuilderJc* thiz)
{
  if(thiz->size < 0) return -thiz->size -1;
  else return thiz->size -1;
}






bool setTruncateMode_StringBuilderJc(StringBuilderJc* thiz, bool bTruncate)
{
  bool bRet = thiz->_mode & _mNoException_StringBuilderJc;
  if(bTruncate) { thiz->_mode |= _mNoException_StringBuilderJc; }
  else          { thiz->_mode &= ~_mNoException_StringBuilderJc; }
  return bRet;
}


bool wasTruncated_StringBuilderJc(StringBuilderJc* thiz)
{
  bool bRet = (thiz->_mode & _mTruncated_StringBuilderJc)!=0;
  thiz->_mode &= ~_mTruncated_StringBuilderJc;
  return bRet;
}





int copyToBuffer_StringBuilderJc(StringBuilderJc* thiz, int start, int end, char* buffer, int zBuffer)
{ int count;
  char const* src;
  STACKTRC_ENTRY("copy_StringBuilderJc");
  src = getCharsAndCount_StringBuilderJc(thiz, &count);
  if(count >= (zBuffer-1)){
    if(thiz->_mode & _mNoException_StringBuilderJc){
      count = zBuffer -1;
    } else THROW_s0(IndexOutOfBoundsException, "string to long", count);
  }
  memcpy(buffer, src, count);
  buffer[count] = 0;
  STACKTRC_LEAVE; return count;
}




int copyToBuffer_CharSeqJc(const StringJc thiz, int start, int end, char* buffer, int sizeBuffer, struct ThreadContextFW_t* _thCxt)
{ //STACKTRC_ENTRY("copyToBuffer_CharSeqJc");
  int nChars = VAL_StringJc(thiz) & mLength__StringJc;
  if(nChars == kIs_0_terminated_StringJc) {
    char const* str = PTR_OS_PtrValue(thiz, char const);
    nChars = strlen_Fwc(str, sizeBuffer);
  }
  if(nChars <= kMaxNrofChars_StringJc) {
    //it is a StringJc
    //faster operation with memcpy instead check of isStringJc for any character.
    char const* str = PTR_OS_PtrValue(thiz, char const);
    if(end < 0){
      end = nChars +end +1;  //end=-1 results in end = nChars
    }
    if(end > start) {
      int nrofBytes = end - start;
      if(nrofBytes > sizeBuffer) {
        nrofBytes = sizeBuffer;
      }
      memcpy(buffer, str + start, nrofBytes);
      //STACKTRC_LEAVE; 
      return nrofBytes;
    } else {
      //STACKTRC_LEAVE; 
      return 0;
    }
  } 
  else if(nChars == kIsStringBuilder_CharSeqJc) {
    StringBuilderJc* sb = PTR_OS_PtrValue(thiz, StringBuilderJc);
    //STACKTRC_LEAVE; 
    return copyToBuffer_StringBuilderJc(sb, start, end, buffer, sizeBuffer);
  } 
  else {
    #ifdef __NoCharSeqJcCapabilities__  
      return 0;  //not used.
    #else 
      //all other values determines a CharSeqJc-interface-instance:
      //It is any ObjectJc which is a CharSeqJc
      Mtbl_CharSeqJc const* mc = getMtbl_CharSeqJc(thiz, _thCxt);
      ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
      int iChars, end1;
      end1 = mc->length(othiz, null); //_thCxt);  
      if(end < 0) { end1 = end1 - (-end) +1; }
      if(end - start > sizeBuffer) { end = start + sizeBuffer; }  
      for(iChars = start; iChars < end1; ++iChars) {
        char cc = mc->charAt(othiz, iChars, null); //_thCxt);
        buffer[iChars] = cc;
      }
      for(iChars = end1 - start; iChars < sizeBuffer; ++iChars) {
        buffer[iChars] = 0;  //fill rest with 0.
      }
      return end1 - start;
    #endif
  }
 
  
  
  
  
  if(nChars & mIsCharSeqJcMtbl_CharSeqJc) {
    STACKTRC_ENTRY("copyToBuffer_StringJc");
    THROW_s0(IllegalArgumentException, "Use copyToBuffer_CharSeqJc", 0);
    STACKTRC_LEAVE;
  }  
  //STACKTRC_LEAVE;
  return( nChars);
}








//central replace routine.
StringBuilderJc* replace_cII_StringBuilderJc(StringBuilderJc* thiz, int start, int end, CharSeqJc add, int from, int to, ThCxt* _thCxt)
{ int countNew;
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int size = (thiz->size < 0 ? -thiz->size : thiz->size); //size of the buffer
  int count = thiz->_count;
  int start1, end1;
  int from1, to1;
  int nInsert;  //nr of chars to insert netto
  int nDelete;
  int zadd;
  char const* padd;
  #ifndef __NoCharSeqJcCapabilities__
    Mtbl_CharSeqJc const* madd = null;
  #endif
  STACKTRC_TENTRY("replace_zI_StringBuilderJc");
  if(thiz->_mode & _mStringBuilt_StringBuilderJc){
    THROW_s0(IllegalStateException, "Buffer was used in StringJc", (int)buffer);
  }
  //
  //determine type of add, zadd, padd, madd:
  { int valAdd = value_OS_PtrValue(add) & mLength__StringJc;
    if(valAdd == kIs_0_terminated_StringJc) { 
      valAdd = strlen_Fwc(PTR_OS_PtrValue(add, char const), kMaxNrofChars_StringJc); 
    }
    if(valAdd <= kMaxNrofChars_StringJc) {
      padd = PTR_OS_PtrValue(add, char const);
      zadd = valAdd;
    }
    else if(valAdd == kIsStringBuilder_CharSeqJc) {
      StringBuilderJc const* buAdd = PTR_OS_PtrValue(add, StringBuilderJc const); 
      zadd = buAdd->_count;
      padd = buAdd->size < 0 ? buAdd->value.buffer : buAdd->value.direct;
    }
    #ifdef __NoCharSeqJcCapabilities__
      else ASSERTJc(false); 
    #else
      else {
        ObjectJc* oadd = PTR_OS_PtrValue(add, ObjectJc);
        madd = getMtbl_CharSeqJc(add, _thCxt);
        zadd = madd->length(oadd, _thCxt) ;
        padd = null;
      }
    #endif
  }
  //
  if(start < 0) { //-1... counts from end, -1 is the end position.
    start1 = count - (-start) +1; 
    if(start1 < 0){ 
      //set start1 to a admissible value if THROW longs only the error.
      start1 = 0; THROW_s0(IndexOutOfBoundsException, "faulty -start", start);
    }  
  } else if(start > count) { 
    start1 = count; THROW_s0(IndexOutOfBoundsException, "faulty start", start); 
  } else {
    start1 = start;
  }
  if(end < 0) { //-1... counts from end, -1 is the end position.
    end1 = count - (-end) +1; 
    if(end1 < start1){ end1 = start1; THROW_s0(IndexOutOfBoundsException, "faulty -end", end);}  
  } else if(end > count) { 
    end1 = count; THROW_s0(IndexOutOfBoundsException, "faulty end", end); 
  } else if(end == 0) {  //it means, delete 0
    end1 = start1; 
  } else if(end < start1) {
    end1 = start1; THROW_s0(IndexOutOfBoundsException, "faulty end before start", end);
  } else {
    end1 = end;
  }
  if(from < 0) { //-1... counts from end, -1 is the end position.
    from1 = zadd - (-from) +1; 
    if(from1 < 0){ from1 = 0; THROW_s0(IndexOutOfBoundsException, "faulty -from", from);}  
  } else if(from > count) { 
    from1 = count; THROW_s0(IndexOutOfBoundsException, "faulty from", from); 
  } else {
    from1 = from;
  }
  if(to < 0) { //-1... counts from end, -1 is the end position.
    to1 = zadd - (-to) +1; 
    if(to1 < from1){ 
      to1 = from1; THROW_s0(IndexOutOfBoundsException, "faulty -to", to);
    }  
  } else if(to > zadd) { 
    to1 = count; THROW_s0(IndexOutOfBoundsException, "faulty to", to); 
  } else if(to < from1) {
    to1 = from1; THROW_s0(IndexOutOfBoundsException, "faulty to before from", to);
  } else {
    to1 = to;
  }

  nDelete = end1 - start1;  //maybe 0
  nInsert = to1 - from1;
  int nMove = nInsert - nDelete;  //maybe negative if more deleted.
  countNew = count + nMove;  //maybe lesser or greater
  if(countNew > size)
  { //in opposite to Java the StringBuffer isnot increased, no dynamically memory management.
    //TODO perhaps test whether it is possible
		if(thiz->_mode & _mNoException_StringBuilderJc){
		  thiz->_mode |= _mTruncated_StringBuilderJc;
			nInsert = size - count;
			countNew = size;
			
		} else {
			THROW_s0(RuntimeException, "StringBuffer too many chars", countNew);
    }
  }
  { int nRest = count - start1 + nDelete ;  //nr of chars from end of replace area to actual end
    if(nRest > 0) memmove(buffer + start1 + nMove, buffer + start1 + nDelete, nRest);  //moves in both directions
  }
  //The area to replace is free.
  if(nInsert >0) {
    if(padd !=null) {
      memcpy(buffer+start1, padd + from1, nInsert);
    }
    else { 
      #ifdef __NoCharSeqJcCapabilities__
  			THROW_s0(RuntimeException, "null add", 0);
      #else
        //a really char seq
        int iDst = 0;
        int iAdd; 
        for(iAdd = from1; iAdd < to1; ++iAdd) {
          char cc = charAt_CharSeqJc(add, iAdd, _thCxt);
          buffer[start1 + iDst] = cc;
          iDst +=1;
        }
      #endif 
    }
  }
  thiz->_count = (int16)((thiz->_count & ~mLength__StringJc) | countNew);
 
  STACKTRC_LEAVE; return( thiz);
}






#ifdef __ObjectJc_simple__
  ClassJc const reflection_StringBuilderJc = {0};
#else
  #include <Jc/ReflectionJc.h>

  


  /**Define the reflection in that source, which used it. */
  const struct Reflection_Fields_StringBuilderJc_t
  { ObjectArrayJc head;
    FieldJc data[4];
  } reflection_Fields_StringBuilderJc =
  { CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_StringBuilderJc)
  , {
      { "_count"
      , 0 //nrofArrayElements
      , REFLECTION_int16
      , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
      , (int16)((int32)(&((StringBuilderJc*)(0x1000))->_count) - (int32)(StringBuilderJc*)0x1000)
      , 0  //offsetToObjectifcBase
      , &reflection_StringBuilderJc
      }
    , { "size"
      , 0 //nrofArrayElements
      , REFLECTION_int16
      , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
      , (int16)((int32)(&((StringBuilderJc*)(0x1000))->size) - (int32)(StringBuilderJc*)0x1000)
      , 0  //offsetToObjectifcBase
      , &reflection_StringBuilderJc
      }
    , { "_mode"
      , 0 //nrofArrayElements
      , REFLECTION_int32
      , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
      , (int16)((int32)(&((StringBuilderJc*)(0x1000))->_mode) - (int32)(StringBuilderJc*)0x1000)
      , 0  //offsetToObjectifcBase
      , &reflection_StringBuilderJc
      }
    , { "value"
      , 0 //nrofArrayElements
      , REFLECTION_void
      , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
      , (int16)((int32)(&((StringBuilderJc*)(0x1000))->value) - (int32)(StringBuilderJc*)0x1000)
      , 0  //offsetToObjectifcBase
      , &reflection_StringBuilderJc
      }
  } };


  const ClassJc reflection_StringBuilderJc =
  { CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_StringBuilderJc, &reflection_ClassJc)
  , "StringBuilderJc"
  , 0
  , sizeof(StringBuilderJc)
  , (FieldJcArray const*)&reflection_Fields_StringBuilderJc  //attributes and associations
  , null  //method
  , null  //superclass
  , null  //interfaces
  , 0 
  #ifndef __NoCharSeqJcCapabilities__  
    , &mtblStringBufferJc.mtbl.head
  #endif
  };



  #define reflection_StringBuilderJc_s reflection_StringBuilderJc
  DEFINE_REFLECTION_REF(StringBuilderJc);


#endif

