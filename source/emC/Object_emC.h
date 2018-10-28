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
 * @content This file defines only the struct ObjectJc_t and the base interface ObjectifcBaseJcpp.
 * It is the minimal base for some struct or interface of the framework layer,
 * which should also be designable without knowledge of the Jc-layer, 
 * but useable outside of the users algorithm if necessary with ReflectionJc-concept.
 *
 * @author Hartmut Schorrig
 * @version 0.83
 * list of changes:
 * 2008-04-22: JcHartmut chg:The elements idSemaphore and idWaitingThread are combined to idSyncHandles.
 *                       New element offsetToHeapBlock, but not in use yet.
 * 2007-10-00: JcHartmut creation, dissolved from ObjectJc.h
 *
 ****************************************************************************/
#include <applstdef_emC.h>  //Note: define before include-guards because applstdef_emC,h may include this file too.
//The following include guard prevent twice include especially if appöstdefJc.h includes this file already.
#ifndef __objectBaseC__h__
#define __objectBaseC__h__

#include <emC/MemC_emC.h>


struct ThreadContext_emC_t;

/**This file defines only the struct Object_Jc_t and the base interface ObjectifcBase_Jcpp.
   It is the minimal base for some struct or interface 
   which should be designable without knowledge of the CRuntimeJavalike concept.
   This Header should be included while using the CRuntimeJavalike concept
   but a surrogating other header which define these two elements in a other way may be used otherwise.
 */


struct Size_Mtbl_t;


#ifndef __StringJc_defined__
  //minimalistic definition of StringJc to use this type before including emC/StringJc
  typedef OS_PtrVal_DEF(StringJc, char const);
  #define __StringJc_defined__
#endif //ifdef isNull_StringJc



#ifndef __ObjectJc_defined__
  //prevent this definition if any other struct for ObjectJc is defined already - for a simple target.
/**8 Byte for size, offs to start, idSync etc.
 * Note: Any struct or union for maybe 64 bit system should be aligned to 8 Byte!
 */
typedef union State_ObjectJc_t
{
  #define ixOffsId_State_Object 1
  #define kBit_idSyncHandles_State_ObjectJc 16
  #define m_idSyncHandles_State_ObjectJc 0x0fff0000

  struct {  //NOTE: firstly the struct with named elements because INITIALIZER_ObjectJc. An { value ,...} uses the first union elements.
    
    /**Info about object identification and the size of the data.
     * There are three informations in several bits:
     *
     * *bit 31,30: Indication wether it is a array (type ObjectArrayJc, max. 3-dimensional).
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
     */

    /** The bits defines an ObjectArrayJc. If this bits are 0, it is not an ObjectArrayJc.*/
    #define mArray_objectIdentSize_ObjectJc      0x40000000
    
    /** The bits defines which mask is used to get the size.*/
    #define mSizeBits_objectIdentSize_ObjectJc   0x30000000

    /** If this value compared with ,,objectIdentSize & mSizeBits_objectIdentSize_ObjectJc,, is true,
      * the size is stored in the bits of ,,mSizeSmall_objectIdentSize_ObjectJc...
      * The bits mask with ,,mTypeMedium_objectIdentSize_ObjectJc,, are used for type info.
      */
    #define kIsSmallSize_objectIdentSize_ObjectJc  0x00000000

    /** If this value compared with ,,objectIdentSize & mSizeBits_objectIdentSize_ObjectJc,, is true,
      * the size is stored in the bits of ,,mSizeMedium_objectIdentSize_ObjectJc...
      * The bits mask with ,,mTypeMedium_objectIdentSize_ObjectJc,, are used for type info.
      */
    #define kIsMediumSize_objectIdentSize_ObjectJc 0x10000000

    /** If this bit is set, the size is stored in the bits of ,,mSizeLarge_objectIdentSize_ObjectJc,,.
      * The bits mask with ,,mTypeLarge_objectIdentSize_ObjectJc,, are used for type info.
      */
    #define mIsLargeSize_objectIdentSize_ObjectJc  0x20000000

    /** Size bits for small objects, small means up to 64 kByte. There are 14 bits
      * useable for 16383 small types.
      */
    #define mSizeSmall_objectIdentSize_ObjectJc  0x0000ffff

    /** This bits are used to store the type or instance info for small objects.
      */
    #define mTypeSmall_objectIdentSize_ObjectJc  0x0fff0000

    /** This constant is used to shift the type info for small objects. */
    #define kBitTypeSmall_objectIdentSize_ObjectJc 16

    /** Size bits for medium objects, medium means up to 1 MByte. There are 10 bits
      * useable for 1023 medium types.
      */
    #define mSizeMedium_objectIdentSize_ObjectJc 0x000fffff

    /** This bits are used to store the type or size info for medium objects.
      */
    #define mTypeMedium_objectIdentSize_ObjectJc 0x0ff00000

    /** This constant is used to shift the type info for small objects. */
    #define kBitTypeMedium_objectIdentSize_ObjectJc 20

    /** Size bits for large objects up to 16 MByte.
      */
    #define mSizeLarge_objectIdentSize_ObjectJc  0x00ffffff

    /** This bits are used to store the type or instance info for large objects.
        There are only 5 bits useable for 31 large instances.
      */
    #define mTypeLarge_objectIdentSize_ObjectJc  0x1f000000

    /** This constant is used to shift the type info for small objects. */
    #define kBitTypeLarge_objectIdentSize_ObjectJc 24

    int32 objectIdentSize;
    
    /**Posive value of offset to the beginn of block, able to use debugging data manually. 
     * If this Object is part of a BlockHeapBlockJc, bit 15 is set, but the rest is the positive offset to start of heap block.
     * 
     */
    int offsetToStartAddr :16;

    /** identification number for wait/notify and synchronized.
     *  Because most of ObjectJc are not used for synchronized or wait/notify,
     *  the necessary handles for that are stored in a separate struct located in an separate memory space
     *  defined in os_wrapper.c.
     *  Here only the 12 bit for a id are offered.
     */
    int idSyncHandles :12;

    #define kNoSyncHandles_ObjectJc -1

    /**Up to 7 handles (number) for memory management. 
     * The operation system should support the access to the correct instance. 
     */
    int memoryMng :3;


    /**Bit to check whether the initializing is complete. 
     * This bit is not existing in Java. For such problems in java a special boolean variable is necessary.
     * This bit should be set to 1 in a users routine if all aggregations are set. Aggregations (UML) are that references
     * which are necessary to execute all capabilities of the class.  
     */
    int isInitialized :1;

    //always: #if defined(mBackRef_ObjectJc)
    /** Pointer to a memory management, which manages this object. old: the BlockHeapBlock-Control-structure, 
     */
    //struct ObjectJc_t* memoryMng;
    //#endif
  } b;

  /**Representation as int32 */
  int32 _w[2];

} State_ObjectJc;





/*@CLASS_C ObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

  /**Object is the superclass of all superclasses. In C-like manner it is a struct
   * at begin of any class-like struct.
   *
   * The headerfile <emC/Object_emC.h> contains the definition of this ,,struct ObjectJc,, for common usage in C-Sources
   * which does not use concepts of ,,ObjectJc,, but should know this embedded struct. 
   * Some definitions and methods are common use-able, that methods are contained here too. 
   * @since 2016-12: The struct is changed, but the number of bytes are held identically. They are 24 Byte or 3 8-Byte-words.
   * Because 64 bit technology :
   * * pointers are 64 bit on pc, use union for own Address.
   * * instead memoryMng - pointer store a handle, 16 or 8 bit are enough, yet 32 bit.
   * * dummy for further using is removed.
   * * notice 64-bit-alignment. 
   */
  typedef struct  ObjectJc_t
  {

    /**The own address of the instance saved in the instance itself. This value may be important
     * if the data are transmitted in an other system (evaluation of data)
     * and some references between data are present. The evaluator may be able to found
     * the correct association between the instances by testing this value.
     * NOTE: It is a unnamed union to support 64 bit pointers if the data are transferred and the address should be adapted.
     */
    union { struct ObjectJc_t* ownAddress; int32 ownAddress_i[2]; };

    /** The info about this type of the object. The Java-like reflection-concept is used.
     * NOTE: It is a union to support 64 bit pointers if the data are transferred and the address should be adapted.
    */
    union { struct ClassJc_t const* reflectionClass; int32 reflectionClass_i[2]; };


    /**Use int64 image for Simulink Busses. */
    State_ObjectJc state;



  }ObjectJc;

/**Compatibility: */
#define Object_Jc_t ObjectJc_t


/**Allocates an ObjectJc in the thread buffer. Such an instance must be used immediately, then it is similar to an embedded instance in the stack. 
 * It can be returned and used in the calling enviroment immediately or return. That is the difference to a embedded instance in the stack.
 * Only one instance can be located in the thread context. It is over-written if another instance is created in the thread context.
 */
