# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++17 -I. -ICore -IUtils
TARGET = sudoku.exe

# Source files
SOURCES = main.cpp Core/Board/Board.cpp

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean build files
clean:
	del /Q $(TARGET) 2>nul

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run