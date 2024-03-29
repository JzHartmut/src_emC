/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#include <applstdef_emC.h>
//#ifdef DEF_ObjectJcpp_REFLECTION  //only possible with reflection because Vtable is need
#ifndef DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE


#include "emC/J1c/StringFunctions_CJc.h"
#include <string.h>  //because using memset()
#include <emC/Jc/ReflectionJc.h>   //Reflection concept 
  //basic stacktrace concept
#include "emC/Jc/StringJc.h"  //embedded type in class data
#include "emC/Jc/ObjectJc.h"      //It is a concept of CRuntimeJavalike


/* J2C: Forward declaration of struct ***********************************************/

/**Contains routines to convert String to number format.
@author Hartmut Schorrig

*/


const char sign_Vtbl_StringFunctions_CJc[] = "StringFunctions_CJc"; //to mark method tables of all implementations

#ifdef DEF_ClassJc_Vtbl
typedef struct VtblDef_StringFunctions_CJc_t { Vtbl_StringFunctions_CJc mtbl; VtblHeadJc end; } VtblDef_StringFunctions_CJc;
 extern VtblDef_StringFunctions_CJc const mtblStringFunctions_CJc;
#endif //DEF_ClassJc_Vtbl

StringJc version_StringFunctions_CJc = CONST_z_StringJc("2015-11-07"); //J2C:static StringJc

/*Constructor *//**J2C: autogenerated as default constructor. */
struct StringFunctions_CJc_t* ctorO_StringFunctions_CJc(ObjectJc* othis, ThCxt* _thCxt)
{ StringFunctions_CJc_s* thiz = (StringFunctions_CJc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("ctorO_StringFunctions_CJc");
  CHECKinit_ObjectJc(othis, sizeof(StringFunctions_CJc_s), refl_StringFunctions_CJc, 0);  
  //TODO: setReflection_ObjectJc(othis, &refl_StringFunctions_CJc, sizeof(StringFunctions_CJc_s));
  //j2c: Initialize all class variables:
  {
  }/*J2C:No body for constructor*/

  STACKTRC_LEAVE;
  return thiz;
}



/**Parses a given String and convert it to the integer number.*/
int32 parseIntRadix_CsiiiiYS_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJc spaceChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseIntRadix_CsiiiiYS_StringFunctions_CJc");
  
  { 
    
    
    int32  val = 0;
    
    bool  bNegativ;/*no initvalue*/
    
    int32  digit;/*no initvalue*/
    
    char  cc;/*no initvalue*/
    
    int32  ixSrc = pos;
    
    int32  size = length_CharSeqJc(srcP/*J1cT2*/, _thCxt) - pos;
    if(size > sizeP) 
    { 
      
      size = sizeP;
    }
    
    int32  maxDigit = ((/*J2C:cast% from char*/int32)((radix <= 10) ? '0' + radix - 1 : '9'));
    if(size > 0 && charAt_CharSeqJc(srcP/*J1cT2*/, ixSrc, _thCxt) == '-') 
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
        
        cc = charAt_CharSeqJc(srcP/*J1cT2*/, ixSrc, _thCxt);
        if(spaceChars.addr.str != null && indexOf_C_StringJc(spaceChars, cc) >= 0) 
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
      
      parsedChars[0] = ixSrc - pos;
    }
    { STACKTRC_LEAVE;
      return (val);
    }
  }
  STACKTRC_LEAVE;
}


/**Adequate method for long values, see {@link #parseIntRadix(String, int, int, int, int[], String)}.*/
int64 parseLong_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJc spaceChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseLong_StringFunctions_CJc");
  
  { 
    
    
    int64  val = 0;
    
    bool  bNegativ;/*no initvalue*/
    
    int32  digit;/*no initvalue*/
    
    char  cc;/*no initvalue*/
    
    int32  ixSrc = pos;
    
    int32  size = length_CharSeqJc(srcP/*J1cT2*/, _thCxt) - pos;
    if(size > sizeP) 
    { 
      
      size = sizeP;
    }
    
    int32  maxDigit = ((/*J2C:cast% from char*/int32)((radix <= 10) ? '0' + radix - 1 : '9'));
    if(charAt_CharSeqJc(srcP/*J1cT2*/, ixSrc, _thCxt) == '-') 
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
        
        cc = charAt_CharSeqJc(srcP/*J1cT2*/, ixSrc, _thCxt);
        if(spaceChars.addr.str != null && indexOf_C_StringJc(spaceChars, cc) >= 0) 
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
      
      parsedChars[0] = ixSrc - pos;
    }
    { STACKTRC_LEAVE;
      return (val);
    }
  }
  STACKTRC_LEAVE;
}


