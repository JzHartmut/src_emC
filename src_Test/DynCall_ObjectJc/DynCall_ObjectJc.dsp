# Microsoft Developer Studio Project File - Name="DynCall_ObjectJc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=DynCall_ObjectJc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DynCall_ObjectJc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DynCall_ObjectJc.mak" CFG="DynCall_ObjectJc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DynCall_ObjectJc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "DynCall_ObjectJc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DynCall_ObjectJc - Win32 Release"

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

!ELSEIF  "$(CFG)" == "DynCall_ObjectJc - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /ZI /Od /I "S:/Jc/CRuntimeJavalike/incApplSpecific/FwConvSimpleAlloc" /I "S:/Jc/CRuntimeJavalike/source/OSAL" /I "S:/Jc/CRuntimeJavalike/source" /I "S:/Jc/CRuntimeJavalike/incComplSpecific/cc_Msc6" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /TP /c
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

# Name "DynCall_ObjectJc - Win32 Release"
# Name "DynCall_ObjectJc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "CRJ"

# PROP Default_Filter ""
# Begin Group "Fwc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_Formatter.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_Formatter.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_MemC.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_MemC.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_Object.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_ReflectionBaseTypes.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_SimpleC.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_SimpleC.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_String.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_String.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\include\Fwc\fw_ThreadContext.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_timeconversions.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_timeconversions.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\objectBaseC.h
# End Source File
# End Group
# Begin Group "cc_Msc6"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\cc_Msc6\compl_adaption.h
# End Source File
# End Group
# Begin Group "OSAL_Win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\os_Windows_Msc6\os_atomic.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\osal_Windows32\os_error.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\osal_Windows32\os_file.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\osal_Windows32\os_mem.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\osal_Windows32\os_mutex.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\osal_Windows32\os_sync.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\osal_Windows32\os_thread.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\osal_Windows32\os_time.c
# End Source File
# End Group
# Begin Group "FwConv_Appl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\FwConv_c\allocOnlyAtStartup.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\FwConv_c\free_ThreadHeapAndBlockHeap.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_Exception.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_Exception.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_ExceptionPrintStacktrace.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\FwConv_c\fw_PlatformConvSimpleStop.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_threadContext.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Fwc\fw_ThreadContext.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\sourceSpecials\FwConv_c\stopAssert_Fwc_while0.c
# End Source File
# End Group
# Begin Group "OSAL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\OSAL\os_AtomicAccess.h
# End Source File
# End Group
# Begin Group "J1c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\InspcJ2c\CmdExecuter_Inspc.c

!IF  "$(CFG)" == "DynCall_ObjectJc - Win32 Release"

!ELSEIF  "$(CFG)" == "DynCall_ObjectJc - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\InspcJ2c\CmdExecuter_Inspc.h

!IF  "$(CFG)" == "DynCall_ObjectJc - Win32 Release"

!ELSEIF  "$(CFG)" == "DynCall_ObjectJc - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\J1c\StringPartJc.c

!IF  "$(CFG)" == "DynCall_ObjectJc - Win32 Release"

!ELSEIF  "$(CFG)" == "DynCall_ObjectJc - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\J1c\StringPartJc.h
# End Source File
# End Group
# Begin Group "Jc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Jc\ObjectJc.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Jc\ObjectJc.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Jc\StringBufferJc.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Jc\StringBufferJc.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Jc\StringJc.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\source\Jc\StringJc.h
# End Source File
# End Group
# End Group
# Begin Group "Appl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\src_Test\DynCall_ObjectJc\DynCall_ObjectJc.c
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\src_Test\DynCall_ObjectJc\DynCall_ObjectJc.crefl
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\src_Test\DynCall_ObjectJc\DynCall_ObjectJc.h
# End Source File
# Begin Source File

SOURCE=S:\Jc\CRuntimeJavalike\src_Test\DynCall_ObjectJc\Ifc_ExampleJc.h
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
