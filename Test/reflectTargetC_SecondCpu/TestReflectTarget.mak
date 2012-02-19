# Microsoft Developer Studio Generated NMAKE File, Based on TestReflectTarget.dsp
!IF "$(CFG)" == ""
CFG=TestReflectTarget - Win32 PreProc
!MESSAGE No configuration specified. Defaulting to TestReflectTarget - Win32 PreProc.
!ENDIF 

!IF "$(CFG)" != "TestReflectTarget - Win32 DebugCpp" && "$(CFG)" != "TestReflectTarget - Win32 DebugC" && "$(CFG)" != "TestReflectTarget - Win32 PreProc"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestReflectTarget.mak" CFG="TestReflectTarget - Win32 PreProc"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestReflectTarget - Win32 DebugCpp" (based on "Win32 (x86) Console Application")
!MESSAGE "TestReflectTarget - Win32 DebugC" (based on "Win32 (x86) Console Application")
!MESSAGE "TestReflectTarget - Win32 PreProc" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "TestReflectTarget - Win32 DebugCpp"

OUTDIR=T:\Jc\TestReflectTarget
INTDIR=T:\Jc\TestReflectTarget
# Begin Custom Macros
OutDir=T:\Jc\TestReflectTarget
# End Custom Macros

ALL : "$(OUTDIR)\TestReflectTarget.exe" "$(OUTDIR)\TestReflectTarget.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\ByteDataAccessJc.obj"
	-@erase "$(INTDIR)\ByteDataAccessJc.sbr"
	-@erase "$(INTDIR)\ClassContent_Inspc.obj"
	-@erase "$(INTDIR)\ClassContent_Inspc.sbr"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.obj"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.obj"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.sbr"
	-@erase "$(INTDIR)\Comm_Inspc.obj"
	-@erase "$(INTDIR)\Comm_Inspc.sbr"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileIoJc.sbr"
	-@erase "$(INTDIR)\FileSystemJc.obj"
	-@erase "$(INTDIR)\FileSystemJc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_MemC.sbr"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_Object.sbr"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_SimpleC.sbr"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_threadContext.sbr"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\fw_timeconversions.sbr"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\OsWrapperJc.obj"
	-@erase "$(INTDIR)\OsWrapperJc.sbr"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.obj"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.sbr"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.sbr"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.sbr"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.obj"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.sbr"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.obj"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.sbr"
	-@erase "$(INTDIR)\ReflMemAccessJc.obj"
	-@erase "$(INTDIR)\ReflMemAccessJc.sbr"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringJc.sbr"
	-@erase "$(INTDIR)\StringPartJc.obj"
	-@erase "$(INTDIR)\StringPartJc.sbr"
	-@erase "$(INTDIR)\SystemJc.obj"
	-@erase "$(INTDIR)\SystemJc.sbr"
	-@erase "$(INTDIR)\SystemOutJc.obj"
	-@erase "$(INTDIR)\SystemOutJc.sbr"
	-@erase "$(INTDIR)\TestReflectTarget.obj"
	-@erase "$(INTDIR)\TestReflectTarget.sbr"
	-@erase "$(INTDIR)\TestSecondCpu.obj"
	-@erase "$(INTDIR)\TestSecondCpu.sbr"
	-@erase "$(INTDIR)\ThreadJc.obj"
	-@erase "$(INTDIR)\ThreadJc.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WorkingThread_Inspc.obj"
	-@erase "$(INTDIR)\WorkingThread_Inspc.sbr"
	-@erase "$(OUTDIR)\TestReflectTarget.bsc"
	-@erase "$(OUTDIR)\TestReflectTarget.exe"
	-@erase "$(OUTDIR)\TestReflectTarget.ilk"
	-@erase "$(OUTDIR)\TestReflectTarget.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "src_c" /I "gensrc_c" /I "../../CRuntimeJavalike/includeSpecials/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestReflectTarget.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /TP /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestReflectTarget.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\ClassContent_Inspc.sbr" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\Comm_Inspc.sbr" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\Inspector_Inspc.sbr" \
	"$(INTDIR)\Reflection_TestReflectTarget.sbr" \
	"$(INTDIR)\ReflectionOffset_Dsp.sbr" \
	"$(INTDIR)\SearchElement_Inspc.sbr" \
	"$(INTDIR)\TestReflectTarget.sbr" \
	"$(INTDIR)\TestSecondCpu.sbr" \
	"$(INTDIR)\WorkingThread_Inspc.sbr" \
	"$(INTDIR)\FileIoJc.sbr" \
	"$(INTDIR)\FileSystemJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\OsWrapperJc.sbr" \
	"$(INTDIR)\ReflectionBasetypesJc.sbr" \
	"$(INTDIR)\ReflectionJc.sbr" \
	"$(INTDIR)\ReflectionLoadExtJc.sbr" \
	"$(INTDIR)\ReflMemAccessJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\SystemJc.sbr" \
	"$(INTDIR)\SystemOutJc.sbr" \
	"$(INTDIR)\ThreadJc.sbr" \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
	"$(INTDIR)\Reflection_Fwc.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\ByteDataAccessJc.sbr" \
	"$(INTDIR)\StringPartJc.sbr"

