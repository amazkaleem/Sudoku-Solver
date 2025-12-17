// UI/Input/MouseHandler.h
#pragma once
#include "GridRenderer.hpp"
#include "SelectionHandler.hpp"

class MouseHandler {
private:
    SelectionHandler& selection;
    GridRenderer& grid;
    
public:
    MouseHandler(SelectionHandler& sel, GridRenderer& grd)
        : selection(sel), grid(grd) {}
    
    void handleMouseClick() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            
            if (grid.isMouseOverGrid(mousePos.x, mousePos.y)) {
                int row, col;
                grid.getCellFromMouse(mousePos.x, mousePos.y, row, col);
                selection.selectCell(row, col);
            }
        }
    }
};