#include <raylib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

bool CheckCollision(Vector3 ball_properties, Vector3 paddle_properties, int paddle_width, int paddle_height) {
    // Check if ball's x is within paddle's horizontal range
    return (ball_properties.x >= paddle_properties.x && ball_properties.x <= paddle_properties.x + paddle_width &&
            // Check if ball's y is within paddle's vertical range
            ball_properties.y >= paddle_properties.y && ball_properties.y <= paddle_properties.y + paddle_height);
}

int main(){
    Vector2 window{800,700};
    InitWindow(window.x,window.y , "pong vs ai");
    SetTargetFPS(120);
    srand(time(0));  // Seed random number generator

    // paddles
    const int paddle_width = 20;
    const int paddle_height = 90;

    // ball 
    const int ball_radius = 10;

    //score
    int player_score = 0;
    int ai_score = 0;

    //player x ,y ,z(speed)
    Vector3 player_properties {10,300,5};
    

    //ai x ,y ,z(speed)
    Vector3 ai_properties {770,0,player_properties.z};

    //ball x ,y ,z(speed)
    Vector3 ball_properties {400,350,3};
    int direction = (rand() % 2) == 0 ? 1 : -1;
    Vector2 ball_velocity {ball_properties.z * direction, 0};

    while(WindowShouldClose() == false){
        // player logic
        if(IsKeyDown(KEY_UP)){
            player_properties.y -= player_properties.z;
        }else if(IsKeyDown(KEY_DOWN)){
            player_properties.y += player_properties.z;
        }  
        // ai logic
        if(ai_properties.y != ball_properties.y){
            ai_properties.y = ball_properties.y - 45;
        }

        // ball logic
        // speed 12, direction either +1 or -1
        // Move the ball sideways and up/down based on its speed
        ball_properties.x += ball_velocity.x;  
        ball_properties.y += ball_velocity.y;

        if (CheckCollision(ball_properties, player_properties, paddle_width, paddle_height)) {
            // When ball hits player paddle, make sure horizontal speed is positive (to the right)
            ball_velocity.x = fabs(ball_velocity.x);  
            ball_velocity.y = (rand() % 5 - 2);  
            // When the ball hits the player paddle, make it go right and pick a random up or down speed
        }

        if (CheckCollision(ball_properties, ai_properties, paddle_width, paddle_height)) {
            // When ball hits AI paddle, make sure horizontal speed is negative (to the left)
            ball_velocity.x = -fabs(ball_velocity.x); 
            ball_velocity.y = (rand() % 5 - 2);  
            // When the ball hits the AI paddle, make it go left and pick a random up or down speed
        }

        // Bounce off the top of the window
        if (ball_properties.y - ball_radius <= 0) {
            ball_velocity.y = fabs(ball_velocity.y);  // Make sure ball moves downwards
        }

        // Bounce off the bottom of the window
        if (ball_properties.y + ball_radius >= window.y) {
            ball_velocity.y = -fabs(ball_velocity.y); // Make sure ball moves upwards
        }



        // border collision
        if(player_properties.y <= 0) {
            player_properties.y += 10;
        }else if (player_properties.y >= 610){
            player_properties.y -=10;
        }
        

        // point system
        if(ball_properties.x <= 0){
            ball_properties.x = 400;
            ball_properties.y = 350;
            ball_velocity.y = 0;
            direction = (rand() % 2) == 0 ? 1 : -1;
            ai_score += 1;
        }if(ball_properties.x >= 800){
            ball_properties.x = 400;
            ball_properties.y = 350;
            ball_velocity.y = 0;
            direction = (rand() % 2) == 0 ? 1 : -1;
            player_score += 1;
        }

        BeginDrawing();
        // center line
        DrawRectangle(395,0 ,10,700 ,BLUE);
        // player
        DrawRectangle(player_properties.x,player_properties.y , paddle_width,paddle_height , WHITE);
        // ai
        DrawRectangle(ai_properties.x,ai_properties.y , 20,90 , WHITE);
        // ball
        DrawCircle(ball_properties.x ,ball_properties.y , 20 , WHITE);
        
        // point dysplay
        DrawText(TextFormat("%d",player_score) , 200,30 ,50 ,WHITE);
        DrawText(TextFormat("%d",ai_score) , 600,30 ,50 ,WHITE);

        // debug statments
        DrawText(TextFormat("ai y: %d",(int)ai_properties.y) , 10,680 ,15 ,WHITE);
        DrawText(TextFormat("player y: %d",(int)player_properties.y) , 100,680 ,15 ,WHITE);
        
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
