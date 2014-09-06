/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#include "J1c/StringFunctionsJc.h"
#include <string.h>  //because using memset()
#include <Jc/ReflectionJc.h>   //Reflection concept 
#include <Fwc/fw_Exception.h>  //basic stacktrace concept
#include "J1c/SpecialCharStringsJc.h"  //reference-association: SpecialCharStringsJc_s
#include "Jc/ObjectJc.h"  //reference-association: IntegerJc
#include "Jc/StringJc.h"  //embedded type in class data


/* J2C: Forward declaration of struct ***********************************************/
struct StringBuilderJc_t;

/**This class contains static String functions without any other dependency.
In C the functions are contained in the Fwc/fw_String.c.
@author Hartmut Schorrig

*/


const char sign_Mtbl_StringFunctionsJc[] = "StringFunctionsJc"; //to mark method tables of all implementations

typedef struct MtblDef_StringFunctionsJc_t { Mtbl_StringFunctionsJc mtbl; MtblHeadJc end; } MtblDef_StringFunctionsJc;
 extern MtblDef_StringFunctionsJc const mtblStringFunctionsJc;
const char cEndOfText_StringFunctionsJc = (char)(0x3);
StringJc indentString_StringFunctionsJc = CONST_z_StringJc("\n                                                                                                    ");

/*Constructor *//**J2C: autogenerated as default constructor. */
struct StringFunctionsJc_t* ctorO_StringFunctionsJc(ObjectJc* othis, ThCxt* _thCxt)
{ StringFunctionsJc_s* thiz = (StringFunctionsJc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("ctorO_StringFunctionsJc");
  checkConsistence_ObjectJc(othis, sizeof(StringFunctionsJc_s), null, _thCxt);  
  setReflection_ObjectJc(othis, &reflection_StringFunctionsJc_s, sizeof(StringFunctionsJc_s));  
  //j2c: Initialize all class variables:
  {
  }/*J2C:No body for constructor*/

  STACKTRC_LEAVE;
  return thiz;
}



/**Returns the position of the end of an identifier.*/
int32 posAfterIdentifier_CsiiSS_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* src, int32 start, int32 endMax, StringJc additionalStartChars, StringJc additionalChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("posAfterIdentifier_CsiiSS_StringFunctionsJc");
  
  { 
    int32 pos; 
    char cc; 
    
    
    pos = start;
    cc = charAt_CharSequenceJc(src, pos, _thCxt);
    if(cc == '_' || (cc >= 'A' && cc <= 'Z') || (cc >= 'a' && cc <= 'z') || (additionalStartChars.ptr__!= null && indexOf_C_StringJc(additionalStartChars, cc) >= 0)) 
    { 
      
      pos += 1;
      
      while(pos < endMax && ((cc = /*? assignment*/charAt_CharSequenceJc(src, pos, _thCxt)) == '_' || (cc >= '0' && cc <= '9') || (cc >= 'A' && cc <= 'Z') || (cc >= 'a' && cc <= 'z') || (additionalChars.ptr__!= null && indexOf_C_StringJc(additionalChars, cc) >= 0)))
        { 
          
          pos += 1;
        }
    }
    { STACKTRC_LEAVE;
      return pos;
    }
  }
  STACKTRC_LEAVE;
}


