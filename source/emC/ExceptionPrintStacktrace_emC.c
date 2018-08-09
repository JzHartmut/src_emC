/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public License,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.
 * 4) But the LPGL ist not appropriate for a whole software product,
 *    if this source is only a part of them. It means, the user
 *    must publish this part of source,
 *    but don't need to publish the whole source of the own product.
 * 5) You can study and modify (improve) this source
 *    for own using or for redistribution, but you have to license the
 *    modified sources likewise under this LGPL Lesser General Public License.
 *    You mustn't delete this Copyright/Copyleft inscription in this source file.
 *
 * This source may be used also with another licence, if the author 
 * and all other here named co-authors have agreed to this contract.
 * Especially a company can use a copy of this sources in its products without publishing.
 * The user should have a underwritten contract therefore.
 *
 * @author Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content implementation of routines for exception handling
 *
 * @author Hartmut Schorrig, www.vishia.org
 * @version 0.91
 * list of changes:
 * 2012-04-10 Hartmut new: printStackTrace_P_ExceptionJc(PrintStreamJc_t* out)
 * 2011-01-07: Hartmut: create form fw_Exception.c: Separated implementation, better able to change
 *
 ****************************************************************************/
//It needs for link:
//os_file.c
//copyToBuffer_CharSeqJc: emC/String_emC.c


#include <emC/Exception_emC.h>
#ifndef __NOT_SUPPORTED_ExceptionJc__

#include <emC/ThreadContext_emC.h>
#include <emC/SimpleC_emC.h>     //ARRAYLEN
#include <emC/String_emC.h> 
#include <os_error.h>
//#include <fw_Platform_conventions.h>
#include <stdlib.h>
#include <string.h>  //strlen
#include <os_file.h>
#include <stdio.h>




void printStackTrace_ExceptionJc(ExceptionJc* ythis, ThCxt* _thCxt)
{
  printStackTraceFile_ExceptionJc(ythis,null, _thCxt);  //null causes printf instead sprintf, os_fwrite
}

void printStackTraceFile_ExceptionJc(ExceptionJc* ythis, OS_HandleFile out, ThCxt* _thCxt)
{ //DEF__threadContextJc
  if(_thCxt == null){ _thCxt = getCurrent_ThreadContext_emC(); } 
  int idxStacktraceEntries = 0;
  //int nrofStacktraceEntriesMax;
  char sBuffer[500] = {0};
	int zBuffer;
  //StacktraceElementJc* stacktraceEntries = ythis->stacktraceEntries;
  //StacktraceJc* stacktrace = ythis->backStacktrace;
  const char* sException = getExceptionText_ExceptionJc(ythis->exceptionNr);

  zBuffer = copyToBuffer_StringJc(ythis->exceptionMsg, 0, -1, sBuffer, sizeof(sBuffer));
  if(out == null)
  { printf("\n%s: %s: %i=0x%8.8X \n",sException, sBuffer, ythis->exceptionValue, ythis->exceptionValue);
  }
  else
  { os_fwrite(out, sException, strlen(sException));
	  os_fwrite(out, ": ", 2);
		os_fwrite(out, sBuffer, zBuffer);
	  zBuffer = snprintf(sBuffer, sizeof(sBuffer), ": %i=0x%8.8X \n",ythis->exceptionValue, ythis->exceptionValue);
		os_fwrite(out, sBuffer, zBuffer);
  }
  //nrofStacktraceEntriesMax = stacktraceEntries == null ? -1 : ythis->nrofStacktraceEntries;
  idxStacktraceEntries = _thCxt->stacktrc.zEntries;
  while(idxStacktraceEntries >=0 ) //< nrofStacktraceEntriesMax)
  { //the entries after try-level
    //StacktraceElementJc* entry = &stacktraceEntries->data[idxStacktraceEntries++];
    StacktraceElementJc* entry = &_thCxt->stacktrc.entries[idxStacktraceEntries--];
    if(out == null)
    { printf("  at %s (%s:%i)\n", entry->name, entry->source, entry->line);
    }
    else
    { zBuffer = snprintf(sBuffer, sizeof(sBuffer), "  at %s (%s:%i)\n", entry->name, entry->source, entry->line);
			os_fwrite(out, sBuffer, zBuffer);
	  }
  }
  #if 0 //TODO
  while(stacktrace != null)
  { //the entries before try-level
    StacktraceElementJc* entry = &stacktrace->entry;
    if(out == null)
    { printf("  at %s (%s:%i)\n", entry->name, entry->source, entry->line);
    }
    else
    { zBuffer = sprintf(sBuffer, "  at %s (%s:%i)\n", entry->name, entry->source, entry->line);
			os_fwrite(out, sBuffer, zBuffer);
    }
    stacktrace = stacktrace->previous;
  }
  #endif
}


void printStackTrace_P_ExceptionJc(struct ExceptionJc_t* ythis, struct PrintStreamJc_t* out, struct ThreadContext_emC_t* _thCxt)
{

}



#endif //not __NOT_SUPPORTED_ThreadContextFw__
