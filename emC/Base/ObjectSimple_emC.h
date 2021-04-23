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
* @content This file defines all necessities for using ObjectJc in simple applications.
* It is the base for Object_emC.h too (there included). 
* It is the minimal base for some struct or interface of the framework layer,
* which should also be designable without knowledge of the Jc-layer, 
* but useable outside of the users algorithm if necessary with ReflectionJc-concept.
*
* @author Hartmut Schorrig
* @version 2.0
* list of changes:
* 2020-07: Hartmut definition for simple applications using  DEF_ObjectSimple_emC

****************************************************************************/
#ifndef HGUARD_applstdef_emC
  #include <applstdef_emC.h>  //Note: define before include-guards because applstdef_emC,h may include this file too.
#endif

//The following include guard prevent twice include especially if applstdefJc.h includes this file already.
#ifndef HGUARD_ObjectSimple_emC
#define HGUARD_ObjectSimple_emC


#ifndef DEFINED_MemC
#define DEFINED_MemC
/**Defines the standard-MemC-type. 
 * @since 2019-10: The pointer type is now a struct type Addr8_emC*, not a MemUnit* like before. 
 *        Reason:  a const char* pointer is aligned to 1 on X86-64 platform, but all other pointer should reference
 *        8-aligned addresses (4-aligned for 32-bit-platform) to assure fast memory access. The compiler arranges
 *        the data in a proper form. But the compiler supposed that the casted address to char const*
 *        may have a 1-allignment and produces this justifiable warning. If the non-casted address is used, it is ok.
 * The addr element is now 8-aligned for 64-bit-applications (4-aligned for 32 bit)
 * @since 2019-10: The name is change to addr from ref in STRUCT_AddrVal_emC (before: OS_PtrValue_DEF). 
 *        Hence using location which may conflict in address calculation are conspicuous by compiler errors. 
 *        Do not replace ref to addr without thinking about. Use the new [[addOffset_MemC(...)]] macro for address calculation.
 */
typedef STRUCT_AddrVal_emC(MemC, Addr8_emC);
#endif

#ifndef HGUARD_ObjectRefl_emC  //it is simple included, not via Object_emC.h

  #if !defined(DEF_ObjectJc_SIMPLE) && !defined(DEF_ObjectJc_REFLREF)
    #ifdef DEF_REFLECTION_NO
      #define DEF_ObjectJc_SIMPLE
    #else
      #define DEF_ObjectJc_REFLREF
    #endif
  #endif

  #ifdef DEF_REFLECTION_FULL
    #error DEF_REFLECTION_FULL needs include of Object_emC.h
  #endif
  #ifdef USE_BlockHeap_emC
    #error USE_Blockheap_emC needs include of Object_emC.h
  #endif

  #ifdef USE_BlockHeap_emC
    #error USE_Blockheap_emC need Object_emC.h
  #endif

  //either it is defined already because this is included in Object_emC.h 
  //or prevent include Object_emC.h, this file is sufficient:
  #define HGUARDRefl_Object_emC  
#endif

#ifdef DEF_REFLECTION_NO
  #if defined(DEF_ObjectJc_REFLREF) || defined(DEF_ObjectJcpp_REFLECTION)
    #error if ObjectJc needs reflection information, it cannot select DEF_REFLECTION_NO. Select at least DEF_REFLECTION_SIMPLE.
  #endif
#endif


//#include <emC/Base/MemC_emC.h>


struct ClassJc_t;


/**Object is the superclass of all superclasses. In C-like manner it is a struct
* at begin of any class-like struct.
*
* This definition is a small variant for only simple capabilities 
* especially for less footprint or non-String-using target systems with usual 16 or 32 bit memory addresses.
* Some definitions and methods are common use-able, that methods are contained here too. 
*/
#ifndef DEFINED_ObjectJc
typedef struct  ObjectJc_T
{
  /**The identSize is helpfull to recognize the instance. 
  * The bit31 is used to detect whether it is initialized or not. */
  uint32 identSize;
  #define mInitialized_ObjectJc  0x80000000
  #define mArray_ObjectJc        0x40000000
  #define mLocked_ObjectJc       0x20000000
  #define mInstanceType_ObjectJc 0x1fff0000  
  #define mIdentSmall_ObjectJc   0x1fff0000
  #define kBitInstanceType_ObjectJc 16
  #define kBitIdentSmall_ObjectJc   16
  #define mSize_ObjectJc         0x0000ffff   //size in memory words, max, 64 kByte
  //
  /**Array bit in a given ID. */
  #define mArrayId_ObjectJc        0x4000

  #ifdef DEF_ObjectJc_REFLREF
    #define mInstance_ObjectJc   0x1fff0000
    #define kBitInstance_ObjectJc 16
    /**The reference to the type information. */
    struct ClassJc_t const* reflection;
  #endif
} ObjectJc;
#endif

