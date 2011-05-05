/**This file emulates a second CPU. The access routines to its data are contained here too. 
*/

#include <Jc/ReflMemAccessJc.h>

#include <fw_Platform_conventions.h>

#include "SecondCpuData.h"

#include <Fwc/fw_simpleC.h>
#include <os_AtomicAccess.h>
#include <string.h>
#include <stdlib.h>
#include <Fwc/fw_Exception.h>


int testArray_g[5];


ExampleData data1;

ExampleIntern data2;

ExampleUnion exampleUnion;


static MainSecondCpu dspMainData =
{ CONST_ObjectJc(0, &dspMainData, null)
, &data1, &data2
, null
, &exampleUnion
, 3.1456F, 3.169876F
  
};



SimpleDataDsp simpleDataArray[5];


//ExampleData data1;
//ExampleIntern data2;
//ExampleUnion testUnion;






void initDsp()
{
  ctor_MainSecondCpu(&dspMainData);
}


void ctor_MainSecondCpu(MainSecondCpu* ythis)
{ int ii,jj;
  STACKTRC_ENTRY("ctor_MainSecondCpu");
  for(jj = 0; jj < ARRAYLEN(ythis->data1->iData); ++jj){
    
    for(ii = 0; ii < ARRAYLEN(ythis->data1->iData[jj].intArray); ++ii){
      ythis->data1->iData[jj].intArray[ii] = 100*jj +ii;
  } }
  for(jj = 0; jj < ARRAYLEN(ythis->data1->iDataRef); ++jj){
    MemC mem = alloc_MemC(sizeof(ExampleIntern));
    ExampleIntern* obj = PTR_MemC(mem, ExampleIntern); 
    obj->i1 = jj + 200;
    ythis->data1->iDataRef[jj] = obj;//(ExampleIntern*)malloc(sizeof(ExampleIntern));
    for(ii = 0; ii < ARRAYLEN(obj->intArray); ++ii){
      obj->intArray[ii] = 1000 + 100*jj +ii;
  } }
	data2.pArray = &data2.intArray[0];
	data2.pArray2 = &data2.intArray[0];
  data2.pDataArray = &data2.dataArray[0];
  
  data1.p_value2 = &data1.value2;
  data1.p_fValue = &data1.fValue;

  for(jj=0; jj<ARRAYLEN(simpleDataArray); ++jj){
    memset(&simpleDataArray[jj], 0, sizeof(simpleDataArray[0]));
    simpleDataArray[jj].b = 4001 + jj;
  }

  dspMainData.simpleDataArray = simpleDataArray;  //refer in the main data.

  data1.testArray = testArray_g;

	testArray_g[0] = 25;

  //exampleUnion.test->a = 23;

	//ii = sizeof(*exampleUnion.test);
	//ii = sizeof(ExampleUnion.Test_t);
  STACKTRC_LEAVE;
}


/**Generated from Header2Reflection, contains offsets and indices of data. */
extern int32 reflectionOffset_MainSecondCpu[];




