#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cmath>

// Namespace to contain all game logic and utilities
namespace MovingSquareGame {

// Forward declarations
struct Vector2D;
class PositionManager;
class InputHandler;
class Renderer;
class Game;

// ------------------
// Vector2D struct to store x, y coordinates (floats)
// ------------------
struct Vector2D {
    float x;
    float y;

    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float _x, float _y) : x(_x), y(_y) {}

    // Add another Vector2D to this one and return a new Vector2D
    Vector2D Add(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    // Subtract another Vector2D from this one
    Vector2D Subtract(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    // Scale vector by a factor
    Vector2D Scale(float factor) const {
        return Vector2D(x * factor, y * factor);
    }

    // Print vector coordinates (debug)
    void Print() const {
        std::cout << "Vector2D(" << x << ", " << y << ")" << std::endl;
    }
};

// ------------------
// Class to manage position of the square
// ------------------
class PositionManager {
private:
    Vector2D position;
public:
    PositionManager() : position(400.0f, 300.0f) {}

    // Get current position
    Vector2D GetPosition() const {
        return position;
    }

    // Set position explicitly
    void SetPosition(const Vector2D& pos) {
        position = pos;
    }

    // Move position by delta vector
    void MoveBy(const Vector2D& delta) {
        position = position.Add(delta);
    }
};

// ------------------
// Class to handle keyboard input and convert to movement vectors
// ------------------
class InputHandler {
public:
    InputHandler() {}

    // Get movement direction vector from WASD keys
    Vector2D GetMovementDirection() const {
        Vector2D dir(0.0f, 0.0f);

        if (IsKeyDown(KEY_W)) dir.y -= 1.0f;
        if (IsKeyDown(KEY_S)) dir.y += 1.0f;
        if (IsKeyDown(KEY_A)) dir.x -= 1.0f;
        if (IsKeyDown(KEY_D)) dir.x += 1.0f;

        // Normalize vector if not zero
        if (dir.x != 0.0f || dir.y != 0.0f) {
            float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            dir.x /= length;
            dir.y /= length;
        }

        return dir;
    }
};

// ------------------
// Class to render the game window and objects
// ------------------
class Renderer {
private:
    int screenWidth;
    int screenHeight;
    int squareSize;

public:
    Renderer(int width, int height, int sqSize) : screenWidth(width), screenHeight(height), squareSize(sqSize) {}

    // Initialize raylib window
    void InitializeWindow() const {
        InitWindow(screenWidth, screenHeight, "Unnecessarily Long Moving Square Game");
        SetTargetFPS(60);
    }

    // Close raylib window
    void CloseWindow() const {
        ::CloseWindow();
    }

    // Draw the blue square at position
    void DrawSquare(const Vector2D& position) const {
        DrawRectangle((int)position.x, (int)position.y, squareSize, squareSize, BLUE);
    }

    // Draw the background and UI elements
    void DrawUI() const {
        ClearBackground(RAYWHITE);
        DrawText("Use WASD to move the blue square", 10, 10, 20, DARKGRAY);
    }
};

// ------------------
// The main Game class tying all parts together
// ------------------
class Game {
private:
    PositionManager positionManager;
    InputHandler inputHandler;
    Renderer renderer;
    float moveSpeed;
public:
    Game() : renderer(800, 600, 50), moveSpeed(5.0f) {}

    void Run() {
        renderer.InitializeWindow();

        while (!WindowShouldClose()) {
            Update();
            Render();
        }

        renderer.CloseWindow();
    }

private:
    // Handle input and update game state
    void Update() {
        Vector2D movement = inputHandler.GetMovementDirection();
        Vector2D deltaMove = movement.Scale(moveSpeed);
        positionManager.MoveBy(deltaMove);
    }

    // Render everything
    void Render() {
        BeginDrawing();
        renderer.DrawUI();
        renderer.DrawSquare(positionManager.GetPosition());
        EndDrawing();
    }
};

} // namespace MovingSquareGame

int main() {
    MovingSquareGame::Game game;
    game.Run();
    return 0;
}
