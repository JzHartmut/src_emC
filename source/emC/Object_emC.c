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
#include <emC/Object_emC.h>
#include <emC/String_emC.h>
#include <stdio.h>
//dependencies:
//assertJc
//getCurrent_ThreadContext_emC
//throw_s0Jc

//#ifdef DEFINE_debugPRINTF
char const* debugPRINTF[10] = {0};
//#endif
#include <string.h> //memset



char const sign_Mtbl_ObjectJc[] = "sign_Mtbl_ObjectJc";
char const signEnd_Mtbl_ObjectJc[] = "signEnd_Mtbl_ObjectJc";


/**Initialize. */
ObjectJc* init_ObjectJc(ObjectJc* ythis, int sizeObj, int identObj)
{ STACKTRC_ENTRY("init_ObjectJc");
  ASSERTJc_IF(sizeObj >= sizeof(ObjectJc))
  { //cc2016-10 memset(ythis, 0, sizeObj);  //don't clear the instance because some references etc. maybe initalized with { ... }
    ythis->ownAddress = ythis;
    ythis->state.b.idSyncHandles = kNoSyncHandles_ObjectJc;
    setSizeAndIdent_ObjectJc(ythis, sizeObj, identObj);
  }
  STACKTRC_LEAVE; return ythis;
}



ObjectJc* initReflection_ObjectJc(ObjectJc* ythis, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj)
{ STACKTRC_ENTRY("initReflection_ObjectJc");
  ythis->ownAddress = ythis;
  ythis->state.b.idSyncHandles = kNoSyncHandles_ObjectJc;
  setSizeAndIdent_ObjectJc(ythis, sizeObj, identObj);
  ythis->state.b.offsetToStartAddr = (int16)(((MemUnit*)(ythis)) - ((MemUnit*)(addrInstance)));
  ythis->reflectionClass = reflection; //may be null.
  STACKTRC_LEAVE; return ythis;
}


void setReflection_ObjectJc(ObjectJc* ythis, struct ClassJc_t const* reflection,  int32 typeInstanceSizeIdent)
{ ythis->reflectionClass = reflection;
  if(typeInstanceSizeIdent != -1)
  { if(ythis->state.b.objectIdentSize == 0){ ythis->state.b.objectIdentSize = typeInstanceSizeIdent; }
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
    THROW1_s0(RuntimeException, "negativ values for all parameter are unexpected, or nrofArrayDimensions >0", sizeObj);
  }
  else if(sizeObj <= mSizeSmall_objectIdentSize_ObjectJc && identObj <= (mTypeSmall_objectIdentSize_ObjectJc >> kBitTypeSmall_objectIdentSize_ObjectJc))
  { ythis->state.b.objectIdentSize = sizeObj | kIsSmallSize_objectIdentSize_ObjectJc | (identObj<<kBitTypeSmall_objectIdentSize_ObjectJc);
  }
  else if(sizeObj <= mSizeMedium_objectIdentSize_ObjectJc && identObj <= (mTypeMedium_objectIdentSize_ObjectJc >> kBitTypeMedium_objectIdentSize_ObjectJc))
  { ythis->state.b.objectIdentSize = sizeObj | kIsMediumSize_objectIdentSize_ObjectJc | (identObj<<kBitTypeMedium_objectIdentSize_ObjectJc);
  }
  else if(sizeObj <= mSizeLarge_objectIdentSize_ObjectJc && identObj <= (mTypeLarge_objectIdentSize_ObjectJc >> kBitTypeLarge_objectIdentSize_ObjectJc))
  { ythis->state.b.objectIdentSize = sizeObj | mIsLargeSize_objectIdentSize_ObjectJc | (identObj<<kBitTypeLarge_objectIdentSize_ObjectJc);
  }
  else
  { STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW1_s0(RuntimeException, "not matched ident and size", sizeObj);
  }
}


int newIdent_ObjectJc()
{
  static int countIdent = 0;  //note: intializing only at startup!
  return ++countIdent;
}





