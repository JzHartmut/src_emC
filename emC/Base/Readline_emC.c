/* **********************************************************************************************
 * This source contains the definition of methods to read a line from file.
 * Note: It uses the OSAL-layer. It means, it is able to use for any platform.
 * Note: Not all platforms supports the standard-C-FILE-routines.
 */

//Styleguide: Include the own header first, it should include all necessary depending headers itself. 
#include <emC/Base/Readline_emC.h>

//Styleguide: Include all necessities for implementation, the standard headers at least.
#include <emC/Base/SimpleC_emC.h>
#include <emC/Base/StringBase_emC.h>
#include <string.h>

void ctor_ReadLine_emC(ReadLine_emC* ythis)
{
	ythis->posBuffer = ythis->endBuffer = 0;
	ythis->endOfFile = false;
	memset(ythis->buffer, 0, sizeof(ythis->buffer));
}


bool open_ReadLine_emC(ReadLine_emC* ythis, char const* sFile)
{ ythis->file = os_fopenToRead(sFile);
  return ythis->file !=null;
}

bool close_ReadLine_emC(ReadLine_emC* ythis)
{ os_fclose(ythis->file);
  return true;
}


char const* readLine_ReadLine_emC(ReadLine_emC* ythis)
{
  char* sLine;
	int length = ythis->endBuffer - ythis->posBuffer;
	if(!ythis->endOfFile && length < (int)sizeof(ythis->buffer) /2) {
		//half buffer processed, read next block
	  int maxRead, read;
		memmove(ythis->buffer, ythis->buffer + ythis->posBuffer, length);  //move to front
    ythis->endBuffer -= ythis->posBuffer;
		ythis->posBuffer = 0;
		maxRead = sizeof(ythis->buffer) - ythis->endBuffer;
		read = os_fread(ythis->file, ythis->buffer + ythis->endBuffer, maxRead);
		if(read >0){
		  ythis->endBuffer += read;
		} else {
			ythis->endOfFile = true;
		}
	}
	//search next 0d0a
	{ int nrofCharsLine = searchChar_emC(ythis->buffer + ythis->posBuffer, ythis->endBuffer - ythis->posBuffer, '\n');
		if(nrofCharsLine <0){ //last line without \n?
			nrofCharsLine = ythis->endBuffer - ythis->posBuffer; 
		}
		if(nrofCharsLine >= 0 && ythis->endBuffer > ythis->posBuffer){
			sLine = ythis->buffer + ythis->posBuffer;
			sLine[nrofCharsLine] = 0;  //0-termination instead 0x0a
			if(sLine[nrofCharsLine-1] == '\r'){
				sLine[nrofCharsLine-1] = 0;  //0-termination instead 0d0a for Windows-like files.
			}
			ythis->posBuffer += nrofCharsLine +1;  //after 0x0a
		} else {
			sLine = null;
		}
	}
	return sLine;  //it is terminated with 0
}

