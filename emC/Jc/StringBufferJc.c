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
 * @version 0.91
 * @content Implementation of Routines for buffered strings.
 * @author Hartmut Schorrig, www.vishia.org
 *
 * list of changes:
 * 2009-06-14: Hartmut: corr: ctorO_StringBuffer uses the given buffer where Object is contained.
 * 2006-05-00: JcHartmut creation
 *
 ****************************************************************************/
#include <applstdef_emC.h>

#include "emC/Jc/StringJc_intern.h"
#include <emC/Jc/ObjectJc.h>
#include <emC/Base/Formatter_emC.h> 
#include <emC/Jc/ReflectionJc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>  //using sprintf
#include <stdarg.h>

extern ClassJc const refl_StringBuilderJc; 
/**
  Strings are necessary in control applications for
  <ul><li>Assignment of warning and error messages with some data,<li>
      <li>some other small things,</li>
  </ul>
  but not to process large string problems. Thats while the maximum number of chars
  may be limited to less than 32000, typical there are 250 or 1000 chars.<br/>
  Strings may be:
  <ul><li>contant string literals, written in form "fix string",</li>
      <li>parts of a given string (from method String.substring)</li>
      <li>Strings in a buffer, managed by StringbufferJc.</li>
  </ul>
  In all this cases the string is identified with the pointer to the chars and the
  actual length. The C-convention: identification of a string by a zero-terminated
  array of chars, is not the matching solution, because only constant strings
  or the whole string in a buffer may be identified in this manner.<br>
  Because a string may be also a part of a content of StringBuilderJc_s, the followed rule
  is found:
  <ul><li>If the string is a constant string, the pointer to the array of chars is stored
          in <code>value</code> and the number of chars is stored in <code>count</code>.
          The <code>offset</code> is set to <code>-1</code>.</li>
      <li>If the string is a part or the whole content of the buffer in StringBuilderJc_s,
          The <code>value</code> pointered the start of buffer in the StringBuilderJc_s.
          The adress of the StringBuilderJc_s-Structur is ascertainable by subtraction of the
          difference between the Buffer inside a StringBuilderJc_s and the StringBuilderJc_s.
          The <code>offset</code>-Attribute is used to pointer the position inside buffer.
          </li>
  </ul>
  A StringBuilderJc_s must known if a StringJc is referenced to it, by two causes:
  <ul><li>For garbage collection: A string should be handled like a reference.</li>
      <li>If a CharSeqJc references the StringBuilderJc_s and a change of the StringBuilderJc_s
          will proceed, the StringBuilderJc_s should copied in a new memory area and than modified,
          to held the content for pointering strings constant.</li>
  </ul>
  This requested knowledge is realized in StringBuilderJc_s by using the array of back-references,
  see RuntimeHeapJc, and by query a flag in the StringBuilderJc_s-attributes.
*/






StringBuilderJc_s* ctorM_StringBuilderJc(MemC rawMem)
{ StringBuilderJc_s* ythis = ADDR_MemC(rawMem, StringBuilderJc_s) ;
  int size;
  STACKTRC_ENTRY("ctorM_StringBuilderJc");
  /**The size of the rest, inclusive start of string in value. */
  size = size_MemC(rawMem) - (int)sizeof(StringBuilderJc_s) + (int)sizeof(ythis->value);
  if(size < 20) THROW1_s0(IllegalArgumentException, "ctor mem-size insufficient", size_MemC(rawMem));
  CTOR_ObjectJc(&ythis->base.object, ythis, size_MemC(rawMem), refl_StringBuilderJc, 0);  //immediately buffer
  ythis->size = (int16)size; //positive value because immediately String  
  //ctorc_s0i_StringBuilderJc(ythis, buffer, size);
  return ythis;
}



/** 2008-12-24: written new without call of sub-ctor, with regarding value direct.
 *  2009-06-15: Note: don't use it in future, 
 *              because the behavior of referencing the buffer is ambiguously depend on the size and amount of memory in othis. 
 *              If the amount of memory is matching to size, the ctorO_StringBuilderJc works proper. The variant is not neccessary.
 *              This variant may allocate a buffer always itself, but it is another concept.
 */
StringBuilderJc_s* ctorO_I_StringBuilderJc(ObjectJc* othis, int size, ThCxt* _thCxt)
{ StringBuilderJc_s* ythis = (StringBuilderJc_s*)othis;
  int sizeObj;
  STACKTRC_TENTRY("ctorO_I_StringBuilderJc");
  CHECKinit_ObjectJc(othis, sizeof(StringBuilderJc_s), refl_StringBuilderJc, 0); 
  sizeObj = getSizeInfo_ObjectJc(othis);
  ythis->_count = 0;
  if(sizeObj >= (int)(sizeof(StringBuilderJc_s) - sizeof(ythis->value) + size ))
  { //enaugh size for StringBuilderJc_s-control structure and the buffer itself:
    ythis->size = (int16)size;  //positiv: use value as buffer direct
    memset(&ythis->value, 0, size);  
    //MemC mem = build_MemC(newObj, sizeObj);
    //return ctorc_s0i_StringBuilderJc((StringBuilderJc_s*)newObj, (char*)address_MemC(mem, sizeof(StringBuilderJc_s),0), size);
  }
  else
  { //not enaugh size:
    STRUCT_AddrVal_emC(mBuffer, char); ALLOC_MemC(mBuffer, size);
    ythis->size =(int16)(ythis->size-size);
    ythis->value.buffer = mBuffer.addr;
  }
  STACKTRC_LEAVE; return ythis;
}



