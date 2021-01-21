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
  #define ARGTYPE_MSG_ExceptionJc void const*    //only possible to use a string literal
#else
  #include <emC/Base/StringBase_emC.h>
  #define ARGTYPE_MSG_ExceptionJc StringJc       //String with char const*, length and some specific bits
#endif

#ifndef DEF_ThreadContext_SIMPLE
  #include <emC/Base/MemC_emC.h>
//  #include <emC/Base/SimpleC_emC.h>
#endif

#ifdef DEF_Exception_longjmp
#include <setjmp.h>
#endif


/**Bit definitions of all error bits.
 * HINT: An enum is used to prevent double definitions of same masks.
 */
typedef enum ExceptionIdentsJc_t
{
  ident_ExceptionJc = 0x00000000
  , ident_RuntimeExceptionJc = 0x00000001
  , ident_ClassCastExceptionJc = 0x00000002
  , ident_NullPointerExceptionJc = 0x00000004
  , ident_IndexOutOfBoundsExceptionJc = 0x00000010
  , ident_ArrayIndexOutOfBoundsExceptionJc = 0x00000020
  , ident_StringIndexOutOfBoundsExceptionJc = 0x00000040
  , ident_ArrayStoreExceptionJc = 0x00000080
  , ident_IllegalArgumentExceptionJc = 0x00000100
  , ident_NumberFormatExceptionJc = 0x00000200
  , ident_IllegalFormatConversionExceptionJc = 0x00000400
  , ident_IllegalAccessExceptionJc = 0x00001000
  , ident_NoSuchElementExceptionJc = 0x00002000
  , ident_IllegalStateExceptionJc = 0x00004000
  , ident_ParseExceptionJc = 0x00008000  //java.text.ParseException

  , ident_NoSuchFieldExceptionJc = 0x00010000
  , ident_InterruptedExceptionJc = 0x00020000
  , ident_UnsupportedEncodingExceptionJc = 0x00100000
  , ident_IOExceptionJc = 0x01000000
  , ident_FileNotFoundExceptionJc = 0x02000000
  , ident_OutOfMemoryErrorJc = 0x40000000
#define ident_SystemExceptionJc            0x80000000  //prevent enum definition warning
}ExceptionIdentsJc;


/**In C: don't different these exceptions: */
#define mask_IllegalFormatPrecisionExceptionJc mask_NumberFormatExceptionJc
#define ident_IllegalFormatPrecisionExceptionJc ident_NumberFormatExceptionJc



/**Bit definitions of all Masks for error bits.
* HINT: An enum is used to prevent double definitions of same masks.
*/
typedef enum ExceptionMasksJc_t
{
  mask_ExceptionJcJc = 0xffffffff
  , mask_ExceptionJc = 0xffffffff
  , mask_RuntimeExceptionJc = 0x0000ffff
  , mask_ClassCastExceptionJc = 0x00000002
  , mask_NullPointerExceptionJc = 0x00000004
  , mask_NoMemoryExceptionJc = 0x00000008

  , mask_IndexOutOfBoundsExceptionJc = 0x00000070
  , mask_ArrayIndexOutOfBoundsExceptionJc = 0x00000020
  , mask_StringIndexOutOfBoundsExceptionJc = 0x00000040
  , mask_ArrayStoreExceptionJc = 0x00000080
  , mask_IllegalArgumentExceptionJc = 0x00001F00
  , mask_NumberFormatExceptionJc = 0x00000200
  , mask_IllegalFormatConversionExceptionJc = 0x00000400
  , mask_IllegalAccessExceptionJc = 0x00001000
  , mask_NoSuchElementExceptionJc = 0x00002000
  , mask_IllegalStateExceptionJc = 0x00004000
  , mask_ParseExceptionJc = 0x00008000

  , mask_NoSuchFieldExceptionJc = 0x00010000
  , mask_InterruptedExceptionJc = 0x00020000
  , mask_UnsupportedEncodingExceptionJc = 0x00100000
  , mask_IOExceptionJc = 0x3F000000
  , mask_FileNotFoundExceptionJc = 0x02000000

  , mask_OutOfMemoryErrorJc = 0x40000000
#define mask_SystemExceptionJc  0x80000000  //prevent enum definition warning
}ExceptionMasksJc;


