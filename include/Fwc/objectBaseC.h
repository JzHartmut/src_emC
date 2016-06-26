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
#ifndef __objectBaseC__h__
#define __objectBaseC__h__

#include <os_types_def.h>
//#include <fw_Platform_conventions.h>  //knowledge of mBackRef_ObjectJc because it is used for conditional comliling.
#include <Fwc/fw_String.h>
#include <Fwc/fw_MemC.h>

struct ThreadContextFW_t;

/**This file defines only the struct Object_Jc_t and the base interface ObjectifcBase_Jcpp.
   It is the minimal base for some struct or interface 
   which should be designable without knowledge of the CRuntimeJavalike concept.
   This Header should be included while using the CRuntimeJavalike concept
   but a surrogating other header which define these two elements in a other way may be used otherwise.
 */


struct Size_Mtbl_t;

/*@CLASS_C ObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

  /**Object is the superclass of all superclasses. In C-like manner it is a struct
   * at begin of any class-like struct.
   */
  typedef struct  ObjectJc_t
  {

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
    int32 objectIdentSize;


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
          There are only 5 bits useable for 31 large types.
        */
      #define mTypeLarge_objectIdentSize_ObjectJc  0x1f000000

      /** This constant is used to shift the type info for small objects. */
      #define kBitTypeLarge_objectIdentSize_ObjectJc 24

  /** The own address of the instance. This information is usefull if the data of the instance
    * are transfered into another memory space (at example via file transfer).
    * All pointers inside this instance may be relativ build with this information.
    */
    /**The own address of the instance saved in the instance itself. This value may be important
     * if the data are transmitted in an other system (evaluation of data)
     * and some references between data are present. The evaluator may be able to found
     * the correct association between the instances by testing this value.
     */
    void const* ownAddress;

    /**Posive value of offset to the beginn of block, able to use debugging data manually. 
     * If this Object is part of a BlockHeapBlockJc, bit 15 is set, but the rest is the positive offset to start of heap block.
     * 
     */
    int16 offsetToStartAddr;

    /** identification number for wait/notify and synchronized.
     *  Because most of ObjectJc are not used for synchronized or wait/notify,
     *  the necessary handles for that are stored in a separate struct located in an separate memory space
     *  defined in os_wrapper.c.
     *  Here only the 2 bytes for a id are provided.
     */
    int16 idSyncHandles;
    #define kNoSyncHandles_ObjectJc -1


    /** The info about this type of the object. The Java-like reflection-concept is used.
    */
    struct ClassJc_t const* reflectionClass;


    //always: #if defined(mBackRef_ObjectJc)
    /** Pointer to a memory management, which manages this object. old: the BlockHeapBlock-Control-structure, 
     */
    struct ObjectJc_t* memoryMng;
    //#endif

    int32 dummy; //further using

  }ObjectJc;

/**Compatibility: */
#define Object_Jc_t ObjectJc_t


/**Allocates an ObjectJc in the thread buffer. Such an instance must be used immediately, then it is similar to an embedded instance in the stack. 
 * It can be returned and used in the calling enviroment immediately or return. That is the difference to a embedded instance in the stack.
 * Only one instance can be located in the thread context. It is over-written if another instance is created in the thread context.
 */
ObjectJc* allocInThreadCxt_ObjectJc(int size, struct ThreadContextFW_t* _thCxt);



/** Macro for constant initialisation with a typesize and a given reflection class.
  * @param TYPESIZEOF see attribute ,,objectIdentSize,,.
  * @param REFLECTION the reflection class of the constant object. It may be ,,null,, also.
*/
#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) {TYPESIZEOF, OWNADDRESS, 0, kNoSyncHandles_ObjectJc, REFLECTION }



/** Macro for constant initialization with a IDENT and a given reflection class.
  * Use it to initialize global or stack variables in form:
  * ,,Type myData = { INITIALIZER_ObjectJc( myData, 123, &reflection_Type) };,,
  * ,,Type myData2 = { INITIALIZER_ObjectJc( myData2, 0, null) };  //set ident and reflection later.,,
  * @param OBJ the variable to initialize itself to store its address and gets its size. 
  * @param IDENT may be 0, see attribute ,,objectIdentSize,,. The size bits will be completed. 
  * @param REFLECTION maybe null, the reflection class of the constant object.
  * @since 2016-04: the better form.
*/
#define INITIALIZER_ObjectJc(OBJ, REFLECTION, IDENT) {sizeof(OBJ) | IDENT, &(OBJ), 0, kNoSyncHandles_ObjectJc, REFLECTION }

