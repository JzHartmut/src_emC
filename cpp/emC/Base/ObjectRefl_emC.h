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
 * 2019-10: Hartmut combined with DEF_ObjectSimple_emC
 * 2008-04-22: JcHartmut chg:The elements idSemaphore and idWaitingThread are combined to idSyncHandles.
 *                       New element offsetToHeapBlock, but not in use yet.
 * 2007-10-00: JcHartmut creation, dissolved from ObjectJc.h
 *
 ****************************************************************************/
#ifndef HGUARD_applstdef_emC
  #include <applstdef_emC.h>  //Note: define before include-guards because applstdef_emC,h may include this file too.
#endif

//The following include guard prevent twice include especially if applstdefJc.h includes this file already.
#if !defined(HGUARD_ObjectRefl_emC) && !defined(DEF_ObjectSimple_emC)  //in case of DEF_ObjectSimple_emC this file should not be used.
#define HGUARD_ObjectRefl_emC


#define DEF_ObjectJc_FULLCAPABILITY

#include <emC/Base/MemC_emC.h>


struct ThreadContext_emC_t;

struct ClassJc_t;


struct Size_Vtbl_t;







/*@CLASS_C ObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#define ObjectJc_t ObjectJc_T


#ifdef DEF_ObjectJc_LARGESIZE


/**Info about object identification and the size of the data.
 * This is a more sophisticated dispersion of bits for the ObjectJc::identSize
 * There are three informations in several bits:
*
* *bit 31: True then the instance is in run mode, 0: initialization not finished.
*
* *bit 30: set if the ObjectJc has only this 4 Byte identSize, else always 0
*
* *bit 29,28: Kind of the size information.
*
* *bit 28..24 or 27..20 or 27..16: 5, 8 or 12 bits to indicate the object (instance).
*
* *bit 23 or 19 or 15 to 0: 24, 20 or 16 bits for size of the instance.
*
* The size may be in range 0 to 65k for ''small'' Objects or to 1 MByte or 16 MByte for
* ''medium'' or ''large'' Objects. Bits 29,28 indicates this kind of designation.
*
* *If bit 29 is 1, it is a large object with up to 16 MByte, the sizeof-Bits are
* Bit 23..0. There are 5 Bits to differ user Objects, bit 28 to 24. The user may have
* upto 31 large Objects (instances) in one data focus or maybe in the whole software.
*
* *If bit 29, 28 is 01, it is a medium object with up to 1 MByte, the sizeof-Bits are
* Bit 19..0. There are 8 Bits to differ user Objects, bit 27 to 20. The user may have
* upto 255 medium Objects (instances) in one data focus or maybe in the whole software.
*
* *If bit 29, 28 is 00, it is a small object with up to 64 kByte, the sizeof-Bits are
* Bit 15..0. There are 12 Bits to differ user Objects, bit 27 to 16. The user may have
* upto 4095 medium Objects (instances) in one data focus or maybe in the whole software.
*
* The ObjectIdent-Bits may be 0, if no identification of the Object is used.
* The user should take the responsibility for this bits.
* The instance idents should be defined in user space.
* it may be non-ambigous for a whole user project or not,
* but it should be non-ambigous for every data set. It helps to identify data
* in a plain old data (POD) structure.
* The user can define this bits in a special definition as constants. This constants
* should contain the kind-of-size bits 29 and 28.
* The ObjectIdent-Bits are not contained in reflection information, this information is only getable here.
*
* The sizeof-Bits may be 0, if no sizeof information is necessarry. But this bits
* are usefull if some different objects are places in a memory space after another, and
* a memory evaluation may be processed. The memory evaluation can detect the type of the
* objects via Reflection. but it need not use this information. The sizeof information
* helps to skip from one Object to the followed.
* @see setSizeAndIdent_ObjectJc(...)
*/

/** The bits defines an ObjectArrayJc. If this bits are 0, it is not an ObjectArrayJc.*/
#define mArray_ObjectJc      0x40000000

/** The bits defines which mask is used to get the size.*/
#define mSizeBits_ObjectJc   0x30000000

