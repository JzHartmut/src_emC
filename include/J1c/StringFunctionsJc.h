/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __J1c_StringFunctionsJc_h__
#define __J1c_StringFunctionsJc_h__

#include "Jc/ObjectJc.h"        //basic concept

#include "Jc/StringJc.h"        //used often

#include "Fwc/fw_Exception.h"   //basic concept


/* J2C: Forward declaration of struct ***********************************************/
struct StringFunctionsJc_t;


/* J2C: includes *********************************************************/


/*@CLASS_C StringFunctionsJc @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct StringFunctionsJc_t
{ 
  union { ObjectJc object; } base; 
} StringFunctionsJc_s;
  

#define sizeof_StringFunctionsJc_s sizeof(StringFunctionsJc_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef StringFunctionsJcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define StringFunctionsJcREFDEF
  struct StringFunctionsJc_t;
  DEFINE_EnhancedRefJc(StringFunctionsJc);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct StringFunctionsJc_X_t { ObjectArrayJc head; StringFunctionsJcREF data[50]; } StringFunctionsJc_X;
typedef struct StringFunctionsJc_Y_t { ObjectArrayJc head; StringFunctionsJc_s data[50]; } StringFunctionsJc_Y;

 extern_C struct ClassJc_t const reflection_StringFunctionsJc_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_StringFunctionsJc(OBJP) { CONST_ObjectJc(sizeof(StringFunctionsJc_s), OBJP, &reflection_StringFunctionsJc_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_StringFunctionsJc_F(ObjectJc* othis, ThCxt* _thCxt);


#define version_StringFunctionsJc 20120822  /*Version, history and license.*/


/**Default constructor. */
METHOD_C struct StringFunctionsJc_t* ctorO_StringFunctionsJc(ObjectJc* othis, ThCxt* _thCxt);

/**Returns the position of the end of an identifier.*/
METHOD_C int32 posAfterIdentifier_tii_StringFunctionsJc(/*static*/ StringJc src, int32 start, int32 endMax, ThCxt* _thCxt);

/**Returns the position of the end of an identifier.*/
METHOD_C int32 posAfterIdentifier_tiiSS_StringFunctionsJc(/*static*/ StringJc src, int32 start, int32 endMax, StringJc additionalStartChars, StringJc additionalChars, ThCxt* _thCxt);

/**Parses a given String and convert it to the integer number.*/
METHOD_C int32 parseIntRadix_StringFunctionsJc(/*static*/ StringJc srcP, int32 pos, int32 sizeP, int32 radix, int32_Y* parsedChars, ThCxt* _thCxt);

/**Parses a given String backward and convert it to the integer number.*/
METHOD_C int32 parseIntRadixBack_StringFunctionsJc(/*static*/ StringJc srcP, int32 pos, int32 sizeP, int32 radix, int32_Y* parsedChars, ThCxt* _thCxt);

/**Parses a given String and convert it to the float number.*/
METHOD_C float parseFloat_StringFunctionsJc(/*static*/ StringJc src, int32 pos, int32 sizeP, int32_Y* parsedCharsP, ThCxt* _thCxt);

/**Compares two Strings or StringBuilder-content or any other CharSequence.*/
METHOD_C int32 compare_StringFunctionsJc(/*static*/ StringJc s1, StringJc s2, ThCxt* _thCxt);

/**Compares two Strings or StringBuilder-content or any other CharSequence.*/
METHOD_C bool equals_tt_StringFunctionsJc(/*static*/ StringJc s1, StringJc s2, ThCxt* _thCxt);


/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Mtbl_StringFunctionsJc[]; //marker for methodTable check
typedef struct Mtbl_StringFunctionsJc_t
{ MtblHeadJc head;
  Mtbl_ObjectJc ObjectJc;
} Mtbl_StringFunctionsJc;



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class StringFunctionsJc : private StringFunctionsJc_s
{ public:

  int32 compare(StringJc s1, StringJc s2){  return compare_StringFunctionsJc(s1, s2,  null/*_thCxt*/); }

  StringFunctionsJc(){ init_ObjectJc(&this->base.object, sizeof(StringFunctionsJc_s), 0); setReflection_ObjectJc(&this->base.object, &reflection_StringFunctionsJc_s, 0); ctorO_StringFunctionsJc(&this->base.object,  null/*_thCxt*/); }

  bool equals(StringJc s1, StringJc s2){  return equals_tt_StringFunctionsJc(s1, s2,  null/*_thCxt*/); }

  float parseFloat(StringJcpp src, int32 pos, int32 sizeP, int32_Y* parsedCharsP){  return parseFloat_StringFunctionsJc(src, pos, sizeP, parsedCharsP,  null/*_thCxt*/); }

  int32 parseIntRadixBack(StringJcpp srcP, int32 pos, int32 sizeP, int32 radix, int32_Y* parsedChars){  return parseIntRadixBack_StringFunctionsJc(srcP, pos, sizeP, radix, parsedChars,  null/*_thCxt*/); }

  int32 parseIntRadix(StringJcpp srcP, int32 pos, int32 sizeP, int32 radix, int32_Y* parsedChars){  return parseIntRadix_StringFunctionsJc(srcP, pos, sizeP, radix, parsedChars,  null/*_thCxt*/); }

  int32 posAfterIdentifier(StringJc src, int32 start, int32 endMax, StringJcpp additionalStartChars, StringJcpp additionalChars){  return posAfterIdentifier_tiiSS_StringFunctionsJc(src, start, endMax, additionalStartChars, additionalChars,  null/*_thCxt*/); }

  int32 posAfterIdentifier(StringJc src, int32 start, int32 endMax){  return posAfterIdentifier_tii_StringFunctionsJc(src, start, endMax,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/

#endif //__J1c_StringFunctionsJc_h__
