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
 * The implementation of this methods may be implemented specially for embedded hardware,
 * which regards memory areas and access rights.
 * All accesses to memory locations with maybe unknown addresses, especially from symbolic accesses via reflection,
 * should be executed using this methods. It may be possible, that a adress in a reference
 * in the users software is faulty. Than a fault access will be executed. That situation should be catched here.
 * This methods may support an access to external memory locations too, at example a signal processor in a host environment.
 * It depends from the implementation there.
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 *
 * @version 0.92
 * @content Interface for Reflection memory access
 * This source may adapted for some embedded hardware conditions.
 *
 * @author Hartmut Schorrig www.vishia.org
 * list of changes:
 * 2016-03-13 Hartmut chg: bugfix access to bitfields
 * 2010-07-13 Hartmut new: MemAccessDebugJc, for debugging the path to an external CPU
 * 2010-01-16 Hartmut created, expandation of memory access for Reflection
 *
 ****************************************************************************/
#include <Jc/ReflMemAccessJc.h>
#include <emC/SimpleC.h>
#include <string.h>
#include <Jc/ObjectJc.h>
#include <os_AtomicAccess.h>
#include <emC/Exception.h>


MemSegmJc null_MemSegmJc = CONST_OS_PtrValue(null, MemUnit, 0);

MemAccessArrayDebugJc memAccessDebugJc = {0};




int32 getInfoDebug_RemoteCpuJc(Cmd_RemoteCpuJc_e cmd, int device, struct RemoteAddressJc* address, int32 input)
{
  int32 value;
  addRequest_MemAccessArrayDebugJc(&memAccessDebugJc, cmd, address, input);
	value = getInfo_RemoteCpuJc(cmd, device, address, input);
	setOutput_MemAccessArrayDebugJc(&memAccessDebugJc, value);
	return value;
}




/**Access to a external memory: */

int setValue_MemAccessJc(MemSegmJc addr, void const* pValue, int nrofBytes)
{
  int32 value;
  int memSegment = segment_MemSegmJc(addr);
  void* dst = ADDR_MemSegmJc(addr, void);
  if(dst !=null){
    if(memSegment == 0){
      value = 0;
      memcpy(dst, pValue, nrofBytes);
      memcpy(&value, pValue, nrofBytes); //re-read
    }
    else {
      Cmd_RemoteCpuJc_e cmd;
      switch(nrofBytes){ 
        case 1: cmd = setByte_RemoteCpuJc; break;
        case 2: cmd = setInt16_RemoteCpuJc; break;
        case 4: cmd = setInt32_RemoteCpuJc; break;
        default: cmd= setInt32_RemoteCpuJc;
      }
      //get 32 bit, but store only requested bytes.
		  { struct RemoteAddressJc* addr = (struct RemoteAddressJc*)dst;
			  value = getInfoDebug_RemoteCpuJc(cmd, memSegment, addr, *(int32*)pValue);
      }
	  }
  } else {
    value = -1;
  }
  return value;
}



float setFloat_MemAccessJc(MemSegmJc addr, float value)
{
  int memSegment = segment_MemSegmJc(addr);
  float* dstAddr = ADDR_MemSegmJc(addr, float);
  if(dstAddr !=null){
    
    if(memSegment == 0){
      *dstAddr = value;
      value = *dstAddr;  //re-read the value because it don't may be writeable.
    }
    else {
      int floatImg = getInfoDebug_RemoteCpuJc(setFloat_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)dstAddr, *(int*)&value);
      value = *(float*)&floatImg;
    }
  } else {
    value = 0.0f;
  }
  return value;
}


double setDouble_MemAccessJc(MemSegmJc addr, double value)
{
  int memSegment = segment_MemSegmJc(addr);
  double* dstAddr = ADDR_MemSegmJc(addr, double);
  if(dstAddr !=null){
    
    if(memSegment == 0){
      *dstAddr = value;
    }
    else {
      //DSP: double is float!
      float valueDsp = (float)value;
      int floatImg = getInfoDebug_RemoteCpuJc(setFloat_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)dstAddr, *(int*)&valueDsp);
      value = *(float*)&floatImg;
    }
  } else {
    value = 0.0f;
  }
  return value;
}



