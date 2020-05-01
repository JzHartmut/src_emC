/************************************************************************************************
 * Copyright/Copyleft:
 *
 * For this source the LGPL Lesser General Public Licens
 * 3) Every user of this source, also the user of redistribute copies
 *    with or without payment, must accept this license for further using.e,
 * published by the Free Software Foundation is valid.
 * It means:
 * 1) You can use this source without any restriction for any desired purpose.
 * 2) You can redistribute copies of this source to everybody.
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
 * @content This file contains basicly definitions and declarations using in C
 * independent of the CRuntimeJavalike concept.
 *
 * @author Jchartmut www.vishia.org
 * @version 0.82
 * list of changes:
 * 2011-02-18 Hartmut chg: parseIntRadix_emC(...) instead parseInt_emC(...). Renaming because last parameter is parsedChars and not restSize. 
 *                         It is better to use for simpe-C-applications. The old form isn't represent anywhere.  
 * 2011-02-18 Hartmut new: method skipWhitespaces_emC(...)
 * 2011-02-18 Hartmut chg: StringJc-methods written in fw_String.c, deleted here
 * 2010-02-20: Hartmut new: OFFSETinTYPE_SimpleC and OFFSETinDATA_SimpleC, but the same functionality is conained in fw_MemC.h, see there.
 * 2008-04-22: JcHartmut some changes in definitions to treat with memory:
 *                       * MemAreaC is shown with 32-bit-integer in debugger, not with char.
 *                       * The macros addOffset_MemAreaC and offset_MemAreaC work with any type of pointer.
 *                       * The element size_ of MemC should not be directly used outside, use the macro size_MemC
 *                         and setSize_MemC instead. size_ stores also an offset for treating in BlockHeap.
 * 2007-10-00: JcHartmut creation
 *
 ****************************************************************************/
#ifndef __applstdef_emC_h__
  /**This file fw_SimpleC.h should be included in the applstdef_emC.h. 
   * If this file is directly included, it needs the applstdef_emC.h. But the __simpleC_h__ guard should not be set firstly
   * to include the fw_SimpleC.h in the given order in applstddef.h
   */
  #include <applstdef_emC.h>
#endif
#ifndef __simpleC_h__
#define __simpleC_h__
/**This file contains some usefull definitions for simpe C programming.

*/
#include <compl_adaption.h>



typedef union U_intfloat_t {
  float f; int32_t i;
} U_intfloat;



typedef union U_ptr_t{
  float* f; int32_t* i; int32_t addr;
} U_ptr;



/*@DEFINE_C specialDefines @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/**specialDefines: ...*/

/** This type represents a pointer to a void name(void) - method.
  * It is needed on some locations in software.
  */
typedef void(* MT_void_Method_void)(void);

/** This type represents a pointer to a int name(int) - method.
  * It is needed on some locations in software.
  */
typedef int(* MT_int_Method_int)(int);



/**Calculates on compile time the number of elements of given array instance.
 * @param ARRAY a instance of an array type.
 */
#define ARRAYLEN_SimpleC(ARRAY) (sizeof(ARRAY)/sizeof(ARRAY[0]))
#define ARRAYLEN(ARRAY) (sizeof(ARRAY)/sizeof(ARRAY[0]))

/**Calculates the offset of an element within the given structure type.
 */
/* NOTE: offsetof in stddef.h works insufficient.
 * NOTE: The pointer to 0x1000 is used because any compiler generates an error if a 0-pointer is used. 
 * @deprecated see fw_MemC.h
 */
#define OFFSETinTYPE_SimpleC(TYPE, ELEMENT)  ( (MemUnit*)( &( ((TYPE*)0x1000)->ELEMENT) )  - (MemUnit*)0x1000)

/**Calculates the offset of an element within the referenced structure data.
 * @deprecated see fw_MemC.h
 */
#define OFFSETinDATA_SimpleC(PTR, ELEMENT)  ( (MemUnit*)( &( (PTR)->ELEMENT) )  - (MemUnit*)(PTR))






/*@CLASS_C Int32Array256 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/** This structure is useable if raw data should be mapped, it may typical used as pointer type.
  * The size of the array is a free choiced number, appropriate to show the data in debugger.
*/
typedef struct Int32Array256_t
{ int32_t data[256];
}Int32Array256;






/*@CLASS_C FloatArray256 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/** This structure is useable if raw data should be mapped, it may typical used as pointer type.
  * The size of the array is a free choiced number, appropriate to show the data in debugger.
*/
typedef struct FloatArray256_t
{ float data[256];
}FloatArray256;






/*@CLASS_C FloatArray20 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/** This structure is useable if raw data should be mapped, it may typical used as pointer type.
  * The size of the array is a free choiced number, appropriate to show the data in debugger.
*/
typedef struct FloatArray20_t
{ float data[20];
}FloatArray20;






/*@CLASS_C BinarySearch @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/**Searches the position of key inside the sorted array data[].
 * This algorithm is equal java.util.binarySearch(int[] a, int fromIndex, int toIndex, int key)
 * but without rangeCheck of input values.
 * The algoritm works only if the data are sorted and the indices are matching.
 *
 * @param data array of values in ascending sorted order
 * @param fromIndex The first index of data inside array, typically 0
 * @param toIndex The last+1 index of data (exclusive), typically the number of values.
 * @param key the value to be searched for 
 * @return index of the search key, if it is contained in the array within the specified range; 
 * otherwise, (-(insertion point) - 1). The insertion point is defined as the point 
 * at which the key would be inserted into the array: 
 * the index of the first element in the range greater than the key, 
 * or toIndex if all elements in the range are less than the specified key. 
 * Note that this guarantees that the return value will be >= 0 if and only if the key is found. 
 */ 
extern_C int binarySearch_int(int32_t const* data, int fromIndex, int toIndex, int32_t key);
extern_C int binarySearch_int64(int64_t const* data, int fromIndex, int toIndex, int64_t key);

#define binarySearch_int_simpleC binarySearch_int


/**Binary search algorithm for universal purpose as macro.
 * Before this algoritm is used, the following line should be defined in the source:

 #define BINARY_SEARCH_ARRAY_emC(INDEX) myArray[INDEX]->maybeElement
 
 * with them the following macro accesses the index.
 * The macro should be used in a C-function-definition:

 int myBinarySearch(int fromIndex, int toIndex) BINARY_SEARCH_emC(fromIndex, toIndex)
 */
#define BINARY_SEARCH_emC(key, fromIndex, toIndex)  \
{ int low = fromIndex;                         \
	int high = toIndex -1;                       \
	while (low <= high) {                        \
    int mid = (low + high) >> 1;               \
	  long midVal = getValue_BINARY_SEARCH_ARRAY_emC(mid);\
	  if (midVal < key)                          \
		{ low = mid + 1;\
	  }\
    else if (midVal > key)\
		{ high = mid - 1;\
	  } else\
		{ return mid; /* key found */ \
    }\
	}\
	return -(low + 1);  /* key not found*/ \
}



#endif  //__simpleC_h__