StringBuilderJc_s* ctorO_StringBuilderJc(ObjectJc* othis, ThCxt* _thCxt)
{ int sizeObj = getSizeInfo_ObjectJc(othis);
  StringBuilderJc_s* ythis = (StringBuilderJc_s*)othis;
  int sizeBuffer = sizeObj - sizeof(StringBuilderJc_s) + sizeof(ythis->value);
  STACKTRC_TENTRY("ctorO_StringBuilderJc");
  CHECKinit_ObjectJc(othis, sizeObj, refl_StringBuilderJc, 0); 
  if(sizeBuffer <=4)
  { /**The StringBuffer has not a direct Buffer: */
    MemC mem = getRestBlock_ObjectJc(othis, -2, _thCxt);  //possible it may be inside a block of a BlockHeap
    sizeBuffer = size_MemC(mem);
    if(sizeBuffer >0)
    { ythis->value.buffer = PTR_MemC(mem, char);
      ythis->size = (int16)(-sizeBuffer); //negative value because immediately String  
    }
    else
    { THROW1_s0(IllegalArgumentException, "initial Buffer size necessary", sizeBuffer);
    } 
  }
  else
  {
    ythis->size = (int16)sizeBuffer; //positive value because immediately String  
  }
  STACKTRC_LEAVE; return ythis;
}



StringBuilderJc_s* ctorO_cs_StringBuilderJc(ObjectJc* othis, CharSeqJc src, ThCxt* _thCxt)
{ StringBuilderJc_s* ythis;
  int zSrc = length_CharSeqJc(src, _thCxt);
  //if(zSrc == mLength_StringJc){ zSrc = strnlen_emC(PTR_StringJc(src), mLength_StringJc); }
  ythis = ctorO_I_StringBuilderJc(othis, zSrc+16, _thCxt);
  return append_c_StringBuilderJc(ythis, src, _thCxt);
}



StringBuilderJc_s* ctorO_zI_StringBuilderJc(ObjectJc* yObj, char* buffer, int size, ThCxt* _thCxt)
{ StringBuilderJc_s* ythis = (StringBuilderJc_s*)yObj;
  int count;
  STACKTRC_TENTRY("ctorO_CI_StringBuilderJc");
  CHECKinit_ObjectJc(yObj, sizeof(StringBuilderJc_s), refl_StringBuilderJc, 0); 
  if(size < 0)
  { size = -size;
  }
  ythis->size = (int16)(-size);  //negative to sign it is a refernce.
  count = strnlen_emC(buffer, size-1);  //from the given content
  if(count >= size)
  { count = size-1; }        //but never greater than given size. The content may be a part of 0-terminate C-String.
  ythis->_count= (int16)count;
  ythis->value.buffer = buffer;
  STACKTRC_LEAVE; return ythis;

}




