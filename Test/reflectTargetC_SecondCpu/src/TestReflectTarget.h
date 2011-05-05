#ifndef __TestInspector_h__
#define __TestInspector_h__

#include <Jc/ObjectJc.h>
#include <Jc/ReflectionJc.h>
//#include <Inspc/ProgressionValue_Inspc.h>
#include <InspcJ2C/WorkingThread_Inspc.h>

struct Inspector_Inspc_t;


typedef union
{
	int32 value;
	struct
	{
    int32 b0:3;
		int32 b3:11;
		int32 b14:5;  //uses bit 18..14, over 16-bit-border.
		int32 b19:1;
    int32 :12;
	};
}TestUnion;

  





typedef struct TestInspector_t
{ 
  ObjectJc object;

  void* _DSP_;

  struct Inspector_Inspc_t* reflexAccess;

  //ProgressionValue_Inspc* progrValue1;

  float x,y,a,b,c,zz;

  double dVal;
  int32 i32Val;
  int16 i16Val;
  int64 i64Val;
  int8 int8Val;
  bool bVal;

	TestUnion testUnion;

  int intArray[12];

  /**A thread which works with some values. */
  WorkingThread_Inspc_s workingThread;

  /**Management class for loading external reflection. */
  ExtReflectionJc_s extReflectionDsp;
  


}TestInspector;


extern struct ClassJc_t const reflection_TestInspector;

#endif //__TestInspector_h__