#define NULL_ObjectJc {0}

/**This macro defines a C-constant (with {..}) for initializing any instance which is derived from Object immediately.
 * @param OBJ The instance itself. It is used to store the OWNADDRESS and to build sizeof(OBJ) for the ObjectJc-part.
 */
#define CONST_Instance_ObjectJc(OBJ) { CONST_ObjectJc(sizeof(OBJ), &(OBJ), null), 0 }


/**Initialization of the basicly data of Object and set all user data to 0.
 * This method should be used for static and embedded instances especially in C environment
 * and inside a C++-constructor.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance). All data are set to 0.
 *                Don't use this kind of initialization for C++-classes, use sizeof(ObjectJc) for this argument than.
 * @param identObj An identification info, see [[class_ObjectJc.objectIdentSize]] 
 * return ythis
*/
/*NOTE: don't use a void* instead ObjectJc*, because a qualified casting have to be done using in C++ from inheriting classes. */
METHOD_C ObjectJc* init_ObjectJc(ObjectJc* ythis, int sizeObj, int identObj);




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
#define isValid_ObjectJc(THIZ) ( (THIZ) !=null && ((ObjectJc const*)(THIZ))->ownAddress == (THIZ))



/**Checks whether a reference refers a valid ObjectJc. A valid ObjectJc has a mark: Its own address
 * is stored in the Object.
 * @param THIZ any Object reference which contains { union { ObjectJc object; } base;  
 */
#define isNotInitialized_ObjectJc(THIZ) ( (THIZ)->base.object.ownAddress == null && (THIZ)->base.object.objectIdentSize == 0)





/**Checks the consistence of the given instance based on ObjectJc.
 * An Object should be initialized before it is used. This method should be used in the constructor
 * of all classes to check whether the initializing is done.
 * @param size The requested size of the instance.
 *             The instance is valid if the size saved in the element ,,objectIdentSize,, is >= size.
 *             A greater instance (derived) is accepted also.
 * @param clazzReflection instanceof_ObjectJc() will be tested. If this param is null, no test of reflection is done.
 *             Unsupported feature: If the reflection class of the instance is null, it will be set with this reference.
 *             But call setReflection_ObjectJc() instead before, because this method may be changed in future. It should only test, not set anything!
*/
METHOD_C void checkConsistence_ObjectJc(ObjectJc* ythis, int size, struct ClassJc_t const* clazzReflection, struct ThreadContextFW_t* _thCxt);



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

/**Returns a new Identification for an Object. This method may be implemented user-specific
 * to generate a log file with instantiated Objects.
 */
METHOD_C int newIdent_ObjectJc();




/*@CLASS_CPP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


#if defined(__CPLUSGEN) && defined(__cplusplus)



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
	  
	/** converts to the ObjectJcpp - pointer, superclass of all instances..
    A type casting to (ObjectJcpp*) applied to a pointer of interface type
    forces the using of the ObjectJcpp* - casting operator of the instance-type,
    mediate from the virtual table of the interface.
    Note that a casting to super or derived classes in C++ modifies the this-pointer
    with small adress modification to the right virtual table.
    The default implementation supplies no Reflection or ObjectJc-support.
    */
    public: virtual class ObjectJcpp* xxxtoObjectJcpp(){ return null; }

    /** converts to the ObjectJc- pointer, superclass of all instances..
    A type casting to (ObjectJc*) applied to a pointer of interface type
    forces the using of the ObjectJcpp* - casting operator of the instance-type,
    mediate from the virtual table of the interface.
    Note that a casting to super or derived classes in C++ modifies the this-pointer
    with small adress modification to the right virtual table.
    The default implementation supplies no Reflection or ObjectJc-support.
    */
    public: virtual ObjectJc* toObject(){ return null; }

    //#define toObject_Jc() toObject()

    /**returns a String which allows the test wether a instance
     * is type of a special user interface. In Java there is the operator instanceof
     * to test such things. 
     */
    public: virtual bool instanceof(const char* type){ return false; } 

    /**The constructor is called automatically in C++. Because it is contained as inline
     * in the header, the user don't need any other library to use it.
     */
    public: ObjectifcBaseJcpp(); //: significance_ObjectifcBase(123), significanceAddress_ObjectifcBase(null){}
    
  };