#ifdef DEF_ClassJc_Vtbl
void finalize_StringBuilderJc_F(ObjectJc* othis, ThCxt* _thCxt)
{ StringBuilderJc_s* ythis = (StringBuilderJc_s*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("finalize_StringBuilderJc_F");
  finalize_ObjectJc_F(&ythis->base.object, _thCxt);      //finalizing the superclass.
  STACKTRC_LEAVE;
}
#endif //def DEF_ClassJc_Vtbl






#ifdef DEF_ThreadContext_HEAP_emC
/**common method for creating and initilizing buffers in threadcontext. 
 * It is static, don't use outside.
 * @return pointer to StringBuilderJc_s or StringBuilderJcpp, therefore the return type is void*. Cast it outside.
 */
static void* getThreadBuffer_StringBuilderJc(bool bCpp, char const* sign, ThCxt* _thCxt)
{ 
  StringBuilderJc_s* sBuffer;
  #if defined(__cplusplus) && defined(__CPLUSPLUSJcpp)
    StringBuilderJcpp* sBufferJcpp;
    int sizeStringBuilderJcpp = sizeof(StringBuilderJcpp);  //regard it at start of area.
  #else
    int sizeStringBuilderJcpp = 0;  //not present!
  #endif
  STACKTRC_TENTRY("threadBuffer_StringBuilderJc");
  {
    MemC mBuffer = getUserBuffer_ThreadContext_emC(0, sign, _thCxt);
    /**Check whether the buffer is in use, TODO... */
    int sizeBufferThreadContext = size_MemC(mBuffer);
    int sizeStringBuffer = sizeBufferThreadContext/2 - sizeStringBuilderJcpp;
    int posBuffer = 0; //(nr == 1 ? sizeBufferThreadContext/2 : 0);

    ObjectJc* othis = (ObjectJc*)addOffset_MemC(mBuffer, posBuffer + sizeStringBuilderJcpp);
    checkAddress_MemC(&mBuffer, othis, sizeStringBuffer);
    CTOR_ObjectJc(othis, othis, sizeStringBuffer, refl_StringBuilderJc, 0);
    sBuffer = ctorO_StringBuilderJc(othis, _thCxt);
    setStringConcatBuffer_StringBuilderJc(sBuffer);     //the buffer is used temporary, it is so, prevent additional copy of String 
    sBuffer->_mode |= _mThread_StringBuilderJc;
    #if defined(__cplusplus) && defined(__CPLUSPLUSJcpp)
      int sizeBuffer;
      char* charBuffer = getCharsAndSize_StringBuilderJc(sBuffer, &sizeBuffer);
      StringBuilderJcpp copyInstance(charBuffer, sizeBuffer);  //the ctor will be execute.
      sBufferJcpp = reinterpret_cast<StringBuilderJcpp*>(address_MemC(mBuffer, posBuffer, sizeof(StringBuilderJcpp)));
      /**TRICKY: to initialize a instance in a given mem area, create it in stack and copy the content.
       * The virtual table will be addressed correct. This procedure is only able to use, 
       * if the instance doesn't contain or store any reference to the instance.
       * It is able to use by StringBuilderJcpp, not commonly!
       */
      memcpy(sBufferJcpp, &copyInstance, sizeof(StringBuilderJcpp));
   
    #endif
  }
  STACKTRC_LEAVE; 
  if(bCpp)
  {
    #if defined(__cplusplus) && defined(__CPLUSPLUSJcpp)
      return sBufferJcpp;
    #else
      return null;  //not supported.
    #endif
  }
  else
  { return( sBuffer);
  }
}



StringBuilderJc_s* threadBuffer_StringBuilderJc(char const* sign, ThCxt* _thCxt)
{ return (StringBuilderJc_s*)getThreadBuffer_StringBuilderJc(false, sign, _thCxt);
}

StringBuilderJc_s* threadBuffer_s_StringBuilderJc(CharSeqJc src, char const* sign, ThCxt* _thCxt)
{ StringBuilderJc_s* buffer;
  STACKTRC_TENTRY("threadBuffer_s_StringBuilderJc");
  buffer = (StringBuilderJc_s*)getThreadBuffer_StringBuilderJc(false, sign, _thCxt);
  append_s_StringBuilderJc(buffer, src, _thCxt);
  STACKTRC_LEAVE; return buffer;
}
#endif //DEF_ThreadContext_HEAP_emC



#if defined(__cplusplus) && defined(__CPLUSPLUSJcpp)

  StringBuilderJcpp* StringBuilderJcpp::threadBuffer(ThCxt* _thCxt)
  { return (reinterpret_cast<StringBuilderJcpp*>(getThreadBuffer_StringBuilderJc(true, _thCxt)));
  }

  StringBuilderJcpp* threadBuffer_StringBuilderJcpp(ThCxt* _thCxt)
  { return (StringBuilderJcpp*)getThreadBuffer_StringBuilderJc(true, _thCxt);
  }


#endif











METHOD_C StringJc toStringPersist_StringBuilderJc(ObjectJc* othis, ThCxt* _thCxt)
{
  StringBuilderJc_s* ythis = C_CAST(StringBuilderJc_s*, othis);  //admissible because the method is only called for StringBuilderJc_s
  StringJc ret = NULL_StringJc;
  const char* s0 = ythis->size < 0 ? ythis->value.buffer : ythis->value.direct;
  int count = ythis->_count;
  /**Detect whether the buffer is found in the stack range. Than its memory address is
   * between any address of a local variable and the Thread-Context pointer. */
  bool bufferInStack = ADDR_IN_STACK_ThreadContext_emC(s0); 
  //int nonPersistent = 0;
  /**A StringJc is designated as non-persistence, if the StringJc referes a location in a change-able buffer. */
  //xx int nonPersistent = ythis->_mode & _mTemporary_StringBuilderJc ? 0 : mNonPersists__StringJc;
  STACKTRC_TENTRY("toStringPersist_StringBuilderJc");
  if(  ythis->_mode & _mStringConcatBuffer_StringBuilderJc
    && !(ythis->_mode & (_mStack_StringBuilderJc|_mThread_StringBuilderJc))
    && !bufferInStack
    ) {
    /**The buffer is created only for concatenation, it means, it is persistent itself: */
    ythis->_mode |= _mStringBuilt_StringBuilderJc;  //only a precaution. A change is not expectable.
    SET_StringJc(ret, s0, count);
  } else {
    /**All other usages of buffer assume that the Buffer should be decoupled from the String. 
     * Therefore create a new StringBuilder
     */
    StringBuilderJc_s* buffer = new_StringBuilderJc(count+1, _thCxt);
    append_zI_StringBuilderJc(buffer, s0, count, _thCxt);
    SET_StringJc(ret, buffer->value.direct, count);
  }
  //false, because it isn't a reference in data: setFromBuffer_StringJc(&ret, ythis);  //the String is contained in the Buffer.
  STACKTRC_LEAVE; return ret;
}


//NOTE: usage of ObjectJc* is necessary because the method is used instead toString_StringBuilderJc(...)
//      without changing of parameters, only change of mehtod name using Java2C.
//      A simple C-programmer may do also. 
METHOD_C StringJc xxxtoStringNonPersist_StringBuilderJc(ObjectJc* othis, ThCxt* _thCxt)
{
  StringBuilderJc_s* ythis = C_CAST(StringBuilderJc_s*, othis);  //admissible because the method is only called for StringBuilderJc_s
  StringJc ret = toString_StringBuilderJc(&ythis->base.object, _thCxt);
  ythis->_mode &= ~_mStringBuilt_StringBuilderJc;
  return ret;
}


#ifdef DEF_ThreadContext_HEAP_emC
METHOD_C StringJc toStringInThreadCxt_StringBuilderJc(StringBuilderJc_s* ythis, ThCxt* _thCxt)
{
  StringJc ret,src;
  StringBuilderJc_s* builderThCxt;
  STACKTRC_TENTRY("toStringInThreadCxt_StringBuilderJc");
  src = toStringNonPersist_StringBuilderJc(&ythis->base.object, _thCxt);
  builderThCxt = threadBuffer_s_StringBuilderJc(src, "toStringStringBuilder", _thCxt);
  ret = toString_StringBuilderJc(&builderThCxt->base.object, _thCxt);
  STACKTRC_LEAVE; return ret;
}
#endif

void ctorc_StringBuilderJc(StringBuilderJc_s* ythis, int size)
{ CTOR_ObjectJc(&ythis->base.object, ythis, size, refl_StringBuilderJc, 0);
  ythis->_count = 0;
  if(size < 0)
  { size = -size;
  }
  ythis->size = (int16)size;
  memset(ythis->value.direct, 0, ythis->size);
}














void clone_String(ObjectJc* ythis)
{
}

void finalize_String(ObjectJc* ythis)
{
}

int32 hashCode_String(ObjectJc* ythis)
{
  return 0;
}



StringJc toString_String(StringJc* ythis)
{ return *ythis;
}










void set_StringJc(StringJc* ythis, StringJc src)
{ int valueSrc = VAL_AddrVal_emC(src);
  char const* sSrc = src.addr.str;
  int zSrc = valueSrc & mLength_StringJc;
  STACKTRC_ENTRY("set_StringJc");
  clear_StringJc(ythis);
  if(zSrc == mLength_StringJc) zSrc = strnlen_emC(sSrc, kMaxNrofChars_StringJc);
  if(valueSrc & mNonPersists__StringJc){  
    /**It needs to save the String persistents: */
    StringBuilderJc_s* buffer = new_StringBuilderJc(zSrc, THCXT); //allocate in heap
    //setTemporary_StringBuilderJc(buffer);  //only referenced by this String.
    replace_zI_StringBuilderJc(buffer, 0,0, sSrc, zSrc, THCXT); //copy
    sSrc = getCharsAndCount_StringBuilderJc(buffer, &zSrc);
    SET_StringJc((*ythis), sSrc, zSrc);
  } else {
    //without copy to a new buffer
    SET_StringJc(*ythis, sSrc, zSrc);
  }
  setBackRefJc(&VAL_AddrVal_emC(*ythis), ythis->addr.str);
  STACKTRC_LEAVE;
}







StringJc persist_StringJc(StringJc src)
{
  StringJc ret;
  int value = VAL_StringJc(src);
  STACKTRC_ENTRY("persist_StringJc");
  if(value & mNonPersists__StringJc){
    int zSrc;
    char const* sSrc = getCharsAndLength_StringJc(&src, &zSrc);
    StringBuilderJc_s* buffer = new_StringBuilderJc(zSrc, THCXT);
    append_s_StringBuilderJc(buffer, src, THCXT);
    SET_StringJc(ret, buffer->value.direct, zSrc);
  } else {
    //it is persistent already:
    ret = src;
  }
  STACKTRC_LEAVE; return ret;

}




StringJc declarePersist_StringJc(StringJc ythis)
{
  int value = VAL_StringJc(ythis);
  value &= ~mNonPersists__StringJc;
  ythis.val = value;
  return ythis;
}




#ifdef DEF_ThreadContext_HEAP_emC
StringJc copyToThreadCxt_StringJc(StringJc src, ThCxt* _thCxt)
{
  StringJc ret;
  StringBuilderJc_s* builderThCxt;
  STACKTRC_TENTRY("copyToThreadCxt_StringJc");
  builderThCxt = threadBuffer_s_StringBuilderJc(src, "copytoThCxtStringStringBuilder", _thCxt);
  ret = toString_StringBuilderJc(&builderThCxt->base.object, _thCxt);
  STACKTRC_LEAVE; return ret;
}
#endif



#ifndef DEF_ObjectSimple_emC
/* Implementation notes: The functionallity of conversion from a given charset is ignored yet.
   Only the copiing of  bytes is done.
 */
StringJc new_BYIICharset_StringJc(int8_Y* bytes, int offset, int length, StringJc charsetName, ThCxt* _thCxt)
{ //StringBuilderJc_s* sbuffer;
  StringJc ret = CONST_StringJc((char*)(bytes->data+offset), length);  //The string refers to the bytes.
  STACKTRC_TENTRY("new_bYiiCharset_StringJc");
  /*
  sbuffer = new_StringBuilderJc(length, _thCxt);
  { int zBuffer; char* buffer = getCharsAndSize_StringBuilderJc(sbuffer, &zBuffer);
    memcpy(buffer, bytes->data + offset, length);
  }
  ret = toString_StringBuilderJc(&sbuffer->base.object, _thCxt);
  */
  STACKTRC_LEAVE; return ret;
}
#endif


/* Implementation notes: The functionallity of conversion from a given charset is ignored yet.
   Only the copiing of  bytes is done.
 */
StringJc new_mBYIIEncoding_StringJc(int8ARRAY bytes, int offset, int length, struct CharsetJc_t* charset, ThCxt* _thCxt)
{ //StringBuilderJc_s* sbuffer;
  StringJc ret = INIZ_StringJc((char*)(bytes.addr+offset), length);  //The string refers to the bytes.
  STACKTRC_TENTRY("new_bYiiCharset_StringJc");
  /*
  sbuffer = new_StringBuilderJc(length, _thCxt);
  { int zBuffer; char* buffer = getCharsAndSize_StringBuilderJc(sbuffer, &zBuffer);
    memcpy(buffer, bytes->data + offset, length);
  }
  ret = toString_StringBuilderJc(&sbuffer->base.object, _thCxt);
  */
  STACKTRC_LEAVE; return ret;
}


#ifndef DEF_ObjectSimple_emC
StringJc new_CY_StringJc(char_Y* chars, ThCxt* _thCxt)
{
  StringJc ret; 
  int length;
  length = chars->head.length;
  if(length >= mLength_StringJc) {
    STACKTRC_TENTRY("new_CY_StringJc");
    THROW1_s0(IndexOutOfBoundsException, "offset <0", length); length = mLength_StringJc-1; 
    STACKTRC_LEAVE;
  }
  SET_StringJc(ret, chars->data, length | mNonPersists__StringJc);
  return ret;

}
#endif



#ifndef DEF_ObjectSimple_emC
StringJc new_CYI_StringJc(char_Y* chars, int offset, int count, ThCxt* _thCxt)
{
  StringJc ret; 
  STACKTRC_TENTRY("new_CYI_StringJc");
  if(offset < 0) THROW1_s0(IndexOutOfBoundsException, "offset <0", offset);
  if(count < 0) THROW1_s0(IndexOutOfBoundsException, "count <0", count);
  if(offset + count > chars->head.length) THROW1_s0(IndexOutOfBoundsException, "offset + count > chars.length", offset + count);
  if( (offset + count) >= mLength_StringJc) { THROW1_s0(IndexOutOfBoundsException, "offset <0", offset); }
  
  SET_StringJc(ret, chars->data + offset, (offset + count) | mNonPersists__StringJc);
 
  STACKTRC_LEAVE; return ret;

}
#endif





#if 0 //unnecessary dependency to format
//StringJc format_BV_StringJc(StringJc text, struct StringBuilderJc_t* sbuffer, struct VaArgBuffer_t const* args)
StringJc xxxformat_BV_StringJc(StringJc text, struct StringBuilderJc_t* sbuffer, Va_listFW vargList)
{
  int zText; 
  char const* sText = getCharsAndLength_StringJc(&text, &zText);
  int nrofChars;
  char* buffer = (sbuffer->size < 0 ? sbuffer->value.buffer : sbuffer->value.direct);
  int zBuffer = (sbuffer->size < 0 ? -sbuffer->size : sbuffer->size);

  STACKTRC_ENTRY("format_BV_StringJc");
  nrofChars = format_va_arg_Formatter_FW(_thCxt, sText, zText, buffer, zBuffer, vargList);
  //sbuffer->count = nrofChars;
  _setCount_StringBuilderJc(sbuffer, nrofChars);  
  STACKTRC_LEAVE; return s0i_StringJc(buffer, nrofChars);
}


StringJc format_a_StringJc(StringJc format, char const* typeArgs, ...)
{ va_list args;
  Va_listFW typedArgs;
  StringJc ret;
  STACKTRC_ENTRY("format_a_StringJc");
  va_start(args, typeArgs);
  typedArgs.typeArgs = typeArgs;
  typedArgs.args = args;
  ret = format_A_StringJc(format, typedArgs, _thCxt);
  STACKTRC_LEAVE; return ret;
}


StringJc format_za_StringJc(char const* format, char const* typeArgs, ...)
{ va_list args;
  Va_listFW typedArgs;
  StringJc ret;
  STACKTRC_ENTRY("format_a_StringJc");
  va_start(args, typeArgs);
  typedArgs.typeArgs = typeArgs;
  typedArgs.args = args;
  ret = format_A_StringJc(z_StringJc(format), typedArgs, _thCxt);
  STACKTRC_LEAVE; return ret;
}




StringJc format_A_StringJc(StringJc format, Va_listFW vargList, ThCxt* _thCxt)
{
  int zFormat; 
  char const* sFormat = getCharsAndLength_StringJc(&format, &zFormat);
  int nrofChars;
  char* buffer;
  int zBuffer;
  StringBuilderJc_s* uBuffer;
  StringJc ret;
  STACKTRC_TENTRY("format_A_StringJc");
  uBuffer = threadBuffer_StringBuilderJc("format_A_StringJc", _thCxt);
  buffer = getCharsAndSize_StringBuilderJc(uBuffer, &zBuffer);
  nrofChars = format_va_arg_Formatter_FW(_thCxt, sFormat, zFormat, buffer, zBuffer, vargList);
  //sbuffer->count = nrofChars;
  _setCount_StringBuilderJc(uBuffer, nrofChars);  
  int sizeBufferInThCxt = _reduceCapacity_StringBuilderJc(uBuffer, (int16)(nrofChars+1));  
  reduceLastUserBuffer_ThreadContext_emC(uBuffer, sizeBufferInThCxt, _thCxt);
  INIT_StringJc(ret, buffer, nrofChars | mThreadContext__StringJc);
  STACKTRC_LEAVE; return ret;
}
#endif //0



#ifdef DEF_ThreadContext_HEAP_emC
StringJc replace_StringJc(StringJc ythis, char oldChar, char newChar, ThCxt* _thCxt)
{
  StringBuilderJc_s* sbuffer = null;
  char const* strThis = PTR_StringJc(ythis);
  int lenThis = VAL_StringJc(ythis) & mLength_StringJc;
  char* buffer = null;
  int ii;
  int max;
  StringJc ret;
  STACKTRC_TENTRY("replace_StringJc");
  if(lenThis == mLength_StringJc){ lenThis = strnlen_emC(strThis, mLength_StringJc); }
  max = lenThis;
  for(ii = 0; ii < max; ++ii)
  { if(strThis[ii] == oldChar)
    { if(sbuffer == null) {
        int maxBuffer;
        sbuffer = threadBuffer_s_StringBuilderJc(ythis, "replace_StringJc", _thCxt);
        buffer = getCharsAndSize_StringBuilderJc(sbuffer, &maxBuffer);
        if(maxBuffer < max){
          THROW1_s0(StringIndexOutOfBoundsException, "input string to long", max);
        }
      }
      buffer[ii] = newChar;
    }
  }
  if(buffer != null) {
    ret = toString_StringBuilderJc(&sbuffer->base.object, _thCxt);
  } else {
    ret = ythis; //it is unchanged.
  }
  STACKTRC_LEAVE; return ret;
}
#endif


StringBuilderJc_s* replace_u_StringJc(StringJc ythis, char oldChar, char newChar
           , StringBuilderJc_s* buffer, ThCxt* _thCxt)
{ int zSrc;
  char const* sSrc;
  int zDst;
  char* sDst;

  sSrc = getCharsAndLength_StringJc(&ythis, &zSrc);
  zDst = buffer->_count;
  sDst = chars_StringBuilderJc(buffer);

  /**The source may be the same position in buffer as the destination,
   * replace only the chars. It is a expect-able situation. */
  if(sDst != sSrc && zDst != zSrc){
    /**if it isn't so, copy the source String first into buffer. */
    replace_StringBuilderJc(buffer, 0, buffer->_count, ythis, _thCxt);
  }

  return replace_CC_StringBuilderJc(buffer, oldChar, newChar);
}



StringBuilderJc_s* replace_CC_StringBuilderJc(StringBuilderJc_s* ythis, char oldChar, char newChar)
{ 
  char* str = chars_StringBuilderJc(ythis);
  int zDst = ythis->_count;
  int ii;

  for(ii = 0; ii < zDst; ii++) { 
    if(str[ii] == oldChar) {
      str[ii] = newChar;
    } 
  }
  return ythis;
}









METHOD_C void setLength_StringBuilderJc(StringBuilderJc_s* ythis, int newLength, ThCxt* _thCxt)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  int count = ythis->_count;
  STACKTRC_TENTRY("setLength_StringBuilderJc");
  if(newLength < 0)
  { THROW1_s0(IndexOutOfBoundsException, "", newLength);
  }
  else if(newLength < count)
  { memset(buffer + newLength, 0, count - newLength);
    _setCount_StringBuilderJc(ythis, newLength); //ythis->count = newLength;
  }
  else if(newLength <= size)
  { memset(buffer + count, 0, newLength - count);
    _setCount_StringBuilderJc(ythis, newLength); //ythis->count = newLength;
  }
  else
  { //the newLength increases the String with \0-chars
    THROW1_s0(IndexOutOfBoundsException, "unrecognize", newLength);
  }
  STACKTRC_LEAVE;
}








