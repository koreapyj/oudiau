# Microsoft Developer Studio Project File - Name="Str" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Str - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "Str.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "Str.mak" CFG="Str - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "Str - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "Str - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Str - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I ".." /I "../../.." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Str - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".." /I "../../.." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Str - Win32 Release"
# Name "Str - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CConnectedStringCompress.cpp
# End Source File
# Begin Source File

SOURCE=.\CdConnectedString2.cpp
# End Source File
# Begin Source File

SOURCE=.\CdFilenameStr.cpp
# End Source File
# Begin Source File

SOURCE=.\CStrCharSizeMb.cpp
# End Source File
# Begin Source File

SOURCE=.\strLf.cpp
# End Source File
# Begin Source File

SOURCE=.\strprintf.cpp
# End Source File
# Begin Source File

SOURCE=.\strToWstr.cpp
# End Source File
# Begin Source File

SOURCE=.\vectorToFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CConnectedStringCompress.h
# End Source File
# Begin Source File

SOURCE=.\CdConnectedString.h
# End Source File
# Begin Source File

SOURCE=.\CdConnectedString2.h
# End Source File
# Begin Source File

SOURCE=.\CdFilenameStr.h
# End Source File
# Begin Source File

SOURCE=.\CStrCharSizeMb.h
# End Source File
# Begin Source File

SOURCE=.\stringSplit.h
# End Source File
# Begin Source File

SOURCE=.\strLf.h
# End Source File
# Begin Source File

SOURCE=.\strprintf.h
# End Source File
# Begin Source File

SOURCE=.\strToInt.h
# End Source File
# Begin Source File

SOURCE=.\strToVector.h
# End Source File
# Begin Source File

SOURCE=.\strToWstr.h
# End Source File
# Begin Source File

SOURCE=.\vectorToFile.h
# End Source File
# End Group
# Begin Group "CsvDocument"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CsvDocument\CConvCsvDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\CsvDocument\CConvCsvDocument.h
# End Source File
# Begin Source File

SOURCE=.\CsvDocument\CdCsvCell.h
# End Source File
# Begin Source File

SOURCE=.\CsvDocument\CdCsvDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\CsvDocument\CdCsvDocument.h
# End Source File
# Begin Source File

SOURCE=.\CsvDocument\CdCsvRow.h
# End Source File
# End Group
# End Target
# End Project
