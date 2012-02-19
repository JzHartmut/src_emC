# Microsoft Developer Studio Generated NMAKE File, Based on TestLibOsalFwc.dsp
!IF "$(CFG)" == ""
CFG=TestLibOsalFwc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TestLibOsalFwc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TestLibOsalFwc - Win32 Release" && "$(CFG)" != "TestLibOsalFwc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestLibOsalFwc.mak" CFG="TestLibOsalFwc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestLibOsalFwc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TestLibOsalFwc - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TestLibOsalFwc.exe"


CLEAN :
	-@erase "$(INTDIR)\File_TestLibOsalFwc.obj"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_formatter.obj"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_Readline.obj"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\Main_TestLibOsalFwc.obj"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_endian.obj"
	-@erase "$(INTDIR)\os_error.obj"
	-@erase "$(INTDIR)\os_file.obj"
	-@erase "$(INTDIR)\os_fileLoLevel.obj"
	-@erase "$(INTDIR)\os_mem.obj"
	-@erase "$(INTDIR)\os_mutex.obj"
	-@erase "$(INTDIR)\os_socket.obj"
	-@erase "$(INTDIR)\os_sync.obj"
	-@erase "$(INTDIR)\os_thread.obj"
	-@erase "$(INTDIR)\os_time.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestLibOsalFwc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\TestLibOsalFwc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestLibOsalFwc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestLibOsalFwc.pdb" /machine:I386 /out:"$(OUTDIR)\TestLibOsalFwc.exe" 
LINK32_OBJS= \
	"$(INTDIR)\os_time.obj" \
	"$(INTDIR)\os_atomic.obj" \
	"$(INTDIR)\os_endian.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_fileLoLevel.obj" \
	"$(INTDIR)\os_mem.obj" \
	"$(INTDIR)\os_mutex.obj" \
	"$(INTDIR)\os_socket.obj" \
	"$(INTDIR)\os_sync.obj" \
	"$(INTDIR)\os_thread.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\fw_formatter.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Readline.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj" \
	"$(INTDIR)\File_TestLibOsalFwc.obj" \
	"$(INTDIR)\Main_TestLibOsalFwc.obj"

"$(OUTDIR)\TestLibOsalFwc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\TestLibOsalFwc.exe" "$(OUTDIR)\TestLibOsalFwc.bsc"


CLEAN :
	-@erase "$(INTDIR)\File_TestLibOsalFwc.obj"
	-@erase "$(INTDIR)\File_TestLibOsalFwc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_formatter.obj"
	-@erase "$(INTDIR)\fw_formatter.sbr"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_MemC.sbr"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.sbr"
	-@erase "$(INTDIR)\fw_Readline.obj"
	-@erase "$(INTDIR)\fw_Readline.sbr"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_SimpleC.sbr"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_String.sbr"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_threadContext.sbr"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\fw_timeconversions.sbr"
	-@erase "$(INTDIR)\Main_TestLibOsalFwc.obj"
	-@erase "$(INTDIR)\Main_TestLibOsalFwc.sbr"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_atomic.sbr"
	-@erase "$(INTDIR)\os_endian.obj"
	-@erase "$(INTDIR)\os_endian.sbr"
	-@erase "$(INTDIR)\os_error.obj"
	-@erase "$(INTDIR)\os_error.sbr"
	-@erase "$(INTDIR)\os_file.obj"
	-@erase "$(INTDIR)\os_file.sbr"
	-@erase "$(INTDIR)\os_mem.obj"
	-@erase "$(INTDIR)\os_mem.sbr"
	-@erase "$(INTDIR)\os_mutex.obj"
	-@erase "$(INTDIR)\os_mutex.sbr"
	-@erase "$(INTDIR)\os_socket.obj"
	-@erase "$(INTDIR)\os_socket.sbr"
	-@erase "$(INTDIR)\os_sync.obj"
	-@erase "$(INTDIR)\os_sync.sbr"
	-@erase "$(INTDIR)\os_thread.obj"
	-@erase "$(INTDIR)\os_thread.sbr"
	-@erase "$(INTDIR)\os_time.obj"
	-@erase "$(INTDIR)\os_time.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestLibOsalFwc.bsc"
	-@erase "$(OUTDIR)\TestLibOsalFwc.exe"
	-@erase "$(OUTDIR)\TestLibOsalFwc.ilk"
	-@erase "$(OUTDIR)\TestLibOsalFwc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../../includeSpecials/os_Windows" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestLibOsalFwc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestLibOsalFwc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\os_time.sbr" \
	"$(INTDIR)\os_atomic.sbr" \
	"$(INTDIR)\os_endian.sbr" \
	"$(INTDIR)\os_error.sbr" \
	"$(INTDIR)\os_file.sbr" \
	"$(INTDIR)\os_mem.sbr" \
	"$(INTDIR)\os_mutex.sbr" \
	"$(INTDIR)\os_socket.sbr" \
	"$(INTDIR)\os_sync.sbr" \
	"$(INTDIR)\os_thread.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\fw_formatter.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Readline.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_String.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" \
	"$(INTDIR)\File_TestLibOsalFwc.sbr" \
	"$(INTDIR)\Main_TestLibOsalFwc.sbr"