"$(OUTDIR)\TestReflectTarget.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestReflectTarget.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestReflectTarget.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\Reflection_TestReflectTarget.obj" \
	"$(INTDIR)\ReflectionOffset_Dsp.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\TestReflectTarget.obj" \
	"$(INTDIR)\TestSecondCpu.obj" \
	"$(INTDIR)\WorkingThread_Inspc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\FileSystemJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\OsWrapperJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\ReflectionLoadExtJc.obj" \
	"$(INTDIR)\ReflMemAccessJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\SystemJc.obj" \
	"$(INTDIR)\SystemOutJc.obj" \
	"$(INTDIR)\ThreadJc.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\ByteDataAccessJc.obj" \
	"$(INTDIR)\StringPartJc.obj" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\baseJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\simpleAllocJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\OSALJcD.lib"

"$(OUTDIR)\TestReflectTarget.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestReflectTarget - Win32 DebugC"

OUTDIR=T:\Jc\TestReflectTarget_DebugC
INTDIR=T:\Jc\TestReflectTarget_DebugC
# Begin Custom Macros
OutDir=T:\Jc\TestReflectTarget_DebugC
# End Custom Macros

ALL : "$(OUTDIR)\TestReflectTarget.exe" "$(OUTDIR)\TestReflectTarget.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\ByteDataAccessJc.obj"
	-@erase "$(INTDIR)\ByteDataAccessJc.sbr"
	-@erase "$(INTDIR)\ClassContent_Inspc.obj"
	-@erase "$(INTDIR)\ClassContent_Inspc.sbr"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.obj"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.obj"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.sbr"
	-@erase "$(INTDIR)\Comm_Inspc.obj"
	-@erase "$(INTDIR)\Comm_Inspc.sbr"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileIoJc.sbr"
	-@erase "$(INTDIR)\FileSystemJc.obj"
	-@erase "$(INTDIR)\FileSystemJc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_MemC.sbr"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_Object.sbr"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_SimpleC.sbr"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_threadContext.sbr"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\fw_timeconversions.sbr"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\OsWrapperJc.obj"
	-@erase "$(INTDIR)\OsWrapperJc.sbr"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.obj"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.sbr"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.sbr"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.sbr"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.obj"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.sbr"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.obj"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.sbr"
	-@erase "$(INTDIR)\ReflMemAccessJc.obj"
	-@erase "$(INTDIR)\ReflMemAccessJc.sbr"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringJc.sbr"
	-@erase "$(INTDIR)\StringPartJc.obj"
	-@erase "$(INTDIR)\StringPartJc.sbr"
	-@erase "$(INTDIR)\SystemJc.obj"
	-@erase "$(INTDIR)\SystemJc.sbr"
	-@erase "$(INTDIR)\SystemOutJc.obj"
	-@erase "$(INTDIR)\SystemOutJc.sbr"
	-@erase "$(INTDIR)\TestReflectTarget.obj"
	-@erase "$(INTDIR)\TestReflectTarget.sbr"
	-@erase "$(INTDIR)\TestSecondCpu.obj"
	-@erase "$(INTDIR)\TestSecondCpu.sbr"
	-@erase "$(INTDIR)\ThreadJc.obj"
	-@erase "$(INTDIR)\ThreadJc.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WorkingThread_Inspc.obj"
	-@erase "$(INTDIR)\WorkingThread_Inspc.sbr"
	-@erase "$(OUTDIR)\TestReflectTarget.bsc"
	-@erase "$(OUTDIR)\TestReflectTarget.exe"
	-@erase "$(OUTDIR)\TestReflectTarget.ilk"
	-@erase "$(OUTDIR)\TestReflectTarget.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MTd /W4 /ZI /Od /I "src_c" /I "gensrc_c" /I "../../CRuntimeJavalike/includeSpecials/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FAcs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestReflectTarget.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\ClassContent_Inspc.sbr" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\Comm_Inspc.sbr" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\Inspector_Inspc.sbr" \
	"$(INTDIR)\Reflection_TestReflectTarget.sbr" \
	"$(INTDIR)\ReflectionOffset_Dsp.sbr" \
	"$(INTDIR)\SearchElement_Inspc.sbr" \
	"$(INTDIR)\TestReflectTarget.sbr" \
	"$(INTDIR)\TestSecondCpu.sbr" \
	"$(INTDIR)\WorkingThread_Inspc.sbr" \
	"$(INTDIR)\FileIoJc.sbr" \
	"$(INTDIR)\FileSystemJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\OsWrapperJc.sbr" \
	"$(INTDIR)\ReflectionBasetypesJc.sbr" \
	"$(INTDIR)\ReflectionJc.sbr" \
	"$(INTDIR)\ReflectionLoadExtJc.sbr" \
	"$(INTDIR)\ReflMemAccessJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\SystemJc.sbr" \
	"$(INTDIR)\SystemOutJc.sbr" \
	"$(INTDIR)\ThreadJc.sbr" \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
	"$(INTDIR)\Reflection_Fwc.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\ByteDataAccessJc.sbr" \
	"$(INTDIR)\StringPartJc.sbr"

