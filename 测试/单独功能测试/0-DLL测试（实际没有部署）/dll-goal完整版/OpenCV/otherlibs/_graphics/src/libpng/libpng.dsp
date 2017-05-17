# Microsoft Developer Studio Project File - Name="libpng" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libpng - Win32 Debug64 Itanium
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libpng.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libpng.mak" CFG="libpng - Win32 Debug64 Itanium"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libpng - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libpng - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libpng - Win32 Release64" (based on "Win32 (x86) Static Library")
!MESSAGE "libpng - Win32 Debug64" (based on "Win32 (x86) Static Library")
!MESSAGE "libpng - Win32 Release64 Itanium" (based on "Win32 (x86) Static Library")
!MESSAGE "libpng - Win32 Debug64 Itanium" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "libpng - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\_temp\libpng_Rls"
# PROP Intermediate_Dir "..\..\..\..\_temp\libpng_Rls"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\libpng.lib"

!ELSEIF  "$(CFG)" == "libpng - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\_temp\libpng_Dbg"
# PROP Intermediate_Dir "..\..\..\..\_temp\libpng_Dbg"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\libpngd.lib"

!ELSEIF  "$(CFG)" == "libpng - Win32 Release64"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libpng___Win32_Release64"
# PROP BASE Intermediate_Dir "libpng___Win32_Release64"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\_temp\libpng_Rls64"
# PROP Intermediate_Dir "..\..\..\..\_temp\libpng_Rls64"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "WIN64" /D "EM64T" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\libpng.lib"
# ADD LIB32 /nologo /out:"..\..\lib\libpng_64.lib" /machine:AMD64

!ELSEIF  "$(CFG)" == "libpng - Win32 Debug64"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libpng___Win32_Debug64"
# PROP BASE Intermediate_Dir "libpng___Win32_Debug64"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\_temp\libpng_Dbg64"
# PROP Intermediate_Dir "..\..\..\..\_temp\libpng_Dbg64"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "WIN64" /D "EM64T" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\libpngd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\libpngd_64.lib" /machine:AMD64

!ELSEIF  "$(CFG)" == "libpng - Win32 Release64 Itanium"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libpng___Win32_Release64_Itanium"
# PROP BASE Intermediate_Dir "libpng___Win32_Release64_Itanium"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\_temp\libpng_RlsI7"
# PROP Intermediate_Dir "..\..\..\..\_temp\libpng_RlsI7"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "WIN64" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\libpng_64.lib"
# ADD LIB32 /nologo /out:"..\..\lib\libpng_i7.lib" /machine:IA64

!ELSEIF  "$(CFG)" == "libpng - Win32 Debug64 Itanium"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libpng___Win32_Debug64_Itanium"
# PROP BASE Intermediate_Dir "libpng___Win32_Debug64_Itanium"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\_temp\libpng_DbgI7"
# PROP Intermediate_Dir "..\..\..\..\_temp\libpng_DbgI7"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "WIN64" /D "_DEBUG" /D "_WINDOWS" /YX /FD /Qwd167 /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\libpngd_64.lib"
# ADD LIB32 /nologo /out:"..\..\lib\libpngd_i7.lib" /machine:IA64

!ENDIF 

# Begin Target

# Name "libpng - Win32 Release"
# Name "libpng - Win32 Debug"
# Name "libpng - Win32 Release64"
# Name "libpng - Win32 Debug64"
# Name "libpng - Win32 Release64 Itanium"
# Name "libpng - Win32 Debug64 Itanium"
# Begin Source File

SOURCE=.\png.c
# End Source File
# Begin Source File

SOURCE=..\..\include\png.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pngconf.h
# End Source File
# Begin Source File

SOURCE=.\pngerror.c
# End Source File
# Begin Source File

SOURCE=.\pnggccrd.c
# End Source File
# Begin Source File

SOURCE=.\pngget.c
# End Source File
# Begin Source File

SOURCE=.\pngmem.c
# End Source File
# Begin Source File

SOURCE=.\pngpread.c
# End Source File
# Begin Source File

SOURCE=.\pngread.c
# End Source File
# Begin Source File

SOURCE=.\pngrio.c
# End Source File
# Begin Source File

SOURCE=.\pngrtran.c
# End Source File
# Begin Source File

SOURCE=.\pngrutil.c
# End Source File
# Begin Source File

SOURCE=.\pngset.c
# End Source File
# Begin Source File

SOURCE=.\pngtest.c
# End Source File
# Begin Source File

SOURCE=.\pngtrans.c
# End Source File
# Begin Source File

SOURCE=.\pngvcrd.c
# End Source File
# Begin Source File

SOURCE=.\pngwio.c
# End Source File
# Begin Source File

SOURCE=.\pngwrite.c
# End Source File
# Begin Source File

SOURCE=.\pngwtran.c
# End Source File
# Begin Source File

SOURCE=.\pngwutil.c
# End Source File
# End Target
# End Project
