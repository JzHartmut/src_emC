# Microsoft Developer Studio Generated NMAKE File, Based on TestAtomic.dsp
!IF "$(CFG)" == ""
CFG=TestAtomic - Win32 DebugCpp
!MESSAGE No configuration specified. Defaulting to TestAtomic - Win32 DebugCpp.
!ENDIF 

!IF "$(CFG)" != "TestAtomic - Win32 Release" && "$(CFG)" != "TestAtomic - Win32 Debug_C" && "$(CFG)" != "TestAtomic - Win32 DebugCpp"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestAtomic.mak" CFG="TestAtomic - Win32 DebugCpp"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestAtomic - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TestAtomic - Win32 Debug_C" (based on "Win32 (x86) Console Application")
!MESSAGE "TestAtomic - Win32 DebugCpp" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "TestAtomic - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TestAtomic.exe"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
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
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\TestAtomic.obj"
	-@erase "$(INTDIR)\TestAtomicMain.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestAtomic.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "../../includeSpecials/os_Windows" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\TestAtomic.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestAtomic.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestAtomic.pdb" /machine:I386 /out:"$(OUTDIR)\TestAtomic.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\TestAtomic.obj" \
	"$(INTDIR)\TestAtomicMain.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_Formatter.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
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
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"

"$(OUTDIR)\TestAtomic.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"

OUTDIR=T:\Jc\TestBlockHeap_C
INTDIR=T:\Jc\TestBlockHeap_C
# Begin Custom Macros
OutDir=T:\Jc\TestBlockHeap_C
# End Custom Macros

ALL : "$(OUTDIR)\TestAtomic.exe" "$(OUTDIR)\TestAtomic.bsc"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\allocOnlyAtStartup.sbr"
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
	-@erase "$(INTDIR)\TestAtomic.obj"
	-@erase "$(INTDIR)\TestAtomic.sbr"
	-@erase "$(INTDIR)\TestAtomicMain.obj"
	-@erase "$(INTDIR)\TestAtomicMain.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestAtomic.bsc"
	-@erase "$(OUTDIR)\TestAtomic.exe"
	-@erase "$(OUTDIR)\TestAtomic.map"
	-@erase "$(OUTDIR)\TestAtomic.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MLd /W3 /Gm /GX /ZI /Od /I "../../includeSpecials/os_Windows" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FAcs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestAtomic.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\StringBufferJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\TestAtomic.sbr" \
	"$(INTDIR)\TestAtomicMain.sbr" \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_Formatter.sbr" \
	"$(INTDIR)\fw_LogMessage.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
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
	"$(INTDIR)\os_error.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\LocaleJc.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"

"$(OUTDIR)\TestAtomic.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestAtomic.pdb" /map:"$(INTDIR)\TestAtomic.map" /debug /machine:I386 /out:"$(OUTDIR)\TestAtomic.exe" /pdbtype:sept /libpath:"D:\Progs\MSC6\act\Microsoft Visual Studio\VC98\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\TestAtomic.obj" \
	"$(INTDIR)\TestAtomicMain.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_Formatter.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
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
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"

"$(OUTDIR)\TestAtomic.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"

OUTDIR=T:\Jc\TestAtomic
INTDIR=T:\Jc\TestAtomic
# Begin Custom Macros
OutDir=T:\Jc\TestAtomic
# End Custom Macros

ALL : "$(OUTDIR)\TestAtomic.exe" "$(OUTDIR)\TestAtomic.bsc"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\allocOnlyAtStartup.sbr"
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
	-@erase "$(INTDIR)\TestAtomic.obj"
	-@erase "$(INTDIR)\TestAtomic.sbr"
	-@erase "$(INTDIR)\TestAtomicMain.obj"
	-@erase "$(INTDIR)\TestAtomicMain.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestAtomic.bsc"
	-@erase "$(OUTDIR)\TestAtomic.exe"
	-@erase "$(OUTDIR)\TestAtomic.ilk"
	-@erase "$(OUTDIR)\TestAtomic.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../../includeSpecials/os_Windows" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestAtomic.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /TP /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestAtomic.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\TestAtomic.sbr" \
	"$(INTDIR)\TestAtomicMain.sbr" \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_Formatter.sbr" \
	"$(INTDIR)\fw_LogMessage.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
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
	"$(INTDIR)\fw_String.sbr" \
	"$(INTDIR)\os_error.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\LocaleJc.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"

