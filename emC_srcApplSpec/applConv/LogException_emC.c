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
* @maintainer Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
*
**copyright***************************************************************************************
*
* @content This file should be used for simple target without exception handling
* if <emC_srcApplSpec/applConv/ExcStacktrcNo_emC.h> is included.
* It contains a simple mechanism to store thrown errors.
* @author Hartmut Schorrig
*
****************************************************************************/
//Dependencies: needs emC/StringBase_emC.c to link.

#include <applstdef_emC.h>

#ifndef SIZEENTRIES_ExceptionLogStore
#define SIZEENTRIES_ExceptionLogStore 100
#endif


/**static data of an Exception Log store. 
 * If you use this file as template for an embedded system, you should arrange this data 
 * in an accessible memory area on a known address which can access with debugging instruments
 * (at least poor memory access).  
 */
struct ExceptionLogStore_t {
  Store_LogException_emC head;
  Entry_LogException_emC __additional_exceptionEntries__[SIZEENTRIES_ExceptionLogStore - SIZEENTRIES_default_ExceptionLogStore];
} exceptionStore = { INIZ_Store_LogException_emC(SIZEENTRIES_ExceptionLogStore - SIZEENTRIES_default_ExceptionLogStore), {0} };



/**Implementation of logging. */
void log_ExceptionJc(ExceptionJc* exc, char const* sourceFile, int sourceline)
{ uint ix = ++exceptionStore.head.ixEntry;  //should be atomic in multithread
  if( ix >= exceptionStore.head.zEntries) {
    //overflow:
    exceptionStore.head.ixEntry = exceptionStore.head.zEntries; //limit it
  } else {
    //normal:
    Entry_LogException_emC* e = &exceptionStore.head.entries[ix];
    //copy the text in any case.
    #ifndef DEF_NO_StringJcCapabilities
    copyToBuffer_StringJc(exc->exceptionMsg, 0, -1, e->msg, sizeof(e->msg));
    e->exc.exceptionMsg = zMax_StringJc(e->msg, sizeof(e->msg)); //set the String in the exception to the own copied buffer.
    #endif
    e->exc = *exc;  //copy of content.
    e->file = sourceFile;
    e->line = sourceline;
  }
}




