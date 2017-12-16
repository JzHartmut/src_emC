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
 * 2012-04-07 Hartmut new: nrofBytesScalarTypes_ClassJc[], reflection__char16Jc
 * 2010-07-10: Hartmut: Array access to second CPU
 * 2010-02-01: prevent exception on getDeclaredField_ClassJc, instead return null, regarding in searchObject_ClassJc. Reason: better to handle, problems with setjmp on some embedded processors.
 * 2009-12-00: Hartmut improved.
 * 2008-04-22: JcHartmut adap: ReflectionJc.h
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
#include "Jc/ReflectionJc.h"
#include "Jc/ReflMemAccessJc.h"
#include "Jc/StringJc.h"
#include "Jc/ObjectJc.h"      //It is a concept of CRuntimeJavalike
#include "Fwc/fw_Exception.h"

#include <Fwc/fw_SimpleC.h>
#include <stdio.h>

#undef mStaticArray_Modifier_reflectJc //it shouldn't be used!
#undef mReference_Modifier_reflectJc

//#include "fw_ThreadContext.h"
/********************************************************************************************/
// Field




struct SearchTrc_t
{ MemSegmJc objWhereFieldIsFound; 
  ClassJc const* clazzWhereFieldIsFound;
  FieldJc const* field; 
  ClassJc const* typeOfField; 
  MemSegmJc objOfField;
} searchTrc_ClassJc[16] = {0}; //only debug
  
int idxSearchTrc = 0;



#ifdef __HandlePtr64__
  #include <Fwc/fw_handle_ptr64.h>      
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



const ClassJc* simpleTypes[kREFLECTION_LastConstant] =
{ null    //0x0
, &reflection__voidJc  //0x1
, &reflection__int64Jc          //0x2
, &reflection__uint64Jc         //0x3
, &reflection__int32Jc          //0x4
, &reflection__uint32Jc         //0x5
, &reflection__int16Jc          //0x6
, &reflection__uint16Jc         //0x7
, &reflection__int8Jc           //0x8
, &reflection__uint8Jc          //0x9
, &reflection__intJc            //0xa
, &reflection__uintJc           //0xb
, &reflection__floatJc          //0xc
, &reflection__doubleJc         //0xd
, &reflection__charJc           //0xe
, &reflection__char16Jc         //0xf
, &reflection_StringJc         //0x10
, null  //0x11
, null  //0x12
, null  //0x13
, &reflection_float_complex    //0x14
, &reflection_double_complex  //0x15
, &reflection__boolJc           //0x16
, &reflection_bitfieldJc      //0x17
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
, &reflection__ObjectifcBaseJcpp  //0x18
#else
, null
#endif
, &reflection__ObjectJc.clazz  //0x19
, &reflection__ObjectJc.clazz  //0x1a
, &reflection__ObjectArrayJc.clazz  //0x1b
, null  //0x1c   //reserviert evtl Object_ArrayJcpp
, &reflection_StringJc  //0x1d
, null  //0x1e
, null  //0x1f
, &reflection__ClassJc.clazz  //0x20
, null  //0x21
, null  //0x22
, null  //0x23
, null  //0x24
, null  //0x25
, null  //0x26
, null  //0x27
, null  //0x28
, null  //0x29
, null  //0x2a
, null  //0x2b
, null  //0x2c
, null  //0x2d
, null  //0x2e
, null  //0x2f
, null  //0x30
, null  //0x31
, null  //0x32
, null  //0x33
, null  //0x34
, null  //0x35
, null  //0x36
, null  //0x37
, null  //0x38
, null  //0x39
, null  //0x3a
, null  //0x3b
, null  //0x3c
, null  //0x3d
, null  //0x3e
, null  //0x3f
, null  //0x40
, &reflection__ObjectJc.clazz             //0x41
, &reflection__ObjectJcpp.clazz        //0x42
, null             //0x43
, null //&reflection__ObjectRefValuesJc"    //0x44
, &reflection__ClassJc.clazz              //0x45
, null  //0x46
, null  //0x47
, null  //0x48
, null  //0x49
, null  //0x4a
, null  //0x4b
, null  //0x4c
, null  //0x4d
, null  //0x4e
, null  //0x4f
};

