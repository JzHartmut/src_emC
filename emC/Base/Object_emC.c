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
#include <applstdef_emC.h>
#ifdef DEF_ObjectJc_FULLCAPABILITY
#include <emC/Base/Object_emC.h>
#include <emC/Base/String_emC.h>
 //dependencies:
 //assertJc
 //getCurrent_ThreadContext_emC
 //throw_s0Jc

 //#include "genRefl/emC/Object_emC.crefl"


 //#ifdef DEFINE_debugPRINTF
char const* debugPRINTF[10] = {0};
//#endif



//checkStrict uses capability of instanceof_ObjectJc(...) for all variants.
#ifdef DEF_ObjectJc_LARGESIZE
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
  return (thiz->identSize & mSizeSmall_ObjectJc) >= size;  //true if size ==0, but mSize-bits should be valid.
}
#endif  //def DEF_ObjectJc_LARGESIZE






#ifndef DEF_ObjectJc_REFLREF  //DEF_ObjectJc_SIMPLE is set
bool checkInit_ObjectJc ( ObjectJc* thiz, uint size, struct ClassJc_t const* refl, uint ident) {
  bool bOk = true;
  bool bSetNecessary = false;
  uint idgiven = getIdentInfo_ObjectJc(thiz);  //It is the type-Id.
  uint sizegiven = getSizeInfo_ObjectJc(thiz); //use the get routines, regards LargeSize etc.
  if(sizegiven != 0) { bOk = size <= sizegiven; }
  else { sizegiven = size; bSetNecessary = true; }  //should be set. 
  if(refl !=null) {
    if( idgiven !=0) {
      bOk = bOk && instanceof_ObjectJc(thiz, refl);
    } 
    else { idgiven = refl->idType; bSetNecessary = true;}
  } else {
    //refl == null, then either ident is the idType, or it is 0 for 'no test' or it is any id, not for type.
    if( idgiven !=0) {
      bOk = bOk && (idgiven == ident);
    } 
    else { idgiven = ident; bSetNecessary = true;}
  }
  if( (ident & mArrayId_ObjectJc) && !isArray_ObjectJc(thiz)) {
    idgiven |= mArrayId_ObjectJc; bSetNecessary = true;
  }
  if(bSetNecessary) {
    setSizeAndIdent_ObjectJc(thiz, sizegiven, idgiven); 
  }
  return bOk;
}
#endif



#ifndef DEF_ObjectJc_REFLREF
bool XXXinstanceofReflid_ObjectJc ( ObjectJc const* thiz, uint reflId) {
  return ((thiz->identSize & mIdentSmall_ObjectJc) >> kBitIdentSmall_ObjectJc) == reflId;
}
#endif





#ifndef DEF_ObjectJc_REFLREF
bool XXXcheckStrictReflid_ObjectJc ( ObjectJc const* thiz, uint size, uint id_refl, uint ident, struct ThreadContext_emC_t* _thCxt) {
  return ((thiz->identSize & mIdentSmall_ObjectJc) >> kBitIdentSmall_ObjectJc) == id_refl
    && (thiz->identSize & mSizeSmall_ObjectJc) >= size;
}
#endif


#if defined(DEF_ObjectJcpp_REFLECTION) || defined(DEF_ObjectJc_OWNADDRESS)
ObjectJc* ctor_ObjectJc ( ObjectJc* othiz, void* ptr, uint size, struct ClassJc_t const* refl, uint idObj) {
  memset(othiz, 0, sizeof(ObjectJc));
  setSizeAndIdent_ObjectJc(othiz, size, idObj);
  #ifdef DEF_ObjectJcpp_REFLECTION
    othiz->handleBits = kNoSyncHandles_ObjectJc;
    othiz->offsetToInstanceAddr = (int16)(((MemUnit*)(othiz)) - ((MemUnit*)(ptr)));
  #endif
  othiz->reflection = refl;
  #ifdef DEF_ObjectJc_OWNADDRESS
  othiz->ownAddress = ptr;
  #endif
  return othiz;
}
#endif  //#else  contained in ObjectSimple_emC






