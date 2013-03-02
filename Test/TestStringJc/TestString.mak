# Microsoft Developer Studio Generated NMAKE File, Based on TestString.dsp
!IF "$(CFG)" == ""
CFG=TestString - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TestString - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TestString - Win32 Release" && "$(CFG)" != "TestString - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestString.mak" CFG="TestString - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestString - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TestString - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "TestString - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TestString.exe"


CLEAN :
	-@erase "$(INTDIR)\BlockHeapJc_Alloc.obj"
	-@erase "$(INTDIR)\BlockHeapJc_GarbageCol.obj"
	-@erase "$(INTDIR)\BlockHeapJc_References.obj"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_formatter.obj"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMsgStream.obj"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_Readline.obj"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_endian.obj"
	-@erase "$(INTDIR)\os_error.obj"
	-@erase "$(INTDIR)\os_file.obj"
	-@erase "$(INTDIR)\os_mem.obj"
	-@erase "$(INTDIR)\os_mutex.obj"
	-@erase "$(INTDIR)\os_socket.obj"
	-@erase "$(INTDIR)\os_sync.obj"
	-@erase "$(INTDIR)\os_thread.obj"
	-@erase "$(INTDIR)\os_time.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_BlockHeap.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringValueConvJc.obj"
	-@erase "$(INTDIR)\TestString.obj"
	-@erase "$(INTDIR)\TestStringCpp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestString.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\TestString.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestString.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestString.pdb" /machine:I386 /out:"$(OUTDIR)\TestString.exe" 
LINK32_OBJS= \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\fw_formatter.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Readline.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\os_atomic.obj" \
	"$(INTDIR)\os_endian.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_mem.obj" \
	"$(INTDIR)\os_mutex.obj" \
	"$(INTDIR)\os_socket.obj" \
	"$(INTDIR)\os_sync.obj" \
	"$(INTDIR)\os_thread.obj" \
	"$(INTDIR)\os_time.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\StringValueConvJc.obj" \
	"$(INTDIR)\BlockHeapJc_Alloc.obj" \
	"$(INTDIR)\BlockHeapJc_GarbageCol.obj" \
	"$(INTDIR)\BlockHeapJc_References.obj" \
	"$(INTDIR)\Reflection_BlockHeap.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\TestString.obj" \
	"$(INTDIR)\TestStringCpp.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj"

"$(OUTDIR)\TestString.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\TestString.exe" "$(OUTDIR)\TestString.bsc"


CLEAN :
	-@erase "$(INTDIR)\BlockHeapJc_Alloc.obj"
	-@erase "$(INTDIR)\BlockHeapJc_Alloc.sbr"
	-@erase "$(INTDIR)\BlockHeapJc_GarbageCol.obj"
	-@erase "$(INTDIR)\BlockHeapJc_GarbageCol.sbr"
	-@erase "$(INTDIR)\BlockHeapJc_References.obj"
	-@erase "$(INTDIR)\BlockHeapJc_References.sbr"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\DateJc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_formatter.obj"
	-@erase "$(INTDIR)\fw_formatter.sbr"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMessage.sbr"
	-@erase "$(INTDIR)\fw_LogMsgStream.obj"
	-@erase "$(INTDIR)\fw_LogMsgStream.sbr"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_MemC.sbr"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_Object.sbr"
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
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\LocaleJc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
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
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.sbr"
	-@erase "$(INTDIR)\Reflection_BlockHeap.obj"
	-@erase "$(INTDIR)\Reflection_BlockHeap.sbr"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.sbr"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.sbr"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringJc.sbr"
	-@erase "$(INTDIR)\StringValueConvJc.obj"
	-@erase "$(INTDIR)\StringValueConvJc.sbr"
	-@erase "$(INTDIR)\TestString.obj"
	-@erase "$(INTDIR)\TestString.sbr"
	-@erase "$(INTDIR)\TestStringCpp.obj"
	-@erase "$(INTDIR)\TestStringCpp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestString.bsc"
	-@erase "$(OUTDIR)\TestString.exe"
	-@erase "$(OUTDIR)\TestString.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../../includeSpecials/os_Windows_Msc6" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestString.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestString.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\fw_formatter.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Readline.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_String.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
	"$(INTDIR)\os_atomic.sbr" \
	"$(INTDIR)\os_endian.sbr" \
	"$(INTDIR)\os_error.sbr" \
	"$(INTDIR)\os_file.sbr" \
	"$(INTDIR)\os_mem.sbr" \
	"$(INTDIR)\os_mutex.sbr" \
	"$(INTDIR)\os_socket.sbr" \
	"$(INTDIR)\os_sync.sbr" \
	"$(INTDIR)\os_thread.sbr" \
	"$(INTDIR)\os_time.sbr" \
	"$(INTDIR)\DateJc.sbr" \
	"$(INTDIR)\LocaleJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\Reflection_AllJc.sbr" \
	"$(INTDIR)\ReflectionBasetypesJc.sbr" \
	"$(INTDIR)\StringBufferJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\StringValueConvJc.sbr" \
	"$(INTDIR)\BlockHeapJc_Alloc.sbr" \
	"$(INTDIR)\BlockHeapJc_GarbageCol.sbr" \
	"$(INTDIR)\BlockHeapJc_References.sbr" \
	"$(INTDIR)\Reflection_BlockHeap.sbr" \
	"$(INTDIR)\fw_LogMessage.sbr" \
	"$(INTDIR)\fw_LogMsgStream.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\Reflection_Fwc.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\TestString.sbr" \
	"$(INTDIR)\TestStringCpp.sbr" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr"

