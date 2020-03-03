/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this software-package the LGPL Lesser General Public License, 
 * published by the Free Software Foundation is valid at first. 
 * This is valid, if no other special licence contract is agreed. It means: 
 * 1. You can use this source without any restriction for any desired purpose.  
 * 2. You can redistribute copies of this source to everybody.  
 * 3. Every user of this source, also the user of redistribute copies with or without payment, 
 *    must accept this license for further using.  
 * 4. But the LPGL ist not appropriate for a whole software product, 
 *    if this source is only a part of them. It means, the user must publish this part of source, 
 *    but don't need to publish the whole source of the own product.  
 * 5. You can study and modify (improve) this source for own using or for redistribution, 
 *    but you have to license the modified sources likewise under this LGPL Lesser General Public License.  
 * 6. You mustn't delete this Copyright/Copyleft inscription in this software package and in all source files. 
 *    If you need only a part of this software-package, you must place this Copyright/Copyleft inscription 
 *    at an easily noticeable position in the adequate file tree. 
 * 7. If you are changing and publishing the content of source files, 
 *    you mustn't delete the Copyright/Copyleft inscription inclusive the first author(s) in the source files. You have to write your changes and your name additionally in the description part for changes in the source files. If you use a part from source files as copy in your own files only, you have to name the author of that part of the sources in your sources. Furthermore you have to declare the usage of sources of the author in your product. 
 * Special licence agreements:
 *
 * If this software or a part of them will be used in a comprehensive software-package 
 * without free publishing of its content or usage, 
 * then a special licence agreement in any other form is possible and necessary. 
 * All developers and users of this software-package should agree to it, 
 * with subscribing a contract, which is stored by both partners in paper-written form. 
 * The state of existence of such a contract doesn't need to be published.
 * But a proper hint to the special licence agreement have to be stored at a position in the file-tree, 
 * which is able to visit from outside, if the content of the files are able to visit from outside too. 
 * If the sources and its usage and the licence is secrecy, it is okay too.
 *
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content This file contains the implementation of os_file.h for MS-Windows 
 *          using the lo-level un-buffered file-routines.
 * @version 0.94
 * list of changes:
 * 2010-05-23: JcHartmut creation from os_Windows/os_file.c, from the fopen-routines.
 *
 * This method bodies are placed inside Fwc because simple applications (ExceptionJc.c)
 * call only this method from string, without other dependencies.
 */

//Styleguide: Include the own header first, it should include all necessary depending headers itself. 
#include <emC/Base/String_emC.h>


#ifndef __NoCharSeqJcCapabilities__  
  //contains any function declarations here called:
  #include <emC/Jc/StringJc.h>
  //contains ObjectJc definition.
  #include <emC/Base/Object_emC.h>
#endif

//Styleguide: Include all necessities for implementation, the standard headers at least.
#include <string.h>   //strncpy
struct Mtbl_CharSeqJc_t;

extern ClassJc const reflection_StringBuilderJc;


int _length_PRIV_CharSeqJc(CharSeqJc thiz, ThCxt* _thCxt) {
  int val = VAL_AddrVal_emC(thiz) & mLength_StringJc;
  if (val == kIs_0_terminated_StringJc) {
    val = strnlen_emC(thiz.addr.str, kMaxNrofChars_StringJc);
  }
  if (val <= kMaxNrofChars_StringJc) return val;
#ifdef __NoCharSeqJcCapabilities__
  else {
    ASSERTJc(val == kIsStringBuilder_CharSeqJc);
    return length_StringBuilderJc(C_CAST(StringBuilderJc_s*, thiz.addr));
  }
#else
  else if (val == kIsStringBuilder_CharSeqJc) {
    return length_StringBuilderJc(thiz.addr.bu ); //reinterpret-cast it refers a StringBuilder.
  }
  else {
    CharSeqObjJc const* othiz = C_CAST(CharSeqObjJc const*, thiz.addr.obj);
    struct Mtbl_CharSeqJc_t const* mthiz = getMtbl_CharSeqJc(thiz, _thCxt);
    return mthiz->length(othiz, _thCxt);
  }
#endif
}




