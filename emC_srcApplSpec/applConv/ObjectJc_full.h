#ifndef HEADERGUARD_ObjectJc_full_h
#define HEADERGUARD_ObjectJc_full_h
/*This file is included in emC/Base/Object_emC.h depending on not defined DEF_ObjectJc_SIMPLE
 */



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
    #define mIdentSmall_objectIdentSize_ObjectJc  0x0fff0000

            /** This constant is used to shift the type info for small objects. */
    #define kBitIdentSmall_objectIdentSize_ObjectJc 16

            /** Size bits for medium objects, medium means up to 1 MByte. There are 10 bits
            * useable for 1023 medium types.
            */
    #define mSizeMedium_objectIdentSize_ObjectJc 0x000fffff

            /** This bits are used to store the type or size info for medium objects.
            */
    #define mIdentMedium_objectIdentSize_ObjectJc 0x0ff00000

            /** This constant is used to shift the type info for small objects. */
    #define kBitIdentMedium_objectIdentSize_ObjectJc 20

            /** Size bits for large objects up to 16 MByte.
            */
    #define mSizeLarge_objectIdentSize_ObjectJc  0x00ffffff

            /** This bits are used to store the type or instance info for large objects.
            There are only 5 bits useable for 31 large instances.
            */
    #define mIdentLarge_objectIdentSize_ObjectJc  0x1f000000

            /** This constant is used to shift the type info for small objects. */
    #define kBitIdentLarge_objectIdentSize_ObjectJc 24

    uint32 objectIdentSize;

    /**Posive value of offset to the beginn of block, able to use debugging data manually. 
    * If this Object is part of a BlockHeapBlockJc, bit 15 is set, but the rest is the positive offset to start of heap block.
    * This element is also used to mark a allocated but not used memory. =-1 after [[alloc_ObjectJc(...)]]
    *   and in [[INIZ_ObjectJc(...)]] 
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
* The headerfile <org/vishia/emC/Base/Object_emC.h> contains the definition of this ,,struct ObjectJc,, for common usage in C-Sources
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
{ /**The own address of the instance is saved in the instance itself. 
   * This value may be important if the data are transmitted 
   * into another system (evaluation of data) and some references 
   * between data are present. The evaluator may be able to find
   * the correct association between the instances by testing this value.
   * NOTE: It is a unnamed union to support 64 bit pointer 
   * if the data are transferred and the address should be adapted.
   */
  union { struct ObjectJc_t const* ownAddress; int32 ownAddress_i[2]; };

  /**The info about this type of the object. 
   * A Java-like reflection-concept is used.
   */
  union { struct ClassJc_t const* reflectionClass; int32 reflectionClass_i[2]; };

  /**Use int64 image for Simulink Busses. */
  State_ObjectJc state;
} ObjectJc;



/**Macro for constant initialisation with a typesize and a given reflection class.
* @param TYPESIZEOF see attribute ,,objectIdentSize,,.
* @param REFLECTION the reflection class of the constant object. It may be ,,null,, also.
* @deprecated use [[INITIALIZER_ObjectJc(...)]] instead
*/
//#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { { (ObjectJc*)(OWNADDRESS) }, { REFLECTION }, { TYPESIZEOF, 0 + (kNoSyncHandles_ObjectJc<<16) + 0}}
#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { { (ObjectJc const*)(OWNADDRESS) }, { REFLECTION }, { TYPESIZEOF, 0,  kNoSyncHandles_ObjectJc, 0, 0 }}
//#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) {TYPESIZEOF, OWNADDRESS, 0, kNoSyncHandles_ObjectJc, REFLECTION }