ObjectJc* allocInThreadCxt_ObjectJc(int size, char const* sign, struct ThreadContext_emC_t* _thCxt);



/**Macro for constant initialisation with a typesize and a given reflection class.
 * @param TYPESIZEOF see attribute ,,objectIdentSize,,.
 * @param REFLECTION the reflection class of the constant object. It may be ,,null,, also.
 * @deprecated use [[INITIALIZER_ObjectJc(...)]] instead
*/
//#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { { (ObjectJc*)(OWNADDRESS) }, { REFLECTION }, { TYPESIZEOF, 0 + (kNoSyncHandles_ObjectJc<<16) + 0}}
#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { { (ObjectJc*)(OWNADDRESS) }, { REFLECTION }, { TYPESIZEOF, 0,  kNoSyncHandles_ObjectJc, 0 }}
//#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) {TYPESIZEOF, OWNADDRESS, 0, kNoSyncHandles_ObjectJc, REFLECTION }



/** Macro for constant initialization with a IDENT and a given reflection class.
  * Use it to initialize global or stack variables in form:
  * * ,,Type myData = { INIZ_objReflId_ObjectJc( myData, &reflection_Type, 123), furtherData };,,
  * * ,,Type myData = { { INIZ_objReflId_ObjectJc( myData, &reflection_Type), 123 }, furtherData};,, 
  * if the definition starts with a union{ ObjectJc obj;} base;
  * You should use that {} -level which is related to the position of the ObjectJc-data in the instance.
  * * ,,TypeDerived data = { { INIZ_DerivedData(data, &reflection_TypeDerived, 0, furtherArgs)}, furtherData};,,
  * for a derived struct which have an adequate INIZ macro.
  * * ,,Type myData2 = { INIZ_objReflId_ObjectJc( myData2, 0, null) };  //set ident and reflection later.,,
  * @param OBJ the variable to initialize itself to store its address and gets its size. 
  *        Note: The size of the OBJ must be lesser than 64 kByte (see [[mSizeSmall_objectIdentSize_ObjectJc]]
  * @param REFLECTION maybe null, the reflection class of the constant object.
  * @param IDENT may be 0, see attribute ,,objectIdentSize,,. 
  * The value of this argument will be written to the bits 31..16 of base.objectIdentSize. It means the value is shifted to left. 
  * The size bits are calculated with sizeof(OBJ) and are written to base.objectIdentSize too, right aligend to bit 0.
  * It means, the value 0 for this argument leads to store the size of the OBJ only.
  *
  * If the sizeof(OBJ) may be > 64k, you should provide a value other than 0 using the macros 
  * [[MASKID_MediumSize_ObjectJc(...)]] and [[MASKID_LargeSize_ObjectJc(...)]]
  *
  * @since 2018-08: the better form.
*/
#define INIZ_objReflId_ObjectJc(OBJ, REFL, ID) { {(ObjectJc*)&(OBJ)} , { REFL } , {{sizeof(OBJ) | ((ID)<<kBitTypeSmall_objectIdentSize_ObjectJc), 0, kNoSyncHandles_ObjectJc, 0}}}
#define INITIALIZER_ObjectJc(OBJ, REFLECTION, IDENT) INIT_OBJ_REFL_ID_ObjectJc(OBJ, REFLECTION, IDENT)



/**This macro should be used for the ID if the size of OBJ might be up to 1 MByte in Memory.
* It is for composite struct definition (whole data of an application).
* The ID information should in range 0..255 only. It is shifted to the bits 27..20 if ObjectJc::base.objectIdentSize.
* The bits 29, 28 are set t0 01. It is [[kIsMediumSize_objectIdentSize_ObjectJc]]
*/
#define MASKID_MediumSize_ObjectJc(ID) (((ID)&0xff)<<4 | 0x1000)

/**This macro should be used for the ID if the size of OBJ might be up to 16 MByte in Memory.
* It is for composite struct definition (whole data of an application).
* The ID information should in range 0..31 only. It is shifted to the bits 28..24 if ObjectJc::base.objectIdentSize.
* The bit 29 is set to 1. It is [[mIsLargeSize_objectIdentSize_ObjectJc]]
*/
#define MASKID_LargeSize_ObjectJc(ID) (((ID)&0x1f)<<8 | 0x2000)



/**Initializer for any instance with {0}. Should be used on stack variable especially before they are handled with a ctor...(...).*/
#define NULL_ObjectJc {0}

/**This macro provides an initializer ,,{...},, for any instance which is derived from Object immediately.
 * Hint: use ,,{INITIALIZER_ObjectJc(...), more data}. 
 * @param OBJ The instance itself. It is used to store the OWNADDRESS and to build sizeof(OBJ) for the ObjectJc-part.
 */
#define CONST_Instance_ObjectJc(OBJ) { INITIALIZER_ObjectJc(OBJ, null, 0) }


/**Initialization of the basicly data of ObjectJc.
 * The instance may have initial data outside of the ObjectJc base on startup. 
 * The contract is: An instance should be initialized (usual cleared with 0) on allocation or definition.
 * For static instances use
 * ,, Type myInstance = {0};
 * 
 * This method should be used for static and embedded instances especially in C environment
 * and inside a C++-constructor.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance). All data are set to 0.
 *                Don't use this kind of initialization for C++-classes, use sizeof(ObjectJc) for this argument than.
 * @param identObj An identification info, see [[class_ObjectJc.objectIdentSize]] 
 * return thiz
*/
/*NOTE: don't use a void* instead ObjectJc*, because a qualified casting have to be done using in C++ from inheriting classes. */
METHOD_C ObjectJc* init_ObjectJc(ObjectJc* thiz, int sizeObj, int identObj);

#define isInitialized_ObjectJc(THIZ) ((THIZ)->state.b.isInitialized) 
#define setInitialized_ObjectJc(THIZ) { (THIZ)->state.b.isInitialized =1; } 

#define ident_newAllocated_ObjectJc 0x0001

/**Initialization of the basicly data of Object.
 * This method should be used for all instances.
 * @param addrInstance: The address of the instance itself, which contains ObjectJc. In C++ the instance address doesn't may be the same as ythis.
 *                      the offset to the instance itself will be stored to help data debugging.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance). 
 * @param reflection The reflection class. It may be null if the reflections are not present.
 * @param identObj An identification info, see [[attribute:_ObjectJc:objectIdentSize]] 
 * return ythis, the reference of the Object itself.
*/
METHOD_C ObjectJc* initReflection_ObjectJc(ObjectJc* ythis, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj);


/**Initialization of the basicly data of Object. It is a Macro to use without any Jc-library.
 * This method should be used for all instances.
 * @param REF The reference of the instance itself with type ObjectJc*
 * @param sizeObj The size of the whole instance which starts with ObjectJc as base struct. 
 *                The memory range starting from REF will be set to 0. In C it supports 0-initializing of the data.
 *                In C++ this parameter should be set to 0, because memset() must not be used. 
 *                The initializing is done in C++ by the constructor of the instance there.
 *                The sizeObj-value is added to the [[attribute:_ObjectJc:objectIdentSize]]. 
 * @param identObj An identification info, see [[attribute:_ObjectJc:objectIdentSize]] If sizeObj is !=0, it must not contain the size info.
 * @param reflection The reflection class. It may be null if the reflections are not present.
 * @return void.
*/
#define INIT_ObjectJc(REF, sizeObj, identObj, reflection) { memset(REF, 0, sizeObj);  \
  (REF)->objectIdentSize = sizeObj | identObj; (REF)->ownAddress = (REF); (REF)->reflectionClass = reflection; }


/** sets the reflection class. This method is to be called by user in its constructor of a derivated class.
  * @param reflection The reflection class of the instance, appropriate to the derivated type.
  * @param objectIdentSize The type or instance and size ident.

           This value will be stored immediately in the attribute objectIdentSize.
           The user may be set a 0-value, if no size or object ident is used in the users scope.
           But if the data are saved and transfered as POD plain old data to evaluate it,
           this information may be necessary for evaluation. The user should calculate this value
           carefully in respect to the size, instance and array bits, see enum ,,k..._objectIdentSize_ObjectJc,,.
           If no ident ifno is necessary, the size may be stored here. If the object has a low size (up to 64 k in a 32-bit-System),
           a simple way is to write ,,sizeof(Type),, or ,,sizeof(ythis),,,
           because the kIsSmallSize_objectIdentSize_ObjectJc is defined with 0.
           But it is exacting to write ,,kIsSmallSize_objectIdentSize_ObjectJc + sizeof(ythis),,,
           because it is shown here that it is a small size object.
  * @return void.
*/
METHOD_C void setReflection_ObjectJc(ObjectJc* ythis, struct ClassJc_t const* reflection, int32 objectIdentSize);



