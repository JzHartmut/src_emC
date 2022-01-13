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
 **copyright**************************************************************************************
 *
 * @content implementation of base routines of a simple ObjectJc
 * Note: Accordingly to definitions of the capablity of an ObjectJc base structure, 
 *       recommended to do in the applstdef_emC.h,
 *       this source excludes contents which are implemented in another way in ObjectRefl_emC.c
 *
 *
 ****************************************************************************/
#include <emC/Base/Object_emC.h>

#ifndef DEF_NO_ObjectJc_emC

#include <emC/Base/MemC_emC.h>
#include <stdlib.h>   //malloc defined here
#include <string.h>   //memset defined here

#if defined(DEF_REFLECTION_SIMPLE) || defined(DEF_REFLECTION_OFFS)
  //REFLECTION_SIMPLE: Used as type designator.
  //REFLECTION_OFFS: It is not part of the generated reflection. It is a standard part. But contained in the index table of reflections.
  //REFLECTION_NO: Not necessary, do not spend space for it.
  //REFLECTION_FULL: Other definition is necessary.
  ClassJc const refl_ObjectJc = INIZ_ClassJc(refl_ObjectJc, "ObjectJc");
#endif




#if !defined(DEF_ObjectJcpp_REFLECTION) && ! defined(DEF_ObjectJc_OWNADDRESS)
struct ObjectJc_T * ctor_ObjectJc ( struct ObjectJc_T * othiz, void* ptr, uint size, struct ClassJc_t const* refl, uint idObj) {
  //removed 2020-12-02: size is the whole C++ instance, memset will set too much. 
  //instead: The data ctor is responsible to clear of data. Commonly: prevent using memset. 
  //removed: memset(othiz, 0, size);
  //
  //Set all data of ObjectJc adequat to its specific definition:
  #ifndef DEF_REFLECTION_NO
    othiz->reflection = refl;
    int id = idObj;
  #else
    int id = refl == null ? idObj : (refl->idType | (idObj & mArrayId_ObjectJc));
  #endif
  setSizeAndIdent_ObjectJc(othiz, size, id);
  return othiz;
}
#endif


#ifndef DEF_REFLECTION_NO
void setReflection_ObjectJc(ObjectJc* thiz, struct ClassJc_t const* refl, uint size)
{ 
  uint sizegiven = getSizeInfo_ObjectJc(thiz);
  #ifndef DEF_REFLECTION_NO  
    thiz->reflection = refl;
    if(size > sizegiven && size != ((uint)-1)) {     //size as parameter givenm but not -1
      uint identInfo = getIdentInfo_ObjectJc(thiz);  //the higher value of size wins.
      if(isArray_ObjectJc(thiz)) { identInfo |= mArrayId_ObjectJc; } 
      setSizeAndIdent_ObjectJc(thiz, size, identInfo);
      sizegiven = size; 
    }
  #else //DEF_REFLECTION_NO
    if(size > sizegiven && size != ((uint)-1)) { sizegiven = size; }
    uint identInfo = refl->idType;
    if(isArray_ObjectJc(thiz)) { identInfo |= mArrayId_ObjectJc; } 
    setSizeAndIdent_ObjectJc(thiz, sizegiven, refl->idType); 
  #endif //DEF_REFLECTION_NO
}
#endif



#ifndef DEF_ObjectJc_LARGESIZE
void setSizeAndIdent_ObjectJc(ObjectJc* thiz, int sizeObj, int ident)
{ ASSERT_emC(sizeObj < mSize_ObjectJc, "too large sizeObj", sizeObj, ident);
  //Note: ident can have the mArrayId_ObjectJc bit. 
  ASSERT_emC( (ident & ~mArrayId_ObjectJc)  < mInstanceType_ObjectJc, "too large ident", sizeObj, ident);
  thiz->identSize = sizeObj | ( ((int32)ident) << kBitInstanceType_ObjectJc);
}
#endif

