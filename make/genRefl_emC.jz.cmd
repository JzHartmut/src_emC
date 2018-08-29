REM start problem: The batch needs the zbnf.jar File. Either the ZBNFJAX_HOME environment variable is set already,
REM or it is set via a found setZBNFJAX_HOME.bat, or it is on D:\vishia... or you should adapt it.
call setZBNFJAX_HOME.bat
if "%ZBNFJAX_HOME%" == "" set ZBNFJAX_HOME=D:/vishia/ZBNF/zbnfjax
java -cp %ZBNFJAX_HOME%/zbnf.jar org.vishia.jztxtcmd.JZtxtcmd %0
pause
if ERRORLEVEL 1 pause
exit /B

==JZtxtcmd==

include $ZBNFJAX_HOME/jzTc/Cheader2Refl.jztxt.cmd;
currdir=scriptdir;

Fileset headers = 
( source:emC/*.h
, source:Jc/*.h
, source:Ipc/*.h
, source:Inspc/*.h
, source:OSAL/os_file.h
, source:OSAL/os_sharedmem.h
, source:OSAL/os_socket.h
);

main()
{
  mkdir T:/header/Jc;
  zmake "../genRefl/*.crefl" := genReflection(..&headers, html="T:/header"); 
  
  <+out>success<.+n>

}

