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
#include <emC/Base/Object_emC.h>
#include <emC/Base/String_emC.h>

#ifdef DEF_ObjectJc_SIMPLE


  void iniz_ObjectJc(ObjectJc* othiz, void* ptr, int size, struct ClassJc_t const* refl, int idObj) {
    #ifdef DEF_ObjectJc_REFLREF
      othiz->idInstanceType = (idObj <<16) + (size & 0xffff);
      othiz->preflection = refl;
    #else
      if(refl !=null) {
        othiz->idInstanceType = (idObj <<16) + (refl->idType & 0xffff);
      } else {
        //Hint: do not store any other id, the type id should be left 0! Because it is supplement later and  test later.
        othiz->idInstanceType = (idObj <<16); // + (size & 0xffff);
      }
    #endif
  }


  /**Opposite implementation of checkInit with only idInstanceType. */
  bool checkInit_ObjectJc  (  ObjectJc* thiz, int size, struct ClassJc_t const* clazzReflection, int ident, struct ThreadContext_emC_t* _thCxt) {
    #ifdef DEF_ObjectJc_REFLREF
      if(thiz->preflection ==null) { 
        thiz->preflection = clazzReflection; 
      } else {
        if(clazzReflection !=null && !instanceof_ObjectJc(thiz, clazzReflection)) return false; 
      }
    #else
      if(clazzReflection !=null){
        if( (thiz->idInstanceType & mType_ObjectJc) ==0) {  thiz->idInstanceType |= clazzReflection->idType & mType_ObjectJc; }
        else if((thiz->idInstanceType & mType_ObjectJc) != (clazzReflection->idType & mType_ObjectJc)) { return false; }
      }
    #endif
    if((thiz->idInstanceType & mInstance_ObjectJc)==0) {
      thiz->idInstanceType |= (((uint32)ident)<<kBitInstance_ObjectJc) & mInstance_ObjectJc;
      return true;
    } else {
      return ident == 0 || (thiz->idInstanceType & mInstance_ObjectJc) == (((uint32)ident)<<kBitInstance_ObjectJc);
    }
  }



  bool instanceof_ObjectJc(ObjectJc const* thiz, struct ClassJc_t const* reflection) {
    #ifdef DEF_ObjectJc_REFLREF
      bool reflOk = true;
      struct ClassJc_t const* refl1 = thiz->preflection;
      if(reflection != null) {
        do {
          reflOk = (refl1 == reflection); 
        } while(!reflOk && (refl1 = refl1->superClass) !=null);
      }
      return reflOk;
    #else
      return (thiz->idInstanceType & mType_ObjectJc) == (reflection->idType & mType_ObjectJc); 
    #endif
  }


  bool checkStrict_ObjectJc  ( ObjectJc const* thiz, uint size, struct ClassJc_t const* refl, int ident, struct ThreadContext_emC_t* _thCxt) {
    bool bReflOk = refl ==null || instanceof_ObjectJc(thiz, refl);
    if(!bReflOk) { return false; }
    else {
      return ident==0 
        || (thiz->idInstanceType & mInstance_ObjectJc) == (((uint32)ident)<< kBitInstance_ObjectJc);
    }
  }



  //#ifdef DEF_ObjectJc_REFLREF
  //  bool checkStrict_ObjectJc  ( ObjectJc const* thiz, uint size, struct ClassJc_t const* refl, int ident, struct ThreadContext_emC_t* _thCxt) {
  //    bool reflOk = true;
  //    struct ClassJc_t const* refl1 = thiz->preflection;
  //    if(refl != null) {
  //      do {
  //        reflOk = (refl1 == refl); 
  //      } while(!reflOk && (refl1 = refl1->superClass) !=null);
  //    }
  //    return reflOk && (size == 0 || size <= (thiz->idInstanceType & mType_ObjectJc));
  //  }
  //#elif !defined(DEF_REFLECTION_NO)
  //  bool checkStrict_ObjectJc  ( ObjectJc const* thiz, uint size, struct ClassJc_t const* refl, int ident, struct ThreadContext_emC_t* _thCxt) {
  //    return refl == null || (refl->idType == (thiz->idInstanceType & mType_ObjectJc));
  //  }
  //#else
  //  bool checkStrict_ObjectJc  ( ObjectJc const* thiz, uint size, struct ClassJc_t const* refl, int ident, struct ThreadContext_emC_t* _thCxt) {
  //    return true;
  //  }
  //#endif
 

  void setSizeAndIdent_ObjectJc(ObjectJc* thiz, int sizeObj, int ident) {
    thiz->idInstanceType = (thiz->idInstanceType & (~mInstance_ObjectJc )) | (((uint32)ident)<<16);
  }