#define ID_refl_ObjectJc 0x0FFE
#ifndef DEF_REFLECTION_NO
extern_C const struct ClassJc_t refl_ObjectJc;
#endif

/*---------------------------------------------
const Initialization                         */

/**Initializing of a simple object.  */
#ifdef DEF_ObjectJc_SIMPLE
  #define INIZ_ObjectJc(OBJ, REFL, ID)  { ((((uint32)(ID_##REFL))<<kBitInstanceType_ObjectJc) & mInstanceType_ObjectJc)  | (uint32)(sizeof(OBJ) & mSize_ObjectJc) }
#elif !defined(DEF_ObjectJcpp_REFLECTION)  //for that, definition in Object_emC.h
  #define INIZ_ObjectJc(OBJ, REFL, ID)  \
   { ( (((uint32)(ID))<<kBitIdentSmall_ObjectJc) \
       & (mIdentSmall_ObjectJc | mArray_ObjectJc) \
     ) | sizeof(OBJ) \
   , &(REFL) \
   }
#endif
/*---------------------------------------------
Initialization and check operations                         */


/**Initialization of the basicly data of Object.
 * This method should be used for all instances.
 * @param addrInstance: The address of the instance itself, which contains ObjectJc. In C++ the instance address doesn't may be the same as ythis.
 *                      the offset to the instance itself will be stored to help data debugging.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance).
 * @param reflection The reflection class. It may be null if the reflections are not present.
 * @param identObj An identSize info, see [[attribute:_ObjectJc:objectIdentSize]]
 * @return the reference of the Object itself to use in argument lists (especially for C++ - ctor)
*/
extern_C struct ObjectJc_T* ctor_ObjectJc ( struct ObjectJc_T* othiz, void* ptr, uint size, struct ClassJc_t const* refl, uint idObj);

#ifdef DEF_REFLECTION_NO
#  define CTOR_ObjectJc(OTHIZ, ADDR, SIZE, REFL, ID) ctor_ObjectJc(OTHIZ, ADDR, SIZE, null, ID_##REFL)
#  define ALLOC_ObjectJc(SIZE, REFL, ID) allocRefl_ObjectJc(SIZE, null, ID_##REFL)
  //extern_C void inizReflid_ObjectJc(struct ObjectJc_T const* othiz, void* ptr, int size, uint id_refl, uint idObj);
#else
#  define CTOR_ObjectJc(OTHIZ, ADDR, SIZE, REFL, ID) ctor_ObjectJc(OTHIZ, ADDR, SIZE, &(REFL), ID)
#  define ALLOC_ObjectJc(SIZE, REFL, ID) allocRefl_ObjectJc(SIZE, &(REFL), ID)
#endif


/**Sets the ident and size of an ObjectJc.
* The bit position of ident and size, and the bits to define which bits are using for ident and size [[mSizeBits_ObjectJc]]
* are calculated from given size and type.
* @param sizeObj The size which is valid for the memory-area, which is used from the derived whole instance.
* @param identObj any special ident. If 0, an automatically ident is built.
* @throws RuntimeException if the identObj and sizeObj are not matching. See Bits of [[class_ObjectJc_objectIdentSize]].
*/
extern_C void setSizeAndIdent_ObjectJc(struct ObjectJc_T* ythis, int sizeObj, int identObj);

/**Set the ident. 
 * * ident if 0 or <0 then an automatic counted ident will be set.
 * * should be < mIdentSmall_ObjectJc or mIdentMedium or Large due to the given initialization.
 * * if > admissible then THROW 
 * * can contain the mArrayId_ObjectJc flag. But if the flag is set already in thiz, it will be not reset.    
 */
extern_CCpp void setIdent_ObjectJc(struct ObjectJc_T* thiz, int ident);

#ifdef DEF_REFLECTION_NO
  //ObjectJc without reflection, this routine is empty
  #define setReflection_ObjectJc(OBJ, REFL, SIZE)
