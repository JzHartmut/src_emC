echo off
set  DBG=%TMP%\InspcTargetProxy_C\MSC15
if exist %DBG% rmdir /S/Q %DBG%
mkdir %DBG%
mkdir %DBG%\x64
mkdir %DBG%\x32
mkdir %DBG%\debug
mkdir %DBG%\.vs

if not exist x64 mklink /J x64 %DBG%\x64
if not exist x32 mklink /J x32 %DBG%\x32
if not exist debug mklink /J debug %DBG%\debug
if not exist .vs mklink /J .vs %DBG%\.vs
pause

