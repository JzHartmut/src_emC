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

#include <Fwc/fw_Exception.h>
#include <Fwc/fw_ThreadContext.h>
#include <Fwc/fw_SimpleC.h>     //ARRAYLEN
#include <os_error.h>
//#include <fw_Platform_conventions.h>
#include <stdlib.h>

const char* exceptionTexts[33]=
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



StacktraceThreadContext_s* ctorM_StacktraceThreadContext(MemC mthis)
{ StacktraceThreadContext_s* ythis = PTR_MemC(mthis, StacktraceThreadContext_s);

  ythis->maxNrofEntriesStacktraceBuffer = ARRAYLEN(ythis->stacktraceBuffer);
  return ythis;
}


void _endTryJc(TryObjectJc* tryObject, StacktraceJc* stacktrace, StacktraceThreadContext_s* stacktrcThCxt)
{ tryObject->exc.backStacktrace = stacktrace; 
  tryObject->exc.nrofStacktraceEntries = stacktrcThCxt->nrofEntriesStacktraceBuffer; 
  tryObject->exc.stacktraceEntries = stacktrcThCxt->stacktraceBuffer; 
  stacktrace->tryObject = null; 
}


void throw_sJc(int32 exceptionNr, StringJc msg, int value, StacktraceThreadContext_s* stacktrcThCxt, int line)
{ //find stack level with try entry:
  if(stacktrcThCxt != null)
  { StacktraceJc* stacktrace = stacktrcThCxt->stacktrace;
    //StacktraceElementJcARRAY* stacktraceEntriesInThreadContext = stacktrcThCxt->stacktraceBuffer;
    StacktraceElementJc* stacktraceEntriesInThreadContext = stacktrcThCxt->stacktraceBuffer;
    int idxStacktraceEntries = 0;
    int idxStacktraceEntriesMax;
    //idxStacktraceEntriesMax = stacktraceEntriesInThreadContext == null ? -1 : stacktraceEntriesInThreadContext->head.length;
    idxStacktraceEntriesMax = stacktrcThCxt->maxNrofEntriesStacktraceBuffer;
    stacktrace->entry.line = line;
    while
    (  stacktrace != null             //false only if no try-level found, if the end of the stacktrace is reached
    && stacktrace->tryObject == null  //while try-level not reached
    )
    { if(idxStacktraceEntries < idxStacktraceEntriesMax)
      { //fill in infos
        //stacktraceEntriesInThreadContext->data[idxStacktraceEntries] = stacktrace->entry; //NOTE: it is a memcpy.
        stacktraceEntriesInThreadContext[idxStacktraceEntries] = stacktrace->entry; //NOTE: it is a memcpy.
        idxStacktraceEntries += 1;
      }
      stacktrace = stacktrace->previous;
    }
    stacktrcThCxt->stacktrace = stacktrace;  //may be null if no TRYJc-level is found.
    stacktrcThCxt->nrofEntriesStacktraceBuffer = idxStacktraceEntries;
    //
    //the stacktrcThCxt->stacktraceBuffer is filled with the followed levels of Stacktrace,
    //the stacktrace refers the level of the TRY or it is null.
    //
    if(stacktrace != null)
    { //TRY-level is found:
      ExceptionJc* exception = &stacktrace->tryObject->exc;
      stacktrace->tryObject->exceptionNr = stacktrace->tryObject->exc.exceptionNr = exceptionNr;  //for longjmp
      exception->exceptionNr = exceptionNr;
      lightCopy_StringJc(&exception->exceptionMsg, msg);
      exception->exceptionValue = value;
      exception->backStacktrace = stacktrace;
      exception->nrofStacktraceEntries = idxStacktraceEntries;
      exception->stacktraceEntries = stacktraceEntriesInThreadContext;
      //throw exception, use the platform dependend variant.
      #if defined(__TRYCPPJc) //&& defined(__cplusplus)
       throw exceptionNr;
      #else
       longjmp(stacktrace->tryObject->longjmpBuffer, exceptionNr);
      #endif

    }
    else
    { //no TRYJc-level found,
      ExceptionJc exception;
      exception.exceptionNr = exceptionNr;
      lightCopy_StringJc(&exception.exceptionMsg, msg);
      exception.exceptionValue = value;
      exception.backStacktrace = stacktrace;  //it is null!
      exception.nrofStacktraceEntries = idxStacktraceEntries;
      exception.stacktraceEntries = stacktraceEntriesInThreadContext;

      uncatched_ExceptionJc(&exception, stacktrcThCxt);
      exit(255);
    }
  }
  else
  { //no TRYJc-level found,
    ExceptionJc exception;
    exception.exceptionNr = exceptionNr;
    lightCopy_StringJc(&exception.exceptionMsg, msg);
    exception.exceptionValue = value;
    exception.backStacktrace = null;
    exception.nrofStacktraceEntries = 0;
    exception.stacktraceEntries = 0;

    uncatched_ExceptionJc(&exception, stacktrcThCxt);
    exit(255);
  }
}



void throw_s0Jc(int32 exceptionNr, const char* msgP, int value, StacktraceThreadContext_s* stacktrcThCxt, int line)
{ StringJc msg = s0_StringJc(msgP);
  throw_sJc(exceptionNr, msg, value, stacktrcThCxt, line);
}



void throw_EJc(int32 exceptionNr, ExceptionJc* exc, int value, StacktraceThreadContext_s* stacktrcThCxt, int line)
{
  //int exceptionNr = exc->exceptionNr;
  StringJc msg = exc->exceptionMsg;
  //int32 value = exc->exceptionValue;
  throw_sJc(exceptionNr, msg, value, stacktrcThCxt, line);

}



void assertJc(bool condition)
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
static StacktraceJc* getEntry_StacktraceThreadContext(StacktraceThreadContext_s* ythis, int level)
{ 
  StacktraceJc* entry = ythis->stacktrace;
  while(entry != null && --level >=0)
  { entry = entry->previous;
  }
  return entry;  
}




METHOD_C char const* getCallingMethodName_StacktraceThreadContext(StacktraceThreadContext_s* ythis, int level)
{
  StacktraceJc* entry = getEntry_StacktraceThreadContext(ythis, level);
  return (entry == null) ? "" : entry->entry.name; 
}



/**The method test_StacktraceJc should be present always, independent of the setting in the headerfile,
 * Because some objects may be translated with several settings. Therefore undef of macro.
 */
#undef test_StacktraceJc

/**Test the consistence of the stacktrace, useable if errors are searched*/
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




//#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)
#if defined(__CPLUSPLUSJcpp) && defined(__cplusplus)

StacktraceJcpp::StacktraceJcpp(const char* sName, ThreadContextFW_s* _thCxt)
{ if(_thCxt == null) 
  { _thCxt = getCurrent_ThreadContextFW();
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
