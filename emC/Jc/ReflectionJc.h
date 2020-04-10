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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.83
 * @content Interface for Reflection
 *
 * @author Jchartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2012-04-07 Hartmut new: nrofBytesScalarTypes_ClassJc[], reflection__char16Jc
 * 2010-02-07 Hartmut new: reflection_floatBigEndian
 * 2010-01-17: Hartmut corr: for C++. but FieldJcpp, ClassJcpp won't be supported as of now.
 * 2009-11-25: Hartmut:
 *   new: String_ClassJc as type in ScalarTypes_ClassJc.
 *   new: REFLECTION_StringJc
 *   new: reflection_int16BigEndian etc, see os_endian.h
 * 2008-04-22: Hartmut rename: MT_void_Method_void instead VoidMethodVoid etc.
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#ifndef __ReflectionJc_h__
#define __ReflectionJc_h__

#include <applstdef_emC.h>
//to include with _Jc, inside ReflectionJc.h the ObjectJc.h will be included, but than the wrapperdefines are missing
#include <emC/Base/Object_emC.h>
//#include <Jc/ObjectJc.h>
//#include <emC/Base/SimpleC_emC.h>
#include <emC/Jc/ReflMemAccessJc.h>

/**This routine should be invoked on start of the application. 
 * Yet it is only necessary for DEF_HandlePtr64
 */
char const* init_ReflectionJc(void);

#ifdef DEF_ObjectJc_FULL

/*@DEFINE_C FieldJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**FieldJc: Defintion of struct FieldJc in emC/Base/Object_emC.h */





//#define const_FieldJc(SNAME, NAME, TYPE, MODI) { /*CONST_ObjectJc(TYPESIZEOF_FieldJc, null), */const_String(SNAME), TYPE, MODI, OFFSET_FieldJc(NAME), &DECLARING_CLASS_FieldJc.reflection }
#define const_FieldJc(SNAME, NAME, TYPE, MODI) { SNAME, 0, TYPE, MODI, OFFSET_FieldJc(NAME), 0, &DECLARING_CLASS_FieldJc.clazz }

//#define CONST_ARRAYFIELDJc(SNAME, NAME, TYPE, MODI) { SNAME, TYPE, MODI, ( (int)&( ((CLASS_CURRENTJc*)(0x1000))->data->NAME ) - (int)&( ((CLASS_CURRENTJc*)(0x1000))->data )), TYPE, &BASE_REFLECTION_CURRENTJc.CLASS_CURRENTJc.clazz }
/** Defines the constant value of a field instance.
  * The followed defines have to be defined before:
  * *REFLECTION_CURRENTJc
  */
#define CONST_ARRAYFIELDJc(SNAME, NAME, TYPE, MODI) { SNAME, 0, TYPE, MODI, ( (int)&( ((CLASS_CURRENTJc*)(0x1000))->data->NAME ) - (int)&( ((CLASS_CURRENTJc*)(0x1000))->data )), 0, REFLECTION_CURRENTJc }

/**Defines a field as constant structure.
 * @param SNAME name of field element as string literal.
 * @param NAME identifier name of the field element in the C-structure.
 * @param TYPE type of the name, with Reflection_NAME the associated classJc is designated.
 * @param MODI Mofifier, using values of enum type Modifier_reflectJc_t.
 */
//#define CONST_FIELDJc(SNAME, NAME, TYPE, MODI) { SNAME, TYPE, MODI,(int)(&( ((CLASS_CURRENTJc*)(0x1000))->NAME )) - (int)((ObjectJc*)((CLASS_CURRENTJc*)(0x1000))), REFLECTION_CURRENTJc }
#define CONST_FIELDJc(SNAME, OFFSET, TYPE, MODI) { SNAME, 0, TYPE, MODI, OFFSET, 0, REFLECTION_CURRENTJc }

/**Defines a field as constant empty structure.
 */
#define NULL_FIELDJc() { "", 0, null, 0, 0, null }

/** Constant Definition of a FieldJc-instance inside a whole reflection definition.
  * @param CLASS Name of the Type wherein this field is defined. The Value is used  to calculate the offset of the element
  *              and to build the pointer to the declaring class in Form reflection##CLASS.clazz.
  * @param SNAME String given name of the field. It should be identical with NAME, but with quotion marks.
  * @param NAME  identifier of the element inside the Type CLASS.
  * @param TYPE  The type of the the element, the reflection class is build with reflection##TYPE
  * @param MODI  Modifier, see CLASS_C ModifierJc.
  */
