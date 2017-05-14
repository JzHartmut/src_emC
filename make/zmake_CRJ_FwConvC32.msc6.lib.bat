@echo off
set TARGET=CRJ_FwConvC32.msc6.lib
set OBJPATH=T:\CRJ_%TARGET%




REM Note DATE2C is compiled in 1999 under DOS. It seems be the best of all programs.
REM But it does not run under Windows7 because it is a 16 bit application.
REM It works proper in the XP-VM.
REM delete and generate newly if this is the develop PC.

if "" == "%NOPAUSE%" set NOPAUSE=zmake_%TARGET%

REM force to compile ccs_reflection_offset because the dependency check does not work for it.
REM It includes ccs_reflection_offset.crefl which has not the extension .h. That is because search in sources should not use that file.
::if exist ..\..\..\%OBJDIR%\XRPDC\src\dsp_ccs\ccs_reflection_offset.doj del ..\..\..\%OBJDIR%\XRPDC\src\dsp_ccs\ccs_reflection_offset.doj
::call genReflection.bat

call setZBNFJAX_HOME.bat

::goto :zmake
echo Generating %TARGET%

REM call common generation with copied files of plant:
::if exist ..\out\dsp_ccs.bin del /F /Q ..\out\dsp_ccs.bin
if exist _gen.bat del /F /Q _gen.bat

set SBOX_DIR=%CD%\..
java.exe -cp "%ZBNFJAX_HOME%/zbnf.jar" org.vishia.jztxtcmd.JZtxtcmd %0 -t:_gen.bat
if errorlevel 1 goto :error

::echo on
echo call make\_gen.bat
call _gen.bat
if "" == "%NOPAUSE%" pause

:okcompiled
goto :ende

:errorEnv
  echo The both environment variables OBJDIR and TARGET and PARAM should be set. Set it before call this batch!
  pause
  goto :ende

:error
  echo ERROR

:ende
if "%NOPAUSE%" == "" pause
exit /B %ERRORLEVEL%


==JZtxtcmd==

include JZtxtcmd/Msc6.zmake.jztc;

currdir=<:><&scriptdir>/..<.>;

Fileset  includePath = 
( incApplSpecific/FwConvC32  ##This is the applstdefJc.h-directory, defines the platform.
, source
, source/OSAL
, sourceSpecials
, sourceSpecials/os_Windows_Msc6
, ./.                        ##uses CRJ base directory as include path
);

Fileset src_make=
( source/Fwc/*.c
, source/Jc/*.c
, source/J1c/*.c
, source/Ipc/*.c
, source/Ipc2c/*.c
, source/InspcJ2c/*.c
, source/MsgDisp/*.c
, source/OSAL/*.c
, source/BlockHeap/*.c
, source/refl/*.c
, sourceSpecials/os_Windows_Msc6/*.c
, sourceSpecials/osal_Windows32/*.c
);

String compileOptions=<:>/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /TP /c<.>; 
##String compileOptions=<:>/nologo /Zp1 /MTd /W4 /ZI /Od  /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FAcs /FD /GZ /TP /c <.>;



##
##The main() routine invokes zmake.
##
main(){
  ##outputs with <+> are done to that file which is given with jztxtcmd cmdline arg -t:File
  ##it is the _gen.bat file. This is executing to invoke the compiler 
  <+>
  @echo off
  call Msc6setpath.bat            ##should be able to found in the system's PATH, set path to compiler tools cl.exe and lib.exe
  PATH ><&objDir>/_cc_error.txt   ##report path in out file.
  ::goto :noSubst
  echo on
  subst X: /D
  subst X: ..
  
  X:
  cd \
  dir
  ::cd make
  ::dir
  pause
  echo off
  
  :noSubst
  set SBOX_DIR=<&$SBOX_DIR>
  set OBJPATH=<&$OBJPATH>
  if not exist <&objDirW> mkdir <&objDirW>
  <.+>    
  zmake ../CRJlibMsc6/CRJ_FwConvC32.msc6.lib := cc(.:&src_make, compilerOptions=compileOptions);
  zmake ../CRJlibMsc6/CRJ_FwConvC32.msc6.lib := clib(.:&src_make, compilerOptions=compileOptions);
  <+>
  if "%NOPAUSE%"=="" pause
  goto :ende
  :error
    echo ERROR, abort generation. See file <&objDir>/_cc_error.txt in 
    pause
    notepad <&objDir>/_cc_error.txt
  :ende  
  <.+>
  onerror{
    <+out>ERROR: <&error><.+n>
  }
}



