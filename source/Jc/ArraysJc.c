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
 * list of changes:
 * 2007-01-01: JcHartmut www.vishia.org creation from older source
 *
 ****************************************************************************/

#include "Jc/ArraysJc.h"
#include <emC/SimpleC_emC.h>
//#include "ReflectionJc.h"

#include "Jc/ComparatorJc.h"

/**@deprecated */
int binarySearch_Object_ArraysJc(const void* a, const void* key, ComparatorJcpp* c) //ComparatorJcRefp c)
{
  ObjectArrayJc* array = (ObjectArrayJc*) a;


	int low = 0;
	int high = array->length-1;

	while (low <= high)
  {
	  int mid = (low + high) >> 1;
    int cmp;
	  const void* elementInArray;
    /* java-sun:
    Object midVal = a[mid];
	  int cmp = c.compare(midVal, key);
    */
    elementInArray = get_i_ObjectArrayJc(array, mid);
    //Use VCALL_IFCJcpp because it is able to compile this source with C without ++

    #ifdef mIdxMtbl_ObjectJc
     /*TODO
      cmp = DCALL_ifc_Jcpp(compare, Comparator_Jc, MT_compare_Comparator_Jc, c) //REFP_REF_Jc(c)) 
            DCALL_arg_Jcpp
               elementInArray, key 
            _endDCALL_Jc;
     */
     cmp = 0;
    #else
      cmp = 0; //TODO c->compare(elementInArray, key);
    #endif
	  if (cmp < 0)     { low = mid + 1; }
	  else if (cmp > 0){ high = mid - 1;}
	  else
		{ return mid; } // key found
	}
	return -(low + 1);  // key not found.
}


METHOD_C void rangeCheck_ArrayJc(int length, int fromIndex, int toIndex, ThCxt* _thCxt)
{
  STACKTRC_TENTRY("rangeCheck_ArraysJc");

  if(fromIndex > toIndex || fromIndex < 0) { THROW_s0(IllegalArgumentException, "", fromIndex); }
  if(toIndex > length-1)  { THROW_s0(ArrayIndexOutOfBoundsException, "", toIndex); }

  STACKTRC_LEAVE;

}



void fill_B_ArraysJc(int8_Y* array, int fromIndex, int toIndex, int value, ThCxt* _thCxt)
{
  int max = array->head.length;
  int8* data;
  if(toIndex > max || fromIndex > toIndex || fromIndex < 0 || toIndex < 0)
    THROW_s0(ArrayIndexOutOfBoundsException, "index error", max);
  data = array->data + fromIndex;
  while(++fromIndex < toIndex){
    *data++ = (int8)value;
  }
}


void fill_mB_ArraysJc(PtrVal_int8 array, int fromIndex, int toIndex, int value, ThCxt* _thCxt)
{
  int max = value_OS_PtrValue(array);
  int8* data;
  if(toIndex > max || fromIndex > toIndex || fromIndex < 0 || toIndex < 0)
    THROW_s0(ArrayIndexOutOfBoundsException, "index error", max);
  data = array.ref + fromIndex;
  while(++fromIndex < toIndex){
    *data++ = (int8)value;
  }
}


void fill_I_ArraysJc(int32_Y* array, int fromIndex, int toIndex, int32 value, ThCxt* _thCxt)
{
  int max = array->head.length;
  int32* data;
  if(toIndex >= max || fromIndex > toIndex || fromIndex < 0 || toIndex < 0)
    THROW_s0(ArrayIndexOutOfBoundsException, "index error", max);
  data = array->data + fromIndex;
  while(++fromIndex <= toIndex){
    *data++ = value;
  }
}





METHOD_C int binarySearch_STRC_int_ii_ArraysJc(int32ARRAY const* a, int fromIndex, int toIndex, int32 key, ThCxt* stacktraceThreadContext)
{ rangeCheck_ArrayJc(a->head.length, fromIndex, toIndex, stacktraceThreadContext);
  return binarySearch_int(a->data, fromIndex, toIndex, key);
}


int binarySearch0_int_ii_ArraysJc(const int32_Y* a, int fromIndex, int toIndex, int32 key)
{ int low = fromIndex;
	int high = toIndex -1;
	while (low <= high)
  { int mid = (low + high) >> 1;
	  long midVal = a->data[mid];

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





int binarySearch_int_ii_ArraysJc(const int32_Y* a, int fromIndex, int toIndex, int32 key, ThCxt* _thCxt)
{ rangeCheck_ArrayJc(a->head.length, fromIndex, toIndex, _thCxt);
  return binarySearch0_int_ii_ArraysJc(a, fromIndex, toIndex, key);
}


int binarySearch0_int64_ii_ArraysJc(const int64_Y* a, int fromIndex, int toIndex, int64 key)
{ int low = fromIndex;
	int high = toIndex -1;
	while (low <= high)
  { int mid = (low + high) >> 1;
	  int64 midVal = a->data[mid];

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





int binarySearch_int64_ii_ArraysJc(const int64_Y* a, int fromIndex, int toIndex, int64 key, ThCxt* _thCxt)
{ rangeCheck_ArrayJc(a->head.length, fromIndex, toIndex, _thCxt);
  return binarySearch0_int64_ii_ArraysJc(a, fromIndex, toIndex, key);
}


/* old algorithm from me, tested but other behaviour on not founded keys:
  int ix, imin, imax;
  imax=array->length;            //Startwert nach letztem Eintrag
  imin=-1;                  //Startwert vor erstem Eintrag
  while( (imin +1) != imax)
  { const void* elementInArray;
    ix=(imin+imax)/2;        //immer dazwischen
    elementInArray = get_i_ObjectArrayJc(array, ix);
    //Use VCALL_IFCJcpp because it is able to compile this source with C without ++
    if( ( VCALL_IFCJcpp(compare, ComparatorJc, xxx, c)
            elementInArray, key
          _endVCALLJc
        ) > 0
      )
    { imax=ix;
    }            //Item in Tabelle ist groesser, d.h. davor suchen
    else
    {imin=ix;
    }       //Tabelleneintrag kleiner oder gleich, ab dort und dahinter suchen
  }
  ix=imin;     //fuer weiterarbeit


  return ix;
}
*/

