REM use the S: drive as alias or symbolic link for all sources of CRuntimeJavalike.
REM adjust the directory path.
subst S: /D
subst S: d:\vishia

REM set the working area. The temporary files of Visual Studio are stored there too.
set WRK=T:\Msc6_TestThreadMutexWaitNotify

REM clean or create working area
if not exist %WRK% mkdir %WRK%
del /F/S/Q %WRK%\*
copy TestThreadMutexWaitNotify.dsp %WRK%\*

REM invoke visual studio in the working area with batch:
msc6.bat %WRK%\TestThreadMutexWaitNotify.dsp

