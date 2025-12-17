// UI/UI.h - Main UI controller
#pragma once
#include "Renderers/GridRenderer.h"
#include "Renderers/NumberRenderer.h"
#include "Selection/SelectionHandler.h"
#include "Input/MouseHandler.h"
#include "Input/KeyboardHandler.h"
#include "../../Core/Board/Board.h"
#include "../../Core/Solver/Solver.h"
#include <iostream>
#include <cstdio>

class UI {
private:
    GridRenderer gridRenderer;
    NumberRenderer numberRenderer;
    SelectionHandler selectionHandler;
    MouseHandler mouseHandler;
    KeyboardHandler keyboardHandler;
    
    bool showErrors;
    bool pencilMode;
    
public:
    UI() 
        : gridRenderer(),
          numberRenderer(),
          selectionHandler(),
          mouseHandler(selectionHandler, gridRenderer),
          keyboardHandler(selectionHandler),
          showErrors(false),
          pencilMode(false) {}
    
    void handleInput(Board& board, Solver& solver) {
        mouseHandler.handleMouseClick();
        keyboardHandler.handleKeyboardInput(board);
        
        // Special keys
        if (IsKeyPressed(KEY_SPACE)) {
            solver.solve(board);
        }
        if (IsKeyPressed(KEY_R)) {
            board.clearBoard();
            // Reset to test puzzle
            setupTestPuzzle(board);
        }
        if (IsKeyPressed(KEY_P)) {
            pencilMode = !pencilMode;
        }
    }
    
    void render(const Board& board) {
        // Draw background
        DrawRectangle(0, 0, UIConstants::SCREEN_WIDTH, UIConstants::SCREEN_HEIGHT, 
                     UIColors::BACKGROUND);
        
        // Draw board background panel
        DrawRectangle(UIConstants::BOARD_X - 10, UIConstants::BOARD_Y - 10,
                     UIConstants::BOARD_SIZE + 20, UIConstants::BOARD_SIZE + 20,
                     UIColors::PANEL_BG);
        
        // Draw grid
        gridRenderer.draw();
        
        // Draw selected cell highlight
        if (selectionHandler.hasSelectedCell()) {
            drawSelectionHighlight();
        }
        
        // Draw numbers
        numberRenderer.drawBoardNumbers(board);
        
        // Draw UI text
        drawUIText();
    }
    
private:
    void drawSelectionHighlight() {
        int row = selectionHandler.getSelectedRow();
        int col = selectionHandler.getSelectedCol();
        
        Rectangle cellRect = gridRenderer.getCellRect(row, col);
        DrawRectangleRec(cellRect, UIColors::CELL_SELECTED);
    }
    
    void drawUIText() {
        DrawText("SUDOKU GAME", 300, 10, 30, UIColors::TEXT_PRIMARY);
        DrawText("Abdul Nafeh - CSC241 OOP Project", 200, 45, 20, UIColors::TEXT_SECONDARY);
        
        // Instructions
        DrawText("Click cells, press 1-9, SPACE to solve, R to reset", 
                150, UIConstants::SCREEN_HEIGHT - 60, 18, UIColors::TEXT_SECONDARY);
        
        // Selection info
        if (selectionHandler.hasSelectedCell()) {
            char info[50];
            sprintf(info, "Selected: (%d, %d)", 
                    selectionHandler.getSelectedRow(), 
                    selectionHandler.getSelectedCol());
            DrawText(info, 10, UIConstants::SCREEN_HEIGHT - 30, 18, UIColors::TEXT_PRIMARY);
        }
    }
    
    void setupTestPuzzle(Board& board) {
        board.setCell(0, 0, 5, true);
        board.setCell(0, 1, 3, true);
        board.setCell(0, 4, 7, true);
        board.setCell(1, 0, 6, true);
        board.setCell(1, 3, 1, true);
        board.setCell(1, 4, 9, true);
        board.setCell(1, 5, 5, true);
    }
};