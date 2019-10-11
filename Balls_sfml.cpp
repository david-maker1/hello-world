#include <cmath>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include "Vector.h"


const int v = 20;
const int w_size_x = 800;
const int w_size_y = 600;
const int N = 100;
const int R = 3;
const int v_max = 10;


struct Ball{
    float x = 0;
    float y = 0;
    int r = 10;
    float vx = 0.5;
    float vy = 0.5;
    float ax = 0;
    float ay  =0;
};


void drawBall( Ball ball, sf::RenderWindow* window ){
	sf::CircleShape shape( 200, 200 );
	for ( int i = ball.r; i > 1; i--){
                        shape.setRadius( i );
                        shape.setFillColor( sf::Color(255 - 255 * i / ball.r, 0, 0 ) );
                        shape.setPosition(  - i + ball.x,  - i + ball.y);
                        window->draw( shape );
                }
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


int abs(int a){
	return sqrt(a*a);
}



void collide(Ball* ball1, Ball* ball2){
         if (pow((ball1->x - ball2->x), 2) + pow((ball1->y - ball2->y), 2) <= pow(2 * ball1->r, 2)){
               	Vector2f v1, v2, rad, n, r, Vc, nv1, nv2, e1, e2;
		e1.x = 1;
		e2.y = 1;
		v1.x = ball1->vx;
                v1.y = ball1->vy;
                v2.x = ball2->vx;
                v2.y = ball2->vy;
                rad.x = ball2->x - ball1->x;
                rad.y = ball2->y - ball1->y;
                r = normalize(rad);
                n.x = r.y;
                n.y = -r.x;
		

		Vc = mul( sum( mul( v1, ball1->r), mul( v2, ball2->r) ), 1/(ball1->r + ball2->r));
		nv1 =sum( sum( mul( Vc, 2), mul( r, -scalar( r, v1) )), mul( n, scalar( n, v1)));
		nv2 =sum( sum( mul( Vc, 2), mul( r, -scalar( r, v2) )), mul( n, scalar( n, v2)));
		
		ball1->vx = nv1.x;
		ball1->vy = nv1.y;
		ball2->vx = nv2.x;
		ball2->vy = nv1.y;
		ball1->x -= R * scalar(e1, r);
		ball1->y -= R * scalar(e2, r);
	        ball2->x += R * scalar(e1, r);
                ball2->y += R * scalar(e2, r);	
	}
}







int main(){
	Ball *ball = new Ball[N];
	
	
	srand( time( NULL ) );
    	for (int i = 0; i < N; i++){
        	ball[i].x = rand() %  ( w_size_x - ball[i].r + 1 ) ;
        	ball[i].y = rand() %  ( w_size_y - ball[i].r + 1 ) ;

        	ball[i].vx = rand() % v_max + 1;
       	 	ball[i].vy = rand() % v_max + 1;
    	}


	sf::RenderWindow window ( sf::VideoMode (800, 600 ), "My window" );
	sf::CircleShape shape( 200,200);
	while ( window.isOpen() ){
		sf::Event event;
		while ( window.pollEvent( event ) ){
			if ( event.type ==sf:: Event::Closed) {
				window.close();
			}
		}


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


		window.clear();
		for (int i = 0; i < N; i++){
           		drawBall( ball[i], &window );
		}
		window.display();
		sf::sleep( sf::milliseconds(20));
	}


	delete [] ball;
	return 0;
}
				
