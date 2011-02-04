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

//to include with _Jc, inside ReflectionJc.h the ObjectJc.h will be included, but than the wrapperdefines are missing
#include <Jc/ObjectJc.h>
#include <Jc/ReflMemAccessJc.h>
#include <stdarg.h>

/*@CLASS_C FieldJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/** A field is one entry in the reflection information about attributes or references of any type.
  * In opposite to orignal-Java a FieldJc is not based on Object,
  * but the Field[]-type, in Jc named "FieldJcArray" is based on ObjectJc like every ARRAYJc.
  * It means at ex you cannot call toString_ObjectJc(myField.object), it results in a compiler syntax error.
  * The reason if the FieldJc-type do not based on ObjectJc is: preserve of expenditure, it is not necessary.
  * A field may describe:
  * * a simle scalar attribute of type such as int or long, the type field references to ,,ReflectionintJc,, and so on.
  * * a reference to any other type, the instance may be derived also, the type field references to ,,ReflectionReferenceType,,.
  * * a embedded other type. That is a possibility only in C(++), not possible in original Java.
  * : but the Java2C translator produces such constructs because optimization, and a hand write code
  * : can use this because optimization. The type field references to ;;ReflectionEmbeddedType,,,
  * : but the modifier-bit mEmbedded_Modifier_reflectJc is set in bitModifiers.
  */


typedef struct  FieldJc_t
{ //ObjectJc super;

  /** The symbolic name of the field*/
  //StringJcRef  name;
  char name[30]; //kLengthNAME_FIELD_ReflectionJc];  //28

  /**Size of the field or size of 1 element if it is an static array. */
  //int16 sizeElement;

  /**Nr of elements of an static array or the bit positions of a bitfield*/
  int16 nrofArrayElementsOrBitfield_;

	/**If the element nrofArrayElementsOrBitfield designates the bits of a bitfield,
	 * this bits represent the bit Position in the field.
	 */
	#define mBitInBitfield_FieldJc 0x0fff
	
	/**If the element nrofArrayElementsOrBitfield designates the bits of a bitfield,
	 * this bits represent the number of bits of the field.
	 */
	#define mNrofBitsInBitfield_FieldJc 0xf000

	/**If the element nrofArrayElementsOrBitfield designates the bits of a bitfield,
	 * this bits represent the position in bits of number of bits of the field.
	 */
	#define kBitNrofBitsInBitfield_FieldJc 12

  /** The class object representing the type of the field.
   * It may be a class object also for primitive types
   * or for primitive Type there is a simple constant value, see REFLECTION_type above.
	 * Don't use this element directly. Only with is getter: [[getType_FieldJc(...)]]
   */
  struct ClassJc_t const* type_;

  /**The modifiers of the Field. The Bits are defined in Modifier_reflectJc.
   * The concept follows Java, see java.lang.reflect.Field.getModifier or java.lang.reflect.Modifier,
   * but it is enhanced in respect to C/C++ and UML requirements.
   */
  int32     bitModifiers;  //Bits of Modifier_reflectJc.

  /** position of the field inside a object of the type of the declaring class.
    * The position is the offset from the ObjectJc base class to the field, not the offset from the total base.
    * Because it is possible that the object is known via interface reference. A interface reference
    * pointered the position of the pointer to the virtual table of the interface,
    * a call of obj->toObjectJc() is necessary to get the base for this offset.
    */
  int16     position;

  /**Offset in a pointered class to the ObjectifcBaseJcpp class structure if such base interface exists.
     This value is 0 if it is not a pointer or if it is a pointer of not Object-derivated structures.
   */
  int16     offsetToObjectifcBase;
  /** The class object representing the class or interface that declares the field represented by this Field object. */
  struct ClassJc_t const* declaringClass;
}FieldJc;



#define TYPESIZEOF_FieldJc (kIsSmallSize_typeSizeIdent_ObjectJc + 0x0FF60000 + sizeof(FieldJc))

/**Identifier for ObjectJc to describe: It's a FieldJc. This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_FieldJc (kIsSmallSize_objectIdentSize_ObjectJc + 0x0FF50000)

#define OBJTYPE_ClassOffset_idxMtblJc (kIsSmallSize_objectIdentSize_ObjectJc + 0x0FF90000)



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

#define getName_FieldJc(THIS) ((THIS)->name)


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



struct ClassJc_t const* getType_FieldJc(FieldJc const* ythis);

#define getDeclaringClass_FieldJc(THIS) ((THIS)->declaringClass)

#define getModifiers_FieldJc(THIS) ((THIS)->bitModifiers)



#define getStaticArraySize_FieldJc(THIS) (((THIS)->bitModifiers & mPrimitiv_Modifier_reflectJc) == kBitfield_Modifier_reflectJc ? 0: (THIS)->nrofArrayElementsOrBitfield_)

/**Gets the absolute adress of the element represented by this field inside the given Instance. 
 * It is assumed, that the instance matches to the Field ythis, it means, the Field ythis
 * is getted from a instance of exactly this type or from the instance itself.
 * This is tested by original Java - set- or get- operations.
 * But it is not tested here to optimize calculation time. If it is a part of a
 * Java2C-translation, the test should be done on Java-level, if it is a directly
 * programmed in C or C++ part, the user should be programmed carefully, how it is
 * ordinary in C or C++.
 *
 * @param obj the Object. It shouln't derivated from ObjectJc, it may be any struct or class,
 *            but the type should matched to the ClassJc description getted with getDeclaringClass_FieldJc(ythis).
 * @param ix -1 if the field isn't a simple array, or the base address should be returned.
 *            0... if the address of a element of the field should be returned.
 *            An index 0... is only admissible for a simple embedded array.
 *            To get the address of elements of a container field, use [[>getAddrElement_FieldJc(...)]]
 */
