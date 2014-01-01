# Microsoft Developer Studio Generated NMAKE File, Based on TestBlockHeap.dsp
!IF "$(CFG)" == ""
CFG=TestBlockHeap - Win32 DebugCpp
!MESSAGE No configuration specified. Defaulting to TestBlockHeap - Win32 DebugCpp.
!ENDIF 

!IF "$(CFG)" != "TestBlockHeap - Win32 Release" && "$(CFG)" != "TestBlockHeap - Win32 Debug_C" && "$(CFG)" != "TestBlockHeap - Win32 DebugCpp"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestBlockHeap.mak" CFG="TestBlockHeap - Win32 DebugCpp"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestBlockHeap - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TestBlockHeap - Win32 Debug_C" (based on "Win32 (x86) Console Application")
!MESSAGE "TestBlockHeap - Win32 DebugCpp" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TestBlockHeap.exe"


CLEAN :
	-@erase "$(INTDIR)\BlockHeapJc_Alloc.obj"
	-@erase "$(INTDIR)\BlockHeapJc_GarbageCol.obj"
	-@erase "$(INTDIR)\BlockHeapJc_References.obj"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.obj"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_Formatter.obj"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMsgStream.obj"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\LinkedListJc.obj"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_common.obj"
	-@erase "$(INTDIR)\os_error.obj"
	-@erase "$(INTDIR)\os_file.obj"
	-@erase "$(INTDIR)\os_mem.obj"
	-@erase "$(INTDIR)\os_mutex.obj"
	-@erase "$(INTDIR)\os_thread.obj"
	-@erase "$(INTDIR)\os_time.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_BlockHeap.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\ReflectionBaseTypesJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\TestBlockHeap.obj"
	-@erase "$(INTDIR)\TestBlockHeapMain.obj"
	-@erase "$(INTDIR)\TestListMap.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestBlockHeap.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\TestBlockHeap.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestBlockHeap.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestBlockHeap.pdb" /machine:I386 /out:"$(OUTDIR)\TestBlockHeap.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ConcurrentLinkedQueueJc.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\LinkedListJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\TestBlockHeap.obj" \
	"$(INTDIR)\TestBlockHeapMain.obj" \
	"$(INTDIR)\TestListMap.obj" \
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
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj" \
	"$(INTDIR)\BlockHeapJc_Alloc.obj" \
	"$(INTDIR)\BlockHeapJc_GarbageCol.obj" \
	"$(INTDIR)\BlockHeapJc_References.obj" \
	"$(INTDIR)\Reflection_BlockHeap.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_common.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\LocaleJc.obj"

"$(OUTDIR)\TestBlockHeap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"

OUTDIR=.\..\..\..\..\tmp_javac\TestBlockHeap_C
INTDIR=.\..\..\..\..\tmp_javac\TestBlockHeap_C
# Begin Custom Macros
OutDir=.\..\..\..\..\tmp_javac\TestBlockHeap_C
# End Custom Macros

ALL : "$(OUTDIR)\TestBlockHeap.exe" "$(OUTDIR)\TestBlockHeap.bsc"


