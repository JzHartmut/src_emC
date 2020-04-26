//Defines the macors for EnhancedRefJc in a kind that they are simpe refernces.


//#include <fw_Platform_conventions.h>
//#define TYPE_EnhancedRefJc(TYPE) struct TYPE##REF_t* TYPE##REF
#define TYPE_EnhancedRefJc(TYPE) struct TYPE##_t* TYPE##REF 
//old form deprcated:
#define DEFINE_EnhancedRefJc(TYPE) typedef TYPE_EnhancedRefJc(TYPE)

#define SETREFJc(REF, OBJP, REFTYPE) (REF) = (OBJP);

/**Makro to set a enhanced reference to null. 
 * Note: because the makro should write in form
 *   CLEAR_REF(dst, value);
 * the ending semicolon is set outside the makro.
 * @param REF The reference as value
 */
#define CLEAR_REFJc(REF) ((REF) = null)
#define CLEARREF_Jc(REF) ((REF) = null)
#define CLEARREFJc(REF) ((REF) = null)
     
#define REFJc(REF)  (REF) 

/**Macro to initialize the value of a defined reference staticly to null. */
#define NULL_REFJc null

/**Macro to define the reflection of the enhanced reference of any type, able to use in a C-File.
 * @param TYPE the type of the reference.
 */
#define DEFINE_REFLECTION_REF(TYPE) \
  extern_C struct ClassJc_t const refl_##TYPE; \
  extern_C struct ClassJc_t const refl_##TYPE##REF; \
  const struct Reflection_Fields_##TYPE##REF_t{ ObjectArrayJc head; FieldJc data[2];} refl_Fields_##TYPE##REF = \
  { CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_##TYPE##REF) \
  , { { "ref", 0 , &refl_##TYPE, 0, 0, 0, &refl_##TYPE##REF } \
  } }; \
  const ClassJc refl_##TYPE##REF =\
  { CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_##TYPE##REF, null) \
  , "Ptr", 0, sizeof(TYPE##REF), (FieldJcArray const*)&refl_Fields_##TYPE##REF \
  }

