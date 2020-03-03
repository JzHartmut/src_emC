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
 * @content Definition of memory access routines. 
 * This routines are implemented in a operation system specific way. 
 *
 * @author Hartmut Schorrig
 * @version sf-0.83
 * list of changes:
 * 2008-02-01: Hartmut creation 
 *
 ************************************************************************************************/
#ifndef __os_mem_h__
#define __os_mem_h__
#include <applstdef_emC.h>

/**Allocates memory from a memory pool (heap) of the operation system. */
METHOD_C void* os_allocMem(uint size);


/**Releases the memory, give back to operation system.
 * @param pMemory pointer to the memory, it should be the same pointer which is returned from os_allocMem().
 *    if null, it is ok. It is possible to invoke os_freeMem(ptr) on a null-initialized pointer if the memory was not allocated. 
 * @return 0 if success. negativ: an error.
 */
METHOD_C int os_freeMem(void const* pMemory);


/**Checks the heap for size.
 * @return number of bytes/memory words which are able to alloc as large block.
 */
METHOD_C int os_availMem();




#endif  //__os_mem_h__
