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
 * @content
 *
 * @author Hartmut Schorrig, Pinzberg, Germany
 * @changes
 * 2010-01-21 Hartmut: All accesses to file system uses the OSAL-Layer, OS_HandleFile instead FILE. This was necessary because not any embedded system supports all standard-C-routines.
 *
 * @version 0.83
 */

#include <Jc/FileIoJc.h>


/*@CLASS_C PrintStreamJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct PrintStreamJc_t
{
  ObjectJc object;
  OutputStreamJcREF out;
  //RefAdditionalValuesJc refadd;
}PrintStreamJc;

#ifndef PrintStreamJcREFDEF
  #define PrintStreamJcREFDEF
  typedef TYPE_EnhancedRefJc(PrintStreamJc);
#endif 

METHOD_C void println_z_PrintStreamJc(PrintStreamJc* ythis, const char* text, ThCxt* _thCxt);
METHOD_C void println_c_PrintStreamJc(PrintStreamJc* ythis, CharSeqJc text, ThCxt* _thCxt);
#define println_s_PrintStreamJc(THIZ, STR, THCXT) println_c_PrintStreamJc(THIZ, (STR), THCXT)
METHOD_C void XXXprintln_c_PrintStreamJc(PrintStreamJc* ythis, CharSeqJc text, ThCxt* _thCxt);
METHOD_C void println_u_PrintStreamJc(PrintStreamJc* ythis, struct StringBuilderJc_t* text, ThCxt* _thCxt);
METHOD_C void println_O_PrintStreamJc(PrintStreamJc* ythis, ObjectJc* text, ThCxt* _thCxt);

METHOD_C void print_z_PrintStreamJc(PrintStreamJc* ythis, const char* text, ThCxt* _thCxt);
METHOD_C void print_s_PrintStreamJc(PrintStreamJc* ythis, StringJc text, ThCxt* _thCxt);
METHOD_C void print_c_PrintStreamJc(PrintStreamJc* ythis, CharSeqJc text, ThCxt* _thCxt);
METHOD_C void print_u_PrintStreamJc(PrintStreamJc* ythis, struct StringBuilderJc_t* text, ThCxt* _thCxt);
METHOD_C void print_O_PrintStreamJc(PrintStreamJc* ythis, ObjectJc* text, ThCxt* _thCxt);

METHOD_C void format_z_PrintStreamJc(PrintStreamJc* ythis, const char* text, char const* sVaargs, ...);


