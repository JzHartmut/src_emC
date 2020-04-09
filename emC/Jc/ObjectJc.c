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
 * @content Implementation of ObjectJc
 *
 * @author Hartmut Schorrig
 * @version 0.82
 * list of changes:
 * 2010-02-05: Hartmut corr: new_ObjectArrayJc(...) was an old implementation, used and improved.
 * 2009-06-23: Hartmut corr: setSizeAndIdent_ObjectJc(), first try to use small size mask.
 * 2008-04-22: Hartmut adap:The elements idSemaphore and idWaitingThread are combined to idSyncHandles.
 * 2006-05-00: Hartmut creation
 *
 ****************************************************************************/

#include "emC/Jc/ObjectJc.h" 

#include <stdlib.h>     //malloc
#include <string.h>     //memset
//#include "StringJc.h"
#include "emC/Jc/ReflectionJc.h"

//#include "os_wrapper.h"

/********************************************************************************************/
//Object

#ifdef DEF_REFLECTION_FULL
  //donot: #include "Jc/ObjectJc.crefl"  because this refelctions are defined in ReflectionBaseTypesJc.c
#endif


bool castOk_ObjectJc;








/************************************************************************/







/**common method for creating and initilizing buffers in threadcontext. 
 * @return pointer to ObjectJc in ThreadContext.
 */
ObjectJc* allocInThreadCxt_ObjectJc(int size, char const* sign, ThCxt* _thCxt)
{ 
  ObjectJc* ret;
  STACKTRC_TENTRY("threadBuffer_StringBuilderJc");
  {
    MemC mBuffer = getUserBuffer_ThreadContext_emC(size, sign, _thCxt);
    /**Check whether the buffer is in use, TODO... */
    int sizeBufferThreadContext = size_MemC(mBuffer);
    if(size > sizeBufferThreadContext) THROW1_s0(RuntimeException, "to large ObjectJc in ThreadBuffer", size);

    ret = ADDR_MemC(mBuffer, ObjectJc);
    init_ObjectJc(ret, size, newIdent_ObjectJc());
    //sBuffer->_mode |= _mThread_StringBuilderJc;
  }
  STACKTRC_LEAVE; 
  return ret;
}







/********************************************************************************************/
//Object__Array


void* get_i_ObjectArrayJc(ObjectArrayJc const* ythis, int idx)
{
  if(idx < 0 || idx > ythis->length){ return null; } //IndexOutOfBoundaryException
  else
  {
    int offset = idx * ythis->sizeElement;
    if(true) //ythis->mode == kDirect_ObjectArrayJc)
    {
      return ((MemUnit*)(ythis + 1)) + offset;
    }
    else
    { return 0;
    }
  }
}


int size_Object__ArrayJc(const ObjectArrayJc* ythis)
{
  return ythis->length;
}


/** Gets the number of bytes of the whole array calculated from the informations inside the head.
  */
METHOD_C int getNrOfBytes_ObjectArrayJc(ObjectArrayJc const* ythis)
{ return sizeof(ObjectArrayJc) + ythis->length * ythis->sizeElement;
}


void_Y* ctorO_AYJc(ObjectJc* othis, int nBytesPerElement, int nSize)
{ void_Y* ythis = (void_Y*)(othis);
  if(ythis != null)
  { ctorc_ObjectJc(&ythis->head.object);
    ythis->head.object.state.b.objectIdentSize |= mArray_objectIdentSize_ObjectJc;
    ythis->head.length = nSize;
    ythis->head.sizeElement = (int16)nBytesPerElement;
    ythis->head.mode = 0; //kDirect_ObjectArrayJc;
  }
  return ythis;
}