//New system of range: 
//For leaf exception the range is a enum, it is identically with the nr_
//For group exception the first item is the nr_ExcpetionGroup. The last item is defined as range_ here.
//TODO not really ready yet.
typedef enum ExceptionNrJc_t
{
  nr_ExceptionJc = 1
  , nr_RuntimeExceptionJc = 2
  , nr_ClassCastExceptionJc = 3
  , nr_NullPointerExceptionJc = 4
  , nr_NoMemoryExceptionJc = 5
  , nr_InterruptedExceptionJc = 6

  , nr_IndexOutOfBoundsExceptionJc = 16
  , nr_ArrayIndexOutOfBoundsExceptionJc = 17
  , nr_StringIndexOutOfBoundsExceptionJc = 18
#define range_IndexOutOfBoundsExceptionJc 31
  , nr_ArrayStoreExceptionJc = 32
  , nr_IllegalArgumentExceptionJc = 33
  , nr_NumberFormatExceptionJc = 34
#define range_IllegalArgumentExceptionJc 47

  , nr_IllegalFormatConversionExceptionJc = 0x40
  , nr_IllegalAccessExceptionJc = 0x41
  , nr_NoSuchElementExceptionJc = 0x42
  , nr_IllegalStateExceptionJc = 0x43

  , nr_NoSuchFieldExceptionJc = 0x44
  , nr_ParseExceptionJc = 0x4f           //java.lang.text


  , nr_IOExceptionJc = 0x100
  , nr_FileNotFoundExceptionJc = 0x101
  , nr_UnsupportedEncodingExceptionJc = 0x133
#define range_IOExceptionJc 0x1ff



  , nr_SystemError = 0x4000 
  , nr_SystemExceptionJc = 0x4001  //prevent enum definition warning
  , nr_OutOfMemoryErrorJc = 0x4002
#define range_SystemExceptionJc 0x7fff
#define range_ExceptionJc 0x7fff
}ExceptionNrJc;


typedef enum ExceptionRangeJc_t
{
    range_RuntimeExceptionJc = 2
  , range_ClassCastExceptionJc = 3
  , range_NullPointerExceptionJc = 4
  , range_NoMemoryExceptionJc = 5
  , range_InterruptedExceptionJc = 6

  , range_ArrayIndexOutOfBoundsExceptionJc = 17
  , range_StringIndexOutOfBoundsExceptionJc = 18
  , range_ArrayStoreExceptionJc = 32
  , range_NumberFormatExceptionJc = 34

  , range_IllegalFormatConversionExceptionJc = 0x40
  , range_IllegalAccessExceptionJc = 0x41
  , range_NoSuchElementExceptionJc = 0x42
  , range_IllegalStateExceptionJc = 0x43

  , range_NoSuchFieldExceptionJc = 0x44
  , range_ParseExceptionJc = 0x4f           //java.lang.text


  , range_FileNotFoundExceptionJc = 0x101
  , range_UnsupportedEncodingExceptionJc = 0x133



  , range_SystemError = 0x4000
  , range_OutOfMemoryErrorJc = 0x4002

}ExceptionRangeJc;





/**The Exception data contains all data of exception.
 *
 */
typedef struct ExceptionJc_t
{
  /**Bit mask of the exception. There are a maximum of 32 Exception types. Every Exception is represented by one bit.
  See enum definition of ExceptionMasksJc.
  */
  int32 exceptionNr;

  /**The user value of the exception.
  */
  int32 exceptionValue;
  
  int val2;

  int line;

  char const* file;   //mem boundary pos

  /**The user message of the exception.
  */
  StringJc exceptionMsg;  //note: align-8
  

} ExceptionJc;

#define DEFINED_Exception_emC


#define NULL_ExceptionJc() { 0 }



/**Logs the occurence of an Exception. This routine can be called either if an exception is catched
 * for a special case (expectable exceptions should not logged),
 * or on any exception for a critical sensitive system or while developing, 
 * or if an exception falls to a basicly catch clause. It is a prototype.
 * A template implementation is in .../emc/source/emC_srcApplSpec/applConv/LogException_emC.c. 
 * The string inside exc can be refer in the current stack area. It is copied in a static buffer
 * inside this routine (the implementation should do so!). 
 */
extern_C void log_ExceptionJc(ExceptionJc* exc, char const* sFile, int line);



/**Fills a common text in the buffer. It should contain the exception message, the file and line of the exception 
 * the file and line of this routine (Arguments sFile, line and, if available, information from the thread context. */
extern_C int writeException(char* buffer, int zbuffer, ExceptionJc* exc, char const* sFile, int line, struct ThreadContext_emC_t* _thCxt);




