# Microsoft Developer Studio Generated NMAKE File, Based on TestReflectTargetLib.dsp
!IF "$(CFG)" == ""
CFG=TestReflectTargetLib - Win32 DebugCpp
!MESSAGE No configuration specified. Defaulting to TestReflectTargetLib - Win32 DebugCpp.
!ENDIF 

!IF "$(CFG)" != "TestReflectTargetLib - Win32 DebugCpp" && "$(CFG)" != "TestReflectTargetLib - Win32 DebugC" && "$(CFG)" != "TestReflectTargetLib - Win32 PreProc"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestReflectTargetLib.mak" CFG="TestReflectTargetLib - Win32 DebugCpp"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestReflectTargetLib - Win32 DebugCpp" (based on "Win32 (x86) Console Application")
!MESSAGE "TestReflectTargetLib - Win32 DebugC" (based on "Win32 (x86) Console Application")
!MESSAGE "TestReflectTargetLib - Win32 PreProc" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "TestReflectTargetLib - Win32 DebugCpp"

OUTDIR=T:\Jc\TestReflectTargetLib
INTDIR=T:\Jc\TestReflectTargetLib
# Begin Custom Macros
OutDir=T:\Jc\TestReflectTargetLib
# End Custom Macros

ALL : "$(OUTDIR)\TestReflectTargetLib.exe" "$(OUTDIR)\TestReflectTargetLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\ClassContent_Inspc.obj"
	-@erase "$(INTDIR)\ClassContent_Inspc.sbr"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.obj"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.obj"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.sbr"
	-@erase "$(INTDIR)\Comm_Inspc.obj"
	-@erase "$(INTDIR)\Comm_Inspc.sbr"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.obj"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.sbr"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.obj"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.sbr"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\TestReflectTarget.obj"
	-@erase "$(INTDIR)\TestReflectTarget.sbr"
	-@erase "$(INTDIR)\TestSecondCpu.obj"
	-@erase "$(INTDIR)\TestSecondCpu.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WorkingThread_Inspc.obj"
	-@erase "$(INTDIR)\WorkingThread_Inspc.sbr"
	-@erase "$(OUTDIR)\TestReflectTargetLib.bsc"
	-@erase "$(OUTDIR)\TestReflectTargetLib.exe"
	-@erase "$(OUTDIR)\TestReflectTargetLib.ilk"
	-@erase "$(OUTDIR)\TestReflectTargetLib.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "src_c" /I "gensrc_c" /I "../../CRuntimeJavalike/includeSpecials/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestReflectTargetLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /TP /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestReflectTargetLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\ClassContent_Inspc.sbr" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\Comm_Inspc.sbr" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\Inspector_Inspc.sbr" \
	"$(INTDIR)\ReflectionOffset_Dsp.sbr" \
	"$(INTDIR)\SearchElement_Inspc.sbr" \
	"$(INTDIR)\TestSecondCpu.sbr" \
	"$(INTDIR)\WorkingThread_Inspc.sbr" \
	"$(INTDIR)\TestReflectTarget.sbr" \
	"$(INTDIR)\Reflection_TestReflectTarget.sbr"

"$(OUTDIR)\TestReflectTargetLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestReflectTargetLib.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestReflectTargetLib.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\ReflectionOffset_Dsp.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\TestSecondCpu.obj" \
	"$(INTDIR)\WorkingThread_Inspc.obj" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\baseJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\simpleAllocJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\OSALJcD.lib" \
	"$(INTDIR)\TestReflectTarget.obj" \
	"$(INTDIR)\Reflection_TestReflectTarget.obj"

"$(OUTDIR)\TestReflectTargetLib.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestReflectTargetLib - Win32 DebugC"

OUTDIR=T:\Jc\TestReflectTargetLib_DebugC
INTDIR=T:\Jc\TestReflectTargetLib_DebugC
# Begin Custom Macros
OutDir=T:\Jc\TestReflectTargetLib_DebugC
# End Custom Macros

