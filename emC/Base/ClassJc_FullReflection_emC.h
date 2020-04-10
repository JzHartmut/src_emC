#ifndef HEADERGUARD_ClassJc_FullReflection_emC
#define HEADERGUARD_ClassJc_FullReflection_emC

#ifndef DEF_REFLECTION_FULL
#error Should only used with full reflection generation
#endif


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
C_TYPE typedef struct  FieldJc_t
{ 
  char name[30]; //kLengthNAME_FIELD_ReflectionJc];  //28

                 /**Nr of elements of an static array 
                 * or the bit positions of a bitfield if bitModifiers & mBitField
                 * If is is a bit field the bitModifiers is set with 
                 */
  uint16_t nrofArrayElementsOrBitfield_;

  /**If the element nrofArrayElementsOrBitfield designates the bits of a bitfield,
  * this bits represent the bit Position in the field.
  * It is a number between 0 and 31 for 32-bit-width bit fields or between 0 and upto 4095
  * for upto 128 int32_t-variables one after another which are all bitfields.
  * Note that an address calculation in C cannot be done for bitfield variables.
  * Therefore the last variable before bitfield determines the offset of the bitfield
  * and all bitfield variables one after another uses this address. Therefore the bit position
  * should be a more great number.
  */
  #define mBitInBitfield_FieldJc 0x0fff

  /**If the element nrofArrayElementsOrBitfield designates the bits of a bitfield,
  * this bits represent the number of bits of the field. Value from 1 to 15, or 0 for a 16-bit-biftield.
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

                           /**The bits 15..10 are not used in Java modifier for fields. Used for the access level. */
  #define mAccessLevel_Modifier_FieldJc 0x00001c00
  #define mChangeLevel_Modifier_FieldJc 0x00007000
  #define kBitAccessLevel_Modifier_FieldJc 10
  #define kBitChangeLevel_Modifier_FieldJc 13

                           /** position of the field inside a object of the type of the declaring class.
                           * The position is the offset from the ObjectJc base class to the field, not the offset from the total base.
                           * Because it is possible that the object is known via interface reference. A interface reference
                           * pointered the position of the pointer to the virtual table of the interface,
                           * a call of obj->toObjectJc() is necessary to get the base for this offset.
                           */
  int16     offsFieldInStruct;

  #define mOffsIsProxyIx4Target_FieldJc 0x8000

  /**Offset in a pointered class to the ObjectJcpp class structure if such base interface exists.
  This value is 0 if it is not a pointer or if it is a pointer of not Object-derivated structures.
  */
  int16     offsetToObjectifcBase;
  /** The class object representing the class or interface that declares the field represented by this Field object. */
  struct ClassJc_t const* declaringClass;
} FieldJc;


/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define INIZ_ID_FieldJc 0x0ff6

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_FieldJc (kIsSmallSize_objectIdentSize_ObjectJc + (INIZ_ID_FieldJc<<kBitIdentSmall_objectIdentSize_ObjectJc))

#define TYPESIZEOF_FieldJc (kIsSmallSize_typeSizeIdent_ObjectJc + 0x0FF60000 + sizeof(FieldJc))

/**gets the Name of the field. 
* @deprecated use name_FieldJc(...) which returns a StringJc. Reason: If the name fills the whold field of FieldJc#_name_, it is not 0-terminated.
*/
#define getName_FieldJc(THIS) ((THIS)->name)


StringJc name_FieldJc(FieldJc const* thiz);



/**Returns the type char for especially primitive fields, J I S F D for long, int short float double, etc.*/ 
char typeChar_FieldJc(FieldJc const* thiz);

struct ClassJc_t const* getType_FieldJc(FieldJc const* ythis);

#define getDeclaringClass_FieldJc(THIS) ((THIS)->declaringClass)

#define getModifiers_FieldJc(THIS) ((THIS)->bitModifiers)

#define isHandleRef_FieldJc(THIS) ( ((THIS)->bitModifiers & mPrimitiv_Modifier_reflectJc) == kHandlePtr_Modifier_reflectJc)

