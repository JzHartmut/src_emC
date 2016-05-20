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
 * @content: All declarations to use from user level to work with BlockHeapJc
 * for References of ObjectJc and derivated classes for C-language.
 * The references are used for garbage collection and virtual methods in C.
 *
 * @author JcHartmut www.vishia.org
 *
 ****************************************************************************/
#ifndef __BlockHeapJc__h
#define __BlockHeapJc__h

#ifndef __ObjectJc_h__
  #include "Jc/ObjectJc.h"
#endif

/*@CLASS_C BlockHeapJc @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Sets the current BlockHeapJc for this thread. */
METHOD_C struct BlockHeapJc_t* setCurrent_BlockHeapJc(struct BlockHeapJc_t* ythis, ThCxt* _thCxt);

/**Returns the current BlockHeap for this thread. */
METHOD_C struct BlockHeapJc_t* current_BlockHeapJc(ThCxt* _thCxt);

/**Sets the run mode for all instances of BlockHeapJc. Any new operation uses the block heap from up to now.
 * In Java it is an empty not necessary instruction, because all actions are done in normal heap.
 * In C this routine have to be implement from the user, because it is situational to all user-defined block heaps. 
 */
METHOD_C void setRunModeAll_BlockHeapJc(ThCxt* _thCxt);




/**Sets the log output for the current BlockHeap. */
void setLogMessageOutput_BlockHeapJc(struct LogMessageFW_t* log, int msgBase, ThCxt* _thCxt);



/**Returns the first BlockHeap in a system, able to use for new Threads without BlockHeap. */
METHOD_C struct BlockHeapJc_t* first_BlockHeapJc();


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
METHOD_C int garbageCollection_BlockHeapJc(bool bUserCall, ThCxt* _thCxt);




/**Return values from [[garbageCollection_BlockHeapJc(...)]] 
 */
typedef enum EChecked_BlockHeapJc_t
{ checkGcBlockUsed_BlockHeapJc = 0
, checkGcBlockFreed_BlockHeapJc = 1
, checkGcFinished_BlockHeapJc = 2
}EChecked_BlockHeapJc_e;




bool runUserCalledGc_BlockHeapJc(ThCxt* _thCxt);


/**Allocates a block which is non-based on ObjectJc. 
 * Note: If the block is based on ObjectJc, [[Jc:alloc_ObjectJc(...)]] have to be called. 
 *       It is necessary because the garbage collector should call [[Jc:finalize_ObjectJc(...)]].
 * @return 
 */
MemC allocMemC_BlockHeapJc(struct BlockHeapJc_t* ythis, int size, int nrofReferences, const char* sCallInfo, ThCxt* _thCxt);



/**Allocates a block in the current Blockheap or initial with standard malloc.
 */
METHOD_C MemC alloc_sBlockHeapJc(int nrofBytes);

/**allocates a block in the standard BlockHeap.
 * @param sCallInfo A pointer to a zero-terminate constant string to report the creater of the block usage.
*/
METHOD_C MemC alloc_s_sBlockHeapJc(int size, const char* sCallInfo, ThCxt* _thCxt);
METHOD_C struct ObjectJc_t* allocObject_s_sBlockHeapJc(int sizeObj, int identObj, const char* sCallInfo, ThCxt* _thCxt);

METHOD_C MemC alloc_s_BlockHeapJc(struct BlockHeapJc_t* ythis, int size, const char* sCallInfo, ThCxt* _thCxt);
METHOD_C struct ObjectJc_t* allocObject_s_BlockHeapJc(struct BlockHeapJc_t* ythis, int sizeObj, int identObj, const char* sCallInfo, ThCxt* _thCxt);


METHOD_C MemC alloc_iis_BlockHeapJc(struct BlockHeapJc_t* ythis, int sizeObj, int noOfReferences, const char* sCallInfo, ThCxt* _thCxt);
METHOD_C struct ObjectJc_t* allocObject_IIs_BlockHeapJc(struct BlockHeapJc_t* ythis, int sizeObj, int identObj, int noOfReferences, const char* sCallInfo, ThCxt* _thCxt);

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
METHOD_C void xxxactivateGarbageCollectorAccess_BlockHeapJc(void const* addr, void const* exclAddr);


#define activateGC_BlockHeapBlockJc(block) { \
  block->typeOrMaxRef |= mConsideredInGarbage_Type_Object; }
    


/**searches the block in any BlockHeap and returns the base address of the block. 
 * @param address Any address inside the block or any other address of any Object. null is admissible too.
 * @param retHeap Pointer to the return-pointer instance, 
 *        it will be filled with the reference to the Heap-Management-Data.
 * @return null if the address-parameter is not localized in any heap, elsewhere the address of the block.
 */
METHOD_C struct BlockHeapBlockJc_t* searchBlockHeapBlock_BlockHeapJc(void const* address, struct BlockHeapJc_t** retHeap);

/**deduces from any address inside the block to the base address of the block.
 * @param address Adress inside any block.of the given heap.
 */
METHOD_C struct BlockHeapBlockJc_t* deduceBlockHeapBlock_BlockheapJc(void const* address);

/**Try to free a block in the block heap. 
 * The block should be unused in any case. Either a block was allocated without [[activateGC_BlockHeapBlockJc(...)]]
 * Then it have to be freed with this algorithm. Or this method is invoked inside the garbage collection after test.
 * @param addr if it refers inside any block in the block heap, free that block.
 * @return true if addr is a block, false if nothing was freed.
 */
METHOD_C bool free_sBlockHeapJc(void const* addr, ThCxt* _thCxt);

METHOD_C void free_BlockHeapJc(struct BlockHeapJc_t* ythis, struct BlockHeapBlockJc_t* block, ThCxt* _thCxt);


/** Allocates the memory for the given type in current BlockHeap*/
#define alloc_T_sBlockHeapJc(TYPE) ((TYPE*)(alloc_BlockHeapJc(current_BlockHeapJc(), sizeof(TYPE))))






#endif //__BlockHeapJc__h
