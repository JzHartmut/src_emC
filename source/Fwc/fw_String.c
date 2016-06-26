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
#include <Jc/ObjectJc.h>
#include <Jc/StringJc.h>
#include <Jc/ReflectionJc.h>
#include <fw_Assert.h>
//#include "fw_Platform_conventions.h"

//Styleguide: Include all necessities for implementation, the standard headers at least.
#include <Fwc/fw_SimpleC.h>
#include <string.h>   //strncpy

StringJc const null_StringJc = NULL_StringJc;

CharSeqJc const null_CharSeqJc = NULL_CharSeqJc;


METHOD_C StringJc z_StringJc(const char* src)
{ StringJc ret;
  int size = strlen_Fwc(src, kMaxLength_StringJc);

  set_OS_PtrValue(ret.s, src, (size)); 
  return ret;
}



StringJc zI_StringJc(char const* src, int len)
{ StringJc ret;
  set_OS_PtrValue(ret.s, src, (len & mLength__StringJc)); 
  return ret;
}


CharSeqJc fromObjectJc_CharSeqJc(struct ObjectJc_t* othiz)
{ CharSeqJc ret;
  
  int val = getPosInMtbl_ObjectJc(othiz, sign_Mtbl_CharSeqJc);
  if(val >=0){
    val |= mIsCharSeqJcMtbl_CharSeqJc;
  } else {
    //TODO this is not an instance of CharSeqJc. THROW!
    val = kIsCharSeqJc_CharSeqJc;
  }
  set_OS_PtrValue(ret, othiz, val); 
  return ret;
}


CharSeqJc fromStringBuilderJc_CharSeqJc(struct StringBuilderJc_t const* othiz)
{ CharSeqJc ret;
  set_OS_PtrValue(ret, othiz, kIsStringBuilder_CharSeqJc); 
  return ret;
}


const char* getConstChar_StringJc(const StringJc* ythis)
{ //int count;
  //const char* sRet = getCharsAndLength_StringJc(ythis, &count);
  const char* sRet = PTR_StringJc(*ythis);
  return sRet;
}




/**This method is adequat zI_StringJc, but it dedicated the String as persistent. */
StringJc toStringFromPersist_zI_StringJc(char const* buffer, int nrofChars)
{ StringJc ret;
  set_OS_PtrValue(ret.s, buffer, (nrofChars & mLength__StringJc)); 
  return ret;
}






char const* getCharsAndLength_StringJc(StringJc const* ythis, int* length)
{ char const* chars = PTR_StringJc(*ythis);
  if(chars == null){
    *length = 0;
  } else {
    int val = VAL_StringJc(*ythis);
    int nChars = val & mLength__StringJc;
    if(nChars <= kMaxLength_StringJc) {
      if(nChars == kMaxLength_StringJc) { nChars = strlen_Fwc(chars, kMaxLength_StringJc); }
      *length = nChars;
    } else {
      //STACKTRC_ENTRY("getCharsAndLength_StringJc");
      //THROW
      *length = 0;
      return null;
    }
  }
  return(chars);  //may be null
}




METHOD_C int length_StringJc(StringJc const ythis)
{ int nChars = VAL_StringJc(ythis) & mLength__StringJc;
  if(nChars == kMaxLength_StringJc) { nChars = strlen_Fwc(PTR_StringJc(ythis), kMaxLength_StringJc); }
  return nChars;
}


METHOD_C bool isZeroTerminated_StringJc(StringJc const ythis)
{ char const* chars = PTR_StringJc(ythis);
  int nChars = VAL_StringJc(ythis) & mLength__StringJc;
  if(nChars == mLength__StringJc) { nChars = strlen_Fwc(chars, mLength__StringJc); }
  return chars[nChars] == 0;
}



INLINE_Fwc Mtbl_CharSeqJc const* getMtbl_CharSeqJc(CharSeqJc thiz)
{
  int nChars = VAL_CharSeqJc(thiz) & mLength__StringJc;
  ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
  MtblHeadJc const* head;
  Mtbl_CharSeqJc const* mc;
  if(nChars == kIsCharSeqJc_CharSeqJc) {
    head = getMtbl_ObjectJc(othiz, sign_Mtbl_CharSeqJc);
  } else {
    int offsetMtbl =  nChars & ~mIsCharSeqJcMtbl_CharSeqJc;
    head = othiz->reflectionClass->mtbl;
    MemUnit* head2 = addOffset_MemUnit(head, offsetMtbl);  //add offset in mtbl
    head = (MtblHeadJc const*) head2;
  }
  ASSERT_s0_Fwc(head->sign == sign_Mtbl_CharSeqJc, "faulty Mtbl of CharSeqJc", (int)ythis);
  mc = (Mtbl_CharSeqJc const*) head;
  return mc;

}