StringBuilderJc_s* append_u_StringBuilderJc(StringBuilderJc_s* ythis, StringBuilderJc_s const* add, ThCxt* _thCxt)
{ int lengthAdd;
  char const* buffer; 
  int count = ythis->_count;
  STACKTRC_TENTRY("append_Sb_StringBuilderJc");
  buffer = getCharsAndCount_StringBuilderJc(add, &lengthAdd);
  replace_zI_StringBuilderJc(ythis, count, count, buffer, lengthAdd, _thCxt);
  STACKTRC_LEAVE;
  return( ythis);
}








StringBuilderJc_s* insert_C_StringBuilderJc(StringBuilderJc_s* ythis, int offset, char add, ThCxt* _thCxt)
{ //NOTE: a macro isn't able to use because add should be a left value, the actual parameter add doesn't may it.
  return replace_zI_StringBuilderJc(ythis, offset, offset, &add, 1, _thCxt);
}



#ifndef DEF_ObjectSimple_emC
StringBuilderJc_s* insert_CYII_StringBuilderJc(StringBuilderJc_s* ythis, int pos, char_Y* src, int offset, int len, ThCxt* _thCxt)
{ //NOTE: a macro isn't able to use because add should be a left value, the actual parameter add doesn't may it.
  int lenSrc = src->head.length;
  STACKTRC_TENTRY("insert_IcYII_StringBuilderJc");
  if(len == -1){ len = lenSrc; }//Special form to support macro insert_IcY_StringBuilderJc(...)
  if(offset <0 || (offset + len) > lenSrc) THROW1(StringIndexOutOfBoundsException, z_StringJc("src indices fault"), offset);
  replace_zI_StringBuilderJc(ythis, pos, 0, &src->data[offset], len, _thCxt);
  STACKTRC_LEAVE; return ythis;
}
#endif

