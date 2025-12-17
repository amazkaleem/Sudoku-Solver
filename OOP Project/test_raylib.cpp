#include "raylib/include/raylib.h"

int main() {
    // Initialize window
    InitWindow(800, 600, "Sudoku - Raylib Test");
    
    // Set target FPS
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Start drawing
        BeginDrawing();
        
        // Clear background
        ClearBackground(RAYWHITE);
        
        // Draw text
        DrawText("Raylib is working!", 190, 200, 40, DARKGRAY);
        DrawText("Sudoku Game Project", 180, 250, 30, GRAY);
        DrawText("Abdul Nafeh - CSC241", 200, 300, 20, LIGHTGRAY);
        
        // End drawing
        EndDrawing();
    }
    
    // Close window
    CloseWindow();
    
    return 0;
}