/**Sets the ident and size of an ObjectJc.
 * The bit position of ident and size, and the bits to define which bits are using for ident and size [[mSizeBits_objectIdentSize_ObjectJc]]
 * are calculated from given size and type.
 * @param sizeObj The size which is valid for the memory-area, which is used from the derived whole instance.
 * @param identObj any special ident. If 0, an automatically ident is built.
 * @throws RuntimeException if the identObj and sizeObj are not matching. See Bits of [[class_ObjectJc_objectIdentSize]].
 */
METHOD_C void setSizeAndIdent_ObjectJc(ObjectJc* ythis, int sizeObj, int identObj);

/**Checks whether a reference refers a valid ObjectJc. A valid ObjectJc has a mark: Its own address
 * is stored in the Object.
 * @param THIZ any reference which may refer an ObjectJc. The reference can be null. If it is not null it have to be refer to a valid data space;  
 */
#define isValid_ObjectJc(THIZ) ( (THIZ) !=null && ((ObjectJc const*)(THIZ))->ownAddress == ((ObjectJc const*)((THIZ))))



/**Checks whether a reference refers a valid ObjectJc. A valid ObjectJc has a mark: Its own address
 * is stored in the Object.
 * @param THIZ any Object reference which contains { union { ObjectJc object; } base;  
 */
#define isNotInitialized_ObjectJc(THIZ) ( (THIZ)->base.object.ownAddress == null && (THIZ)->base.object.state.b.objectIdentSize == 0)





/**Checks the consistence of the given instance based on ObjectJc and initialize the ident and reflection if they are empty.
 * An Object should be initialized before with [[init_ObjectJc(...)]] or as static instance with [[INIZ_objReflId_ObjectJc(...)]]. 
 * This method should be used in the constructor of all classes to check whether the initializing is done.
 * @param size The requested size of the instance.
 *             The instance is valid if the size saved in the element ,,objectIdentSize,, is >= size.
 *             A greater instance (derived) is accepted also.
 * @param clazzReflection instanceof_ObjectJc() will be tested. If this param is null, no test of reflection is done.
 *             Unsupported feature: If the reflection class of the instance is null, it will be set with this reference.
 *             But call setReflection_ObjectJc() instead before, because this method may be changed in future. It should only test, not set anything!
 * @return null if ok, elsewhere a short error msg
*/
METHOD_C char const* checkInit_ObjectJc(ObjectJc* ythis, int size, int ident, struct ClassJc_t const* clazzReflection, struct ThreadContext_emC_t* _thCxt);

/**Checks the consistence or init, 
 * @deprecated, use [[checkOrInit_ObjectJc(...)]] with a more significant name.
 */
#define checkConsistence_ObjectJc(THIS, SIZE, REFL, THCXT) checkInit_ObjectJc(THIS, SIZE, 0, REFL, THCXT)
#define checkOrInit_ObjectJc checkInit_ObjectJc

/**Checks the consistence of the given instance based on ObjectJc.
 * An Object should be initialized before it is used. This method should be used in the constructor
 * of all classes to check whether the initializing is done.
 * @param size 0 or the requested size of the instance. If 0 then the size info will not be checked.
 *             The instance is valid if the size saved in the element ,,objectIdentSize,, is >= size.
 *             A greater instance (derived) is accepted also.
 * @param ident 0 or the requested indent. If 0 then the size info will not be checked.
 * @param clazzReflection instanceof_ObjectJc() will be tested. If this param is null, no test of reflection is done.
 * @return null if no error, error String if check fails
 */
METHOD_C char const* checkStrict_ObjectJc(ObjectJc const* thiz, int size, int ident, struct ClassJc_t const* clazzReflection, struct ThreadContext_emC_t* _thCxt);




/** gets the size of the Object stored in attribute objectIdentSize. This value helps to step through data
  * particularly by using direct composed plain old data,
  * but the user is responsible for the exactly realization.
  */
METHOD_C int getSizeInfo_ObjectJc(ObjectJc const* ythis);

/**gets the ident and size of the Object stored in attribute objectIdentSize.
 * This value is useable as debug information.
 */
METHOD_C int getIdentInfo_ObjectJc(ObjectJc const* ythis);
//#define getIdentInfo_ObjectJc(YTHIS) (

/** gets the reflection class.*/
METHOD_C struct ClassJc_t const* getClass_ObjectJc(ObjectJc const* ythis);

/**tests wether the given object is an instance of the requested Type.
 * Javalike: instanceof-operator.
 * @param thiz any Object
 * @param reflection The reflection of the type to compare. The chararcter sequence is tested.
 * In opposite to [[instanceof_ObjectJc(...)]] they may be more as one reflection instance possible.
 * That is especially in dll libraries with static linked reflection.
 */
METHOD_C bool instanceof_s_ObjectJc(ObjectJc const* ythis, char const* reflection);


/**Returns a new Identification for an Object. This method may be implemented user-specific
 * to generate a log file with instantiated Objects.
 */
METHOD_C int newIdent_ObjectJc();


#endif  //#ifndef __ObjectJc_defined__


/*@CLASS_CPP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)



  /** Superclass for class ObjectJcpp and especially for all interface classes.
      This base class defines a method to convert this to Object*
      especially necessary for interface classes.<br/>
      The methods of this class should be implemented in any class
      implementing any interface.
  */
  class  ObjectifcBaseJcpp
  {
    /**This value should be set with the kSignificance_ObjectifcBase 
     * to allow a test wether a reference to ObjectifcBase is correct
     * after a pointerCasting to such type and before calling its virtual methods.
     */
    public: const int32 significance_ObjectifcBase;
	#define kSignificance_ObjectifcBase 0x0efcba5e
	
	/**This value should be set with the own address 
     * to allow a test wether a reference to ObjectifcBase is correct
     * after a pointerCasting to such type and before calling its virtual methods.
     */
    public: const void* significanceAddress_ObjectifcBase;
	  
    /** converts to the ObjectJc- pointer, superclass of all instances..
    A type casting to (ObjectJc*) applied to a pointer of interface type
    forces the using of the ObjectJcpp* - casting operator of the instance-type,
    mediate from the virtual table of the interface.
    Note that a casting to super or derived classes in C++ modifies the this-pointer
    with small adress modification to the right virtual table.
    The default implementation supplies no Reflection or ObjectJc-support.
    */
    public: virtual ObjectJc* toObject() = 0; //{ return null; }

    //#define toObject_Jc() toObject()

    /**returns true if the String given Type is the instance can derived immeditately 
     * to the given type with simple cast (C-cast). 
     * In Java there it is the operator instanceof
     * Note: It does not regard C++ deviation. Only able to use for the ObjectJc-C-inheritance.
     */
    public: bool instanceof(const char* type){ return instanceof_s_ObjectJc(toObject(), type); } 

    public: struct ClassJc_t* getClass(){ getClass_ObjectJc(toObject()); }

    /**The constructor is called automatically in C++. Because it is contained as inline
     * in the header, the user don't need any other library to use it.
     */
    public: ObjectifcBaseJcpp(); //: significance_ObjectifcBase(123), significanceAddress_ObjectifcBase(null){}
    
  };

#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

/*@CLASS_C VtblHeadJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**This is a only forward declared struct used in [[VtblHeadJc]] for the size value stored as pointer. */
struct Size_Vtbl_t;
#define Size_Mtbl_t Size_Vtbl_t

#define NrofMethodsForSize_VTBL_Jc(NR) (struct Size_Mtbl_t*)((2 +NR) * sizeof(void*)) 

/** The definition of ordered method pointer, it is a jump table.
  * The virtual methods are callable in a C-environment adequate to virtual methods in C++.
  * This struct of method pointer determines the order of virtual methods of ObjectJc for all implementation classes.
  */
typedef struct VtblHeadJc_t
{ /**The value of sign must be identically with the address of the sign_Mtbl_TYPE. Check it for safe access. */
  char const* sign;
  /**The sizeTable is really an simple int. But all members of Method table are from pointer type. casted internally. 
   * Check of sizeTable makes possible to use older implementation versions with less methods.
   * NOTE: don't use a void*, because all is compatible with it and no errors are signated.
   */
  struct Size_Mtbl_t* sizeTable;  
}VtblHeadJc;

#define MtblHeadJc VtblHeadJc

/**Structure which represents the common Vtbl-ref-type. 
 * It holds the pointer to the correct Vtbl (represented with the Head)
 * and the reference to the data based on Objectjc.
 * The vtbl->sign should be tested to correctness, and then the vtbl pointer should be casted.
 */
typedef struct VtblObjectJcRef_t
{ VtblHeadJc* vtbl;
  ObjectJc* ref;
} VtblObjectJcRef;

