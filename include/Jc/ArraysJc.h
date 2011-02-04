/****************************************************************************
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
 *    You mustn't deletee this Copyright/Copyleft inscription in this source file.
 **copyright***************************************************************************************
 *
 * @author www.vishia.de
 * @version 0.81d
 * list of changes:
 * 2007-03-01: JcHartmut www.vishia.org creation from older source
 *
 ****************************************************************************/

#ifndef __ArraysJc_h__
#define __ArraysJc_h__
#include "Jc/ObjectJc.h"
#include "Jc/ComparatorJc.h"

/*@CLASS_C Arrays @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

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


METHOD_C int binarySearch_Object_ArraysJc(const void* a, const void* key, ComparatorJcpp* c); //Comparator_JcRefp c);


#define binarySearch_int_ArraysJc(ARRAY, value, _thCxt) binarySearch_int_ii_ArraysJc(ARRAY, value, 0, ARRAY->head.length, _thCxt)

METHOD_C int binarySearch_int_ii_ArraysJc(const int32_Y* a, int fromIndex, int toIndex, int32 key, ThCxt* _thCxt);

/**Search without check of bounds. It is for internal use, like in Java. */
METHOD_C int binarySearch0_int_ii_ArraysJc(const int32_Y* a, int fromIndex, int toIndex, int32 key);



/**internal routine to search, see java.util.Arrays.
 */
METHOD_C int binarySearch0_int_ArraysJc(int32 const* data, int fromIndex, int toIndex, int32 key);

#define binarySearch_int64_ArraysJc(ARRAY, KEY, _thCxt) binarySearch_int64_ii_ArraysJc(ARRAY, 0, ARRAY->head.length, KEY, _thCxt)


METHOD_C int binarySearch_int64_ii_ArraysJc(int64_Y const* data, int fromIndex, int toIndex, int64 key, ThCxt* _thCxt);
METHOD_C int binarySearch0_int64_ii_ArraysJc(int64_Y const* data, int fromIndex, int toIndex, int64 key);


METHOD_C void fill_B_ArraysJc(int8_Y* array, int fromIndex, int toIndex, int value, ThCxt* _thCxt);

METHOD_C void fill_I_ArraysJc(int32_Y* array, int fromIndex, int toIndex, int32 value, ThCxt* _thCxt);


#endif  //__ArraysJc_h__
