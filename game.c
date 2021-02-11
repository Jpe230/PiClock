#include "raylib.h"
#include <stdio.h>
#include <time.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 480;
    const int screenHeight = 320;

    time_t now = time(NULL);
    struct tm tm_now;

    char buff[100];

    InitWindow(screenWidth, screenHeight, "Clock");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D background = LoadTexture("resources/backgroun.png");
    Texture2D lonk = LoadTexture("resources/lonk.png");

    Texture2D leaf = LoadTexture("resources/leaffull.png");
    Texture2D leafshadow = LoadTexture("resources/leaffullshadow.png");

    Texture2D textBox = LoadTexture("resources/textbox.png");

    Rectangle frameRec = {0.0f, 0.0f, (float)lonk.width / 5, (float)lonk.height / 2};

    Vector2 position = {screenWidth / 2 - lonk.width / 10, screenHeight / 2 - lonk.height / 4 - 50};

    Font fontTtf = LoadFontEx("resources/font.ttf", 32, 0, 250);

    int currentFrame = 0;
    int currentFrameY = 0;

    int framesCounter = 0;
    int framesSpeed = 15; // Number of spritesheet frames shown by second

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    float scrollingBack = 0.0f;
    float scrollingBackLeaf = 0.0f;

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        localtime_r(&now, &tm_now);

        scrollingBack -= .5f;
        scrollingBackLeaf -= .6f;

        if (scrollingBack <= -background.height)
            scrollingBack = 0;
        if (scrollingBackLeaf <= -leaf.height)
            scrollingBackLeaf = 0;
        //----------------------------------------------------------------------------------
        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5)
            {
                currentFrame = 0;
                currentFrameY++;
                if (currentFrameY > 1)
                    currentFrameY = 0;
            }

            frameRec.x = (float)currentFrame * (float)lonk.width / 5;
            frameRec.y = (float)currentFrameY * (float)lonk.height / 2;
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2){0, scrollingBack}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(background, (Vector2){0, background.height + scrollingBack}, 0.0f, 1.0f, WHITE);

        DrawTextureEx(leafshadow, (Vector2){0, scrollingBack}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(leafshadow, (Vector2){0, leaf.height + scrollingBack}, 0.0f, 1.0f, WHITE);

        DrawTextureEx(leaf, (Vector2){0, scrollingBackLeaf}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(leaf, (Vector2){0, leaf.height + scrollingBackLeaf}, 0.0f, 1.0f, WHITE);

        DrawTextureEx(textBox, (Vector2){53, 195}, 0.0f, 1.0f, WHITE);

        DrawTextureRec(lonk, frameRec, position, WHITE);

        strftime(buff, sizeof(buff), "Hey Link, the time is %H %M", &tm_now);

        DrawTextEx(fontTtf, buff, (Vector2){90.58f, 230.4f}, fontTtf.baseSize, 2, WHITE);

        if (IsGamepadAvailable(GAMEPAD_PLAYER1))
        {
            for(int i = 0; i < 32; i++){
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, i))
                    printf("Button: %d", i);
            }
            
            DrawCircle(259, 152, 39, BLACK);
            DrawCircle(259, 152, 34, LIGHTGRAY);
            DrawCircle(259 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_X) * 20),
                       152 + (GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_Y) * 20), 25, BLACK);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(lonk); // Texture unloading

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}