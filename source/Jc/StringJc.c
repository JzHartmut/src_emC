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
 * @content Implementation of String processing
 *
 * @author Jchartmut www.vishia.org
 * @version 0.81
 * list of changes:
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/

#include "StringJc_intern.h"
#include "Jc/ObjectJc.h"      //It is a concept of CRuntimeJavalike
#include <Jc/ReflectionJc.h>

//#include "fw_ThreadContext.h"

#include <string.h>

#ifdef mBackRef_ObjectJc
  /** The RuntimeHeapJc.h are only needed, if back references are to be stored.*/
//xxxTODO  #include "RuntimeHeapJc.h"
#else
  #define setBackref_BheapJc(REF, SRC_P) /*it is unused*/
#endif


/*@CLASS_C_IMPLEMENT StringJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/** Some methods from StringJc are defined in ObjectJc.h, because there are simple methods
  * not using RuntimeHeap, Garbage Collection and others. This simple methods are implemented here.
  * That are all methods which do not copy strings, only compare, convert to char* etc.
  */



CharSeqJc fromObjectJc_CharSeqJc(struct ObjectJc_t* othiz)
{ CharSeqJc ret;
  
  int val = getPosInMtbl_ObjectJc(othiz, sign_Mtbl_CharSeqJc);
  if(val >=0){
    val |= mIsCharSeqJcMtbl_CharSeqJc;
  } else {
    STACKTRC_ENTRY("fromObjectJc_CharSeqJc");
    THROW1_s0(IllegalArgumentException, "thiz does not implement the CharSeqJc interface.", (int)othiz);
    STACKTRC_LEAVE;
	  return z_CharSeqJc("faulty instance ");
  }
  set_OS_PtrValue(ret, othiz, val); 
  return ret;
}







int32 length_StringJc_CharSeqJc_F(ObjectJc* ithiz, ThCxt* _ThCxt)
{ StringJc_CharSeqJc* thiz = (StringJc_CharSeqJc*)ithiz;
  return thiz->length; 
}

char charAt_StringJc_CharSeqJc_F(ObjectJc* ithiz, int32 ix, ThCxt* _thCxt)
{ StringJc_CharSeqJc* thiz = (StringJc_CharSeqJc*)ithiz;
  if(ix < 0 || ix >= thiz->length) {
    //THROW
    return 0;
  }
  return thiz->s[ix]; 
}

CharSeqJc subSequence_StringJc_CharSeqJc_F(ObjectJc* ithiz, int32 from, int32 to, ThCxt* _thCxt)
{ CharSeqJc ret = {0};
  return ret;  //TODO
}


bool equals_StringJc_CharSeqJc_F(ObjectJc* ithiz, ObjectJc* second, ThCxt* _thCxt) {
  StringJc_CharSeqJc* thiz = (StringJc_CharSeqJc*)ithiz;
  return false;  //TODO 
}

StringJc toString_StringJc_CharSeqJc_F(ObjectJc* ithiz, ThCxt* _thCxt) {
  StringJc_CharSeqJc* thiz = (StringJc_CharSeqJc*)ithiz;
  StringJc ret = CONST_StringJc(thiz->s, thiz->length);
  return ret; 
}

void finalize_StringJc_CharSeqJc_F(ObjectJc* ithiz, ThCxt* _thCxt) {
}

Mtbl_CharSeqJc mtbl_StringJc_CharSeqJc =
{ { sign_Mtbl_CharSeqJc//J2C: Head of methodtable.
    , (struct Size_Mtbl_t*)((sizeof(Mtbl_CharSeqJc))) //size. NOTE: all elements are standard-pointer-types.
  }
  , length_StringJc_CharSeqJc_F 
  , charAt_StringJc_CharSeqJc_F
  , subSequence_StringJc_CharSeqJc_F
  , { {sign_Mtbl_ObjectJc//J2C: Head of methodtable.
    , (struct Size_Mtbl_t*)((sizeof(Mtbl_ObjectJc)))
      }
    , null
    , equals_StringJc_CharSeqJc_F  //equals
    , finalize_StringJc_CharSeqJc_F
    , null
    , toString_StringJc_CharSeqJc_F 
    }
}; 