/**Returns the position of the end of an identifier.*/
int32 posAfterIdentifier_Csii_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* src, int32 start, int32 endMax, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("posAfterIdentifier_Csii_StringFunctionsJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return posAfterIdentifier_CsiiSS_StringFunctionsJc(/*static*/src, start, endMax, null_StringJc, null_StringJc, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}


/**Parses a given String and convert it to the integer number.*/
int32 parseIntRadix_SiiiiYS_StringFunctionsJc(/*static*/ StringJc srcP, int32 pos, int32 sizeP, int32 radix, int32_Y* parsedChars, StringJc spaceChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseIntRadix_SiiiiYS_StringFunctionsJc");
  
  { 
    int32 val = 0; 
    bool bNegativ = 0; 
    int32 digit = 0; 
    char cc = 0; 
    int32 ixSrc; 
    int32 size; 
    int32 maxDigit; 
    
    
    val = 0;
    /*no initvalue*/
    /*no initvalue*/
    /*no initvalue*/
    ixSrc = pos;
    size = length_StringJc(srcP) - pos;
    if(size > sizeP) 
    { 
      
      size = sizeP;
    }
    maxDigit = ((/*J2C:cast% from char*/int32)((radix <= 10) ? '0' + radix - 1 : '9'));
    if(size > 0 && charAt_StringJc(srcP, ixSrc) == '-') 
    { 
      
      ixSrc += 1;
      size -= 1;
      bNegativ = true;
    }
    else 
    { 
      
      bNegativ = false;
    }
    
    while(--size >= 0)
      { 
        
        cc = charAt_StringJc(srcP, ixSrc);
        if(spaceChars.ptr__!= null && indexOf_C_StringJc(spaceChars, cc) >= 0) 
        { 
          
          ixSrc += 1;
        }
        else if((digit = /*? assignment*/cc - '0') >= 0 && (cc <= maxDigit || (radix > 10 && (cc >= 'A' && (digit = /*? assignment*/(cc - 'A' + 10)) <= radix || cc >= 'a' && (digit = /*? assignment*/(cc - 'a' + 10)) <= radix)))) 
        { 
          
          val = radix * val + digit;
          ixSrc += 1;
        }
        else 
        { 
          
          break;
        }
      }
    if(bNegativ) 
    { 
      
      val = -val;
    }
    if(parsedChars != null) 
    { 
      
      parsedChars->data[0] = ixSrc - pos;
    }
    { STACKTRC_LEAVE;
      return (val);
    }
  }
  STACKTRC_LEAVE;
}


/**Adequate method for long values, see {@link #parseIntRadix(String, int, int, int, int[], String)}.*/
int64 parseLong_StringFunctionsJc(/*static*/ StringJc srcP, int32 pos, int32 sizeP, int32 radix, int32_Y* parsedChars, StringJc spaceChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseLong_StringFunctionsJc");
  
  { 
    int64 val = 0; 
    bool bNegativ = 0; 
    int32 digit = 0; 
    char cc = 0; 
    int32 ixSrc; 
    int32 size; 
    int32 maxDigit; 
    
    
    val = 0;
    /*no initvalue*/
    /*no initvalue*/
    /*no initvalue*/
    ixSrc = pos;
    size = length_StringJc(srcP) - pos;
    if(size > sizeP) 
    { 
      
      size = sizeP;
    }
    maxDigit = ((/*J2C:cast% from char*/int32)((radix <= 10) ? '0' + radix - 1 : '9'));
    if(charAt_StringJc(srcP, ixSrc) == '-') 
    { 
      
      ixSrc += 1;
      size -= 1;
      bNegativ = true;
    }
    else 
    { 
      
      bNegativ = false;
    }
    
    while(--size >= 0)
      { 
        
        cc = charAt_StringJc(srcP, ixSrc);
        if(spaceChars.ptr__!= null && indexOf_C_StringJc(spaceChars, cc) >= 0) 
        { 
          
          ixSrc += 1;
        }
        else if((digit = /*? assignment*/cc - '0') >= 0 && (cc <= maxDigit || (radix > 10 && (cc >= 'A' && (digit = /*? assignment*/(cc - 'A' + 10)) <= radix || cc >= 'a' && (digit = /*? assignment*/(cc - 'a' + 10)) <= radix)))) 
        { 
          
          val = radix * val + digit;
          ixSrc += 1;
        }
        else 
        { 
          
          break;
        }
      }
    if(bNegativ) 
    { 
      
      val = -val;
    }
    if(parsedChars != null) 
    { 
      
      parsedChars->data[0] = ixSrc - pos;
    }
    { STACKTRC_LEAVE;
      return (val);
    }
  }
  STACKTRC_LEAVE;
}


/**Parses a given String backward and convert it to the integer number.*/
int32 parseIntRadixBack_StringFunctionsJc(/*static*/ StringJc srcP, int32 pos, int32 sizeP, int32 radix, int32_Y* parsedChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseIntRadixBack_StringFunctionsJc");
  
  { 
    int32 val = 0; 
    bool bNegativ = 0; 
    int32 digit = 0; 
    char cc = 0; 
    int32 ixSrc; 
    int32 size; 
    int32 maxDigit; 
    int32 maxHexDigitLower = 'A'/*J2C: no cast found from char=char: ClassData@2576a288*/; 
    int32 maxHexDigitUpper = 'a'/*J2C: no cast found from char=char: ClassData@2576a288*/; 
    int32 multPosition = 1; 
    
    
    val = 0;
    /*no initvalue*/
    /*no initvalue*/
    /*no initvalue*/
    ixSrc = pos;
    size = length_StringJc(srcP) - pos;
    if(size > sizeP) 
    { 
      
      size = sizeP;
    }
    maxDigit = ((/*J2C:cast% from char*/int32)((radix <= 10) ? '0' + radix - 1 : '9'));
    maxHexDigitLower = ((/*J2C:cast% from char*/int32)('A' + radix - 11));
    maxHexDigitUpper = ((/*J2C:cast% from char*/int32)('a' + radix - 11));
    multPosition = 1;
    
    while(size > 0 && ixSrc >= 0 && (digit = /*? assignment*/(cc = /*? assignment*/charAt_StringJc(srcP, ixSrc)) - '0') >= 0 && (cc <= maxDigit || (radix > 10 && (cc >= 'A' && (digit = /*? assignment*/(cc - 'A' + 10)) <= radix || cc >= 'a' && (digit = /*? assignment*/(cc - 'a' + 10)) <= radix))))
      { 
        
        val += multPosition * digit;
        multPosition *= radix;
        ixSrc -= 1;
        size -= 1;
      }
    if(size > 0 && ixSrc >= 0 && charAt_StringJc(srcP, ixSrc) == '-') 
    { 
      
      ixSrc -= 1;
      size -= 1;
      val = -val;
    }
    if(parsedChars != null) 
    { 
      
      parsedChars->data[0] = pos - ixSrc;
    }
    { STACKTRC_LEAVE;
      return (val);
    }
  }
  STACKTRC_LEAVE;
}

float parseFloat_SiiiY_StringFunctionsJc(/*static*/ StringJc src, int32 pos, int32 sizeP, int32_Y* parsedCharsP, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseFloat_SiiiY_StringFunctionsJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return parseFloat_SiiciY_StringFunctionsJc(/*static*/src, pos, sizeP, '.', parsedCharsP, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}


/**Parses a given String and convert it to the float number.*/
float parseFloat_SiiciY_StringFunctionsJc(/*static*/ StringJc src, int32 pos, int32 sizeP, char decimalpoint, int32_Y* parsedCharsP, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseFloat_SiiciY_StringFunctionsJc");
  
  { 
    int32 parsedChars = 0; 
    float ret = 0; 
    int32 restlen; 
    int32_Y* zParsed; 
    int32 ixsrc; 
    
    ObjectJc *newObj1_1=null; /*J2C: temporary Objects for new operations
    */
    parsedChars = 0;
    /*no initvalue*/
    restlen = length_StringJc(src) - pos;
    if(restlen > sizeP) 
    { 
      
      restlen = sizeP;
    }
    
    zParsed = (int32_Y*)ctorO_ObjectArrayJc((newObj1_1 = alloc_ObjectJc( sizeof(ObjectArrayJc) + (1) * sizeof(int32), mIsLargeSize_objectIdentSize_ObjectJc, _thCxt)), 1, sizeof(int32),REFLECTION_int32, 0);
    ret = parseIntRadix_SiiiiY_StringFunctionsJc(/*static*/src, pos, restlen, 10, zParsed);
    parsedChars += zParsed->data[0];/*maybe 0 if .123 is written*/
    
    ixsrc = pos + zParsed->data[0];
    restlen -= zParsed->data[0];
    if(ixsrc < (restlen + pos) && charAt_StringJc(src, ixsrc) == decimalpoint) 
    { 
      float fracPart; 
      
      
      fracPart = parseIntRadix_SiiiiY_StringFunctionsJc(/*static*/src, ixsrc + 1, restlen - 1, 10, zParsed);
      if(zParsed->data[0] > 0) 
      { 
        
        switch(zParsed->data[0]){
          case 1: fracPart *= 0.1F;break;
          case 2: fracPart *= 0.01F;break;
          case 3: fracPart *= 0.001F;break;
          case 4: fracPart *= 1.0E-4F;break;
          case 5: fracPart *= 1.0E-5F;break;
          case 6: fracPart *= 1.0E-6F;break;
          case 7: fracPart *= 1.0E-7F;break;
          case 8: fracPart *= 1.0E-8F;break;
          case 9: fracPart *= 1.0E-9F;break;
          case 10: fracPart *= 1.0E-10F;break;
        }/*switch*/;
        ret += fracPart;
      }
      parsedChars += zParsed->data[0] + 1;/*maybe 0 if .123 is written*/
      
      restlen -= zParsed->data[0] - 1;
    }/*TODO exponent*/
    
    if(parsedCharsP != null) 
    { 
      
      parsedCharsP->data[0] = parsedChars;
    }
    { STACKTRC_LEAVE;
      activateGC_ObjectJc(newObj1_1, null, _thCxt);
      return ret;
    }
  }
  STACKTRC_LEAVE;
}


/**Compares two CharSequence (Strings, StringBuilder-content etc.*/
int32 compare_CsiCsii_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* s1, int32 from1, struct CharSequenceJc_t* s2, int32 from2, int32 nrofChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("compare_CsiCsii_StringFunctionsJc");
  
  { 
    int32 i1; 
    int32 i2; 
    int32 z; 
    int32 returnEq = 0; 
    
    
    i1 = from1 - 1;
    i2 = from2 - 1;
    z = nrofChars + from1;
    returnEq = 0;
    if(z > length_CharSequenceJc(s1, _thCxt)) 
    { 
      int32 nrofChars1; 
      int32 z2; 
      
      
      z = length_CharSequenceJc(s1, _thCxt);
      nrofChars1 = z - from1;
      z2 = from2 + nrofChars1;
      if(z2 == length_CharSequenceJc(s2, _thCxt)) 
      { 
        
        returnEq = 0;
      }/*both have the same length after shorten.*/
      
      else if(z2 > length_CharSequenceJc(s2, _thCxt)) 
      { 
        int32 nrofChars2; 
        
        
        nrofChars2 = length_CharSequenceJc(s2, _thCxt) - from2;
        z = from1 + nrofChars2;/*reduce length because s2*/
        
        returnEq = 1;/*returns 1 if equal because s2 is shorter*/
        
      }
      else 
      { 
        
        returnEq = -1;
      }/*returns -1 if equal because s1 is shorter*/
      
    }
    else if((from2 + nrofChars) > length_CharSequenceJc(s2, _thCxt)) 
    { /*:s2 is shorter than the requested or adjusted length:*/
      
      
      z = (length_CharSequenceJc(s2, _thCxt) - from2) + from1;
      returnEq = 1;/*returns 1 if equal because s2 is shorter*/
      
    }
    
    while(++i1 < z)
      { 
        char c1; 
        char c2; 
        
        
        c1 = charAt_CharSequenceJc(s1, i1, _thCxt);
        c2 = charAt_CharSequenceJc(s2, ++i2, _thCxt);
        if(c1 != c2) 
        { 
          
          if(c1 < c2) 
          { 
            
            { STACKTRC_LEAVE;
            return -1;
          }
          }
          else if(c1 > c2) 
          { 
            
            { STACKTRC_LEAVE;
            return 1;
          }
          }
        }
      }/*all chars till z are equal.*/
      
    { STACKTRC_LEAVE;
      return returnEq;
    }
  }
  STACKTRC_LEAVE;
}


/**Compares two Strings or StringBuilder-content or any other CharSequence.*/
int32 compare_CsCs_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* s1, struct CharSequenceJc_t* s2, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("compare_CsCs_StringFunctionsJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return compare_CsiCsii_StringFunctionsJc(/*static*/s1, 0, s2, 0, MAX_VALUE_IntegerJc, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}

bool equals_CsiiCs_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* s1, int32 from, int32 to, struct CharSequenceJc_t* s2, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("equals_CsiiCs_StringFunctionsJc");
  
  { 
    int32 zz; 
    
    
    zz = to - from;
    if(zz != length_CharSequenceJc(s2, _thCxt)) { STACKTRC_LEAVE;
      return false;
    }
    else 
    { 
      
      { int32 ii; 
        for(ii = 0; ii < zz; ++ii)
          { 
            
            if(charAt_CharSequenceJc(s1, from + ii, _thCxt) != charAt_CharSequenceJc(s2, ii, _thCxt)) { STACKTRC_LEAVE;
            return false;
          }
          }
      }
      { STACKTRC_LEAVE;
        return true;
      }
    }
  }
  STACKTRC_LEAVE;
}


/**Compares two Strings or StringBuilder-content or any other CharSequence.*/
bool equals_CsCs_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* s1, struct CharSequenceJc_t* s2, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("equals_CsCs_StringFunctionsJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return equals_CsiiCs_StringFunctionsJc(/*static*/s1, 0, length_CharSequenceJc(s1, _thCxt), s2, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}


/**Checks whether the given CharSequence starts with a CharSequence.*/
bool startsWith_CsCs_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, struct CharSequenceJc_t* start, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("startsWith_CsCs_StringFunctionsJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return compare_CsiCsii_StringFunctionsJc(/*static*/sq, 0, start, 0, length_CharSequenceJc(start, _thCxt), _thCxt) == 0;
    }
  }
  STACKTRC_LEAVE;
}


