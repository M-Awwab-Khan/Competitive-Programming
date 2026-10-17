@echo off
if "%~1"=="" (
    echo Usage: run file.cpp
    exit /b 1
)

rem Compile the file using g++
g++ "%~1"
if %ERRORLEVEL% neq 0 (
    echo Compilation failed.
    exit /b %ERRORLEVEL%
)

rem Run the compiled executable
a.exe
