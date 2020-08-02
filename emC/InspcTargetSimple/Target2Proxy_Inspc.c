/**This file contains the adaption of the Inspc-Interface via Accsess with the simple interface
 * made by Hartmut Schorrig, www vishia.org
 * date first: 2010
 * date last change: 2016-10-29
 */
#include "Target2Proxy_Inspc.h"
#include <emC/OSAL/os_AtomicAccess.h>
#include <applstdef_emC.h>

#ifndef DEF_REFLECTION_NO
  //#include "Inspc/Target2Proxy_Inspc.crefl"
  #include "emC/InspcTargetSimple/genRefl/IfcTargetProxy_Inspc.crefl" //The telg struct has no own implementation
#else
  
#endif

//Switch on only in an debug situation, then compile newly
#undef PRINTF2
#define PRINTF2(TEXT, VAL) //empty.

#ifdef DEF_TARGETSIMPLE

int32 processInspcCmdOnTarget_Inspc(Cmd_InspcTargetProxy_e const cmd, int32 address, int32 inputVal, void const* mainData
, int32 const* reflectionOffset_MainData, ClassJc const* const* reflectionOffsetArrays)
{ int32 retVal;  
  STACKTRC_ENTRY("processInspcCmdOnTarget_Inspc");
  TRY {
  switch( cmd )
  {
    case getRootInstance_InspcTargetProxy: {
      retVal = (int32)mainData;  //Address of the root instance.
      PRINTF2("getRootInstance %8.8X\n", retVal);
    } break;       
    case getRootType_InspcTargetProxy: {
      retVal = reflectionOffset_MainData[0];
      PRINTF2("getRootType %8.8X\n", retVal);
    } break;
    case getType_InspcTargetProxy: {
      retVal = getTypeId_ObjectJc((ObjectJc*)address);
      PRINTF2("getType %8.8X\n", retVal);
    } break;
    case getOffsetLength_InspcTargetProxy: {
      int ixClass = (inputVal >>16) & 0xffff;
      int ixField = inputVal & 0xffff;
      int32 const* offsetArray = reflectionOffsetArrays[ixClass]->reflOffs;
      retVal = offsetArray[ixField];
      PRINTF2("getOffsetLength %8.8X\n", retVal);
    } break;
    case getRealLengthStaticArray_InspcTargetProxy: {
      void** adr = (void**)address;  //an array of pointers.
      int length = inputVal;
      while(length > 0 &&  ((void**)(adr))[length-1] == null)  //dereferenced at the given position with index.
      { length -=1;
      }
      retVal = length;
      PRINTF2("getRealLengthStaticArray %8.8X\n", retVal);
    }break;
    case getByte_InspcTargetProxy:
    {
      retVal = (*(int8*)(address)) & 0xFF;
      PRINTF2("getInt16 %8.8X\n", retVal);
    } break;
    case getInt16_InspcTargetProxy:
    {
      retVal = (*(int16*)(address)) & 0xFFFF;
      PRINTF2("getInt16 %8.8X\n", retVal);

    } break;
    case getInt32_InspcTargetProxy:
    {
      retVal = *(int32*)address;
      PRINTF2("getInt32 %8.8X\n", retVal);
      
    } break;
    case getInt64_InspcTargetProxy: {
      retVal = *(int32*)address;
      PRINTF2("getInt64 %8.8X\n", retVal);
    } break;
    case getFloat_InspcTargetProxy:
    {
      retVal = *(int32*)address;  //return float as int-image. It is standard-IEEE
      PRINTF2("getFloat %8.8X\n", retVal);
    } break;
    case getDouble_InspcTargetProxy: {
      *(float*)&retVal = (float)(*(double*)address);
      PRINTF2("getDouble %8.8X\n", retVal);
    } break;
    case getRef_InspcTargetProxy: {
      retVal = *(int*)address;  //return float as int-image. It is standard-IEEE
      PRINTF2("getAddr %8.8X\n", retVal);
    } break;
    case setByte_InspcTargetProxy: {
      *((int8*)address) = (int8)(inputVal & 0xFF); 
      retVal = *(int8*)address;  //return float as int-image. It is standard-IEEE
      PRINTF2("setByte %8.8X\n", retVal);
    } break;
    case setInt16_InspcTargetProxy: {
      *((int16*)address) = (int16)(inputVal & 0xFFFF); 
      retVal = (*(int16*)address) & 0xFFFF;
      PRINTF2("setInt16 %8.8X\n", retVal);
    } break;
    case setInt32_InspcTargetProxy: {
      *((int32*)address) = inputVal; 
      retVal = *(int32*)address;
      PRINTF2("setInt32 %8.8X\n", retVal);
    } break;
    case setInt64_InspcTargetProxy: {
      *((int64*)address) = inputVal; 
      retVal = (int32)(*(int64*)address);    
      PRINTF2("setInt64 %8.8X\n", retVal);
    } break;
    case setFloat_InspcTargetProxy:
    {
      //*((float*)address) = *(float*)&inputVal;    
      *((int32*)address) = inputVal;   //Set the image, it is a float.    
      retVal = *(int32*)address;  
      PRINTF2("setFloat %8.8X\n", retVal);
    } break;
    case setDouble_InspcTargetProxy: {
      *((double*)address) = *(float*)&inputVal;  //The input value is gotten as float, only 32 bit.      
      *(float*)&retVal = (float)(*((double*)address)); 
      PRINTF2("setDouble %8.8X\n", retVal);
    } break;
    case setRef_InspcTargetProxy: {
      *((void**)address) = *(void**)&inputVal;      
      retVal = (int32)*((void**)address);
      PRINTF2("setAddr %8.8X\n", retVal);
    } break; 
    
    case getBitfield_InspcTargetProxy:
    {
      int posBits = (inputVal & mPosBitsInBitfieldAccess_InspcTargetProxy) >> bitPosBitsInBitfieldAccess_InspcTargetProxy ;
      int posByte = posBits >> 3;
      int nrofBits = (inputVal & mNrofBitsInBitfieldAccess_InspcTargetProxy) >> bitNrofBitsInBitfieldAccess_InspcTargetProxy ;
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
    case setBitfield_InspcTargetProxy:
    {
            //regard the possibilities of the target processor in bit/byte-access!
      //regard thread safety!
      //This example works on a PC-hardware without bit-access instructions, but with full byte-access!
      //adjust the memory address, because the posBits may be in range 0..4095 (512 Bytes):
      int posBits = (inputVal & mPosBitsInBitfieldAccess_InspcTargetProxy) >> bitPosBitsInBitfieldAccess_InspcTargetProxy ;
      int nrofBits = (inputVal & mNrofBitsInBitfieldAccess_InspcTargetProxy) >> bitNrofBitsInBitfieldAccess_InspcTargetProxy ;
      int setValue = (inputVal & mValueInBitfieldAccess_InspcTargetProxy) >> kBitValueInBitfieldAccess_InspcTargetProxy ;
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
  }_TRY
  CATCH(Exception, exc){
    retVal = 0;  //usual an memory exception
  } END_TRY   
  STACKTRC_RETURN retVal;
}

void step_Target2Proxy_Inspc(Target2Proxy_Inspc* thiz
  , void const* rootData
  , int32 const* reflectionOffset_RootData, ClassJc const* const* reflectionOffsetArrays
) {
  int seqnr = getSeqnr_TelgProxy2Target_Inspc(thiz->proxy2target);
  if( seqnr != thiz->seqnrLast ) {  //it is changed, new cmd expected
    thiz->seqnrLast = seqnr;        //only execute while one time, think on exception handling.
    STACKTRC_ENTRY("step_Target2Proxy_Inspc");
    int32 retValue = -1;
    Cmd_InspcTargetProxy_e cmd = getCmd_TelgProxy2Target_Inspc(thiz->proxy2target);
    TRY{
      int32 address = getInt32BigEndian(&thiz->proxy2target->address);
      int32 value = getInt32BigEndian(&thiz->proxy2target->value);
      retValue = processInspcCmdOnTarget_Inspc(cmd, address, value, rootData, reflectionOffset_RootData, reflectionOffsetArrays);
    }_TRY
    CATCH(Exception, exc) {
      retValue = -1;
    }
    END_TRY
    setInt32BigEndian(&thiz->target2proxy->retValue, retValue);
    setCmdSeqnr_TelgTarget2Proxy_Inspc(thiz->target2proxy, cmd, seqnr);  //return the same cmd and seqnr as received
    STACKTRC_LEAVE;
  }
  else {
    setLifeCt_TelgTarget2Proxy_Inspc(thiz->target2proxy, ++thiz->lifeCt);
  }

}
#endif //DEF_TARGETSIMPLE


