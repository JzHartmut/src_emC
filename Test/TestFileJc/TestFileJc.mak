# Microsoft Developer Studio Generated NMAKE File, Based on TestFileJc.dsp
!IF "$(CFG)" == ""
CFG=TestFileJc - Win32 DebugCpp
!MESSAGE No configuration specified. Defaulting to TestFileJc - Win32 DebugCpp.
!ENDIF 

!IF "$(CFG)" != "TestFileJc - Win32 Release" && "$(CFG)" != "TestFileJc - Win32 Debug_C" && "$(CFG)" != "TestFileJc - Win32 DebugCpp"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestFileJc.mak" CFG="TestFileJc - Win32 DebugCpp"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestFileJc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TestFileJc - Win32 Debug_C" (based on "Win32 (x86) Console Application")
!MESSAGE "TestFileJc - Win32 DebugCpp" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestFileJc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TestFileJc.exe"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_Formatter.obj"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_error.obj"
	-@erase "$(INTDIR)\os_file.obj"
	-@erase "$(INTDIR)\os_mem.obj"
	-@erase "$(INTDIR)\os_mutex.obj"
	-@erase "$(INTDIR)\os_thread.obj"
	-@erase "$(INTDIR)\os_time.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\ReflectionBaseTypesJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\TestFileJc.obj"
	-@erase "$(INTDIR)\TestFileJcMain.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestFileJc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "../../includeSpecials/os_Windows" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\TestFileJc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestFileJc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestFileJc.pdb" /machine:I386 /out:"$(OUTDIR)\TestFileJc.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\TestFileJc.obj" \
	"$(INTDIR)\TestFileJcMain.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_Formatter.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\os_atomic.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_mem.obj" \
	"$(INTDIR)\os_mutex.obj" \
	"$(INTDIR)\os_thread.obj" \
	"$(INTDIR)\os_time.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\ReflectionBaseTypesJc.obj" \
	"$(INTDIR)\allocOnlyAtStartup.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\LocaleJc.obj"

"$(OUTDIR)\TestFileJc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"

OUTDIR=T:\Jc\TestBlockHeap_C
INTDIR=T:\Jc\TestBlockHeap_C
# Begin Custom Macros
OutDir=T:\Jc\TestBlockHeap_C
# End Custom Macros

ALL : "$(OUTDIR)\TestFileJc.exe" "$(OUTDIR)\TestFileJc.bsc"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\allocOnlyAtStartup.sbr"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\DateJc.sbr"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileIoJc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_Formatter.obj"
	-@erase "$(INTDIR)\fw_Formatter.sbr"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMessage.sbr"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_MemC.sbr"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_Object.sbr"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.sbr"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_SimpleC.sbr"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_String.sbr"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_threadContext.sbr"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\fw_timeconversions.sbr"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\LocaleJc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_atomic.sbr"
	-@erase "$(INTDIR)\os_error.obj"
	-@erase "$(INTDIR)\os_error.sbr"
	-@erase "$(INTDIR)\os_file.obj"
	-@erase "$(INTDIR)\os_file.sbr"
	-@erase "$(INTDIR)\os_mem.obj"
	-@erase "$(INTDIR)\os_mem.sbr"
	-@erase "$(INTDIR)\os_mutex.obj"
	-@erase "$(INTDIR)\os_mutex.sbr"
	-@erase "$(INTDIR)\os_thread.obj"
	-@erase "$(INTDIR)\os_thread.sbr"
	-@erase "$(INTDIR)\os_time.obj"
	-@erase "$(INTDIR)\os_time.sbr"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.sbr"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\ReflectionBaseTypesJc.obj"
	-@erase "$(INTDIR)\ReflectionBaseTypesJc.sbr"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.sbr"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringJc.sbr"
	-@erase "$(INTDIR)\TestFileJc.obj"
	-@erase "$(INTDIR)\TestFileJc.sbr"
	-@erase "$(INTDIR)\TestFileJcMain.obj"
	-@erase "$(INTDIR)\TestFileJcMain.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestFileJc.bsc"
	-@erase "$(OUTDIR)\TestFileJc.exe"
	-@erase "$(OUTDIR)\TestFileJc.map"
	-@erase "$(OUTDIR)\TestFileJc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MLd /W3 /Gm /GX /ZI /Od /I "../../includeSpecials/os_Windows" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FAcs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestFileJc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DateJc.sbr" \
	"$(INTDIR)\FileIoJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\StringBufferJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\TestFileJc.sbr" \
	"$(INTDIR)\TestFileJcMain.sbr" \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_Formatter.sbr" \
	"$(INTDIR)\fw_LogMessage.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\os_atomic.sbr" \
	"$(INTDIR)\os_file.sbr" \
	"$(INTDIR)\os_mem.sbr" \
	"$(INTDIR)\os_mutex.sbr" \
	"$(INTDIR)\os_thread.sbr" \
	"$(INTDIR)\os_time.sbr" \
	"$(INTDIR)\Reflection_AllJc.sbr" \
	"$(INTDIR)\Reflection_Fwc.sbr" \
	"$(INTDIR)\ReflectionBaseTypesJc.sbr" \
	"$(INTDIR)\allocOnlyAtStartup.sbr" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" \
	"$(INTDIR)\fw_String.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
	"$(INTDIR)\os_error.sbr" \
	"$(INTDIR)\LocaleJc.sbr"

