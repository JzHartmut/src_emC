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
 * @content This file defines basicly properties of each data like java.lang.Object.
 *
 * @author Hartmut Schorrig www.vishia.org
 * @version 0.94
 * list of changes:
 * 2010-11-13: Hartmut: ObjectArrayJc, change the order of elements, length as second. It is prepared for multi-dimension arrays.
 * 2009-11-25: Hartmut
 *   new: getRestBlock_ObjectJc(...) to improve usage of Blockheap if possible.
 *   chg: wait_ObjectJc(...), notify_ObjectJc(...) with ThreadContext as last argument.
 *   chg: activateGarbageCollectorAccess_BlockHeap_emC(...) has 2. argument EXCLOBJ, here only for empty definiition while using without Blockheap.
 * 2009-06-14: Hartmut new: newIdent_ObjectJc() declared.
 * 2008-04-22: JcHartmut docu
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#ifndef HEADERGUARD_ObjectJc_h
#define HEADERGUARD_ObjectJc_h
#include <applstdef_emC.h>
#include <emC/Base/Object_emC.h>
//#include "emC/SimpleC_emC.h"  //should be includeed in applstdef_emC.h
//#include "emC/Base/MemC_emC.h"     //should be includeed in applstdef_emC.h
//  ////should be includeed in applstdef_emC.h, knowledge of Thcxt, Exception is supplied
//#include "emC/Base/String_emC.h"  //should be includeed in applstdef_emC.h
#include <emC/Jc/StringJc.h>

/*@CLASS_C ObjectJc_ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**ObjectJc_: This division in the headerfile <Jc/ObjectJc.h> contains the definitions of [[class_ObjectJc]]
 * whith deeper pure ObjectJc-concepts.
 */

//NOTE: the Definition of the struct is containing in objectBaseC.h



/**Finishes the startup phase and sets the run mode.
 * 
 */
METHOD_C int setRunMode_ObjectJc(ThCxt* _thCxt);



/**Tests wether it is an ObjectJc-based instance or not. The criterium is, the ownAddress inside ObjectJc must be identical with the instance address.
 * @throws an exception if it is not true.
 * @deprecated
 */
#define XXXtestConsistence_ObjectJc(SRC) { if( (SRC) != null && (SRC) != (SRC)->ownAddress ) THROW(RuntimeException, "no ObjectJc-based instance.", (int)(SRC)); }

//The null pointer may be tested outside, or it should cause an exception outside if it is unexpected.
//METHOD_C 
//see on end: VtblHeadJc const* checkVtbl_ObjectJc(ObjectJc const* ythis, int ix, char const* sign, ThCxt* _thCxt);



/**********************************************************************************************
 * Methods for thread synchronization
 */


/**The synchronized(obj) keyword from Java. */
METHOD_C void synchronized(ObjectJc* obj);

/**New identifier, better associated to ObjectJc (there are global link labels! 
 * Note the original identifier isn't changed yet, because some libraries use it.
 */
#define synchronized_ObjectJc synchronized   
#define endSynchronized_ObjectJc synchronizedEnd   

/**The synchronizedEnd-Methode should be called on end of a synchronized block.
 * write:
 * ,,  synchronized(obj);
 * ,,  { //critical section
 * ,,  }synchronizedEnd(obj);
 */
METHOD_C void synchronizedEnd(ObjectJc* obj);

/**The wait method, see java.lang.Object.wait(long),
 * In opposite to original Java, the millisecond arg is 32 bit, so the max wait time is limited to about 24 days.
 */
METHOD_C void wait_ObjectJc(ObjectJc* obj, int milliseconds, ThCxt* _thCxt);


/**The notify method, see java.lang.Object.wait(long),
 */
METHOD_C void notify_ObjectJc(ObjectJc* obj, ThCxt* _thCxt);

/**The notifyAll method, see java.lang.Object.wait(long),
 */
METHOD_C void notifyAll_ObjectJc(ObjectJc* obj, ThCxt* _thCxt);



/*@CLASS_C ObjectArrayJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**ObjectArrayJc_: This division in the headerfile <Jc/ObjectJc.h> contains the definitions of [[class_ObjectJc]]
 * whith deeper pure ObjectJc-concepts.
 */

//NOTE: the Definition of the struct is containing in objectBaseC.h




extern_C const struct ClassJc_t refl_ObjectArrayJc;

