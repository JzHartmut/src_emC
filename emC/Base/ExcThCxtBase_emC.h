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
 * 2017-03-25: Hartmut dissolved from fw_Exception.h because that definitions may neccessary in fw_ExcStacktrcNo.h too.
 *
 ****************************************************************************/


#ifndef __emC__ExcThCxtBase_emC_h__
#define __emC__ExcThCxtBase_emC_h__


#ifdef DEF_Exception_longjmp
#include <setjmp.h>
#endif

#ifndef DEF_NO_StringJcCapabilities  //It is possible to renounce usage of StringJc in simple targets.
//  #include <emC/Base/String_emC.h>  //StringJc
#endif
struct ThreadContext_emC_t;


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





/**The Exception data contains all data of exception but references to the stacktrace.
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






typedef struct TryObjectJc_t
{
  #ifdef DEF_Exception_longjmp
  #ifdef ReflectionHidden 
    /**Buffer for the longjmp mechanism, see standard-C-documentation. Defined in standard-include-file setjmp.h */ 
    jmp_buf longjmpBuffer;
  #endif
  #else //if defined(DEF_ThreadContext_SIMPLE)
    int32 nrNested;
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



#endif //__emC__ExcThCxtBase_emC_h__

