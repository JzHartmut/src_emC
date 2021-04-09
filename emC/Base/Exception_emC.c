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
 * 2009-02-05: Hartmut corr: printStackTrace_Exception_emC, call of printf, not fprintf, any problems with stdout in Windows
 * 2008-04-22: Hartmut new: routine to test the consistence of stacktrace.
 * 2007-07-00: Hartmut creation
 *
 ****************************************************************************/

#include <applstdef_emC.h>

//Check if DEF_Exception_TRYCpp is set it needs C++ compilation.
//Then this file is included in compilation of ExceptionCpp_emC.cpp to assert C++ compilation anyway. 
//
#if !defined(DEF_Exception_TRYCpp) || defined(DEF_ExceptionCpp_INCLUDED)

#include <emC/Base/Exception_emC.h>

#ifndef DEF_NO_StringJcCapabilities
  #include <emC/Base/StringBase_emC.h>
  #include <emC/Base/MemC_emC.h>
#endif

#ifdef DEF_Exception_emC_NO

int writeException(char* buffer, int zbuffer, Exception_emC* exc, char const* sFile, int line, ThCxt* _thCxt)
{
  return 0;
}

#else //not DEF_Exception_emC_NO

//#include <emC/Base/SimpleC_emC.h>     //ARRAYLEN
//#include <emC/OSAL/os_error.h>
//#include <fw_Platform_conventions.h>
//#include <stdlib.h>

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


void throw_sJc (int32 exceptionNr, ARGTYPE_MSG_Exception_emC msg, int value, char const* file, int line, ThCxt* _thCxt)
{ //find stack level with try entry:
  if(_thCxt ==null) { _thCxt = getCurrent_ThreadContext_emC(); }
  Exception_emC* exception = &_thCxt->tryObject->exc;        //locate in stack of the try level.
  exception->file = file;
  exception->line = line;
  exception->exceptionNr = exceptionNr;
  //check the memory area where the msg is stored. Maybe in stack, then copy it.
  #ifndef DEF_NO_StringJcCapabilities
  MemUnit* addrMsg = (MemUnit*)msg.addr.str;
  if (addrMsg < _thCxt->topmemAddrOfStack && addrMsg >((MemUnit*)&exception)) {
    //The msg is in stack area, copy it in ThreadContext!
    int zMsg = length_StringJc(msg);
    if(zMsg >0){
      #ifdef DEF_ThreadContext_HEAP_emC
        MemC memb = getUserBuffer_ThreadContext_emC(zMsg +1, "throw_sJc", _thCxt);
        char* b = PTR_MemC(memb, char);
        if(b !=null) {
          copyToBuffer_StringJc(msg, 0, -1, b, zMsg);
          SET_StringJc(exception->exceptionMsg, b, zMsg);
        }
        else {
          exception->exceptionMsg = z_StringJc("unexpected: No space in ThreadCxt");
        }
      #else //no DEF_ThreadContext_HEAP_emC
        exception->exceptionMsg = z_StringJc("Exception message in stack, but no ThreadHeap, cannot be used.");
      #endif
    }
  }
  else {
    lightCopy_StringJc(&exception->exceptionMsg, msg);
  }
  #endif
  exception->exceptionValue = value;
  throwCore_emC(_thCxt);
}


void throwCore_emC(ThCxt* _thCxt) {

  if(_thCxt->tryObject !=null) {
    //tryObject->excNrTestCatch = exception->exceptionNr;
    #ifdef DEF_Exception_NO
      //Only log, the program continues after THROW
      //Note: The compilation does not call this operation because THROW is defined
      //with immediately call of log_Exception usually
      log_Exception_emC(&_thCxt->tryObject->exc, _thCxt->tryObject->exc.file, _thCxt->tryObject->exc.line);
    #elif defined(DEF_Exception_TRYCpp) || defined(DEF_Exception_TRYCpp)
      #ifndef __cplusplus
        #error to use C++ exception handing you should compile this source with C++
      #endif
      throw _thCxt->tryObject->exc.exceptionNr;
    #else
      longjmp(_thCxt->tryObject->longjmpBuffer, _thCxt->tryObject->exc.exceptionNr);
    #endif

  }
  else
  { //no TRYJc-level found,
    uncatched_Exception_emC(&_thCxt->tryObject->exc, _thCxt);
  }
}


void throw_s0Jc ( int32 exceptionNr, const char* msgP, int value, char const* file, int line, ThCxt* _thCxt)
{
  #ifndef DEF_NO_StringJcCapabilities
    StringJc msg = s0_StringJc(msgP);
  #else
    char const* msg = msgP;
  #endif
  throw_sJc(exceptionNr, msg, value, file, line, _thCxt);
}