#define ObjectJcMTB VtblObjectJcRef


extern char const sign_Mtbl_ObjectJc[]; 
extern char const signEnd_Mtbl_ObjectJc[];

/**returns the method table of the given instance for the given maybe super class or interface. 
 * This routine presumed that the given Object has a correct method table.
 * This method is used basicly.
 * If the instance is not type of the required class, null is returned.
 *
 * If the pointer to the method table is worse, either an exception is thrown 
 * because the search process detects any memory content as size of method table, which is worse,
 * or an memory protection exception is caused.   
 *
 * This is useable in safety critical software: If any error in data occurs, 
 * the programm is aborted, the throw may be catched or not, but the software works deterministic.
 *
 * @param sign The address of the sign to the required method table for the maybe interface or super class.
 *    Use  ,,sign_Mtbl_TYPE,,   in the user's software to determine the type. 
 *    The sign... is defined with the Method table and reflection for any class.
 * @return null or the reference of the method table of the required base class.
 * The Method table may be a derived table depending on sign parameter..
 * Whether the method table is derived or not, it means wether a up-casting is allowed,
 * depends on a derived class. 
 */
METHOD_C MtblHeadJc const* getVtbl_ObjectJc(ObjectJc const* ythis, char const* sign);
#define getMtbl_ObjectJc getVtbl_ObjectJc


int getPosInVtbl_ObjectJc(ObjectJc const* thiz, char const* sign);
#define getPosInMtbl_ObjectJc getPosInVtbl_ObjectJc


METHOD_C VtblHeadJc const* checkMtbl_ObjectJcTT(ObjectJc const* ythis, int ix, char const* sign, struct ThreadContext_emC_t* _thCxt);




#define SETMTBJc(DST, REF, TYPE) { (DST).ref = (struct TYPE##_t*)(REF); (DST).mtbl = (DST).ref == null ? null : (Mtbl_##TYPE const*)getMtbl_ObjectJc(&(DST).ref->base.object, sign_Mtbl_##TYPE); }
#define SETMTBJc_XXX(DST, REF, TYPE) { (DST).ref = (TYPE*)(REF); (DST).mtbl = (DST).ref == null ? null : (Mtbl_##TYPE const*)getMtbl_ObjectJc(&(DST).ref->base.object, sign_Mtbl_##TYPE); }

/**Macro to get the method table from a given reference. 
 * @Deprecated. Don't use the macro. It is better to write the two routines one after another. Keep clearly.
 * @param REF A reference to any type which is based on Object. It should hava a ,,union{ ... ObjectJc object; } base;,,
 * @param TYPE The Typ of the method table. It is used to build ,,Mtbl_TYPE const*,, and ,,sign_Mtbl_TYPE,,
 * @return casted returnvalue of ,,getMtableObjectJc(othis, sign),,. 
 *         returns null if the instance doesn't have a method table. An NullPointerException outside may be thrown.
 *         This behaviour is able to use whether base methods of ObjectJc are available on any instance.
 * @throws ClassCastException If the object isn't based on the required type.
 */
#define MTBCALLJc(REF, TYPE) ((Mtbl_##TYPE const*)getMtbl_ObjectJc(&(REF)->base.object, sign_Mtbl_##TYPE))


/****************************************************************************************************
 * Virtual methods of ObjectJc:
 * The virtual methods are defined as Methodtypes.
 */

/** Produces a new instance equal to the old one. The method is virtual,
  * because it may be able that some register operations or others should be done
  * by the users class. This operation is the object-oriented replacement
  * for the old C-style memcpy of instances data.
*/
METHOD_C typedef ObjectJc* MT_clone_ObjectJc(ObjectJc const* ythis, MemC buffer);

/**Tests wether or not both objects are equal. The statement of homogeneousness
 * may be depended on some informations inside the instances, other informations
 * may be differenced, though both objects are equal. Thats why the method is virtual.
 * This operation is the object-oriented replacement
 * for the old C-style memcpy of instances data.
 */
METHOD_C typedef bool MT_equals_ObjectJc(ObjectJc* ythis, ObjectJc* second, struct ThreadContext_emC_t* _thCxt);

/**This method should be called before the instance is deleted finally. It is called
 * by garbage collection. Some action such as deregister or free memory may be taken
 * from the users overload class.
 */
METHOD_C typedef void MT_finalize_ObjectJc(ObjectJc* ythis, struct ThreadContext_emC_t* _thCxt);

/**This method supplies a hash code for thid onstance.
 */
METHOD_C typedef int32 MT_hashCode_ObjectJc(ObjectJc const* ythis, struct ThreadContext_emC_t* _thCxt);

/**This method supplies a string representation of the content of the instance,
 * useable especially for debug or analyze information.
 */
METHOD_C typedef StringJc MT_toString_ObjectJc(ObjectJc* ythis, struct ThreadContext_emC_t* _thCxt);




/**The definition of ordered pointer to overideable operations, it is a jump table.
 * The virtual operations are callable in a C-environment adequate to virtual methods in C++.
 * This struct of method pointer determines the order of virtual methods of ObjectJc for all implementation classes.
 * @refl: no.
 */
typedef struct Vtbl_ObjectJc_t
{ VtblHeadJc head;
  /**Methods of ObjectJc. */
  MT_clone_ObjectJc*    clone;
  MT_equals_ObjectJc*   equals;
  MT_finalize_ObjectJc* finalize;
  MT_hashCode_ObjectJc* hashCode;
  MT_toString_ObjectJc* toString;
} Vtbl_ObjectJc;


#define Mtbl_ObjectJc Vtbl_ObjectJc

/**Structure of the Vtbl of an Instance derived from Objectjc without any overridden operations. 
 * This structure is defined in Object_emC.c, see extern declaration.
 * @refl: no.
 */
typedef struct VtblDef_ObjectJc_t {
  Vtbl_ObjectJc tbl; VtblHeadJc end;
} VtblDef_ObjectJc;

extern_C VtblDef_ObjectJc const vtbl_ObjectJc;

/**The override-able method toString tests the virtual table inside reflection
 * to call the correct toString-Method of the implementation class. */
StringJc toString_ObjectJc(ObjectJc* ithis, struct ThreadContext_emC_t* _thCxt);


/** The implemented method for ObjectJc forward declared here.
 *  They should be known if a user class will not overload some methods from ObjectJc with its own methods
 *  but use this methods.
 *  In generally, implementation methods needn't be forward declared, they need only be defined in the C file.
 */
extern_C MT_clone_ObjectJc clone_ObjectJc_F;
extern_C MT_equals_ObjectJc equals_ObjectJc_F;
extern_C MT_finalize_ObjectJc finalize_ObjectJc_F;
extern_C MT_hashCode_ObjectJc hashCode_ObjectJc_F;
extern_C MT_toString_ObjectJc toString_ObjectJc_F;


/** The virtual table of non overloaded methods from object,
    useable as part of a users virtual table.
  */
#define CONST_MtblStd_ObjectJc \
{ clone_ObjectJc_F    \
, equals_ObjectJc_F   \
, finalize_ObjectJc_F \
, hashCode_ObjectJc_F \
, toString_ObjectJc_F \
}




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
  { INIZ_objReflId_ObjectJc(OBJ, REFL_ELEM, ID | (mArray_objectIdentSize_ObjectJc >>16)), sizeof(TYPE), 1<<kBitDimension_ObjectArrayJc, NROF_ELEM }


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

#define reflection__ObjectJcpp reflection__ObjectJc


#if !defined(mBackRef_ObjectJc) 
  //if enhanced references are used, the REF types have own reflection const.
  //in this case they are dummies.
  #define reflection_StringBufferJcREF reflection_StringBufferJc

#endif


/*@CLASS_C FieldJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/** A field is one entry in the reflection information about attributes or references of any type.
 * In opposite to orignal-Java a FieldJc is not based on Object,
 * but the Field[]-type, in Jc named "FieldJcArray" is based on ObjectJc like every ARRAYJc.
 * It means at ex you cannot call toString_ObjectJc(myField.object), it results in a compiler syntax error.
 * The reason if the FieldJc-type do not based on ObjectJc is: preserve of expenditure, it is not necessary.
 * A field may describe:
 * * a simle scalar attribute of type such as int or long, the type field references to ,,ReflectionintJc,, and so on.
 * * a reference to any other type, the instance may be derived also, the type field references to ,,ReflectionReferenceType,,.
 * * a embedded other type. That is a possibility only in C(++), not possible in original Java.
 * : but the Java2C translator produces such constructs because optimization, and a hand write code
 * : can use this because optimization. The type field references to ;;ReflectionEmbeddedType,,,
 * : but the modifier-bit mEmbedded_Modifier_reflectJc is set in bitModifiers.
 */