#ifdef DEF_ObjectJc_REFLREF
bool checkInit_ObjectJc ( ObjectJc* thiz, uint size, struct ClassJc_t const* clazzReflection, uint ident) {
  if(thiz->reflection ==null) {
    thiz->reflection = clazzReflection; 
  } else if(clazzReflection !=null) {
    if(!instanceof_ObjectJc(thiz, clazzReflection)) { 
      return false;
    }
  }
  uint sizeGiven; 
  if(thiz->identSize ==0) {
    sizeGiven = size;
    setSizeAndIdent_ObjectJc(thiz, size, ident);
  } else {
    sizeGiven = getSizeInfo_ObjectJc(thiz);
    if(ident != 0) { //this ident should always set indepenent of a given ident. 
      setIdent_ObjectJc(thiz, ident);
    }
  }
  return (sizeGiven >= size);  //true if size ==0
}
#endif




#ifndef DEF_ObjectJc_REFLREF //Using a simple ObjectJc





#elif !defined(DEF_REFLECTION_FULL) 

#else //DEF_REFLECTION_FULL  //Note: this feature is not able to use without full reflection support


  char const sign_Vtbl_ObjectJc[] = "sign_Vtbl_ObjectJc";
  char const signEnd_Vtbl_ObjectJc[] = "signEnd_Vtbl_ObjectJc";


const ClassOffset_idxVtblJc1 refl_super_ObjectJc =   //reflection instance for the super class
{ INIZ_ObjectArrayJc(refl_super_ObjectJc, 1, ClassOffset_idxVtblJc, refl_ClassOffset_idxVtblJc, ID_refl_ClassOffset_idxVtblJc)
, { &refl_ObjectJc                                   
, 0 //Index of mtbl of ObjectJc
    //The field which presents the superclass data in inspector access.
  , { "object"              
  , 0 //arraysize
  , &refl_ObjectJc  //type of super                                                                                         
  , kEmbedded_Modifier_reflectJc //hint: embd helps to show the real type.
  | (0<< kBitAccessLevel_Modifier_FieldJc)  //access level
  | (7<< kBitChangeLevel_Modifier_FieldJc)  //never change
  , 0 //offsetalways 0 (C++?)
  , 0  //offsetToObjectifcBase
  , &refl_ObjectJc  
  }
}
};




#endif


/**Initialize. */
ObjectJc const* init_ObjectJc  ( ObjectJc* ythis, int sizeObj, int identObj) {
  //Note: The second ythis should be the real address of the instance in C++. 
  ctor_ObjectJc(ythis, ythis, sizeObj, null, identObj);
  return ythis;
}






#ifdef DEF_ObjectJc_LARGESIZE 
void setSizeAndIdent_ObjectJc(ObjectJc* thiz, int sizeObj, int ident)
{ 

  int identObj;
  if(ident==0) {
    identObj=newIdent_ObjectJc();
  } else { 
    identObj = ident; 
  }
  int identObjTest = ident  & ~mArrayId_ObjectJc; 
  int nrofArrayDimensions = 0;  //unused. The number of array dimensions should be noted in the reflection- FieldJc and in the ObjectArrayJc-data.

  if(identObj < 0 || sizeObj < 0 || nrofArrayDimensions <0 || nrofArrayDimensions > 3)
  { STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW1_s0(RuntimeException, "negativ values for all parameter are unexpected, or nrofArrayDimensions >0", sizeObj);
  }
  else if(sizeObj <= mSizeSmall_ObjectJc && identObj <= (mIdentSmall_ObjectJc >> kBitIdentSmall_ObjectJc))
  { thiz->identSize = sizeObj | kIsSmallSize_ObjectJc | (identObj<<kBitIdentSmall_ObjectJc);
  }
  else if(sizeObj <= mSizeMedium_ObjectJc && identObj <= (mIdentMedium_ObjectJc >> kBitIdentMedium_ObjectJc))
  { thiz->identSize = sizeObj | kIsMediumSize_ObjectJc | (identObj<<kBitIdentMedium_ObjectJc);
  }
  else if(sizeObj <= mSizeLarge_ObjectJc && identObj <= (mIdentLarge_ObjectJc >> kBitIdentLarge_ObjectJc))
  { thiz->identSize = sizeObj | mIsLargeSize_ObjectJc | (identObj<<kBitIdentLarge_ObjectJc);
  }
  else
  { STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW1_s0(RuntimeException, "not matched ident and size", sizeObj);
  }
}
#endif  //DEF_ObjectJc_LARGESIZE 


