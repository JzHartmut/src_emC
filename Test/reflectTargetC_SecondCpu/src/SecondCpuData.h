#ifndef __ExampleData_h__
#define __ExampleData_h__

#include "Fwc/objectBaseC.h"
#include <os_types_def.h>


typedef struct SimpleDataDsp_t
{

  int32 a,b;
  float c,d;
  double e,f;
}SimpleDataDsp;







typedef struct ExampleArrayElement_t
{
  int32 a;
  float b;
  double c;
  struct ExampleData_t* data;
}ExampleArrayElement;


typedef struct ExampleIntern_t
{ int32 i1;
  int16 i2;
  unsigned int x1;
  int8 i3,i4;
  float f1;
  int32 intArray[20];
  /**@refl: arrayLength = 20 . Damit ist das ein Array. */
  int32* pArray;       //@refl:arrayLength=20.
  /**@refl: arrayLength = 19 */  //punkt vergessen, aber auch keine weitere Info, ist OK
  int32* pArray2;       //@refl:arrayLength=20.
  float afterArray;
  ExampleArrayElement dataArray[4];
  
  /**@refl: arrayLength = 4 */
  ExampleArrayElement* pDataArray;
}ExampleIntern;	



typedef union BitFieldTest_T
{ int32 ints[4];
  struct
  { int32 bit7_0: 8;
    int32: 3;
    int32 bit11: 1;
    int32: 4;
    int32 bit16: 4; // 16
    int32: 4;
    int32: 4;
    int32: 4;
    int32: 4;  //32
    int32 bit36: 4;
    int32: 4;
    int32: 4;
    int32: 4;  //48
    int32: 4;
    int32: 4;
    int32: 4;
    int32 bit64: 4;  //64
    int32: 4;
    int32: 4;
    int32: 4;
    
  }bits;
} BitFieldTest;


typedef struct ExampleData_t
{
  int32 value1, value2;
  float fValue;
  int32* p_value2;
  float* p_fValue;
  BitFieldTest bitField;
  ExampleIntern iData[5];
  ExampleIntern* iDataRef[5];
	/** @refl: arrayLength=5 */
	int* testArray;
  double dValue;
}ExampleData;	


typedef union
{ int first;

  //typedef struct XX_t{ int a;} XX;
  
	struct
	{ int32 bit1:1;
		int32:13;
		unsigned bit2: 5;
		unsigned: 2;
		signed: 3;
	};
}ExampleUnion;

typedef struct MainSecondCpu_t
{ ObjectJc Object;
  ExampleData* data1;
  ExampleIntern* data2;

  /**@refl: arrayLength = 5 . Damit ist das ein Array. */
  SimpleDataDsp* simpleDataArray;
  ExampleUnion* testunion;
  float x,y;
}MainSecondCpu;



void ctor_MainSecondCpu(MainSecondCpu* ythis);

void initDsp();

//extern MainSecondCpu dspMainData;

#endif //__ExampleData_h__