C_TYPE typedef struct  FieldJc_t
{ 
  char name[30]; //kLengthNAME_FIELD_ReflectionJc];  //28

                 /**Size of the field or size of 1 element if it is an static array. */
                 //int16 sizeElement;

                 /**Nr of elements of an static array or the bit positions of a bitfield
                 * If is is a bit field
                 */
  uint16_t nrofArrayElementsOrBitfield_;

  /**If the element nrofArrayElementsOrBitfield designates the bits of a bitfield,
  * this bits represent the bit Position in the field.
  * It is a number between 0 and 31 for 32-bit-width bit fields or between 0 and upto 4095
  * for upto 128 int32_t-variables one after another which are all bitfields.
  * Note that an address calculation in C cannot be done for bitfield variables.
  * Therefore the last variable before bitfield determines the offset of the bitfield
  * and all bitfield variables one after another uses this address. Therefore the bit position
  * should be a more great number.
  */
#define mBitInBitfield_FieldJc 0x0fff

  /**If the element nrofArrayElementsOrBitfield designates the bits of a bitfield,
  * this bits represent the number of bits of the field. Value from 1 to 15, or 0 for a 16-bit-biftield.
  */
#define mNrofBitsInBitfield_FieldJc 0xf000

  /**If the element nrofArrayElementsOrBitfield designates the bits of a bitfield,
  * this bits represent the position in bits of number of bits of the field.
  */
#define kBitNrofBitsInBitfield_FieldJc 12

  /** The class object representing the type of the field.
  * It may be a class object also for primitive types
  * or for primitive Type there is a simple constant value, see REFLECTION_type above.
  * Don't use this element directly. Only with is getter: [[getType_FieldJc(...)]]
  */
  struct ClassJc_t const* type_;

  /**The modifiers of the Field. The Bits are defined in Modifier_reflectJc.
  * The concept follows Java, see java.lang.reflect.Field.getModifier or java.lang.reflect.Modifier,
  * but it is enhanced in respect to C/C++ and UML requirements.
  */
  int32     bitModifiers;  //Bits of Modifier_reflectJc.

  /**The bits 15..10 are not used in Java modifier for fields. Used for the access level. */
  #define mAccessLevel_Modifier_FieldJc 0x00001c00
  #define mChangeLevel_Modifier_FieldJc 0x00007000
  #define kBitAccessLevel_Modifier_FieldJc 10
  #define kBitChangeLevel_Modifier_FieldJc 13

  /** position of the field inside a object of the type of the declaring class.
  * The position is the offset from the ObjectJc base class to the field, not the offset from the total base.
  * Because it is possible that the object is known via interface reference. A interface reference
  * pointered the position of the pointer to the virtual table of the interface,
  * a call of obj->toObjectJc() is necessary to get the base for this offset.
  */
  int16     position;

  /**Offset in a pointered class to the ObjectifcBaseJcpp class structure if such base interface exists.
  This value is 0 if it is not a pointer or if it is a pointer of not Object-derivated structures.
  */
  int16     offsetToObjectifcBase;
  /** The class object representing the class or interface that declares the field represented by this Field object. */
  struct ClassJc_t const* declaringClass;
}FieldJc;


/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define INIZ_ID_FieldJc 0x0ff6

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_FieldJc (kIsSmallSize_objectIdentSize_ObjectJc + (INIZ_ID_FieldJc<<kBitTypeSmall_objectIdentSize_ObjectJc))

#define TYPESIZEOF_FieldJc (kIsSmallSize_typeSizeIdent_ObjectJc + 0x0FF60000 + sizeof(FieldJc))



/*@CLASS_C ClassJc ************************************************************************/
#ifndef __ObjectJc_defined__


struct FieldJc_t;
struct FieldJc_Y_t;
struct MethodJc_t;
struct MethodJcARRAY_t;

/**A ClassJc is the head instance of the reflection of any type using ObjectJc. It is adequat to [[javadoc/lang/Class]].
 * Because the instance is defined in compile time, it should be defined as ,,const,, anyway. Therefore it can be protected
 * for touching by side effects of other failures in any C program either if a memory management unit is present on the processor
 * or if it is stored in a ROM. Therefore is should be defined as a C struct in a C++ environment too. 
 * Note that data of a const class in C++ can be filled on constructor, therefore it is not a const in memory. A C const can be really stored in const memory.
 *
 * The ClassJc contains the reference to the method table too. Because of safety of an application for side-effect-failures the method table
 * is constant too.
 *
 * This definition is contained in the header <Jc/ObjectJc.h> because some inline methods of ObjectJc need the method table reference.
 */
C_TYPE typedef struct  ClassJc_t
{ ObjectJc object;

  /** The typename. If it is a Class represents a primitive type, the name is such as "int", "float", "boolean".*/
  char name[32];

  /** position of the base structure/class ObjectJc inside this type, it is the base address for the offset of fields.*/
  int32 posObjectBase;

  /**sizeof the type. Hint: It may be longer as 64 kByte, int32 is necessary.*/
  int32 nSize;

  struct FieldJc_Y_t const* attributes;

  struct MethodJcARRAY_t const* methods;

  /** The superclass, ObjectJc if no other superclass.*/
  struct ClassOffset_idxMtblJcARRAY_t const* superClasses;
  //struct ClassJc_t const* superClass;

  /** Array of interfaces to this class.*/
  //ObjectJc const* interfaces;
  struct ClassOffset_idxMtblJcARRAY_t const* interfaces;
  //struct{ ObjectArrayJc base; ClassJc* interfaces; };

  /** Some bits determines the kind of the Class, see Modifier_reflectJc*/
  int32 modifiers;

  /**Pointer to jump table for dynamic calls (virtual methods).
   * This is a typed struct, starting with Mtbl_ObjectJc.
   */
  VtblHeadJc const* mtbl;
  //Method_int_Object* mtbl;

}ClassJc;

/**Compatibility. */
#define Class_Jc_t ClassJc_t

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define INIZ_ID_ClassJc 0x0ff8

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ClassJc (kIsSmallSize_objectIdentSize_ObjectJc + (INIZ_ID_ClassJc<<kBitTypeSmall_objectIdentSize_ObjectJc))

/**This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ReflectionImageJc (mIsLargeSize_objectIdentSize_ObjectJc + 0x1e000000)

/**This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ReflectionImageBaseAddressJc (kIsSmallSize_objectIdentSize_ObjectJc + 0x0ff70000)

extern const ClassJc reflection_ClassJc;


extern_C void init_Fields_super_ClassJc(ClassJc* thiz, StringJc name, ObjectArrayJc* fields, ObjectArrayJc* super);



/*@CLASS_C ModifierJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/** Modifiers to specify the kind of field, see class java.lang.reflect.Modifier
*/

