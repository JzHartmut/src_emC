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
 * @content definition of user interface for exception handling
 * @author Jchartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2009-11-25: Hartmut
 *   *new: InterruptedExceptionJc
 *   *corr: NULL_ExceptionJc better written, prevent warning from GNU-cc
 *   *corr: jmpBufferDummies[64]: There is a problem in definition of jmp_buf by any compiler, included dummies.
 *   *corr: TRY {0}-initislization better written, prevent warning from GNU-cc
 * 2008-04-22: Hartmut new: routine to test the consistence of stacktrace.
 * 2007-07-00: Hartmut creation
 *
 ****************************************************************************/

#ifndef __applstdef_emC_h__
  /**This file fw_Exception.h should be included in the applstdef_emC.h. 
   * If this file is directly included, it needs the applstdef_emC.h. But the __fw_Exception_h__ guard should not be set firstly
   * to include the fw_Exception.h in the given order in applstddef.h
   */
  #include <applstdef_emC.h>
#endif

#ifndef __emC_ThreadContext_emC_h__
  //include fw_ThreadContext.h firstly, it includes this file internally.
  //then the guards are defined already.
  #include "emC/ThreadContext_emC.h"
#endif
#ifndef __fw_Exception_h__
#define __fw_Exception_h__

#include <emC/ExceptionDefs_emC.h>
#include <emC/SimpleC_emC.h>

#ifndef __cplusplus
  //For a C compiler, __TRYCPPJc cannot be used.
  #undef __TRYCPPJc
#endif

#ifndef __StringJc_defined__
  //minimalistic definition of StringJc to use this type before including emC/StringJc
  typedef OS_PtrVal_DEF(StringJc, void const);
  #define __StringJc_defined__
#endif //ifdef isNull_StringJc

#include "emC/MemC_emC.h"
#ifndef __TRYCPPJc
  #include <setjmp.h>
#endif

C_TYPE struct OS_HandleFile_t;

/**Forward declaration of struct to prevent warnings. */
struct ThreadContext_emC_t;
struct PrintStreamJc_t;


extern_C void stop_DebugutilJc(struct ThreadContext_emC_t* _thCxt);


/*@CLASS_C ExceptionJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/







#define NULL_ExceptionJc() { 0, NULL_StringJc, 0 }

/**Gets the exception describing text to the number. 
 * This method is called in [[printStackTraceFile_ExceptionJc(...)]] especially.
 * @param exceptionNr: Any bit describes one exception type.
 */
METHOD_C const char* getExceptionText_ExceptionJc(int32 exceptionNr);


/**Javalike: prints the Stacktrace at output stream. */
METHOD_C void printStackTrace_ExceptionJc(ExceptionJc* ythis, struct ThreadContext_emC_t* _thCxt);

METHOD_C void printStackTrace_P_ExceptionJc(ExceptionJc* ythis, struct PrintStreamJc_t* out, struct ThreadContext_emC_t* _thCxt);

/**Javalike: prints the Stacktrace at output stream. 
 * @since 2011-02: The output stream handle is designated as OS_HandleFile.
 * @param out channel, where the outputs should written to. 
 */
METHOD_C void printStackTraceFile_ExceptionJc(ExceptionJc* ythis, struct OS_HandleFile_t* out, ThCxt* _thCxt);

/**Special: manifests the content of the stacktrace to a given structure.
 * It means, all information holded in the stack itself via previous pointers from each StacktraceJc-structure
 * or holded in the stacktrcThCxt is copied to the destination strutures.
 *
 * The element backStacktrace is set to null after this operation,
 *
 * @param dst a provided buffer for the exception or null. If null a new element is allocated in heap.
 * @param dst a provided buffer for the stacktrace or null. If null a new array with the designated length is allocated in heap.
 */
//METHOD_C ExceptionJc* manifest_ExceptionJc(ExceptionJc* ythis, ExceptionJc* dst, struct StacktraceElementJcARRAY_t* dstStacktrace);

