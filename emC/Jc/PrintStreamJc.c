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
 *
 * @version 0.94
 *
 * @content like java.io.PrintStream.
 *
 *
 * @author JcHartmut www.vishia.org
 * @version 0.83
 * list of changes:
 * 2007-05-00: JcHartmut creation
 *
 ****************************************************************************/
#include <applstdef_emC.h>
#if !defined(DEF_ObjectSimple_emC) && !defined(DEF_NO_ObjectJc_emC) && !defined(DEF_NO_StringUSAGE)

#include "emC/Jc/PrintStreamJc.h"
#include "emC/Jc/FileIoJc.h"
#include <emC/Jc/StringJc.h>



#include <string.h>
#include <stdarg.h>
#include <stdio.h>




/**premilinary implementation, console output.
 * TODO: PrintStream extends ....
 */
void println_z_PrintStreamJc(PrintStreamJc* ythis, const char* text, ThCxt* _thCxt)
{ 
  printf("%s\n", text);
}


/**premilinary implementation, console output.
 * TODO: PrintStream extends ....
 */
void print_z_PrintStreamJc(PrintStreamJc* ythis, const char* text, ThCxt* _thCxt)
{ 
  printf("%s", text);
}


void format_z_PrintStreamJc(PrintStreamJc* ythis, const char* text, char const* sVaargs, ...)
{
  va_list vaargs;
  va_start(vaargs, sVaargs);
  vprintf(text, vaargs);
}


void println_c_PrintStreamJc(PrintStreamJc* ythis, CharSeqJc text, ThCxt* _thCxt)
{ char buffer[500];  //no more space in stack!
  int nrofChars;
  STACKTRC_TENTRY("println_s_PrintStreamJc");
  nrofChars = copyToBuffer_CharSeqJc(text, 0, -1, buffer, sizeof(buffer)-1, _thCxt);
  buffer[nrofChars] = 0;  //zero terminated, the rest of buffer is undefined.
  printf("%s\n", buffer);
  STACKTRC_LEAVE;
}


#include "emC/Jc/StringJc.h"
void println_u_PrintStreamJc(PrintStreamJc* ythis, StringBuilderJc_s* text, ThCxt* _thCxt)
{
  StringJc ss = toStringNonPersist_StringBuilderJc(&text->base.object, _thCxt);
  println_s_PrintStreamJc(ythis, ss, _thCxt);
}



void println_O_PrintStreamJc(PrintStreamJc* ythis, ObjectJc* text, ThCxt* _thCxt)
{
  
  
  StringJc ss = toString_ObjectJc(text, _thCxt);
  println_s_PrintStreamJc(ythis, ss, _thCxt);
}

void XXXXXXprintStackTrace_P_ExceptionJc(struct ExceptionJc_t* ythis, struct PrintStreamJc_t* out, struct ThreadContext_emC_t* _thCxt)
{

}

#endif //ndef DEF_ObjectSimple_emC