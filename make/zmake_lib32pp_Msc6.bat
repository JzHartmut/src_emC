@echo off
set TARGET=lib32pp_Msc6
set OBJPATH=T:\CRJ_%TARGET%

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
if exist gen_.bat del /F /Q gen_.bat

set SBOX_DIR=..
java.exe -cp "%ZBNFJAX_HOME%/zbnf.jar" org.vishia.jzTc.JzTc make/zmake_%TARGET%.bat -t:make/_gen.bat
if errorlevel 1 goto :error

::echo on
echo call make\_gen.bat
call make\_gen.bat
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


==JZcmd==

include jzTc/Msc6.zmake.jzTc;

currdir=<:>scriptdir/..<.>;

Fileset  includePath = 
( source
, include/OSAL
, include 
, sourceSpecials
, sourceSpecials/ExcHandling_Printf.template
, sourceSpecials/os_Windows_Msc6
, ./.               //uses CRJ base directory as include path
);

Fileset src_make=
( source/Fwc/*.c);


String compileOptions=<:>/nologo /Zp1 /MTd /W4 /ZI /Od  /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FAcs /FD /GZ /TP /c <.>;

//Compilation and linking in one target, see control file VDSP.zmake.ctr
//..\out\dsp_ccs.bin := cc($src_make, compileOptions=$compileOptions);

sub zmake(){
  zmake ..\CRJlibMsc6\%TARGET%.lib := cc(.:&src_make, compilerOptions=compileOptions);
  zmake CRJlibMsc6\CRJ32pp.lib := clib(.:&src_make, compilerOptions=compileOptions);
  onerror{
    <+out>ERROR: <&error><.+n>
  }
}