typedef enum  Modifier_reflectJc_t
{  /**
   * The <code>int</code> value representing the <code>public</code>
   * modifier.
   */
  mPUBLIC_Modifier_reflectJc = 0x00000001

  /**
  * The <code>int</code> value representing the <code>private</code>
  * modifier.
  */
  , mPRIVATE_Modifier_reflectJc = 0x00000002

  /**
  * The <code>int</code> value representing the <code>protected</code>
  * modifier.
  */
  , mPROTECTED_Modifier_reflectJc = 0x00000004

  /**
  * The <code>int</code> value representing the <code>static</code>
  * modifier.
  */
  , mSTATIC_Modifier_reflectJc = 0x00000008

  /**
  * The <code>int</code> value representing the <code>final</code>
  * modifier.
  */
  , mFINAL_Modifier_reflectJc = 0x00000010

  /**
  * The <code>int</code> value representing the <code>synchronized</code>
  * modifier.
  */
  , mSYNCHRONIZED_Modifier_reflectJc = 0x00000020

  /**
  * The <code>int</code> value representing the <code>volatile</code>
  * modifier.
  */
  , mVOLATILE_Modifier_reflectJc = 0x00000040

  /**
  * The <code>int</code> value representing the <code>transient</code>
  * modifier.
  */
  , mTRANSIENT_Modifier_reflectJc = 0x00000080

  /**
  * The <code>int</code> value representing the <code>native</code>
  * modifier.
  */
  , mNATIVE_Modifier_reflectJc = 0x00000100

  /**
  * The <code>int</code> value representing the <code>interface</code>
  * modifier.
  */
  , mINTERFACE_Modifier_reflectJc = 0x00000200

  /**
  * The <code>int</code> value representing the <code>abstract</code>
  * modifier.
  */
  , mABSTRACT_Modifier_reflectJc = 0x00000400

  /**
  * The <code>int</code> value representing the <code>strictfp</code>
  * modifier.
  */
  , mSTRICT_Modifier_reflectJc = 0x00000800

  /**outside java definition:
  * If not 0, than it is a primitive type.
  * The value at this bits represents the nr of Bits of the primitive type in the target system.
  */
  , mPrimitiv_Modifier_reflectJc = 0x000F0000

  /**It may be a primitive with 7*8= 56 bit, it is used to designate a bitfield. */
  , kBitfield_Modifier_reflectJc = 0x00070000

  /**It may be a primitive with 9*8= 72 bit, it is used to designate a handle for a pointer.
  * This is a special feature for supporting 64-bit-addresses with 32-bit handle. The handle is the index
  * of a global address table which contains the pointer. Alternatively for 32-bit-Systems the handle is equal the pointer value.
  */
  , kHandlePtr_Modifier_reflectJc = 0x00090000

  /**outside java definition:
  * Position of this Bits.
  */
  , kBitPrimitiv_Modifier_reflectJc = 16

  /**outside java definition:
  * This bits represents the containertype.
  */
#define m_Containertype_Modifier_reflectJc 0x00f00000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_List()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container
  * using the ListJc interface.
  */
  , kListJc_Modifier_reflectJc = 0x00100000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_List()-Property.
  * It is set if a Reference is a multiple aggregation realized with a array container
  * using the ObjectArrayJc structure.
  */
  , kObjectArrayJc_Modifier_reflectJc = 0x00200000   //do not change, compatibility with older data

                                                     /**outside java definition:
                                                     * The <code>int</code> value representing the isUML_List()-Property.
                                                     * It is set if a Reference is a multiple aggregation realized with a array container
                                                     * using the ObjectArrayJc structure.
                                                     */
  , kPtrVal_Modifier_reflectJc = 0x00300000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_List()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container
  * using the MapJc interface.
  */
  , kMapJc_Modifier_reflectJc = 0x00400000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_List()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container.
  * The realisation of the list may be specific for a UML framework, therefore the access to the elements
  * is made with the user definable UML_ListJc methods.
  */
  , kUML_LinkedList_Modifier_reflectJc = 0x00500000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_Map()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container.
  * The realisation of the list may be user specific for a UML framework, therefore the access to the elements
  * is made with the user definable UML_MapJc methods.
  */
  , kUML_Map_Modifier_reflectJc = 0x00600000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_Array()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container.
  * The realisation of the list may be user specific for a UML framework, therefore the access to the elements
  * is made with the user definable UML_ArrayJc methods.
  */
  , kUML_ArrayList_Modifier_reflectJc = 0x00700000

  /**outside java definition:
  * The <code>int</code> value representing the isStaticArray-Property.
  * It is set if multiple elements are after another imediately,
  * The number of elements is hold in the FieldJc.nrofArrayElements
  */
  , kStaticArray_Modifier_reflectJc = 0x00800000   //do not change, compatibility with older data

                                                   /**Mode of addressing of complex elements. This mode is regarded to the elements of a container,
                                                   * if the field represents a container.
                                                   * The kind of the instanciation of the container is found in @see mContainerinstance_Modifier_reflectJc.
                                                   */
#define mAddressing_Modifier_reflectJc 0x03000000
                                                   /** outside java definition:
                                                   * The <code>int</code> value representing the isEmbedded()-Property of fields,
                                                   * It is set if a attribute represented by the field in reflection represents
                                                   * a embedded structured (not a reference to data).
                                                   */
  , kEmbedded_Modifier_reflectJc = 0x01000000

  /** outside java definition:
  * The <code>int</code> value representing the isReference()-Property.
  * A reference is a reference to a primitive type or structured type,
  * not inherited from ObjectJc.
  */
  , kReference_Modifier_reflectJc = 0x02000000



  /** outside java definition:
  * The <code>int</code> value representing the isEnhancedReference()-Property.
  * An enhanced reference may be reference a ObjectJc-inherited instance.
  * NOTE: mask and compare both bits mEmbedded_Modifier_reflectJc and mReference_Modifier_reflectJc!
  */
  , kEnhancedReference_Modifier_reflectJc = 0x03000000
  /** outside java definition:
  * The <code>int</code> value representing the isObjectJc()-Property.
  * It is set if the Type contains ObjectJc at its first position,
  * especially for C-struct using CRuntimeJavalike-concepts. If it is set,
  * a C-pointer cast is allowed to keep the ObjectJc-pointer.
  * The bit is not set if the type is derived from ObjectJc,
  * but don't contain it at first position
  * It is not set if
  */
  , mObjectJc_Modifier_reflectJc = 0x04000000

  /**outside java definition:
  * The <code>int</code> value representing the isObjectifc()-Property.
  * It is set if the Type is derived from ObjectifcBaseJcpp.
  */
  , mObjectifcBaseJcpp_Modifier_reflectJc = 0x08000000


  /**The container is instanciated embeddedly. */
  , kEmbeddedContainer_Modifier_reflectJc = 0x10000000
  /**The container is referenced with a simple reference. */
  , kReferencedContainer_Modifier_reflectJc = 0x20000000
  /**The container is referenced with an enhanced reference. */
  , kEnhancedRefContainer_Modifier_reflectJc = 0x30000000



} Modifier_reflectJc;



typedef enum Mask_ModifierJc_t
{
  /**If this bit is set, it is either a reference or a enhanced reference.*/
  mReference_Modifier_reflectJc = 0x02000000

  /**outside java definition:
  * The <code>int</code> represents the kind of the instanciation of the container.
  *
  */
  , mContainerinstance_Modifier_reflectJc = 0x30000000
}Mask_ModifierJc;



#define isReference_ModifierJc(VALUE) ( (VALUE & mReference_Modifier_reflectJc) !=0)

//#define isCollection_ModifierJc(VALUE) ( (VALUE & (mListJc_Modifier_reflectJc | mObjectArrayJc_Modifier_reflectJc  | mMapJc_Modifier_reflectJc | mStaticArray_Modifier_reflectJc | mUML_LinkedList_Modifier_reflectJc | mUML_ArrayList_Modifier_reflectJc| mUML_Map_Modifier_reflectJc)) != 0 )
#define isCollection_ModifierJc(VALUE) ( (VALUE & m_Containertype_Modifier_reflectJc) != 0 )

#define isStaticArray_ModifierJc(VALUE) ( (VALUE & m_Containertype_Modifier_reflectJc) == kStaticArray_Modifier_reflectJc )

/**Returns true if it is an embedded static simple array.*/
#define isStaticEmbeddedArray_ModifierJc(VALUE) ( (VALUE & (m_Containertype_Modifier_reflectJc|mContainerinstance_Modifier_reflectJc)) == (kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc ) )





/*@CLASS_C ClassOffset_idxMtblJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**This type describes one entry of a interface or superclass.
 * In regard of virtual methods an index inside the table of virtual methods is stored here.
 */
typedef struct ClassOffset_idxMtblJc_t
{
  /** The reflection definition*/
  ClassJc const* clazz;
 
  /** Index of the virtual table inside its parent. The array of virtual operations is in othiz->reflection.mtbl */
  int idxMtbl;
 
  /**The field is a helper for inspector access: It contains the name of the interface or "super"
   * at position 0 repectively the correct position for C++ reflection. */
  FieldJc field;

} ClassOffset_idxMtblJc;

/**This macro calculates the index of a particulary method table inside a table, to use for idxMtbl in ClassOffset_idxMtblJc.
 */
#define OFFSET_Mtbl(TYPE, ELEMENT) ( ( (int)(&((TYPE*)(0x1000))->ELEMENT) - 0x1000) / sizeof(MT_void_Method_void const*)) 
//#define OFFSET_Mtbl(BASE, ELEMENT) ( (MT_void_Method_void const*)(&BASE.ELEMENT) - (MT_void_Method_void const*)(&BASE)) 

/** This type describes a array of ClassOffset_idxMtblJc*/
typedef struct ClassOffset_idxMtblJcARRAY_t
{ /** Base data of every array */
  ObjectArrayJc head;
  /** For debugging, 10 Elements are assumed. The real number of values is stored in array.len*/
  ClassOffset_idxMtblJc data[10];
}ClassOffset_idxMtblJcARRAY;

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define INIZ_ID_ClassOffset_idxMtblJc 0x0ff9

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ClassOffset_idxMtblJc (kIsSmallSize_objectIdentSize_ObjectJc + (INIZ_ID_ClassOffset_idxMtblJc<<kBitTypeSmall_objectIdentSize_ObjectJc))


/**Initializes a super class or interface reference in RAM for runtime reflection. 
 * @param refl_super The reflection for this super class or interface.
 * @param ixVtbl The index of the virtual table part. Use 0 if the superclass or interface has not a Vtbl.  
 */
extern_C void init_ClassOffset_idxMtblJc(ClassOffset_idxMtblJc* thiz, ClassJc const* refl_super, int ixVtbl);