"$(OUTDIR)\TestFileJc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestFileJc.pdb" /map:"$(INTDIR)\TestFileJc.map" /debug /machine:I386 /out:"$(OUTDIR)\TestFileJc.exe" /pdbtype:sept /libpath:"D:\Progs\MSC6\act\Microsoft Visual Studio\VC98\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\TestFileJc.obj" \
	"$(INTDIR)\TestFileJcMain.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_Formatter.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\os_atomic.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_mem.obj" \
	"$(INTDIR)\os_mutex.obj" \
	"$(INTDIR)\os_thread.obj" \
	"$(INTDIR)\os_time.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\ReflectionBaseTypesJc.obj" \
	"$(INTDIR)\allocOnlyAtStartup.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\LocaleJc.obj"

"$(OUTDIR)\TestFileJc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"

OUTDIR=T:\Jc\TestFileJc
INTDIR=T:\Jc\TestFileJc
# Begin Custom Macros
OutDir=T:\Jc\TestFileJc
# End Custom Macros

ALL : "$(OUTDIR)\TestFileJc.exe" "$(OUTDIR)\TestFileJc.bsc"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\allocOnlyAtStartup.sbr"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\DateJc.sbr"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileIoJc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_Formatter.obj"
	-@erase "$(INTDIR)\fw_Formatter.sbr"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMessage.sbr"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_MemC.sbr"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_Object.sbr"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.sbr"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_SimpleC.sbr"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_String.sbr"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_threadContext.sbr"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\fw_timeconversions.sbr"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\LocaleJc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_atomic.sbr"
	-@erase "$(INTDIR)\os_error.obj"
	-@erase "$(INTDIR)\os_error.sbr"
	-@erase "$(INTDIR)\os_file.obj"
	-@erase "$(INTDIR)\os_file.sbr"
	-@erase "$(INTDIR)\os_mem.obj"
	-@erase "$(INTDIR)\os_mem.sbr"
	-@erase "$(INTDIR)\os_mutex.obj"
	-@erase "$(INTDIR)\os_mutex.sbr"
	-@erase "$(INTDIR)\os_thread.obj"
	-@erase "$(INTDIR)\os_thread.sbr"
	-@erase "$(INTDIR)\os_time.obj"
	-@erase "$(INTDIR)\os_time.sbr"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.sbr"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\ReflectionBaseTypesJc.obj"
	-@erase "$(INTDIR)\ReflectionBaseTypesJc.sbr"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.sbr"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringJc.sbr"
	-@erase "$(INTDIR)\TestFileJc.obj"
	-@erase "$(INTDIR)\TestFileJc.sbr"
	-@erase "$(INTDIR)\TestFileJcMain.obj"
	-@erase "$(INTDIR)\TestFileJcMain.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestFileJc.bsc"
	-@erase "$(OUTDIR)\TestFileJc.exe"
	-@erase "$(OUTDIR)\TestFileJc.ilk"
	-@erase "$(OUTDIR)\TestFileJc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../../includeSpecials/os_Windows" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestFileJc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /TP /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestFileJc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DateJc.sbr" \
	"$(INTDIR)\FileIoJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\StringBufferJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\TestFileJc.sbr" \
	"$(INTDIR)\TestFileJcMain.sbr" \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_Formatter.sbr" \
	"$(INTDIR)\fw_LogMessage.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\os_atomic.sbr" \
	"$(INTDIR)\os_mem.sbr" \
	"$(INTDIR)\os_mutex.sbr" \
	"$(INTDIR)\os_thread.sbr" \
	"$(INTDIR)\os_time.sbr" \
	"$(INTDIR)\Reflection_AllJc.sbr" \
	"$(INTDIR)\Reflection_Fwc.sbr" \
	"$(INTDIR)\ReflectionBaseTypesJc.sbr" \
	"$(INTDIR)\allocOnlyAtStartup.sbr" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" \
	"$(INTDIR)\os_file.sbr" \
	"$(INTDIR)\fw_String.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
	"$(INTDIR)\os_error.sbr" \
	"$(INTDIR)\LocaleJc.sbr"

