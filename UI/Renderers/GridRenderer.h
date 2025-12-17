// UI/Renderers/GridRenderer.h
#pragma once
#include "../../Utils/Colors.h"
#include "../../UI/UIConstants.h"

class GridRenderer {
private:
    int boardX, boardY, cellSize;
    
public:
    GridRenderer(int x = UIConstants::BOARD_X,
                 int y = UIConstants::BOARD_Y,
                 int size = UIConstants::CELL_SIZE)
        : boardX(x), boardY(y), cellSize(size) {}
    
    void draw() const {
        // Draw thin grid lines
        for (int i = 0; i <= 9; i++) {
            // Vertical lines
            DrawLine(boardX + i * cellSize, boardY,
                     boardX + i * cellSize, boardY + cellSize * 9,
                     UIColors::GRID_LINE_THIN);
            
            // Horizontal lines
            DrawLine(boardX, boardY + i * cellSize,
                     boardX + cellSize * 9, boardY + i * cellSize,
                     UIColors::GRID_LINE_THIN);
        }
        
        //YES!
        // Draw thick 3x3 box lines
        for (int i = 0; i <= 3; i++) {
            // Vertical thick lines
            //void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);
            // Draw a line
            DrawLine(boardX + i * cellSize * 3, boardY,
                     boardX + i * cellSize * 3, boardY + cellSize * 9,
                     UIColors::GRID_LINE_THICK);
            
            // Horizontal thick lines
            DrawLine(boardX, boardY + i * cellSize * 3,
                     boardX + cellSize * 9, boardY + i * cellSize * 3,
                     UIColors::GRID_LINE_THICK);
        }
    }
    
    Rectangle getCellRect(int row, int col) const {
        return {
            (float)(boardX + col * cellSize),
            (float)(boardY + row * cellSize),
            (float)cellSize,
            (float)cellSize
        };
    }
    
    bool isMouseOverGrid(int mouseX, int mouseY) const {
        return mouseX >= boardX && mouseX <= boardX + cellSize * 9 &&
               mouseY >= boardY && mouseY <= boardY + cellSize * 9;
    }
    
    void getCellFromMouse(int mouseX, int mouseY, int& row, int& col) const {
        if (isMouseOverGrid(mouseX, mouseY)) {
            col = (mouseX - boardX) / cellSize;
            row = (mouseY - boardY) / cellSize;
        } else {
            row = col = -1;
        }
    }
};