#define CONST_FieldJc(CLASS, SNAME, NAME, TYPE, MODI) { SNAME, 0, REFLECTION_##TYPE, MODI, (int)&( ((CLASS*)(0x1000))->NAME ) - 0x1000, 0 }
//#define CONST_FieldJc(CLASS, SNAME, NAME, TYPE, MODI) { SNAME, 0, &reflection##TYPE.clazz, MODI, (int)&( ((CLASS*)(0x1000))->NAME ) - 0x1000, &reflection##CLASS.clazz }


#define const_ObjectJcpp_FieldJc(SNAME, NAME, TYPE) const_FieldJc(SNAME, NAME, TYPE, mObjectJcpp_FieldJc)
#define const_ObjectJc_FieldJc  (SNAME, NAME, TYPE) const_FieldJc(SNAME, NAME, TYPE, mObjectJc_FieldJc)




/**Macro for a constant head of FieldJc array useable to define the constants for reflection. New since 2007.09
 */
#define CONST_ARRAYHEAD_FieldJc(NAME) CONST_ObjectArrayJc(FieldJc, ARRAYLEN(REFLECTION_IMAGE.attributes_##NAME.data), 0, null, &REFLECTION_IMAGE.attributes_##NAME)

/**Macro for a constant head of FieldJc array useable to define the constants for reflection. New since 2007.09
 */
#define CONST_ARRAYHEAD_z_FieldJc(SIZE, OWNADDRESS) CONST_ObjectArrayJc(FieldJc, SIZE, 0, null, OWNADDRESS)


/**initializes a FieldJc, see [[ctorc_FieldJc(...)]].
 * @param rawMem raw memory area, it may be uninitialized. 
 *        The size may be greater as necessary. The constructor initializes only its own area.
 * @throws IllegalArgumentException if the sizeof rawMem is to less.  
 */
METHOD_C FieldJc* ctorM_FieldJc(MemC rawMem);


/**initializes a FieldJc. 
 * All content is set to 0.
 */
METHOD_C void ctorc_FieldJc(FieldJc* ythis);



/**Gets the absolute adress of the element represented by this field inside the given Instance. 
 * It is assumed, that the given instance matches to thiz Field.
 * The type given in thiz->[[declaringClass_FieldJc]] should be the type of the given instance.
 *
 * If thiz FieldJc describes a reference type, not the referenced data but the address of the reference is returned.
 *
 * Simple field, also if the field is a reference type:
 *  intance-->[ ...some fields]  
 *            [ ...           ]  
 *            [ this field----]<--<<This reference will be returned.
 *            [ ...           ] 
 *
 * Embedded-array-field, also if the field-elements are a reference types:
 *  intance-->[ ...some fields  ]  
 *            [ ...             ]  
 *            [ [this field is] ]
 *            [ [an aarry ....] ]
 *            [ [..element<---]-]--<<This reference will be returned.
 *            [ [..element    ] ]
 *            [ ...             ]
 *
 * If the field references an array, the address of the field itself is returned.
 *
 * @param instance the Object. It need not derivated from ObjectJc, it may be any struct or class,
 *            but the type should matched to the ClassJc description getted with getDeclaringClass_FieldJc(ythis).
 * @param bFieldAddr If it is true, then 'instance' contains the address of the field already. 
 *            This method is then used only to calculate the address of an element inside the array,
 *            if it this is an array-kind-element. This functionality is used internally.
 * @param sVaargs The method can have one or more indices to index an element in the array,
 *            if ythis is an array-field. The sVaarg-string contains one or more characters "I"
 *            to designate that the following variable arguments are from type int. This concept of
 *            processing a variable argument list is established with the Java2C-translator. In Java
 *            the type of the elements of a variable argument list are well known in Runtime,
 *            other than its usual in C. This String defines the types. It the type is null or empty,
 *            no variable arguments are given.
 * @param vaargs indices for indexing an array element.
 * @return The address of the field or the address of an element inside the array-kind-field with the given indices.
 *         Note: To get the address of elements of a container field, use [[>getAddrElement_V_FieldJc(...)]]
 */
METHOD_C MemSegmJc getMemoryAddress_FieldJc(const FieldJc* thiz, MemSegmJc instance, bool bFieldAddr, char const* sVaargs, va_list vaargs);