/** found an algorithm unusing division, because some divisions may be expensive in time
  * at some processors.
*/
StringBuilderJc_s* insert_Ir_StringBuilderJc(StringBuilderJc_s* ythis, int offset, int32 value, int radix, ThCxt* _thCxt)
{ char buffer[33];    //max 32 bits and negativ sign for "-10000000000000000000000000000000"
  StringBuilderJc_s* ret;
  int nrofChars;
  STACKTRC_TENTRY("insert_Ir_StringBuilderJc");
  nrofChars = toString_Integer_FW(buffer, sizeof(buffer), value, radix, 0);

  ret = replace_zI_StringBuilderJc(ythis, offset, 0, buffer, nrofChars, _thCxt);
  STACKTRC_LEAVE; return( ret);
}


/** found an algorithm unusing division, because some divisions may be expensive in time
  * at some processors.
*/
StringBuilderJc_s* insert_Jr_StringBuilderJc(StringBuilderJc_s* ythis, int offset, int64 value, int radix, ThCxt* _thCxt)
{ char buffer[65];    //max 32 bits and negativ sign for "-10000000000000000000000000000000"
  char cc;
  /**Array of values to test the position in digit. Fill it with 10, 100 etc if radix = 10;*/
  int64 testValues[64];

  int idxTestValues = 0;
  int nChars = 0;
  int64 test = radix;
  StringBuilderJc_s* ret;
  STACKTRC_TENTRY("insert_Jr_StringBuilderJc");
  if(value < 0)
  { value = -value; //may be -0x80000000
    buffer[nChars++] = '-';
  }
  //
  //fill in digigts to detect positions in digit
  while(value >= test)
  { testValues[idxTestValues++] = test;
    test *= radix;
  }
  //
  //test input digit
  while(--idxTestValues >=0)
  { cc = '0';
    test =testValues[idxTestValues];
    while(value >= test)
    { cc += 1;
      value -= test;
    }
    if(cc > '9')
    { cc += ('a' - '9' -1);
    }
    buffer[nChars++] = cc;
  }
  cc = (char)('0' + value); //last digit
  if(cc > '9')
  { cc += ('a' - '9' -1);
  }
  buffer[nChars++] = cc;
  ret = replace_zI_StringBuilderJc(ythis, offset, 0, buffer, nChars, _thCxt);
  STACKTRC_LEAVE; return( ret);
}