#define getStaticArraySize_FieldJc(THIS) (((THIS)->bitModifiers & mPrimitiv_Modifier_reflectJc) == kBitfield_Modifier_reflectJc ? 0: (THIS)->nrofArrayElementsOrBitfield_)



/** Field[] consists of ObjectArrayJc and some FieldJc elements directly after them.
*/
typedef struct  FieldJc_Y_t
{ /** Base data of every array */
  //ObjectArrayJc array;
  ObjectArrayJc head;

  #define zFieldsInHead_FieldJc_Y 10

  /** For debugging, 10 Elements are assumed. The real number of values is stored in array.len*/
  FieldJc data[zFieldsInHead_FieldJc_Y];
}FieldJc_Y;


#define FieldJcArray FieldJc_Y

//METHOD_C FieldJc_Y* new_FieldJcArray(int size);

//#define FieldARRAY FieldJcArray



/*@CLASS_C ClassJc ************************************************************************/
#ifndef __ObjectJc_defined__


struct FieldJc_t;
struct FieldJc_Y_t;
struct MethodJc_t;
struct MethodJcARRAY_t;

/**A ClassJc is the head instance of the reflection of any type using ObjectJc. It is adequat to [[javadoc/lang/Class]].
* Because the instance is defined in compile time, it should be defined as ,,const,, anyway. Therefore it can be protected
* for touching by side effects of other failures in any C program either if a memory management unit is present on the processor
* or if it is stored in a ROM. Therefore is should be defined as a C struct in a C++ environment too. 
* Note that data of a const class in C++ can be filled on constructor, therefore it is not a const in memory. A C const can be really stored in const memory.
*
* The ClassJc contains the reference to the method table too. Because of safety of an application for side-effect-failures the method table
* is constant too.
*
* This definition is contained in the header <Jc/ObjectJc.h> because some inline methods of ObjectJc need the method table reference.
*/
C_TYPE typedef struct  ClassJc_t
{ ObjectJc object;

/** The typename. If it is a Class represents a primitive type, the name is such as "int", "float", "boolean".*/
char name[32];

/** position of the base structure/class ObjectJc inside this type, it is the base address for the offset of fields.*/
int32 posObjectBase;

/**sizeof the type. Hint: It may be longer as 64 kByte, int32 is necessary. But never longer than 2 GByte*/
int32 nSize;

FieldJc_Y const* attributes;

struct MethodJcARRAY_t const* methods;

/** The superclass, ObjectJc if no other superclass.*/
struct ClassOffset_idxVtblJcARRAY_t const* superClasses;
//struct ClassJc_t const* superClass;

/** Array of interfaces to this class.*/
//ObjectJc const* interfaces;
struct ClassOffset_idxVtblJcARRAY_t const* interfaces;
//struct{ ObjectArrayJc base; ClassJc* interfaces; };

/** Some bits determines the kind of the Class, see Modifier_reflectJc*/
int32 modifiers;

/**Pointer to jump table for dynamic calls (virtual methods).
* This is a typed struct, starting with Vtbl_ObjectJc.
*/
VtblHeadJc const* mtbl;
//Method_int_Object* mtbl;

} ClassJc;

/**Compatibility. */
#define Class_Jc_t ClassJc_t

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define INIZ_ID_ClassJc 0x0ff8

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ClassJc (kIsSmallSize_objectIdentSize_ObjectJc + (INIZ_ID_ClassJc<<kBitIdentSmall_objectIdentSize_ObjectJc))

/**This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ReflectionImageJc (mIsLargeSize_objectIdentSize_ObjectJc + 0x1e000000)

/**This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ReflectionImageBaseAddressJc (kIsSmallSize_objectIdentSize_ObjectJc + 0x0ff70000)



/**Returns the name of the class as StringJc. 
* Hint: The name is not 0-terminated if the name uses the full length of the field name.
* Therefore a StringJc presentation gives the exact information. Do not use thiz->name immediately.
*/
StringJc name_ClassJc(ClassJc const* thiz);


extern_C const ClassJc reflection_ClassJc;

/**Initializes a class in RAM for runtime reflection. 
*/
extern_C void ctor_Fields_super_ClassJc(ClassJc* thiz, StringJc name, int sizeType, ObjectArrayJc const* fields, ObjectArrayJc const* super);

