/*@NoReflection*/
/************************************************************************************************
 * This file should be included in any applstdef.h to fulfill some  default settings.
 *
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
 * @content Definitions for basics, which maybe identical for all operation systems and compilers,
 * This file is include in <os_types_def.h>. Because that file is able to adjust in a project specific way,
 * the inclusion of this file can be changed. In that way the definitions in this file can be adapted.
 * Therefor it is not recommended to include this file directly in a users file. 
 *
 * @author Hartmut Schorrig
 */
#ifndef HGUARD_emCBase_applstdef_default
#define HGUARD_emCBase_applstdef_default


/**Adaption and test of some settings in the user's applstdef_emC.h */
//If no reflection are used, anyway DEF_REFLECTION_NO should be defined. 
#if !defined(DEF_REFLECTION_SIMPLE) && !defined(DEF_REFLECTION_OFFS) && !defined(DEF_REFLECTION_FULL) && !defined(DEF_REFLECTION_NO)
  #define DEF_REFLECTION_NO
#endif

//If reflection are given Object has Reflection. TODO remove DEF_ObjectJc_REFL..REF against immediately usage ifndef DEF_REFLECTION_NO
//#if !defined(DEF_REFLECTION_NO) && !!defined(DEF_REFLECTION_NO)
//  #define DEF_ObjectJc_REFL..REF
//  #undef DEF_ObjectJc_..SIMPLE
//#endif


//Yet always defined with the reflection, TODO maybe a variant if using virtual C++
#if defined(DEF_REFLECTION_FULL) && !defined(DEF_ClassJc_Vtbl)
  #define DEF_ClassJc_Vtbl    //It is used in the inspector sources
#endif

#if defined(DEF_ClassJc_Vtbl) && !defined(DEF_CharSeqJcCapabilities)
  //yet always defined with DEF_ClassJc_Vtbl, first one is necessary. 
  #define DEF_CharSeqJcCapabilities
#endif 

#ifdef DEF_ThreadContext_STACKTRC_NO
  #define DEF_ThreadContext_NOSTACKTRC_emC
#endif

#ifdef DEF_Exception_NO
  #define DEF_NO_Exception_emC
#endif

#ifndef VIRTUAL_emC  //empty definition, no virtual operations
  #ifdef DEF_USEvirtual_emC
    #define VIRTUAL_emC virtual
  #else
    #define VIRTUAL_emC
  #endif
#endif
#ifndef OVERRIDE_VIRTUAL_emC
  #ifdef DEF_USEvirtual_emC
    #define OVERRIDE_VIRTUAL_emC override
  #else
    #define OVERRIDE_VIRTUAL_emC
  #endif
#endif



//tag::StringJc[]
/**This is the defintion of a reference to a String and a value and state information. 
 * It is similar as the defintion of AddrVal_emC  or the macro STRUCT_AddrVal_emC
 * but the address is a union because of different capabilities. It is written in the same kind. 
 * * First element is a pointer with different types in the union.
 * * Second element is the length and flags, see in header emC/Base/StringBase_emC.h
 * Hint: definition of StringJc independent of an included emC/.../StringJc.h 
 * because it is used for example also in Exception_emC.h. 
 * It is a simple data struct and some macros, commonly usable. 
 */
typedef struct StringJc_T { 
  union CharSeqTypes_T { 
    char const* str; 
    #ifndef DEF_NO_StringUSAGE 
      struct StringBuilderJc_t* bu; 
      #ifdef DEF_CharSeqJcCapabilities
        struct ObjectJc_T const* obj; 
        #ifdef __cplusplus
          class CharSequenceJc* csq;
        #endif
      #endif
    #endif
  } addr; 
  VALTYPE_AddrVal_emC val;    //Note: Use same type as in STRUCT_AddrVal_emC 
} StringJc;
//end::StringJc[]

#define DEFINED_StringJc_emC

//old: typedef STRUCT_AddrVal_emC(StringJc, char const);

//tag::StringJc_Common[]
/**StringJc object containing null-values. */
extern_C StringJc const null_StringJc;

/**StringJc object containing an empty String, ref to  "", lenght = 0 */
extern_C StringJc const empty_StringJc;



/**Initializer-Macro for constant StringJc, initialize the StringJc-reference to a zero-terminated text.
 * The length of the text
 * is not stored inside StringJc, the length bits are setted to kIs_0_terminated_StringJc 
 * (it is the value of ,,mLength_StringJc,,), to detect this constellation.
 * @param TEXT should be a text-literal only. If it references a char-array, 
 *        a problem with persistence may existing.
 */