/**Gets the absolute adress of the container represented by this field inside obj. It is assumed that the obj represented that object,
 * which contains really this field. Otherwise the behavior is undefined.
 *
 * At example: If a field references an int[]-Array (at ex int32Array-Typ in ObjectJc.h), this method returns the address
 * of the whole array instance. 
 * 
 * The container contains the reference. The container may be referenced too. 
 * A simplest container is a simple reference, than the container is embedded.
 * A more complex container may be an ObjectArrayJc, or some UML-Containers. It may be embedded or not.
 * 
 * Variant if the container is referenced:
 *  intance-->[ ...some fields]  
 *            [ ...           ]  
 *            [ this field----]--+-->[container....]
 *            [ ...           ]  |   [  refOfData--]-->[the data]
 *                               |   
 *                               +--<<This reference will be returned.
 *
 * Variant if the container is embedded in the intstance:
 *  intance-->[ ...some fields  ]  
 *            [ ...             ]  
 *      +---->[ [this field is] ]
 *      |     [ [a container..] ]
 *      |     [ [refOfData----]-]-->[the data]
 *      |     [ ...             ]
 *      |   
 *      +--<<This reference will be returned.
 *
 * See method [[>getAddrElement_V_FieldJc(...)]], this methods accesses inside the container with a given index.
 *
 * @param instance the Object. It shouln't derivated from ObjectJc, it may be any struct or class,
 *             but the type should matched to the ClassJc description getted with getDeclaringClass_FieldJc(ythis).
 * @param sVaargs The method can have one or more indices to index an element in the array,
 *            if ythis is an array-field. The sVaarg-string contains one or more characters "I"
 *            to designate that the following variable arguments are from type int. This concept of
 *            processing a variable argument list is established with the Java2C-translator. In Java
 *            the type of the elements of a variable argument list are well known in Runtime,
 *            other than its usual in C. This String defines the types. It the type is null or empty,
 *            no variable arguments are given.
 * @param vaargs indices for indexing an array element.
 *  @return if the container is an embedded element, this method returns the same value as getMemoryAddress_FieldJc(...),
 *          but if it is referenced, the referenced address is returned. The bits mContainerReference_Modifier_reflectJc in bitModifiers
 *          are tested to get the result.
 */
METHOD_C MemSegmJc getContainerAddress_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, va_list vaargs);



/**Gets the address of the element described with the field of the given object.
 * It regards whether the field is of container type, it regards the index.
 * @param address The address of the reference, it may be the address of a container element.
 * @param sVaargs The method can have one or more indices to index an element in the array,
 *            if ythis is an array-field. The sVaarg-string contains one or more characters "I"
 *            to designate that the following variable arguments are from type int. This concept of
 *            processing a variable argument list is established with the Java2C-translator. In Java
 *            the type of the elements of a variable argument list are well known in Runtime,
 *            other than its usual in C. This String defines the types. It the type is null or empty,
 *            no variable arguments are given.
 * @param vaargs indices for indexing an array element.
 * @returns the address of the reference maybe in a container or the address of the reference immediately, if it isn't a container. 
 *          If the contained instances in the container are embedded in the container, this address is equal with the address of the instance.
 *          If the instances in the container are references, this is the address where the reference to the instance is found.
 *          The type of the reference should be regarded. Check ,,(getModifiers_FieldJc(field) & mAddressing_Modifier_reflectJc),,
 *          to detect which to do whith the address.   
 * @throws IndexOutOfBoundsException if the idx is fault.
 * @since 2009-11-26, it is necessary to set references with the ''inspector''-Tool.
 */
METHOD_C MemSegmJc getAddrElement_V_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, va_list vaargs);



/**Gets the address of the element described with the field of the given object.
* It regards whether the field is of container type, it regards the index.
* @param address The address of the reference, it may be the address of a container element.
* @param sVaargs The method can have one or more indices to index an element in the array,
*            if ythis is an array-field. The sVaarg-string contains one or more characters "I"
*            to designate that the following variable arguments are from type int. This concept of
*            processing a variable argument list is established with the Java2C-translator. In Java
*            the type of the elements of a variable argument list are well known in Runtime,
*            other than its usual in C. This String defines the types. It the type is null or empty,
*            no variable arguments are given.
* @param vaargs indices for indexing an array element.
* @returns the address of the reference maybe in a container or the address of the reference immediately, if it isn't a container.
*          If the contained instances in the container are embedded in the container, this address is equal with the address of the instance.
*          If the instances in the container are references, this is the address where the reference to the instance is found.
*          The type of the reference should be regarded. Check ,,(getModifiers_FieldJc(field) & mAddressing_Modifier_reflectJc),,
*          to detect which to do whith the address.
* @throws IndexOutOfBoundsException if the idx is fault.
* @since 2018-11-02, without va_list.
*/
METHOD_C MemSegmJc getAddressElement_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);




