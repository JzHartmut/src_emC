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
 * @maintainer: Hartmut Schorrig, Germany, Pinzberg, www.vishia.org
 *
 **copyright***************************************************************************************
 *
 * @content implementation of routines for exception handling
 *
 * @author Hartmut Schorrig, www.vishia.org
 * @version 0.91
 * list of changes:
 * 2010-01-07: Hartmut chg: printStacktrace in extra file, because maybe differently implementation possible.
 * 2009-11-01: Hartmut: chg: Condition for os_FatalError(-1, "Stacktrace corrupt",,,)
 * 2009-02-05: Hartmut corr: printStackTrace_ExceptionJc, call of printf, not fprintf, any problems with stdout in Windows
 * 2008-04-22: Hartmut new: routine to test the consistence of stacktrace.
 * 2007-07-00: Hartmut creation
 *
 ****************************************************************************/

#include <emC/Exception_emC.h>

#include <emC/String_emC.h>
#ifndef __NOT_SUPPORTED_ExceptionJc__

#include <emC/ThreadContext_emC.h>
#include <emC/SimpleC_emC.h>     //ARRAYLEN
#include <os_error.h>
//#include <fw_Platform_conventions.h>
#include <stdlib.h>

void stop_DebugutilJc DEF(ThreadContext_emC_s* _thCxt){
}



const char* exceptionTexts DEF [33] =
{ "RuntimeException"  //0x0001
, "ClassCastException"   //0x0002
, ""   //0x0004
, ""   //0x0008
, "IndexOutOfBoundsException"   //0x0010
, "ArrayIndexOutOfBoundsException"   //0x0020
, "StringIndexOutOfBoundsException"   //0x0040
, ""   //0x0080
, "IllegalArgumentException"   //0x0100
, "NoSuchElementException"   //0x0200

, "IllegalStateException"   //0x0400
, ""   //0x0800
, ""   //0x1000
, ""   //0x2000
, ""   //0x4000
, ""   //0x8000
, "NoSuchFieldException"   //0x00010000
, ""   //0x00020000
, ""   //0x00040000
, ""   //0x00080000
, ""   //0x00100000
, ""   //0x00200000
, ""   //0x00400000
, ""   //0x00800000
, ""   //0x01000000
, ""   //0x02000000
, ""   //0x04000000
, ""   //0x08000000
, ""   //0x10000000
, ""   //0x20000000
, ""   //0x40000000
, ""   //0x80000000

, "commonException"   //0x0


};




void XXX_endTryJc(TryObjectJc* tryObject, StacktraceJc* stacktrace, StacktraceThreadContext_emC_s* _thCxt)
{ _thCxt->entries[stacktrace->ix].tryObject = null;
}


void throw_sJc (int32 exceptionNr, StringJc msg, int value, int line, ThCxt* _thCxt)
{ //find stack level with try entry:
  if(_thCxt !=null)
  {
    StacktraceThreadContext_emC_s* stacktrcThCxt = &_thCxt->stacktrc;
    StacktraceElementJc* stacktraceEntriesInThreadContext = stacktrcThCxt->entries;
    StacktraceElementJc* stacktraceTry;
    int ixStacktraceEntries = stacktrcThCxt->zEntries-1;
    do {
      stacktraceTry = &stacktrcThCxt->entries[ixStacktraceEntries];
    } while(stacktraceTry->tryObject == null && --ixStacktraceEntries >=0); 
    if(stacktraceTry->tryObject !=null)
    { //TRY-level is found:
      TryObjectJc* tryObject = stacktraceTry->tryObject;
      ExceptionJc* exception = &tryObject->exc;
      tryObject->excNrTestCatch = tryObject->exc.exceptionNr = exceptionNr;  //for longjmp
      exception->exceptionNr = exceptionNr;
      //check the memory area where the msg is stored. Maybe in stack, then copy it.
      MemUnit* addrMsg = PTR_OS_PtrValue(msg, MemUnit);
      if (addrMsg < _thCxt->topmemAddrOfStack && addrMsg >((MemUnit*)&exception)) {
        //The msg is in stack area, copy it in ThreadContext!
        int zMsg = length_StringJc(msg);
        MemC memb = getUserBuffer_ThreadContext_emC(zMsg +1, "throw_sJc", _thCxt);
        char* b = PTR_MemC(memb, char);
        if(b !=null) {
          copyToBuffer_StringJc(msg, 0, -1, b, zMsg);
          exception->exceptionMsg.ref = b;
          exception->exceptionMsg.val = zMsg;
        }
        else {
          exception->exceptionMsg.ref = "unexpected: No space in ThreadCxt";
          exception->exceptionMsg.val = kIs_0_terminated_StringJc;
        }
      }
      else {
        lightCopy_StringJc(&exception->exceptionMsg, msg);
      }
      exception->exceptionValue = value;
      #if defined(__TRYCPPJc) //&& defined(__cplusplus)
       throw exceptionNr;
      #else
       longjmp(stacktraceTry->tryObject->longjmpBuffer, exceptionNr);
      #endif

    }
    else
    { //no TRYJc-level found,
      ExceptionJc exception;
      exception.exceptionNr = exceptionNr;
      lightCopy_StringJc(&exception.exceptionMsg, msg);
      exception.exceptionValue = value;
      uncatched_ExceptionJc(&exception, stacktrcThCxt);
    }
  }
  else
  { //no TRYJc-level found,
    ExceptionJc exception;
    exception.exceptionNr = exceptionNr;
    lightCopy_StringJc(&exception.exceptionMsg, msg);
    exception.exceptionValue = value;
    uncatched_ExceptionJc(&exception, &_thCxt->stacktrc);
  }
}



