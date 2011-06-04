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
#include <Fwc/fw_SimpleC.h>

/**This algorithm is equal java.util.Arrays.binarySearch(int[] a, int fromIndex, int toIndex, int key)
 * but without rangeCheck of input values.
 * The algoritm works only if the data are sorted and the indices are matching.
 */ 
int binarySearch_int(int32_t const* data, int fromIndex, int toIndex, int32_t key)
{ int low = fromIndex;
	int high = toIndex -1;
	while (low <= high)
  { int mid = (low + high) >> 1;
	  int32_t midVal = data[mid];
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


int binarySearch_int64(int64_t const* data, int fromIndex, int toIndex, int64_t key)
{ int low = fromIndex;
	int high = toIndex -1;
	while (low <= high)
  { int mid = (low + high) >> 1;
	  int64_t midVal = data[mid];
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