#else
  extern_C void setReflection_ObjectJc(struct ObjectJc_T* thiz, struct ClassJc_t const* reflection, uint size);
#endif



/**Checks the consistence of the given instance based on ObjectJc.
 * An Object should be initialized before it is used  with [[CTOR_ObjectJc(...)]] 
 * or as static instance with [[INIZ_ObjectJc(...)]]. 
 * This method should be used in the constructor
 * of all classes to check whether the base initializing is done.
 * Hint: Use the macro form CHECKstrict_ObjectJc(...) and use it inside an ASSERT_emC line.
 * * Then it does not need any calculation time or space in a well tested target environment.
 * * In a test or development environment it throws on error, it is safe.
 * * It regards DEF_REFLECTION_NO for poor targets. 
 *
 * @param othiz pointer to the ObjectJc part of the instance. Used decicated access. Do never use a simple casting!
 * @param size 0 or the requested size of the instance. If 0 then the size info will not be checked.
 *             The instance is valid if the size saved in the element ,,objectIdentSize,, is >= size.
 *             A greater instance (derived) is also accepted.
 * @param refl Given Reflection Information as instance denotation. 
 *             For the macro version and if DEF_REFLECTION_NO is set, 
 *             then an ID_##REFL is build for the ident which is ored with the mArrayId_ObjectJc
 *             of the ident value for integer identification of the type. This argument is null in that case. 
 * @param ident 0 or the requested indent. If 0 then the ident info will not be checked.
 *             For the macro version and DEF_REFLECTION_NO only the mArrayId_ObjectJc bit is used here.
 * @return true if all ok, false on error.
 */
extern_C bool checkStrict_ObjectJc ( struct ObjectJc_T const* othiz, uint size, struct ClassJc_t const* refl, uint ident);
#ifdef DEF_REFLECTION_NO
  #define CHECKstrict_ObjectJc(OTHIZ, SIZE, REFL, IDENT) checkStrict_ObjectJc(OTHIZ, SIZE, null, (ID_##REFL) | ((IDENT) & mArrayId_ObjectJc))
#else 
  #define CHECKstrict_ObjectJc(OTHIZ, SIZE, REFL, IDENT) checkStrict_ObjectJc(OTHIZ, SIZE, &(REFL), IDENT)
#endif






/**Checks the consistence of the given instance based on ObjectJc and initialize the missing information. 
 * An Object should be proper initialized before it is used with [[CTOR_ObjectJc(...)]] 
 * or as static instance with [[INIZ_ObjectJc(...)]]. 
 * This method should be used in the constructor of classes to check whether the initializing is done.
 * It supplements the missing information. But this routine is a loop hole for a incorrect initialization. 
 * It should never be uses in an ASSERT_emC(...), use checkStrict there. 
 * @param size The requested size of the instance.
 *             The instance is valid if the size saved in the element ,,objectIdentSize,, is >= size.
 *             A greater instance (derived) is accepted also.
 * @param refl instanceof_ObjectJc() will be tested. If this param is null, no test of reflection is done.
 *             Unsupported feature: If the reflection class of the instance is null, it will be set with this reference.
 *             But call setReflection_ObjectJc() instead before, because this method may be changed in future. It should only test, not set anything!
 * @param ident 0 or the requested indent. If 0 then the ident info will not be checked.
 * @return true if ok, 
 */
extern_C bool checkInit_ObjectJc ( ObjectJc* thiz, uint size, struct ClassJc_t const* clazzReflection, uint ident);
#ifdef DEF_REFLECTION_NO
  #define CHECKinit_ObjectJc(OTHIZ, SIZE, REFL, IDENT) checkInit_ObjectJc(OTHIZ, SIZE, null, (ID_##REFL) | ((IDENT) & mArrayId_ObjectJc))
#else 
  #define CHECKinit_ObjectJc(OTHIZ, SIZE, REFL, IDENT) checkInit_ObjectJc(OTHIZ, SIZE, &(REFL), IDENT)
#endif


/*---------------------------------------------
Get operations for core properties          */

#ifdef DEF_ObjectJc_REFLREF
  #define getClass_ObjectJc(THIZ) ((THIZ)->reflection)
  #define getTypeId_ObjectJc(THIZ) ((THIZ)->reflection !=null ? (THIZ)->reflection->idType : 0) 
