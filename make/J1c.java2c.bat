set TMP=..\..\tmpJava2CJc
if exist T:\tmp set TMP=T:\tmp\java2c_Jc
::del /F /Q ..\source\J1c\*.*
if not exist %TMP% mkdir %TMP%
call java -ea -cp ../../Java2C.jar org.vishia.java2C.Java2C -cfg=J1c.java2c.cfg -oc=../source -oh=../include -os=../stc -syntax=../../zbnfjax/zbnf --rlevel:334 --report:%TMP%/java2cJc.rpt
pause
