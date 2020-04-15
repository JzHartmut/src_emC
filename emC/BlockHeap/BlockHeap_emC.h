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
 * @content: All declarations to use from user level to work with BlockHeap_emC_s
 * for References of ObjectJc and derivated classes for C-language.
 * The references are used for garbage collection and virtual methods in C.
 *
 * @author JcHartmut www.vishia.org
 *
 ****************************************************************************/
#ifndef __BlockHeap_emC__h
#define __BlockHeap_emC__h
#include <applstdef_emC.h>
#ifndef HEADERGUARD_ObjectJc_h
  #include <emC/Base/Object_emC.h>
#endif

/*@CLASS_C BlockHeap_emC_s @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Sets the current BlockHeap_emC_s for this thread. */
METHOD_C struct BlockHeap_emC_T* setCurrent_BlockHeap_emC(struct BlockHeap_emC_T* ythis, ThCxt* _thCxt);

/**Returns the current BlockHeap for this thread. */
METHOD_C struct BlockHeap_emC_T* current_BlockHeap_emC(ThCxt* _thCxt);

/**Sets the run mode for all instances of BlockHeap_emC_s. Any new operation uses the block heap from up to now.
 * In Java it is an empty not necessary instruction, because all actions are done in normal heap.
 * In C this routine have to be implement from the user, because it is situational to all user-defined block heaps. 
 */
METHOD_C void setRunModeAll_BlockHeap_emC();




/**Sets the log output for the current BlockHeap. */
void setLogMessageOutput_BlockHeap_emC(struct LogMessageFW_t* log, int msgBase, ThCxt* _thCxt);



/**Returns the first BlockHeap in a system, able to use for new Threads without BlockHeap. */
METHOD_C struct BlockHeap_emC_T* first_BlockHeap_emC();


/**runs the garbage collector. One run tests one block cluster and returns after the test.
 * Either the blocks are freed or if at least one block is used, therefore no freeing is done.
 * @param logIdFreed The ident number of log system for the message of freed.
 *                      This message will be expected rarely.
 * @param logIdUsed  The ident number of log system for the message of used.
 *                      This message will be expected in every call.
 * @return 0-if a block is handled, but not freed.
 *         1-if a block is handled and freed.
 *         2-if the end is found
 */
METHOD_C int garbageCollection_BlockHeap_emC(bool bUserCall, ThCxt* _thCxt);




/**Return values from [[garbageCollection_BlockHeap_emC(...)]] 
 */
typedef enum EChecked_BlockHeap_emC_t
{ checkGcBlockUsed_BlockHeap_emC = 0
, checkGcBlockFreed_BlockHeap_emC = 1
, checkGcFinished_BlockHeap_emC = 2
}EChecked_BlockHeap_emC_e;




bool runUserCalledGc_BlockHeap_emC(ThCxt* _thCxt);


/**Allocates a block which is non-based on ObjectJc. 
 * Note: If the block is based on ObjectJc, [[Jc:alloc_ObjectJc(...)]] have to be called. 
 *       It is necessary because the garbage collector should call [[Jc:finalize_ObjectJc(...)]].
 * @return 
 */
MemC allocMemC_BlockHeap_emC(struct BlockHeap_emC_T* ythis, int size, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt);



/**Allocates a block in the current Blockheap or initial with standard malloc.
 */
METHOD_C MemC alloc_sBlockHeap_emC(int nrofBytes);

/**allocates a block in the standard BlockHeap.
 * @param sCallInfo A pointer to a zero-terminate constant string to report the creater of the block usage.
*/
METHOD_C MemC alloc_s_sBlockHeap_emC(int size, const char* sCallInfo, ThCxt* _thCxt);
METHOD_C struct ObjectJc_t* allocObject_s_sBlockHeap_emC(int sizeObj, int identObj, const char* sCallInfo, ThCxt* _thCxt);

extern_C int nrofFreeBlocks_BlockHeap_emC(struct BlockHeap_emC_T* thiz);

METHOD_C MemC alloc_s_BlockHeap_emC(struct BlockHeap_emC_T* ythis, int size, const char* sCallInfo, ThCxt* _thCxt);
METHOD_C struct ObjectJc_t* allocObject_s_BlockHeap_emC(struct BlockHeap_emC_T* ythis, int sizeObj, int identObj, const char* sCallInfo, ThCxt* _thCxt);


METHOD_C MemC alloc_iis_BlockHeap_emC(struct BlockHeap_emC_T* ythis, int sizeObj, int noOfReferences, const char* sCallInfo, ThCxt* _thCxt);
METHOD_C struct ObjectJc_t* allocObject_IIs_BlockHeap_emC(struct BlockHeap_emC_T* ythis, int sizeObj, int identObj, int noOfReferences, const char* sCallInfo, ThCxt* _thCxt);

/**activates the access of garbage collector if it is not done already.
 * If the reference is not stored in any enhanced reference using setBackRefJc
 * it is not testet by garbage collector until this time.
 * This method should be called on end of a statement block which allocs the mem.
 *
 * @param addr Memory location of any object. It will be tested whether it is in range of any Blockheap-block.
 * @param exclAddr If this addr isn't null and it is in the same block, the block doesn't activate for garbage collection.
 *        It is because a returned address may be use in the calling environment. 
 *        The activating for garbage collection have to be organized there. The Java2C-Translator consideres this situation.
 */
METHOD_C void xxxactivateGarbageCollectorAccess_BlockHeap_emC(void const* addr, void const* exclAddr);


#define activateGC_BlockHeapBlockJc(block) { \
  block->typeOrMaxRef |= mConsideredInGarbage_Type_Object; }
    


/**searches the block in any BlockHeap and returns the base address of the block. 
 * @param address Any address inside the block or any other address of any Object. null is admissible too.
 * @param retHeap Pointer to the return-pointer instance, 
 *        it will be filled with the reference to the Heap-Management-Data.
 * @return null if the address-parameter is not localized in any heap, elsewhere the address of the block.
 */
METHOD_C struct BlockHeapBlockJc_t* searchBlockHeapBlock_BlockHeap_emC(void const* address, struct BlockHeap_emC_T** retHeap);

/**deduces from any address inside the block to the base address of the block.
 * @param address Adress inside any block.of the given heap.
 */
METHOD_C struct BlockHeapBlockJc_t* deduceBlockHeapBlock_BlockheapJc(void const* address);


extern_C struct BlockHeapBlockJc_t* getBlockFromAddr_BlockHeap_emC(struct BlockHeap_emC_T* thiz, void* addr);

/**Try to free a block in the block heap. 
 * The block should be unused in any case. Either a block was allocated without [[activateGC_BlockHeapBlockJc(...)]]
 * Then it have to be freed with this algorithm. Or this method is invoked inside the garbage collection after test.
 * @param addr if it refers inside any block in the block heap, free that block.
 * @return true if addr is a block, false if nothing was freed.
 */
METHOD_C bool free_sBlockHeap_emC(void const* addr, ThCxt* _thCxt);

METHOD_C void free_BlockHeap_emC(struct BlockHeap_emC_T* ythis, struct BlockHeapBlockJc_t* block, ThCxt* _thCxt);


/** Allocates the memory for the given type in current BlockHeap*/
#define alloc_T_sBlockHeap_emC(TYPE) ((TYPE*)(alloc_BlockHeap_emC(current_BlockHeap_emC(), sizeof(TYPE))))






#endif //__BlockHeap_emC__h
