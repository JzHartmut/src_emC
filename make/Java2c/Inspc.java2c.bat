set TMP=..\..\tmp
if exist T:\tmp set TMP=T:\tmp\java2c_Jc
if not exist %TMP% mkdir %TMP%
::set JAVA2CPATH=../..
set JAVA2CPATH=D:/vishia/Java2C/sf/Java2C

::set CLASSPATH=../../exe/Java2C.jar;../../zbnfjax/zbnf.jar
set CLASSPATH=%JAVA2CPATH%/exe/Java2C.jar;%JAVA2CPATH%/zbnfjax/zbnf.jar
call java -ea -cp %CLASSPATH% org.vishia.java2C.Java2C -cfg=Inspc.java2c.cfg -oc=../source -oh=../source -os=../stc -syntax:%JAVA2CPATH%/zbnfjax/zbnf --rlevel:334 --report:%TMP%/Inspc.java2c.rpt
if "%NOPAUSE%"=="" pause