/**Checks whether the given CharSequence starts with a CharSequence.*/
bool startsWith_CsiiCs_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 from, int32 to, struct CharSequenceJc_t* start, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("startsWith_CsiiCs_StringFunctionsJc");
  
  { 
    int32 zstart; 
    
    
    zstart = length_CharSequenceJc(start, _thCxt);
    if((to - from) < zstart) { STACKTRC_LEAVE;
      return false;
    }
    { STACKTRC_LEAVE;
      return compare_CsiCsii_StringFunctionsJc(/*static*/sq, from, start, 0, zstart, _thCxt) == 0;
    }
  }
  STACKTRC_LEAVE;
}


/**Checks whether the given CharSequence ends with a CharSequence.*/
bool endsWith_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, struct CharSequenceJc_t* end, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("endsWith_StringFunctionsJc");
  
  { 
    int32 z; 
    
    
    z = length_CharSequenceJc(end, _thCxt);
    if(z > length_CharSequenceJc(sq, _thCxt)) { STACKTRC_LEAVE;
      return false;
    }
    else { STACKTRC_LEAVE;
      return compare_CsiCsii_StringFunctionsJc(/*static*/sq, length_CharSequenceJc(sq, _thCxt) - z, end, 0, z, _thCxt) == 0;
    }
  }
  STACKTRC_LEAVE;
}


