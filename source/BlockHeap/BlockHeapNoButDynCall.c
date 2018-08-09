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
 * @version 0.83
 * list of changes:
 * 2006-05-00: www.vishia.de creation
 *
 ****************************************************************************/
//#include "CRuntimeJavalike.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "RuntimeHeapJc.h"
//#include "ThreadJc.h"
//#include "StringJc.h"

#include "Jc/ObjectJc.h"
#include "emC/Exception.h"



#define maxBackRef_ObjectJcRef ((mBackRef_ObjectJcRef>>kBitBackRef_ObjectJcRef) -1)


/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/
/* handling references of Object and derivated ones.
   This methods are containing in RuntimeHeapJc.c though there are belong to ObjectJc,
   because the algorithm of using references is used firstly regarding the RuntimeHeap.
   Secondly it consideres the requirements of virtual methods, but it is only an index.
*/




/** Implementation of clearRef_Object: First the offsetBackPointer is built from refbase.
    The value is matching to an int value always, also on 16 bit-System, though the
    refbase itself may be 32 bit. That is okay, because the shift and mask operation is done first.
    If this offsetBackPointer is 0 or all bit are set, there is no back reference. The case of
    all bits set is happens if it is a constant string pointer.
    If the BackRef is inside a valid range, it is an index at the back reference array after the
    objects memory location inside the runtimeheap block.

*/
void clearRef_Object(void* enhancedRef)
{ 
}







/** Implementation description:

*/
void setRef_ObjectJc(void* enhancedRef, ObjectJc* src, struct ClassJc_t* reflectionRef) //uint16 idxVtbl)
{ 
}





