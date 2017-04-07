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
 * @content implementation of base routines of ObjectJc
 *
 * @author Hartmut Schorrig www.vishia.org
 * @version 0.82
 * list of changes:
 * 2009-06-24: Hartmut creation, dissolved from ObjectJc.c
 *
 ****************************************************************************/
#include <Fwc/objectBaseC.h>
//dependencies:
//assertJc
//getCurrent_ThreadContextFW
//throw_s0Jc

#include <string.h> //memset

/**Initialize. */
ObjectJc* init_ObjectJc(ObjectJc* ythis, int sizeObj, int identObj)
{ STACKTRC_ENTRY("init_ObjectJc");
  ASSERT_Fwc(sizeObj >= sizeof(ObjectJc));
  //cc2016-10 memset(ythis, 0, sizeObj);  //don't clear the instance because some references etc. maybe initalized with { ... }
  ythis->ownAddress = ythis;
  ythis->idSyncHandles = kNoSyncHandles_ObjectJc;
  setSizeAndIdent_ObjectJc(ythis, sizeObj, identObj);
  STACKTRC_LEAVE; return ythis;
}



ObjectJc* initReflection_ObjectJc(ObjectJc* ythis, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj)
{ STACKTRC_ENTRY("initReflection_ObjectJc");
  ythis->ownAddress = ythis;
  ythis->idSyncHandles = kNoSyncHandles_ObjectJc;
  setSizeAndIdent_ObjectJc(ythis, sizeObj, identObj);
  ythis->offsetToStartAddr = (int16)(((MemUnit*)(ythis)) - ((MemUnit*)(addrInstance)));
  ythis->reflectionClass = reflection; //may be null.
  STACKTRC_LEAVE; return ythis;
}


void setReflection_ObjectJc(ObjectJc* ythis, struct ClassJc_t const* reflection,  int32 typeInstanceSizeIdent)
{ ythis->reflectionClass = reflection;
  if(typeInstanceSizeIdent != -1)
  { if(ythis->objectIdentSize == 0){ ythis->objectIdentSize = typeInstanceSizeIdent; }
    else
    { //TODO setIdent_ObjectJc(typeInstanceSizeIdent);
    }
  }
}


void setSizeAndIdent_ObjectJc(ObjectJc* ythis, int sizeObj, int identAndMaskObj)
{ int identObj =identAndMaskObj & ~(mArray_objectIdentSize_ObjectJc | mSizeBits_objectIdentSize_ObjectJc);
  int nrofArrayDimensions = 0;  //unused. The number of array dimensions should be noted in the reflection- FieldJc and in the ObjectArrayJc-data.

  if(identObj < 0 || sizeObj < 0 || nrofArrayDimensions <0 || nrofArrayDimensions > 3)
  { STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW_s0(RuntimeException, "negativ values for all parameter are unexpected, or nrofArrayDimensions >0", sizeObj);
  }
  else if(sizeObj <= mSizeSmall_objectIdentSize_ObjectJc && identObj <= (mTypeSmall_objectIdentSize_ObjectJc >> kBitTypeSmall_objectIdentSize_ObjectJc))
  { ythis->objectIdentSize = sizeObj | kIsSmallSize_objectIdentSize_ObjectJc | (identObj<<kBitTypeSmall_objectIdentSize_ObjectJc);
  }
  else if(sizeObj <= mSizeMedium_objectIdentSize_ObjectJc && identObj <= (mTypeMedium_objectIdentSize_ObjectJc >> kBitTypeMedium_objectIdentSize_ObjectJc))
  { ythis->objectIdentSize = sizeObj | kIsMediumSize_objectIdentSize_ObjectJc | (identObj<<kBitTypeMedium_objectIdentSize_ObjectJc);
  }
  else if(sizeObj <= mSizeLarge_objectIdentSize_ObjectJc && identObj <= (mTypeLarge_objectIdentSize_ObjectJc >> kBitTypeLarge_objectIdentSize_ObjectJc))
  { ythis->objectIdentSize = sizeObj | mIsLargeSize_objectIdentSize_ObjectJc | (identObj<<kBitTypeLarge_objectIdentSize_ObjectJc);
  }
  else
  { STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW_s0(RuntimeException, "not matched ident and size", sizeObj);
  }
}


int newIdent_ObjectJc()
{
  static int countIdent = 0;  //note: intializing only at startup!
  return ++countIdent;
}





