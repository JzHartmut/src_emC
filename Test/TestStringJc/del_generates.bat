del /F /Q *.ncb
del /F /Q *.opt
del /F /Q *.plg
del /F /Q *.dsw
del /F /Q *.txt
del /F /Q *.rpt
if exist *.i del /F /Q *.i
if exist debug rmdir /S /Q debug
if exist tmp rmdir /S /Q tmp
if exist log\* del /F /Q log\*
::call del__testAll