"$(OUTDIR)\TestFileJc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestFileJc.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestFileJc.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\TestFileJc.obj" \
	"$(INTDIR)\TestFileJcMain.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_Formatter.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\os_atomic.obj" \
	"$(INTDIR)\os_mem.obj" \
	"$(INTDIR)\os_mutex.obj" \
	"$(INTDIR)\os_thread.obj" \
	"$(INTDIR)\os_time.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\ReflectionBaseTypesJc.obj" \
	"$(INTDIR)\allocOnlyAtStartup.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\LocaleJc.obj"

"$(OUTDIR)\TestFileJc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TestFileJc.dep")
!INCLUDE "TestFileJc.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestFileJc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestFileJc - Win32 Release" || "$(CFG)" == "TestFileJc - Win32 Debug_C" || "$(CFG)" == "TestFileJc - Win32 DebugCpp"
SOURCE=..\..\source\Jc\DateJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\DateJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\DateJc.obj"	"$(INTDIR)\DateJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\DateJc.obj"	"$(INTDIR)\DateJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\FileIoJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\FileIoJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\FileIoJc.obj"	"$(INTDIR)\FileIoJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\FileIoJc.obj"	"$(INTDIR)\FileIoJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\LocaleJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\LocaleJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ObjectJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\ObjectJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ReflectionJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\ReflectionJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"

!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"

!ENDIF 

SOURCE=..\..\source\Jc\StringBufferJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\StringBufferJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\StringJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\StringJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=src\TestFileJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\TestFileJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\TestFileJc.obj"	"$(INTDIR)\TestFileJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\TestFileJc.obj"	"$(INTDIR)\TestFileJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\TestFileJcMain.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\TestFileJcMain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\TestFileJcMain.obj"	"$(INTDIR)\TestFileJcMain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\TestFileJcMain.obj"	"$(INTDIR)\TestFileJcMain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Exception.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_Exception.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_ExceptionPrintStacktrace.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Formatter.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_Formatter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_Formatter.obj"	"$(INTDIR)\fw_Formatter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_Formatter.obj"	"$(INTDIR)\fw_Formatter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_LogMessage.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_LogMessage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_MemC.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_MemC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Object.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_Object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_SimpleC.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_SimpleC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_String.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_String.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_String.obj"	"$(INTDIR)\fw_String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_String.obj"	"$(INTDIR)\fw_String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_threadContext.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_threadContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_timeconversions.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_timeconversions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_atomic.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\os_atomic.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\os_atomic.obj"	"$(INTDIR)\os_atomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\os_atomic.obj"	"$(INTDIR)\os_atomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_error.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\os_error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\os_error.obj"	"$(INTDIR)\os_error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\os_error.obj"	"$(INTDIR)\os_error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_file.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\os_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\os_file.obj"	"$(INTDIR)\os_file.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\os_file.obj"	"$(INTDIR)\os_file.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_mem.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\os_mem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\os_mem.obj"	"$(INTDIR)\os_mem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\os_mem.obj"	"$(INTDIR)\os_mem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_mutex.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\os_mutex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\os_mutex.obj"	"$(INTDIR)\os_mutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\os_mutex.obj"	"$(INTDIR)\os_mutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_thread.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\os_thread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\os_thread.obj"	"$(INTDIR)\os_thread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\os_thread.obj"	"$(INTDIR)\os_thread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_time.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\os_time.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\os_time.obj"	"$(INTDIR)\os_time.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\os_time.obj"	"$(INTDIR)\os_time.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\Reflection_AllJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\Reflection_AllJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\Reflection_Fwc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\Reflection_Fwc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\OSAL\Reflection_OSAL.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\Reflection_OSAL.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ReflectionBaseTypesJc.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\ReflectionBaseTypesJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\ReflectionBaseTypesJc.obj"	"$(INTDIR)\ReflectionBaseTypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\ReflectionBaseTypesJc.obj"	"$(INTDIR)\ReflectionBaseTypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\FwConv\allocOnlyAtStartup.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\allocOnlyAtStartup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\allocOnlyAtStartup.obj"	"$(INTDIR)\allocOnlyAtStartup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\allocOnlyAtStartup.obj"	"$(INTDIR)\allocOnlyAtStartup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\FwConv\fw_PlatformConvSimpleStop.c

!IF  "$(CFG)" == "TestFileJc - Win32 Release"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 Debug_C"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestFileJc - Win32 DebugCpp"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

