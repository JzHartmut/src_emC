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
 * @content This file defines only the struct ObjectJc_t and the base interface ObjectJcpp.
 * It is the minimal base for some struct or interface of the framework layer,
 * which should also be designable without knowledge of the Jc-layer, 
 * but useable outside of the users algorithm if necessary with ReflectionJc-concept.
 *
 * @author Hartmut Schorrig
 * @version 2.0
 * list of changes:
 * 2019-10: Hartmut combined with DEF_ObjectJc_SIMPLE
 * 2008-04-22: JcHartmut chg:The elements idSemaphore and idWaitingThread are combined to idSyncHandles.
 *                       New element offsetToHeapBlock, but not in use yet.
 * 2007-10-00: JcHartmut creation, dissolved from ObjectJc.h
 *
 ****************************************************************************/
#include <applstdef_emC.h>  //Note: define before include-guards because applstdef_emC,h may include this file too.
//The following include guard prevent twice include especially if app�stdefJc.h includes this file already.
#ifndef __objectBaseC__h__
#define __objectBaseC__h__

#include <emC/Base/MemC_emC.h>


struct ThreadContext_emC_t;
struct ClassJc_t;


struct Size_Mtbl_t;


//definition of StringJc to use this type before including emC/StringJc
typedef struct StringJc_T { 
  union CharSeqTypes_T { 
    char const* str; 
    struct StringBuilderJc_t* bu; 
    struct ObjectJc_t const* obj; 
  } addr; 
  VALTYPE_AddrVal_emC val;    //Note: Use same type as in STRUCT_AddrVal_emC 
} StringJc;
//old: typedef STRUCT_AddrVal_emC(StringJc, char const);







/*@CLASS_C ObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#ifdef DEF_ObjectJc_SIMPLE
  #include <emC_srcApplSpec/SimpleNumCNoExc/ObjectJc_simple.h>  //use this
#elif !defined(DEF_ObjectJc_NO)
  #include <emC_srcApplSpec/applConv/ObjectJc_full.h>  //use this
#endif


/**Compatibility: */
#define Object_Jc_t ObjectJc_t


/**Allocates an ObjectJc in the thread buffer. Such an instance must be used immediately, then it is similar to an embedded instance in the stack. 
 * It can be returned and used in the calling enviroment immediately or return. That is the difference to a embedded instance in the stack.
 * Only one instance can be located in the thread context. It is over-written if another instance is created in the thread context.
 */
ObjectJc* allocInThreadCxt_ObjectJc(int size, char const* sign, struct ThreadContext_emC_t* _thCxt);


/**Allocates an memory area and initialized it with the basicly values of ObjectJc.
* * The element objectIdentSize is set with the size information.
* * The element ownAddress is set
* * The element reflectionClass is set to null.  
* * All other elements are set initially.
*
* To free the ObjectJc use [[free_ObjectJc(...)]] because it should work with the same memory management. Don't use low level functions.
*
* This routine assumes, that dynamically memory is present. 
* In long-running-realtime-applications a dynamic-memory-management may be spurious
* in the running phase, but maybe possible at startupt time.
* The implementation of this routine may be different adequate to the system definitions.
* Therefore it is not implemented in the associated source file ,,ObjectJc.c,,.
* The Implementation should be provided in a proper source file for memory management.
* @param size The size of the Object to allocate. 
*             If a value of -1 is given, a standard size will be allocated.
*             This feature can be used to provide so much as possible space for a buffer.
* @param typeInstanceIdent Information bits, see [[setIdentAndSize_ObjectJc(int, int)]],
*        but without the size information. 
*        The bits kIsMediumSize_objectIdentSize_ObjectJc and mIsLargeSize_objectIdentSize_ObjectJc
*        are regarded especially.
* @return the reference to the initialized Object.
* @throws IndexOutOfBoundsException if the size doesn't match to typeInstanceIdent. 
* @throws RuntimeException if a memory space can't allocate.
*/
extern_C ObjectJc* alloc_ObjectJc ( const int size, const int32 typeInstanceIdent, struct ThreadContext_emC_t* _thCxt);


/**Freeze an Object allocated with [[alloc_ObjectJc(...)]]. */
extern_C void free_ObjectJc(ObjectJc* thiz);



