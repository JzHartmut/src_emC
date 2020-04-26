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
#ifndef DEF_ObjectJc_SIMPLE
#define DEF_ObjectJc_SIMPLE

//#define DEF_REFLECTION_NO

//#define DONOTUSE_REFLECTION_emC   //The reflection is not able to use here.

#ifndef DEF_ObjectJc_SIMPLE  //prevent warning if defined as compiler argument
#define DEF_ObjectJc_SIMPLE
#endif

/*@CLASS_C ClassJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


#define ObjectJc_s ObjectJc

#define ident_newAllocated_ObjectJc 0x0001



//Marker: ObjectJc is defined.
#define __ObjectJc_defined__

/**Initialize only the idInstanceType. */
#define CONST_ObjectJc(TYPESIZEOF, OWNADDRESS, REFLECTION) { TYPESIZEOF } 
//, { (char const*)(REFLECTION)} }


/** Macro for constant initialization with a IDENT and a given reflection class.
* Use it to initialize global or stack variables in form:
* * ,,Type myData = { INIZ_ObjectJc( myData, &refl_Type, 123), furtherData };,,
* * ,,Type myData = { { INIZ_ObjectJc( myData, &refl_Type), 123 }, furtherData};,,
* if the definition starts with a union{ ObjectJc obj;} base;
* You should use that {} -level which is related to the position of the ObjectJc-data in the instance.
* * ,,TypeDerived data = { { INIZ_DerivedData(data, &refl_TypeDerived, 0, furtherArgs)}, furtherData};,,
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











/*@CLASS_CPP ObjectJcpp @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

//#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)




#endif  //DEF_ObjectJc_SIMPLE
