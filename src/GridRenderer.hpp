// UI/Renderers/GridRenderer.hpp
#pragma once
#include <raylib.h>
#include "Colors.hpp"
#include "UIConstants.hpp"

//This file goes against the logic of IMPLEMENTATION within the .cpp and DECLARATION within the .hpp
//But I couldn't solve the error

class GridRenderer {
private:
    int boardX;
    int boardY;
    int cellSize;

public:
    GridRenderer(int x, int y, int size)
    : boardX(x), boardY(y), cellSize(size) {};

    void draw() const {
        for (int i = 0; i <= 3; i++) {
            DrawLine(boardX + i * cellSize * 3, boardY,
                    boardX + i * cellSize * 3, boardY + cellSize * 9,
                    UIColors::GRID_LINE_THICK);

            DrawLine(boardX, boardY + i * cellSize * 3,
                    boardX + cellSize * 9, boardY + i * cellSize * 3,
                    UIColors::GRID_LINE_THICK);
        }
    };

    Rectangle getCellRect(int row, int col) const {
        return {
            //For example: The boardX is 200 and boardY is 50
            //If the row is 0 and col is 0
            //The Rectangle object(i.e the cell) will have:
            //X-coordinate of (200 + 0 * 46) = 200
            //Y-Coordinate of (50 + 0 * 46) = 50
            //Hence cell is at (200, 50) of the canvas
            /*
            Each Cell must know:
                1) Where to draw itself
                2) Where to detect mouse clicks
                3) Where to draw highlights / borders
                4) Where to center text
            */
            (float)(boardX + col * cellSize),
            (float)(boardY + row * cellSize),
            (float)cellSize,
            (float)cellSize
        };
    };
    bool isMouseOverGrid(int mouseX, int mouseY) const {
        return mouseX >= boardX && mouseX <= boardX + cellSize * 9 &&
               mouseY >= boardY && mouseY <= boardY + cellSize * 9;
    };

    void getCellFromMouse(int mouseX, int mouseY, int& row, int& col) const {
        if (isMouseOverGrid(mouseX, mouseY)) {
            col = (mouseX - boardX) / cellSize;
            row = (mouseY - boardY) / cellSize;
        } else {
            row = col = -1;
        }
    };
};
