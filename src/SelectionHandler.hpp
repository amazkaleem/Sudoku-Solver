// UI/Selection/SelectionHandler.h
#pragma once

class SelectionHandler {
private:
    int selectedRow;
    int selectedCol;
    bool hasSelection;
    
public:
    SelectionHandler() : selectedRow(-1), selectedCol(-1), hasSelection(false) {}
    
    void selectCell(int row, int col) {
        if (row >= 0 && row < 9 && col >= 0 && col < 9) {
            selectedRow = row;
            selectedCol = col;
            hasSelection = true;
        }
    }
    
    void clearSelection() {
        selectedRow = selectedCol = -1;
        hasSelection = false;
    }
    
    void moveSelection(int rowDelta, int colDelta) {
        if (hasSelection) {
            int newRow = selectedRow + rowDelta;
            int newCol = selectedCol + colDelta;
            
            if (newRow >= 0 && newRow < 9 && newCol >= 0 && newCol < 9) {
                selectedRow = newRow;
                selectedCol = newCol;
            }
        }
    }
    
    // Getters
    bool hasSelectedCell() const { return hasSelection; }
    int getSelectedRow() const { return selectedRow; }
    int getSelectedCol() const { return selectedCol; }
    
    bool isValidSelection() const {
        return hasSelection && selectedRow >= 0 && selectedRow < 9 && 
               selectedCol >= 0 && selectedCol < 9;
    }
};