/** initializes the data of the array. This includes the head and the associated data. It is the rule or law,
 *  that all data are disposed immediately after the head of array. The data are set to 0.
 *
 *  @param ythis The head of the array.
 *  @param size  The number of elements of the 1-dimensional array
 *  @param nBytesPerElement sizeof(ElementType)
 *  @param reflection The reflection definition
 *  @param typeInstanceIdent The Type or Instance Id without size information but with the kind of size information, see kIsMediumSize_objectIdentSize_ObjectJc.
 *
 */
METHOD_C ObjectArrayJc* ctorc_ObjectArrayJc(ObjectArrayJc* ythis, int size, int nBytesPerElement, struct ClassJc_t const* REFLECTION, int32 typeInstanceIdent);
#define ctor_ObjectArrayJc(YTHIS, SIZE, BYTESPERELEMENT, REFLECTION, IDENT) ctorc_ObjectArrayJc(YTHIS, SIZE, BYTESPERELEMENT, REFLECTION, IDENT) 

/**initializes a ObjectArrayJc, see [[ctorc_ObjectArrayJc(...)]].
 * @param rawMem raw memory area, it may be uninitialized. 
 *        The size may be greater as necessary. The constructor initializes only its own area.
 * @throws IllegalArgumentException if the sizeof rawMem is to less.  
 */
METHOD_C ObjectArrayJc* ctorM_ObjectArrayJc(MemC rawMem, int size, int nBytesPerElement, struct ClassJc_t const* REFLECTION, int32 typeInstanceIdent);


/**initializes a ObjectArrayJc, see [[ctorc_ObjectArrayJc(...)]].
 * @param rawMem raw memory area, it may be uninitialized. 
 *        The size may be greater as necessary. The constructor initializes only its own area.
 * @throws IllegalArgumentException if the sizeof rawMem is to less.  
 */
METHOD_C ObjectArrayJc* ctorO_ObjectArrayJc(ObjectJc* objthis, int size, int nBytesPerElement, struct ClassJc_t const* REFLECTION, int32 typeInstanceIdent);




/**creates an new Array of any desired struct type. The memory for the array is allocated, all elements are setted to 0,
 * and the ObjectArray-Head-Structure is initialized.
 * Do not use this method to create an array of a C++ class, because there constructors are not called
 * and no virtual-table-pointer are initialized.
 * @param size Number of elements of the 1-dimensional array.
 * @param bytesPerElement This value should be written as ,,sizeof(ElementType),,.
 * @param reflection The reflection class of the elements. Note: The elements need not have ObjectJc as baseclass.
 *        The access to reflection info is possible via the array head.
 * @param typeInstanceIdent It may be 0. If the data are evaluate in a POD plain old data data image,
 *        the value may be important. See element ,,objectIdentSize,, in ,,ObjectJc,,.
 *        But here only the ident bits, not the size should be given.
 * @param STACKTRCP My be null, if no memory allocation error is expected.
 * @return The pointer of the allocated data as reference to ObjectArrayJc. A casting outside is necessary, see macro new_ARRAYJc.
 * @throws RuntimeException if no memory is allocatable.
 */
METHOD_C ObjectArrayJc* new_ObjectArrayJc(int size, int bytesPerElement, struct ClassJc_t const* reflection, int32 typeInstanceIdent);


#define free_ObjectArrayJc(THIZ){ free_ObjectJc(&(THIZ)->object); }


/**returns the address of the first element of the array. The type depends on the derived declaration. 
 * Therefore it is untyped here. 
 * @param size pointer to a int-variable to return the size of the whole array inclusive the head.  
 *             If this pointer is null, the size isn't returned.
 */
METHOD_C MemUnit* getAddrSizeof_ObjectArrayJc(ObjectArrayJc* ythis, int32* size);


/**Builds a MemC struct and returns it per value.
 * This is a helper method to supply a MemC argument in a method call.
 */
METHOD_C MemC buildFromArrayX_MemC(ObjectArrayJc* objArray);


/**Gets the pointer to an element in the data area of the array, indexed by idx.
   This method returns a non constant untyped pointer. The user should cast it to the correct type.
   To do so, the definition of an access macro is recommended in a users header.
 */
METHOD_C void* get_i_ObjectArrayJc(ObjectArrayJc const* ythis, int idx);

/** Gets the size of the array, it means number of elements of the array, not number of bytes.
  It is the content of element length. Because it is a simple access a define may be a possible implementation.
  An compiler-errormessage may be clear cut, if the user works with wrong argument BASE.
*/
#define size_ObjectArrayJc(BASE) ((BASE)->length)
//METHOD_C int size_ObjectArrayJc(const ObjectArrayJc* base);


/** Gets the number of bytes of the whole array calculated from the informations inside the head.
  */
