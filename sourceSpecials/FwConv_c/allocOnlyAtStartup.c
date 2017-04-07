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
 * @content: Sample for allocation implementation for systems, which uses dynamical memory management
 *           only in the startup phase.
 *
 * @author Hartmut Schorrig, Pinzberg, Germany, www.vishia.org
 *
 * @version 0.93
 * list of changes:
 * 2010-04-02: Hartmut creation
 *
 ****************************************************************************/

#include <Jc/ObjectJc.h>
#include <Jc/ReflectionJc.h>

static bool bRunMode = false;

int setRunMode_ObjectJc(ThCxt* _thCxt)
{
  bRunMode = true;
  return 0;
}


ObjectJc* alloc_ObjectJc(const int size, const int32 typeInstanceIdent, ThCxt* _thCxt)
{ ObjectJc* othis;
  int size2 = size;
  STACKTRC_TENTRY("alloc_ObjectJc");
  if(!bRunMode)
  { MemC mem;
    if(size == -1){ 
      size2 = 480; 
    } else if(size < 0 || size > 0x100000) {
      THROW_s0(RuntimeException, "to much memory to allocate. ", size);
    }
    mem = alloc_MemC(size2);
    othis = PTR_MemC(mem, ObjectJc);
    init_ObjectJc(othis, size, typeInstanceIdent);
  }
  else {
    THROW_s0(RuntimeException, "no memory because it is runtime. ", 0);
		othis=null;
  }

  STACKTRC_LEAVE; return othis;
}


void free_ObjectJc(ObjectJc* thiz) {
  MemC mem = build_MemC(thiz, getSizeInfo_ObjectJc(thiz));
  freeM_MemC(mem);
}



/**A BlockHeap isn't use. The reference to BlockHeap inside an ObjectJc is null anytime.
 * Therefore this class is empty. It shuould be exist, because the linker need the label.
 */
ClassJc const reflection_BlockHeapBlockJc = {0}; 



/**If no block heap is used, this routine returns {0, null} because there is no rest. */
MemC getRestBlock_ObjectJc(ObjectJc* ythis, int size, ThCxt* _thCxt)
{ MemC ret = NULL_MemC();
  return ret;
}


void setBackRefJc(void *ref,void const *instance)
{
}


void clearBackRefJc(void *ref)
{
}




void activateGC_ObjectJc(void const* instance,void const* excl,struct ThreadContextFW_t* _thCxt)
{
  
}