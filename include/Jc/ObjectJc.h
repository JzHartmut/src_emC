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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 * @content This file defines basicly properties of each data like java.lang.Object.
 *
 * @author Hartmut Schorrig www.vishia.org
 * @version 0.94
 * list of changes:
 * 2010-11-13: Hartmut: ObjectArrayJc, change the order of elements, length as second. It is prepared for multi-dimension arrays.
 * 2009-11-25: Hartmut
 *   new: getRestBlock_ObjectJc(...) to improve usage of Blockheap if possible.
 *   chg: wait_ObjectJc(...), notify_ObjectJc(...) with ThreadContext as last argument.
 *   chg: activateGarbageCollectorAccess_BlockHeapJc(...) has 2. argument EXCLOBJ, here only for empty definiition while using without Blockheap.
 * 2009-06-14: Hartmut new: newIdent_ObjectJc() declared.
 * 2008-04-22: JcHartmut docu
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#include <applstdefJc.h>  //Note: define before include-guards because applstdefJc,h may include this file too.
//The following include guard prevent twice include especially if appöstdefJc.h includes this file already.
#ifndef __ObjectJc_h__
#define __ObjectJc_h__

#include "Fwc/fw_SimpleC.h"
#include "Fwc/fw_MemC.h"
#include "Fwc/fw_Exception.h"  //knowledge of Thcxt, Exception is supplied
#include "Fwc/objectBaseC.h"
#include "Fwc/fw_String.h"


/*@CLASS_C ObjectJc_ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**ObjectJc_: This division in the headerfile <Jc/ObjectJc.h> contains the definitions of [[class_ObjectJc]]
 * whith deeper pure ObjectJc-concepts.
 */

//NOTE: the Definition of the struct is containing in objectBaseC.h



/** The default construtor. An offset to BlockHeap in mem is considered. */
METHOD_C ObjectJc* ctorM_ObjectJc(MemC mem); //ObjectJc* ythis);
#define ctor_ObjectJc(MEM) ctorM_ObjectJc(MEM)

/**The default construtor in C-manner. It assumes, that the area is cleared or is initialized already. 
 * @deprecated use init_ObjectJc() instead
 */
METHOD_C void ctorc_ObjectJc(ObjectJc* ythis);

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
METHOD_C ObjectJc* alloc_ObjectJc(const int size, const int32 typeInstanceIdent, ThCxt* _thCxt);


/**Freeze an Object allocated with [[alloc_ObjectJc(...)]]. */
METHOD_C void free_ObjectJc(ObjectJc* thiz);


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
METHOD_C void activateGC_ObjectJc(void const* object, void const* exclObject, ThCxt* _thCxt);



/**Finishes the startup phase and sets the run mode.
 * 
 */
METHOD_C int setRunMode_ObjectJc(ThCxt* _thCxt);



/**Tests wether it is an ObjectJc-based instance or not. The criterium is, the ownAddress inside ObjectJc must be identical with the instance address.
 * @throws an exception if it is not true.
 * @deprecated
 */
#define XXXtestConsistence_ObjectJc(SRC) { if( (SRC) != null && (SRC) != (SRC)->ownAddress ) THROW(RuntimeException, "no ObjectJc-based instance.", (int)(SRC)); }



/**Supplies the rest of block if the Object is allocated in a block heap, or an empty MemC if there is no rest space. 
 * @param size The requested size (>0) or the requested number of references (<0). 
 *        If < 0 then the available size is returned, where the given number of references is considered (this value negative).
 * @return A MemC-information which is placed immediate after the Object, or this size_MemC(returnObject) is 0.
 * The implementation of this method depends from a BlockHeap-Concept and is located there.
 */
METHOD_C MemC getRestBlock_ObjectJc(ObjectJc* ythis, int size, ThCxt* _thCxt);

/**tests wether the given object is an instance of the requested Type.
 * Javalike: instanceof-operator.
 * @param ythis any Object
 * @param reflection The reflection of the type to compare.
 */
METHOD_C bool instanceof_ObjectJc(ObjectJc const* ythis, struct ClassJc_t const* reflection);

//The null pointer may be tested outside, or it should cause an exception outside if it is unexpected.
METHOD_C MtblHeadJc const* checkMtbl_ObjectJc(ObjectJc const* ythis, int ix, char const* sign, ThCxt* _thCxt);



/**********************************************************************************************
 * Methods for thread synchronization
 */


/**The synchronized(obj) keyword from Java. */
METHOD_C void synchronized(ObjectJc* obj);

/**New identifier, better associated to ObjectJc (there are global link labels! 
 * Note the original identifier isn't changed yet, because some libraries use it.
 */
#define synchronized_ObjectJc synchronized   
#define endSynchronized_ObjectJc synchronizedEnd   

/**The synchronizedEnd-Methode should be called on end of a synchronized block.
 * write:
 * ,,  synchronized(obj);
 * ,,  { //critical section
 * ,,  }synchronizedEnd(obj);
 */
METHOD_C void synchronizedEnd(ObjectJc* obj);

/**The wait method, see java.lang.Object.wait(long),
 * In opposite to original Java, the millisecond arg is 32 bit, so the max wait time is limited to about 24 days.
 */
METHOD_C void wait_ObjectJc(ObjectJc* obj, int milliseconds, ThCxt* _thCxt);


/**The notify method, see java.lang.Object.wait(long),
 */
