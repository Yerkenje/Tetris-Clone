#include "grid.h"
#include "colors.h"
#include <iostream>

Grid::Grid()
{   
    rows = 20;
    columns = 10;
    cellSize = 30;
    colors = GetCellColors();
    Initialize();
}

void Grid::Initialize(){
    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < columns; ++col){
            grid[row][col] = 0;
        }
    }
}


void Grid::Draw(){
    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < columns; ++col){
            DrawRectangle(col * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[grid[row][col]]);
        }
    }

}

bool Grid::IsCellOutside(int row, int column)
{   
    return (row < 0 || row >= rows || column < 0 || column >= columns);
}

bool Grid::IsCellEmpty(int row, int column)
{
    return (grid[row][column] == 0 ? true : false);
}

int Grid::ClearAllRows()
{
    int completed = 0;
    for(int row = rows - 1; row >= 0; row--){
        if(IsRowFull(row)){
            ClearRow(row);
            completed ++;
        }
        else if(completed > 0) MoveRowDown(row, completed);
    }
    return completed;
}

bool Grid::IsRowFull(int row)
{   
    for(int col = 0; col < columns; col++){
        if(grid[row][col] == 0) return false;
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int col = 0; col < columns; col++){
        grid[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for(int col = 0; col < columns; col++){
        grid[row + numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

void Grid::DebugPrint(){
    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < columns; ++col){
            std::cout << grid[row][col] << ' ';
        }
        std::cout << std::endl;  
    }
}
