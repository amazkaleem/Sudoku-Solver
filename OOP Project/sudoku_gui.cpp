#define GRAPHICS_API_OPENGL_21
#define RLGL_IMPLEMENTATION
#define RLGL_SUPPORT_TRACELOG
#include "raylib/include/raylib.h"
#include <iostream>
#include <cstring>
#include <vector>

// ================= YOUR EXISTING CODE HERE =================
// PASTE YOUR ENTIRE SOLVER, GENERATOR, AND HELPER FUNCTIONS HERE
// For example:

bool isValid(int board[9][9], int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num) return false;
    }
    
    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) return false;
        }
    }
    return true;
}

bool solveSudoku(int board[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board)) return true;
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void generateBoard(int board[9][9]) {
    // PASTE YOUR ACTUAL GENERATOR HERE
    // For now, create a simple puzzle
    memset(board, 0, sizeof(int) * 81);
    
    // Example puzzle (zeros are empty cells)
    int example[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    memcpy(board, example, sizeof(example));
}
// ================= END OF YOUR CODE =================

// ================= RAYLIB GRAPHICS CODE =================
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 50;
const int BOARD_X = 100;
const int BOARD_Y = 100;

int board[9][9] = {0};
int originalBoard[9][9] = {0};
int selectedRow = -1, selectedCol = -1;
bool pencilMode = false;
int pencilMarks[9][9][9] = {0}; // [row][col][number-1]

void drawBoard() {
    // Draw the Sudoku grid
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int x = BOARD_X + col * CELL_SIZE;
            int y = BOARD_Y + row * CELL_SIZE;
            
            // Draw cell background
            Color bgColor = RAYWHITE;
            
            // Highlight selected cell
            if (row == selectedRow && col == selectedCol) {
                bgColor = YELLOW;
            }
            // Highlight same row/column
            else if (row == selectedRow || col == selectedCol) {
                bgColor = Color{230, 230, 230, 255}; // Light gray
            }
            
            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, bgColor);
            
            // Draw cell border
            DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, BLACK);
            
            // Draw thick lines for 3x3 boxes
            if (col % 3 == 0) {
                DrawLine(x, y, x, y + CELL_SIZE * 3, BLACK);
            }
            if (row % 3 == 0) {
                DrawLine(x, y, x + CELL_SIZE * 3, y, BLACK);
            }
            
            // Draw number if present
            if (board[row][col] != 0) {
                Color numColor = (originalBoard[row][col] != 0) ? BLACK : BLUE;
                char numText[2];
                sprintf(numText, "%d", board[row][col]);
                DrawText(numText, x + 15, y + 10, 30, numColor);
            }
            
            // Draw pencil marks
            for (int num = 1; num <= 9; num++) {
                if (pencilMarks[row][col][num-1] == 1) {
                    int subX = (num-1) % 3;
                    int subY = (num-1) / 3;
                    int px = x + subX * (CELL_SIZE/3) + 3;
                    int py = y + subY * (CELL_SIZE/3) + 2;
                    
                    char mark[2];
                    sprintf(mark, "%d", num);
                    DrawText(mark, px, py, 15, GRAY);
                }
            }
        }
    }
    
    // Draw outer border
    DrawRectangleLines(BOARD_X, BOARD_Y, CELL_SIZE * 9, CELL_SIZE * 9, BLACK);
}

void handleInput() {
    // Mouse input
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        int col = (mousePos.x - BOARD_X) / CELL_SIZE;
        int row = (mousePos.y - BOARD_Y) / CELL_SIZE;
        
        if (row >= 0 && row < 9 && col >= 0 && col < 9) {
            selectedRow = row;
            selectedCol = col;
        }
    }
    
    // Keyboard input
    if (selectedRow != -1 && selectedCol != -1) {
        // Number keys 1-9
        for (int key = KEY_ONE; key <= KEY_NINE; key++) {
            if (IsKeyPressed(key)) {
                int number = key - KEY_ONE + 1;
                
                if (pencilMode) {
                    // Toggle pencil mark
                    pencilMarks[selectedRow][selectedCol][number-1] ^= 1;
                } else if (originalBoard[selectedRow][selectedCol] == 0) {
                    // Only allow editing non-original cells
                    board[selectedRow][selectedCol] = number;
                }
            }
        }
        
        // Delete/Backspace key
        if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_BACKSPACE)) {
            if (originalBoard[selectedRow][selectedCol] == 0) {
                board[selectedRow][selectedCol] = 0;
                // Clear pencil marks for this cell
                memset(pencilMarks[selectedRow][selectedCol], 0, sizeof(int) * 9);
            }
        }
    }
    
    // Control keys
    if (IsKeyPressed(KEY_P)) pencilMode = !pencilMode;
    if (IsKeyPressed(KEY_S)) {
        // Solve the board
        int tempBoard[9][9];
        memcpy(tempBoard, board, sizeof(board));
        if (solveSudoku(tempBoard)) {
            memcpy(board, tempBoard, sizeof(board));
            DrawText("Solved!", BOARD_X, BOARD_Y - 40, 30, GREEN);
        }
    }
    if (IsKeyPressed(KEY_H) && selectedRow != -1 && selectedCol != -1) {
        // Give hint for selected cell
        int tempBoard[9][9];
        memcpy(tempBoard, board, sizeof(board));
        if (solveSudoku(tempBoard)) {
            board[selectedRow][selectedCol] = tempBoard[selectedRow][selectedCol];
        }
    }
    if (IsKeyPressed(KEY_N)) {
        // New game
        generateBoard(originalBoard);
        memcpy(board, originalBoard, sizeof(originalBoard));
        memset(pencilMarks, 0, sizeof(pencilMarks));
        selectedRow = selectedCol = -1;
    }
}

void drawUI() {
    // Draw instructions
    DrawText("SUDOKU GAME", 300, 20, 30, DARKBLUE);
    
    // Draw mode indicator
    if (pencilMode) {
        DrawText("PENCIL MODE", BOARD_X, BOARD_Y - 40, 20, RED);
    } else {
        DrawText("NORMAL MODE", BOARD_X, BOARD_Y - 40, 20, GREEN);
    }
    
    // Draw controls
    DrawText("Controls:", 600, 100, 20, DARKGRAY);
    DrawText("P: Toggle Pencil Mode", 600, 130, 18, GRAY);
    DrawText("S: Solve Board", 600, 155, 18, GRAY);
    DrawText("H: Get Hint", 600, 180, 18, GRAY);
    DrawText("N: New Game", 600, 205, 18, GRAY);
    DrawText("Click: Select Cell", 600, 230, 18, GRAY);
    DrawText("1-9: Enter Number", 600, 255, 18, GRAY);
    DrawText("DEL: Clear Cell", 600, 280, 18, GRAY);
    
    // Draw selected cell info
    if (selectedRow != -1 && selectedCol != -1) {
        char posText[50];
        sprintf(posText, "Selected: [%d, %d]", selectedRow, selectedCol);
        DrawText(posText, BOARD_X, BOARD_Y + CELL_SIZE * 9 + 20, 20, BLUE);
    }
}

int main() {
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sudoku Game");
    SetTargetFPS(60);
    
    // Initialize game
    generateBoard(originalBoard);
    memcpy(board, originalBoard, sizeof(originalBoard));
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        handleInput();
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        drawBoard();
        drawUI();
        
        // Show FPS
        DrawFPS(10, 10);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}