#define INIZ_ClassJc(OBJ, NAME) { INIZ_ObjectJc(OBJ, &reflection_ClassJc, 0), NAME }

#define INIZtypeOnly_ClassJc(OBJ, NAME) { INIZ_ObjectJc(OBJ, &reflection_ClassJc, 0), NAME }


//TODO because of multiple inheritance support the field superClasses cannot be set, because an own array is necessary.
//the multiple inheritance seems to be an unecessary feature. For complex C++ classes the interfaces may be able to use!
#define INIZsuper_ClassJc(OBJ, NAME, REFLSUPER) { INIZ_ObjectJc(OBJ, &reflection_ClassJc, 0), NAME }

/*@CLASS_C ModifierJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/** Modifiers to specify the kind of field, see class java.lang.reflect.Modifier
*/

typedef enum  Modifier_reflectJc_t
{  /**
   * The <code>int</code> value representing the <code>public</code>
   * modifier.
   */
  mPUBLIC_Modifier_reflectJc = 0x00000001

  /**
  * The <code>int</code> value representing the <code>private</code>
  * modifier.
  */
  , mPRIVATE_Modifier_reflectJc = 0x00000002

  /**
  * The <code>int</code> value representing the <code>protected</code>
  * modifier.
  */
  , mPROTECTED_Modifier_reflectJc = 0x00000004

  /**
  * The <code>int</code> value representing the <code>static</code>
  * modifier.
  */
  , mSTATIC_Modifier_reflectJc = 0x00000008

  /**
  * The <code>int</code> value representing the <code>final</code>
  * modifier.
  */
  , mFINAL_Modifier_reflectJc = 0x00000010

  /**
  * The <code>int</code> value representing the <code>synchronized</code>
  * modifier.
  */
  , mSYNCHRONIZED_Modifier_reflectJc = 0x00000020

  /**
  * The <code>int</code> value representing the <code>volatile</code>
  * modifier.
  */
  , mVOLATILE_Modifier_reflectJc = 0x00000040

  /**
  * The <code>int</code> value representing the <code>transient</code>
  * modifier.
  */
  , mTRANSIENT_Modifier_reflectJc = 0x00000080

  /**
  * The <code>int</code> value representing the <code>native</code>
  * modifier.
  */
  , mNATIVE_Modifier_reflectJc = 0x00000100

  /**
  * The <code>int</code> value representing the <code>interface</code>
  * modifier.
  */
  , mINTERFACE_Modifier_reflectJc = 0x00000200

  /**
  * The <code>int</code> value representing the <code>abstract</code>
  * modifier.
  */
  , mABSTRACT_Modifier_reflectJc = 0x00000400

  /**
  * The <code>int</code> value representing the <code>strictfp</code>
  * modifier.
  */
  , mSTRICT_Modifier_reflectJc = 0x00000800

  /**outside java definition:
  * If not 0, than it is a primitive type.
  * The value at this bits represents the nr of Bits of the primitive type in the target system.
  */
  , mPrimitiv_Modifier_reflectJc = 0x000F0000

  /**It may be a primitive with 7*8= 56 bit, it is used to designate a bitfield. */
  , kBitfield_Modifier_reflectJc = 0x00070000

  /**It is not a primitive with 9*8= 72 bit, it is used to designate a handle for a pointer.
  * This is a special feature for supporting 64-bit-addresses with 32-bit handle. The handle is the index
  * of a global address table which contains the pointer. Alternatively for 32-bit-Systems the handle is equal the pointer value.
  */
  , kHandlePtr_Modifier_reflectJc = 0x00090000

  /**outside java definition:
  * Position of this Bits.
  */
  , kBitPrimitiv_Modifier_reflectJc = 16

  /**outside java definition:
  * This bits represents the containertype.
  */
  #define m_Containertype_Modifier_reflectJc 0x00f00000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_List()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container
  * using the ListJc interface.
  */
  , kListJc_Modifier_reflectJc = 0x00100000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_List()-Property.
  * It is set if a Reference is a multiple aggregation realized with a array container
  * using the ObjectArrayJc structure.
  */
  , kObjectArrayJc_Modifier_reflectJc = 0x00200000   //do not change, compatibility with older data

                                                     /**outside java definition:
                                                     * The <code>int</code> value representing the isUML_List()-Property.
                                                     * It is set if a Reference is a multiple aggregation realized with a array container
                                                     * using the ObjectArrayJc structure.
                                                     */
  , kPtrVal_Modifier_reflectJc = 0x00300000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_List()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container
  * using the MapJc interface.
  */
  , kMapJc_Modifier_reflectJc = 0x00400000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_List()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container.
  * The realisation of the list may be specific for a UML framework, therefore the access to the elements
  * is made with the user definable UML_ListJc methods.
  */
  , kUML_LinkedList_Modifier_reflectJc = 0x00500000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_Map()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container.
  * The realisation of the list may be user specific for a UML framework, therefore the access to the elements
  * is made with the user definable UML_MapJc methods.
  */
  , kUML_Map_Modifier_reflectJc = 0x00600000

  /**outside java definition:
  * The <code>int</code> value representing the isUML_Array()-Property.
  * It is set if a Reference is a multiple aggregation realized with a list container.
  * The realisation of the list may be user specific for a UML framework, therefore the access to the elements
  * is made with the user definable UML_ArrayJc methods.
  */
  , kUML_ArrayList_Modifier_reflectJc = 0x00700000

  /**outside java definition:
  * The <code>int</code> value representing the isStaticArray-Property.
  * It is set if multiple elements are after another imediately,
  * The number of elements is hold in the FieldJc.nrofArrayElements
  */
  , kStaticArray_Modifier_reflectJc = 0x00800000   //do not change, compatibility with older data

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
  , kEmbedded_Modifier_reflectJc = 0x01000000

  /** outside java definition:
  * The <code>int</code> value representing the isReference()-Property.
  * A reference is a reference to a primitive type or structured type,
  * not inherited from ObjectJc.
  */
  , kReference_Modifier_reflectJc = 0x02000000



  /** outside java definition:
  * The <code>int</code> value representing the isEnhancedReference()-Property.
  * An enhanced reference may be reference a ObjectJc-inherited instance.
  * NOTE: mask and compare both bits mEmbedded_Modifier_reflectJc and mReference_Modifier_reflectJc!
  */
  , kEnhancedReference_Modifier_reflectJc = 0x03000000
  /** outside java definition:
  * The <code>int</code> value representing the isObjectJc()-Property.
  * It is set if the Type contains ObjectJc at its first position,
  * especially for C-struct using CRuntimeJavalike-concepts. If it is set,
  * a C-pointer cast is allowed to keep the ObjectJc-pointer.
  * The bit is not set if the type is derived from ObjectJc,
  * but don't contain it at first position
  * It is not set if
  */
  , mObjectJc_Modifier_reflectJc = 0x04000000

  /**outside java definition:
  * The <code>int</code> value representing the isObjectifc()-Property.
  * It is set if the Type is derived from ObjectJcpp.
  */
  , mObjectJcpp_Modifier_reflectJc = 0x08000000

  /**If one of the bit is set on a reference type in FieldJc, the runtype type of src should be evaluated instead. */
  , mObjectJcBased_Modifier_reflectJc = 0x0c000000


  /**The container is instanciated embeddedly. */
  , kEmbeddedContainer_Modifier_reflectJc = 0x10000000
  /**The container is referenced with a simple reference. */
  , kReferencedContainer_Modifier_reflectJc = 0x20000000
  /**The container is referenced with an enhanced reference. */
  , kEnhancedRefContainer_Modifier_reflectJc = 0x30000000



} Modifier_reflectJc;



