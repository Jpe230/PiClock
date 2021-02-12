#include "raylib.h"
#include <stdio.h>
#include <time.h>

int FindPoint(int x1, int y1, int x2, 
               int y2, int x, int y) 
{ 
    if (x > x1 && x < x2 && y > y1 && y < y2) 
        return 1; 
  
    return 0; 
} 

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
    Texture2D retroPie = LoadTexture("resources/retroPie.png");
    Texture2D volumeUp = LoadTexture("resources/volUp.png");
    Texture2D volumeDown = LoadTexture("resources/volDown.png");

    Rectangle frameRec = {0.0f, 0.0f, (float)lonk.width / 5, (float)lonk.height / 2};

    Vector2 position = {screenWidth / 2 - lonk.width / 10, screenHeight / 2 - lonk.height / 4 - 50};
    Vector2 optionsPosition = {screenWidth / 2 - textBox.width / 2 , -textBox.height};

    Font fontTtf = LoadFontEx("resources/font.ttf", 32, 0, 250);

    int currentFrame = 0;
    int currentFrameY = 0;

    int framesCounter = 0;
    int framesSpeed = 15; // Number of spritesheet frames shown by second

    float scrollingBack = 0.0f;
    float scrollingBackLeaf = 0.0f;

    int buttonPressed = -1;
    int showingOptionAnimation = 0;
    float maxOptionHeight = 20.0f;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Vector2 mousePosition = { 0.0f, 0.0f };
    
    int debounceMouse = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        
        if (IsGamepadAvailable(GAMEPAD_PLAYER1))
        {
            for(int i = 0; i < 32; i++){
                if (IsGamepadButtonDown(GAMEPAD_PLAYER1, i)){
                    printf("button pressed: %d\n", i);
                    buttonPressed = i;
                    break;
                }
            }
        }
        
        //Pressed Select
        if(buttonPressed == 8 && showingOptionAnimation == 0){
            buttonPressed = -1;
            if(optionsPosition.y < maxOptionHeight)
                showingOptionAnimation = 1;
            if(optionsPosition.y >= maxOptionHeight)
                showingOptionAnimation = 2;
        }
        
        if(showingOptionAnimation == 1){
            if(optionsPosition.y > maxOptionHeight){
                showingOptionAnimation = 0;
                optionsPosition.y = maxOptionHeight;
            }else{
                optionsPosition.y += 5.0f;
            }
        }

        if(showingOptionAnimation == 2){
            if(optionsPosition.y < -textBox.height){
                showingOptionAnimation = 0;
                optionsPosition.y = -textBox.height;
            }else{
                optionsPosition.y -= 5.0f;
            }
        }
         
        //Animations
        //----------------------------------------------------------------------------------
        scrollingBack -= .5f;
        scrollingBackLeaf -= .6f;

        if (scrollingBack <= -background.height)
            scrollingBack = 0;
        if (scrollingBackLeaf <= -leaf.height)
            scrollingBackLeaf = 0;
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
        // Background
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2){0, scrollingBack}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(background, (Vector2){0, background.height + scrollingBack}, 0.0f, 1.0f, WHITE);

        DrawTextureEx(leafshadow, (Vector2){0, scrollingBack}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(leafshadow, (Vector2){0, leaf.height + scrollingBack}, 0.0f, 1.0f, WHITE);

        DrawTextureEx(leaf, (Vector2){0, scrollingBackLeaf}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(leaf, (Vector2){0, leaf.height + scrollingBackLeaf}, 0.0f, 1.0f, WHITE);

        //Lonk
        DrawTextureRec(lonk, frameRec, position, WHITE);

        // Clock
        //----------------------------------------------------------------------------------
        localtime_r(&now, &tm_now);
        DrawTextureEx(textBox, (Vector2){53, 195}, 0.0f, 1.0f, WHITE);
        strftime(buff, sizeof(buff), "Hey Link, the time is %H %M", &tm_now);
        DrawTextEx(fontTtf, buff, (Vector2){90.58f, 230.4f}, fontTtf.baseSize, 2, WHITE);

        DrawTextureEx(retroPie,   (Vector2){400, 30}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(volumeUp,   (Vector2){10, 30}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(volumeDown, (Vector2){10, 85}, 0.0f, 1.0f, WHITE);

        mousePosition = GetMousePosition();
        if(FindPoint(400, 30, 475, 357, mousePosition.x, mousePosition.y) && debounceMouse == 0){
            debounceMouse = 1;
            //printf("help 1\n");
            system("/home/pi/test.sh");
        }
        else if(FindPoint(10, 30, 60, 80, mousePosition.x, mousePosition.y) && debounceMouse == 0){
            debounceMouse = 1;
            //printf("help 2\n");
            system("/home/pi/volu.sh");
        }
        else if(FindPoint(10, 85, 60, 135, mousePosition.x, mousePosition.y) && debounceMouse == 0){
            debounceMouse = 1;
            //printf("help 3\n");
            system("/home/pi/vold.sh");
        }else if(!FindPoint(400, 30, 475, 357, mousePosition.x, mousePosition.y) && 
                 !FindPoint(10, 30, 60, 80, mousePosition.x, mousePosition.y) &&
                 !FindPoint(10, 85, 60, 135, mousePosition.x, mousePosition.y) && 
                 debounceMouse == 1){
            debounceMouse = 0;
        }

        // Option Menu
        //----------------------------------------------------------------------------------
        //DrawTextureEx(textBox, optionsPosition, 0.0f, 1.0f, WHITE);

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