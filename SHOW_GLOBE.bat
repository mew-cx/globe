::@echo off

set OSG_ROOT=C:\Program Files (x86)\OpenSceneGraph
set OSG_ROOT=C:\mew\osg\runtime

set OSG_FILE_PATH=%OSG_ROOT%\data;%OSG_ROOT%\data\osg240
set OSG_PATH=%OSG_ROOT%\bin

set PATH=%OSG_PATH%;%PATH%

REM Config section ========================================================

set OSG_NOTIFY_LEVEL=FATAL
REM set OSG_NOTIFY_LEVEL=WARN
REM set OSG_NOTIFY_LEVEL=NOTICE
REM set OSG_NOTIFY_LEVEL=DEBUG_INFO
REM set OSG_NOTIFY_LEVEL=DEBUG_FP
REM set OSG_NOTIFY_LEVEL=DEBUG
REM set OSG_NOTIFY_LEVEL=INFO
REM set OSG_NOTIFY_LEVEL=ALWAYS

set OSG_WINDOW=10 10 800 800

REM Runtime section =======================================================

title osgShell
echo A console configured for OpenSceneGraph:
echo OSG_ROOT = %OSG_ROOT%
echo OSG_FILE_PATH = %OSG_FILE_PATH%
echo OSG_NOTIFY_LEVEL = %OSG_NOTIFY_LEVEL%

::Debug\globe.exe > globe.obj

set OSGVIEWER=start osgviewer.exe -O noRotation
%OSGVIEWER% globe.obj xyz100.osg
::%OSGVIEWER% globe.obj

::pause