int32 getInt32_MemAccessJc(MemSegmJc addr)
{
  int memSegment = segment_MemSegmJc(addr);
  int32* src = ADDR_MemSegmJc(addr, int32);
  if(memSegment == 0){
    if(src !=null) return *src;
    else return -1;
  }
  else {
    int32 value = getInfoDebug_RemoteCpuJc(getInt32_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)src, 0);
    return value;
  }
}

int16 getInt16_MemAccessJc(MemSegmJc addr)
{
  int memSegment = segment_MemSegmJc(addr);
  int16* src = ADDR_MemSegmJc(addr, int16);
  if(memSegment == 0){
    if(src !=null) return *src;
    else return -1;
  }
  else {
    int16 value = (int16)getInfoDebug_RemoteCpuJc(getInt16_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)src, 0);
    return value;
  }
}

int8 getByte_MemAccessJc(MemSegmJc addr)
{
  int memSegment = segment_MemSegmJc(addr);
  int8* src = ADDR_MemSegmJc(addr, int8);
  if(memSegment == 0){
    if(src !=null) return *src;
    else return -1;
  }
  else {
    int8 value = (int8)getInfoDebug_RemoteCpuJc(getByte_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)src, 0);
    return value;
  }
}

int32 getValue32Ix_MemAccessJc(MemSegmJc addr, int ix)
{
  int memSegment = segment_MemSegmJc(addr);
  int32* src = ADDR_MemSegmJc(addr, int32);
  if(memSegment == 0){
    return src !=null ? src[ix] :-1;
  }
  else {
    int32 value = getInfoDebug_RemoteCpuJc(getInt32_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)src, ix);
    return value;
  }

}


int16 getBitfield_MemAccessJc(MemSegmJc addr, int posBit, int nrofBit)
{
  int memSegment = segment_MemSegmJc(addr);

	intPTR addr1 = (intPTR)ADDR_MemSegmJc(addr, void);    //NOTE: the addr may be in a remote CPU
	int32 val = 0;
  STACKTRC_ENTRY("getBitfield_MemAccessJc");

  if(memSegment == 0){
    int32 posBitUsed = -1;
		//adjust the address of bits depending of the bit position.
    //posBit is any position of the bit based on addr. It can be >32, >64 etc. because bitfields can be larger.
		//nrofBit should be <=32.
    //check whether all bits are located in the same int16, same int32 or in different int16 locations.
    if(BYTE_IN_MemUnit <=2 && (posBit & 0xfff0) == ((posBit + nrofBit -1) & 0xfff0)) {
			//all bits are arranged in the same int16:
			int offset = (posBit >>3) & 0xfffe;  //offset for byte address count, 2.byte-aligned
			offset /= BYTE_IN_MemUnit;   //If the address counts 16 bit, correct the offset.
			addr1 += offset;  //increment the address adequat posBit. Regard 1 address step are 8 bits.
			posBitUsed = posBit & 0xf;  //
			val = *(int16*)(addr1);
		  //shift the bit in position:
      val >>= posBitUsed;
		} else if(BYTE_IN_MemUnit <=4 && (posBit & 0xffe0) == ((posBit + nrofBit -1) & 0xffe0)){ 
			int offset = (posBit >>3) & 0xfffc;  //offset for byte address count, 4-byte-aligned.
			offset /= BYTE_IN_MemUnit;   //If the address counts 16 or 32 bit, correct the offset.
			addr1 += offset;  //32-bit-step
			posBitUsed = posBit & 0x1f;  //
      val = *(int32*)(addr1);
		  //shift the bit in position:
      val >>= posBitUsed;
		} else {
      //The bits are dispersed over 2 int32 parts. That may not possible for 32 bit processors, depending on the compiler. 
      //It is a mistake of reflection generating. For 64 bit Processors it is possible if the bitfield uses 64 bit.
      //If the compiler dispereses bit fields over 2 int words, the algorithm is correct for 32 bit processors.
      //Read 2 times 32 bit to support all bit field positions. 
      int offset = (posBit >>3) & 0xfff8;  //offset for byte address count, 4-byte-aligned.
			offset /= BYTE_IN_MemUnit;   //If the address counts 16 or 32 bit, correct the offset.
			addr1 += offset;  //32-bit-step
			posBitUsed = posBit & 0x3f;  //
      val = *(int32*)(addr1);
      int64 val2 = *(int32*)(addr1 + (4 / BYTE_IN_MemUnit));
      val2 = val2<<32 | val;
      val = (int32)(val2 >>= posBitUsed);
    }
		val &= (1<<nrofBit)-1;  //mask the bits, forex: nrofBit = 1, mask = 1, nrofBit = 2, mask = 4-1 = 0x03
	} else { //memSegment !=0
		//NOTE: don't correct the addr because it is unknown whether the 2CPU has byte or int32-addressing!
    //NOTE: the maximal length of an bitfield is limited to 16.
		//NOTE don't use a bitfield to assemble this informations, because the assignment of the bits is platform-depending.
    int32 info = (posBit  << bitPosBitsInBitfieldAccess_RemoteCpuJc ) & mPosBitsInBitfieldAccess_RemoteCpuJc
			         | (nrofBit << bitNrofBitsInBitfieldAccess_RemoteCpuJc) & mNrofBitsInBitfieldAccess_RemoteCpuJc
		           ;
    val = getInfoDebug_RemoteCpuJc(getBitfield_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)addr1, info);
  }
  STACKTRC_LEAVE; return (int16)val;  //The bits of the bitfield are arranged and mask in the bits 15..0
}





