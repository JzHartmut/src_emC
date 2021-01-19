#include <emC/OSAL/os_keyboard.h>

//undef some things which may be defined in any other user's compl_adaption.h and which are defined by MS VS too:
#undef BOOL
#undef PBOOL
#undef boolean
#undef INT32
#undef UINT32
#undef int64
//#undef uint64   //elsewhere unknown, MS-Visual Studio does not define it. 
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