/**This routine is called in the THROW processing, if no TRY-level is found. The user should write this method.*/
extern_C void uncatched_ExceptionJc(ExceptionJc* ythis, StacktraceThreadContext_emC_s* _thCxt);
//METHOD_C void uncatchedException(int32 exceptionNr, StringJcRef*  msg, int value, StacktraceThreadContext_emC_s* stacktrcThCxt);

#define getMessage_ExceptionJc(YTHIS, THC) ((YTHIS)->exceptionMsg)


//#define null_ExceptionJc() {0}

/*@CLASS_C TryObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/






typedef struct TryObjectJc_t
{
  /**The exception object here temporary in stack*/
  ExceptionJc exc;
  /**The exceptionNr is set on throw here and in the Exception instance. The exception instance will be unchanged,
   * but this variable is set to 0 if a CATCH BLOCK is detected. 
   * It it is not 0 on END_TRY (note: after FINALY), then the exception will not be handled.
   * With this test the exception is thrown for a maybe existing superior try-catch level. This is the reason for this variable. */
  int32 excNrTestCatch;
  #ifndef __TRYCPPJc
    #ifdef ReflectionHidden 
      /**Buffer for the longjmp mechanism, see standard-C-documentation. Defined in standard-include-file setjmp.h */ 
      jmp_buf longjmpBuffer;
      //int32 jmpBufferDummies[64];  //because Hynet has an internal problem.
    #endif
  #endif

} TryObjectJc;




/*@CLASS_C StacktraceJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct StacktraceJc_t
{ //struct StacktraceJc_t* previous;
  //StacktraceElementJc entry;
  /**The index in the stacktrace entry array for this level. */
  int ix;
  /**The number of Entries of the previous level for STACKTRC_LEAVE. */
  int ixPrev;
  /**Exception-reference if there is an exception, or null */
  //TryObjectJc* tryObject;
} StacktraceJc;




/**This macro defines and initializes the stack variables ,,stacktrace,,.
 * Use the macro ,,STACKTRC_LEAVE;,, at end of the block unconditionally!
 * After the macro in the users call a semicolon should be written.
 */
/* NOTE: The initialization with __FILE__ and __LINE__ must be a part of macro
 * because otherwise it is the fault file and line.
 */
#if defined(__CPLUSGEN) && defined(__cplusplus)
  #define STACKTRC_TENTRY(NAME) \
  if(_thCxt==null){ _thCxt = getCurrent_ThreadContext_emC(); } \
  StacktraceJcpp stacktrace(NAME, _thCxt);\
  stacktrace.entry.source = __FILE__; stacktrace.entry.line = __LINE__; \
  _thCxt->stacktrc.stacktrace = static_cast<StacktraceJc*>(&stacktrace)

#else
  #define STACKTRC_TENTRY(NAME) \
    StacktraceJc stacktrace; \
    if(_thCxt==null){ _thCxt = getCurrent_ThreadContext_emC(); } \
    stacktrace.ixPrev = _thCxt->stacktrc.zEntries; \
    if(_thCxt->stacktrc.zEntries < (ARRAYLEN_SimpleC(_thCxt->stacktrc.entries))) { \
      StacktraceElementJc* stdst; \
      stacktrace.ix = _thCxt->stacktrc.zEntries; \
      _thCxt->stacktrc.zEntries+=1; \
      stdst = &_thCxt->stacktrc.entries[stacktrace.ix]; \
      stdst->name = NAME; stdst->source = __FILE__; stdst->line = __LINE__;  stdst->tryObject = null; \
    } else { /**do nothing special in this error case. */ \
      /**But do not create the index in thread context. */ \
      stacktrace.ix = stacktrace.ixPrev; \
    } 
#endif

/**This macro defines and initializes the stack variable ,,stacktrcThCxt,, and ,,stacktrace,,.
 *
 */

