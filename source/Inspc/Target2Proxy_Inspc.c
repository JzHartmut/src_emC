/**This file contains the adaption of the Inspc-Interface via Accsess with the simple interface
 * made by Hartmut Schorrig, www vishia.org
 * date first: 2010
 * date last change: 2016-10-29
 */
#include "Inspc/Target2Proxy_Inspc.h"
#include <OSAL/os_AtomicAccess.h>
#include <applstdef_emC.h>

#ifndef __DONOTUSE_REFLECTION__
  #include "Inspc/Target2Proxy_Inspc.crefl"
#else
  
#endif

#undef PRINTF2
#define PRINTF2(TEXT, VAL) //empty.

int32 processInspcCmdOnTarget_Inspc(Cmd_InspcTargetProxyTelg_e const cmd, int32 address, int32 inputVal, void const* mainData
, int32 const* reflectionOffset_MainData, int32 const* const* reflectionOffsetArrays)
{ int32 retVal;  
  switch( cmd )
  {
    case getRootInstance_InspcTargetProxyTelg: {
      retVal = (int32)mainData;  //Address of the root instance.
      PRINTF2("getRootInstance %8.8X\n", retVal);
    } break;       
    case getRootType_InspcTargetProxyTelg: {
      retVal = reflectionOffset_MainData[0];
      PRINTF2("getRootType %8.8X\n", retVal);
    } break;
    case getType_InspcTargetProxyTelg: {
      retVal = 0;
      PRINTF2("getType %8.8X\n", retVal);
    } break;
    case getOffsetLength_InspcTargetProxyTelg: {
      int ixClass = (inputVal >>16) & 0xffff;
      int ixField = inputVal & 0xffff;
      int32 const* offsetArray = reflectionOffsetArrays[ixClass];
      retVal = offsetArray[ixField];
      PRINTF2("getOffsetLength %8.8X\n", retVal);
    } break;
    case getRealLengthStaticArray_InspcTargetProxyTelg: {
      void** adr = (void**)address;  //an array of pointers.
      int length = inputVal;
      while(length > 0 &&  ((void**)(adr))[length-1] == null)  //dereferenced at the given position with index.
      { length -=1;
      }
      retVal = length;
      PRINTF2("getRealLengthStaticArray %8.8X\n", retVal);
    }break;
    case getInt16_InspcTargetProxyTelg:
    {
      retVal = (*(int16*)(address)) & 0xFFFF;
      PRINTF2("getInt16 %8.8X\n", retVal);
      
    } break;
    case getInt32_InspcTargetProxyTelg:
    {
      retVal = *(int32*)address;
      PRINTF2("getInt32 %8.8X\n", retVal);
      
    } break;
    case getInt64_InspcTargetProxyTelg: {
      retVal = *(int32*)address;
      PRINTF2("getInt64 %8.8X\n", retVal);
    } break;
    case getFloat_InspcTargetProxyTelg:
    {
      retVal = *(int32*)address;  //return float as int-image. It is standard-IEEE
      PRINTF2("getFloat %8.8X\n", retVal);
    } break;
    case getDouble_InspcTargetProxyTelg: {
      *(float*)&retVal = (float)(*(double*)address);
      PRINTF2("getDouble %8.8X\n", retVal);
    } break;
    case getRef_InspcTargetProxyTelg: {
      retVal = *(int*)address;  //return float as int-image. It is standard-IEEE
      PRINTF2("getAddr %8.8X\n", retVal);
    } break;
    case setByte_InspcTargetProxyTelg: {
      retVal = *(int8*)address;  //return float as int-image. It is standard-IEEE
      PRINTF2("setByte %8.8X\n", retVal);
    } break;
    case setInt16_InspcTargetProxyTelg: {
      *((int16*)address) = (int16)(inputVal & 0xFFFF); 
      retVal = (*(int16*)address) & 0xFFFF;
      PRINTF2("setInt16 %8.8X\n", retVal);
    } break;
    case setInt32_InspcTargetProxyTelg: {
      *((int32*)address) = inputVal; 
      retVal = *(int32*)address;
      PRINTF2("setInt32 %8.8X\n", retVal);
    } break;
    case setInt64_InspcTargetProxyTelg: {
      *((int64*)address) = inputVal; 
      retVal = (int32)(*(int64*)address);    
      PRINTF2("setInt64 %8.8X\n", retVal);
    } break;
    case setFloat_InspcTargetProxyTelg:
    {
      //*((float*)address) = *(float*)&inputVal;    
      *((int32*)address) = inputVal;   //Set the image, it is a float.    
      retVal = *(int32*)address;  
      PRINTF2("setFloat %8.8X\n", retVal);
    } break;
    case setDouble_InspcTargetProxyTelg: {
      *((double*)address) = *(float*)&inputVal;  //The input value is gotten as float, only 32 bit.      
      *(float*)&retVal = (float)(*((double*)address)); 
      PRINTF2("setDouble %8.8X\n", retVal);
    } break;
    case setRef_InspcTargetProxyTelg: {
      *((void**)address) = *(void**)&inputVal;      
      retVal = (int32)*((void**)address);
      PRINTF2("setAddr %8.8X\n", retVal);
    } break; 
    
    case getBitfield_InspcTargetProxyTelg:
    {
      int posBits = (inputVal & mPosBitsInBitfieldAccess_InspcTargetProxyTelg) >> bitPosBitsInBitfieldAccess_InspcTargetProxyTelg ;
      int posByte = posBits >> 3;
      int nrofBits = (inputVal & mNrofBitsInBitfieldAccess_InspcTargetProxyTelg) >> bitNrofBitsInBitfieldAccess_InspcTargetProxyTelg ;
      if(nrofBits ==0){ nrofBits = 16; }

      //regard the possibilities of the target processor in bit/byte-access!
      //regard thread safety!

      //This example works on a PC-hardware without bit-access instructions, but with full byte-access!
      //adjust the memory address, because the posBits may be in range 0..4095 (512 Bytes):
        int offsetByte = (posBits >> 3) & 0xfffc;
        posBits = posBits - ( 8 * offsetByte );

        MemUnit* addr1 = ((MemUnit*)address) + (offsetByte / BYTE_IN_MemUnit); //calculate the byte/word-address where the bits are found. 
        int32 mask = ((1 << nrofBits) -1) << posBits;
        int32 valueRaw;
        valueRaw = *(int32*)addr1;
        retVal = (valueRaw & mask) >> posBits;
      PRINTF2("getBitField %8.8X\n", retVal);
    } break;   
    case setBitfield_InspcTargetProxyTelg:
    {
            //regard the possibilities of the target processor in bit/byte-access!
      //regard thread safety!
      //This example works on a PC-hardware without bit-access instructions, but with full byte-access!
      //adjust the memory address, because the posBits may be in range 0..4095 (512 Bytes):
      int posBits = (inputVal & mPosBitsInBitfieldAccess_InspcTargetProxyTelg) >> bitPosBitsInBitfieldAccess_InspcTargetProxyTelg ;
      int nrofBits = (inputVal & mNrofBitsInBitfieldAccess_InspcTargetProxyTelg) >> bitNrofBitsInBitfieldAccess_InspcTargetProxyTelg ;
      int setValue = (inputVal & mValueInBitfieldAccess_InspcTargetProxyTelg) >> kBitValueInBitfieldAccess_InspcTargetProxyTelg ;
      int offsetByte;
      //NOTE: use 32 bit anytime, because compareAndSet_AtomicInteger is available yet only for 32 bit,
      //and the DSP-Implementation should use 32 bit,
      offsetByte = (posBits >> 3) & 0xfffc;
      posBits -= 8 * offsetByte;
      { 
        MemUnit* addr1 = ((MemUnit*)address) + (offsetByte / BYTE_IN_MemUnit);  //calculate the byte/word-address where the bits are found. 
        int32 mask = ((1<<nrofBits) -1) << posBits;
        int32 setValueBit = setValue; 
        int32 oldValue, newValue;
        int catastrophicCount = 1000;  //it should be success in 1 or a few accesses.
        do
        {
          oldValue = *(int32*)addr1;
          newValue = oldValue & ~mask;  //delete this bits.
          newValue |= (setValueBit << posBits) & mask;
        } while( !compareAndSet_AtomicInteger((volatile int32*)addr1, oldValue, newValue)
               && --catastrophicCount >0);
        newValue = *(int32*)addr1;  //re-read from memory 
        retVal = newValue >> posBits & (mask >> posBits);
        PRINTF2("setBitField %8.8X\n", retVal);
      }
    } break; 
    default: 
      retVal = -1;
  }//switch    
  return retVal;
}



void step_Target2Proxy_Inspc(Target2Proxy_Inspc* thiz
  , void const* rootData
  , int32 const* reflectionOffset_RootData, int32 const* const* reflectionOffsetArrays
) {
  thiz->lifeCt += 1;
  setInt32BigEndian(&thiz->target2proxy->lifeCt_ErrorState, (((int32_t)thiz->lifeCt) << 16) | thiz->errorMsg);
  int32 seqnr = getInt32BigEndian(&thiz->proxy2target->seqnr);
  if ((int)seqnr != thiz->seqnrLast) {
    Cmd_InspcTargetProxyTelg_e cmd = (Cmd_InspcTargetProxyTelg_e)(getInt32BigEndian(&thiz->proxy2target->length_cmd) & 0xffff);
    int32 address = getInt32BigEndian(&thiz->proxy2target->address);
    int32 value = getInt32BigEndian(&thiz->proxy2target->value);
    int32 retValue = processInspcCmdOnTarget_Inspc(cmd, address, value, rootData, reflectionOffset_RootData, reflectionOffsetArrays);
    setInt32BigEndian(&thiz->target2proxy->retValue, retValue);
    setInt32BigEndian(&thiz->target2proxy->seqnr, seqnr);  //therewith it will be processed.
  }

}