void throw_s0Jc (int32 exceptionNr, const char* msgP, int value, int line, ThCxt* _thCxt)
{ StringJc msg = s0_StringJc(msgP);
  throw_sJc(exceptionNr, msg, value, line, _thCxt);
}



void throw_EJc (int32 exceptionNr, ExceptionJc* exc, int value, int line, ThCxt* _thCxt)
{
  //int exceptionNr = exc->exceptionNr;
  StringJc msg = exc->exceptionMsg;
  //int32 value = exc->exceptionValue;
  throw_sJc(exceptionNr, msg, value, line, _thCxt);

}



void assertJc (bool condition)
{ if(!condition)
  { STACKTRC_ENTRY("assertJc");
    THROW_s0(RuntimeException, "assertion failed", 0);
  }
}



METHOD_C const char* getExceptionText_ExceptionJc(int32 exceptionNr)
{ int idxText = 0;
  const char* sText;
  if(exceptionNr != 0)
  { while((exceptionNr & 0x00000001) == 0){ exceptionNr >>=1; idxText +=1; }
  }
  else
  { idxText = 32;
  }
  sText = exceptionTexts[idxText];
  return sText;
}



/**Returns the entry of the Stacktrace of the requested level.
 * @param level 0 is actual, 1... are previous levels.
 * @return null if no previous level is found.
 */

static StacktraceElementJc* getEntry_StacktraceThreadContext_emC(StacktraceThreadContext_emC_s* ythis, uint level)
{ 
  if(level < ythis->zEntries) {
    return &ythis->entries[ythis->zEntries - level -1];
  }
  else return null;
  #if 0
  StacktraceJc* entry = ythis->stacktrace;
  while(entry != null && --level >=0)
  { entry = entry->previous;
  }
  return entry; 
  #endif 
}



METHOD_C char const* getCallingMethodName_StacktraceThreadContext_emC(StacktraceThreadContext_emC_s* ythis, int level)
{
  StacktraceElementJc* entry = getEntry_StacktraceThreadContext_emC(ythis, level);
  return (entry == null) ? "" : entry->name; 
}



/**The method test_StacktraceJc should be present always, independent of the setting in the headerfile,
 * Because some objects may be translated with several settings. Therefore undef of macro.
 */
#undef test_StacktraceJc

extern_C bool test_StacktraceJc(StacktraceJc* ythis);


/**Test the consistence of the stacktrace, useable if errors are searched*/
#if 0
bool test_StacktraceJc(StacktraceJc* ythis)
{ bool bCont = true;
  StacktraceJc* stacktrace, *stacktracePrev = null;
  stacktrace = ythis;
  while(bCont)
  { stacktracePrev = stacktrace->previous;
    if(stacktracePrev == null)
    { bCont = false;
    }
    else
    { if(stacktracePrev <= stacktrace)
      { bCont = false;
      }
      else if(stacktracePrev > stacktrace + 0x200000)
      { bCont = false;
      }
      else
      {
        stacktrace = stacktracePrev;
      }
    }
  }
  if(stacktracePrev != null)
  { /**This situation is a correcting-need software error. Therefore a hard stop is forced.
     * The error is mostly a forgotten STACKTRC_LEAVE in a called routine before. 
     * It should be search either with source code review or with debugging the statements before 
     * and checking the content of *_thCxt
     */
    os_FatalError(-1, "Stacktrace corrupt", 0, 0);
  }
  return stacktracePrev == null;
}
#endif



#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

StacktraceJcpp::StacktraceJcpp(const char* sName, ThreadContext_emC_s* _thCxt)
{ if(_thCxt == null) 
  { _thCxt = getCurrent_ThreadContext_emC();
  }
  this->threadContext= _thCxt;  //save it to use in destructor.
  this->entry.name = sName;
  //NOTE: this->entry.line and source should not be set here, see macro STACKTRC_ENTRY in C++-version!
  tryObject = null;
  if(_thCxt != null)
  { //if the threadContext is under construction while calling this routine,
    //it cannot be used.
    this->previous = _thCxt->stacktraceThreadContext.stacktrace;  
    //see macro STACKTRC_ENTRY: stacktrcThCxt->stacktrace = static_cast<StacktraceJc*>(this);
    //NOTE: this is done outside macro STACKTRC_ENTRY to do it in a stable way.
    //NOTE: the user may use the StacktraceJcpp outside its macro STACKTRC_ENTRY or STACKTRC_TENTRY 
  }
}


StacktraceJcpp::~StacktraceJcpp()
{ if(this->threadContext != null) { this->threadContext->stacktraceThreadContext.stacktrace = previous;}
}



#endif

#endif //not __NOT_SUPPORTED_ThreadContext_emC__
