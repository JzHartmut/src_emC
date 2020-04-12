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


struct Size_Vtbl_t;


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

/** The default construtor. An offset to BlockHeap in mem is considered. */
inline ObjectJc* ctorM_ObjectJc(MemC mem) //ObjectJc* ythis);
{ init0_MemC(mem);   //A ctor should initialize all, no old data regarded. Cleanup!
  ObjectJc* thiz = PTR_MemC(mem, ObjectJc);
  int size = size_MemC(mem);
  init_ObjectJc(thiz, size, 0);
  return thiz;
}





/**The default construtor in C-manner. It assumes, that the area is cleared or is initialized already. 
 * @deprecated use init_ObjectJc() instead with the correct instance size
 */
inline void ctorc_ObjectJc(ObjectJc* thiz) {
  memset(thiz, 0, sizeof(ObjectJc));   //A ctor should initialize all, no old data regarded. Cleanup!
  init_ObjectJc(thiz, sizeof(ObjectJc), 0);
}






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


/**Sets the ident and size of an ObjectJc.
* The bit position of ident and size, and the bits to define which bits are using for ident and size [[mSizeBits_objectIdentSize_ObjectJc]]
* are calculated from given size and type.
* @param sizeObj The size which is valid for the memory-area, which is used from the derived whole instance.
* @param identObj any special ident. If 0, an automatically ident is built.
* @throws RuntimeException if the identObj and sizeObj are not matching. See Bits of [[class_ObjectJc_objectIdentSize]].
*/
extern_C void setSizeAndIdent_ObjectJc(ObjectJc* ythis, int sizeObj, int identObj);




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





/*@CLASS_C ObjectArrayJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Base data of an array.
* This type is used as base data of an user defined array. The array data followes directly
* in the user struct. The array data need not have ObjectJc as base.
* *ObjectJc object: The array base type based on Object. Reflection is useable for the whole array.
*int32 length: acual no of elements, in java it is the final public attribute length
*int16 sizeElement size of an element, this is the sizeof a pointer if it is a array of pointers.
*int16 mode: mode of operation, see enum Emode. Here is coding the no of elements in 1 block
and the using of pointers or not.

*/
typedef struct  ObjectArrayJc_t
{ //ARRAYJc
  /**Head struct, it contains especially the number of dimensions. */
  ObjectJc object;

  /**size of an element. If the element is a pointer, the sizeof is the sizeof the pointer. */
  int16 sizeElement;

  /**Rerserve Element. */
  int16 mode;
  #define mPointered_ObjectArrayJc 1
  //#define mDirect_ObjectArrayJc 2
  /**Up to 255 dimensions for an array. The arraylength of the element length depends from it. */
  #define mDimension_ObjectArrayJc 0xff00 
  #define kBitDimension_ObjectArrayJc 8 

  /**Nr of elements of the array. It may be greater than 65000. 
  * If the dimension of the array is >1, then there is an array of length here. */
  int32 length;

}ObjectArrayJc;

/** Constant definition of the head of any array
* @param TYPE the type of the elements, used in sizeof(TYPE) and in reflection##TYPE
* @param SIZE number of elements
*/
#define CONST_ObjectArrayJc(TYPE, SIZE, IDENT, REFLECTION, OWNADDR) \
  { CONST_ObjectJc(IDENT + sizeof(ObjectArrayJc) + (SIZE) * sizeof(TYPE), OWNADDR, REFLECTION), sizeof(TYPE), 1<<kBitDimension_ObjectArrayJc, SIZE }

#define INITIALIZER_ObjectArrayJc(TYPE, SIZE, IDENT, REFLECTION, OWNADDR) \
  { CONST_ObjectJc(IDENT + sizeof(ObjectArrayJc) + (SIZE) * sizeof(TYPE), OWNADDR, REFLECTION), sizeof(TYPE), 1<<kBitDimension_ObjectArrayJc, SIZE }



/**Initializer definition of an array based on ObjectArrayJc. The structure should have the following format:
* ,,struct { ObjectArrayJc head; Type data[100];} myArray 
* ,,    = { INIZ_ObjectArrayJc(myArray, 100, Type, &reflection_TYPE, 0) };
* @param NROF_ELEM number of elements
* @param TYPE the type of the elements, used for sizeof(TYPE)
* @param REFL_ELEM reflection class for the elements of the field.
* @param ID Object ident.
*/
#define INIZ_ObjectArrayJc(OBJ, NROF_ELEM, TYPE, REFL_ELEM, ID) \
  { INIZ_ObjectJc(OBJ, REFL_ELEM, ID | (mArray_objectIdentSize_ObjectJc >>16)), sizeof(TYPE), 1<<kBitDimension_ObjectArrayJc, NROF_ELEM }


extern_C void init_immediate_ObjectArrayJc(ObjectArrayJc* thiz, int nrofElements, int sizeElement, struct ClassJc_t const* refl_Elem, int idObj);


/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@DEFINE_C Arrays of standard types @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**ArraysOfStandardType: xxx
*/

