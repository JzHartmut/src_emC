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
 *
 * @author Hartmut Schorrig www.vishia.org
 * creation: 2007-06-00
 * changes:
 * 2010-02-20 Hartmut new: Concept x_MemUnit: 
 *                    OFFSETinTYPE_MemUnit() and OFFSETinDATA_MemUnit: macro to get offset in struct
 *                    addOffset_MemUnit(): macro for address calculation. It is better foundable and visible as any simple address calculation.
 *                    del: OFFSETinStruct_MemUnit(): macro, it is the same as OFFSETinDATA_MemUnit(). 
 * 2010-02-07 Hartmut new: OFFSETinStruct_MemUnit(...)
 * 2010-01-21 Hartmut new: inRange_MemAreaC(...)
 * 2009-11-15
 *  *new: Forward declaration of struct to prevent warnings.
 *  *new: define NULL_MemC()
 *
 ****************************************************************************/
#ifndef __applstdef_emC_h__
  /**This file MemC should be included in the applstdef_emC.h. 
   * If this file is directly included, it needs the applstdef_emC.h. But the INCLUDED_emC_Base_MemC_emC_h guard should not be set firstly
   * to include the MemC.h in the given order in applstddef.h
   */
  #include <applstdef_emC.h>
#endif


#ifndef INCLUDED_emC_Base_MemC_emC_h  //include guards, inlude only one time.
#define INCLUDED_emC_Base_MemC_emC_h
/**This file contains some usefull definitions for simpe C programming.

*/

//Note: prevent including sum compiler specific unecessary stuff?
#include <string.h>  //memcpy used.
//TODO use memcpy_emC internally for all emC sources.
//extern_C void* memcpy(void* dst, void const* src, unsigned int len);

/**Forward declaration of struct to prevent warnings. */
struct ThreadContext_emC_t;

/*@CLASS_C MemAreaC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/**returns a pointer to MemAreaC with OFFSET in memory.
 * @param BASE a pointer from type struct MemAreaC_t*. The type will be tested by compiling.
 * @param OFFSET a address-offset (sizeof-Type)
 * @return pointer from type struct MemAreaC_t* at memory location BASE + OFFSET
 */
#define addOffset_MemAreaC(BASE, OFFSET) ( (struct MemAreaC_t*) (((MemUnit*)(BASE)) + (OFFSET)) )

/**Offset between 2 memory locations, from BASE to INSIDE.
 * @param BASE a pointer to an instance.
 * @param INSIDE  a pointer inside any data of the instance
 * @return number of memory address steps from BASE to INSIDE
 */
#define offset_MemAreaC(BASE, INSIDE) (int32)((MemUnit*)(INSIDE) - (MemUnit*)(BASE))

#define inRange_MemAreaC(ADDR, START, END) ( (void const*)(ADDR) >= (void const*)(START) && (void const*)(ADDR) < (void const*)(END)) 




/*@CLASS_C MemUnit @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**Offset of an element in a given struct instance. It is a macro.
 * @param BASE The reference to a instance with known struct type.
 * @param ELEMENT Name of the element in the struct.
 */
//#define OFFSETinStruct_MemUnit(BASE, ELEMENT) ((MemUnit*)((BASE)->ELEMENT) - (MemUnit*)(BASE))

/**Calculates the offset of an element within the given structure type.
 */
/* NOTE: offsetof in stddef.h works insufficient.
 * NOTE: The pointer to 0x1000 is used because any compiler generates an error if a 0-pointer is used. 
 */
#define OFFSETinTYPE_MemUnit(TYPE, ELEMENT)  ( (MemUnit*)( &( ((TYPE*)0x1000)->ELEMENT) )  - (MemUnit*)0x1000)

/**Macro to calculates the offset of an element within the referenced structure data.
 */
#define OFFSETinDATA_MemUnit(PTR, ELEMENT)  ( (MemUnit*)( &( (PTR)->ELEMENT) )  - (MemUnit*)(PTR))


#define OFFSET_MemUnit(P1, P2) ((MemUnit*)(P2) - (MemUnit*)(P1)) 

/**Adds a offset to a memory address. 
 * @param BASE a pointer from any type.
 * @param OFFSET a address-offset (sizeof-Type)
 * @return pointer from type struct MemUnit* to the memory location BASE + OFFSET
 */
#define addOffset_MemUnit(BASE, OFFSET) (((MemUnit*)(BASE)) + (OFFSET))
#define ADD_OFFSET_MemUnit(BASE, OFFSET) (((MemUnit*)(BASE)) + (OFFSET))



/*@DEFINE_C MemC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**MemC: There are some macros and routines to work in memory ranges.  */


