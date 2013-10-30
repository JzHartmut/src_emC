@echo off
set TMP=..\..\tmp
if exist T:\tmp set TMP=T:\tmp\Jc
if not exist %TMP% mkdir %TMP%
set OUTPUT=..\source\Fwc\Reflection_Fwc
set ZBNFJAX=..\..\zbnfjax

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
set INPUT=%INPUT% -i:../include:Fwc/fw_String.h
set INPUT=%INPUT% -i:../include:Fwc/fw_ThreadContext.h
set INPUT=%INPUT% -i:../include:Fwc/fw_timeconversions.h
set INPUT=%INPUT% -i:../include:Fwc/fw_Va_list.h
set INPUT=%INPUT% -i:../include:Fwc/objectBaseC.h


java -cp %ZBNFJAX%/zbnf.jar org.vishia.header2Reflection.CmdHeader2Reflection -out.c:../source/Fwc/Reflection_Fwc.c -c_only %INPUT% -b:Reflection.ctr -z:%ZBNFJAX%/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:334
if errorlevel 1 goto :error
goto :ende

:error
  @echo ======= error ========================
  pause
:ende
pause