/*NOTE: The #define int8_YREFDEF etc. are necessary if an automatic generated source use the same one. */
typedef struct int8_Y_t{ ObjectArrayJc head; int8 data[50]; } int8_Y;

typedef struct int16_Y_t{ ObjectArrayJc head; int16 data[50]; } int16_Y;
//TYPEDEF_AYJc(int16);

typedef struct int32_Y_t{ ObjectArrayJc head; int32 data[50]; } int32_Y;

typedef struct int64_Y_t{ ObjectArrayJc head; int64 data[50]; } int64_Y;

typedef struct float_Y_t{ ObjectArrayJc head; int64 data[50]; } float_Y;

typedef struct double_Y_t{ ObjectArrayJc head; int64 data[50]; } double_Y;

typedef struct bool_Y_t{ ObjectArrayJc head; bool data[50]; } bool_Y;

typedef struct char_Y_t{ ObjectArrayJc head; char data[50]; } char_Y;

typedef struct void_Y_t{ ObjectArrayJc head; void* data[50]; } void_Y;




//typedef struct StringJc_AY_t{ ObjectJc object; int32 length; int16 sizeElement; int16 mode; StringJc data[50]; } *StringJc_AY;
//typedef struct StringJc_AYREF_t{ ObjectJc object; int32 length; int16 sizeElement; int16 mode; StringJc data[50]; } *StringJc_AYREF;


METHOD_C void_Y* ctorO_AYJc(ObjectJc* othis, int sizeElement, int nrofElements);



/*@CLASS_C int8_ObjArray @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/** Array of direct adressed integer values with 8 bit.
* This may be a template to build users arrays:
* Copy it and replace 'int32' with the users type.
* If the users array is a array of pointers, the users type is such as 'Userclass*'
*/
typedef struct int8ARRAY_t
{ /** consist of the base data of the array*/
  ObjectArrayJc head;
  /** direct data followed immediately after the ObjectArrayJc.
  The size of the array given here is only a helper for debugging, the debugger
  shows the given number of value. The really value is held inside array.
  */
  int8 data[0x100];
}int8_ObjArray;

/** The constructor accepts also a null pointer (on error) and returns the pointer itself,
* necessary to use inside definition new_type
*/
METHOD_C int8_ObjArray* ctor_int8ARRAY(int8_ObjArray* ythis, int nrOfBytes);


/** Gets the sizeof of the instance with given nr of elements. It is a static-like method.
* @param SIZE number of elements
*/
#define sizeof_int8ARRAY(SIZE) (sizeof(ObjectArrayJc) + SIZE * sizeof(int32))

#define staticSize_int8ARRAY (sizeof(((int8_ObjArray*)(0x1000))->data) / sizeof(int8))

#define CONST_int8ARRAY(OBJP) { CONST_ObjectArrayJc(int8, 100, 0, REFLECTION_int8, OBJP->head), {0} }
//#define CONSTaddSize_int32ARRAY(OBJP, ADDSIZE) { CONST_ObjectArrayJc(int32, 100 + ADDSIZE, 0, REFLECTION_int32, (OBJP)->head), {0} }
#define CONSTaddSize_int8ARRAY(OBJP, ADDSIZE) { CONST_ObjectArrayJc(int8, 100 + ADDSIZE, 0, null, null), {0} }

#define reflection__ObjectJcpp reflection__ObjectJc


#if !defined(mBackRef_ObjectJc) 
//if enhanced references are used, the REF types have own reflection const.
//in this case they are dummies.
#define reflection_StringBufferJcREF reflection_StringBufferJc

#endif






/*@CLASS_C int32_ObjArray @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**Number of array elements of a instance definition of a int32_ObjArray.
* An int32_ObjArray with any desired number of elements may be created dynamically, the int32_ObjArray- Type
* is than used as a pointer type.
* But if an instance of int32_ObjArray is defined, the number of elements are fixed as defined in the struct.
* This macro returns the defined number of.
*/
#define instanceSize_int32ARRAY 100

/** Array of direct adressed integer values with 32 bit.
* This may be a template to build users arrays:
* Copy it and replace 'int32' with the users type.
* If the users array is a array of pointers, the users type is such as 'Userclass*'
*/
typedef struct int32ARRAY_t
{ /** consist of the base data of the array*/
  ObjectArrayJc head;
  /** direct data followed immediately after the ObjectArrayJc.
  The size of the array given here is only a helper for debugging, the debugger
  shows the given number of value. The really value is held inside array.
  */
  int32 data[instanceSize_int32ARRAY];
}int32_ObjArray;





/** The constructor accepts also a null pointer (on error) and returns the pointer itself,
* necessary to use inside definition new_type
*/
METHOD_C int32_ObjArray* ctor_int32ARRAY(int32_ObjArray* ythis, int nrOfBytes);

/** Gets the element with given Index. The element is the value itself, of type 'int32'*/
#define get_int32ARRAY(ARRAY,IX) (*(int32*)(get_i_ObjectArrayJc(&ARRAY->array, IX)))

/** Sets the element with given Index*/
#define set_int32ARRAY(ARRAY,IX, VAL) (*(int32*)(get_i_ObjectArrayJc(&ARRAY->head, IX)) = VAL)