METHOD_C MemSegmJc getMemoryAddress_FieldJc(const FieldJc* ythis, MemSegmJc instance, bool bFieldAddr, char const* sVaargs, va_list vaargs);


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
 * See method [[>getAddrElement_FieldJc(...)]], this methods accesses inside the container with a given index.
 *
 * @param instance the Object. It shouln't derivated from ObjectJc, it may be any struct or class,
 *             but the type should matched to the ClassJc description getted with getDeclaringClass_FieldJc(ythis).
 *  @return if the container is an embedded element, this method returns the same value as getMemoryAddress_FieldJc(...),
 *          but if it is referenced, the referenced address is returned. The bits mContainerReference_Modifier_reflectJc in bitModifiers
 *          are tested to get the result.
 */
METHOD_C MemSegmJc getContainerAddress_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, va_list vaargs);



/**Gets the address of the element described with the field of the given object.
 * It regards whether the field is of container type, it regards the index.
 * @param address The address of the reference, it may be the address of a container element.
 * @param idx The index. 
 *          If the index < 0, the address of the whole container is returned.
 *          If the index exceeds the boundaries of the container, null is returned.
 * @returns the address of the reference maybe in a container or the address of the reference immediately, if it isn't a container. 
 *          If the contained instances in the container are embedded in the container, this address is equal with the address of the instance.
 *          If the instances in the container are references, this is the address where the reference to the instance is found.
 *          The type of the reference should be regarded. Check ,,(getModifiers_FieldJc(field) & mAddressing_Modifier_reflectJc),,
 *          to detect which to do whith the address.   
 * @throws IndexOutOfBoundsException if the idx is fault.
 * @since 2009-11-26, it is necessary to set references with the ''inspector''-Tool.
 */
METHOD_C MemSegmJc getAddrElement_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, va_list vaargs);




/**Gets the address of the instance with given address of the reference to it.
 * This method regards the ,,(getModifiers_FieldJc(field) & mAddressing_Modifier_reflectJc),,.
 * @param addrReference Adress of the position in the container, where a reference or the instance is located in memory.
 * @return If the field describes an embedded instance in an container, addrReference itself is returned.
 *         Otherwise the address of the instance, which is contained in the reference is returned.
 */
METHOD_C MemSegmJc XXXgetAddrReferencedInstance_FieldJc(const FieldJc* ythis, MemSegmJc addrReference);




/**Gets the reference contained in the field of the given object.
 * @param address The address of the reference, it may be the address of a container element.
 * @param idx the index
 * @throws IndexOutOfBoundsException if the idx is fault.
 */
METHOD_C MemSegmJc xxxgetRefAddr_FieldJc(const FieldJc* ythis, MemSegmJc instance, int idx);

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
  inline MemSegmJc get_FieldJc(FieldJc const* ythis, ObjectifcBaseJcpp* obj, int idx)
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
METHOD_C MemSegmJc searchObject_ClassJc(StringJc sPath, ObjectJc* startObj, FieldJc const** field, int* idx);



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



/** Returns the reference to the field inside the given object. This method is not javalike.
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


METHOD_C int32 getMemoryIdent_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...);

METHOD_C int32 getMemoryIdent_V_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, va_list vaargs);



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





/** Field[] consists of ObjectArrayJc and some FieldJc elements directly after them.
*/
typedef struct  FieldJc_Y_t
{ /** Base data of every array */
  //ObjectArrayJc array;
  ObjectArrayJc head;
  /** For debugging, 10 Elements are assumed. The real number of values is stored in array.len*/
  FieldJc data[10];
}FieldJc_Y;


#define FieldJcArray FieldJc_Y

METHOD_C FieldJc_Y* new_FieldJcArray(int size);

#define FieldARRAY FieldJcArray
//METHOD_C const FieldJc* get_FieldARRAYc(const FieldARRAY* ythis, int idx);






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
  typedef void (*Object__VoidMethod)();
#endif


typedef void (*Method_void_Object)(ObjectJc*);
typedef void (*Method_void_Object1Int)(ObjectJc*, int);
typedef void (*Method_void_Object2Int)(ObjectJc*, int, int);
typedef void (*Method_void_Object3Int)(ObjectJc*, int, int, int);
typedef void (*Method_void_Object1Float)(ObjectJc*, float);
typedef int (*Method_int_Object)(ObjectJc*);


/**Type of the Method */
typedef enum Type_MethodJc_t
{ kNothing_Method, kInt_void, kInt_Int, kInt_2Int, kInt_3Int, kInt_Float, kInt_2Float
, kFloat_void, kFloat_Int, kFloat_2Int, kFloat_3Int, kFloat_Float, kFloat_2Float
, kVoid_void, kVoid_Int, kVoid_2Int, kVoid_3Int, kVoid_Float, kVoid_2Float
}Type_MethodJc;