#define INIZ_z_StringJc(TEXT) { TEXT, kIs_0_terminated_StringJc}
#define CONST_z_StringJc(TEXT) INIZ_z_StringJc(TEXT)

/**Initializer-Macro for StringJc, initialize the StringJc-reference to a string literal.
 * The length of the literal is calculated via sizeof("text").
 * @param TEXT should only be a text-literal. 
 * If it references a char-array, the size is faulty 
 * and  problem with persistence may existing. 
 */
#define INIZ_text_StringJc(TEXT) { TEXT, (int)(sizeof(TEXT)-1) }

/**Initializer-Macro for constant StringJc, initialize the StringJc-reference to a text with known length.
 * Using this macro instead ,,CONST_StringJc(...),, saves calculation time to calculate the ,,strlen(),,.
 * @param TEXT should be a text-literal only. If it references a char-array, 
 *             a problem with persistence may existing.
 * @param LEN The length as number. Do not use methods like strlen(...)
 *            to determine the length, because this is a const-initializing-macro.
 *            In C++, methods are syntaxtically able to use, but it produces more machine code
 *            and the definition cannot store in a const segment. In C it is an error.
 */
#define INIZ_StringJc(TEXT, LEN) { {TEXT}, LEN }
#define CONST_StringJc(TEXT, LEN) INIZ_StringJc(TEXT, LEN)
#define NULL_StringJc { {null}, 0}
//end::StringJc_Common[]



#ifdef __cplusplus
  #ifdef DEF_CPP_COMPILE  //If the apropriate C-sources are compiled as C++
    /**C-Sources are compiled with C++, C++ linker label is desired.*/
    #define extern_CCpp extern
  #else                   //If all C-Sources are compiled with C
    /**C-Sources are compiled with C*/
    #define extern_CCpp extern "C"
  #endif
#else
  #define extern_CCpp extern
#endif


#if !defined(DEF_NO_THCXT_STACKTRC_EXC_emC) 
  #include <emC/Base/Assert_emC.h>
  #include <emC_srcApplSpec/applConv/EnhanceRef_simple.h>
  #include <emC/Base/Exception_emC.h>
#else
  //This is for a system without including Base/Exception_emC.h
  
  #define ASSERT_IGNORE_emC     //emC assertions not possible with that situation.
  
  //all STCKTRC macro are empty. Not necessary to include emC/Base/Exception_emC.h
  #define HGUARD_emC_Base_Exception_emC    //Prevents including Base/Exception_emC.h
  //#define DEF_DONOTCOMPILE_Base_Exception_emC


  /**An empty macro instead Stacktrace entry.
   * Note: the variable _thCxt may be used for some functions, but if not used, it should be optimized by compilation.
   */
  #define STACKTRC_ENTRY(NAME) MAYBE_UNUSED_emC struct ThreadContext_emC_t* _thCxt = null;
  #define STACKTRC_ROOT_ENTRY(NAME) MAYBE_UNUSED_emC struct ThreadContext_emC_t* _thCxt = null;
  #define ThCxt struct ThreadContext_emC_t

  /**An empty macro instead Stacktrace entry.
   * Here the _thCxt variable is given by argument list
   */
  #define STACKTRC_TENTRY(NAME)
  #define STACKTRC_ROOT_TENTRY(NAME)

  #define STACKTRC_LEAVE
  #define STACKTRC_RETURN return
  #define STACKTRC_THCXT null              //null as parameter for _thCxt, get it internally
  #define GET_STACKTRC_THCXT //ThreadContext_emC_s* _thCxt = getCurrent_ThreadContext_emC();
  #define CALLINE
  #define THCXT null

  #define Exception_emC void    //incognizable unused type.
  #define EXCEPTION_TRY
  #define EXCEPTION_CATCH if(0)      // let CATCH block empty, removed by compiler   ??_thCxt->tryObject->exc.exceptionNr !=0)
  #define TRY                        // The TRY... construction is empty
  #define _TRY
  #define CATCH(ID, DATA) if(false)  // let CATCH block empty, removed by compiler
  #define FINALLY
  #define END_TRY
  #define printStackTrace_Exception_emC(EXC, THCXT)  //it is empty, not used

  #ifndef THROW                      // It may be possible to define a special log out
    #define THROW(ID, MSG, VAL1, VAL2)  {}
    #define THROW1(ID, MSG, VAL1)  {}
    #define THROW_s0(ID, MSG, VAL1, VAL2) {}
    #define THROW1_s0(ID, MSG, VAL1) {}
    #define THROW_s0n(ID, MSG, VAL1, VAL2)  {}
    #define THROW_s0nf(ID, MSG, VAL1, VAL2, FILE1, LINE1)  {}
  #endif

