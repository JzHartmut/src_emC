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

#ifndef HGUARD_applstdef_emC
  /**This file fw_Exception.h should be included in the applstdef_emC.h. 
   * If this file is directly included, it needs the applstdef_emC.h. 
   * But the HGUARD_emC_Base_Exception_emC guard should not be set firstly
   * to include the fw_Exception.h in the given order in applstddef.h
   */
  #include <applstdef_emC.h>
#endif

#ifndef HGUARD_emC_Base_Exception_emC
#define HGUARD_emC_Base_Exception_emC


#if !defined(DEF_Exception_longjmp) && !defined(DEF_Exception_NO) && !defined(DEF_Exception_TRYCpp)
#  define   DEF_Exception_TRYCpp
#endif

#if !defined(__cplusplus) && defined(DEF_Exception_TRYCpp)
  //for C-compiled sources TRYCpp cannot be used, then SIMPLE only for C sources.
#  undef DEF_Exception_TRYJcpp
#  define DEF_Exception_NO
#endif

//#error Exception_emC.h A

#ifdef DEF_NO_StringJcCapabilities
  #define ARGTYPE_MSG_ExceptionJc void const*
#else
  #include <emC/Base/StringBase_emC.h>
  #define ARGTYPE_MSG_ExceptionJc StringJc
#endif



#include <emC/Base/ExcThCxtBase_emC.h>
//#include <emC/Base/SimpleC_emC.h>
#include <emC/Base/ExcThreadCxt_emC.h>


#ifndef INCLUDED_emC_Base_String_emC_h
//#include <emC/Base/String_emC.h>
#endif


struct OS_HandleFile_t;

/**Forward declaration of struct to prevent warnings. */
struct ThreadContext_emC_t;
struct PrintStreamJc_t;


//extern_C void stop_DebugutilJc ( struct ThreadContext_emC_t* _thCxt);


/*@CLASS_C ExceptionJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**CLASS_C_Description Defintion in ExcThCxtBase_emC.h */





/**Gets the exception describing text to the number. 
 * This method is called in [[printStackTraceFile_ExceptionJc ( ...)]] especially.
 * @param exceptionNr: Any bit describes one exception type.
 */
extern_C const char* getExceptionText_ExceptionJc ( int32 exceptionNr);


/**Javalike: prints the Stacktrace at output stream. */
extern_C void printStackTrace_ExceptionJc ( ExceptionJc* ythis, struct ThreadContext_emC_t* _thCxt);

extern_C void printStackTrace_P_ExceptionJc ( ExceptionJc* ythis, struct PrintStreamJc_t* out, struct ThreadContext_emC_t* _thCxt);

/**Javalike: prints the Stacktrace at output stream. 
 * @since 2011-02: The output stream handle is designated as OS_HandleFile.
 * @param out channel, where the outputs should written to. 
 */
extern_C void printStackTraceFile_ExceptionJc ( ExceptionJc* ythis, struct OS_HandleFile_t* out, ThCxt* _thCxt);

/**Special: manifests the content of the stacktrace to a given structure.
 * It means, all information holded in the stack itself via previous pointers from each IxStacktrace_emC-structure
 * or holded in the stacktrcThCxt is copied to the destination strutures.
 *
 * The element backStacktrace is set to null after this operation,
 *
 * @param dst a provided buffer for the exception or null. If null a new element is allocated in heap.
 * @param dst a provided buffer for the stacktrace or null. If null a new array with the designated length is allocated in heap.
 */
//extern_C ExceptionJc* manifest_ExceptionJc ( ExceptionJc* ythis, ExceptionJc* dst, struct StacktraceElementJcARRAY_t* dstStacktrace);

/**This routine is called in the THROW processing, if no TRY-level is found. The user should write this method.*/

extern_C void uncatched_ExceptionJc  (  ExceptionJc* ythis, ThreadContext_emC_s* _thCxt);
//extern_C void uncatchedException ( int32 exceptionNr, StringJcRef*  msg, int value, StacktraceThreadContext_emC_s* stacktrcThCxt);

#define getMessage_ExceptionJc(YTHIS, THC) ((YTHIS)->exceptionMsg)