Mtbl_CharSeqJc const* getMtbl_CharSeqJc(CharSeqJc thiz, struct ThreadContext_emC_t* _thCxt)
{
  int nChars = VAL_CharSeqJc(thiz) & mLength__StringJc;
  ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
  MtblHeadJc const* head;
  Mtbl_CharSeqJc const* mc;
  if(nChars == kIsCharSeqJc_CharSeqJc) {
    head = getMtbl_ObjectJc(othiz, sign_Mtbl_CharSeqJc);
  } else {
    int offsetMtbl =  nChars & ~mIsCharSeqJcMtbl_CharSeqJc;
    head = othiz->reflectionClass->mtbl;
    head = (MtblHeadJc const*)(&head->sign + offsetMtbl);
    //MemUnit* head2 = addOffset_MemUnit(head, offsetMtbl);  //add offset in mtbl
    //head = (MtblHeadJc const*) head2;
  }
  ASSERT_s0_Jc(head->sign == sign_Mtbl_CharSeqJc, "faulty Mtbl of CharSeqJc", (int)ythis);
  mc = (Mtbl_CharSeqJc const*) head;
  return mc;

}


CharSeqJcMTB getMtblRef_CharSeqJc(CharSeqJc thiz, StringJc_CharSeqJc* dst_StringJc, ThCxt* _thCxt)
{ CharSeqJcMTB ret;
  int val = VAL_CharSeqJc(thiz) & mLength__StringJc;
  if(val == kIs_0_terminated_StringJc) { 
    val = strnlen_emC(PTR_OS_PtrValue(thiz, char const), kMaxNrofChars_StringJc); 
  }

  if(val <= kMaxNrofChars_StringJc) {
    //A String, use the given instance of dst_StringJc
    if(dst_StringJc !=null) {
      memset(dst_StringJc, 0, sizeof(StringJc_CharSeqJc));
      init_ObjectJc(&dst_StringJc->base, sizeof(StringJc_CharSeqJc), 0);
      dst_StringJc->s = PTR_OS_PtrValue(thiz, char const);
      dst_StringJc->length = val;
      ret.mtbl = null;
      ret.ref = null;

    } else {
      ret.mtbl = null;
      ret.ref = null;
    }
  } 
  else if(val < kIsStringBuilder_CharSeqJc) {
    //It contains the index to the method table inside the given reflection.
    ret.ref = PTR_OS_PtrValue(thiz, ObjectJc);
    ret.mtbl  = (Mtbl_CharSeqJc*)checkMtbl_ObjectJc(ret.ref, val & mMtbl_CharSeqJc, sign_Mtbl_CharSeqJc, _thCxt);
  }
  else {
    //Any Object, may be a StringBuilder too.
    ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
    Mtbl_CharSeqJc* mthiz = (Mtbl_CharSeqJc*)getMtbl_ObjectJc(othiz, sign_Mtbl_CharSeqJc);
    ret.mtbl = mthiz;
    ret.ref = othiz;
  }
  return ret;
}










StringJc toString_CharSeqJc(CharSeqJc thiz)
{
  STACKTRC_ENTRY("toString_CharSeqJc");
  int val = value_OS_PtrValue(thiz);
  if(val == kIsStringBuilder_CharSeqJc) {
    StringBuilderJc* sb = PTR_OS_PtrValue(thiz, StringBuilderJc);
    char const* buffer = chars_StringBuilderJc(sb);
    int nChars = length_StringBuilderJc(sb);
    StringJc ret = CONST_StringJc(buffer, nChars);
    STACKTRC_LEAVE; return ret;
  }
  else if(val & mIsCharSeqJcMtbl_CharSeqJc) {
    Mtbl_CharSeqJc const* mc = getMtbl_CharSeqJc(thiz, _thCxt);
    ObjectJc* othiz = PTR_OS_PtrValue(thiz, ObjectJc);
    int iChars;
    int nChars = mc->length(othiz, _thCxt);
    MemC mBuffer = getUserBuffer_ThreadContext_emC(nChars+1, "toString_CharSeqJc", _thCxt);
    int sizeBufferThreadContext = size_MemC(mBuffer);
    if(nChars >= sizeBufferThreadContext){ 
      nChars = sizeBufferThreadContext-1;   //limit it.
    }
    char* buffer = PTR_MemC(mBuffer, char);
    for(iChars = 0; iChars < nChars; ++iChars) {
      char cc = mc->charAt(othiz, iChars, _thCxt);
      buffer[iChars] = cc;
    }
    buffer[iChars] = 0;
    StringJc ret = CONST_StringJc(buffer, nChars);
    STACKTRC_LEAVE; return ret;
  } else {
    //it is a String
    STACKTRC_LEAVE; return *(StringJc*)&thiz;
  } 
}