typedef enum Mask_ModifierJc_t
{
  /**If this bit is set, it is either a reference or a enhanced reference.*/
  mReference_Modifier_reflectJc = 0x02000000

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





/*@CLASS_C ClassOffset_idxVtblJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**This type describes one entry of a interface or superclass.
* In regard of virtual methods an index inside the table of virtual methods is stored here.
*/
typedef struct ClassOffset_idxVtblJc_t
{
  /**This was the reference to the super class. But the super class is not sufficient. 
  * It needs a field which describes details of the super relation.
  * Because some generated reflection and the binary generation creates this 4 bytes (32-bit-pointer) it should not be removed.
  * But it is not used anymore. Hold it as reserve in the binary structure.
  */
  ClassJc const* unused_clazz_super;

  /** Index of the virtual table inside its parent. The array of virtual operations is in othiz->reflection.mtbl */
  int idxVtbl;

  /**The field contains all information about the super relation, especially the getType_FieldJc(superfield), the super type.
  * It is not only a helper for inspector access. 
  * It contains the name of the interface or "super"
  * and the position 0 repectively the correct position for C++ reflection. */
  FieldJc superfield;

} ClassOffset_idxVtblJc;

/**This macro calculates the index of a particulary method table inside a table, to use for idxVtbl in ClassOffset_idxVtblJc.
*/
#define OFFSET_Vtbl(TYPE, ELEMENT) ( (int)( (intptr_t)(&((TYPE*)(0x1000))->ELEMENT) - 0x1000) / (int)sizeof(MT_void_Method_void const*)) 
//#define OFFSET_Vtbl(BASE, ELEMENT) ( (MT_void_Method_void const*)(&BASE.ELEMENT) - (MT_void_Method_void const*)(&BASE)) 

/**This type describes a array of ClassOffset_idxVtblJc
* With 10 Elements to view in debug
*/
typedef struct ClassOffset_idxVtblJcARRAY_t
{ /** Base data of every array */
  ObjectArrayJc head;
  /** For debugging, 10 Elements are assumed. The real number of values is stored in array.len*/
  ClassOffset_idxVtblJc data[10];
}ClassOffset_idxVtblJcARRAY;

/**This type is the usefull type for a simple superclass. */
typedef struct ClassOffset_idxVtblJc1_t  //Type for the super class
{ ObjectArrayJc head;
ClassOffset_idxVtblJc data[1];
} ClassOffset_idxVtblJc1;




/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define INIZ_ID_ClassOffset_idxVtblJc 0x0ff9

/**Identifier for ObjectJc to describe: It's a ClassJc. This type is used in Plain Old Data-images of reflections. */
#define OBJTYPE_ClassOffset_idxVtblJc (kIsSmallSize_objectIdentSize_ObjectJc + (INIZ_ID_ClassOffset_idxVtblJc<<kBitIdentSmall_objectIdentSize_ObjectJc))


/**Initializes a super class or interface reference in RAM for runtime reflection. 
* @param refl_super The reflection for this super class or interface.
* @param ixVtbl The index of the virtual table part. Use 0 if the superclass or interface has not a Vtbl.  
*/
extern_C void ctor_ClassOffset_idxVtblJc(ClassOffset_idxVtblJc* thiz, ClassJc const* refl_super, int accesLevel, int ixVtbl);

#endif  //#ifndef __ObjectJc_defined__


/*@DEFINE_C reflection_Types********************************************************************************************/
/**reflection_Types: External definitions of language standard types.
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
//extern_C const struct Reflectionint_t{ ClassJc clazz; } reflectionint;

#define reflection_int16BigEndian reflection__shortJc
#define reflection_int32BigEndian reflection__intJc
#define reflection_floatBigEndian reflection__intJc  //don't use float, it is byte-order-changed!!!


#define reflection__uintJc reflection__intJc
#define reflection__boolJc reflection__booleanJc
//extern_C ClassJc reflection__booleanJc;

#define reflection__float32Jc reflection__floatJc
//extern_C const struct Reflectionfloat_t{ ClassJc clazz; } reflectionfloat;

extern_C const ClassJc reflection__longJc;
extern_C const ClassJc reflection__intJc;
extern_C const ClassJc reflection__shortJc;
extern_C const ClassJc reflection__byteJc;
extern_C const ClassJc reflection__booleanJc;
extern_C const ClassJc reflection__floatJc;
extern_C const ClassJc reflection__doubleJc;
extern_C const ClassJc reflection__charJc;
extern_C const ClassJc reflection__char16Jc;
extern_C const ClassJc reflection_bitfieldJc;

extern_C const ClassJc reflection_ObjectJc;

#ifndef __ObjectJc_simple__
//reflection instance for the super class ObjectJc
extern_C const ClassOffset_idxVtblJc1 reflection_super_ObjectJc;
#endif


extern_C const ClassJc reflection_StringJc;
extern_C struct ClassJc_t const reflection_CharSeqJc;
//extern_C const ClassJc reflection_ClassJc;
extern_C const ClassJc reflection_BlockHeapBlockJc;

extern_C const ClassJc reflection_OS_PtrValue;
#define reflection_MemC reflection_OS_PtrValue
#define reflection_MemSegmentJc reflection_OS_PtrValue


/** Reflection_void is a reflection definition for a void pointer.
*/
extern_C const ClassJc reflection__voidJc;
extern_C const ClassJc reflection__ObjectJcpp;

#define reflection__ObjectArrayJc reflection_ObjectJc
#define reflection__StringJc reflection_StringJc
#define reflection__ClassJc reflection__ObjectJc


/**Definition of constant values for primitive type reflection
* and some special classes.
* @deprecated because using kXYZ for a defined constant is better to read. It is more mmemonicly.
*/
typedef enum DeprecatedScalarTypes_ClassJc_t
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
  REFLECTION_boolean_ClassJc    = 0x0f,
  REFLECTION_String_ClassJc     = 0x10,
  REFLECTION_complexfloat_ClassJc  = 0x14,
  REFLECTION_complexdouble_ClassJc = 0x15,
  REFLECTION_bitfield_ClassJc   = 0x17,
  REFLECTION_afterlastPrimitive_ClassJc       = 0x50
}DeprecatedScalarTypes_ClassJc;

