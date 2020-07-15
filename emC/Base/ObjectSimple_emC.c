#include <applstdef_emC.h>
#ifdef DEF_ObjectJc_SIMPLEST
#include <stdlib.h>   //malloc defined here
#include <string.h>   //memset defined here



ObjectJc* ctor_ObjectJc ( ObjectJc* othiz, void* ptr, int size, struct ClassJc_t const* refl, int idObj) {
  memset(othiz, 0, size);
  int id = refl == null ? idObj : refl->id | idObj & mArrayId_ObjectJc;
  setSizeAndIdent_ObjectJc(othiz, size, id);
  return othiz;
}



void setSizeAndIdent_ObjectJc(ObjectJc* thiz, int sizeObj, int ident)
{ ASSERT_emC(sizeObj < mSize_ObjectJc, "too large sizeObj", sizeObj, ident);
  //Note: ident can have the mArrayId_ObjectJc bit. 
  ASSERT_emC( (ident & ~mArrayId_ObjectJc)  < mInstanceType_ObjectJc, "too large ident", sizeObj, ident);
  thiz->identSize = sizeObj | ( ((int32)ident) << kBitInstanceType_ObjectJc);
}



bool checkStrict_ObjectJc ( ObjectJc const* thiz, uint size, struct ClassJc_t const* refl, uint ident) {
  if (refl !=null && !instanceof_ObjectJc(thiz, refl)) {
    return false; 
  }
  return (thiz->identSize & mSize_ObjectJc) >= size;  //true if size ==0, but mSize-bits should be valid.
}



bool instanceof_ObjectJc(ObjectJc const* thiz, struct ClassJc_t const* refl)
{ 
  bool bOk;
  if(refl !=null) {
    //TODO regard single inheritance 
    bOk = (refl->id == (thiz->identSize & mInstanceType_ObjectJc) >> kBitInstanceType_ObjectJc);
  }
  else { 
    bOk = true; //refl not given, no negative information possible.
  }
  return bOk;
}


/**Opposite implementation of checkInit with only idInstanceType. */
bool checkInit_ObjectJc ( ObjectJc* thiz, uint size, uint reflId, uint ident, struct ThreadContext_emC_t* _thCxt) {
  if( (thiz->identSize & mInstanceType_ObjectJc) ==0) {  
    thiz->identSize |= (((uint32)reflId) << kBitInstanceType_ObjectJc) & mInstanceType_ObjectJc;
  } else {
    if(!instanceofReflid_ObjectJc(thiz, reflId)) {
      return false;
    }
  }
  if((thiz->identSize & mSize_ObjectJc) ==0) {
    thiz->identSize = size;  //size is not determined on allocation, store now.
  }
  return (thiz->identSize & mSize_ObjectJc) >= size;  //true if size ==0
}

#ifdef DEF_REFLECTION_NO
bool instanceofReflid_ObjectJc(ObjectJc const* thiz, uint reflId) {
  return ((thiz->identSize & mInstanceType_ObjectJc) >> kBitInstanceType_ObjectJc) == reflId;
}
#endif

#ifdef DEF_REFLECTION_NO
bool checkStrictReflid_ObjectJc ( ObjectJc const* thiz, uint size, uint id_refl, uint ident, struct ThreadContext_emC_t* _thCxt) {
  return ((thiz->identSize & mInstanceType_ObjectJc) >> kBitInstanceType_ObjectJc) == id_refl
    && (thiz->identSize & mInstanceType_ObjectJc) >= size;
}
#endif




ObjectJc* alloc_ObjectJc(int size, struct ClassJc_t const* refl, int id, struct ThreadContext_emC_t* thCxt) {
  ObjectJc* thiz = (ObjectJc*)malloc(size);
  ctor_ObjectJc(thiz, thiz, size, null, id);
  return thiz;
}


#endif