//#error exclude it from compilation for simple ObjectJc, include ObjectSimple_emC.c instead

#else //!DEF_ObjectJc_SIMPLE

#include <stdio.h>
//dependencies:
//assertJc
//getCurrent_ThreadContext_emC
//throw_s0Jc

//#include "genRefl/emC/Object_emC.crefl"


//#ifdef DEFINE_debugPRINTF
char const* debugPRINTF[10] = {0};
//#endif
#include <string.h> //memset



char const sign_Vtbl_ObjectJc[] = "sign_Vtbl_ObjectJc";
char const signEnd_Vtbl_ObjectJc[] = "signEnd_Vtbl_ObjectJc";



extern_C const ClassJc reflection_ObjectJc;  //the super class here used.

#ifdef DEF_REFLECTION_FULL  //Note: this feature is not able to use without full reflection support

const ClassOffset_idxVtblJc1 reflection_super_ObjectJc =   //reflection instance for the super class
{ INIZ_ObjectArrayJc(reflection_super_ObjectJc, 1, ClassOffset_idxVtblJc, null, INIZ_ID_ClassOffset_idxVtblJc)
, { &reflection_ObjectJc                                   
, 0 //Index of mtbl of ObjectJc
    //The field which presents the superclass data in inspector access.
  , { "object"              
  , 0 //arraysize
  , &reflection_ObjectJc  //type of super                                                                                         
  , kEmbedded_Modifier_reflectJc //hint: embd helps to show the real type.
  | (0<< kBitAccessLevel_Modifier_FieldJc)  //access level
  | (7<< kBitChangeLevel_Modifier_FieldJc)  //never change
  , 0 //offsetalways 0 (C++?)
  , 0  //offsetToObjectifcBase
  , &reflection_ObjectJc  
  }
}
};

#endif


/**Initialize. */
ObjectJc* init_ObjectJc  ( ObjectJc* ythis, int sizeObj, int identObj) {
  //Note: The second ythis should be the real address of the instance in C++. 
  iniz_ObjectJc(ythis, ythis, sizeObj, null, identObj);
  return ythis;
}



