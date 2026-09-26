#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlock(std::pair<int, int>);
    std::map<int, std::pair<int, int>> moves;
    bool gameover;
    int score;
    Music music;

    
private:
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void UpdateScore(int rowsCleared, int movesDownpoints);
    void RotateBlock();
    void LockBlock();
    void Reset();
    bool BlockFits();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsBlockOutside();
    Grid grid;
    int lastKeyPressed;
    bool keyHeld;
};