/** If this value compared with ,,objectIdentSize & mSizeBits_ObjectJc,, is true,
* the size is stored in the bits of ,,mSizeSmall_ObjectJc...
* The bits mask with ,,mTypeMedium_ObjectJc,, are used for type info.
*/
#define kIsSmallSize_ObjectJc  0x00000000

/** If this value compared with ,,objectIdentSize & mSizeBits_ObjectJc,, is true,
* the size is stored in the bits of ,,mSizeMedium_ObjectJc...
* The bits mask with ,,mTypeMedium_ObjectJc,, are used for type info.
*/
#define kIsMediumSize_ObjectJc 0x10000000

/** If this bit is set, the size is stored in the bits of ,,mSizeLarge_ObjectJc,,.
* The bits mask with ,,mTypeLarge_ObjectJc,, are used for type info.
*/
#define mIsLargeSize_ObjectJc  0x20000000

/** Size bits for small objects, small means up to 64 kByte. There are 14 bits
* useable for 16383 small types.
*/
#define mSizeSmall_ObjectJc  0x0000ffff

/** This bits are used to store the type or instance info for small objects.
*/
#define mIdentSmall_ObjectJc  0x0fff0000

/** This constant is used to shift the type info for small objects. */
#define kBitIdentSmall_ObjectJc 16

/** Size bits for medium objects, medium means up to 1 MByte. There are 10 bits
* useable for 1023 medium types.
*/
#define mSizeMedium_ObjectJc 0x000fffff

/** This bits are used to store the type or size info for medium objects.
*/
#define mIdentMedium_ObjectJc 0x0ff00000

/** This constant is used to shift the type info for small objects. */
#define kBitIdentMedium_ObjectJc 20

/** Size bits for large objects up to 16 MByte.
*/
#define mSizeLarge_ObjectJc  0x00ffffff

/** This bits are used to store the type or instance info for large objects.
There are only 5 bits useable for 31 large instances.
*/
#define mIdentLarge_ObjectJc  0x1f000000

/** This constant is used to shift the type info for small objects. */
#define kBitIdentLarge_ObjectJc 24

#endif //DEF_ObjectJc_LARGESIZE
  




//Include some definitions from this file, it is used anyway. But its own Definition of ObjectJc is not used. 
#include <emC/Base/ObjectSimple_emC.h>


/*---------------------------------------------
  const Initialization                         */

/**Initializing of a simple object. 
 * Note: The CONST_ObjectJc macro is yet necessary for legacy code, Reflection. It is adequate INIZ_idSize_ObjectJc(...)
 * It is not proper for all cases. Deprecated! 
 */
#ifdef DEF_ObjectJcpp_REFLECTION
#  define INIZ_idSize_ObjectJc(OBJ, REFL, IDSIZE)  { (IDSIZE), 0,  kNoSyncHandles_ObjectJc, REFL }
#  define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { TYPESIZEOF, 0,  kNoSyncHandles_ObjectJc, REFLECTION }
#elif !defined(DEF_REFLECTION_NO)
  //Note: INIZ_ObjectJc(OBJ, REFL, ID)  defined in ObjectSimple_emC.h
  #define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { TYPESIZEOF, REFLECTION }
#else
  //already contained in ObjectSimple_emC, not DEF_REFLECTION_NO without DEF_ObjectJcpp_REFLECTION
#endif


#ifdef DEF_ObjectJc_LARGESIZE
  //The positions of the bits are controlled by mSizeBits_ObjectJc, more complex algorithm needs a subroutine.  
  uint getIdentInfo_ObjectJc ( ObjectJc const* ythis);
  uint getSizeInfo_ObjectJc ( ObjectJc const* ythis);
  uint getSizeData_ObjectJc ( ObjectJc const* ythis);
#endif





#if defined(__cplusplus) && defined(DEF_cplusplus_emC)



/** Superclass for class ObjectJcpp and especially for all interface classes.
This base class defines a method to convert this to ObjectJc const*
especially necessary for interface classes.<br/>
The methods of this class should be implemented in any class
implementing any interface.
*/
class  ObjectJcpp
{
  public: virtual ObjectJc const* toObject() = 0; //{ return null; }