void iniz_ObjectJc(ObjectJc* othiz, void* addrInstance, int sizeObj, struct ClassJc_t const* reflection, int identObj)
{ STACKTRC_ENTRY("iniz_ObjectJc");
  if(sizeObj >= sizeof(ObjectJc))
  { //cc2016-10 memset(ythis, 0, sizeObj);  //don't clear the whole instance because some references etc. maybe initalized with { ... }
    //but set all information in ObjectJc:
    memset(othiz, 0, sizeof(ObjectJc));
    othiz->ownAddress = othiz;
    othiz->state.b.idSyncHandles = kNoSyncHandles_ObjectJc;
    othiz->state.b.isInitialized = 0;  //mark as new initialized.  
    setSizeAndIdent_ObjectJc(othiz, sizeObj, identObj);
    othiz->state.b.offsetToStartAddr = (int16)(((MemUnit*)(othiz)) - ((MemUnit*)(addrInstance)));
    othiz->reflectionClass = reflection; //may be null.
  }
  else {
    THROW_s0(IllegalArgumentException, "size to less", sizeObj, identObj);
  }
  STACKTRC_LEAVE;
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


void setSizeAndIdent_ObjectJc(ObjectJc* ythis, int sizeObj, int ident)
{ int identObj;
  if(ident==0) {
    identObj=newIdent_ObjectJc();
  } else { 
    identObj = ident; 
  }
  int nrofArrayDimensions = 0;  //unused. The number of array dimensions should be noted in the reflection- FieldJc and in the ObjectArrayJc-data.

  if(identObj < 0 || sizeObj < 0 || nrofArrayDimensions <0 || nrofArrayDimensions > 3)
  { STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW1_s0(RuntimeException, "negativ values for all parameter are unexpected, or nrofArrayDimensions >0", sizeObj);
  }
  else if(sizeObj <= mSizeSmall_objectIdentSize_ObjectJc && identObj <= (mIdentSmall_objectIdentSize_ObjectJc >> kBitIdentSmall_objectIdentSize_ObjectJc))
  { ythis->state.b.objectIdentSize = sizeObj | kIsSmallSize_objectIdentSize_ObjectJc | (identObj<<kBitIdentSmall_objectIdentSize_ObjectJc);
  }
  else if(sizeObj <= mSizeMedium_objectIdentSize_ObjectJc && identObj <= (mIdentMedium_objectIdentSize_ObjectJc >> kBitIdentMedium_objectIdentSize_ObjectJc))
  { ythis->state.b.objectIdentSize = sizeObj | kIsMediumSize_objectIdentSize_ObjectJc | (identObj<<kBitIdentMedium_objectIdentSize_ObjectJc);
  }
  else if(sizeObj <= mSizeLarge_objectIdentSize_ObjectJc && identObj <= (mIdentLarge_objectIdentSize_ObjectJc >> kBitIdentLarge_objectIdentSize_ObjectJc))
  { ythis->state.b.objectIdentSize = sizeObj | mIsLargeSize_objectIdentSize_ObjectJc | (identObj<<kBitIdentLarge_objectIdentSize_ObjectJc);
  }
  else
  { STACKTRC_ENTRY("setSizeAndIdent_ObjectJc");
    THROW1_s0(RuntimeException, "not matched ident and size", sizeObj);
  }
}


int newIdent_ObjectJc()
{ //TODO important: Use entry in handle2Ptr for Simulink S-functions and dll
  static int countIdent = 0;  //note: intializing only at startup!
  return ++countIdent;
}





bool checkStrict_ObjectJc(ObjectJc const* ythis, uint size, struct ClassJc_t const* clazzReflection, int ident, struct ThreadContext_emC_t* _thCxt)
{ int identObj = getIdentInfo_ObjectJc(ythis);
  STACKTRC_TENTRY("checkConsistence_ObjectJc");
  { //it is initialized, check it
    int sizeObj = getSizeInfo_ObjectJc(ythis);
    if(ythis->ownAddress != ythis) {
      ident = -1;  //marker for faulty.
      THROW_s0(RuntimeException, "faulty ownAddress", (int)(intptr_t)ythis->ownAddress, (int)(int_ptr)ythis);
      return false;
    }
    if(size != 0 && ((uint)sizeObj) < size) {
      ident = -1;  //marker for faulty.
      THROW_s0(RuntimeException, "faulty size", sizeObj, size);
      return false;
    }
    //
    if(ident != 0 && ident != identObj) {
      THROW_s0(RuntimeException, "faulty ident", identObj, ident);
      return false;
      identObj = -1;  //marker for faulty.
    }
    //
    if(clazzReflection != null && ythis->reflectionClass !=null)
    { if(!instanceof_s_ObjectJc(ythis, clazzReflection->name)) {
      THROW_s0(RuntimeException, "faulty type", (int)(intptr_t)ythis->reflectionClass, (int)(int_ptr)clazzReflection);
      return false;
      }
    }
  }
  STACKTRC_RETURN true; //all ok
}



bool checkInit_ObjectJc  ( ObjectJc* thiz, int size, struct ClassJc_t const* clazzReflection, int ident, ThCxt* _thCxt)
{ //bool bOk;
  STACKTRC_TENTRY("checkInit_ObjectJc");
  if(thiz->state.b.objectIdentSize == 0) { //size and ident not initialized
    setSizeAndIdent_ObjectJc(thiz, size, ident);
  }
  if(thiz->reflectionClass == null) {
    setReflection_ObjectJc(thiz, clazzReflection, 0);
  }
  STACKTRC_RETURN checkStrict_ObjectJc(thiz, size, clazzReflection, ident,_thCxt);
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
    return (ythis->state.b.objectIdentSize & mIdentLarge_objectIdentSize_ObjectJc) >>kBitIdentLarge_objectIdentSize_ObjectJc;
  else if( (ythis->state.b.objectIdentSize & mSizeBits_objectIdentSize_ObjectJc) == kIsMediumSize_objectIdentSize_ObjectJc)
    return (ythis->state.b.objectIdentSize & mIdentMedium_objectIdentSize_ObjectJc) >>kBitIdentMedium_objectIdentSize_ObjectJc;
  else
    return (ythis->state.b.objectIdentSize & mIdentSmall_objectIdentSize_ObjectJc) >>kBitIdentSmall_objectIdentSize_ObjectJc;
}



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
  if(refl->object.reflectionClass == null) { 
    return false; //The reflection class should have exact Object data.
  }
  if(strncmp(refl->object.reflectionClass->name, "ClassJc", 7) != 0){ 
    return false; //The reflection class should have exact Object data.
  }

  return (strncmp(refl->name, reflectionName, zReflectionName) ==0);
}
#endif