char const sign_Mtbl_CharSeqJc[] = "sign_Mtbl_CharSeqJc";

char const* gets0_StringJc(StringJc const thiz, char* const buffer, int const zBuffer, bool exceptionOnLessBuffer, struct ThreadContext_emC_t* _thCxt)
{
  int len;
  char const* str = getCharsAndLength_StringJc(&thiz, &len);
  if(str[len] == 0){ return str;
  } else {
    if(len >= zBuffer){
      if(exceptionOnLessBuffer){
        STACKTRC_TENTRY("substring_StringJc");
        THROW1_s0(IndexOutOfBoundsException, "String too long", len); 
        STACKTRC_LEAVE;
      } else {
        len = zBuffer -1;
      }
    }
    memcpy(buffer, str, len);
    buffer[len] = 0;
    return buffer;
  }
}




void clear_StringJc(StringJc* ythis)
{ STACKTRC_ENTRY("clear_StringJc");

  clearBackRefJc(ythis);
  if((VAL_StringJc(*ythis) & mThreadContext__StringJc) == mThreadContext__StringJc){
    releaseUserBuffer_ThreadContext_emC(PTR_StringJc(*ythis), _thCxt);
  }
  INIT_StringJc(*ythis, null, 0);
  STACKTRC_LEAVE;
}








/**NOTE: don't use a macro for this routine, because if it were written
 * #define equals_StringJc(YTHIS, STR) (equals_zI_StringJc(YTHIS; PTR_StringJc(STR), VAL_StringJc(STR))
 * than an expression for STR will be evaluated twice. This may be fatal in runtime.
 */