/**Parses a given String backward and convert it to the integer number.*/
int32 parseIntRadixBack_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseIntRadixBack_StringFunctions_CJc");
  
  { 
    
    
    int32  val = 0;
    
    //bool  bNegativ;/*no initvalue*/
    
    int32  digit;/*no initvalue*/
    
    char  cc;/*no initvalue*/
    
    int32  ixSrc = pos;
    
    int32  size = length_CharSeqJc(srcP/*J1cT2*/, _thCxt) - pos;
    if(size > sizeP) 
    { 
      
      size = sizeP;
    }
    
    int32  maxDigit = ((/*J2C:cast% from char*/int32)((radix <= 10) ? '0' + radix - 1 : '9'));
    
    int32  maxHexDigitLower = ((/*J2C:cast% from char*/int32)('A' + radix - 11));
    
    int32  maxHexDigitUpper = ((/*J2C:cast% from char*/int32)('a' + radix - 11));
    
    int32  multPosition = 1;
    
    while(size > 0 && ixSrc >= 0 && (digit = /*? assignment*/(cc = /*? assignment*/charAt_CharSeqJc(srcP/*J1cT2*/, ixSrc, _thCxt)) - '0') >= 0 && (cc <= maxDigit || (radix > 10 && (cc >= 'A' && (digit = /*? assignment*/(cc - 'A' + 10)) <= radix || cc >= 'a' && (digit = /*? assignment*/(cc - 'a' + 10)) <= radix))))
      { 
        
        val += multPosition * digit;
        multPosition *= radix;
        ixSrc -= 1;
        size -= 1;
      }
    if(size > 0 && ixSrc >= 0 && charAt_CharSeqJc(srcP/*J1cT2*/, ixSrc, _thCxt) == '-') 
    { 
      
      ixSrc -= 1;
      size -= 1;
      val = -val;
    }
    if(parsedChars != null) 
    { 
      
      parsedChars[0] = pos - ixSrc;
    }
    { STACKTRC_LEAVE;
      return (val);
    }
  }
  STACKTRC_LEAVE;
}


/*** */
float parseFloat_CsiiiY_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc src, int32 pos, int32 sizeP, int32* parsedChars, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseFloat_CsiiiY_StringFunctions_CJc");
  
  { 
    
    { STACKTRC_LEAVE;
      return parseFloat_CsiiciY_StringFunctions_CJc(/*J2C:static method call*/src, pos, sizeP, '.', parsedChars, _thCxt);
    }
  }
  STACKTRC_LEAVE;
}