/**Gets the absolute address of the indexed element of a UML-specific container element known as UML_LinkedList.
 * The algorithm should be specified in the users area (extra file.c) because it is UML-Framework-specific.
 * @param address The address of the container element.
 * @param idx the index
 * @throws IndexOutOfBoundsException if the idx is fault.
 */
METHOD_C MemSegmJc getRefAddrUML_LinkedList_FieldJc(MemSegmJc container, char const* sVaargs, va_list vaargs, ThCxt* _thCxt);

/**Gets the absolute address of the indexed element of a UML-specific container element known as UML_ArrayList.
 * The algorithm should be specified in the users area (extra file.c) because it is UML-Framework-specific.
 * @param address The address of the container element.
 * @param idx the index
 * @throws IndexOutOfBoundsException if the idx is fault.
 */
METHOD_C MemSegmJc getRefAddrUML_ArrayList_FieldJc(MemSegmJc container, char const* sVaargs, va_list vaargs, ThCxt* _thCxt);

/**Gets the absolute address of the indexed element of a UML-specific container element known as UML_Map.
 * The algorithm should be specified in the users area (extra file.c) because it is UML-Framework-specific.
 * @param address The address of the container element.
 * @param idx the index
 * @throws IndexOutOfBoundsException if the idx is fault.
 */
METHOD_C MemSegmJc getRefAddrUML_Map_FieldJc(MemSegmJc container, char const* sVaargs, va_list vaargs, ThCxt* _thCxt);


/**Gets the object represented by the Field ythis from an given object.
 * If it is not a complex datatype but an simple type (int, float and others),
 * this method returns null. This is in opposite to Java, java wrappes the primitive type.
 *
 * If the object it is a C++ class and it is derived from ObjectJc, 
 * this method returns the pointer to the baseclass ,,ObjectJc,, of the instance. 
 * If the instance itself with its really type should be gotten, a ,,<dynamic_cast>(ptr),,
 * is necessary, usual in C++.
 *
 * If the object isn't based on ObjectJc, the address of that entry in the instance is returned,
 * which is matching to the type of the field. It means, if multi-inheritance is used in C++,
 * it may not be the really address of the instance. Than a dynamic_cast from the known pointer
 * with the correct type to the type of the instance supplies the really instance-address. The type
 * of the instance isn't able to evaluate with reflection in this case, it should be known by the programmer.
 *
 * If the object is located in an external memory, the reference in that memory with the adequate
 * segment information is returned. 
 *
 * @param obj The Object. In opposite to Java it may not based on Object.
 *     The declaring class of the FieldJc must match to the type of Object, that is the condition.
 *     If the Class description of the declaring class of the Field don't request, that obj is based on ObjectJc,
 *     the Field describes at example a simple structure. But the getField-method isn't able to test it.
 * @param idx Index, used if the Field describes an ObjectArrayJc or an container or UML-container.
 *     This is an additional argument in opposite to Java. The reason is: In Java an array or container everytime
 *     is accessible outside the reflections, because the containers such as LinkedList have own reflections
 *     and own access methods, and the arrays have the own Element length.
 *     But in C there is the possibility to describe elements of arrays or containers with this Field information,
 *     but only the address of the container or ObjectArrayJc-base is given. The get-Method allows the access to
 *     this elements. If no idx is necessary, the idx is ignored.
 */
METHOD_C MemSegmJc get_FieldJc(FieldJc const* ythis, MemSegmJc instance, char const* sVaArgIdx, ...);


#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  inline MemSegmJc get_FieldJc(FieldJc const* ythis, ObjectJcpp* obj, int idx)
  { ObjectJc* obj1 = obj->toObject();
  MemSegmJc instance = CONST_MemSegmJc(obj1, 0);
    return get_FieldJc(ythis, instance, "I", idx);
  }
#endif



/**Searches an object with given start object and path. This is a static method in context of ClassJc.
 * The returned object may be based on ObjectJc or not. In C/C++ systems, especially in user oriented data structures,
 * the inheritance of ObjectJc is not taken for granted. In this cases the describing ClassJc information will be kept as getType_FieldJc()
 * in the Field information of this element, not in the implementing instance.
 *
 * @param sPath The path to the object. At example ,,"myObj.theElement[20].x",,.
 * @param startObj The object from which the path starts, it have to be based on ObjectJc.
 * @param field Reference to a FieldJc reference, it will be set as return with the last found Field information.
 * @param idx Reference to a int, it will be set as return with the last found index information in path,
 *            or set to -1 if no index is given at last position.
 * @return The founded object matching to the returned field. The Object is the last but one part of the VariablePath,
 *         but the returned field is the last part of the Variable path. The returned idx is >=0 if the last part
 *         contains an index information.
 */
