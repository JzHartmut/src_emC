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

#include "emC/Jc/StringJc_intern.h"

#ifndef DEF_NO_StringUSAGE


#include "emC/Jc/ObjectJc.h"      //It is a concept of CRuntimeJavalike
#include <emC/Jc/ReflectionJc.h>

//#include "fw_ThreadContext.h"

#include <string.h>

#ifdef mBackRef_ObjectJc
  /** The RuntimeHeapJc.h are only needed, if back references are to be stored.*/
//xxxTODO  #include "RuntimeHeapJc.h"
#else
  #define setBackref_BheapJc(REF, SRC_P) /*it is unused*/
#endif


/*@CLASS_C_IMPLEMENT StringJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/












void clear_StringJc(StringJc* ythis)
{ STACKTRC_ENTRY("clear_StringJc");

  #ifdef DEF_ObjectJc_FULLCAPABILITY
  clearBackRefJc(ythis);
  #endif
  #ifdef DEF_ThreadContext_HEAP_emC
  if((VAL_StringJc(*ythis) & mThreadContext__StringJc) == mThreadContext__StringJc){
    releaseUserBuffer_ThreadContext_emC(PTR_StringJc(*ythis), _thCxt);
  }
  #endif
  SET_StringJc(*ythis, null, 0);
  STACKTRC_LEAVE;
}








/**NOTE: don't use a macro for this routine, because if it were written
 * #define equals_StringJc(YTHIS, STR) (equals_zI_StringJc(YTHIS; PTR_StringJc(STR), VAL_StringJc(STR))
 * than an expression for STR will be evaluated twice. This may be fatal in runtime.
 */
bool equals_StringJc ( const StringJc ythis, const StringJc cmp)
{ int countThis = VAL_StringJc(ythis) & mLength_StringJc; 
  int countCmp = VAL_StringJc(cmp) & mLength_StringJc;
  const char* strThis = PTR_StringJc(ythis);
  const char* strCmp = PTR_StringJc(cmp);
  if(countThis == mLength_StringJc){
    countThis = strnlen_emC(strThis, mLength_StringJc);
  }
  if(countCmp == mLength_StringJc){
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
{ int countThis = VAL_StringJc(ythis) & mLength_StringJc; 
  int countCmp = VAL_StringJc(cmp) & mLength_StringJc;
  const char* strThis = PTR_StringJc(ythis);
  const char* strCmp = PTR_StringJc(cmp);
  if(countThis == mLength_StringJc){
    countThis = strnlen_emC(strThis, mLength_StringJc);
  }
  if(countCmp == mLength_StringJc){
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
{ int countThis = VAL_StringJc(ythis) & mLength_StringJc; 
  int countCmp = valueCmp & mLength_StringJc;
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength_StringJc){
    countThis = strnlen_emC(strThis, mLength_StringJc);
  }
  if(countCmp == mLength_StringJc){
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
{ int countThis = VAL_StringJc(ythis) & mLength_StringJc; 
  int countCmp = VAL_StringJc(cmp) & mLength_StringJc;
  const char* strThis = PTR_StringJc(ythis);
  const char* strCmp = PTR_StringJc(cmp);
  if(countThis == mLength_StringJc){
    countThis = strnlen_emC(strThis, mLength_StringJc);
  }
  if(countCmp == mLength_StringJc){
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
{ int countThis = VAL_StringJc(ythis) & mLength_StringJc; 
  int countCmp = valueCmp & mLength_StringJc;
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength_StringJc){
    countThis = strnlen_emC(strThis, mLength_StringJc);
  }
  if(countCmp == mLength_StringJc){
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
  * If the String is inside a StringBuffer, may be a SubstringJc of StringBuilderJc_s or StringBuilderJc_s itself,
  * the problem is more complexly. In this case inside the parent string it should be registered
  * the using of the Buffer. It may be a RuntimeHeapBlockJc with garbage collection.
  */
METHOD_C StringJc substring_StringJc(StringJc ythis, int beginIndex, int endIndex, ThCxt* _thCxt)
{ StringJc ret = NULL_StringJc;
  int valueThis = VAL_StringJc(ythis);
  int count = valueThis & mLength_StringJc;
  const char* chars = PTR_StringJc(ythis);
  STACKTRC_TENTRY("substring_StringJc");
  
  if(count == mLength_StringJc) { count = (int)strlen(chars);}

  if(endIndex < 0) {endIndex = count; }

  if(endIndex > count){ THROW1_s0(IndexOutOfBoundsException, "endIndex", endIndex); }
  else if(beginIndex <0 || beginIndex > endIndex){ THROW1_s0(IndexOutOfBoundsException, "beginIndex", beginIndex); }
  else
  { int value = (endIndex - beginIndex)                //length 
              | (valueThis & mNonPersists__StringJc);  //non persistent only if the src is non-persistent.
    SET_StringJc(ret, chars + beginIndex, value);
  }

  STACKTRC_LEAVE; return( ret);
}


METHOD_C int indexOf_CI_StringJc(StringJc ythis, int ch, int fromIndex)
{ const char* chars = PTR_StringJc(ythis);
  int nChars = VAL_StringJc(ythis) & mLength_StringJc;
  //STACKTRC_TENTRY("StringJc.indexOf(int,int)");
  if(nChars == mLength_StringJc) { nChars = strnlen_emC(chars, kMaxNrofChars_StringJc); }
  //const char* chars = getCharsAndLength_StringJc(ythis, &nChars);
  if (fromIndex <0)
  { //STACKTRC_LEAVE; 
    fromIndex = 0; //In java it is so too.
  }
  if(fromIndex <0 || fromIndex >= nChars)
  { //STACKTRC_LEAVE; 
    return( -1);
  }
  int pos = searchChar_emC(chars + fromIndex, nChars - fromIndex, ch);
  if(pos >=0) return fromIndex + pos;
  else return -1;
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
  if (fromIndex <0 || fromIndex >= nChars)
  { //STACKTRC_LEAVE; 
    return(-1);
  }
  int pos = searchString_emC(chars + fromIndex, nChars - fromIndex, charsSearch, nCharsSearch);
  if (pos >= 0) return fromIndex + pos;
  else return -1;
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
{ int countThis = VAL_StringJc(ythis) & mLength_StringJc; 
  int countCmp = VAL_StringJc(cmp) & mLength_StringJc;
  const char* strThis = PTR_StringJc(ythis);
  const char* strCmp = PTR_StringJc(cmp);
  if(countThis == mLength_StringJc){
    countThis = strnlen_emC(strThis, mLength_StringJc);
  }
  if(countCmp == mLength_StringJc){
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




#ifdef DEF_ObjectJc_FULLCAPABILITY
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
#endif



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
  int countThis = VAL_StringJc(ythis) & mLength_StringJc; 
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength_StringJc){
    countThis = strnlen_emC(strThis, mLength_StringJc);
  }
  value = parseIntRadix_emC(strThis, countThis, radix, &nrofCharsParsed, null);
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


#endif //DEF_NO_StringUSAGE
