# Microsoft Developer Studio Project File - Name="CRuntimeJavalike_baseJclib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CRuntimeJavalike_baseJclib - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "baseJc.mak".
!MESSAGE 
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
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\baseJc.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\baseJc.lib"

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "T:\CRuntimeJavalike\lib\baseJcD"
# PROP Intermediate_Dir "T:\CRuntimeJavalike\lib\baseJcD"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MTd /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\baseJcD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\baseJcD.lib"

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_baseJclib - Win32 DebugCpp"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "CRuntimeJavalike_baseJclib___Win32_DebugCpp"
# PROP BASE Intermediate_Dir "CRuntimeJavalike_baseJclib___Win32_DebugCpp"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".."
# PROP Intermediate_Dir "T:\CRuntimeJavalike_baseJclib\DebugCpp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MT /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /TP /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../baseJcppD.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\baseJcppD.lib"

!ENDIF 

# Begin Target

# Name "CRuntimeJavalike_baseJclib - Win32 Release"
# Name "CRuntimeJavalike_baseJclib - Win32 Debug"
# Name "CRuntimeJavalike_baseJclib - Win32 DebugCpp"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Jc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\include\Jc\AbstractListJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\ArraysJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ArraysJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ComparatorJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\ConcurrentLinkedQueueJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ConcurrentLinkedQueueJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\DateJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\DateJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\FileIoJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\FileIoJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\FileSystemJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\FileSystemJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\FormatterJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\FormatterJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\LinkedListJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\LinkedListJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ListIteratorJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ListJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ListMapEntryJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\LocaleJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\LocaleJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\MathJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\MathJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\ObjectJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ObjectJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\OsWrapperJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\OsWrapperJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\PrintStreamJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\PrintStreamJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\Reflection_AllJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\ReflectionBasetypesJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\ReflectionJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ReflectionJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\ReflectionLoadExtJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\ReflMemAccessJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ReflMemAccessJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\StringBufferJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\StringBufferJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\StringJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\StringJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\StringJc_intern.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\StringValueConvJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\SystemJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\SystemJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\SystemOutJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\ThreadJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\ThreadJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Jc\TimeZoneJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Jc\TimeZoneJc.h
# End Source File
# End Group
# Begin Group "Ipc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\Ipc\InterProcessComm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Ipc\InterProcessComm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Ipc2c\InterProcessCommFactorySocket_Ipc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Ipc\InterProcessCommSocket.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Ipc\InterProcessCommSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Ipc\Reflection_Ipc.c
# End Source File
# End Group
# Begin Group "J1c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\J1c\ByteDataAccessJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\J1c\ByteDataAccessJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\J1c\LeapSecondsJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\J1c\LeapSecondsJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\J1c\RawDataAccessJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\J1c\RawDataAccessJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\J1c\SpecialCharStringsJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\J1c\SpecialCharStringsJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\J1c\StringFormatterJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\J1c\StringFormatterJc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\J1c\StringPartJc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\include\J1c\StringPartJc.h
# End Source File
# End Group
# Begin Group "Specials"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\FwConv\UmlContainer_Dummy.c
# End Source File
# End Group
# Begin Group "Fwc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_LogMessage.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_LogMsgStream.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\fw_Object.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Fwc\Reflection_Fwc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\OSAL\Reflection_OSAL.c
# End Source File
# End Group
# Begin Group "Inspc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\InspcJ2c\AnswerComm_ifc_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\InspcJ2c\ClassContent_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\InspcJ2c\CmdConsumer_ifc_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\InspcJ2c\CmdExecuter_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\InspcJ2c\Comm_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\InspcJ2c\InspcDataExchangeAccess_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\InspcJ2c\Inspector_Inspc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\source\InspcJ2c\SearchElement_Inspc.c
# End Source File
# End Group
# End Group
# Begin Group "Headerfiles"

# PROP Default_Filter ""
# Begin Group "OSAL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_AtomicAccess.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_endian.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_error.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_file.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_mem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_socket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_sync.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_thread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_time.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\OSAL\os_waitnotify.h
# End Source File
# End Group
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