char _charAt_PRIV_CharSeqJc(CharSeqJc thiz, int pos, struct ThreadContext_emC_t* _thCxt)
{
  int val = VAL_AddrVal_emC(thiz) & mLength_StringJc;
  if (val == kIs_0_terminated_StringJc) {
    val = strnlen_emC(thiz.addr.str, kMaxNrofChars_StringJc);
  }
  if (val <= kMaxNrofChars_StringJc) {
    if (pos <= val) return thiz.addr.str[pos];
    else {
      STACKTRC_ENTRY("charAt_CharSeqJc");
      THROW1_s0(IndexOutOfBoundsException, "", pos);
      STACKTRC_LEAVE;
      return 0;
    }
  }
#ifdef __NoCharSeqJcCapabilities__
  else {
    ASSERTJc(val == kIsStringBuilder_CharSeqJc);
    return charAt_StringBuilderJc(C_CAST(StringBuilderJc_s*, thiz.addr), pos, _thCxt);
  }
#else
  else if (val == kIsStringBuilder_CharSeqJc) {
    return charAt_StringBuilderJc(thiz.addr.bu, pos, _thCxt);
  }
  else {
    CharSeqObjJc const* othiz = C_CAST(CharSeqObjJc const*, thiz.addr.obj);
    struct Mtbl_CharSeqJc_t const* mthiz = getMtbl_CharSeqJc(thiz, _thCxt);
    return mthiz->charAt(othiz, pos, _thCxt);
  }
#endif
}

void ctor_addSize_StringBuilderJc(StringBuilderJc_s* thiz, int addSize)
{ STACKTRC_ENTRY("ctor_addSize_StringBuilderJc");
  iniz_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz) + addSize, &reflection_StringBuilderJc, 0);
  int size1 = sizeof(thiz->value) + addSize;
  ASSERTs_emC(size1 >=0 && size1 < 0x7fff, "faulty size for StringBuilder", size1, 0);
  thiz->size = (int16)(size1);
  thiz->_mode = 0;  //no mode bits yet initialize
  thiz->_count = 0;
  memset(thiz->value.direct, 0, thiz->size);  //guaranteed 0-terminated NOTE it should be assumed that the instance is set to 0
  STACKTRC_LEAVE;
}

void ctor_Buffer_StringBuilderJc(StringBuilderJc_s* thiz, char* buffer, int size)
{ STACKTRC_ENTRY("ctor_Buffer_StringBuilderJc");
  iniz_ObjectJc(&thiz->base.object, thiz, sizeof(*thiz), &reflection_StringBuilderJc, 0);
  ASSERTs_emC(size >=0 && size < 0x7fff, "faulty size for StringBuilder", size, 0);
  thiz->size = (int16)(-size);
  thiz->_mode = 0;  //no mode bits yet initialize
  thiz->_count = 0;
  thiz->value.buffer = buffer;  //guaranteed 0-terminated NOTE it should be assumed that the instance is set to 0
  memset(buffer, 0, size);
  STACKTRC_LEAVE;
}








METHOD_C void clear_StringBuilderJc(StringBuilderJc_s* thiz)
{
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int size = (thiz->size < 0 ? -thiz->size : thiz->size);
  memset(buffer, 0, size);
  thiz->_count = 0;
}




char charAt_StringBuilderJc(StringBuilderJc_s const* thiz, int index, ThCxt* _thCxt)
{
  char const* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int count = thiz->_count;
  STACKTRC_TENTRY("charAt_StringBuilderJc");
  if (index < 0 || index >= count) THROW1_s0(IndexOutOfBoundsException, "", index);
  STACKTRC_LEAVE; return buffer[index];
}




void setCharAt_StringBuilderJc(StringBuilderJc_s* thiz, int index, char ch, ThCxt* _thCxt)
{
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int size = (thiz->size < 0 ? -thiz->size : thiz->size);
  STACKTRC_TENTRY("setCharAt_StringBuilderJc");

  if (index >= size || index <0)
  { //StringJc msg = s0_StringJc("StringBuffer to many chars");
    THROW1_s0(IndexOutOfBoundsException, "index fault", index);
  }
  buffer[index] = ch;

  STACKTRC_LEAVE;
}




/**reads the nrofChars and the reference into local variable. Static subroutine for inner organisation:*/
char* getCharsAndSize_StringBuilderJc(StringBuilderJc_s* thiz, int* size)
{
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  *size = (thiz->size < 0 ? -thiz->size : thiz->size);
  return(buffer);
}


