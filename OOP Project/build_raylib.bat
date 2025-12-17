@echo off
echo ==============================
echo   Building Sudoku with Raylib
echo ==============================
echo.

REM Check if raylib exists
if not exist "raylib\include\raylib.h" (
    echo ERROR: raylib not found!
    echo Please make sure you have:
    echo 1. raylib\include\raylib.h
    echo 2. raylib\lib\libraylib.a
    pause
    exit /b 1
)

echo Compiling all files...
g++ game_raylib.cpp Core/Board/Board.cpp Core/Solver/Solver.cpp ^
    -o sudoku_raylib.exe ^
    -I. -ICore -IUI -IUtils -Iraylib/include ^
    -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm ^
    -std=c++17

if %errorlevel% equ 0 (
    echo.
    echo BUILD SUCCESSFUL!
    echo.
    echo ==============================
    echo   Running Raylib Sudoku
    echo ==============================
    echo.
    sudoku_raylib.exe
) else (
    echo.
    echo BUILD FAILED!
    echo.
    echo Check:
    echo 1. All header files exist
    echo 2. #include paths are correct
    echo 3. No syntax errors in .cpp files
)

pause