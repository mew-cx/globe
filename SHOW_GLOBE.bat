@echo off

set OSG_ROOT=C:\mew\opt\osg

set X=%OSG_ROOT%\240\data
set OSG_FILE_PATH=%OSG_FILE_PATH%;%X%
set OSG_FILE_PATH=%OSG_FILE_PATH%;%X%\Images

set X=%OSG_ROOT%\313\data
set OSG_FILE_PATH=%OSG_FILE_PATH%;%X%
set OSG_FILE_PATH=%OSG_FILE_PATH%;%X%\Images
set OSG_FILE_PATH=%OSG_FILE_PATH%;%X%\fonts
set OSG_FILE_PATH=%OSG_FILE_PATH%;%X%\earth

set PATH=%OSG_ROOT%\313\release\bin;%PATH%
REM set PATH=%OSG_ROOT%\313\debug\bin;%PATH%

REM Config section ========================================================

REM set OSG_NOTIFY_LEVEL=FATAL
REM set OSG_NOTIFY_LEVEL=WARN
REM set OSG_NOTIFY_LEVEL=NOTICE
REM set OSG_NOTIFY_LEVEL=DEBUG_INFO
REM set OSG_NOTIFY_LEVEL=DEBUG_FP
REM set OSG_NOTIFY_LEVEL=DEBUG
REM set OSG_NOTIFY_LEVEL=INFO
REM set OSG_NOTIFY_LEVEL=ALWAYS

set OSG_WINDOW=10 10 500 500

REM Runtime section =======================================================

title osgShell
echo A console configured for OpenSceneGraph:
echo OSG_ROOT = %OSG_ROOT%
echo OSG_FILE_PATH = %OSG_FILE_PATH%
echo OSG_NOTIFY_LEVEL = %OSG_NOTIFY_LEVEL%

start osgviewer.exe globe.obj.90,0,0.rot.70.scale xyz100.osg

::pause