                                          //#define toObject_Jc() toObject()

  /**returns true if the String given Type is the instance can derived immeditately 
   * to the given type with simple cast (C-cast). 
   * In Java there it is the operator instanceof
   * Note: It does not regard C++ deviation. Only able to use for the ObjectJc-C-inheritance.
   */
  public: bool instanceof(const char* type){ return true; }  //TODO instanceof_s_ObjectJc(toObject(), type); } 

  public: struct ClassJc_t* getClass(){ return null; }  //cannot be supported: getClass_ObjectJc(toObject()); }

                                                      /**The constructor is called automatically in C++. Because it is contained as inline
                                                      * in the header, the user don't need any other library to use it.
                                                      */
  public: ObjectJcpp(); //: significance_ObjectifcBase(123), significanceAddress_ObjectifcBase(null){}

  public: virtual ~ObjectJcpp(){}

};

#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)




/**Free an Object allocated with [[alloc_ObjectJc(...)]]. */
extern_C void free_ObjectJc(ObjectJc* thiz);


#define iniz_ObjectJc(THIZ, ADDR, SIZE, REFL, ID) ctor_ObjectJc(THIZ, ADDR, SIZE, REFL, ID)



  
  
  
/**Initialization of the basicly data of ObjectJc.
* This routine should be used only for C, not for C++. The offsetToStartAddr is not set correctly.
* Hence it is deprecated. Use [[ctor_ObjectJc(...)]] maybe with null for reflection argument.
* @param sizeObj The size of the whole instance, use sizeof(TypeInstance). All data are set to 0.
*                Don't use this kind of initialization for C++-classes, use sizeof(ObjectJc) for this argument than.
* @param identObj An identification info, see [[class_ObjectJc.objectIdentSize]] 
* @deprecated
* return thiz
*/
/*NOTE: don't use a void* instead ObjectJc const*, because a qualified casting have to be done using in C++ from inheriting classes. */
extern_C ObjectJc const* init_ObjectJc ( ObjectJc* thiz, int sizeObj, int identObj);


/** The default construtor. An offset to BlockHeap in mem is considered. */
inline ObjectJc const* ctorM_ObjectJc(MemC mem, struct ClassJc_t const* refl, int id) //ObjectJc const* ythis);
{ init0_MemC(mem);   //A ctor should initialize all, no old data regarded. Cleanup!
  ObjectJc* thiz = PTR_MemC(mem, ObjectJc);
  int size = size_MemC(mem);
  #ifndef NO_PARSE_ZbnfCheader
  #ifndef DEF_REFLECTION_NO
    ctor_ObjectJc(thiz, thiz, size, refl, id);
  #else
    ctor_ObjectJc(thiz, thiz, size, null, id);
  #endif
  #endif//NO_PARSE_ZbnfCheader
  return thiz;
}





/**The default construtor in C-manner. It assumes, that the area is cleared or is initialized already. 
 * @deprecated use ctor_ObjectJc() instead with the correct instance size
 */
inline void ctorc_ObjectJc(ObjectJc* thiz) { //, struct ClassJc_t const* refl, int id) {
  memset(thiz, 0, sizeof(ObjectJc));   //A ctor should initialize all, no old data regarded. Cleanup!
  ctor_ObjectJc(thiz, thiz, sizeof(ObjectJc), null, 0); //refl, id);
}










/**Checks the consistence or init, 
* @deprecated, use [[checkInit_ObjectJc(...)]] with a more significant name.
*/
#define checkConsistence_ObjectJc(THIS, SIZE, REFL, THCXT) checkInit_ObjectJc(THIS, SIZE, REFL, 0)
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
inline MemC getMemC_ObjectJc(ObjectJc const* thiz){ MemC ret; SET_MemC(ret, thiz, getSizeInfo_ObjectJc(thiz)); return ret; } 