#ifdef DEF_ThreadContext_HEAP_emC
StringJc toString_DoubleJc(double value, ThCxt* _thCxt)
{ StringBuilderJc_s* sbuffer;
  STACKTRC_TENTRY("toString_DoubleJc");
  { int size;
    char* buffer;
    int count;
    sbuffer = threadBuffer_StringBuilderJc("toString_DoubleJc", _thCxt);
    buffer = getCharsAndSize_StringBuilderJc(sbuffer, &size); 
    count = snprintf(buffer, size, "%f", value);
    _setCount_StringBuilderJc(sbuffer, count); //
  }
  STACKTRC_LEAVE;
  return toString_StringBuilderJc(&sbuffer->base.object, _thCxt);
}
#endif




#if 0
StringBuilderJc_s* append_I_StringBuilderJc(StringBuilderJc_s* ythis, int value)
{ STACKTRC_ENTRY("append_I_StringBuilderJc");
  insert_I_StringBuilderJc(ythis, ythis->count, value, 10, _thCxt);
  STACKTRC_LEAVE; return ythis;
}


StringBuilderJc_s* insert_sII_StringBuilderJc(StringBuilderJc_s* ythis, int offset, StringJc add, int start, int end, ThCxt* _thCxt)
{ STACKTRC_TENTRY("insert_sII_StringBuilderJc");
  { int nAdd; 
    const char* sAdd = getCharsAndLength_StringJc(&add, &nAdd);
    if(end < start || end > nAdd || start <0) THROW1_s0(IndexOutOfBoundsException, "", end);
    sAdd += start;
    nAdd = end - start;
    replace_zI_StringBuilderJc(ythis, offset, offset, sAdd, nAdd, _thCxt);
  }
  STACKTRC_LEAVE; return ythis;
}
#endif





