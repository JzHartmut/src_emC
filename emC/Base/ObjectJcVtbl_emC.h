#ifndef HGUARD_ObjectJcVtbl_emC
#define HGUARD_ObjectJcVtbl_emC


/*@CLASS_C VtblHeadJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/**This is a only forward declared struct used in [[VtblHeadJc]] for the size value stored as pointer. */
struct Size_Vtbl_t;
#define Size_Vtbl_t Size_Vtbl_t

#define DEF_ClassJc_Vtbl


#define NrofMethodsForSize_VTBL_Jc(NR) (struct Size_Vtbl_t*)((2 +NR) * sizeof(void*)) 

/** The definition of ordered method pointer, it is a jump table.
* The virtual methods are callable in a C-environment adequate to virtual methods in C++.
* This struct of method pointer determines the order of virtual methods of ObjectJc for all implementation classes.
*/
typedef struct VtblHeadJc_T
{ /**The value of sign must be identically with the address of the sign_Vtbl_TYPE. Check it for safe access. */
  char const* sign;
  /**The sizeTable is really an simple int. But all members of Method table are from pointer type. casted internally. 
  * Check of sizeTable makes possible to use older implementation versions with less methods.
  * NOTE: don't use a void*, because all is compatible with it and no errors are signated.
  */
  struct Size_Vtbl_t* sizeTable;  
}VtblHeadJc;

#define VtblHeadJc VtblHeadJc

/**Structure which represents the common Vtbl-ref-type. 
* It holds the pointer to the correct Vtbl (represented with the Head)
* and the reference to the data based on Objectjc.
* The vtbl->sign should be tested to correctness, and then the vtbl pointer should be casted.
*/
typedef struct VtblObjectJcRef_t
{ VtblHeadJc* vtbl;
  ObjectJc* ref;
} VtblObjectJcRef;

#define ObjectJcMTB VtblObjectJcRef


extern char const sign_Vtbl_ObjectJc[]; 
extern char const signEnd_Vtbl_ObjectJc[];

/**returns the method table of the given instance for the given maybe super class or interface. 
* This routine presumed that the given Object has a correct method table.
* This method is used basicly.
* If the instance is not type of the required class, null is returned.
*
* If the pointer to the method table is worse, either an exception is thrown 
* because the search process detects any memory content as size of method table, which is worse,
* or an memory protection exception is caused.   
*
* This is useable in safety critical software: If any error in data occurs, 
* the programm is aborted, the throw may be catched or not, but the software works deterministic.
*
* @param sign The address of the sign to the required method table for the maybe interface or super class.
*    Use  ,,sign_Vtbl_TYPE,,   in the user's software to determine the type. 
*    The sign... is defined with the Method table and reflection for any class.
* @return null or the reference of the method table of the required base class.
* The Method table may be a derived table depending on sign parameter..
* Whether the method table is derived or not, it means wether a up-casting is allowed,
* depends on a derived class. 
*/
extern_C VtblHeadJc const* getVtbl_ObjectJc(ObjectJc const* ythis, char const* sign);
#define getVtbl_ObjectJc getVtbl_ObjectJc


int getPosInVtbl_ObjectJc(ObjectJc const* thiz, char const* sign);
#define getPosInVtbl_ObjectJc getPosInVtbl_ObjectJc


METHOD_C VtblHeadJc const* checkVtbl_ObjectJcTT(ObjectJc const* ythis, int ix, char const* sign, struct ThreadContext_emC_t* _thCxt);




#define SETMTBJc(DST, REF, TYPE) { (DST).ref = (struct TYPE##_t*)(REF); (DST).mtbl = (DST).ref == null ? null : (Vtbl_##TYPE const*)getVtbl_ObjectJc(&(DST).ref->base.object, sign_Vtbl_##TYPE); }
#define SETMTBJc_XXX(DST, REF, TYPE) { (DST).ref = (TYPE*)(REF); (DST).mtbl = (DST).ref == null ? null : (Vtbl_##TYPE const*)getVtbl_ObjectJc(&(DST).ref->base.object, sign_Vtbl_##TYPE); }

