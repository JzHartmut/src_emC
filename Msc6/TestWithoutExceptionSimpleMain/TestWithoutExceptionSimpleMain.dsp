# Microsoft Developer Studio Project File - Name="TestWithoutExceptionSimpleMain" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TestWithoutExceptionSimpleMain - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestWithoutExceptionSimpleMain.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestWithoutExceptionSimpleMain.mak" CFG="TestWithoutExceptionSimpleMain - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestWithoutExceptionSimpleMain - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TestWithoutExceptionSimpleMain - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestWithoutExceptionSimpleMain - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "TestWithoutExceptionSimpleMain - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /ZI /Od /I "S:/Jc/CRuntimeJavalike/include" /I "S:/Jc/CRuntimeJavalike/include/OSAL" /I "S:/Jc/CRuntimeJavalike/sourceSpecials/ExcHandling_Printf.template" /I "S:/Jc/CRuntimeJavalike/includeSpecials/os_Windows_Msc6" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestWithoutExceptionSimpleMain - Win32 Release"
# Name "TestWithoutExceptionSimpleMain - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "CRJ"

# PROP Default_Filter ""
# Begin Group "Fwc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=D:\vishia\Jc\CRuntimeJavalike\include\Fwc\fw_ExcStacktrcNo.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_MemC.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\include\Fwc\fw_MemC.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_Object.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_SimpleC.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\include\Fwc\fw_SimpleC.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_String.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\include\Fwc\fw_String.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_threadContext.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\include\Fwc\fw_ThreadContext.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_timeconversions.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\include\Fwc\fw_timeconversions.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\include\Fwc\objectBaseC.h
# End Source File
# End Group
# Begin Group "Jc"

# PROP Default_Filter ""
# End Group
# Begin Group "OSAL"

# PROP Default_Filter ""
# End Group
# Begin Group "ApplstdefJc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\ExcHandling_Printf.template\applstdefJc.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\ExcHandling_Printf.template\BlockHeap_PlatformSpec.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\ExcHandling_Printf.template\fw_assert.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\ExcHandling_Printf.template\fw_ExcStacktrcNo.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\ExcHandling_Printf.template\fw_Platform_conventions.h
# End Source File
# End Group
# End Group
# Begin Group "Appl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\src_Test\SimpleIntr\test_Error.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