/**Returns false if at least one char was found in text which is not a whitespace.*/
bool isEmptyOrOnlyWhitespaces_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* text, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("isEmptyOrOnlyWhitespaces_StringFunctionsJc");
  
  { 
    char cc = 0; 
    int32 zz; 
    int32 ii = -1; 
    
    
    /*no initvalue*/
    zz = length_CharSequenceJc(text, _thCxt);
    ii = -1;
    
    while(++ii < zz)
      { 
        
        cc = charAt_CharSequenceJc(text, ii, _thCxt);
        if(indexOf_C_StringJc(zI_StringJc(" \t\n\r",4), cc) < 0) 
        { 
          
          { STACKTRC_LEAVE;
          return false;
        }
        }/*other character than whitespace*/
        
      }
    { STACKTRC_LEAVE;
      return true;
    }
  }
  STACKTRC_LEAVE;
}


/**Searches the first occurrence of the given CharSequence in a CharSequence.*/
int32 indexOf_Csiic_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 fromIndex, int32 to, char ch, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("indexOf_Csiic_StringFunctionsJc");
  
  { 
    int32 zsq; 
    int32 max; 
    int32 ii; 
    
    
    zsq = length_CharSequenceJc(sq, _thCxt);
    max = to > zsq ? zsq : to;
    ii = fromIndex - 1;
    if(fromIndex < 0) 
    { 
      
      ii = -1;
    }
    else if(fromIndex >= max) 
    { 
      
      { STACKTRC_LEAVE;
        return -1;
      }
    }
    
    while(++ii < max)
      { 
        
        if(charAt_CharSequenceJc(sq, ii, _thCxt) == ch) 
        { 
          
          { STACKTRC_LEAVE;
          return ii;
        }
        }
      }
    { STACKTRC_LEAVE;
      return -1;
    }/*not found;*/
    
  }
  STACKTRC_LEAVE;
}