//see javaSrc_vishiaBase/org.vishia.reflect.Java2C.nrofBytesScalarTypes.
const int nrofBytesScalarTypes_ClassJc[] =
{ 0, 0, 8, 8, 4, 4, 2, 2, 1, 1, 4, 4
  , 4, 8  //float, double
  , 1, 2  //char8, char16
  , 8     //StringJc?
  , 0,0,0,0,0  //0x11..0x15
  , 1     //boolean represented with 1 byte
  , 4     //bitfield supplied with 4 bytes
  ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 
};


/**A maximum of 5 external CPUs are supported. */
ClassJc_YP const* extReflectionClasses_ReflectionJc[5];   





static int stop()
{ return 0;  //debug breakpoint here able to set.
}


ClassJc* ctorM_ClassJc(MemC rawMem)
{ ClassJc* thiz = PTR_MemC(rawMem, ClassJc);
  STACKTRC_ENTRY("ctor_ClassJc");
  if(size_MemC(rawMem)<sizeof(ClassJc)) THROW_s0(IllegalArgumentException, "ctor mem-size insufficient", size_MemC(rawMem));
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
  if(size_MemC(rawMem)<sizeof(FieldJc)) THROW_s0(IllegalArgumentException, "ctor mem-size insufficient", size_MemC(rawMem));
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


const char* getName_ClassJc(ClassJc const* thiz)
{ if( ((uint64)(thiz)) < kREFLECTION_LastConstant )
  { thiz = simpleTypes[(int)(thiz)];
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
  if( ((uint64)(thiz)) < kREFLECTION_LastConstant )
  { thiz = simpleTypes[(int)(thiz)];
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
  if( ((uint64)(thiz)) < kREFLECTION_LastConstant ) //2015-06 regard 64-bit-addresses and >0x7fffffff
  { thiz = simpleTypes[(int)(thiz)];
  }
  //thiz is the real class:
  fields = thiz->attributes;
  return fields; 
}


const FieldJc* getDeclaredField_ClassJc(ClassJc const* thiz, StringJc sName)
{ int ii;
  bool bFound = false;
  const FieldJc* field = null;
  STACKTRC_ENTRY("getDeclaredField_ClassJc");
  //for(ii=0; !bFound && ii< thiz->attributes->array.length; ii++)
  if(thiz->attributes != null)
  { for(ii=0; !bFound && ii< thiz->attributes->head.length; ii++)
    { //StringJcRef sNameField;
      const char* sNameField;
      //field = get_FieldJc_Y(thiz->attributes,ii);
      field = &thiz->attributes->data[ii];
      sNameField = getName_FieldJc(field);
      //if(equals_StringJc(&sNameField,sName_ROOT))
      if(equals_z_StringJc(sName, sNameField))
      { bFound= true;
      }
    }
  }
  if(!bFound)  //also if attributes == null
  { //THROW_s(NoSuchFieldException, *sName,0); 
    field = null;
  }
  STACKTRC_LEAVE;
  return field;
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
  if(thiz->superClasses == null) return null;
  else return thiz->superClasses->data[0].clazz; //Note: C++ knows more superclasses, this is for Java-like and C
}



METHOD_C FieldJc const* getSuperField_ClassJc(ClassJc const* thiz)
{
  if(thiz->superClasses == null) return null;
  else return &thiz->attributes->data[0];    //TODO should do so for C
}




MethodJcARRAY const* ptrConstCasting_MethodJcARRAY(ObjectArrayJc const* ptr)
{ return (MethodJcARRAY const*)(ptr);
}



MethodJc const* get_MethodJcARRAY(const MethodJcARRAY* thiz, int idx)
{ return (MethodJc const*)(get_i_ObjectArrayJc(&thiz->head, idx));
}



const StringJc getName_Method(const MethodJc* thiz)
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




/**Implementation hint: It is possible, that the type indent is a simple integer number,
   than return the correct representation!
 */
ClassJc const* getType_FieldJc(FieldJc const* thiz)
{ ClassJc const* type = thiz->type_;
  if( ((uint64)(type)) < kREFLECTION_LastConstant )
  { type = simpleTypes[(int)(type)];
  }
  return type;
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
  {  set_OS_PtrValue(address, 0, null);
  }
  else
  { int position = thiz->position;  //2CPU
    int sizeElement = 1;
    void* memAddr;
    if((position & 0x8000) !=0){
      ClassJc const* declaringClazz = getDeclaringClass_FieldJc(thiz);
      int32 sizeEntry = declaringClazz->nSize;
      int32 idxClass = sizeEntry - 0xFFFFF000;
      //int idxField = thiz->nrofArrayElements & 0x0fff;
      int idxField = position & 0x7FFF;
      int32 posLength;
      /**Significance check to prevent failed access: */
      ASSERT(idxClass >0 && idxClass < 1000 && idxField >=0 && idxField < 0xfff);

      posLength = getInfoDebug_RemoteCpuJc(getOffsetLength_RemoteCpuJc, segment_MemSegmJc(instance), null, idxClass<<16 |idxField);
      position = posLength & 0x0000ffff; //position-part in bit15..0
      sizeElement = (posLength & 0x7FFF0000) >>16;
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
        case kEnhancedReference_Modifier_reflectJc: sizeElement = sizeof(OS_PtrValue); break;
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
    address = null_OS_PtrValue;
  }
  STACKTRC_LEAVE; return(address);
}



static MemSegmJc getRefAddrObjectArray_FieldJc(MemSegmJc addrArray, char const* sVaargs, va_list vaargs, ThCxt* _thCxt)
{ MemSegmJc retAddress = NULL_MemC();
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
    if(retAddress1 == null){ THROW_s0(IndexOutOfBoundsException, "index to large", ixData);}
    setADDR_MemSegmJc(retAddress, retAddress1);
  }
  STACKTRC_LEAVE; return retAddress;
  
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
MemSegmJc getAddrElement_FieldJc(const FieldJc* thiz, MemSegmJc instance, char const* sVaargs, va_list vaargs)
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
            default: THROW_s0(IllegalArgumentException, "undefined container type", bitContainerType);
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
      //THROW_s0(NoSuchFieldException, "not an array or container field, field=", (int32)(thiz));
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
  int32 modifiers = getModifiers_FieldJc(thiz);
  ObjectJc* retObjBase;
  

  int32 typeModifier, fieldModifier;
  int offsetBase;
  STACKTRC_ENTRY("getClassAndObj_FieldJc");

  clazzFromField = getType_FieldJc(thiz);  //get class from the field, but it may  be a superclass-reference to a derivated type.
  typeModifier = getModifiers_ClassJc(clazzFromField);
  fieldModifier = thiz->bitModifiers;
  offsetBase = clazzFromField->posObjectBase;
  if( ADDR_MemSegmJc(obj, void) == null)
  { //the inputted obj is null already:
    retObj = null_OS_PtrValue;
    clazzRet = clazzFromField;  //clazz is set from FieldJc-type for information, but it shouldn't used to access.
  }
  else
  { //?ref is the direct address of the referenced object, consider, it may be a embedded, array, container
    //obj is the parent obj, which contains the field thiz. idx is the index inside the field, or -1
    intPTR iRef;
    MemSegmJc ref; // = getReference_FieldJc(thiz, obj, idx);  //getRefAddr_FieldJc(thiz, obj, idx);
    //ref = address of the element inside obj. obj is the instance which contains this field.
    ref = getAddrElement_FieldJc(thiz, obj, sVaargs, vaargs); //getRefAddr_FieldJc(thiz, instance, 0);
    if(isReference_ModifierJc(modifiers))
    { 
      #ifdef __HandlePtr64__
        //Only for a system which deals with 32-bit-handle instead of pointer. Especially S-Function in Simulink.
        if( (fieldModifier & mPrimitiv_Modifier_reflectJc) == kHandlePtr_Modifier_reflectJc) {
          //replace the handle found in a field with the 64-bit address.
          uint32 handle = *(ADDR_MemSegmJc(ref, uint32));
          void* ptr64 = null;
          getPtr_Handle2Ptr(handle, &ptr64); 
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
      retObj = null_OS_PtrValue;             
      clazzRet = clazzFromField;  //clazz is set from FieldJc-type for information, but it shouldn't used to access.
    }
    else if((int)iRef == -1)
    { //Access to a second CPU
      int memSegment = -(int)iRef;
      int32 addrRemote = getInfoDebug_RemoteCpuJc(getRootInstance_RemoteCpuJc, memSegment, null, 0);
      int ixClass = getInfoDebug_RemoteCpuJc(getRootType_RemoteCpuJc, memSegment, null, 0);
      if(addrRemote != -1 && ixClass >0) {
        clazzRet = extReflectionClasses_ReflectionJc[0]->data[ixClass -1]; //get from loaded reflection file.
        { set_OS_PtrValue(retObj, (void*)addrRemote, memSegment);
        }
      } else {
        //access error on remote:
        clazzRet = null;
        retObj = null_MemSegmJc;
      }
    }
    else if(iRef < 100 && iRef > 0xf0000000)
    { //This is a invalid memory area. prevent access. TODO platform-depending, may be variable sizes.
      retObj = null_OS_PtrValue;             
      clazzRet = clazzFromField;  //clazz is set from FieldJc-type for information, but it shouldn't used to access.
    }
    else
    {
      #if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
        if(typeModifier & mObjectifcBaseJcpp_Modifier_reflectJc)
        { //int offsetToObjectifcBaseJcppMtbl = (typeModifier & mDistanceObjectifcBase_Modifier_reflectJc) >> kBitDistanceObjectifcBase_Modifier_reflectJc;
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
            THROW_s0(RuntimeException, "no significance ObjectifcBaseJcpp at address", (int32)objifc);
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
      /*else in C++*/ if((typeModifier & mObjectJc_Modifier_reflectJc) && (modifiers & kEmbeddedContainer_Modifier_reflectJc)==0)
      { /**If the type is based on ObjectJc, the clazz is getted from its reflections.
           But not for an embedded instance. Only for references. A reference may from base type. 
           Especially it is ObjectJc itself, it should show the fields of ObjectJc.
         */
        MemUnit* ref1 = ADDR_MemSegmJc(ref, MemUnit);
        ClassJc const* clazzFromInstance;
        MemSegmJc ret = ref;
        if(segment_MemSegmJc(ref)!=0){
          stop(); //2CPU
        } else {
          retObjBase = (ObjectJc*)(ref1 + offsetBase);
          setADDR_MemSegmJc(ret, retObjBase);
          retObj = ret;
          clazzFromInstance = retObjBase->reflectionClass;    //2CPU get Clazz from object itself. It may be null if there is no reflection.
          if(clazzFromInstance != null) { 
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
  MemSegmJc currentObj = null_OS_PtrValue; //default if nothing is found
  //bool bFound = true;
  /*NOTE: usage of set_StringJc() and clear_StringJc() is a exactly mirror of String usage with possible garbage collection,
    here it is not necessary because the Strings are only in Stack focus, but is has not disadvantages.
    The other variant is a simple sName = value. It copies the content..
    This variant is used now, not set_StringJc
  */
  StringJc sName = NULL_StringJc;
  StringJc sElement = NULL_StringJc;
  ClassJc const* clazz = getClass_ObjectJc(startObj);
  MemSegmJc nextObj = CONST_OS_PtrValue(startObj, MemUnit, 0);  //the source Object for the next access
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
    currentObj = null_OS_PtrValue; field = null; idx = -1;
  }
  CATCH(Exception, exc)
  { //bFound = false;
    currentObj = null_OS_PtrValue; field = null; idx = -1;
  }
  END_TRY
  if(field == null){
    //instead noSuchFieldException:
    currentObj = null_OS_PtrValue; idx = -1;
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
{ MemSegmJc ret = null_OS_PtrValue;
  MemSegmJc addr;
  int modifiers = getModifiers_FieldJc(thiz);
  STACKTRC_ENTRY("setReference_FieldJc");
  addr = getAddrElement_FieldJc(thiz, instance, sVaargs, vaargs); //getRefAddr_FieldJc(thiz, instance, 0);
  if(isReference_ModifierJc(modifiers))
  { ret = getRef_MemAccessJc(addr);
    //MemSegmJc adr = (void**)getMemoryAddress_FieldJc(thiz, -1,obj);
  }
  else
  { ret = addr;
    //THROW_s0(RuntimeException, "no reference type", 0);
  }
  STACKTRC_LEAVE; return ret;
}



void* getMemoryIdent_FieldJc(FieldJc const* thiz, MemSegmJc instance, char const* sVaargs, ...)
{ va_list vaargs;
  va_start(vaargs, sVaargs);
  return getMemoryIdent_V_FieldJc(thiz, instance, sVaargs, vaargs);
}



void* getMemoryIdent_V_FieldJc(FieldJc const* thiz, MemSegmJc instance, char const* sVaargs, va_list vaargs)
{ MemSegmJc adr = getAddrElement_FieldJc(thiz, instance, sVaargs, vaargs);
  if(thiz->bitModifiers & kReference_Modifier_reflectJc){
    //the field is a reference field, get the reference value instead the address. The reference value
    //addresses the real target value.
    adr = getRef_MemAccessJc(adr);
  }
  //returns the address in the memory space of the target. It may be another CPU.
  return (ADDR_MemSegmJc(adr, void)); 
}



METHOD_C void* setReference_FieldJc(FieldJc const* thiz, MemSegmJc instance, void* value, char const* sVaargs, ...)
{ int modifiers = getModifiers_FieldJc(thiz);
  void* ret = null;
  va_list vaargs;
  STACKTRC_ENTRY("setReference_FieldJc");
  va_start(vaargs, sVaargs);
  
  if(isReference_ModifierJc(modifiers))
  { MemSegmJc addr = getAddrElement_FieldJc(thiz,instance, sVaargs, vaargs);
    ret = (void*)setValue_MemAccessJc(addr, &value, sizeof(void*));
  }
  else
  { THROW_s0(RuntimeException, "no reference type", 0);
  }
  STACKTRC_LEAVE; return ret;

}



char getChar_FieldJc(const FieldJc* thiz, MemSegmJc obj, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc adr;
  va_start(vaargs, sVaargs);
  //TODO use getAddrElement_FieldJc instead getMemoryAddress_FieldJc to regard whether it may be a complex container.
  //TODO on all get- and set methods. 
  adr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  adr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  adr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
    MemSegmJc adrElementInObj = getAddrElement_FieldJc(thiz, obj, null, null); //The address of the reference
    adr = getRef_MemAccessJc(adrElementInObj);
    if(adr.ref !=null && sVaargs != null && *sVaargs == 'I'){  //only 1 index yet, todo later.
      int ixData = va_arg(vaargs, int32);
      //Manipulate the adr of the array to the adr of the array element.
      //TODO if the remote CPU is a Analog Devices DSP with word adressing, it is wrong.
      //It is necessary to have information about that detail.
      int32* addrElement = PTR_OS_PtrValue(adr, int32) + ixData;
      setPtr_OS_PtrValue(adr, addrElement);
    }
  } else {
  	//scalar int or embedded array with given index
    adr = getAddrElement_FieldJc(thiz, obj, sVaargs, vaargs);
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
	adr = getAddrElement_FieldJc(thiz, obj, sVaargs, vaargs);
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
  adr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  adr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  adr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);

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
	//TODO getAddrElement_FieldJc
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
	//TODO getAddrElement_FieldJc
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
  addrField = getAddrElement_FieldJc(thiz,instance, sVaargs, vaargs);
  if(!isPrimitive_ClassJc(type)){
    ref = getReference_V_FieldJc(thiz, instance, sVaargs, vaargs);  //The address of the Object.
    if(ADDR_MemSegmJc(ref, void) == null){
      ret = z_StringJc("null");
    } else if(false && isObjectJc_ClassJc(type)){ //check based on ObjectJc
      ret = z_StringJc("toString(...)");; //invoke toString
    } else {
      //TODO:
      //StringBuilderJc* sret = threadBuffer_StringBuilderJc("", null);
      int32* addr1 = ADDR_MemSegmJc(addrField, int32);
      int32 val1 = addr1 == null ? 0 : *addr1;
      sprintf(addret, "@%p:%8.8X", addr1, val1);
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
  addr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  addr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  addr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  addr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  addr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  addr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
  valRet = setValue_MemAccessJc(addr, &val1, 1);
  return valRet !=0;
}


METHOD_C float setFloat_FieldJc(const FieldJc* thiz, MemSegmJc obj, float val, char const* sVaargs, ...)
{ 
  va_list vaargs;
  MemSegmJc addr;
  va_start(vaargs, sVaargs);
  addr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
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
  addr = getAddrElement_FieldJc(thiz,obj, sVaargs, vaargs);
  if(isReference_ModifierJc(thiz->bitModifiers))
  { addr = getRef_MemAccessJc(addr);
  }
  return setDouble_MemAccessJc(addr, val);
}

