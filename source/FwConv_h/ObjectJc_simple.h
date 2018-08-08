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
 * The headerfile <Fwc/objectBaseC.h> contains the definition of this ,,struct ObjectJc,, for common usage in C-Sources 
 * with all capabilities.
 * This definition is a small variant for only simple capabilities 
 * especially for less footprint or non-String-using target systems with usual 16 or 32 bit memory addresses.
 * Some definitions and methods are common use-able, that methods are contained here too. 
 */
typedef struct  ObjectJc_t
{
  /**The instanceId is helpfull to recognize the instance. 
   * The bit31 is used to detect whether it is initialized or not. */
  int32 instanceId;
  
  /**The reference to the type is either an index to a central pointer table (for 64-bit-addresses) or the address itself.
   * In any case this is a 32-bit-location which references the type.
   */
  //OS_HandlePtr(struct ClassJc_t const, type);
  OS_HandlePtr(char const, type);
} ObjectJc;


#define ident_newAllocated_ObjectJc 0x0001



//Marker: ObjectJc is defined.
#define __ObjectJc_defined__

/**Initialize only the instanceId. */
#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { TYPESIZEOF, { (char const*)(REFLECTION)} }

/**Initialization of the basicly data of Object.
 * This method should be used for all instances.
 * @param addrInstance: The address of the instance itself, which contains ObjectJc. In C++ the instance address doesn't may be the same as ythis.
 *                      the offset to the instance itself will be stored to help data debugging.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance). 
 * @param reflection The reflection class. It may be null if the reflections are not present.
 * @param identObj An instanceId info, see [[attribute:_ObjectJc:objectIdentSize]] 
 * return ythis, the reference of the Object itself.
*/
//METHOD_C ObjectJc* initReflection_ObjectJc(ObjectJc* ythis, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj);
#define initReflection_ObjectJc(THIZ, ADDR, SIZE, REFL, IDENT) { (THIZ)->instanceId = (IDENT); (THIZ)->typeId = SIZE; }

#define checkStrict_ObjectJc(THIZ, SIZE, IDENT, REFL, THCXT) ( (IDENT) !=0 && (IDENT) != (THIZ)->instanceId ? -1 : (THIZ)->instanceId )


#define setInitialized_ObjectJc(THIZ) { (THIZ)->instanceId |= 0x80000000; }

#define isInitialized_ObjectJc(THIZ) ( (THIZ)->instanceId & 0x80000000 )


#define init_ObjectJc(THIZ, SIZE, IDENT) { (THIZ)->instanceId = (IDENT) & 0x7fffffff; } 


/**The Reflection is reduced to a character constant which contains the name of the type, helpfull for debug. 
 * This struct needs only 6 int32 words per existing type.
 */
typedef struct ClassJc_t
{
  ObjectJc obj;
  //char const* name;
  char name[32];
  int32 ident;
} ClassJc;

extern ClassJc const reflection_ClassJc;

#define CONST_NAME_ClassJc(NAME, IDENT) { CONST_ObjectJc(0, null, &reflection_ClassJc), NAME, IDENT }

#endif  //__ObjectJc_simple__