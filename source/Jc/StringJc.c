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
#include "Fwc/fw_Exception.h"
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


/*
const struct{ ObjectArrayJc head; FieldJc data[2]; } fields_StringBuilderJc
=
{ CONST_ObjectArrayJc(FieldJc, 2, 0, null, &fields_StringBuilderJc)
, { CONST_FieldJc(StringBuilderJc, "count", count, int, 0)
  , CONST_FieldJc(StringBuilderJc, "count", count, int, 0)
} };

const ReflectionStringBuilderJc reflectionStringBuilderJc
=
{ { CONST_ObjectJc(0, &reflectionStringBuilderJc, null)
  , "StringBuilderJc"
  , 0 //posObjBase
  , sizeof(StringBuilderJc)
  , (FieldJcArray const*) &fields_StringBuilderJc
  , (MethodJcARRAY const*) null
  ,  null  //superClasses
  ,  null  //interfaces
  ,0 //modifiers
  }
, { null
  }
};
*/

/** Some methods from StringJc are defined in ObjectJc.h, because there are simple methods
  * not using RuntimeHeap, Garbage Collection and others. This simple methods are implemented here.
  * That are all methods which do not copy strings, only compare, convert to char* etc.
  */



/**reads the nrofChars and the reference into local variable. Static subroutine for inner organisation:*/
char const* getCharsAndCount_StringJc(const StringJc* ythis, int* count)
{ char const* chars = PTR_StringJc(*ythis);
  int nChars = value_OS_PtrValue(*ythis);
  if(nChars == mLength__StringJc) { nChars = strlen(chars); }

  *count = nChars;
  return( chars);
}





void clear_StringJc(StringJc* ythis)
{ STACKTRC_ENTRY("clear_StringJc");

  clearBackRefJc(ythis);
  if((VAL_StringJc(*ythis) & mThreadContext__StringJc) == mThreadContext__StringJc){
    releaseUserBuffer_ThreadContextFw(_thCxt);
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
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strlen_Fwc(strCmp, countThis+1); //more chars are not necessary.
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


bool equals_zI_StringJc(const StringJc ythis, const char* strCmp, int valueCmp  )
{ int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  int countCmp = valueCmp & mLength__StringJc;
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength__StringJc){
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strlen_Fwc(strCmp, countThis+1);
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
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strlen_Fwc(strCmp, countThis+1); //more chars are not necessary.
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
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strlen_Fwc(strCmp, countThis+1);
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
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strlen_Fwc(strCmp, countThis+1); //more chars are not necessary.
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
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strlen_Fwc(strCmp, countThis+1);
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
  int valueThis = value_OS_PtrValue(ythis);
  int count = valueThis & mLength__StringJc;
  const char* chars = PTR_OS_PtrValue(ythis, char const);
  STACKTRC_TENTRY("substring_StringJc");
  
  if(count == mLength__StringJc) { count = strlen(chars);}

  if(endIndex < 0) {endIndex = count; }

  if(endIndex > count){ THROW_s0(IndexOutOfBoundsException, "endIndex", endIndex); }
  else if(beginIndex <0 || beginIndex > endIndex){ THROW_s0(IndexOutOfBoundsException, "beginIndex", beginIndex); }
  else
  { int value = (endIndex - beginIndex)                //length 
              | (valueThis & mNonPersists__StringJc);  //non persistent only if the src is non-persistent.
    INIT_StringJc(ret, chars + beginIndex, value);
  }

  STACKTRC_LEAVE; return( ret);
}



METHOD_C int indexOf_CI_StringJc(StringJc ythis, int ch, int fromIndex)
{ const char* chars = PTR_OS_PtrValue(ythis, char const);
  int nChars = value_OS_PtrValue(ythis) & mLength__StringJc;
  //STACKTRC_TENTRY("StringJc.indexOf(int,int)");
  if(nChars == mLength__StringJc) { nChars = strlen(chars); }
  //const char* chars = getCharsAndCount_StringJc(ythis, &nChars);
  if(fromIndex <0)
  { //STACKTRC_LEAVE; 
    return( -1);
  }
  else
  { int ii;
    for(ii = fromIndex; ii < nChars; ii++)
    { if(chars[ii] == ch) 
      { //STACKTRC_LEAVE; 
        return( ii); 
      }
    }
    //STACKTRC_LEAVE; 
    return( -1);  //not found STACKTRC_LEAVE; return(s in for loop if found!
  }
}



int indexOf_sI_StringJc(StringJc ythis, StringJc str, int fromIndex)
{ int nChars;
  //STACKTRC_TENTRY("StringJc._Si_StringJc");
  { 
    const char* chars = getCharsAndCount_StringJc(&ythis, &nChars);
    int nCharsSearch;
    const char* charsSearch = getCharsAndCount_StringJc(&str, &nCharsSearch);
    if(fromIndex <0)
    { //STACKTRC_LEAVE; 
      fromIndex = 0; //In java it is so too.
    }
    //
    { int ii;
      char cc = charsSearch[0];
      for(ii = fromIndex; ii < (nChars - nCharsSearch) +1; ii++)
      { if(chars[ii] == cc)
        { //first char found, test the rest chars
          if(strncmp(charsSearch, chars+ii, nCharsSearch) == 0)
          { //STACKTRC_LEAVE; 
            return( ii);
          }
        }
      }
    }
    //STACKTRC_LEAVE; 
    return( -1);  //not found, note: return ii in for-loop if found.
  }
}



int lastIndexOf_CI_StringJc(StringJc ythis, int ch, int fromIndex )
{ const char* chars;
  int nChars;
  //STACKTRC_TENTRY("StringJc.indexOf(int,int)");
  chars = getCharsAndCount_StringJc(&ythis, &nChars);
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
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  if(countCmp == mLength__StringJc){
    countCmp = strlen_Fwc(strCmp, countThis+1); //more chars are not necessary.
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
  //if(sizeBuffer < size_StringJc(ythis,_thCxt)) THROW_s0(IndexOutOfBoundsException, "size to small", sizeBuffer);
  if(nrofChars > sizeBuffer) THROW_s0(IndexOutOfBoundsException, "buffer to small", sizeBuffer);
  if(nrofChars < 0) THROW_s0(IndexOutOfBoundsException, "srcEnd less than srcBegin", nrofChars);
  if(srcBegin < 0) THROW_s0(IndexOutOfBoundsException, "srcBegin <0", srcBegin);
  if(dstBegin < 0) THROW_s0(IndexOutOfBoundsException, "dstBegin <0", srcBegin);
  if((dstBegin + nrofChars) > sizeBuffer) THROW_s0(IndexOutOfBoundsException, "dstBegin fault", dstBegin);

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
  return ythis;
}





/**************************************************************************************************/
/* some conversions numeric from/to String */



int parseInt_radix_IntegerJc(StringJc ythis, int radix)
{ 
  int unusedChars;
  int value;
  int countThis = VAL_StringJc(ythis) & mLength__StringJc; 
  const char* strThis = PTR_StringJc(ythis);
  if(countThis == mLength__StringJc){
    countThis = strlen_Fwc(strThis, mLength__StringJc);
  }
  value = parseInt_Fwc(strThis, countThis, radix, &unusedChars);
  if(unusedChars >0){
    STACKTRC_ENTRY("parseInt_IntegerJc");
    THROW_s0(NumberFormatException, " rest:", unusedChars);
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
  //TODO
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
  //TODO
  return 0.0F;
}