int getIxVtbl_s_ClassJc(ClassJc const* reflectionObj, char const* reflectionName)
{ int idxVtbl = -1;
  STACKTRC_ENTRY("getIdxVtbl_ClassJc");
#ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
  if(reflectionObj == null || reflectionObj->object.reflectionClass == null || strcmp(reflectionObj->object.reflectionClass->name, "ClassJc") !=0){
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
    ClassOffset_idxVtblJcARRAY const* reflectionSuper;
    if(idxVtbl < 0 && (reflectionSuper = reflectionObj->superClasses) != null)
    { int idxSuper = 0;
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
          idxVtbl = getIxVtbl_s_ClassJc(superType, reflectionName);
        }
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







bool instanceof_s_ObjectJc(ObjectJc const* ythis, char const* reflectionName)
{ if(ythis == null) return false;
  int idxVtbl = getIxVtbl_s_ClassJc(ythis->reflectionClass, reflectionName);
  return idxVtbl >=0;
}




struct ClassJc_t const* getClass_ObjectJc(ObjectJc const* ythis)
{ return ythis->reflectionClass;//->theClass;
}



int getTypeId_ObjectJc(ObjectJc* thiz) {
  return 0; //TODO
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






#ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
VtblHeadJc const* getVtbl_ObjectJc(ObjectJc const* ythis, char const* sign)
{ VtblHeadJc const* head = null; //nullpointer-return possible
  ClassJc const* reflection;
  STACKTRC_ENTRY("getVtbl_ObjectJc");
  if(ythis->ownAddress != ythis){ 
    THROW1_s0(IllegalArgumentException, "Object head faulty", (int)(intptr_t)ythis);
    STACKTRC_LEAVE; return null;  //The null pointer may be tested outside, or it should cause an exception outside if it is unexpected.
  }
  reflection = ythis->reflectionClass;
  if( reflection != null) { 
  if(reflection->object.reflectionClass != &reflection_ClassJc){
    THROW1_s0(IllegalArgumentException, "Object reflection faulty", (int)(intptr_t)ythis);
    STACKTRC_LEAVE; return null;  //The null pointer may be tested outside, or it should cause an exception outside if it is unexpected.
  }
  head = ythis->reflectionClass->mtbl;  
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
#endif




#ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
int getPosInVtbl_ObjectJc(ObjectJc const* thiz, char const* sign)
{ VtblHeadJc const* headSign = getVtbl_ObjectJc(thiz, sign);
  if(headSign !=null){
    VtblHeadJc const* headBase = thiz->reflectionClass->mtbl;
    return OFFSET_MemUnit(headBase, headSign) / (int)sizeof(sign);
  } 
  else return -1;  //no Vtbl found.
}
#endif



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
    ClassOffset_idxVtblJcARRAY const* reflectionSuper;
    if(idxVtbl < 0 && (reflectionSuper = reflectionObj->superClasses) != null)
    { int idxSuper = 0;
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
    }
  #endif
    { //search in superclasses and there interfaces
      //old if only 1 superclass:
      //idxVtbl = getIdxVtbl_ClassJc(reflectionObj->superClass, reflectionRef);
    }

  }
  STACKTRC_LEAVE; return(idxVtbl);
}



bool instanceof_ObjectJc(ObjectJc const* ythis, struct ClassJc_t const* reflection)
{ 
  int idxVtbl = getIdxVtbl_ClassJc(ythis->reflectionClass, reflection);
  return idxVtbl >=0;
}


#ifdef DEF_REFLECTION_FULL   //TODO create variant without Reflection but with ixVtbl
/*J2C: dynamic call variant of the override-able method: */
StringJc toString_ObjectJc(ObjectJc* ithis, ThCxt* _thCxt)
{ Vtbl_ObjectJc const* mtbl = (Vtbl_ObjectJc const*)getVtbl_ObjectJc(ithis, sign_Vtbl_ObjectJc);
  return mtbl->toString(ithis, _thCxt);
}
#endif






void init_immediate_ObjectArrayJc(ObjectArrayJc* thiz, int nrofElements, int sizeElement, ClassJc const* refl_Elem, int idObj) {
  iniz_ObjectJc(&thiz->object, thiz, sizeof(ObjectArrayJc) + nrofElements * sizeElement, refl_Elem, idObj);
  thiz->length = nrofElements;
  thiz->sizeElement = sizeElement;
  thiz->mode = 1 << kBitDimension_ObjectArrayJc;
}

StringJc name_ClassJc(ClassJc const* thiz) {
  int zz = strnlen_emC(thiz->name, sizeof(thiz->name));  //at leas the length of buffer
  return zI_StringJc(thiz->name, zz);
}

#endif //!DEF_ObjectJc_SIMPLE





#ifdef DEF_REFLECTION_FULL 
StringJc name_FieldJc(FieldJc const* thiz) {
  int zz = strnlen_emC(thiz->name, sizeof(thiz->name));  //at leas the length of buffer
  return zI_StringJc(thiz->name, zz);
}
#endif

#include "emC/Base/SystemInit_emC.h"

SystemInit_emC _systemInit_emC_ = { 0 };

SystemInit_emC* systemInit_emC = &_systemInit_emC_;

