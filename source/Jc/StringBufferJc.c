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

//#include "CRuntimeJavalike.h"
#include "StringJc_intern.h"
#include <Jc/ObjectJc.h>
#include <Fwc/fw_Exception.h>
#include <Fwc/fw_Formatter.h> 
//#include "StringBuilderJc.h"
#include <Jc/ReflectionJc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>  //using sprintf
#include <stdarg.h>
//#include "RuntimeHeapJc.h"

extern ClassJc const reflection_StringBuilderJc; 
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
  Because a string may be also a part of a content of StringBuilderJc, the followed rule
  is found:
  <ul><li>If the string is a constant string, the pointer to the array of chars is stored
          in <code>value</code> and the number of chars is stored in <code>count</code>.
          The <code>offset</code> is set to <code>-1</code>.</li>
      <li>If the string is a part or the whole content of the buffer in StringBuilderJc,
          The <code>value</code> pointered the start of buffer in the StringBuilderJc.
          The adress of the StringBuilderJc-Structur is ascertainable by subtraction of the
          difference between the Buffer inside a StringBuilderJc and the StringBuilderJc.
          The <code>offset</code>-Attribute is used to pointer the position inside buffer.
          </li>
  </ul>
  A StringBuilderJc must known if a StringJc is referenced to it, by two causes:
  <ul><li>For garbage collection: A string should be handled like a reference.</li>
      <li>If a StringJc references the StringBuilderJc and a change of the StringBuilderJc
          will proceed, the StringBuilderJc should copied in a new memory area and than modified,
          to held the content for pointering strings constant.</li>
  </ul>
  This requested knowledge is realized in StringBuilderJc by using the array of back-references,
  see RuntimeHeapJc, and by query a flag in the StringBuilderJc-attributes.
*/






