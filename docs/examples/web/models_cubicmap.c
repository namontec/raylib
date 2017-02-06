/*******************************************************************************************
*
*   raylib [models] example - Cubicmap loading and drawing (adapted for HTML5 platform)
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 450;

// Define the camera to look into our 3d world
Camera camera = {{ 16.0f, 14.0f, 16.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f };

Texture2D cubicmap;
Model map;

Vector3 mapPosition = { -16.0f, 0.0f, -8.0f };                 // Set model position

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [models] example - cubesmap loading and drawing");

    Image image = LoadImage("resources/cubicmap.png");  // Load cubicmap image (RAM)
    cubicmap = LoadTextureFromImage(image);             // Convert image to texture to display (VRAM)
    map = LoadCubicmap(image);                          // Load cubicmap model (generate model from image)
    
    // NOTE: By default each cube is mapped to one part of texture atlas
    Texture2D texture = LoadTexture("resources/cubicmap_atlas.png");    // Load map texture
    map.material.texDiffuse = texture;                  // Set map diffuse texture

    UnloadImage(image);     // Unload cubesmap image from RAM, already uploaded to VRAM
    
    SetCameraMode(CAMERA_ORBITAL);      // Set an orbital camera mode
    SetCameraPosition(camera.position); // Set internal camera position to match our custom camera position

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(cubicmap);    // Unload cubicmap texture
    UnloadTexture(texture);     // Unload map texture
    UnloadModel(map);           // Unload map model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    UpdateCamera(&camera);          // Update internal camera and our camera
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        Begin3dMode(camera);

            DrawModel(map, mapPosition, 1.0f, WHITE);

        End3dMode();
        
        DrawTextureEx(cubicmap, (Vector2){ screenWidth - cubicmap.width*4 - 20, 20 }, 0.0f, 4.0f, WHITE);
        DrawRectangleLines(screenWidth - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, GREEN);
        
        DrawText("cubicmap image used to", 658, 90, 10, GRAY);
        DrawText("generate map 3d model", 658, 104, 10, GRAY);

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