"$(OUTDIR)\TestString.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestString.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestString.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\fw_formatter.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Readline.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\os_atomic.obj" \
	"$(INTDIR)\os_endian.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_mem.obj" \
	"$(INTDIR)\os_mutex.obj" \
	"$(INTDIR)\os_socket.obj" \
	"$(INTDIR)\os_sync.obj" \
	"$(INTDIR)\os_thread.obj" \
	"$(INTDIR)\os_time.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\StringValueConvJc.obj" \
	"$(INTDIR)\BlockHeapJc_Alloc.obj" \
	"$(INTDIR)\BlockHeapJc_GarbageCol.obj" \
	"$(INTDIR)\BlockHeapJc_References.obj" \
	"$(INTDIR)\Reflection_BlockHeap.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\TestString.obj" \
	"$(INTDIR)\TestStringCpp.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj"

"$(OUTDIR)\TestString.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("TestString.dep")
!INCLUDE "TestString.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestString.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestString - Win32 Release" || "$(CFG)" == "TestString - Win32 Debug"
SOURCE=..\..\source\Fwc\fw_Exception.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_Exception.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_ExceptionPrintStacktrace.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_formatter.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_formatter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_formatter.obj"	"$(INTDIR)\fw_formatter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_MemC.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_MemC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Readline.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_Readline.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_Readline.obj"	"$(INTDIR)\fw_Readline.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_SimpleC.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_SimpleC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_String.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_String.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_String.obj"	"$(INTDIR)\fw_String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_threadContext.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_threadContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_timeconversions.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_timeconversions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\DateJc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\DateJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\DateJc.obj"	"$(INTDIR)\DateJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\LocaleJc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\LocaleJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ObjectJc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\ObjectJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\Reflection_AllJc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\Reflection_AllJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ReflectionBasetypesJc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\ReflectionBasetypesJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\ReflectionBasetypesJc.obj"	"$(INTDIR)\ReflectionBasetypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\StringBufferJc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\StringBufferJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\StringJc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\StringJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\StringValueConvJc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\StringValueConvJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\StringValueConvJc.obj"	"$(INTDIR)\StringValueConvJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\BlockHeap\BlockHeapJc_Alloc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\BlockHeapJc_Alloc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\BlockHeapJc_Alloc.obj"	"$(INTDIR)\BlockHeapJc_Alloc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\BlockHeap\BlockHeapJc_GarbageCol.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\BlockHeapJc_GarbageCol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\BlockHeapJc_GarbageCol.obj"	"$(INTDIR)\BlockHeapJc_GarbageCol.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\BlockHeap\BlockHeapJc_References.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\BlockHeapJc_References.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\BlockHeapJc_References.obj"	"$(INTDIR)\BlockHeapJc_References.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\BlockHeap\Reflection_BlockHeap.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\Reflection_BlockHeap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\Reflection_BlockHeap.obj"	"$(INTDIR)\Reflection_BlockHeap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_LogMessage.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_LogMessage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_LogMsgStream.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_LogMsgStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_LogMsgStream.obj"	"$(INTDIR)\fw_LogMsgStream.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Object.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_Object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\Reflection_Fwc.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\Reflection_Fwc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\OSAL\Reflection_OSAL.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\Reflection_OSAL.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_atomic.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_atomic.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_atomic.obj"	"$(INTDIR)\os_atomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_endian.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_endian.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_endian.obj"	"$(INTDIR)\os_endian.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_error.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_error.obj"	"$(INTDIR)\os_error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_file.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_file.obj"	"$(INTDIR)\os_file.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_mem.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_mem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_mem.obj"	"$(INTDIR)\os_mem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_mutex.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_mutex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_mutex.obj"	"$(INTDIR)\os_mutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_socket.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_socket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_socket.obj"	"$(INTDIR)\os_socket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_sync.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_sync.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_sync.obj"	"$(INTDIR)\os_sync.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_thread.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_thread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_thread.obj"	"$(INTDIR)\os_thread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_time.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\os_time.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\os_time.obj"	"$(INTDIR)\os_time.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\TestString.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\TestString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\TestString.obj"	"$(INTDIR)\TestString.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\TestStringCpp.cpp

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\TestStringCpp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\TestStringCpp.obj"	"$(INTDIR)\TestStringCpp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\FwConv\fw_PlatformConvSimpleStop.c

!IF  "$(CFG)" == "TestString - Win32 Release"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