/**Defines a struct with pointer and size. 
 * Use it with typedef MemC_DEF(MyType) Mem_MyType; to define a type.
 * Use it with MemC_DEF(MyType) name; to define a variable.
 * You can use name.ref to access MyType* and name.val to access a size information.
 * @param REFTYPE it should be only a type identifier, without modifier. The struct MemC_REFTYPE_t is built.
 * @param NAME The name.
 *  
 */
//#define STRUCT_MemC(REFTYPE) struct MemC_##REFTYPE##_t { REFTYPE* ref; intptr_t size; }  //OS_REFValue_DEF(NAME, TYPE)

/**Defines the standard-MemC-type. 
 * @since 2019-10: The pointer type is now a struct type Addr8_emC*, not a MemUnit* like before. 
 *        Reason:  a const char* pointer is aligned to 1 on X86-64 platform, but all other pointer should reference
 *        8-aligned addresses (4-aligned for 32-bit-platform) to assure fast memory access. The compiler arranges
 *        the data in a proper form. But the compiler supposed that the casted address to char const*
 *        may have a 1-allignment and produces this justifiable warning. If the non-casted address is used, it is ok.
 * The addr element is now 8-aligned for 64-bit-applications (4-aligned for 32 bit)
 * @since 2019-10: The name is change to addr from ref in STRUCT_AddrVal_emC (before: OS_PtrValue_DEF). 
 *        Hence using location which may conflict in address calculation are conspicuous by compiler errors. 
 *        Do not replace ref to addr without thinking about. Use the new [[addOffset_MemC(...)]] macro for address calculation.
 */
typedef STRUCT_AddrVal_emC(MemC, Addr8_emC);


extern_C MemC null_MemC;

/**Macro to get the pointer from a given MemC. It casts the pointer to the given type pointer.
* , #define PTR_MemC(MEMC, TYPE) ((TYPE*)(MEMC).ref)
* @param TYPE the type of the pointer, without *. for example: "void" to return a void*
* @return the pointer
*/
#define ADDR_MemC(MEMC, TYPE) (TYPE*)((MEMC).addr)
#define PTR_MemC(MEMC, TYPE) (TYPE*)((MEMC).addr)

#define ISNULL_MemC(MEMC) ((MEMC).addr == null)


#define INIZ_MemC(ADDR, SIZE) { (Addr8_emC*)(ADDR), SIZE }

/**gets the size. 
* It's an uint value because the operator sizeof() returns an uint also, and typically it is compared one another.
*/
#define size_MemC(THIS) ((THIS).val)

#define SET_MemC(MEM, ADDR, SIZE){ (MEM).addr = (Addr8_emC*)ADDR; (MEM).val = SIZE; }



/**returns a pointer to MemUnit with OFFSET to the ref in MemC.
* @param MemC 
* @param OFFSET a address-offset (sizeof-Type)
* @return pointer from type struct MemUnit* at memory location MemC.ref + OFFSET
* @since 2019-10, use it for all address calculation.
*/
#define addOffset_MemC(MemC, OFFSET) ( ((MemUnit*)(MemC).addr) + (OFFSET) )






/**Allocates memory in a stanard way. This method substitures the using of malloc() from standard-C-libraries.
 * It is possible to implement this method in a platform/framework specific way different to the given C-libraries. 
 */
#define ALLOC_MemC(M, SIZE) { *(void**)(&(M).addr) = alloc_MemC(SIZE); (M).val = SIZE; }


/**Internal method checks which error and throws. */
METHOD_C void __errorAddress_MemC(MemC* memC, void* addr, int nrofBytes);

/**Throw routine is defined in the C-file because include order. Note: MemC_emC.h is necessary for exception organization itself.*/
METHOD_C void __throw_MemC(char const* error, int val1, int val2);



/**Check whether a calculated address is inside the MemC
 * @param mem Reference to any incarnation of STRUCT_MemC.
 *        Note: If the pointer is faulty this operation fails in most of cases.
 * @param addr any address inside this range
 * @param nrofBytes It is checked, whether the area contains enaugh bytes
 * @throws IndexOutOfBoundsException if the param are failed.
 */
inline bool checkAddress_MemC(void* memC, void* addr, int nrofBytes){
  MemC* mem = (MemC*)memC;   //Note: the mem as param can have any Type of reference.
  if (((MemUnit*)addr) >= PTR_MemC(*mem, MemUnit) && ((MemUnit*)addr) <= (PTR_MemC(*mem, MemUnit) + mem->val - nrofBytes)) return true; 
  else {  
    __errorAddress_MemC(mem, addr, nrofBytes);
    return false;
  } 
}




