#include <emC/Base/Math_emC.h>
#include <compl_adaption.h>
#include <math.h>
#include <stdio.h>


//free to "A Quake III Algorithm", see https://www.youtube.com/watch?v=p8u_k2LIZyo&feature=youtu.be
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


                                                       
static const int16 cosTable[] = {
  NOM_i16_Ctrl_emC                  // cos table calculate in compile time.
, (int16)(NOM_i16_Ctrl_emC * (cosf( 1.0f*PI_float_emC/128)) - ( (cosf( 1.0f* PI_float_emC/128)+cosf( 2.0f* PI_float_emC/128))/2 - cosf( 1.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf( 2.0f*PI_float_emC/128)) - ( (cosf( 2.0f* PI_float_emC/128)+cosf( 3.0f* PI_float_emC/128))/2 - cosf( 2.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf( 3.0f*PI_float_emC/128)) - ( (cosf( 3.0f* PI_float_emC/128)+cosf( 4.0f* PI_float_emC/128))/2 - cosf( 3.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf( 4.0f*PI_float_emC/128)) - ( (cosf( 4.0f* PI_float_emC/128)+cosf( 5.0f* PI_float_emC/128))/2 - cosf( 4.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf( 5.0f*PI_float_emC/128)) - ( (cosf( 5.0f* PI_float_emC/128)+cosf( 6.0f* PI_float_emC/128))/2 - cosf( 5.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf( 6.0f*PI_float_emC/128)) - ( (cosf( 6.0f* PI_float_emC/128)+cosf( 7.0f* PI_float_emC/128))/2 - cosf( 6.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf( 7.0f*PI_float_emC/128)) - ( (cosf( 7.0f* PI_float_emC/128)+cosf( 8.0f* PI_float_emC/128))/2 - cosf( 7.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf( 8.0f*PI_float_emC/128)) - ( (cosf( 8.0f* PI_float_emC/128)+cosf( 9.0f* PI_float_emC/128))/2 - cosf( 8.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf( 9.0f*PI_float_emC/128)) - ( (cosf( 9.0f* PI_float_emC/128)+cosf(10.0f* PI_float_emC/128))/2 - cosf( 9.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(10.0f*PI_float_emC/128)) - ( (cosf(10.0f* PI_float_emC/128)+cosf(11.0f* PI_float_emC/128))/2 - cosf(10.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(11.0f*PI_float_emC/128)) - ( (cosf(11.0f* PI_float_emC/128)+cosf(12.0f* PI_float_emC/128))/2 - cosf(11.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(12.0f*PI_float_emC/128)) - ( (cosf(12.0f* PI_float_emC/128)+cosf(13.0f* PI_float_emC/128))/2 - cosf(12.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(13.0f*PI_float_emC/128)) - ( (cosf(13.0f* PI_float_emC/128)+cosf(14.0f* PI_float_emC/128))/2 - cosf(13.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(14.0f*PI_float_emC/128)) - ( (cosf(14.0f* PI_float_emC/128)+cosf(15.0f* PI_float_emC/128))/2 - cosf(14.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(15.0f*PI_float_emC/128)) - ( (cosf(15.0f* PI_float_emC/128)+cosf(16.0f* PI_float_emC/128))/2 - cosf(15.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(16.0f*PI_float_emC/128)) - ( (cosf(16.0f* PI_float_emC/128)+cosf(17.0f* PI_float_emC/128))/2 - cosf(16.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(17.0f*PI_float_emC/128)) - ( (cosf(17.0f* PI_float_emC/128)+cosf(18.0f* PI_float_emC/128))/2 - cosf(17.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(18.0f*PI_float_emC/128)) - ( (cosf(18.0f* PI_float_emC/128)+cosf(19.0f* PI_float_emC/128))/2 - cosf(18.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(19.0f*PI_float_emC/128)) - ( (cosf(19.0f* PI_float_emC/128)+cosf(20.0f* PI_float_emC/128))/2 - cosf(19.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(20.0f*PI_float_emC/128)) - ( (cosf(20.0f* PI_float_emC/128)+cosf(21.0f* PI_float_emC/128))/2 - cosf(20.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(21.0f*PI_float_emC/128)) - ( (cosf(21.0f* PI_float_emC/128)+cosf(22.0f* PI_float_emC/128))/2 - cosf(21.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(22.0f*PI_float_emC/128)) - ( (cosf(22.0f* PI_float_emC/128)+cosf(23.0f* PI_float_emC/128))/2 - cosf(22.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(23.0f*PI_float_emC/128)) - ( (cosf(23.0f* PI_float_emC/128)+cosf(24.0f* PI_float_emC/128))/2 - cosf(23.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(24.0f*PI_float_emC/128)) - ( (cosf(24.0f* PI_float_emC/128)+cosf(25.0f* PI_float_emC/128))/2 - cosf(24.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(25.0f*PI_float_emC/128)) - ( (cosf(25.0f* PI_float_emC/128)+cosf(26.0f* PI_float_emC/128))/2 - cosf(25.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(26.0f*PI_float_emC/128)) - ( (cosf(26.0f* PI_float_emC/128)+cosf(27.0f* PI_float_emC/128))/2 - cosf(26.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(27.0f*PI_float_emC/128)) - ( (cosf(27.0f* PI_float_emC/128)+cosf(28.0f* PI_float_emC/128))/2 - cosf(27.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(28.0f*PI_float_emC/128)) - ( (cosf(28.0f* PI_float_emC/128)+cosf(29.0f* PI_float_emC/128))/2 - cosf(28.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(29.0f*PI_float_emC/128)) - ( (cosf(29.0f* PI_float_emC/128)+cosf(30.0f* PI_float_emC/128))/2 - cosf(29.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(30.0f*PI_float_emC/128)) - ( (cosf(30.0f* PI_float_emC/128)+cosf(31.0f* PI_float_emC/128))/2 - cosf(30.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(31.0f*PI_float_emC/128)) - ( (cosf(31.0f* PI_float_emC/128)+cosf(32.0f* PI_float_emC/128))/2 - cosf(31.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(32.0f*PI_float_emC/128)) - ( (cosf(32.0f* PI_float_emC/128)+cosf(33.0f* PI_float_emC/128))/2 - cosf(32.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(33.0f*PI_float_emC/128)) - ( (cosf(33.0f* PI_float_emC/128)+cosf(34.0f* PI_float_emC/128))/2 - cosf(33.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(34.0f*PI_float_emC/128)) - ( (cosf(34.0f* PI_float_emC/128)+cosf(35.0f* PI_float_emC/128))/2 - cosf(34.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(35.0f*PI_float_emC/128)) - ( (cosf(35.0f* PI_float_emC/128)+cosf(36.0f* PI_float_emC/128))/2 - cosf(35.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(36.0f*PI_float_emC/128)) - ( (cosf(36.0f* PI_float_emC/128)+cosf(37.0f* PI_float_emC/128))/2 - cosf(36.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(37.0f*PI_float_emC/128)) - ( (cosf(37.0f* PI_float_emC/128)+cosf(38.0f* PI_float_emC/128))/2 - cosf(37.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(38.0f*PI_float_emC/128)) - ( (cosf(38.0f* PI_float_emC/128)+cosf(39.0f* PI_float_emC/128))/2 - cosf(38.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(39.0f*PI_float_emC/128)) - ( (cosf(39.0f* PI_float_emC/128)+cosf(40.0f* PI_float_emC/128))/2 - cosf(39.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(40.0f*PI_float_emC/128)) - ( (cosf(40.0f* PI_float_emC/128)+cosf(41.0f* PI_float_emC/128))/2 - cosf(40.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(41.0f*PI_float_emC/128)) - ( (cosf(41.0f* PI_float_emC/128)+cosf(42.0f* PI_float_emC/128))/2 - cosf(41.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(42.0f*PI_float_emC/128)) - ( (cosf(42.0f* PI_float_emC/128)+cosf(43.0f* PI_float_emC/128))/2 - cosf(42.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(43.0f*PI_float_emC/128)) - ( (cosf(43.0f* PI_float_emC/128)+cosf(44.0f* PI_float_emC/128))/2 - cosf(43.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(44.0f*PI_float_emC/128)) - ( (cosf(44.0f* PI_float_emC/128)+cosf(45.0f* PI_float_emC/128))/2 - cosf(44.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(45.0f*PI_float_emC/128)) - ( (cosf(45.0f* PI_float_emC/128)+cosf(46.0f* PI_float_emC/128))/2 - cosf(45.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(46.0f*PI_float_emC/128)) - ( (cosf(46.0f* PI_float_emC/128)+cosf(47.0f* PI_float_emC/128))/2 - cosf(46.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(47.0f*PI_float_emC/128)) - ( (cosf(47.0f* PI_float_emC/128)+cosf(48.0f* PI_float_emC/128))/2 - cosf(47.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(48.0f*PI_float_emC/128)) - ( (cosf(48.0f* PI_float_emC/128)+cosf(49.0f* PI_float_emC/128))/2 - cosf(48.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(49.0f*PI_float_emC/128)) - ( (cosf(49.0f* PI_float_emC/128)+cosf(50.0f* PI_float_emC/128))/2 - cosf(49.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(50.0f*PI_float_emC/128)) - ( (cosf(50.0f* PI_float_emC/128)+cosf(51.0f* PI_float_emC/128))/2 - cosf(50.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(51.0f*PI_float_emC/128)) - ( (cosf(51.0f* PI_float_emC/128)+cosf(52.0f* PI_float_emC/128))/2 - cosf(51.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(52.0f*PI_float_emC/128)) - ( (cosf(52.0f* PI_float_emC/128)+cosf(53.0f* PI_float_emC/128))/2 - cosf(52.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(53.0f*PI_float_emC/128)) - ( (cosf(53.0f* PI_float_emC/128)+cosf(54.0f* PI_float_emC/128))/2 - cosf(53.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(54.0f*PI_float_emC/128)) - ( (cosf(54.0f* PI_float_emC/128)+cosf(55.0f* PI_float_emC/128))/2 - cosf(54.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(55.0f*PI_float_emC/128)) - ( (cosf(55.0f* PI_float_emC/128)+cosf(56.0f* PI_float_emC/128))/2 - cosf(55.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(56.0f*PI_float_emC/128)) - ( (cosf(56.0f* PI_float_emC/128)+cosf(57.0f* PI_float_emC/128))/2 - cosf(56.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(57.0f*PI_float_emC/128)) - ( (cosf(57.0f* PI_float_emC/128)+cosf(58.0f* PI_float_emC/128))/2 - cosf(57.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(58.0f*PI_float_emC/128)) - ( (cosf(58.0f* PI_float_emC/128)+cosf(59.0f* PI_float_emC/128))/2 - cosf(58.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(59.0f*PI_float_emC/128)) - ( (cosf(59.0f* PI_float_emC/128)+cosf(60.0f* PI_float_emC/128))/2 - cosf(59.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(60.0f*PI_float_emC/128)) - ( (cosf(60.0f* PI_float_emC/128)+cosf(61.0f* PI_float_emC/128))/2 - cosf(60.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(61.0f*PI_float_emC/128)) - ( (cosf(61.0f* PI_float_emC/128)+cosf(62.0f* PI_float_emC/128))/2 - cosf(61.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(62.0f*PI_float_emC/128)) - ( (cosf(62.0f* PI_float_emC/128)+cosf(63.0f* PI_float_emC/128))/2 - cosf(62.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(63.0f*PI_float_emC/128)) - ( (cosf(63.0f* PI_float_emC/128)+cosf(64.0f* PI_float_emC/128))/2 - cosf(63.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(64.0f*PI_float_emC/128)) - ( (cosf(64.0f* PI_float_emC/128)+cosf(65.0f* PI_float_emC/128))/2 - cosf(64.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(65.0f*PI_float_emC/128)) - ( (cosf(65.0f* PI_float_emC/128)+cosf(66.0f* PI_float_emC/128))/2 - cosf(65.5f*PI_float_emC/128)) )
, (int16)(NOM_i16_Ctrl_emC * (cosf(66.0f*PI_float_emC/128)) - ( (cosf(66.0f* PI_float_emC/128)+cosf(67.0f* PI_float_emC/128))/2 - cosf(66.5f*PI_float_emC/128)) )
};

int16 cos16_emC(int16 angle) {
  uint16 angle1 = (uint16)angle; 
  int16 sign = 0;
  if(angle <0) { angle1 = (uint16)(-angle); }    //cos is 0-y-axes symmetric. Note: 0x8000 results in 0x8000.
  if(angle1 & 0xc000) {
    angle1 = 0x8000U - angle1;          //cos is point-symmetric on 90°
    sign = -0x8000;
  }
  //now angle1 is in range 0000...0x4000
  uint ixTable = angle1 >> 8;         // 64 entries for linear approximation between 0x0000 .. 0x4000
  int16 cos1 = cosTable[ixTable];
  int16 cos2 = cosTable[ixTable+1];
  int16 dcos = (cos2 - cos1);          // y-growth for linear approximation  
  dcos += (dcos & 3);                  // fefc->fffc  feff->ff81  round near to correct value
  dcos >>=2;                           // max value should < -0xff
  int16 diff = angle1 & 0x0ff;         // x-diff for linear approximation 
  int16 corr = (int16)((diff * (dcos)) >>6);  //shift at least for size of diff, but y-groth was shifted too. 
  //printf("%1.5f ", (float)corr / (float)NOM_i16_Ctrl_emC);
  int16 cos0 = cos1 + corr;            // corr is the add value of the linear approximation.
  if(sign <0) return -cos0;
  else return cos0;
}



static const int32 cosTable32[] = {
  NOM_i32_Ctrl_emC                  // cos table calculate in compile time.
, (int32)(NOM_i32_Ctrl_emC * (cosf( 1.0f*PI_float_emC/128)) - ( (cosf( 1.0f* PI_float_emC/128)+cosf( 2.0f* PI_float_emC/128))/2 - cosf( 1.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf( 2.0f*PI_float_emC/128)) - ( (cosf( 2.0f* PI_float_emC/128)+cosf( 3.0f* PI_float_emC/128))/2 - cosf( 2.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf( 3.0f*PI_float_emC/128)) - ( (cosf( 3.0f* PI_float_emC/128)+cosf( 4.0f* PI_float_emC/128))/2 - cosf( 3.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf( 4.0f*PI_float_emC/128)) - ( (cosf( 4.0f* PI_float_emC/128)+cosf( 5.0f* PI_float_emC/128))/2 - cosf( 4.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf( 5.0f*PI_float_emC/128)) - ( (cosf( 5.0f* PI_float_emC/128)+cosf( 6.0f* PI_float_emC/128))/2 - cosf( 5.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf( 6.0f*PI_float_emC/128)) - ( (cosf( 6.0f* PI_float_emC/128)+cosf( 7.0f* PI_float_emC/128))/2 - cosf( 6.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf( 7.0f*PI_float_emC/128)) - ( (cosf( 7.0f* PI_float_emC/128)+cosf( 8.0f* PI_float_emC/128))/2 - cosf( 7.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf( 8.0f*PI_float_emC/128)) - ( (cosf( 8.0f* PI_float_emC/128)+cosf( 9.0f* PI_float_emC/128))/2 - cosf( 8.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf( 9.0f*PI_float_emC/128)) - ( (cosf( 9.0f* PI_float_emC/128)+cosf(10.0f* PI_float_emC/128))/2 - cosf( 9.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(10.0f*PI_float_emC/128)) - ( (cosf(10.0f* PI_float_emC/128)+cosf(11.0f* PI_float_emC/128))/2 - cosf(10.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(11.0f*PI_float_emC/128)) - ( (cosf(11.0f* PI_float_emC/128)+cosf(12.0f* PI_float_emC/128))/2 - cosf(11.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(12.0f*PI_float_emC/128)) - ( (cosf(12.0f* PI_float_emC/128)+cosf(13.0f* PI_float_emC/128))/2 - cosf(12.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(13.0f*PI_float_emC/128)) - ( (cosf(13.0f* PI_float_emC/128)+cosf(14.0f* PI_float_emC/128))/2 - cosf(13.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(14.0f*PI_float_emC/128)) - ( (cosf(14.0f* PI_float_emC/128)+cosf(15.0f* PI_float_emC/128))/2 - cosf(14.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(15.0f*PI_float_emC/128)) - ( (cosf(15.0f* PI_float_emC/128)+cosf(16.0f* PI_float_emC/128))/2 - cosf(15.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(16.0f*PI_float_emC/128)) - ( (cosf(16.0f* PI_float_emC/128)+cosf(17.0f* PI_float_emC/128))/2 - cosf(16.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(17.0f*PI_float_emC/128)) - ( (cosf(17.0f* PI_float_emC/128)+cosf(18.0f* PI_float_emC/128))/2 - cosf(17.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(18.0f*PI_float_emC/128)) - ( (cosf(18.0f* PI_float_emC/128)+cosf(19.0f* PI_float_emC/128))/2 - cosf(18.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(19.0f*PI_float_emC/128)) - ( (cosf(19.0f* PI_float_emC/128)+cosf(20.0f* PI_float_emC/128))/2 - cosf(19.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(20.0f*PI_float_emC/128)) - ( (cosf(20.0f* PI_float_emC/128)+cosf(21.0f* PI_float_emC/128))/2 - cosf(20.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(21.0f*PI_float_emC/128)) - ( (cosf(21.0f* PI_float_emC/128)+cosf(22.0f* PI_float_emC/128))/2 - cosf(21.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(22.0f*PI_float_emC/128)) - ( (cosf(22.0f* PI_float_emC/128)+cosf(23.0f* PI_float_emC/128))/2 - cosf(22.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(23.0f*PI_float_emC/128)) - ( (cosf(23.0f* PI_float_emC/128)+cosf(24.0f* PI_float_emC/128))/2 - cosf(23.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(24.0f*PI_float_emC/128)) - ( (cosf(24.0f* PI_float_emC/128)+cosf(25.0f* PI_float_emC/128))/2 - cosf(24.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(25.0f*PI_float_emC/128)) - ( (cosf(25.0f* PI_float_emC/128)+cosf(26.0f* PI_float_emC/128))/2 - cosf(25.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(26.0f*PI_float_emC/128)) - ( (cosf(26.0f* PI_float_emC/128)+cosf(27.0f* PI_float_emC/128))/2 - cosf(26.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(27.0f*PI_float_emC/128)) - ( (cosf(27.0f* PI_float_emC/128)+cosf(28.0f* PI_float_emC/128))/2 - cosf(27.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(28.0f*PI_float_emC/128)) - ( (cosf(28.0f* PI_float_emC/128)+cosf(29.0f* PI_float_emC/128))/2 - cosf(28.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(29.0f*PI_float_emC/128)) - ( (cosf(29.0f* PI_float_emC/128)+cosf(30.0f* PI_float_emC/128))/2 - cosf(29.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(30.0f*PI_float_emC/128)) - ( (cosf(30.0f* PI_float_emC/128)+cosf(31.0f* PI_float_emC/128))/2 - cosf(30.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(31.0f*PI_float_emC/128)) - ( (cosf(31.0f* PI_float_emC/128)+cosf(32.0f* PI_float_emC/128))/2 - cosf(31.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(32.0f*PI_float_emC/128)) - ( (cosf(32.0f* PI_float_emC/128)+cosf(33.0f* PI_float_emC/128))/2 - cosf(32.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(33.0f*PI_float_emC/128)) - ( (cosf(33.0f* PI_float_emC/128)+cosf(34.0f* PI_float_emC/128))/2 - cosf(33.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(34.0f*PI_float_emC/128)) - ( (cosf(34.0f* PI_float_emC/128)+cosf(35.0f* PI_float_emC/128))/2 - cosf(34.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(35.0f*PI_float_emC/128)) - ( (cosf(35.0f* PI_float_emC/128)+cosf(36.0f* PI_float_emC/128))/2 - cosf(35.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(36.0f*PI_float_emC/128)) - ( (cosf(36.0f* PI_float_emC/128)+cosf(37.0f* PI_float_emC/128))/2 - cosf(36.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(37.0f*PI_float_emC/128)) - ( (cosf(37.0f* PI_float_emC/128)+cosf(38.0f* PI_float_emC/128))/2 - cosf(37.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(38.0f*PI_float_emC/128)) - ( (cosf(38.0f* PI_float_emC/128)+cosf(39.0f* PI_float_emC/128))/2 - cosf(38.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(39.0f*PI_float_emC/128)) - ( (cosf(39.0f* PI_float_emC/128)+cosf(40.0f* PI_float_emC/128))/2 - cosf(39.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(40.0f*PI_float_emC/128)) - ( (cosf(40.0f* PI_float_emC/128)+cosf(41.0f* PI_float_emC/128))/2 - cosf(40.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(41.0f*PI_float_emC/128)) - ( (cosf(41.0f* PI_float_emC/128)+cosf(42.0f* PI_float_emC/128))/2 - cosf(41.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(42.0f*PI_float_emC/128)) - ( (cosf(42.0f* PI_float_emC/128)+cosf(43.0f* PI_float_emC/128))/2 - cosf(42.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(43.0f*PI_float_emC/128)) - ( (cosf(43.0f* PI_float_emC/128)+cosf(44.0f* PI_float_emC/128))/2 - cosf(43.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(44.0f*PI_float_emC/128)) - ( (cosf(44.0f* PI_float_emC/128)+cosf(45.0f* PI_float_emC/128))/2 - cosf(44.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(45.0f*PI_float_emC/128)) - ( (cosf(45.0f* PI_float_emC/128)+cosf(46.0f* PI_float_emC/128))/2 - cosf(45.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(46.0f*PI_float_emC/128)) - ( (cosf(46.0f* PI_float_emC/128)+cosf(47.0f* PI_float_emC/128))/2 - cosf(46.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(47.0f*PI_float_emC/128)) - ( (cosf(47.0f* PI_float_emC/128)+cosf(48.0f* PI_float_emC/128))/2 - cosf(47.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(48.0f*PI_float_emC/128)) - ( (cosf(48.0f* PI_float_emC/128)+cosf(49.0f* PI_float_emC/128))/2 - cosf(48.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(49.0f*PI_float_emC/128)) - ( (cosf(49.0f* PI_float_emC/128)+cosf(50.0f* PI_float_emC/128))/2 - cosf(49.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(50.0f*PI_float_emC/128)) - ( (cosf(50.0f* PI_float_emC/128)+cosf(51.0f* PI_float_emC/128))/2 - cosf(50.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(51.0f*PI_float_emC/128)) - ( (cosf(51.0f* PI_float_emC/128)+cosf(52.0f* PI_float_emC/128))/2 - cosf(51.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(52.0f*PI_float_emC/128)) - ( (cosf(52.0f* PI_float_emC/128)+cosf(53.0f* PI_float_emC/128))/2 - cosf(52.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(53.0f*PI_float_emC/128)) - ( (cosf(53.0f* PI_float_emC/128)+cosf(54.0f* PI_float_emC/128))/2 - cosf(53.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(54.0f*PI_float_emC/128)) - ( (cosf(54.0f* PI_float_emC/128)+cosf(55.0f* PI_float_emC/128))/2 - cosf(54.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(55.0f*PI_float_emC/128)) - ( (cosf(55.0f* PI_float_emC/128)+cosf(56.0f* PI_float_emC/128))/2 - cosf(55.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(56.0f*PI_float_emC/128)) - ( (cosf(56.0f* PI_float_emC/128)+cosf(57.0f* PI_float_emC/128))/2 - cosf(56.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(57.0f*PI_float_emC/128)) - ( (cosf(57.0f* PI_float_emC/128)+cosf(58.0f* PI_float_emC/128))/2 - cosf(57.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(58.0f*PI_float_emC/128)) - ( (cosf(58.0f* PI_float_emC/128)+cosf(59.0f* PI_float_emC/128))/2 - cosf(58.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(59.0f*PI_float_emC/128)) - ( (cosf(59.0f* PI_float_emC/128)+cosf(60.0f* PI_float_emC/128))/2 - cosf(59.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(60.0f*PI_float_emC/128)) - ( (cosf(60.0f* PI_float_emC/128)+cosf(61.0f* PI_float_emC/128))/2 - cosf(60.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(61.0f*PI_float_emC/128)) - ( (cosf(61.0f* PI_float_emC/128)+cosf(62.0f* PI_float_emC/128))/2 - cosf(61.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(62.0f*PI_float_emC/128)) - ( (cosf(62.0f* PI_float_emC/128)+cosf(63.0f* PI_float_emC/128))/2 - cosf(62.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(63.0f*PI_float_emC/128)) - ( (cosf(63.0f* PI_float_emC/128)+cosf(64.0f* PI_float_emC/128))/2 - cosf(63.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(64.0f*PI_float_emC/128)) - ( (cosf(64.0f* PI_float_emC/128)+cosf(65.0f* PI_float_emC/128))/2 - cosf(64.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(65.0f*PI_float_emC/128)) - ( (cosf(65.0f* PI_float_emC/128)+cosf(66.0f* PI_float_emC/128))/2 - cosf(65.5f*PI_float_emC/128)) )
, (int32)(NOM_i32_Ctrl_emC * (cosf(66.0f*PI_float_emC/128)) - ( (cosf(66.0f* PI_float_emC/128)+cosf(67.0f* PI_float_emC/128))/2 - cosf(66.5f*PI_float_emC/128)) )
};



int32 cos32_emC(int32 angle) {
  uint32 angle1 = (uint32)angle; 
  int32 sign = 0;
  if(angle <0) { angle1 = (uint32)(-angle); }    //cos is 0-y-axes symmetric. Note: 0x8000 results in 0x8000.
  if(angle1 & 0xc0000000) {
    angle1 = 0x80000000U - angle1;          //cos is point-symmetric on 90°
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