int checkStrict_ObjectJc(ObjectJc const* ythis, int size, int ident, struct ClassJc_t const* clazzReflection, ThCxt* _thCxt)
{ int identObj = getIdentInfo_ObjectJc(ythis);
  STACKTRC_TENTRY("checkConsistence_ObjectJc");
  { //it is initialized, check it
    int sizeObj = getSizeInfo_ObjectJc(ythis);
    if(ythis->ownAddress != ythis) {
      ident = -1;  //marker for faulty.
      THROW_s0(IllegalArgumentException, "faut ownAddress", (int)ythis->ownAddress);
    }
    if(size != 0 && sizeObj < size) {
      ident = -1;  //marker for faulty.
      THROW_s0(IllegalArgumentException, "faut size", sizeObj);
    }
    //
    if(ident != 0 && ident != identObj) {
      identObj = -1;  //marker for faulty.
      THROW_s0(IllegalArgumentException, "faut ident", identObj);
    }
    //
    if(clazzReflection != null)
    { if(ythis->reflectionClass == null)
      { //ythis->reflectionClass = clazzReflection;
      }
      else
      { //TODO test Reflection, it can be a derived class.
      }
    }
  }
  STACKTRC_LEAVE;
  return identObj;
}



int checkOrInit_ObjectJc(ObjectJc* thiz, int size, int ident, struct ClassJc_t const* clazzReflection, ThCxt* _thCxt)
{ int identObj;
  STACKTRC_TENTRY("checkConsistence_ObjectJc");
  if(thiz->ownAddress == null && thiz->objectIdentSize == 0)
  { //not initialized
    init_ObjectJc(thiz, size, ident);   //TODO ident=0? 
    setReflection_ObjectJc(thiz, clazzReflection, 0);
    identObj = ident;
  }
  else
  { if(thiz->objectIdentSize == 0)
    { //size and ident not initialized
      setSizeAndIdent_ObjectJc(thiz, size, ident);
  }
    if(thiz->reflectionClass == null) {
      setReflection_ObjectJc(thiz, clazzReflection, 0);
    }
    identObj = checkStrict_ObjectJc(thiz, size, ident, clazzReflection,_thCxt);
  }
  STACKTRC_LEAVE; return identObj;
}







int getSizeInfo_ObjectJc(ObjectJc const* ythis)
{ if(ythis->objectIdentSize & mIsLargeSize_objectIdentSize_ObjectJc) 
    return ythis->objectIdentSize & mSizeLarge_objectIdentSize_ObjectJc;
  else if( (ythis->objectIdentSize & mSizeBits_objectIdentSize_ObjectJc) == kIsMediumSize_objectIdentSize_ObjectJc)
    return ythis->objectIdentSize & mSizeMedium_objectIdentSize_ObjectJc;
  else
    return ythis->objectIdentSize & mSizeSmall_objectIdentSize_ObjectJc;
}

int getIdentInfo_ObjectJc(ObjectJc const* ythis)
{ if(ythis->objectIdentSize & mIsLargeSize_objectIdentSize_ObjectJc) 
    return (ythis->objectIdentSize & mTypeLarge_objectIdentSize_ObjectJc) >>kBitTypeLarge_objectIdentSize_ObjectJc;
  else if( (ythis->objectIdentSize & mSizeBits_objectIdentSize_ObjectJc) == kIsMediumSize_objectIdentSize_ObjectJc)
    return (ythis->objectIdentSize & mTypeMedium_objectIdentSize_ObjectJc) >>kBitTypeMedium_objectIdentSize_ObjectJc;
  else
    return (ythis->objectIdentSize & mTypeSmall_objectIdentSize_ObjectJc) >>kBitTypeSmall_objectIdentSize_ObjectJc;
}






struct ClassJc_t const* getClass_ObjectJc(ObjectJc const* ythis)
{ return ythis->reflectionClass;//->theClass;
}






#if defined(__CPLUSGEN) && defined(__cplusplus)
  ObjectifcBaseJcpp::ObjectifcBaseJcpp()
  : significance_ObjectifcBase(kSignificance_ObjectifcBase)
  //, significanceAddress_ObjectifcBase(this)  NOTE: note possible because this is not accessible here! 
  { //NOTE the significanceAddress_ObjectifcBase is const void* to prevent change outside,
    //     but it can't set in constructor list with this.
    *(void**)(&significanceAddress_ObjectifcBase) = this;
  }
#endif //__CPLUSGEN

