# Microsoft Developer Studio Project File - Name="CRuntimeJavalike_simpleC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CRuntimeJavalike_simpleC - Win32 PreProcessor
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "simpleC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "simpleC.mak" CFG="CRuntimeJavalike_simpleC - Win32 PreProcessor"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CRuntimeJavalike_simpleC - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_simpleC - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_simpleC - Win32 DebugCpp" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_simpleC - Win32 PreProcessor" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CRuntimeJavalike_simpleC - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\simpleC.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\simpleC.lib"

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleC - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\CRuntimeJavalike\lib\simpleCD"
# PROP Intermediate_Dir "T:\CRuntimeJavalike\lib\simpleCD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MTd /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\simpleCD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\simpleCD.lib"

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleC - Win32 DebugCpp"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CRuntimeJavalike_simpleC___Win32_DebugCpp"
# PROP BASE Intermediate_Dir "CRuntimeJavalike_simpleC___Win32_DebugCpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".."
# PROP Intermediate_Dir "T:\CRuntimeJavalike_simpleC\DebugCpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MT /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /TP /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../simpleCppD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\simpleCppD.lib"

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleC - Win32 PreProcessor"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CRuntimeJavalike_simpleC___Win32_PreProcessor"
# PROP BASE Intermediate_Dir "CRuntimeJavalike_simpleC___Win32_PreProcessor"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "CRuntimeJavalike_simpleC___Win32_PreProcessor"
# PROP Intermediate_Dir "CRuntimeJavalike_simpleC___Win32_PreProcessor"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /P /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"..\simpleCD.bsc"
# ADD BSC32 /nologo /o"..\simpleCD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\simpleCD.lib"
# ADD LIB32 /nologo /out:"..\simpleCD.lib"

!ENDIF 

# Begin Target

# Name "CRuntimeJavalike_simpleC - Win32 Release"
# Name "CRuntimeJavalike_simpleC - Win32 Debug"
# Name "CRuntimeJavalike_simpleC - Win32 DebugCpp"
# Name "CRuntimeJavalike_simpleC - Win32 PreProcessor"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Fwc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_Exception.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_Exception.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_ExceptionPrintStacktrace.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_formatter.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_Formatter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_LogMessage.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_LogMessage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_LogMsgStream.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_MemC.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_MemC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_Object.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_SimpleC.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_SimpleC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_String.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_String.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_threadContext.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_ThreadContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_timeconversions.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_timeconversions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\fw_Va_list.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Fwc\objectBaseC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\Reflection_Fwc.c
# End Source File
# End Group
# End Group
# Begin Group "Headerfiles"

# PROP Default_Filter ""
# Begin Group "Platform"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\includeSpecials\FwConvC32\fw_Platform_conventions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\includeSpecials\os_Windows\os_types_def.h
# End Source File
# End Group
# End Group
# End Target
# End Project
