@echo off
set TMP=..\tmp
if exist T:\tmp set TMP=T:\tmp\Jc
if not exist %TMP% mkdir %TMP%

set INPUT=-i:../include/BlockHeap/*.h
set INPUT=%INPUT% -i:../source/BlockHeap/*.h

java -cp ../../zbnfjax/zbnf.jar;../../zbnfjax/header2Reflection.jar org.vishia.header2Reflection.CmdHeader2Reflection -out.c:../source/BlockHeap/Reflection_BlockHeap.c -c_only %INPUT% -b:Reflection.ctr -z:../../zbnfjax/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:334
if errorlevel 1 goto :error
goto :ende

:error
  @echo ======= error ========================
  pause
:ende
pause