#else 
  #define getClass_ObjectJc(THIZ) null
  #define getTypeId_ObjectJc(THIZ){ ((THIZ)->identSize & mInstanceType_ObjectJc) >> kBitInstanceType_ObjectJc)
#endif

#ifndef DEF_ObjectJc_LARGESIZE
  /**Builds the size of the whole instance, for C++ usage inclusively the C++ parts. */
  #define getSizeInfo_ObjectJc(THIZ) ((THIZ)->identSize & mSize_ObjectJc)
  
  #define getIdentInfo_ObjectJc(THIZ) ((uint)(((THIZ)->identSize & (mInstanceType_ObjectJc | mArray_ObjectJc)) >> kBitInstanceType_ObjectJc))
#endif //#else: see Object_emC.h, large size is not supported for ObjectSimple.

#define isArray_ObjectJc(THIZ) (((THIZ)->identSize & mArray_ObjectJc) !=0)


/**tests wether the given object is an instance of the requested Type.
* Javalike: instanceof-operator.
* @param ythis any Object
* @param reflection The reflection of the type to compare.
*/
extern_C bool instanceof_ObjectJc ( struct ObjectJc_T const* ythis, struct ClassJc_t const* reflection);


/**tests wether the given object is an instance of the requested Type.
* Javalike: instanceof-operator.
* @param ythis any Object
* @param reflection The reflection of the type to compare.
*/
#ifdef DEF_REFLECTION_NO
  extern_C bool instanceofReflid_ObjectJc ( struct ObjectJc_T const* ythis, uint reflId);
  #define INSTANCEOF_ObjectJc(OTHIZ, REFL) instanceofReflid_ObjectJc(OTHIZ, ID_##REFL)
#else
  #define INSTANCEOF_ObjectJc(OTHIZ, REFL) instanceof_ObjectJc(OTHIZ, &(REFL))
#endif

/*---------------------------------------------
Working operations                         */
//#define setInitialized_ObjectJc(THIZ) { WR_CAST(struct ObjectJc_T*, THIZ)->identSize |= mInitialized_ObjectJc; }
extern_C void setInitialized_ObjectJc ( struct ObjectJc_T const* thiz);

#define isInitialized_ObjectJc(THIZ) ( ((THIZ)->identSize & mInitialized_ObjectJc )!=0)

#ifndef DEF_ObjectJc_SYNCHANDLE

static inline void lock_ObjectJc ( ObjectJc* thiz) { thiz->identSize |= mLocked_ObjectJc; }

static inline bool isLocked_ObjectJc ( ObjectJc* thiz) { return (thiz->identSize & mLocked_ObjectJc) !=0; }

static inline void unlock_ObjectJc ( ObjectJc* thiz)  { thiz->identSize &= ~mLocked_ObjectJc; }

#endif




/**Initializer for any instance with {0}. Should be used on stack variable especially before they are handled with a ctor...(...).*/
#define NULL_ObjectJc {0}


/**Returns a new Identification for an Object. This method may be implemented user-specific
* to generate a log file with instantiated Objects.
*/
extern_C int newIdent_ObjectJc();


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
*        The bits kIsMediumSize_ObjectJc and mIsLargeSize_ObjectJc
*        are regarded especially.
* @return the reference to the initialized Object.
* @throws IndexOutOfBoundsException if the size doesn't match to typeInstanceIdent. 
* @throws RuntimeException if a memory space can't allocate.
*/
extern_C struct ObjectJc_T* allocRefl_ObjectJc ( uint size, struct ClassJc_t const* refl, uint typeInstanceIdent);

/**traditional usual in Java2C sources: */
#define alloc_ObjectJc(SIZE, ID, _THCXT) allocRefl_ObjectJc(SIZE, null, ID)

/**Supplies the rest of block if the Object is allocated in a block heap, or an empty MemC if there is no rest space. 
* @param size The requested size (>0) or the requested number of references (<0). 
*        If < 0 then the available size is returned, where the given number of references is considered (this value negative).
* @return A MemC-information which is placed immediate after the Object, or this size_MemC(returnObject) is 0.
* The implementation of this method depends from a BlockHeap-Concept and is located there.
*/
METHOD_C MemC getRestBlock_ObjectJc(ObjectJc const* ythis, int size, struct ThreadContext_emC_t* _thCxt);


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
#ifdef DEF_BlockHeap_GARBAGECOLLECTOR
extern_C void activateGC_ObjectJc(void const* object, void const* exclObject, struct ThreadContext_emC_t* _thCxt);
#else
#define activateGC_ObjectJc(OBJ, EXCL, THCXT)
#endif

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
#ifdef DEF_BlockHeap_GARBAGECOLLECTOR
  extern_C void setBackRefJc(void* reference, void const* instance);
