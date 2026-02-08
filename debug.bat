@echo off
setlocal enabledelayedexpansion

if not exist "version.txt" echo 1.0.0.0 > version.txt
set /p OLD_VER=<version.txt

for /f "tokens=1-4 delims=." %%a in ("%OLD_VER%") do (set V1=%%a& set V2=%%b& set V3=%%c& set V4=%%d)
set /a NEW_V4=V4+1
set NEW_VER=%V1%.%V2%.%V3%.%NEW_V4%

if not exist "obj" mkdir obj
if not exist "debug" mkdir debug

echo [1/2] Resources...
:: Передаем только числа. Это НЕ может вызвать синтаксическую ошибку.
windres metadata.rc -O coff -o obj/res.o ^
    --codepage=1251 ^
    -DV1=%V1% -DV2=%V2% -DV3=%V3% -DV4=%NEW_V4% -DIS_DEBUG

if %errorlevel% neq 0 (echo [ERR] Resource Error! & pause & exit /b 1)

echo [2/2] Code...
set "SOURCES="
for /r "src" %%f in (*.cpp) do set "SOURCES=!SOURCES! "%%f""
g++ -g -O0 -DVERSION_STRING="\"%NEW_VER%\"" -I"C:/SDL/include/" -L"C:/SDL/lib/" !SOURCES! obj/res.o -o "debug/debug_game.exe" -lsdl2 -lsdl2_image -lsdl2_ttf -lsdl2_mixer -static-libgcc -static-libstdc++

if %errorlevel% equ 0 (
    echo %NEW_VER%>version.txt
    if exist "output" xcopy /Y /I "output\*" "debug\" >nul
	start "" /D "debug" "debug_game.exe"
) else (echo [ERR] Compile failed! & pause)