char* XXXXXXXchars_StringBuilderJc(StringBuilderJc_s* thiz)
{
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  return(buffer);
}


char const* getCharsAndCount_StringBuilderJc(StringBuilderJc_s const* thiz, int* count)
{
  char const* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  //*count = (thiz->count < 0 ? -thiz->count : thiz->count);
  *count = thiz->_count;
  ;
  return(buffer);
}

char* getCharsSizeCount_StringBuilderJc(StringBuilderJc_s* thiz, int* size, int* count)
{
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  *size = (thiz->size < 0 ? -thiz->size : thiz->size);
  //*count = (thiz->count < 0 ? -thiz->count : thiz->count);
  *count = thiz->_count;
  return(buffer);
}


void _setCount_StringBuilderJc(StringBuilderJc_s* thiz, int count)
{
  thiz->_count = (int16)((thiz->_count & ~mLength_StringJc) | count);
}




int capacity_StringBuilderJc(StringBuilderJc_s* thiz)
{
  if (thiz->size < 0) return -thiz->size - 1;
  else return thiz->size - 1;
}






bool setTruncateMode_StringBuilderJc(StringBuilderJc_s* thiz, bool bTruncate)
{
  bool bRet = thiz->_mode & _mNoException_StringBuilderJc;
  if (bTruncate) { thiz->_mode |= _mNoException_StringBuilderJc; }
  else { thiz->_mode &= ~_mNoException_StringBuilderJc; }
  return bRet;
}


bool wasTruncated_StringBuilderJc(StringBuilderJc_s* thiz)
{
  bool bRet = (thiz->_mode & _mTruncated_StringBuilderJc) != 0;
  thiz->_mode &= ~_mTruncated_StringBuilderJc;
  return bRet;
}





int copyToBuffer_StringBuilderJc(StringBuilderJc_s const* thiz, int start, int end, char* buffer, int zBuffer)
{
  int count;
  char const* src;
  STACKTRC_ENTRY("copy_StringBuilderJc");
  src = getCharsAndCount_StringBuilderJc(thiz, &count);
  if (count >= (zBuffer - 1)) {
    if (thiz->_mode & _mNoException_StringBuilderJc) {
      count = zBuffer - 1;
    }
    else THROW1_s0(IndexOutOfBoundsException, "string to long", count);
  }
  memcpy(buffer, src, count);
  buffer[count] = 0;
  STACKTRC_LEAVE; return count;
}




int copyToBuffer_CharSeqJc(const StringJc thiz, int start, int end, char* buffer, int sizeBuffer, struct ThreadContext_emC_t* _thCxt)
{ //STACKTRC_ENTRY("copyToBuffer_CharSeqJc");
  int nChars = VAL_StringJc(thiz) & mLength_StringJc;
  if (nChars == kIs_0_terminated_StringJc || nChars <= kMaxNrofChars_StringJc) {
    return copyToBuffer_StringJc(thiz, start, end, buffer, sizeBuffer);
  }
  else if (nChars == kIsStringBuilder_CharSeqJc) {
    StringBuilderJc_s const* sb = thiz.addr.bu;
    //STACKTRC_LEAVE; 
    return copyToBuffer_StringBuilderJc(sb, start, end, buffer, sizeBuffer);
  }
  else {
#ifdef __NoCharSeqJcCapabilities__  
    return 0;  //not used.
#else 
    //all other values determines a CharSeqJc-interface-instance:
    //It is any ObjectJc which is a CharSeqJc
    Mtbl_CharSeqJc const* mc = getMtbl_CharSeqJc(thiz, _thCxt);
    CharSeqObjJc const* othiz = C_CAST(CharSeqObjJc const*, thiz.addr.obj);
    int iChars, end1;
    end1 = mc->length(othiz, null); //_thCxt);  
    if (end < 0) { end1 = end1 - (-end) + 1; }
    if (end - start > sizeBuffer) { end = start + sizeBuffer; }
    for (iChars = start; iChars < end1; ++iChars) {
      char cc = mc->charAt(othiz, iChars, null); //_thCxt);
      buffer[iChars] = cc;
    }
    for (iChars = end1 - start; iChars < sizeBuffer; ++iChars) {
      buffer[iChars] = 0;  //fill rest with 0.
    }
    return end1 - start;
#endif
  }





  if (nChars & mIsCharSeqJcMtbl_CharSeqJc) {
    STACKTRC_ENTRY("copyToBuffer_StringJc");
    THROW1_s0(IllegalArgumentException, "Use copyToBuffer_CharSeqJc", 0);
    STACKTRC_LEAVE;
  }
  //STACKTRC_LEAVE;
  return(nChars);
}








