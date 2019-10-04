#include "TXLib.h"
#include "Windows.h"
#include <cmath>

const int v = 20;
const int w_size_x = 800;
const int w_size_y = 600;


struct Ball{
    float x = 400;
    float y = 300;
    int r = 50;
    float vx = 0;
    float vy = 0;
    float ax = 0;
    float ay = 0;
};


struct Platform{
    float x1 = 350;
    float y1 = 500;
    float x2 = 450;
    float y2 = 520;
    float vx = 0;
    int points = 0;
};


void drawBall(Ball ball){
    int r = ball.r;
    int norm = r;
    for (r; r>0; r--){
        txSetFillColor(RGB(255 - (r*255)/norm, 0, 0));
        txSetColor(RGB(255 - (r*255)/norm, 0, 0));
        txCircle(ball.x, ball.y, r);
    }
}


void drawPlatform(Platform platform){
    txSetFillColor(RGB(255, 211, 0));
    txSetColor(RGB(255, 211, 0));
    txRectangle(platform.x1, platform.y1, platform.x2, platform.y2);
}


void mooveBallByMouse(Ball* ball){
    int x,y;
    if (txMouseButtons() == 1){
        x = txMouseX();
        y = txMouseY();
        if(((x - ball->x)*(x - ball->x)+(y - ball->y)*(y - ball->y) != 0)){
            ball->vx = v*(x - ball->x)/sqrt((x - ball->x)*(x - ball->x)+(y - ball->y)*(y - ball->y));
            ball->vy = v*(y - ball->y)/sqrt((x - ball->x)*(x - ball->x)+(y - ball->y)*(y - ball->y));
        }
    }
   /* else{
        ball->vx = 0;
        ball->vy = 0;
    } */
}


void ballReflection(Ball* ball){
    if((ball->x <= ball->r)&&(ball->vx < 0)){
        ball->vx = -ball->vx;
        }
    if((ball->y <= ball->r)&&(ball->vy < 0)){
        ball->vy = -ball->vy;
        }
    if((ball->x >= w_size_x - ball->r)&&(ball->vx > 0)){
        ball->vx = -ball->vx;
        }
    if((ball->y >= w_size_y - ball->r)&&(ball->vy > 0)){
        ball->vy = -ball->vy;
        }
}


void changeCoordinatesOfBall(Ball* ball){
    ball->x += ball->vx;
    ball->y += ball->vy;
}


void moovePlatform(Platform* platform){
    if(GetAsyncKeyState( VK_LEFT )){
        platform->vx = -20;
    }
    if(GetAsyncKeyState( VK_RIGHT )){
        platform->vx = 20;
    }
    if ((!GetAsyncKeyState( VK_LEFT ))&&(!GetAsyncKeyState( VK_RIGHT ))){
        platform->vx = 0;
    }
}


void changeCoordinatesOfPlatform(Platform* platform){
    if((platform->x1 <= 0) && (platform->vx < 0)){
        platform->vx = 0;
    }
    if((platform->x2 >= 800) && (platform->vx > 0)){
        platform->vx = 0;
    }
    platform->x1 += platform->vx;
    platform->x2 += platform->vx;
}


void checkCollision(Ball* ball, Platform* platform){
    if ((ball->x >= platform->x1 - ball->r)&&(ball->x <= platform->x2 + ball->r)&&(ball->y >= platform->y1 - ball->r - 5)){
        ball->vy = -ball->vy;
        ball->y -= 20;
        platform->points++;
        platform->x1+=2;
        platform->x2-=2;
        std::cout<<platform->points<<" ";
    }
}


int main(){
    txCreateWindow(w_size_x,w_size_y);
    Ball ball;
    Platform platform;
    while(!GetAsyncKeyState( VK_SPACE )){
        mooveBallByMouse(&ball);
        ballReflection(&ball);
        checkCollision(&ball, &platform);
        changeCoordinatesOfBall(&ball);
        moovePlatform(&platform);
        changeCoordinatesOfPlatform(&platform);
        if (ball.y >= w_size_y - ball.r){
            std::cout<<"Player with a ball win!";
            break;
        }
        if (platform.points == 10){
            std::cout<<"Player with platform win!";
            break;
        }


        txBegin();

        drawBall(ball);
        drawPlatform(platform);
        txEnd();
        txSleep(1);
        txSetFillColor(RGB(0,0,0));
        txClear();
    }
    while(!GetAsyncKeyState( VK_SPACE )){
    }
    return 0;
}



















