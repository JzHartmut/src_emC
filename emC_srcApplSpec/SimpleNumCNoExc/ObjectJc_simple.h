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
 * @version 0.83
 * list of changes:
 * 2017-06-02: JcHartmut creation
 *
 ****************************************************************************/
//The following include guard prevent twice include of the alternate ObjectJc.h
//
#ifndef __applstdef_emC_h__
  #include <applstdef_emC.h>
#endif
#ifndef __ObjectJc_simple__
#define __ObjectJc_simple__

//#define DEF_REFLECTION_NO

//#define DONOTUSE_REFLECTION_emC   //The reflection is not able to use here.

#ifndef DEF_ObjectJc_SIMPLE  //prevent warning if defined as compiler argument
#define DEF_ObjectJc_SIMPLE
#endif

/*@CLASS_C ClassJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/*@CLASS_C ObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Object is the superclass of all superclasses. In C-like manner it is a struct
 * at begin of any class-like struct.
 *
 * This definition is a small variant for only simple capabilities 
 * especially for less footprint or non-String-using target systems with usual 16 or 32 bit memory addresses.
 * Some definitions and methods are common use-able, that methods are contained here too. 
 */
typedef struct  ObjectJc_t
{
  /**The idInstanceType is helpfull to recognize the instance. 
   * The bit31 is used to detect whether it is initialized or not. */
  uint32 idInstanceType;
  
  #define mType_ObjectJc 0xffff
  #define kBitType_ObjectJc 0
  #define mInstance_ObjectJc 0x7fff0000
  #define kBitInstance_ObjectJc 16
  #define mInitialized_ObjectJc 0x80000000

  /**The reference to the type is either an index to a central pointer table (for 64-bit-addresses) or the address itself.
   * In any case this is a 32-bit-location which references the type.
   */
  #ifdef DEF_ObjectJc_REFLREF
    HandlePtr_emC(struct ClassJc_t const, reflection);
  #endif
} ObjectJc;

#define ObjectJc_s ObjectJc

#define ident_newAllocated_ObjectJc 0x0001



//Marker: ObjectJc is defined.
#define __ObjectJc_defined__

/**Initialize only the idInstanceType. */
#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { TYPESIZEOF } 
//, { (char const*)(REFLECTION)} }


/** Macro for constant initialization with a IDENT and a given reflection class.
* Use it to initialize global or stack variables in form:
* * ,,Type myData = { INIZ_ObjectJc( myData, &reflection_Type, 123), furtherData };,,
* * ,,Type myData = { { INIZ_ObjectJc( myData, &reflection_Type), 123 }, furtherData};,,
* if the definition starts with a union{ ObjectJc obj;} base;
* You should use that {} -level which is related to the position of the ObjectJc-data in the instance.
* * ,,TypeDerived data = { { INIZ_DerivedData(data, &reflection_TypeDerived, 0, furtherArgs)}, furtherData};,,
* for a derived struct which have an adequate INIZ macro.
* * ,,Type myData2 = { INIZ_ObjectJc( myData2, 0, null) };  //set ident and reflection later.,,
* @param OBJ the variable to initialize itself to gets its size.
*        Note: The size of the OBJ must be lesser than 64 kByte (see [[mSizeSmall_objectIdentSize_ObjectJc]]
* @param REFLECTION maybe null, the reflection class of the constant object.
* @param IDENT may be 0, see attribute ,,objectIdentSize,,.
* The value of this argument will be written to the bits 31..16 of idInstanceType. It means the value is shifted to left.
* The size bits are calculated with sizeof(OBJ) and are written to idInstanceType too, right aligend to bit 0.
* It means, the value 0 for this argument leads to store the size of the OBJ only.
* 
* If the sizeof(OBJ) may be > 64k, you should provide a value other than 0 in the form
*
*
* @since 2016-04: the better form.
*/
//#define INIZ_ObjectJc(OBJ, REFL, ID)  { ((ID)<<16) + sizeof(OBJ) } //, { (char const*)(REFL)} }

//the following line does not compile in C! because it uses another defined data.
//#define INIZ_ObjectJc(OBJ, REFL, ID)  { ((ID)<<16) + (((REFL)->idType) & mType_ObjectJc) } //, { (char const*)(REFL)} }

/**Initializing of a simple object. It uses the address of the reflection definition, lo 16 bit (64 kByte) as type identifier.
 * Note: All reflection should be define in the same compiling unit to have different addresses in the 64 kByte-space.
 */
//Note: the & 0xffff forces error in C 'is not a contant' in VS15


#ifdef DEF_ObjectJc_REFLREF
#  define INIZ_ObjectJc(OBJ, REFL, ID)  { (((uint32)(ID))<<16) + sizeof(OBJ), { (uint32)(REFL) } } //, { (char const*)(REFL)} }
#else 
#  define INIZ_ObjectJc(OBJ, REFL, ID)  { (((uint32)(ID))<<16) + (((int16_t)(intptr_t)REFL) /*& 0xffff*/) } //, { (char const*)(REFL)} }
#endif






#define setReflection_ObjectJc(OBJ, REFL, SIZE)

#define setInitialized_ObjectJc(THIZ) { (THIZ)->idInstanceType |= mInitialized_ObjectJc; }

#define isInitialized_ObjectJc(THIZ) ( ((THIZ)->idInstanceType & mInitialized_ObjectJc )!=0)


#define init_ObjectJc(THIZ, SIZE, IDENT) { (THIZ)->idInstanceType = (IDENT) & 0x7fffffff; } 

inline int getTypeId_ObjectJc(ObjectJc* thiz){ return (thiz->idInstanceType >> kBitType_ObjectJc) & mType_ObjectJc; }




#ifdef DEF_REFLECTION_OFFS
#define getSizeInfo_ObjectJc(THIZ) ((THIZ)->idInstanceType & mType_ObjectJc)
#else
#define getSizeInfo_ObjectJc(THIZ) ((THIZ)->idInstanceType & mType_ObjectJc)
#endif


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




#endif  //__ObjectJc_simple__
