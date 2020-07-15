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
#include <emC/Base/Object_emC.h>
#include <emC/Base/String_emC.h>

#ifndef USE_BlockHeap_emC
//It is the alternative concept without Blockheap, with allocation usual only on startup of the application.
//It defines the same operations as emC/BlockHeap/BlockHeapJc_Alloc.c

static bool bRunMode = false;

int setRunMode_ObjectJc  (  ThCxt* _thCxt)
{
  bRunMode = true;
  return 0;
}


ObjectJc* allocRefl_ObjectJc ( const int size, struct ClassJc_t const* refl, const int32 typeInstanceIdent, struct ThreadContext_emC_t* _thCxt)
{ ObjectJc* othis;
  int size2 = size;
  STACKTRC_TENTRY("alloc_ObjectJc");
  if(!bRunMode)
  { MemC mem;
    if(size == -1){ 
      size2 = 480; 
    } else if(size < 0 || size > 0x100000) {
      THROW1_s0(RuntimeException, "to much memory to allocate. ", size);
    }
    ALLOC_MemC(mem, size2);
    othis = PTR_MemC(mem, ObjectJc);
    ctor_ObjectJc(othis, othis, size, refl, typeInstanceIdent);
  }
  else {
    THROW1_s0(RuntimeException, "no memory because it is runtime. ", 0);
		othis=null;
  }

  STACKTRC_LEAVE; return othis;
}


void free_ObjectJc ( ObjectJc* thiz) {
  //MemC mem = build_MemC(thiz, getSizeInfo_ObjectJc(thiz));
  free_MemC(thiz);
}



/**A BlockHeap isn't use. The reference to BlockHeap inside an ObjectJc is null anytime.
 * Therefore this class is empty. It shuould be exist, because the linker need the label.
 */
ClassJc const refl_BlockHeapBlockJc = {0}; 



/**If no block heap is used, this routine returns {0, null} because there is no rest. */
MemC getRestBlock_ObjectJc  (  ObjectJc* ythis, int size, ThCxt* _thCxt)
{ MemC ret = {null, 0};
  return ret;
}


void setBackRefJc  (  void *ref,void const *instance)
{
}


void clearBackRefJc  (  void *ref)
{
}




void activateGC_ObjectJc  (  void const* instance,void const* excl,struct ThreadContext_emC_t* _thCxt)
{
  
}
#endif  //USE_BlockHeap_emC
