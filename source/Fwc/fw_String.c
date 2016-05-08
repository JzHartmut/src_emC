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
//#include "fw_Platform_conventions.h"

//Styleguide: Include all necessities for implementation, the standard headers at least.
#include <Fwc/fw_SimpleC.h>
#include <string.h>   //strncpy

StringJc const null_StringJc = NULL_StringJc;


METHOD_C StringJc z_StringJc(const char* src)
{ StringJc ret;
  int size = strlen_Fwc(src, mLength__StringJc);

  set_OS_PtrValue(ret, src, (size & mLength__StringJc)); 
  return ret;
}



StringJc zI_StringJc(char const* src, int len)
{ StringJc ret;
  set_OS_PtrValue(ret, src, (len & mLength__StringJc)); 
  return ret;
}




const char* getConstChar_StringJc(const StringJc* ythis)
{ //int count;
  //const char* sRet = getCharsAndLength_StringJc(ythis, &count);
  const char* sRet = PTR_OS_PtrValue(*ythis, char const);
  return sRet;
}




/**This method is adequat zI_StringJc, but it dedicated the String as persistent. */
StringJc toStringFromPersist_zI_StringJc(char const* buffer, int nrofChars)
{ StringJc ret;
  set_OS_PtrValue(ret, buffer, (nrofChars & mLength__StringJc)); 
  return ret;
}






char const* getCharsAndLength_StringJc(StringJc const* ythis, int* length)
{ char const* chars = PTR_StringJc(*ythis);
  if(chars == null){
    *length = 0;
  } else {
    int val = VAL_StringJc(*ythis);
    int nChars = val & mLength__StringJc;
    if(nChars == kIsCharSequence_StringJc) {
      //TODO

    } else {
      if(nChars == mLength__StringJc) { nChars = strlen_Fwc(chars, mLength__StringJc); }
      *length = nChars;
    }
  }
  return(chars);  //may be null
}




METHOD_C int length_StringJc(StringJc const ythis)
{ int nChars = VAL_StringJc(ythis) & mLength__StringJc;
  if(nChars == mLength__StringJc) { nChars = strlen_Fwc(PTR_StringJc(ythis), mLength__StringJc); }
  return nChars;
}


METHOD_C bool isZeroTerminated_StringJc(StringJc const ythis)
{ char const* chars = PTR_StringJc(ythis);
  int nChars = VAL_StringJc(ythis) & mLength__StringJc;
  if(nChars == mLength__StringJc) { nChars = strlen_Fwc(chars, mLength__StringJc); }
  return chars[nChars] == 0;
}





METHOD_C int copyToBuffer_StringJc(const StringJc ythis, char* buffer, int maxSizeBuffer)
{ int nChars = VAL_StringJc(ythis) & mLength__StringJc;
  const char* str = PTR_StringJc(ythis);
  if(nChars == mLength__StringJc) { nChars = strlen_Fwc(str, mLength__StringJc); }
  if(nChars >= maxSizeBuffer){ nChars = maxSizeBuffer -1; }
  strncpy(buffer, str, nChars);
  buffer[nChars] = 0;
  return( nChars);
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