METHOD_C int getNrofBytes_ObjectArrayJc(ObjectArrayJc const* ythis);
#define getNrOfBytes_ObjectArrayJc(THIS) getNrofBytes_ObjectArrayJc(THIS)


/**Macro to define the reflection of an array of any type, able to use in a C-File.
 * @param TYPE the type of the array elements.
 */
#define DEFINE_REFLECTION_ARRAYJc(TYPE) \
  extern struct ClassJc_t const refl_##TYPE##_Y; \
  const struct Reflection_Fields_##TYPE##_Y_t{ ObjectArrayJc head; FieldJc data[2];} refl_Fields_##TYPE##_Y = \
  { CONST_ObjectArrayJc(FieldJc, 2, OBJTYPE_FieldJc, null, &refl_Fields_##TYPE##_Y) \
  , { { "head", 0 , &refl_ObjectArrayJc, 0, 0, 0, &refl_##TYPE##_Y } \
    , { "data", 0 , &refl_##TYPE, 0, 0, 0, &refl_##TYPE##_Y } \
  } }; \
  const ClassJc refl_##TYPE##_Y =\
  { CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_##TYPE##_Y, null) \
  , "Y", 0, sizeof(TYPE##_Y), (FieldJcArray const*)&refl_Fields_##TYPE##_Y \
  }




/*@DEFINE ARRAYJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**ARRAYJc: Macros for definition of arrays.
 */


/**This macro helps to define user specific javalike array pointer. 
 * The structure of the user defined type follows the structure of ObjectArrayJc. 
 * But because a direct access to the element length should be ... 
 */
#define TYPEDEF_AYJc(TYPE) \
typedef struct TYPE##_Y_t{ ObjectJc object; int32 length; int16 sizeElement; int16 mode; TYPE data[50]; } *TYPE##_Y; \
typedef struct TYPE##_YREF_t{ ObjectRefValuesJc refbase; TYPE##_Y ref; } TYPE##_YREF

#define TYPEDEF_AYPJc(TYPE) \
typedef struct TYPE##_YP_t{ ObjectJc object; int32 length; int16 sizeElement; int16 mode; TYPE* data[50]; } *TYPE##_YP; \
typedef struct TYPE##_YPREF_t{ ObjectRefValuesJc refbase; TYPE##_YP ref; } TYPE##_YPREF


/**Macro to define a Object based array.
   syntactical using as type in form
   , typedef ARRAYJc(MyElementType, 23) MyArrayType;
   or
   , ARRAYJc(MyElementType, 23) myArrayData;
   It results as a definition in form:
   , struct { Object_ArrayJc head; TYPE data[SIZE]; }
   @param TYPE the type of the elements
   @param SIZE nr of elements to shown in the array type. Often the defined arraytype
          is used as pointer, in that cases the number of elements may not be identical
          with the number of elements defined here. Use new_ARRAYJc to get a instance.
   @return inappropriate, it is used like a type.
 */
//#define ARRAYJc(TYPE, SIZE) struct { ObjectJc object; int32 length; int16 sizeElement; int16 mode; TYPE data[SIZE]; }
//#define ARRAYJc(TYPE, SIZE) struct { ObjectArrayJc head; TYPE data[SIZE]; }


#define ctor_AYJc(OBJ, SIZE) { ctorc_ObjectJc(&(OBJ)->object); setIdentAndSize_ObjectJc(&(OBJ)->object, 0, sizeof_AYJc((OBJ)->data[0], SIZE)); (OBJ)->length = SIZE; (OBJ)->sizeElement = sizeof((OBJ)->data[0]); } 

/** Gets the reference of the addressed element of an array with any desired type.
  * This is a macro because the type is unknown here and kept from the users ARRAY
  * by macro expansion.
  * @param ARRAY instance of an array, must construct with "ObjectArrayJc head; Usertype data;"
  * @param IDX the index of the instance
  * @return the "left value" as C-syntax of the element.
  * @throws IndexOutOfBoundsException if the IDX is failed.
  *Note: 3thrd Parameter TYPE is necessary for universal use, especially THROWJc
  */
#define element_AYJc(ARRAY, IDX) \
  (  (IDX) < 0 || (IDX) >= (ARRAY)->length ? /*(TYPE)THROWJc(IndexOutOfBoundsExceptionJc, "", 0)*/ null :  &((ARRAY)->data[IDX]) )
#define element_ARRAYJc(ARRAY, IDX) \
  (  (IDX) < 0 || (IDX) >= (ARRAY)->head.length ? /*(TYPE)THROWJc(IndexOutOfBoundsExceptionJc, "", 0)*/ null :  &((ARRAY)->data[IDX]) )


  /** calculates the size of an array with ObjectArrayJc-Head in compiletime.
    * This is a macro because the type is given.
    * @param TYPE The type of the elements.
    * @param SIZE The number of the elements.
    * @return The number of bytes
    */
#define sizeof_AYJc(TYPE, SIZE) (sizeof(ObjectJc) + 2*sizeof(int32) + (SIZE) * sizeof(TYPE))
#define sizeof_ARRAYJc(TYPE, SIZE) (sizeof(ObjectArrayJc) + (SIZE) * sizeof(TYPE))


/**creates an new Array of the given struct type. The memory for the array is reserved, all elements are setted to 0,
 * and the ObjectArray-Head-Structure is initialized.
 * Do not use this method to create an array of a C++ class, because there constructors are not called
 * and no virtual-table-pointer are initialized.
 *
 * @param TYPE The type of the elements. It should be a struct type.
          It is used to calculate the sizeof(TYPE) for memory allocation and to cast the result pointer to the expected type.
 * @param SIZE Number of elements of the 1-dimensional array.
 * @param REFLECTION The reflection class of the elements. Note: The elements need not have ObjectJc as baseclass.
 *        The access to reflection info is possible via the array head.
 * @param IDENT It may be 0. If the data are evaluate in a POD plain old data data image,
 *        the value may be important. See element ,,objectIdentSize,, in ,,ObjectJc,,.
 *        But here only the ident bits, not the size should be given.
 * @return The pointer of the allocated data in the correct type reference.
 * @throws RuntimeException if no memory is allocatable. In the environment the STACKTRC_ENTRY("name") should be present.
 */
#define new_ARRAYJc(TYPE, SIZE, REFLECTION, IDENT) ((TYPE##Array*)(new_ObjectArrayJc(SIZE, sizeof(TYPE), REFLECTION, IDENT)))



/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/*@DEFINE_C EnhancedReferences @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**EnhancedReferences: Enhanced references contains the reference itself and an additional integer value. 
 * Any reference in a struct-type should be enhanced, if the platform should use them.
 * The enhanced references can be used to register all references. 
 * It supports garbage collection in any form.
 *
 * Because the usage of enhanced references may be ineffective on cheap 16-bit-controller,
 * there are defined platform-depending: 
 * The macro ,,REFTYPEDEF,, is containing in the headerfile <fw_Platform_conventions.h>.
 * The macro is used to define types which presents the enhanced reference for any struct type.
 *
 * The enhanced references are present in a given platform, independently of there usage
 * of any garbage collection algorithm. The methods defined for the usage of enhanced references
 * may be implemented with several algorithm depending on the garbage-collection or other
 * reference-management-software moduls.
 */


//typedef int8_Y* int8_YREF;

#define int8_YREFDEF
typedef TYPE_EnhancedRefJc(int8_Y);

#define int16_YREFDEF
typedef TYPE_EnhancedRefJc(int16_Y);
//TYPEDEF_AYJc(int16);

#define int32_YREFDEF
typedef TYPE_EnhancedRefJc(int32_Y);

#define int64_YREFDEF
typedef TYPE_EnhancedRefJc(int64_Y);

#define bool_YREFDEF
typedef TYPE_EnhancedRefJc(bool_Y);

#define char_YREFDEF
typedef TYPE_EnhancedRefJc(char_Y);

#define void_YREFDEF
typedef TYPE_EnhancedRefJc(void_Y);

#define ObjectJcREFDEF
typedef TYPE_EnhancedRefJc(ObjectJc);


#ifndef LogMessageFWREFDEF
//  #define LogMessageFWREFDEF
//  DEFINE_EnhancedRefJc(LogMessageFW);
#endif






/*@DEFINE_C IFC_IMPL_dataMETHOD1_ObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**IFC_IMPL_dataMETHOD1_ObjectJc: This macro helps to define the reflections and the method table for a given abstract class
 * which has the following definition in Java ...
 * ,,public abstract class TYPE
 * ,,{ @Java4C.SimpleRef public Object data;
 * ,,  public abstract void METHOD(...);
 * ,,}
 * It is a universal approach with one data reference to any data and one method whith a specific signature.
 * The given abstract class should be defined in C language usual with Java2C-translation or maybe manual written. 
 * Especially the definition of the structure
 * ,,typedef struct TYPE_t 
 * ,,{ union { ObjectJc object; } base; 
 * ,,  struct ObjectJc_t* data;   
 * ,,} TYPE_s;
 * and the method table
 * ,,extern const char sign_Vtbl_TYPE[]; //marker for methodTable check
 * ,,typedef struct Vtbl_TYPE_t
 * ,,{ VtblHeadJc head;
 * ,,  MT_METHOD_TYPE* METHOD;
 * ,,  Vtbl_ObjectJc ObjectJc;
 * ,,} Vtbl_TYPE;
 * should be given. Whereby ,,TYPE,, and ,,METHOD,, are any proper definitions. 
 * The ,,MT_METHOD_TYPE,, is the function-Type of the method which should be matched to the user defined method.
 * It is for example:
 * ,,typedef void MT_METHOD_TYPE(TYPE_s* thiz, int arg1, float arg2, ThCxt* _thCxt);
 *
 * The implementing method should be defined as simpe C method 
 * with the appropriate signature. Use this macro to define the reflection with method table which is used
 * as ''derived anonymous class'' (Java slang) based on the given TYPE. It is to deal with the overridden method.
 *
 * An instance of this can be defined then with
 * ,,TYPE_s myImpl = CONST_ObjectJc(0, &myImpl, &refl_METHOD);
 * This type has the reflection with reference to the implementing method but the data of the struct definition.
 * 
 * The macro defines 2 const variable:
 * * mtbl_METHOD: The method table of the interface type with the given method.
 * * refl_METHOD: Reflection for the given variable refers the mtbl_METHOD.
 *
 * All 2 generated variable are const, therefore assigned to a const segment by linking. There are static global,
 * therefore only a unique name in this compilation unit is necessary. Note that the reference of the variable
 * can be forwarding to other parts of code.
 *
 * @param TYPE Type name of the interface without suffix _s. It should be given: ,,struct TYPE_t{...}TYPE_s;
 * @param METHOD Only the name of the method which implements the only 1 interface method. 
 *    This METHOD name is used both as name for the Vtbl_ and Reflection. The METHOD should match to the method definiton
  
 * @since 2015-06-14. It is the concequently usage of ObjectJc overridden methods, prepared for C usage.  
 */
//Note: extern_C static resp. extern static is not accepted by gcc. extern declaration; static definition is not accepted too. 
#define IFC_IMPL_dataMETHOD1_ObjectJc(TYPE, METHOD) \
Vtbl_##TYPE static const mtbl_##METHOD = \
{ { sign_Vtbl_##TYPE , (struct Size_Vtbl_t*)((0 +2) * sizeof(void*)) } \
, METHOD \
, { { sign_Vtbl_ObjectJc, (struct Size_Vtbl_t*)((5 +2) * sizeof(void*)) } \
  , clone_ObjectJc_F, equals_ObjectJc_F, finalize_ObjectJc_F, hashCode_ObjectJc_F \
  , toString_ObjectJc_F \
  } \
} /*, { signEnd_Vtbl_ObjectJc, null } }*/; \
\
\
extern_C struct ClassJc_t const refl_##METHOD; \
static const struct Reflection_Fields_##METHOD_t  \
{ ObjectArrayJc head; FieldJc data[1]; } refl_Fields_##METHOD = \
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &refl_Fields_##METHOD) \
, { { "data" \
    , 0  \
    , &refl_ObjectJc \
    , kReference_Modifier_reflectJc  \
    , (int16)((int32)(&((TYPE##_s*)(0x1000))->data) - (int32)(TYPE##_s*)0x1000) \
    , 0   \
    , &refl_##METHOD \
    } \
} }; \
const ClassJc refl_##METHOD =  \
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &refl_ObjectJc, &refl_ClassJc)  \
, #METHOD \
,  0  \
, sizeof(TYPE##_s) \
, (FieldJcArray const*)&refl_Fields_##METHOD \
, null /*methods*/  \
, null /*superclasses */  \
, null  \
, 0     \
, &mtbl_##METHOD.head   \
};


//TODO check usage of existing fields:
//extern const struct Reflection_Fields_##TYPE##_s_t refl_Fields_##TYPE##_s;
//  , (FieldJcArray const*)&refl_Fields_##TYPE##_s


/*@CLASS_CPP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)


  /*=====================================================================================*/
  /* C++-version of Object, named ObjectJcpp */

  class ObjectJcpp;
  struct ClassJc_t;



  class ObjectBaseJcpp: public ObjectJcpp //, public virtual ObjectBaseJc
  {

    /** The destructor. It should be virtual because the correct destructor
        for an instance by referencing the instance via a base class must be used.
    */
    public: virtual ~ObjectBaseJcpp(){}

    virtual StringJc toString()=0;

    virtual void finalize()=0;

    public: virtual ObjectJcpp* toObjectJcpp()=0;
    public: virtual ObjectJc* toObjectJc()=0;


  };

//  #endif
//  #endif
//  #endSBNF

  class  ObjectJcpp: public ObjectJcpp, public ObjectJc
  {
    /** The data from the C-like class: */
    //private: ObjectJc objectdata;


    /** RuntimeHeap is the class to get Block in Heap on Runtime.
        The protected method finalize() should be accesable from Runtimeheap.
    */
    friend class RuntimeHeap;

    /** Access also to private attributes in reflection.
    */
    friend class Reflection__Object;


    /** default constructor with no reflection information. The reflection  pointer will be
        setted to Reflection__Object.
    */





   /**copy-constructor*/
    //Object(const Object&);


    /** Implements virtual method from Object__BaseJc. Because the method here
        is not virtual, no further overload can be done.<br/>
        The type conversion to Object* is required in baseclass (interface) Object__Base
        and is implemented here. It returns this. Note that the value of the this-pointer
        dependence on the inheritance structure. A this-pointer of type of an interface
        pointered exactly the virtual table of the interface, a this-pointer of a multiple
        inheranced base class pointered the part of the class represented this base class.
        It is not equal to the this-pointer to the instance itself, referenced with the
        instance-type pointer. The compiler adds or subtracts some adress differences.
    */
    //public: operator ObjectJcpp*(){ return this; }  //type conversion

    /** see java-documentation*/
    public: int hashCode() const;

    /** wake up one waiting thread if any threads called wait().
        It wakes up exactly one thread, but it is not defined which thread if several
        threads are waiting.
    */
    public: void notify();

    /** wake up all waiting thread if any threads called wait().
    */
    public: void notifyAll();

    /** to fall asleep the current thread. The Thread will be waked up
        either by calling notify on this object from another thread or if the time is expired.
        If the value of time is less 0, no timeout is used.
    */
    public: void wait(long nTime = -1);


    public: ObjectJcpp* clone() const;

    public: class ClassJcpp const* getClass() const;


    /** casting from Object* to String
    */
    //operator class String();
    //operator class String&();
    //operator class String*();




    /** substitue the java operator instanceof
    */
    public: bool instanceof( struct ClassJc_t const* reflection);

    /** compare to content of the instance, take the length in memory over reflection
    */
    public: virtual bool equals(ObjectJcpp const* obj) const
    {
      //return this == obj;
      return false; //toObjectJc() == obj;
    }

    //void synchronized(class ObjectJcpp* obj);

    //void synchronizedEnd(class ObjectJcpp* obj);


    /** In the runmode parentRef() is to be execute for all member references of a class.
     ** The runmode is to coordinate with the using of RuntimeHeap.
     ** parentRef() are necesserry for the garbage collector.
    */
    static bool isRunMode();





    /** setuseless is used instead of garbage collection in C++. If any application don't need this instance
        furtherly, it called setuseless(). The instance itself must clarify the conditions to delete or destroy it.
        Thats why the user should overwrite this method.<br/>
        The default manner is to delete the instance immediately.
    */
    public: virtual void setuseless(){ delete this; }

    /** delete__ called by garbage collector at last, to free system ressources*/
    public: void delete__();

    public: ObjectJcpp()
    { ObjectJc* ythis = static_cast<ObjectJc*>(this);
      init0p_MemC(ythis, sizeof(ObjectJc));  //note: ctorc don't initialze with 0.
      ctorc_ObjectJc(ythis); 
    }


    void setReflection(struct ClassJc_t const* reflection, int32 typeInstanceSizeIdent = 0)
    //{ setReflection_Object(&(this->objectdata), reflection);
    {
      setReflection_ObjectJc(static_cast<ObjectJc*>(this), reflection, typeInstanceSizeIdent);
    }


    //virtual StringJc toString(){ STACKTRC_ENTRY("ObjectJcpp::toString"); return toString_ObjectJc_F(static_cast<ObjectJc*>(this), _thCxt); }

    virtual void finalize(){}



    public: virtual ObjectJc* toObjectJc(){ return this;}
    public: virtual ObjectJcpp* toObjectJcpp(){ return this;}
  };

#endif  /*__CPLUSPLUSJcpp*/




/*@CLASS_C Thread_Jc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


METHOD_C void sleep_Thread_Jc(int32 milliseconds);



/*@CLASS_C MathJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef __MathJc_h__
//	#include <Jc/MathJc.h>
#endif
/*@CLASS_C IntegerJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#define MAX_VALUE_IntegerJc 0x7FFFFFFF
#define MIN_VALUE_IntegerJc 0x80000000

/**Parses the string argument as a signed decimal integer. The characters in the text must all be decimal digits,
 * except that the first character may be an ASCII minus sign '-' ('\u002D') to indicate a negative value.
 * The resulting integer value is returned, exactly as if the argument and the radix 10 were given as arguments
 * to the parseInt(java.lang.String, int) method.
 * @param s String containing the int representation to be parsed
 * @return the integer value represented by the argument in decimal.
 * @throws NumberFormatException - if the text does not contain a parsable integer.
 * @javaLike
 */
METHOD_C int parseInt_radix_IntegerJc(StringJc src, int radix);


/**Parses the string argument as a signed decimal integer. The characters in the text must all be decimal digits,
 * except that the first character may be an ASCII minus sign '-' ('\u002D') to indicate a negative value.
 * The resulting integer value is returned, exactly as if the argument and the radix 10 were given as arguments
 * to the parseInt(java.lang.String, int) method.
 * @param s String containing the int representation to be parsed
 * @return the integer value represented by the argument in decimal.
 * @throws NumberFormatException - if the text does not contain a parsable integer.
 * @javaLike
 */
#define parseInt_IntegerJc(src) parseInt_radix_IntegerJc(src, 10)


/*@CLASS_C FloatJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

METHOD_C int32 floatToRawIntBits_FloatJc(float val);
METHOD_C int32 floatToIntBits_FloatJc(float val);



METHOD_C float intBitsToFloat_FloatJc(int32 val);

//#define intBitsToFloat_FloatJc(val) (*((float*)(&val)))

/**Parses the string argument as a signed decimal integer. The characters in the text must all be decimal digits,
 * except that the first character may be an ASCII minus sign '-' ('\u002D') to indicate a negative value.
 * The resulting integer value is returned, exactly as if the argument and the radix 10 were given as arguments
 * to the parseInt(java.lang.String, int) method.
 * @param s String containing the int representation to be parsed
 * @return the integer value represented by the argument in decimal.
 * @throws NumberFormatException - if the text does not contain a parsable integer.
 * @javaLike
 */
METHOD_C float parseFloat_FloatJc(StringJc src);

/*@CLASS_C DoubleJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

METHOD_C int64 doubleToRawLongBits_DoubleJc(double val);
METHOD_C int64 doubleToLongBits_DoubleJc(double val);

METHOD_C double longBitsToDouble_DoubleJc(int64 val);

/**Parses the string argument as a signed decimal integer. The characters in the text must all be decimal digits,
 * except that the first character may be an ASCII minus sign '-' ('\u002D') to indicate a negative value.
 * The resulting integer value is returned, exactly as if the argument and the radix 10 were given as arguments
 * to the parseInt(java.lang.String, int) method.
 * @param s String containing the int representation to be parsed
 * @return the integer value represented by the argument in decimal.
 * @throws NumberFormatException - if the text does not contain a parsable integer.
 * @javaLike
 */
METHOD_C double parseDouble_DoubleJc(StringJc src);




METHOD_C StringJc toString_F_FloatJc(float val);

METHOD_C StringJc toHexString_FloatJc(float val);


#ifndef DEF_ObjectJc_SIMPLE
/*@CLASS_C ComparableJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct ComparableJc_t
{ struct { ObjectJc object;} base;
}ComparableJc;


/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Vtbl_ComparableJc_t
{ Vtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
} Vtbl_ComparableJc;

extern char const sign_Vtbl_ComparableJc[]; 

extern_C const struct ClassJc_t refl_ComparableJc; 


/*@CLASS_C CloseableJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct CloseableJc_t
{ struct { ObjectJc object;} base;
}CloseableJc;

typedef bool MT_close_CloseableJc(ObjectJc* thiz, ThCxt* _thCxt);


/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Vtbl_CloseableJc_t
{ VtblHeadJc head;
  MT_close_CloseableJc* close;
  Vtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
} Vtbl_CloseableJc;

extern char const sign_Vtbl_CloseableJc[]; 

#define close_CloseableJc(THIZ, THCXT) ((Vtbl_CloseableJc*)getVtbl_ObjectJc((ObjectJc*)(THIZ), sign_Vtbl_CloseableJc))->close(THIZ, THCXT)

extern_C const struct ClassJc_t refl_CloseableJc; 


/*@CLASS_C FlushableJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct FlushableJc_t
{ struct { ObjectJc object;} base;
} FlushableJc;

typedef void MT_flush_FlushableJc(ObjectJc* thiz, ThCxt* _thCxt);


/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Vtbl_FlushableJc_t
{ VtblHeadJc head;
  MT_flush_FlushableJc* flush;
  Vtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc
} Vtbl_FlushableJc;

extern char const sign_Vtbl_FlushableJc[]; 

#define flush_FlushableJc(THIZ, THCXT) ((Vtbl_FlushableJc*)getVtbl_ObjectJc((ObjectJc*)(THIZ), sign_Vtbl_FlushableJc))->flush(THIZ, THCXT)


extern_C const struct ClassJc_t refl_FlushableJc; 

/*@CLASS_C AppendableJc_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Interface Appendable.
 * NOTE: It is defined in the Headerfile ObjectJc.h because it is based on ObjectJc and its reflection are defined in ReflectionBaseTypesJc.c
 * which includes only ObjectJc. It is respected as base type.
 */
typedef struct AppendableJc_t
{ struct { ObjectJc object;} base;
}AppendableJc_s;


typedef AppendableJc_s* MT_append_C_AppendableJc(ObjectJc* thiz, char c, ThCxt* _thCxt);

typedef AppendableJc_s* MT_append_cs_AppendableJc(ObjectJc* thiz, CharSeqJc cs, ThCxt* _thCxt);

typedef AppendableJc_s* MT_append_csI_AppendableJc(ObjectJc* thiz, CharSeqJc cs, int from, int to, ThCxt* _thCxt);



/**To organize dynamic link method call the jump table of virtual methods is neccessary. */
typedef struct Vtbl_AppendableJc_t
{ VtblHeadJc head;
  MT_append_C_AppendableJc* append_C;
  MT_append_cs_AppendableJc* append_cs;
  MT_append_csI_AppendableJc* append_csI;
  Vtbl_ObjectJc mtblObjectJc;  //same method types as ObjectJc


} Vtbl_AppendableJc;

extern char const sign_Vtbl_AppendableJc[]; 

extern_C const struct ClassJc_t refl_AppendableJc; 

#define append_C_AppendableJc(THIZ, SRC, THCXT) ((Vtbl_AppendableJc*)getVtbl_ObjectJc((ObjectJc*)(THIZ), sign_Vtbl_AppendableJc))->append_C((ObjectJc*)(THIZ), SRC, THCXT)
#define append_cs_AppendableJc(THIZ, SRC, THCXT) ((Vtbl_AppendableJc*)getVtbl_ObjectJc((ObjectJc*)(THIZ), sign_Vtbl_AppendableJc))->append_cs((ObjectJc*)(THIZ), SRC, THCXT)
#define append_csI_AppendableJc(THIZ, SRC, FROM, TO, THCXT) ((Vtbl_AppendableJc*)getVtbl_ObjectJc((ObjectJc*)(THIZ), sign_Vtbl_AppendableJc))->append_csI((ObjectJc*)(THIZ), SRC, FROM, TO, THCXT)

#endif //DEF_ObjectJc_SIMPLE
/*@DEFINE_C Inlines @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Inlines: inline definitions which uses definitions above. On end of header.*/



#ifndef DEF_ObjectJc_SIMPLE

VtblHeadJc const* checkVtblError_ObjectJc(ObjectJc const* ythis, int error, ThCxt* _thCxt);

INLINE_emC VtblHeadJc const* checkVtbl_ObjectJc(ObjectJc const* ythis, int ix, char const* sign, ThCxt* _thCxt)
{ ClassJc const* reflection = ythis->reflection;
  if( reflection != null || reflection->object.reflection == &refl_ClassJc) {
    VtblHeadJc const* head0, *head;
    head0 = ythis->reflection->mtbl;  
    if(head0 != null){
      head = (VtblHeadJc const*)(((MemUnit const*) (head0)) + ix * sizeof(head0->sign)); 
      if(head->sign == sign) {
        return head;
      } else return checkVtblError_ObjectJc(ythis, 3, _thCxt);
    } else return checkVtblError_ObjectJc(ythis, 2, _thCxt);
  } else return checkVtblError_ObjectJc(ythis, 1, _thCxt);
}


#endif  //DEF_ObjectJc_SIMPLE


/**It should able to work with Stacktrace. */


//#include "emC/LogMessage.h"
//#include "emC/Formatter.h"

#endif //HEADERGUARD_ObjectJc_h