/**tests wether the given object is an instance of the requested Type.
* Javalike: instanceof-operator.
* @param thiz any Object null is admissible then returns false. If the reflection are faulty, an exception is thrown.
* @param reflection The reflection of the type to compare. The chararcter sequence is tested.
* In opposite to [[instanceof_ObjectJc(...)]] they may be more as one reflection instance possible.
* That is especially in dll libraries with static linked reflection.
*/
extern_C bool instanceof_s_ObjectJc(ObjectJc const* ythis, char const* reflection);




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


/**Initializer definition of an array based on ObjectArrayJc. The structure should have the following format:
* ,,struct { ObjectArrayJc head; Type data[100];} myArray 
* ,,    = { INIZ_ObjectArrayJc(myArray, 100, Type, refl_TYPE, 0) };
* @param NROF_ELEM number of elements
* @param TYPE the type of the elements, used for sizeof(TYPE)
* @param REFL_ELEM reflection class for the elements of the field.
* @param ID Object ident.
*/
#define INIZ_ObjectArrayJc(OBJ, NROF_ELEM, TYPE, REFL_ELEM, ID) \
  { INIZ_ObjectJc(OBJ, REFL_ELEM, (ID) | mArrayId_ObjectJc ), sizeof(TYPE), 1<<kBitDimension_ObjectArrayJc, NROF_ELEM }
//old:{ INIZ_ObjectJc(OBJ, REFL_ELEM, ID | (mArray_ObjectJc >>16)), sizeof(TYPE), 1<<kBitDimension_ObjectArrayJc, NROF_ELEM }


/**Initializer definition of an array with primitive data based on ObjectArrayJc. The structure should have the following format:
* ,,struct { ObjectArrayJc head; Type data[100];} myArray 
* ,,    = { INIZ_ObjectArrayJc(myArray, 100, Type, REFLECTION_int32, 0) };
* @param NROF_ELEM number of elements
* @param TYPE the type of the elements, used for sizeof(TYPE)
* @param REFL_ELEM reflection class reference for the elements of the field.
* @param ID Object ident.
*/
#define INIZ_ReflRef_ObjectArrayJc(OBJ, NROF_ELEM, TYPE, REFL_ELEM, ID) \
  { INIZ_ReflRef_ObjectJc(OBJ, REFL_ELEM, (ID) | mArrayId_ObjectJc ), sizeof(TYPE), 1<<kBitDimension_ObjectArrayJc, NROF_ELEM }




/** Constant definition of the head of any array
 * @param TYPE the type of the elements, used in sizeof(TYPE) and in reflection##TYPE
 * @param SIZE number of elements
 * @deprecated, use INIZ_ObjectArrayJc(...). This macro does not initialize the reflection of the element
 *              because it should be given as identifier, not with null.
 *              Most of the usages are invoked with null for REFL_ELEM then this macro is ok. 
 *              All initializations with given type of element reflection should use INIZ_ObjectArrayJc(...)
 */
#define CONST_ObjectArrayJc(TYPE, NROF_ELEM, ID, REFL_ELEM, OBJ) \
  { CONST_ObjectJc((ID) | mArrayId_ObjectJc, OBJ, &refl_ObjectJc ), sizeof(TYPE), 1<<kBitDimension_ObjectArrayJc, NROF_ELEM }





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


METHOD_C void_Y* ctorO_AYJc(ObjectJc const* othis, int sizeElement, int nrofElements);



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

#define refl__ObjectJcpp refl__ObjectJc


#if !defined(mBackRef_ObjectJc) 
//if enhanced references are used, the REF types have own reflection const.
//in this case they are dummies.
#define refl_StringBufferJcREF refl_StringBufferJc

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
typedef struct ObjectJcARRAY{ ObjectArrayJc head; ObjectJc const* data[50]; }ObjectJcARRAY;


#ifdef DEF_ClassJc_Vtbl
#include <emC/Base/ObjectJcVtbl_emC.h>
#endif






#ifdef DEF_REFLECTION_FULL  
  #include <emC/Base/ClassJc_FullReflection_emC.h>
#endif //DEF_REFLECTION_FULL







#endif //HGUARD_ObjectRefl_emC

