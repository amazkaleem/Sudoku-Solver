@echo off
echo ==============================
echo   Building Sudoku Project
echo   with GENERATOR
echo ==============================
echo.

echo Step 1: Compiling...
g++ main.cpp Core/Board/Board.cpp Core/Solver/Solver.cpp Core/Solver/Generator.cpp -o sudoku.exe

if errorlevel 1 (
    echo.
    echo ❌ COMPILATION FAILED!
    echo Check for syntax errors.
    pause
    exit /b 1
)

echo.
echo ✅ BUILD SUCCESSFUL!
echo.
echo ==============================
echo   Running Program
echo ==============================
echo.
sudoku.exe

pause