"$(OUTDIR)\TestReflectTarget.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestReflectTarget.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestReflectTarget.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\Reflection_TestReflectTarget.obj" \
	"$(INTDIR)\ReflectionOffset_Dsp.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\TestReflectTarget.obj" \
	"$(INTDIR)\TestSecondCpu.obj" \
	"$(INTDIR)\WorkingThread_Inspc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\FileSystemJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\OsWrapperJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\ReflectionLoadExtJc.obj" \
	"$(INTDIR)\ReflMemAccessJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\SystemJc.obj" \
	"$(INTDIR)\SystemOutJc.obj" \
	"$(INTDIR)\ThreadJc.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\ByteDataAccessJc.obj" \
	"$(INTDIR)\StringPartJc.obj" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\baseJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\simpleAllocJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\OSALJcD.lib"

"$(OUTDIR)\TestReflectTarget.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestReflectTarget - Win32 PreProc"

OUTDIR=T:\Jc\TestReflectTarget_PreProc
INTDIR=T:\Jc\TestReflectTarget_PreProc
# Begin Custom Macros
OutDir=T:\Jc\TestReflectTarget_PreProc
# End Custom Macros

ALL : "$(OUTDIR)\TestReflectTarget.exe" "$(OUTDIR)\TestReflectTarget.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\ByteDataAccessJc.obj"
	-@erase "$(INTDIR)\ByteDataAccessJc.sbr"
	-@erase "$(INTDIR)\ClassContent_Inspc.obj"
	-@erase "$(INTDIR)\ClassContent_Inspc.sbr"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.obj"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.obj"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.sbr"
	-@erase "$(INTDIR)\Comm_Inspc.obj"
	-@erase "$(INTDIR)\Comm_Inspc.sbr"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileIoJc.sbr"
	-@erase "$(INTDIR)\FileSystemJc.obj"
	-@erase "$(INTDIR)\FileSystemJc.sbr"
	-@erase "$(INTDIR)\fw_Exception.obj"
	-@erase "$(INTDIR)\fw_Exception.sbr"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.obj"
	-@erase "$(INTDIR)\fw_ExceptionPrintStacktrace.sbr"
	-@erase "$(INTDIR)\fw_MemC.obj"
	-@erase "$(INTDIR)\fw_MemC.sbr"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_Object.sbr"
	-@erase "$(INTDIR)\fw_SimpleC.obj"
	-@erase "$(INTDIR)\fw_SimpleC.sbr"
	-@erase "$(INTDIR)\fw_threadContext.obj"
	-@erase "$(INTDIR)\fw_threadContext.sbr"
	-@erase "$(INTDIR)\fw_timeconversions.obj"
	-@erase "$(INTDIR)\fw_timeconversions.sbr"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\OsWrapperJc.obj"
	-@erase "$(INTDIR)\OsWrapperJc.sbr"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.obj"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.sbr"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.sbr"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.sbr"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.obj"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.sbr"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.obj"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.sbr"
	-@erase "$(INTDIR)\ReflMemAccessJc.obj"
	-@erase "$(INTDIR)\ReflMemAccessJc.sbr"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringJc.sbr"
	-@erase "$(INTDIR)\StringPartJc.obj"
	-@erase "$(INTDIR)\StringPartJc.sbr"
	-@erase "$(INTDIR)\SystemJc.obj"
	-@erase "$(INTDIR)\SystemJc.sbr"
	-@erase "$(INTDIR)\SystemOutJc.obj"
	-@erase "$(INTDIR)\SystemOutJc.sbr"
	-@erase "$(INTDIR)\TestReflectTarget.obj"
	-@erase "$(INTDIR)\TestReflectTarget.sbr"
	-@erase "$(INTDIR)\TestSecondCpu.obj"
	-@erase "$(INTDIR)\TestSecondCpu.sbr"
	-@erase "$(INTDIR)\ThreadJc.obj"
	-@erase "$(INTDIR)\ThreadJc.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WorkingThread_Inspc.obj"
	-@erase "$(INTDIR)\WorkingThread_Inspc.sbr"
	-@erase "$(OUTDIR)\TestReflectTarget.bsc"
	-@erase "$(OUTDIR)\TestReflectTarget.exe"
	-@erase "$(OUTDIR)\TestReflectTarget.ilk"
	-@erase "$(OUTDIR)\TestReflectTarget.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "src_c" /I "gensrc_c" /I "../../CRuntimeJavalike/includeSpecials/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestReflectTarget.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /P /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestReflectTarget.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\ClassContent_Inspc.sbr" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\Comm_Inspc.sbr" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\Inspector_Inspc.sbr" \
	"$(INTDIR)\Reflection_TestReflectTarget.sbr" \
	"$(INTDIR)\ReflectionOffset_Dsp.sbr" \
	"$(INTDIR)\SearchElement_Inspc.sbr" \
	"$(INTDIR)\TestReflectTarget.sbr" \
	"$(INTDIR)\TestSecondCpu.sbr" \
	"$(INTDIR)\WorkingThread_Inspc.sbr" \
	"$(INTDIR)\FileIoJc.sbr" \
	"$(INTDIR)\FileSystemJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\OsWrapperJc.sbr" \
	"$(INTDIR)\ReflectionBasetypesJc.sbr" \
	"$(INTDIR)\ReflectionJc.sbr" \
	"$(INTDIR)\ReflectionLoadExtJc.sbr" \
	"$(INTDIR)\ReflMemAccessJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\SystemJc.sbr" \
	"$(INTDIR)\SystemOutJc.sbr" \
	"$(INTDIR)\ThreadJc.sbr" \
	"$(INTDIR)\fw_Exception.sbr" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" \
	"$(INTDIR)\fw_MemC.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\fw_SimpleC.sbr" \
	"$(INTDIR)\fw_threadContext.sbr" \
	"$(INTDIR)\fw_timeconversions.sbr" \
	"$(INTDIR)\Reflection_Fwc.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\ByteDataAccessJc.sbr" \
	"$(INTDIR)\StringPartJc.sbr"