/**Definition of constant values for primitive type reflection
* and some special classes.
*/
typedef enum ScalarTypes_ClassJc_t
{
  kREFLECTION_void_ClassJc       = 0x01,
  kREFLECTION_int64_ClassJc      = 0x02,
  kREFLECTION_uint64_ClassJc     = 0x03,
  kREFLECTION_int32_ClassJc      = 0x04,
  kREFLECTION_uint32_ClassJc     = 0x05,
  kREFLECTION_int16_ClassJc      = 0x06,
  kREFLECTION_uint16_ClassJc     = 0x07,
  kREFLECTION_int8_ClassJc       = 0x08,
  kREFLECTION_uint8_ClassJc      = 0x09,
  kREFLECTION_int_ClassJc        = 0x0a,
  kREFLECTION_uint_ClassJc       = 0x0b,
  kREFLECTION_float_ClassJc      = 0x0c,
  kREFLECTION_double_ClassJc     = 0x0d,
  kREFLECTION_char_ClassJc       = 0x0e,
  kREFLECTION_bool_ClassJc       = 0x0f,
  #define kREFLECTION_boolean_ClassJc kREFLECTION_bool_ClassJc

  kREFLECTION_complexint16_ClassJc = 0x11,
  kREFLECTION_complexint32_ClassJc = 0x12,
  kREFLECTION_complexint64_ClassJc = 0x13,
  kREFLECTION_complexfloat_ClassJc = 0x14,
  kREFLECTION_complexdouble_ClassJc = 0x15,

  kREFLECTION_bitfield_ClassJc      = 0x17,

  kREFLECTION_ObjectJc              = 0x19,
  kREFLECTION_ObjectJcpp            = 0x1a,
  kREFLECTION_Object_ArrayJc        = 0x1b,

  kREFLECTION_StringJc              = 0x1d,
  kREFLECTION_OS_PtrValue           = 0x1e,

  kREFLECTION_ClassJc               = 0x20,

  kREFLECTION_afterlastPrimitive_ClassJc       = 0x50
}ScalarTypes_ClassJc;


