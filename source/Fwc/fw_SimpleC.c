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
 * @content Basicly routines useable in C.
 *
 * @author Hartmut Schorrig
 * @version 0.81ad
 * list of changes:
 * 2007-10-01: JcHartmut creation
 *
 ****************************************************************************/
#include <Fwc/fw_SimpleC.h>

/**This algorithm is equal java.util.Arrays.binarySearch(int[] a, int fromIndex, int toIndex, int key)
 * but without rangeCheck of input values.
 * The algoritm works only if the data are sorted and the indices are matching.
 */ 
int binarySearch_int(int32_t const* data, int fromIndex, int toIndex, int32_t key)
{ int low = fromIndex;
	int high = toIndex -1;
	while (low <= high)
  { int mid = (low + high) >> 1;
	  int32_t midVal = data[mid];
	  if (midVal < key)
		{ low = mid + 1;
	  }
    else if (midVal > key)
		{ high = mid - 1;
	  }
    else
		{ return mid; // key found
    }
	}
	return -(low + 1);  // key not found.
}


int binarySearch_int64(int64_t const* data, int fromIndex, int toIndex, int64_t key)
{ int low = fromIndex;
	int high = toIndex -1;
	while (low <= high)
  { int mid = (low + high) >> 1;
	  int64_t midVal = data[mid];
	  if (midVal < key)
		{ low = mid + 1;
	  }
    else if (midVal > key)
		{ high = mid - 1;
	  }
    else
		{ return mid; // key found
    }
	}
	return -(low + 1);  // key not found.
}


