/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __J1c_StringFunctions_CJc_h__
#define __J1c_StringFunctions_CJc_h__

#include "Fwc/fw_MemC.h"        //basic concept

#include "Jc/ObjectJc.h"        //basic concept

#include "Jc/StringJc.h"        //used often

#include "Fwc/fw_Exception.h"   //basic concept


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
  DEFINE_EnhancedRefJc(StringFunctions_CJc);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct StringFunctions_CJc_X_t { ObjectArrayJc head; StringFunctions_CJcREF data[50]; } StringFunctions_CJc_X;
typedef struct StringFunctions_CJc_Y_t { ObjectArrayJc head; StringFunctions_CJc_s data[50]; } StringFunctions_CJc_Y;

 extern_C struct ClassJc_t const reflection_StringFunctions_CJc_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_StringFunctions_CJc(OBJP) { CONST_ObjectJc(sizeof(StringFunctions_CJc_s), OBJP, &reflection_StringFunctions_CJc_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_StringFunctions_CJc_F(ObjectJc* othis, ThCxt* _thCxt);


 extern StringJc version_StringFunctions_CJc;   /*Version, history and license.*/


/**Default constructor. */
METHOD_C struct StringFunctions_CJc_t* ctorO_StringFunctions_CJc(ObjectJc* othis, ThCxt* _thCxt);

/**Parses a given String and convert it to the integer number.*/
METHOD_C int32 parseIntRadix_SiiiiYS_StringFunctions_CJc(/*J2C:static method*/ StringJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJc spaceChars, ThCxt* _thCxt);

/*** */
#define parseIntRadix_SiiiiY_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars) \
(parseIntRadix_SiiiiYS_StringFunctions_CJc(/*J2C:static method call*/srcP, pos, sizeP, radix, parsedChars, null_StringJc /*J2C: mem assignment*/, _thCxt))

/**Adequate method for long values, see {@link #parseIntRadix(String, int, int, int, int[], String)}.*/
METHOD_C int64 parseLong_StringFunctions_CJc(/*J2C:static method*/ StringJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJc spaceChars, ThCxt* _thCxt);

/**Parses a given String backward and convert it to the integer number.*/
METHOD_C int32 parseIntRadixBack_StringFunctions_CJc(/*J2C:static method*/ StringJc srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, ThCxt* _thCxt);

/*** */
METHOD_C float parseFloat_SiiiY_StringFunctions_CJc(/*J2C:static method*/ StringJc src, int32 pos, int32 sizeP, int32* parsedChars, ThCxt* _thCxt);

/**Parses a given String and convert it to the float number.*/
METHOD_C float parseFloat_SiiciY_StringFunctions_CJc(/*J2C:static method*/ StringJc src, int32 pos, int32 sizeP, char decimalpoint, int32* parsedCharsP, ThCxt* _thCxt);


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Mtbl_StringFunctions_CJc[]; //marker for methodTable check
typedef struct Mtbl_StringFunctions_CJc_t
{ MtblHeadJc head;
  Mtbl_ObjectJc ObjectJc;
} Mtbl_StringFunctions_CJc;



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class StringFunctions_CJc : private StringFunctions_CJc_s
{ public:

  StringFunctions_CJc(){ init_ObjectJc(&this->base.object, sizeof(StringFunctions_CJc_s), 0); setReflection_ObjectJc(&this->base.object, &reflection_StringFunctions_CJc_s, 0); ctorO_StringFunctions_CJc(&this->base.object,  null/*_thCxt*/); }

  float parseFloat(StringJcpp src, int32 pos, int32 sizeP, char decimalpoint, int32* parsedCharsP){  return parseFloat_SiiciY_StringFunctions_CJc(src, pos, sizeP, decimalpoint, parsedCharsP,  null/*_thCxt*/); }

  float parseFloat(StringJcpp src, int32 pos, int32 sizeP, int32* parsedChars){  return parseFloat_SiiiY_StringFunctions_CJc(src, pos, sizeP, parsedChars,  null/*_thCxt*/); }

  int32 parseIntRadixBack(StringJcpp srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars){  return parseIntRadixBack_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars,  null/*_thCxt*/); }

  int32 parseIntRadix(StringJcpp srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJcpp spaceChars){  return parseIntRadix_SiiiiYS_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars, spaceChars,  null/*_thCxt*/); }

  int32 parseIntRadix(StringJcpp srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars){  return parseIntRadix_SiiiiY_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars); }

  int64 parseLong(StringJcpp srcP, int32 pos, int32 sizeP, int32 radix, int32* parsedChars, StringJcpp spaceChars){  return parseLong_StringFunctions_CJc(srcP, pos, sizeP, radix, parsedChars, spaceChars,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/

#endif //__J1c_StringFunctions_CJc_h__