//central replace routine.
StringBuilderJc_s* replace_cII_StringBuilderJc(StringBuilderJc_s* thiz, int start, int end, CharSeqJc add, int from, int to, ThCxt* _thCxt)
{
  int countNew;
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int size = (thiz->size < 0 ? -thiz->size : thiz->size); //size of the buffer
  int count = thiz->_count;
  int start1, end1;
  int from1, to1;
  int nInsert;  //nr of chars to insert netto
  int nDelete;
  int zadd;
  char const* padd;
#ifndef __NoCharSeqJcCapabilities__
  Mtbl_CharSeqJc const* madd = null;
#endif
  STACKTRC_TENTRY("replace_zI_StringBuilderJc");
  if (thiz->_mode & _mStringBuilt_StringBuilderJc) {
    THROW1_s0(IllegalStateException, "Buffer was used in StringJc", (int)(intptr_t)buffer);
  }
  //
  //determine type of add, zadd, padd, madd:
  { int valAdd = VAL_AddrVal_emC(add) & mLength_StringJc;
  if (valAdd == kIs_0_terminated_StringJc) {
    valAdd = strnlen_emC(add.addr.str, kMaxNrofChars_StringJc);
  }
  if (valAdd <= kMaxNrofChars_StringJc) {
    padd = add.addr.str;
    zadd = valAdd;
  }
  else if (valAdd == kIsStringBuilder_CharSeqJc) {
    StringBuilderJc_s const* buAdd = add.addr.bu;
    zadd = buAdd->_count;
    padd = buAdd->size < 0 ? buAdd->value.buffer : buAdd->value.direct;
  }
#ifdef __NoCharSeqJcCapabilities__
  else ASSERTJc(false);
#else
  else {
    CharSeqObjJc const* oadd = C_CAST(CharSeqObjJc const*, add.addr.obj);
    madd = getMtbl_CharSeqJc(add, _thCxt);
    zadd = madd->length(oadd, _thCxt);
    padd = null;
  }
#endif
  }
  //
  if (start < 0) { //-1... counts from end, -1 is the end position.
    start1 = count - (-start) + 1;
    if (start1 < 0) {
      //set start1 to a admissible value if THROW longs only the error.
      start1 = 0; THROW1_s0(IndexOutOfBoundsException, "faulty -start", start);
    }
  }
  else if (start > count) {
    start1 = count; THROW1_s0(IndexOutOfBoundsException, "faulty start", start);
  }
  else {
    start1 = start;
  }
  if (end < 0) { //-1... counts from end, -1 is the end position.
    end1 = count - (-end) + 1;
    if (end1 < start1) { end1 = start1; THROW1_s0(IndexOutOfBoundsException, "faulty -end", end); }
  }
  else if (end > count) {
    end1 = count; THROW1_s0(IndexOutOfBoundsException, "faulty end", end);
  }
  else if (end == 0) {  //it means, delete 0
    end1 = start1;
  }
  else if (end < start1) {
    end1 = start1; THROW1_s0(IndexOutOfBoundsException, "faulty end before start", end);
  }
  else {
    end1 = end;
  }
  if (from < 0) { //-1... counts from end, -1 is the end position.
    from1 = zadd - (-from) + 1;
    if (from1 < 0) { from1 = 0; THROW1_s0(IndexOutOfBoundsException, "faulty -from", from); }
  }
  else if (from > count) {
    from1 = count; THROW1_s0(IndexOutOfBoundsException, "faulty from", from);
  }
  else {
    from1 = from;
  }
  if (to < 0) { //-1... counts from end, -1 is the end position.
    to1 = zadd - (-to) + 1;
    if (to1 < from1) {
      to1 = from1; THROW1_s0(IndexOutOfBoundsException, "faulty -to", to);
    }
  }
  else if (to > zadd) {
    to1 = count; THROW1_s0(IndexOutOfBoundsException, "faulty to", to);
  }
  else if (to < from1) {
    to1 = from1; THROW1_s0(IndexOutOfBoundsException, "faulty to before from", to);
  }
  else {
    to1 = to;
  }

  nDelete = end1 - start1;  //maybe 0
  nInsert = to1 - from1;
  int nMove = nInsert - nDelete;  //maybe negative if more deleted.
  countNew = count + nMove;  //maybe lesser or greater
  if (countNew > size)
  { //in opposite to Java the StringBuffer isnot increased, no dynamically memory management.
    //TODO perhaps test whether it is possible
    if (thiz->_mode & _mNoException_StringBuilderJc) {
      thiz->_mode |= _mTruncated_StringBuilderJc;
      nInsert = size - count;
      countNew = size;

    }
    else {
      THROW1_s0(RuntimeException, "StringBuffer too many chars", countNew);
    }
  }
  { int nRest = count - start1 + nDelete;  //nr of chars from end of replace area to actual end
  if (nRest > 0) memmove(buffer + start1 + nMove, buffer + start1 + nDelete, nRest);  //moves in both directions
  }
  //The area to replace is free.
  if (nInsert >0) {
    if (padd != null) {
      memcpy(buffer + start1, padd + from1, nInsert);
    }
    else {
#ifdef __NoCharSeqJcCapabilities__
      THROW1_s0(RuntimeException, "null add", 0);
#else
      //a really char seq
      int iDst = 0;
      int iAdd;
      for (iAdd = from1; iAdd < to1; ++iAdd) {
        char cc = charAt_CharSeqJc(add, iAdd, _thCxt);
        buffer[start1 + iDst] = cc;
        iDst += 1;
      }
#endif 
    }
  }
  thiz->_count = (int16)((thiz->_count & ~mLength_StringJc) | countNew);

  STACKTRC_LEAVE; return(thiz);
}


