/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __J1c_StringFunctions_CJc_h__
#define __J1c_StringFunctions_CJc_h__
#include <applstdef_emC.h>
#ifndef DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE

#include "emC/Base/MemC_emC.h"        //basic concept

#include "emC/Jc/ObjectJc.h"        //basic concept

#include "emC/Jc/StringJc.h"        //used often

   //basic concept


/* J2C: Forward declaration of struct ***********************************************/
struct StringFunctions_CJc_t;


/* J2C: includes *********************************************************/


/*@CLASS_C StringFunctions_CJc @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct StringFunctions_CJc_t
{ 
  union { ObjectJc object; } base; 
} StringFunctions_CJc_s;
  

#define sizeof_StringFunctions_CJc_s sizeof(StringFunctions_CJc_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef StringFunctions_CJcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define StringFunctions_CJcREFDEF
  struct StringFunctions_CJc_t;
  typedef TYPE_EnhancedRefJc(StringFunctions_CJc);
#endif

#ifdef DEF_ObjectJc_FULLCAPABILITY
/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct StringFunctions_CJc_X_t { ObjectArrayJc head; StringFunctions_CJcREF data[50]; } StringFunctions_CJc_X;
typedef struct StringFunctions_CJc_Y_t { ObjectArrayJc head; StringFunctions_CJc_s data[50]; } StringFunctions_CJc_Y;
#endif
 extern_C struct ClassJc_t const refl_StringFunctions_CJc_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_StringFunctions_CJc(OBJP) { CONST_ObjectJc(sizeof(StringFunctions_CJc_s), OBJP, &refl_StringFunctions_CJc_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_StringFunctions_CJc_F(ObjectJc* othis, ThCxt* _thCxt);


 extern StringJc version_StringFunctions_CJc;   /*Version, history and license.*/

//!!usage: static init code, invoke that one time in start of main.
void initStatic_StringFunctions_CJc();




/**Default constructor. */
METHOD_C struct StringFunctions_CJc_t* ctorO_StringFunctions_CJc(ObjectJc* othis, ThCxt* _thCxt);

/**Parses a given String and convert it to the integer number.
The String may start with a negative sign ('-') and should contain digits after them.
The digits for radix > 10 where built by the numbers 'A'..'Z' respectively 'a'..'z',
known as hexa numbers A..F or a..f. 
*/
METHOD_C int32 parseIntRadix_CsiiiiYS_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJc spaceChars, ThCxt* _thCxt);

/***  */
#define parseIntRadix_CsiiiiY_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars) \
(parseIntRadix_CsiiiiYS_StringFunctions_CJc(/*J2C:static method call*/srcP, pos, sizeP, radix, parsedChars, null_StringJc /*J2C: mem assignment*/, _thCxt))

/**Adequate method for long values, see {@link #parseIntRadix(String, int, int, int, int[], String)}.
*/
METHOD_C int64 parseLong_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJc spaceChars, ThCxt* _thCxt);

/**Parses a given String backward and convert it to the integer number.
The String may start with a negative sign ('-') and should contain digits after them.
The digits for radix > 10 where built by the numbers 'A'..'Z' respectively 'a'..'z',
known as hexa numbers A..F or a..f. 
*/
METHOD_C int32 parseIntRadixBack_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, ThCxt* _thCxt);

/*** */
METHOD_C float parseFloat_CsiiiY_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc src, int32 pos, int32 sizeP, int32* parsedChars, ThCxt* _thCxt);

/**Parses a given String and convert it to the float number.
An exponent is not regarded yet (TODO).
*/
METHOD_C float parseFloat_CsiiciY_StringFunctions_CJc(/*J2C:static method*/ CharSeqJc src, int32 pos, int32 sizeP, char decimalpoint, int32* parsedCharsP, ThCxt* _thCxt);


#ifdef DEF_ClassJc_Vtbl
/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Vtbl_StringFunctions_CJc[]; //marker for methodTable check
typedef struct Vtbl_StringFunctions_CJc_t
{ VtblHeadJc head;
  Vtbl_ObjectJc ObjectJc;
} Vtbl_StringFunctions_CJc;
#endif //#ifdef DEF_ClassJc_Vtbl



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class StringFunctions_CJc : private StringFunctions_CJc_s
{ public:

  StringFunctions_CJc(){ init_ObjectJc(&this->base.object, sizeof(StringFunctions_CJc_s), 0); setReflection_ObjectJc(&this->base.object, &refl_StringFunctions_CJc_s, 0); ctorO_StringFunctions_CJc(&this->base.object,  null/*_thCxt*/); }

  float parseFloat(CharSeqJc src, int32 pos, int32 sizeP, char decimalpoint, int32* parsedCharsP){  return parseFloat_CsiiciY_StringFunctions_CJc(src, pos, sizeP, decimalpoint, parsedCharsP,  null/*_thCxt*/); }

  float parseFloat(CharSeqJc src, int32 pos, int32 sizeP, int32* parsedChars){  return parseFloat_CsiiiY_StringFunctions_CJc(src, pos, sizeP, parsedChars,  null/*_thCxt*/); }

  int32 parseIntRadixBack(CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars){  return parseIntRadixBack_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars,  null/*_thCxt*/); }

  int32 parseIntRadix(CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJcpp spaceChars){  return parseIntRadix_CsiiiiYS_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars, spaceChars,  null/*_thCxt*/); }

  int32 parseIntRadix(CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars){  return parseIntRadix_CsiiiiY_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars); }

  int64 parseLong(CharSeqJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJcpp spaceChars){  return parseLong_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars, spaceChars,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/
#endif  //ndef DEF_NO_StringUSAGE  //Note: this capabilities should not be used on DEF_NO_StringUSAGE

#endif //__J1c_StringFunctions_CJc_h__
