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

struct ClassJc_t;

/**Object is the superclass of all superclasses. In C-like manner it is a struct
 * at begin of any class-like struct.
 *
 * The headerfile <emC/Object_emC.h> contains the definition of this ,,struct ObjectJc,, for common usage in C-Sources 
 * with all capabilities.
 * This definition is a small variant for only simple capabilities 
 * especially for less footprint or non-String-using target systems with usual 16 or 32 bit memory addresses.
 * Some definitions and methods are common use-able, that methods are contained here too. 
 */
typedef struct  ObjectJc_t
{
  /**The idInstanceType is helpfull to recognize the instance. 
   * The bit31 is used to detect whether it is initialized or not. */
  int32 idInstanceType;
  
#define mType_ObjectJc 0xffff
#define kBitType_ObjectJc 0
#define mInstance_ObjectJc 0xffff
#define kBitInstance_ObjectJc 16

  /**The reference to the type is either an index to a central pointer table (for 64-bit-addresses) or the address itself.
   * In any case this is a 32-bit-location which references the type.
   */
  //HandlePtr_emC(struct ClassJc_t const, type);
  //HandlePtr_emC(char const, type);
} ObjectJc;

#define ObjectJc_s ObjectJc

#define ident_newAllocated_ObjectJc 0x0001



//Marker: ObjectJc is defined.
#define __ObjectJc_defined__

/**Initialize only the idInstanceType. */
#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { TYPESIZEOF, { (char const*)(REFLECTION)} }


/** Macro for constant initialization with a IDENT and a given reflection class.
* Use it to initialize global or stack variables in form:
* * ,,Type myData = { INIZ_objReflId_ObjectJc( myData, &reflection_Type, 123), furtherData };,,
* * ,,Type myData = { { INIZ_objReflId_ObjectJc( myData, &reflection_Type), 123 }, furtherData};,,
* if the definition starts with a union{ ObjectJc obj;} base;
* You should use that {} -level which is related to the position of the ObjectJc-data in the instance.
* * ,,TypeDerived data = { { INIZ_DerivedData(data, &reflection_TypeDerived, 0, furtherArgs)}, furtherData};,,
* for a derived struct which have an adequate INIZ macro.
* * ,,Type myData2 = { INIZ_objReflId_ObjectJc( myData2, 0, null) };  //set ident and reflection later.,,
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
#define INIZ_objReflId_ObjectJc(OBJ, REFL, ID)  { ((ID)<<16) + sizeof(OBJ), { (char const*)(REFL)} }



/**Initialization of the basicly data of Object.
 * This method should be used for all instances.
 * @param addrInstance: The address of the instance itself, which contains ObjectJc. In C++ the instance address doesn't may be the same as ythis.
 *                      the offset to the instance itself will be stored to help data debugging.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance). 
 * @param reflection The reflection class. It may be null if the reflections are not present.
 * @param identObj An idInstanceType info, see [[attribute:_ObjectJc:objectIdentSize]] 
 * return ythis, the reference of the Object itself.
*/
//METHOD_C ObjectJc* initReflection_ObjectJc(ObjectJc* ythis, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj);
//#define initReflection_ObjectJc(THIZ, ADDR, SIZE, REFL, IDENT) { (THIZ)->idInstanceType = ((IDENT)<<16) + (SIZE); (THIZ)->ptype = *(REFL); }
#ifdef __USE_REFLECTION__
  /**initializes with reflection which are defined with the ,,ClassJc,, struct in this header. */
  #define initReflection_ObjectJc(THIZ, ADDR, SIZE, REFL, IDENT) { (THIZ)->idInstanceType = ((IDENT)<<16) + ((REFL)->ixType & 0xffff); }
#else
  /**Initialize with ignoring the REFL information, for compatibility with the same source which uses but does not define the reflection instance. */
  #define initReflection_ObjectJc(THIZ, ADDR, SIZE, REFL, IDENT) { (THIZ)->idInstanceType = ((IDENT)<<16); }
#endif

#define checkStrict_ObjectJc(THIZ, SIZE, IDENT, REFL, THCXT) ( (IDENT) !=0 && (IDENT) != (THIZ)->idInstanceType ? -1 : (THIZ)->idInstanceType )


#define setInitialized_ObjectJc(THIZ) { (THIZ)->idInstanceType |= 0x80000000; }

#define isInitialized_ObjectJc(THIZ) ( (THIZ)->idInstanceType & 0x80000000 )


#define init_ObjectJc(THIZ, SIZE, IDENT) { (THIZ)->idInstanceType = (IDENT) & 0x7fffffff; } 

inline int getTypeId_ObjectJc(ObjectJc* thiz){ return (thiz->idInstanceType >> kBitType_ObjectJc) & mType_ObjectJc; }


/**The Reflection is reduced to a character constant which contains the name of the type, helpfull for debug. 
 * This struct needs only 6 int32 words per existing type.
 */
typedef struct ClassJc_t
{
  int ixType;   // sizeReflOffs;
  int const* reflOffs;
} ClassJc;

extern ClassJc const reflection_ClassJc;

#define CONST_NAME_ClassJc(NAME, IDENT) { CONST_ObjectJc(0, null, &reflection_ClassJc), NAME, IDENT }

#endif  //__ObjectJc_simple__
