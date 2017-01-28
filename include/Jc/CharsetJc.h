#ifndef __CharsetJc_h__
#define __CharsetJc_h__

#include <applstdefJc.h>  //defines ThCxt

typedef struct CharsetJc_t
{
  StringJc name;

} CharsetJc;


extern CharsetJc charset_ISO_8859_1;


CharsetJc* forName_CharsetJc(StringJc name, ThCxt* _thCxt);

CharsetJc* forNamez_CharsetJc(char const* name, ThCxt* _thCxt);


#endif  // __CharsetJc_h__