/**Searches the first occurrence of the given Character in a CharSequence.*/
int32 indexOf_Csci_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, char ch, int32 fromIndex, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("indexOf_Csci_StringFunctionsJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return indexOf_Csiic_StringFunctionsJc(/*static*/sq, fromIndex, MAX_VALUE_IntegerJc, ch, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}


/**Searches any char inside sChars in the given Charsequence*/
int32 indexOfAnyChar_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 begin, int32 end, StringJc sChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("indexOfAnyChar_StringFunctionsJc");
  
  { 
    int32 pos; 
    
    
    pos = begin - 1;
    
    while(++pos < end && indexOf_C_StringJc(sChars, charAt_CharSequenceJc(sq, pos, _thCxt)) < 0)
      { }/*while any of char in sChars not found:*/
      
    if(pos < end || (pos == end && indexOf_C_StringJc(sChars, cEndOfText_StringFunctionsJc) >= 0)) 
    { 
      
      { STACKTRC_LEAVE;
        return pos;
      }
    }
    else { STACKTRC_LEAVE;
      return -1;
    }
  }
  STACKTRC_LEAVE;
}


/**Searches the last occurrence of the given char in a CharSequence.*/
int32 lastIndexOf_Csiic_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 from, int32 to, char ch, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("lastIndexOf_Csiic_StringFunctionsJc");
  
  { 
    int32 zsq; 
    int32 ii; 
    
    
    zsq = length_CharSequenceJc(sq, _thCxt);
    ii = to > zsq ? zsq : to;
    
    while(--ii >= from)
      { 
        
        if(charAt_CharSequenceJc(sq, ii, _thCxt) == ch) 
        { 
          
          { STACKTRC_LEAVE;
          return ii;
        }
        }
      }
    { STACKTRC_LEAVE;
      return -1;
    }/*not found;*/
    
  }
  STACKTRC_LEAVE;
}


/**Searches the last occurrence of the given char in a CharSequence.*/
int32 lastIndexOf_Csc_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, char ch, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("lastIndexOf_Csc_StringFunctionsJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return lastIndexOf_Csiic_StringFunctionsJc(/*static*/sq, 0, MAX_VALUE_IntegerJc, ch, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}


/**Searches the last occurrence of the given char in a CharSequence.*/
int32 lastIndexOfAnyChar_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 from, int32 to, StringJc chars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("lastIndexOfAnyChar_StringFunctionsJc");
  
  { 
    int32 zsq; 
    int32 ii; 
    
    StringBuilderJc* _stringBuilderThCxt = threadBuffer_StringBuilderJc(_thCxt);
    
    zsq = length_CharSequenceJc(sq, _thCxt);
    ii = to > zsq ? zsq : to;
    if(from < 0) { throw_sJc(ident_IndexOutOfBoundsExceptionJc, 
      ( setLength_StringBuilderJc(_stringBuilderThCxt, 0, _thCxt)
      , append_z_StringBuilderJc(_stringBuilderThCxt, "StringFunctions.lastIndexOfAnyChar - form <0; ", _thCxt)
      , append_I_StringBuilderJc(_stringBuilderThCxt, from, _thCxt)
      , toString_StringBuilderJc(&(_stringBuilderThCxt)->base.object, _thCxt)
      ), 0, &_thCxt->stacktraceThreadContext, __LINE__); return 0; };
    
    while(--ii >= from && indexOf_C_StringJc(chars, charAt_CharSequenceJc(sq, ii, _thCxt)) < 0)
      { }/*pre-decrement.*/
      
    { STACKTRC_LEAVE;
      return ii >= from ? ii + 1 : -1;
    }/*not found;*/
    
  }
  STACKTRC_LEAVE;
}


