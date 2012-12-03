# Microsoft Developer Studio Generated NMAKE File, Based on baseJc.dsp
!IF "$(CFG)" == ""
CFG=CRuntimeJavalike_baseJclib - Win32 Release
!MESSAGE No configuration specified. Defaulting to CRuntimeJavalike_baseJclib - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "CRuntimeJavalike_baseJclib - Win32 Release" && "$(CFG)" != "CRuntimeJavalike_baseJclib - Win32 Debug" && "$(CFG)" != "CRuntimeJavalike_baseJclib - Win32 DebugCpp" && "$(CFG)" != "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "baseJc.mak" CFG="CRuntimeJavalike_baseJclib - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CRuntimeJavalike_baseJclib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_baseJclib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_baseJclib - Win32 DebugCpp" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp" (based on "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\baseJc.lib" "..\baseJc.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\ArraysJc.obj"
	-@erase "$(INTDIR)\ArraysJc.sbr"
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
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.obj"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.sbr"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\DateJc.sbr"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileIoJc.sbr"
	-@erase "$(INTDIR)\FileSystemJc.obj"
	-@erase "$(INTDIR)\FileSystemJc.sbr"
	-@erase "$(INTDIR)\FormatterJc.obj"
	-@erase "$(INTDIR)\FormatterJc.sbr"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMessage.sbr"
	-@erase "$(INTDIR)\fw_LogMsgStream.obj"
	-@erase "$(INTDIR)\fw_LogMsgStream.sbr"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_Object.sbr"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\InspcDataInfo_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataInfo_Inspc.sbr"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\InterProcessComm.obj"
	-@erase "$(INTDIR)\InterProcessComm.sbr"
	-@erase "$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj"
	-@erase "$(INTDIR)\InterProcessCommFactorySocket_Ipc.sbr"
	-@erase "$(INTDIR)\InterProcessCommSocket.obj"
	-@erase "$(INTDIR)\InterProcessCommSocket.sbr"
	-@erase "$(INTDIR)\LeapSecondsJc.obj"
	-@erase "$(INTDIR)\LeapSecondsJc.sbr"
	-@erase "$(INTDIR)\LinkedListJc.obj"
	-@erase "$(INTDIR)\LinkedListJc.sbr"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\LocaleJc.sbr"
	-@erase "$(INTDIR)\MathJc.obj"
	-@erase "$(INTDIR)\MathJc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\OsWrapperJc.obj"
	-@erase "$(INTDIR)\OsWrapperJc.sbr"
	-@erase "$(INTDIR)\PrintStreamJc.obj"
	-@erase "$(INTDIR)\PrintStreamJc.sbr"
	-@erase "$(INTDIR)\RawDataAccessJc.obj"
	-@erase "$(INTDIR)\RawDataAccessJc.sbr"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.sbr"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\Reflection_Ipc.obj"
	-@erase "$(INTDIR)\Reflection_Ipc.sbr"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.sbr"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.sbr"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.obj"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.sbr"
	-@erase "$(INTDIR)\ReflMemAccessJc.obj"
	-@erase "$(INTDIR)\ReflMemAccessJc.sbr"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\SpecialCharStringsJc.obj"
	-@erase "$(INTDIR)\SpecialCharStringsJc.sbr"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.sbr"
	-@erase "$(INTDIR)\StringFormatterJc.obj"
	-@erase "$(INTDIR)\StringFormatterJc.sbr"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringJc.sbr"
	-@erase "$(INTDIR)\StringPartJc.obj"
	-@erase "$(INTDIR)\StringPartJc.sbr"
	-@erase "$(INTDIR)\StringValueConvJc.obj"
	-@erase "$(INTDIR)\StringValueConvJc.sbr"
	-@erase "$(INTDIR)\SystemJc.obj"
	-@erase "$(INTDIR)\SystemJc.sbr"
	-@erase "$(INTDIR)\SystemOutJc.obj"
	-@erase "$(INTDIR)\SystemOutJc.sbr"
	-@erase "$(INTDIR)\ThreadJc.obj"
	-@erase "$(INTDIR)\ThreadJc.sbr"
	-@erase "$(INTDIR)\TimeZoneJc.obj"
	-@erase "$(INTDIR)\TimeZoneJc.sbr"
	-@erase "$(INTDIR)\UmlContainer_Dummy.obj"
	-@erase "$(INTDIR)\UmlContainer_Dummy.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\baseJc.bsc"
	-@erase "..\baseJc.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows_Msc6" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"..\baseJc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ArraysJc.sbr" \
	"$(INTDIR)\ConcurrentLinkedQueueJc.sbr" \
	"$(INTDIR)\DateJc.sbr" \
	"$(INTDIR)\FileIoJc.sbr" \
	"$(INTDIR)\FileSystemJc.sbr" \
	"$(INTDIR)\FormatterJc.sbr" \
	"$(INTDIR)\LinkedListJc.sbr" \
	"$(INTDIR)\LocaleJc.sbr" \
	"$(INTDIR)\MathJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\OsWrapperJc.sbr" \
	"$(INTDIR)\PrintStreamJc.sbr" \
	"$(INTDIR)\Reflection_AllJc.sbr" \
	"$(INTDIR)\ReflectionBasetypesJc.sbr" \
	"$(INTDIR)\ReflectionJc.sbr" \
	"$(INTDIR)\ReflectionLoadExtJc.sbr" \
	"$(INTDIR)\ReflMemAccessJc.sbr" \
	"$(INTDIR)\StringBufferJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\StringValueConvJc.sbr" \
	"$(INTDIR)\SystemJc.sbr" \
	"$(INTDIR)\SystemOutJc.sbr" \
	"$(INTDIR)\ThreadJc.sbr" \
	"$(INTDIR)\TimeZoneJc.sbr" \
	"$(INTDIR)\InterProcessComm.sbr" \
	"$(INTDIR)\InterProcessCommFactorySocket_Ipc.sbr" \
	"$(INTDIR)\InterProcessCommSocket.sbr" \
	"$(INTDIR)\Reflection_Ipc.sbr" \
	"$(INTDIR)\ByteDataAccessJc.sbr" \
	"$(INTDIR)\LeapSecondsJc.sbr" \
	"$(INTDIR)\RawDataAccessJc.sbr" \
	"$(INTDIR)\SpecialCharStringsJc.sbr" \
	"$(INTDIR)\StringFormatterJc.sbr" \
	"$(INTDIR)\StringPartJc.sbr" \
	"$(INTDIR)\UmlContainer_Dummy.sbr" \
	"$(INTDIR)\fw_LogMessage.sbr" \
	"$(INTDIR)\fw_LogMsgStream.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\Reflection_Fwc.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\ClassContent_Inspc.sbr" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\Comm_Inspc.sbr" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\Inspector_Inspc.sbr" \
	"$(INTDIR)\SearchElement_Inspc.sbr" \
	"$(INTDIR)\InspcDataInfo_Inspc.sbr"

"..\baseJc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\baseJc.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ArraysJc.obj" \
	"$(INTDIR)\ConcurrentLinkedQueueJc.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\FileSystemJc.obj" \
	"$(INTDIR)\FormatterJc.obj" \
	"$(INTDIR)\LinkedListJc.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\MathJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\OsWrapperJc.obj" \
	"$(INTDIR)\PrintStreamJc.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\ReflectionLoadExtJc.obj" \
	"$(INTDIR)\ReflMemAccessJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\StringValueConvJc.obj" \
	"$(INTDIR)\SystemJc.obj" \
	"$(INTDIR)\SystemOutJc.obj" \
	"$(INTDIR)\ThreadJc.obj" \
	"$(INTDIR)\TimeZoneJc.obj" \
	"$(INTDIR)\InterProcessComm.obj" \
	"$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj" \
	"$(INTDIR)\InterProcessCommSocket.obj" \
	"$(INTDIR)\Reflection_Ipc.obj" \
	"$(INTDIR)\ByteDataAccessJc.obj" \
	"$(INTDIR)\LeapSecondsJc.obj" \
	"$(INTDIR)\RawDataAccessJc.obj" \
	"$(INTDIR)\SpecialCharStringsJc.obj" \
	"$(INTDIR)\StringFormatterJc.obj" \
	"$(INTDIR)\StringPartJc.obj" \
	"$(INTDIR)\UmlContainer_Dummy.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\InspcDataInfo_Inspc.obj"

"..\baseJc.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"

OUTDIR=T:\CRuntimeJavalike\lib\baseJcD
INTDIR=T:\CRuntimeJavalike\lib\baseJcD

ALL : "..\baseJcD.lib" "..\baseJcD.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\ArraysJc.obj"
	-@erase "$(INTDIR)\ArraysJc.sbr"
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
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.obj"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.sbr"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\DateJc.sbr"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileIoJc.sbr"
	-@erase "$(INTDIR)\FileSystemJc.obj"
	-@erase "$(INTDIR)\FileSystemJc.sbr"
	-@erase "$(INTDIR)\FormatterJc.obj"
	-@erase "$(INTDIR)\FormatterJc.sbr"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMessage.sbr"
	-@erase "$(INTDIR)\fw_LogMsgStream.obj"
	-@erase "$(INTDIR)\fw_LogMsgStream.sbr"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\fw_Object.sbr"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\InspcDataInfo_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataInfo_Inspc.sbr"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\InterProcessComm.obj"
	-@erase "$(INTDIR)\InterProcessComm.sbr"
	-@erase "$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj"
	-@erase "$(INTDIR)\InterProcessCommFactorySocket_Ipc.sbr"
	-@erase "$(INTDIR)\InterProcessCommSocket.obj"
	-@erase "$(INTDIR)\InterProcessCommSocket.sbr"
	-@erase "$(INTDIR)\LeapSecondsJc.obj"
	-@erase "$(INTDIR)\LeapSecondsJc.sbr"
	-@erase "$(INTDIR)\LinkedListJc.obj"
	-@erase "$(INTDIR)\LinkedListJc.sbr"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\LocaleJc.sbr"
	-@erase "$(INTDIR)\MathJc.obj"
	-@erase "$(INTDIR)\MathJc.sbr"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\ObjectJc.sbr"
	-@erase "$(INTDIR)\OsWrapperJc.obj"
	-@erase "$(INTDIR)\OsWrapperJc.sbr"
	-@erase "$(INTDIR)\PrintStreamJc.obj"
	-@erase "$(INTDIR)\PrintStreamJc.sbr"
	-@erase "$(INTDIR)\RawDataAccessJc.obj"
	-@erase "$(INTDIR)\RawDataAccessJc.sbr"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.sbr"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\Reflection_Ipc.obj"
	-@erase "$(INTDIR)\Reflection_Ipc.sbr"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.sbr"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.sbr"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.obj"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.sbr"
	-@erase "$(INTDIR)\ReflMemAccessJc.obj"
	-@erase "$(INTDIR)\ReflMemAccessJc.sbr"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\SpecialCharStringsJc.obj"
	-@erase "$(INTDIR)\SpecialCharStringsJc.sbr"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.sbr"
	-@erase "$(INTDIR)\StringFormatterJc.obj"
	-@erase "$(INTDIR)\StringFormatterJc.sbr"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringJc.sbr"
	-@erase "$(INTDIR)\StringPartJc.obj"
	-@erase "$(INTDIR)\StringPartJc.sbr"
	-@erase "$(INTDIR)\StringValueConvJc.obj"
	-@erase "$(INTDIR)\StringValueConvJc.sbr"
	-@erase "$(INTDIR)\SystemJc.obj"
	-@erase "$(INTDIR)\SystemJc.sbr"
	-@erase "$(INTDIR)\SystemOutJc.obj"
	-@erase "$(INTDIR)\SystemOutJc.sbr"
	-@erase "$(INTDIR)\ThreadJc.obj"
	-@erase "$(INTDIR)\ThreadJc.sbr"
	-@erase "$(INTDIR)\TimeZoneJc.obj"
	-@erase "$(INTDIR)\TimeZoneJc.sbr"
	-@erase "$(INTDIR)\UmlContainer_Dummy.obj"
	-@erase "$(INTDIR)\UmlContainer_Dummy.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\baseJcD.bsc"
	-@erase "..\baseJcD.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MTd /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows_Msc6" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"..\baseJcD.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ArraysJc.sbr" \
	"$(INTDIR)\ConcurrentLinkedQueueJc.sbr" \
	"$(INTDIR)\DateJc.sbr" \
	"$(INTDIR)\FileIoJc.sbr" \
	"$(INTDIR)\FileSystemJc.sbr" \
	"$(INTDIR)\FormatterJc.sbr" \
	"$(INTDIR)\LinkedListJc.sbr" \
	"$(INTDIR)\LocaleJc.sbr" \
	"$(INTDIR)\MathJc.sbr" \
	"$(INTDIR)\ObjectJc.sbr" \
	"$(INTDIR)\OsWrapperJc.sbr" \
	"$(INTDIR)\PrintStreamJc.sbr" \
	"$(INTDIR)\Reflection_AllJc.sbr" \
	"$(INTDIR)\ReflectionBasetypesJc.sbr" \
	"$(INTDIR)\ReflectionJc.sbr" \
	"$(INTDIR)\ReflectionLoadExtJc.sbr" \
	"$(INTDIR)\ReflMemAccessJc.sbr" \
	"$(INTDIR)\StringBufferJc.sbr" \
	"$(INTDIR)\StringJc.sbr" \
	"$(INTDIR)\StringValueConvJc.sbr" \
	"$(INTDIR)\SystemJc.sbr" \
	"$(INTDIR)\SystemOutJc.sbr" \
	"$(INTDIR)\ThreadJc.sbr" \
	"$(INTDIR)\TimeZoneJc.sbr" \
	"$(INTDIR)\InterProcessComm.sbr" \
	"$(INTDIR)\InterProcessCommFactorySocket_Ipc.sbr" \
	"$(INTDIR)\InterProcessCommSocket.sbr" \
	"$(INTDIR)\Reflection_Ipc.sbr" \
	"$(INTDIR)\ByteDataAccessJc.sbr" \
	"$(INTDIR)\LeapSecondsJc.sbr" \
	"$(INTDIR)\RawDataAccessJc.sbr" \
	"$(INTDIR)\SpecialCharStringsJc.sbr" \
	"$(INTDIR)\StringFormatterJc.sbr" \
	"$(INTDIR)\StringPartJc.sbr" \
	"$(INTDIR)\UmlContainer_Dummy.sbr" \
	"$(INTDIR)\fw_LogMessage.sbr" \
	"$(INTDIR)\fw_LogMsgStream.sbr" \
	"$(INTDIR)\fw_Object.sbr" \
	"$(INTDIR)\Reflection_Fwc.sbr" \
	"$(INTDIR)\Reflection_OSAL.sbr" \
	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\ClassContent_Inspc.sbr" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\Comm_Inspc.sbr" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\Inspector_Inspc.sbr" \
	"$(INTDIR)\SearchElement_Inspc.sbr" \
	"$(INTDIR)\InspcDataInfo_Inspc.sbr"

"..\baseJcD.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\baseJcD.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ArraysJc.obj" \
	"$(INTDIR)\ConcurrentLinkedQueueJc.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\FileSystemJc.obj" \
	"$(INTDIR)\FormatterJc.obj" \
	"$(INTDIR)\LinkedListJc.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\MathJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\OsWrapperJc.obj" \
	"$(INTDIR)\PrintStreamJc.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\ReflectionLoadExtJc.obj" \
	"$(INTDIR)\ReflMemAccessJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\StringValueConvJc.obj" \
	"$(INTDIR)\SystemJc.obj" \
	"$(INTDIR)\SystemOutJc.obj" \
	"$(INTDIR)\ThreadJc.obj" \
	"$(INTDIR)\TimeZoneJc.obj" \
	"$(INTDIR)\InterProcessComm.obj" \
	"$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj" \
	"$(INTDIR)\InterProcessCommSocket.obj" \
	"$(INTDIR)\Reflection_Ipc.obj" \
	"$(INTDIR)\ByteDataAccessJc.obj" \
	"$(INTDIR)\LeapSecondsJc.obj" \
	"$(INTDIR)\RawDataAccessJc.obj" \
	"$(INTDIR)\SpecialCharStringsJc.obj" \
	"$(INTDIR)\StringFormatterJc.obj" \
	"$(INTDIR)\StringPartJc.obj" \
	"$(INTDIR)\UmlContainer_Dummy.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\InspcDataInfo_Inspc.obj"

"..\baseJcD.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"

OUTDIR=.\..
INTDIR=T:\CRuntimeJavalike_baseJclib\DebugCpp
# Begin Custom Macros
OutDir=.\..
# End Custom Macros

ALL : "$(OUTDIR)\baseJcppD.lib" "$(OUTDIR)\baseJcppD.bsc"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\ArraysJc.obj"
	-@erase "$(INTDIR)\browse\AnswerComm_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\browse\ArraysJc.sbr"
	-@erase "$(INTDIR)\browse\ByteDataAccessJc.sbr"
	-@erase "$(INTDIR)\browse\ClassContent_Inspc.sbr"
	-@erase "$(INTDIR)\browse\CmdConsumer_ifc_Inspc.sbr"
	-@erase "$(INTDIR)\browse\CmdExecuter_Inspc.sbr"
	-@erase "$(INTDIR)\browse\Comm_Inspc.sbr"
	-@erase "$(INTDIR)\browse\ConcurrentLinkedQueueJc.sbr"
	-@erase "$(INTDIR)\browse\DateJc.sbr"
	-@erase "$(INTDIR)\browse\FileIoJc.sbr"
	-@erase "$(INTDIR)\browse\FileSystemJc.sbr"
	-@erase "$(INTDIR)\browse\FormatterJc.sbr"
	-@erase "$(INTDIR)\browse\fw_LogMessage.sbr"
	-@erase "$(INTDIR)\browse\fw_LogMsgStream.sbr"
	-@erase "$(INTDIR)\browse\fw_Object.sbr"
	-@erase "$(INTDIR)\browse\InspcDataExchangeAccess_Inspc.sbr"
	-@erase "$(INTDIR)\browse\InspcDataInfo_Inspc.sbr"
	-@erase "$(INTDIR)\browse\Inspector_Inspc.sbr"
	-@erase "$(INTDIR)\browse\InterProcessComm.sbr"
	-@erase "$(INTDIR)\browse\InterProcessCommFactorySocket_Ipc.sbr"
	-@erase "$(INTDIR)\browse\InterProcessCommSocket.sbr"
	-@erase "$(INTDIR)\browse\LeapSecondsJc.sbr"
	-@erase "$(INTDIR)\browse\LinkedListJc.sbr"
	-@erase "$(INTDIR)\browse\LocaleJc.sbr"
	-@erase "$(INTDIR)\browse\MathJc.sbr"
	-@erase "$(INTDIR)\browse\ObjectJc.sbr"
	-@erase "$(INTDIR)\browse\OsWrapperJc.sbr"
	-@erase "$(INTDIR)\browse\PrintStreamJc.sbr"
	-@erase "$(INTDIR)\browse\RawDataAccessJc.sbr"
	-@erase "$(INTDIR)\browse\Reflection_AllJc.sbr"
	-@erase "$(INTDIR)\browse\Reflection_Fwc.sbr"
	-@erase "$(INTDIR)\browse\Reflection_Ipc.sbr"
	-@erase "$(INTDIR)\browse\Reflection_OSAL.sbr"
	-@erase "$(INTDIR)\browse\ReflectionBasetypesJc.sbr"
	-@erase "$(INTDIR)\browse\ReflectionJc.sbr"
	-@erase "$(INTDIR)\browse\ReflectionLoadExtJc.sbr"
	-@erase "$(INTDIR)\browse\ReflMemAccessJc.sbr"
	-@erase "$(INTDIR)\browse\SearchElement_Inspc.sbr"
	-@erase "$(INTDIR)\browse\SpecialCharStringsJc.sbr"
	-@erase "$(INTDIR)\browse\StringBufferJc.sbr"
	-@erase "$(INTDIR)\browse\StringFormatterJc.sbr"
	-@erase "$(INTDIR)\browse\StringJc.sbr"
	-@erase "$(INTDIR)\browse\StringPartJc.sbr"
	-@erase "$(INTDIR)\browse\StringValueConvJc.sbr"
	-@erase "$(INTDIR)\browse\SystemJc.sbr"
	-@erase "$(INTDIR)\browse\SystemOutJc.sbr"
	-@erase "$(INTDIR)\browse\ThreadJc.sbr"
	-@erase "$(INTDIR)\browse\TimeZoneJc.sbr"
	-@erase "$(INTDIR)\browse\UmlContainer_Dummy.sbr"
	-@erase "$(INTDIR)\ByteDataAccessJc.obj"
	-@erase "$(INTDIR)\ClassContent_Inspc.obj"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.obj"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.obj"
	-@erase "$(INTDIR)\Comm_Inspc.obj"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.obj"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileSystemJc.obj"
	-@erase "$(INTDIR)\FormatterJc.obj"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMsgStream.obj"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataInfo_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\InterProcessComm.obj"
	-@erase "$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj"
	-@erase "$(INTDIR)\InterProcessCommSocket.obj"
	-@erase "$(INTDIR)\LeapSecondsJc.obj"
	-@erase "$(INTDIR)\LinkedListJc.obj"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\MathJc.obj"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\OsWrapperJc.obj"
	-@erase "$(INTDIR)\PrintStreamJc.obj"
	-@erase "$(INTDIR)\RawDataAccessJc.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Ipc.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.obj"
	-@erase "$(INTDIR)\ReflMemAccessJc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SpecialCharStringsJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringFormatterJc.obj"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringPartJc.obj"
	-@erase "$(INTDIR)\StringValueConvJc.obj"
	-@erase "$(INTDIR)\SystemJc.obj"
	-@erase "$(INTDIR)\SystemOutJc.obj"
	-@erase "$(INTDIR)\ThreadJc.obj"
	-@erase "$(INTDIR)\TimeZoneJc.obj"
	-@erase "$(INTDIR)\UmlContainer_Dummy.obj"
	-@erase "$(OUTDIR)\baseJcppD.bsc"
	-@erase "$(OUTDIR)\baseJcppD.lib"
	-@erase "..\baseJcppD.idb"
	-@erase "..\baseJcppD.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /Zp1 /MTd /W4 /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows_Msc6" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FAs /Fa"$(INTDIR)\\" /Fr"$(INTDIR)\browse\\" /Fo"$(INTDIR)\\" /Fd"..\baseJcppD.pdb" /FD /GZ /TP /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\baseJcppD.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\browse\ArraysJc.sbr" \
	"$(INTDIR)\browse\ConcurrentLinkedQueueJc.sbr" \
	"$(INTDIR)\browse\DateJc.sbr" \
	"$(INTDIR)\browse\FileIoJc.sbr" \
	"$(INTDIR)\browse\FileSystemJc.sbr" \
	"$(INTDIR)\browse\FormatterJc.sbr" \
	"$(INTDIR)\browse\LinkedListJc.sbr" \
	"$(INTDIR)\browse\LocaleJc.sbr" \
	"$(INTDIR)\browse\MathJc.sbr" \
	"$(INTDIR)\browse\ObjectJc.sbr" \
	"$(INTDIR)\browse\OsWrapperJc.sbr" \
	"$(INTDIR)\browse\PrintStreamJc.sbr" \
	"$(INTDIR)\browse\Reflection_AllJc.sbr" \
	"$(INTDIR)\browse\ReflectionBasetypesJc.sbr" \
	"$(INTDIR)\browse\ReflectionJc.sbr" \
	"$(INTDIR)\browse\ReflectionLoadExtJc.sbr" \
	"$(INTDIR)\browse\ReflMemAccessJc.sbr" \
	"$(INTDIR)\browse\StringBufferJc.sbr" \
	"$(INTDIR)\browse\StringJc.sbr" \
	"$(INTDIR)\browse\StringValueConvJc.sbr" \
	"$(INTDIR)\browse\SystemJc.sbr" \
	"$(INTDIR)\browse\SystemOutJc.sbr" \
	"$(INTDIR)\browse\ThreadJc.sbr" \
	"$(INTDIR)\browse\TimeZoneJc.sbr" \
	"$(INTDIR)\browse\InterProcessComm.sbr" \
	"$(INTDIR)\browse\InterProcessCommFactorySocket_Ipc.sbr" \
	"$(INTDIR)\browse\InterProcessCommSocket.sbr" \
	"$(INTDIR)\browse\Reflection_Ipc.sbr" \
	"$(INTDIR)\browse\ByteDataAccessJc.sbr" \
	"$(INTDIR)\browse\LeapSecondsJc.sbr" \
	"$(INTDIR)\browse\RawDataAccessJc.sbr" \
	"$(INTDIR)\browse\SpecialCharStringsJc.sbr" \
	"$(INTDIR)\browse\StringFormatterJc.sbr" \
	"$(INTDIR)\browse\StringPartJc.sbr" \
	"$(INTDIR)\browse\UmlContainer_Dummy.sbr" \
	"$(INTDIR)\browse\fw_LogMessage.sbr" \
	"$(INTDIR)\browse\fw_LogMsgStream.sbr" \
	"$(INTDIR)\browse\fw_Object.sbr" \
	"$(INTDIR)\browse\Reflection_Fwc.sbr" \
	"$(INTDIR)\browse\Reflection_OSAL.sbr" \
	"$(INTDIR)\browse\AnswerComm_ifc_Inspc.sbr" \
	"$(INTDIR)\browse\ClassContent_Inspc.sbr" \
	"$(INTDIR)\browse\CmdConsumer_ifc_Inspc.sbr" \
	"$(INTDIR)\browse\CmdExecuter_Inspc.sbr" \
	"$(INTDIR)\browse\Comm_Inspc.sbr" \
	"$(INTDIR)\browse\InspcDataExchangeAccess_Inspc.sbr" \
	"$(INTDIR)\browse\Inspector_Inspc.sbr" \
	"$(INTDIR)\browse\SearchElement_Inspc.sbr" \
	"$(INTDIR)\browse\InspcDataInfo_Inspc.sbr"

"$(OUTDIR)\baseJcppD.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\baseJcppD.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ArraysJc.obj" \
	"$(INTDIR)\ConcurrentLinkedQueueJc.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\FileSystemJc.obj" \
	"$(INTDIR)\FormatterJc.obj" \
	"$(INTDIR)\LinkedListJc.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\MathJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\OsWrapperJc.obj" \
	"$(INTDIR)\PrintStreamJc.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\ReflectionLoadExtJc.obj" \
	"$(INTDIR)\ReflMemAccessJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\StringValueConvJc.obj" \
	"$(INTDIR)\SystemJc.obj" \
	"$(INTDIR)\SystemOutJc.obj" \
	"$(INTDIR)\ThreadJc.obj" \
	"$(INTDIR)\TimeZoneJc.obj" \
	"$(INTDIR)\InterProcessComm.obj" \
	"$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj" \
	"$(INTDIR)\InterProcessCommSocket.obj" \
	"$(INTDIR)\Reflection_Ipc.obj" \
	"$(INTDIR)\ByteDataAccessJc.obj" \
	"$(INTDIR)\LeapSecondsJc.obj" \
	"$(INTDIR)\RawDataAccessJc.obj" \
	"$(INTDIR)\SpecialCharStringsJc.obj" \
	"$(INTDIR)\StringFormatterJc.obj" \
	"$(INTDIR)\StringPartJc.obj" \
	"$(INTDIR)\UmlContainer_Dummy.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\InspcDataInfo_Inspc.obj"

"$(OUTDIR)\baseJcppD.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"

OUTDIR=.\CRuntimeJavalike_baseJclib___Win32_ReleaseCpp
INTDIR=.\CRuntimeJavalike_baseJclib___Win32_ReleaseCpp

ALL : "..\baseJc.lib"


CLEAN :
	-@erase "$(INTDIR)\AnswerComm_ifc_Inspc.obj"
	-@erase "$(INTDIR)\ArraysJc.obj"
	-@erase "$(INTDIR)\ByteDataAccessJc.obj"
	-@erase "$(INTDIR)\ClassContent_Inspc.obj"
	-@erase "$(INTDIR)\CmdConsumer_ifc_Inspc.obj"
	-@erase "$(INTDIR)\CmdExecuter_Inspc.obj"
	-@erase "$(INTDIR)\Comm_Inspc.obj"
	-@erase "$(INTDIR)\ConcurrentLinkedQueueJc.obj"
	-@erase "$(INTDIR)\DateJc.obj"
	-@erase "$(INTDIR)\FileIoJc.obj"
	-@erase "$(INTDIR)\FileSystemJc.obj"
	-@erase "$(INTDIR)\FormatterJc.obj"
	-@erase "$(INTDIR)\fw_LogMessage.obj"
	-@erase "$(INTDIR)\fw_LogMsgStream.obj"
	-@erase "$(INTDIR)\fw_Object.obj"
	-@erase "$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"
	-@erase "$(INTDIR)\InspcDataInfo_Inspc.obj"
	-@erase "$(INTDIR)\Inspector_Inspc.obj"
	-@erase "$(INTDIR)\InterProcessComm.obj"
	-@erase "$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj"
	-@erase "$(INTDIR)\InterProcessCommSocket.obj"
	-@erase "$(INTDIR)\LeapSecondsJc.obj"
	-@erase "$(INTDIR)\LinkedListJc.obj"
	-@erase "$(INTDIR)\LocaleJc.obj"
	-@erase "$(INTDIR)\MathJc.obj"
	-@erase "$(INTDIR)\ObjectJc.obj"
	-@erase "$(INTDIR)\OsWrapperJc.obj"
	-@erase "$(INTDIR)\PrintStreamJc.obj"
	-@erase "$(INTDIR)\RawDataAccessJc.obj"
	-@erase "$(INTDIR)\Reflection_AllJc.obj"
	-@erase "$(INTDIR)\Reflection_Fwc.obj"
	-@erase "$(INTDIR)\Reflection_Ipc.obj"
	-@erase "$(INTDIR)\Reflection_OSAL.obj"
	-@erase "$(INTDIR)\ReflectionBasetypesJc.obj"
	-@erase "$(INTDIR)\ReflectionJc.obj"
	-@erase "$(INTDIR)\ReflectionLoadExtJc.obj"
	-@erase "$(INTDIR)\ReflMemAccessJc.obj"
	-@erase "$(INTDIR)\SearchElement_Inspc.obj"
	-@erase "$(INTDIR)\SpecialCharStringsJc.obj"
	-@erase "$(INTDIR)\StringBufferJc.obj"
	-@erase "$(INTDIR)\StringFormatterJc.obj"
	-@erase "$(INTDIR)\StringJc.obj"
	-@erase "$(INTDIR)\StringPartJc.obj"
	-@erase "$(INTDIR)\StringValueConvJc.obj"
	-@erase "$(INTDIR)\SystemJc.obj"
	-@erase "$(INTDIR)\SystemOutJc.obj"
	-@erase "$(INTDIR)\ThreadJc.obj"
	-@erase "$(INTDIR)\TimeZoneJc.obj"
	-@erase "$(INTDIR)\UmlContainer_Dummy.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\baseJc.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows_Msc6" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"..\baseJc.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\baseJc.lib" 
LIB32_OBJS= \
	"$(INTDIR)\ArraysJc.obj" \
	"$(INTDIR)\ConcurrentLinkedQueueJc.obj" \
	"$(INTDIR)\DateJc.obj" \
	"$(INTDIR)\FileIoJc.obj" \
	"$(INTDIR)\FileSystemJc.obj" \
	"$(INTDIR)\FormatterJc.obj" \
	"$(INTDIR)\LinkedListJc.obj" \
	"$(INTDIR)\LocaleJc.obj" \
	"$(INTDIR)\MathJc.obj" \
	"$(INTDIR)\ObjectJc.obj" \
	"$(INTDIR)\OsWrapperJc.obj" \
	"$(INTDIR)\PrintStreamJc.obj" \
	"$(INTDIR)\Reflection_AllJc.obj" \
	"$(INTDIR)\ReflectionBasetypesJc.obj" \
	"$(INTDIR)\ReflectionJc.obj" \
	"$(INTDIR)\ReflectionLoadExtJc.obj" \
	"$(INTDIR)\ReflMemAccessJc.obj" \
	"$(INTDIR)\StringBufferJc.obj" \
	"$(INTDIR)\StringJc.obj" \
	"$(INTDIR)\StringValueConvJc.obj" \
	"$(INTDIR)\SystemJc.obj" \
	"$(INTDIR)\SystemOutJc.obj" \
	"$(INTDIR)\ThreadJc.obj" \
	"$(INTDIR)\TimeZoneJc.obj" \
	"$(INTDIR)\InterProcessComm.obj" \
	"$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj" \
	"$(INTDIR)\InterProcessCommSocket.obj" \
	"$(INTDIR)\Reflection_Ipc.obj" \
	"$(INTDIR)\ByteDataAccessJc.obj" \
	"$(INTDIR)\LeapSecondsJc.obj" \
	"$(INTDIR)\RawDataAccessJc.obj" \
	"$(INTDIR)\SpecialCharStringsJc.obj" \
	"$(INTDIR)\StringFormatterJc.obj" \
	"$(INTDIR)\StringPartJc.obj" \
	"$(INTDIR)\UmlContainer_Dummy.obj" \
	"$(INTDIR)\fw_LogMessage.obj" \
	"$(INTDIR)\fw_LogMsgStream.obj" \
	"$(INTDIR)\fw_Object.obj" \
	"$(INTDIR)\Reflection_Fwc.obj" \
	"$(INTDIR)\Reflection_OSAL.obj" \
	"$(INTDIR)\AnswerComm_ifc_Inspc.obj" \
	"$(INTDIR)\ClassContent_Inspc.obj" \
	"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" \
	"$(INTDIR)\CmdExecuter_Inspc.obj" \
	"$(INTDIR)\Comm_Inspc.obj" \
	"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" \
	"$(INTDIR)\Inspector_Inspc.obj" \
	"$(INTDIR)\SearchElement_Inspc.obj" \
	"$(INTDIR)\InspcDataInfo_Inspc.obj"

"..\baseJc.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("baseJc.dep")
!INCLUDE "baseJc.dep"
!ELSE 
!MESSAGE Warning: cannot find "baseJc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release" || "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug" || "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp" || "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"
SOURCE=..\..\..\source\Jc\ArraysJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ArraysJc.obj"	"$(INTDIR)\ArraysJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ArraysJc.obj"	"$(INTDIR)\ArraysJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ArraysJc.obj"	"$(INTDIR)\browse\ArraysJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ArraysJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\ConcurrentLinkedQueueJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ConcurrentLinkedQueueJc.obj"	"$(INTDIR)\ConcurrentLinkedQueueJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ConcurrentLinkedQueueJc.obj"	"$(INTDIR)\ConcurrentLinkedQueueJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ConcurrentLinkedQueueJc.obj"	"$(INTDIR)\browse\ConcurrentLinkedQueueJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ConcurrentLinkedQueueJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\DateJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\DateJc.obj"	"$(INTDIR)\DateJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\DateJc.obj"	"$(INTDIR)\DateJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\DateJc.obj"	"$(INTDIR)\browse\DateJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\DateJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\FileIoJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\FileIoJc.obj"	"$(INTDIR)\FileIoJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\FileIoJc.obj"	"$(INTDIR)\FileIoJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\FileIoJc.obj"	"$(INTDIR)\browse\FileIoJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\FileIoJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\FileSystemJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\FileSystemJc.obj"	"$(INTDIR)\FileSystemJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\FileSystemJc.obj"	"$(INTDIR)\FileSystemJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\FileSystemJc.obj"	"$(INTDIR)\browse\FileSystemJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\FileSystemJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\FormatterJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\FormatterJc.obj"	"$(INTDIR)\FormatterJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\FormatterJc.obj"	"$(INTDIR)\FormatterJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\FormatterJc.obj"	"$(INTDIR)\browse\FormatterJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\FormatterJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\LinkedListJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\LinkedListJc.obj"	"$(INTDIR)\LinkedListJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\LinkedListJc.obj"	"$(INTDIR)\LinkedListJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\LinkedListJc.obj"	"$(INTDIR)\browse\LinkedListJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\LinkedListJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\LocaleJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\LocaleJc.obj"	"$(INTDIR)\browse\LocaleJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\LocaleJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\MathJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\MathJc.obj"	"$(INTDIR)\MathJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\MathJc.obj"	"$(INTDIR)\MathJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\MathJc.obj"	"$(INTDIR)\browse\MathJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\MathJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\ObjectJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ObjectJc.obj"	"$(INTDIR)\browse\ObjectJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ObjectJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\OsWrapperJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\OsWrapperJc.obj"	"$(INTDIR)\OsWrapperJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\OsWrapperJc.obj"	"$(INTDIR)\OsWrapperJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\OsWrapperJc.obj"	"$(INTDIR)\browse\OsWrapperJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\OsWrapperJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\PrintStreamJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\PrintStreamJc.obj"	"$(INTDIR)\PrintStreamJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\PrintStreamJc.obj"	"$(INTDIR)\PrintStreamJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\PrintStreamJc.obj"	"$(INTDIR)\browse\PrintStreamJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\PrintStreamJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\Reflection_AllJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\Reflection_AllJc.obj"	"$(INTDIR)\browse\Reflection_AllJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\Reflection_AllJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\ReflectionBasetypesJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ReflectionBasetypesJc.obj"	"$(INTDIR)\ReflectionBasetypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ReflectionBasetypesJc.obj"	"$(INTDIR)\ReflectionBasetypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ReflectionBasetypesJc.obj"	"$(INTDIR)\browse\ReflectionBasetypesJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ReflectionBasetypesJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\ReflectionJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ReflectionJc.obj"	"$(INTDIR)\ReflectionJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ReflectionJc.obj"	"$(INTDIR)\ReflectionJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ReflectionJc.obj"	"$(INTDIR)\browse\ReflectionJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ReflectionJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\ReflectionLoadExtJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ReflectionLoadExtJc.obj"	"$(INTDIR)\ReflectionLoadExtJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ReflectionLoadExtJc.obj"	"$(INTDIR)\ReflectionLoadExtJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ReflectionLoadExtJc.obj"	"$(INTDIR)\browse\ReflectionLoadExtJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ReflectionLoadExtJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\ReflMemAccessJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ReflMemAccessJc.obj"	"$(INTDIR)\ReflMemAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ReflMemAccessJc.obj"	"$(INTDIR)\ReflMemAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ReflMemAccessJc.obj"	"$(INTDIR)\browse\ReflMemAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ReflMemAccessJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\StringBufferJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\StringBufferJc.obj"	"$(INTDIR)\browse\StringBufferJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\StringBufferJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\StringJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\StringJc.obj"	"$(INTDIR)\browse\StringJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\StringJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\StringValueConvJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\StringValueConvJc.obj"	"$(INTDIR)\StringValueConvJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\StringValueConvJc.obj"	"$(INTDIR)\StringValueConvJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\StringValueConvJc.obj"	"$(INTDIR)\browse\StringValueConvJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\StringValueConvJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\SystemJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\SystemJc.obj"	"$(INTDIR)\SystemJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\SystemJc.obj"	"$(INTDIR)\SystemJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\SystemJc.obj"	"$(INTDIR)\browse\SystemJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\SystemJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\SystemOutJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\SystemOutJc.obj"	"$(INTDIR)\SystemOutJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\SystemOutJc.obj"	"$(INTDIR)\SystemOutJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\SystemOutJc.obj"	"$(INTDIR)\browse\SystemOutJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\SystemOutJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\ThreadJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ThreadJc.obj"	"$(INTDIR)\ThreadJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ThreadJc.obj"	"$(INTDIR)\ThreadJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ThreadJc.obj"	"$(INTDIR)\browse\ThreadJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ThreadJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Jc\TimeZoneJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\TimeZoneJc.obj"	"$(INTDIR)\TimeZoneJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\TimeZoneJc.obj"	"$(INTDIR)\TimeZoneJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\TimeZoneJc.obj"	"$(INTDIR)\browse\TimeZoneJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\TimeZoneJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Ipc\InterProcessComm.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\InterProcessComm.obj"	"$(INTDIR)\InterProcessComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\InterProcessComm.obj"	"$(INTDIR)\InterProcessComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\InterProcessComm.obj"	"$(INTDIR)\browse\InterProcessComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\InterProcessComm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Ipc2c\InterProcessCommFactorySocket_Ipc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj"	"$(INTDIR)\InterProcessCommFactorySocket_Ipc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj"	"$(INTDIR)\InterProcessCommFactorySocket_Ipc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj"	"$(INTDIR)\browse\InterProcessCommFactorySocket_Ipc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\InterProcessCommFactorySocket_Ipc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Ipc\InterProcessCommSocket.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\InterProcessCommSocket.obj"	"$(INTDIR)\InterProcessCommSocket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\InterProcessCommSocket.obj"	"$(INTDIR)\InterProcessCommSocket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\InterProcessCommSocket.obj"	"$(INTDIR)\browse\InterProcessCommSocket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\InterProcessCommSocket.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Ipc\Reflection_Ipc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\Reflection_Ipc.obj"	"$(INTDIR)\Reflection_Ipc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\Reflection_Ipc.obj"	"$(INTDIR)\Reflection_Ipc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\Reflection_Ipc.obj"	"$(INTDIR)\browse\Reflection_Ipc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\Reflection_Ipc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\J1c\ByteDataAccessJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ByteDataAccessJc.obj"	"$(INTDIR)\ByteDataAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ByteDataAccessJc.obj"	"$(INTDIR)\ByteDataAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ByteDataAccessJc.obj"	"$(INTDIR)\browse\ByteDataAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ByteDataAccessJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\J1c\LeapSecondsJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\LeapSecondsJc.obj"	"$(INTDIR)\LeapSecondsJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\LeapSecondsJc.obj"	"$(INTDIR)\LeapSecondsJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\LeapSecondsJc.obj"	"$(INTDIR)\browse\LeapSecondsJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\LeapSecondsJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\J1c\RawDataAccessJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\RawDataAccessJc.obj"	"$(INTDIR)\RawDataAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\RawDataAccessJc.obj"	"$(INTDIR)\RawDataAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\RawDataAccessJc.obj"	"$(INTDIR)\browse\RawDataAccessJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\RawDataAccessJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\J1c\SpecialCharStringsJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\SpecialCharStringsJc.obj"	"$(INTDIR)\SpecialCharStringsJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\SpecialCharStringsJc.obj"	"$(INTDIR)\SpecialCharStringsJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\SpecialCharStringsJc.obj"	"$(INTDIR)\browse\SpecialCharStringsJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\SpecialCharStringsJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\J1c\StringFormatterJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\StringFormatterJc.obj"	"$(INTDIR)\StringFormatterJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\StringFormatterJc.obj"	"$(INTDIR)\StringFormatterJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\StringFormatterJc.obj"	"$(INTDIR)\browse\StringFormatterJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\StringFormatterJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\J1c\StringPartJc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\StringPartJc.obj"	"$(INTDIR)\StringPartJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\StringPartJc.obj"	"$(INTDIR)\StringPartJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\StringPartJc.obj"	"$(INTDIR)\browse\StringPartJc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\StringPartJc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\FwConv\UmlContainer_Dummy.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\UmlContainer_Dummy.obj"	"$(INTDIR)\UmlContainer_Dummy.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\UmlContainer_Dummy.obj"	"$(INTDIR)\UmlContainer_Dummy.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\UmlContainer_Dummy.obj"	"$(INTDIR)\browse\UmlContainer_Dummy.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\UmlContainer_Dummy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Fwc\fw_LogMessage.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\fw_LogMessage.obj"	"$(INTDIR)\browse\fw_LogMessage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\fw_LogMessage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Fwc\fw_LogMsgStream.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\fw_LogMsgStream.obj"	"$(INTDIR)\fw_LogMsgStream.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\fw_LogMsgStream.obj"	"$(INTDIR)\fw_LogMsgStream.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\fw_LogMsgStream.obj"	"$(INTDIR)\browse\fw_LogMsgStream.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\fw_LogMsgStream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Fwc\fw_Object.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\fw_Object.obj"	"$(INTDIR)\browse\fw_Object.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\fw_Object.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\Fwc\Reflection_Fwc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\Reflection_Fwc.obj"	"$(INTDIR)\browse\Reflection_Fwc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\Reflection_Fwc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\OSAL\Reflection_OSAL.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\Reflection_OSAL.obj"	"$(INTDIR)\browse\Reflection_OSAL.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\Reflection_OSAL.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\AnswerComm_ifc_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\AnswerComm_ifc_Inspc.obj"	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\AnswerComm_ifc_Inspc.obj"	"$(INTDIR)\AnswerComm_ifc_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\AnswerComm_ifc_Inspc.obj"	"$(INTDIR)\browse\AnswerComm_ifc_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\AnswerComm_ifc_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\ClassContent_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\ClassContent_Inspc.obj"	"$(INTDIR)\ClassContent_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\ClassContent_Inspc.obj"	"$(INTDIR)\ClassContent_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\ClassContent_Inspc.obj"	"$(INTDIR)\browse\ClassContent_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\ClassContent_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\CmdConsumer_ifc_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\CmdConsumer_ifc_Inspc.obj"	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\CmdConsumer_ifc_Inspc.obj"	"$(INTDIR)\CmdConsumer_ifc_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\CmdConsumer_ifc_Inspc.obj"	"$(INTDIR)\browse\CmdConsumer_ifc_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\CmdConsumer_ifc_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\CmdExecuter_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\CmdExecuter_Inspc.obj"	"$(INTDIR)\CmdExecuter_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\CmdExecuter_Inspc.obj"	"$(INTDIR)\CmdExecuter_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\CmdExecuter_Inspc.obj"	"$(INTDIR)\browse\CmdExecuter_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\CmdExecuter_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\Comm_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\Comm_Inspc.obj"	"$(INTDIR)\Comm_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\Comm_Inspc.obj"	"$(INTDIR)\Comm_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\Comm_Inspc.obj"	"$(INTDIR)\browse\Comm_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\Comm_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\InspcDataExchangeAccess_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"	"$(INTDIR)\InspcDataExchangeAccess_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj"	"$(INTDIR)\browse\InspcDataExchangeAccess_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\InspcDataExchangeAccess_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\InspcDataInfo_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\InspcDataInfo_Inspc.obj"	"$(INTDIR)\InspcDataInfo_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\InspcDataInfo_Inspc.obj"	"$(INTDIR)\InspcDataInfo_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\InspcDataInfo_Inspc.obj"	"$(INTDIR)\browse\InspcDataInfo_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\InspcDataInfo_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\Inspector_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\Inspector_Inspc.obj"	"$(INTDIR)\Inspector_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\Inspector_Inspc.obj"	"$(INTDIR)\Inspector_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\Inspector_Inspc.obj"	"$(INTDIR)\browse\Inspector_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\Inspector_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\InspcJ2c\SearchElement_Inspc.c

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"


"$(INTDIR)\SearchElement_Inspc.obj"	"$(INTDIR)\SearchElement_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"


"$(INTDIR)\SearchElement_Inspc.obj"	"$(INTDIR)\SearchElement_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"


"$(INTDIR)\SearchElement_Inspc.obj"	"$(INTDIR)\browse\SearchElement_Inspc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 ReleaseCpp"


"$(INTDIR)\SearchElement_Inspc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

