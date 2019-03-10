#include <OSAL/os_keyboard.h>
#include <applstdef_emC.h>

#undef BOOL
#undef PBOOL
#undef boolean
#undef INT32
#undef UINT32
#undef int64
#undef uint64
#include <wtypes.h>
#include <Winbase.h>


//#define _X86_
//#include <WinUser.h>

bool os_keyState(int key) {

  int16 s = GetAsyncKeyState(key);
  if(s & 1){
    return true;
  } else if(s){
    return true;
  } else {
    return false; 
  } 

}