/**Checks whether the given CharSequence contains the other given CharSequence.*/
int32 indexOf_CsiiS_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 fromIndex, int32 to, StringJc str, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("indexOf_CsiiS_StringFunctionsJc");
  
  { 
    int32 zsq; 
    int32 max; 
    int32 ii; 
    char ch; 
    
    
    zsq = length_CharSequenceJc(sq, _thCxt);
    max = (to >= zsq ? zsq : to) - length_StringJc(str) + 1;
    ii = fromIndex - 1;
    if(fromIndex < 0) 
    { 
      
      ii = -1;
    }
    else if(fromIndex >= max) 
    { 
      
      { STACKTRC_LEAVE;
        return -1;
      }
    }
    ch = charAt_StringJc(str, 0);
    
    while(++ii < max)
      { 
        
        if(charAt_CharSequenceJc(sq, ii, _thCxt) == ch) 
        { /*:search first char of str*/
          
          int32 s1 = 0; 
          
          
          s1 = 0;
          { int32 jj; 
            for(jj = ii + 1; jj < ii + length_StringJc(str); ++jj)
              { 
                
                if(charAt_CharSequenceJc(sq, jj, _thCxt) != charAt_StringJc(str, ++s1)) 
                { 
                  
                  s1 = -1;/*designate: not found*/
                  
                  break;
                }
              }
          }
          if(s1 >= 0) { STACKTRC_LEAVE;
          return ii;
        }/*found.*/
          
        }
      }
    { STACKTRC_LEAVE;
      return -1;
    }/*not found;*/
    
  }
  STACKTRC_LEAVE;
}


/**Checks whether the given CharSequence contains the other given CharSequence.*/
int32 indexOf_CsiiCs_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 fromIndex, int32 to, struct CharSequenceJc_t* str, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("indexOf_CsiiCs_StringFunctionsJc");
  
  { 
    int32 zsq; 
    int32 max; 
    int32 ii; 
    char ch; 
    
    
    zsq = length_CharSequenceJc(sq, _thCxt);
    max = (to >= zsq ? zsq : to) - length_CharSequenceJc(str, _thCxt) + 1;
    ii = fromIndex - 1;
    if(fromIndex < 0) 
    { 
      
      ii = -1;
    }
    else if(fromIndex >= max) 
    { 
      
      { STACKTRC_LEAVE;
        return -1;
      }
    }
    ch = charAt_CharSequenceJc(str, 0, _thCxt);
    
    while(++ii < max)
      { 
        
        if(charAt_CharSequenceJc(sq, ii, _thCxt) == ch) 
        { /*:search first char of str*/
          
          int32 s1 = 0; 
          
          
          s1 = 0;
          { int32 jj; 
            for(jj = ii + 1; jj < ii + length_CharSequenceJc(str, _thCxt); ++jj)
              { 
                
                if(charAt_CharSequenceJc(sq, jj, _thCxt) != charAt_CharSequenceJc(str, ++s1, _thCxt)) 
                { 
                  
                  s1 = -1;/*designate: not found*/
                  
                  break;
                }
              }
          }
          if(s1 >= 0) { STACKTRC_LEAVE;
          return ii;
        }/*found.*/
          
        }
      }
    { STACKTRC_LEAVE;
      return -1;
    }/*not found;*/
    
  }
  STACKTRC_LEAVE;
}


/**Searches the first occurrence of the given CharSequence in a CharSequence.*/
int32 indexOf_CsCsi_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, struct CharSequenceJc_t* str, int32 fromIndex, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("indexOf_CsCsi_StringFunctionsJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return indexOf_CsiiCs_StringFunctionsJc(/*static*/sq, fromIndex, MAX_VALUE_IntegerJc, str, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}


/**Checks whether the given CharSequence contains the given String.*/
int32 lastIndexOf_CsiiS_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 fromIndex, int32 to, StringJc str, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("lastIndexOf_CsiiS_StringFunctionsJc");
  
  { 
    int32 zsq; 
    int32 max; 
    char ch; 
    
    
    zsq = length_CharSequenceJc(sq, _thCxt);
    max = (to >= zsq ? zsq : to) - length_StringJc(str) + 1;
    if(fromIndex >= max) 
    { 
      
      { STACKTRC_LEAVE;
        return -1;
      }
    }
    ch = charAt_StringJc(str, 0);
    
    while(--max >= fromIndex)
      { 
        
        if(charAt_CharSequenceJc(sq, max, _thCxt) == ch) 
        { 
          int32 s1 = 0; 
          
          
          s1 = 0;
          { int32 jj; 
            for(jj = max + 1; jj < max + length_StringJc(str); ++jj)
              { 
                
                if(charAt_CharSequenceJc(sq, jj, _thCxt) != charAt_StringJc(str, ++s1)) 
                { 
                  
                  s1 = -1;/*designate: not found*/
                  
                  break;
                }
              }
          }
          if(s1 > 0) { STACKTRC_LEAVE;
          return max;
        }/*found.*/
          
        }
      }
    { STACKTRC_LEAVE;
      return -1;
    }/*not found;*/
    
  }
  STACKTRC_LEAVE;
}


