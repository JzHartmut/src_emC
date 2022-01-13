#include <emC/Base/Math_emC.h>
#include <math.h>
#include <stdio.h>


//free to "A Quake III Algorithm", see https://www.youtube.com/watch?v=p8u_k2LIZyo&feature=youtu.be
//see also https://en.wikipedia.org/wiki/Fast_inverse_square_root
float Q_rsqrt ( float number) {
  int32 i;
  float x2, y;
  float const threehalfs = 1.5f;
  x2 = number * 0.5f;
  y = number;
  i = * (long*) &y;
  i = 0x5f3759df - (i >>1 );
  y = * (float*) &i;
  y = y * ( threehalfs - ( x2 * y * y));  //1st iteration
  //y = y * ( threehalfs - ( x2 * y * y));  //2st iteration
  return y;
}



static const uint32 sqrt16_32Table[] = 
{ 0x000020c6  // 0  0
, 0x163e0bb6  // 1  800
, 0x1fdf0810  // 2  1000
, 0x2720068e  // 3  1800
, 0x2d3605ab  // 4  2000
, 0x32910511  // 5  2800
, 0x3767049f  // 6  3000
, 0x3bd90447  // 7  3800
, 0x40000401  // 8  4000
, 0x43df03c6  // 9  4800
, 0x478b0394  // 10  5000
, 0x4b090369  // 11  5800
, 0x4e600344  // 12  6000
, 0x51940323  // 13  6800
, 0x54a80306  // 14  7000
, 0x57a102ec  // 15  7800
, 0x5a8102d4  // 16  8000
, 0x5d4a02bf  // 17  8800
, 0x5fff02ab  // 18  9000
, 0x62a00299  // 19  9800
, 0x65300288  // 20  a000
, 0x67b00278  // 21  a800
, 0x6a21026a  // 22  b000
, 0x6c84025c  // 23  b800
, 0x6ed9024f  // 24  c000
, 0x71220243  // 25  c800
, 0x73600238  // 26  d000
, 0x7593022d  // 27  d800
, 0x77bb0223  // 28  e000
, 0x79da021a  // 29  e800
, 0x7bef0211  // 30  f000
, 0x7dfb0208  // 31  f800
, 0x7fff0200  // 32  10000
};



static const uint32 rsqrt4_32Table[] = 
{ 0x7fff0000  // 0
, 0x7fff0000  // 1
, 0x793ef27f  // 2
, 0x6911ee47  // 3
, 0x5ac7f494  // 4
, 0x511bf7dc  // 5
, 0x49fff9d2  // 6
, 0x4476fb0e  // 7
, 0x4000fbfe  // 8
, 0x3c5dfcb1  // 9
, 0x3945fd23  // 10
, 0x369afd85  // 11
, 0x3446fdd3  // 12
, 0x3238fe12  // 13
, 0x3064fe46  // 14
, 0x2ec0fe72  // 15
, 0x2d43fe97  // 16
, 0x2be9feb6  // 17
, 0x2aacfed1  // 18
, 0x2989fee9  // 19
, 0x287bfefe  // 20
, 0x2781ff10  // 21
, 0x2699ff20  // 22
, 0x25c0ff2f  // 23
, 0x24f4ff3c  // 24
, 0x2435ff48  // 25
, 0x2381ff52  // 26
, 0x22d7ff5c  // 27
, 0x2236ff65  // 28
, 0x219eff6d  // 29
, 0x210dff74  // 30
, 0x2083ff7b  // 31
, 0x2000ff81  // 32
};