//Note: implemented in Java2C
METHOD_C MemSegmJc XXXXXXXsearchObject_ClassJc(StringJc sPath, ObjectJc* startObj, FieldJc const** field, int* idx);



/**Gets the Object and the describing class of the Object from given FieldJc in given object. See get_FieldJc(...)
 * If the object is non based on ObjectJc, it hasn't own reflection infos inside it,
 * but the reflection info to the pointer to it is known as a Class type, returned by getType_FieldJc.
 * In this case this information is supplied.
 * The class info always matches to the returned obj.
 * If the field describes a primitive type, it returns null and sets obj to null.
 *
 * @param obj src obj as input to which the FieldJc matches. Because reflections are also
 *            useable in C for non-ObjectJc-inherited instances, it is a void*-reference.
 *            It may be the return value of the method searchObject_ClassJc(...), where ythis is the outputted field from there.
 * @param idx Index, used if the Field describes an ObjectArrayJc or an container or UML-container.
 *     This is an additional argument in opposite to Java. The reason is: In Java an array or container everytime
 *     is accessible outside the reflections, because the containers such as LinkedList have own reflections
 *     and own access methods, and the arrays have the own Element length.
 *     But in C there is the possibility to describe elements of arrays or containers with this Field information,
 *     but only the address of the container or ObjectArrayJc-base is given. The get-Method allows the access to
 *     this elements. If no idx is necessary, the idx is ignored.
 * @param retObj Reference of type void* for the getted obj as output. It may be null if this output is not necessary.
 *
 */
METHOD_C MemSegmJc getObjAndClass_FieldJc(FieldJc const* ythis, MemSegmJc instance, struct ClassJc_t const** retClazz, char const* sVaargs, ...);
//METHOD_C struct ClassJc_t const* getClassAndObj_FieldJc(FieldJc const* ythis, MemSegmJc instance, MemSegmJc* retInstance, int idx);




/**Gets the actual length of the array if the field describes a reference of an array or collection,
 * @param obj The Object matching to the Field
 * @return the actual length, it may be 0.
 * @throws NoSuchFieldException if it describes not an array or collection.
 */
METHOD_C int getArraylength_FieldJc(FieldJc const* ythis, MemSegmJc instance);

METHOD_C int getArraylengthUML_LinkedList_FieldJc(MemSegmJc instance);


METHOD_C int getArraylengthUML_ArrayList_FieldJc(MemSegmJc instance);


METHOD_C int getArraylengthUML_Map_FieldJc(MemSegmJc instance);





METHOD_C bool  getBoolean_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C char getChar_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C int8 getByte_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C int16 getShort_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C int32 getInt_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

/**Set the bits of a bitfield descibed by the given field.
 * @param obj The object to get the value inside.
 * @return The value for the bits. The bits are adjusted rigth here, they will be shifted from the correct bit position.
 *         NOTE: It is a int-value, may be 16 bit, because the register width is proper for that.
 * @javalike: Because java doesn' know bitfields, it isn't java-like, but it is proper and necessary for C-programming.
 */
METHOD_C int16 getBitfield_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C float getFloat_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C double getDouble_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);



/**Gets a String representation of the content of this FieldJc in the given instance.
 * <ul>
 * <li>If the field is a Object-compatible type (a reference) and the reference is not null, then the Object.toString()-method
 * is invoked with this reference. 
 * <li>If the reference is null, than "null" is returned.
 * <li>If the field is a primitive type, the String representation of its content is returned.
 * <li>For C-usage: If the field references a non-Object-instance, "@addr" is returned, 
 *   where addr is the memory address of the referenced instance (the reference value). 
 * </ul>
 * @param instance The instance where this FieldJc is member of.
 * @param ix 0 or more indices if the Field is an array or container.
 * @return A String which represents the content of the field.
 * @throws IllegalArgumentException
 * @throws IllegalAccessException
 */
METHOD_C StringJc getString_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);



/** Returns the reference to the data which is described with thiz FieldJc and the given instance.
  * If thize FieldJc describes a reference, the reference in the instance is derefered and the reference to the real data is returned. 
  * This method is not javalike.
  * Because the type of the field is not known in this context, the reference is of type void*.
  * The user should cast it outside to the type of the field. The casting is only admissible
  * to the exactly type of the field.
  * If it is a primitive type, the reference may be casted to the reference to the primitive type,
  * such as (int*). If the reference is a complex type, especially a interface in C++, the cast
  * is only admissible to the interface type, not to a supposed derivated type. The casting to
  * a derivated type in C++ is only admissible with static_cast<type>, because the compiler
  * should adjust the reference.
  *@since 2010-07-01: Uses anyway, returns the address of the container or primitive type, if it isn't a reference,
  *     returns the reference to the instance if it is a reference.
  */