#endif  //#ifndef __ObjectJc_defined__

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

#define reflection__ObjectArrayJc reflection_ObjectJc
#define reflection__StringJc reflection_StringJc
#define reflection__ClassJc reflection__ObjectJc


/**Definition of constant values for primitive type reflection
 * and some special classes.
 * @deprecated because using kXYZ for a defined constant is better to read. It is more mmemonicly.
 */
typedef enum DeprecatedScalarTypes_ClassJc_t
{
  REFLECTION_void_ClassJc       = 0x01,
  REFLECTION_int64_ClassJc      = 0x02,
  REFLECTION_uint64_ClassJc     = 0x03,
  REFLECTION_int32_ClassJc      = 0x04,
  REFLECTION_uint32_ClassJc     = 0x05,
  REFLECTION_int16_ClassJc      = 0x06,
  REFLECTION_uint16_ClassJc     = 0x07,
  REFLECTION_int8_ClassJc       = 0x08,
  REFLECTION_uint8_ClassJc      = 0x09,
  REFLECTION_int_ClassJc        = 0x0a,
  REFLECTION_uint_ClassJc       = 0x0b,
  REFLECTION_float_ClassJc      = 0x0c,
  REFLECTION_double_ClassJc     = 0x0d,
  REFLECTION_char_ClassJc       = 0x0e,
  REFLECTION_bool_ClassJc       = 0x0f,
  REFLECTION_boolean_ClassJc    = 0x0f,
  REFLECTION_String_ClassJc     = 0x10,
  REFLECTION_complexfloat_ClassJc  = 0x14,
  REFLECTION_complexdouble_ClassJc = 0x15,
  REFLECTION_bitfield_ClassJc   = 0x17,
  REFLECTION_afterlastPrimitive_ClassJc       = 0x50
}DeprecatedScalarTypes_ClassJc;

/**Definition of constant values for primitive type reflection
 * and some special classes.
 */
typedef enum ScalarTypes_ClassJc_t
{
  kREFLECTION_void_ClassJc       = 0x01,
  kREFLECTION_int64_ClassJc      = 0x02,
  kREFLECTION_uint64_ClassJc     = 0x03,
  kREFLECTION_int32_ClassJc      = 0x04,
  kREFLECTION_uint32_ClassJc     = 0x05,
  kREFLECTION_int16_ClassJc      = 0x06,
  kREFLECTION_uint16_ClassJc     = 0x07,
  kREFLECTION_int8_ClassJc       = 0x08,
  kREFLECTION_uint8_ClassJc      = 0x09,
  kREFLECTION_int_ClassJc        = 0x0a,
  kREFLECTION_uint_ClassJc       = 0x0b,
  kREFLECTION_float_ClassJc      = 0x0c,
  kREFLECTION_double_ClassJc     = 0x0d,
  kREFLECTION_char_ClassJc       = 0x0e,
  kREFLECTION_bool_ClassJc       = 0x0f,
#define kREFLECTION_boolean_ClassJc kREFLECTION_bool_ClassJc

  kREFLECTION_complexint16_ClassJc = 0x11,
  kREFLECTION_complexint32_ClassJc = 0x12,
  kREFLECTION_complexint64_ClassJc = 0x13,
  kREFLECTION_complexfloat_ClassJc = 0x14,
  kREFLECTION_complexdouble_ClassJc = 0x15,

  kREFLECTION_bitfield_ClassJc      = 0x17,
  kREFLECTION_ObjectifcBaseJcpp     = 0x18,
  kREFLECTION_ObjectJc              = 0x19,
  kREFLECTION_ObjectJcpp            = 0x1a,
  kREFLECTION_Object_ArrayJc        = 0x1b,

  kREFLECTION_StringJc              = 0x1d,
  kREFLECTION_OS_PtrValue           = 0x1e,

  kREFLECTION_ClassJc               = 0x20,

  kREFLECTION_afterlastPrimitive_ClassJc       = 0x50
}ScalarTypes_ClassJc;


/**Array contains the number of byte which were used if the scalar types with designation 0..0x17
 * are stored in a byte structure. 
 * 
 * see see javaSrc_vishiaBase/org.vishia.reflect.Java2C.nrofBytesScalarTypes.
 */
extern const int nrofBytesScalarTypes_ClassJc[];






/**The next defines are necessary because the automatic code generation generates such types if void * or void* or char* is written.*/
#define REFLECTION_void_Pointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_voidPointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_charPointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_char_Pointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )

/**Reflection of standard types. This identifier can be used to assign the symbolic value to a ClassJc const* pointer
 * espacially for const Initializer definitions.
 * The access is done always with getClass_FieldJc(FieldJc const* thiz). This routine converts with the const simpleTypes_ClassJc in Reflection_emC.c
 */
#define REFLECTION_void               ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_int64              ((struct ClassJc_t const*) REFLECTION_int64_ClassJc )
#define REFLECTION_uint64             ((struct ClassJc_t const*) REFLECTION_uint64_ClassJc)
#define REFLECTION_int32              ((struct ClassJc_t const*) REFLECTION_int32_ClassJc )
#define REFLECTION_uint32             ((struct ClassJc_t const*) REFLECTION_uint32_ClassJc)
#define REFLECTION_int16              ((struct ClassJc_t const*) REFLECTION_int16_ClassJc )
#define REFLECTION_short              ((struct ClassJc_t const*) REFLECTION_int16_ClassJc )
#define REFLECTION_uint16             ((struct ClassJc_t const*) REFLECTION_uint16_ClassJc)
#define REFLECTION_int8               ((struct ClassJc_t const*) REFLECTION_int8_ClassJc  )
#define REFLECTION_byte               ((struct ClassJc_t const*) REFLECTION_int8_ClassJc  )
#define REFLECTION_uint8              ((struct ClassJc_t const*) REFLECTION_uint8_ClassJc )
#define REFLECTION_int                ((struct ClassJc_t const*) REFLECTION_int_ClassJc   )
#define REFLECTION_uint               ((struct ClassJc_t const*) REFLECTION_uint_ClassJc  )
#define REFLECTION_long               ((struct ClassJc_t const*) REFLECTION_uint32_ClassJc)
#define REFLECTION_float              ((struct ClassJc_t const*) REFLECTION_float_ClassJc  )
#define REFLECTION_float32            ((struct ClassJc_t const*) REFLECTION_float_ClassJc  )
#define REFLECTION_double             ((struct ClassJc_t const*) REFLECTION_double_ClassJc )
#define REFLECTION_char               ((struct ClassJc_t const*) REFLECTION_char_ClassJc  )
#define REFLECTION_bool               ((struct ClassJc_t const*) REFLECTION_bool_ClassJc  )
#define REFLECTION_boolean            ((struct ClassJc_t const*) REFLECTION_bool_ClassJc )
#define REFLECTION_BOOL               ((struct ClassJc_t const*) REFLECTION_bool_ClassJc )
#define REFLECTION_BITFIELD           ((struct ClassJc_t const*) REFLECTION_bitfield_ClassJc )

#define REFLECTION_s32                ((struct ClassJc_t const*) REFLECTION_int32_ClassJc )
#define REFLECTION_u32                ((struct ClassJc_t const*) REFLECTION_uint32_ClassJc)
#define REFLECTION_s16                ((struct ClassJc_t const*) REFLECTION_int16_ClassJc )
#define REFLECTION_u16                ((struct ClassJc_t const*) REFLECTION_uint16_ClassJc)
#define REFLECTION_s08                ((struct ClassJc_t const*) REFLECTION_int8_ClassJc  )
#define REFLECTION_u08                ((struct ClassJc_t const*) REFLECTION_uint8_ClassJc )



#define REFLECTION_complexint16  ((struct ClassJc_t const*) kREFLECTION_complexint16_ClassJc
#define REFLECTION_complexint32  ((struct ClassJc_t const*) kREFLECTION_complexint32_ClassJc
#define REFLECTION_complexint64  ((struct ClassJc_t const*) kREFLECTION_complexint64_ClassJc
#define REFLECTION_complexfloat  ((struct ClassJc_t const*) kREFLECTION_complexfloat_ClassJc
#define REFLECTION_complexdouble ((struct ClassJc_t const*) kREFLECTION_complexdouble_ClassJc

#define REFLECTION_ObjectifcBaseJcpp ((struct ClassJc_t const*) kREFLECTION_ObjectifcBaseJcpp )
#define REFLECTION_ObjectJc          ((struct ClassJc_t const*) kREFLECTION_ObjectJc )
#define REFLECTION_ObjectJcpp        ((struct ClassJc_t const*) kREFLECTION_ObjectJcpp )
#define REFLECTION_Object_ArrayJc    ((struct ClassJc_t const*) kREFLECTION_Object_ArrayJc )
#define REFLECTION_StringJc          ((struct ClassJc_t const*) kREFLECTION_StringJc )
#define REFLECTION_ClassJc           ((struct ClassJc_t const*) kREFLECTION_ClassJc )



