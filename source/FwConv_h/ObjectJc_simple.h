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
#include <applstdefJc.h>
#ifndef __objectBaseC__h__
#define __objectBaseC__h__
#define __ObjectJc_simple__

/**Object is the superclass of all superclasses. In C-like manner it is a struct
 * at begin of any class-like struct.
 *
 * The headerfile <Fwc/objectBaseC.h> contains the definition of this ,,struct ObjectJc,, for common usage in C-Sources
 * which does not use concepts of ,,ObjectJc,, but should know this embedded struct. 
 * Some definitions and methods are common use-able, that methods are contained here too. 
 */
typedef struct  ObjectJc_t
{
  int identification;
  int isInitialized;
} ObjectJc;


/**Initialize only the identification. */
#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { TYPESIZEOF }

/**Initialization of the basicly data of Object.
 * This method should be used for all instances.
 * @param addrInstance: The address of the instance itself, which contains ObjectJc. In C++ the instance address doesn't may be the same as ythis.
 *                      the offset to the instance itself will be stored to help data debugging.
 * @param sizeObj The size of the whole instance, use sizeof(TypeInstance). 
 * @param reflection The reflection class. It may be null if the reflections are not present.
 * @param identObj An identification info, see [[attribute:_ObjectJc:objectIdentSize]] 
 * return ythis, the reference of the Object itself.
*/
//METHOD_C ObjectJc* initReflection_ObjectJc(ObjectJc* ythis, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj);
#define initReflection_ObjectJc(THIZ, ADDR, SIZE, REFL, IDENT) { (THIZ)->identification = (IDENT); }

typedef struct ClassJc_t
{ ObjectJc obj;
  char name[32];
  int ident;
} ClassJc;


#endif  //__objectBaseC__h__