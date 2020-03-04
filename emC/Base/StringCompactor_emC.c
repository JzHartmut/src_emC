#include <applstdef_emC.h>
#include <emC/Base/String_emC.h>
//https://en.wikipedia.org/wiki/Letter_frequency
//                       xx1     -       |x10    -       |x00      -       |       -       |       -       |       -        |       -       |
char const* charOrder = "eatoihnsrdlcumwfygpkvpbyEATOIHNS !\"#$%&'()*+,-./0123456789:;<=>?@zBCDqFGxjJKLM{}PQR|~UVWXYZ[\\]^_'";

int decode_StringCompactor_emC(char* bu, int zbu, uint8 const* src, int zsrc) {
  int ixSrc = 0;
  int ixDst = 0;
  uint16 w = 0;
  int bit = 0;
  while((ixSrc < zsrc) && ixDst < zbu) {
    if(bit <8 && ixSrc < zsrc) {
      uint16 w2 = src[ixSrc++];
      if(ixSrc == zsrc){
        ixSrc +=0;
      }
      w |= w2 <<bit;
      bit +=8;
    } else {
      bit +=0;
    }
    if(w & 0x01) {
      bu[ixDst++] = charOrder[(w>>1) & 0xf];  //one of first 16 uses 5 bit
      bit -=5;
      w >>=5;
    } else if( (w & 0x3) ==2) {
      bu[ixDst++] = charOrder[((w>>2) & 0xf) +16];  //uses 6 bit, 16 chars
      bit -=6;
      w >>=6;
    } else  {
      bu[ixDst++] = charOrder[((w>>2) & 0x3f) +32];  //uses 8 bit with 64 chars
      bit -=8;
      w >>=8;
    }
  }
  if(ixDst < zbu){
    bu[ixDst] = '\0';  //terminating
  }
  return ixDst;
}


int encode_StringCompactor_emC(uint8* const dst, int zdst, char const* const src, int zsrc) {
  uint8* dst1 = dst;
  char const* src1 = src;
  char cc;
  uint16 w=0;
  int bit = 0;
  int ixdst = 0;
  while(--zsrc>=0 && (cc=*(src1++))!=0) {
    int ix=0;
    while(charOrder[ix] !=cc) {
      if(++ix > 96) break;
    }
    if(ix<16){
      w |= (ix<<(bit+1)) | (1<<bit);
      bit +=5; 
    } else if(ix<32) {
      w |= ( (ix-16)<<(bit+2)) |(2<<bit);
      bit +=6; 
    } else {
      w |= ( (ix-32)<<(bit+2));
      bit +=8; 
    }
    if(bit >=8 && ixdst < zdst) {
      dst1[ixdst] = (uint8)w;
      w >>=8;
      bit -=8;
      ixdst +=1;
    }
  }
  if(bit >=0 && ixdst < zdst) {
    dst1[ixdst] = (uint8)w;
    ixdst +=1;
  }
  return ixdst;

}