/**Array contains the number of byte which were used if the scalar types with designation 0..0x17
* are stored in a byte structure. 
* 
* see see javaSrc_vishiaBase/org.vishia.reflect.Java2C.nrofBytesScalarTypes.
*/
extern const int nrofBytesScalarTypes_ClassJc[];






/**The next defines are necessary because the automatic code generation generates such types if void * or void* or char* is written.*/
#define REFLECTION_void_Pointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_voidPointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_charPointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )
#define REFLECTION_char_Pointer       ((struct ClassJc_t const*) REFLECTION_void_ClassJc )

/**Reflection of standard types. This identifier can be used to assign the symbolic value to a ClassJc const* pointer
* espacially for const Initializer definitions.
* The access is done always with getClass_FieldJc(FieldJc const* thiz). This routine converts with the const simpleTypes_ClassJc in Reflection_emC.c
*/
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



#define REFLECTION_complexint16  ((struct ClassJc_t const*) kREFLECTION_complexint16_ClassJc
#define REFLECTION_complexint32  ((struct ClassJc_t const*) kREFLECTION_complexint32_ClassJc
#define REFLECTION_complexint64  ((struct ClassJc_t const*) kREFLECTION_complexint64_ClassJc
#define REFLECTION_complexfloat  ((struct ClassJc_t const*) kREFLECTION_complexfloat_ClassJc
#define REFLECTION_complexdouble ((struct ClassJc_t const*) kREFLECTION_complexdouble_ClassJc

