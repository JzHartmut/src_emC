@echo off
set TMP=..\..\..\tmp
if exist T:\tmp set TMP=T:\tmp\Jc
if exist D:\tmp set TMP=D:\tmp\Jc
if not exist %TMP% mkdir %TMP%

set INPUT= -i:TimeSignals_Inspc.h
set OUTPUT=.\TimeSignals_Inspc_Refl

REM either use local zbnfjax folder or the setZBNFJAX_HOME.bat should be able to locate in the PATH.
if exist ..\..\..\zbnfjax set ZBNFJAX_HOME=..\..\zbnfjax
if not exist ..\..\..\zbnfjax call setZBNFJAX_HOME.bat

if exist %OUTPUT%.crefl del /F /Q %OUTPUT%.crefl 

echo on
java -cp %ZBNFJAX_HOME%/zbnf.jar org.vishia.header2Reflection.CmdHeader2Reflection -out.c:%OUTPUT%.crefl -c_only %INPUT% -b:../../make/ReflectionJc.ctr -z:%ZBNFJAX_HOME%/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:334
if errorlevel 1 goto :error
goto :ende

:error
  @echo ======= error ========================
  pause
:ende
pause