/** Macro for constant initialization with a IDENT and a given reflection class.
* Use it to initialize global or stack variables in form:
* * ,,Type myData = { INIZ_ObjectJc( myData, &refl_Type, 123), furtherData };,,
* * ,,Type myData = { { INIZ_ObjectJc( myData, &refl_Type), 123 }, furtherData};,, 
* if the definition starts with a union{ ObjectJc obj;} base;
* You should use that {} -level which is related to the position of the ObjectJc-data in the instance.
* * ,,TypeDerived data = { { INIZ_DerivedData(data, &refl_TypeDerived, 0, furtherArgs)}, furtherData};,,
* for a derived struct which have an adequate INIZ macro.
* * ,,Type myData2 = { INIZ_ObjectJc( myData2, 0, null) };  //set ident and reflection later.,,
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
#define INIZ_ObjectJc(OBJ, REFL, ID) { {(ObjectJc const*)&(OBJ)} , { REFL } , {{(int)sizeof(OBJ) | (int)(((ID)<<kBitIdentSmall_objectIdentSize_ObjectJc)), 0, kNoSyncHandles_ObjectJc, 0, 0 }}}
//???
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

/**Initialization of the basicly data of ObjectJc.
 * This routine should be used only for C, not for C++. The offsetToStartAddr is not set correctly.
 * Hence it is deprecated. Use [[iniz_ObjectJc(...)]] maybe with null for reflection argument.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance). All data are set to 0.
 *                Don't use this kind of initialization for C++-classes, use sizeof(ObjectJc) for this argument than.
 * @param identObj An identification info, see [[class_ObjectJc.objectIdentSize]] 
 * @deprecated
 * return thiz
 */
/*NOTE: don't use a void* instead ObjectJc*, because a qualified casting have to be done using in C++ from inheriting classes. */
METHOD_C ObjectJc* init_ObjectJc ( ObjectJc* thiz, int sizeObj, int identObj);

#define isInitialized_ObjectJc( THIZ) ((THIZ)->state.b.isInitialized !=0) 
#define setInitialized_ObjectJc( THIZ) { (THIZ)->state.b.isInitialized =1; } 

/**Initialization of the basicly data of Object.
* This method should be used for all instances.
* @param addrInstance: The address of the instance itself, which contains ObjectJc. 
    In C++ the instance address doesn't may be the same as ythis.
*                      the offset to the instance itself will be stored to help data debugging.
* @param sizeObj The size of the whole instance, use sizeof(TypeInstance). 
* @param reflection The reflection class. It may be null if the reflections are not present.
* @param identObj An identification info, see [[attribute:_ObjectJc:objectIdentSize]] 
* return ythis, the reference of the Object itself.
*/
extern_C void iniz_ObjectJc ( ObjectJc* ythis, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj);

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






/** gets the size of the Object stored in attribute objectIdentSize. This value helps to step through data
* particularly by using direct composed plain old data,
* but the user is responsible for the exactly realization.
*/
METHOD_C int getSizeInfo_ObjectJc(ObjectJc const* ythis);

/**gets the ident and size of the Object stored in attribute objectIdentSize.
* This value is useable as debug information.
*/
METHOD_C int getIdentInfo_ObjectJc(ObjectJc const* ythis);


extern_C int getTypeId_ObjectJc(ObjectJc* thiz);

//#define getIdentInfo_ObjectJc(YTHIS) (

/** gets the reflection class.*/
METHOD_C struct ClassJc_t const* getClass_ObjectJc(ObjectJc const* ythis);

/**tests wether the given object is an instance of the requested Type.
* Javalike: instanceof-operator.
* @param thiz any Object null is admissible then returns false. If the reflection are faulty, an exception is thrown.
* @param reflection The reflection of the type to compare. The chararcter sequence is tested.
* In opposite to [[instanceof_ObjectJc(...)]] they may be more as one reflection instance possible.
* That is especially in dll libraries with static linked reflection.
*/
METHOD_C bool instanceof_s_ObjectJc(ObjectJc const* ythis, char const* reflection);

/*@CLASS_CPP ObjectJcpp @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


//#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
#if defined(__cplusplus)



/** Superclass for class ObjectJcpp and especially for all interface classes.
This base class defines a method to convert this to ObjectJc*
especially necessary for interface classes.<br/>
The methods of this class should be implemented in any class
implementing any interface.
*/
class  ObjectJcpp
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
public: ObjectJcpp(); //: significance_ObjectifcBase(123), significanceAddress_ObjectifcBase(null){}

};

#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

/*@CLASS_C VtblHeadJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/**This is a only forward declared struct used in [[VtblHeadJc]] for the size value stored as pointer. */
struct Size_Vtbl_t;
#define Size_Vtbl_t Size_Vtbl_t

#define DEF_ClassJc_Vtbl

#define NrofMethodsForSize_VTBL_Jc(NR) (struct Size_Vtbl_t*)((2 +NR) * sizeof(void*)) 