int length_CharSeqJc_(CharSeqJc thiz)
{
  int val = VAL_CharSeqJc(thiz) & mLength__StringJc;
  if(val == kIsStringBuilder_CharSeqJc) {
    StringBuilderJc* b = PTR_OS_PtrValue(thiz, StringBuilderJc);
    return b->_count; 
  }
  else if(val == kMaxLength_StringJc) {
    return strlen_Fwc(PTR_OS_PtrValue(thiz, char const), kMaxLength_StringJc);
  }
  else if(val < kMaxLength_StringJc) {
    return val;
  } else {
    const Mtbl_CharSeqJc* mtbl = getMtbl_CharSeqJc(thiz);
    return mtbl->length(PTR_OS_PtrValue(thiz, ObjectJc), null);
  }
}




METHOD_C int copyToBuffer_CharSeqJc(const CharSeqJc thiz, int start, int end, char* buffer, int maxSizeBuffer)
{ STACKTRC_ENTRY("copyToBuffer_CharSeqJc");
  int nChars = VAL_CharSeqJc(thiz) & mLength__StringJc;
  if(nChars <= kMaxLength_StringJc) {
    //it is a StringJc
    //faster operation with memcpy instead check of isStringJc for any character.
    char const* str = PTR_OS_PtrValue(thiz, char const);
    if(nChars == kMaxLength_StringJc){
      nChars = strlen_Fwc(str, maxSizeBuffer);
    }
    if(end < 0){
      end = nChars -end +1;  //end=-1 results in end = nChars
    }
    if(end > start) {
      int nrofBytes = end - start;
      if(nrofBytes > maxSizeBuffer) {
        nrofBytes = maxSizeBuffer;
      }
      memcpy(buffer, str + start, nrofBytes);
      return nrofBytes;
    } else {
      return 0;
    }
  } 
  else if(nChars == kIsStringBuilder_CharSeqJc) {
    StringBuilderJc* sb = PTR_OS_PtrValue(thiz, StringBuilderJc);
    return copyToBuffer_StringBuilderJc(sb, start, end, buffer, maxSizeBuffer);
  } 
  else if(nChars & mIsCharSeqJcMtbl_CharSeqJc) {
    //CharSeqJc with given index to method table in the ObjectJc reference.
    Mtbl_CharSeqJc const* mc = getMtbl_CharSeqJc(thiz);
    ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
    int iChars;
    nChars = mc->length(othiz, _thCxt);  
    if(nChars >= maxSizeBuffer){ nChars = maxSizeBuffer ; }
    for(iChars = 0; iChars < nChars; ++iChars) {
      char cc = mc->charAt(othiz, iChars, _thCxt);
      buffer[iChars] = cc;
    }
  }  
  STACKTRC_LEAVE;
  return( nChars);
}



StringJc toString_CharSeqJc(CharSeqJc thiz)
{
  STACKTRC_ENTRY("toString_CharSeqJc");
  int val = value_OS_PtrValue(thiz);
  if(val == kIsStringBuilder_CharSeqJc) {
    StringBuilderJc* sb = PTR_OS_PtrValue(thiz, StringBuilderJc);
    char const* buffer = chars_StringBuilderJc(sb);
    int nChars = length_StringBuilderJc(sb);
    StringJc ret = CONST_StringJc(buffer, nChars);
    STACKTRC_LEAVE; return ret;
  }
  else if(val & mIsCharSeqJcMtbl_CharSeqJc) {
    Mtbl_CharSeqJc const* mc = getMtbl_CharSeqJc(thiz);
    ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
    int iChars;
    int nChars = mc->length(othiz, _thCxt);
    MemC mBuffer = getUserBuffer_ThreadContextFw(nChars+1, _thCxt);
    int sizeBufferThreadContext = size_MemC(mBuffer);
    if(nChars >= sizeBufferThreadContext){ 
      nChars = sizeBufferThreadContext-1;   //limit it.
    }
    char* buffer = PTR_MemC(mBuffer, char);
    for(iChars = 0; iChars < nChars; ++iChars) {
      char cc = mc->charAt(othiz, iChars, _thCxt);
      buffer[iChars] = cc;
    }
    buffer[iChars] = 0;
    StringJc ret = CONST_StringJc(buffer, nChars);
    STACKTRC_LEAVE; return ret;
  } else {
    //it is a String
    STACKTRC_LEAVE; return *(StringJc*)&thiz;
  } 
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

