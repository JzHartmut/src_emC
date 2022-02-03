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
 *
 * @content Implementation of Reflection
 *
 * @author Jchartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2012-04-07 Hartmut new: nrofBytesScalarTypes_ClassJc[], refl__char16Jc
 * 2010-07-10: Hartmut: Array access to second CPU
 * 2010-02-01: prevent exception on getDeclaredField_ClassJc, instead return null, regarding in searchObject_ClassJc. Reason: better to handle, problems with setjmp on some embedded processors.
 * 2009-12-00: Hartmut improved.
 * 2008-04-22: JcHartmut adap: ReflectionJc.h
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#include <applstdef_emC.h>
#include "emC/Jc/ReflectionJc.h"
#include "emC/Jc/ReflMemAccessJc.h"
#include <emC/Base/Handle_ptr64_emC.h>
//#include "Jc/StringJc.h"
#include "emC/Jc/ObjectJc.h"      //It is a concept of CRuntimeJavalike

#ifdef DEF_REFLECTION_FULL
#include <emC/Base/SimpleC_emC.h>
#include <stdio.h>
#include <stdarg.h>


#undef mStaticArray_Modifier_reflectJc //it shouldn't be used!
#undef mReference_Modifier_reflectJc

//#include "fw_ThreadContext.h"
/********************************************************************************************/
// Field


extern const ClassJc* simpleTypes_ClassJc[];

struct SearchTrc_t
{ MemSegmJc objWhereFieldIsFound; 
  ClassJc const* clazzWhereFieldIsFound;
  FieldJc const* field; 
  ClassJc const* typeOfField; 
  MemSegmJc objOfField;
} searchTrc_ClassJc[16] = {0}; //only debug
  
int idxSearchTrc = 0;



#ifdef DEF_HandlePtr64
  #include <emC/Base/handle_ptr64_emC.h>      
  const char* init_ReflectionJc() {
    const char* error = null;
    //error = init_Handle2Ptr(1000);  //see DEFINED_nrEntries_Handle2Ptr
    return error;
  }
#else
  const char* init_ReflectionJc() { return null; }
#endif

/*
FieldJc const* get_FieldJc_Y(const FieldJc_Y* thiz, int idx)
{ return (FieldJc const*)(get_i_ObjectArrayJc(&thiz->array, idx));
}
*/




/**A maximum of 5 external CPUs are supported. */
ClassJc_YP const* extReflectionClasses_ReflectionJc[5];   




static int stop()
{ return 0;  //debug breakpoint here able to set.
}


ClassJc* ctorM_ClassJc(MemC rawMem)
{ ClassJc* thiz = PTR_MemC(rawMem, ClassJc);
  STACKTRC_ENTRY("ctor_ClassJc");
  if(size_MemC(rawMem)<sizeof(ClassJc)) THROW1_s0(IllegalArgumentException, "ctor mem-size insufficient", size_MemC(rawMem));
  ctorc_ClassJc(thiz);
  return thiz;
}



void ctorc_ClassJc(ClassJc* thiz)
{ memset(thiz, 0, sizeof(ClassJc));
  ctorc_ObjectJc(&thiz->object);
  setReflection_ObjectJc(&thiz->object, null, OBJTYPE_ClassJc + sizeof(ClassJc));
}



FieldJc* ctorM_FieldJc(MemC rawMem)
{ FieldJc* thiz = PTR_MemC(rawMem, FieldJc);
  STACKTRC_ENTRY("ctor_FieldJc");
  if(size_MemC(rawMem)<sizeof(FieldJc)) THROW1_s0(IllegalArgumentException, "ctor mem-size insufficient", size_MemC(rawMem));
  ctorc_FieldJc(thiz);
  return thiz;
}


void ctorc_FieldJc(FieldJc* thiz)
{
  memset(thiz, 0, sizeof(FieldJc));
  //NOTE: FieldJc hasnot a base ObjectJc.
}


FieldJc_Y* new_FieldJc_Y(int size)
{ 
  FieldJc_Y* thiz = (FieldJc_Y*)new_ObjectArrayJc(size, sizeof(FieldJc), null, OBJTYPE_FieldJc);
  /*
  int nrofBytes = sizeof(ObjectArrayJc) + size * sizeof(FieldJc);
  MemC rawMem = alloc_MemC(nrofBytes);
  FieldJc_Y* thiz = (FieldJc_Y*)ctor_ObjectArrayJc(rawMem);
  setReflection_ObjectJc(&thiz->head.object, null, OBJTYPE_FieldJc + nrofBytes);
  */
  int idx;
  for(idx = 0; idx < size; idx++)
  { ctorc_FieldJc(&thiz->data[idx]);
  }
  return thiz;
}

//Note: use name_ClassJc
const char* getName_ClassJc(ClassJc const* thiz)
{ if( ((uint64)(thiz)) < kREFLECTION_LastConstant )
  { thiz = simpleTypes_ClassJc[(int)(intptr_t)(thiz)];
    //Note, TODO thiz should not be a simpleType-const
  }
  return thiz->name;
}




METHOD_C bool isPrimitive_ClassJc(ClassJc const* thiz)
{ bool bRet;
  int32 modifiers = getModifiers_ClassJc(thiz);
  bRet = ((modifiers & mPrimitiv_Modifier_reflectJc)!=0);
  return bRet;
}


METHOD_C int32 getModifiers_ClassJc(ClassJc const* thiz)
{
  if( ((intptr_t)(thiz)) < kREFLECTION_LastConstant )
  { thiz = simpleTypes_ClassJc[(int)(intptr_t)(thiz)];
    //Note, TODO thiz should not be a simpleType-const
  }
  return thiz->modifiers;
}



METHOD_C ClassJc const* getEnclosingClass_ClassJc(ClassJc const* thiz)
{
  return null;  //TODO not used yet.
}



/**NOTE: regards that thiz may be a identifier for simple types.
 */
FieldJc_Y const* getDeclaredFields_ClassJc(const ClassJc* thiz)
{ FieldJc_Y const* fields;
  if( ((intptr_t)(thiz)) < kREFLECTION_LastConstant ) //2015-06 regard 64-bit-addresses and >0x7fffffff
  { thiz = simpleTypes_ClassJc[(int)(intptr_t)(thiz)];
    //Note, TODO thiz should not be a simpleType-const
  }
  //thiz is the real class:
  fields = thiz->attributes;
  return fields; 
}






MethodJc const* getDeclaredMethod_ClassJc(ClassJc const* thiz, char const* sName)
{ int ii;
  bool bFound = false;
  MethodJc const* method = null;
  STACKTRC_ENTRY("getDeclaredMethod_ClassJc");
  if(thiz->methods == null){ STACKTRC_LEAVE; return(null); }
  for(ii=0; !bFound && ii< thiz->methods->head.length; ii++)
  { StringJc sNameMethod;
    method = get_MethodJcARRAY(thiz->methods,ii);
    sNameMethod = getName_Method(method);
    if(equals_s0_StringJc(sNameMethod, sName))
    { //:TODO: test the param
      bFound= true;
    }
  }
  STACKTRC_LEAVE;
  if(bFound) return method;
  else return null;  //original Java: NoSuchMethodException

}