/*@CLASS_C TryObjectJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/





/**A TryObject_emC will be defined stacklocal in the TRY level with name _tryObject_emC. 
 * It contains space for Exception_emC information.
 * The ThreadContext_emC _thCxt->tryObject refers the TryObject_emC for the current TRY level.
 * The reference to the previos TryObject_emC for a superior TRY construct is referenced 
 * by the local stack variable _tryObjectPrev_emC. It is null if no superior TRY exists.
 * It will be restored on END_TRY.    
 */
typedef struct TryObjectJc_t
{
  /**Stores the exception or contains 0. */
  ExceptionJc exc;

  #ifdef DEF_Exception_longjmp
  #ifdef ReflectionHidden 
    /**Buffer for the longjmp mechanism, see standard-C-documentation. Defined in standard-include-file setjmp.h */ 
    jmp_buf longjmpBuffer;
  #endif
  #else //if defined(DEF_ThreadContext_SIMPLE)
    int32 XXXnrNested;
  #endif

} TryObjectJc;




/*@CLASS_C ThreadContext_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@qq*/

/**CLASS_C_Description The Definition of the ThreadContext_emC itself depends on decision of the application. 
 * The headerfile ExeptionSefs_emC.h contains only common valid declarations and definitions.
 */




/**Gets the threadContext in the current state. 
 * A ThreadContext at least in minimalistic form should be existent in any application. 
 * It should hold an thread safe exception number for exception handling (adequate errno of C-Standard, but threadsafe). 
 * For implementations in an simple main / interrupt system see .../emc/source/emC_srcApplSpec/applConv/ThreadContextInterrTpl.c
 * For implementation in multithreading environment with OSAL/os_thread.h capabilities see .../emc/source/emC_srcApplSpec/applConv/ThreadContextInterrTpl.c
 */
//Note: Because of cpp and c may be compiled, it should be unique a C function.
extern_C struct ThreadContext_emC_t* getCurrent_ThreadContext_emC();

void ctor_ThreadContext_emC(struct ThreadContext_emC_t* thiz, void const* topAddrStack);

/**Returns the approximately current size of stack */
int getCurrentStackDepth_ThreadContext_emC(struct ThreadContext_emC_t* thiz);


/**Returns the maximum of approximately current size of stack of this thread */
int getMaxStackDepth_ThreadContext_emC(struct ThreadContext_emC_t* thiz);

//NOTE: Definition of THROW(EXC, TEXT, VAL1, VAL2) can be different in several perculiarities

#define THROW1(EXC, TEXT, VAL) THROW(EXC, TEXT, VAL,0)

#ifdef DEF_NO_StringJcCapabilities
  #define THROW_s0f(EXCEPTION, TEXT, VAL1, VAL2, FILE, LINE)  THROWf(EXCEPTION, TEXT, VAL1, VAL2, FILE, LINE)
  #define THROW_s0(EXCEPTION, TEXT, VAL1, VAL2)  THROW(EXCEPTION, TEXT, VAL1, VAL2)
#else
  #define THROW_s0f(EXCEPTION, TEXT, VAL1, VAL2, FILE, LINE)  THROWf(EXCEPTION, z_StringJc(TEXT), VAL1, VAL2, FILE, LINE)
  #define THROW_s0(EXCEPTION, TEXT, VAL1, VAL2)  THROW(EXCEPTION, z_StringJc(TEXT), VAL1, VAL2)
#endif

#define THROW1_s0(EXC, TEXT, VAL) THROW_s0(EXC, TEXT, VAL,0)

#define THROW_s(EXCEPTION, STRING, VAL1, VAL2) THROW(EXCEPTION, STRING, VAL1, VAL2)

#define STACKTRC_RETURN STACKTRC_LEAVE; return

/**Possibility call throw without STACKTRC(...) designation.
 */
//The THROW... macros expect a variable _ThCxt. It can be null, admissible. 
#define THROW_s0nf(EXCEPTION, MSG, VAL1, VAL2, FILE, LINE)  { ThCxt* _thCxt = null; THROW_s0f(EXCEPTION, MSG, VAL1, VAL2, FILE, LINE); }
#define THROW_s0n(EXCEPTION, MSG, VAL1, VAL2)  { ThCxt* _thCxt = null; ; THROW_s0(EXCEPTION, MSG, VAL1, VAL2); }


/*@CLASS_C LogException_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@qq*/


typedef struct ExceptionStore_t {
  uint32 ctException;
  ExceptionJc first;
  ExceptionJc last;
} ExceptionStore;

