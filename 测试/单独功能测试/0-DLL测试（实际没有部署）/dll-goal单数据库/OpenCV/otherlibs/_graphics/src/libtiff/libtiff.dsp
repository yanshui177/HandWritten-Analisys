# Microsoft Developer Studio Project File - Name="libtiff" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libtiff - Win32 Debug64 Itanium
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libtiff.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libtiff.mak" CFG="libtiff - Win32 Debug64 Itanium"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libtiff - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libtiff - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "libtiff - Win32 Release64" (based on "Win32 (x86) Static Library")
!MESSAGE "libtiff - Win32 Debug64" (based on "Win32 (x86) Static Library")
!MESSAGE "libtiff - Win32 Release64 Itanium" (based on "Win32 (x86) Static Library")
!MESSAGE "libtiff - Win32 Debug64 Itanium" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "libtiff - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\_temp\libtiff_Rls"
# PROP Intermediate_Dir "..\..\..\..\_temp\libtiff_Rls"
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
# ADD LIB32 /nologo /out:"..\..\lib\libtiff.lib"

!ELSEIF  "$(CFG)" == "libtiff - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\_temp\libtiff_Dbg"
# PROP Intermediate_Dir "..\..\..\..\_temp\libtiff_Dbg"
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
# ADD LIB32 /nologo /out:"..\..\lib\libtiffd.lib"

!ELSEIF  "$(CFG)" == "libtiff - Win32 Release64"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libtiff___Win32_Release64"
# PROP BASE Intermediate_Dir "libtiff___Win32_Release64"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\_temp\libtiff_Rls64"
# PROP Intermediate_Dir "..\..\..\..\_temp\libtiff_Rls64"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "WIN64" /D "EM64T" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\libtiff.lib"
# ADD LIB32 /nologo /out:"..\..\lib\libtiff_64.lib" /machine:AMD64

!ELSEIF  "$(CFG)" == "libtiff - Win32 Debug64"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libtiff___Win32_Debug64"
# PROP BASE Intermediate_Dir "libtiff___Win32_Debug64"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\_temp\libtiff_Dbg64"
# PROP Intermediate_Dir "..\..\..\..\_temp\libtiff_Dbg64"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "WIN64" /D "EM64T" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\libtiffd.lib"
# ADD LIB32 /nologo /out:"..\..\lib\libtiffd_64.lib" /machine:AMD64

!ELSEIF  "$(CFG)" == "libtiff - Win32 Release64 Itanium"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libtiff___Win32_Release64_Itanium"
# PROP BASE Intermediate_Dir "libtiff___Win32_Release64_Itanium"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\_temp\libtiff_RlsI7"
# PROP Intermediate_Dir "..\..\..\..\_temp\libtiff_RlsI7"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "WIN64" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\libtiff_64.lib"
# ADD LIB32 /nologo /out:"..\..\lib\libtiff_i7.lib" /machine:IA64

!ELSEIF  "$(CFG)" == "libtiff - Win32 Debug64 Itanium"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libtiff___Win32_Debug64_Itanium"
# PROP BASE Intermediate_Dir "libtiff___Win32_Debug64_Itanium"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\_temp\libtiff_DbgI7"
# PROP Intermediate_Dir "..\..\..\..\_temp\libtiff_DbgI7"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\include" /D "WIN32" /D "WIN64" /D "_DEBUG" /D "_WINDOWS" /YX /FD /Qwd167 /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\lib\libtiffd_64.lib"
# ADD LIB32 /nologo /out:"..\..\lib\libtiffd_i7.lib" /machine:IA64

!ENDIF 

# Begin Target

# Name "libtiff - Win32 Release"
# Name "libtiff - Win32 Debug"
# Name "libtiff - Win32 Release64"
# Name "libtiff - Win32 Debug64"
# Name "libtiff - Win32 Release64 Itanium"
# Name "libtiff - Win32 Debug64 Itanium"
# Begin Source File

SOURCE=.\t4.h
# End Source File
# Begin Source File

SOURCE=.\tif_aux.c
# End Source File
# Begin Source File

SOURCE=.\tif_close.c
# End Source File
# Begin Source File

SOURCE=.\tif_codec.c
# End Source File
# Begin Source File

SOURCE=.\tif_color.c
# End Source File
# Begin Source File

SOURCE=.\tif_compress.c
# End Source File
# Begin Source File

SOURCE=.\tif_dir.c
# End Source File
# Begin Source File

SOURCE=.\tif_dir.h
# End Source File
# Begin Source File

SOURCE=.\tif_dirinfo.c
# End Source File
# Begin Source File

SOURCE=.\tif_dirread.c
# End Source File
# Begin Source File

SOURCE=.\tif_dirwrite.c
# End Source File
# Begin Source File

SOURCE=.\tif_dumpmode.c
# End Source File
# Begin Source File

SOURCE=.\tif_error.c
# End Source File
# Begin Source File

SOURCE=.\tif_extension.c
# End Source File
# Begin Source File

SOURCE=.\tif_fax3.c
# End Source File
# Begin Source File

SOURCE=.\tif_fax3.h
# End Source File
# Begin Source File

SOURCE=.\tif_fax3sm.c
# End Source File
# Begin Source File

SOURCE=.\tif_flush.c
# End Source File
# Begin Source File

SOURCE=.\tif_getimage.c
# End Source File
# Begin Source File

SOURCE=.\tif_jpeg.c
# End Source File
# Begin Source File

SOURCE=.\tif_luv.c
# End Source File
# Begin Source File

SOURCE=.\tif_lzw.c
# End Source File
# Begin Source File

SOURCE=.\tif_next.c
# End Source File
# Begin Source File

SOURCE=.\tif_ojpeg.c
# End Source File
# Begin Source File

SOURCE=.\tif_open.c
# End Source File
# Begin Source File

SOURCE=.\tif_packbits.c
# End Source File
# Begin Source File

SOURCE=.\tif_pixarlog.c
# End Source File
# Begin Source File

SOURCE=.\tif_predict.c
# End Source File
# Begin Source File

SOURCE=.\tif_predict.h
# End Source File
# Begin Source File

SOURCE=.\tif_print.c
# End Source File
# Begin Source File

SOURCE=.\tif_read.c
# End Source File
# Begin Source File

SOURCE=.\tif_stream.cxx
# End Source File
# Begin Source File

SOURCE=.\tif_strip.c
# End Source File
# Begin Source File

SOURCE=.\tif_swab.c
# End Source File
# Begin Source File

SOURCE=.\tif_thunder.c
# End Source File
# Begin Source File

SOURCE=.\tif_tile.c
# End Source File
# Begin Source File

SOURCE=.\tif_version.c
# End Source File
# Begin Source File

SOURCE=.\tif_warning.c
# End Source File
# Begin Source File

SOURCE=.\tif_win32.c
# End Source File
# Begin Source File

SOURCE=.\tif_write.c
# End Source File
# Begin Source File

SOURCE=.\tif_zip.c
# End Source File
# Begin Source File

SOURCE=..\..\include\tiff.h
# End Source File
# Begin Source File

SOURCE=.\tiffconf.h
# End Source File
# Begin Source File

SOURCE=..\..\include\tiffio.h
# End Source File
# Begin Source File

SOURCE=.\tiffiop.h
# End Source File
# Begin Source File

SOURCE=..\..\include\tiffvers.h
# End Source File
# Begin Source File

SOURCE=.\uvcode.h
# End Source File
# End Target
# End Project