METHOD_C ClassJc const* getSuperClass_ClassJc(ClassJc const* thiz)
{
  FieldJc const* superField = getSuperField_ClassJc(thiz);
  return superField == null ? null : getType_FieldJc(superField);
}



METHOD_C FieldJc const* getSuperField_ClassJc(ClassJc const* thiz)
{
  if(thiz->superClass_es.obj == null) return null;
  else if(isArray_ObjectJc(thiz->superClass_es.obj)) {
    ASSERT_emC(  (thiz->superClass_es.obj->reflection !=null && checkStrict_ObjectJc(thiz->superClass_es.obj, 0, &refl_ClassOffset_idxVtblJc, 0))
              || getIdentInfo_ObjectJc(thiz->superClass_es.obj) == ID_refl_ClassOffset_idxVtblJc, "superClas_es should be an Array of FieldJc", 0,0);
    ClassOffset_idxVtblJc const* fieldIdx = &thiz->superClass_es.clazzArray->data[0];
    //FieldJc_Y const* superFields = C_CAST(FieldJc_Y const*, thiz->superClass_es);
    return &fieldIdx->superfield; //Note: C++ knows more superclasses, this is for Java-like and C
  } else {
    //faulty: it is the class only for type test.
    ASSERT_emC(  (thiz->superClass_es.obj->reflection !=null && checkStrict_ObjectJc(thiz->superClass_es.obj, 0, &refl_FieldJc, 0))
              || getIdentInfo_ObjectJc(thiz->superClass_es.obj) == ID_refl_FieldJc, "superClas_es should be a FieldJc", 0,0);
    FieldJc const* superField = C_CAST(FieldJc const*, thiz->superClass_es.obj);
    return superField;

  }
}




MethodJcARRAY const* ptrConstCasting_MethodJcARRAY(ObjectArrayJc const* ptr)
{ return (MethodJcARRAY const*)(ptr);
}



MethodJc const* get_MethodJcARRAY(const MethodJcARRAY* thiz, int idx)
{ return (MethodJc const*)(get_i_ObjectArrayJc(&thiz->head, idx));
}



StringJc getName_Method(const MethodJc* thiz)
{ return s0_StringJc(thiz->name);
}






int32 invoke_MethodJcSi(const MethodJc* thiz, MemSegmJc objP, int32ARRAY* params)
{ ObjectJc* obj = null; //TODO (ObjectJc*)(objP);
  switch(thiz->eType)
  { case kInt_void:
    { //int ret = (obj->*thiz->adress)();
    }break;
    #if 0
    case kInt_Int:
    { int p1 = ((Integer*)(args[0].obj()))->intValue();
      int ret = (obj->*(Object_Method1Int)(adress))(p1);
    } break;
    #endif
  }
  return 0;

}






//gets the address of the field inside the instance, regards indices, don't derefer.
//
METHOD_C MemSegmJc getMemoryAddress_FieldJc(const FieldJc* thiz, MemSegmJc instance, bool bFieldAddr, char const* sVaargs, va_list vaargs)
{ /* it is assumed, that the obj matches to the Field thiz, it means, the Field thiz
     is getted from a object of exactly this type or from the obj itself.
     This is tested by original Java - set- or get- operations.
     But it is not tested here to optimize calculation time. If it is a part of a
     Java2C-translation, the test should be done on Java-level, if it is a directly
     programmed in C or C++ part, the user should be programmed carefully, how it is
     ordinary in C or C++.
  */
  MemSegmJc address = instance;  //copy because the segment is the same.
  int ixData;
  STACKTRC_ENTRY("getMemoryAddress_FieldJc");
  //:TODO: test obj
  if(sVaargs != null && *sVaargs == 'I'){  //only 1 index yet, todo later.
    ixData = va_arg(vaargs, int32);
  } else {
    ixData = -1;  //not given.
  }
  //
  if(thiz->bitModifiers & mSTATIC_Modifier_reflectJc)
  {  setNull_MemSegmJc(address);
  }
  else
  { int position = thiz->offsFieldInStruct;  //2CPU
    int sizeElement = 1;
    void* memAddr;
    if((position & mOffsIsProxyIx4Target_FieldJc) !=0){
      //Note: It is a decision of reflection generation whether the size and offset is gotten from the target (more universal)
      //or the size and offset is stored in the reflection table. 
      //In the second case the reflection generation should know which memory layout, alignment and type size the target has.
      //The more universal approach is this branch, whereby the size and offset is gotten from target. 
      ASSERT_emC(segment_MemSegmJc(instance) !=0, "segment should be given", 0,0); //only if a remote target is accessed, elsewhere the reflection tables are faulty.
      ClassJc const* declaringClazz = getDeclaringClass_FieldJc(thiz);
      int32 sizeEntry = declaringClazz->nSize;
      int32 idxClass = sizeEntry - 0xFFFFF000;
      //int idxField = thiz->nrofArrayElements & 0x0fff;
      int idxField = position & 0x7FFF;
      int32 len_pos_element;
      /**Significance check to prevent failed access: */
      if(idxClass < 0 || idxClass > 1000 || idxField < 0 || idxField > 0xfff) {
        ASSERT_emC(false, "idxClass or idxField faulty", idxClass, idxField);  //may cause exception
        idxClass  = 1; idxField = 0; //without assert check  corr it.
      }
      int nrofElements = getStaticArraySize_FieldJc(thiz);
      if(nrofElements ==0){ 
        nrofElements = 1; 
        ASSERT_emC(ixData <=0, "no index access should be done if the element in struct is not an array", ixData, 0);  //.
      }
      len_pos_element = getInfoDebug_InspcTargetProxy(getOffsetLength_InspcTargetProxy, segment_MemSegmJc(instance), 0, idxClass<<16 |idxField);
      position = len_pos_element & 0x0000ffff; //position-part in bit15..0
      sizeElement = ((len_pos_element & 0x7FFF0000) >>16) / nrofElements; //Note: The target returns the size of the element in struct, not the size of type (element size in array).
    } else {
      if(ixData >=0){
				ClassJc const* type = getType_FieldJc(thiz);  //NOTE: don't use thiz->type directly, because it may be a number only.
        switch(thiz->bitModifiers & mAddressing_Modifier_reflectJc){
        case kEmbedded_Modifier_reflectJc: sizeElement = type->nSize; break;
        case kReference_Modifier_reflectJc: { //a reference  //TODO k....
          if( (thiz->bitModifiers & mPrimitiv_Modifier_reflectJc) == kHandlePtr_Modifier_reflectJc) {
            sizeElement = sizeof(uint32);  //a handle
          } else {
            sizeElement = sizeof(void*);
          }  
        } break;
        case kEnhancedReference_Modifier_reflectJc: sizeElement = sizeof(MemSegmJc); break;
        default: sizeElement = type->nSize; //TODO check ASSERT(false), check primitive, should be embedded
        }//switch
        //an index must not be given on a non-embedded container. Check it to prevent software errors.
        //ASSERT(isStaticEmbeddedArray_ModifierJc(thiz->bitModifiers)); 
      }
    }
    if(bFieldAddr){
      position = 0; //because it is the address of the field element already.
    }
    if(ixData >0){
      memAddr = ADDR_MemSegmJc(instance, MemUnit) + position + ixData * sizeElement;
    } else {
      memAddr = ADDR_MemSegmJc(instance, MemUnit) + position;
    }
    setADDR_MemSegmJc(address,  memAddr );
  }
  STACKTRC_LEAVE; return(address);
}