bool equals_StringJc(const StringJc ythis, const StringJc cmp)
{ int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  int countCmp = VAL_StringJc(cmp) & mLength__StringJc;
  const char* strThis = PTR_StringJc(ythis);
  const char* strCmp = PTR_StringJc(cmp);
  if(countThis == mLength__StringJc){
    countThis = strnlen_emC(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strnlen_emC(strCmp, countThis+1); //more chars are not necessary.
  }
  if(countCmp != countThis)
  { return(false);
  }
  else if(strThis == strCmp){
    return true;  //same length and same addresses of text.
  }
  else
  { bool bRet = memcmp(strThis, strCmp, countCmp) == 0;
    return(bRet);
  }
}



bool startsWith_StringJc(const StringJc ythis, const StringJc cmp)
{ int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  int countCmp = VAL_StringJc(cmp) & mLength__StringJc;
  const char* strThis = PTR_StringJc(ythis);
  const char* strCmp = PTR_StringJc(cmp);
  if(countThis == mLength__StringJc){
    countThis = strnlen_emC(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strnlen_emC(strCmp, countThis+1); //more chars are not necessary.
  }
  if(countCmp > countThis)
  { return(false);
  }
  else if(strThis == strCmp){
    return true;  //same length and same addresses of text.
  }
  else
  { bool bRet = memcmp(strThis, strCmp, countCmp) == 0;
    return(bRet);
  }
}


bool startsWith_zI_StringJc(const StringJc ythis, const char* strCmp, int valueCmp  )
{ int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  int countCmp = valueCmp & mLength__StringJc;
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength__StringJc){
    countThis = strnlen_emC(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strnlen_emC(strCmp, countThis+1);
  }
  if(countCmp > countThis)
  { return(false);
  }
  else if(strThis == strCmp){
    return true;  //same length and same addresses of text.
  }
  else
  { bool bRet = memcmp(strThis, strCmp, countCmp) == 0;
    return(bRet);
  }
}



bool endsWith_StringJc(const StringJc ythis, const StringJc cmp)
{ int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  int countCmp = VAL_StringJc(cmp) & mLength__StringJc;
  const char* strThis = PTR_StringJc(ythis);
  const char* strCmp = PTR_StringJc(cmp);
  if(countThis == mLength__StringJc){
    countThis = strnlen_emC(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strnlen_emC(strCmp, countThis+1); //more chars are not necessary.
  }
  if(countCmp > countThis)
  { return(false);
  }
  else {
    int pos = countThis - countCmp;
    if(strThis + pos == strCmp){
      return true;  //same length and same addresses of text.
    }
    else{ 
      bool bRet = memcmp(strThis + pos, strCmp, countCmp) == 0;
      return(bRet);
    }
  }
}

bool endsWith_zI_StringJc(const StringJc ythis, const char* strCmp, int valueCmp  )
{ int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  int countCmp = valueCmp & mLength__StringJc;
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength__StringJc){
    countThis = strnlen_emC(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strnlen_emC(strCmp, countThis+1);
  }
  if(countCmp > countThis)
  { return(false);
  }
  else {
    int pos = countThis - countCmp;
    if(strThis + pos == strCmp){
      return true;  //same length and same addresses of text.
    }
    else{ 
      bool bRet = memcmp(strThis + pos, strCmp, countCmp) == 0;
      return(bRet);
    }
  }
}









/** Realisation of substring: If the parent string is a constant string,
  * the substring will be also a simple constant string directly pointered a part of parent.
  * If the String is inside a StringBuffer, may be a SubstringJc of StringBuilderJc or StringBuilderJc itself,
  * the problem is more complexly. In this case inside the parent string it should be registered
  * the using of the Buffer. It may be a RuntimeHeapBlockJc with garbage collection.
  */
METHOD_C StringJc substring_StringJc(StringJc ythis, int beginIndex, int endIndex, ThCxt* _thCxt)
{ StringJc ret = NULL_StringJc;
  int valueThis = VAL_StringJc(ythis);
  int count = valueThis & mLength__StringJc;
  const char* chars = PTR_StringJc(ythis);
  STACKTRC_TENTRY("substring_StringJc");
  
  if(count == mLength__StringJc) { count = strlen(chars);}

  if(endIndex < 0) {endIndex = count; }

  if(endIndex > count){ THROW1_s0(IndexOutOfBoundsException, "endIndex", endIndex); }
  else if(beginIndex <0 || beginIndex > endIndex){ THROW1_s0(IndexOutOfBoundsException, "beginIndex", beginIndex); }
  else
  { int value = (endIndex - beginIndex)                //length 
              | (valueThis & mNonPersists__StringJc);  //non persistent only if the src is non-persistent.
    INIT_StringJc(ret, chars + beginIndex, value);
  }

  STACKTRC_LEAVE; return( ret);
}


METHOD_C int indexOf_CI_StringJc(StringJc ythis, int ch, int fromIndex)
{ const char* chars = PTR_StringJc(ythis);
  int nChars = VAL_StringJc(ythis) & mLength__StringJc;
  //STACKTRC_TENTRY("StringJc.indexOf(int,int)");
  if(nChars == mLength__StringJc) { nChars = strlen(chars); }
  //const char* chars = getCharsAndLength_StringJc(ythis, &nChars);
  if(fromIndex <0 || fromIndex >= nChars)
  { //STACKTRC_LEAVE; 
    return( -1);
  }
  return searchChar_emC(chars + fromIndex, nChars - fromIndex, ch);
}



int indexOf_sI_StringJc(StringJc ythis, StringJc str, int fromIndex)
{ int nChars;
  const char* chars = getCharsAndLength_StringJc(&ythis, &nChars);
  int nCharsSearch;
  const char* charsSearch = getCharsAndLength_StringJc(&str, &nCharsSearch);
  if(fromIndex <0)
  { //STACKTRC_LEAVE; 
    fromIndex = 0; //In java it is so too.
  }
  return searchString_emC(chars + fromIndex, nChars - fromIndex, charsSearch, nCharsSearch);
  //
}



int lastIndexOf_CI_StringJc(StringJc ythis, int ch, int fromIndex )
{ const char* chars;
  int nChars;
  //STACKTRC_TENTRY("StringJc.indexOf(int,int)");
  chars = getCharsAndLength_StringJc(&ythis, &nChars);
  { int ii;
    if(fromIndex >= nChars)
    { fromIndex = nChars -1; }
    for(ii = fromIndex; ii >=0; ii--)
    { if(chars[ii] == ch) 
      { //STACKTRC_LEAVE; 
        return ii;
      }
    }
    //STACKTRC_LEAVE; 
    return( -1);  //not found STACKTRC_LEAVE; return(s in for loop if found!
  }
}


int lastIndexOf_sI_StringJc(StringJc ythis, StringJc cmp, int fromIndex )
{ int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  int countCmp = VAL_StringJc(cmp) & mLength__StringJc;
  const char* strThis = PTR_StringJc(ythis);
  const char* strCmp = PTR_StringJc(cmp);
  if(countThis == mLength__StringJc){
    countThis = strnlen_emC(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strnlen_emC(strCmp, countThis+1); //more chars are not necessary.
  }
  if(fromIndex > (countThis - countCmp)){ 
    fromIndex = countThis - countCmp;     //start at last possible position.     
  }
  if(countCmp == 0)
  { return fromIndex < 0 ? -1 : fromIndex;  //equals to Java
  }
  { int ii;
    char cc = strCmp[0];
    for(ii = fromIndex; ii >=0; ii--)  //seacrch the first char backward
    { if(strThis[ii] == cc) 
      { //if the first char is found, compare the rest.
        if(countCmp == 1 || strncmp(strCmp +1, strThis + ii +1, countCmp-1) == 0)
        { //STACKTRC_LEAVE; 
          return( ii);   //found
        }
      }
    }
    //STACKTRC_LEAVE; 
    return( -1);  //not found (returns in for loop if found!)
  }
}





void getChars_StringJc(StringJc ythis, int srcBegin, int srcEnd, char_Y* dst, int dstBegin, ThCxt* _thCxt)
{
  int sizeBuffer = dst->head.length;
  int nrofChars = srcEnd - srcBegin;
  int sizeString;
  char const* sString = getCharsAndLength_StringJc(&ythis, &sizeString);
  STACKTRC_TENTRY("getChars_StringJc");
  //if(sizeBuffer < size_StringJc(ythis,_thCxt)) THROW1_s0(IndexOutOfBoundsException, "size to small", sizeBuffer);
  if(nrofChars > sizeBuffer) THROW1_s0(IndexOutOfBoundsException, "buffer to small", sizeBuffer);
  if(nrofChars < 0) THROW1_s0(IndexOutOfBoundsException, "srcEnd less than srcBegin", nrofChars);
  if(srcBegin < 0) THROW1_s0(IndexOutOfBoundsException, "srcBegin <0", srcBegin);
  if(dstBegin < 0) THROW1_s0(IndexOutOfBoundsException, "dstBegin <0", srcBegin);
  if((dstBegin + nrofChars) > sizeBuffer) THROW1_s0(IndexOutOfBoundsException, "dstBegin fault", dstBegin);

  memcpy(dst->data + dstBegin, sString + srcBegin, nrofChars);  
  STACKTRC_LEAVE;
}




ByteStringJc getBytesEncoding_StringJc(StringJc ythis, StringJc encoding, ThCxt* _txCtx)
{
  int length;
  char const* chars;
  //int sizeArray;
  int iChar;
  chars = getCharsAndLength_StringJc(&ythis, &length);
  //check encoding.
  for(iChar = 0; iChar < length; ++iChar){
    //nothing to do yet
  }
  return *(ByteStringJc*)&ythis;
}





/**************************************************************************************************/
/* some conversions numeric from/to String */



int parseInt_radix_IntegerJc(StringJc ythis, int radix)
{ 
  int nrofCharsParsed;
  int value;
  int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength__StringJc){
    countThis = strnlen_emC(strThis, mLength__StringJc);
  }
  value = parseIntRadix_emC(strThis, countThis, radix, &nrofCharsParsed);
  if(nrofCharsParsed < countThis){
    STACKTRC_ENTRY("parseInt_IntegerJc");
    THROW1_s0(NumberFormatException, " rest:", countThis - nrofCharsParsed);
    STACKTRC_LEAVE;
  }
  return value;
}


//see StringValueConvJc.c
int32 xxxfloatToRawIntBits_FloatJc(float val)
{
  return *(int32*)&val;
}

int32 xxxfloatToIntBits_FloatJc(float val)
{
  return *(int32*)&val;
}



float xxxintBitsToFloat_FloatJc(int32 val)
{
  return *(float*)&val;
}

float parseFloat_FloatJc(StringJc src)
{
  //TODO see parseFloat_emC() in simpleC.c
  return 0.0F;
}



int64 xxxdoubleToRawLongBits_DoubleJc(double val)
{
  return *(int64*)&val;
}

int64 xxxdoubleToLongBits_DoubleJc(double val)
{
  return *(int64*)&val;
}

double xxxlongBitsToDouble_DoubleJc(int64 val)
{
  return *(double*)&val;
}

double parseDouble_DoubleJc(StringJc src)
{
  //TODO see parseFloat_emC() in simpleC.c
  return 0.0F;
}