int newIdent_ObjectJc()
{ //TODO important: Use entry in handle2Ptr for Simulink S-functions and dll
  static int countIdent = 0;  //note: intializing only at startup!
  return ++countIdent;
}


void setIdent_ObjectJc(ObjectJc* thiz, int ident)
{ 
  int identObj;
  if(ident <=0) {
    identObj=newIdent_ObjectJc();
  } else { 
    identObj = ident; 
  }
  int identObjTest = ident  & ~mArrayId_ObjectJc; 
#ifdef DEF_ObjectJc_LARGESIZE 

  int nrofArrayDimensions = 0;  //unused. The number of array dimensions should be noted in the reflection- FieldJc and in the ObjectArrayJc-data.
  int typeSize = thiz->identSize & mSizeBits_ObjectJc;
  if(typeSize == kIsSmallSize_ObjectJc && identObjTest <= (mIdentSmall_ObjectJc >> kBitIdentSmall_ObjectJc))
  { thiz->identSize = thiz->identSize & ~mIdentSmall_ObjectJc   | (identObj<<kBitIdentSmall_ObjectJc);
  }
  else if(typeSize == kIsMediumSize_ObjectJc && identObjTest <= (mIdentMedium_ObjectJc >> kBitIdentMedium_ObjectJc))
  { thiz->identSize = thiz->identSize & ~mIdentMedium_ObjectJc  | (identObj<<kBitIdentMedium_ObjectJc);
  }
  else if( (typeSize & mIsLargeSize_ObjectJc)!=0 && identObjTest <= (mIdentLarge_ObjectJc >> kBitIdentLarge_ObjectJc))
  { thiz->identSize = thiz->identSize & ~mIdentLarge_ObjectJc   | (identObj<<kBitIdentLarge_ObjectJc);
  }
  else
  { STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW_s0(RuntimeException, "not matched ident", identObj, 0);
    STACKTRC_LEAVE;
  }
#else //!DEF_ObjectJc_REFLREF
  if(identObjTest > (mIdentSmall_ObjectJc >> kBitIdentSmall_ObjectJc)) {
    STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW_s0(RuntimeException, "not matched ident", identObj, 0);
    STACKTRC_LEAVE;
  } else {
    thiz->identSize = (thiz->identSize & ~mInstanceType_ObjectJc) | ( ((int32)identObj) << kBitInstanceType_ObjectJc);
  }
#endif  //DEF_ObjectJc_REFLREF 
}





