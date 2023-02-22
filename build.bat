@echo off
pushd %~dp0\..\
call vendor\premake-5.0\premake5.exe vs2022
popd
PAUSE