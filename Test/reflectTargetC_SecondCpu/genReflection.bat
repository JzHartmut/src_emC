@echo off

set INPUT=-i:src/SecondCpuData.h
java -cp ../../../zbnfjax/zbnf.jar org.vishia.header2Reflection.CmdHeader2Reflection -z:../../../zbnfjax/zbnf/Cheader.zbnf %INPUT% -out.c:genRefl/Reflection_Dsp.c -obinl:genRefl/Reflection_Dsp.bin -offs:genRefl/ReflectionOffset_Dsp.c -b:src/Reflection.cfg --report:genRefl/genReflection_Dsp.rpt --rlevel:334

set INPUT=-i:src/TestReflectTarget.h
::call zbnfjax Header2Reflection 

java -cp ../../../zbnfjax/zbnf.jar org.vishia.header2Reflection.CmdHeader2Reflection -z:../../../zbnfjax/zbnf/Cheader.zbnf %INPUT% -out.c:genRefl/Reflection_TestReflectTarget.c -b:src/Reflection.cfg --report:genRefl/genReflectionInspector.rpt --rlevel:334

pause