CLEAN :
	-@erase "$(INTDIR)\BlockHeapJc_Alloc.obj"
	-@erase "$(INTDIR)\BlockHeapJc_Alloc.sbr"
	-@erase "$(INTDIR)\BlockHeapJc_GarbageCol.obj"
	-@erase "$(INTDIR)\BlockHeapJc_GarbageCol.sbr"
	-@erase "$(INTDIR)\BlockHeapJc_References.obj"
	-@erase "$(INTDIR)\BlockHeapJc_References.sbr"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.obj"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.sbr"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\DateJc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_Formatter.obj"
	-@erase "$(INTDIR)\fw_Formatter.sbr"
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
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_SimpleC.sbr"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_String.sbr"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_threadContext.sbr"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\fw_timeconversions.sbr"
	-@erase "$(INTDIR)\LinkedListJc.obj"
	-@erase "$(INTDIR)\LinkedListJc.sbr"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\LocaleJc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_atomic.sbr"
	-@erase "$(INTDIR)\os_common.obj"
	-@erase "$(INTDIR)\os_common.sbr"
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
	-@erase "$(INTDIR)\Reflection_BlockHeap.obj"
	-@erase "$(INTDIR)\Reflection_BlockHeap.sbr"
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
	-@erase "$(INTDIR)\TestBlockHeap.obj"
	-@erase "$(INTDIR)\TestBlockHeap.sbr"
	-@erase "$(INTDIR)\TestBlockHeapMain.obj"
	-@erase "$(INTDIR)\TestBlockHeapMain.sbr"
	-@erase "$(INTDIR)\TestListMap.obj"
	-@erase "$(INTDIR)\TestListMap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestBlockHeap.bsc"
	-@erase "$(OUTDIR)\TestBlockHeap.exe"
	-@erase "$(OUTDIR)\TestBlockHeap.map"
	-@erase "$(OUTDIR)\TestBlockHeap.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MLd /W3 /Gm /GX /ZI /Od /I "../../includeSpecials/os_Windows_Msc6" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FAcs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestBlockHeap.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ConcurrentLinkedQueueJc.sbr" \
	"$(INTDIR)\DateJc.sbr" \
	"$(INTDIR)\LinkedListJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\StringBufferJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\TestBlockHeap.sbr" \
	"$(INTDIR)\TestBlockHeapMain.sbr" \
	"$(INTDIR)\TestListMap.sbr" \
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
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" \
	"$(INTDIR)\BlockHeapJc_Alloc.sbr" \
	"$(INTDIR)\BlockHeapJc_GarbageCol.sbr" \
	"$(INTDIR)\BlockHeapJc_References.sbr" \
	"$(INTDIR)\Reflection_BlockHeap.sbr" \
	"$(INTDIR)\fw_LogMsgStream.sbr" \
	"$(INTDIR)\fw_String.sbr" \
	"$(INTDIR)\os_error.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\os_file.sbr" \
	"$(INTDIR)\os_common.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\LocaleJc.sbr"

"$(OUTDIR)\TestBlockHeap.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\TestBlockHeap.pdb" /map:"$(INTDIR)\TestBlockHeap.map" /debug /machine:I386 /out:"$(OUTDIR)\TestBlockHeap.exe" /pdbtype:sept /libpath:"D:\Progs\MSC6\act\Microsoft Visual Studio\VC98\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\ConcurrentLinkedQueueJc.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\LinkedListJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\TestBlockHeap.obj" \
	"$(INTDIR)\TestBlockHeapMain.obj" \
	"$(INTDIR)\TestListMap.obj" \
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
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj" \
	"$(INTDIR)\BlockHeapJc_Alloc.obj" \
	"$(INTDIR)\BlockHeapJc_GarbageCol.obj" \
	"$(INTDIR)\BlockHeapJc_References.obj" \
	"$(INTDIR)\Reflection_BlockHeap.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_common.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\LocaleJc.obj"

"$(OUTDIR)\TestBlockHeap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"

OUTDIR=.\..\..\..\..\tmp_javac\TestBlockHeap_cpp
INTDIR=.\..\..\..\..\tmp_javac\TestBlockHeap_cpp
# Begin Custom Macros
OutDir=.\..\..\..\..\tmp_javac\TestBlockHeap_cpp
# End Custom Macros

ALL : "$(OUTDIR)\TestBlockHeap.exe" "$(OUTDIR)\TestBlockHeap.bsc"