typedef struct  MethodJc_t
{ //ObjectJc super;
  //StringJcRef  name;
  char name[32];

  /**Modifier see java class Modifier*/
  int32     bModifiers;
  /**adress of the method*/
  //void* adress;
  Object__VoidMethod adress;
  //Void_Method* adress;
  /** Type of the method */
  Type_MethodJc eType;
}MethodJc;


METHOD_C const StringJc getName_Method(const MethodJc* ythis);



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



/*@CLASS_C ClassJc ************************************************************************/




typedef struct  ClassJc_t
{ ObjectJc object;

  /** The typename. If it is a Class represents a primitive type, the name is such as "int", "float", "boolean".*/
  char name[32];

  /** position of the base structure/class ObjectJc inside this type, it is the base address for the offset of fields.*/
  int32 posObjectBase;

  /**sizeof the type. Hint: It may be longer as 64 kByte, int32 is necessary.*/
  int32 nSize;

  FieldJcArray const* attributes;

  MethodJcARRAY const* methods;

  /** The superclass, ObjectJc if no other superclass.*/
  struct ClassOffset_idxMtblJcARRAY_t const* superClasses;
  //struct ClassJc_t const* superClass;

  /** Array of interfaces to this class.*/
  //ObjectJc const* interfaces;
  struct ClassOffset_idxMtblJcARRAY_t const* interfaces;
  //struct{ ObjectArrayJc base; ClassJc* interfaces; };

  /** Some bits determines the kind of the Class, see Modifier_reflectJc*/
  int32 modifiers;

  /**Pointer to jump table for dynamic calls (virtual methods).
   * This is a typed struct, starting with Mtbl_ObjectJc.
   */
  MtblHeadJc const* mtbl;
  //Method_int_Object* mtbl;

}ClassJc;

/**Compatibility. */
#define Class_Jc_t ClassJc_t

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ClassJc (kIsSmallSize_objectIdentSize_ObjectJc + 0x0ff80000)

/**This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ReflectionImageJc (mIsLargeSize_objectIdentSize_ObjectJc + 0x1e000000)

/**This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ReflectionImageBaseAddressJc (kIsSmallSize_objectIdentSize_ObjectJc + 0x0ff70000)




/*
typedef enum ScalarTypes_ClassJc_t
{ int64_ClassJc = 1, int32_ClassJc, int16_ClassJc, int8_ClassJc
, uint64_ClassJc, uint32_ClassJc, uint16_ClassJc, uint8_ClassJc
, float_ClassJc, double_ClassJc
, char8_ClassJc, char8Array_ClassJc
, char16_ClassJc, char16Array_ClassJc
, void_ClassJc
, ObjectJc_ClassJc , ObjectArrayJc_ClassJc
, StringJc_ClassJc
, ClassJc_ClassJc
, reflection__ObjectRefValuesJc
}ScalarTypes_ClassJc;
*/

typedef enum ScalarTypes_ClassJc_t
{
  REFLECTION_void_ClassJc       = 0x01,
  REFLECTION_int64_ClassJc      = 0x02,
  REFLECTION_uint64_ClassJc     = 0x03,
  REFLECTION_int32_ClassJc      = 0x04,
  REFLECTION_uint32_ClassJc     = 0x05,
  REFLECTION_int16_ClassJc      = 0x06,
  REFLECTION_uint16_ClassJc     = 0x07,
  REFLECTION_int8_ClassJc       = 0x08,
  REFLECTION_uint8_ClassJc      = 0x09,
  REFLECTION_int_ClassJc        = 0x0a,
  REFLECTION_uint_ClassJc       = 0x0b,
  REFLECTION_float_ClassJc      = 0x0c,
  REFLECTION_double_ClassJc     = 0x0d,
  REFLECTION_char_ClassJc       = 0x0e,
  REFLECTION_bool_ClassJc       = 0x0f,
  REFLECTION_String_ClassJc     = 0x10,
  REFLECTION_bitfield_ClassJc   = 0x17,
  REFLECTION_afterlastPrimitive_ClassJc       = 0x18
}ScalarTypes_ClassJc;










/**The next defines are necessary because the automatic code generation generates such types if void * or void* or char* is written.*/
#define REFLECTION_void_Pointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_voidPointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_charPointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_char_Pointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )

/**Reflection of standard types. */
#define REFLECTION_void               ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_int64              ((struct ClassJc_t const*) REFLECTION_int64_ClassJc )
#define REFLECTION_uint64             ((struct ClassJc_t const*) REFLECTION_uint64_ClassJc)
#define REFLECTION_int32              ((struct ClassJc_t const*) REFLECTION_int32_ClassJc )
#define REFLECTION_uint32             ((struct ClassJc_t const*) REFLECTION_uint32_ClassJc)
#define REFLECTION_int16              ((struct ClassJc_t const*) REFLECTION_int16_ClassJc )
#define REFLECTION_short              ((struct ClassJc_t const*) REFLECTION_int16_ClassJc )
#define REFLECTION_uint16             ((struct ClassJc_t const*) REFLECTION_uint16_ClassJc)
#define REFLECTION_int8               ((struct ClassJc_t const*) REFLECTION_int8_ClassJc  )
#define REFLECTION_byte               ((struct ClassJc_t const*) REFLECTION_int8_ClassJc  )
#define REFLECTION_uint8              ((struct ClassJc_t const*) REFLECTION_uint8_ClassJc )
#define REFLECTION_int                ((struct ClassJc_t const*) REFLECTION_int_ClassJc   )
#define REFLECTION_uint               ((struct ClassJc_t const*) REFLECTION_uint_ClassJc  )
#define REFLECTION_long               ((struct ClassJc_t const*) REFLECTION_uint32_ClassJc)
#define REFLECTION_float              ((struct ClassJc_t const*) REFLECTION_float_ClassJc  )
#define REFLECTION_float32            ((struct ClassJc_t const*) REFLECTION_float_ClassJc  )
#define REFLECTION_double             ((struct ClassJc_t const*) REFLECTION_double_ClassJc )
#define REFLECTION_char               ((struct ClassJc_t const*) REFLECTION_char_ClassJc  )
#define REFLECTION_bool               ((struct ClassJc_t const*) REFLECTION_bool_ClassJc  )
#define REFLECTION_boolean            ((struct ClassJc_t const*) REFLECTION_bool_ClassJc )
#define REFLECTION_BOOL               ((struct ClassJc_t const*) REFLECTION_bool_ClassJc )
#define REFLECTION_BITFIELD           ((struct ClassJc_t const*) REFLECTION_bitfield_ClassJc )

