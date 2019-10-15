#include <iostream>
#include <cmath>
#ifndef Vector
#define Vector

struct Vector2f;

#endif


struct Vector2f{
    float x = 0;
    float y = 0;
    Vector2f operator+ ( Vector2f v2 );
    Vector2f operator- ( Vector2f v2 );
    Vector2f operator*( float a );
    float scalar ( Vector2f v2 );
    float modul ();
    Vector2f normalize ();
    Vector2f (float x, float y);
    Vector2f();
};


Vector2f::Vector2f(){
	this->x = 0;
	this->y = 0;
}


Vector2f::Vector2f(float x, float y){
	this->x = x;
	this->y = y;
}


Vector2f Vector2f::operator+ (Vector2f v2){
    return Vector2f(x + v2.x, y + v2.y);
}


Vector2f Vector2f::operator- (Vector2f v2){
    return Vector2f(x -  v2.x, y - v2.y);
}

Vector2f Vector2f::operator*(float a){
    return Vector2f(a * x, a * y );
}


float Vector2f::scalar (Vector2f v2){
    return x * v2.x + y * v2.y;
}


float Vector2f::modul (){
    return sqrt( scalar(*this ) );
}


Vector2f Vector2f::normalize (){
    return *this * (1/this->modul( ));
}
