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
* 2020-07: Hartmut extra definition for simple applications using  DEF_ObjectJc_SIMPLE

****************************************************************************/
#include <applstdef_emC.h>  //Note: define before include-guards because applstdef_emC,h may include this file too.
//The following include guard prevent twice include especially if applstdefJc.h includes this file already.
//It prevents including Object_emC.h too (same HGUARD), both are exclusively. 
#ifndef HGUARD_Object_emC
#define HGUARD_Object_emC

#ifndef DEF_ObjectJc_SIMPLE      //prevent warning on twice define the same
  #define DEF_ObjectJc_SIMPLE
#endif
#ifndef DEF_ObjectJc_SIMPLEST
  #define DEF_ObjectJc_SIMPLEST
#endif
//#include <emC/Base/MemC_emC.h>


//struct ThreadContext_emC_t;
//struct ClassJc_t;


//struct Size_Vtbl_t;

struct ClassJc_t;


/**Object is the superclass of all superclasses. In C-like manner it is a struct
* at begin of any class-like struct.
*
* This definition is a small variant for only simple capabilities 
* especially for less footprint or non-String-using target systems with usual 16 or 32 bit memory addresses.
* Some definitions and methods are common use-able, that methods are contained here too. 
*/
typedef struct  ObjectJc_T
{
  /**The identSize is helpfull to recognize the instance. 
  * The bit31 is used to detect whether it is initialized or not. */
  uint32 identSize;
  #define mInitialized_ObjectJc  0x80000000
  #define mArray_ObjectJc        0x40000000
  #define mInstanceType_ObjectJc 0x3fff0000  
  #define kBitInstanceType_ObjectJc 16
  #define mSize_ObjectJc         0x0000ffff   //size in memory words, max, 64 kByte
  //
  /**Array bit in a given ID. */
  #define mArrayId_ObjectJc        0x4000

} ObjectJc;

#define ID_refl_ObjectJc 0x0FFE


/*---------------------------------------------
const Initialization                         */

/**Initializing of a simple object.  */
#define INIZ_ObjectJc(OBJ, REFL, ID)  { ((((uint32)(ID_##REFL))<<kBitInstanceType_ObjectJc) & mInstanceType_ObjectJc)  | (sizeof(OBJ) & mSize_ObjectJc) }

/**Initialization of the basicly data of Object.
 * This method should be used for all instances.
 * @param addrInstance: The address of the instance itself, which contains ObjectJc. In C++ the instance address doesn't may be the same as ythis.
 *                      the offset to the instance itself will be stored to help data debugging.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance).
 * @param reflection The reflection class. It may be null if the reflections are not present.
 * @param identObj An identSize info, see [[attribute:_ObjectJc:objectIdentSize]]
 * @return the reference of the Object itself to use in argument lists (especially for C++ - ctor)
*/
extern_C ObjectJc* ctor_ObjectJc ( ObjectJc* othiz, void* ptr, int size, struct ClassJc_t const* refl, int idObj);

#ifdef DEF_REFLECTION_NO
#  define CTOR_ObjectJc(OTHIZ, ADDR, SIZE, REFL, ID) ctor_ObjectJc(OTHIZ, ADDR, SIZE, null, ID_##REFL)
#  define ALLOC_ObjectJc(SIZE, REFL, ID) alloc_ObjectJc(SIZE, null, ID_##REFL, _thCxt)
  //extern_C void inizReflid_ObjectJc(ObjectJc const* othiz, void* ptr, int size, uint id_refl, uint idObj);
#else
#  define CTOR_ObjectJc(OTHIZ, ADDR, SIZE, REFL, ID) ctor_ObjectJc(OTHIZ, ADDR, SIZE, &(REFL), ID)
#  define ALLOC_ObjectJc(SIZE, REFL, ID) alloc_ObjectJc(SIZE, &(REFL), ID, _thCxt)
#endif

extern_C bool checkStrict_ObjectJc ( ObjectJc const* thiz, uint size, struct ClassJc_t const* refl, uint ident);

