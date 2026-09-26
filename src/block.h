#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"


class Block
{
public:
    Block();
    void Draw(int offsetx, int offsety);
    void Move(int rows, int columns);
    void Rotate();
    void UndoRotation();
    std::vector<Position> GetCellPosition();
    int id;
    std::map<int, std::vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int row_offset, column_offset;
};