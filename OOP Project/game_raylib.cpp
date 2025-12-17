// game_raylib.cpp - Main Raylib entry point
#include "raylib/include/raylib.h"
#include "Core/Board/Board.h"
#include "Core/Solver/Solver.h"
#include "UI/UI.h"
#include "UI/UIConstants.h"
#include <iostream>
#include <cstdio>

int main() {
    // Initialize window
    InitWindow(UIConstants::SCREEN_WIDTH, UIConstants::SCREEN_HEIGHT, 
               UIConstants::WINDOW_TITLE);
    
    // Enable window resizing
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    
    // Create game objects
    Board board;
    Solver solver;
    UI ui;
    
    // Setup initial puzzle
    board.setCell(0, 0, 5, true);
    board.setCell(0, 1, 3, true);
    board.setCell(0, 4, 7, true);
    board.setCell(1, 0, 6, true);
    board.setCell(1, 3, 1, true);
    board.setCell(1, 4, 9, true);
    board.setCell(1, 5, 5, true);
    
    std::cout << "Raylib Sudoku Game Started!\n";
    std::cout << "Controls:\n";
    std::cout << "- Click cells to select\n";
    std::cout << "- Numbers 1-9 to fill\n";
    std::cout << "- Arrow keys/WASD to move\n";
    std::cout << "- Delete/Backspace to clear\n";
    std::cout << "- SPACE to solve puzzle\n";
    std::cout << "- R to reset puzzle\n";
    std::cout << "- P to toggle pencil mode\n";
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Handle input
        ui.handleInput(board, solver);
        
        // Draw everything
        BeginDrawing();
        ui.render(board);
        EndDrawing();
    }
    
    // Cleanup
    CloseWindow();
    
    std::cout << "Game closed.\n";
    return 0;
}