StringBuilderJc_s* insert_F_StringBuilderJc(StringBuilderJc_s* ythis, int index, float value, ThCxt* _thCxt)
{ char buffer[20];
  int nChars;
  nChars = snprintf(buffer, sizeof(buffer), "%f", value);
  return replace_zI_StringBuilderJc(ythis, index, 0, buffer, nChars, _thCxt);
}




StringBuilderJc_s* insert_D_StringBuilderJc(StringBuilderJc_s* ythis, int index, double value, ThCxt* _thCxt)
{ char buffer[40];
  int nChars;
  nChars = snprintf(buffer, sizeof(buffer), "%f", value);
  return replace_zI_StringBuilderJc(ythis, index, 0, buffer, nChars, _thCxt);
}




StringBuilderJc_s* XXXinsert_cYii_StringBuilderJc(StringBuilderJc_s* thiz, int offset, CharSeqJc add, int start, int end, struct ThreadContext_emC_t* _thCxt)
{
  int countNew;
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int size = (thiz->size < 0 ? -thiz->size : thiz->size); //size of the buffer
  int count = thiz->_count;
  STACKTRC_TENTRY("insert_cYii_StringBuilderJc");
  int nInsert;
  int endmax = length_CharSeqJc(add, _thCxt);
  if(offset < 0) { //check offset
    offset = thiz->_count + offset +1; //-1: it is _count
  }
  if(offset <0){ offset = 0; }
  //check end
  if(end < 0){  // -1: till endmax, -2  endmax -1 etc.
    end = endmax + end +1;  //-1 result in endmax
  }
  if(end <0) {
    end = 0; 
  } else if(end > endmax){
    STACKTRC_LEAVE; return thiz;  //do nothing, nothing to append
  }
  if(thiz->_mode & _mStringBuilt_StringBuilderJc){
    THROW1_s0(IllegalStateException, "Buffer was used in StringJc", (int)(intptr_t)buffer);
  }
  nInsert = end - start;  //nr of chars to insert netto
  countNew = count + nInsert;
  if(countNew > size)
  { //in opposite to Java the StringBuffer is not increased, no dynamically memory management.
    //TODO perhaps test whether it is possible
		if(thiz->_mode & _mNoException_StringBuilderJc){
		  thiz->_mode |= _mTruncated_StringBuilderJc;
			nInsert = size - count;
			countNew = size;
		} else {
			THROW1_s0(RuntimeException, "StringBuffer too many chars", countNew);
    }
  }
  { int nRest = count - end;  //nr of chars from end of replace area to actual end
    if(nRest > 0) memmove(buffer + end + nInsert, buffer + end, nRest);  //moves in both directions
  }
  //The area to replace is free.
  //Read characters and insert

  copyToBuffer_CharSeqJc(add, start, end, buffer + offset, size - offset, _thCxt);
  _setCount_StringBuilderJc(thiz, countNew); //thiz->count = countNew;

  STACKTRC_LEAVE; return( thiz);
}





