@echo off


set INPUT=-i:src/TestReflectTargetCpp.h

java -jar ../../zbnfjax/header2Reflection.jar
pause
java -jar ../../zbnfjax/header2Reflection.jar -z:../../zbnfjax/zbnf/Cheader.zbnf %INPUT% -out.c:genRefl/Reflection_TestReflectTarget.c -b:src/Reflection.cfg --report:genRefl/genReflectionInspector.rpt --rlevel:334

pause