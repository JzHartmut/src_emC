set TMP=..\..\tmp
if exist T:\tmp set TMP=T:\tmp\java2c_Jc
::del /F /Q ..\CRuntimeJavalike\J1c\*.*
if not exist %TMP% mkdir %TMP%
set CLASSPATH=../../exe/Java2C.jar;../../zbnfjax/zbnf.jar
call java -ea -cp %CLASSPATH% org.vishia.java2C.Java2C -cfg=Inspc.java2c.cfg -oc=../source -oh=../include -os=../stc -syntax:../../zbnfjax/zbnf --rlevel:334 --report:%TMP%/Inspc.java2c.rpt
if "%NOPAUSE%"=="" pause