METHOD_C StringBuilderJc_s* delete_StringBuilderJc(StringBuilderJc_s* ythis, int start, int end, ThCxt* _thCxt)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  STACKTRC_TENTRY("delete_StringBuilderJc");
  if(end >= start && end <= size && start >=0)
  { int nrofBytesFromEndOfDeleteAreaToRealyEnd = (ythis->_count) - end;
    int offset = end - start;
    if(offset > 0 && nrofBytesFromEndOfDeleteAreaToRealyEnd >0)
    { memmove(buffer + start, buffer + start + offset, nrofBytesFromEndOfDeleteAreaToRealyEnd);
      memset(buffer + start + nrofBytesFromEndOfDeleteAreaToRealyEnd, 0, offset);  //store 0 at rest to clean it.
    }
  }
  else
  { THROW1_s0(StringIndexOutOfBoundsException, "", 0);
  }
  STACKTRC_LEAVE;
  return ythis;
}


METHOD_C void cleanToSize_StringBuilderJc(StringBuilderJc_s* ythis)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  int count = ythis->_count;
  if(count >= 0 && count <= size)
  { memset(buffer + count, 0, size - count);  //store 0 at rest to clean it.
  }
  else
  { STACKTRC_ENTRY("cleanToSize_StringBuilderJc");
    THROW1_s0(RuntimeException, "corrupt content, count=", ythis->_count);
    STACKTRC_LEAVE;
  }
}



#if defined(use_StringJcpp) && defined(__CPLUSPLUSJcpp) && defined(__cplusplus)


StringJcpp& StringJcpp::operator=(StringBuilderJcpp& src)
{ setFromBuffer_StringJc(this, &src);
  return *this;
}


StringBuilderJcpp& operator+(StringJc src, StringJc src2)
{ STACKTRC_ENTRY("operator+(StringJc, StringJc)");
  StringBuilderJcpp* buffer = new_StringBuilderJcpp(-1);
  append_s_StringBuilderJc(buffer, src, _thCxt);
  append_s_StringBuilderJc(buffer, src2, _thCxt);

  
  STACKTRC_LEAVE; return *buffer;
}


StringBuilderJcpp* new_StringBuilderJcpp(int size)
{

  /**It isn't settled, how to allocate without responsibility of the user
   * but also without garbage collection.
   * Therefore this solution isn't able to use.
   */
  return null;  


}

#endif











//#include "Jc/ReflectionJc.h"

//DEFINE_REFLECTION_REF(StringBuilderJc_s);