#define REFLECTION_ObjectJcpp ((struct ClassJc_t const*) kREFLECTION_ObjectJcpp )
#define REFLECTION_ObjectJc          ((struct ClassJc_t const*) kREFLECTION_ObjectJc )
#define REFLECTION_ObjectJcpp        ((struct ClassJc_t const*) kREFLECTION_ObjectJcpp )
#define REFLECTION_Object_ArrayJc    ((struct ClassJc_t const*) kREFLECTION_Object_ArrayJc )
#define REFLECTION_StringJc          ((struct ClassJc_t const*) kREFLECTION_StringJc )
#define REFLECTION_ClassJc           ((struct ClassJc_t const*) kREFLECTION_ClassJc )



#define kREFLECTION_LastConstant      0x50



/**The float_complex is defined in os_types_def_common.h. The reflection are defined in ReflectionBastTypesJc.c. */
extern_C const ClassJc reflection_float_complex;  //the just defined reflection_

                                                  /**The double_complex is defined in os_types_def_common.h. The reflection are defined in ReflectionBastTypesJc.c. */
extern_C const ClassJc reflection_double_complex;  //the just defined reflection_



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
, mObjectJcpp_Modifier_reflectJc   \
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
METHOD_C struct FieldJc_Y_t const* getDeclaredFields_ClassJc(ClassJc const* ythis);//sss

METHOD_C struct FieldJc_t const* getDeclaredField_ClassJc(ClassJc const* ythis, StringJc sName);

METHOD_C struct MethodJcARRAY_t const* getDeclaredMethods_ClassJc(ClassJc const* ythis);

METHOD_C struct MethodJc_T const* getDeclaredMethod_ClassJc(ClassJc const* ythis, char const* sName);


METHOD_C ClassJc const* getEnclosingClass_ClassJc(ClassJc const* ythis);

/**Returns the type of the super class for this class or null. */
METHOD_C ClassJc const* getSuperClass_ClassJc(ClassJc const* thiz);

/**Returns the field which describes the access to the super class data for this class or null. */
METHOD_C struct FieldJc_t const* getSuperField_ClassJc(ClassJc const* thiz);

/**gets the Name of the class. It is a static method, because the argument class may be a constant for simple types.
* @param class Either the class object or a constant to design simple types, see REFLECTION_xxx.
* @deprecated use name_ClassJc(...) which returns a StringJc. Reason: If the name fills the whold field of ClassJc#_name_, it is not 0-terminated.
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

/** returns true if the type is a instance of a C++-class, based on ObjectJcpp.
* It may be also a reference to a interface. The reference type should based on ObjectJcpp.
* This method is defined outside java, in java all classes based only on Object.
*/
#define isObjectJcpp_ClassJc(THIS) ((THIS->modifiers & mObjectJcpp_Modifier_reflectJc)!=0)








#endif HEADERGUARD_ClassJc_FullReflection_emC