#ifndef DEF_ObjectJc_LARGESIZE
bool checkStrict_ObjectJc ( ObjectJc const* thiz, uint size, struct ClassJc_t const* refl, uint ident) {
  //Note: on DEF_REFLECTION_NO it cannot be checked whether the reflection is ok
  //      because it cannot be distinguish between a non-derived or derived plain data instance. 
  #ifndef DEF_REFLECTION_NO
    if (refl !=null && !instanceof_ObjectJc(thiz, refl)) {
      return false; 
    }
    if( ident!=0 && (thiz->identSize & mInstance_ObjectJc) != (((uint32)ident)<< kBitInstance_ObjectJc)) {
      return false;
    }
  #endif
  //Note: The size contains the size of a C++ class too, hence this test is not sufficient.
  //      but it is a necessary test.
  return (thiz->identSize & mSize_ObjectJc) >= size;  //true if size ==0, but mSize-bits should be valid.
}
#endif



#ifdef DEF_ObjectSimple_emC
bool checkInit_ObjectJc ( ObjectJc* thiz, uint size, struct ClassJc_t const* refl, uint ident) {
  #ifndef DEF_REFLECTION_NO
    if(thiz->reflection == null) {
      thiz->reflection = refl;
    }
    if((thiz->identSize & mInstance_ObjectJc)==0) {
      thiz->identSize |= ident & mInstance_ObjectJc;
    }
    if (refl !=null && !instanceof_ObjectJc(thiz, refl)) {
      return false; 
    }
    if( ident!=0 && (thiz->identSize & mInstance_ObjectJc) != (((uint32)ident)<< kBitInstance_ObjectJc)) {
      return false;
    }
  #endif
  //Note: The size contains the size of a C++ class too, hence this test is not sufficient.
  //      but it is a necessary test.
  if((thiz->identSize & mSize_ObjectJc) ==0) {
    thiz->identSize |= size & mSize_ObjectJc;
  }
  return (thiz->identSize & mSize_ObjectJc) >= size;  //true if size ==0, but mSize-bits should be valid.
}
#endif



#ifdef DEF_REFLECTION_NO
bool instanceofReflid_ObjectJc ( struct ObjectJc_T const* thiz, uint reflId) {
  return ((thiz->identSize & mInstanceType_ObjectJc) >> kBitInstanceType_ObjectJc) == reflId;
}
#endif

#if !defined(DEF_REFLECTION_FULL)
bool instanceof_ObjectJc ( struct ObjectJc_T const* thiz, struct ClassJc_t const* reflection) {
  bool reflOk = reflection == null; //true if the argument is null, special case 
  if(!reflOk) {
    #if defined (DEF_REFLECTION_NO)
      //The mInstanceType_ObjectJc have to be contain the same type Id as in reflection.
      //An instance Id is not possible for minimal ObjectJc
      uint idType = getIdentInfo_ObjectJc(thiz);
      ClassJc const* refl1 = reflection;
      reflOk = (refl1->idType == idType);  //It is not possible to detect a superclass type! 
    #else
      //It is a more simle ClassJc definition:
      if(reflection != null) {
        struct ClassJc_t const* refl1 = thiz->reflection;
        while(!reflOk && refl1 !=null) { //Check superclasses of this
          reflOk = refl1 == reflection;
          refl1 = refl1->superClass;
        }
      }
    #endif
  }
  return reflOk;
}
#endif



void setInitialized_ObjectJc(struct ObjectJc_T const* thiz) {
  ObjectJc* wthiz = WR_CAST(ObjectJc*, thiz);
  wthiz->identSize |= mInitialized_ObjectJc;
}





#ifndef USE_BlockHeap_emC
struct ObjectJc_T* allocRefl_ObjectJc ( uint size, struct ClassJc_t const* refl, uint id) {
  ObjectJc* thiz = C_CAST(ObjectJc*, alloc_MemC(size));
  ctor_ObjectJc(thiz, thiz, size, refl, id);
  return thiz;
}
#endif  //#else: The Blockheap has its own algorithm.


void finalize_ObjectJc_F(ObjectJc const* ythis, ThCxt* _thCxt)
{
}



#endif //DEF_NO_ObjectJc_emC