//extern_C void logSimple_ExceptionJc(int exc, ARGTYPE_MSG_ExceptionJc msg, int32 value, int val2, char const* file, int line);




/**This struct is one entry in Store_LogException_emC.
 * Any of such an exception store entry has 128 Byte for a 32 bit system, so address calculation may be simple.
 */
typedef struct Entry_LogException_emC_emC_t
{ ExceptionJc exc;
  char const* file;
  int32 line;
  #ifndef DEF_NO_StringJcCapabilities
    /**Because the text in the exc.exceptionMsg may not persistent, it is copied here. */
    char msg[104];
  #endif
} Entry_LogException_emC;


#define SIZEENTRIES_default_ExceptionLogStore 2

/**This struct can be used and is used in .../emc/source/emC_srcApplSpec/applConv/LogException_emC.c
 * as structure to store / log the data of an exception for debugging in runtime and view thrown exception in the memory.
 * It has space for two entries only. To enhance the space, use a combined struct see implementation in LogException_emC.c
 */
typedef struct Store_LogException_emC_t
{ /**For checking correctness: */
  char const* identString;
  /**Maximal number of entries. If more as 10 are necessary, you should write:
   * ExceptionStore_emC exceptionStore = {0};  //(should be static)
   * ExceptionStoredEntry_emC _exceptionStoreMoreEntries_[20] = {0}; //to get 30 entries.
   */
  uint zEntries;
  /**Current number of entries after startup or manual reset.*/
  uint ixEntry;

  /**Only 2 entries are presumed at least. To enhance it add an array of entries immediately after this struct instance. 
   * See  implementation in LogException_emC.c.
   */
  Entry_LogException_emC entries[SIZEENTRIES_default_ExceptionLogStore];
} Store_LogException_emC;


/**Initializer for the ExceptionLogStore_emC*/
#define INIZ_Store_LogException_emC(ENTRIES) { "Store_LogException_emC", ENTRIES + SIZEENTRIES_default_ExceptionLogStore, (uint)(-1) }

/*========== structures only for not SIMPLE thread context =============================================*/
#ifndef DEF_ThreadContext_SIMPLE   //only defined for full ThreadContext


#define DEF_ThreadContextHeap_emC

typedef struct AddrUsed_ThreadContext_emC_t
{ char const* sign;
  MemC used;
} AddrUsed_ThreadContext_emC;




typedef struct UserBufferInThCxt_T {
/**A memory area referenced in the thread context. This area is either initially created or created on demand
* with a default size. It can be used especially for String values or other instances
* which are used only in the tread, returned by reference and immediately used and freed.
*/
MemC bufferAlloc;
//TODO this define in applstdef_emC.h
#define DEF_UserBuffer_ThreadContext_emC

/**Up to 30 used addresses for allocated buffers in thread context.
* The positions in this array refers to the bits from 0...9 in [[ThreadContext_emC_s.bitAddrUsed]].
* If the bit is set, this is the associated memory location for a allocated buffer.
* If the bit is 0 but higher bits are set, this is the gap in the buffer for a freed block. 
* That block is reused if an [[ThreadContext_emC_s.getUserBuffer_ThreadContext_emC(...)]] is called with exactly the same size.
* That is usual if more as one time a block is allocated and freed in a loop.
* If the element contains {0,0} than it is not a gap, and the whole memory till end of [[ThreadContext_emC_s.bufferAlloc]] is available. 
*/
AddrUsed_ThreadContext_emC addrUsed[30];

/**If the bit from 0..29 is set, the address is in use. 0: freed. */
int32 bitAddrUsed;

/**The free address of [[ThreadContext_emC_s.bufferAlloc]]. It is equal the start address if all is free.*/
MemUnit* addrFree;

int16 ixLastAddrUsed;

int16 mode;

#define mOptimizeToString_Mode_ThCxt 0x0001

#define mBufferUsed_Mode_ThCxt 0x0002

#define mCheckBufferUsed_Mode_ThCxt 0x0004

} UserBufferInThCxt_s;



#ifndef DEF_ThreadContext_STACKTRC
  #define DEF_ThreadContext_STACKTRC
#endif

/*@CLASS_C StacktraceElement_emC_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**An element of the stacktrace, 12 Byte for a 32-bit-System, 
 * 6 byte for a 16-bit-system, if char const* references are short. */
typedef struct StacktraceElement_emC_T
{
  const char* name;
  const char* source;
  int line;
} StacktraceElement_emC_s;