/**This is a message on start of threads, essential os calls etc. which prevent running of the system. 
 * It can replace the uncatched_ExceptionJc(), to simplificate the user necessities. 
 */
extern_C void errorSystem_emC_  (  int errorCode, const char* description, int value1, int value2, char const* file, int line);
#define ERROR_SYSTEM_emC(ERR, TEXT, VAL1, VAL2) errorSystem_emC_(ERR, TEXT, VAL1, VAL2, __FILE__, __LINE__)

//#define null_ExceptionJc() {0}

/*@CLASS_C IxStacktrace_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**An instance of this struct is used for any stack frame level in the STACKTRC_TENTRY macro.
 * It is necessary to restore the correct Stacktrace index on THROW. */
typedef struct IxStacktrace_emC_t
{ /**The index in the stacktrace entry array for this level. */
  uint ixStacktrace;
  /**The number of Entries of the previous level for STACKTRC_LEAVE. */
  uint ixStacktracePrev;
} IxStacktrace_emC;




/**This macro defines and initializes the stack variable ,,stacktrcThCxt,, and ,,_ixStacktrace_,,.
 *
 */



/*@CLASS_CPP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/



#if defined(__CPLUSGEN) && defined(__cplusplus)

class StacktraceJcpp: public IxStacktrace_emC
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
extern_C void throw_sJc ( int32 exceptionNr, ARGTYPE_MSG_ExceptionJc msg, int value, char const* file, int line, ThCxt* _thCxt);



extern_C void throw_s0Jc ( int32 exceptionNr, const char* msg, int value, char const* file, int line, ThCxt* _thCxt);


extern_C void throw_EJc ( int32 exceptionNr, ExceptionJc* exc, int value, char const* file, int line, ThCxt* _thCxt);



extern_C void throwCore_emC(ThCxt* _thCxt);

extern_C void clearException(ExceptionJc* exc);





#if defined(DEF_Exception_NO)
  #define EXCEPTION_TRY
  #define EXCEPTION_CATCH if(_thCxt->exception[0].exceptionNr !=0)
#elif defined(DEF_Exception_longjmp)
  #define EXCEPTION_TRY \
  if( setjmp(tryObject.longjmpBuffer) ==0) {
  #define EXCEPTION_CATCH \
   } else  /*longjmp cames to here on THROW */
#else
  #define EXCEPTION_TRY try
  #define EXCEPTION_CATCH catch(...)
#endif


#ifdef DEF_ThreadContext_SIMPLE
  #define RESTORE_STACKTRACE_DEEPNESS
#else 
  /**remove the validy of _ixStacktrace_ entries of the deeper levels. */
  #define RESTORE_STACKTRACE_DEEPNESS _thCxt->stacktrc.zEntries = _ixStacktrace_.ixStacktrace+1;