/**Checks whether the given CharSequence contains the other given CharSequence.*/
int32 lastIndexOf_CsiiCs_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* sq, int32 fromIndex, int32 to, struct CharSequenceJc_t* str, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("lastIndexOf_CsiiCs_StringFunctionsJc");
  
  { 
    int32 zsq; 
    int32 max; 
    char ch; 
    
    
    zsq = length_CharSequenceJc(sq, _thCxt);
    max = (to >= zsq ? zsq : to) - length_CharSequenceJc(str, _thCxt) + 1;
    if(fromIndex >= max) 
    { 
      
      { STACKTRC_LEAVE;
        return -1;
      }
    }
    ch = charAt_CharSequenceJc(str, 0, _thCxt);
    
    while(--max >= fromIndex)
      { 
        
        if(charAt_CharSequenceJc(sq, max, _thCxt) == ch) 
        { 
          int32 s1 = 0; 
          
          
          s1 = 0;
          { int32 jj; 
            for(jj = max + 1; jj < max + length_CharSequenceJc(str, _thCxt); ++jj)
              { 
                
                if(charAt_CharSequenceJc(sq, jj, _thCxt) != charAt_CharSequenceJc(str, ++s1, _thCxt)) 
                { 
                  
                  s1 = -1;/*designate: not found*/
                  
                  break;
                }
              }
          }
          if(s1 > 0) { STACKTRC_LEAVE;
          return max;
        }/*found.*/
          
        }
      }
    { STACKTRC_LEAVE;
      return -1;
    }/*not found;*/
    
  }
  STACKTRC_LEAVE;
}


/**Resolves the given String containing some transcription chars (usual backslash)*/
struct CharSequenceJc_t* convertTransliteration_StringFunctionsJc(/*static*/ struct CharSequenceJc_t* src, char transcriptChar, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("convertTransliteration_StringFunctionsJc");
  
  { 
    struct CharSequenceJc_t* sResult = null; 
    int32 posSwitch; 
    
    
    /*no initvalue*/
    posSwitch = indexOf_Csiic_StringFunctionsJc(/*static*/src, 0, length_CharSequenceJc(src, _thCxt), transcriptChar, _thCxt);
    if(posSwitch < 0) 
    { 
      
      sResult = src;
    }
    else 
    { /*:escape character is found before end*/
      
      struct StringBuilderJc_t* sbReturn = null; 
      
      ObjectJc *newObj2_1=null; /*J2C: temporary Objects for new operations
      */
      
      sbReturn = ctorO_c_StringBuilderJc(/*static*/(newObj2_1 = alloc_ObjectJc(sizeof_StringBuilderJc, 0, _thCxt)), src, _thCxt);
      
      while(posSwitch >= 0)
        { 
          char cNext; 
          int32 iChangedChar = 0; 
          
          StringJc _temp3_1; /*J2C: temporary references for concatenation */
          
          if(posSwitch < length_StringBuilderJc(sbReturn) - 1) 
          { 
            
            deleteCharAt_StringBuilderJc(sbReturn, posSwitch, _thCxt);
          }
          cNext = charAt_StringBuilderJc(sbReturn, posSwitch, _thCxt);
          /*no initvalue*/
          if((iChangedChar = /*? assignment*/indexOf_C_StringJc(zI_StringJc("snrtfb",6), cNext)) >= 0) 
          { 
            
            setCharAt_StringBuilderJc(sbReturn, posSwitch, charAt_StringJc(zI_StringJc(" \n\r\t\f\b",6), iChangedChar), _thCxt);
          }
          else if(cNext == 'a') 
          { /*: \a means end of file, coded inside with 4 = EOT (end of transmission).*/
            
            
            setCharAt_StringBuilderJc(sbReturn, posSwitch, cStartOfText_SpecialCharStringsJc, _thCxt);
          }
          else if(cNext == 'e') 
          { /*: \e means end of file, coded inside with 4 = EOT (end of transmission).*/
            
            
            setCharAt_StringBuilderJc(sbReturn, posSwitch, cEndOfText_SpecialCharStringsJc, _thCxt);
          }
          else 
          { }
          posSwitch = 
          ( _temp3_1= toString_StringBuilderJc(& ((* (sbReturn)).base.object), _thCxt)
          , indexOf_CI_StringJc(_temp3_1, transcriptChar, posSwitch + 1)
          );
        }
      sResult = sbReturn;
      activateGC_ObjectJc(newObj2_1, null, _thCxt);
    }
    { STACKTRC_LEAVE;
      return sResult;
    }
  }
  STACKTRC_LEAVE;
}


