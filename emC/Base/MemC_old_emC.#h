#ifndef __MemC_old_MemC_h__
#define __MemC_old_MemC_h__
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
* creation: 2019-02-04 as excerp from MemC_emC.h, old name fw_MemC.h
* The old concept is: MemC contains a char* or MemUnit* pointer.
* It is deprecated. The new concept defines a well typed pointer. Use MemC_emC.h only for newer development. 
*
****************************************************************************/

#include <applstdef_emC.h>

/*@DEFINE_C MemC @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


#error don't use it'



/**MemC: The Type ,,MemC,, is a ,,PtrVal_TYPE(MemUnit),, which is defined in the ,,os_types_def.h,,
* This type provides basic working with memory allocation.
* The Problem in C is: a Pointer to memory does not contain the information about the amount of memory.
* It is a simple pointer only, often a void*. How many bytes are there, it is unknown.
* The struct MemC contains the pointer to memory as MemUnit type and the amount of memory.
* This struct is based on the 
* A PtrVal_MemUnit struct contains both:
* * The pointer to the data as memory address unit.
* * The size of data in memory.
*
* The ,,PtrVal_TYPE(MemUnit),, is specificly defined for any operation system or runtime environment.
* It contains a pointer to memory represented as ,,MemUnit*,, pointer and a size, number of MemUnit elements.
* Because of the definition of ,,PtrVal_TYPE(MemUnit),, an instance of MemC is usually returned by value
* in processor registers, therefore optimized in runtime. 
* For that  its definition is contained in the ,,os_types_def.h,, which can be optimized to the processor properties.
*
* Note that the following struct definition is only a place holder for documentation. Use the following macros and functions.
*/
//typedef struct _MemC_t { int __doNotuse_onlyDocuHelper__; }_MemC;

/**Defines the type. */
//#define MemC PtrVal_MemUnit

/**A const definition of a MemC using as initializer for static or stack variables.
* In standard-C only useable for global static variables, if SIZE or PTR are not constants itself.
*/
#define INIZ_MemC(PTR, SIZE) INIZ_OS_PtrValue(PTR, MemUnit, SIZE)
#define CONST_MemC INIZ_MemC

/**Macro for a value which contains {null, 0} for immediately initializing. 
* Application example:
* , MemC myMemc = NULL_MemC();  //initialized with {null, 0}
*/
#define NULL_MemC() CONST_OS_PtrValue(null, MemUnit, 0)


/**Builds a MemC in the stack as Argument in function call. 
* @return MemC as value.
*/
inline MemC ret_MemC(void* ptr, int size){ MemC ret = INIZ_OS_PtrValue(ptr, MemUnit, size); return ret; }



/**gets the size. 
* It's an uint value because the operator sizeof() returns an uint also, and typically it is compared one another.
*/
//#define size_MemC(THIS) (uint)(value_OS_PtrValue(THIS))

//#define getPtr_MemC(MEMC, TYPE) PTR_OS_PtrValue(MEMC, TYPE)


/**Macro to get the pointer from a given MemC. It casts the pointer to the given type pointer.
* , #define PTR_MemC(MEMC, TYPE) ((TYPE*)(MEMC).ref)
* @param TYPE the type of the pointer, without *. for example: "void" to return a void*
* @return the pointer
*/
//#define PTR_MemC(MEMC, TYPE) PTR_OS_PtrValue(MEMC, TYPE)

//#define PTR1_MemC(MEMC) (MEMC.ptr)

#define PTRPOS_MemC(MEMC, TYPE, POS) (TYPE*)(PTR_OS_PtrValue(MEMC, MemUnit) + (POS))



/**Macro to get the int8* pointer from a memory location. 
* Note: That is not a MemUnit in any case, only if it is a byte address processor (most processors).
*/
#define bytePtr_MemC(MEMC) PTR_OS_PtrValue(MEMC, int8*)

/**Macro to check whether the reference to the memory is a null reference.
* The SIZE is not tested.
* Application example:
* , if(! isNull_MemC(myMemC)) { ... } 
* @return true if it is a null reference, else false.
*/
#define isNull_MemC(MEMC) (PTR_OS_PtrValue(MEMC, void)==null)

