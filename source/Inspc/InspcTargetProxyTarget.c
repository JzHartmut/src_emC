/**This file contains the adaption of the Inspc-Interface via Accsess with the simple interface
 * made by Hartmut Schorrig, www vishia.org
 * date first: 2010
 * date last change: 2016-10-29
 */
#include "InspcTargetProxyTelg.h"
#include <os_AtomicAccess.h>
#include <OSAL_UserExceptionAndDebug.h>

int32 processInspcCmdOnTarget_Inspc(Cmd_InspcTargetProxyTelg_e const cmd, int32 address, int32 inputVal, void const* mainData
, int32 const* reflectionOffset_MainData, int32 const* const* reflectionOffsetArrays)
{ int32 retVal;  
  switch( cmd )
  {
    case getRootInstance_InspcTargetProxyTelg: {
      retVal = (int32)mainData;  //Address of the root instance.
      DEBUGOUT2_OSALUserDEBUG("getRootInstance %8.8X\n", retVal);
    } break;       
    case getRootType_InspcTargetProxyTelg: {
      retVal = reflectionOffset_MainData[0];
      DEBUGOUT2_OSALUserDEBUG("getRootType %8.8X\n", retVal);
    } break;
    case getType_InspcTargetProxyTelg: {
      retVal = 0;
      DEBUGOUT2_OSALUserDEBUG("getType %8.8X\n", retVal);
    } break;
    case getOffsetLength_InspcTargetProxyTelg: {
      int ixClass = (inputVal >>16) & 0xffff;
      int ixField = inputVal & 0xffff;
      int32 const* offsetArray = reflectionOffsetArrays[ixClass];
      retVal = offsetArray[ixField];
      DEBUGOUT2_OSALUserDEBUG("getOffsetLength %8.8X\n", retVal);
    } break;
    case getRealLengthStaticArray_InspcTargetProxyTelg: {
      void** adr = (void**)address;  //an array of pointers.
      int length = inputVal;
      while(length > 0 &&  ((void**)(adr))[length-1] == null)  //dereferenced at the given position with index.
      { length -=1;
      }
      retVal = length;
      DEBUGOUT2_OSALUserDEBUG("getRealLengthStaticArray %8.8X\n", retVal);
    }break;
    case getInt16_InspcTargetProxyTelg:
    {
      retVal = (*(int16*)(address)) & 0xFFFF;
      DEBUGOUT2_OSALUserDEBUG("getInt16 %8.8X\n", retVal);
      
    } break;
    case getInt32_InspcTargetProxyTelg:
    {
      retVal = *(int32*)address;
      DEBUGOUT2_OSALUserDEBUG("getInt32 %8.8X\n", retVal);
      
    } break;
    case getInt64_InspcTargetProxyTelg: {
      retVal = *(int32*)address;
      DEBUGOUT2_OSALUserDEBUG("getInt64 %8.8X\n", retVal);
    } break;
    case getFloat_InspcTargetProxyTelg:
    {
      retVal = *(int32*)address;  //return float as int-image. It is standard-IEEE
      DEBUGOUT2_OSALUserDEBUG("getFloat %8.8X\n", retVal);
    } break;
    case getDouble_InspcTargetProxyTelg: {
      *(float*)&retVal = (float)(*(double*)address);
      DEBUGOUT2_OSALUserDEBUG("getDouble %8.8X\n", retVal);
    } break;
    case getRef_InspcTargetProxyTelg: {
      retVal = *(int*)address;  //return float as int-image. It is standard-IEEE
      DEBUGOUT2_OSALUserDEBUG("getAddr %8.8X\n", retVal);
    } break;
    case setByte_InspcTargetProxyTelg: {
      retVal = *(int8*)address;  //return float as int-image. It is standard-IEEE
      DEBUGOUT2_OSALUserDEBUG("setByte %8.8X\n", retVal);
    } break;
    case setInt16_InspcTargetProxyTelg: {
      *((int16*)address) = (int16)(inputVal & 0xFFFF); 
      retVal = (*(int16*)address) & 0xFFFF;
      DEBUGOUT2_OSALUserDEBUG("setInt16 %8.8X\n", retVal);
    } break;
    case setInt32_InspcTargetProxyTelg: {
      *((int32*)address) = inputVal; 
      retVal = *(int32*)address;
      DEBUGOUT2_OSALUserDEBUG("setInt32 %8.8X\n", retVal);
    } break;
    case setInt64_InspcTargetProxyTelg: {
      *((int64*)address) = inputVal; 
      retVal = (int32)(*(int64*)address);    
      DEBUGOUT2_OSALUserDEBUG("setInt64 %8.8X\n", retVal);
    } break;
    case setFloat_InspcTargetProxyTelg:
    {
      //*((float*)address) = *(float*)&inputVal;    
      *((int32*)address) = inputVal;   //Set the image, it is a float.    
      retVal = *(int32*)address;  
      DEBUGOUT2_OSALUserDEBUG("setFloat %8.8X\n", retVal);
    } break;
    case setDouble_InspcTargetProxyTelg: {
      *((double*)address) = *(float*)&inputVal;  //The input value is gotten as float, only 32 bit.      
      *(float*)&retVal = (float)(*((double*)address)); 
      DEBUGOUT2_OSALUserDEBUG("setDouble %8.8X\n", retVal);
    } break;
    case setRef_InspcTargetProxyTelg: {
      *((void**)address) = *(void**)&inputVal;      
      retVal = (int32)*((void**)address);
      DEBUGOUT2_OSALUserDEBUG("setAddr %8.8X\n", retVal);
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
      DEBUGOUT2_OSALUserDEBUG("getBitField %8.8X\n", retVal);
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
        DEBUGOUT2_OSALUserDEBUG("setBitField %8.8X\n", retVal);
      }
    } break; 
    default: 
      retVal = -1;
  }//switch    
  return retVal;
}



