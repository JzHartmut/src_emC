@echo off
REM This file generates a reflection file only with that reflections there are used for this compilation. 

REM Fill the INPUT environment variable with all command options -i:files. It is used internally:
set INPUT=
set INPUT=%INPUT% -i:../Jc/DateJc.h
set INPUT=%INPUT% -i:../OSAL/inc/os_time.h
set INPUT=%INPUT% -i:../Jc/ListMapEntryJc.h 
set INPUT=%INPUT% -i:../Jc/ObjectJc.h 
//set INPUT=%INPUT% -i:../Fwc/fw_time.h
//set INPUT=%INPUT% -i:../Jc/StringJc.h

call zbnfjax Header2Reflection -out.c:src/Reflection_TestStringJc.c -b:src/ReflectionBlockedTypes.txt --report:header2Reflection.log --rlevel:333

pause