/*@CLASS_C StacktraceThreadContext_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**The max. number of stacktrace entries should be defined as constant. It limits the shown stacktrace depth,
* but it doesn't limit the useable stacktrace depth. It is a problem of available memory. It should be not to small.
*/
#define nrofStacktraceEntries_ThreadContexJc 100

struct StacktraceJc_t;

/**This structure is the last part of the ThreadContext and contains the necessary values for handling with Stacktrace.
 */
typedef struct StacktraceThreadContext_emC_t
{
  /**actual nrofEntries in stacktraceBuffer. */
  uint zEntries; 

  /**The available number of Stacktrace entries. */
  uint maxNrofEntriesStacktraceBuffer;

  /**This mask is used for safety operation 
   * if the indices in IxStacktrace_emC are corrupt.
   * This can occure especially in errorneous situations on software development.
   * It simply helps to prevent faulty array accesses.
   * But this mask information should be safe by itself or cyclically checkec
   */
  uint mBitEntriesStacktrc;

  /**Space for Stacktrace Buffer. Should be the last element because of enhancements*/
  StacktraceElement_emC_s entries[128]; 

} StacktraceThreadContext_emC_s;

/**Initializer.
 * @arg SIZE have to be a power of 2! 
   The really number of elements maybe with additional elements.
 */
#define INIZ_StacktraceThreadContext_emC(SIZE) { 0, SIZE, SIZE-1, {0}}



METHOD_C StacktraceThreadContext_emC_s* ctorM_StacktraceThreadContext_emC(MemC mthis);

/**Returns the method name of the requested level.
* @param level 0 is actual, 1... are previous levels.
* @return "" if no previous level is found.
*/
METHOD_C char const* getCallingMethodName_StacktraceThreadContext_emC(StacktraceThreadContext_emC_s* ythis, int level);




#endif //not DEF_ThreadContext_SIMPLE









/*========== ThreadContext_emC_s ============================================================*/

typedef struct ThreadContext_emC_t {
  #ifdef DEF_ThreadContextHeap_emC
  UserBufferInThCxt_s threadheap;
  #endif

  #ifdef USE_BlockHeap_emC
  /**It is the heap, where block heap allocations are provided in this thread. */
  struct BlockHeap_emC_T* blockHeap;
  #endif

  /**The known highest address in the stack. It is the address of the _struct ThreadContext_emC_t* pointer
  * of the first routine, which creates the Thread context.
  */
  MemUnit const* topmemAddrOfStack;

  /**This is the maximal found value of the stack size which is evaluated on [[getCurrentStackDepth_ThreadContext_emC(...)]] . */
  int stacksizeMax;

  /**Reference to the current TryObject in Stack.
  * It is possible to access in deeper stack frames.
  * This reference is removed for the outer stack frames.
  */
  TryObjectJc* tryObject;

  #ifdef DEF_ThreadContext_STACKTRC
  /**Data of the Stacktrace if this concept is used. */
  StacktraceThreadContext_emC_s stacktrc;
  /*IMPORTANT NOTE: The element stacktrc have to be the last because some additional StackEntryJc may be added on end.*/
  #endif

} ThreadContext_emC_s;

#define ThCxt ThreadContext_emC_s

/**Gets the ThreadContext of the current Thread.
 * How it is done depends deeply from the Operation system. Hence it is a function call.
 * It is possible that a simple access to a global pointer is done, possible on non-preemptive threads
 * Or simple interrupt systems. 
 */
#ifndef getCurrent_ThreadContext_emC  //NOTE: may be defined as macro via applstdef_emC.h
extern_C ThreadContext_emC_s* getCurrent_ThreadContext_emC ();
#endif


#ifdef DEF_ThreadContext_SIMPLE

/**Because the operation may use a pointer variable named _thCxt it is defined here.
* But it is initialized with null, because a ThreadContext is unknown, and it is a unknown forward type.
*/
#define STACKTRC_ROOT_ENTRY(NAME) struct ThreadContext_emC_t* _thCxt = getCurrent_ThreadContext_emC(); _thCxt->topmemAddrOfStack = (MemUnit*)&_thCxt 

#define STACKTRC_ROOT_TENTRY(NAME) _thCxt->topmemAddrOfStack = (MemUnit*)&_thCxt

/**For that the _thCxt variable is given in arguments of the operation */
#define STACKTRC_TENTRY(NAME)