/**Macro to get the method table from a given reference. 
* @Deprecated. Don't use the macro. It is better to write the two routines one after another. Keep clearly.
* @param REF A reference to any type which is based on Object. It should hava a ,,union{ ... ObjectJc object; } base;,,
* @param TYPE The Typ of the method table. It is used to build ,,Vtbl_TYPE const*,, and ,,sign_Vtbl_TYPE,,
* @return casted returnvalue of ,,getMtableObjectJc(othis, sign),,. 
*         returns null if the instance doesn't have a method table. An NullPointerException outside may be thrown.
*         This behaviour is able to use whether base methods of ObjectJc are available on any instance.
* @throws ClassCastException If the object isn't based on the required type.
*/
#define MTBCALLJc(REF, TYPE) ((Vtbl_##TYPE const*)getVtbl_ObjectJc(&(REF)->base.object, sign_Vtbl_##TYPE))


/****************************************************************************************************
* Virtual methods of ObjectJc:
* The virtual methods are defined as Methodtypes.
*/

/** Produces a new instance equal to the old one. The method is virtual,
* because it may be able that some register operations or others should be done
* by the users class. This operation is the object-oriented replacement
* for the old C-style memcpy of instances data.
*/
METHOD_C typedef ObjectJc* MT_clone_ObjectJc(ObjectJc const* ythis, MemC buffer);

/**Tests wether or not both objects are equal. The statement of homogeneousness
* may be depended on some informations inside the instances, other informations
* may be differenced, though both objects are equal. Thats why the method is virtual.
* This operation is the object-oriented replacement
* for the old C-style memcpy of instances data.
*/
METHOD_C typedef bool MT_equals_ObjectJc(ObjectJc const* ythis, ObjectJc const* second, struct ThreadContext_emC_t* _thCxt);

/**This method should be called before the instance is deleted finally. It is called
* by garbage collection. Some action such as deregister or free memory may be taken
* from the users overload class.
*/
METHOD_C typedef void MT_finalize_ObjectJc(ObjectJc const* ythis, struct ThreadContext_emC_t* _thCxt);

/**This method supplies a hash code for thid onstance.
*/
METHOD_C typedef int32 MT_hashCode_ObjectJc(ObjectJc const* ythis, struct ThreadContext_emC_t* _thCxt);

/**This method supplies a string representation of the content of the instance,
* useable especially for debug or analyze information.
*/
METHOD_C typedef StringJc MT_toString_ObjectJc(ObjectJc const* ythis, struct ThreadContext_emC_t* _thCxt);




/**The definition of ordered pointer to overideable operations, it is a jump table.
* The virtual operations are callable in a C-environment adequate to virtual methods in C++.
* This struct of method pointer determines the order of virtual methods of ObjectJc for all implementation classes.
* @refl: no.
*/
typedef struct Vtbl_ObjectJc_t
{ VtblHeadJc head;
/**Methods of ObjectJc. */
MT_clone_ObjectJc*    clone;
MT_equals_ObjectJc*   equals;
MT_finalize_ObjectJc* finalize;
MT_hashCode_ObjectJc* hashCode;
MT_toString_ObjectJc* toString;
} Vtbl_ObjectJc;


/**Structure of the Vtbl of an Instance derived from Objectjc without any overridden operations. 
* This structure is defined in Object_emC.c, see extern declaration.
* @refl: no.
*/
typedef struct VtblDef_ObjectJc_t {
  Vtbl_ObjectJc tbl; VtblHeadJc end;
} VtblDef_ObjectJc;

extern_C VtblDef_ObjectJc const vtbl_ObjectJc;

/**The override-able method toString tests the virtual table inside reflection
* to call the correct toString-Method of the implementation class. */
StringJc toString_ObjectJc(ObjectJc const* ithis, struct ThreadContext_emC_t* _thCxt);


/** The implemented method for ObjectJc forward declared here.
*  They should be known if a user class will not overload some methods from ObjectJc with its own methods
*  but use this methods.
*  In generally, implementation methods needn't be forward declared, they need only be defined in the C file.
*/
extern_C MT_clone_ObjectJc clone_ObjectJc_F;
extern_C MT_equals_ObjectJc equals_ObjectJc_F;
extern_C MT_finalize_ObjectJc finalize_ObjectJc_F;
extern_C MT_hashCode_ObjectJc hashCode_ObjectJc_F;
extern_C MT_toString_ObjectJc toString_ObjectJc_F;


/** The virtual table of non overloaded methods from object,
useable as part of a users virtual table.
*/
#define CONST_VtblStd_ObjectJc \
{ clone_ObjectJc_F    \
, equals_ObjectJc_F   \
, finalize_ObjectJc_F \
, hashCode_ObjectJc_F \
, toString_ObjectJc_F \
}




#endif //HGUARD_ObjectJcVtbl_emC