static const uint32 rsqrt2_32Table[] = 
{ 0x7fff0000  // 0  0
, 0x7fff0000  // 1  400
, 0x7fff0000  // 2  800
, 0x7fff0000  // 3  c00
, 0x7c56f8b0  // 4  1000
, 0x72b4f47c  // 5  1400
, 0x68a6f742  // 6  1800
, 0x60daf912  // 7  1c00
, 0x5a93fa55  // 8  2000
, 0x5562fb41  // 9  2400
, 0x50fefbf3  // 10  2800
, 0x4d38fc7e  // 11  2c00
, 0x49edfcec  // 12  3000
, 0x4705fd45  // 13  3400
, 0x446ffd8f  // 14  3800
, 0x421cfdca  // 15  3c00
, 0x4000fe01  // 16  4000
, 0x3e19fe30  // 17  4400
, 0x3c59fe54  // 18  4800
, 0x3abdfe75  // 19  4c00
, 0x3940fe92  // 20  5000
, 0x37dffeac  // 21  5400
, 0x3696fec3  // 22  5800
, 0x3562fed8  // 23  5c00
, 0x3443feea  // 24  6000
, 0x3334fefb  // 25  6400
, 0x3236ff0a  // 26  6800
, 0x3145ff17  // 27  6c00
, 0x3062ff24  // 28  7000
, 0x2f8aff2f  // 29  7400
, 0x2ebeff3a  // 30  7800
, 0x2dfbff43  // 31  7c00
, 0x2d42ff4c  // 32  8000
};



static const uint32 cosTable[] = 
{ 0x7ffffffb  // 0  0
, 0x7fd3ffb2  // 1  200
, 0x7f5dff64  // 2  400
, 0x7e98ff15  // 3  600
, 0x7d86fec7  // 4  800
, 0x7c25fe7a  // 5  a00
, 0x7a78fe2e  // 6  c00
, 0x7880fde3  // 7  e00
, 0x763dfd9a  // 8  1000
, 0x73b1fd51  // 9  1200
, 0x70defd0b  // 10  1400
, 0x6dc6fcc6  // 11  1600
, 0x6a69fc83  // 12  1800
, 0x66ccfc43  // 13  1a00
, 0x62eefc05  // 14  1c00
, 0x5ed4fbc9  // 15  1e00
, 0x5a7ffb90  // 16  2000
, 0x55f2fb59  // 17  2200
, 0x5131fb26  // 18  2400
, 0x4c3dfaf5  // 19  2600
, 0x471afac8  // 20  2800
, 0x41ccfa9d  // 21  2a00
, 0x3c54fa77  // 22  2c00
, 0x36b8fa53  // 23  2e00
, 0x30fafa33  // 24  3000
, 0x2b1efa17  // 25  3200
, 0x2527f9fe  // 26  3400
, 0x1f19f9e9  // 27  3600
, 0x18f8f9d8  // 28  3800
, 0x12c7f9ca  // 29  3a00
, 0x0c8bf9c0  // 30  3c00
, 0x0648f9bb  // 31  3e00
, 0x0000f9b9  // 32  4000
, 0xf9b9f9bb  // 33  4200
, 0xf376f9c0  // 34  4400
, 0xed3af9ca  // 35  4600
, 0xe709f9d8  // 36  4800
, 0xe0e8f9e9  // 37  4a00
, 0xdadaf9fe  // 38  4c00
, 0xd4e3fa17  // 39  4e00
, 0xcf07fa33  // 40  5000
, 0xc949fa53  // 41  5200
, 0xc3adfa77  // 42  5400
, 0xbe35fa9d  // 43  5600
, 0xb8e7fac8  // 44  5800
, 0xb3c4faf5  // 45  5a00
, 0xaed0fb26  // 46  5c00
, 0xaa0ffb59  // 47  5e00
, 0xa582fb90  // 48  6000
, 0xa12dfbc9  // 49  6200
, 0x9d13fc05  // 50  6400
, 0x9935fc43  // 51  6600
, 0x9598fc83  // 52  6800
, 0x923bfcc6  // 53  6a00
, 0x8f23fd0b  // 54  6c00
, 0x8c50fd51  // 55  6e00
, 0x89c4fd9a  // 56  7000
, 0x8781fde3  // 57  7200
, 0x8589fe2e  // 58  7400
, 0x83dcfe7a  // 59  7600
, 0x827bfec7  // 60  7800
, 0x8169ff15  // 61  7a00
, 0x80a4ff63  // 62  7c00
, 0x802dffb2  // 63  7e00
, 0x8000fffa  // 64  8000
};