#if defined(__CPLUSGEN) && defined(__cplusplus)
  /**C++-Variant: The StacktraceJcpp with its destructor is used, no STACKTRCE_LEAVE is necessary.
   * After the macro in the users call a semicolon should be written.
  */
  /* NOTE: The initialization with __FILE__ and __LINE__ must be a part of macro
   * because otherwise it is the fault file and line.
   */
  #define STACKTRC_ENTRY(NAME) ThCxt* _thCxt = getCurrent_ThreadContext_emC(); STACKTRC_TENTRY(NAME) 
#else
  /**C-Variant: Use the macro ,,STACKTRC_LEAVE;,, at end of the block unconditionally!*/
  #define STACKTRC_ENTRY(NAME) \
    ThCxt* _thCxt = getCurrent_ThreadContext_emC();  STACKTRC_TENTRY(NAME)
#endif


/**This macro supplies the ,,_thCxt,,-Variable but stores the __LINE__ before.
 * A forgotten ,,STACKTRC_LEAVE,, in a last subroutine will be repaire yet also.
 */
#define THCXT (_thCxt->stacktrc.entries[stacktrace.ix].line=__LINE__, _thCxt->stacktrc.zEntries = stacktrace.ix +1, _thCxt)



/**This macro corrects the chained list of stacktrace, it sets the end of the previous stacktrace.
 * Use this macro unconditionally at end of a block using ,,STACKTRC_ENTRY(),, or ,,STACKTRC_XENTRY(),,.
 * Otherwise the chain of stacktrace elements is corrupted.
 */
#if defined(__CPLUSGEN) && defined(__cplusplus)
  #define STACKTRC_LEAVE
#else
  //#define STACKTRC_LEAVE _thCxt->stacktrc.stacktrace = stacktrace.previous
  //Restore the index in stacktrace.
  #define STACKTRC_LEAVE _thCxt->stacktrc.zEntries = stacktrace.ixPrev
#endif


/**Test the consistence of the stacktrace, useable if errors are searched
 * The compiler switch should be set in the ,,fw_Platform_conventions.h,,
 */
#ifdef TEST_STACKTRCJc
  METHOD_C bool test_StacktraceJc(StacktraceJc* ythis);
#else
  /**Let it empty. */
  #define test_StacktraceJc(ST)
#endif



/**@deprecated. This macro is only present because compatibility with older sources. It is only useable in C++.
 */
#define STACKTRC_ROOT_ENTRY(NAME) STACKTRC_ENTRY(NAME);

/*@CLASS_CPP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#if defined(__CPLUSGEN) && defined(__cplusplus)

class StacktraceJcpp: public StacktraceJc
{
  private: struct ThreadContext_emC_t* threadContext;

  public: StacktraceJcpp(const char* sName, struct ThreadContext_emC_t* stacktrcThCxt = null);

  public: ~StacktraceJcpp();

};




#endif  /*__CPLUSPLUSJcpp*/


/*@DEFINE_C TRYJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



/**TRYJc: Definitions and methods for the TRY-CATCH-THROW-concept in CRuntimeJavalike.
 */ 
/**throws an exception. This method is called directly in a THROW macro. It may be called immediately
 * without an _thCxt if an uncatchable exception occurs.
 * @param stacktrcThCxt if null than the uncatchedException-routine is called.
 */
extern_C void throw_sJc(int32 exceptionNr, StringJc msg, int value, int line, ThCxt* _thCxt);



extern_C void throw_s0Jc(int32 exceptionNr, const char* msg, int value, int line, ThCxt* _thCxt);


METHOD_C void throw_EJc(int32 exceptionNr, ExceptionJc* exc, int value, int line, ThCxt* _thCxt);





//#define CALLINE (stacktrace.entry.line=__LINE__)
#define CALLINE (_thCxt->stacktrc.entries[stacktrace.ix].line=__LINE__)

void XXX_endTryJc(TryObjectJc* tryObject, StacktraceJc* stacktrace, StacktraceThreadContext_emC_s* stacktrcThCxt);




