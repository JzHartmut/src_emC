# Microsoft Developer Studio Project File - Name="TcpSocket" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=TcpSocket - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TcpSocket_Client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TcpSocket_Client.mak" CFG="TcpSocket - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TcpSocket - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "TcpSocket - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TcpSocket - Win32 Release"

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

!ELSEIF  "$(CFG)" == "TcpSocket - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\TcpSocket_Client_Msc6"
# PROP Intermediate_Dir "T:\TcpSocket_Client_Msc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../incComplSpecific/cc_Msc6" /I "../../incApplSpecific/FwConvC32" /I "../.." /I "../../source" /I "../../source/OSAL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TcpSocket - Win32 Release"
# Name "TcpSocket - Win32 Debug"
# Begin Group "Source"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "CRJ"

# PROP Default_Filter ""
# Begin Group "Fwc"

# PROP Default_Filter ""
# End Group
# Begin Group "Jc"

# PROP Default_Filter ""
# End Group
# Begin Group "OSAL_inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\OSAL\os_AtomicAccess.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_common.c
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_endian.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_error.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_file.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_mem.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_sharedmem.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_socket.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_sync.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_thread.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_time.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_types_def_common.h
# End Source File
# Begin Source File

SOURCE=..\..\source\OSAL\os_waitnotify.h
# End Source File
# End Group
# Begin Group "OSAL_Win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sourceSpecials\os_Windows_Msc6\os_atomic.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_endian.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_error.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_file.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_mutex.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_sharedmem.c

!IF  "$(CFG)" == "TcpSocket - Win32 Release"

!ELSEIF  "$(CFG)" == "TcpSocket - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_socket.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_sync.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_thread.c
# End Source File
# Begin Source File

SOURCE=..\..\sourceSpecials\osal_Windows32\os_time.c
# End Source File
# End Group
# Begin Group "ApplSpec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\sourceSpecials\FwConv_c\fw_PlatformConvSimpleStop.c
# End Source File
# End Group
# End Group
# Begin Group "TcpSocket"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TcpSocket.c
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