#define REFLECTION_s32                ((struct ClassJc_t const*) REFLECTION_int32_ClassJc )
#define REFLECTION_u32                ((struct ClassJc_t const*) REFLECTION_uint32_ClassJc)
#define REFLECTION_s16                ((struct ClassJc_t const*) REFLECTION_int16_ClassJc )
#define REFLECTION_u16                ((struct ClassJc_t const*) REFLECTION_uint16_ClassJc)
#define REFLECTION_s08                ((struct ClassJc_t const*) REFLECTION_int8_ClassJc  )
#define REFLECTION_u08                ((struct ClassJc_t const*) REFLECTION_uint8_ClassJc )
#define REFLECTION_StringJc           ((struct ClassJc_t const*) REFLECTION_String_ClassJc )

/*
#define REFLECTION_bool               ((struct ClassJc_t const*) 0x0f )
#define REFLECTION_bool               ((struct ClassJc_t const*) 0x0f )
#define REFLECTION_bool               ((struct ClassJc_t const*) 0x0f )
#define REFLECTION_bool               ((struct ClassJc_t const*) 0x0f )
*/


#define reflection_int8             (*((struct ClassJc_t const*) REFLECTION_int8_ClassJc ))
#define reflection_int16             (*((struct ClassJc_t const*) REFLECTION_int16_ClassJc ))

//#define REFLECTION_ObjectifcBaseJcpp ((struct ClassJc_t const*) 0x18 )

//#define REFLECTION_ObjectJc          ((struct ClassJc_t const*) 0x19 )
//#define REFLECTION_ObjectJcpp        ((struct ClassJc_t const*) 0x1a )
#define REFLECTION_Object_ArrayJc    ((struct ClassJc_t const*) 0x1b )
//#define REFLECTION_StringJc          ((struct ClassJc_t const*) 0x1d )
//#define REFLECTION_ClassJc           ((struct ClassJc_t const*) 0x20 )


//#define REFLECTION_ObjectJc          ((struct ClassJc_t const*) 0x41 )
//#define REFLECTION_ObjectJcpp        ((struct ClassJc_t const*) 0x42 )
#define REFLECTION_ObjectRefValuesJc ((struct ClassJc_t const*) 0x44 )
//#define REFLECTION_ClassJc           ((struct ClassJc_t const*) 0x45 )
#define REFLECTION_ClassJc_t         ((struct ClassJc_t const*) 0x45 )

#define kREFLECTION_LastConstant      0x50



/** Constant Definition of a ClassJc-instance usefull for simple plain old data
  * without special defined methods. A superclass ObjectJc is not specified.
  * It doesn#t mean that the data can't base on ObjectJc, but the access is not able
  * via this reflection definition. It may or may not based on any superclass.
  * Use the macro CONST_xxx_ClassJc instead if you have complexer structures.
  *
  * It is been designated for a whole reflection constant definition block
  * with the following rules:
  * *The name of the constant whole reflection instance should be ,,reflectionNAME,,.
  * *The ''virtual table'' is denoted with ,,vtbl,,.
  * *The attribute-block is denoted with ,,fields,,.
  * *A superclass or any interfaces are not present.
  * *Methods are not present.
  *
  */