ObjectArrayJc* ctorc_ObjectArrayJc(ObjectArrayJc* ythis, int nSize, int nBytesPerElement, struct ClassJc_t const* reflection, int32 typeInstanceIdent)
{ //ObjectArrayJc* arrayHead = (ObjectArrayJc*)(ythis);  //the universal type of ARRAYJc
  STACKTRC_ENTRY("ctorc_ObjectArrayJc");
  if(ythis != null)
  { int32 sizeArray;
    int32 sizeInfoObject;
    ctorc_ObjectJc(&ythis->object);
    sizeArray = nSize * nBytesPerElement + sizeof(ObjectArrayJc);
    sizeInfoObject = getSizeInfo_ObjectJc(&ythis->object);  //may be setted or it should be 0
      if(sizeInfoObject > 0 && sizeInfoObject < sizeArray)
      { THROW1_s0(IllegalArgumentException, "size mismatch", sizeArray);
      }    
      if( (typeInstanceIdent & mSizeBits_objectIdentSize_ObjectJc) == kIsSmallSize_objectIdentSize_ObjectJc)
      { if(sizeArray > mSizeSmall_objectIdentSize_ObjectJc)
        { THROW1_s0(IndexOutOfBoundsException, "too large", sizeArray);
        }
        typeInstanceIdent &= ~mSizeSmall_objectIdentSize_ObjectJc;
      }
      else if( (typeInstanceIdent & mSizeBits_objectIdentSize_ObjectJc) == kIsMediumSize_objectIdentSize_ObjectJc)
      { if(sizeArray > mSizeMedium_objectIdentSize_ObjectJc)
        { THROW1_s0(IndexOutOfBoundsException, "too large", sizeArray);
        }
        typeInstanceIdent &= ~mSizeMedium_objectIdentSize_ObjectJc;
      }
      else if(typeInstanceIdent & mIsLargeSize_objectIdentSize_ObjectJc)
      { if(sizeArray > mSizeLarge_objectIdentSize_ObjectJc)
        { THROW1_s0(IndexOutOfBoundsException, "too large", sizeArray);
        }
        typeInstanceIdent &= ~mSizeLarge_objectIdentSize_ObjectJc;
      }
      else
      { THROW1_s0(IndexOutOfBoundsException, "undefined size", typeInstanceIdent);
      }
      typeInstanceIdent |= sizeArray;
      //it is always 1-dimension.
      typeInstanceIdent = (typeInstanceIdent & ~mArray_objectIdentSize_ObjectJc) | mArray_objectIdentSize_ObjectJc;
    }
    setReflection_ObjectJc(&ythis->object, reflection, typeInstanceIdent);

    ythis->length = nSize;
    ythis->sizeElement = (int16)nBytesPerElement;
    ythis->mode = 0; //kDirect_ObjectArrayJc;
    { MemUnit* data = (MemUnit*)(ythis) + sizeof(ObjectArrayJc);  //The data are assigned always immediately after the head. This is the law.
      memset(data, 0, nSize * nBytesPerElement);
    }
  STACKTRC_LEAVE;
  return ythis;
}


ObjectArrayJc* ctorO_ObjectArrayJc(ObjectJc* othis, int size, int nBytesPerElement, struct ClassJc_t const* reflection, int32 typeInstanceIdent)
{ ObjectArrayJc* ythis = (ObjectArrayJc*)othis;
//  ctorc_ObjectArrayJc(ythis, size, nBytesPerElement, reflection, typeInstanceIdent);
  STACKTRC_ENTRY("ctorO_ObjectArrayJc");
  if(ythis != null)
  { int32 sizeArray;
    int32 sizeInfoObject;
    int32 objectIdentSize;
    //ctorc_ObjectJc(&ythis->object);
    sizeArray = size * nBytesPerElement + sizeof(ObjectArrayJc);
    sizeInfoObject = getSizeInfo_ObjectJc(&ythis->object);
    if(sizeArray > sizeInfoObject) THROW1_s0(IllegalArgumentException, "less sizeObject, require=", sizeArray);
    objectIdentSize = (othis->state.b.objectIdentSize & ~mArray_objectIdentSize_ObjectJc) | mArray_objectIdentSize_ObjectJc;
    setReflection_ObjectJc(&ythis->object, reflection, objectIdentSize);

    ythis->length = size;
    ythis->sizeElement = (int16)nBytesPerElement;
    ythis->mode = 0; //kDirect_ObjectArrayJc;
    { MemUnit* data = (MemUnit*)(ythis) + sizeof(ObjectArrayJc);  //The data are assigned always immediately after the head. This is the law.
      memset(data, 0, size * nBytesPerElement);
    }
  }
  STACKTRC_LEAVE; return ythis;
}