#endif //DEF_NO_Exception_emC



#ifdef ASSERT_IGNORE_emC
  /**The assertion is fully ignored. An if-Block is always true.*/
  #define ASSERT_emC(COND, TEXT, VAL1, VAL2)
  #define ASSERT_TEST_emC(COND, TEXT, VAL1, VAL2)

  /**This variant of assertion enables the execution of a following code only if the assertion mets.
   * Because the assertions are ignored here, the construct is simple:
   * Pattern:<pre>
   * IF_ASSERT_emC(condition, "failure description", value1, value2) {
   *   //execute only if met.
   * }</pre>
   * creates:<pre>
   * {
   *   //execute only if met.
   * }</pre>
   * */
  #define IF_ASSERT_emC(COND, TEXT, VAL1, VAL2)

  #define CHECK_ASSERT_emC(COND, TEXT, VAL1, VAL2) true
  #ifndef ASSERT
    #define ASSERT(COND) ASSERT_emC(COND, "Assertion", 0,0)
  #endif
#endif







#ifdef DEF_NO_ObjectJc_emC
  #ifndef BASED_ON_ObjectJc_emC
    #define BASED_ON_ObjectJc_emC union{ObjectJc obj; } base;
  #endif
  typedef struct  ObjectJc_T { int id; } ObjectJc;
  typedef struct  ClassJc_T { int id; } ClassJc;
  extern_C ObjectJc* alloc_ObjectJc_verySimple_emC(int size, int id);
  #define ALLOC_ObjectJc(SIZE, REFL, ID) alloc_ObjectJc_verySimple_emC(SIZE, ID)
  #define INIZ_ObjectJc(OTHIZ, REFL, ID) {ID}  
  #define INIZ_ClassJc(THIZ, NAME) { *(NAME)}  //store first char only, do not use space for text  
  #define INIZsuper_ClassJc(THIZ, NAME, BASE) { 0 }  //store nothing, do not use space for text  
  #define CTOR_ObjectJc(OTHIZ, ADDR, SIZE, REFL, ID) ((OTHIZ)->id = ID, OTHIZ)  
  #define ctor_ObjectJc(OTHIZ, ADDR, SIZE, REFL, ID) ((OTHIZ)->id = ID, OTHIZ)  
  #define CHECKstrict_ObjectJc(OTHIZ, SIZE, REFL, ID) true
  #define CHECKinit_ObjectJc(OTHIZ, SIZE, REFL, ID) { (OTHIZ)->id = ID; }
  #define INSTANCEOF_ObjectJc(OZHIZ, REFL) true
  #define setReflection_ObjectJc(OTHIZ, REFL, ID) (OTHIZ)->id = ID
  #define setInitialized_ObjectJc(OTHIZ)
  #define isInitialized_ObjectJc(OTHIZ) true  //no information, default: It is initialized
  #define getID_ObjectJc(THIZ) ((THIZ)->id)
  #define getClass_ObjectJc(OTZHIZ) null
  #define lock_ObjectJc(OBJ)
  #define isLocked_ObjectJc(OBJ) true
  #define finalize_ObjectJc_F(OBJ, THCXT)
  #define unlock_ObjectJc(OBJ)

#else
  #ifndef BASED_ON_ObjectJc_emC
    #define BASED_ON_ObjectJc_emC union{ObjectJc obj; } base;
  #endif
  #include <emC/Base/Object_emC.h>
#endif


//The same definitions are also contained in EnhancedRef_simple.h, see concept of BlocKMem
#ifndef TYPE_EnhancedRefJc
  #define TYPE_EnhancedRefJc(TYPE) struct TYPE##_t* TYPE##REF
  #define NULL_REFJc null 
  #define SETREFJc(REF, OBJP, REFTYPE) (REF) = (OBJP);
  #define CLEAR_REFJc(REF) ((REF) = null)
  #define CLEARREF_Jc(REF) ((REF) = null)
  #define CLEARREFJc(REF) ((REF) = null)
  #define REFJc(REF)  (REF) 
#endif



//#if defined(DEF_ObjectJc_..SIMPLE) || !defined(DEF_ObjectJc_FULLCAPABILITY)
//# if defined(DEF_ObjectJcpp_REFLECTION) || defined(DEF_ObjectJc_SYNCHANDLE) || defined(DEF_ObjectJc_OWNADDRESS)
//#   error DEF_ObjectJc_..SIMPLE was defined together with one of the other DEF_ObjectJc...
//# endif
//#elif !!defined(DEF_REFLECTION_NO) 
//#  define DEF_ObjectJc_REFL..REF
//#endif



 

#endif //HGUARD_emCBase_applstdef_default