#ifndef __NoCharSeqJcCapabilities__


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
    THROW1_s0(IllegalArgumentException, "thiz does not implement the CharSeqJc interface.", (int)(intptr_t)othiz);
    STACKTRC_LEAVE;
	  return z_CharSeqJc("faulty instance ");
  }
  SET_StringJc(ret, (char const*)othiz, val);
  return ret;
}







int32 length_StringJc_CharSeqJc_F(CharSeqObjJc const* ithiz, ThCxt* _ThCxt)
{ StringJc_CharSeqJc const* thiz = (StringJc_CharSeqJc const*)ithiz;
  return thiz->length;
}

char charAt_StringJc_CharSeqJc_F(CharSeqObjJc const* ithiz, int32 ix, ThCxt* _thCxt)
{ StringJc_CharSeqJc const* thiz = (StringJc_CharSeqJc const*)ithiz;
  if(ix < 0 || ix >= thiz->length) {
    //THROW
    return 0;
  }
  return thiz->s[ix];
}

CharSeqJc subSequence_StringJc_CharSeqJc_F(CharSeqObjJc const* ithiz, int32 from, int32 to, ThCxt* _thCxt)
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

static Mtbl_CharSeqJc mtbl_StringJc_CharSeqJc =
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
  int nChars = VAL_CharSeqJc(thiz) & mLength_StringJc;
  ObjectJc const* othiz = thiz.addr.obj;
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
  ASSERT_s0_Jc(head->sign == sign_Mtbl_CharSeqJc, "faulty Mtbl of CharSeqJc", (int)(intptr_t)(thiz.addr.obj));
  mc = (Mtbl_CharSeqJc const*) head;
  return mc;

}


