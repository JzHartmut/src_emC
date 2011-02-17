/********************************************************************************************************** 
 * This method bodies are placed inside Fwc because simple applications (ExceptionJc.c)
 * call only this method from string, without other dependencies.
 */

//Styleguide: Include the own header first, it should include all necessary depending headers itself. 
#include <Fwc/fw_String.h>

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
    int nChars = VAL_StringJc(*ythis) & mLength__StringJc;
    if(nChars == mLength__StringJc) { nChars = strlen_Fwc(chars, mLength__StringJc); }
    *length = nChars;
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