#else 
  #define setBackRefJc(REF, OBJ)
#endif
/** Clears a reference in any reference management system.
*  The reference itself will be not stored here, it should be done outside because better
*  pointer type checking. A back reference to refbase is stored in the block of the heap,
*  and the Index of this back reference is stored in refbase.
*
*  If src is not inside a block heap, a 0 value is setted to *refbase.
*
*  @ param reference address of the enhanced reference
*/
#ifdef DEF_BlockHeap_GARBAGECOLLECTOR
  extern_C void clearBackRefJc(void* reference);
#else
  #define clearBackRefJc(REF)
#endif

extern_C void finalize_ObjectJc_F(ObjectJc const* ythis, ThCxt* _thCxt);


extern_C StringJc toString_ObjectJc_F(ObjectJc const* ythis, struct ThreadContext_emC_t* _thCxt);

extern_C StringJc toString_ObjectJc ( ObjectJc const* thiz, ThCxt* _thCxt);

#ifndef DEF_REFLECTION_FULL
//Note: this file is also included if DEF_ObjectSimple_emC is not set, 
//      inside the ObjectRefl_emC. 
//      This class definition is used anyway if DEF_REFLECTION_FULL is not set.

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
  uint32 idType;   // sizeReflOffs;

  #ifndef DEF_NO_StringUSAGE
  char const* name;
  #endif

  #ifdef DEF_REFLECTION_OFFS
  /**The lo-part (16 bit) of the address of this element is used as type ident. */
  int32 const* reflOffs;
  #endif
  struct ClassJc_t const* superClass;
} ClassJc;





/**There are some variants of the macro INIZ_ClassJc(OBJ, NAME, REFLOFFS) 
* and INIZsuper_ClassJc(OBJ, NAME, REFLOFFS, REFLSUPER)
* depending of the existing elements in ClassJc:
*/
#ifndef NO_PARSE_ZbnfCheader
#ifdef DEF_NO_StringUsage
//#  define INIZtypeOnly_ClassJc(OBJ, NAME) { (uint32)(intptr_t)&(OBJ)}
#  ifdef DEF_ObjectJc_REFLREF
#    define INIZ_ClassJc(OBJ, NAME) { 0 }
#  else
#    define INIZ_ClassJc(OBJ, NAME) { ID_##OBJ }
#  endif

#  ifdef DEF_REFLECTION_OFFS   //a field for reflOffs is given, but initialize with null
#    ifdef DEF_ObjectJc_REFLREF
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { 0, null, REFLSUPER }
#    else   //no field for superClass given
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { ID_##OBJ, null}
#    endif
#  else      //no field for reflOffs given
#    ifdef DEF_ObjectJc_REFLREF
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { 0, REFLSUPER }
#    else   //no field for superClass given
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { ID_##OBJ }
#    endif
#  endif
#else
//#  define INIZtypeOnly_ClassJc(OBJ, NAME) { (int)(intptr_t)&(OBJ), NAME}
#  ifdef DEF_ObjectJc_REFLREF
#    define INIZ_ClassJc(OBJ, NAME) { 0, NAME }
#  else
#    define INIZ_ClassJc(OBJ, NAME) { ID_##OBJ, NAME }
#  endif
#  ifdef DEF_REFLECTION_OFFS   //a field for reflOffs is given, but initialize with null
#    ifdef DEF_ObjectJc_REFLREF
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { 0, NAME, null, REFLSUPER }
#    else   //no field for superClass given
#      define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { ID_##OBJ, NAME, null}
#    endif
#  else      //no field for reflOffs given 
#    define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { 0, NAME, REFLSUPER }
#  endif
#endif
#endif//NO_PARSE_ZbnfCheader


extern_C ClassJc const refl_ClassJc;

#endif //ifndef DEF_REFLECTION_FULL


/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define ID_refl_ClassJc 0x0FFC

//extern_C ClassJc const refl_null;
//#define ID_refl_null 0



#endif //HGUARD_ObjectSimple_emC
