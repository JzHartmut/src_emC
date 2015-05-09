@echo off
set TMP=..\..\tmp
if exist T:\tmp set TMP=T:\tmp\Jc
if exist D:\tmp set TMP=D:\tmp\Jc
if not exist %TMP% mkdir %TMP%
set OUTPUT=..\source\refl\Reflection_OSAL
REM either use local zbnfjax folder or the setZBNFJAX_HOME.bat should be able to locate in the PATH.
if exist ..\..\zbnfjax set ZBNFJAX_HOME=..\..\zbnfjax
if not exist ..\..\zbnfjax call setZBNFJAX_HOME.bat

if exist %OUTPUT%.c del /F /Q %OUTPUT%.c 


set INPUT=
set INPUT=%INPUT% -i:../include/OSAL:os_types_def_common.h
set INPUT=%INPUT% -i:../include/OSAL:os_AtomicAccess.h
set INPUT=%INPUT% -i:../include/OSAL:os_endian.h
set INPUT=%INPUT% -i:../include/OSAL:os_error.h
set INPUT=%INPUT% -i:../include/OSAL:os_file.h
set INPUT=%INPUT% -i:../include/OSAL:os_mem.h
set INPUT=%INPUT% -i:../include/OSAL:os_socket.h
set INPUT=%INPUT% -i:../include/OSAL:os_sync.h
set INPUT=%INPUT% -i:../include/OSAL:os_thread.h
set INPUT=%INPUT% -i:../include/OSAL:os_time.h
set INPUT=%INPUT% -i:../include/OSAL:os_waitnotify.h

echo on
java -cp %ZBNFJAX_HOME%/zbnf.jar org.vishia.header2Reflection.CmdHeader2Reflection -out.c:%OUTPUT%.c -c_only %INPUT% -b:ReflectionJc.ctr -z:%ZBNFJAX_HOME%/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:334
if errorlevel 1 goto :error
goto :ende

:error
  @echo ======= error ========================
  pause
:ende
pause
