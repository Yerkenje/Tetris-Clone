#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastTime = 0;
double intervalGlobal = 0.2;

bool EventTrigger(double interval)
{   
    double currentTime = GetTime();

    if(currentTime - lastTime >= interval)
    {
        lastTime = currentTime;
        return true;
    }
    return false;
}

constexpr int screenWidth = 500;
constexpr int screenHeight = 620;

int main() 
{   
    InitWindow(screenWidth, screenHeight, "tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    
    Game game = Game();

    while (!WindowShouldClose())
    {   
        UpdateMusicStream(game.music);
        game.HandleInput();

        if(EventTrigger(intervalGlobal)){
            game.MoveBlock(game.moves[2]); // probably a bad thing
        }

        BeginDrawing();

        ClearBackground(darkBlue);
        DrawTextEx(font, "score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "next", {370, 175}, 38, 2, WHITE);
        if(game.gameover) DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        DrawRectangleRounded(Rectangle{320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {(float)320 + ((170 - static_cast<int>(textSize.x)) >> 1), 65}, 38, 2, WHITE);

        DrawRectangleRounded(Rectangle{320, 215, 170, 180}, 0.3, 6, lightBlue);

        game.Draw();

        EndDrawing();
    }
    
    CloseWindow();
}