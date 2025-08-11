#include "raylib.h"
#include <deque>

// Screen size
const int screenWidth = 800;
const int screenHeight = 600;
const int cellSize = 20;  // size of each snake segment and food

enum Direction { UP, DOWN, LEFT, RIGHT };

int main() {
    InitWindow(screenWidth, screenHeight, "Snake with raylib");

    SetTargetFPS(10);  // Snake speed (10 frames per second)

    // Snake represented as a deque of positions (head at front)
    std::deque<Vector2> snake;
    snake.push_back({screenWidth / 2, screenHeight / 2});

    Direction dir = RIGHT;

    // Initial food position (random)
    Vector2 food = { (float)((GetRandomValue(0, screenWidth / cellSize - 1)) * cellSize),
                     (float)((GetRandomValue(0, screenHeight / cellSize - 1)) * cellSize) };

    bool gameOver = false;

    while (!WindowShouldClose() && !gameOver) {
        // Input: change direction
        if (IsKeyPressed(KEY_UP) && dir != DOWN) dir = UP;
        else if (IsKeyPressed(KEY_DOWN) && dir != UP) dir = DOWN;
        else if (IsKeyPressed(KEY_LEFT) && dir != RIGHT) dir = LEFT;
        else if (IsKeyPressed(KEY_RIGHT) && dir != LEFT) dir = RIGHT;

        // Move snake by adding new head based on direction
        Vector2 newHead = snake.front();

        switch (dir) {
            case UP: newHead.y -= cellSize; break;
            case DOWN: newHead.y += cellSize; break;
            case LEFT: newHead.x -= cellSize; break;
            case RIGHT: newHead.x += cellSize; break;
        }

        // Check collisions with walls
        if (newHead.x < 0 || newHead.x >= screenWidth || newHead.y < 0 || newHead.y >= screenHeight) {
            gameOver = true;
        }

        // Check collision with self
        for (auto& segment : snake) {
            if (segment.x == newHead.x && segment.y == newHead.y) {
                gameOver = true;
                break;
            }
        }

        if (gameOver) break;

        snake.push_front(newHead);

        // Check if food eaten
        if (newHead.x == food.x && newHead.y == food.y) {
            // Spawn new food in a free spot
            bool validFood = false;
            while (!validFood) {
                food.x = (float)(GetRandomValue(0, screenWidth / cellSize - 1) * cellSize);
                food.y = (float)(GetRandomValue(0, screenHeight / cellSize - 1) * cellSize);
                validFood = true;
                for (auto& s : snake) {
                    if (s.x == food.x && s.y == food.y) {
                        validFood = false;
                        break;
                    }
                }
            }
        } else {
            // No food eaten, remove tail
            snake.pop_back();
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw food
        DrawRectangleV(food, { cellSize, cellSize }, RED);

        // Draw snake
        for (auto& segment : snake) {
            DrawRectangleV(segment, { cellSize, cellSize }, GREEN);
        }

        EndDrawing();
    }

    // Game Over screen
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Game Over! Press ESC to exit", 200, screenHeight / 2 - 20, 20, RAYWHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_ESCAPE)) break;
    }

    CloseWindow();

    return 0;
}