/**Parses a given String and convert it to the float number.*/
float parseFloat_CsiiciY_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc src, int32 pos, int32 sizeP, char decimalpoint, int32* parsedCharsP, ThCxt* _thCxt)
{ 
  STACKTRC_TENTRY("parseFloat_CsiiciY_StringFunctions_CJc");
  
  { 
    
    
    float  ret;/*no initvalue*/
    
    int32  poscurr = pos;
    
    int32  restlen = length_CharSeqJc(src/*J1cT2*/, _thCxt) - pos;
    if(sizeP >= 0 && restlen > sizeP) 
    { 
      
      restlen = sizeP;
    }
    
    bool  bNegative;/*no initvalue*/
    if(restlen > 0 && charAt_CharSeqJc(src/*J1cT2*/, poscurr, _thCxt) == '-') 
    { 
      
      poscurr += 1;
      restlen -= 1;
      bNegative = true;
    }
    else 
    { 
      
      bNegative = false;
    }
    
    int32 zParsed[1] ; zParsed; /*J2C:modeAccess=Q*/
    ret = (float)parseIntRadix_CsiiiiYS_StringFunctions_CJc(/*J2C:static method call*/src, poscurr, restlen, 10, &zParsed[0], null_StringJc /*J2C: mem assignment*/, _thCxt);/*parses only a positive number.*/
    
    poscurr += zParsed[0];/*maybe 0 if .123 is written*/
    
    restlen -= zParsed[0];/*if(poscurr < (restlen+pos) && src.charAt(poscurr)==decimalpoint){*/
    
    if(restlen > 0 && charAt_CharSeqJc(src/*J1cT2*/, poscurr, _thCxt) == decimalpoint) 
    { 
      
      
      float  fracPart = (float)parseIntRadix_CsiiiiY_StringFunctions_CJc(/*J2C:static method call*/src, poscurr + 1, restlen - 1, 10, &zParsed[0]);
      if(zParsed[0] > 0) 
      { 
        
        switch(zParsed[0]){
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
      poscurr += zParsed[0] + 1;/*don't forget the decimal point  */
      
    }/*TODO exponent*/
    
    if(parsedCharsP != null) 
    { 
      
      parsedCharsP[0] = poscurr - pos;
    }
    if(bNegative) 
    { 
      
      ret = -ret;
    }
    { STACKTRC_LEAVE;
      return ret;
    }
  }
  STACKTRC_LEAVE;
}



#ifdef DEF_ClassJc_Vtbl
/**J2C: Reflections and Method-table *************************************************/
const VtblDef_StringFunctions_CJc mtblStringFunctions_CJc = {
{ { sign_Vtbl_StringFunctions_CJc //J2C: Head of methodtable of StringFunctions_CJc
  , (struct Size_Vtbl_t*)((0 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
  }
  //J2C: The superclass's methodtable: 
, { { sign_Vtbl_ObjectJc //J2C: Head of methodtable of ObjectJc
    , (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
    }
    //J2C: Dynamic methods of the class :ObjectJc:
  , clone_ObjectJc_F //clone
  , equals_ObjectJc_F //equals
  , finalize_ObjectJc_F //finalize
  , hashCode_ObjectJc_F //hashCode
  , toString_ObjectJc_F //toString
  }
}, { signEnd_Vtbl_ObjectJc, null } }; //Vtbl
#endif //#ifdef DEF_ClassJc_Vtbl



#ifdef DEF_REFLECTION_FULL

 extern_C struct ClassJc_t const refl_ObjectJc;
 static struct superClasses_StringFunctions_CJc_s_t
 { ObjectArrayJc head;
   ClassOffset_idxVtblJc data[1];
 }superclasses_StringFunctions_CJc_s =
 { CONST_ObjectArrayJc(ClassOffset_idxVtblJc, 1, OBJTYPE_ClassOffset_idxVtblJc, null, null)
 , { {&refl_ObjectJc
     #ifdef DEF_ClassJc_Vtbl
     , OFFSET_Vtbl(Vtbl_StringFunctions_CJc, ObjectJc) 
     #endif
     }
   }
 };

extern_C struct ClassJc_t const refl_StringFunctions_CJc;
extern_C struct ClassJc_t const refl_StringJc;
const struct Reflection_Fields_StringFunctions_CJc_t
{ ObjectArrayJc head; FieldJc data[1];
} refl_Fields_StringFunctions_CJc_s =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_StringFunctions_CJc)
, {
     { "version"
    , 0 //nrofArrayElements
    , &refl_StringJc
    , kEnhancedReference_Modifier_reflectJc /*t*/ |mSTATIC_Modifier_reflectJc //bitModifiers
    , 0 //compiler problem, not a constant,TODO: (int16)(&version_StringFunctions_CJc) //lo part of memory address of static member
    , 0 //compiler problem, not a constant,TODO: (int16)((int32)(&version_StringFunctions_CJc)>>16) //hi part of memory address of static member instead offsetToObjectifcBase, TRICKY because compatibilty.
    , &refl_StringFunctions_CJc
    }
} };
const ClassJc refl_StringFunctions_CJc = 
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc) 
, "StringFunctions_CJc_s"
,  0 //position of ObjectJc
, sizeof(StringFunctions_CJc_s)
, (FieldJc_Y const*)&refl_Fields_StringFunctions_CJc_s
, null //method
, &superclasses_StringFunctions_CJc_s.head.object //superclass
, null //interfaces
, 0    //modifiers
#ifdef DEF_ClassJc_Vtbl
, &mtblStringFunctions_CJc.mtbl.head
#endif
};


#elif !defined(DEF_REFLECTION_NO) && !defined(DEFINED_refl_StringFunctions_CJc)

ClassJc const refl_StringFunctions_CJc = INIZ_ClassJc(refl_StringFunctions_CJc, "StringFunctions_CJc");


#endif //DEF_REFLECTION_FULL

#endif //ndef DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE

//#endif //#ifdef DEF_ObjectJcpp_REFLECTION  //only possible with reflection because Vtable is need
