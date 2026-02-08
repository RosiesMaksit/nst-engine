@echo off
setlocal enabledelayedexpansion

if not exist "version.txt" (echo [ERR] version.txt missing! & pause & exit /b 1)
set /p VER=<version.txt
for /f "tokens=1-4 delims=." %%a in ("%VER%") do (set V1=%%a& set V2=%%b& set V3=%%c& set V4=%%d)
set "REL_PATH=releases\v%VER%"

if not exist "obj" mkdir obj
if not exist "temp_build" mkdir temp_build

echo [1/2] Resources...
windres metadata.rc -O coff -o obj/res.o ^
    --codepage=1251 ^
    -DV1=%V1% -DV2=%V2% -DV3=%V3% -DV4=%V4%

if %errorlevel% neq 0 (echo [ERR] Resource Error! & pause & exit /b 1)

echo [2/2] Code (Release)...
set "SOURCES="
for /r "src" %%f in (*.cpp) do set "SOURCES=!SOURCES! "%%f""
g++ -mwindows -O3 -s -DNDEBUG -DVERSION_STRING="\"%VER%\"" -I"C:/SDL/include/" -L"C:/SDL/lib/" !SOURCES! obj/res.o -o "temp_build/game.exe" -lsdl2 -lsdl2_image -lsdl2_ttf -lsdl2_mixer -static-libgcc -static-libstdc++

if %errorlevel% neq 0 (echo [ERR] Build failed! & rmdir /s /q temp_build & pause & exit /b 1)

mkdir "%REL_PATH%\bin" "%REL_PATH%\src" 2>nul
move /Y "temp_build\game.exe" "%REL_PATH%\bin\" >nul
if exist "output" xcopy /E /Y /I "output\*" "%REL_PATH%\bin\" >nul
xcopy /E /Y /I "src\*" "%REL_PATH%\src\src\" >nul
for %%f in (metadata.rc *.bat *.txt) do (copy /Y "%%f" "%REL_PATH%\src\" >nul)
rmdir /s /q temp_build

echo [SUCCESS] v%VER% ready in %REL_PATH%
pause
