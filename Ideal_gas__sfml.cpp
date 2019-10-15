#include <cmath>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include "Vector.h"


const int v = 20;
const int w_size_x = 800;
const int w_size_y = 600;
const int N = 200;
const int R = 3;
const int v_max = 10;


struct Ball{
    	Vector2f R = Vector2f();
    	Vector2f v = Vector2f();
   	int r = 10;
    	void drawBall(sf::RenderWindow* window );
	void ballReflection();
	void changeCoordinatesOfBall();
};


void Ball::drawBall(sf::RenderWindow* window){
	sf::CircleShape shape(200, 200);
	for (int i = this->r; i > 1; i--){
                        shape.setRadius( i );
                        shape.setFillColor( sf::Color(255 - 255 * i / r, 0, 0 ) );
                        shape.setPosition(  - i + this->R.x,  - i + this->R.y);
                        window->draw( shape );
                }
}


void Ball::ballReflection(){
	if((this->R.x <= this->r)&&(this->v.x < 0)){
		this->v.x = -this->v.x;
        }
	if((this->R.y <= this->r)&&(this->v.y < 0)){
        	this->v.y = -this->v.y;
        }
    	if((this->R.x >= w_size_x - this->r)&&(this->v.x > 0)){
        	this->v.x = -this->v.x;
        }
    	if((this->R.y >= w_size_y - this->r)&&(this->v.y > 0)){
        	this->v.y = -this->v.y;
        }
}


void Ball::changeCoordinatesOfBall(){
    	this->R.x += this->v.x;
    	this->R.y += this->v.y;
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
         if ((ball2->R - ball1->R).modul() <=ball1->r + ball2->r){     
		Vector2f e1 = Vector2f(1, 0);
		Vector2f e2 = Vector2f(0, 1);
                Vector2f r = Vector2f();
		r = (ball2->R - ball1->R).normalize();
                Vector2f n = Vector2f(-r.y, r.x);
		if(r.scalar(ball1->v - ball2->v) > 0 ){
			Vector2f Vc = Vector2f();			
			Vc = (ball1->v * ball1->r + ball2->v * ball2->r) * (1/(ball1->r + ball2->r));
			Vector2f nv1 = Vector2f();
			Vector2f nv2 = Vector2f();
			nv1 = Vc * 2 - r * ball1->v.scalar(r) + n * ball1->v.scalar(n);
			nv2 = Vc * 2 - r * ball2->v.scalar(r) + n * ball2->v.scalar(n);
			ball1->v = nv1;
			ball2->v = nv2;
			ball1->R.x -= R * e1.scalar(r);
			ball1->R.y -= R * e2.scalar(r);
	       		ball2->R.x += R * e1.scalar(r);
                	ball2->R.y += R * e2.scalar(r);	
		}
	}
}


int main(){
	Ball *ball = new Ball[N];
	
	
	srand( time( NULL ) );
    	for (int i = 0; i < N; i++){
        	ball[i].R.x = rand() %  ( w_size_x - ball[i].r + 1 ) ;
        	ball[i].R.y = rand() %  ( w_size_y - ball[i].r + 1 ) ;

        	ball[i].v.x = rand() % v_max + 1;
       	 	ball[i].v.y = rand() % v_max + 1;
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


		for (int i = 0; i < N; i++){
            		for (int j = i; j < N; j++){
               			if ( i != j) {
                    			collide(&ball[i], &ball[j]);
                		}		
            		}
        	}


		for (int i = 0; i < N; i++){
            		ball[i].ballReflection();
            		ball[i].changeCoordinatesOfBall();
		}


		window.clear();
		for (int i = 0; i < N; i++){
           		ball[i].drawBall(&window);
		}
		window.display();
		sf::sleep( sf::milliseconds(20));
	}


	delete [] ball;
	return 0;
}

