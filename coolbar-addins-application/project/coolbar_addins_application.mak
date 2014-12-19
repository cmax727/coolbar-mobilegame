# Microsoft Developer Studio Generated NMAKE File, Based on coolbar_addins_application.dsp
!IF "$(CFG)" == ""
CFG=coolbar_addins_application - Win32 Debug
!MESSAGE No configuration specified. Defaulting to coolbar_addins_application - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "coolbar_addins_application - Win32 Release" && "$(CFG)" != "coolbar_addins_application - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "coolbar_addins_application.mak" CFG="coolbar_addins_application - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "coolbar_addins_application - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "coolbar_addins_application - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "coolbar_addins_application - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\coolbar_addins_application.dll"


CLEAN :
	-@erase "$(INTDIR)\CoolbarDemo.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\coolbar_addins_application.dll"
	-@erase "$(OUTDIR)\coolbar_addins_application.exp"
	-@erase "$(OUTDIR)\coolbar_addins_application.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOLBAR_ADDINS_APPLICATION_EXPORTS" /Fp"$(INTDIR)\coolbar_addins_application.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\coolbar_addins_application.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\coolbar_addins_application.pdb" /machine:I386 /def:"..\src\interface\coolbar-addins-application.def" /out:"$(OUTDIR)\coolbar_addins_application.dll" /implib:"$(OUTDIR)\coolbar_addins_application.lib" 
DEF_FILE= \
	"..\src\interface\coolbar-addins-application.def"
LINK32_OBJS= \
	"$(INTDIR)\CoolbarDemo.obj" \
	"..\..\..\..\..\release\coolbar模拟器发布\coolbar-emulator\coolbar-addins-application\src\interface\game_sdk_lib.lib"

"$(OUTDIR)\coolbar_addins_application.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "coolbar_addins_application - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\coolbar-win32-emulator\coolbar_addins_application.dll"


CLEAN :
	-@erase "$(INTDIR)\CoolbarDemo.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\coolbar_addins_application.exp"
	-@erase "$(OUTDIR)\coolbar_addins_application.lib"
	-@erase "$(OUTDIR)\coolbar_addins_application.map"
	-@erase "$(OUTDIR)\coolbar_addins_application.pdb"
	-@erase "..\..\coolbar-win32-emulator\coolbar_addins_application.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /w /W0 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOLBAR_ADDINS_APPLICATION_EXPORTS" /Fp"$(INTDIR)\coolbar_addins_application.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /Zm1000 @"coolbar_addins_application.ini" /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\coolbar_addins_application.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\coolbar_addins_application.pdb" /map:"$(INTDIR)\coolbar_addins_application.map" /debug /machine:I386 /def:"..\src\interface\coolbar-addins-application.def" /out:"..\..\coolbar-win32-emulator\coolbar_addins_application.dll" /implib:"$(OUTDIR)\coolbar_addins_application.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\CoolbarDemo.obj" \
	"..\..\..\..\..\release\coolbar模拟器发布\coolbar-emulator\coolbar-addins-application\src\interface\game_sdk_lib.lib"

"..\..\coolbar-win32-emulator\coolbar_addins_application.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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
!IF EXISTS("coolbar_addins_application.dep")
!INCLUDE "coolbar_addins_application.dep"
!ELSE 
!MESSAGE Warning: cannot find "coolbar_addins_application.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "coolbar_addins_application - Win32 Release" || "$(CFG)" == "coolbar_addins_application - Win32 Debug"
SOURCE=..\src\CoolbarDemo\src\CoolbarDemo.c

"$(INTDIR)\CoolbarDemo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

