# Microsoft Developer Studio Project File - Name="hidemdi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=hidemdi - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "Hidemdi.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "Hidemdi.mak" CFG="hidemdi - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "hidemdi - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "hidemdi - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "hidemdi - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "hidemdi - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "hidemdi - Win32 Release"
# Name "hidemdi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CDropTargetDoctmpl.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiApp.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiDoctmplDocstrAlone.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiMainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiRootDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiRootDoctmpl.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiRootFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiRootView.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiSubDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CHidemdiSubDoctmpl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CDropTargetDoctmpl.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiApp.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiDoctmplDocstrAlone.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiMainFrm.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiRootDoc.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiRootDoctmpl.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiRootFrame.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiRootView.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiSubDoc.h
# End Source File
# Begin Source File

SOURCE=.\CHidemdiSubDoctmpl.h
# End Source File
# Begin Source File

SOURCE=.\hidemdi.h
# End Source File
# End Group
# End Target
# End Project