/**Because the operation may use a pointer variable named _thCxt it is defined here.
* But it is initialized with null, because a ThreadContext is unknown, and it is a unknown forward type.
*/
#define STACKTRC_ENTRY(NAME) \
  MAYBE_UNUSED_emC struct ThreadContext_emC_t* _thCxt = getCurrent_ThreadContext_emC(); /*It is a variable in Stack. */\
  int stacksize = (int)(((MemUnit*)&_thCxt) - _thCxt->topmemAddrOfStack); \
  if(stacksize <0) { stacksize = -stacksize; } \
  if(stacksize > _thCxt->stacksizeMax) { _thCxt->stacksizeMax = stacksize; } \



#else  //not DEF_ThreadContext_SIMPLE

/**It should be the first invocation of STACKTRC_ENTRY in main or in a thread routine. 
* For this environment it does the same as STACKTRC_ENTRY(NAME). 
*/
#define STACKTRC_ROOT_ENTRY(NAME) STACKTRC_ENTRY(NAME); _thCxt->topmemAddrOfStack = (MemUnit*)&_thCxt


/**This macro defines and initializes the stack variables ,,_ixStacktrace_,,.
* Use the macro ,,STACKTRC_LEAVE;,, at end of the block unconditionally!
* After the macro in the users call a semicolon should be written.
* NOTE: The initialization with __FILE__ and __LINE__ must be a part of macro
* because otherwise it is the fault file and line.
*/
#define STACKTRC_TENTRY(NAME) \
  IxStacktrace_emC _ixStacktrace_; \
  if(_thCxt==null){ _thCxt = getCurrent_ThreadContext_emC(); } \
  _ixStacktrace_.ixStacktracePrev = _thCxt->stacktrc.zEntries; \
  if(_thCxt->stacktrc.zEntries < (ARRAYLEN_emC(_thCxt->stacktrc.entries))) { \
    StacktraceElement_emC_s* stdst; \
    _ixStacktrace_.ixStacktrace = _thCxt->stacktrc.zEntries; \
    _thCxt->stacktrc.zEntries+=1; \
    stdst = &_thCxt->stacktrc.entries[_ixStacktrace_.ixStacktrace]; \
    stdst->name = NAME; stdst->source = __FILE__; stdst->line = __LINE__;  \
  } else { /**do nothing special in this error case. */ \
    /**But do not create the index in thread context. */ \
    _ixStacktrace_.ixStacktrace = _ixStacktrace_.ixStacktracePrev; \
  } 

/**Use the macro ,,STACKTRC_LEAVE;,, at end of the block unconditionally!*/
#define STACKTRC_ENTRY(NAME) ThCxt* _thCxt = getCurrent_ThreadContext_emC();  STACKTRC_TENTRY(NAME)

#endif


#ifdef DEF_ThreadContext_SIMPLE

#define STACKTRC_LEAVE

#define THCXT _thCxt

#define CALLINE

#else  //not DEF_ThreadContext_SIMPLE

/**This macro corrects the chained list of stacktrace, it sets the end of the previous stacktrace.
* Use this macro unconditionally at end of a block using ,,STACKTRC_ENTRY(),, or ,,STACKTRC_XENTRY(),,.
* Otherwise the chain of stacktrace elements is corrupted.
*/
#define STACKTRC_LEAVE _thCxt->stacktrc.zEntries = _ixStacktrace_.ixStacktracePrev

/**This macro supplies the ,,_thCxt,,-Variable but stores the __LINE__ before.
* A forgotten ,,STACKTRC_LEAVE,, in a last subroutine will be repaire yet also.
*/
#define THCXT (_thCxt->stacktrc.entries[_ixStacktrace_.ixStacktrace].line=__LINE__, _thCxt->stacktrc.zEntries = _ixStacktrace_.ixStacktrace +1, _thCxt)

//#define CALLINE(stacktrace.entry.line=__LINE__)
#define CALLINE (_thCxt->stacktrc.entries[_ixStacktrace_.ixStacktrace].line=__LINE__)

#endif  //not DEF_ThreadContext_SIMPLE








#define ADDR_IN_STACK_ThreadContext_emC(ptr) ((MemUnit const*)ptr > (MemUnit const*)&ptr && (MemUnit const*)ptr < _thCxt->topmemAddrOfStack)








#ifndef DEF_ThreadContext_SIMPLE

