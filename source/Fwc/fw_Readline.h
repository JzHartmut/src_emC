/* **********************************************************************************************
 * This source contains the declaration of methods to read a line from file.
 * Note: It uses the OSAL-layer. It means, it is able to use for any platform.
 * Note: Not all platforms supports the standard-C-FILE-routines.
 */
#ifndef __Fwc_fw_readline_h
#define __Fwc_fw_readline_h

//#include <stdio.h>
#include <applstdefJc.h>
#include <os_file.h>

/*@CLASS_C ReadLine_Fwc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct ReadLine_Fwc_t
{ OS_HandleFile file;
  bool endOfFile;
	char buffer[4096];
  int posBuffer;
  int endBuffer;

}ReadLine_Fwc;


extern_C void ctor_ReadLine_Fwc();

extern_C bool open_ReadLine_Fwc(ReadLine_Fwc* ythis, char const* file);
extern_C bool close_ReadLine_Fwc(ReadLine_Fwc* ythis);
extern_C char const* readLine_ReadLine_Fwc(ReadLine_Fwc* ythis);




#endif //__Fwc_fw_readline_h
