// UI/Input/KeyboardHandler.h
#pragma once
#include "Board.hpp"
#include "SelectionHandler.hpp"
#include <raylib.h>

class KeyboardHandler {
private:
    SelectionHandler& selection;
    
public:
    KeyboardHandler(SelectionHandler& sel) : selection(sel) {}
    
    void handleKeyboardInput(Board& board) {
        // Number keys 1-9
        for (int key = KEY_ONE; key <= KEY_NINE; key++) {
            if (IsKeyPressed(key)) {
                int number = key - KEY_ONE + 1;
                if (selection.hasSelectedCell()) {
                    int row = selection.getSelectedRow();
                    int col = selection.getSelectedCol();
                    
                    // Only set if not original cell and the number confirms to Sudoku logic
                    if (board.canAddMoreInputs() && board.isValidMove(row, col, number)) {
                        board.userSetCell(row, col, number);
                    }
                }
            }
        }
        
        // Delete/Backspace to clear
        if (IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_BACKSPACE)) {
            if (selection.hasSelectedCell()) {
                int row = selection.getSelectedRow();
                int col = selection.getSelectedCol();
                
                // Only clear if not original
                if (!board.isCellOriginal(row, col)) {
                    board.clearCell(row, col); // ✅ Use 0 instead of EMPTY_CELL
                }
            }
        }
        
        
        // Arrow keys for navigation
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            selection.moveSelection(0, 1);
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            selection.moveSelection(0, -1);
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            selection.moveSelection(1, 0);
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            selection.moveSelection(-1, 0);
        }
    }
};