bool checkStrict_OLD_ObjectJc(ObjectJc const* ythis, uint size, struct ClassJc_t const* clazzReflection, int ident, struct ThreadContext_emC_t* _thCxt)
{ uint identObj = getIdentInfo_ObjectJc(ythis);
  STACKTRC_TENTRY("checkConsistence_ObjectJc");
  { //it is initialized, check it
    uint sizeObj = getSizeInfo_ObjectJc(ythis);
    #ifdef DEF_ObjectJc_OWNADDRESS
    if(ythis->ownAddress != ythis) {
      ident = -1;  //marker for faulty.
      THROW_s0(RuntimeException, "faulty ownAddress", (int)(intptr_t)ythis->ownAddress, (int)(intptr_t)ythis);
      return false;
    }
    #endif //DEF_ObjectJc_OWNADDRESS
    if(size != 0 && ((uint)sizeObj) < size) {
      ident = -1;  //marker for faulty.
      THROW_s0(RuntimeException, "faulty size", sizeObj, size);
      return false;
    }
    //
    if(ident != 0 && ident != identObj) {
      THROW_s0(RuntimeException, "faulty ident", identObj, ident);
      return false;
      //identObj = -1;  //marker for faulty.
    }
    //
    #ifdef DEF_ObjectJc_REFLREF
    if(clazzReflection != null && ythis->reflection !=null)
    { 
      #ifdef DEF_NO_StringJcCapabilities
      if(true) {
      #else
      if(!instanceof_s_ObjectJc(ythis, clazzReflection->name)) {
      #endif 
        THROW_s0(RuntimeException, "faulty type", (int)(intptr_t)ythis->reflection, (int)(intptr_t)clazzReflection);
        return false;
      }
    }
    #endif
  }
  STACKTRC_RETURN true; //all ok
}



bool checkInit_OLD_ObjectJc ( ObjectJc* thiz, int size, struct ClassJc_t const* clazzReflection, int ident, ThCxt* _thCxt)
{ bool bOk = true;
  STACKTRC_TENTRY("checkInit_ObjectJc");
  if(thiz->identSize == 0) { //size and ident not initialized
    setSizeAndIdent_ObjectJc(thiz, size, ident);
  }
#ifdef DEF_ObjectJc_REFLREF
  if(thiz->reflection == null) {
    setReflection_ObjectJc(thiz, clazzReflection, 0);
  }
  bOk = checkStrict_ObjectJc(thiz, size, clazzReflection, ident);
#endif //DEF_ObjectJc_REFLREF
  STACKTRC_RETURN bOk;
}






#ifdef DEF_ObjectJc_LARGESIZE  
uint getSizeInfo_ObjectJc(ObjectJc const* ythis)
{ 
  if(ythis->identSize & mIsLargeSize_ObjectJc) 
    return ythis->identSize & mSizeLarge_ObjectJc;
  else if( (ythis->identSize & mSizeBits_ObjectJc) == kIsMediumSize_ObjectJc)
    return ythis->identSize & mSizeMedium_ObjectJc;
  else
    return ythis->identSize & mSizeSmall_ObjectJc;
}
#endif


#ifdef DEF_ObjectJc_LARGESIZE  
uint getIdentInfo_ObjectJc(ObjectJc const* ythis)
{ 
  if(ythis->identSize & mIsLargeSize_ObjectJc) 
    return (ythis->identSize & mIdentLarge_ObjectJc) >>kBitIdentLarge_ObjectJc;
  else if( (ythis->identSize & mSizeBits_ObjectJc) == kIsMediumSize_ObjectJc)
    return (ythis->identSize & mIdentMedium_ObjectJc) >>kBitIdentMedium_ObjectJc;
  else
    return (ythis->identSize & mIdentSmall_ObjectJc) >>kBitIdentSmall_ObjectJc;
}
#endif





#if 0 //defined but not used
static bool checkRefl(ClassJc const* refl, char const* reflectionName)
{ 
  int zReflectionName = strnlen_emC(reflectionName, sizeof(refl->name));  //till 0 or maximal the size of name[] it is not 0-terminated.
  if(refl == null) {
    return false;
  }
  if(refl->object.ownAddress != (ObjectJc const*)refl) { 
    return false;
  }
  if(refl->object.reflection == null) { 
    return false; //The reflection class should have exact Object data.
  }
  if(strncmp(refl->object.reflection->name, "ClassJc", 7) != 0){ 
    return false; //The reflection class should have exact Object data.
  }

  return (strncmp(refl->name, reflectionName, zReflectionName) ==0);
}
#endif



#ifndef DEF_NO_StringJcCapabilities


int getIxVtbl_s_ClassJc(ClassJc const* reflectionObj, char const* reflectionName, int recursive)
{ int idxVtbl = -1;
  STACKTRC_ENTRY("getIdxVtbl_ClassJc");
#ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
  if(reflectionObj == null || reflectionObj->object.reflection == null || strcmp(reflectionObj->object.reflection->name, "ClassJc") !=0){
    THROW_s0(ClassCastException, "reflection class invalid", (int)(intptr_t)reflectionObj, 0);
  }
#endif
  int zReflectionName = strnlen_emC(reflectionName, sizeof(reflectionObj->name));  //till 0 or maximal the size of name[] it is not 0-terminated.
  if(reflectionObj == null)
  { //if no reflection is used, it is able in C++ environment or if no dynamic linked methods are used.
    idxVtbl = -1; //mIdxVtbl_ObjectJc;  //causes an error if it will be used!
  }
  else
  { if(reflectionName == null)  //if no reflection is prescribed:
    { idxVtbl = 0;  //returns the Vtbl_ObjectJc
    }
    //else if(strncmp(reflectionName, "ObjectJc", 8)==0)
    //{ idxVtbl = 0;  //returns the whole Vtbl for the type.
    //}
    else if (strncmp(reflectionObj->name, reflectionName, zReflectionName) == 0) {
      idxVtbl = 0;  //returns the Vtbl for this instance.
    }
  #ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
    else
    { ClassOffset_idxVtblJcARRAY const* reflectionIfc = 
        (ClassOffset_idxVtblJcARRAY const*)reflectionObj->interfaces;
      if( reflectionIfc != null)
      { int idxIfc;
        for(idxIfc = 0; idxVtbl < 0 && idxIfc < reflectionIfc->head.length; idxIfc++)
        { ClassOffset_idxVtblJc const* reflectionChild;
          reflectionChild = &reflectionIfc->data[idxIfc];
          ClassJc const* superType = reflectionChild->superfield.type_;    //A super field is never a primitive, anytime a real pointer to ClassJc 
          if(strncmp(superType->name, reflectionName, zReflectionName)==0) //check via strcmp   
          { idxVtbl = reflectionChild->idxVtbl;
          }
        }
      }
      else
      { idxVtbl = -1;
      }
    }
  #endif
  #ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
    if(idxVtbl < 0 && (reflectionObj->superClass_es) != null) {
      int identSuperClass = ((reflectionObj->superClass_es->identSize & mIdentSmall_ObjectJc)>>kBitIdentSmall_ObjectJc);
      if( identSuperClass == ID_refl_ClassJc) {
        ClassJc const* superType = (ClassJc const*)reflectionObj->superClass_es;
        if(strncmp(superType->name, reflectionName, zReflectionName)==0)
        { idxVtbl = 0;  //not supported, only 0 to show found.
        }
        else
        { //Recursive call because deeper inheritance:
          idxVtbl = getIxVtbl_s_ClassJc(superType, reflectionName, recursive -1);
        }
      } else if(identSuperClass == ID_refl_ClassOffset_idxVtblJc) {
        ClassOffset_idxVtblJcARRAY const* reflectionSuper = (ClassOffset_idxVtblJcARRAY const*)reflectionObj->superClass_es;
        int idxSuper = 0;
        for(idxSuper = 0; idxVtbl < 0 && idxSuper < reflectionSuper->head.length; idxSuper++)
        { ClassOffset_idxVtblJc const* reflectionChild;
          reflectionChild = &reflectionSuper->data[idxSuper];
          ClassJc const* superType = reflectionChild->superfield.type_;    //A super field is never a primitive, anytime a real pointer to ClassJc 
          if(strncmp(superType->name, reflectionName, zReflectionName)==0)
          { idxVtbl = reflectionChild->idxVtbl;
          }
          else
          { //Recursive call because deeper inheritance:
            ClassJc const* superType = reflectionChild->superfield.type_;    //A super field is never a primitive, anytime a real pointer to ClassJc 
            idxVtbl = getIxVtbl_s_ClassJc(superType, reflectionName, recursive -1);
          }
        }
      } else {
        THROW_s0(IllegalStateException, "faulty identSuperClass", identSuperClass, (int)(intPTR)(reflectionObj));
      }
    }
  #endif
    { //search in superclasses and there interfaces
      //old if only 1 superclass:
      //idxVtbl = getIdxVtbl_ClassJc(reflectionObj->superClass, reflectionRef);
    }

  }
  STACKTRC_LEAVE; return(idxVtbl);
}

#endif




#if !defined(DEF_NO_StringJcCapabilities) && defined(DEF_ObjectJc_REFLREF)
//TODO:
bool instanceof_s_ObjectJc(ObjectJc const* ythis, char const* reflectionName)
{ if(ythis == null) return false;
  #ifdef DEF_ClassJc_Vtbl
  int idxVtbl = getIxVtbl_s_ClassJc(ythis->reflection, reflectionName, 20);
  return idxVtbl >=0;
  #else
    //TODO !!
    return true;
  #endif

}
#endif





ObjectJc* clone_ObjectJc_F(ObjectJc const* ythis, MemC buffer)
{
  return null;
}

bool equals_ObjectJc_F(ObjectJc const* ythis, ObjectJc const* cmp, ThCxt* _thCxt)
{
  return false;
}

void finalize_ObjectJc_F(ObjectJc const* ythis, ThCxt* _thCxt)
{
}

int32 hashCode_ObjectJc_F(ObjectJc const* ythis, ThCxt* _thCxt)
{
  return 0;
}

StringJc toString_ObjectJc_F(ObjectJc const* ythis, ThCxt* _thCxt)
{ //StringBuffer* ss = StringBuffer::new_();
  //ss->append("Object at @").append(Integer::toHexString((int)(this)));
  StringJc ss = CONST_StringJc("No information", 14); //only constant
  return ss;   //return by value, that is 2 words (8 Byte).
}






#ifdef DEF_ClassJc_Vtbl   //TODO create variant without Reflection but with ixVtbl
VtblHeadJc const* getVtbl_ObjectJc(ObjectJc const* ythis, char const* sign)
{ VtblHeadJc const* head = null; //nullpointer-return possible
  ClassJc const* reflection;
  STACKTRC_ENTRY("getVtbl_ObjectJc");
  #ifdef DEF_ObjectJc_OWNADDRESS
  if(ythis->ownAddress != ythis){ 
    THROW1_s0(IllegalArgumentException, "Object head faulty", (int)(intptr_t)ythis);
    STACKTRC_LEAVE; return null;  //The null pointer may be tested outside, or it should cause an exception outside if it is unexpected.
  }
  #endif
  reflection = ythis->reflection;
  if( reflection != null) { 
  if(reflection->object.reflection != &refl_ClassJc){
    THROW1_s0(IllegalArgumentException, "Object reflection faulty", (int)(intptr_t)ythis);
    STACKTRC_LEAVE; return null;  //The null pointer may be tested outside, or it should cause an exception outside if it is unexpected.
  }
  head = ythis->reflection->mtbl;  
  if(head != null)//nullpointer exception outside possible.
  {
    while(  head->sign != sign 
      && head->sign != signEnd_Vtbl_ObjectJc 
      )
    { int sizeTable = (int)(intptr_t)(head->sizeTable);
    if(sizeTable < 0 || sizeTable > (302 * sizeof(void*))) {
      THROW1_s0(IllegalStateException, "Internal error, Vtbl faulty, searched:", (int)(intptr_t)sign);
    }   
    //ASSERT_emC(sizeTable >0 && sizeTable < (302 * sizeof(void*)));  //no more as 300 virtual methods per class, detect false content and step forward!
    //The next part of method table is found after the current.
    head = (VtblHeadJc const*)( (MemUnit*)head + sizeTable );
    }
    if(head->sign == signEnd_Vtbl_ObjectJc){
      THROW1_s0(ClassCastException, "baseclass not found", (int)(intptr_t)sign);
      head = null;  //The null pointer may be tested outside, or it should cause an exception outside if it is unexpected.
    } } }
  STACKTRC_LEAVE; return head;
}



//TODO create variant without Reflection but with ixVtbl
int getPosInVtbl_ObjectJc(ObjectJc const* thiz, char const* sign)
{ VtblHeadJc const* headSign = getVtbl_ObjectJc(thiz, sign);
  if(headSign !=null){
    VtblHeadJc const* headBase = thiz->reflection->mtbl;
    return OFFSET_MemUnit(headBase, headSign) / (int)sizeof(sign);
  } 
  else return -1;  //no Vtbl found.
}



VtblHeadJc const* checkVtblError_ObjectJc(ObjectJc const* ythis, int error, ThCxt* _thCxt)
{ 
  switch(error) {
  case 1: THROW1_s0(IllegalArgumentException, "checkVtbl_ObjectJc: Object reflection faulty", (int)(intptr_t)ythis); break;
  case 2: THROW1_s0(IllegalArgumentException, "checkVtbl_ObjectJc: Vtbl not given", (int)(intptr_t)ythis); break;
  case 3: THROW1_s0(IllegalArgumentException, "checkVtbl_ObjectJc: faulty index to Vtbl", (int)(intptr_t)ythis); break;
  default: THROW1_s0(IllegalArgumentException, "checkVtbl_ObjectJc: unknown error", (int)(intptr_t)ythis);
  }
  return null;
}




/**calculates the index insided the jumptable of a dynamic call,
* regarding the type of reference and the type of the instance.
* @param reflectionObj The reflection of the referenced instance.
* @param reflectionRef The reflection of the reference. It should be the same as reflectionObj
*        or it should be found as a superclass or interface of the reflectionObj.
*        This param is only used with its pointer value, no access to the referenced memory location will be done.
* @return The index of the part of jumptable of the reference inside the jump table of the object.
*         * It is 0, if reflectionObj == reflectionRef, it means the reference is from the same type as the Object.
*         * It is mIdxVtbl_ObjectJc if reflectionObj is null. This case is possible if the Object has no reflection infos.
*           If the index with this value is used as an index of jumptable, an exception occurs.
*           But if it is not used, it is a valid case, especially if no dynamic linked call occurs.
*/
//this is the older form, not able to use for reflection in divided dll files such as in Simulink-mex-files.
//The problem is, there are different instantiations of the reflection data in several dll.
//The better solution is getIxVtbl_s_ClassJc(...) which compares the names of the reflection. 
//but this is faster!

int getIdxVtbl_ClassJc(ClassJc const* reflectionObj, ClassJc const* reflectionRef)
{ int idxVtbl = -1;
  STACKTRC_ENTRY("getIdxVtbl_ClassJc");
  if(reflectionObj == null)
  { //if no reflection is used, it is able in C++ environment or if no dynamic linked methods are used.
    idxVtbl = -1; //mIdxVtbl_ObjectJc;  //causes an error if it will be used!
  }
  else
  { if(reflectionRef == null)  //if no reflection is prescribed:
    { idxVtbl = 0;  //returns the Vtbl_ObjectJc
    }
    else if(reflectionRef == reflectionObj)
    { idxVtbl = 0;  //returns the whole Vtbl for the type.
    }
  #ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
    else
    { ClassOffset_idxVtblJcARRAY const* reflectionIfc = 
      (ClassOffset_idxVtblJcARRAY const*)reflectionObj->interfaces;
      if( reflectionIfc != null)
      { int idxIfc;
        for(idxIfc = 0; idxVtbl < 0 && idxIfc < reflectionIfc->head.length; idxIfc++)
        { ClassOffset_idxVtblJc const* reflectionChild;
          reflectionChild = &reflectionIfc->data[idxIfc];
          ClassJc const* superType = reflectionChild->superfield.type_;    //A super field is never a primitive, anytime a real pointer to ClassJc 
          if(superType == reflectionRef)
          { idxVtbl = reflectionChild->idxVtbl;
          }
        }
      }
      else
      { idxVtbl = -1;
      }
    }
  #endif
  #ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
    if(idxVtbl < 0 && (reflectionObj->superClass_es) != null) { 
      int identSuperClass = ((reflectionObj->superClass_es->identSize & mIdentSmall_ObjectJc)>>kBitIdentSmall_ObjectJc);
      if( identSuperClass == ID_refl_ClassJc) {
        ClassJc const* superType = C_CAST(ClassJc const*,reflectionObj->superClass_es);
        if(superType == reflectionRef)
        { idxVtbl = 0;  //not supported, show only found type
        }
        else
        { //Recursive call because deeper inheritance:
          idxVtbl = getIdxVtbl_ClassJc(superType, reflectionRef);
        }
      } else if(identSuperClass == ID_refl_ClassOffset_idxVtblJc) {
        ClassOffset_idxVtblJcARRAY const* reflectionSuper = C_CAST(ClassOffset_idxVtblJcARRAY const*, reflectionObj->superClass_es);
        int idxSuper = 0;
        for(idxSuper = 0; idxVtbl < 0 && idxSuper < reflectionSuper->head.length; idxSuper++)
        { ClassOffset_idxVtblJc const* reflectionChild;
          reflectionChild = &reflectionSuper->data[idxSuper];
          ClassJc const* superType = reflectionChild->superfield.type_;    //A super field is never a primitive, anytime a real pointer to ClassJc 
          if(superType == reflectionRef)
          { idxVtbl = reflectionChild->idxVtbl;
          }
          else
          { //Recursive call because deeper inheritance:
            ClassJc const* superType = reflectionChild->superfield.type_;    //A super field is never a primitive, anytime a real pointer to ClassJc 
            idxVtbl = getIdxVtbl_ClassJc(superType, reflectionRef);
          }
        }
      } else {
        THROW_s0(IllegalStateException, "faulty identSuperClass", identSuperClass, (int)(intPTR)(reflectionObj));
      }
    }
  #endif
    { //search in superclasses and there interfaces
      //old if only 1 superclass:
      //idxVtbl = getIdxVtbl_ClassJc(reflectionObj->superClass, reflectionRef);
    }

  }
  STACKTRC_LEAVE; return(idxVtbl);
}


bool instanceof_ObjectJc ( ObjectJc const* ythis, struct ClassJc_t const* reflection)
{ 
  int idxVtbl = getIdxVtbl_ClassJc(ythis->reflection, reflection);
  return idxVtbl >=0;
}





  #ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
  /*J2C: dynamic call variant of the override-able method: */
  StringJc toString_ObjectJc ( ObjectJc const* ithis, ThCxt* _thCxt)
  { Vtbl_ObjectJc const* mtbl = (Vtbl_ObjectJc const*)getVtbl_ObjectJc(ithis, sign_Vtbl_ObjectJc);
    return mtbl->toString(ithis, _thCxt);
  }
  #endif


#else //not DEF_ClassJc_Vtbl



  #ifdef DEF_REFLECTION_FULL
  static bool instanceofSuper_ClassJc ( ClassJc const* thiz
    , struct ClassJc_t const* reflection, int recursive) {
    if(recursive <0) return false;
    bool reflOk = false;
    struct ClassOffset_idxVtblJcARRAY_t const* superClasses = thiz->superClasses;
    if(superClasses !=null) {
      for(int ix = 0; ix < superClasses->head.length; ++ix) {
        ClassJc const* superType = superClasses->data[ix].superfield.type_;
        reflOk = superType == reflection;
        if(!reflOk) {
          reflOk = instanceofSuper_ClassJc(superType, reflection, --recursive);
        }
        if(reflOk) { break; }
      }
    }
    if(!reflOk && thiz->interfaces !=null) {
      superClasses = thiz->interfaces;
      for(int ix = 0; ix < superClasses->head.length; ++ix) {
        ClassJc const* superType = superClasses->data[ix].superfield.type_;
        reflOk = superType == reflection;
        if(!reflOk) {
          reflOk = instanceofSuper_ClassJc(superType, reflection, --recursive);
        }
        if(reflOk) { break; }
      }
    }
    return  reflOk;
  }
  #endif


  #ifdef DEF_REFLECTION_FULL
  //Then the instanceof should use another algorithm, only single inheritance.
  bool instanceof_ObjectJc ( ObjectJc const* thiz, struct ClassJc_t const* reflection) {
    bool reflOk = reflection == null; //true if the argument is null, special case 
    if(!reflOk) {
      #if defined (DEF_ObjectJc_SIMPLE)
        //The mInstanceType_ObjectJc have to be contain the same type Id as in reflection.
        //An instance Id is not possible for minimal ObjectJc
        uint idType = getIdentInfo_ObjectJc(thiz);
        ClassJc const* refl1 = reflection;
        reflOk = (refl1->idType == idType);  //It is not possible to detect a superclass type! 
      #elif defined(DEF_REFLECTION_FULL)
        if(reflection != null) {
          reflOk = thiz->reflection == reflection;
          if(!reflOk && thiz->reflection !=null) {
            reflOk = instanceofSuper_ClassJc(thiz->reflection, reflection, 10);
          }
        }
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
  #endif //DEF_REFLECTION_FULL

#endif  //not DEF_ClassJc_Vtbl



void init_immediate_ObjectArrayJc(ObjectArrayJc* thiz, int nrofElements, int sizeElement, ClassJc const* refl_Elem, int idObj) {
  iniz_ObjectJc(&thiz->object, thiz, sizeof(ObjectArrayJc) + nrofElements * sizeElement, refl_Elem, idObj);
  thiz->length = nrofElements;
  thiz->sizeElement = sizeElement;
  thiz->mode = 1 << kBitDimension_ObjectArrayJc;
}


#ifndef DEF_NO_StringJcCapabilities
StringJc name_ClassJc(ClassJc const* thiz) {
  int zz = strnlen_emC(thiz->name, sizeof(thiz->name));  //at leas the length of buffer
  return zI_StringJc(thiz->name, zz);
}
#endif


#ifndef DEF_REFLECTION_FULL
ClassJc const refl_ClassJc = INIZ_ClassJc(refl_ClassJc, "ClassJc");
#endif

#ifdef DEF_REFLECTION_FULL 
StringJc name_FieldJc(FieldJc const* thiz) {
  int zz = strnlen_emC(thiz->name, sizeof(thiz->name));  //at leas the length of buffer
  return zI_StringJc(thiz->name, zz);
}
#endif

#include "emC/Base/SystemInit_emC.h"

SystemInit_emC _systemInit_emC_ = { 0 };

SystemInit_emC* systemInit_emC = &_systemInit_emC_;

#endif //DEF_ObjectJc_SIMPLE