"$(OUTDIR)\TestAtomic.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestAtomic.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestAtomic.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\TestAtomic.obj" \
	"$(INTDIR)\TestAtomicMain.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_Formatter.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
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
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"

"$(OUTDIR)\TestAtomic.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("TestAtomic.dep")
!INCLUDE "TestAtomic.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestAtomic.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestAtomic - Win32 Release" || "$(CFG)" == "TestAtomic - Win32 Debug_C" || "$(CFG)" == "TestAtomic - Win32 DebugCpp"
SOURCE=..\..\source\Jc\LocaleJc.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\LocaleJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ObjectJc.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\ObjectJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\StringBufferJc.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\StringBufferJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"

!ENDIF 

SOURCE=..\..\source\Jc\StringJc.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\StringJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"

!ENDIF 

SOURCE=src\TestAtomic.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\TestAtomic.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\TestAtomic.obj"	"$(INTDIR)\TestAtomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\TestAtomic.obj"	"$(INTDIR)\TestAtomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\TestAtomicMain.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\TestAtomicMain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\TestAtomicMain.obj"	"$(INTDIR)\TestAtomicMain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\TestAtomicMain.obj"	"$(INTDIR)\TestAtomicMain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Exception.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_Exception.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_ExceptionPrintStacktrace.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Formatter.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_Formatter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_Formatter.obj"	"$(INTDIR)\fw_Formatter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_Formatter.obj"	"$(INTDIR)\fw_Formatter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_LogMessage.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_LogMessage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_MemC.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_MemC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Object.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_Object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_SimpleC.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_SimpleC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_String.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_String.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_String.obj"	"$(INTDIR)\fw_String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_String.obj"	"$(INTDIR)\fw_String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_threadContext.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_threadContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_timeconversions.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_timeconversions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\\os_atomic.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\os_atomic.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\os_atomic.obj"	"$(INTDIR)\os_atomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\os_atomic.obj"	"$(INTDIR)\os_atomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_error.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\os_error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\os_error.obj"	"$(INTDIR)\os_error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\os_error.obj"	"$(INTDIR)\os_error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\\os_file.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\os_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\os_file.obj"	"$(INTDIR)\os_file.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"

!ENDIF 

SOURCE=..\..\source\os_Windows\\os_mem.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\os_mem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\os_mem.obj"	"$(INTDIR)\os_mem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\os_mem.obj"	"$(INTDIR)\os_mem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\\os_mutex.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\os_mutex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\os_mutex.obj"	"$(INTDIR)\os_mutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\os_mutex.obj"	"$(INTDIR)\os_mutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\\os_thread.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\os_thread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\os_thread.obj"	"$(INTDIR)\os_thread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\os_thread.obj"	"$(INTDIR)\os_thread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\\os_time.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\os_time.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\os_time.obj"	"$(INTDIR)\os_time.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\os_time.obj"	"$(INTDIR)\os_time.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\Reflection_AllJc.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\Reflection_AllJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\Reflection_Fwc.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\Reflection_Fwc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\OSAL\Reflection_OSAL.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\Reflection_OSAL.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ReflectionBaseTypesJc.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\ReflectionBaseTypesJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\ReflectionBaseTypesJc.obj"	"$(INTDIR)\ReflectionBaseTypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\ReflectionBaseTypesJc.obj"	"$(INTDIR)\ReflectionBaseTypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\FwConv\allocOnlyAtStartup.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\allocOnlyAtStartup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\allocOnlyAtStartup.obj"	"$(INTDIR)\allocOnlyAtStartup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\allocOnlyAtStartup.obj"	"$(INTDIR)\allocOnlyAtStartup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\FwConv\fw_PlatformConvSimpleStop.c

!IF  "$(CFG)" == "TestAtomic - Win32 Release"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 Debug_C"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestAtomic - Win32 DebugCpp"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