CLEAN :
	-@erase "$(INTDIR)\BlockHeapJc_Alloc.obj"
	-@erase "$(INTDIR)\BlockHeapJc_Alloc.sbr"
	-@erase "$(INTDIR)\BlockHeapJc_GarbageCol.obj"
	-@erase "$(INTDIR)\BlockHeapJc_GarbageCol.sbr"
	-@erase "$(INTDIR)\BlockHeapJc_References.obj"
	-@erase "$(INTDIR)\BlockHeapJc_References.sbr"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.obj"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.sbr"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\DateJc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_Formatter.obj"
	-@erase "$(INTDIR)\fw_Formatter.sbr"
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
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_SimpleC.sbr"
	-@erase "$(INTDIR)\fw_String.obj"
	-@erase "$(INTDIR)\fw_String.sbr"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_threadContext.sbr"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\fw_timeconversions.sbr"
	-@erase "$(INTDIR)\LinkedListJc.obj"
	-@erase "$(INTDIR)\LinkedListJc.sbr"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\LocaleJc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\os_atomic.obj"
	-@erase "$(INTDIR)\os_atomic.sbr"
	-@erase "$(INTDIR)\os_common.obj"
	-@erase "$(INTDIR)\os_common.sbr"
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
	-@erase "$(INTDIR)\Reflection_BlockHeap.obj"
	-@erase "$(INTDIR)\Reflection_BlockHeap.sbr"
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
	-@erase "$(INTDIR)\TestBlockHeap.obj"
	-@erase "$(INTDIR)\TestBlockHeap.sbr"
	-@erase "$(INTDIR)\TestBlockHeapMain.obj"
	-@erase "$(INTDIR)\TestBlockHeapMain.sbr"
	-@erase "$(INTDIR)\TestListMap.obj"
	-@erase "$(INTDIR)\TestListMap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestBlockHeap.bsc"
	-@erase "$(OUTDIR)\TestBlockHeap.exe"
	-@erase "$(OUTDIR)\TestBlockHeap.ilk"
	-@erase "$(OUTDIR)\TestBlockHeap.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I ".." /I "../../CRuntimeJavalike/FwConvCpp" /I "../../CRuntimeJavalike/OSAL/inc" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestBlockHeap.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /TP /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestBlockHeap.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ConcurrentLinkedQueueJc.sbr" \
	"$(INTDIR)\DateJc.sbr" \
	"$(INTDIR)\LinkedListJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\StringBufferJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\TestBlockHeap.sbr" \
	"$(INTDIR)\TestBlockHeapMain.sbr" \
	"$(INTDIR)\TestListMap.sbr" \
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
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" \
	"$(INTDIR)\BlockHeapJc_Alloc.sbr" \
	"$(INTDIR)\BlockHeapJc_GarbageCol.sbr" \
	"$(INTDIR)\BlockHeapJc_References.sbr" \
	"$(INTDIR)\Reflection_BlockHeap.sbr" \
	"$(INTDIR)\fw_LogMsgStream.sbr" \
	"$(INTDIR)\fw_String.sbr" \
	"$(INTDIR)\os_error.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\os_file.sbr" \
	"$(INTDIR)\os_common.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\LocaleJc.sbr"

"$(OUTDIR)\TestBlockHeap.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestBlockHeap.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestBlockHeap.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ConcurrentLinkedQueueJc.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\LinkedListJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\TestBlockHeap.obj" \
	"$(INTDIR)\TestBlockHeapMain.obj" \
	"$(INTDIR)\TestListMap.obj" \
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
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj" \
	"$(INTDIR)\BlockHeapJc_Alloc.obj" \
	"$(INTDIR)\BlockHeapJc_GarbageCol.obj" \
	"$(INTDIR)\BlockHeapJc_References.obj" \
	"$(INTDIR)\Reflection_BlockHeap.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_String.obj" \
	"$(INTDIR)\os_error.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\os_file.obj" \
	"$(INTDIR)\os_common.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\LocaleJc.obj"

"$(OUTDIR)\TestBlockHeap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("TestBlockHeap.dep")
!INCLUDE "TestBlockHeap.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestBlockHeap.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestBlockHeap - Win32 Release" || "$(CFG)" == "TestBlockHeap - Win32 Debug_C" || "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"
SOURCE=..\..\source\Jc\ConcurrentLinkedQueueJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\ConcurrentLinkedQueueJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\ConcurrentLinkedQueueJc.obj"	"$(INTDIR)\ConcurrentLinkedQueueJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\ConcurrentLinkedQueueJc.obj"	"$(INTDIR)\ConcurrentLinkedQueueJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\DateJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\DateJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\DateJc.obj"	"$(INTDIR)\DateJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\DateJc.obj"	"$(INTDIR)\DateJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\LinkedListJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\LinkedListJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\LinkedListJc.obj"	"$(INTDIR)\LinkedListJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\LinkedListJc.obj"	"$(INTDIR)\LinkedListJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\LocaleJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\LocaleJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ObjectJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\ObjectJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ReflectionJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\ReflectionJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"

!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"

!ENDIF 

