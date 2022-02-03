/**************************************************************************
 * This file is generated by Java2C
 **copyright***************************************************************
 *************************************************************************/
#ifndef __J1c_StringFunctions_BJc_h__
#define __J1c_StringFunctions_BJc_h__
#include <applstdef_emC.h>
#if ! defined(DEF_NO_StringUSAGE)  //only possible with reflection because Vtable is need
#include "emC/Base/MemC_emC.h"        //basic concept

#include "emC/Jc/ObjectJc.h"        //basic concept

#include "emC/Jc/StringJc.h"        //used often

   //basic concept


/* J2C: Forward declaration of struct ***********************************************/
struct StringFunctions_BJc_t;


/* J2C: includes *********************************************************/


/*@CLASS_C StringFunctions_BJc @@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct StringFunctions_BJc_t
{ 
  union { ObjectJc object; } base; 
} StringFunctions_BJc_s;
  

#define sizeof_StringFunctions_BJc_s sizeof(StringFunctions_BJc_s)


/**J2c: Definitions of the enhanced reference. It's conditinally because it may be defined in a included header before. */
#ifndef StringFunctions_BJcREFDEF
  //J2C: definition of enhanced reference where it was need firstly: 
  #define StringFunctions_BJcREFDEF
  struct StringFunctions_BJc_t;
  typedef TYPE_EnhancedRefJc(StringFunctions_BJc);
#endif

/**J2c: Definitions of the array forms. NOTE: The number of elements are a helper for debug, the really used number depends on the memory size! */
typedef struct StringFunctions_BJc_X_t { ObjectArrayJc head; StringFunctions_BJcREF data[50]; } StringFunctions_BJc_X;
typedef struct StringFunctions_BJc_Y_t { ObjectArrayJc head; StringFunctions_BJc_s data[50]; } StringFunctions_BJc_Y;

 extern_C struct ClassJc_t const refl_StringFunctions_BJc_s;
  


/**CONST_Type useable as initializer for embedded/stack-instances*/
#define CONST_StringFunctions_BJc(OBJP) { CONST_ObjectJc(sizeof(StringFunctions_BJc_s), OBJP, &refl_StringFunctions_BJc_s), 0 }

/**J2C: finalize declaration. It is called by Garbage collector and inside other finalized methods.
 * It should be called by the user if the instance is removed. */
void finalize_StringFunctions_BJc_F(ObjectJc* othis, ThCxt* _thCxt);


 extern StringJc version_StringFunctions_BJc;   /*Version, history and license.*/
 extern StringJc sWhiteSpaces_StringFunctions_BJc; 

//!!usage: static init code, invoke that one time in start of main.
void initStatic_StringFunctions_BJc();




/**Default constructor. */
METHOD_C struct StringFunctions_BJc_t* ctorO_StringFunctions_BJc(ObjectJc* othis, ThCxt* _thCxt);

/**Returns the first line of any text.
*/
METHOD_C StringJc firstLine_StringFunctions_BJc(/*J2C:static method*/ CharSeqJc src, ThCxt* _thCxt);

/**Cleans a text which may be parsed or such, remove undesired indentation and replace the line end characters. 
*/
METHOD_C CharSeqJc removeIndentReplaceNewline_StringFunctions_BJc(/*J2C:static method*/ CharSeqJc src, int32 indent, StringJc indentChars, int32 tabSize, StringJc sNewline, bool bSkipSpaces, ThCxt* _thCxt);


#ifdef DEF_ClassJc_Vtbl
/* J2C: Method table contains all dynamic linked (virtual) methods
 * of the class and all super classes and interfaces. */
 extern const char sign_Vtbl_StringFunctions_BJc[]; //marker for methodTable check
typedef struct Vtbl_StringFunctions_BJc_t
{ VtblHeadJc head;
  Vtbl_ObjectJc ObjectJc;
} Vtbl_StringFunctions_BJc;
#endif //#ifdef DEF_ClassJc_Vtbl



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
/* J2C: The C++-class-definition. */
class StringFunctions_BJc : private StringFunctions_BJc_s
{ public:

  StringFunctions_BJc(){ init_ObjectJc(&this->base.object, sizeof(StringFunctions_BJc_s), 0); setReflection_ObjectJc(&this->base.object, &refl_StringFunctions_BJc_s, 0); ctorO_StringFunctions_BJc(&this->base.object,  null/*_thCxt*/); }

  StringJc firstLine(CharSeqJc src){  return firstLine_StringFunctions_BJc(src,  null/*_thCxt*/); }

  CharSeqJc removeIndentReplaceNewline(CharSeqJc src, int32 indent, StringJcpp indentChars, int32 tabSize, StringJcpp sNewline, bool bSkipSpaces){  return removeIndentReplaceNewline_StringFunctions_BJc(src, indent, indentChars, tabSize, sNewline, bSkipSpaces,  null/*_thCxt*/); }
};

#endif /*__CPLUSPLUSJcpp*/
#endif //! defined(DEF_NO_StringUSAGE)  //only possible with reflection because Vtable is need


#endif //__J1c_StringFunctions_BJc_h__
