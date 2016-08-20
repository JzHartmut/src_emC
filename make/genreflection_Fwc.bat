@echo off
set TMP=..\..\tmp
if exist T:\tmp set TMP=T:\tmp\Jc
if exist D:\tmp set TMP=D:\tmp\Jc
if not exist %TMP% mkdir %TMP%
set OUTPUT=..\source\refl\Reflection_Fwc

REM either use local zbnfjax folder or the setZBNFJAX_HOME.bat should be able to locate in the PATH.
if exist ..\..\zbnfjax set ZBNFJAX_HOME=..\..\zbnfjax
if not exist ..\..\zbnfjax call setZBNFJAX_HOME.bat

if exist %OUTPUT%.c del /F /Q %OUTPUT%.c 


set INPUT=
::set INPUT=%INPUT% -i:../include:Fwc/fw_basic.h
::set INPUT=%INPUT% -i:../include:Fwc/fw_Event.h
set INPUT=%INPUT% -i:../include:Fwc/fw_Exception.h
set INPUT=%INPUT% -i:../include:Fwc/fw_Formatter.h
set INPUT=%INPUT% -i:../include:Fwc/fw_LogMessage.h
set INPUT=%INPUT% -i:../include:Fwc/fw_MemC.h
set INPUT=%INPUT% -i:../include:Fwc/fw_Readline.h
set INPUT=%INPUT% -i:../include:Fwc/fw_SimpleC.h
::set INPUT=%INPUT% -i:../include:Fwc/fw_StateM.h
::set INPUT=%INPUT% -i:../include:Fwc/fw_String.h
set INPUT=%INPUT% -i:../include:Fwc/fw_ThreadContext.h
set INPUT=%INPUT% -i:../include:Fwc/fw_timeconversions.h
set INPUT=%INPUT% -i:../include:Fwc/fw_Va_list.h
set INPUT=%INPUT% -i:../include:Fwc/objectBaseC.h

echo on
java -cp %ZBNFJAX_HOME%/zbnf.jar org.vishia.header2Reflection.CmdHeader2Reflection -out.c:%OUTPUT%.c -c_only %INPUT% -b:ReflectionJc.ctr -z:%ZBNFJAX_HOME%/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:334
if errorlevel 1 goto :error
goto :ende

:error
  @echo ======= error ========================
  pause
:ende
pause