SOURCE=..\..\source\Jc\StringBufferJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\StringBufferJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\StringJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\StringJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=src\TestBlockHeap.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\TestBlockHeap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\TestBlockHeap.obj"	"$(INTDIR)\TestBlockHeap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\TestBlockHeap.obj"	"$(INTDIR)\TestBlockHeap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\TestBlockHeapMain.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\TestBlockHeapMain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\TestBlockHeapMain.obj"	"$(INTDIR)\TestBlockHeapMain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\TestBlockHeapMain.obj"	"$(INTDIR)\TestBlockHeapMain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\TestListMap.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\TestListMap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\TestListMap.obj"	"$(INTDIR)\TestListMap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\TestListMap.obj"	"$(INTDIR)\TestListMap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Exception.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_Exception.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_ExceptionPrintStacktrace.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Formatter.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_Formatter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_Formatter.obj"	"$(INTDIR)\fw_Formatter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_Formatter.obj"	"$(INTDIR)\fw_Formatter.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_LogMessage.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_LogMessage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_LogMsgStream.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_LogMsgStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_LogMsgStream.obj"	"$(INTDIR)\fw_LogMsgStream.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_LogMsgStream.obj"	"$(INTDIR)\fw_LogMsgStream.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_MemC.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_MemC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_Object.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_Object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_SimpleC.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_SimpleC.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_String.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_String.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_String.obj"	"$(INTDIR)\fw_String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_String.obj"	"$(INTDIR)\fw_String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_threadContext.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_threadContext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\fw_timeconversions.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_timeconversions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_atomic.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\os_atomic.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\os_atomic.obj"	"$(INTDIR)\os_atomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\os_atomic.obj"	"$(INTDIR)\os_atomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\OSAL\os_common.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\os_common.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\os_common.obj"	"$(INTDIR)\os_common.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\os_common.obj"	"$(INTDIR)\os_common.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_error.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\os_error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\os_error.obj"	"$(INTDIR)\os_error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\os_error.obj"	"$(INTDIR)\os_error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_file.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\os_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\os_file.obj"	"$(INTDIR)\os_file.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\os_file.obj"	"$(INTDIR)\os_file.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_mem.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\os_mem.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\os_mem.obj"	"$(INTDIR)\os_mem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\os_mem.obj"	"$(INTDIR)\os_mem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_mutex.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\os_mutex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\os_mutex.obj"	"$(INTDIR)\os_mutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\os_mutex.obj"	"$(INTDIR)\os_mutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_thread.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\os_thread.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\os_thread.obj"	"$(INTDIR)\os_thread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\os_thread.obj"	"$(INTDIR)\os_thread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_time.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\os_time.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\os_time.obj"	"$(INTDIR)\os_time.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\os_time.obj"	"$(INTDIR)\os_time.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\Reflection_AllJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\Reflection_AllJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Fwc\Reflection_Fwc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\Reflection_Fwc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\OSAL\Reflection_OSAL.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\Reflection_OSAL.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\Jc\ReflectionBaseTypesJc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\ReflectionBaseTypesJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\ReflectionBaseTypesJc.obj"	"$(INTDIR)\ReflectionBaseTypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\ReflectionBaseTypesJc.obj"	"$(INTDIR)\ReflectionBaseTypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\FwConv\fw_PlatformConvSimpleStop.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\BlockHeap\BlockHeapJc_Alloc.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\BlockHeapJc_Alloc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\BlockHeapJc_Alloc.obj"	"$(INTDIR)\BlockHeapJc_Alloc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\BlockHeapJc_Alloc.obj"	"$(INTDIR)\BlockHeapJc_Alloc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\BlockHeap\BlockHeapJc_GarbageCol.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\BlockHeapJc_GarbageCol.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\BlockHeapJc_GarbageCol.obj"	"$(INTDIR)\BlockHeapJc_GarbageCol.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\BlockHeapJc_GarbageCol.obj"	"$(INTDIR)\BlockHeapJc_GarbageCol.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\BlockHeap\BlockHeapJc_References.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\BlockHeapJc_References.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\BlockHeapJc_References.obj"	"$(INTDIR)\BlockHeapJc_References.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\BlockHeapJc_References.obj"	"$(INTDIR)\BlockHeapJc_References.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\source\BlockHeap\Reflection_BlockHeap.c

!IF  "$(CFG)" == "TestBlockHeap - Win32 Release"


"$(INTDIR)\Reflection_BlockHeap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 Debug_C"


"$(INTDIR)\Reflection_BlockHeap.obj"	"$(INTDIR)\Reflection_BlockHeap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "TestBlockHeap - Win32 DebugCpp"


"$(INTDIR)\Reflection_BlockHeap.obj"	"$(INTDIR)\Reflection_BlockHeap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

