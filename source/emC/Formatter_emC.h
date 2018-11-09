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
 * @changes
 * 2011-02-06: method format_Formatter_FW(...). It is able to use immediately with variable arguments.
 * 2010-01-21 Hartmut: Timer functionality moved to an extra include file fw_timeconversions.h
 *
 */
#ifndef __fw_Formatter_h__
#define __fw_Formatter_h__
#include <applstdef_emC.h>
#include <OSAL/os_time.h>
#include <emC/Va_list_emC.h>
#include <emC/String_emC.h>

struct ThreadContext_emC_t;
//#include "emC/LogMessage.h" //only because Va_listFW, TODO

/*@CLASS_C ParseResultPrintfStyle_fwFormatter @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Element of a array of parse results for printf style.
 * It is a union. The common member is specifier. 
 * The element references either a text (specifier == 't') or a argument access.
 */
typedef union ParseResultPrintfStyle_fwFormatter_t
{
  /**If it is a String. */
  struct
  { /**Type of entry. 
     * t if text is present, do not use an argument value.
    */
    int8 specifier;

    /** number of chars for precesion etc, the second number. */
    int8 dummy;
  
    int16 nrofChars;
    char const* text;
    //}value
  } text;
  struct
  { /**Type of entry. 
     * * s const char*
     * * d integer
     */
    int8 specifier;

    /**Default Type of the argument. The type of argument may be determined instead from an extra string.
     */
    int8 argument;
    
    /**Nr of chars of representation. */
    int8 width;
    /**second number of chars for representation. */
    int8 precision;
    /**The argument number*/
    int8 indexArg; 
    /**The time conversion specifier, it specifier is 't' */
    int8 timeSpecifier;
  } value;
  
  
}ParseResultPrintfStyle_fwFormatter;


/**A string literal which designates a variable argument list with information.
 * It contains a type string. This is used as the first value in variable arguments
 */
extern char const typedVaArg_VaArgBuffer[];


/**Parses the printf-style control string.
 * @param dst Array of entries for parts of the control string.
 *        Each %-char, but each constant text too, creates one entry.
 * @param zDst Number of array-elements of dst. If the control-string starts with a '%'
 *        then zDst=1 is admissible. Then only this item is parsed.
 * @param src The control string.
 * @param zSrc in: Number of chars of src, out: Number of parsed chars. 
 *        The number of parsed chars is less than the in-value, if the dst-array contains 
 *        not enaugh elements to store all parse results.
 *        Especially zDst==1, then zSrc returns the number of chars for this only one item.
 *        This feature is new since 2010-06
 * @return number of found entries in dst
 */
METHOD_C int parsePrinfStyleString_fwFormatter(ParseResultPrintfStyle_fwFormatter* dst, int zDst, char const* src, int* zSrc);

/**Returns a string of argument types from given printf-style-string. 
 * This method is necessary especially for routines which processed variable arguments in a special way,
 * but don't use the printf-style format string.
 * @param typeArgs a char[..] to affiliate the type chars.
 * @param zTypeArgs lenght of the char[...]
 * @param text the text containing the type characters in the printf-style.  
 * @return number of type args chars.
 */ 
int detectTypeArgs_fwFormatter(char* typeArgs, int zTypeArgs, StringJc text);


#define toString_Integer_FW toString_int32_emC

/**Produces a String with given format and given values.
 * @param sFormat the format text. It need not be 0-terminated if zFormat is >=0.
 * @param zFormat The length of the format text. If 0 or <=0, then the format text will be accepted as 0-terminated with max 1000 character.
 * @param sBuffer The buffer to write the result into
 * @param zBuffer length of buffer.  
 * @param sTypeArg One character per variable argument which defines the type of it. See [[Va_listFW]] in header fw_Va_list.h.
 * @return Number of written chars in buffer without the terminating 0. A 0 to terminate is written in sBuffer. 
 */
extern_C int format_Formatter_FW(struct ThreadContext_emC_t* _thCxt, const char* sFormat, int zFormat
                                 , char* buffer, int zBuffer, char const* sTypeArg, ...);

/**Produces a String with given format and given values.
 * @param sFormat the format text. It need not be 0-terminated if zFormat is >=0.
 * @param zFormat The length of the format text. If 0 or <=0, then the format text will be accepted as 0-terminated with max 1000 character.
 * @param sBuffer The buffer to write the result into
 * @param zBuffer length of buffer.  
 * @param vargList structure of type and value of variable arguments.
 * @return Number of written chars in buffer without the terminating 0. A 0 to terminate is written in sBuffer. 
 */
extern_C int format_va_arg_Formatter_FW(struct ThreadContext_emC_t* _thCxt, const char* sFormat, int zFormat
                                        , char* buffer, int zBuffer, Va_listFW vargList);


#include <emC/Timeconversions_emC.h>

#endif //__fw_Formatter_h__
