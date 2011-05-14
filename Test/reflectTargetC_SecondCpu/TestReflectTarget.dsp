# Microsoft Developer Studio Project File - Name="TestReflectTarget" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TestReflectTarget - Win32 DebugCpp
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestReflectTarget.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestReflectTarget.mak" CFG="TestReflectTarget - Win32 DebugCpp"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestReflectTarget - Win32 DebugCpp" (based on "Win32 (x86) Console Application")
!MESSAGE "TestReflectTarget - Win32 DebugC" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestReflectTarget - Win32 DebugCpp"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TestReflectTarget___Win32_DebugCpp"
# PROP BASE Intermediate_Dir "TestReflectTarget___Win32_DebugCpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\Jc\TestReflectTarget"
# PROP Intermediate_Dir "T:\Jc\TestReflectTarget"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../FwConvCpp" /I "../../OSAL/inc" /I "../../os_Windows" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "src_c" /I "gensrc_c" /I "../../includeSpecials/FwConvC32" /I "../../includeSpecials/os_Windows" /I "../../include" /I "../../include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "TestReflectTarget - Win32 DebugC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TestReflectTarget___Win32_DebugC"
# PROP BASE Intermediate_Dir "TestReflectTarget___Win32_DebugC"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\Jc\TestReflectTarget_DebugC"
# PROP Intermediate_Dir "T:\Jc\TestReflectTarget_DebugC"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../FwConvCpp" /I "../../OSAL/inc" /I "../../os_Windows" /I "../.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD CPP /nologo /Zp1 /MTd /W4 /ZI /Od /I "src_c" /I "gensrc_c" /I "../../includeSpecials/FwConvC32" /I "../../includeSpecials/os_Windows" /I "../../include" /I "../../include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FAcs /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestReflectTarget - Win32 DebugCpp"
# Name "TestReflectTarget - Win32 DebugC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "InspcJ2c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\InspcJ2c\AnswerComm_ifc_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\InspcJ2c\AnswerComm_ifc_Inspc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\InspcJ2c\ClassContent_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\InspcJ2c\ClassContent_Inspc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\InspcJ2c\CmdConsumer_ifc_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\InspcJ2c\CmdConsumer_ifc_Inspc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\InspcJ2c\CmdExecuter_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\InspcJ2c\CmdExecuter_Inspc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\InspcJ2c\Comm_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\InspcJ2c\Comm_Inspc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\InspcJ2c\InspcDataExchangeAccess_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\InspcJ2c\InspcDataExchangeAccess_Inspc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\InspcJ2c\Inspector_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\InspcJ2c\Inspector_Inspc.h
# End Source File
# End Group
# Begin Group "Test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\genRefl\Reflection_Dsp.c

!IF  "$(CFG)" == "TestReflectTarget - Win32 DebugCpp"

!ELSEIF  "$(CFG)" == "TestReflectTarget - Win32 DebugC"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\genRefl\Reflection_TestReflectTarget.c
# End Source File
# Begin Source File

SOURCE=.\genRefl\ReflectionOffset_Dsp.c
# End Source File
# Begin Source File

SOURCE=..\..\source\InspcJ2c\SearchElement_Inspc.c
# End Source File
# Begin Source File

SOURCE=.\src\SecondCpuData.h
# End Source File
# Begin Source File

SOURCE=.\src\TestReflectTarget.c
# End Source File
# Begin Source File

SOURCE=.\src\TestReflectTarget.h
# End Source File
# Begin Source File

SOURCE=.\src\TestSecondCpu.c
# End Source File
# End Group
# Begin Group "InspcExample"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\InspcJ2c\WorkingThread_Inspc.c
# End Source File
# End Group
# Begin Group "Jc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\Jc\ArraysJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\FileIoJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\FileSystemJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\LocaleJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\MathJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\ObjectJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\OsWrapperJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\OsWrapperJc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\PrintStreamJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\Reflection_AllJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\ReflectionBasetypesJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\ReflectionJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\ReflectionLoadExtJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\ReflMemAccessJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\StringBufferJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\StringJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\StringJc_intern.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\StringValueConvJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\SystemJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\SystemOutJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\ThreadJc.c
# End Source File
# End Group
# Begin Group "Fwc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\Fwc\fw_Exception.c
# End Source File
# Begin Source File

SOURCE=..\..\include\Fwc\fw_Exception.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_ExceptionPrintStacktrace.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_MemC.c
# End Source File
# Begin Source File

SOURCE=..\..\include\Fwc\fw_MemC.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_Object.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_SimpleC.c
# End Source File
# Begin Source File

SOURCE=..\..\include\Fwc\fw_SimpleC.h
# End Source File
# Begin Source File

SOURCE=..\..\include\Fwc\fw_String.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_threadContext.c
# End Source File
# Begin Source File

SOURCE=..\..\include\Fwc\fw_ThreadContext.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_timeconversions.c
# End Source File
# Begin Source File

SOURCE=..\..\include\Fwc\fw_timeconversions.h
# End Source File
# Begin Source File

SOURCE=..\..\include\Fwc\objectBaseC.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\Reflection_Fwc.c
# End Source File
# End Group
# Begin Group "OSAL"

# PROP Default_Filter ""
# Begin Group "os_windows"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\os_Windows\os_atomic.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_endian.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_error.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_file.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_mutex.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_socket.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_sync.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_thread.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_Windows\os_time.c
# End Source File
# End Group
# Begin Group "inc_common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\OSAL\os_AtomicAccess.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_endian.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_error.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_file.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_mem.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_socket.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_sync.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_thread.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_time.h
# End Source File
# Begin Source File

SOURCE=..\..\include\OSAL\os_types_def_common.h
# End Source File
# End Group
# Begin Group "inc_special"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\..\source\OSAL\Reflection_OSAL.c
# End Source File
# End Group
# Begin Group "J1c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\J1c\ByteDataAccessJc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\J1c\ByteDataAccessJc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\J1c\SpecialCharStringsJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\J1c\StringPartJc.c
# End Source File
# Begin Source File

SOURCE=..\..\include\J1c\StringPartJc.h
# End Source File
# End Group
# Begin Group "Ipc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\Ipc\InterProcessComm.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Ipc\InterProcessCommSocket.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Ipc\Reflection_Ipc.c
# End Source File
# End Group
# Begin Group "Ipc2c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\Ipc2c\InterProcessCommFactorySocket_Ipc.c
# End Source File
# End Group
# Begin Group "FwConv"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\FwConv\allocOnlyAtStartup.c
# End Source File
# Begin Source File

SOURCE=..\..\source\FwConv\UmlContainer_Dummy.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\lib\windows_VC98\baseJcD.lib

!IF  "$(CFG)" == "TestReflectTarget - Win32 DebugCpp"

!ELSEIF  "$(CFG)" == "TestReflectTarget - Win32 DebugC"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\lib\windows_VC98\simpleAllocJcD.lib
# End Source File
# Begin Source File

SOURCE=..\..\lib\windows_VC98\OSALJcD.lib
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\includeSpecials\os_Windows\os_types_def.h
# End Source File
# End Target
# End Project
