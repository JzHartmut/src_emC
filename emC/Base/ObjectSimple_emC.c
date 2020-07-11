#include <applstdef_emC.h>
#ifdef DEF_ObjectJc_SIMPLEST
#include <stdlib.h>


void inizReflid_ObjectJc(ObjectJc* thiz, void* ptr, int size, uint id_refl, uint idObj){
  thiz->identSize = (((int32)id_refl)<<16) + size;
}


/**Opposite implementation of checkInit with only idInstanceType. */
bool checkInitReflid_ObjectJc ( ObjectJc* thiz, uint size, uint reflId, uint ident, struct ThreadContext_emC_t* _thCxt) {
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

bool instanceofReflid_ObjectJc(ObjectJc const* thiz, uint reflId) {
  return ((thiz->identSize & mInstanceType_ObjectJc) >> kBitInstanceType_ObjectJc) == reflId;
}


bool checkStrictReflid_ObjectJc ( ObjectJc const* thiz, uint size, uint id_refl, uint ident, struct ThreadContext_emC_t* _thCxt) {
  return ((thiz->identSize & mInstanceType_ObjectJc) >> kBitInstanceType_ObjectJc) == id_refl
    && (thiz->identSize & mInstanceType_ObjectJc) >= size;
}





ObjectJc* alloc_ObjectJc(int size, int id, struct ThreadContext_emC_t* thCxt) {
  ObjectJc* thiz = (ObjectJc*)malloc(size);
  inizReflid_ObjectJc(thiz, thiz, size, id, id);
  return thiz;
}
#endif