METHOD_C void notify_ObjectJc(ObjectJc* obj, ThCxt* _thCxt);

/**The notifyAll method, see java.lang.Object.wait(long),
 */
METHOD_C void notifyAll_ObjectJc(ObjectJc* obj, ThCxt* _thCxt);



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


extern_C const struct ClassJc_t reflection_ObjectArrayJc;

/** initializes the data of the array. This includes the head and the associated data. It is the rule or law,
 *  that all data are disposed immediately after the head of array. The data are set to 0.
 *
 *  @param ythis The head of the array.
 *  @param size  The number of elements of the 1-dimensional array
 *  @param nBytesPerElement sizeof(ElementType)
 *  @param reflection The reflection definition
 *  @param typeInstanceIdent The Type or Instance Id without size information but with the kind of size information, see kIsMediumSize_objectIdentSize_ObjectJc.
 *
 */
METHOD_C ObjectArrayJc* ctorc_ObjectArrayJc(ObjectArrayJc* ythis, int size, int nBytesPerElement, struct ClassJc_t const* REFLECTION, int32 typeInstanceIdent);
#define ctor_ObjectArrayJc(YTHIS, SIZE, BYTESPERELEMENT, REFLECTION, IDENT) ctorc_ObjectArrayJc(YTHIS, SIZE, BYTESPERELEMENT, REFLECTION, IDENT) 

/**initializes a ObjectArrayJc, see [[ctorc_ObjectArrayJc(...)]].
 * @param rawMem raw memory area, it may be uninitialized. 
 *        The size may be greater as necessary. The constructor initializes only its own area.
 * @throws IllegalArgumentException if the sizeof rawMem is to less.  
 */
METHOD_C ObjectArrayJc* ctorM_ObjectArrayJc(MemC rawMem, int size, int nBytesPerElement, struct ClassJc_t const* REFLECTION, int32 typeInstanceIdent);


/**initializes a ObjectArrayJc, see [[ctorc_ObjectArrayJc(...)]].
 * @param rawMem raw memory area, it may be uninitialized. 
 *        The size may be greater as necessary. The constructor initializes only its own area.
 * @throws IllegalArgumentException if the sizeof rawMem is to less.  
 */
METHOD_C ObjectArrayJc* ctorO_ObjectArrayJc(ObjectJc* objthis, int size, int nBytesPerElement, struct ClassJc_t const* REFLECTION, int32 typeInstanceIdent);




/**creates an new Array of any desired struct type. The memory for the array is allocated, all elements are setted to 0,
 * and the ObjectArray-Head-Structure is initialized.
 * Do not use this method to create an array of a C++ class, because there constructors are not called
 * and no virtual-table-pointer are initialized.
 * @param size Number of elements of the 1-dimensional array.
 * @param bytesPerElement This value should be written as ,,sizeof(ElementType),,.
 * @param reflection The reflection class of the elements. Note: The elements need not have ObjectJc as baseclass.
 *        The access to reflection info is possible via the array head.
 * @param typeInstanceIdent It may be 0. If the data are evaluate in a POD plain old data data image,
 *        the value may be important. See element ,,objectIdentSize,, in ,,ObjectJc,,.
 *        But here only the ident bits, not the size should be given.
 * @param STACKTRCP My be null, if no memory allocation error is expected.
 * @return The pointer of the allocated data as reference to ObjectArrayJc. A casting outside is necessary, see macro new_ARRAYJc.
 * @throws RuntimeException if no memory is allocatable.
 */
METHOD_C ObjectArrayJc* new_ObjectArrayJc(int size, int bytesPerElement, struct ClassJc_t const* reflection, int32 typeInstanceIdent);


#define free_ObjectArrayJc(THIZ){ free_ObjectJc(&(THIZ)->object); }


/**returns the address of the first element of the array. The type depends on the derived declaration. 
 * Therefore it is untyped here. 
 * @param size pointer to a int-variable to return the size of the whole array inclusive the head.  
 *             If this pointer is null, the size isn't returned.
 */
METHOD_C MemUnit* getAddrSizeof_ObjectArrayJc(ObjectArrayJc* ythis, int32* size);


/**Builds a MemC struct and returns it per value.
 * This is a helper method to supply a MemC argument in a method call.
 */
METHOD_C MemC buildFromArrayX_MemC(ObjectArrayJc* objArray);


/**Gets the pointer to an element in the data area of the array, indexed by idx.
   This method returns a non constant untyped pointer. The user should cast it to the correct type.
   To do so, the definition of an access macro is recommended in a users header.
 */
METHOD_C void* get_i_ObjectArrayJc(ObjectArrayJc const* ythis, int idx);

/** Gets the size of the array, it means number of elements of the array, not number of bytes.
  It is the content of element length. Because it is a simple access a define may be a possible implementation.
  An compiler-errormessage may be clear cut, if the user works with wrong argument BASE.
*/
#define size_ObjectArrayJc(BASE) ((BASE)->length)
//METHOD_C int size_ObjectArrayJc(const ObjectArrayJc* base);


/** Gets the number of bytes of the whole array calculated from the informations inside the head.
  */
METHOD_C int getNrofBytes_ObjectArrayJc(ObjectArrayJc const* ythis);
#define getNrOfBytes_ObjectArrayJc(THIS) getNrofBytes_ObjectArrayJc(THIS)


