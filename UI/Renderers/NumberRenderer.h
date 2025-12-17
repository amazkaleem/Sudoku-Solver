// UI/Renderers/NumberRenderer.h
#pragma once
#include <cstdio>        // For TextFormat
#include "../../Utils/Colors.h"
#include "../../UI/UIConstants.h"
#include "../../Core/Board/Board.h"

class NumberRenderer {
private:
    int cellSize;
    
public:
    NumberRenderer(int size = UIConstants::CELL_SIZE) : cellSize(size) {}
    
    void drawBoardNumbers(const Board& board) const {
        for (int row = 0; row < BOARD_SIZE; row++) {           // REMOVE GameConstants::
            for (int col = 0; col < BOARD_SIZE; col++) {       // REMOVE GameConstants::
                int value = board.getCell(row, col);
                if (value != EMPTY_CELL) {                     // REMOVE GameConstants::
                    drawNumber(row, col, value, board.isCellOriginal(row, col));
                }
            }
        }
    }
    
    void drawNumber(int row, int col, int value, bool isOriginal) const {
        int x = UIConstants::BOARD_X + col * cellSize + cellSize / 2;
        int y = UIConstants::BOARD_Y + row * cellSize + cellSize / 2;
        
        Color color = isOriginal ? UIColors::NUMBER_ORIGINAL : UIColors::NUMBER_USER;
        
        // TextFormat is a raylib function
        const char* text = TextFormat("%d", value);
        
        // Center the text
        Vector2 textSize = MeasureTextEx(GetFontDefault(), text, 30, 2);
        DrawText(text, x - textSize.x / 2, y - textSize.y / 2, 30, color);
    }
};