"$(OUTDIR)\TestReflectTarget.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestReflectTarget.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestReflectTarget.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\Reflection_TestReflectTarget.obj" \
	"$(INTDIR)\ReflectionOffset_Dsp.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\TestReflectTarget.obj" \
	"$(INTDIR)\TestSecondCpu.obj" \
	"$(INTDIR)\WorkingThread_Inspc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\FileSystemJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\OsWrapperJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\ReflectionLoadExtJc.obj" \
	"$(INTDIR)\ReflMemAccessJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\SystemJc.obj" \
	"$(INTDIR)\SystemOutJc.obj" \
	"$(INTDIR)\ThreadJc.obj" \
	"$(INTDIR)\fw_Exception.obj" \
	"$(INTDIR)\fw_ExceptionPrintStacktrace.obj" \
	"$(INTDIR)\fw_MemC.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\fw_SimpleC.obj" \
	"$(INTDIR)\fw_threadContext.obj" \
	"$(INTDIR)\fw_timeconversions.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\ByteDataAccessJc.obj" \
	"$(INTDIR)\StringPartJc.obj" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\baseJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\simpleAllocJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\OSALJcD.lib"

"$(OUTDIR)\TestReflectTarget.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("TestReflectTarget.dep")
!INCLUDE "TestReflectTarget.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestReflectTarget.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestReflectTarget - Win32 DebugCpp" || "$(CFG)" == "TestReflectTarget - Win32 DebugC" || "$(CFG)" == "TestReflectTarget - Win32 PreProc"
SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\AnswerComm_ifc_Inspc.c

