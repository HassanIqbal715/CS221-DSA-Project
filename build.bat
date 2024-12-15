@echo off
cd /d "d:\code\Git_code\CS221-DSA-Project"

REM Compile the project
g++ main.cpp Character.cpp Functions.cpp Game.cpp GlobalVariables.cpp Menu.cpp Inventory.cpp Item.cpp Shop.cpp -o bin\main.exe

REM Check if compilation succeeded
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b %errorlevel%
)

REM Run the executable
bin\main.exe