//TODO: an atomic access is necessary, to prevent bit changes if the read-set-write-process is interrupted (make it thread-safe).
int setBitfield_MemAccessJc(MemSegmJc addr, int setVal, int posBit, int nrofBit )
{
  int memSegment = segment_MemSegmJc(addr);
	OS_intPTR addr1 = (OS_intPTR)ADDR_MemSegmJc(addr, void);    //NOTE: the addr may be in a remote CPU
	int32 val1;
  
  if(memSegment == 0){
    int32 posBitUsed = -1;
		//adjust the address of bits depending of the bit position.
    //posBit is any position of the bit based on addr. It can be >32, >64 etc. because bitfields can be larger.
		//nrofBit should be <=32.
    //check whether all bits are located in the same int16, same int32 or in different int16 locations.
    if(false && BYTE_IN_MemUnit <=2 && (posBit & 0xfff0) == ((posBit + nrofBit -1) & 0xfff0)) {
			//NOTE: there is not a compareAndSwap for 16 bit!
      //all bits are arranged in the same int16:
			int offset = (posBit >>3) & 0xfffe;  //offset for byte address count, 2.byte-aligned
			offset /= BYTE_IN_MemUnit;   //If the address counts 16 bit, correct the offset.
			addr1 += offset;  //increment the address adequat posBit. Regard 1 address step are 8 bits.
			posBitUsed = posBit & 0xf;  //

			int mask = ((1<<nrofBit)-1) << (posBitUsed);
      int orVal = (setVal << (posBitUsed)) & mask;
			val1 = *(int16*)(addr1);
			val1 &= ~mask;  //set this bits to 0
			val1 |= orVal;
			*(int16*)(addr1) = (int16)val1;
			val1 = *(int16*)(addr1);
		  //shift the bit in position:
      val1 >>= posBitUsed;
  		val1 &= (1<<nrofBit)-1;  //mask the bits, forex: nrofBit = 1, mask = 1, nrofBit = 2, mask = 4-1 = 0x03
		} else if(BYTE_IN_MemUnit <=4 && (posBit & 0xffe0) == ((posBit + nrofBit -1) & 0xffe0)){ 
			int offset = (posBit >>3) & 0xfffc;  //offset for byte address count, 4-byte-aligned.
			offset /= BYTE_IN_MemUnit;   //If the address counts 16 or 32 bit, correct the offset.
			addr1 += offset;  //32-bit-step
			posBitUsed = posBit & 0x1f;  //

      int32 mask = ((1<<nrofBit)-1) << (posBitUsed);
      int32 orVal = (setVal << (posBitUsed)) & mask;
			int32* addr2 = (int32*) addr1;
      int32 val0;
      int ctCatastrophic = 999;  //terminate a while-loop
      { val0 = *addr2;
			  val1 = val0 & ~mask;  //set this bits to 0
			  val1 |= orVal;
      } while(--ctCatastrophic >=0 && !compareAndSet_AtomicInteger(addr2, val0, val1));  //repeat if memory was changed. 
			if(ctCatastrophic < 0) {
        val1 = 0xbad;
      } else {
        val1 = *(int32*)(addr1);  //read the value after operation.
      }
		  //shift the bit in position:
      val1 >>= posBitUsed;
  		val1 &= (1<<nrofBit)-1;  //mask the bits, forex: nrofBit = 1, mask = 1, nrofBit = 2, mask = 4-1 = 0x03
		} else {
      //The bits are dispersed over 2 int32 parts. That may not possible for 32 bit processors, depending on the compiler. 
      //It is a mistake of reflection generating. For 64 bit Processors it is possible if the bitfield uses 64 bit.
      //If the compiler dispereses bit fields over 2 int words, the algorithm is correct for 32 bit processors.
      //Read 2 times 32 bit to support all bit field positions. 
      //TODO don't set yet. only read. Not supported yet.
      int offset = (posBit >>3) & 0xfff8;  //offset for byte address count, 4-byte-aligned.
			offset /= BYTE_IN_MemUnit;   //If the address counts 16 or 32 bit, correct the offset.
			addr1 += offset;  //32-bit-step
			posBitUsed = posBit & 0x3f;  //
      val1 = *(int32*)(addr1);
      int64 val2 = *(int32*)(addr1 + (4 / BYTE_IN_MemUnit));
      val2 = val2<<32 | val1;
      val1 = 0xbad; //(int32)(val2 >>= posBitUsed);
    }
	}
  else { //memSegment !=0
		//NOTE: the maximal length of an bitfield is limited to 16.
		//NOTE don't use a bitfield to assemble this informations, because the assignment of the bits is platform-depending.
    int32 info = (posBit  << bitPosBitsInBitfieldAccess_RemoteCpuJc ) & mPosBitsInBitfieldAccess_RemoteCpuJc
			         | (nrofBit << bitNrofBitsInBitfieldAccess_RemoteCpuJc) & mNrofBitsInBitfieldAccess_RemoteCpuJc
               | (setVal << kBitValueInBitfieldAccess_RemoteCpuJc) & mValueInBitfieldAccess_RemoteCpuJc
							 ;
    val1 = getInfoDebug_RemoteCpuJc(setBitfield_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)addr1, info);
  }
  return (int)val1;
}








