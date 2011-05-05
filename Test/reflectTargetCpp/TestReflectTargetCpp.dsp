# Microsoft Developer Studio Project File - Name="TestReflectTargetCpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TestReflectTargetCpp - Win32 DebugCpp
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestReflectTargetCpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestReflectTargetCpp.mak" CFG="TestReflectTargetCpp - Win32 DebugCpp"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestReflectTargetCpp - Win32 DebugCpp" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TestReflectTargetCpp___Win32_DebugCpp"
# PROP BASE Intermediate_Dir "TestReflectTargetCpp___Win32_DebugCpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\Jc\TestReflectTargetCppLib"
# PROP Intermediate_Dir "T:\Jc\TestReflectTargetCppLib"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../FwConvCpp" /I "../../OSAL/inc" /I "../../os_Windows" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD CPP /nologo /Zp1 /MTd /W3 /Gm /GX /ZI /Od /I "src_c" /I "gensrc_c" /I "../../includeSpecials/FwConvC32" /I "../../includeSpecials/os_Windows" /I "../../include" /I "../../include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Target

# Name "TestReflectTargetCpp - Win32 DebugCpp"
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
# Begin Source File

SOURCE=..\..\source\InspcJ2c\SearchElement_Inspc.c
# End Source File
# End Group
# Begin Group "Test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\genRefl\Reflection_TestReflectTarget.c
# End Source File
# Begin Source File

SOURCE=.\src\TestReflectTarget.c
# End Source File
# Begin Source File

SOURCE=.\src\TestReflectTargetCpp.h
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\lib\windows_VC98\simpleAllocJcD.lib
# End Source File
# Begin Source File

SOURCE=..\..\lib\windows_VC98\baseJcppD.lib
# End Source File
# Begin Source File

SOURCE=..\..\lib\windows_VC98\OsalFwcppD.lib
# End Source File
# End Group
# End Target
# End Project