ObjectArrayJc* new_ObjectArrayJc(int SIZE, int BYTESELEMENT, struct ClassJc_t const* REFLECTION, int32 typeInstanceIdent)
{ int nrofBytes = sizeof(ObjectArrayJc) + SIZE * BYTESELEMENT;
  ObjectArrayJc* nthis;
  ObjectJc* othis;
  STACKTRC_ENTRY("new_ObjectArrayJc");
  othis = alloc_ObjectJc( nrofBytes, typeInstanceIdent, _thCxt);
  nthis = ctorO_ObjectArrayJc(othis, SIZE, BYTESELEMENT, REFLECTION, typeInstanceIdent);
  STACKTRC_LEAVE;
  return nthis;
  //return &address->object;
}




MemUnit* getAddrSizeof_ObjectArrayJc(ObjectArrayJc* ythis, int32* size)
{ MemUnit* addr;
  int dimensions = (ythis->mode & mDimension_ObjectArrayJc) >> kBitDimension_ObjectArrayJc;
  if(dimensions == 0){ dimensions = 1; }
  addr = ((MemUnit*)ythis) + sizeof(ObjectArrayJc) + (dimensions-1)*sizeof(int32);
  if(size !=null){
    int idim;
    int* lengthptr = (int*)(&ythis->length);
    int32 nrofBytes = (ythis->mode & mPointered_ObjectArrayJc) ? sizeof(void*) : ythis->sizeElement;
    for(idim = 0; idim < dimensions; ++idim){
      int lengthDim = *lengthptr++;
      nrofBytes *= lengthDim;
    }
    *size = nrofBytes;
  }
  return addr;
}



MemC buildFromArrayX_MemC(ObjectArrayJc* objArray)
{
  MemC mem;
  int32 nrofBytes;
  void* addr = getAddrSizeof_ObjectArrayJc(objArray, &nrofBytes);
  
  SET_MemC(mem, addr, nrofBytes);
  return mem;
}



int32_ObjArray* ctor_int32ARRAY(int32_ObjArray* ythis, int nrOfElements)
{ if(ythis != null)
  { ythis->head.length = nrOfElements;
    ythis->head.sizeElement = sizeof(int32);
    ythis->head.mode = 0; //kDirect_ObjectArrayJc;
    memset(ythis->data, 0, nrOfElements * ythis->head.sizeElement);
  }
  return ythis;
}





const ClassJc xxxreflection_ObjectJc =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &xxxreflection_ObjectJc, null)
, "ObjectJc"
, 0
, sizeof(ObjectJc)
, null  //attributes
, null  //method
, null  //superclass
, null  //interfaces
, mObjectJc_Modifier_reflectJc  //modifiers
};


char const sign_Mtbl_ComparableJc[] = "Mtbl_ComparableJc";

char const sign_Mtbl_FlushableJc[] = "Mtbl_FlushableJc";

char const sign_Mtbl_CloseableJc[] = "Mtbl_CloseableJc";

char const sign_Mtbl_AppendableJc[] = "Mtbl_AppendableJc";



extern_C const ClassJc reflection_ObjectJcREF;  //the just defined reflection_ used in the own fields.

const struct Reflection_Fields_ObjectJcREF_t
{ ObjectArrayJc head;
  FieldJc data[1];
} reflection_Fields_ObjectJcREF =
{ CONST_ObjectArrayJc(FieldJc, 1, OBJTYPE_FieldJc, null, &reflection_Fields_ObjectJcREF)
, { { "ptr"
    , 0   //no Array, no Bitfield
    , &reflection_ObjectJc                                                                                            
    , 0|kReference_Modifier_reflectJc //bitModifiers
    , 0 //offset
    , 0  //offsetToObjectifcBase
    , &reflection_ObjectJcREF
    }
} };
  
const ClassJc reflection_ObjectJcREF =
{ CONST_ObjectJc(OBJTYPE_ClassJc + sizeof(ClassJc), &reflection_ObjectJcREF, &reflection_ClassJc)
, "ObjectJcREF"
, 0
, sizeof(ObjectJcREF)
, (FieldJcArray const*)&reflection_Fields_ObjectJcREF  //attributes and associations
, null  //method      
, null  //superclass  
, null  //interfaces  
, 0 
, null  //virtual table
};


#ifndef DEF_REFLECTION_NO
#include <emC/Jc/genRefl/ObjectRefJc.crefl>
#endif