float getFloat_MemAccessJc(MemSegmJc addr)
{
  int memSegment = segment_MemSegmJc(addr);
  float* src = ADDR_MemSegmJc(addr, float);
  if(memSegment == 0){
    if(src !=null) return *src;
    else return 0.0f;
  }
  else {
    int32 floatImg = getInfoDebug_RemoteCpuJc(getFloat_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)src, 0);
    float value = *(float*)&floatImg;
    return value;
  }
}

double getDouble_MemAccessJc(MemSegmJc addr)
{
  int memSegment = segment_MemSegmJc(addr);
  double* src = ADDR_MemSegmJc(addr, double);
  if(memSegment == 0){
    return *src;
  }
  else {
    //The dsp uses double as float.
    int32 floatImg = getInfoDebug_RemoteCpuJc(getFloat_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)src, 0);
    float value = *(float*)&floatImg;
    return value;  //cast to double
  }

}

int64 getInt64_MemAccessJc(MemSegmJc addr)
{
  int memSegment = segment_MemSegmJc(addr);
  int64* src = ADDR_MemSegmJc(addr, int64);
  if(memSegment == 0){
    return *src;
  }
  else return 0;

}




MemSegmJc getRef_MemAccessJc(MemSegmJc addr)
{
  int memSegment = segment_MemSegmJc(addr);
  void** src = ADDR_MemSegmJc(addr, void*);
  if(memSegment == 0){
    void* addr = src == null ? null : *src;
    MemSegmJc ret = CONST_MemSegmJc(addr, memSegment);
    return ret;
  }
  else {
    int addr = getInfoDebug_RemoteCpuJc(getRef_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)src, 0);
    MemSegmJc ret = CONST_MemSegmJc(addr, memSegment);
    return ret;
  }
}

