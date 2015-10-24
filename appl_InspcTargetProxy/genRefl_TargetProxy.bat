@echo off
::set ZBNFJAX=../../zbnfjax
set ZBNFJAX=D:\vishia\ZBNF\sf\ZBNF\zbnfjax

set INPUT=
set INPUT=%INPUT% -i:srcTargetProxy/InspcTargetProxy.h
set INPUT=%INPUT% -i:include/InspcTargetProxyTelg.h
::call zbnfjax Header2Reflection 

java -cp %ZBNFJAX%/zbnf.jar org.vishia.header2Reflection.CmdHeader2Reflection -z:%ZBNFJAX%/zbnf/Cheader.zbnf %INPUT% -out.c:2srcTargetProxy/Refl_InspcTargetProxy.c -b:srcTargetProxy/Reflection.cfg --report:D:\TMP\genRefl/Refl_InspcTargetProxy.rpt --rlevel:334

pause