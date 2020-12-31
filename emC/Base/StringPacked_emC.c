#include <emC/Base/StringPacked_emC.h>



int strncmpPacked_emC ( void const* const text1, char const* const text2, int const maxNrofChars) {
  MemUnit const* text1a = C_CAST(MemUnit const*,text1);
  char const* text2a = text2;
  int maxNrofChars1 = maxNrofChars;
  char c1, c2;
  while(--maxNrofChars1 >=0) {
    MemUnit d1 = *text1a++;
    c1 = (char)(d1 & 0xff);  //d1 may be a char on byte access platform because MemUnit is a char
    c2 = *text2a++;
    if(c1 != c2) { break; }
    #ifdef MemUnit_16bit
      if(--maxNrofChars1 <0) { break; }
      c1 = (char)((d1 >>8) & 0xff);
      if( (c2 = *text2a++) ==0) { break; }
      if(c1 != c2) { break; }
    #endif
    if(c2 ==0) { break; }              //only c2 is a reason for break, but if c1 ==0 it breaks because difference
  }
  //loop till end or till difference
  if(maxNrofChars1<0 || c1 == c2) return 0; //equal
  else if(c2 > c1) return maxNrofChars - maxNrofChars1;  //positive number, it is the position.
  else return maxNrofChars1 - maxNrofChars;  //negativ Number, abs is position of difference.
}


//#define BYTE_IN_MemUnit_Test 4

int bytecpyPacked_emC ( void* const dst, int const ixByteDst, void const* const src, int const ixByteSrc, int const nrofBytes2cpy) {
  int* dst0 = C_CAST(int*, dst);  //C_CAST: The dst is a memory address, the access is int-wise (full words).
  int const* src0 = C_CAST(int const*, src);  //C_CAST: Note: int is on PC 4 Byte, it is the memory access unit for embedded processors with >1 Byte per address step 
  int zBytes = nrofBytes2cpy;
  int nrofByte4MemAccess = sizeof(int) * BYTE_IN_MemUnit;  //int is the real memory access unit. Use it especially for test. 
  uint maskix = nrofByte4MemAccess -1;
  uint shix = nrofByte4MemAccess <=1 ? nrofByte4MemAccess : 2;  //0, 1 or 2
  uint ixmemSrcEnd = (ixByteSrc + nrofBytes2cpy) >> shix;  //following index in src after last access
  uint byteSrc = ixByteSrc & maskix;     //always 0 in byte adressing, optimized for byte processors.
  int bitSrc1 = byteSrc * 8;
  int bitSrc2 = (nrofByte4MemAccess - byteSrc) *8;
  uint zMemWords = nrofBytes2cpy >>shix;
  uint ixmemSrc = ixByteSrc >> shix;
  int byteDst = ixByteDst & maskix;     //always 0 in byte adressing, optimized for byte processors.
  int bitDst1 = byteDst * 8;
  int bitDst2 = (nrofByte4MemAccess - byteDst) *8;
  uint maskDst1 = (1<<bitDst1) -1;
  uint maskDst2 = ~maskDst1;
  int bitSrcDst1 = bitDst1 - bitSrc1;          //bit diff position to shift src to dst.
  int bitSrcDst0 = (nrofByte4MemAccess <<3) - bitSrcDst1; //bit diff position to shift lo part of src to dst.
  int bitDstSrc1 = -bitSrcDst1;
  int bitDstSrc2 = 32 - bitDstSrc1;
  uint maskSrcDst0 = (1<<bitSrcDst1)-1;
  uint maskSrcDst3 = ~((1<< (32 + bitSrcDst1)) -1);  //only for negative bitSrcDst1;
  uint ixmemDst = ixByteDst >> shix;
  
  uint valDst0 = dst0[ ixmemDst]; //<< bitDstSrc2; //start value for or
  uint valSrc1 = src0[ ixmemSrc]; //value from first word
  
  //src: 221100xx 66554433
  //dst: 1100xxxx 55443322
  //start problem: first time it may be possible that lesser bytes are copied, ixByteDst is odd.
  //prevent dst content.
  uint valDst;
    
  uint valSrc2;
  if(ixmemSrc < ixmemSrcEnd) { //zBytes >= nrofByte4MemAccess) { 
    valSrc2 = src0[ ++ixmemSrc]; 
  } else {
    valSrc2 = 0; //Hi part of first word unneccesary  
  }

  if(bitSrcDst1 >0) {
    valDst = ((valSrc1<< bitSrcDst1) & maskDst2) |  (valDst0 & maskDst1);
  }
  else if(bitSrcDst1 <0) {
    valDst = ((valSrc2<< bitDstSrc2) & maskSrcDst3) | ((valSrc1>> bitDstSrc1) & maskDst2) | ((valDst0) & maskDst1);
//    valDst = ((valSrc1>> bitDstSrc1) & maskDst2) | ((valSrc0>> bitDstSrc2) & maskDst1);
  } else {
    valDst = (valSrc1 & maskDst2) | (valDst0 & maskDst1);
  }


  uint ix = 0; 
  while( zBytes >0) {
    if( (zBytes + byteDst) < nrofByte4MemAccess) {  //prevent rest in dst
      uint maskDst = (1<<((zBytes + byteDst)<<3))-1;  //0x000000ff, 0x0000ffff, 0x00ffffff if zBytes = 1,2,3
      valDst = (valDst & maskDst ) | (dst0[ixmemDst] & ~maskDst); 
    }
    dst0[ixmemDst++] = valDst;

    zBytes -= (nrofByte4MemAccess - byteDst);  //decrement with number of first bytes written.
    byteDst = 0;                    //next loop uses right bounded byteDst.
    if(zBytes >0) {
      uint valSrc0 = valSrc1;
      valSrc1 = valSrc2;
      //if(zBytes >= nrofByte4MemAccess) { 
      if(ixmemSrc < ixmemSrcEnd) { 
        valSrc2 = src0[ ++ixmemSrc]; 
      } else {
        valSrc2 = 0; //dst[ixmemDst] >> bitDstSrc2;  //only this bits are used, shift left again 
      }
      if(bitSrcDst1 >0) {
        valDst = ((valSrc1<< bitSrcDst1) & maskSrcDst3) |  ( (valSrc0>> bitSrcDst0) & maskSrcDst0);
      }
      else if(bitSrcDst1 <0) {
        valDst = ((valSrc2<< bitDstSrc2) & maskSrcDst3) | ((valSrc1>> bitDstSrc1) & maskSrcDst0);
      } else {
        valDst = (valSrc1 & maskSrcDst3) | (valSrc0 & maskSrcDst0);
      }
    }
  }

  return 0;
}