/**Macro to define the reflection of an array of any type, able to use in a C-File.
 * @param TYPE the type of the array elements.
 */
#define DEFINE_REFLECTION_ARRAYJc(TYPE) \
  extern struct ClassJc_t const reflection_##TYPE##_Y; \
  const struct Reflection_Fields_##TYPE##_Y_t{ ObjectArrayJc head; FieldJc data[2];} reflection_Fields_##TYPE##_Y = \
  { CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &reflection_Fields_##TYPE##_Y) \
  , { { "head", 0 , &reflection_ObjectArrayJc, 0, 0, 0, &reflection_##TYPE##_Y } \
    , { "data", 0 , &reflection_##TYPE, 0, 0, 0, &reflection_##TYPE##_Y } \
  } }; \
  const ClassJc reflection_##TYPE##_Y =\
  { CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_##TYPE##_Y, null) \
  , "Y", 0, sizeof(TYPE##_Y), (FieldJcArray const*)&reflection_Fields_##TYPE##_Y \
  }




/*@DEFINE ARRAYJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**ARRAYJc: Macros for definition of arrays.
 */


/**This macro helps to define user specific javalike array pointer. 
 * The structure of the user defined type follows the structure of ObjectArrayJc. 
 * But because a direct access to the element length should be ... 
 */
#define TYPEDEF_AYJc(TYPE) \
typedef struct TYPE##_Y_t{ ObjectJc object; int32 length; int16 sizeElement; int16 mode; TYPE data[50]; } *TYPE##_Y; \
typedef struct TYPE##_YREF_t{ ObjectRefValuesJc refbase; TYPE##_Y ref; } TYPE##_YREF

#define TYPEDEF_AYPJc(TYPE) \
typedef struct TYPE##_YP_t{ ObjectJc object; int32 length; int16 sizeElement; int16 mode; TYPE* data[50]; } *TYPE##_YP; \
typedef struct TYPE##_YPREF_t{ ObjectRefValuesJc refbase; TYPE##_YP ref; } TYPE##_YPREF


/**Macro to define a Object based array.
   syntactical using as type in form
   , typedef ARRAYJc(MyElementType, 23) MyArrayType;
   or
   , ARRAYJc(MyElementType, 23) myArrayData;
   It results as a definition in form:
   , struct { Object_ArrayJc head; TYPE data[SIZE]; }
   @param TYPE the type of the elements
   @param SIZE nr of elements to shown in the array type. Often the defined arraytype
          is used as pointer, in that cases the number of elements may not be identical
          with the number of elements defined here. Use new_ARRAYJc to get a instance.
   @return inappropriate, it is used like a type.
 */
//#define ARRAYJc(TYPE, SIZE) struct { ObjectJc object; int32 length; int16 sizeElement; int16 mode; TYPE data[SIZE]; }
//#define ARRAYJc(TYPE, SIZE) struct { ObjectArrayJc head; TYPE data[SIZE]; }


#define ctor_AYJc(OBJ, SIZE) { ctorc_ObjectJc(&(OBJ)->object); setIdentAndSize_ObjectJc(&(OBJ)->object, 0, sizeof_AYJc((OBJ)->data[0], SIZE)); (OBJ)->length = SIZE; (OBJ)->sizeElement = sizeof((OBJ)->data[0]); } 

/** Gets the reference of the addressed element of an array with any desired type.
  * This is a macro because the type is unknown here and kept from the users ARRAY
  * by macro expansion.
  * @param ARRAY instance of an array, must construct with "ObjectArrayJc head; Usertype data;"
  * @param IDX the index of the instance
  * @return the "left value" as C-syntax of the element.
  * @throws IndexOutOfBoundsException if the IDX is failed.
  *Note: 3thrd Parameter TYPE is necessary for universal use, especially THROWJc
  */
#define element_AYJc(ARRAY, IDX) \
  (  (IDX) < 0 || (IDX) >= (ARRAY)->length ? /*(TYPE)THROWJc(IndexOutOfBoundsExceptionJc, "", 0)*/ null :  &((ARRAY)->data[IDX]) )
#define element_ARRAYJc(ARRAY, IDX) \
  (  (IDX) < 0 || (IDX) >= (ARRAY)->head.length ? /*(TYPE)THROWJc(IndexOutOfBoundsExceptionJc, "", 0)*/ null :  &((ARRAY)->data[IDX]) )


  /** calculates the size of an array with ObjectArrayJc-Head in compiletime.
    * This is a macro because the type is given.
    * @param TYPE The type of the elements.
    * @param SIZE The number of the elements.
    * @return The number of bytes
    */
#define sizeof_AYJc(TYPE, SIZE) (sizeof(ObjectJc) + 2*sizeof(int32) + (SIZE) * sizeof(TYPE))
#define sizeof_ARRAYJc(TYPE, SIZE) (sizeof(ObjectArrayJc) + (SIZE) * sizeof(TYPE))


/**creates an new Array of the given struct type. The memory for the array is reserved, all elements are setted to 0,
 * and the ObjectArray-Head-Structure is initialized.
 * Do not use this method to create an array of a C++ class, because there constructors are not called
 * and no virtual-table-pointer are initialized.
 *
 * @param TYPE The type of the elements. It should be a struct type.
          It is used to calculate the sizeof(TYPE) for memory allocation and to cast the result pointer to the expected type.
 * @param SIZE Number of elements of the 1-dimensional array.
 * @param REFLECTION The reflection class of the elements. Note: The elements need not have ObjectJc as baseclass.
 *        The access to reflection info is possible via the array head.
 * @param IDENT It may be 0. If the data are evaluate in a POD plain old data data image,
 *        the value may be important. See element ,,objectIdentSize,, in ,,ObjectJc,,.
 *        But here only the ident bits, not the size should be given.
 * @return The pointer of the allocated data in the correct type reference.
 * @throws RuntimeException if no memory is allocatable. In the environment the STACKTRC_ENTRY("name") should be present.
 */
#define new_ARRAYJc(TYPE, SIZE, REFLECTION, IDENT) ((TYPE##Array*)(new_ObjectArrayJc(SIZE, sizeof(TYPE), REFLECTION, IDENT)))



/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@DEFINE_C EnhancedReferences @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**EnhancedReferences: Enhanced references contains the reference itself and an additional integer value. 
 * Any reference in a struct-type should be enhanced, if the platform should use them.
 * The enhanced references can be used to register all references. 
 * It supports garbage collection in any form.
 *
 * Because the usage of enhanced references may be ineffective on cheap 16-bit-controller,
 * there are defined platform-depending: 
 * The macro ,,REFTYPEDEF,, is containing in the headerfile <fw_Platform_conventions.h>.
 * The macro is used to define types which presents the enhanced reference for any struct type.
 *
 * The enhanced references are present in a given platform, independently of there usage
 * of any garbage collection algorithm. The methods defined for the usage of enhanced references
 * may be implemented with several algorithm depending on the garbage-collection or other
 * reference-management-software moduls.
 */

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
METHOD_C void setBackRefJc(void* reference, void const* instance);

/** Clears a reference in any reference management system.
 *  The reference itself will be not stored here, it should be done outside because better
 *  pointer type checking. A back reference to refbase is stored in the block of the heap,
 *  and the Index of this back reference is stored in refbase.
 *
 *  If src is not inside a block heap, a 0 value is setted to *refbase.
 *
 *  @ param reference address of the enhanced reference
 */
METHOD_C void clearBackRefJc(void* reference);



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


#define int8_YREFDEF
typedef TYPE_EnhancedRefJc(int8_Y);

#define int16_YREFDEF
typedef TYPE_EnhancedRefJc(int16_Y);
//TYPEDEF_AYJc(int16);

#define int32_YREFDEF
typedef TYPE_EnhancedRefJc(int32_Y);

#define int64_YREFDEF
typedef TYPE_EnhancedRefJc(int64_Y);

#define bool_YREFDEF
typedef TYPE_EnhancedRefJc(bool_Y);

#define char_YREFDEF
typedef TYPE_EnhancedRefJc(char_Y);

#define void_YREFDEF
typedef TYPE_EnhancedRefJc(void_Y);

#define ObjectJcREFDEF
typedef TYPE_EnhancedRefJc(ObjectJc);


#ifndef LogMessageFWREFDEF
//  #define LogMessageFWREFDEF
//  TYPE_EnhancedRefJc(LogMessageFW);
#endif




/*@CLASS_C int8ARRAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



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
}int8ARRAY;

/** The constructor accepts also a null pointer (on error) and returns the pointer itself,
  * necessary to use inside definition new_type
  */
METHOD_C int8ARRAY* ctor_int8ARRAY(int8ARRAY* ythis, int nrOfBytes);


/** Gets the sizeof of the instance with given nr of elements. It is a static-like method.
 * @param SIZE number of elements
*/
#define sizeof_int8ARRAY(SIZE) (sizeof(ObjectArrayJc) + SIZE * sizeof(int32))

#define staticSize_int8ARRAY (sizeof(((int8ARRAY*)(0x1000))->data) / sizeof(int8))

#define CONST_int8ARRAY(OBJP) { CONST_ObjectArrayJc(int8, 100, 0, REFLECTION_int8, OBJP->head), {0} }
//#define CONSTaddSize_int32ARRAY(OBJP, ADDSIZE) { CONST_ObjectArrayJc(int32, 100 + ADDSIZE, 0, REFLECTION_int32, (OBJP)->head), {0} }
#define CONSTaddSize_int8ARRAY(OBJP, ADDSIZE) { CONST_ObjectArrayJc(int8, 100 + ADDSIZE, 0, null, null), {0} }

/*@CLASS_C Int32ARRAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**Number of array elements of a instance definition of a int32ARRAY.
 * An int32ARRAY with any desired number of elements may be created dynamically, the int32ARRAY- Type
 * is than used as a pointer type.
 * But if an instance of int32ARRAY is defined, the number of elements are fixed as defined in the struct.
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
}int32ARRAY;





/** The constructor accepts also a null pointer (on error) and returns the pointer itself,
  * necessary to use inside definition new_type
  */
METHOD_C int32ARRAY* ctor_int32ARRAY(int32ARRAY* ythis, int nrOfBytes);

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
//METHOD_C Int32ARRAY* new_Int32ARRAY(int size);

#define new_int32ARRAY(SIZE) (ctor_int32ARRAY( (int32ARRAY*)malloc(sizeof_int32ARRAY(SIZE)), SIZE ))



#define CONST_int32ARRAY(OBJP, SIZE) { CONST_ObjectArrayJc(int32, SIZE, 0, REFLECTION_int32, &(OBJP)->head), {0} }

/*@ARRAY ObjectJcARRAY @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

//TYPEDEF_ARRAYJc(ObjectJc, 50)
typedef struct ObjectJcARRAY{ ObjectArrayJc head; ObjectJc* data[50]; }ObjectJcARRAY;




/*@DEFINE_C reflection_Types********************************************************************************************/


/**reflection_Types: External definitions of language standard types.
    Note: The types with postfix Jc are the same as in Java (int is 32 bit, long is 64 bit), the transformations from special c/c++-Types are made with define.
*/

#define reflection__uint64Jc reflection__longJc
#define reflection__int64Jc reflection__longJc
#define reflection__uint32Jc reflection__intJc
#define reflection__int32Jc reflection__intJc
#define reflection__uint16Jc reflection__shortJc
#define reflection__int16Jc reflection__shortJc
#define reflection__uint8Jc reflection__byteJc
#define reflection__int8Jc reflection__byteJc
//extern_C const struct Reflectionint_t{ ClassJc clazz; } reflectionint;

#define reflection_int16BigEndian reflection__shortJc
#define reflection_int32BigEndian reflection__intJc
#define reflection_floatBigEndian reflection__intJc  //don't use float, it is byte-order-changed!!!


#define reflection__uintJc reflection__intJc
#define reflection__boolJc reflection__booleanJc
//extern_C ClassJc reflection__booleanJc;

#define reflection__float32Jc reflection__floatJc
//extern_C const struct Reflectionfloat_t{ ClassJc clazz; } reflectionfloat;

extern_C const ClassJc reflection__longJc;
extern_C const ClassJc reflection__intJc;
extern_C const ClassJc reflection__shortJc;
extern_C const ClassJc reflection__byteJc;
extern_C const ClassJc reflection__booleanJc;
extern_C const ClassJc reflection__floatJc;
extern_C const ClassJc reflection__doubleJc;
extern_C const ClassJc reflection__charJc;
extern_C const ClassJc reflection__char16Jc;
extern_C const ClassJc reflection_bitfieldJc;

extern_C const ClassJc reflection_ObjectJc;
extern_C const ClassJc reflection_StringJc;
extern_C struct ClassJc_t const reflection_CharSeqJc;
extern_C const ClassJc reflection_ClassJc;
extern_C const ClassJc reflection_BlockHeapBlockJc;

extern_C const ClassJc reflection_OS_PtrValue;
#define reflection_MemC reflection_OS_PtrValue
#define reflection_MemSegmentJc reflection_OS_PtrValue


/** Reflection_void is a reflection definition for a void pointer.
 */
extern_C const ClassJc reflection__voidJc;
extern_C const ClassJc reflection__ObjectifcBaseJcpp;

#define reflection__ObjectArrayJc reflection__ObjectJc
#define reflection__StringJc reflection_StringJc
#define reflection__ClassJc reflection__ObjectJc
#define reflection__ObjectJcpp reflection__ObjectJc


#if !defined(mBackRef_ObjectJc) 
  //if enhanced references are used, the REF types have own reflection const.
  //in this case they are dummies.
  #define reflection_StringBufferJcREF reflection_StringBufferJc

#endif







/*@DEFINE_C IFC_IMPL_dataMETHOD1_ObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**IFC_IMPL_dataMETHOD1_ObjectJc: This macro helps to define the reflections and the method table for a given abstract class
 * which has the following definition in Java ...
 * ,,public abstract class TYPE
 * ,,{ @Java4C.SimpleRef public Object data;
 * ,,  public abstract void METHOD(...);
 * ,,}
 * It is a universal approach with one data reference to any data and one method whith a specific signature.
 * The given abstract class should be defined in C language usual with Java2C-translation or maybe manual written. 
 * Especially the definition of the structure
 * ,,typedef struct TYPE_t 
 * ,,{ union { ObjectJc object; } base; 
 * ,,  struct ObjectJc_t* data;   
 * ,,} TYPE_s;
 * and the method table
 * ,,extern const char sign_Mtbl_TYPE[]; //marker for methodTable check
 * ,,typedef struct Mtbl_TYPE_t
 * ,,{ MtblHeadJc head;
 * ,,  MT_METHOD_TYPE* METHOD;
 * ,,  Mtbl_ObjectJc ObjectJc;
 * ,,} Mtbl_TYPE;
 * should be given. Whereby ,,TYPE,, and ,,METHOD,, are any proper definitions. 
 * The ,,MT_METHOD_TYPE,, is the function-Type of the method which should be matched to the user defined method.
 * It is for example:
 * ,,typedef void MT_METHOD_TYPE(TYPE_s* thiz, int arg1, float arg2, ThCxt* _thCxt);
 *
 * The implementing method should be defined as simpe C method 
 * with the appropriate signature. Use this macro to define the reflection with method table which is used
 * as ''derived anonymous class'' (Java slang) based on the given TYPE. It is to deal with the overridden method.
 *
 * An instance of this can be defined then with
 * ,,TYPE_s myImpl = CONST_ObjectJc(0, &myImpl, &reflection_METHOD);
 * This type has the reflection with reference to the implementing method but the data of the struct definition.
 * 
 * The macro defines 2 const variable:
 * * mtbl_METHOD: The method table of the interface type with the given method.
 * * reflection_METHOD: Reflection for the given variable refers the mtbl_METHOD.
 *
 * All 2 generated variable are const, therefore assigned to a const segment by linking. There are static global,
 * therefore only a unique name in this compilation unit is necessary. Note that the reference of the variable
 * can be forwarding to other parts of code.
 *
 * @param TYPE Type name of the interface without suffix _s. It should be given: ,,struct TYPE_t{...}TYPE_s;
 * @param METHOD Only the name of the method which implements the only 1 interface method. 
 *    This METHOD name is used both as name for the Mtbl_ and Reflection. The METHOD should match to the method definiton
  
 * @since 2015-06-14. It is the concequently usage of ObjectJc overridden methods, prepared for C usage.  
 */
#define IFC_IMPL_dataMETHOD1_ObjectJc(TYPE, METHOD) \
Mtbl_##TYPE static const mtbl_##METHOD = \
{ { sign_Mtbl_##TYPE , (struct Size_Mtbl_t*)((0 +2) * sizeof(void*)) } \
, METHOD \
, { { sign_Mtbl_ObjectJc, (struct Size_Mtbl_t*)((5 +2) * sizeof(void*)) } \
  , clone_ObjectJc_F, equals_ObjectJc_F, finalize_ObjectJc_F, hashCode_ObjectJc_F \
  , toString_ObjectJc_F \
  } \
} /*, { signEnd_Mtbl_ObjectJc, null } }*/; \
\
\
extern_C struct ClassJc_t const reflection_##METHOD; \
static const struct Reflection_Fields_##METHOD_t  \
{ ObjectArrayJc head; FieldJc data[1]; } reflection_Fields_##METHOD = \
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_##METHOD) \
, { { "data" \
    , 0  \
    , &reflection_ObjectJc \
    , kReference_Modifier_reflectJc  \
    , (int16)((int32)(&((TYPE##_s*)(0x1000))->data) - (int32)(TYPE##_s*)0x1000) \
    , 0   \
    , &reflection_##METHOD \
    } \
} }; \
static const ClassJc reflection_##METHOD =  \
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJc, &reflection_ClassJc)  \
, #METHOD \
,  0  \
, sizeof(TYPE##_s) \
, (FieldJcArray const*)&reflection_Fields_##METHOD \
, null /*methods*/  \
, null /*superclasses */  \
, null  \
, 0     \
, &mtbl_##METHOD.head   \
};


//TODO check usage of existing fields:
//extern const struct Reflection_Fields_##TYPE##_s_t reflection_Fields_##TYPE##_s; \
//  , (FieldJcArray const*)&reflection_Fields_##TYPE##_s \


/*@CLASS_CPP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)


  /*=====================================================================================*/
  /* C++-version of Object, named ObjectJcpp */

  class ObjectJcpp;
  struct ClassJc_t;



  class ObjectBaseJcpp: public ObjectifcBaseJcpp //, public virtual ObjectBaseJc
  {

    /** The destructor. It should be virtual because the correct destructor
        for an instance by referencing the instance via a base class must be used.
    */
    public: virtual ~ObjectBaseJcpp(){}

    virtual StringJc toString()=0;

    virtual void finalize()=0;

    public: virtual ObjectJcpp* toObjectJcpp()=0;
    public: virtual ObjectJc* toObjectJc()=0;


  };

//  #endif
//  #endif
//  #endSBNF

  class  ObjectJcpp: public ObjectifcBaseJcpp, public ObjectJc
  {
    /** The data from the C-like class: */
    //private: ObjectJc objectdata;


    /** RuntimeHeap is the class to get Block in Heap on Runtime.
        The protected method finalize() should be accesable from Runtimeheap.
    */
    friend class RuntimeHeap;

    /** Access also to private attributes in reflection.
    */
    friend class Reflection__Object;


    /** default constructor with no reflection information. The reflection  pointer will be
        setted to Reflection__Object.
    */





   /**copy-constructor*/
    //Object(const Object&);


    /** Implements virtual method from Object__BaseJc. Because the method here
        is not virtual, no further overload can be done.<br/>
        The type conversion to Object* is required in baseclass (interface) Object__Base
        and is implemented here. It returns this. Note that the value of the this-pointer
        dependence on the inheritance structure. A this-pointer of type of an interface
        pointered exactly the virtual table of the interface, a this-pointer of a multiple
        inheranced base class pointered the part of the class represented this base class.
        It is not equal to the this-pointer to the instance itself, referenced with the
        instance-type pointer. The compiler adds or subtracts some adress differences.
    */
    //public: operator ObjectJcpp*(){ return this; }  //type conversion

    /** see java-documentation*/
    public: int hashCode() const;

    /** wake up one waiting thread if any threads called wait().
        It wakes up exactly one thread, but it is not defined which thread if several
        threads are waiting.
    */
    public: void notify();

    /** wake up all waiting thread if any threads called wait().
    */
    public: void notifyAll();

    /** to fall asleep the current thread. The Thread will be waked up
        either by calling notify on this object from another thread or if the time is expired.
        If the value of time is less 0, no timeout is used.
    */
    public: void wait(long nTime = -1);


    public: ObjectJcpp* clone() const;

    public: class ClassJcpp const* getClass() const;


    /** casting from Object* to String
    */
    //operator class String();
    //operator class String&();
    //operator class String*();




    /** substitue the java operator instanceof
    */
    public: bool instanceof( struct ClassJc_t const* reflection);

    /** compare to content of the instance, take the length in memory over reflection
    */
    public: virtual bool equals(ObjectJcpp const* obj) const
    {
      //return this == obj;
      return false; //toObjectJc() == obj;
    }

    //void synchronized(class ObjectJcpp* obj);

    //void synchronizedEnd(class ObjectJcpp* obj);


    /** In the runmode parentRef() is to be execute for all member references of a class.
     ** The runmode is to coordinate with the using of RuntimeHeap.
     ** parentRef() are necesserry for the garbage collector.
    */
    static bool isRunMode();





    /** setuseless is used instead of garbage collection in C++. If any application don't need this instance
        furtherly, it called setuseless(). The instance itself must clarify the conditions to delete or destroy it.
        Thats why the user should overwrite this method.<br/>
        The default manner is to delete the instance immediately.
    */
    public: virtual void setuseless(){ delete this; }

    /** delete__ called by garbage collector at last, to free system ressources*/
    public: void delete__();

    public: ObjectJcpp()
    { ObjectJc* ythis = static_cast<ObjectJc*>(this);
      init0p_MemC(ythis, sizeof(ObjectJc));  //note: ctorc don't initialze with 0.
      ctorc_ObjectJc(ythis); 
    }


    void setReflection(struct ClassJc_t const* reflection, int32 typeInstanceSizeIdent = 0)
    //{ setReflection_Object(&(this->objectdata), reflection);
    {
      setReflection_ObjectJc(static_cast<ObjectJc*>(this), reflection, typeInstanceSizeIdent);
    }


    //virtual StringJc toString(){ STACKTRC_ENTRY("ObjectJcpp::toString"); return toString_ObjectJc_F(static_cast<ObjectJc*>(this), _thCxt); }

    virtual void finalize(){}



    public: virtual ObjectJc* toObjectJc(){ return this;}
    public: virtual ObjectJcpp* toObjectJcpp(){ return this;}
  };

#endif  /*__CPLUSPLUSJcpp*/




/*@CLASS_C Thread_Jc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


METHOD_C void sleep_Thread_Jc(int32 milliseconds);



/*@CLASS_C MathJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef __MathJc_h__
	#include <Jc/MathJc.h>
#endif
/*@CLASS_C IntegerJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#define MAX_VALUE_IntegerJc 0x7FFFFFFF
#define MIN_VALUE_IntegerJc 0x80000000

/**Parses the string argument as a signed decimal integer. The characters in the text must all be decimal digits,
 * except that the first character may be an ASCII minus sign '-' ('\u002D') to indicate a negative value.
 * The resulting integer value is returned, exactly as if the argument and the radix 10 were given as arguments
 * to the parseInt(java.lang.String, int) method.
 * @param s String containing the int representation to be parsed
 * @return the integer value represented by the argument in decimal.
 * @throws NumberFormatException - if the text does not contain a parsable integer.
 * @javaLike
 */
METHOD_C int parseInt_radix_IntegerJc(StringJc src, int radix);


/**Parses the string argument as a signed decimal integer. The characters in the text must all be decimal digits,
 * except that the first character may be an ASCII minus sign '-' ('\u002D') to indicate a negative value.
 * The resulting integer value is returned, exactly as if the argument and the radix 10 were given as arguments
 * to the parseInt(java.lang.String, int) method.
 * @param s String containing the int representation to be parsed
 * @return the integer value represented by the argument in decimal.
 * @throws NumberFormatException - if the text does not contain a parsable integer.
 * @javaLike
 */
#define parseInt_IntegerJc(src) parseInt_radix_IntegerJc(src, 10)


/*@CLASS_C FloatJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

METHOD_C int32 floatToRawIntBits_FloatJc(float val);
METHOD_C int32 floatToIntBits_FloatJc(float val);



METHOD_C float intBitsToFloat_FloatJc(int32 val);

//#define intBitsToFloat_FloatJc(val) (*((float*)(&val)))

/**Parses the string argument as a signed decimal integer. The characters in the text must all be decimal digits,
 * except that the first character may be an ASCII minus sign '-' ('\u002D') to indicate a negative value.
 * The resulting integer value is returned, exactly as if the argument and the radix 10 were given as arguments
 * to the parseInt(java.lang.String, int) method.
 * @param s String containing the int representation to be parsed
 * @return the integer value represented by the argument in decimal.
 * @throws NumberFormatException - if the text does not contain a parsable integer.
 * @javaLike
 */
METHOD_C float parseFloat_FloatJc(StringJc src);

/*@CLASS_C DoubleJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

METHOD_C int64 doubleToRawLongBits_DoubleJc(double val);
METHOD_C int64 doubleToLongBits_DoubleJc(double val);

METHOD_C double longBitsToDouble_DoubleJc(int64 val);

/**Parses the string argument as a signed decimal integer. The characters in the text must all be decimal digits,
 * except that the first character may be an ASCII minus sign '-' ('\u002D') to indicate a negative value.
 * The resulting integer value is returned, exactly as if the argument and the radix 10 were given as arguments
 * to the parseInt(java.lang.String, int) method.
 * @param s String containing the int representation to be parsed
 * @return the integer value represented by the argument in decimal.
 * @throws NumberFormatException - if the text does not contain a parsable integer.
 * @javaLike
 */
METHOD_C double parseDouble_DoubleJc(StringJc src);




METHOD_C StringJc toString_F_FloatJc(float val);

METHOD_C StringJc toHexString_FloatJc(float val);

/*@CLASS_C ComparableJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct ComparableJc_t
{ struct { ObjectJc object;} base;
}ComparableJc;


/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Mtbl_ComparableJc_t
{ Mtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
} Mtbl_ComparableJc;

extern char const sign_Mtbl_ComparableJc[]; 

extern_C const struct ClassJc_t reflection_ComparableJc; 


/*@CLASS_C CloseableJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct CloseableJc_t
{ struct { ObjectJc object;} base;
}CloseableJc;

typedef bool MT_close_CloseableJc(ObjectJc* thiz, ThCxt* _thCxt);


/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Mtbl_CloseableJc_t
{ MtblHeadJc head;
  MT_close_CloseableJc* close;
  Mtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
} Mtbl_CloseableJc;

extern char const sign_Mtbl_CloseableJc[]; 

#define close_CloseableJc(THIZ, THCXT) ((Mtbl_CloseableJc*)getMtbl_ObjectJc((ObjectJc*)(THIZ), sign_Mtbl_CloseableJc))->close(THIZ, THCXT)

extern_C const struct ClassJc_t reflection_CloseableJc; 


/*@CLASS_C FlushableJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct FlushableJc_t
{ struct { ObjectJc object;} base;
} FlushableJc;

typedef void MT_flush_FlushableJc(ObjectJc* thiz, ThCxt* _thCxt);


/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Mtbl_FlushableJc_t
{ MtblHeadJc head;
  MT_flush_FlushableJc* flush;
  Mtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
} Mtbl_FlushableJc;

extern char const sign_Mtbl_FlushableJc[]; 

#define flush_FlushableJc(THIZ, THCXT) ((Mtbl_FlushableJc*)getMtbl_ObjectJc((ObjectJc*)(THIZ), sign_Mtbl_FlushableJc))->flush(THIZ, THCXT)


extern_C const struct ClassJc_t reflection_FlushableJc; 

/*@CLASS_C AppendableJc_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Interface Appendable.
 * NOTE: It is defined in the Headerfile ObjectJc.h because it is based on ObjectJc and its reflection are defined in ReflectionBaseTypesJc.c
 * which includes only ObjectJc. It is respected as base type.
 */
typedef struct AppendableJc_t
{ struct { ObjectJc object;} base;
}AppendableJc_s;


typedef AppendableJc_s* MT_append_C_AppendableJc(ObjectJc* thiz, char c, ThCxt* _thCxt);

typedef AppendableJc_s* MT_append_cs_AppendableJc(ObjectJc* thiz, CharSeqJc cs, ThCxt* _thCxt);

typedef AppendableJc_s* MT_append_csI_AppendableJc(ObjectJc* thiz, CharSeqJc cs, int from, int to, ThCxt* _thCxt);



/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Mtbl_AppendableJc_t
{ MtblHeadJc head;
  MT_append_C_AppendableJc* append_C;
  MT_append_cs_AppendableJc* append_cs;
  MT_append_csI_AppendableJc* append_csI;
  Mtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc


} Mtbl_AppendableJc;

extern char const sign_Mtbl_AppendableJc[]; 

extern_C const struct ClassJc_t reflection_AppendableJc; 

#define append_C_AppendableJc(THIZ, SRC, THCXT) ((Mtbl_AppendableJc*)getMtbl_ObjectJc((ObjectJc*)(THIZ), sign_Mtbl_AppendableJc))->append_C((ObjectJc*)(THIZ), SRC, THCXT)
#define append_cs_AppendableJc(THIZ, SRC, THCXT) ((Mtbl_AppendableJc*)getMtbl_ObjectJc((ObjectJc*)(THIZ), sign_Mtbl_AppendableJc))->append_cs((ObjectJc*)(THIZ), SRC, THCXT)
#define append_csI_AppendableJc(THIZ, SRC, FROM, TO, THCXT) ((Mtbl_AppendableJc*)getMtbl_ObjectJc((ObjectJc*)(THIZ), sign_Mtbl_AppendableJc))->append_csI((ObjectJc*)(THIZ), SRC, FROM, TO, THCXT)


/*@DEFINE_C Inlines @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Inlines: inline definitions which uses definitions above. On end of header.*/

MtblHeadJc const* checkMtblError_ObjectJc(ObjectJc const* ythis, int error, ThCxt* _thCxt);

INLINE_Fwc MtblHeadJc const* checkMtbl_ObjectJc(ObjectJc const* ythis, int ix, char const* sign, ThCxt* _thCxt)
{ ClassJc const* reflection = ythis->reflectionClass;
  if( reflection != null || reflection->object.reflectionClass == &reflection_ClassJc) {
    MtblHeadJc const* head0, *head;
    head0 = ythis->reflectionClass->mtbl;  
    if(head0 != null){
      head = (MtblHeadJc const*)(((MemUnit const*) (head0)) + ix * sizeof(head0->sign)); 
      if(head->sign == sign) {
        return head;
      } else return checkMtblError_ObjectJc(ythis, 3, _thCxt);
    } else return checkMtblError_ObjectJc(ythis, 2, _thCxt);
  } else return checkMtblError_ObjectJc(ythis, 1, _thCxt);
}





/**It should able to work with Stacktrace. */


//#include "Fwc/fw_LogMessage.h"
//#include "Fwc/fw_Formatter.h"

#endif //__ObjectJc_h__