METHOD_C MemSegmJc getContainerAddress_FieldJc(const FieldJc* thiz, MemSegmJc instance, char const* sVaargs, va_list vaargs)
{ MemSegmJc address;  //reference to the really data, the field my contain a reference.
  STACKTRC_ENTRY("getContainerAddress_FieldJc");
  
  if(ADDR_MemSegmJc(instance, void)!=null) { 
    int32 modeContainerRef = thiz->bitModifiers & mContainerinstance_Modifier_reflectJc;
    
    /**Get address of the reference to the data which are described by thiz and instance, the address may be at a remote memory location: */
    MemSegmJc fieldPosAddr = getMemoryAddress_FieldJc(thiz, instance, false, sVaargs, vaargs);  
  
    /**The container contains the reference. The container may be referenced too. 
     * A simplest container is a simple reference, than the container is embedded.
     * A more complex container may be an ObjectArrayJc, or some UML-Containers. It may be embedded or not.
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
     */
    switch(modeContainerRef)
    { case kEmbeddedContainer_Modifier_reflectJc: address = fieldPosAddr; break; //the field ref is the address of the referenced data is the .
      case kReferencedContainer_Modifier_reflectJc: address = getRef_MemAccessJc(fieldPosAddr); break; //implicitely.
      case kEnhancedRefContainer_Modifier_reflectJc: address = getEnhancedRef_MemAccessJc(fieldPosAddr); break;
      default: address = fieldPosAddr; //noting, a normal reference or scalar
    }
  }
  else {
    address = null_MemSegmJc;
  }
  STACKTRC_LEAVE; return(address);
}



static MemSegmJc getRefAddrObjectArray_FieldJc(MemSegmJc addrArray, char const* sVaargs, va_list vaargs, ThCxt* _thCxt)
{ MemSegmJc retAddress = { 0 };
  int ixData;
  STACKTRC_TENTRY("getRefAddrObjectArray_FieldJc");
  //:TODO: test obj
  if(sVaargs != null && *sVaargs == 'I'){  //only 1 index yet, todo later.
    ixData = va_arg(vaargs, int32);
  } else {
    ixData = -1;  //not given.
  }
  if(segment_MemSegmJc(addrArray)!=0){
    stop(); //2CPU
  } else {
    //own memory:
    ObjectArrayJc* array = ADDR_MemSegmJc(addrArray, ObjectArrayJc);  //it is known that it is an ObjectArrayJc
    void* retAddress1 = get_i_ObjectArrayJc(array, ixData);
    if(retAddress1 == null){ THROW1_s0(IndexOutOfBoundsException, "index to large", ixData);}
    setADDR_MemSegmJc(retAddress, retAddress1);
  }
  STACKTRC_LEAVE; return retAddress;
  
}




MemSegmJc getAddressElement_FieldJc(const FieldJc* ythis, MemSegmJc instance, char const* sVaargs, ...) {
  va_list vaargs;
  va_start(vaargs, sVaargs);
  return getAddrElement_V_FieldJc(ythis, instance, sVaargs, vaargs);
}


/**Gets the address of the element described with the field in the data of the given object. 
 * If the field describes a reference, it returns the address of the reference. It does not derefer.
 * It regards whether the field is of container type, it regards the index.
 * @param address The address of the reference, it may be the address of a container element.
 * @param idx The index. 
 *          If the index < 0, the address of the whole container is returned.
 *          If the index exceeds the boundaries of the container, null is returned.
 * @returns the address of the reference maybe in a container or the address of the reference immediately, if it isn't a container. 
 *          If the contained instances in the container are embedded in the container, this address is equal with the address of the instance.
 *          If the instances in the container are references, this is the address where the reference to the instance is found.
 *          The type of the reference should be regarded. Check ,,(getModifiers_FieldJc(field) & mAddressing_Modifier_reflectJc)
 *          to detect which to do whith the address.   
 * @throws IndexOutOfBoundsException if the idx is fault.
 * @since 2009-11-26, it is necessary to set references with the ''inspector''-Tool.
 */
MemSegmJc getAddrElement_V_FieldJc(const FieldJc* thiz, MemSegmJc instance, char const* sVaargs, va_list vaargs)
{ /* it is assumed, that the obj matches to the Field thiz, it means, the Field thiz
     is getted from a object of exactly this type or from the obj itself.
     This is tested by original Java - set- or get- operations.
     But it is not tested here to optimize calculation time. If it is a part of a
     Java2C-translation, the test should be done on Java-level, if it is a directly
     programmed in C or C++ part, the user should be programmed carefully, how it is
     ordinary in C or C++.
  */
  MemSegmJc retAddr;
  STACKTRC_ENTRY("getRefAddr_FieldJc");

  { int32 bitModifiers = thiz->bitModifiers;
    int32 bitContainerType = bitModifiers & m_Containertype_Modifier_reflectJc;
    int32 modeAddr = thiz->bitModifiers & mAddressing_Modifier_reflectJc;
    MemSegmJc fieldPosOrContainerAddr;
    if((thiz->bitModifiers & mPrimitiv_Modifier_reflectJc) == kHandlePtr_Modifier_reflectJc){
      stop();
    }
    if(modeAddr == 0 && (thiz->bitModifiers & mPrimitiv_Modifier_reflectJc) == 0)
    { //falsch modeAddr = kReference_Modifier_reflectJc; 
      /**no primitive, but also not embedded, its a reference maybe of ObjectJc-based type.
       * this is for compatibility for older reflection generation. 
       * The mReference_Modifier_reflectJc-bit is set there only if it is a simple reference not Object-based.
       * But it is difference between embedded ObjectJc-based and referenced ObjectJc-based. 
       * Therefore the kReference_Modifier_reflectJc is obligate now if it is referenced.
       */
    }
    //if(idx < 0 || isStaticEmbeddedArray_ModifierJc(bitModifiers)){
    if(sVaargs == null || *sVaargs == 0 || isStaticEmbeddedArray_ModifierJc(bitModifiers)){
       //It is a simple field or simple array. Access direct, regarding such simple things at second CPU.
       retAddr = fieldPosOrContainerAddr = getMemoryAddress_FieldJc(thiz, instance, false, sVaargs, vaargs);
    } else {
      retAddr =instance;  //copy the segment information
      //It is a complex container. TODO: Test with second CPU, it isn't need yet.
      //gets the memory location of the container, without regarding the index. 
      //The index is used inside the container.
      fieldPosOrContainerAddr = getContainerAddress_FieldJc(thiz, instance, null, null); //memory location of the field inside obj
      if(ADDR_MemSegmJc(fieldPosOrContainerAddr, void) != null)
      {
        //if(bitContainerType != 0 && idx >=0)
        if(bitContainerType != 0 && sVaargs != null && *sVaargs == 'I')
        { /**Correct the fieldPosOrContainerAddr with idx: it should be the address of the indexed element. */
          CALLINE;
          switch(bitContainerType)
          { case kListJc_Modifier_reflectJc:
            case kMapJc_Modifier_reflectJc: setADDR_MemSegmJc(retAddr, null); break;  //TODO
            case kStaticArray_Modifier_reflectJc:{
              //void* addrFieldPosOrContainer = ADDR_MemSegmJc(fieldPosOrContainerAddr, void);
              //void* addr = getRefAddrStaticArray_FieldJc(thiz, addrFieldPosOrContainer, sVaargs, vaargs, _thCxt);
              MemSegmJc addr = getMemoryAddress_FieldJc(thiz, fieldPosOrContainerAddr, true, sVaargs, vaargs);
              setADDR_MemSegmJc(retAddr, ADDR_MemSegmJc(addr, void)); 
            } break;
            case kObjectArrayJc_Modifier_reflectJc:  
              retAddr = getRefAddrObjectArray_FieldJc(fieldPosOrContainerAddr, sVaargs, vaargs, _thCxt); 
              break;
            case kUML_LinkedList_Modifier_reflectJc: 
              retAddr = getRefAddrUML_LinkedList_FieldJc(fieldPosOrContainerAddr, sVaargs, vaargs, _thCxt); 
              break;
            case kUML_ArrayList_Modifier_reflectJc: 
              retAddr = getRefAddrUML_ArrayList_FieldJc(fieldPosOrContainerAddr, sVaargs, vaargs, _thCxt); 
              break;
            case kUML_Map_Modifier_reflectJc:  
              retAddr = getRefAddrUML_Map_FieldJc(fieldPosOrContainerAddr, sVaargs, vaargs, _thCxt); 
              break;
            default: THROW1_s0(IllegalArgumentException, "undefined container type", bitContainerType);
          }
        }
        else
        { /**if it isn't a container, the fieldPosAddr is correct.
           * if the idx<0, the idx is not given, the base address of container is requested.
           */
          retAddr = fieldPosOrContainerAddr;
        }
      }
      else {
        setADDR_MemSegmJc(retAddr, null); 
      }
    }

  }
  STACKTRC_LEAVE; return retAddr;
}