"$(INTDIR)\AnswerComm_ifc_Inspc.obj"	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\ClassContent_Inspc.c

"$(INTDIR)\ClassContent_Inspc.obj"	"$(INTDIR)\ClassContent_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\CmdConsumer_ifc_Inspc.c

"$(INTDIR)\CmdConsumer_ifc_Inspc.obj"	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\CmdExecuter_Inspc.c

"$(INTDIR)\CmdExecuter_Inspc.obj"	"$(INTDIR)\CmdExecuter_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\Comm_Inspc.c

"$(INTDIR)\Comm_Inspc.obj"	"$(INTDIR)\Comm_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\InspcDataExchangeAccess_Inspc.c

"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\Inspector_Inspc.c

"$(INTDIR)\Inspector_Inspc.obj"	"$(INTDIR)\Inspector_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\genRefl\Reflection_TestReflectTarget.c

"$(INTDIR)\Reflection_TestReflectTarget.obj"	"$(INTDIR)\Reflection_TestReflectTarget.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\genRefl\ReflectionOffset_Dsp.c

"$(INTDIR)\ReflectionOffset_Dsp.obj"	"$(INTDIR)\ReflectionOffset_Dsp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\SearchElement_Inspc.c

"$(INTDIR)\SearchElement_Inspc.obj"	"$(INTDIR)\SearchElement_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\TestReflectTarget.c

"$(INTDIR)\TestReflectTarget.obj"	"$(INTDIR)\TestReflectTarget.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\TestSecondCpu.c

"$(INTDIR)\TestSecondCpu.obj"	"$(INTDIR)\TestSecondCpu.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\InspcJ2c\WorkingThread_Inspc.c

"$(INTDIR)\WorkingThread_Inspc.obj"	"$(INTDIR)\WorkingThread_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\FileIoJc.c

"$(INTDIR)\FileIoJc.obj"	"$(INTDIR)\FileIoJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\FileSystemJc.c

"$(INTDIR)\FileSystemJc.obj"	"$(INTDIR)\FileSystemJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\ObjectJc.c

"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\OsWrapperJc.c

"$(INTDIR)\OsWrapperJc.obj"	"$(INTDIR)\OsWrapperJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\ReflectionBasetypesJc.c

"$(INTDIR)\ReflectionBasetypesJc.obj"	"$(INTDIR)\ReflectionBasetypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\ReflectionJc.c

"$(INTDIR)\ReflectionJc.obj"	"$(INTDIR)\ReflectionJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\ReflectionLoadExtJc.c

"$(INTDIR)\ReflectionLoadExtJc.obj"	"$(INTDIR)\ReflectionLoadExtJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\ReflMemAccessJc.c

"$(INTDIR)\ReflMemAccessJc.obj"	"$(INTDIR)\ReflMemAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\StringJc.c

"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\SystemJc.c

"$(INTDIR)\SystemJc.obj"	"$(INTDIR)\SystemJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\SystemOutJc.c

"$(INTDIR)\SystemOutJc.obj"	"$(INTDIR)\SystemOutJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Jc\ThreadJc.c

"$(INTDIR)\ThreadJc.obj"	"$(INTDIR)\ThreadJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_Exception.c

"$(INTDIR)\fw_Exception.obj"	"$(INTDIR)\fw_Exception.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_ExceptionPrintStacktrace.c

"$(INTDIR)\fw_ExceptionPrintStacktrace.obj"	"$(INTDIR)\fw_ExceptionPrintStacktrace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_MemC.c

"$(INTDIR)\fw_MemC.obj"	"$(INTDIR)\fw_MemC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_Object.c

"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_SimpleC.c

"$(INTDIR)\fw_SimpleC.obj"	"$(INTDIR)\fw_SimpleC.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_threadContext.c

"$(INTDIR)\fw_threadContext.obj"	"$(INTDIR)\fw_threadContext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_timeconversions.c

"$(INTDIR)\fw_timeconversions.obj"	"$(INTDIR)\fw_timeconversions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\Fwc\Reflection_Fwc.c

"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\OSAL\Reflection_OSAL.c

"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\J1c\ByteDataAccessJc.c

"$(INTDIR)\ByteDataAccessJc.obj"	"$(INTDIR)\ByteDataAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\CRuntimeJavalike\source\J1c\StringPartJc.c

"$(INTDIR)\StringPartJc.obj"	"$(INTDIR)\StringPartJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