StringBuilderJc* ctorM_StringBuilderJc(MemC rawMem)
{ StringBuilderJc* ythis = PTR_MemC(rawMem, StringBuilderJc);
  int size;
  char* buffer;
  STACKTRC_ENTRY("ctorM_StringBuilderJc");
  /**The size of the rest, inclusive start of string in value. */
  size = size_MemC(rawMem) - sizeof(StringBuilderJc) + sizeof(ythis->value);
  if(size < 20) THROW_s0(IllegalArgumentException, "ctor mem-size insufficient", size_MemC(rawMem));
  buffer = (char*)address_MemC(rawMem, sizeof(StringBuilderJc), size);
  //init0_MemC(rawMem);
  init_ObjectJc(&ythis->base.object, size_MemC(rawMem), 0);
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
StringBuilderJc* ctorO_I_StringBuilderJc(ObjectJc* othis, int size, ThCxt* _thCxt)
{ StringBuilderJc* ythis = (StringBuilderJc*)othis;
  int sizeObj;
  STACKTRC_TENTRY("ctorO_I_StringBuilderJc");
  checkConsistence_ObjectJc(othis, sizeof(StringBuilderJc), &reflection_StringBuilderJc, _thCxt); 
  sizeObj = getSizeInfo_ObjectJc(othis);
  ythis->_count = 0;
  if(sizeObj >= (int)(sizeof(StringBuilderJc) - sizeof(ythis->value) + size ))
  { //enaugh size for StringBuilderJc-control structure and the buffer itself:
    ythis->size = (int16)size;  //positiv: use value as buffer direct
    memset(&ythis->value, 0, size);  
    //MemC mem = build_MemC(newObj, sizeObj);
    //return ctorc_s0i_StringBuilderJc((StringBuilderJc*)newObj, (char*)address_MemC(mem, sizeof(StringBuilderJc),0), size);
  }
  else
  { //not enaugh size:
    MemC mBuffer = alloc_MemC(size);
    init0_MemC(mBuffer);
    ythis->size =(int16)(ythis->size-size);
    ythis->value.buffer = PTR_MemC(mBuffer, char);
  }
  STACKTRC_LEAVE; return ythis;
}



StringBuilderJc* ctorO_StringBuilderJc(ObjectJc* othis, ThCxt* _thCxt)
{ int sizeObj = getSizeInfo_ObjectJc(othis);
  MemC mem = build_MemC(othis, sizeObj);
  StringBuilderJc* ythis = (StringBuilderJc*)othis;
  int sizeBuffer = size_MemC(mem) - sizeof(StringBuilderJc) + sizeof(ythis->value);
  STACKTRC_TENTRY("ctorO_StringBuilderJc");
  checkConsistence_ObjectJc(othis, sizeObj, &reflection_StringBuilderJc, _thCxt); 
  if(sizeBuffer <=4)
  { /**The StringBuffer has not a direct Buffer: */
    MemC mem = getRestBlock_ObjectJc(othis, -2, _thCxt);
    sizeBuffer = size_MemC(mem);
    if(sizeBuffer >0)
    { ythis->value.buffer = PTR_MemC(mem, char);
      ythis->size = (int16)(-sizeBuffer); //negative value because immediately String  
    }
    else
    { THROW_s0(IllegalArgumentException, "initial Buffer size necessary", sizeBuffer);
    } 
  }
  else
  {
    if(sizeBuffer < 20) THROW_s0(IllegalArgumentException, "ctor mem-size insufficient", size_MemC(mem));
    ythis->size = (int16)sizeBuffer; //positive value because immediately String  
  }
  STACKTRC_LEAVE; return ythis;
}



StringBuilderJc* ctorO_cs_StringBuilderJc(ObjectJc* othis, CharSeqJc src, ThCxt* _thCxt)
{ StringBuilderJc* ythis;
  int zSrc = length_CharSeqJc(src, _thCxt);
  //if(zSrc == mLength__StringJc){ zSrc = strlen_Fwc(PTR_StringJc(src), mLength__StringJc); }
  ythis = ctorO_I_StringBuilderJc(othis, zSrc+16, _thCxt);
  return append_c_StringBuilderJc(ythis, src, _thCxt);
}



StringBuilderJc* ctorO_zI_StringBuilderJc(ObjectJc* yObj, char* buffer, int size, ThCxt* _thCxt)
{ StringBuilderJc* ythis = (StringBuilderJc*)yObj;
  int count;
  STACKTRC_TENTRY("ctorO_CI_StringBuilderJc");
  checkConsistence_ObjectJc(yObj, sizeof(StringBuilderJc), null/*&reflection_StringBuilderJc*/, _thCxt); 
  if(size < 0)
  { size = -size;
  }
  ythis->size = (int16)(-size);  //negative to sign it is a refernce.
  count = strlen(buffer);  //from the given content
  if(count >= size)
  { count = size-1; }        //but never greater than given size. The content may be a part of 0-terminate C-String.
  ythis->_count= (int16)count;
  ythis->value.buffer = buffer;
  STACKTRC_LEAVE; return ythis;

}




void finalize_StringBuilderJc_F(ObjectJc* othis, ThCxt* _thCxt)
{ StringBuilderJc* ythis = (StringBuilderJc*)othis;  //upcasting to the real class.
  STACKTRC_TENTRY("finalize_StringBuilderJc_F");
  finalize_ObjectJc_F(&ythis->base.object, _thCxt);      //finalizing the superclass.
  STACKTRC_LEAVE;
}




StringBuilderJc* xxxnew_StringBuilderJc(int size, ThCxt* _thCxt)
{ StringBuilderJc* buffer;
  STACKTRC_TENTRY("new_StringBuilderJc");
  if(size <=0)
  { //no size is given
    #ifdef USE_BlockHeapJc
      /*
      if(threadContext->blockheapStd!=null)
      { size = threadContext->blockheapStd->bytesNormalBlock - 10 * 8; //sizeof(ObjectJcRef);
      }
      else
      { //initial mode:
        size = 240;
      }
      */
    #else
      size =240;
    #endif
  }
  #if defined(USE_BlockHeapJc)
    //If Blockheap is available, get the buffer from it.
    { ObjectJc* yObj = allocObject_IIs_BlockHeapJc(_thCxt->blockHeap, size, 0, 10, "concatenationString", _thCxt);
      buffer = ctorO_StringBuilderJc(yObj, _thCxt);
    }
  #elif defined(USE_MALLOC_FREE)
    //If no Blockheap is available, and the system is arranged to use malloc and delete,
    //the user is responsible for free the buffer!
    { MemC mem = alloc_MemC(size+sizeof(StringBuilderJc));
      buffer = ctorM_StringBuilderJc(mem);
    }
  #else
    //From where to get the buffer? If a Garbage Collector concept is established, it is the best way.
    //Therefore the buffer is created in BlockHeap and deleted by Garbage Collector if no references to it are exist.
    //But without a Garbage Collection? If the user should look after it, it is unappreciative
    //because it is a negligibly subject. Therefore it may be soluted errorneous.
    //A better way is to release the user from this decision.
    //A StringBuilderJc are available in the threadContext as thread local resource. It can be used temporary
    //for this aim. But the user must not store this reference in a non predictable way.It should be used only locally.
    //if there are conflicts, the user gets to know from this because the content of buffer is changed.
    //Normally the content is assembled in a buffer and than transported to any other location, especially to console via printf.
    { buffer = threadBuffer_StringBuilderJc(_thCxt);
    }
  #endif
  STACKTRC_LEAVE; return( buffer);

}



//Used for Mtbl for interface CharSeqJc
static int32 length_StringBuilderJc_F(ObjectJc* thiz, ThCxt* _thCxt){ return ((StringBuilderJc*)thiz)->_count; }

static char charAt_StringBuilderJc_F(ObjectJc* othiz, int32 ix, ThCxt* _thCxt){ 
  StringBuilderJc* thiz = (StringBuilderJc*)othiz;
  char const* chars = chars_StringBuilderJc(thiz);
  if(ix < 0 || ix >= thiz->_count) { THROW_s0(IndexOutOfBoundsException, "faulty indices", ix); return 0; }
  else return chars[ix]; 
}

static CharSeqJc subSequence_StringBuilderJc_F(ObjectJc* othiz, int32 from, int32 to, ThCxt* _thCxt)
{ StringBuilderJc* thiz = (StringBuilderJc*)othiz;
  CharSeqJc ret = {0};
  if(from > 0 && from <= to && to <= thiz->_count) {
    ret.ref = null; //TODO
  } 
  else THROW_s0(IndexOutOfBoundsException, "faulty indices", to); 
  return ret;
}


/**common method for creating and initilizing buffers in threadcontext. 
 * It is static, don't use outside.
 * @return pointer to StringBuilderJc or StringBuilderJcpp, therefore the return type is void*. Cast it outside.
 */
static void* getThreadBuffer_StringBuilderJc(bool bCpp, ThCxt* _thCxt)
{ 
  StringBuilderJc* sBuffer;
  #if defined(__cplusplus) && defined(__CPLUSPLUSJcpp)
    StringBuilderJcpp* sBufferJcpp;
    int sizeStringBuilderJcpp = sizeof(StringBuilderJcpp);  //regard it at start of area.
  #else
    int sizeStringBuilderJcpp = 0;  //not present!
  #endif
  STACKTRC_TENTRY("threadBuffer_StringBuilderJc");
  {
    MemC mBuffer = getUserBuffer_ThreadContextFw(0, _thCxt);
    /**Check whether the buffer is in use, TODO... */
    int sizeBufferThreadContext = size_MemC(mBuffer);
    int sizeStringBuffer = sizeBufferThreadContext/2 - sizeStringBuilderJcpp;
    int posBuffer = 0; //(nr == 1 ? sizeBufferThreadContext/2 : 0);


    ObjectJc* othis = (ObjectJc*)address_MemC(mBuffer, posBuffer + sizeStringBuilderJcpp, sizeStringBuffer);
    init_ObjectJc(othis, sizeStringBuffer, newIdent_ObjectJc());
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



StringBuilderJc* threadBuffer_StringBuilderJc(ThCxt* _thCxt)
{ return (StringBuilderJc*)getThreadBuffer_StringBuilderJc(false, _thCxt);
}

StringBuilderJc* threadBuffer_s_StringBuilderJc(StringJc src, ThCxt* _thCxt)
{ StringBuilderJc* buffer;
  STACKTRC_TENTRY("threadBuffer_s_StringBuilderJc");
  buffer = (StringBuilderJc*)getThreadBuffer_StringBuilderJc(false, _thCxt);
  append_s_StringBuilderJc(buffer, src, _thCxt);
  STACKTRC_LEAVE; return buffer;
}



#if defined(__cplusplus) && defined(__CPLUSPLUSJcpp)

  StringBuilderJcpp* StringBuilderJcpp::threadBuffer(ThCxt* _thCxt)
  { return (reinterpret_cast<StringBuilderJcpp*>(getThreadBuffer_StringBuilderJc(true, _thCxt)));
  }

  StringBuilderJcpp* threadBuffer_StringBuilderJcpp(ThCxt* _thCxt)
  { return (StringBuilderJcpp*)getThreadBuffer_StringBuilderJc(true, _thCxt);
  }


#endif






/**reads the nrofChars and the reference into local variable. Static subroutine for inner organisation:*/
char* getCharsAndSize_StringBuilderJc(StringBuilderJc* ythis, int* size)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  *size = (ythis->size < 0 ? -ythis->size : ythis->size);
  return( buffer);
}


char* chars_StringBuilderJc(StringBuilderJc* ythis)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  return( buffer);
}


char* getCharsAndCount_StringBuilderJc(StringBuilderJc* ythis, int* count)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  //*count = (ythis->count < 0 ? -ythis->count : ythis->count);
  *count = ythis->_count;
  ;
  return( buffer);
}