/**Gets the actual length of the array if the field describes a reference of an array or collection,
 * @param obj The Object matching to the Field
 * @return the actual length, it may be 0.
 * @throws NoSuchFieldException if it describes not an array or collection.
 */
int getArraylength_FieldJc(FieldJc const* thiz, MemSegmJc instance)
{ /* it is assumed, that the obj matches to the Field thiz, it means, the Field thiz
     is getted from a object of exactly this type or from the obj itself.
     This is tested by original Java - set- or get- operations.
     But it is not tested here to optimize calculation time. If it is a part of a
     Java2C-translation, the test should be done on Java-level, if it is a directly
     programmed in C or C++ part, the user should be programmed carefully, how it is
     ordinary in C or C++.
  */
  int length;
  int32 bitModifiers;
  int32 bitContainerType;
  MemSegmJc adr;
  STACKTRC_ENTRY("getArraylength_FieldJc");

  bitModifiers = getModifiers_FieldJc(thiz);
  bitContainerType = bitModifiers & m_Containertype_Modifier_reflectJc;
  //gets the address of the container without index
  adr = getContainerAddress_FieldJc(thiz, instance, null, null); //memory location of the field inside obj
  if(ADDR_MemSegmJc(adr,void) != null)
  { if(bitContainerType == kUML_LinkedList_Modifier_reflectJc)
    { length = getArraylengthUML_LinkedList_FieldJc(adr);
    }
    else if(bitContainerType == kUML_ArrayList_Modifier_reflectJc)
    { length = getArraylengthUML_ArrayList_FieldJc(adr);
    }
    else if(bitContainerType == kUML_Map_Modifier_reflectJc)
    { length = getArraylengthUML_Map_FieldJc(adr);
    }
    else if(bitContainerType == kObjectArrayJc_Modifier_reflectJc)
    { ObjectArrayJc* array = ADDR_MemSegmJc(adr,ObjectArrayJc);  //it is known that it is an ObjectArrayJc
      length = array->length;
    }
    else if(bitContainerType == kStaticArray_Modifier_reflectJc)
    { //memory location of the field inside obj
      MemSegmJc adr = getMemoryAddress_FieldJc(thiz,instance, false, null, null); 
      length = getStaticArraySize_FieldJc(thiz);
      if(  (bitModifiers & mAddressing_Modifier_reflectJc) == kReference_Modifier_reflectJc) {
        /**Only if it is an reference, check the reference values from back. Show only non-null references. */
        length = getRealLengthStaticArray_MemAccessJc(adr, length);
      }
      else if(  (bitModifiers & mAddressing_Modifier_reflectJc) == kEnhancedReference_Modifier_reflectJc) {
        /**Adequate for enhanced references, check the reference values from back. Show only non-null references. */
        //TODO
        //while(length > 0 &&  ((void**)(adr))[length-1] == null)  //dereferenced at the given position with index.
        //{ length -=1;
        //}
      }
    }
    else
    { //assumed, it is a reference:
      //THROW1_s0(NoSuchFieldException, "not an array or container field, field=", (int32)(thiz));
      length = 0;  //dereferenced at the given position.
    }
  }
  else
  { length = 0; //because container is not exitsting
  }
  STACKTRC_LEAVE;
  return length;
}







/**it is a adequat method to get_FieldJc (java: Field.get(obj),
 * but the class is supplied also, because the class may be getted only from thiz, or from the Object.
 * In Java it is more simple: The class is getted anytime from the object.
 */
