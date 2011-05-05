
#include "TestReflectTarget.h"
#include "SecondCpuData.h"

#include "Jc/ObjectJc.h"
#include "Jc/ReflectionJc.h"

//#include "InspcJ2c/ModulAcq_Inspc.h"
//#include "InspcJ2c/FactoryDevice_Inspc.h"
#include "InspcJ2c/Inspector_Inspc.h"
#include <stdlib.h>
#include <math.h>


TestInspector data;

Inspector_Inspc_s theInspector;




void initInspector(ObjectJc* appl)
{ //struct ModulAcq_Inspc_t* inspector;
  STACKTRC_ENTRY("initInspector");
  //inspector = create_ii_Device_modulifcInspc_FactoryDevice_Inspc(appl, 0, 60078);
  init_ObjectJc(&theInspector.base.object, sizeof(theInspector), 0);
  ctorO_Inspector_Inspc(&theInspector.base.object, s0_StringJc("UDP:0.0.0.0:60080"), _thCxt);

  data.reflexAccess = &theInspector;

  /**Progression value, create it for any value capturing. */
  //data.progrValue1 = create_ProgressionValue_Inspc(inspector, 'A', 12, 300);

  //createCommThread_ModulAcq_Inspc(inspector);
  start_Inspector_Inspc_F(&theInspector, &data.object, _thCxt); 
  //addApplication_Inspc(inspector, &inspector->base.object);
  STACKTRC_LEAVE;
}




void calculate()
{ float r = rand() / 32768.0F;
  data.b += 0.1F;
  if(data.b > 6.28F){ data.b = 0; }
  data.c = 100.0F * (float)sin(data.b) + r;
  data.a += data.y;
  if(data.a >=10){
    data.y = -0.17F;
  }
  if(data.a <=-10){
    data.y = 0.243F;
  }
  data.x = data.a + r;
}



void main()
{ StringJc sExtReflectionFile = CONST_z_StringJc("genRefl/Reflection_Dsp.bin");
	int headerOffset = 0;
	//StringJc sExtReflectionFile = CONST_z_StringJc("xxx");
	//int headerOffset = 0x70;
	STACKTRC_ENTRY("main");
  init_ObjectJc(&data.object, sizeof(data), 0);
  setReflection_ObjectJc(&data.object, &reflection_TestInspector, 0);

  init_ObjectJc(&data.workingThread.base.object, sizeof(data.workingThread), 0);
  ctorO_WorkingThread_Inspc(&data.workingThread.base.object, _thCxt);


  if(load_ExtReflectionJc(&data.extReflectionDsp, sExtReflectionFile, headerOffset)==null){
    data._DSP_ = (void*)(-1);
  }
  initDsp();
  data.y = 0.143F;
  initInspector(null);

  start_WorkingThread_Inspc(&data.workingThread, _thCxt);

  while(true)
  { int iTime;
    sleep_ThreadJc(10, _thCxt);
    for(iTime = 0; iTime < 50; iTime++)
    { calculate();
      //TODO capture_ProgressionValue_Inspc(data.progrValue1);
    }
  }

  terminate_WorkingThread_Inspc(&data.workingThread, _thCxt);

  STACKTRC_LEAVE;
}