void throw_EJc ( int32 exceptionNr, Exception_emC* exc, int value, char const* file, int line, ThCxt* _thCxt)
{
  //int exceptionNr = exc->exceptionNr;
  #ifdef DEF_NO_StringJcCapabilities
    void const* msg = null;
  #else
    StringJc msg = exc->exceptionMsg;
  #endif
    //int32 value = exc->exceptionValue;
  throw_sJc(exceptionNr, msg, value, file, line, _thCxt);

}



void clearException ( Exception_emC* exc) {
  #ifndef DEF_NO_StringJcCapabilities
  if(exc->exceptionMsg.addr.str!=null) { free_MemC(exc->exceptionMsg.addr.str); }
  #endif
  exc->exceptionNr = 0;
  exc->exceptionValue = 0;
  exc->val2 = 0;
  exc->file = null;
  exc->line = 0;
}



void assertJc (bool condition)
{ if(!condition)
  { STACKTRC_ENTRY("assertJc");
    THROW1_s0(RuntimeException, "assertion failed", 0);
  }
}



const char* getExceptionText_Exception_emC(int32 exceptionNr)
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


#ifndef DEF_NO_StringJcCapabilities
int writeException(char* buffer, int zbuffer, Exception_emC* exc, char const* sFile, int line, ThCxt* _thCxt)
{
  if(zbuffer == 0) { return 0; }
  zbuffer -=2; //append a \n\0 in any case.
  int pos = 0;
  pos += copyToBuffer_StringJc(exc->exceptionMsg, 0, -1, buffer + pos, zbuffer - pos);
  pos += strncpy_emC(buffer+pos, "(", zbuffer - pos);
  pos += toString_int32_emC(buffer + pos, zbuffer - pos, exc->exceptionValue, 10, 0);
  pos += strncpy_emC(buffer+pos, ", ", zbuffer - pos);
  pos += toString_int32_emC(buffer + pos, zbuffer - pos, exc->val2, 10, 0);
  pos += strncpy_emC(buffer + pos, ") in: ", zbuffer - pos);
  if(exc->file !=null) {
    pos += strncpy_emC(buffer + pos, exc->file, zbuffer - pos);  //The routine where the throw is invoked or the deepest routine with Stacktrace.
    pos += strncpy_emC(buffer + pos, "@", zbuffer - pos);
    pos += toString_int32_emC(buffer + pos, zbuffer - pos, exc->line, 10, 0);
  }
  #ifdef DEF_ThreadContext_STACKTRC
  if (_thCxt != null) {
    int ixThrow = _thCxt->stacktrc.zEntries - 1;
    StacktraceElement_emC_s* stackThrow = &_thCxt->stacktrc.entries[ixThrow];
    pos += strncpy_emC(buffer + pos, ", oper: ", zbuffer - pos);
    pos += strncpy_emC(buffer + pos, stackThrow->name, zbuffer - pos);  //The routine where the throw is invoked or the deepest routine with Stacktrace.
    pos += strncpy_emC(buffer + pos, "(@", zbuffer - pos);
    pos += toString_int32_emC(buffer + pos, zbuffer - pos, stackThrow->line, 10, 0);
    pos += strncpy_emC(buffer + pos, ")", zbuffer - pos);
  }
  #endif //DEF_ThreadContext_STACKTRC
  pos += strncpy_emC(buffer + pos, ", detect in: ", zbuffer - pos);
  pos += strncpy_emC(buffer + pos, sFile, zbuffer - pos);
  pos += strncpy_emC(buffer + pos, "@", zbuffer - pos);
  pos += toString_int32_emC(buffer + pos, zbuffer - pos, line, 10, 0);
  buffer[pos++] = '\n';  //terminating 0
  buffer[pos] = 0;  //terminating 0
  return pos;
}
#endif



#ifdef DEF_ThreadContext_STACKTRC
/**Returns the entry of the Stacktrace of the requested level.
 * @param level 0 is actual, 1... are previous levels.
 * @return null if no previous level is found.
 */

static StacktraceElement_emC_s* getEntry_StacktraceThreadContext_emC(StacktraceThreadContext_emC_s* ythis, uint level)
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
  StacktraceElement_emC_s* entry = getEntry_StacktraceThreadContext_emC(ythis, level);
  return (entry == null) ? "" : entry->name; 
}
#endif  //DEF_ThreadContext_STACKTRC



/**The method test_StacktraceJc should be present always, independent of the setting in the headerfile,
 * Because some objects may be translated with several settings. Therefore undef of macro.
 */
#undef test_StacktraceJc

#ifdef DEF_ThreadContext_STACKTRC

extern_C bool test_StacktraceJc(IxStacktrace_emC* ythis);
#endif //DEF_ThreadContext_STACKTRC


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




#endif //not __NOT_SUPPORTED_ThreadContext_emC__

#endif //__cplusplus or DEF_ExceptionCpp_INCLUDED
