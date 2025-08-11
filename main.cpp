#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "3D movable character example");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 4.0f, 4.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    // No camera.type field anymore

    Vector3 playerPos = { 0.0f, 1.0f, 0.0f };
    float playerSpeed = 2.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Move player with arrow keys
        if (IsKeyDown(KEY_RIGHT)) playerPos.x += playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT)) playerPos.x -= playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_UP)) playerPos.z -= playerSpeed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN)) playerPos.z += playerSpeed * GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCube(playerPos, 1.0f, 2.0f, 1.0f, RED);
        DrawCubeWires(playerPos, 1.0f, 2.0f, 1.0f, MAROON);
        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Use arrow keys to move the red cube", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