/**Gets any info which has max. 4 byte return value. */
int32 getInfo_RemoteCpuJc(Cmd_RemoteCpuJc_e cmd, int device, struct RemoteAddressJc* address, int32 input)
{ int32 ret = -1;
  switch(cmd){
    case getRootInstance_RemoteCpuJc: {
      ret = (int32)&dspMainData;
    } break;
    case getRootType_RemoteCpuJc: {
      ret = (int32)reflectionOffset_MainSecondCpu[0];
    } break;
    case getType_RemoteCpuJc: {
      ret = 0;
    } break;
    case getOffsetLength_RemoteCpuJc: {
      int ixClass = (input >>16) & 0xffff;
      int ixField = input & 0xffff;
      extern int32* reflectionOffsetArrays[];
      int32* offsetArray = reflectionOffsetArrays[ixClass];
      ret = offsetArray[ixField];
    } break;

    case getRealLengthStaticArray_RemoteCpuJc: {
      void** adr = (void**)address;  //an array of pointers.
      int length = input;
      while(length > 0 &&  ((void**)(adr))[length-1] == null)  //dereferenced at the given position with index.
      { length -=1;
      }
      ret = length;
    }break;
    
    case getByte_RemoteCpuJc: {
      ret = *(int8*)address;  //return float as int-image. It is standard-IEEE
    } break;
    case getInt16_RemoteCpuJc: {
      ret = *(int16*)address;  //return float as int-image. It is standard-IEEE
    } break;
    case getInt32_RemoteCpuJc: {
      ret = *(int32*)address;  //return float as int-image. It is standard-IEEE
    } break;
    case getInt64_RemoteCpuJc: {
      ret = *(int32*)address;  //return float as int-image. It is standard-IEEE
    } break;
    case getFloat_RemoteCpuJc: {
      ret = *(int*)address;  //return float as int-image. It is standard-IEEE
    } break;
    case getDouble_RemoteCpuJc: {
      ret = *(int*)address;  //return float as int-image. It is standard-IEEE
    } break;
    case getRef_RemoteCpuJc: {
      ret = *(int*)address;  //return float as int-image. It is standard-IEEE
    } break;
    case setByte_RemoteCpuJc: {
    } break;
    case setInt16_RemoteCpuJc: {
    } break;
    case setInt32_RemoteCpuJc: {
      *((int32*)address) = input;      
      ret = *(int32*)(address);
    } break;
    case setInt64_RemoteCpuJc: {
      ret = -1;
      ASSERT(false);
      //*((int64*)address) = *(int64*)input;      
    } break;
    case setFloat_RemoteCpuJc: {
      *((float*)address) = *(float*)&input;      
      ret = *(int32*)(address);
    } break;
    case setDouble_RemoteCpuJc: {
      ret = -1;
      ASSERT(false);
      //*((double*)address) = *(double*)&input;      
    } break;
    case setRef_RemoteCpuJc: {
      *((void**)address) = *(void**)&input;      
      ret = *(int32*)(address);
    } break;
    case getBitfield_RemoteCpuJc: {
      //BitfieldInfo_RemoteCpuJc bitInfo;
			//bitInfo.allBits = input;
      //regard the possibilities of the target processor in bit/byte-access!
			//regard thread safety!
			//This example works on a PC-hardware without bit-access instructions, but with full byte-access!
			//adjust the memory address, because the posBits may be in range 0..4095 (512 Bytes):
			{ int posBits = (input & mPosBitsInBitfieldAccess_RemoteCpuJc) >> bitPosBitsInBitfieldAccess_RemoteCpuJc ;
				int posByte = posBits >> 3;
				int nrofBits = (input & mNrofBitsInBitfieldAccess_RemoteCpuJc) >> bitNrofBitsInBitfieldAccess_RemoteCpuJc ;
				int nrofByte, offsetByte;
				ASSERT(BYTE_IN_MemUnit == 1);
				if((posBits & 0xfff8) == ((posBits + nrofBits -1) & 0xfff8)){
					//bits in the same byte:
					nrofByte = 1;
					offsetByte = posBits >> 3;
					posBits -= 8 * offsetByte;
				} else if((posBits & 0xfff0) == ((posBits + nrofBits -1) & 0xfff0)){
					//bits overlap 1 byte, but in the same 16 bit-range
					nrofByte = 2;
					offsetByte = (posBits >> 3) & 0xfffe;
					posBits -= 8 * offsetByte;
				} else {
					nrofByte = 4;
					offsetByte = (posBits >> 3) & 0xfffc;
					posBits -= 8 * offsetByte;
				}
				{ MemUnit* addr1 = ((MemUnit*)address) + offsetByte;  //calculate the byte/word-address where the bits are found. 
					int32 mask = ((1<<nrofBits) -1) << posBits;
					int32 valueRaw;
					switch(nrofByte){
					case 1: valueRaw = *(int8*)addr1; break;
					case 2: valueRaw = *(int16*)addr1; break;
					case 4: valueRaw = *(int32*)addr1; break;
					default: valueRaw = 0; ASSERT(false);
					}//switch
					ret = (valueRaw & mask) >> posBits;
			}	}
	  } break;
    case setBitfield_RemoteCpuJc: {
      //regard the possibilities of the target processor in bit/byte-access!
			//regard thread safety!
			//This example works on a PC-hardware without bit-access instructions, but with full byte-access!
			//adjust the memory address, because the posBits may be in range 0..4095 (512 Bytes):
			{ int posBits = (input & mPosBitsInBitfieldAccess_RemoteCpuJc) >> bitPosBitsInBitfieldAccess_RemoteCpuJc ;
				int posByte = posBits >> 3;
				int nrofBits = (input & mNrofBitsInBitfieldAccess_RemoteCpuJc) >> bitNrofBitsInBitfieldAccess_RemoteCpuJc ;
				int value = (input & mValueInBitfieldAccess_RemoteCpuJc) >> kBitValueInBitfieldAccess_RemoteCpuJc ;
				int offsetByte;
				//NOTE: use 32 bit anytime, because compareAndSet_AtomicInteger is available yet only for 32 bit,
				//and the DSP-Implementation should use 32 bit,
				offsetByte = (posBits >> 3) & 0xfffc;
				posBits -= 8 * offsetByte;
				{ MemUnit* addr1 = ((MemUnit*)address) + (offsetByte / BYTE_IN_MemUnit);  //calculate the byte/word-address where the bits are found. 
					int32 mask = ((1<<nrofBits) -1) << posBits;
					int32 setValueBit = value; 
					int32 oldValue, value;
					int catastrophicCount = 1000;  //it should be success in 1 or a few accesses.
					do{
						oldValue = *(int32*)addr1;
						value = oldValue & ~mask;  //delete this bits.
						value |= (setValueBit << posBits) & mask;
					} while( !compareAndSet_AtomicInteger((volatile int32*)addr1, oldValue, value)
								 && --catastrophicCount >0);
					value = *(int32*)addr1;  //re-read from memory 
					ret = value >> posBits & (mask >> posBits);
			}	}
	  } break;
    default: ASSERT(false);
  }
  return ret;
}