static const uint32 asinTable[] = 
{ 0x0000028c  // 0  0
, 0x028c028d  // 1  400
, 0x051c0291  // 2  800
, 0x07b00298  // 3  c00
, 0x0a4c02a1  // 4  1000
, 0x0cf402ae  // 5  1400
, 0x0fab02bf  // 6  1800
, 0x127502d5  // 7  1c00
, 0x155702f1  // 8  2000
, 0x185a0315  // 9  2400
, 0x1b850344  // 10  2800
, 0x1ee70383  // 11  2c00
, 0x229403db  // 12  3000
, 0x26af0462  // 13  3400
, 0x2b7d054d  // 14  3800
, 0x31c30792  // 15  3c00
, 0x40000f3d  // 16  4000
};




static const uint16 cosTableQu[][3] = 
{ { 0x7fff, 0x0000, 0xfec6 } // 0
, { 0x7f62, 0xfd8b, 0xfec5 } // 1
, { 0x7d8a, 0xfb1b, 0xfecb } // 2
, { 0x7a7d, 0xf8b7, 0xfed1 } // 3
, { 0x7641, 0xf665, 0xfedd } // 4
, { 0x70e2, 0xf42c, 0xfeea } // 5
, { 0x6a6d, 0xf210, 0xfefa } // 6
, { 0x62f2, 0xf015, 0xff0b } // 7
, { 0x5a82, 0xee41, 0xff21 } // 8
, { 0x5133, 0xec9a, 0xff38 } // 9
, { 0x471c, 0xeb23, 0xff51 } // 10
, { 0x3c56, 0xe9df, 0xff6b } // 11
, { 0x30fb, 0xe8d2, 0xff88 } // 12
, { 0x2528, 0xe7fd, 0xffa3 } // 13
, { 0x18f8, 0xe763, 0xffc3 } // 14
, { 0x0c8b, 0xe708, 0xffe2 } // 15
, { 0x0000, 0xe6ea, 0x0000 } // 16
};


static const int16 arcsinTable[][3] = 
{ { 0x0000, 0x0518, 0x0000 } // 0
, { 0x028c, 0x051b, 0x0003 } // 1
, { 0x051b, 0x0523, 0x0005 } // 2
, { 0x07af, 0x0530, 0x0008 } // 3
, { 0x0a4b, 0x0544, 0x000c } // 4
, { 0x0cf3, 0x055e, 0x000e } // 5
, { 0x0fa9, 0x0580, 0x0014 } // 6
, { 0x1273, 0x05ac, 0x0018 } // 7
, { 0x1555, 0x05e4, 0x0020 } // 8
, { 0x1857, 0x062c, 0x0028 } // 9
, { 0x1b81, 0x068b, 0x0037 } // 10
, { 0x1ee2, 0x070c, 0x004a } // 11
, { 0x228d, 0x07c2, 0x006c } // 12
, { 0x26a4, 0x08db, 0x00ad } // 13
, { 0x2b68, 0x0ae0, 0x0158 } // 14
, { 0x3184, 0x1498, 0x0860 } // 15
};





//https://www.astro.uni-jena.de/Teaching/Praktikum/pra2002/node288.html ... quadratische Interpolation
  
short interpolqu16 ( int16 x, uint16 const table[][3]) {
  ASSERT_emC(x >=0 && x <= 0x4000, "not in range 0...0x4000", x, 0);      
  int ixTable = x >> 10;               // index from bits 15..10
  int diff = x & 0x3ff;                // 1 entry for range -200 .. 1ff, 
  if( (diff & 0x200) !=0) {
    diff -= 0x400;                     // seen from the other side, get negative.
    ixTable +=1;
  }
  uint16 const* tableix = table[ixTable];     // address the line of the table
  int16 val = tableix[0];              // get val and difference-factors
  int16 dval1 = tableix[1];
  int16 dval2 = tableix[2];
  int32 yd1, yd2, diff2;
  muls16_emC(yd1, diff, dval1);        //interpolation first order
  muls16_emC(diff2, diff, diff);       //diff^2 
  int16 diff2a = (int16)(diff2 >>5);   //should not be too large, lesser bits not necessary
  muls16_emC(yd2, diff2a, dval2);        //interpolation second order dval2 * diff^2

  int16 ret = val + (int16)(yd1>>11) + (int16)(yd2>>16);
  return ret;
}