/**Returns a String with 2*indent spaces for indentation.*/
StringJc indent2_StringFunctionsJc(/*static*/ int32 indent, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("indent2_StringFunctionsJc");
  
  { 
    
    if(2 * indent < length_StringJc(indentString_StringFunctionsJc) - 1) 
    { 
      
      { STACKTRC_LEAVE;
        return substring_StringJc(indentString_StringFunctionsJc, 1, 1 + 2 * indent, _thCxt);
      }
    }
    else { STACKTRC_LEAVE;
      return substring_I_StringJc(indentString_StringFunctionsJc, 1, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}


/**Returns a String with a newline \n character and 2*indent spaces for indentation.*/
StringJc nl_indent2_StringFunctionsJc(/*static*/ int32 indent, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("nl_indent2_StringFunctionsJc");
  
  { 
    
    if(2 * indent < length_StringJc(indentString_StringFunctionsJc) - 1) 
    { 
      
      { STACKTRC_LEAVE;
        return substring_StringJc(indentString_StringFunctionsJc, 0, 1 + 2 * indent, _thCxt);
      }
    }
    else { STACKTRC_LEAVE;
      return indentString_StringFunctionsJc;
    }
  }
  STACKTRC_LEAVE;
}



/**J2C: Reflections and Method-table *************************************************/
const MtblDef_StringFunctionsJc mtblStringFunctionsJc = {
{ { sign_Mtbl_StringFunctionsJc//J2C: Head of methodtable.
  , (struct Size_Mtbl_t*)((0 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
  }
, { { sign_Mtbl_ObjectJc//J2C: Head of methodtable.
    , (struct Size_Mtbl_t*)((5 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
    }
  , clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_ObjectJc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
}, { signEnd_Mtbl_ObjectJc, null } }; //Mtbl


 extern_C struct ClassJc_t const reflection_ObjectJc;
 static struct superClasses_StringFunctionsJc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxMtblJc data[1];
 }superclasses_StringFunctionsJc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxMtblJc, 1, OBJTYPE_ClassOffset_idxMtblJc, null, null)
 , { {&reflection_ObjectJc, OFFSET_Mtbl(Mtbl_StringFunctionsJc, ObjectJc) }
   }
 };

extern_C struct ClassJc_t const reflection_StringFunctionsJc_s;
extern_C struct ClassJc_t const reflection_StringJc;
const struct Reflection_Fields_StringFunctionsJc_s_t
{ ObjectArrayJc head; FieldJc data[2];
} reflection_Fields_StringFunctionsJc_s =
{ CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_StringFunctionsJc_s)
, {
     { "cEndOfText"
    , 0 //nrofArrayElements
    , REFLECTION_char
    , 4 << kBitPrimitiv_Modifier_reflectJc |mSTATIC_Modifier_reflectJc //bitModifiers
    , 0 //compiler problem, not a constant,TODO: (int16)(&cEndOfText_StringFunctionsJc) //lo part of memory address of static member
    , 0 //compiler problem, not a constant,TODO: (int16)((int32)(&cEndOfText_StringFunctionsJc)>>16) //hi part of memory address of static member instead offsetToObjectifcBase, TRICKY because compatibilty.
    , &reflection_StringFunctionsJc_s
    }
   , { "indentString"
    , 0 //nrofArrayElements
    , &reflection_StringJc
    , kEnhancedReference_Modifier_reflectJc /*t*/ |mSTATIC_Modifier_reflectJc //bitModifiers
    , 0 //compiler problem, not a constant,TODO: (int16)(&indentString_StringFunctionsJc) //lo part of memory address of static member
    , 0 //compiler problem, not a constant,TODO: (int16)((int32)(&indentString_StringFunctionsJc)>>16) //hi part of memory address of static member instead offsetToObjectifcBase, TRICKY because compatibilty.
    , &reflection_StringFunctionsJc_s
    }
} };
const ClassJc reflection_StringFunctionsJc_s = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc) 
, "StringFunctionsJc_s"
,  0 //position of ObjectJc
, sizeof(StringFunctionsJc_s)
, (FieldJcArray const*)&reflection_Fields_StringFunctionsJc_s
, null //method
, (ClassOffset_idxMtblJcARRAY*)&superclasses_StringFunctionsJc_s //superclass
, null //interfaces
, 0    //modifiers
, &mtblStringFunctionsJc.mtbl.head
};