//@deprecated, NOTE: better to use PTR_MemC
#define start_MemC(THIS) PTR_OS_PtrValue(THIS, struct MemAreaC_t)

//@deprecated, NOTE: better to use END_MemC, don't use MemAreaC_t 
#define end_MemC(THIS) (addOffset_MemAreaC(value_OS_PtrValue(THIS), size_MemC(THIS)))

/**Macro to return the exclusively end address of THIS MemC as MemUnit* reference for address calculation. 
* Application example:
* , MemUnit* startAddr = PTR_MemC(myMemC, MemUnit);
* , MemUnit* endAddr = END_MemC(myMemC);  
* , MemUnit* myAddr = (MemUnit*)&anyData;
* , if(myAddr >= startAddr && myAddr < endAddr) { .... //it is inside 
*/
#define END_MemC(THIS) ( PTR_MemC(THIS, MemUnit) + size_MemC(THIS) )



/**Macro to set a given embedded instance to the given values. 
* @param PTR pointer to any memory location with any type.
* @param SIZE number of [[class_MemUnit]] for this memory area.
*/
#define set_MemC(THIS, PTR, SIZE) { (THIS).ref = (MemUnit*)PTR; (THIS).size = SIZE; }

/**Macro to set an given embedded instance to 0. */
#define setNull_MemC(THIS) set_OS_PtrValue(THIS, null, 0)

/**An Instance which contains {0, 0} 
* Application example:
* , return null_MemC;
*/
extern MemC null_MemC;


/**Allocates memory in a stanard way. This method substitures the using of malloc() from standard-C-libraries.
* It is possible to implement this method in a platform/framework specific way different to the given C-libraries. 
*/
//METHOD_C MemC alloc_MemC(int size);


/**frees an allocated memory. This is the old form before 2016-05 which uses the MemC instance to free.
* Not it is a macro for compatibility which invokes ,,free_MemC(PTR_MemC(mem, void)),,
* It is deprecated since 2016-05, now only the address is necessary.
* It is the opposite method to alloc_MemC(). */
#define freeM_MemC(mem) free_MemC(PTR_MemC(mem, void))  


/**Builds a MemC struct and returns it per value.
* This is a helper method to supply a MemC argument in a method call.
*/
//METHOD_C MemC build_MemC(void* address, int size);




/**Builds a MemC struct and returns it per value.
*/
METHOD_C MemC fromArea_MemC(void* address, void* endAddress);

/**Build a subset from current.
* @param offsetStart 0... adress offset from start
* @param offsetEnd 0 = to end, negativ = backward from end, positiv = from start. It should be greaterequal offsetStart.
*/
METHOD_C MemC subset_MemC(MemC parent, int offsetStart, int offsetEnd);


/**Build a address inside mem. 
* @param offset 0... adress offset from start
* @param nrofBytes It is checked, whether the area contains enaugh bytes
* @throws IndexOutOfBoundsException if the param are failed.
*/
METHOD_C struct MemAreaC_t* address_MemC(MemC mem, int offset, int nrofBytes);

/**Inserts a hole in the memory area at byte index idx. 
* It means the content after insertAddress will be shifted to back.
* The free moved content at insertAddress don't be changed. It means, this content is invalid in most of cases.
* It is a copy of the content after insertAddr+ nrofBytes.
*
* Using this method no pointer arithmetic and memmove, memset is necessary. It prevents errors.
* @param mem An area of memory, address and size.
* @param insertAddr address inside the area of memory, on which the nrofBytes should inserted.
* @param nrofBytes number of bytes to insert.
*/ 
METHOD_C void insert_MemC(MemC mem, void const* insertAddr, int nrofBytes);

/**Deletes some bytes in the memory area at byte index idx. It means the content after idx will be shifted to front.
* The rest to end is filled with 0-bytes.
*/ 
METHOD_C void delete_MemC(MemC mem, int idx, int nrofBytes);

/**Allocates the amount of bytes in heap,but do not initialize it. */
#define MALLOC(TYPE) ((TYPE*)malloc(sizeof(TYPE)))


/**allocates and initializes with 0.
*/
MemC alloc0_MemC(int size);


/**Kompatibilität: */
#define os_init0MemC init0_MemC


#endif //__MemC_old_MemC_h__