/**Supplies the rest of block if the Object is allocated in a block heap, or an empty MemC if there is no rest space. 
* @param size The requested size (>0) or the requested number of references (<0). 
*        If < 0 then the available size is returned, where the given number of references is considered (this value negative).
* @return A MemC-information which is placed immediate after the Object, or this size_MemC(returnObject) is 0.
* The implementation of this method depends from a BlockHeap-Concept and is located there.
*/
METHOD_C MemC getRestBlock_ObjectJc(ObjectJc* ythis, int size, ThCxt* _thCxt);


/**Submits the responsibility to the instance to a garbage collector. 
* It should be deleted if there are no more references to the object.
* The garbage collector mechanism should check whether the object is still referenced.
* @param object the object which is submitted to the GC
* @param exclObject excluding: If this addr isn't null and it is in the same block, 
*        the block doesn't activate for garbage collection.
*        It is because a returned address may be use in the calling environment. 
*        The activating for garbage collection have to be organized there. 
*        The Java2C-Translator consideres this situation.
*
*/
extern_C void activateGC_ObjectJc(void const* object, void const* exclObject, ThCxt* _thCxt);


/** Assigns a reference to any reference management system.
* This method doesn't store the reference to the src in the enhanced reference, 
* it should be done outside because better pointer type checking. 
* A back reference to refbase is stored in the block of the heap,
* and the Index of this back reference is stored in refbase.
* If src is not inside a block heap, a 0 value is setted to *refbase.
*
* @ param reference the address of the enhanced reference. It is a void* because there are several reference types.
* @ param instance The address of the instance which is referenced.
*/
extern_C void setBackRefJc(void* reference, void const* instance);

/** Clears a reference in any reference management system.
*  The reference itself will be not stored here, it should be done outside because better
*  pointer type checking. A back reference to refbase is stored in the block of the heap,
*  and the Index of this back reference is stored in refbase.
*
*  If src is not inside a block heap, a 0 value is setted to *refbase.
*
*  @ param reference address of the enhanced reference
*/
extern_C void clearBackRefJc(void* reference);




/**Checks the consistence of the given instance based on ObjectJc.
* An Object should be initialized before it is used. This method should be used in the constructor
* of all classes to check whether the initializing is done.
* @param size 0 or the requested size of the instance. If 0 then the size info will not be checked.
*             The instance is valid if the size saved in the element ,,objectIdentSize,, is >= size.
*             A greater instance (derived) is also accepted.
* @param ident 0 or the requested indent. If 0 then the ident info will not be checked.
* @param clazzReflection instanceof_ObjectJc() will be tested. If this param is null, no test of reflection is done.
* @return true if no error, false on error and not activated throw handle
* @throws RuntimeException if faulty.
*/
extern_C bool checkStrict_ObjectJc ( ObjectJc const* thiz, uint size, struct ClassJc_t const* clazzReflection, int ident, struct ThreadContext_emC_t* _thCxt);


/**Checks the consistence of the given instance based on ObjectJc and initialize the ident and reflection if they are empty.
* An Object should be initialized before with [[iniz_ObjectJc(...)]] or as static instance with [[INIZ_ObjectJc(...)]]. 
* This method should be used in the constructor of all classes to check whether the initializing is done.
* @param size The requested size of the instance.
*             The instance is valid if the size saved in the element ,,objectIdentSize,, is >= size.
*             A greater instance (derived) is accepted also.
* @param clazzReflection instanceof_ObjectJc() will be tested. If this param is null, no test of reflection is done.
*             Unsupported feature: If the reflection class of the instance is null, it will be set with this reference.
*             But call setReflection_ObjectJc() instead before, because this method may be changed in future. It should only test, not set anything!
* @return true if ok, 
*/
extern_C bool checkInit_ObjectJc ( ObjectJc* ythis, int size, int ident, struct ClassJc_t const* clazzReflection, struct ThreadContext_emC_t* _thCxt);

/**Checks the consistence or init, 
* @deprecated, use [[checkOrInit_ObjectJc(...)]] with a more significant name.
*/
#define checkConsistence_ObjectJc(THIS, SIZE, REFL, THCXT) checkInit_ObjectJc(THIS, SIZE, 0, REFL, THCXT)
#define checkOrInit_ObjectJc checkInit_ObjectJc

#define INIZ_objReflId_ObjectJc INIZ_ObjectJc



/**Initializer for any instance with {0}. Should be used on stack variable especially before they are handled with a ctor...(...).*/
#define NULL_ObjectJc {0}