char const* checkStrict_ObjectJc(ObjectJc const* ythis, int size, int ident, struct ClassJc_t const* clazzReflection, struct ThreadContext_emC_t* _thCxt)
{ int identObj = getIdentInfo_ObjectJc(ythis);
  STACKTRC_TENTRY("checkConsistence_ObjectJc");
  { //it is initialized, check it
    int sizeObj = getSizeInfo_ObjectJc(ythis);
    if(ythis->ownAddress != ythis) {
      ident = -1;  //marker for faulty.
      return "faulty ownAddress";
    }
    if(size != 0 && sizeObj < size) {
      ident = -1;  //marker for faulty.
      return "faulty size";
    }
    //
    if(ident != 0 && ident != identObj) {
      identObj = -1;  //marker for faulty.
      return "faulty ident";
    }
    //
    if(clazzReflection != null && ythis->reflectionClass !=null)
    { if(!instanceof_s_ObjectJc(ythis, clazzReflection->name)) {
        return "faulty type";
      }
    }
  }
  STACKTRC_RETURN null; //all ok
}



char const* checkInit_ObjectJc(ObjectJc* thiz, int size, int ident, struct ClassJc_t const* clazzReflection, ThCxt* _thCxt)
{ bool bOk;
  STACKTRC_TENTRY("checkInit_ObjectJc");
  if(thiz->ownAddress == null && thiz->state.b.objectIdentSize == 0)
  { //not initialized
    init_ObjectJc(thiz, size, ident);   //TODO ident=0? 
  }
  //int ident = getIdentInfo_ObjectJc(thiz);
  //if(ident == 0 || ident == )
  if(thiz->state.b.objectIdentSize == 0) { //size and ident not initialized
    setSizeAndIdent_ObjectJc(thiz, size, ident);
  }
  if(thiz->reflectionClass == null) {
    setReflection_ObjectJc(thiz, clazzReflection, 0);
  }
  STACKTRC_RETURN checkStrict_ObjectJc(thiz, size, ident, clazzReflection,_thCxt);
}







int getSizeInfo_ObjectJc(ObjectJc const* ythis)
{ if(ythis->state.b.objectIdentSize & mIsLargeSize_objectIdentSize_ObjectJc) 
    return ythis->state.b.objectIdentSize & mSizeLarge_objectIdentSize_ObjectJc;
  else if( (ythis->state.b.objectIdentSize & mSizeBits_objectIdentSize_ObjectJc) == kIsMediumSize_objectIdentSize_ObjectJc)
    return ythis->state.b.objectIdentSize & mSizeMedium_objectIdentSize_ObjectJc;
  else
    return ythis->state.b.objectIdentSize & mSizeSmall_objectIdentSize_ObjectJc;
}

int getIdentInfo_ObjectJc(ObjectJc const* ythis)
{ if(ythis->state.b.objectIdentSize & mIsLargeSize_objectIdentSize_ObjectJc) 
    return (ythis->state.b.objectIdentSize & mTypeLarge_objectIdentSize_ObjectJc) >>kBitTypeLarge_objectIdentSize_ObjectJc;
  else if( (ythis->state.b.objectIdentSize & mSizeBits_objectIdentSize_ObjectJc) == kIsMediumSize_objectIdentSize_ObjectJc)
    return (ythis->state.b.objectIdentSize & mTypeMedium_objectIdentSize_ObjectJc) >>kBitTypeMedium_objectIdentSize_ObjectJc;
  else
    return (ythis->state.b.objectIdentSize & mTypeSmall_objectIdentSize_ObjectJc) >>kBitTypeSmall_objectIdentSize_ObjectJc;
}




static bool checkRefl(ClassJc const* refl, char const* reflectionName)
{ 
  int zReflectionName = strnlen_emC(reflectionName, sizeof(refl->name));  //till 0 or maximal the size of name[] it is not 0-terminated.
  if(refl == null) {
    return false;
  }
  if(refl->object.ownAddress != (ObjectJc const*)refl) { 
    return false;
  }
  if(refl->object.reflectionClass == null) { 
    return false; //The reflection class should have exact Object data.
  }
  if(strncmp(refl->object.reflectionClass->name, "ClassJc", 7) != 0){ 
    return false; //The reflection class should have exact Object data.
  }

  return (strncmp(refl->name, reflectionName, zReflectionName) ==0);
}