#define CONST_dataonly_ClassJc(SNAME, NAME) \
{ CONST_ObjectJc(sizeof(reflection##NAME), , &reflection##NAME.clazz , null) \
, SNAME\
, 0     \
, sizeof(NAME) \
, (FieldJcArray const*)(&reflection##NAME.fields) \
, null, null, null, 0 \
}

/** Adaequate complex reflection for C++-classes
*/

#define CONST_Cpp_ClassJc(SNAME, NAME, OWNADDRESS)\
{ CONST_ObjectJc(sizeof(reflection##NAME), OWNADDRESS, null)   \
, SNAME /*CONST_StringJc(SNAME)*/                      \
, 0  \
, sizeof(NAME)                              \
, (FieldJcArray const*)&reflection##NAME.fields \
, (MethodJcARRAY const*)(&reflection##NAME.methods)\
, null  \
, null  \
, mObjectifcBaseJcpp_Modifier_reflectJc   \
}




/**Macro for constant value of the ObjectJc on head of any reflectionImage-structure.
 * The macro REFLECTION_IMAGE should be defined with the identifier of the reflection image.
 * Therefore all information to build the constant value is given, no additionaly arguments are needed.
 */
#define CONST_ObjectJc_REFLECTION_IMAGE() CONST_ObjectJc(OBJTYPE_ReflectionImageJc + sizeof(REFLECTION_IMAGE), &(REFLECTION_IMAGE), null)


/**Macro for constant value of a ClassJc inside a ReflectionImage-structure.
 * The macro REFLECTION_IMAGE should be defined with the identifier of the reflection image.
 */
#define CONST_ClassJc(SNAME, NAME)\
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(REFLECTION_IMAGE.reflect_##NAME), &REFLECTION_IMAGE.reflect_##NAME, null)   \
, SNAME                       \
, 0  /**Position of ObjectJc in the Type should be 0, if only C struct should be used.*/ \
, sizeof(NAME)                              \
, (FieldJcArray const*)&REFLECTION_IMAGE.attributes_##NAME \
, (MethodJcARRAY const*)(&REFLECTION_IMAGE.methods_##NAME)\
, null  \
, null  \
, mObjectJc_Modifier_reflectJc   \
}



/**Macro for constant value of a only-data-ClassJc inside a ReflectionImage-structure.
 * The macro REFLECTION_IMAGE should be defined with the identifier of the reflection image.
 */
#define CONST_dataImg_ClassJc(SNAME, NAME)\
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(REFLECTION_IMAGE.reflect_##NAME), &REFLECTION_IMAGE.reflect_##NAME, null)   \
, SNAME /*CONST_StringJc(SNAME)*/                      \
, 0  /**Position of ObjectJc in the Type should be 0, if only C struct should be used.*/ \
, sizeof(NAME)                              \
, (FieldJcArray const*)&REFLECTION_IMAGE.attributes_##NAME \
, null  \
, null  \
, null  \
, mObjectJc_Modifier_reflectJc   \
}


/**Macro for constant value of a ClassJc inside a ReflectionImage-structure.
 * The macro REFLECTION_IMAGE should be defined with the identifier of the reflection image.
 */
#define CONST_data_ClassJc(SNAME, NAME)\
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflect##NAME, null)   \
, SNAME                       \
, 0  /**Position of ObjectJc in the Type should be 0, if only C struct should be used.*/ \
, sizeof(NAME)                              \
, &attribs##NAME \
, null  \
, null  \
, null  \
, 0   \
}

/**initializes a ClassJc, see [[ctorc_ClassJc(...)]].
 * @param rawMem raw memory area, it may be uninitialized. 
 *        The size may be greater as necessary. The constructor initializes only its own area.
 * @throws IllegalArgumentException if the sizeof rawMem is to less.  
 */
METHOD_C ClassJc* ctorM_ClassJc(MemC rawMem);


/**initializes a ClassJc. 
 * All content is set to 0.
 */
METHOD_C void ctorc_ClassJc(ClassJc* ythis);


#define getClass_ClassJc(OBJ) getClass_ObjectJc(OBJ)

/** Methods from Class */
METHOD_C FieldJcArray const* getDeclaredFields_ClassJc(ClassJc const* ythis);//sss

METHOD_C FieldJc const* getDeclaredField_ClassJc(ClassJc const* ythis, StringJc sName);

METHOD_C MethodJcARRAY const* getDeclaredMethods_ClassJc(ClassJc const* ythis);

METHOD_C MethodJc const* getDeclaredMethod_ClassJc(ClassJc const* ythis, char const* sName);


METHOD_C ClassJc const* getEnclosingClass_ClassJc(ClassJc const* ythis);

/**gets the Name of the class. It is a static method, because the argument class may be a constant for simple types.
 * @param class Either the class object or a constant to design simple types, see REFLECTION_xxx.
 */
METHOD_C const char* getName_ClassJc(ClassJc const* clazz);

METHOD_C ClassJc const* getSuperclass_ClassJc(ClassJc const* ythis);

/**gets the modifiers for this class or interface, encoded in an integer.
 * They should be decoded using the methods of class ModifierJc.
 */
METHOD_C int32 getModifiers_ClassJc(ClassJc const* ythis);


/** returns true if the type is a primitive Type, like java Class::isPrimitive()
  */
METHOD_C bool isPrimitive_ClassJc(ClassJc const* ythis);

/** returns true if the type is a reference Type. Not javalike.
  */
#define isReference_ClassJc(THIS) ((THIS->modifiers & mReference_Modifier_reflectJc)!=0)

/** returns true if the type is a instance of a C-struct, based on ObjectJc.
  * This method is defined outside java, in java all classes based only on Object.
  */
#define isObjectJc_ClassJc(THIS) ((THIS->modifiers & mObjectJc_Modifier_reflectJc)!=0)

/** returns true if the type is a instance of a C++-class, based on ObjectifcBaseJcpp.
  * It may be also a reference to a interface. The reference type should based on ObjectifcBaseJcpp.
  * This method is defined outside java, in java all classes based only on Object.
  */
#define isObjectifcBaseJcpp_ClassJc(THIS) ((THIS->modifiers & mObjectifcBaseJcpp_Modifier_reflectJc)!=0)







/*@CLASS_C ModifierJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/** Modifiers to specify the kind of field, see class java.lang.reflect.Modifier
*/

typedef enum  Modifier_reflectJc_t
{  /**
   * The <code>int</code> value representing the <code>public</code>
   * modifier.
   */
  mPUBLIC_Modifier_reflectJc           = 0x00000001

  /**
   * The <code>int</code> value representing the <code>private</code>
   * modifier.
   */
, mPRIVATE_Modifier_reflectJc          = 0x00000002

  /**
   * The <code>int</code> value representing the <code>protected</code>
   * modifier.
   */
, mPROTECTED_Modifier_reflectJc        = 0x00000004

  /**
   * The <code>int</code> value representing the <code>static</code>
   * modifier.
   */
, mSTATIC_Modifier_reflectJc           = 0x00000008

  /**
   * The <code>int</code> value representing the <code>final</code>
   * modifier.
   */
, mFINAL_Modifier_reflectJc            = 0x00000010

  /**
   * The <code>int</code> value representing the <code>synchronized</code>
   * modifier.
   */
, mSYNCHRONIZED_Modifier_reflectJc     = 0x00000020

  /**
   * The <code>int</code> value representing the <code>volatile</code>
   * modifier.
   */
, mVOLATILE_Modifier_reflectJc         = 0x00000040

  /**
   * The <code>int</code> value representing the <code>transient</code>
   * modifier.
   */
, mTRANSIENT_Modifier_reflectJc        = 0x00000080

  /**
   * The <code>int</code> value representing the <code>native</code>
   * modifier.
   */
, mNATIVE_Modifier_reflectJc           = 0x00000100

  /**
   * The <code>int</code> value representing the <code>interface</code>
   * modifier.
   */
, mINTERFACE_Modifier_reflectJc        = 0x00000200

  /**
   * The <code>int</code> value representing the <code>abstract</code>
   * modifier.
   */
, mABSTRACT_Modifier_reflectJc         = 0x00000400

  /**
   * The <code>int</code> value representing the <code>strictfp</code>
   * modifier.
   */
, mSTRICT_Modifier_reflectJc           = 0x00000800

    /**outside java definition:
     * If not 0, than it is a primitive type.
     * The value at this bits represents the nr of Bits of the primitive type in the target system.
     */
, mPrimitiv_Modifier_reflectJc         = 0x000F0000

  /**It may be a primitive with 7*8= 56 bit, it is used to designate a bitfield. */
, kBitfield_Modifier_reflectJc         = 0x00070000   

    /**outside java definition:
     * Position of this Bits.
     */
, kBitPrimitiv_Modifier_reflectJc =  16

    /**outside java definition:
     * This bits represents the containertype.
     */
#define m_Containertype_Modifier_reflectJc 0x00f00000

    /**outside java definition:
     * The <code>int</code> value representing the isUML_List()-Property.
     * It is set if a Reference is a multiple aggregation realized with a list container
     * using the ListJc interface.
     */
, kListJc_Modifier_reflectJc          =    0x00100000

    /**outside java definition:
     * The <code>int</code> value representing the isUML_List()-Property.
     * It is set if a Reference is a multiple aggregation realized with a array container
     * using the ObjectArrayJc structure.
     */
, kObjectArrayJc_Modifier_reflectJc   =    0x00200000   //do not change, compatibility with older data

    /**outside java definition:
     * The <code>int</code> value representing the isUML_List()-Property.
     * It is set if a Reference is a multiple aggregation realized with a list container
     * using the MapJc interface.
     */
, kMapJc_Modifier_reflectJc           =    0x00400000

    /**outside java definition:
     * The <code>int</code> value representing the isStaticArray-Property.
     * It is set if multiple elements are after another imediately,
     * The number of elements is hold in the FieldJc.nrofArrayElements
     */
, kStaticArray_Modifier_reflectJc     =    0x00800000   //do not change, compatibility with older data

    /**outside java definition:
     * The <code>int</code> value representing the isUML_List()-Property.
     * It is set if a Reference is a multiple aggregation realized with a list container.
     * The realisation of the list may be specific for a UML framework, therefore the access to the elements
     * is made with the user definable UML_ListJc methods.
     */
, kUML_LinkedList_Modifier_reflectJc  =    0x00500000

    /**outside java definition:
     * The <code>int</code> value representing the isUML_Array()-Property.
     * It is set if a Reference is a multiple aggregation realized with a list container.
     * The realisation of the list may be user specific for a UML framework, therefore the access to the elements
     * is made with the user definable UML_ArrayJc methods.
     */
, kUML_ArrayList_Modifier_reflectJc    =   0x00700000

    /**outside java definition:
     * The <code>int</code> value representing the isUML_Map()-Property.
     * It is set if a Reference is a multiple aggregation realized with a list container.
     * The realisation of the list may be user specific for a UML framework, therefore the access to the elements
     * is made with the user definable UML_MapJc methods.
     */
, kUML_Map_Modifier_reflectJc          =   0x00600000

    /**Mode of addressing of complex elements. This mode is regarded to the elements of a container,
     * if the field represents a container. 
     * The kind of the instanciation of the container is found in @see mContainerinstance_Modifier_reflectJc.
     */
    #define mAddressing_Modifier_reflectJc 0x03000000
    /** outside java definition:
     * The <code>int</code> value representing the isEmbedded()-Property of fields,
     * It is set if a attribute represented by the field in reflection represents
     * a embedded structured (not a reference to data).
     */
, kEmbedded_Modifier_reflectJc         =  0x01000000

    /** outside java definition:
     * The <code>int</code> value representing the isReference()-Property.
     * A reference is a reference to a primitive type or structured type,
     * not inherited from ObjectJc.
     */
, kReference_Modifier_reflectJc        =  0x02000000



    /** outside java definition:
     * The <code>int</code> value representing the isEnhancedReference()-Property.
     * An enhanced reference may be reference a ObjectJc-inherited instance.
     * NOTE: mask and compare both bits mEmbedded_Modifier_reflectJc and mReference_Modifier_reflectJc!
     */
, kEnhancedReference_Modifier_reflectJc= 0x03000000
    /** outside java definition:
     * The <code>int</code> value representing the isObjectJc()-Property.
     * It is set if the Type contains ObjectJc at its first position,
     * especially for C-struct using CRuntimeJavalike-concepts. If it is set,
     * a C-pointer cast is allowed to keep the ObjectJc-pointer.
     * The bit is not set if the type is derived from ObjectJc,
     * but don't contain it at first position
     * It is not set if
     */
, mObjectJc_Modifier_reflectJc        =  0x04000000

    /**outside java definition:
     * The <code>int</code> value representing the isObjectifc()-Property.
     * It is set if the Type is derived from ObjectifcBaseJcpp.
     */
, mObjectifcBaseJcpp_Modifier_reflectJc  =  0x08000000


    /**The container is instanciated embeddedly. */
    , kEmbeddedContainer_Modifier_reflectJc =      0x10000000
    /**The container is referenced with a simple reference. */
    , kReferencedContainer_Modifier_reflectJc=     0x20000000
    /**The container is referenced with an enhanced reference. */
    , kEnhancedRefContainer_Modifier_reflectJc =   0x30000000



} Modifier_reflectJc;



typedef enum Mask_ModifierJc_t
{
  /**If this bit is set, it is either a reference or a enhanced reference.*/
  mReference_Modifier_reflectJc         = 0x02000000

    /**outside java definition:
     * The <code>int</code> represents the kind of the instanciation of the container.
     * 
     */
, mContainerinstance_Modifier_reflectJc = 0x30000000
}Mask_ModifierJc;



#define isReference_ModifierJc(VALUE) ( (VALUE & mReference_Modifier_reflectJc) !=0)

//#define isCollection_ModifierJc(VALUE) ( (VALUE & (mListJc_Modifier_reflectJc | mObjectArrayJc_Modifier_reflectJc  | mMapJc_Modifier_reflectJc | mStaticArray_Modifier_reflectJc | mUML_LinkedList_Modifier_reflectJc | mUML_ArrayList_Modifier_reflectJc| mUML_Map_Modifier_reflectJc)) != 0 )
#define isCollection_ModifierJc(VALUE) ( (VALUE & m_Containertype_Modifier_reflectJc) != 0 )

#define isStaticArray_ModifierJc(VALUE) ( (VALUE & m_Containertype_Modifier_reflectJc) == kStaticArray_Modifier_reflectJc )

/**Returns true if it is an embedded static simple array.*/
#define isStaticEmbeddedArray_ModifierJc(VALUE) ( (VALUE & (m_Containertype_Modifier_reflectJc|mContainerinstance_Modifier_reflectJc)) == (kStaticArray_Modifier_reflectJc|kEmbeddedContainer_Modifier_reflectJc ) )



/*@DEFINE_C @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/




/** Macro to define a users type reflection with the exactly length of the table of virtual methods
  * used in the header file of a users type.
  * See ReflectionMtblJc. It creates a type named Reflection__TYPE and a external reference
  * to the static reflection variable named reflection__TYPE.
  * @param TYPE The users type.
  * @param nrofVIRTFN really number of the virtual methods, it must match with the
  *        definition of the reflection of this type.
  */
//#define TYPEDEF_REFLECTIONJc(TYPE, nrofVIRTFN) typedef struct Reflection__##TYPE##_t{ ClassJc reflection; Void_MethodVoid vTbl[nrofVIRTFN];} Reflection__##TYPE; extern const Reflection__##TYPE reflection__##TYPE;
#define TYPEDEF_REFLECTIONJc(TYPE) typedef struct Reflection__##TYPE##_t{ ClassJc clazz; Mtbl_##TYPE vtbl;} Reflection__##TYPE; extern const Reflection__##TYPE reflection__##TYPE;

/** Macro to define a users type reflection of a class type,
  * used in the header file of a users type.
  * See ReflectionMtblJc. It creates a type named Reflection__TYPE and a external reference
  * to the static reflection variable named reflection__TYPE.
  * @param TYPE The users type.
  * @param NROFVCALL number of virtual methods of the type, may be 0 if the type is only used in C++.
  */
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
  #define TYPEDEF_REFLECTIONJcpp(TYPE) typedef struct Reflection__##TYPE##_t{ ClassJc clazz; } Reflection__##TYPE; extern const Reflection__##TYPE reflection__##TYPE;
#else
  #define TYPEDEF_REFLECTIONJcpp(TYPE) TYPEDEF_REFLECTIONJc(TYPE)
#endif


/** Typedef of a reflection structure inclusive pointer to dynamic linked methods.
  * It is used particularly for C-structure-like classes to realize dynamic linked methods
  * in C. In a C++-environment it is necessary if Plain Old Data (POD) are used
  * in conjunction with the using of reflection and overloading of some ObjectJc
  * methods, at example toString().<br>
  * The number of elements in vMethods are depended on the number of virtual methods.
  * The number here is only a standard value to support a debugging.
  * You see the first ones methods, or, also able fault pointers. See macro TYPEDEF_REFLECTIONJc.<br>
  * In a poor C++ environment the element vMethods is not existent, the debugger shows
  * fault pointers. See macro TYPEDEF_REFLECTIONJcpp.
*/
/*
typedef struct ReflectionMtblJc_t
{
  ClassJc clazz;
  MT_void_Method_void vMethods[10];
}ReflectionMtblJc;
*/

//TYPEDEF_REFLECTIONJc(ObjectJc)





/** This type describes one entry of a interface or superclass.
    In regard of virtual methods an index inside the table of virtual methods is stored here.
*/
typedef struct ClassOffset_idxMtblJc_t
{
  /** The reflection definition*/
  ClassJc const* clazz;
  /** Index of the virtual table inside its parent.*/
  int idxMtbl;
}ClassOffset_idxMtblJc;

/**This macro calculates the index of a particulary method table inside a table, to use for idxMtbl in ClassOffset_idxMtblJc.
 */
#define OFFSET_Mtbl(TYPE, ELEMENT) ( ( (int)(&((TYPE*)(0x1000))->ELEMENT) - 0x1000) / sizeof(MT_void_Method_void const*)) 
//#define OFFSET_Mtbl(BASE, ELEMENT) ( (MT_void_Method_void const*)(&BASE.ELEMENT) - (MT_void_Method_void const*)(&BASE)) 

/** This type describes a array of ClassOffset_idxMtblJc*/
typedef struct ClassOffset_idxMtblJcARRAY_t
{ /** Base data of every array */
  ObjectArrayJc head;
  /** For debugging, 10 Elements are assumed. The real number of values is stored in array.len*/
  ClassOffset_idxMtblJc data[10];
}ClassOffset_idxMtblJcARRAY;






/** Class[] consists of ObjectArrayJc and some ClassJc elements directly after them.
*/
typedef struct ClassJc_YP_t
{ /** Base data of every array */
  ObjectArrayJc head;
  /** For debugging, 10 Elements are assumed. The real number of values is stored in array.len*/
  ClassJc const* data[10];
}ClassJc_YP;

//METHOD_C const ClassJc* get_ClassJc_Y(const ClassJc_Y* ythis, int idx);


extern ClassJc_YP const* extReflectionClasses_ReflectionJc[];   






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



/*@DEFINE_C ********************************************************************************************/


/** External definitions of language standard types.
    Note: The types with postfix Jc are the same as in Java (int is 32 bit, long is 64 bit), the transformations from special c/c++-Types are made with define.
*/

#define reflection__uint64Jc reflection__longJc
#define reflection__int64Jc reflection__longJc
#define reflection__uint32Jc reflection__intJc
#define reflection__int32Jc reflection__intJc
#define reflection__uint16Jc reflection__shortJc
#define reflection__int16Jc reflection__shortJc
#define reflection__uint8Jc reflection__byteJc
#define reflection__int8Jc reflection__byteJc
//extern const struct Reflectionint_t{ ClassJc clazz; } reflectionint;

#define reflection_int16BigEndian reflection__shortJc
#define reflection_int32BigEndian reflection__intJc
#define reflection_floatBigEndian reflection__intJc  //don't use float, it is byte-order-changed!!!


#define reflection__uintJc reflection__intJc
#define reflection__boolJc reflection__booleanJc
//extern ClassJc reflection__booleanJc;

#define reflection__float32Jc reflection__floatJc
//extern const struct Reflectionfloat_t{ ClassJc clazz; } reflectionfloat;

extern const ClassJc reflection__longJc;
extern const ClassJc reflection__intJc;
extern const ClassJc reflection__shortJc;
extern const ClassJc reflection__byteJc;
extern const ClassJc reflection__booleanJc;
extern const ClassJc reflection__floatJc;
extern const ClassJc reflection__doubleJc;
extern const ClassJc reflection__charJc;
extern const ClassJc reflection_bitfieldJc;

extern const ClassJc reflection_ObjectJc;
extern const ClassJc reflection_StringJc;
extern const ClassJc reflection_ClassJc;
extern const ClassJc reflection_BlockHeapBlockJc;

extern const ClassJc reflection_OS_ValuePtr;
#define reflection_MemC reflection_OS_ValuePtr
#define reflection_MemSegmentJc reflection_OS_ValuePtr


/** Reflection_void is a reflection definition for a void pointer.
 */
extern const ClassJc reflection__voidJc;
extern const ClassJc reflection__ObjectifcBaseJcpp;

#define reflection__ObjectArrayJc reflection__ObjectJc
#define reflection__StringJc reflection_StringJc
#define reflection__ClassJc reflection__ObjectJc
#define reflection__ObjectJcpp reflection__ObjectJc


#if !defined(mBackRef_ObjectJc) 
  //if enhanced references are used, the REF types have own reflection const.
  //in this case they are dummies.
  #define reflection_StringBufferJcREF reflection_StringBufferJc

#endif




/*@CLASS_C Reflection__ObjectJc @@@@@@@@*/

typedef struct Reflection__ObjectJc_t
{ ClassJc clazz; //x
  MT_void_Method_void vtbl[5];
} Reflection__ObjectJc;

extern const Reflection__ObjectJc reflection__ObjectJc;


#if 0
/*
extern const struct ReflectionFieldJc_t
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





#endif //__ReflectionJc_h__

