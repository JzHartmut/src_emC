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


#ifndef __fw_ExceptionDefs_h__
#define __fw_ExceptionDefs_h__


#include <emC/String_emC.h>  //StringJc


 /**The Exception data contains all data of exception but references to the stacktrace.
 *
 */
typedef struct ExceptionJc_t
{
  /**Bit mask of the exception. There are a maximum of 32 Exception types. Every Exception is represented by one bit.
  See enum definition of ExceptionMasksJc.
  */
  int32 exceptionNr;

  /**The user message of the exception.
  */
  StringJc exceptionMsg;

  /**The user value of the exception.
  */
  int32 exceptionValue;

}ExceptionJc;


#define CONST_ExceptionJc(IDENT, MSG, VAL) { ident_##IDENT##Jc, MSG, VAL }


extern_C void log_ExceptionJc(ExceptionJc* exc, char const* sFile, int line);

/**This struct can be used and is used in .../emc/sourceSpecials/appl_emC/ExcStacktrcNo_emC.c
 * To store one exception entry for debugging in runtime and view thrown exception in the memory.
 * Any record of such an exception store entry has 128 Byte for a 32 bit system, so address calculation may be simple.
 */
typedef struct ExceptionStoredEntry_emC_t
{ ExceptionJc exc;
  char const* file;
  int32 line;
  /**Because the text in the exc.exceptionMsg may not persistent, it is copied here. */
  char msg[104];
} ExceptionStoredEntry_emC;


/**This struct can be used and is used in .../emc/sourceSpecials/appl_emC/ExcStacktrcNo_emC.c
* To store the data of an exception for debugging in runtime and view thrown exception in the memory.
* Any record of such an exception store entry has 128 Byte for a 32 bit system, so address calculation may be simple.
*/
typedef struct ExceptionStore_emC_t
{ /**For checking correctness: */
  char const* identString;
  /**Maximal number of entries. If more as 10 are necessary, you should write:
   * ExceptionStore_emC exceptionStore = {0};  //(should be static)
   * ExceptionStoredEntry_emC _exceptionStoreMoreEntries_[20] = {0}; //to get 30 entries.
   */
  int32 zEntries;
  /**Current number of entries after startup or manual reset.*/
  int32 ixEntry;
} ExceptionStore_emC;


#define CONST_ExceptionStore_emC(ENTRIES) { "ExceptionStore_emC", ARRAYLEN_emC(ENTRIES), -1 }




/**Bit definitions of all error bits. 
 * HINT: An enum is used to prevent double definitions of same masks.
 */
typedef enum ExceptionIdentsJc_t
{ ident_ExceptionJc                = 0x00000000
, ident_RuntimeExceptionJc         = 0x00000001
, ident_ClassCastExceptionJc       = 0x00000002
, ident_NullPointerExceptionJc     = 0x00000004
, ident_IndexOutOfBoundsExceptionJc=       0x00000010
, ident_ArrayIndexOutOfBoundsExceptionJc = 0x00000020
, ident_StringIndexOutOfBoundsExceptionJc =0x00000040
, ident_ArrayStoreExceptionJc =            0x00000080
, ident_IllegalArgumentExceptionJc =       0x00000100
, ident_NumberFormatExceptionJc =          0x00000200
, ident_IllegalFormatConversionExceptionJc=0x00000400  
, ident_IllegalAccessExceptionJc =         0x00001000
, ident_NoSuchElementExceptionJc =         0x00002000
, ident_IllegalStateExceptionJc =          0x00004000
, ident_ParseExceptionJc =                 0x00008000  //java.text.ParseException

, ident_NoSuchFieldExceptionJc =           0x00010000
, ident_InterruptedExceptionJc =           0x00020000
, ident_UnsupportedEncodingExceptionJc =   0x00100000
, ident_IOExceptionJc =                    0x01000000  
, ident_FileNotFoundExceptionJc =          0x02000000  
, ident_OutOfMemoryErrorJc =               0x40000000
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
  mask_ExceptionJcJc                 = 0xffffffff
, mask_ExceptionJc                 = 0xffffffff
, mask_RuntimeExceptionJc          = 0x0000ffff
, mask_ClassCastExceptionJc        = 0x00000002
, mask_NullPointerExceptionJc      = 0x00000004
, mask_NoMemoryExceptionJc        = 0x00000008

, mask_IndexOutOfBoundsExceptionJc =      0x00000070
, mask_ArrayIndexOutOfBoundsExceptionJc = 0x00000020
, mask_StringIndexOutOfBoundsExceptionJc =0x00000040
, mask_ArrayStoreExceptionJc =            0x00000080
, mask_IllegalArgumentExceptionJc =       0x00001F00
, mask_NumberFormatExceptionJc =          0x00000200
, mask_IllegalFormatConversionExceptionJc=0x00000400
, mask_IllegalAccessExceptionJc =         0x00001000
, mask_NoSuchElementExceptionJc =         0x00002000
, mask_IllegalStateExceptionJc =          0x00004000
, mask_ParseExceptionJc =                 0x00008000

, mask_NoSuchFieldExceptionJc =           0x00010000
, mask_InterruptedExceptionJc =           0x00020000
, mask_UnsupportedEncodingExceptionJc =   0x00100000
, mask_IOExceptionJc =                    0x3F000000  
, mask_FileNotFoundExceptionJc =          0x02000000  

, mask_OutOfMemoryErrorJc =               0x40000000  
#define mask_SystemExceptionJc  0x80000000  //prevent enum definition warning
}ExceptionMasksJc;





#endif //__fw_ExceptionDefs_h__