METHOD_C MemSegmJc getReference_FieldJc(FieldJc const* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C MemSegmJc getReference_V_FieldJc(FieldJc const* ythis, MemSegmJc instance, char const* sVaargs, va_list vaargs);

/**Returns the memory address of an equal identifier of the address, maybe in a remote memory. */
METHOD_C intptr_t getMemoryIdent_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C intptr_t getMemoryIdent_V_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, va_list vaargs);



METHOD_C int64 getInt64_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C bool setBoolean_FieldJc(const FieldJc* ythis, MemSegmJc obj, bool val, char const* sVaargs, ...);

METHOD_C char setChar_FieldJc(const FieldJc* ythis, MemSegmJc obj, char val, char const* sVaargs, ...);

METHOD_C int8 setByte_FieldJc(const FieldJc* ythis, MemSegmJc obj, int8 val, char const* sVaargs, ...);

METHOD_C int16 setShort_FieldJc(const FieldJc* ythis, MemSegmJc obj, int16 val, char const* sVaargs, ...);

METHOD_C int32 setInt_FieldJc(const FieldJc* ythis, MemSegmJc instance, int val, char const* sVaargs, ...);

METHOD_C int64 setLong_FieldJc(const FieldJc* ythis, MemSegmJc obj, int64 val, char const* sVaargs, ...);

/**Set the bits of a bitfield descibed by the given field.
 * @param obj The object to set the value inside.
 * @param val The value for the bits. The bits are adjusted rigth here, they will be shifted to the correct bit position.
 *            NOTE: It is a int-value, may be 16 bit, because the register width is proper for that.
 * @javalike: Because java doesn' know bitfields, it isn't java-like, but it is proper and necessary for C-programming.
 */
METHOD_C int setBitfield_FieldJc(const FieldJc* ythis, MemSegmJc obj, int val, char const* sVaargs, ...);

METHOD_C float setFloat_FieldJc(const FieldJc* ythis, MemSegmJc instance, float val, char const* sVaargs, ...);

METHOD_C double setDouble_FieldJc(const FieldJc* ythis, MemSegmJc obj, double val, char const* sVaargs, ...);

/** Sets a reference at the desired field in the given object obj. The field should be
  * a reference type of a scalar or not object-based instance. In other cases (if it is a scalar direct
  * or a object base reference), the method throws IllegalArgumentException.
  * Use set_FieldJc to assign a reference to a object-based instance. The method
  * don't check anything. This method isn't exist in java, because java don't know references.to
  * not object base instances.
  * @param obj The object to set the value inside.
  * @param value The reference to the destination instance to set in the object's field.
  * @exception IllegalArgumentException if the methode doesn't match to the arguments.
  */
METHOD_C void* setReference_FieldJc(FieldJc const* ythis, MemSegmJc instance, void* value, char const* sVaargs, ...);







#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

#if 0
class  FieldJcpp: public FieldJc
{
  public: ObjectJcpp* get(ObjectJcpp* obj, int idx) const
  { return static_cast<ObjectJcpp*>(get_FieldJc(this, obj->toObjectJc(), idx));
  }

  public: ClassJcpp const* getType() const;

  public: MemSegmJc getMemoryAddress(ObjectJcpp* obj) const
  { return getMemoryAddress_FieldJc(this, obj->toObjectJc());
  }

  public: int getInt(ObjectJc* obj) const
  { return getInt_FieldJc(this, obj);
  }

  public: void setInt(ObjectJcpp* obj, int value) const
  { setInt_FieldJc(this, obj->toObjectJc(), value);
  }

  public: float getFloat(ObjectJc* obj) const
  { return getFloat_FieldJc(this, obj);
  }

  public: bool  getBoolean_FieldJc(const FieldJc* ythis, MemSegmJc instance)
  { return getBoolean_FieldJc(this, obj);
  }

  public: void setFloat(ObjectJcpp* obj, float value) const
  { setFloat_FieldJc(this, obj->toObjectJc(), value);
  }

  public: MemSegmJc getReference(ObjectJcpp* obj) const
  { return getReference_FieldJc(this, obj->toObjectJc());
  }

  public: void setReference(ObjectJcpp* obj, void* value) const
  { setReference_FieldJc(this, obj->toObjectJc(), value);
  }

  public: int getModifiers() const { return getModifiers_FieldJc(this); }

};
#endif
#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)






