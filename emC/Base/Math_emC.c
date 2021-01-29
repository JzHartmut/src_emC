#include <emC/Base/Math_emC.h>
#include <compl_adaption.h>


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