int getIdxMtbl_s_ClassJc(ClassJc const* reflectionObj, char const* reflectionName)
{ int idxMtbl = -1;
  ClassOffset_idxMtblJcARRAY const* reflectionSuper;
  int zReflectionName = strnlen_emC(reflectionName, sizeof(reflectionObj->name));  //till 0 or maximal the size of name[] it is not 0-terminated.
  STACKTRC_ENTRY("getIdxMtbl_ClassJc");
  if(reflectionObj == null)
  { //if no reflection is used, it is able in C++ environment or if no dynamic linked methods are used.
    idxMtbl = -1; //mIdxMtbl_ObjectJc;  //causes an error if it will be used!
  }
  else
  { if(reflectionName == null)  //if no reflection is prescribed:
    { idxMtbl = 0;  //returns the Mtbl_ObjectJc
    }
    //else if(strncmp(reflectionName, "ObjectJc", 8)==0)
    //{ idxMtbl = 0;  //returns the whole Mtbl for the type.
    //}
    else if (strncmp(reflectionObj->name, reflectionName, zReflectionName) == 0) {
      idxMtbl = 0;  //returns the Mtbl for this instance.
    }
    else
    { ClassOffset_idxMtblJcARRAY const* reflectionIfc = 
        (ClassOffset_idxMtblJcARRAY const*)reflectionObj->interfaces;
      if( reflectionIfc != null)
      { int idxIfc;
        for(idxIfc = 0; idxMtbl < 0 && idxIfc < reflectionIfc->head.length; idxIfc++)
        { ClassOffset_idxMtblJc const* reflectionChild;
          reflectionChild = &reflectionIfc->data[idxIfc];
          if(strncmp(reflectionChild->clazz->name, reflectionName, zReflectionName)==0)
          { idxMtbl = reflectionChild->idxMtbl;
          }
        }
      }
      else
      { idxMtbl = -1;
      }
    }
    if(idxMtbl < 0 && (reflectionSuper = reflectionObj->superClasses) != null)
    { int idxSuper = 0;
      for(idxSuper = 0; idxMtbl < 0 && idxSuper < reflectionSuper->head.length; idxSuper++)
      { ClassOffset_idxMtblJc const* reflectionChild;
        reflectionChild = &reflectionSuper->data[idxSuper];
        if(strncmp(reflectionChild->clazz->name, reflectionName, zReflectionName)==0)
        { idxMtbl = reflectionChild->idxMtbl;
        }
        else
        { //Recursive call because deeper inheritance:
          idxMtbl = getIdxMtbl_s_ClassJc(reflectionChild->clazz, reflectionName);
        }
      }
    }
    { //search in superclasses and there interfaces
      //old if only 1 superclass:
      //idxMtbl = getIdxMtbl_ClassJc(reflectionObj->superClass, reflectionRef);
    }

  }
  STACKTRC_LEAVE; return(idxMtbl);
}







bool instanceof_s_ObjectJc(ObjectJc const* ythis, char const* reflectionName)
{ 
  int idxMtbl = getIdxMtbl_s_ClassJc(ythis->reflectionClass, reflectionName);
  return idxMtbl >=0;
}




struct ClassJc_t const* getClass_ObjectJc(ObjectJc const* ythis)
{ return ythis->reflectionClass;//->theClass;
}



ObjectJc* clone_ObjectJc_F(ObjectJc const* ythis, MemC buffer)
{
  return null;
}

bool equals_ObjectJc_F(ObjectJc* ythis, ObjectJc* cmp, ThCxt* _thCxt)
{
  return false;
}

void finalize_ObjectJc_F(ObjectJc* ythis, ThCxt* _thCxt)
{
}

int32 hashCode_ObjectJc_F(ObjectJc const* ythis, ThCxt* _thCxt)
{
  return 0;
}

StringJc toString_ObjectJc_F(ObjectJc* ythis, ThCxt* _thCxt)
{ //StringBuffer* ss = StringBuffer::new_();
  //ss->append("Object at @").append(Integer::toHexString((int)(this)));
  StringJc ss = CONST_StringJc("No information", 14); //only constant
  return ss;   //return by value, that is 2 words (8 Byte).
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




void init_immediate_ObjectArrayJc(ObjectArrayJc* thiz, int nrofElements, int sizeElement, ClassJc const* refl_Elem, int idObj) {
  initReflection_ObjectJc(&thiz->object, thiz, sizeof(ObjectArrayJc) + nrofElements * sizeElement, refl_Elem, idObj);
  thiz->length = nrofElements;
  thiz->sizeElement = sizeElement;
  thiz->mode = 1 << kBitDimension_ObjectArrayJc;
}