/*@CLASS_C MethodJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  typedef void(* Void_Method)(void);   //normaler Funktionszeiger

  typedef void(ObjectJc::*Object__VoidMethod)();  //Klassenfunktionszeiger ???
  typedef int(ObjectJc::*Object__IntMethod)();  //Klassenfunktionszeiger ???
  typedef int(ObjectJc::*Object__IntMethod1Int)(int);  //Klassenfunktionszeiger ???
  typedef int(ObjectJc::*Object__IntMethod2Int)(int, int);  //Klassenfunktionszeiger ???
  typedef int(ObjectJc::*Object__IntMethod1Float)(float);  //Klassenfunktionszeiger ???
  typedef int(ObjectJc::*Object__IntMethod2Float)(float, float);  //Klassenfunktionszeiger ???
  typedef float(ObjectJc::*Object__FloatMethod1Int)(int);  //Klassenfunktionszeiger ???
  typedef float(ObjectJc::*Object__FloatMethod2Int)(int, int);  //Klassenfunktionszeiger ???
  typedef float(ObjectJc::*Object__FloatMethod1Float)(float);  //Klassenfunktionszeiger ???
  typedef float(ObjectJc::*Object__FloatMethod2Float)(float, float);  //Klassenfunktionszeiger ???
#else
  typedef void (*Object__VoidMethod)(void);
#endif


typedef void (*Method_void_Object)(ObjectJc*);
typedef void (*Method_void_Object1Int)(ObjectJc*, int);
typedef void (*Method_void_Object2Int)(ObjectJc*, int, int);
typedef void (*Method_void_Object3Int)(ObjectJc*, int, int, int);
typedef void (*Method_void_Object1Float)(ObjectJc*, float);
typedef int (*Method_int_Object)(ObjectJc*);


/**Type of the Method */
typedef enum Type_MethodJc_T
{ kNothing_Method, kInt_void, kInt_Int, kInt_2Int, kInt_3Int, kInt_Float, kInt_2Float
, kFloat_void, kFloat_Int, kFloat_2Int, kFloat_3Int, kFloat_Float, kFloat_2Float
, kVoid_void, kVoid_Int, kVoid_2Int, kVoid_3Int, kVoid_Float, kVoid_2Float
}Type_MethodJc;


typedef struct  MethodJc_T
{ //ObjectJc super;
  //StringJcRef  name;
  char name[32];

  /**adress of the method*/
  //void* adress;

  Object__VoidMethod adress;
  //Void_Method* adress;
  /**Modifier see java class Modifier*/
  int32     bModifiers;

  /** Type of the method */
  Type_MethodJc eType;
} MethodJc;

METHOD_C StringJc getName_Method(const MethodJc* ythis);



/**
Invokes the underlying method represented by this Method object,
on the specified object with the specified parameters.
Individual parameters are automatically unwrapped to match primitive formal parameters,
and both primitive and reference parameters are subject to method invocation conversions
as necessary. <br/>

If the underlying method is static, then the specified obj argument is ignored. It may be null. <br/>

If the number of formal parameters required by the underlying method is 0,
the supplied args array may be of length 0 or null. <br/>

If the underlying method is an instance method, it is invoked using dynamic method lookup.<br/>

@param obj the object the underlying method is invoked from.
           that the obj matches to the MethodJc ythis. It means, the MethodJc ythis
           is getted from a object of exactly this type or from the obj itself.
           This is tested by original Java - set- or get- operations.
           But it is not tested here to optimize calculation time. If it is a part of a
           Java2C-translation, the test should be done on Java-level, if it is a directly
           programmed in C or C++ part, the user should be programmed carefully, how it is
           ordinary in C or C++.<br/>
           The pointer is accepted as an void*, from there the user does not need to convert
           it to the common ObjectJc.<br/>
@param args the arguments used for the method call. This Arguments are given as int32-types.
           If the method has differing parameters, they are converted inside the invoke.
           The Description in MethodJc knows the type. The user also must know the type.
           The parameter must stored in the binary form used inside, it means, a float value
           must be stored as its integer image, getted by <code>*(int32*)(&floatVaribale)</code>.<br/>
Returns:
the result of dispatching the method represented by this object on obj with parameters args
*/
METHOD_C int32 invoke_v_MethodJc(const MethodJc* ythis, MemSegmJc instance, int32ARRAY* params);


//#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  int32 invoke_MethodJc(const MethodJc* ythis, ObjectJc* obj, int32ARRAY* params);
//#endif

#define CONST_ARRAYHEAD_MethodJc(NAME) CONST_ObjectArrayJc(MethodJc, ARRAYLEN(REFLECTION_IMAGE.methods_##NAME.data), 0, null, &REFLECTION_IMAGE.methods_##NAME)

