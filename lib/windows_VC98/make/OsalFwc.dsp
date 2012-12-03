# Microsoft Developer Studio Project File - Name="CRuntimeJavalike_OSALlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CRuntimeJavalike_OSALlib - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OsalFwc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OsalFwc.mak" CFG="CRuntimeJavalike_OSALlib - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CRuntimeJavalike_OSALlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_OSALlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_OSALlib - Win32 DebugCpp" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CRuntimeJavalike_OSALlib - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows_Msc6" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FAcs /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\OsalFwc.lib"

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_OSALlib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\CRuntimeJavalike\lib\OSALJcD"
# PROP Intermediate_Dir "T:\CRuntimeJavalike\lib\OSALJcD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MTd /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows_Msc6" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FAcs /FR"T:\CRuntimeJavalike\lib\OsalFwcD/" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\OsalFwcD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\OsalFwcD.lib"

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_OSALlib - Win32 DebugCpp"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CRuntimeJavalike_OSALlib___Win32_DebugCpp"
# PROP BASE Intermediate_Dir "CRuntimeJavalike_OSALlib___Win32_DebugCpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".."
# PROP Intermediate_Dir "T:\CRuntimeJavalike_OSALlib\DebugCpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MTd /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows_Msc6" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /Fd"..\OsalFwcppD.pdb" /FD /GZ /TP /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../OSALD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\OsalFwcppD.lib"

!ENDIF 

# Begin Target

# Name "CRuntimeJavalike_OSALlib - Win32 Release"
# Name "CRuntimeJavalike_OSALlib - Win32 Debug"
# Name "CRuntimeJavalike_OSALlib - Win32 DebugCpp"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "OSAL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_atomic.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_endian.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_error.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_file.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_internal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_mem.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_mutex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_socket.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_sync.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_thread.c
# End Source File
# Begin Source File

SOURCE=..\..\..\sourceSpecials\os_Windows_Msc6\os_time.c
# End Source File
# End Group
# Begin Group "Fwc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_Exception.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_ExceptionPrintStacktrace.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_formatter.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_MemC.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_Readline.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_SimpleC.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_String.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_threadContext.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_timeconversions.c
# End Source File
# End Group
# Begin Group "OS_common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\OSAL\os_common.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OSAL\Reflection_OSAL.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
