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
 * @content: Implementation of References of ObjectJc and derivated classes for C-language.
 * The references are used for garbage collection and virtual methods in C.
 *
 * @author JcHartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2008-04-15: JcHartmut creation from older sources
 *
 ****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "BlockHeapJc_internal.h"

//#include <BlockHeap_PlatformSpec.h>

//#include "Jc/ReflectionJc.h"
//#include <Jc/ObjectRefJc.h>

#ifndef DONOTUSE_GCJc


//#define maxBackRef_ObjectJcREF ((mBackRef_ObjectJcREF>>kBitBackRef_ObjectJcREF) -1)


/***************************************************************************************/
/***************************************************************************************/
/***************************************************************************************/
/* handling references of Object and derivated ones.
   This methods are containing in BlockHeap_emC_s.c though there are belong to ObjectJc,
   because the algorithm of using references is used firstly regarding the BlockHeap concept.
   Secondly it consideres the requirements of virtual methods, but it is only an index.
*/



/** Implementation of clearBackRef_Object: First the offsetBackPointer is built from refbase.
    The value is matching to an int value always, also on 16 bit-System, though the
    refbase itself may be 32 bit. That is okay, because the shift and mask operation is done first.
    If this offsetBackPointer is 0 or all bit are set, there is no back reference.
    If the BackRef is inside a valid range, it is an index at the back reference array after the
    objects memory location inside the runtimeheap block. The address of the backRef pointer
    is calculated from the address of the object, its size, written down inside the object,
    and the idxBackref. The back ref founded there must be the reference to ythis,
    otherwise it is an fatal error. It is tested. If the memory content is confused,
    the test fails. It it is okay, the reference is set to 0.
*/
void clearBackRefJc(void* enhancedRef)
//bool clearBackRefJc(ObjectRefValuesJc* refbase)
{ //NOTE: it may be a 16-bit-integer, therefore shift and mask first.
  ObjectJcREF* ref = (ObjectJcREF*)enhancedRef;
  
  int idxBackref = (int)( (ref->refbase) >>kBitBackRef_ObjectJc) & (uint)(mBackRef_ObjectJc>>kBitBackRef_ObjectJc);

  if(idxBackref > 0)
  { BlockHeap_emC_s* heap;
    //ObjectJcREF* ref = (ObjectJcREF*)refbase;
    BlockHeapBlockJc* block;
    STACKTRC_ENTRY("clearBackrefJc");
    block = searchBlockHeapBlock_BlockHeap_emC(ref->ref, &heap);
    if(block->typeOrMaxRef == kFree_Type_BlockHeapBlock)
    { /**a back reference from a freed block.
       * This situation is typically if a cluster of blocks with mutual references is freed.
       * The block is freed already. The backrefs are deletes hence.
       */
    }
    else
    {
      if(block == null)
        THROW1_s0(RuntimeException, "clearBackrefJc(): reference not in any BlockHeap", 1);
      { ObjectJcREF** backRef = &block->backRefs->data[idxBackref-1];
        if(ref != *backRef) THROW1_s0(RuntimeException, "clearBackrefJc(): backref test fails", 1);
        *backRef = null;  //clear the backref
      }
    }
    ref->ref = null;    //clear the ref.
    ref->refbase = 0;
    STACKTRC_LEAVE;
    //return true;
  }
  else
  { //return true;
  }
}



/**calculates the index insided the jumptable of a dynamic call,
 * regarding the type of reference and the type of the instance.
 * @param reflectionObj The reflection of the referenced instance.
 * @param reflectionRef The reflection of the reference. It should be the same as reflectionObj
 *        or it should be found as a superclass or interface of the reflectionObj.
 *        This param is only used with its pointer value, no access to the referenced memory location will be done.
 * @return The index of the part of jumptable of the reference inside the jump table of the object.
 *         * It is 0, if reflectionObj == reflectionRef, it means the reference is from the same type as the Object.
 *         * It is mIdxVtbl_ObjectJc if reflectionObj is null. This case is possible if the Object has no reflection infos.
 *           If the index with this value is used as an index of jumptable, an exception occurs.
 *           But if it is not used, it is a valid case, especially if no dynamic linked call occurs.
 */
