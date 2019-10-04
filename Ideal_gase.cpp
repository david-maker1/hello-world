#include "TXLib.h"
#include "Windows.h"
#include <cmath>
#include <ctime>
#include "Vector.h"
const int v = 20;
const int w_size_x = 800;
const int w_size_y = 600;
const int N = 50;
const int v_max = 10;
const int R = 15 ;

struct Ball{
    float x = 400;
    float y = 300;
    int r = 20;
    float vx = 0;
    float vy = 0;
    float ax = 0;
    float ay = 0;
};


void drawBall(Ball* ball){
    int r = ball->r;
    int norm = r;
    txBegin();
    for (r; r>0; r--){
        txSetFillColor(RGB(255 - (r*255)/norm, 0, 0));
        txSetColor(RGB(255 - (r*255)/norm, 0, 0));

        txCircle(ball->x, ball->y, r);

    }
    txBegin();
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


int sign(int a){
    if (a >= 0){
        return 1;
    }
    else {
        return -1;
    }
}


void collide(Ball* ball1, Ball* ball2){
    Vector2f v1, v2, rad, n, e1, e2, r;
    e1.x = 1;
    e2.y = 1;
    if (pow((ball1->x - ball2->x), 2) + pow((ball1->y - ball2->y), 2) <= pow(2 * ball1->r, 2) - 5){
        v1.x = ball1->vx;
        v1.y = ball1->vy;
        v2.x = ball2->vx;
        v2.y = ball2->vy;
        rad.x = ball1->x - ball2->x;
        rad.y = ball1->y - ball2->y;
        r = normalize(rad);
        n.x = r.y;
        n.y = -r.x;


        ball1->vx = scalar( mul( n, scalar(v1, n) ), e1 ) - scalar( mul( r, scalar(v1, r) ), e1);
        ball1->vy = scalar( mul( n, scalar(v1, n) ), e2 ) - scalar( mul( r, scalar(v1, r) ), e2);
        ball2->vx = scalar( mul( n, scalar(v2, n) ), e1 ) - scalar( mul( r, scalar(v2, r) ), e1);
        ball2->vy = scalar( mul( n, scalar(v2, n) ), e2 ) - scalar( mul( r, scalar(v2, r) ), e2);


        ball1->x += sign( scalar(v1, n) ) * R * scalar( e1, r );
        ball1->y += sign( scalar(v1, n) ) * R * scalar( e2, r );
        ball2->x += -sign( scalar(v2, n) ) * R * scalar( e1, r );
        ball2->y += -sign( scalar(v2, n) ) * R * scalar( e2, r );

    }
}


int main(){
    txCreateWindow(w_size_x,w_size_y);
    Ball *ball = new Ball [N];
    srand( time( NULL ) );
    for (int i = 0; i < N; i++){
        ball[i].x = rand() %  ( w_size_x - ball[i].r + 1 ) ;
        ball[i].y = rand() %  ( w_size_y - ball[i].r + 1 ) ;

        ball[i].vx = rand() % v_max + 1;
        ball[i].vy = rand() % v_max + 1;
    }


    while(!GetAsyncKeyState( VK_SPACE )){

        for (int i = 0; i <= N; i++){
            for (int j = i; j <= N; j++){
                if ( i != j) {
                    collide(&ball[i], &ball[j]);
                }
            }
        }
        for (int i = 0; i < N; i++){
            ballReflection( &ball[i] );
            changeCoordinatesOfBall( &ball[i] );
        }



        txBegin();
        for (int i = 0; i < N; i++){
            drawBall( &ball[i] );
            txSetFillColor(RGB(0,0,0));
        }
        txSleep(15);
        txClear();
        txEnd();
    }
    delete [] ball;
    return 0;
}