char* getCharsSizeCount_StringBuilderJc(StringBuilderJc* ythis, int* size, int* count)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  *size = (ythis->size < 0 ? -ythis->size : ythis->size);
  //*count = (ythis->count < 0 ? -ythis->count : ythis->count);
  *count = ythis->_count;
  return( buffer);
}


int copyToBuffer_StringBuilderJc(StringBuilderJc* ythis, int start, int end, char* buffer, int zBuffer)
{ int count;
  char const* src;
  STACKTRC_ENTRY("copy_StringBuilderJc");
  src = getCharsAndCount_StringBuilderJc(ythis, &count);
  if(count >= (zBuffer-1)){
    if(ythis->_mode & _mNoException_StringBuilderJc){
      count = zBuffer -1;
    } else THROW_s0(IndexOutOfBoundsException, "string to long", count);
  }
  memcpy(buffer, src, count);
  buffer[count] = 0;
  STACKTRC_LEAVE; return count;
}

void _setCount_StringBuilderJc(StringBuilderJc* ythis, int count)
{ ythis->_count = (int16)((ythis->_count & ~mLength__StringJc) | count);
}




int capacity_StringBuilderJc(StringBuilderJc* ythis)
{
  if(ythis->size < 0) return -ythis->size -1;
  else return ythis->size -1;
}






bool setTruncateMode_StringBuilderJc(StringBuilderJc* ythis, bool bTruncate)
{
  bool bRet = ythis->_mode & _mNoException_StringBuilderJc;
  if(bTruncate) { ythis->_mode |= _mNoException_StringBuilderJc; }
  else          { ythis->_mode &= ~_mNoException_StringBuilderJc; }
  return bRet;
}


bool wasTruncated_StringBuilderJc(StringBuilderJc* ythis)
{
  bool bRet = (ythis->_mode & _mTruncated_StringBuilderJc)!=0;
  ythis->_mode &= ~_mTruncated_StringBuilderJc;
  return bRet;
}