//This definition should be included immediately in any routine. 
//Because of some compiler calculated const it is written as macro.
//The macro is expanded in comment in cos16_emC(...) to test it.
#define LINEARinterpol16_emC(X, TABLE, BITSEGM) \
  uint32 const* table = TABLE; \
  uint32 valTable = table[( X + (1 <<(BITSEGM-1) ) ) >>BITSEGM]; \
  int16 dx = ( X <<(16 - BITSEGM) ) & 0xffff; \
  int16 gain = (int16)(valTable & 0xffff); \
  muls16add32_emC(valTable, dx, gain); \
  int16 y = (int16)(valTable >>16); \


int16 cos16_emC ( int16 angle) {
  int16 x = angle; 
  if(angle <0) {                       // cos is 0-y-axes symmetric. .
    x = -x;                  // Note: 0x8000 results in 0x8000
  }
  //now x is in range 0000...0x4000
  //commented possibility, using interpolqu, extra call, more calctime
  //int16 val = interpolqu16(angle1, cosTableQu);
  //                                   // access to left or right point
  LINEARinterpol16_emC(x, cosTable, 9)
  /*
  uint32 const* table = cosTable; 
  uint32 valTable = table[( x + (1<<(9-1) ) >>9]; 
  int16 dx = ( x <<(16 - 9) ) & 0xffff; 
  int16 gain = (int16)(valTable & 0xffff); 
  muls16add32_emC(valTable, dx, gain); 
  int16 y = (int16)(valTable >>16); 
  */
  return y;
}





int16 atan2nom16_emC ( int16_complex x ) {
  short re1 = x.re; short im1 = x.im;
  int quadr = 0;
  if(im1 <0) {
    im1 = (short)-im1;
    quadr = 2;
  }
  if(re1 <0) {
    re1 = (short)-re1;
    quadr |= 4;
  }
  int xasin;
  if(re1 < im1) {
    xasin = re1;
    quadr |= 1;
  } else {
    xasin = im1;
  }
  LINEARinterpol16_emC(xasin, asinTable, 10);
  switch(quadr) {
  case 0: return y;
  case 1: return 0x4000 - y;
  case 5: return 0x4000 + y;
  case 4: return 0x8000 - y;
  case 6: return 0x8000 + y;
  case 7: return 0xc000 - y;
  case 3: return 0xc000 + y;
  case 2: return -y;
  default: return 0;
  }
}






int16 sqrt16_emC ( uint16 x) {
  //x is valid in range 0000...0xFFFF
  LINEARinterpol16_emC(x, sqrt16_32Table, 11)
  return y;
}


int16 rsqrt16_emC ( int16 x) {
  //x is valid in range 0000...0xFFFF
  LINEARinterpol16_emC(x, rsqrt2_32Table, 10)
  /*
  uint32 const* table = rsqrt2_32Table; 
  uint32 valTable = table[( x + 0x400 ) >>11]; 
  int16 dx = ( x <<(16 - 11) ) & 0xffff; 
  int16 gain = (int16)(valTable & 0xffff); 
  muls16add32_emC(valTable, dx, gain); 
  int16 y = (int16)(valTable >>16); 
  */
  return y;
}





/*
int32 cos32_emC(int32 angle) {
  uint32 angle1 = (uint32)angle; 
  int32 sign = 0;
  if(angle <0) { angle1 = (uint32)(-angle); }    //cos is 0-y-axes symmetric. Note: 0x8000 results in 0x8000.
  if(angle1 & 0xc0000000) {
    angle1 = 0x80000000U - angle1;          //cos is point-symmetric on 90?
    sign = 0x80000000;
  }
  //now angle1 is in range 0000...0x4000
  uint ixTable = angle1 >> 24;         // 64 entries for linear approximation between 0x0000 .. 0x4000
  int32 cos1 = cosTable32[ixTable];
  int32 cos2 = cosTable32[ixTable+1];
  int32 dcos = (cos2 - cos1);          // y-growth for linear approximation  
  int32 diff = angle1 & 0x0ffffff;         // x-diff for linear approximation 
  int32 corr = (int32)(((int64)diff * dcos) >>24);  //shift at least for size of diff, but y-groth was shifted too. 
  //printf("%1.5f ", (float)corr / (float)NOM_i16_Ctrl_emC);
  int32 cos0 = cos1 + corr;            // corr is the add value of the linear approximation.
  if(sign <0) return -cos0;
  else return cos0;
}
*/