CharSeqJcMTB getMtblRef_CharSeqJc(CharSeqJc thiz, StringJc_CharSeqJc* dst_StringJc, ThCxt* _thCxt)
{ CharSeqJcMTB ret;
  int val = VAL_CharSeqJc(thiz) & mLength_StringJc;
  if(val == kIs_0_terminated_StringJc) {
    val = strnlen_emC(thiz.addr.str, kMaxNrofChars_StringJc);
  }

  if(val <= kMaxNrofChars_StringJc) {
    //A String, use the given instance of dst_StringJc
    if(dst_StringJc !=null) {
      memset(dst_StringJc, 0, sizeof(StringJc_CharSeqJc));
      iniz_ObjectJc(&dst_StringJc->base, &dst_StringJc->base, sizeof(StringJc_CharSeqJc), null, 0);
      dst_StringJc->s = thiz.addr.str;
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
    ret.ref = thiz.addr.obj;
    ret.mtbl  = (Mtbl_CharSeqJc const*)checkMtbl_ObjectJc(ret.ref, val & mMtbl_CharSeqJc, sign_Mtbl_CharSeqJc, _thCxt);
  }
  else {
    //Any Object, may be a StringBuilder too.
    ObjectJc const* othiz = thiz.addr.obj;
    Mtbl_CharSeqJc const* mthiz = (Mtbl_CharSeqJc const*)getMtbl_ObjectJc(othiz, sign_Mtbl_CharSeqJc);
    ret.mtbl = mthiz;
    ret.ref = othiz;
  }
  return ret;
}




StringJc toString_CharSeqJc(CharSeqJc thiz)
{
  STACKTRC_ENTRY("toString_CharSeqJc");
  int val = VAL_AddrVal_emC(thiz);
  if(val == kIsStringBuilder_CharSeqJc) {
    StringBuilderJc_s const* sb = thiz.addr.bu;
    char const* buffer = chars_StringBuilderJc(sb);
    int nChars = length_StringBuilderJc(sb);
    StringJc ret = CONST_StringJc(buffer, nChars);
    STACKTRC_LEAVE; return ret;
  }
  else if(val & mIsCharSeqJcMtbl_CharSeqJc) {
    Mtbl_CharSeqJc const* mc = getMtbl_CharSeqJc(thiz, _thCxt);
    CharSeqObjJc const* othiz = C_CAST(CharSeqObjJc const*, thiz.addr.obj);
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



#endif





//METHOD_C StringJc toString_StringBuilderJc(StringBuilderJc_s* src, ThCxt* _thCxt)
METHOD_C StringJc toStringNonPersist_StringBuilderJc(ObjectJc* othis, ThCxt* _thCxt)
{
  StringJc ret = NULL_StringJc;
  STACKTRC_TENTRY("toStringNonPersist_StringBuilderJc");
  { StringBuilderJc_s* ythis = SIMPLE_CAST(StringBuilderJc_s*, othis);  //admissible because the method is only called for StringBuilderJc_s
    const char* s0 = ythis->size < 0 ? ythis->value.buffer : ythis->value.direct;
    int count = ythis->_count;
    /**Detect whether the buffer is found in the stack range. Than its memory address is
     * between any address of a local variable and the Thread-Context pointer. */
    bool bufferInStack = ADDR_IN_STACK_ThreadContext_emC(s0);
    int nonPersistent = 0;
    /**A StringJc is designated as non-persistence, if the StringJc referes a location in a change-able buffer. */
    //xx int nonPersistent = ythis->_mode & _mTemporary_StringBuilderJc ? 0 : mNonPersists__StringJc;
    if(bufferInStack || ythis->_mode & (_mStack_StringBuilderJc | _mThread_StringBuilderJc)){
      nonPersistent |= mNonPersists__StringJc;
    }
    if(ythis->_mode & _mThread_StringBuilderJc){
      nonPersistent |= mThreadContext__StringJc;
      int sizeInThCxt = _reduceCapacity_StringBuilderJc(ythis, (int16)(ythis->_count+1));
      reduceLastUserBuffer_ThreadContext_emC(ythis, sizeInThCxt, _thCxt);
    }
    /**If the StringBuffer is a temporary, the String is persistence because the buffer is not use anywhere else.
     * Elsewhere the String is not persistant. That is okay mostly.
     * If the String will be stored persistent, it would be copied than.
     */
    SET_StringJc(ret, s0, count | nonPersistent);

    //false, because it isn't a reference in data: setFromBuffer_StringJc(&ret, ythis);  //the String is contained in the Buffer.
  }
  STACKTRC_LEAVE; return ret;
}





//Used for Mtbl for interface CharSeqJc
static int32 length_StringBuilderJc_F(CharSeqObjJc const* thiz, ThCxt* _thCxt){ return ((StringBuilderJc_s const*)thiz)->_count; }

static char charAt_StringBuilderJc_F(CharSeqObjJc const* othiz, int32 ix, ThCxt* _thCxt){
  StringBuilderJc_s const* thiz = (StringBuilderJc_s const*)othiz;
  char const* chars = chars_StringBuilderJc(thiz);
  if(ix < 0 || ix >= thiz->_count) { THROW1_s0(IndexOutOfBoundsException, "faulty indices", ix); return 0; }
  else return chars[ix];
}

static CharSeqJc subSequence_StringBuilderJc_F(CharSeqObjJc const* othiz, int32 from, int32 to, ThCxt* _thCxt)
{ StringBuilderJc_s const* thiz = (StringBuilderJc_s const*)othiz;
  CharSeqJc ret = {0};
  if(from > 0 && from <= to && to <= thiz->_count) {
    ret.addr.str = null; //TODO
  }
  else THROW1_s0(IndexOutOfBoundsException, "faulty indices", to);
  return ret;
}




static const char sign_Mtbl_StringBufferJc[] = "StringBufferJc"; //to mark method tables of all implementations


const MtblDef_StringBufferJc mtblStringBufferJc = {
{
  { sign_Mtbl_StringBufferJc //J2C: Head of methodtable of Part_StringPartJc
  , (struct Size_Mtbl_t*)((0 +2) * sizeof(void*)) //J2C:size. NOTE: all elements has the size of void*.
  }
, { { sign_Mtbl_ObjectJc//J2C: Head of methodtable.
    , (struct Size_Mtbl_t*)((5 +2) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
    }
    , clone_ObjectJc_F //clone
    , equals_ObjectJc_F //equals
    , finalize_ObjectJc_F //finalize
    , hashCode_ObjectJc_F //hashCode
    , toStringNonPersist_StringBuilderJc //toString
  }
, { { sign_Mtbl_CharSeqJc//J2C: Head of methodtable.
    , (struct Size_Mtbl_t*)((5 +1) * sizeof(void*)) //size. NOTE: all elements are standard-pointer-types.
    }
    , length_StringBuilderJc_F
    , charAt_StringBuilderJc_F
    , subSequence_StringBuilderJc_F
  }
}
, { signEnd_Mtbl_ObjectJc, null } }; //Mtbl






#ifdef __ObjectJc_simple__
ClassJc const reflection_StringBuilderJc = { 0 };
#else
#include <emC/Jc/ReflectionJc.h>




/**Define the reflection in that source, which used it. */
const struct Reflection_Fields_StringBuilderJc_t
{
  ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_StringBuilderJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_StringBuilderJc)
,{
  { "_count"
  , 0 //nrofArrayElements
  , REFLECTION_int16
  , (2 << kBitPrimitiv_Modifier_reflectJc) //bitModifiers
  , (int16)((intptr_t)(&((StringBuilderJc_s*)(0x1000))->_count) -  0x1000)
  , 0  //offsetToObjectifcBase
  , &reflection_StringBuilderJc
  }
  ,{ "size"
  , 0 //nrofArrayElements
  , REFLECTION_int16
  , (2 << kBitPrimitiv_Modifier_reflectJc) //bitModifiers
  , (int16)((intptr_t)(&((StringBuilderJc_s*)(0x1000))->size) -  0x1000)
  , 0  //offsetToObjectifcBase
  , &reflection_StringBuilderJc
  }
  ,{ "_mode"
  , 0 //nrofArrayElements
  , REFLECTION_int32
  , (4 << kBitPrimitiv_Modifier_reflectJc) //bitModifiers
  , (int16)((intptr_t)(&((StringBuilderJc_s*)(0x1000))->_mode) -  0x1000)
  , 0  //offsetToObjectifcBase
  , &reflection_StringBuilderJc
  }
  ,{ "value"
  , 0 //nrofArrayElements
  , REFLECTION_void
  , (4 << kBitPrimitiv_Modifier_reflectJc) //bitModifiers
  , (int16)((intptr_t)(&((StringBuilderJc_s*)(0x1000))->value) -  0x1000)
  , 0  //offsetToObjectifcBase
  , &reflection_StringBuilderJc
  }
} };


const ClassJc reflection_StringBuilderJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_StringBuilderJc, &reflection_ClassJc)
, "StringBuilderJc_s"
, 0
, sizeof(StringBuilderJc_s)
, (FieldJcArray const*)&reflection_Fields_StringBuilderJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0
#ifndef __NoCharSeqJcCapabilities__  
, &mtblStringBufferJc.mtbl.head
#endif
};



#define reflection_StringBuilderJc_s reflection_StringBuilderJc
DEFINE_REFLECTION_REF(StringBuilderJc);


#endif