//METHOD_C StringJc toString_StringBuilderJc(StringBuilderJc* src, ThCxt* _thCxt)
METHOD_C StringJc toStringNonPersist_StringBuilderJc(ObjectJc* othis, ThCxt* _thCxt)
{
  StringJc ret = NULL_StringJc;
  STACKTRC_TENTRY("toStringNonPersist_StringBuilderJc");
  { StringBuilderJc* ythis = SIMPLE_CAST(StringBuilderJc*, othis);  //admissible because the method is only called for StringBuilderJc
    const char* s0 = ythis->size < 0 ? ythis->value.buffer : ythis->value.direct;
    int count = ythis->_count;
    /**Detect whether the buffer is found in the stack range. Than its memory address is
     * between any address of a local variable and the Thread-Context pointer. */
    bool bufferInStack = ((void*)s0 > (void*)&s0 && (void*)s0 < _thCxt->topmemAddrOfStack); 
    int nonPersistent = 0;
    /**A StringJc is designated as non-persistence, if the StringJc referes a location in a change-able buffer. */
    //xx int nonPersistent = ythis->_mode & _mTemporary_StringBuilderJc ? 0 : mNonPersists__StringJc;
    if(bufferInStack || ythis->_mode & (_mStack_StringBuilderJc | _mThread_StringBuilderJc)){
      nonPersistent |= mNonPersists__StringJc;
    }
    if(ythis->_mode & _mThread_StringBuilderJc){
      nonPersistent |= mThreadContext__StringJc;
    }
    /**If the StringBuffer is a temporary, the String is persistence because the buffer is not use anywhere else.
     * Elsewhere the String is not persistant. That is okay mostly. 
     * If the String will be stored persistent, it would be copied than. 
     */
    INIT_StringJc(ret, s0, count | nonPersistent);

    //false, because it isn't a reference in data: setFromBuffer_StringJc(&ret, ythis);  //the String is contained in the Buffer.
  }
  STACKTRC_LEAVE; return ret;
}


METHOD_C StringJc toStringPersist_StringBuilderJc(ObjectJc* othis, ThCxt* _thCxt)
{
  StringBuilderJc* ythis = SIMPLE_CAST(StringBuilderJc*, othis);  //admissible because the method is only called for StringBuilderJc
  StringJc ret = NULL_StringJc;
  const char* s0 = ythis->size < 0 ? ythis->value.buffer : ythis->value.direct;
  int count = ythis->_count;
  /**Detect whether the buffer is found in the stack range. Than its memory address is
   * between any address of a local variable and the Thread-Context pointer. */
  bool bufferInStack = ((void*)s0 > (void*)&s0 && (void*)s0 < _thCxt->topmemAddrOfStack); 
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
    INIT_StringJc(ret, s0, count);
  } else {
    /**All other usages of buffer assume that the Buffer should be decoupled from the String. 
     * Therefore create a new StringBuilder
     */
    StringBuilderJc* buffer = new_StringBuilderJc(count+1, _thCxt);
    append_zI_StringBuilderJc(buffer, s0, count, _thCxt);
    INIT_StringJc(ret, buffer->value.direct, count);
  }
  //false, because it isn't a reference in data: setFromBuffer_StringJc(&ret, ythis);  //the String is contained in the Buffer.
  STACKTRC_LEAVE; return ret;
}


//NOTE: usage of ObjectJc* is necessary because the method is used instead toString_StringBuilderJc(...)
//      without changing of parameters, only change of mehtod name using Java2C.
//      A simple C-programmer may do also. 
METHOD_C StringJc xxxtoStringNonPersist_StringBuilderJc(ObjectJc* othis, ThCxt* _thCxt)
{
  StringBuilderJc* ythis = SIMPLE_CAST(StringBuilderJc*, othis);  //admissible because the method is only called for StringBuilderJc
  StringJc ret = toString_StringBuilderJc(&ythis->base.object, _thCxt);
  ythis->_mode &= ~_mStringBuilt_StringBuilderJc;
  return ret;
}


METHOD_C StringJc toStringInThreadCxt_StringBuilderJc(StringBuilderJc* ythis, ThCxt* _thCxt)
{
  StringJc ret,src;
  StringBuilderJc* builderThCxt;
  STACKTRC_TENTRY("toStringInThreadCxt_StringBuilderJc");
  src = toStringNonPersist_StringBuilderJc(&ythis->base.object, _thCxt);
  builderThCxt = threadBuffer_s_StringBuilderJc(src, _thCxt);
  ret = toString_StringBuilderJc(&builderThCxt->base.object, _thCxt);
  STACKTRC_LEAVE; return ret;
}