static int xxxgetIdxVtbl(ClassJc const* reflectionObj, ClassJc const* reflectionRef)
{ int idxVtbl = -1;
  ClassOffset_idxVtblJcARRAY const* reflectionIfc;
  ClassOffset_idxVtblJcARRAY const* reflectionSuper;
  STACKTRC_ENTRY("getIdxVtbl_ObjectJc");
  if(reflectionObj == null)
  { //if no reflection is used, it is able in C++ environment or if no dynamic linked methods are used.
    idxVtbl = mIdxVtbl_ObjectJc;  //causes an error if it will be used!
  }
  else
  { if(reflectionRef == null)  //if no reflection is prescribed:
    { idxVtbl = 0;  //returns the Vtbl_ObjectJc
    }
    if(reflectionRef == reflectionObj)
    { idxVtbl = 0;  //returns the whole Vtbl for the type.
    }
    else if( (reflectionIfc = reflectionObj->interfaces) != null)
    { int idxIfc;
      for(idxIfc = 0; idxVtbl < 0 && idxIfc < reflectionIfc->head.length; idxIfc++)
      { ClassOffset_idxVtblJc const* reflectionChild;
        reflectionChild = &reflectionIfc->data[idxIfc];
        if(reflectionChild->clazz == reflectionRef)
        { idxVtbl = reflectionChild->idxVtbl;
        }
      }
    }

    if(idxVtbl < 0 && (reflectionSuper = reflectionObj->superClasses) != null)
    { int idxSuper = 0;
      for(idxSuper = 0; idxVtbl < 0 && idxSuper < reflectionSuper->head.length; idxSuper++)
      { ClassOffset_idxVtblJc const* reflectionChild;
        reflectionChild = &reflectionSuper->data[idxSuper];
        if(reflectionChild->clazz == reflectionRef)
        { idxVtbl = reflectionChild->idxVtbl;
        }
        else
        { //Recursive call because deeper inheritance:
          idxVtbl = xxxgetIdxVtbl(reflectionChild->clazz, reflectionRef);
        }
      }
    }
    { //search in superclasses and there interfaces
      //old if only 1 superclass:
      //idxVtbl = getIdxVtbl(reflectionObj->superClass, reflectionRef);
    }

  }
  STACKTRC_LEAVE; return(idxVtbl);
}





/** Implementation description:

*/






void setBackRefJc(void* refP, void const* src)
//METHOD_C bool setBackRefJc(ObjectRefValuesJc* refbase, void const* src)
{ //check which RuntimeHeap is used
  ObjectJcREF* ref = (ObjectJcREF*)(refP);  //
  BlockHeap_emC_s* heap;
  BlockHeapBlockJc* block;
  int imax;
  STACKTRC_ENTRY("setBackref_BheapJc");

  block = searchBlockHeapBlock_BlockHeap_emC(src, &heap);

  if(  block != null
    && (imax = block->heapidxAndMaxref & mMaxRef_ObjectJc_BlockHeap) > 0
    )
  { int idx = 0;
    ObjectJcREF** backRef = block->backRefs->data;
    //TODO use cmpAndSet!
    block->typeOrMaxRef |= mIsReferenced;
    if(block->nextBlock != null)
    { //the block is processed by Garbage collection and may be detect as free.
      theGarbageCollectorJc.bAbortTest = true;  //therefore abort the current test.
    }
    //backRef = (ObjectJcREF**)( ((MemUnit*)(block)) + (block->ctrl.typeAndSize & mSize_Type_Object));
    while( idx < imax)
    { if(*backRef == null)
      { /**NOTE: ObjectRefValuesJc is the type of the reference-value.
         * The index stored in an enhanced reference starts from 1. It will be placed in higher bits. */
        ObjectRefValuesJc refIx = (((ObjectRefValuesJc)(idx+1)) << kBitBackRef_ObjectJc); 
        /**The part in the exclusive-mBackRef_ObjectJc bits is to be kept. It may be a String-length especially. */
        ObjectRefValuesJc refSave = ref->refbase & ~mBackRef_ObjectJc; 
        /**an ObjectRefValuesJc is the first data inside ObjectJcREF always. The pointer is need to store. */
        //ObjectJcREF* objRef = (ObjectJcREF*)(refbase);  //
        /**Store the pointer to the reference in the backref-table of the block. */
        *backRef = ref;
        /**Store the index of backref-table in the reference. */
        ref->refbase = refSave | refIx;
        break;           //NOTE: break is faster as the TRICKY next. 
        //idx = imax + 1;  //TRICKY: exit loop. I don't want use the break-statement.
      }
      else { 
        /**Check next position. */
        idx +=1; backRef +=1;
      }
    }
    if(idx == imax)
    {
      THROW1_s0(RuntimeException, "too much references for Object", false);
    }
  }
  STACKTRC_LEAVE;
}













#endif //DONOTUSE_GCJc

