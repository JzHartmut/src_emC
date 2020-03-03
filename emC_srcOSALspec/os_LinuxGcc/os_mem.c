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
 * @content This file contains the implementation of os_mem for Linux-GNU.
 * @author Hartmut Schorrig
 * @version 0.81d
 * list of changes:
 * 2007-10-01: Hartmut creation
 *
 ****************************************************************************/
//the own include file firstly
#include <emC/OSAL/os_mem.h>

//Needed includes from os:
#include <stdlib.h>
//#include <errno.h>

//needed from os_adaption itself
//#include <emC/OSAL/os_mem.h>


void* os_allocMem(uint size)
{ void* ptr = malloc(size);  //
  if(ptr == null)
  { //int error = errno;
    //os_notifyError(OSAL_NoMemory, OSAL_TEXT_NoMemory, error, 0);
  }
  return ptr;
}



int os_freeMem(void const* ptr)
{ free((void*)ptr);
  return 0;
}



