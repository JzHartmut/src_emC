@echo off
set TMP=..\..\tmp
if exist T:\tmp set TMP=T:\tmp\Jc
if not exist %TMP% mkdir %TMP%

set INPUT= -i:../include:Ipc/*.h

java -cp ../../zbnfjax/zbnf.jar org.vishia.header2Reflection.CmdHeader2Reflection %INPUT% -out.c:../source/Ipc/Reflection_Ipc.c -c_only  -b:Reflection.ctr -z:../../zbnfjax/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:334
if errorlevel 1 goto :error
goto :ende

:error
  @echo ======= error ========================
  pause
:ende
pause