static MemSegmJc getObjAndClassV_FieldJc(FieldJc const* thiz, MemSegmJc obj
, ClassJc const** retClazz, const char* sVaargs, va_list vaargs)
{ ClassJc const* clazzFromField;
  ClassJc const* clazzRet = null;
  MemSegmJc retObj = NULL_MemSegmJc;
  //MemSegmJc dstObj;
  ObjectJc* retObjBase;
  

  int32 typeModifier, fieldModifier;
  int offsetBase;
  STACKTRC_ENTRY("getClassAndObj_FieldJc");

  clazzFromField = getType_FieldJc(thiz);  //get class from the field, but it may  be a superclass-reference to a derivated type.
  typeModifier = getModifiers_ClassJc(clazzFromField);
  fieldModifier = getModifiers_FieldJc(thiz);
  offsetBase = clazzFromField->posObjectBase;
  if( ADDR_MemSegmJc(obj, void) == null)
  { //the inputted obj is null already:
    retObj = null_MemSegmJc;
    clazzRet = clazzFromField;  //clazz is set from FieldJc-type for information, but it shouldn't used to access.
  }
  else
  { //?ref is the direct address of the referenced object, consider, it may be a embedded, array, container
    //obj is the parent obj, which contains the field thiz. idx is the index inside the field, or -1
    intPTR iRef;
    MemSegmJc ref; // = getReference_FieldJc(thiz, obj, idx);  //getRefAddr_FieldJc(thiz, obj, idx);
    //ref = address of the element inside obj. obj is the instance which contains this field.
    ref = getAddrElement_V_FieldJc(thiz, obj, sVaargs, vaargs); //getRefAddr_FieldJc(thiz, instance, 0);
    if(isReference_ModifierJc(fieldModifier))
    { 
      #ifdef DEF_HandlePtr64
        //Only for a system which deals with 32-bit-handle instead of pointer. Especially S-Function in Simulink.
        if( (fieldModifier & mPrimitiv_Modifier_reflectJc) == kHandlePtr_Modifier_reflectJc) {
          //replace the handle found in a field with the 64-bit address.
          uint32 handle = *(ADDR_MemSegmJc(ref, uint32));
          void* ptr64 = ptr_Handle2Ptr(handle); 
          setADDR_MemSegmJc(ref, (MemUnit*)ptr64);  //replace the handle with the 
        } else {
          ref = getRef_MemAccessJc(ref);   
        }
      #else
        ref = getRef_MemAccessJc(ref);   
      #endif
    }
    //the ref is the address of the object, which is referenced with field thiz.
    //A reference may be fault, than the address is not valid. Test it!
    iRef = (intPTR)ADDR_MemSegmJc(ref, void);
    if(iRef==0) //especially a null-pointer should be expected.
    { //a null pointer.
      retObj = null_MemSegmJc;             
      clazzRet = clazzFromField;  //clazz is set from FieldJc-type for information, but it shouldn't used to access.
    }
    else if((int)iRef == -1)
    { //Access to a remote CPU, a target via proxy
      int memSegment = -(int)iRef;
      int ixClass = -1;
      int32 addrRemote = getInfoDebug_InspcTargetProxy(getRootInstance_InspcTargetProxy, memSegment, 0, 0);
      if(addrRemote !=-1) {
        ixClass = getInfoDebug_InspcTargetProxy(getRootType_InspcTargetProxy, memSegment, 0, 0);
      }
      if(ixClass >0) {
        clazzRet = extReflectionClasses_ReflectionJc[0]->data[ixClass -1]; //get from loaded reflection file.
        { setAddr32Segm_MemSegmJc(retObj, addrRemote, memSegment );
        }
      } else {
        //access error on remote:
        clazzRet = null;
        retObj = null_MemSegmJc;
      }
    }
    else if(iRef < 100 && iRef > 0xf0000000)
    { //This is a invalid memory area. prevent access. TODO platform-depending, may be variable sizes.
      retObj = null_MemSegmJc;             
      clazzRet = clazzFromField;  //clazz is set from FieldJc-type for information, but it shouldn't used to access.
    }
    else
    {
      #if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
        if(typeModifier & mObjectifcBaseJcpp_Modifier_reflectJc)
        { //int offsetToObjectifcBaseJcppVtbl = (typeModifier & mDistanceObjectifcBase_Modifier_reflectJc) >> kBitDistanceObjectifcBase_Modifier_reflectJc;
          ClassJc const* clazzFromInstance;
          ObjectifcBaseJcpp* objifc = (ObjectifcBaseJcpp*)(ADDR_MemSegmJc(ref, MemUnit) + offsetBase);
          //Significant test:
          if(  objifc->significance_ObjectifcBase == kSignificance_ObjectifcBase
            && objifc->significanceAddress_ObjectifcBase == objifc
            )
          { retObjBase = objifc->toObject();
            MemSegmJc retObj1 = CONST_MemSegmJc(retObjBase, 0);  //C++ only at own memory. 
            retObj = retObj1;
            if(retObjBase != null)
            { clazzFromInstance = retObjBase->reflectionClass;  //get Clazz from object itself. It may be null if there is no reflection.
            }  
            else
            { clazzFromInstance = null; //the method toObject() supplies 'return null; '
            }
          }
          else
          { //This is a fatal error, because anything in headeres ins't correct. Problem of compilation of fault revisions.
            THROW1_s0(RuntimeException, "no significance ObjectifcBaseJcpp at address", (int32)objifc);
            clazzFromInstance = null;
          }
          if(clazzFromInstance != null) 
          { clazzRet = clazzFromInstance; 
          }
          else
          { //it is possible, that the instance is inherited from ObjectJc, but no reflection infos are given there.
            clazzRet = clazzFromField; //access to the given type, it may be a super clazz or interface.
          }
        }
        else
      #endif
      /**get the retObj and clazz. 
       * In normally the ref is the object to return. Save it in retObj. 
       * But in C++ the position of ObjectJc may have an offset to the instance itself, Therefore offsetBase is added.
       */
      /*else in C++*/ if((typeModifier & mObjectJcBased_Modifier_reflectJc) && (fieldModifier & (kEmbedded_Modifier_reflectJc |kEmbeddedContainer_Modifier_reflectJc))==0)
      { /**If the type is based on ObjectJc, the clazz is getted from its reflections.
           But if it is an embedded instance then the field type is used. For That is especially for super classes and ObjectJc on first position.
           Without this rule the Type is gotten again from the instance and the super type was not shown.
         */
        MemUnit* ref1 = ADDR_MemSegmJc(ref, MemUnit);
        ClassJc const* clazzFromInstance;
        if(segment_MemSegmJc(ref)!=0){
          stop(); //2CPU
          int ixClass = getInfoDebug_InspcTargetProxy(getType_InspcTargetProxy, segment_MemSegmJc(ref), ref.addr.a32  /*ADDR_MemSegmJc(ref, struct RemoteAddressJc)*/, 0);
          if (ixClass >0) {
            clazzRet = extReflectionClasses_ReflectionJc[0]->data[ixClass - 1]; //get from loaded reflection file.
          } else { 
            clazzRet = clazzFromField; 
          }
          retObj = ref;
        } else {
          if ((typeModifier & mObjectJcBased_Modifier_reflectJc) == mObjectJcpp_Modifier_reflectJc) {
            #if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
            //#if defined __cplusplus
              retObjBase = (static_cast<ObjectifcBase>ref1)->toObject();
            #else
              THROW_s0(IllegalArgumentException, "cannot use ObjectifcBaseJcpp", 0, 0);
              retObjBase = null;
            #endif
          } else {
            retObjBase = (ObjectJc*)(ref1 + offsetBase);  //offsetBase should be 0
          }
          MemSegmJc ret = ref;
          setADDR_MemSegmJc(ret, retObjBase);
          retObj = ret;
          if(retObjBase != null && (clazzFromInstance = retObjBase->reflection) != null) {
            clazzRet = clazzFromInstance; 
          }
          else
          { //it is possible, that the instance is inherited from ObjectJc, but no reflection infos are given there.
            clazzRet = clazzFromField; //access to the given type, it may be a super clazz or interface.
          }
        }
      }
      else
      { //a non object based refernce
        retObj = ref;
        clazzRet = clazzFromField;  //clazz is set from FieldJc-type because no other information is available.
        //it is correct of struct or class non based on ObjectJc are referenced. It is the referenced type always.
      }
    }
  }
  if(retClazz != null){ retClazz[0] = clazzRet; }
  STACKTRC_LEAVE; return(retObj);
}




