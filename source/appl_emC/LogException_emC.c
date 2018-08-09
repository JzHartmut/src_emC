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
* if <emC/ExcStacktrcNo_emC.h> is included.
* It contains a simple mechanism to store thrown errors.
* @author Hartmut Schorrig
*
****************************************************************************/
//Dependencies: needs emC/StringBase_emC.c to link.

#include <applstdef_emC.h>


ExceptionStoredEntry_emC exceptionEntries[100];
ExceptionStore_emC exceptionStore = CONST_ExceptionStore_emC(exceptionEntries);

void log_ExceptionJc(ExceptionJc* exc, char const* sourceFile, int sourceline)
{ int ix = ++exceptionStore.ixEntry;  //should be atomic in multithread
  if( ix >= exceptionStore.zEntries) {
    //overflow:
    exceptionStore.ixEntry = exceptionStore.zEntries; //limit it
  } else {
    //normal:
    ExceptionStoredEntry_emC* e = &exceptionEntries[ix];
    //copy the text in any case.
    copyToBuffer_StringJc(exc->exceptionMsg, 0, -1, e->msg, sizeof(e->msg));
    e->exc = *exc;  //copy of content.
    e->file = sourceFile;
    e->line = sourceline;
  }
}