/**Test the consistence of the stacktrace, useable if errors are searched
* The compiler switch should be set in the ,,fw_Platform_conventions.h,,
*/
#ifdef TEST_STACKTRCJc
METHOD_C bool test_StacktraceJc ( IxStacktrace_emC* ythis);
#else
/**Let it empty. */
#define test_StacktraceJc(ST)

#endif

#endif  //not DEF_ThreadContext_SIMPLE











/*===== Operations for User Buffer ThreadContext ==============================================*/
#ifdef DEF_ThreadContextHeap_emC
//only available on not simple ThreadContext, elsewhere linker error. 
//You cannot use things which are not defined. 

/**Sets a buffer in ThreadContext.
* The buffer may be necessary and filled in inner routines.
* @return the existing buffer. If an existing buffer is to be kept, 
*         the content of the returned buffer should be stored in stack and restore
*         before the calling routine returns. 
*/
METHOD_C MemC setUserBuffer_ThreadContext_emC ( MemC newBuffer, struct ThreadContext_emC_t* _thCxt);

/**Gets a buffer in ThreadContext. 
* This is a special simple way to handle with memory, if no everlastingly allocation is admissible,
* but a buffer should filled and returned inside called routines. 
* It is possible to allocate a buffer more as one time but at maximum 10 buffers are possible.
* That is enough to build string etc. for logging messages, paths etc.
* A buffer can be allocate, freed with [[ThreadContext_emC_s.releaseUserBuffer_ThreadContext_emC(...)]] and allocate with the same size again.
* Then the same position is reused. 
*
* The algorithm used the fields [[ThreadContext_emC_s.addrUsed]] etc.
*
* The buffer may be given by [[ThreadContext_emC_s.setUserBuffer_ThreadContext_emC(...)]] or it is allocated on demand on first usage.
* Because the buffer is stored not globally but thread specific this mechanism is threadsafe, .
* @param size in MemUnit
* @param sign a number to support debugging which part of code has allocated, use a unified number if possible.
* @return null_MemC with length=0 if no buffer is free. The application should deal with this situation.
* NOTE: An exception is not thrown because this is an expectable result. Especially if this routine is used inside an exception handling
*   a simple exception exacerbate the situation.
*/ 
METHOD_C MemC getUserBuffer_ThreadContext_emC ( int size, char const* sign, struct ThreadContext_emC_t* _thCxt);

/**Reduces the size of the last gotten buffer in thread context.
* This routine shall be called immediately after filling the current one buffer, before another buffer is gotten.
* This routine is called in toStringNonPersist_StringBuilderJc(). It is success if it is the last gotten buffer.
* If ptr does not refer the last gotten buffer this routine does nothing.
* Especially if a string is prepared, its length is only given after preparation. Then it is time to set to used size.
* @param ptr To check wheterh it is the last gotten buffer.
* @param size the used size. The rest till the end of the Thread contect buffer area is now free for further buffer. 
*/
METHOD_C void reduceLastUserBuffer_ThreadContext_emC ( void* ptr, int size, struct ThreadContext_emC_t* _thCxt);


/**Sets the mode whether the release of the buffer in ThreadContext is necessary. 
*/ 
METHOD_C bool setCheckingUserBuffer_ThreadContext_emC ( struct ThreadContext_emC_t* _thCxt, bool value);


/**Releases the buffer in ThreadContext. 
*/ 
METHOD_C bool releaseUserBuffer_ThreadContext_emC ( void const* data, struct ThreadContext_emC_t* _thCxt);




/**Allocates an ObjectJc in the thread buffer. Such an instance must be used immediately, then it is similar to an embedded instance in the stack. 
* It can be returned and used in the calling enviroment immediately or return. That is the difference to a embedded instance in the stack.
* Only one instance can be located in the thread context. It is over-written if another instance is created in the thread context.
*/
struct ObjectJc_T* allocInThreadCxt_ObjectJc ( int size, char const* sign, struct ThreadContext_emC_t* _thCxt);




#endif


#ifndef INCLUDED_emC_Base_String_emC_h
//#include <emC/Base/String_emC.h>
#endif



#ifdef DEF_Exception_longjmp
#include <setjmp.h>
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
  #define MSG_SystemException_ExcpetionJc tryObject.exc.exceptionMsg = z_StringJc("System exception");