//use getClassAndObj_FieldJc, it is the same.
METHOD_C MemSegmJc getObjAndClass_FieldJc(FieldJc const* thiz, MemSegmJc obj, ClassJc const ** retClazz, char const* sVaArgIdx, ...)
{ MemSegmJc ret;
  va_list vaList; 
  va_start(vaList, sVaArgIdx);
  ret = getObjAndClassV_FieldJc(thiz, obj, retClazz, sVaArgIdx, vaList);
  return ret;
}



//use getClassAndObj_FieldJc, it is the same.
METHOD_C MemSegmJc get_FieldJc(FieldJc const* thiz, MemSegmJc obj, char const* sVaArgIdx, ...)
{ MemSegmJc ret;
  va_list vaList; 
  va_start(vaList, sVaArgIdx);
  ret = getObjAndClassV_FieldJc(thiz, obj, null, sVaArgIdx, vaList);
  return ret;
}





/*
  modifiers = getModifiers_ClassJc(clazz);


  if(modifiers & mObjectifcBaseJcpp_Modifier_reflectJc)
  { //it is a type which is derivated from ObjectifcBaseJcpp, than get the ObjectJc-Pointer calling:
    int offsetBase = thiz->offsetToObjectifcBase;
    ObjectifcBaseJcpp* objifc = (ObjectifcBaseJcpp*)((MemUnit*)(ref) + offsetBase);
    objBase = objifc->toObjectJc();
    clazz = objBase->reflectionClass;  //the Class of the object.
  }
  else if(modifiers & mObjectJc_Modifier_reflectJc)
  { //it is a type which is derivated from ObjectifcBaseJcpp, than get the ObjectJc-Pointer calling:
    int offsetBase = thiz->offsetToObjectifcBase;
    objBase = (ObjectJc*)((MemUnit*)(ref) + offsetBase);
    clazz = objBase->reflectionClass;  //the Class of the object.
  }
  else
  {
    *

  if(modifiers & (mObjectJc_Modifier_reflectJc | mObjectifcBaseJcpp_Modifier_reflectJc))
  { //it is known that dstObj is pointer to ObjectJc directly, this is a feature of get_FieldJc.
    //But the dstObj instance itself may be a derivated class, get the class from the getted instance (like java):
    dstObj = get_FieldJc(thiz, obj, idx);  //this call may be thrown!
    if(dstObj != null)
    { clazz = getClass_ObjectJc((ObjectJc*)(dstObj));  //get the clazz from the instance.
    }
    else
    { clazz = null;
    }
  }
  else
  { //nextObj don't based on ObjectJc, but the clazz is supplied from field
    clazz = getType_FieldJc(thiz);  //get from the real object because the reference may be from a base type.
    if(retObj != null)
    { //get the retObj only if it is necessary
      dstObj = getRefAddr_FieldJc(thiz, obj, idx);  //considered a container.
    }
  }
  if(retObj != null){ *retObj = dstObj; }
  STACKTRC_LEAVE; return(clazz);
}
*/



//Note it is implemented in Java2C
METHOD_C MemSegmJc XXXXXXXsearchObject_ClassJc(StringJc sPath, ObjectJc* startObj, FieldJc const** retField, int* retIdx)
{
  MemSegmJc currentObj = null_MemSegmJc; //default if nothing is found
  //bool bFound = true;
  /*NOTE: usage of set_StringJc() and clear_StringJc() is a exactly mirror of String usage with possible garbage collection,
    here it is not necessary because the Strings are only in Stack focus, but is has not disadvantages.
    The other variant is a simple sName = value. It copies the content..
    This variant is used now, not set_StringJc
  */
  StringJc sName = NULL_StringJc;
  StringJc sElement = NULL_StringJc;
  ClassJc const* clazz = getClass_ObjectJc(startObj);
  MemSegmJc nextObj = CONST_MemSegmJc(startObj, 0);  //the source Object for the next access
  FieldJc const* field = null;
  int idx = -1;
  int posSep;
  int posStart = 0;
  idxSearchTrc = 0;
  STACKTRC_ENTRY("searchObject_ClassJc");
  TRY
  {
    do
    { int posEnd;
      posSep = indexOf_i_StringJc(sPath, '.', posStart);  //may be <0 if no '.' is found
      posEnd = posSep >= 0 ? posSep : length_StringJc(sPath );
      if(posEnd > posStart)  //should be always, only not on '.' on end.
      { //next loop to search:
        int posBracket;
        currentObj = nextObj;
        idx = -1;
        sElement = substring_StringJc(sPath, posStart, posEnd, _thCxt);
        posBracket = indexOf_C_StringJc(sElement, '[');
        { int posAngleBracket = indexOf_C_StringJc(sElement, '<');
          if(posAngleBracket >=0)
          { posBracket = posAngleBracket;  //may be also <0
          }
          if(posBracket >=0)
          { int posBracketEnd = indexOf_i_StringJc(sElement, posAngleBracket >=0 ? '>' : ']', posBracket + 1 );
            if(posBracketEnd <0) { posBracketEnd = length_StringJc(sElement ); } //if the ] is missing in the actual context
            //get index:
            idx = parseInt_IntegerJc(substring_StringJc(sElement, posBracket +1, posBracketEnd, _thCxt));
            sName = substring_StringJc(sElement, 0, posBracket, _thCxt);
          }
          else
          { sName = sElement;
          }
        }
        sElement = null_StringJc; //clear_StringJc(&sElement);
        field = getDeclaredField_ClassJc(clazz, sName);
        sName = null_StringJc; //clear_StringJc(&sName);

        /*
        //There was some confusion: In last version posBracket >= 0 was testet as positiv entry in if statements.
        //but the idx was > nrofArrayElements and an exception is thrown.
        //The simple test of chars after . may be correct, I think. HSchorrig 2008-01-25

        if(  (  posBracket >= 0     //an index [123] is given, access to the indexed element.
             && (!(bitModifiers & mStaticArray_Modifier_reflectJc)  //not a static array
                || (idx >=0  && idx < thiz->nrofArrayElements) //static array, index in range
             )  )
          || (  posSep >0        //a separator is given, access to the element because it is the base of next loop.
             && (posSep+1) < length_StringJc(&sPath)  //but at least 1 char after separator!
          )  )
        */
        if(  field != null    //instead exception. See getDeclaredField_ClassJc(). 
          && (  posSep >0                             //a separator is given,
             && length_StringJc(sPath ) > (posSep+1) //but at least 1 char after separator!
          )  )
        { //a next loop may be necessary because a . is found:
          //access to the element because it is the base of next loop.
          //currentObj is the object where the field is searched. 
          searchTrc_ClassJc[idxSearchTrc].objWhereFieldIsFound = currentObj; 
          searchTrc_ClassJc[idxSearchTrc].clazzWhereFieldIsFound = clazz;
          searchTrc_ClassJc[idxSearchTrc].field = field;
          nextObj = getObjAndClass_FieldJc(field, currentObj, &clazz, "I", idx);  
          searchTrc_ClassJc[idxSearchTrc].typeOfField = clazz;
          searchTrc_ClassJc[idxSearchTrc].objOfField = nextObj;
          if(++idxSearchTrc >= ARRAYLEN(searchTrc_ClassJc)){ idxSearchTrc = ARRAYLEN(searchTrc_ClassJc)-1; } //prevent overflow. 
          //nextObj is the object where the field is member of, 
          //nextObj is getted started from currentObj, +via offset in field, and access than. 
          //nextObj may be null, than exit the loop.
        }
        else; //the obj and field are found.
        posStart = posSep + 1;
      }
    } while(field != null && posSep > 0 && ADDR_MemSegmJc(nextObj, void) != null);
  } _TRY
  CATCH(NoSuchFieldException, exc)
  { //bFound = false;
    currentObj = null_MemSegmJc; field = null; idx = -1;
  }
  CATCH(Exception, exc)
  { //bFound = false;
    currentObj = null_MemSegmJc; field = null; idx = -1;
  }
  END_TRY
  if(field == null){
    //instead noSuchFieldException:
    currentObj = null_MemSegmJc; idx = -1;
  }
  if(retField != null){ retField[0] = field; }
  if(retIdx != null){ retIdx[0] = idx; }
  STACKTRC_LEAVE; return(currentObj);
    //#]
}




