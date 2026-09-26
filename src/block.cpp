#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    row_offset = 0;
    column_offset = 0;
}

void Block::Draw(int offsetx, int offsety)
{
    std::vector<Position> tiles = GetCellPosition();
    for(Position item : tiles){
        DrawRectangle(item.column * cellSize + offsetx, item.row * cellSize + offsety, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int columns)
{
    row_offset += rows;
    column_offset += columns;
}

void Block::Rotate()
{
    rotationState ++;
    if(rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState --;
    if(rotationState == -1  )
    {
        rotationState = (int)cells.size() - 1   ; 
    }
}

std::vector<Position> Block::GetCellPosition()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position item : tiles){
        Position newPos = Position(row_offset + item.row, item.column + column_offset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}