#ifdef __TRYCPPJc
  /**TRY in C++: It is the try statement.
   * The exceptionNr is initialized with ident_SystemExceptionJc.
   * That is because a system exception like memory protection exception does not write
   * to the exceptionnr.
   */
  #define TRY \
  { /*The matching close curly brace is given in the END_TRY at least. */ \
    TryObjectJc tryObject = {NULL_ExceptionJc(), 0}; \
    _thCxt->stacktrc.entries[stacktrace.ix].tryObject = &tryObject; \
    _thCxt->stacktrc.entries[stacktrace.ix].line = __LINE__; \
    try
#else
  /**TRY in C: it sets the [[longjmpBuffer_TryObjectJc]] via invocation of setjmp(...).
   * The invocation of setjmp returns 0, so the execution is continued 
   * in the if(tryObject.exceptionNr==0) { ...branch of execution } 
   * On a longjmp the execution resumes in the setjmp-statements but returns !=0. 
   * Therefore the execution is continued in the else if(...) branches which checks the exception.
   */
  #define TRY \
  { TryObjectJc tryObject = {NULL_ExceptionJc(), 0}; \
    _thCxt->stacktrc.entries[stacktrace.ix].tryObject = &tryObject; \
    _thCxt->stacktrc.entries[stacktrace.ix].line = __LINE__; \
    { tryObject.excNrTestCatch = setjmp(tryObject.longjmpBuffer); \
      if(tryObject.excNrTestCatch==0) \
      {
#endif

//#if defined(_JcPLUSPLUSJcpp) && defined(_Jcplusplus)
/**Write at end of a TRY-Block the followed macro: */
#ifdef __TRYCPPJc
  #define _TRY \
  catch(...) { _thCxt->stacktrc.entries[stacktrace.ix].tryObject = null;  \
  if(tryObject.exc.exceptionNr == 0) { /*if 0, a system has occured:*/ \
    tryObject.exc.exceptionNr = tryObject.excNrTestCatch = ident_SystemExceptionJc;  \
    tryObject.exc.exceptionMsg = z_StringJc("System exception"); \
  }  \
  if(false) { /*opens an empty block, closed on the first CATCH macro. */

#else
  #define _TRY _thCxt->stacktrc.entries[stacktrace.ix].tryObject = null;
#endif


#define CATCH(EXCEPTION, EXC_OBJ) \
    _thCxt->stacktrc.zEntries = stacktrace.ix+1; /*remove stacktrace entries of the deeper levels. */ \
  } else if((tryObject.excNrTestCatch & mask_##EXCEPTION##Jc)!= 0) \
  { ExceptionJc* EXC_OBJ = &tryObject.exc; tryObject.excNrTestCatch = 0;  /*do not check it a second time.*/






#define FINALLY \
  /*remove the validy of stacktrace entries of the deeper levels. */ \
  _thCxt->stacktrc.zEntries = stacktrace.ix+1; \
 } /*close CATCH brace */\
 } /*close brace of whole catch block*/ \
 { { /*open to braces because END_TRY has 2 closing braces.*/



/**Write on end of the whole TRY-CATCH-Block the followed macro:*/
#define END_TRY \
    /*remove the validy of stacktrace entries of the deeper levels. */ \
    _thCxt->stacktrc.zEntries = stacktrace.ix+1; \
   } /*close FINALLY, CATCH or TRY brace */\
  } /*close brace of whole catch block*/ \
  if(tryObject.excNrTestCatch != 0) /*Exception not handled*/ \
  { /* delegate exception to previous level. */ \
   _thCxt->stacktrc.entries[stacktrace.ix].tryObject = null; \
   throw_sJc(tryObject.exc.exceptionNr, tryObject.exc.exceptionMsg, tryObject.exc.exceptionValue, __LINE__, _thCxt); \
  } \
  freeM_MemC(tryObject.exc.exceptionMsg); /*In case it is a allocated one*/ \
  /*remove the validy of stacktrace entries of the deeper levels. */ \
  _thCxt->stacktrc.zEntries = stacktrace.ix+1; \
 } /*close brace from beginning TRY*/


/**Throws an exception.
 * @param EXCPETION ones of the defines in ExceptionIdentsJc, but without ident_ and Jc. It's the same like Exception class names in Java.
 *        example RuntimeException or IndexOutOfBoundsException, see ident_IndexOutOfBoundsExceptionJc
 * @param TEXT type StringJc. To get a StringJc from a string literal, write s0_StringJc("my text")
 * @param VAL a int value
 */
#ifndef THROW
  #define THROW(EXCEPTION, TEXT, VAL)  throw_sJc(ident_##EXCEPTION##Jc, TEXT, VAL, __LINE__, _thCxt)
#endif

#ifndef THROW_s0
  #define THROW_s0(EXCEPTION, TEXT, VAL)  throw_s0Jc(ident_##EXCEPTION##Jc, TEXT, VAL, __LINE__, _thCxt)
#endif

#ifndef THROW_s
  #define THROW_s(EXCEPTION, TEXT, VAL)  throw_sJc(ident_##EXCEPTION##Jc, TEXT, VAL, __LINE__, _thCxt)
#endif



/**Either throws an exception or write an exception information in any logging or debugging system and return with the given value. 
 * This concept supports both, exception handling and system of return values in exception situation.
 */
#define THROWRET(EXCEPTION, TEXT, VAL, RETURN)  { throw_sJc(ident_##EXCEPTION##Jc, TEXT, VAL, __LINE__, _thCxt); return RETURN; }

#define THROWRET_s0(EXCEPTION, TEXT, VAL, RETURN)  { throw_s0Jc(ident_##EXCEPTION##Jc, TEXT, VAL, __LINE__, _thCxt); return RETURN; }

#define THROWRET_s(EXCEPTION, TEXT, VAL, RETURN)  { throw_sJc(ident_##EXCEPTION##Jc, TEXT, VAL, __LINE__, _thCxt); return RETURN; }





/**The access methods to os_ThreadContext should be known from user. 
 * There are not necessary here, but used in macro definitions.
 */
//#include "os/os_ThreadContext.h"

/**The structure of the user ThreadContext, defined for the framework, 
 * should be known from user using this header, Therefore it is included here.
 * It should be contained an element named ,,stacktrc,, 
 * of the here defined type ,,StacktraceThreadContext_emC_s,,. 
 * All other elements are not used here.
 * There are not necessary here, but used in macro definitions.
 */
//#include "emC/ThreadContext_emC.h"

/* OLD:A ThreadContext is necessarry, but it is not defined here.
 * It have to be contained for the Stacktrace theme: 
 * struct StacktraceJc_t* stacktrace; Pointer to the actual stacktrace entry.
 * int32 nrofEntriesStacktraceBuffer; actual nrofEntries in entries
 * struct StacktraceElementJcARRAY_t* buffer; Space for Stacktrace Buffer
 * struct StringBufferJc_t* excMsg; Space for a exception message.
 * The include is only necessary because inline dtor of StacktraceJcpp. 
 * Otherwise the forward declaration is sufficing. 
 * But the OS_ThreadContext should contain only forward declared references,
 * so no additional dependencies are caused.
 * 
 * TODO docu soultion: The OS_ThreadContext shouldn't be known here,
 * It contains some special things and should also known in the implementation of OSAL,
 * that is also the ExceptionJc.c
 * The OS_ThreadContext contains a Stacktrace image, therefore it includes this header.
 */
//#include "OS_ThreadContext.h"  



/*****************************************************************************************/
//compatibility:
#define s0_String_Jc(TEXT) s0_StringJc(TEXT)  //hier kann meist die einfachere Variante THROW_s0(..,"text",..) verwendet werden.


#endif //__fw_Exception_h__