/** The definition of ordered method pointer, it is a jump table.
* The virtual methods are callable in a C-environment adequate to virtual methods in C++.
* This struct of method pointer determines the order of virtual methods of ObjectJc for all implementation classes.
*/
typedef struct VtblHeadJc_T
{ /**The value of sign must be identically with the address of the sign_Vtbl_TYPE. Check it for safe access. */
  char const* sign;
  /**The sizeTable is really an simple int. But all members of Method table are from pointer type. casted internally. 
  * Check of sizeTable makes possible to use older implementation versions with less methods.
  * NOTE: don't use a void*, because all is compatible with it and no errors are signated.
  */
  struct Size_Vtbl_t* sizeTable;  
}VtblHeadJc;

#define VtblHeadJc VtblHeadJc

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


extern char const sign_Vtbl_ObjectJc[]; 
extern char const signEnd_Vtbl_ObjectJc[];

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
*    Use  ,,sign_Vtbl_TYPE,,   in the user's software to determine the type. 
*    The sign... is defined with the Method table and reflection for any class.
* @return null or the reference of the method table of the required base class.
* The Method table may be a derived table depending on sign parameter..
* Whether the method table is derived or not, it means wether a up-casting is allowed,
* depends on a derived class. 
*/
extern_C VtblHeadJc const* getVtbl_ObjectJc(ObjectJc const* ythis, char const* sign);
#define getVtbl_ObjectJc getVtbl_ObjectJc


int getPosInVtbl_ObjectJc(ObjectJc const* thiz, char const* sign);
#define getPosInVtbl_ObjectJc getPosInVtbl_ObjectJc


METHOD_C VtblHeadJc const* checkVtbl_ObjectJcTT(ObjectJc const* ythis, int ix, char const* sign, struct ThreadContext_emC_t* _thCxt);




#define SETMTBJc(DST, REF, TYPE) { (DST).ref = (struct TYPE##_t*)(REF); (DST).mtbl = (DST).ref == null ? null : (Vtbl_##TYPE const*)getVtbl_ObjectJc(&(DST).ref->base.object, sign_Vtbl_##TYPE); }
#define SETMTBJc_XXX(DST, REF, TYPE) { (DST).ref = (TYPE*)(REF); (DST).mtbl = (DST).ref == null ? null : (Vtbl_##TYPE const*)getVtbl_ObjectJc(&(DST).ref->base.object, sign_Vtbl_##TYPE); }

/**Macro to get the method table from a given reference. 
* @Deprecated. Don't use the macro. It is better to write the two routines one after another. Keep clearly.
* @param REF A reference to any type which is based on Object. It should hava a ,,union{ ... ObjectJc object; } base;,,
* @param TYPE The Typ of the method table. It is used to build ,,Vtbl_TYPE const*,, and ,,sign_Vtbl_TYPE,,
* @return casted returnvalue of ,,getMtableObjectJc(othis, sign),,. 
*         returns null if the instance doesn't have a method table. An NullPointerException outside may be thrown.
*         This behaviour is able to use whether base methods of ObjectJc are available on any instance.
* @throws ClassCastException If the object isn't based on the required type.
*/
#define MTBCALLJc(REF, TYPE) ((Vtbl_##TYPE const*)getVtbl_ObjectJc(&(REF)->base.object, sign_Vtbl_##TYPE))


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


#define Vtbl_ObjectJc Vtbl_ObjectJc

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
#define CONST_VtblStd_ObjectJc \
{ clone_ObjectJc_F    \
, equals_ObjectJc_F   \
, finalize_ObjectJc_F \
, hashCode_ObjectJc_F \
, toString_ObjectJc_F \
}




/*@CLASS_C QueryInterface_SYS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#if defined(__CPLUSGEN) && defined(__cplusplus)


/**This interface supports a commonly query possibility of a interface connection to forein instances.
*/   
class QueryInterface_SYS  
{
  /**query an instance. The instance type should be derivated from ObjectJcpp*. 
  * Use the following sequence of secure query:
  * ,,ObjectJcpp* ptr = myRequire->queryInterface("Name_ifc_Instance");                //quere the instance
  * ,,if(!ptr->instanceof("Name_ifc")) THROW(ClassCastException, "failed queryInterface", 0);  //test the correct type
  * ,,myRef = static_cast<Name_ifc*>(ptr);                                                   //cast to required type.
  */
public : virtual ObjectJcpp* queryInterface(const char* name)=0;
};


#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)


#endif //HEADERGUARD_ObjectJc_full_h