/** Gets the sizeof of the instance with given nr of elements. It is a static-like method.
* @param SIZE number of elements
*/
#define sizeof_int32ARRAY(SIZE) (sizeof(ObjectArrayJc) + SIZE * sizeof(int32))

/** Create a new Instance with the given number of elements
* @param size number of elements
*/
//METHOD_C int32_ObjArray* new_Int32ARRAY(int size);

#define new_int32_ObjArray(SIZE) (ctor_int32ARRAY( (int32_ObjArray*)malloc(sizeof_int32ARRAY(SIZE)), SIZE ))



#define CONST_int32_ObjArray(OBJP, SIZE) { CONST_ObjectArrayJc(int32, SIZE, 0, REFLECTION_int32, &(OBJP)->head), {0} }

/*@ARRAY ObjectJcARRAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

//TYPEDEF_ARRAYJc(ObjectJc, 50)
typedef struct ObjectJcARRAY{ ObjectArrayJc head; ObjectJc* data[50]; }ObjectJcARRAY;


#ifndef DEF_REFLECTION_FULL

struct ClassJc_t;

/**Reflection for a simple system which does not contain reflection information for itself
* but uses the reflection instance for type detection
* and maybe for offsets of data members for the InspectorTargetProxy. 
* This type has different elements depending on compiler switch 
* * DEF_NO_StringJcCapabilities and: The does not contain a name
* * DEF_REFLECTION_OFFS only then contains a reference to the offset array
* * DEF_ObjectJc_REFLREF then contains a reference to one super class for type check. 
*/
typedef struct ClassJc_t
{
  int32 idType;   // sizeReflOffs;

  #ifndef DEF_NO_StringJcCapabilities
  char const* name;
  #endif

  #ifdef DEF_REFLECTION_OFFS
  /**The lo-part (16 bit) of the address of this element is used as type ident. */
  int32 const* reflOffs;
  #endif
  #ifdef DEF_ObjectJc_REFLREF
  struct ClassJc_t const* superClass;
  #endif
} ClassJc;

extern_C ClassJc const reflection_ClassJc;


/**There are some variants of the macro INIZ_ClassJc(OBJ, NAME, REFLOFFS) 
* and INIZsuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER)
* depending of the existing elements in ClassJc:
*/
#ifdef DEF_NO_StringJcCapabilities
#  define INIZtypeOnly_ClassJc(OBJ, NAME) { (int)(intptr_t)&(OBJ)}
#  define INIZ_ClassJc(OBJ, NAME) { (int)(intptr_t)&(OBJ)}
#  ifdef DEF_REFLECTION_OFFS
#    define INIZreflOffs_ClassJc(OBJ, NAME, REFLOFFS) { ((int32)(intptr_t)&(REFLOFFS)), REFLOFFS }
#    ifdef DEF_ObjectJc_REFLREF
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), null, REFLSUPER }
#      define INIZreflOffsSuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(REFLOFFS), REFLOFFS, REFLSUPER }/*TODO*/
#    else 
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), null}
#      define INIZreflOffsSuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(REFLOFFS), REFLOFFS }/*TODO*/
#    endif
#  else 
#    define INIZreflOffs_ClassJc(OBJ, NAME, REFLOFFS) { (int)(intptr_t)&(OBJ)}
#    ifdef DEF_ObjectJc_REFLREF
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), REFLSUPER }
#      define INIZreflOffsSuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(OBJ), REFLSUPER }
#    else 
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ) }
#      define INIZreflOffsSuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(OBJ) }
#    endif
#  endif
#else
#  define INIZtypeOnly_ClassJc(OBJ, NAME) { (int)(intptr_t)&(OBJ), NAME}
#  define INIZ_ClassJc(OBJ, NAME) { (int)(intptr_t)&(OBJ), NAME}
#  ifdef DEF_REFLECTION_OFFS
#    define INIZreflOffs_ClassJc(OBJ, NAME, REFLOFFS) { ((int32)(intptr_t)&(REFLOFFS)), NAME, REFLOFFS }
#    ifdef DEF_ObjectJc_REFLREF
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), NAME, null, REFLSUPER }
#      define INIZreflOffsSuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(REFLOFFS), NAME, REFLOFFS, REFLSUPER }/*TODO*/
#    else 
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), NAME, null }
#      define INIZreflOffsSuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(REFLOFFS), NAME, REFLOFFS }/*TODO*/
#    endif
#  else 
#    define INIZreflOffs_ClassJc(OBJ, NAME, REFLOFFS) { (int)(intptr_t)&(OBJ), NAME}
#    ifdef DEF_ObjectJc_REFLREF
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), NAME, REFLSUPER }
#      define INIZreflOffsSuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(OBJ), NAME, REFLSUPER }
#    else 
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { (int)(intptr_t)&(OBJ), NAME}
#      define INIZreflOffsSuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER) { (int)(intptr_t)&(OBJ), NAME }
#    endif
#  endif
#endif



#else
#include <emC/Base/ClassJc_FullReflection_emC.h>
#endif







#endif //__objectBaseC__h__