#endif


 /**Written on end of a TRY-Block the followed macro: */
 #define _TRY \
  EXCEPTION_CATCH { \
    _thCxt->tryObject = tryObjectPrev; \
    if(tryObject.exc.exceptionNr == 0) {/*system Exception:*/ \
      tryObject.exc.exceptionNr = ident_SystemExceptionJc;  \
      MSG_SystemException_ExcpetionJc \
    }  \
    excNrCatchTest = tryObject.exc.exceptionNr; \
    if(false) { /*opens an empty block, closed on first CATCH starts with }*/


 //end of CATCH before: remove _ixStacktrace_ entries of the deeper levels.
 //Note: Till end of catch the stacktrace of the throw level is visible.
 #define CATCH(EXCEPTION, EXC_OBJ) \
      RESTORE_STACKTRACE_DEEPNESS  \
    } else if((excNrCatchTest & mask_##EXCEPTION##Jc)!= 0) \
    { MAYBE_UNUSED_emC ExceptionJc* EXC_OBJ = &tryObject.exc; \
      excNrCatchTest = 0; //do not check it a second time


 #define FINALLY \
      RESTORE_STACKTRACE_DEEPNESS \
  } } /*close CATCH brace */\
  _thCxt->tryObject = tryObjectPrev; \
  { { /*open two braces because END_TRY has 2 closing braces.*/


 //Write on end of the whole TRY-CATCH-Block the followed macro:*/
 #define END_TRY \
  } } /*close FINALLY, CATCH or TRY brace */\
  if( excNrCatchTest != 0 ) /*Exception not handled*/ \
  { /* delegate exception to previous level. */ \
    tryObjectPrev->exc = tryObject.exc; /*Copy all exception info, it's a memcpy*/ \
    _thCxt->tryObject = tryObjectPrev; \
    throwCore_emC(_thCxt); \
  } else { /*remain exception for prev level on throwCore_emC if DEF_Exception_NO */\
    _thCxt->tryObject = tryObjectPrev; \
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
  #e#define THROWf(EXCEPTION, MSG, VAL1, VAL2, FILE, LINE) { if(_thCxt == null) \
    { _thCxt = getCurrent_ThreadContext_emC(); } \
      _thCxt->exception[0].exceptionNr = nr_##EXCEPTION##Jc; \
      _thCxt->exception[0].exceptionValue = VAL1; \
      _thCxt->exception[0].file = FILE; \
      _thCxt->exception[0].line = LINE; \
      log_ExceptionJc(&_thCxt->exception[0], __FILE__, __LINE__); \
    }
  #else //both DEF_Exception_TRYCpp or longjmp:
    #ifdef DEF_NO_StringJcCapabilities
      #define THROWf(EXCEPTION, MSG, VAL1, VAL2, FILE, LINE) \
        throw_sJc(ident_##EXCEPTION##Jc, null, VAL1, FILE, LINE, _thCxt)
      #define THROW(EXCEPTION, MSG, VAL1, VAL2) \
        throw_sJc(ident_##EXCEPTION##Jc, null, VAL1, __FILE__, __LINE__, _thCxt)
    #else
      #define THROWf(EXCEPTION, MSG, VAL1, VAL2, FILE, LINE) \
        throw_sJc(ident_##EXCEPTION##Jc, MSG, VAL1, FILE, LINE, _thCxt)
      #define THROW(EXCEPTION, MSG, VAL1, VAL2) \
        throw_sJc(ident_##EXCEPTION##Jc, MSG, VAL1, __FILE__, __LINE__, _thCxt)
    #endif
  #endif
#endif

#ifndef THROW_s0
  #define THROW_s0f(EXCEPTION, TEXT, VAL1, VAL2, FILE, LINE)  throw_s0Jc(ident_##EXCEPTION##Jc, TEXT, VAL1, FILE, LINE, _thCxt)
  #define THROW_s0(EXCEPTION, TEXT, VAL1, VAL2)  throw_s0Jc(ident_##EXCEPTION##Jc, TEXT, VAL1, __FILE__, __LINE__, _thCxt)
#endif


/**Throws an exception without need of STACKTRC_ENTRY or ThCxt in the given routine.
 * @param EXCPETION ones of the defines in ExceptionIdentsJc, but without ident_ and Jc. It's the same like Exception class names in Java.
 *        example RuntimeException or IndexOutOfBoundsException, see ident_IndexOutOfBoundsExceptionJc
 * @param TEXT as literal
 * @param VAL1, VAL2 two int values
 */
#ifndef THROW_s0n
  #define THROW_s0nf(EXCEPTION, TEXT, VAL1, VAL2, FILE, LINE)  throw_s0Jc(ident_##EXCEPTION##Jc, TEXT, VAL1, FILE, LINE, null)
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
