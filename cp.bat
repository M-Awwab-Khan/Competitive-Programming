@echo off
setlocal

:: Usage:
:: cp filename.cpp          -> normal optimized build
:: cp filename.cpp debug    -> debug build
:: cp filename.cpp fast     -> aggressive build

if "%1"=="" (
    echo Usage: cp filename.cpp [debug^|fast]
    exit /b
)

set FILE=%1
set OUT=main.exe

:: Default flags (recommended for contests)
set FLAGS=-std=gnu++23 -O2 -Wall -Wextra -Wshadow

if "%2"=="debug" (
    echo Compiling in DEBUG mode...
    set FLAGS=-std=gnu++23 -O0 -g -Wall -Wextra -Wshadow
)

if "%2"=="fast" (
    echo Compiling in FAST mode...
    set FLAGS=-std=gnu++23 -O3 -Ofast -march=native
)

echo.
echo Compiling %FILE% ...
g++ %FILE% %FLAGS% -o %OUT%

if %ERRORLEVEL% neq 0 (
    echo.
    echo Compilation failed.
    exit /b
)

echo.
echo Running program...
echo ---------------------
%OUT%
echo ---------------------

endlocal