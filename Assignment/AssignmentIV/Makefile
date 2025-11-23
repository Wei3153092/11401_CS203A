@echo off
rem Makefile.bat for Assignment IV - Hash Function
rem 使用 MinGW/GCC/G++ 編譯 C 和 C++ 程式
rem 假設您已在 Windows 環境中安裝 MinGW 並將其路徑加入 PATH

set CC=gcc
set CXX=g++
set CFLAGS=-Wall -Wextra -std=c99 -g
set CXXFLAGS=-Wall -Wextra -std=c++11 -g

set C_DIR=C
set CXX_DIR=CXX
set C_TARGET=%C_DIR%\c_hash_test.exe
set CXX_TARGET=%CXX_DIR%\cpp_hash_test.exe

echo.
echo === 編譯 C 程式 ===

%CC% %CFLAGS% -c %C_DIR%\hash_fn.c -o %C_DIR%\hash_fn.o
if errorlevel 1 goto error_c

%CC% %CFLAGS% -c %C_DIR%\main.c -o %C_DIR%\main.o
if errorlevel 1 goto error_c

%CC% %C_DIR%\main.o %C_DIR%\hash_fn.o -o %C_TARGET%
if errorlevel 1 goto error_c

echo C 程式編譯成功: %C_TARGET%

echo.
echo === 編譯 C++ 程式 ===

%CXX% %CXXFLAGS% -c %CXX_DIR%\hash_fn.cpp -o %CXX_DIR%\hash_fn.o
if errorlevel 1 goto error_cpp

%CXX% %CXXFLAGS% -c %CXX_DIR%\main.cpp -o %CXX_DIR%\main.o
if errorlevel 1 goto error_cpp

%CXX% %CXX_DIR%\main.o %CXX_DIR%\hash_fn.o -o %CXX_TARGET%
if errorlevel 1 goto error_cpp

echo C++ 程式編譯成功: %CXX_TARGET%

goto end

:error_c
echo.
echo [錯誤] C 程式編譯失敗。
goto end

:error_cpp
echo.
echo [錯誤] C++ 程式編譯失敗。
goto end

:end
echo.
pause