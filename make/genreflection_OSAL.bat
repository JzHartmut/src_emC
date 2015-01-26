@echo off
set TMP=..\tmp
if exist T:\tmp set TMP=T:\tmp\Jc
if exist D:\tmp set TMP=D:\tmp\Jc
if not exist %TMP% mkdir %TMP%
set OUTPUT=..\source\refl\Reflection_OSAL.c

del %OUTPUT%

set INPUT=
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

java -cp ../../zbnfjax/zbnf.jar;../../zbnfjax/header2Reflection.jar org.vishia.header2Reflection.CmdHeader2Reflection -out.c:%OUTPUT% -c_only %INPUT% -b:ReflectionJc.ctr -z:../../zbnfjax/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:335
if errorlevel 1 goto :error
goto :ende

:error
  @echo ======= error ========================
  pause
:ende
pause
