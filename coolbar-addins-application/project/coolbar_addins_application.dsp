# Microsoft Developer Studio Project File - Name="coolbar_addins_application" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=coolbar_addins_application - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "coolbar_addins_application.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "coolbar_addins_application - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOLBAR_ADDINS_APPLICATION_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOLBAR_ADDINS_APPLICATION_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "coolbar_addins_application - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOLBAR_ADDINS_APPLICATION_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "COOLBAR_ADDINS_APPLICATION_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR /YX /FD /GZ /Zm1000 @"coolbar_addins_application.ini" /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /dll /incremental:no /map /debug /machine:I386 /def:"..\src\interface\coolbar-addins-application.def" /out:"..\..\coolbar-win32-emulator\coolbar_addins_application.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "coolbar_addins_application - Win32 Release"
# Name "coolbar_addins_application - Win32 Debug"
# Begin Group "coolbar-games-old-sdk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\interface\game_sdk_old.c
# End Source File
# End Group
# Begin Group "demo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\demo\src\CbDemoRes_Resource_Data.c
# End Source File
# Begin Source File

SOURCE=..\src\demo\src\CoolbarCtrlDemo.c
# End Source File
# End Group
# Begin Group "RussBlock"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_Help.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_HighScore.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_Map.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_PropShop.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_Resource.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_Resource_Data.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\russblock_screen_ingame.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_Screen_Loading.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_Screen_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_ScrollTextBox.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\russblock_titlemenu.c
# End Source File
# Begin Source File

SOURCE=..\src\RussBlock\src\RussBlock_UI.c
# End Source File
# End Group
# Begin Group "HitMole"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_About.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_Help.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_HighScore.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_Pay.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_Resource_Data.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_Screen_ingame.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_Screen_Loading.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_Screen_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_SelectLevel.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMole_TitleMenu.c
# End Source File
# Begin Source File

SOURCE="..\src\HitMole\src\HitMole_User-defined.c"
# End Source File
# Begin Source File

SOURCE=..\src\HitMole\src\HitMolePlay.c
# End Source File
# End Group
# Begin Group "MemoryBox"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_About.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_Exersice.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_Help.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_HighScore.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_Pay.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_Resource_Data.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_Screen_ingame.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_Screen_Loading.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_Screen_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBox_TitleMenu.c
# End Source File
# Begin Source File

SOURCE=..\src\MemoryBox\src\MemoryBoxPlay.c
# End Source File
# End Group
# Begin Group "ONFF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_About.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_Help.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_map.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_Pay.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_Resource_Data.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_Screen_ingame.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_Screen_Loading.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_Screen_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_Set.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\ONFF\src\ONFF_TitleMenu.c
# End Source File
# End Group
# Begin Group "CatLoveDog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_Help.c
# End Source File
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_InGame.c
# End Source File
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_Pay.c
# End Source File
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_Resource_Data.c
# End Source File
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_Screen_ingame.c
# End Source File
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_Screen_Loading.c
# End Source File
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_Screen_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_Title.c
# End Source File
# Begin Source File

SOURCE=..\src\CatLoveDog\src\CatLoveDog_TitleMenu.c
# End Source File
# End Group
# Begin Group "SameGame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_ChangeChip.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_CompleteMenu.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_HighScore.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_Logo.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_Playing.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_PlayMenu.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_Resource_Data.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_Screen_Gaming.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_Screen_Loading.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_Screen_Main.c
# End Source File
# Begin Source File

SOURCE=..\src\SameGame\src\SameGame_TitleMenu.c
# End Source File
# End Group
# Begin Source File

SOURCE="..\src\interface\coolbar-addins-application.def"

!IF  "$(CFG)" == "coolbar_addins_application - Win32 Release"

!ELSEIF  "$(CFG)" == "coolbar_addins_application - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