"$(OUTDIR)\TestLibOsalFwc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestLibOsalFwc.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestLibOsalFwc.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\os_time.obj" \
	"$(INTDIR)\os_atomic.obj" \
	"$(INTDIR)\os_endian.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_mem.obj" \
	"$(INTDIR)\os_mutex.obj" \
	"$(INTDIR)\os_socket.obj" \
	"$(INTDIR)\os_sync.obj" \
	"$(INTDIR)\os_thread.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\fw_formatter.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Readline.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj" \
	"$(INTDIR)\File_TestLibOsalFwc.obj" \
	"$(INTDIR)\Main_TestLibOsalFwc.obj"

"$(OUTDIR)\TestLibOsalFwc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("TestLibOsalFwc.dep")
!INCLUDE "TestLibOsalFwc.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestLibOsalFwc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestLibOsalFwc - Win32 Release" || "$(CFG)" == "TestLibOsalFwc - Win32 Debug"
SOURCE=..\..\source\Fwc\fw_Exception.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_Exception.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_ExceptionPrintStacktrace.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_formatter.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_formatter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_formatter.obj"	"$(INTDIR)\fw_formatter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_MemC.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_MemC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Readline.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_Readline.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_Readline.obj"	"$(INTDIR)\fw_Readline.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_SimpleC.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_SimpleC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_String.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_String.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_String.obj"	"$(INTDIR)\fw_String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_threadContext.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_threadContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_timeconversions.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_timeconversions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_atomic.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_atomic.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_atomic.obj"	"$(INTDIR)\os_atomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_endian.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_endian.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_endian.obj"	"$(INTDIR)\os_endian.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_error.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_error.obj"	"$(INTDIR)\os_error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_file.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_file.obj"	"$(INTDIR)\os_file.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_fileLoLevel.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_fileLoLevel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"

!ENDIF 

SOURCE=..\..\source\os_Windows\os_mem.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_mem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_mem.obj"	"$(INTDIR)\os_mem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_mutex.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_mutex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_mutex.obj"	"$(INTDIR)\os_mutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_socket.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_socket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_socket.obj"	"$(INTDIR)\os_socket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_sync.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_sync.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_sync.obj"	"$(INTDIR)\os_sync.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_thread.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_thread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_thread.obj"	"$(INTDIR)\os_thread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\os_Windows\os_time.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\os_time.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\os_time.obj"	"$(INTDIR)\os_time.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\File_TestLibOsalFwc.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\File_TestLibOsalFwc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\File_TestLibOsalFwc.obj"	"$(INTDIR)\File_TestLibOsalFwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\Main_TestLibOsalFwc.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\Main_TestLibOsalFwc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\Main_TestLibOsalFwc.obj"	"$(INTDIR)\Main_TestLibOsalFwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\FwConv\fw_PlatformConvSimpleStop.c

!IF  "$(CFG)" == "TestLibOsalFwc - Win32 Release"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestLibOsalFwc - Win32 Debug"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