#endif

 #define TRY \
 {if(_thCxt == null) { _thCxt = getCurrent_ThreadContext_emC(); } \
  TryObjectJc tryObject = {0}; \
  TryObjectJc* tryObjectPrev = _thCxt->tryObject; _thCxt->tryObject = &tryObject; \
  int32 excNrCatchTest = 0; \
  CALLINE; \
  EXCEPTION_TRY


#ifdef DEF_NO_StringJcCapabilities
  #define MSG_SystemException_ExcpetionJc
#else
  #define MSG_SystemException_ExcpetionJc _thCxt->exception[0].exceptionMsg = z_StringJc("System exception");
#endif


 /**Written on end of a TRY-Block the followed macro: */
 #define _TRY \
  EXCEPTION_CATCH { \
    _thCxt->tryObject = tryObjectPrev; \
    if(_thCxt->exception[0].exceptionNr == 0) {/*system Exception:*/ \
      _thCxt->exception[0].exceptionNr = ident_SystemExceptionJc;  \
      MSG_SystemException_ExcpetionJc \
    }  \
    excNrCatchTest = _thCxt->exception[0].exceptionNr; \
    if(false) { /*opens an empty block, closed on first CATCH starts with }*/


 //end of CATCH before: remove _ixStacktrace_ entries of the deeper levels.
 //Note: Till end of catch the stacktrace of the throw level is visible.
 #define CATCH(EXCEPTION, EXC_OBJ) \
      RESTORE_STACKTRACE_DEEPNESS  \
    } else if((excNrCatchTest & mask_##EXCEPTION##Jc)!= 0) \
    { MAYBE_UNUSED_emC ExceptionJc* EXC_OBJ = &_thCxt->exception[0]; \
      excNrCatchTest = 0; //do not check it a second time


 #define FINALLY \
      RESTORE_STACKTRACE_DEEPNESS \
  } } /*close CATCH brace */\
  _thCxt->tryObject = tryObjectPrev; \
  { { /*open two braces because END_TRY has 2 closing braces.*/


 //Write on end of the whole TRY-CATCH-Block the followed macro:*/
 #define END_TRY \
  } } /*close FINALLY, CATCH or TRY brace */\
  _thCxt->tryObject = tryObjectPrev; \
  if( excNrCatchTest != 0 ) /*Exception not handled*/ \
  { /* delegate exception to previous level. */ \
    throwCore_emC(_thCxt); \
  } else { /*remain exception for prev level on throwCore_emC if DEF_Exception_NO */\
    clearException(&_thCxt->exception[0]); \
  } /*remove the validy of _ixStacktrace_ entries of the deeper levels. */ \
  RESTORE_STACKTRACE_DEEPNESS \
 } /*close brace from beginning TRY*/



/**Throws an exception.
 * @param EXCPETION ones of the defines in ExceptionIdentsJc, but without ident_ and Jc. It's the same like Exception class names in Java.
 *        example RuntimeException or IndexOutOfBoundsException, see ident_IndexOutOfBoundsExceptionJc
 * @param TEXT type StringJc. To get a StringJc from a string literal, write s0_StringJc("my text")
 * @param VAL a int value
 */
#ifndef THROW
  #ifdef DEF_Exception_NO
     /**All THROW() macros writes the exception into the ThreadContext_emC,
      * but the calling routine is continued.
      * It should check itself for sufficient conditions to work.
      */
    #define THROW(EXCEPTION, MSG, VAL1, VAL2) { if(_thCxt == null) \
    { _thCxt = getCurrent_ThreadContext_emC(); } \
      _thCxt->exception[0].exceptionNr = nr_##EXCEPTION##Jc; \
      _thCxt->exception[0].exceptionValue = VAL1; \
      _thCxt->exception[0].file = __FILE__; \
      _thCxt->exception[0].line = __LINE__; \
      log_ExceptionJc(&_thCxt->exception[0], __FILE__, __LINE__); \
    }
  #else //both DEF_Exception_TRYCpp or longjmp:
    #ifdef DEF_NO_StringJcCapabilities
      #define THROW(EXCEPTION, MSG, VAL1, VAL2) \
        throw_sJc(ident_##EXCEPTION##Jc, null, VAL1, __FILE__, __LINE__, _thCxt)
    #else
      #define THROW(EXCEPTION, MSG, VAL1, VAL2) \
        throw_sJc(ident_##EXCEPTION##Jc, MSG, VAL1, __FILE__, __LINE__, _thCxt)
    #endif
  #endif
#endif

#ifndef THROW_s0
  #define THROW_s0(EXCEPTION, TEXT, VAL1, VAL2)  throw_s0Jc(ident_##EXCEPTION##Jc, TEXT, VAL1, __FILE__, __LINE__, _thCxt)
#endif


/**Throws an exception without need of STACKTRC_ENTRY or ThCxt in the given routine.
 * @param EXCPETION ones of the defines in ExceptionIdentsJc, but without ident_ and Jc. It's the same like Exception class names in Java.
 *        example RuntimeException or IndexOutOfBoundsException, see ident_IndexOutOfBoundsExceptionJc
 * @param TEXT as literal
 * @param VAL1, VAL2 two int values
 */
#ifndef THROW_s0n
  #define THROW_s0n(EXCEPTION, TEXT, VAL1, VAL2)  throw_s0Jc(ident_##EXCEPTION##Jc, TEXT, VAL1, __FILE__, __LINE__, null)
#endif





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
#define s0_String_Jc(TEXT) s0_StringJc(TEXT)  //hier kann meist die einfachere Variante THROW1_s0(..,"text",..) verwendet werden.


#endif //HGUARD_emC_Base_Exception_emC
