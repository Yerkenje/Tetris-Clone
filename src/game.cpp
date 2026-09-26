#include "game.h"
#include <random>
#include <iostream>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    moves[0] = {0, 1};
    moves[1] = {0, -1};
    moves[2] = {1, 0};
    gameover = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Music/tetris_theme.ogg");
    PlayMusicStream(music);

    lastKeyPressed = 0;
    keyHeld = false;
}

Game::~Game()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randIndex = rand() % blocks.size();
    Block block = blocks[randIndex];
    blocks.erase(blocks.begin() + randIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);

    switch(nextBlock.id){
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
            break;
    }
}

void Game::HandleInput()
{   
    int keyPressed = GetKeyPressed();
    lastKeyPressed = keyPressed;

    if(IsKeyDown(lastKeyPressed)) keyHeld = true; // if it is held then continuesly send control
    if(IsKeyUp(lastKeyPressed)) keyHeld = false;

    keyPressed -= 262;
    if(gameover && keyPressed != -262){
        gameover = false;
        Reset();
    }


    if(keyPressed < 3 && keyPressed >= 0)
    {
        MoveBlock(moves[keyPressed]);
    }
    else if(keyPressed == 3)
    {
        RotateBlock();
    }
}

void Game::MoveBlock(std::pair<int, int> change)
{   
    if(gameover) return;
    currentBlock.Move(change.first, change.second);
    if(IsBlockOutside() || BlockFits() == false)
    {
        currentBlock.Move(-change.first, -change.second);
        if(change.first == 1) LockBlock(), UpdateScore(0, 1);
    }
}

void Game::UpdateScore(int rowsCleared, int movesDownpoints)
{
    switch (rowsCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += movesDownpoints;
}

void Game::RotateBlock()
{   
    if(gameover) return;
    currentBlock.Rotate();  
    if(IsBlockOutside() || BlockFits() == false)
    {
        currentBlock.UndoRotation();
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits() == false){
        gameover = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearAllRows();
    UpdateScore(rowsCleared, 0);
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles)
    {
        if(!grid.IsCellEmpty(item.row, item.column)) return false;
    }
    return true;
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles)
    {
        if(grid.IsCellOutside(item.row, item.column)) return true;
    }
    return false;
}