MemSegmJc getReference_FieldJc(FieldJc const* thiz, MemSegmJc instance, char const* sVaargs, ...)
{ va_list vaargs;
  va_start(vaargs, sVaargs);
  return getReference_V_FieldJc(thiz, instance, sVaargs, vaargs);
}



METHOD_C MemSegmJc getReference_V_FieldJc(FieldJc const* thiz, MemSegmJc instance, char const* sVaargs, va_list vaargs)
{ MemSegmJc ret = null_MemSegmJc;
  MemSegmJc addr;
  int modifiers = getModifiers_FieldJc(thiz);
  STACKTRC_ENTRY("setReference_FieldJc");
  addr = getAddrElement_V_FieldJc(thiz, instance, sVaargs, vaargs); //getRefAddr_FieldJc(thiz, instance, 0);
  if(isReference_ModifierJc(modifiers))
  { ret = getRef_MemAccessJc(addr);
    //MemSegmJc adr = (void**)getMemoryAddress_FieldJc(thiz, -1,obj);
  }
  else
  { ret = addr;
    //THROW1_s0(RuntimeException, "no reference type", 0);
  }
  STACKTRC_LEAVE; return ret;
}



intptr_t getMemoryIdent_FieldJc(FieldJc const* thiz, MemSegmJc instance, char const* sVaargs, ...)
{ va_list vaargs;
  va_start(vaargs, sVaargs);
  return getMemoryIdent_V_FieldJc(thiz, instance, sVaargs, vaargs);
}



intptr_t getMemoryIdent_V_FieldJc(FieldJc const* thiz, MemSegmJc instance, char const* sVaargs, va_list vaargs)
{ MemSegmJc adr = getAddrElement_V_FieldJc(thiz, instance, sVaargs, vaargs); //The address of the element inside the instance
  if(thiz->bitModifiers & kReference_Modifier_reflectJc){
    //the field is a reference field, get the reference value instead the address. The reference value
    //addresses the real target value.
    if ((thiz->bitModifiers & mPrimitiv_Modifier_reflectJc) == kHandlePtr_Modifier_reflectJc) {
      intptr_t* addrfield = ADDR_MemSegmJc(adr, intptr_t);
      intptr_t handle = *addrfield;
      void* addr = ptr_Handle2Ptr(handle);  //TODO what about Handle2Ptr-table. This branch is only used in Simulink, than Hande2Ptr-Table exists. 
      setADDR_MemSegmJc(adr, addr);
    } else {
      adr = getRef_MemAccessJc(adr);
    }
  }
  //returns the address in the memory space of the target. It may be another CPU.
  return (intptr_t)(ADDR_MemSegmJc(adr, void)); //further processing as int type 
}



METHOD_C void* setReference_FieldJc(FieldJc const* thiz, MemSegmJc instance, void* value, char const* sVaargs, ...)
{ int modifiers = getModifiers_FieldJc(thiz);
  void* ret = null;
  va_list vaargs;
  STACKTRC_ENTRY("setReference_FieldJc");
  va_start(vaargs, sVaargs);
  
  if(isReference_ModifierJc(modifiers))
  { MemSegmJc addr = getAddrElement_V_FieldJc(thiz,instance, sVaargs, vaargs);
    ret = (void*)(intptr_t)setValue_MemAccessJc(addr, &value, sizeof(void*));
  }
  else
  { THROW1_s0(RuntimeException, "no reference type", 0);
  }
  STACKTRC_LEAVE; return ret;

}



char getChar_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc adr;
  va_start(vaargs, sVaargs);
  adr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { adr = getRef_MemAccessJc(adr);
  }

  //TODO test if it is an integer field!
  
	return getByte_MemAccessJc(adr);  //char8
  //return (*(int*)(adr));
}


int8 getByte_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc adr;
  va_start(vaargs, sVaargs);
  adr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { adr = getRef_MemAccessJc(adr);
  }

  //TODO test if it is an integer field!
  
	return getByte_MemAccessJc(adr);
  //return (*(int*)(adr));
}


int16 getShort_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc adr;
  va_start(vaargs, sVaargs);
  adr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { adr = getRef_MemAccessJc(adr);
  }

  //TODO test if it is an integer field!
  
	return getInt16_MemAccessJc(adr);
  //return (*(int*)(adr));
}


//Note: 2016-12-04: If it is a reference to an integer, the indices should be applied
//inside the referenced field. Not to the obj. The field is not an embedded array of references but a reference to an array.  
METHOD_C int32 getInt_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{ va_list vaargs;
  MemSegmJc adr;
  int32 value;
  va_start(vaargs, sVaargs);
  //adr = getMemoryAddress_FieldJc(thiz,obj, false, sVaargs, vaargs);
  //TODO test if it is an integer field!
  if(isReference_ModifierJc(thiz->bitModifiers))
  { //Reference to an int element or an int array.
    MemSegmJc adrElementInObj = getAddrElement_V_FieldJc(thiz, obj, null, null); //The address of the reference
    adr = getRef_MemAccessJc(adrElementInObj);
    if(adr.addr.a !=null && sVaargs != null && *sVaargs == 'I'){  //only 1 index yet, todo later.
      int ixData = va_arg(vaargs, int32);
      //Manipulate the adr of the array to the adr of the array element.
      //TODO if the remote CPU is a Analog Devices DSP with word adressing, it is wrong.
      //It is necessary to have information about that detail.
      int32* addrElement = ADDR_MemSegmJc(adr, int32) + ixData;
      setADDR_MemSegmJc(adr, addrElement);
    }
  } else {
  	//scalar int or embedded array with given index
    adr = getAddrElement_V_FieldJc(thiz, obj, sVaargs, vaargs);
  }
  value = getInt32_MemAccessJc(adr);
  return value;
  //return (*(int*)(adr));
}