extern_C bool checkStrictReflid_ObjectJc ( ObjectJc const* thiz, uint size, uint idRefl, uint ident, struct ThreadContext_emC_t* _thCxt);
extern_C bool checkInitReflid_ObjectJc ( ObjectJc* thiz, uint size, uint idRefl, uint ident, struct ThreadContext_emC_t* _thCxt);
#define CHECKstrict_ObjectJc(OTHIZ, SIZE, REFL, IDENT) checkStrictReflid_ObjectJc(OTHIZ, SIZE, ID_##REFL, IDENT, null)
#define CHECKinit_ObjectJc(OTHIZ, SIZE, REFL, IDENT) checkInitReflid_ObjectJc(OTHIZ, SIZE, ID_##REFL, IDENT, null)


/*---------------------------------------------
Initialization operations                         */


/**Sets the ident and size of an ObjectJc.
* The bit position of ident and size, and the bits to define which bits are using for ident and size [[mSizeBits_ObjectJc]]
* are calculated from given size and type.
* @param sizeObj The size which is valid for the memory-area, which is used from the derived whole instance.
* @param identObj any special ident. If 0, an automatically ident is built.
* @throws RuntimeException if the identObj and sizeObj are not matching. See Bits of [[class_ObjectJc_objectIdentSize]].
*/
extern_C void setSizeAndIdent_ObjectJc(ObjectJc* ythis, int sizeObj, int identObj);

#define setReflection_ObjectJc(OBJ, REFL, SIZE)


/*---------------------------------------------
Get operations for core properties          */

#define getClass_ObjectJc(THIZ) null
#define getTypeId_ObjectJc(THIZ){ ((THIZ)->identSize & mInstanceType_ObjectJc) >> kBitInstanceType_ObjectJc)
#define getSizeInfo_ObjectJc(THIZ) ((THIZ)->identSize & mSize_ObjectJc)
#define getIdentInfo_ObjectJc(THIZ) (0)

/**tests wether the given object is an instance of the requested Type.
* Javalike: instanceof-operator.
* @param ythis any Object
* @param reflection The reflection of the type to compare.
*/
extern_C bool instanceof_ObjectJc(ObjectJc const* ythis, struct ClassJc_t const* reflection);


/**tests wether the given object is an instance of the requested Type.
* Javalike: instanceof-operator.
* @param ythis any Object
* @param reflection The reflection of the type to compare.
*/
#ifdef DEF_REFLECTION_NO
  extern_C bool instanceofReflid_ObjectJc(ObjectJc const* ythis, uint reflId);
  #define INSTANCEOF_ObjectJc(OTHIZ, REFL) instanceofReflid_ObjectJc(OTHIZ, ID_##REFL)
#else
  #define INSTANCEOF_ObjectJc(OTHIZ, REFL) instanceof_ObjectJc(OTHIZ, &(REFL))
#endif

/*---------------------------------------------
Working operations                         */
#define setInitialized_ObjectJc(THIZ) { WR_CAST(ObjectJc*, THIZ)->identSize |= mInitialized_ObjectJc; }

#define isInitialized_ObjectJc(THIZ) ( ((THIZ)->identSize & mInitialized_ObjectJc )!=0)





/**Initializer for any instance with {0}. Should be used on stack variable especially before they are handled with a ctor...(...).*/
#define NULL_ObjectJc {0}


/**Returns a new Identification for an Object. This method may be implemented user-specific
* to generate a log file with instantiated Objects.
*/
extern_C int newIdent_ObjectJc();




extern_C ObjectJc* alloc_ObjectJc(int size, struct ClassJc_t const* refl, int id, struct ThreadContext_emC_t* thCxt);



#if defined(__cplusplus)



/** Superclass for class ObjectJcpp and especially for all interface classes.
This base class defines a method to convert this to ObjectJc*
especially necessary for interface classes.<br/>
The methods of this class should be implemented in any class
implementing any interface.
*/
class  ObjectJcpp
{
  public: virtual ObjectJc* toObject() = 0; //{ return null; }

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

/**The ClassJc is only used to assure the type information of an ObjectJc, not for symbolic access.*/
typedef struct ClassJc_t { 
  int32 id; 
  struct ClassJc_t const* superClass;
} ClassJc;




#define INIZ_ClassJc(REFL, TEXT) { ID_##REFL, null }
#define INIZsuper_ClassJc(REFL, TEXT, REFLSUPER) { ID_##REFL, REFLSUPER }



#endif //HGUARD_Object_emC
