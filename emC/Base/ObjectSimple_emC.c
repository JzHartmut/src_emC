#include <applstdef_emC.h>
#include <stdlib.h>   //malloc defined here
#include <string.h>   //memset defined here

#ifdef DEF_REFLECTION_SIMPLE
ClassJc const refl_ObjectJc = INIZ_ClassJc(refl_ObjectJc, "ObjectJc");
#endif




#if !defined(DEF_ObjectJcpp_REFLECTION) && ! defined(DEF_ObjectJc_OWNADDRESS)
struct ObjectJc_T * ctor_ObjectJc ( struct ObjectJc_T * othiz, void* ptr, uint size, struct ClassJc_t const* refl, uint idObj) {
  memset(othiz, 0, size);
  #ifdef DEF_ObjectJc_REFLREF
    othiz->reflection = refl;
    int id = idObj;
  #else
    int id = refl == null ? idObj : refl->idType | idObj & mArrayId_ObjectJc;
  #endif
  setSizeAndIdent_ObjectJc(othiz, size, id);
  return othiz;
}
#endif


#ifndef DEF_REFLECTION_NO
void setReflection_ObjectJc(ObjectJc* thiz, struct ClassJc_t const* refl, uint size)
{ 
  uint sizegiven = getSizeInfo_ObjectJc(thiz);
  #ifdef DEF_ObjectJc_REFLREF  
    thiz->reflection = refl;
    if(size > sizegiven) { //size as parameter given:
      uint identInfo = getIdentInfo_ObjectJc(thiz);
      if(isArray_ObjectJc(thiz)) { identInfo |= mArrayId_ObjectJc; } 
      setSizeAndIdent_ObjectJc(thiz, size, identInfo);
      sizegiven = size; 
    }
  #else //not DEF_ObjectJc_SIMPLE
    if(size > sizegiven) { sizegiven = size; }
    uint identInfo = refl->idType;
    if(isArray_ObjectJc(thiz)) { identInfo |= mArrayId_ObjectJc; } 
    setSizeAndIdent_ObjectJc(thiz, sizegiven, refl->idType); 
  #endif //DEF_ObjectJc_REFLREF
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
  if (refl !=null && !instanceof_ObjectJc(thiz, refl)) {
    return false; 
  }
  #ifdef DEF_ObjectJc_REFLREF
  //ObjectJc hase REFLREF: check both, ident and refl
  if( ident!=0 && (thiz->identSize & mInstance_ObjectJc) != (((uint32)ident)<< kBitInstance_ObjectJc)) {
    return false;
  }
  #endif
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
    #if defined (DEF_ObjectJc_SIMPLE)
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
  ObjectJc* thiz = (ObjectJc*)malloc(size);
  ctor_ObjectJc(thiz, thiz, size, refl, id);
  return thiz;
}
#endif  //#else: The Blockheap has its own algorithm.