METHOD_C float getFloat_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{
  va_list vaargs;
  MemSegmJc adr;
  va_start(vaargs, sVaargs);
	adr = getAddrElement_V_FieldJc(thiz, obj, sVaargs, vaargs);
  //adr = getMemoryAddress_FieldJc(thiz,obj, false, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { adr = getRef_MemAccessJc(adr);
  }
  //TODO test if it is an integer field!
  return getFloat_MemAccessJc(adr);
  //return (*(float*)(adr));
}

METHOD_C double getDouble_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{ //STACKTRC_ENTRY("getDouble_FieldJc")

  va_list vaargs;
  MemSegmJc adr;
  va_start(vaargs, sVaargs);
  adr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { adr = getRef_MemAccessJc(adr);
  }

  //TODO test if it is an double field!
  return getDouble_MemAccessJc(adr);
  //return (*(double*)(adr));
}

METHOD_C bool getBoolean_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{ //STACKTRC_ENTRY("getBool_FieldJc")

  va_list vaargs;
  MemSegmJc adr;
  va_start(vaargs, sVaargs);
  adr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { adr = getRef_MemAccessJc(adr);
  }

  //TODO test if it is an integer field!
  return ( (getInt32_MemAccessJc(adr) & 0xff) != 0);
  //return (*(bool*)(adr));
}

METHOD_C int64 getInt64_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{ //STACKTRC_ENTRY("getInt64_FieldJc")

  va_list vaargs;
  MemSegmJc adr;
  va_start(vaargs, sVaargs);
  adr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);

  //TODO test if it is an integer field!
  return getInt64_MemAccessJc(adr);
  //return (*(int64*)(adr));
}



int16 getBitfield_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{
  va_list vaargs;
  MemSegmJc adr;
  int nrofBits = (thiz->nrofArrayElementsOrBitfield_ & mNrofBitsInBitfield_FieldJc) >> kBitNrofBitsInBitfield_FieldJc;
  int posBit = thiz->nrofArrayElementsOrBitfield_ & mBitInBitfield_FieldJc;
  if(nrofBits == 0){ nrofBits = 16; }  //special case: 0 is 16 bit.
  
  va_start(vaargs, sVaargs);
	//TODO getAddrElement_V_FieldJc
  adr = getMemoryAddress_FieldJc(thiz,obj, false, sVaargs, vaargs);

  //TODO test if it is an integer field!
  return getBitfield_MemAccessJc(adr, posBit, nrofBits);
}



int setBitfield_FieldJc(const FieldJc* thiz, MemSegmJc obj, int val, char const* sVaargs, ...)
{
  va_list vaargs;
  MemSegmJc adr;
  int nrofBits = (thiz->nrofArrayElementsOrBitfield_ & mNrofBitsInBitfield_FieldJc) >> kBitNrofBitsInBitfield_FieldJc;
  int posBit = thiz->nrofArrayElementsOrBitfield_ & mBitInBitfield_FieldJc;
  if(nrofBits == 0){ nrofBits = 16; }  //special case: 0 is 16 bit.

  va_start(vaargs, sVaargs);
	//TODO getAddrElement_V_FieldJc
  adr = getMemoryAddress_FieldJc(thiz,obj, false, sVaargs, vaargs);
  //TODO test if it is an integer field!
  return setBitfield_MemAccessJc(adr, val, posBit, nrofBits);

}




METHOD_C StringJc getString_FieldJc(const FieldJc* thiz, MemSegmJc instance, char const* sVaargs, ...)
{
  static char addret[100];  //TODO primitive solution, not thread safe.
  va_list vaargs;
  MemSegmJc addrField, ref;
  StringJc ret;
  ClassJc const* type = getType_FieldJc(thiz);
  int modifier = getModifiers_ClassJc(type);
  va_start(vaargs, sVaargs);
  addrField = getAddrElement_V_FieldJc(thiz,instance, sVaargs, vaargs);
  if(!isPrimitive_ClassJc(type)){
    ref = getReference_V_FieldJc(thiz, instance, sVaargs, vaargs);  //The address of the Object.
    if(ADDR_MemSegmJc(ref, void) == null){
      ret = z_StringJc("null");
    } else if(false && isObjectJc_ClassJc(type)){ //check based on ObjectJc
      ret = z_StringJc("toString(...)");; //invoke toString
    } else {
      //TODO:
      //StringBuilderJc_s* sret = threadBuffer_StringBuilderJc("", null);
      int32* addr1 = ADDR_MemSegmJc(addrField, int32);
      int32 val1 = addr1 == null ? 0 : getInt32_MemAccessJc(addrField); //from remote too.
      snprintf(addret, sizeof(addret), "@%p:%8.8X", addr1, val1);
      ret = z_StringJc(addret);
    }
  } else { //primitive Type of field:
    ret = null_StringJc;  //TODO
  }
  return ret;
}



METHOD_C int32 setInt_FieldJc(const FieldJc* thiz, MemSegmJc obj, int val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { addr = getRef_MemAccessJc(addr);
  }
  return (int32)setValue_MemAccessJc(addr, &val, 4);
}


METHOD_C int64 setLong_FieldJc(const FieldJc* thiz, MemSegmJc obj, int64 val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { addr = getRef_MemAccessJc(addr);
  }
  return (int64)setValue_MemAccessJc(addr, &val, 8);
}


METHOD_C int16 setShort_FieldJc(const FieldJc* thiz, MemSegmJc obj, int16 val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { addr = getRef_MemAccessJc(addr);
  }
  return (int16)setValue_MemAccessJc(addr, &val, 2);
}


METHOD_C char setChar_FieldJc(const FieldJc* thiz, MemSegmJc obj, char val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { addr = getRef_MemAccessJc(addr);
  }
  return (char)setValue_MemAccessJc(addr, &val, 1);
}

METHOD_C int8 setByte_FieldJc(const FieldJc* thiz, MemSegmJc obj, int8 val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { addr = getRef_MemAccessJc(addr);
  }
  return (int8)setValue_MemAccessJc(addr, &val, 1);
}

METHOD_C bool setBoolean_FieldJc(const FieldJc* thiz, MemSegmJc obj, bool val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  int8 val1 = (int8)(val ? 0 : 1);
  int32 valRet;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  valRet = setValue_MemAccessJc(addr, &val1, 1);
  return valRet !=0;
}


METHOD_C float setFloat_FieldJc(const FieldJc* thiz, MemSegmJc obj, float val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { addr = getRef_MemAccessJc(addr);
  }
  return setFloat_MemAccessJc(addr, val);
}


METHOD_C double setDouble_FieldJc(const FieldJc* thiz, MemSegmJc obj, double val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_V_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { addr = getRef_MemAccessJc(addr);
  }
  return setDouble_MemAccessJc(addr, val);
}



#endif //def DEF_REFLECTION_FULL

