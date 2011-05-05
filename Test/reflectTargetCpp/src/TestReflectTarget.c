
#include "TestReflectTargetCpp.h"

#include "Jc/ObjectJc.h"
#include "Jc/ThreadJc.h"
#include "Jc/ReflectionJc.h"

#include <InspcJ2c/Inspector_Inspc.h>
#include <stdlib.h>
#include <math.h>


Main mainData;

Inspector_Inspc* theInspector;




void initInspector(ObjectJc* appl)
{ //struct ModulAcq_Inspc_t* inspector;
  STACKTRC_ENTRY("initInspector");
  //inspector = create_ii_Device_modulifcInspc_FactoryDevice_Inspc(appl, 0, 60078);
  theInspector = new Inspector_Inspc("UDP:0.0.0.0:60078");
  
  //data.reflexAccess = &theInspector;

  //start_Inspector_Inspc_F(&theInspector, &data.object, _thCxt); 
  theInspector->start(&mainData);
  STACKTRC_LEAVE;
}





void main()
{ STACKTRC_ENTRY("main");
  initInspector(null);


  while(true)
  { int iTime;
    //ThreadJcpp::sleep(10);
    sleep_ThreadJc(10, _thCxt);
    for(iTime = 0; iTime < 50; iTime++)
    { mainData.execute();
      //TODO capture_ProgressionValue_Inspc(data.progrValue1);
    }
  }


  STACKTRC_LEAVE;
}

extern_C const ClassJc reflection_Main;
  
Main::Main()
{ //init the Object-base data. 
  //Hint: If the class is derived, the derived constructor is called after this ctor and overwrites the Object's values.
  initReflection_ObjectJc(this, this, sizeof(Main),&reflection_Main, 0);
  sibling = new SubData();
  data2 = new Data2();
}


void Main::execute()
{
}

METHOD_C int32 getInfo_RemoteCpuJc(Cmd_RemoteCpuJc_e cmd, int device, struct RemoteAddressJc* address, int32 input)
{ return -1; }