#define CONST_MethodJc(CLASS, SNAME, NAME, TYPE, MODI) { SNAME, 0, null, TYPE }


/** Method[] consists of ObjectArrayJc and some MethodJc elements directly after them.
*/


typedef struct MethodJcARRAY_t
{ /** Base data of every array */
  ObjectArrayJc head;
  /** For debugging, 10 Elements are assumed. The real number of values is stored in array.len*/
  MethodJc fields[10];
}MethodJcARRAY;

METHOD_C const MethodJc* get_MethodJcARRAY(const MethodJcARRAY* ythis, int idx);

/**Converts a Array of type MethodJcARRAY with any desired size to the given MethodJcARRAY-Type.
   The conversion may test the content or not.
*/
METHOD_C MethodJcARRAY const* ptrConstCasting_MethodJcARRAY(ObjectArrayJc const* ptr);



/*@CLASS_C ClassJc_YP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/** Class[] consists of ObjectArrayJc and some ClassJc elements directly after them.
*/
typedef struct ClassJc_YP_t
{ /** Base data of every array */
  ObjectArrayJc head;
  /** For debugging, 10 Elements are assumed. The real number of values is stored in array.len*/
  ClassJc const* data[10];
}ClassJc_YP;

//METHOD_C const ClassJc* get_ClassJc_Y(const ClassJc_Y* ythis, int idx);


extern_C ClassJc_YP const* extReflectionClasses_ReflectionJc[];   






#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

#if 0
class  ClassJcpp: public ClassJc
{
  public: FieldJcpp const* getDeclaredField(StringJc src) const
  {
    return static_cast<FieldJcpp const*>(getDeclaredField_ClassJc(this, src));
  }

};
#endif
#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)



/*@INLINE ********************************************************************************************/

#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

/* Problem with CHeader.sbnf
inline ClassJcpp const* FieldJcpp::getType() const
{ return static_cast<ClassJcpp const*>(getType_FieldJc(this));
}
*/


#endif //defined(__CPLUSPLUSJcpp) && defined(__cplusplus)




#if 0
/*
extern_C const struct ReflectionFieldJc_t
{ ClassJc clazz;
  Mtbl_ObjectJc vtbl;
  DEFINE_ARRAYJc(FieldJc, 2) fields;
}reflectionFieldJc;
*/
#endif




//compatibility with generated refelctions:

#define mStaticArray_Modifier_reflectJc kStaticArray_Modifier_reflectJc


/*@CLASS_C ExtReflectionJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

struct Data_ExtReflectionJc_t;

typedef struct ExtReflectionJc_t
{
  /**A counter ...*/
  int16 ct;

  /**Error message after loading and processing. */
  int16 errorRelocationExtRefl;

  /**The reference to the buffer with raw loaded data. */
  MemC extReflectionBuffer;

  /**The reference to all data, only for debug. */
  struct Data_ExtReflectionJc_t* extReflectionData;

  /**Array of some classes which are loaded from an external file. 
   * @container=ObjectArrayJc<ClassJc*>. */
  ClassJc_YP const* extReflection;

} ExtReflectionJc_s;



char const* load_ExtReflectionJc(ExtReflectionJc_s* ythis, StringJc fileName, int headerOffset);



/*@CLASS_C Data_ExtReflectionJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**Head structure of the data, which are produced as bin file from the Header2Reflection.java tool. */
typedef struct Data_ExtReflectionJc_t
{ ObjectJc object;
	
  /**Only a designation. */
  int32 sign;
	
  /**Length of the array relocateAddr. */
  int32 nrofRelocEntries;

  /**Array of pointers to ClassJc. In the binary file the offset relative to the start of bin-Data are given.
   * After load the really memory address should be calculate and stored here. Only after them the type is valid. 
   * The pointers should be relocated too. Its origin point is the really address of classDataBlock.
   * @container=ObjectArrayJc<ClassJc*>. @sizeof=4.
   */
	ClassJc_YP const* arrayClasses;
	
  /**Block of all ClassJc and FieldJcArray. In the binary file the offset relative to the start of bin-Data are given.
   * After load the really memory address should be calculate and stored here. Only after them the type is valid. */
  ClassJc const* classDataBlock;

  /**Array of offsets to adresses to relocate. Each offset has its origin point at really address of classDataBlock.
   * The really number of relocateAddr is stored in nrofRelocEntries. */
  int32 relocateAddr[10];
}Data_ExtReflectionJc;


#endif //DEF_ObjectJc_FULL



#endif //__ReflectionJc_h__

