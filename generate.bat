@echo off
IF NOT EXIST premake5.exe (
    echo [ERROR] premake5.exe not found!
    echo Please download it from: https://premake.github.io/download/
    pause
    exit /b
)

echo [Premake] Generating Visual Studio 2022 project files...
premake5.exe vs2022
pause