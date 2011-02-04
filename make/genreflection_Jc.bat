@echo off
set TMP=..\tmp
if exist T:\tmp set TMP=T:\tmp\Jc
if not exist %TMP% mkdir %TMP%

::java -cp ../zbnfjax/zbnf.jar;../zbnfjax/header2Reflection.jar org.vishia.header2Reflection.CmdHeader2Reflection -out.c:../gen/AllReflectionsJc.c -c_only -i:..:BlockHeap/*.h -i:..:Fwc/*.h -i:..:Jc/*.h -i:..:MsgDisp/*.h -i:..:OSAL/inc/*.h -b:../ReflectionBlockedTypes.ctr -z:../zbnfjax/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:334

set INPUT=
set INPUT=%INPUT% -i:../include:Jc/AbstractListJc.h
set INPUT=%INPUT% -i:../include:Jc/ArraysJc.h
//set INPUT=%INPUT% -i:../include:Jc/byteDataJc.h
set INPUT=%INPUT% -i:../include:Jc/ComparatorJc.h
set INPUT=%INPUT% -i:../include:Jc/ConcurrentLinkedQueueJc.h
//set INPUT=%INPUT% -i:../include:Jc/ConcurrentRingBufferJc.h
set INPUT=%INPUT% -i:../include:Jc/DateJc.h
set INPUT=%INPUT% -i:../include:Jc/LocaleJc.h
set INPUT=%INPUT% -i:../include:Jc/SystemJc.h
set INPUT=%INPUT% -i:../include:Jc/ObjectJc.h
set INPUT=%INPUT% -i:../include:Jc/LinkedListJc.h
set INPUT=%INPUT% -i:../include:Jc/ListIteratorJc.h
set INPUT=%INPUT% -i:../include:Jc/ListJc.h
set INPUT=%INPUT% -i:../include:Jc/ListMapEntryJc.h
set INPUT=%INPUT% -i:../include:Jc/StringJc.h
set INPUT=%INPUT% -i:../include:Jc/OsWrapperJc.h
set INPUT=%INPUT% -i:../include:Jc/ReflectionJc.h
set INPUT=%INPUT% -i:../include:Jc/ReflMemAccessJc.h
set INPUT=%INPUT% -i:../include:Jc/StringBufferJc.h
set INPUT=%INPUT% -i:../include:Jc/FileIoJc.h
set INPUT=%INPUT% -i:../include:Jc/ObjectRefJc.h
set INPUT=%INPUT% -i:../include:Jc/ThreadJc.h
set INPUT=%INPUT% -i:../include:Jc/FormatterJc.h
set INPUT=%INPUT% -i:../include:Jc/TimeZoneJc.h
set INPUT=%INPUT% -i:../include:Jc/StringJc_intern.h

set INPUT=%INPUT% -i:../include:MsgDisp/VaArgBuffer.h

java -cp ../../zbnfjax/header2Reflection.jar org.vishia.header2Reflection.CmdHeader2Reflection -out.c:../source/Jc/Reflection_AllJc.c -c_only %INPUT% -b:Reflection.ctr -z:../../zbnfjax/zbnf/Cheader.zbnf --report:%TMP%/genReflection.rpt --rlevel:334
if errorlevel 1 goto :error
goto :ende

:error
  @echo ======= error ========================
  pause
:ende
pause
