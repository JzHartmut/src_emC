# Microsoft Developer Studio Generated NMAKE File, Based on simpleAlloc.dsp
!IF "$(CFG)" == ""
CFG=CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor
!MESSAGE No configuration specified. Defaulting to CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor.
!ENDIF 

!IF "$(CFG)" != "CRuntimeJavalike_simpleAlloclib - Win32 Release" && "$(CFG)" != "CRuntimeJavalike_simpleAlloclib - Win32 Debug" && "$(CFG)" != "CRuntimeJavalike_simpleAlloclib - Win32 DebugCpp" && "$(CFG)" != "CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "simpleAlloc.mak" CFG="CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CRuntimeJavalike_simpleAlloclib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_simpleAlloclib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_simpleAlloclib - Win32 DebugCpp" (based on "Win32 (x86) Static Library")
!MESSAGE "CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\simpleAllocJc.lib"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\simpleAllocJc.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MTd /W3 /GX /O2 /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\simpleAlloc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\simpleAlloc.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\simpleAllocJc.lib" 
LIB32_OBJS= \
	"$(INTDIR)\allocOnlyAtStartup.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj"

"$(OUTDIR)\simpleAllocJc.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 Debug"

OUTDIR=T:\CRuntimeJavalike\lib\simpleAllocJcD
INTDIR=T:\CRuntimeJavalike\lib\simpleAllocJcD

ALL : "..\simpleAllocJcD.lib" "..\simpleAllocJcD.bsc"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\allocOnlyAtStartup.sbr"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\simpleAllocJcD.bsc"
	-@erase "..\simpleAllocJcD.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Zp1 /MTd /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\simpleAlloc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"..\simpleAllocJcD.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\allocOnlyAtStartup.sbr" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr"

"..\simpleAllocJcD.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\simpleAllocJcD.lib" 
LIB32_OBJS= \
	"$(INTDIR)\allocOnlyAtStartup.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj"

"..\simpleAllocJcD.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 DebugCpp"

OUTDIR=.\..
INTDIR=T:\CRuntimeJavalike_simpleAlloclib\DebugCpp
# Begin Custom Macros
OutDir=.\..
# End Custom Macros

ALL : "$(OUTDIR)\simpleAllocJcppD.lib" "$(OUTDIR)\simpleAllocJcppD.bsc"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\allocOnlyAtStartup.sbr"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\simpleAllocJcppD.bsc"
	-@erase "$(OUTDIR)\simpleAllocJcppD.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W4 /Gm /GX /ZI /Od /I "includeEmptyRef" /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\simpleAlloc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /TC /TP /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\simpleAllocJcppD.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\allocOnlyAtStartup.sbr" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr"

"$(OUTDIR)\simpleAllocJcppD.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\simpleAllocJcppD.lib" 
LIB32_OBJS= \
	"$(INTDIR)\allocOnlyAtStartup.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj"

"$(OUTDIR)\simpleAllocJcppD.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor"

OUTDIR=.\CRuntimeJavalike_simpleAlloclib___Win32_PreProcessor
INTDIR=.\CRuntimeJavalike_simpleAlloclib___Win32_PreProcessor

ALL : "..\baseJcD.lib" "..\baseJcD.bsc"


CLEAN :
	-@erase "$(INTDIR)\allocOnlyAtStartup.obj"
	-@erase "$(INTDIR)\allocOnlyAtStartup.sbr"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.obj"
	-@erase "$(INTDIR)\fw_PlatformConvSimpleStop.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\baseJcD.bsc"
	-@erase "..\baseJcD.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../../../include" /I "../../../include/OSAL" /I "../../../includeSpecials/os_Windows" /I "../../../includeSpecials/FwConvC32" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\simpleAlloc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /P /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"..\baseJcD.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\allocOnlyAtStartup.sbr" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr"

"..\baseJcD.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\baseJcD.lib" 
LIB32_OBJS= \
	"$(INTDIR)\allocOnlyAtStartup.obj" \
	"$(INTDIR)\fw_PlatformConvSimpleStop.obj"

"..\baseJcD.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("simpleAlloc.dep")
!INCLUDE "simpleAlloc.dep"
!ELSE 
!MESSAGE Warning: cannot find "simpleAlloc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 Release" || "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 Debug" || "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 DebugCpp" || "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor"
SOURCE=..\..\..\source\FwConv\allocOnlyAtStartup.c

!IF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 Release"


"$(INTDIR)\allocOnlyAtStartup.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 Debug"


"$(INTDIR)\allocOnlyAtStartup.obj"	"$(INTDIR)\allocOnlyAtStartup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 DebugCpp"


"$(INTDIR)\allocOnlyAtStartup.obj"	"$(INTDIR)\allocOnlyAtStartup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor"


"$(INTDIR)\allocOnlyAtStartup.obj"	"$(INTDIR)\allocOnlyAtStartup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\source\FwConv\fw_PlatformConvSimpleStop.c

!IF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 Release"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 Debug"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 DebugCpp"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CRuntimeJavalike_simpleAlloclib - Win32 PreProcessor"


"$(INTDIR)\fw_PlatformConvSimpleStop.obj"	"$(INTDIR)\fw_PlatformConvSimpleStop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