/**This macro provides an initializer ,,{...},, for any instance which is derived from Object immediately.
 * Hint: use ,,{INITIALIZER_ObjectJc(...), more data}. 
 * @param OBJ The instance itself. It is used to store the OWNADDRESS and to build sizeof(OBJ) for the ObjectJc-part.
 */
#define CONST_Instance_ObjectJc(OBJ) { INITIALIZER_ObjectJc(OBJ, null, 0) }


#define ident_newAllocated_ObjectJc 0x0001


/**Returns the mem area for this Object.
* It can be used to check whether a member is really in range, especially for complex data. See [[checkAddress_MemC(...)]]  
*/
inline MemC getMemC_ObjectJc(ObjectJc* thiz){ MemC ret; SET_MemC(ret, thiz, getSizeInfo_ObjectJc(thiz)); return ret; } 




/**Returns a new Identification for an Object. This method may be implemented user-specific
 * to generate a log file with instantiated Objects.
 */
extern_C int newIdent_ObjectJc();



/**tests wether the given object is an instance of the requested Type.
* Javalike: instanceof-operator.
* @param ythis any Object
* @param reflection The reflection of the type to compare.
*/
extern_C bool instanceof_ObjectJc(ObjectJc const* ythis, struct ClassJc_t const* reflection);




#ifndef DEF_REFLECTION_FULL

struct ClassJc_t;

/**The Reflection is reduced to a character constant which contains the name of the type, helpfull for debug. 
* This struct needs only 6 int32 words per existing type.
*/
typedef struct ClassJc_t
{
  int idType;   // sizeReflOffs;

  #ifndef DEF_NO_StringJcCapabilities
  char const* name;
  #endif

  #ifdef DEF_REFLECTION_OFFS
  /**The lo-part (16 bit) of the address of this element is used as type ident. */
  int32 const* reflOffs;
  //#elif !defined(DEF_REFLECTION_NO)
  /**The lo-part (16 bit) of the address of this element is used as type ident. */
  //  int const* reflOffs;
  #endif
  #ifdef DEF_ObjectJc_REFLREF
  struct ClassJc_t const* superClass;
  #endif
} ClassJc;

extern ClassJc const reflection_ClassJc;


/**There are some variants of the macro INIZ_ClassJc(OBJ, NAME, REFLOFFS) 
 * and INIZsuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER)
 * depending of the existing elements in ClassJc:
 */
#ifdef DEF_NO_StringJcCapabilities
  #ifdef DEF_REFLECTION_OFFS
    #define INIZ_ClassJc(OBJ, NAME, REFLOFFS) { (int)(intptr_t)&(REFLOFFS) & mType_ObjectJc, REFLOFFS }
    #ifdef DEF_ObjectJc_REFLREF
      #define INIZsuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(REFLOFFS) & mType_ObjectJc, REFLOFFS, REFLSUPER }/*TODO*/
    #else 
      #define INIZsuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(REFLOFFS) & mType_ObjectJc, REFLOFFS }/*TODO*/
    #endif
  #else 
    #define INIZ_ClassJc(OBJ, NAME) { (int)(intptr_t)&(OBJ)}
    #ifdef DEF_ObjectJc_REFLREF
      #define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), REFLSUPER }
    #else 
      #define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ) }
    #endif
  #endif
#else
  #ifdef DEF_REFLECTION_OFFS
    #define INIZ_ClassJc(OBJ, NAME, REFLOFFS) { (int)(intptr_t)&(REFLOFFS) & mType_ObjectJc, NAME, REFLOFFS }/*TODO*/
    #ifdef DEF_ObjectJc_REFLREF
      #define INIZsuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(REFLOFFS) & mType_ObjectJc, NAME, REFLOFFS, REFLSUPER }/*TODO*/
    #else 
      #define INIZsuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(REFLOFFS) & mType_ObjectJc, NAME, REFLOFFS }/*TODO*/
    #endif
  #else 
    #define INIZ_ClassJc(OBJ, NAME) { (int)(intptr_t)&(NAME), NAME}
    #ifdef DEF_ObjectJc_REFLREF
      #define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), NAME, REFLSUPER }
    #else 
      #define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), NAME }
    #endif
  #endif

#endif



#else
  #include <emC/Base/ClassJc_FullReflection_emC.h>
#endif






#endif //__objectBaseC__h__
