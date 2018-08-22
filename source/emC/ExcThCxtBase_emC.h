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


#ifndef __ExceptionDefs_emC_h__
#define __ExceptionDefs_emC_h__


#include <emC/String_emC.h>  //StringJc




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

  /**The user message of the exception.
  */
  StringJc exceptionMsg;  //note: align-8

}ExceptionJc;


#define CONST_ExceptionJc(IDENT, MSG, VAL) { ident_##IDENT##Jc, VAL, MSG}


#define NULL_ExceptionJc() { 0, 0, NULL_StringJc}



/**Prototype of a logging routine for exceptions.
 * A template implementation is in .../emc/source/appl_emC/LogException_emC.c. 
 * The string inside exc can be refer in the current stack area. It is copied in a static buffer
 * inside this routine (the implementation should do so!). 
 */
extern_C void log_ExceptionJc(ExceptionJc* exc, char const* sFile, int line);



/*@CLASS_C ThreadContext_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@qq*/

/**CLASS_C_Description The Definition of the ThreadContext_emC itself depends on decision of the application. 
 * The headerfile ExeptionSefs_emC.h contains only common valid declarations and definitions.
 */




/**Gets the threadContext in the current state. 
 * A ThreadContext at least in minimalistic form should be existent in any application. 
 * It should hold an thread safe exception number for exception handling (adequate errno of C-Standard, but threadsafe). 
 * For implementations in an simple main / interrupt system see .../emc/source/appl_emC/ThreadContextInterrTpl.c
 * For implementation in multithreading environment with OSAL/os_thread.h capabilities see .../emc/source/appl_emC/ThreadContextInterrTpl.c
 */
struct ThreadContext_emC_t* getCurrent_ThreadContext_emC();

/**Returns the approximately current size of stack */
int getCurrentStackDepth_ThreadContext_emC(struct ThreadContext_emC_t* thiz);


/**Returns the maximum of approximately current size of stack of this thread */
int getMaxStackDepth_ThreadContext_emC(struct ThreadContext_emC_t* thiz);






/*@CLASS_C LogException_emC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@qq*/

/**This struct is one entry in Store_LogException_emC.
 * Any of such an exception store entry has 128 Byte for a 32 bit system, so address calculation may be simple.
 */
typedef struct Entry_LogException_emC_emC_t
{ ExceptionJc exc;
  char const* file;
  int32 line;
  /**Because the text in the exc.exceptionMsg may not persistent, it is copied here. */
  char msg[104];
} Entry_LogException_emC;


/**This struct can be used and is used in .../emc/source/appl_emC/LogException_emC.c
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
  int32 zEntries;
  /**Current number of entries after startup or manual reset.*/
  int32 ixEntry;

  /**Only 2 entries are presumed at least. To enhance it add an array of entries immediately after this struct instance. 
   * See  implementation in LogException_emC.c.
   */
  Entry_LogException_emC entries[2];
} Store_LogException_emC;


/**Initializer for the ExceptionLogStore_emC*/
#define INIZ_Store_LogException_emC(ENTRIES) { "Store_LogException_emC", ENTRIES + 2, -1, {0} }



#endif //__ExceptionDefs_emC_h__

