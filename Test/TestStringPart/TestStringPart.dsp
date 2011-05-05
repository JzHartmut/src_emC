# Microsoft Developer Studio Project File - Name="TestStringPart" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TestStringPart - Win32 Debug_CppC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestStringPart.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestStringPart.mak" CFG="TestStringPart - Win32 Debug_CppC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestStringPart - Win32 Debug_C" (based on "Win32 (x86) Console Application")
!MESSAGE "TestStringPart - Win32 Debug_Cpp" (based on "Win32 (x86) Console Application")
!MESSAGE "TestStringPart - Win32 Debug_CppC" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestStringPart - Win32 Debug_C"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TestString___Win32_Debug_C"
# PROP BASE Intermediate_Dir "TestString___Win32_Debug_C"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\TestJc\TestStringPart\debug_C"
# PROP Intermediate_Dir "T:\TestJc\TestStringPart\debug_C"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../OSAL/inc_Win" /I "../OSAL/inc" /I "../OSAL/src" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../CRuntimeJavalike/includeSpecials/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include/OSAL" /I "../../CRuntimeJavalike/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "TestStringPart - Win32 Debug_Cpp"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TestStringPart___Win32_Debug_Cpp"
# PROP BASE Intermediate_Dir "TestStringPart___Win32_Debug_Cpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\TestJc\TestStringPart\debug_Cpp"
# PROP Intermediate_Dir "T:\TestJc\TestStringPart\debug_Cpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../CRuntimeJavalike/include/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../CRuntimeJavalike/includeSpecials/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include/OSAL" /I "../../CRuntimeJavalike/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "TestStringPart - Win32 Debug_CppC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TestStringPart___Win32_Debug_CppC"
# PROP BASE Intermediate_Dir "TestStringPart___Win32_Debug_CppC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\TestJc\TestStringPart\debug_CppC"
# PROP Intermediate_Dir "T:\TestJc\TestStringPart\debug_CppC"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "../../CRuntimeJavalike/include/FwConvC32" /I "../../CRuntimeJavalike/includeSpecials/os_Windows" /I "../../CRuntimeJavalike/include/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestStringPart - Win32 Debug_C"
# Name "TestStringPart - Win32 Debug_Cpp"
# Name "TestStringPart - Win32 Debug_CppC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Reflection_TestStringJc.c
# End Source File
# Begin Source File

SOURCE=src\TestStringPart.c

!IF  "$(CFG)" == "TestStringPart - Win32 Debug_C"

!ELSEIF  "$(CFG)" == "TestStringPart - Win32 Debug_Cpp"

!ELSEIF  "$(CFG)" == "TestStringPart - Win32 Debug_CppC"

# ADD CPP /I "src"

!ENDIF 

# End Source File
# End Group
# Begin Group "Fwc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_Exception.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Fwc\fw_Exception.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_ExceptionPrintStacktrace.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_Formatter.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Fwc\fw_Formatter.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_LogMessage.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Fwc\fw_LogMessage.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_MemC.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Fwc\fw_MemC.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_Object.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_SimpleC.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Fwc\fw_String.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_threadContext.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Fwc\fw_ThreadContext.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\fw_timeconversions.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\objectBaseC.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Fwc\Reflection_Fwc.c
# End Source File
# End Group
# Begin Group "Jc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\FileIoJc.c

!IF  "$(CFG)" == "TestStringPart - Win32 Debug_C"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TestStringPart - Win32 Debug_Cpp"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TestStringPart - Win32 Debug_CppC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Jc\FileIoJc.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\LocaleJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\MathJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\ObjectJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Jc\ObjectJc.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\OsWrapperJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Jc\OsWrapperJc.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\Reflection_AllJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\ReflectionBaseTypesJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Jc\ReflectionJc.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\StringBufferJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\Jc\StringJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\Jc\StringJc.h
# End Source File
# End Group
# Begin Group "FwConv"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\FwConv\allocOnlyAtStartup.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\FwConv\fw_PlatformConvSimpleStop.c
# End Source File
# End Group
# Begin Group "OSAL_Windows"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\os_Windows\os_error.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\os_Windows\os_file.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\os_Windows\os_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\os_Windows\os_mutex.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\os_Windows\os_sync.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\os_Windows\os_thread.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\os_Windows\os_time.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\os_Windows\os_types_def.h
# End Source File
# End Group
# Begin Group "OSAL_inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_AtomicAccess.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_endian.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_error.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_file.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\OSAL\src\os_internal_common.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_mem.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_serror.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_socket.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_sync.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_thread.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_time.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\OSAL\os_waitnotify.h
# End Source File
# End Group
# Begin Group "J1C"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\J1c\SpecialCharStringsJc.c
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\include\J1c\SpecialCharStringsJc.h
# End Source File
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\J1c\StringPartJc.c
# End Source File
# Begin Source File

SOURCE=..\J1c\StringPartJc.h
# End Source File
# End Group
# Begin Group "OSAL_src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CRuntimeJavalike\source\OSAL\Reflection_OSAL.c
# End Source File
# End Group
# End Group
# End Target
# End Project