MemSegmJc getEnhancedRef_MemAccessJc(MemSegmJc addr)
{
  #ifdef NOENHANCEDREFJc 
    return getRef_MemAccessJc(addr);
  #else      
    int memSegment = segment_MemSegmJc(addr);
    void** src = ADDR_MemSegmJc(addr, void*);
    if(memSegment == 0){
      void* addr = *(void**)( ((MemUnit*)src) + 4); //TODO OFFSETinTYPE_SimpleC(ObjectJcREF, ref) ); 
      MemSegmJc ret = CONST_MemSegmJc(addr, memSegment);
      return ret;
    }
    else {
      int addr = 0; //TODO getInfoDebug_RemoteCpuJc(getEnhancedRef_RemoteCpuJc, memSegment, (struct RemoteAddressJc*)src, 0);
      MemSegmJc ret = CONST_MemSegmJc(addr, memSegment);
      return ret;
    }
  #endif
}


/**gets the 
 * That is the implementation on DSP-side!
 */
int getRealLengthStaticArray_MemAccessJc(MemSegmJc instance, int length)
{ int memSegment = segment_MemSegmJc(instance);
  if(memSegment == 0){
    /**The own memory range. */
    void** adr = ADDR_MemSegmJc(instance, void*);  //an array of pointers.
    while(length > 0 &&  ((void**)(adr))[length-1] == null)  //dereferenced at the given position with index.
    { length -=1;
    }
  }
  else {
    length = getInfoDebug_RemoteCpuJc(getRealLengthStaticArray_RemoteCpuJc, memSegment, ADDR_MemSegmJc(instance, struct RemoteAddressJc), length);
  }
  return length;

}



void xxxwriteRemoteAccessDebug_MemAccessJc(int32 cmd, void* address, int32 input, int32 output){
  if(cmd == getRootInstance_RemoteCpuJc){
    memAccessDebugJc.ix = 0;
  } else {
    memAccessDebugJc.ix +=1;
    if(memAccessDebugJc.ix >= ARRAYLEN(memAccessDebugJc.item)){
      memAccessDebugJc.ix = ARRAYLEN(memAccessDebugJc.item)-1;  //limit it, write in last cell.
    }
  }
  { MemAccessDebugJc* item = &memAccessDebugJc.item[memAccessDebugJc.ix];
    item->address = (int32)address;
    item->cmd = cmd;
    item->input = input;
    item->output = output;
  }
}





void addRequest_MemAccessArrayDebugJc(MemAccessArrayDebugJc* ythis, int32 cmd, struct RemoteAddressJc* addr, int32 input)
{
	int ix = ythis->ix;
	MemAccessDebugJc* item;
	if(ix < 0 || ix >= ARRAYLEN(ythis->item)){
		ix = ARRAYLEN(ythis->item) -1;   //write at last in the last cell in any case, only if to much accesses. 
	}
  if(cmd == getRootInstance_RemoteCpuJc){
		ix = 0;   //start with 0 with the whole newly access.
		ythis->ix = ix;
	}
	item = &ythis->item[ix];
	item->cmd =     cmd;
	item->address = (int32)addr;
	item->input =   input;
	item->output =  0xbad00bad;
}




void setOutput_MemAccessArrayDebugJc(MemAccessArrayDebugJc* ythis, int32 output)
{
	int ix = ythis->ix;
	MemAccessDebugJc* item;
	if(ix < 0 || ix >= ARRAYLEN(ythis->item)){
		ix = ARRAYLEN(ythis->item) -1;   //write at last in the last cell in any case, only if to much accesses. 
	}
	item = &ythis->item[ix];
	item->output =  output;
  ix +=1;  //do not wrap arround, instead start with 0 on root access.
	ythis->ix = ix;
}




#include "genRefl/Jc/ReflMemAccessJc.crefl"
