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
 * @version 0.91
 * @content Defintion of routines javalike java.lang.System and related
 * @author Hartmut Schorrig, www.vishia.org
 *
 * list of changes:
 * 2009-10-15: new: println_s_PrintStreamJc(...), println_sb_PrintStreamJc(...)
 * 2006-05-00: Hartmut creation
 *
 ****************************************************************************/
#ifndef __SystemJc_h__
#define __SystemJc_h__

#include "Jc/ObjectJc.h"
#include "Jc/FileIoJc.h"

struct StringBuilderJc_t;

#ifndef PrintStreamJcREFDEF
  #define PrintStreamJcREFDEF
  DEFINE_EnhancedRefJc(PrintStreamJc);
#endif 



/*@CLASS_C SystemJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


typedef struct SystemJc_t
{
  ObjectJc object;
}SystemJc;

struct PrintStreamJc_t;

extern PrintStreamJcREF out_SystemJc;

extern PrintStreamJcREF err_SystemJc;

METHOD_C void arraycopy_SystemJc(ObjectJc* src, int srcPos, ObjectJc* dst, int dstPos, int length, ThCxt* _thCxt); 

METHOD_C void arraycopy_v_SystemJc(ByteStringJc src, int srcPos, ObjectJc* dst, int dstPos, int length, ThCxt* _thCxt); 


/**Runs the garbage collector. 
 *
 * Calling the gc method suggests that the Java Virtual Machine expend effort toward recycling unused objects 
 * in order to make the memory they currently occupy available for quick reuse. 
 * When control returns from the method call, the Java Virtual Machine has made a best effort to reclaim space from all discarded objects.
 *
 * NOTE: description original Java made by Sun
*/
METHOD_C void gc_SystemJc(ThCxt* _thCxt);

METHOD_C StringJc getenv_SystemJc(StringJc name, ThCxt* _thCxt);


/**Returns a value, which presents a nanotime-Counter. */
int64 nanoTime_SystemJc(ThCxt* _thCxt);


#endif //__SystemJc_h__



