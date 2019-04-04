/* **********************************************************************************************
 * This source contains the declaration of methods to read a line from file.
 * Note: It uses the OSAL-layer. It means, it is able to use for any platform.
 * Note: Not all platforms supports the standard-C-FILE-routines.
 */
#ifndef __emC_fw_readline_h
#define __emC_fw_readline_h

//#include <stdio.h>
#include <applstdef_emC.h>
#include <OSAL/os_file.h>

/*@CLASS_C ReadLine_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

typedef struct ReadLine_emC_t
{ OS_HandleFile file;
  bool endOfFile;
	char buffer[4096];
  int posBuffer;
  int endBuffer;

}ReadLine_emC;


extern_C void ctor_ReadLine_emC();

extern_C bool open_ReadLine_emC(ReadLine_emC* ythis, char const* file);
extern_C bool close_ReadLine_emC(ReadLine_emC* ythis);
extern_C char const* readLine_ReadLine_emC(ReadLine_emC* ythis);




#endif //__emC_fw_readline_h
