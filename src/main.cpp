#include <iostream>
#include "raylib.h"

using namespace std;
int player_score = 0;
int computer_score = 0;
class Ball{
    public:
        float x, y;
        int speed_x, speed_y;
        int radius;
    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }

    void Update(){
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0 ){
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <=0){
            computer_score++;
            ResetBall();
        }
        if (x- radius<=0){
            player_score++;
            ResetBall();
        }
    }

    void ResetBall(){
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_choices[2] = {-1,1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];
    }
};

class Paddle{

    protected:
        void Limitmovement(){
            if ( y <= 0){
            y = 0;
        } 
            if (y + height >= GetScreenHeight()){
                y = GetScreenHeight() - height;
            }
        }

    
    public:
        float x,y;
        float width, height;
        int speed;

    void Draw(){
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update(){
        if (IsKeyDown(KEY_UP)){
            y = y - speed;
            
        } if (IsKeyDown(KEY_DOWN)){
            y = y + speed;

        }
        Limitmovement();
        
    }
};

class CPUPaddle: public Paddle{
    public:

    void Update(int ball_y){
        if(y + height/2 > ball_y){
            y=y - speed;
        }
        if (y + height/2 <= ball_y){
            y= y + speed; 
        }
        Limitmovement();
    }
};



Paddle player;
CPUPaddle computer;

Ball ball;

int main() {
    cout << "starting the game\n";
    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "My Pong Game");
    SetTargetFPS(60);
    ball.radius = 20;
    ball.x = screenWidth/2;
    ball.y = screenHeight/2; 
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight/2 - player.height/2;
    player.speed = 6;


    computer.width = 25;
    computer.height = 120;
    computer.x = 10;
    computer.y = screenHeight/2 - player.height/2;
    computer.speed = 6;
    while (WindowShouldClose() == false) {
        BeginDrawing();

        // Updating the ball
        ball.Update();
        player.Update();
        computer.Update(ball.y);

        // Checking for a collision
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
            
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{computer.x, computer.y, computer.width, computer.height}))
        {
            ball.speed_x *= -1;
        }

        // Drawing everything
        ClearBackground(BLACK);
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        
        ball.Draw();
        
        computer.Draw();
        player.Draw();
        DrawText(TextFormat("%i", computer_score), screenWidth/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screenWidth/4 - 20, 20, 80, WHITE);
        EndDrawing();
    }
    CloseWindow();

    cout << "Closing the game\n";


    return 0;
}