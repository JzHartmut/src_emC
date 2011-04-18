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
 * 2010-07-13 Hartmut new: MemAccessDebugJc, for debugging the path to an external CPU
 * 2010-01-16 Hartmut created, expandation of memory access for Reflection
 *
 ****************************************************************************/
#include <Jc/ReflMemAccessJc.h>
#include <Fwc/fw_SimpleC.h>
#include <string.h>
#include <Jc/ObjectJc.h>



MemSegmJc null_MemSegmJc = CONST_OS_PtrValue(0, null);

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
		//TODO use algorithm from setBitField_MemAccessJc to decide nrofBytesSrc
    int nrofBytesSrc;
	  //adjust the address of bits depending of the bit position.
		//if the bit position overlaps 1 Byte, int16 or int32 are necessary. TODO
	  if( (addr1 & 0xfffffffc) == addr1 && (posBit & 0xffe0) == ((posBit + nrofBit -1) & 0xffe0)){
		  //typically: All the bits are in the same 32-bit-range.
      addr1 += (posBit >>3) & 0xfffc;  //32-bit-step
      setADDR_MemSegmJc(addr, addr1);
      nrofBytesSrc = 4;
	  } else if( (intPTR)(addr1 & 0xfffffffe) == addr1 && (posBit & 0xfff0) == ((posBit + nrofBit -1) & 0xfff0)){
		  //typically: Address at 2-alignment and All the bits are in the same 16-bit-range.
      addr1 += (posBit >>3) & 0xfffe;  //32-bit-step
      setADDR_MemSegmJc(addr, addr1);
      nrofBytesSrc = 2;
	  } else {
      nrofBytesSrc = 1;
	  }
    switch(nrofBytesSrc){
		case 1: val = *(int8*)(addr1); break;
		case 2: val = *(int16*)(addr1); break;
		case 4: val = *(int32*)(addr1); break;
    default: THROW_s0(RuntimeException, "unexpected default in switch", nrofBytesSrc);
		}
		//shift the bit in position:
    val >>= posBit & 0xf;
		val &= (1<<nrofBit)-1;  //mask the bits, forex: nrofBit = 1, mask = 1, nrofBit = 2, mask = 4-1 = 0x03
	} else { //memSegment !=0
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
	int32 addr1 = (int32)ADDR_MemSegmJc(addr, void);    //NOTE: the addr may be in a remote CPU
	int32 val1;
  
  if(memSegment == 0){
    int32 posBitUsed = -1;

		int nrofBytesSrc;
		//adjust the address of bits depending of the bit position.
		if((posBit & 0xfff8) == ((posBit + nrofBit -1) & 0xfff8)){
			//all bits are arranged in the same byte, the processor supports byte addressing:
			addr1 += (posBit >>3);
			posBitUsed = posBit & 0x7;
			nrofBytesSrc = 1;
		} else if((posBit & 0xfff0) == ((posBit + nrofBit -1) & 0xfff0)){
			//all bits are arranged in the same byte, the processor supports byte addressing:
			addr1 += (posBit >>3);
			posBitUsed = posBit & 0xf;
			if((addr1 & 0x1) != 0){
				//even address, don't use 16-bit-access!
				//only if the user builds an unaligned structure. Then it is supported. No special case!
				nrofBytesSrc = 2;
			}
			nrofBytesSrc = 2;
		} else { 
		
			//if( (int32)(addr1 & 0xfffffffc) == addr1 && (posBit & 0xffe0) == ((posBit + nrofBit -1) & 0xffe0)){
			//typically: All the bits are in the same 32-bit-range.
			int offset = (posBit >>3) & 0xfffc;
			offset /= BYTE_IN_MemUnit;   //special for DSP! But use DSP-characteristics, TODO.
			addr1 += offset;  //32-bit-step
			nrofBytesSrc = 4;
		}
	  setADDR_MemSegmJc(addr, addr1);  //sets the address adjusted with bit position.
		switch(nrofBytesSrc){
		case 1: 
			val1 = *(int8*)(addr1);
			val1 &= ~((1<<nrofBit)-1);  //set this bits to 0
			val1 |= (setVal & ((1<<nrofBit)-1)) << (posBit & 0x7);
			*(int8*)(addr1) = (int8)val1;
			val1 = *(int8*)(addr1);
			break;
		case 2: 
			val1 = *(int16*)(addr1);
			val1 &= ~((1<<nrofBit)-1);  //set this bits to 0
			val1 |= (setVal & ((1<<nrofBit)-1)) << (posBit & 0xf);
			*(int16*)(addr1) = (int16)val1;
			val1 = *(int16*)(addr1);
			break;
		case 4: 
			val1 = *(int32*)(addr1);
			val1 &= ~((1<<nrofBit)-1);  //set this bits to 0
			val1 |= ((int32)(setVal & ((1<<nrofBit)-1))) << (posBit & 0x1f);
			*(int32*)(addr1) = val1;
			val1 = *(int32*)(addr1);
			break;
    default: val1 = 0xbad;  //TODO is it real?
		}//switch
		//set the given bits.
		//rewrite the bits. NOTE: use compareAndSetAtomicInteger!
		
		//shift the bit in position:
		val1 >>= posBit & 0xf;
		val1 &= (1<<nrofBit)-1;  //mask the bits, forex: nrofBit = 1, mask = 1, nrofBit = 2, mask = 4-1 = 0x03
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
    void* addr = *src;
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