#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

  
/*@CLASS_C MtblHeadJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


struct Size_Mtbl_t;

/** The definition of ordered method pointer, it is a jump table.
  * The virtual methods are callable in a C-environment adequate to virtual methods in C++.
  * This struct of method pointer determines the order of virtual methods of ObjectJc for all implementation classes.
  */
typedef struct MtblHeadJc_t
{ /**The value of sign must be identically with the address of the sign_Mtbl_TYPE. Check it for safe access. */
  char const* sign;
  /**The sizeTable is really an simple int. But all members of Method table are from pointer type. casted internally. 
   * Check of sizeTable makes possible to use older implementation versions with less methods.
   * NOTE: don't use a void*, because all is compatible with it and no errors are signated.
   */
  struct Size_Mtbl_t* sizeTable;  
}MtblHeadJc;


/**Structure which represents the common MTB-ref-type. */
typedef struct ObjectJcMTB_t
{ struct Mtbl_ObjectJc_t* mtbl;
  ObjectJc* ref;
}ObjectJcMTB;

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
METHOD_C MtblHeadJc const* getMtbl_ObjectJc(ObjectJc const* ythis, char const* sign);

int getPosInMtbl_ObjectJc(ObjectJc const* thiz, char const* sign);

/**Builds a method table reference. */
METHOD_C ObjectJcMTB XXXmtblRef_ObjectJc(ObjectJc const* ythis, char const* sign);


#define SETMTBJc(DST, REF, TYPE) { (DST).ref = (TYPE*)(REF); (DST).mtbl = (DST).ref == null ? null : (Mtbl_##TYPE const*)getMtbl_ObjectJc(&(DST).ref->base.object, sign_Mtbl_##TYPE); }

/**Macro to get the method table from a given reference. 
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
METHOD_C typedef bool MT_equals_ObjectJc(ObjectJc* ythis, ObjectJc* second, struct ThreadContextFW_t* _thCxt);

/**This method should be called before the instance is deleted finally. It is called
 * by garbage collection. Some action such as deregister or free memory may be taken
 * from the users overload class.
 */
METHOD_C typedef void MT_finalize_ObjectJc(ObjectJc* ythis, struct ThreadContextFW_t* _thCxt);

/**This method supplies a hash code for thid onstance.
 */
METHOD_C typedef int32 MT_hashCode_ObjectJc(ObjectJc const* ythis, struct ThreadContextFW_t* _thCxt);

/**This method supplies a string representation of the content of the instance,
 * useable especially for debug or analyze information.
 */
METHOD_C typedef StringJc MT_toString_ObjectJc(ObjectJc* ythis, struct ThreadContextFW_t* _thCxt);




/** The definition of ordered method pointer, it is a jump table.
  * The virtual methods are callable in a C-environment adequate to virtual methods in C++.
  * This struct of method pointer determines the order of virtual methods of ObjectJc for all implementation classes.
  */
typedef struct Mtbl_ObjectJc_t
{ MtblHeadJc head;
  /**Methods of ObjectJc. */
  MT_clone_ObjectJc*    clone;
  MT_equals_ObjectJc*   equals;
  MT_finalize_ObjectJc* finalize;
  MT_hashCode_ObjectJc* hashCode;
  MT_toString_ObjectJc* toString;
} Mtbl_ObjectJc;




/**The override-able method toString tests the virtual table inside reflection
 * to call the correct toString-Method of the implementation class. */
StringJc toString_ObjectJc(ObjectJc* ithis, struct ThreadContextFW_t* _thCxt);


/** The implemented method for ObjectJc forward declared here.
 *  They should be known if a user class will not overload some methods from ObjectJc with its own methods
 *  but use this methods.
 *  In generally, implementation methods needn't be forward declared, they need only be defined in the C file.
 */
extern MT_clone_ObjectJc clone_ObjectJc_F;
extern MT_equals_ObjectJc equals_ObjectJc_F;
extern MT_finalize_ObjectJc finalize_ObjectJc_F;
extern MT_hashCode_ObjectJc hashCode_ObjectJc_F;
extern MT_toString_ObjectJc toString_ObjectJc_F;


/** The virtual table of non overloaded methods from object,
    useable as part of a users virtual table.
  */
#define CONST_MtblStd_ObjectJc \
{ clone_Object_F    \
, equals_Object_F   \
, finalize_Object_F \
, hashCode_Object_F \
, toString_Object_F \
}





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
