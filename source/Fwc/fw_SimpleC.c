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
 **copyright***************************************************************************************
 *
 * @content Basicly routines useable in C.
 *
 * @author Hartmut Schorrig
 * @version 0.81ad
 * list of changes:
 * 2007-10-01: JcHartmut creation
 *
 ****************************************************************************/
#include <Fwc/fw_simpleC.h>
#include <string.h>
#include <Fwc/fw_String.h>
//#include "os_wrapper.h"
//#include "osSpecifica.h"
//#include "fw_Exception.h"

/**This algorithm is equal java.util.Arrays.binarySearch(int[] a, int fromIndex, int toIndex, int key)
 * but without rangeCheck of input values.
 * The algoritm works only if the data are sorted and the indices are matching.
 */ 
int binarySearch_int(int32 const* data, int fromIndex, int toIndex, int32 key)
{ int low = fromIndex;
	int high = toIndex -1;
	while (low <= high)
  { int mid = (low + high) >> 1;
	  int32 midVal = data[mid];
	  if (midVal < key)
		{ low = mid + 1;
	  }
    else if (midVal > key)
		{ high = mid - 1;
	  }
    else
		{ return mid; // key found
    }
	}
	return -(low + 1);  // key not found.
}


int binarySearch_int64(int64 const* data, int fromIndex, int toIndex, int64 key)
{ int low = fromIndex;
	int high = toIndex -1;
	while (low <= high)
  { int mid = (low + high) >> 1;
	  int64 midVal = data[mid];
	  if (midVal < key)
		{ low = mid + 1;
	  }
    else if (midVal > key)
		{ high = mid - 1;
	  }
    else
		{ return mid; // key found
    }
	}
	return -(low + 1);  // key not found.
}


int strlen_Fwc(char const* text, int maxNrofChars)
{ register char const* text1 = text;
  register char const* text9 = text + maxNrofChars;
  //optimization: test only one pointer register, which is incremented too
  while(text1 < text9 && *text1 != 0){ text1+=1;}
  return (text1 - text);
}



/********************************************************************************************************** 
 * This method bodies are placed inside MemC.c because simple applications (ExceptionJc.c)
 * call only this method from string, without other dependencies.
 */

StringJc const null_StringJc = NULL_StringJc;


METHOD_C StringJc z_StringJc(const char* src)
{ StringJc ret;
  int size = strlen(src);

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
    if(nChars == mLength__StringJc) { nChars = strlen(chars); }
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
  if(nChars == mLength__StringJc) { nChars = strlen(str); }
  if(nChars >= maxSizeBuffer){ nChars = maxSizeBuffer -1; }
  strncpy(buffer, str, nChars);
  buffer[nChars] = 0;
  return( nChars);
}


int parseInt_Fwc(const char* src, int size, int radix, int* retSize)
{ int val = 0;
  bool bNegativ;
  int digit;
  char cc;
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
  *retSize = size;
  return( val);
}


