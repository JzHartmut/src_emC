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
 *
 * @content like java.lang.System.
 *
 *
 * @author JcHartmut www.vishia.org
 * @version 0.83
 * list of changes:
 * 2007-05-00: JcHartmut creation
 *
 ****************************************************************************/
#include "Jc/SystemJc.h"
#include "Fwc/fw_ThreadContext.h"
#include "Fwc/fw_Exception.h"




#include <string.h>

void arraycopy_SystemJc(ObjectJc* src, int srcPos, ObjectJc* dst, int dstPos, int length, ThCxt* _thCxt)
{ ObjectArrayJc* srcArray = (ObjectArrayJc*)src;  //TODO test whether it is admissible
  ObjectArrayJc* dstArray = (ObjectArrayJc*)dst;  //TODO test whether it is admissible
  STACKTRC_TENTRY("arraycopy_SystemJc");
  if(srcPos < 0 || srcPos > srcArray->length) THROW_s0(IndexOutOfBoundsException, "srcPos failed", srcPos);
  if(dstPos < 0 || dstPos > dstArray->length) THROW_s0(IndexOutOfBoundsException, "dstPos failed", dstPos);
  if(srcPos +length > srcArray->length || dstPos +length > dstArray->length) THROW_s0(IndexOutOfBoundsException, "length failed", length);
  if(srcArray->sizeElement != dstArray->sizeElement) THROW_s0(ArrayStoreException, "dstPos failed", dstPos);
  { int sizeElement = srcArray->sizeElement; 
    int nrofBytes = sizeElement * length;
    int srcPosBytes = sizeElement * srcPos;
    int dstPosBytes = sizeElement * dstPos;
    //TODO test whehter it is in the size of ObjectJc, use objectIdentSize
    int srcMaxNrofBytes = getSizeInfo_ObjectJc(src);
    int dstMaxNrofBytes = getSizeInfo_ObjectJc(dst);
    if(sizeElement < 0) THROW_s0(ArrayStoreException, "src/dst-consistence failed, sizeElement negative", sizeElement);
    if(srcPosBytes + nrofBytes > srcMaxNrofBytes) THROW_s0(ArrayStoreException, "src-consistence failed", (int)(src));
    if(dstPosBytes + nrofBytes > dstMaxNrofBytes) THROW_s0(ArrayStoreException, "dst-consistence failed", (int)(dst));
    //all is tested.
    { MemUnit* dst = (MemUnit*)(dstArray +1);   //The position after the head data.
      MemUnit* src = (MemUnit*)(srcArray +1);
      memmove( dst +dstPosBytes, src +srcPosBytes, nrofBytes); 
    }
  }
  STACKTRC_LEAVE;
}


void arraycopy_v_SystemJc(ByteStringJc src, int srcPos, ObjectJc* dst, int dstPos, int length, ThCxt* _thCxt)
{ ObjectArrayJc* dstArray = (ObjectArrayJc*)dst;  //TODO test whether it is admissible
  int srclen = length_ByteStringJc(src);
  int8* srcPtr = data_ByteStringJc(src);
  STACKTRC_TENTRY("arraycopy_SystemJc");
  if(srcPos < 0 || srcPos > srclen) THROW_s0(IndexOutOfBoundsException, "srcPos failed", srcPos);
  if(dstPos < 0 || dstPos > dstArray->length) THROW_s0(IndexOutOfBoundsException, "dstPos failed", dstPos);
  if(srcPos +length > srclen || dstPos +length > dstArray->length) THROW_s0(IndexOutOfBoundsException, "length failed", length);
  if(1 != dstArray->sizeElement) THROW_s0(ArrayStoreException, "dstPos failed", dstPos);
  { int sizeElement = 1; 
    int nrofBytes = sizeElement * length;
    int srcPosBytes = sizeElement * srcPos;
    int dstPosBytes = sizeElement * dstPos;
    //TODO test whehter it is in the size of ObjectJc, use objectIdentSize
    int srcMaxNrofBytes = srclen;
    int dstMaxNrofBytes = getSizeInfo_ObjectJc(dst);
    if(sizeElement < 0) THROW_s0(ArrayStoreException, "src/dst-consistence failed, sizeElement negative", sizeElement);
    if(srcPosBytes + nrofBytes > srcMaxNrofBytes) THROW_s0(ArrayStoreException, "src-consistence failed", (int)(srcPtr));
    if(dstPosBytes + nrofBytes > dstMaxNrofBytes) THROW_s0(ArrayStoreException, "dst-consistence failed", (int)(dst));
    //all is tested.
    { MemUnit* dst = (MemUnit*)(dstArray +1);   //The position after the head data.
      MemUnit* src = (MemUnit*)srcPtr;
      memmove( dst +dstPosBytes, src +srcPosBytes, nrofBytes); 
    }
  }
  STACKTRC_LEAVE;
}


//PrintStreamJcREF out_SystemJc = NULL_REFJc; 
//PrintStreamJc_s* out_SystemJc = null;

int64 nanoPerClock_SystemJc = 1;

int64 nanoTime_SystemJc(ThCxt* _thCxt)
{ return nanoPerClock_SystemJc * os_getClockCnt();
}