#define kREFLECTION_LastConstant      0x50



/**The float_complex is defined in os_types_def_common.h. The reflection are defined in ReflectionBastTypesJc.c. */
extern_C const ClassJc reflection_float_complex;  //the just defined reflection_

/**The double_complex is defined in os_types_def_common.h. The reflection are defined in ReflectionBastTypesJc.c. */
extern_C const ClassJc reflection_double_complex;  //the just defined reflection_



/** Constant Definition of a ClassJc-instance usefull for simple plain old data
  * without special defined methods. A superclass ObjectJc is not specified.
  * It doesn#t mean that the data can't base on ObjectJc, but the access is not able
  * via this reflection definition. It may or may not based on any superclass.
  * Use the macro CONST_xxx_ClassJc instead if you have complexer structures.
  *
  * It is been designated for a whole reflection constant definition block
  * with the following rules:
  * *The name of the constant whole reflection instance should be ,,reflectionNAME,,.
  * *The ''virtual table'' is denoted with ,,vtbl,,.
  * *The attribute-block is denoted with ,,fields,,.
  * *A superclass or any interfaces are not present.
  * *Methods are not present.
  *
  */
#define CONST_dataonly_ClassJc(SNAME, NAME) \
{ CONST_ObjectJc(sizeof(reflection##NAME), , &reflection##NAME.clazz , null) \
, SNAME\
, 0     \
, sizeof(NAME) \
, (FieldJcArray const*)(&reflection##NAME.fields) \
, null, null, null, 0 \
}

/** Adaequate complex reflection for C++-classes
*/

#define CONST_Cpp_ClassJc(SNAME, NAME, OWNADDRESS)\
{ CONST_ObjectJc(sizeof(reflection##NAME), OWNADDRESS, null)   \
, SNAME /*CONST_StringJc(SNAME)*/                      \
, 0  \
, sizeof(NAME)                              \
, (FieldJcArray const*)&reflection##NAME.fields \
, (MethodJcARRAY const*)(&reflection##NAME.methods)\
, null  \
, null  \
, mObjectifcBaseJcpp_Modifier_reflectJc   \
}




/**Macro for constant value of the ObjectJc on head of any reflectionImage-structure.
 * The macro REFLECTION_IMAGE should be defined with the identifier of the reflection image.
 * Therefore all information to build the constant value is given, no additionaly arguments are needed.
 */
#define CONST_ObjectJc_REFLECTION_IMAGE() CONST_ObjectJc(OBJTYPE_ReflectionImageJc + sizeof(REFLECTION_IMAGE), &(REFLECTION_IMAGE), null)


/**Macro for constant value of a ClassJc inside a ReflectionImage-structure.
 * The macro REFLECTION_IMAGE should be defined with the identifier of the reflection image.
 */
#define CONST_ClassJc(SNAME, NAME)\
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(REFLECTION_IMAGE.reflect_##NAME), &REFLECTION_IMAGE.reflect_##NAME, null)   \
, SNAME                       \
, 0  /**Position of ObjectJc in the Type should be 0, if only C struct should be used.*/ \
, sizeof(NAME)                              \
, (FieldJcArray const*)&REFLECTION_IMAGE.attributes_##NAME \
, (MethodJcARRAY const*)(&REFLECTION_IMAGE.methods_##NAME)\
, null  \
, null  \
, mObjectJc_Modifier_reflectJc   \
}



/**Macro for constant value of a only-data-ClassJc inside a ReflectionImage-structure.
 * The macro REFLECTION_IMAGE should be defined with the identifier of the reflection image.
 */
#define CONST_dataImg_ClassJc(SNAME, NAME)\
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(REFLECTION_IMAGE.reflect_##NAME), &REFLECTION_IMAGE.reflect_##NAME, null)   \
, SNAME /*CONST_StringJc(SNAME)*/                      \
, 0  /**Position of ObjectJc in the Type should be 0, if only C struct should be used.*/ \
, sizeof(NAME)                              \
, (FieldJcArray const*)&REFLECTION_IMAGE.attributes_##NAME \
, null  \
, null  \
, null  \
, mObjectJc_Modifier_reflectJc   \
}


/**Macro for constant value of a ClassJc inside a ReflectionImage-structure.
 * The macro REFLECTION_IMAGE should be defined with the identifier of the reflection image.
 */
#define CONST_data_ClassJc(SNAME, NAME)\
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflect##NAME, null)   \
, SNAME                       \
, 0  /**Position of ObjectJc in the Type should be 0, if only C struct should be used.*/ \
, sizeof(NAME)                              \
, &attribs##NAME \
, null  \
, null  \
, null  \
, 0   \
}

/**initializes a ClassJc, see [[ctorc_ClassJc(...)]].
 * @param rawMem raw memory area, it may be uninitialized. 
 *        The size may be greater as necessary. The constructor initializes only its own area.
 * @throws IllegalArgumentException if the sizeof rawMem is to less.  
 */
METHOD_C ClassJc* ctorM_ClassJc(MemC rawMem);


/**initializes a ClassJc. 
 * All content is set to 0.
 */
METHOD_C void ctorc_ClassJc(ClassJc* ythis);


#define getClass_ClassJc(OBJ) getClass_ObjectJc(OBJ)

/** Methods from Class */
METHOD_C struct FieldJc_Y_t const* getDeclaredFields_ClassJc(ClassJc const* ythis);//sss

METHOD_C struct FieldJc_t const* getDeclaredField_ClassJc(ClassJc const* ythis, StringJc sName);

METHOD_C struct MethodJcARRAY_t const* getDeclaredMethods_ClassJc(ClassJc const* ythis);

METHOD_C struct MethodJc_t const* getDeclaredMethod_ClassJc(ClassJc const* ythis, char const* sName);


METHOD_C ClassJc const* getEnclosingClass_ClassJc(ClassJc const* ythis);

/**Returns the type of the super class for this class or null. */
METHOD_C ClassJc const* getSuperClass_ClassJc(ClassJc const* thiz);

/**Returns the field which describes the access to the super class data for this class or null. */
METHOD_C struct FieldJc_t const* getSuperField_ClassJc(ClassJc const* thiz);

/**gets the Name of the class. It is a static method, because the argument class may be a constant for simple types.
 * @param class Either the class object or a constant to design simple types, see REFLECTION_xxx.
 */
METHOD_C const char* getName_ClassJc(ClassJc const* clazz);

METHOD_C ClassJc const* getSuperclass_ClassJc(ClassJc const* ythis);

/**gets the modifiers for this class or interface, encoded in an integer.
 * They should be decoded using the methods of class ModifierJc.
 */
METHOD_C int32 getModifiers_ClassJc(ClassJc const* ythis);


/** returns true if the type is a primitive Type, like java Class::isPrimitive()
  */
METHOD_C bool isPrimitive_ClassJc(ClassJc const* ythis);

/** returns true if the type is a reference Type. Not javalike.
  */
#define isReference_ClassJc(THIS) ((THIS->modifiers & mReference_Modifier_reflectJc)!=0)

/** returns true if the type is a instance of a C-struct, based on ObjectJc.
  * This method is defined outside java, in java all classes based only on Object.
  */
#define isObjectJc_ClassJc(THIS) ((THIS->modifiers & mObjectJc_Modifier_reflectJc)!=0)

/** returns true if the type is a instance of a C++-class, based on ObjectifcBaseJcpp.
  * It may be also a reference to a interface. The reference type should based on ObjectifcBaseJcpp.
  * This method is defined outside java, in java all classes based only on Object.
  */
#define isObjectifcBaseJcpp_ClassJc(THIS) ((THIS->modifiers & mObjectifcBaseJcpp_Modifier_reflectJc)!=0)





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




/*@CLASS_C QueryInterface_SYS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#if defined(__CPLUSGEN) && defined(__cplusplus)


/**This interface supports a commonly query possibility of a interface connection to forein instances.
 */   
class QueryInterface_SYS  
{
  /**query an instance. The instance type should be derivated from ObjectifcBaseJcpp*. 
   * Use the following sequence of secure query:
   * ,,ObjectifcBaseJcpp* ptr = myRequire->queryInterface("Name_ifc_Instance");                //quere the instance
   * ,,if(!ptr->instanceof("Name_ifc")) THROW(ClassCastException, "failed queryInterface", 0);  //test the correct type
   * ,,myRef = static_cast<Name_ifc*>(ptr);                                                   //cast to required type.
   */
  public : virtual ObjectifcBaseJcpp* queryInterface(const char* name)=0;
};
  
  
#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)







#endif //__objectBaseC__h__