ALL : "$(OUTDIR)\TestReflectTargetLib.exe" "$(OUTDIR)\TestReflectTargetLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\ClassContent_Inspc.obj"
	-@erase "$(INTDIR)\ClassContent_Inspc.sbr"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.obj"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.obj"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.sbr"
	-@erase "$(INTDIR)\Comm_Inspc.obj"
	-@erase "$(INTDIR)\Comm_Inspc.sbr"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.obj"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.sbr"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.obj"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.sbr"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\TestReflectTarget.obj"
	-@erase "$(INTDIR)\TestReflectTarget.sbr"
	-@erase "$(INTDIR)\TestSecondCpu.obj"
	-@erase "$(INTDIR)\TestSecondCpu.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WorkingThread_Inspc.obj"
	-@erase "$(INTDIR)\WorkingThread_Inspc.sbr"
	-@erase "$(OUTDIR)\TestReflectTargetLib.bsc"
	-@erase "$(OUTDIR)\TestReflectTargetLib.exe"
	-@erase "$(OUTDIR)\TestReflectTargetLib.ilk"
	-@erase "$(OUTDIR)\TestReflectTargetLib.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MTd /W4 /ZI /Od /I "src_c" /I "gensrc_c" /I "../../CRuntimeJavalike/includeSpecials/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FAcs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestReflectTargetLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\ClassContent_Inspc.sbr" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\Comm_Inspc.sbr" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\Inspector_Inspc.sbr" \
	"$(INTDIR)\ReflectionOffset_Dsp.sbr" \
	"$(INTDIR)\SearchElement_Inspc.sbr" \
	"$(INTDIR)\TestSecondCpu.sbr" \
	"$(INTDIR)\WorkingThread_Inspc.sbr" \
	"$(INTDIR)\TestReflectTarget.sbr" \
	"$(INTDIR)\Reflection_TestReflectTarget.sbr"

"$(OUTDIR)\TestReflectTargetLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestReflectTargetLib.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestReflectTargetLib.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\ReflectionOffset_Dsp.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\TestSecondCpu.obj" \
	"$(INTDIR)\WorkingThread_Inspc.obj" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\baseJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\simpleAllocJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\OSALJcD.lib" \
	"$(INTDIR)\TestReflectTarget.obj" \
	"$(INTDIR)\Reflection_TestReflectTarget.obj"

"$(OUTDIR)\TestReflectTargetLib.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestReflectTargetLib - Win32 PreProc"

OUTDIR=T:\Jc\TestReflectTargetLib_PreProc
INTDIR=T:\Jc\TestReflectTargetLib_PreProc
# Begin Custom Macros
OutDir=T:\Jc\TestReflectTargetLib_PreProc
# End Custom Macros

ALL : "$(OUTDIR)\TestReflectTargetLib.exe" "$(OUTDIR)\TestReflectTargetLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\ClassContent_Inspc.obj"
	-@erase "$(INTDIR)\ClassContent_Inspc.sbr"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.obj"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.obj"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.sbr"
	-@erase "$(INTDIR)\Comm_Inspc.obj"
	-@erase "$(INTDIR)\Comm_Inspc.sbr"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.obj"
	-@erase "$(INTDIR)\Reflection_TestReflectTarget.sbr"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.obj"
	-@erase "$(INTDIR)\ReflectionOffset_Dsp.sbr"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\TestReflectTarget.obj"
	-@erase "$(INTDIR)\TestReflectTarget.sbr"
	-@erase "$(INTDIR)\TestSecondCpu.obj"
	-@erase "$(INTDIR)\TestSecondCpu.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WorkingThread_Inspc.obj"
	-@erase "$(INTDIR)\WorkingThread_Inspc.sbr"
	-@erase "$(OUTDIR)\TestReflectTargetLib.bsc"
	-@erase "$(OUTDIR)\TestReflectTargetLib.exe"
	-@erase "$(OUTDIR)\TestReflectTargetLib.ilk"
	-@erase "$(OUTDIR)\TestReflectTargetLib.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "src_c" /I "gensrc_c" /I "../../CRuntimeJavalike/includeSpecials/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestReflectTargetLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /P /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestReflectTargetLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\ClassContent_Inspc.sbr" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\Comm_Inspc.sbr" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\Inspector_Inspc.sbr" \
	"$(INTDIR)\ReflectionOffset_Dsp.sbr" \
	"$(INTDIR)\SearchElement_Inspc.sbr" \
	"$(INTDIR)\TestSecondCpu.sbr" \
	"$(INTDIR)\WorkingThread_Inspc.sbr" \
	"$(INTDIR)\TestReflectTarget.sbr" \
	"$(INTDIR)\Reflection_TestReflectTarget.sbr"

"$(OUTDIR)\TestReflectTargetLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\TestReflectTargetLib.pdb" /debug /machine:I386 /out:"$(OUTDIR)\TestReflectTargetLib.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\ReflectionOffset_Dsp.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\TestSecondCpu.obj" \
	"$(INTDIR)\WorkingThread_Inspc.obj" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\baseJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\simpleAllocJcD.lib" \
	"..\..\CRuntimeJavalike\lib\windows_VC98\OSALJcD.lib" \
	"$(INTDIR)\TestReflectTarget.obj" \
	"$(INTDIR)\Reflection_TestReflectTarget.obj"

"$(OUTDIR)\TestReflectTargetLib.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("TestReflectTargetLib.dep")
!INCLUDE "TestReflectTargetLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestReflectTargetLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestReflectTargetLib - Win32 DebugCpp" || "$(CFG)" == "TestReflectTargetLib - Win32 DebugC" || "$(CFG)" == "TestReflectTargetLib - Win32 PreProc"
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



!ENDIF 