void ctorc_StringBuilderJc(StringBuilderJc* ythis, int size)
{ ctorc_ObjectJc(&ythis->base.object);
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
{ int valueSrc = value_OS_PtrValue(src.s);
  char const* sSrc = PTR_OS_PtrValue(src.s, char const);
  int zSrc = valueSrc & mLength__StringJc;
  STACKTRC_ENTRY("set_StringJc");
  clear_StringJc(ythis);
  if(zSrc == mLength__StringJc) zSrc = strlen(sSrc);
  if(valueSrc & mNonPersists__StringJc){  
    /**It needs to save the String persistents: */
    StringBuilderJc* buffer = new_StringBuilderJc(zSrc, _thCxt); //allocate in heap
    //setTemporary_StringBuilderJc(buffer);  //only referenced by this String.
    replace_zI_StringBuilderJc(buffer, 0,0, sSrc, zSrc, _thCxt); //copy
    sSrc = getCharsAndCount_StringBuilderJc(buffer, &zSrc);
    set_OS_PtrValue((ythis->s), sSrc, zSrc);
  } else {
    //without copy to a new buffer
    set_OS_PtrValue(ythis->s, sSrc, zSrc);
  }
  setBackRefJc(&value_OS_PtrValue(ythis->s), PTR_OS_PtrValue(ythis->s, char const));
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
    StringBuilderJc* buffer = new_StringBuilderJc(zSrc, _thCxt);
    append_s_StringBuilderJc(buffer, src, _thCxt);
    set_OS_PtrValue(ret.s, buffer->value.direct, zSrc);
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
  setValue_OS_PtrValue(ythis.s, value);
  return ythis;
}




StringJc copyToThreadCxt_StringJc(StringJc src, ThCxt* _thCxt)
{
  StringJc ret;
  StringBuilderJc* builderThCxt;
  STACKTRC_TENTRY("copyToThreadCxt_StringJc");
  builderThCxt = threadBuffer_s_StringBuilderJc(src, _thCxt);
  ret = toString_StringBuilderJc(&builderThCxt->base.object, _thCxt);
  STACKTRC_LEAVE; return ret;
}



/* Implementation notes: The functionallity of conversion from a given charset is ignored yet.
   Only the copiing of  bytes is done.
 */
StringJc new_BYIICharset_StringJc(int8_Y* bytes, int offset, int length, StringJc charsetName, ThCxt* _thCxt)
{ //StringBuilderJc* sbuffer;
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



/* Implementation notes: The functionallity of conversion from a given charset is ignored yet.
   Only the copiing of  bytes is done.
 */
StringJc new_mBYIIEncoding_StringJc(PtrVal_int8 bytes, int offset, int length, struct CharsetJc_t* charset, ThCxt* _thCxt)
{ //StringBuilderJc* sbuffer;
  StringJc ret = CONST_StringJc((char*)(bytes.ref+offset), length);  //The string refers to the bytes.
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



StringJc new_CY_StringJc(char_Y* chars, ThCxt* _thCxt)
{
  StringJc ret; 
  int length;
  length = chars->head.length;
  if(length >= mLength__StringJc) {
    STACKTRC_TENTRY("new_CY_StringJc");
    THROW_s0(IndexOutOfBoundsException, "offset <0", length); length = mLength__StringJc-1; 
    STACKTRC_LEAVE;
  }
  set_OS_PtrValue(ret.s, chars->data, length | mNonPersists__StringJc);
  return ret;

}




StringJc new_CYI_StringJc(char_Y* chars, int offset, int count, ThCxt* _thCxt)
{
  StringJc ret; 
  STACKTRC_TENTRY("new_CYI_StringJc");
  if(offset < 0) THROW_s0(IndexOutOfBoundsException, "offset <0", offset);
  if(count < 0) THROW_s0(IndexOutOfBoundsException, "count <0", count);
  if(offset + count > chars->head.length) THROW_s0(IndexOutOfBoundsException, "offset + count > chars.length", offset + count);
  if( (offset + count) >= mLength__StringJc) { THROW_s0(IndexOutOfBoundsException, "offset <0", offset); }
  
  set_OS_PtrValue(ret.s, chars->data + offset, (offset + count) | mNonPersists__StringJc);
 
  STACKTRC_LEAVE; return ret;

}







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
  StringBuilderJc* uBuffer;
  StringJc ret;
  STACKTRC_TENTRY("format_A_StringJc");
  uBuffer = threadBuffer_StringBuilderJc(_thCxt);
  buffer = getCharsAndSize_StringBuilderJc(uBuffer, &zBuffer);
  nrofChars = format_va_arg_Formatter_FW(_thCxt, sFormat, zFormat, buffer, zBuffer, vargList);
  //sbuffer->count = nrofChars;
  _setCount_StringBuilderJc(uBuffer, nrofChars);  
  INIT_StringJc(ret, buffer, nrofChars | mThreadContext__StringJc);
  STACKTRC_LEAVE; return ret;
}




StringJc replace_StringJc(StringJc ythis, char oldChar, char newChar, ThCxt* _thCxt)
{
  StringBuilderJc* sbuffer = null;
  char const* strThis = PTR_StringJc(ythis);
  int lenThis = VAL_StringJc(ythis) & mLength__StringJc;
  char* buffer = null;
  int ii;
  int max;
  StringJc ret;
  STACKTRC_TENTRY("replace_StringJc");
  if(lenThis == mLength__StringJc){ lenThis = strlen_Fwc(strThis, mLength__StringJc); }
  max = lenThis;
  for(ii = 0; ii < max; ++ii)
  { if(strThis[ii] == oldChar)
    { if(sbuffer == null) {
        int maxBuffer;
        sbuffer = threadBuffer_s_StringBuilderJc(ythis, _thCxt);
        buffer = getCharsAndSize_StringBuilderJc(sbuffer, &maxBuffer);
        if(maxBuffer < max){
          THROW_s0(StringIndexOutOfBoundsException, "input string to long", max);
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



StringBuilderJc* replace_u_StringJc(StringJc ythis, char oldChar, char newChar
           , StringBuilderJc* buffer, ThCxt* _thCxt)
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



StringBuilderJc* replace_CC_StringBuilderJc(StringBuilderJc* ythis, char oldChar, char newChar)
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









METHOD_C void setLength_StringBuilderJc(StringBuilderJc* ythis, int newLength, ThCxt* _thCxt)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  int count = ythis->_count;
  STACKTRC_TENTRY("setLength_StringBuilderJc");
  if(newLength < 0)
  { THROW_s0(IndexOutOfBoundsException, "", newLength);
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
    THROW_s0(IndexOutOfBoundsException, "unrecognize", newLength);
  }
  STACKTRC_LEAVE;
}



METHOD_C void clear_StringBuilderJc(StringBuilderJc* ythis)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  memset(buffer, 0, size);
  ythis->_count = 0;
}




char charAt_StringBuilderJc(StringBuilderJc* ythis, int index, ThCxt* _thCxt)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int count = ythis->_count;
  STACKTRC_TENTRY("charAt_StringBuilderJc");
  if(index < 0 || index >=count) THROW_s0(IndexOutOfBoundsException, "", index);
  STACKTRC_LEAVE; return buffer[index];
}




void setCharAt_StringBuilderJc(StringBuilderJc* ythis, int index, char ch, ThCxt* _thCxt)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  STACKTRC_TENTRY("setCharAt_StringBuilderJc");

  if(index >= size || index <0)
  { //StringJc msg = s0_StringJc("StringBuffer to many chars");
    THROW_s0(IndexOutOfBoundsException, "index fault", index);
  }
  buffer[index] = ch;

  STACKTRC_LEAVE;
}



StringBuilderJc* xxxappend_zI_StringBuilderJc(StringBuilderJc* ythis, const char* add, int lengthAdd, ThCxt* _thCxt)
{ int nChars;
  char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  int count = ythis->_count;
  STACKTRC_TENTRY("append_s_StringBuilderJc");

  if(lengthAdd < 0){ lengthAdd = strlen(add); }
  nChars = count + lengthAdd;
  if(nChars > size)
  { //StringJc msg = s0_StringJc("StringBuffer to many chars");
    THROW_s0(RuntimeException, "StringBuffer to many chars", nChars);
  }
  memcpy(buffer + count, add, lengthAdd);
  _setCount_StringBuilderJc(ythis, nChars); //ythis->count = nChars;

  STACKTRC_LEAVE;
  return( ythis);
}

StringBuilderJc* xxxappend_z_StringBuilderJc(StringBuilderJc* ythis, const char* add, ThCxt* _thCxt)
{ STACKTRC_TENTRY("append_s0_StringBuilderJc");
  append_zI_StringBuilderJc(ythis, add, -1, _thCxt);
  STACKTRC_LEAVE;
  return( ythis);
}

StringBuilderJc* append_s_StringBuilderJc(StringBuilderJc* ythis, StringJc add, ThCxt* _thCxt)
{ int lengthAdd = length_StringJc(add);
  STACKTRC_TENTRY("append_s_StringBuilderJc");
  if(lengthAdd == mLength__StringJc){ lengthAdd = -1; }
  append_zI_StringBuilderJc(ythis, PTR_StringJc(add), lengthAdd, _thCxt);
  STACKTRC_LEAVE;
  return( ythis);
}


StringBuilderJc* append_sII_StringBuilderJc(StringBuilderJc* ythis, StringJc src, int start, int end, ThCxt* _thCxt)
{ int lengthMax; char const* src1;
  STACKTRC_TENTRY("append_sII_StringBuilderJc");
  src1 = getCharsAndLength_StringJc(&src, &lengthMax);
  if(start < 0 || end < start || end > lengthMax) THROW_s0(IndexOutOfBoundsException, "fault start/end max=",lengthMax); 
  append_zI_StringBuilderJc(ythis, src1+start, end-start, _thCxt);
  STACKTRC_LEAVE;
  return( ythis);
}




StringBuilderJc* append_u_StringBuilderJc(StringBuilderJc* ythis, StringBuilderJc* add, ThCxt* _thCxt)
{ int lengthAdd;
  char* buffer; 
  int count = ythis->_count;
  STACKTRC_TENTRY("append_Sb_StringBuilderJc");
  buffer = getCharsAndCount_StringBuilderJc(add, &lengthAdd);
  replace_zI_StringBuilderJc(ythis, count, count, buffer, lengthAdd, _thCxt);
  STACKTRC_LEAVE;
  return( ythis);
}






StringBuilderJc* xxxappend_C_StringBuilderJc(StringBuilderJc* ythis, char add, ThCxt* _thCxt)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  int count = ythis->_count;
  int nChars = count + 1;
  STACKTRC_TENTRY("append_C_StringBuilderJc");
  if(nChars > size)
  { //StringJc msg = const_String("StringBuffer to many chars");
    THROW_s0(RuntimeException, "StringBuffer to many chars", nChars);
  }
  buffer[count] = add;
  _setCount_StringBuilderJc(ythis, nChars); //ythis->count = nChars;

  STACKTRC_LEAVE;
  return( ythis);
}



StringBuilderJc* replace_zI_StringBuilderJc(StringBuilderJc* ythis, int start, int end, const char* add, int nAdd, ThCxt* _thCxt)
{ int countNew;
  char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size); //size of the buffer
  int count = ythis->_count;
  int nInsert;  //nr of chars to insert netto
  STACKTRC_TENTRY("replace_zI_StringBuilderJc");
  if(end <= 0){ end = start + (-end); }  //0 or negative value: it is the number of chars.
  if(ythis->_mode & _mStringBuilt_StringBuilderJc){
    THROW_s0(IllegalStateException, "Buffer was used in StringJc", (int)buffer);
  }
  if(nAdd < 0) { nAdd = strlen_Fwc(add, mLength__StringJc); }  //nr of chars of add
  nInsert = nAdd - (end - start); //nr of chars to insert netto, may be positive or negative.
  countNew = count + nInsert;
  if(countNew > size)
  { //in opposite to Java the StringBuffer isnot increased, no dynamically memory management.
    //TODO perhaps test whether it is possible
		if(ythis->_mode & _mNoException_StringBuilderJc){
		  ythis->_mode |= _mTruncated_StringBuilderJc;
			nInsert = size - count;
			nAdd -= (countNew - size);
			countNew = size;
			
		} else {
			THROW_s0(RuntimeException, "StringBuffer too many chars", countNew);
    }
  }
  { int nRest = count - end;  //nr of chars from end of replace area to actual end
    if(nRest > 0) memmove(buffer + end + nInsert, buffer + end, nRest);  //moves in both directions
  }
  //The area to replace is free.
  memcpy(buffer + start, add, nAdd);
  _setCount_StringBuilderJc(ythis, countNew); //ythis->count = countNew;

  STACKTRC_LEAVE; return( ythis);
}



StringBuilderJc* replace_StringBuilderJc(StringBuilderJc* ythis, int start, int end, StringJc add, ThCxt* _thCxt)
{
  int nAdd; 
  const char* sAdd = getCharsAndLength_StringJc(&add, &nAdd);
  return replace_zI_StringBuilderJc(ythis,start, end, sAdd, nAdd, _thCxt); 
}

StringBuilderJc* insert_C_StringBuilderJc(StringBuilderJc* ythis, int offset, char add, ThCxt* _thCxt)
{ //NOTE: a macro isn't able to use because add should be a left value, the actual parameter add doesn't may it.
  return replace_zI_StringBuilderJc(ythis, offset, offset, &add, 1, _thCxt);
}

StringBuilderJc* insert_CYII_StringBuilderJc(StringBuilderJc* ythis, int pos, char_Y* src, int offset, int len, ThCxt* _thCxt)
{ //NOTE: a macro isn't able to use because add should be a left value, the actual parameter add doesn't may it.
  int lenSrc = src->head.length;
  STACKTRC_TENTRY("insert_IcYII_StringBuilderJc");
  if(len == -1){ len = lenSrc; }//Special form to support macro insert_IcY_StringBuilderJc(...)
  if(offset <0 || (offset + len) > lenSrc) THROW(StringIndexOutOfBoundsException, z_StringJc("src indices fault"), offset);
  replace_zI_StringBuilderJc(ythis, pos, 0, &src->data[offset], len, _thCxt);
  STACKTRC_LEAVE; return ythis;
}


/** found an algorithm unusing division, because some divisions may be expensive in time
  * at some processors.
*/
StringBuilderJc* insert_Ir_StringBuilderJc(StringBuilderJc* ythis, int offset, int32 value, int radix, ThCxt* _thCxt)
{ char buffer[33];    //max 32 bits and negativ sign for "-10000000000000000000000000000000"
  StringBuilderJc* ret;
  int nrofChars;
  STACKTRC_TENTRY("insert_Ir_StringBuilderJc");
  nrofChars = toString_Integer_FW(buffer, sizeof(buffer), value, radix, 0, _thCxt);

  ret = replace_zI_StringBuilderJc(ythis, offset, 0, buffer, nrofChars, _thCxt);
  STACKTRC_LEAVE; return( ret);
}


/** found an algorithm unusing division, because some divisions may be expensive in time
  * at some processors.
*/
StringBuilderJc* insert_Jr_StringBuilderJc(StringBuilderJc* ythis, int offset, int64 value, int radix, ThCxt* _thCxt)
{ char buffer[65];    //max 32 bits and negativ sign for "-10000000000000000000000000000000"
  char cc;
  /**Array of values to test the position in digit. Fill it with 10, 100 etc if radix = 10;*/
  int64 testValues[64];

  int idxTestValues = 0;
  int nChars = 0;
  int64 test = radix;
  StringBuilderJc* ret;
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


StringJc toString_DoubleJc(double value, ThCxt* _thCxt)
{ StringBuilderJc* sbuffer;
  STACKTRC_TENTRY("toString_DoubleJc");
  { int size;
    char* buffer;
    int count;
    sbuffer = threadBuffer_StringBuilderJc(_thCxt);
    buffer = getCharsAndSize_StringBuilderJc(sbuffer, &size); 
    count = sprintf(buffer, "%d", value);
    _setCount_StringBuilderJc(sbuffer, count); //
  }
  STACKTRC_LEAVE;
  return toString_StringBuilderJc(&sbuffer->base.object, _thCxt);
}





#if 0
StringBuilderJc* append_I_StringBuilderJc(StringBuilderJc* ythis, int value)
{ STACKTRC_ENTRY("append_I_StringBuilderJc");
  insert_I_StringBuilderJc(ythis, ythis->count, value, 10, _thCxt);
  STACKTRC_LEAVE; return ythis;
}
#endif


StringBuilderJc* insert_sII_StringBuilderJc(StringBuilderJc* ythis, int offset, StringJc add, int start, int end, ThCxt* _thCxt)
{ STACKTRC_TENTRY("insert_sII_StringBuilderJc");
  { int nAdd; 
    const char* sAdd = getCharsAndLength_StringJc(&add, &nAdd);
    if(end < start || end > nAdd || start <0) THROW_s0(IndexOutOfBoundsException, "", end);
    sAdd += start;
    nAdd = end - start;
    replace_zI_StringBuilderJc(ythis, offset, offset, sAdd, nAdd, _thCxt);
  }
  STACKTRC_LEAVE; return ythis;
}





StringBuilderJc* insert_F_StringBuilderJc(StringBuilderJc* ythis, int index, float value, ThCxt* _thCxt)
{ char buffer[20];
  int nChars;
  nChars = sprintf(buffer, "%f", value);
  return replace_zI_StringBuilderJc(ythis, index, 0, buffer, nChars, _thCxt);
}




StringBuilderJc* insert_D_StringBuilderJc(StringBuilderJc* ythis, int index, double value, ThCxt* _thCxt)
{ char buffer[40];
  int nChars;
  nChars = sprintf(buffer, "%d", value);
  return replace_zI_StringBuilderJc(ythis, index, 0, buffer, nChars, _thCxt);
}




StringBuilderJc* insert_cYii_StringBuilderJc(StringBuilderJc* thiz, int offset, CharSeqJc add, int start, int end, struct ThreadContextFW_t* _thCxt)
{
  int countNew;
  char* buffer = (thiz->size < 0 ? thiz->value.buffer : thiz->value.direct);
  int size = (thiz->size < 0 ? -thiz->size : thiz->size); //size of the buffer
  int count = thiz->_count;
  int nInsert = end - start;  //nr of chars to insert netto
  STACKTRC_TENTRY("insert_cYii_StringBuilderJc");
  int endmax = length_CharSeqJc(add, _ThCxt);
  if(offset < 0) { //check offset
    offset = thiz->_count + offset +1; //-1: it is _count
  }
  if(offset <0){ offset = 0; }
  //check end
  if(end < 0){
    end = endmax - end +1;  //-1 result in endmax
  }
  if(end <0) {
    end = 0; 
  } else if(end > endmax){
    return thiz;  //do nothing, nothing to append
  }
  if(thiz->_mode & _mStringBuilt_StringBuilderJc){
    THROW_s0(IllegalStateException, "Buffer was used in StringJc", (int)buffer);
  }
  countNew = count + nInsert;
  if(countNew > size)
  { //in opposite to Java the StringBuffer is not increased, no dynamically memory management.
    //TODO perhaps test whether it is possible
		if(thiz->_mode & _mNoException_StringBuilderJc){
		  thiz->_mode |= _mTruncated_StringBuilderJc;
			nInsert = size - count;
			countNew = size;
		} else {
			THROW_s0(RuntimeException, "StringBuffer too many chars", countNew);
    }
  }
  { int nRest = count - end;  //nr of chars from end of replace area to actual end
    if(nRest > 0) memmove(buffer + end + nInsert, buffer + end, nRest);  //moves in both directions
  }
  //The area to replace is free.
  //Read characters and insert

  copyToBuffer_CharSeqJc(add, start, end, buffer + offset, thiz->size - offset);
  _setCount_StringBuilderJc(thiz, countNew); //thiz->count = countNew;

  STACKTRC_LEAVE; return( thiz);
}





METHOD_C StringBuilderJc* delete_StringBuilderJc(StringBuilderJc* ythis, int start, int end, ThCxt* _thCxt)
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
  { THROW_s0(StringIndexOutOfBoundsException, "", 0);
  }
  STACKTRC_LEAVE;
  return ythis;
}


METHOD_C void cleanToSize_StringBuilderJc(StringBuilderJc* ythis)
{ char* buffer = (ythis->size < 0 ? ythis->value.buffer : ythis->value.direct);
  int size = (ythis->size < 0 ? -ythis->size : ythis->size);
  int count = ythis->_count;
  if(count >= 0 && count <= size)
  { memset(buffer + count, 0, size - count);  //store 0 at rest to clean it.
  }
  else
  { STACKTRC_ENTRY("cleanToSize_StringBuilderJc");
    THROW_s0(RuntimeException, "corrupt content, count=", ythis->_count);
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


typedef struct Mtbl_StringBufferJc_t 
{ MtblHeadJc head;
  Mtbl_ObjectJc ObjectJc; 
  //Method table of interfaces:
  Mtbl_CharSeqJc CharSeqJc;
} Mtbl_StringBufferJc;


typedef struct MtblDef_StringBufferJc_t { Mtbl_StringBufferJc mtbl; MtblHeadJc end; } MtblDef_StringBufferJc;

 extern MtblDef_StringBufferJc const mtblStringBufferJc;

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





/**Define the reflection in that source, which used it. */
const struct Reflection_Fields_StringBuilderJc_t
{ ObjectArrayJc head;
  FieldJc data[4];
} reflection_Fields_StringBuilderJc =
{ CONST_ObjectArrayJc(FieldJc, 4, OBJTYPE_FieldJc, null, &reflection_Fields_StringBuilderJc)
, {
    { "_count"
    , 0 //nrofArrayElements
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StringBuilderJc*)(0x1000))->_count) - (int32)(StringBuilderJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StringBuilderJc
    }
  , { "size"
    , 0 //nrofArrayElements
    , REFLECTION_int16
    , (2<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StringBuilderJc*)(0x1000))->size) - (int32)(StringBuilderJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StringBuilderJc
    }
  , { "_mode"
    , 0 //nrofArrayElements
    , REFLECTION_int32
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StringBuilderJc*)(0x1000))->_mode) - (int32)(StringBuilderJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StringBuilderJc
    }
  , { "value"
    , 0 //nrofArrayElements
    , REFLECTION_void
    , (4<<kBitPrimitiv_Modifier_reflectJc) //bitModifiers
    , (int16)((int32)(&((StringBuilderJc*)(0x1000))->value) - (int32)(StringBuilderJc*)0x1000)
    , 0  //offsetToObjectifcBase
    , &reflection_StringBuilderJc
    }
} };


const ClassJc reflection_StringBuilderJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_StringBuilderJc, &reflection_ClassJc)
, "StringBuilderJc"
, 0
, sizeof(StringBuilderJc)
, (FieldJcArray const*)&reflection_Fields_StringBuilderJc  //attributes and associations
, null  //method
, null  //superclass
, null  //interfaces
, 0 
, &mtblStringBufferJc.mtbl.head
};



#define reflection_StringBuilderJc_s reflection_StringBuilderJc
DEFINE_REFLECTION_REF(StringBuilderJc);





//#include "Jc/ReflectionJc.h"

//DEFINE_REFLECTION_REF(StringBuilderJc);