/**Checks wether the size info in MemC is greater or equal given size, throws an IllegalArgumentException if there isn't so.
*/
inline void checkSize_MemC(MemC mem, int size, struct ThreadContext_emC_t* _thCxt) {
  if(size < (int)size_MemC(mem)) __throw_MemC("insufficient size", mem.val, size);  
}


/**Builds a MemC struct and returns it per value.
* This is a helper method to supply a MemC argument in a method call.
*/
INLINE_emC MemC build_MemC ( void* address, int size) {
  MemC ret; SET_MemC(ret, address, size);
  return ret;
}


/**Initializes the given mem area with 0. This method substitutes the using of memset(ptr, 0, size) of standard-C. */
METHOD_C MemC init0_MemC(MemC mem);

/**Initializes the given mem area with 0. This method substitutes directly the  memset(ptr, 0, size) of standard-C.*/
METHOD_C void init0p_MemC(void* ptr, int size);


/**A macro to prevent writing errors. The pointered mem area occupied from the given type is set to 0, */
#define INIT0p_MemC(PTR) init0p_MemC(PTR, sizeof(*PTR));



/**Ordinary alloc routine without storing of the size. This routine is used inside ALLOC_MemC(...). */
METHOD_C void* alloc_MemC(int size);

/**Macro to set an given embedded instance to 0. */
#define setNull_MemC(THIS) { (THIS).addr = null; (THIS).val = 0; }



/**frees an allocated memory. This is the old form before 2016-05 which uses the MemC instance to free.
 * Note it is a macro for compatibility which invokes ,,free_MemC(PTR_MemC(mem, void)),,
 * It is deprecated since 2016-05, now only the address is necessary.
 * It is the opposite method to alloc_MemC(). 
 * TODO possible: use size to check whether the mem instance is unchanged to the allocated.
 */
#define freeM_MemC(mem) free_MemC(&mem.addr)  

/**frees an allocated memory. It is the opposite method to alloc_MemC().
 * @return has released: 3 - buffer in threadContext, 2 - BlockHeap 1 - allocMem,  4- nothing, unknown (set DebugBreak in freeM_MemC)  
 * * since 2016-05: Only the memory address is necessary.
 * * since 2016-05: It can also free memory in the Thread Context or in the Block Heap, see [[CRJT:_ThreadContext_emC_s.getUserBuffer_ThreadContext_emC(...)]]
 */
METHOD_C int free_MemC(void const* addr);


INLINE_emC int freeMemC_MemC(MemC* mem) {
  int ret = free_MemC(mem->addr);
  mem->addr = null;  //no more referenced
  return ret;
}



#define FREE_MemC(mem) { free_MemC(&mem.addr); mem.addr = null; }  



/**check memory boundaries and copy. */
inline void memcpy_MemC(void* memC, void* addr, void const* src, int size) {
  MemC* mem = (MemC*)memC;
  if (((MemUnit*)addr) < PTR_MemC(*mem, MemUnit) || ((MemUnit*)addr) >= (PTR_MemC(*mem, MemUnit) + mem->val - size)) {
    __errorAddress_MemC(mem, addr, size);
  } else {
    memcpy(addr, src, size);
  }
}


/**What is it? The old version experience of Set any memory location with check.*/
//#define SET_MemC(M, LVAL, VAL) memcpy_MemC((MemC*)&(M), &((M).ref->LVAL), &(VAL), sizeof((M).ref->LVAL))

/**Sets a value inside a area which is defined via STRUCT_MemC. 
 * ,,instead writing of   memcpy(myRef->MemCdata->ref->element, src, size); 
 * ,,write:          MEMcpy_MemC(myRef->MemCdata, element, src, size);
 * It is similar. The routine checks the memory boundaries and executes a memcpy inside the inlined routine _set_MemC(...).
 * If the memory boundaries are exceeded, an Exception is thrown via THROW (see Exception_emC.h).        
 */
//#define MEMcpy_MemC(M, LVAL, SRCADDR, SIZE) memcpy_MemC((MemC*)&(M), &((M).ref->LVAL), SRCADDR, SIZE)






/**The type OS_PtrVal handles with a pointer for a 8 byte alignment.
*/
typedef STRUCT_AddrVal_emC(MemSegmJc, Addr8_emC);

#define INIZ_MemSegmJc(PTR, SEGM) { (Addr8_emC*)(PTR), SEGM }

//typedef OS_PtrValue MemSegmJc;
//#define MemSegmJc OS_PtrValue






#endif  //INCLUDED_emC_Base_MemC_emC_h
