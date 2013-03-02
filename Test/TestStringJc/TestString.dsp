# Microsoft Developer Studio Project File - Name="TestString" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TestString - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestString.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestString - Win32 Release"

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

!ELSEIF  "$(CFG)" == "TestString - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../includeSpecials/os_Windows_Msc6" /I "../../includeSpecials/FwConvC32" /I "../../include/OSAL" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /incremental:no /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TestString - Win32 Release"
# Name "TestString - Win32 Debug"
# Begin Group "Source Lib Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Fwc-OSAL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\Fwc\fw_Exception.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_ExceptionPrintStacktrace.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_formatter.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_MemC.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_Readline.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_SimpleC.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_String.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_threadContext.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_timeconversions.c
# End Source File
# End Group
# Begin Group "Jc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\Jc\DateJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\LocaleJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\ObjectJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\Reflection_AllJc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Jc\ReflectionBasetypesJc.c
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
# End Group
# Begin Group "BlockHeap"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\BlockHeap\BlockHeapJc_Alloc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BlockHeap\BlockHeapJc_GarbageCol.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BlockHeap\BlockHeapJc_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\source\BlockHeap\BlockHeapJc_References.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BlockHeap\Reflection_BlockHeap.c
# End Source File
# Begin Source File

SOURCE=..\..\source\BlockHeap\Reflection_BlockHeap.h
# End Source File
# End Group
# Begin Group "Fwc_Jc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\Fwc\fw_LogMessage.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_LogMsgStream.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\fw_Object.c
# End Source File
# Begin Source File

SOURCE=..\..\source\Fwc\Reflection_Fwc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\Reflection_OSAL.c
# End Source File
# End Group
# Begin Group "Win-OSAL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_atomic.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_endian.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_error.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_file.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_mutex.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_socket.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_sync.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_thread.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_time.c
# End Source File
# End Group
# End Group
# Begin Group "Source Test"

# PROP Default_Filter ""
# Begin Group "Test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\TestString.c
# End Source File
# Begin Source File

SOURCE=.\src\TestStringCpp.cpp
# End Source File
# End Group
# Begin Group "Platform"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\FwConv\fw_PlatformConvSimpleStop.c
# End Source File
# End Group
# End Group
# End Target
# End Project
